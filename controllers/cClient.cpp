#include "cClient.h"
#include "../manager.h"
#include "../ext/json.h"
#include "../main.h"

using namespace Controller;

const char* Client::qClients = "clients.json";

Client::Client(Manager::Client* manager) : manager(manager), mHttp(this)
{

}

Client::~Client()
{

}

void Client::actionClients()
{
	if (!Manager::main->mLogin.controller->isAuthenticated())
		manager->view->callbackClients();

	memset(buffer, 0, sizeof(buffer));
	result = "";
	mClients.clear();

	int res = mHttp.create((MAUtil::String(Manager::main->host) + "/" + qClients + "?access_token=" + Manager::main->mLogin.controller->getAuthToken()).c_str(), HTTP_GET);

	if (res < 0)
	{
		Manager::main->mLogin.controller->removeAuth();
		manager->view->callbackClients();
		return;
	}

	mHttp.setRequestHeader("Accept", "application/json");
	mHttp.finish();
}

void Client::httpFinished(MAUtil::HttpConnection* conn, int result)
{
	if (result == 200)
		mHttp.recv(buffer, sizeof(buffer));
	else
	{
		mHttp.close();
		Manager::main->mLogin.controller->removeAuth();
		manager->view->callbackClients();
	}
}

void Client::connRecvFinished(MAUtil::Connection* conn, int result)
{
	if (result >= 0)
	{
		Client::result += MAUtil::String(buffer, result);
		mHttp.recv(buffer, sizeof(buffer));
		return;
	}

	mHttp.close();

	if (Client::result.length())
	{
		char* buffer = new char[Client::result.length()];
		strcpy(buffer, Client::result.c_str());

		char* errorPos = 0;
		char* errorDesc = 0;
		int errorLine = 0;
		block_allocator allocator(1 << 10);

		json_value* root = json_parse(buffer, &errorPos, &errorDesc, &errorLine, &allocator);

		if (root)
		{
			if (root->type == JSON_ARRAY)
                for (json_value* it = root->first_child; it; it = it->next_sibling)
                	if (it->type == JSON_OBJECT)
                	{
                		ClientData data;

                        for (json_value* it2 = it->first_child; it2; it2 = it2->next_sibling)
                        {
                        	if (!strcmp(it2->name, "name"))
                        		data.name = it2->string_value;
                        	else if (!strcmp(it2->name, "id"))
                        		data.id = it2->int_value;
                        }

                        mClients.add(data);
                	}
		}

		delete[] buffer;
	}

	manager->view->callbackClients();
}
