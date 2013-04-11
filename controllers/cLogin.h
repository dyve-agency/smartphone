#ifndef CONTROLLER_LOGIN_H
#define CONTROLLER_LOGIN_H

#include <maapi.h>
#include <MAUtil/util.h>
#include <mautil/connection.h>
#include <mastdlib.h>
#include <conprint.h>

namespace Manager
{
	class Login;
}

namespace Controller
{
	class Login : private MAUtil::HttpConnectionListener
	{
		private:
			Manager::Login* manager;

			MAUtil::HttpConnection mHttp;
			MAUtil::String auth_token;
			char buffer[64]; // max response len
			bool connection;

			static const char* qLogin;

			virtual void httpFinished(MAUtil::HttpConnection* conn, int result);
			virtual void connReadFinished(MAUtil::Connection* conn, int result);
			virtual void connWriteFinished(MAUtil::Connection* conn, int result);

		public:
			Login(Manager::Login* manager);
			~Login();

			bool isAuthenticated() { return auth_token.size() > 0; }
			const MAUtil::String& getAuthToken() { return auth_token; }

			void actionSubmit(const MAUtil::String& mail, const MAUtil::String& pwd);
	};
}

#endif
