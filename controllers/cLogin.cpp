#include "cLogin.h"
#include "../manager.h"
#include "../ext/json.h"
#include "../main.h"

using namespace Controller;

const char* Login::qLogin = "sessions";

Login::Login(Manager::Login* manager) : manager(manager), mHttp(this)
{

}

Login::~Login()
{

}

void Login::actionSubmit(const MAUtil::String& mail, const MAUtil::String& pwd)
{
	auth_token = "";
	memset(buffer, 0, sizeof(buffer));

	int res = mHttp.create((MAUtil::String(manager->main->host) + "/" + qLogin).c_str(), HTTP_POST);

	if (res < 0)
		return;

	// escape input
	static MAUtil::String jsonQuery;
	jsonQuery = "{\"email\": \"" + mail + "\", \"password\": \"" + pwd + "\"}";

	mHttp.setRequestHeader("Accept", "application/json");
	mHttp.setRequestHeader("Content-type", "application/json");

	char buf[32];
	sprintf(buf, "%d", jsonQuery.size());

	mHttp.setRequestHeader("Content-length", buf);

	mHttp.write(jsonQuery.c_str(), jsonQuery.size());
}

void Login::httpFinished(MAUtil::HttpConnection* conn, int result)
{
	if (result == 200)
		mHttp.read(buffer, sizeof(buffer));
	else
	{
		mHttp.close();
		manager->view->callbackAuthentication();
	}
}

void Login::connReadFinished(MAUtil::Connection* conn, int result)
{
	mHttp.close();

	char* errorPos = 0;
	char* errorDesc = 0;
	int errorLine = 0;
	block_allocator allocator(1 << 10);

	json_value* root = json_parse(buffer, &errorPos, &errorDesc, &errorLine, &allocator);

	if (root)
		auth_token = root->first_child->string_value;

	manager->view->callbackAuthentication();
}

void Login::connWriteFinished(MAUtil::Connection* conn, int result)
{
	mHttp.finish();
}
