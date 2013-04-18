#include "cLogin.h"
#include "../manager.h"
#include "../ext/json.h"
#include "../main.h"

using namespace Controller;

const char* Login::qLogin = "sessions";

Login::Login(Manager::Login* manager) : manager(manager), mHttp(this)
{
	MAHandle zeitstore = maOpenStore("ZeitkitTimer", 0);

	if (false && zeitstore != STERR_NONEXISTENT)
	{
		MAHandle authdata = maCreatePlaceholder();

		maReadStore(zeitstore, authdata);
		memset(buffer, 0, sizeof(buffer));
		maReadData(authdata, buffer, 0, maGetDataSize(authdata));

		auth_token = buffer;

		maDestroyObject(authdata);
		maCloseStore(zeitstore, 0);
	}
}

Login::~Login()
{

}

void Login::actionSubmit(const MAUtil::String& mail, const MAUtil::String& pwd)
{
	auth_token = "";
	memset(buffer, 0, sizeof(buffer));

	int res = mHttp.create((MAUtil::String(Manager::main->host) + "/" + qLogin).c_str(), HTTP_POST);

	if (res < 0)
	{
		manager->view->callbackAuthentication();
		return;
	}

	// escape input
	static MAUtil::String jsonQuery;
	jsonQuery = "{\"email\": " + Wormhole::Encoder::JSONStringify(mail.c_str()) + ", \"password\": " + Wormhole::Encoder::JSONStringify(pwd.c_str()) + "}";

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
	{
		auth_token = root->first_child->string_value;

		MAHandle zeitstore = maOpenStore("ZeitkitTimer", MAS_CREATE_IF_NECESSARY);
		MAHandle authdata = maCreatePlaceholder();

		maCreateData(authdata, auth_token.length());
		maWriteData(authdata, auth_token.c_str(), 0, auth_token.length());

		maWriteStore(zeitstore, authdata);

		maDestroyObject(authdata);
		maCloseStore(zeitstore, 0);
	}

	manager->view->callbackAuthentication();
}

void Login::connWriteFinished(MAUtil::Connection* conn, int result)
{
	mHttp.finish();
}
