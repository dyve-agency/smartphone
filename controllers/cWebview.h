#ifndef CONTROLLER_WEBVIEW_H
#define CONTROLLER_WEBVIEW_H

#include <maapi.h>
#include <MAUtil/util.h>

namespace Manager
{
	class Webview;
}

namespace Controller
{
	class Webview
	{
		private:
			Manager::Webview* manager;

			static const char* qCreateClient;
			static const char* qRegister;

		public:
			Webview(Manager::Webview* manager);
			~Webview();

			MAUtil::String pageCreateClient();
			MAUtil::String pageRegister();

			void actionCreateClient();
			void actionRegister();
	};
}

#endif
