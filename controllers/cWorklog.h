#ifndef CONTROLLER_WORKLOG_H
#define CONTROLLER_WORKLOG_H

#include <maapi.h>
#include <MAUtil/util.h>
#include <mautil/connection.h>
#include <Wormhole/Encoder.h>
#include <mastdlib.h>
#include <conprint.h>

namespace Manager
{
	class Worklog;
}

namespace Controller
{
	class Worklog : private MAUtil::HttpConnectionListener
	{
		private:
			Manager::Worklog* manager;

			MAUtil::HttpConnection mHttp;
			char buffer[256];
			MAUtil::String result;

			static const char* qWorklog;

			virtual void httpFinished(MAUtil::HttpConnection* conn, int result);
			virtual void connRecvFinished(MAUtil::Connection* conn, int result);
			virtual void connWriteFinished(MAUtil::Connection* conn, int result);

		public:
			Worklog(Manager::Worklog* manager);
			~Worklog();

			void actionSubmit(unsigned int start, unsigned int end, unsigned int client, const MAUtil::String& reason);
	};
}

#endif
