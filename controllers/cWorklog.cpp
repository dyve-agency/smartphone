#include "cWorklog.h"
#include "../manager.h"
#include "../ext/json.h"
#include "../main.h"

using namespace Controller;

const char* Worklog::qWorklog = "worklogs.json";

Worklog::Worklog(Manager::Worklog* manager) : manager(manager), mHttp(this)
{

}

Worklog::~Worklog()
{

}

void Worklog::actionSubmit(unsigned int start, unsigned int end, unsigned int client, const MAUtil::String& reason)
{
	if (!Manager::main->mLogin.controller->isAuthenticated())
		manager->view->callbackWorklog(false);

	memset(buffer, 0, sizeof(buffer));
	result = "";

	int res = mHttp.create((MAUtil::String(Manager::main->host) + "/" + qWorklog + "?access_token=" + Manager::main->mLogin.controller->getAuthToken()).c_str(), HTTP_POST);

	if (res < 0)
	{
		manager->view->callbackWorklog(false);
		return;
	}

	static MAUtil::String jsonQuery;
	jsonQuery = "{\"worklog\": {\"from_date\": \"";

	MAPUtil::DateTime start_(start);
	MAPUtil::DateTime end_(end);

	char buf[64];
	sprintf(buf, "%02d/%02d/%04d", start_.getDay(), start_.getMonth(), start_.getYear() + 1900);

	jsonQuery += buf;
	jsonQuery += "\", \"from_time\": \"";

	sprintf(buf, "%02d:%02d:%02d", start_.getHour(), start_.getMinute(), start_.getSecond());

	jsonQuery += buf;
	jsonQuery += "\", \"to_date\": \"";

	sprintf(buf, "%02d/%02d/%04d", end_.getDay(), end_.getMonth(), end_.getYear() + 1900);

	jsonQuery += buf;
	jsonQuery += "\", \"to_time\": \"";

	sprintf(buf, "%02d:%02d:%02d", end_.getHour(), end_.getMinute(), end_.getSecond());

	jsonQuery += buf;
	jsonQuery += "\", \"summary\": " + Wormhole::Encoder::JSONStringify(reason.c_str()) + ", \"client_id\": \"";

	sprintf(buf, "%d", client);

	jsonQuery += buf;
	jsonQuery += "\"}, \"commit\": \"Create Worklog\"}";

	mHttp.setRequestHeader("Accept", "application/json");
	mHttp.setRequestHeader("Content-type", "application/json");

	sprintf(buf, "%d", jsonQuery.size());

	mHttp.setRequestHeader("Content-length", buf);

	mHttp.write(jsonQuery.c_str(), jsonQuery.size());
}

void Worklog::httpFinished(MAUtil::HttpConnection* conn, int result)
{
	if (result == 200 || result == 201)
		mHttp.recv(buffer, sizeof(buffer));
	else
	{
		mHttp.close();
		manager->view->callbackWorklog(false);
	}
}

void Worklog::connRecvFinished(MAUtil::Connection* conn, int result)
{
	if (result >= 0)
	{
		Worklog::result += MAUtil::String(buffer, result);
		mHttp.recv(buffer, sizeof(buffer));
		return;
	}

	mHttp.close();
/*
	char* errorPos = 0;
	char* errorDesc = 0;
	int errorLine = 0;
	block_allocator allocator(1 << 10);

	json_value* root = json_parse(buffer, &errorPos, &errorDesc, &errorLine, &allocator);
*/
	manager->view->callbackWorklog(true);
}

void Worklog::connWriteFinished(MAUtil::Connection* conn, int result)
{
	mHttp.finish();
}
