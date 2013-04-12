#ifndef CONTROLLER_CLIENT_H
#define CONTROLLER_CLIENT_H

#include <maapi.h>
#include <MAUtil/util.h>
#include <mautil/connection.h>
#include <mastdlib.h>
#include <conprint.h>
#include <cstring>

namespace Manager
{
	class Client;
}

namespace Controller
{
	class Client : private MAUtil::HttpConnectionListener
	{
		public:
			struct ClientData
			{
				unsigned int id;
				MAUtil::String name;
			};

		private:
			Manager::Client* manager;

			MAUtil::HttpConnection mHttp;
			char buffer[256];
			MAUtil::String result;

			MAUtil::Vector<ClientData> mClients;

			static const char* qClients;

			virtual void httpFinished(MAUtil::HttpConnection* conn, int result);
			virtual void connRecvFinished(MAUtil::Connection* conn, int result);

		public:
			Client(Manager::Client* manager);
			~Client();

			const MAUtil::Vector<ClientData>& getClients() { return mClients; }
			const ClientData* getClient(unsigned int id)
			{
				MAUtil::Vector<ClientData>::iterator it;

				for (it = mClients.begin(); it != mClients.end(); ++it)
					if (it->id == id)
						return it;

				return NULL;
			}

			void actionClients();
	};
}

#endif
