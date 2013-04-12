#ifndef MAIN_H
#define MAIN_H

#include <ma.h>
#include <MAUtil/String.h>
#include <MAUtil/Moblet.h>
#include <NativeUI/Widgets.h>

#include "manager.h"

class ZeitkitTimer : public MAUtil::Moblet
{
	public:
		static const char* host;

		Manager::Worklog mWorklog;
		Manager::Client mClient;
		Manager::Login mLogin;

		ZeitkitTimer()
		{
			Manager::main = this;

			if (mLogin.controller->isAuthenticated())
				mClient.controller->actionClients();
			else
				mLogin.view->show();
		}

		virtual ~ZeitkitTimer()
		{

		}

		void ZeitkitTimer::closeEvent() GCCATTRIB(noreturn)
		{
			mLogin.free();
			mClient.free();
			mWorklog.free();
			close();
		}

		void ZeitkitTimer::keyPressEvent(int keyCode, int nativeCode)
		{
			if (MAK_BACK == keyCode)
				closeEvent();
		}
};

#endif
