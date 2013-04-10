#include <ma.h>
#include <MAUtil/String.h>
#include <MAUtil/Moblet.h>
#include <NativeUI/Widgets.h>

#include "manager.h"

using namespace MAUtil;
using namespace NativeUI;

class ZeitkitTimer : public Moblet
{
	private:
		Manager::Login mLogin;
		Manager::Worklog mWorklog;

	public:
		ZeitkitTimer()
		{
			mLogin.view->show();
		}

		virtual ~ZeitkitTimer()
		{

		}

		void ZeitkitTimer::closeEvent() GCCATTRIB(noreturn)
		{
			mLogin.free();
			mWorklog.free();
			close();
		}

		void ZeitkitTimer::keyPressEvent(int keyCode, int nativeCode)
		{
			if (MAK_BACK == keyCode)
				closeEvent();
		}
};

extern "C" int MAMain()
{
	ZeitkitTimer* zeitkit = new ZeitkitTimer();
	Moblet::run(zeitkit);
	delete zeitkit;
	return 0;
}
