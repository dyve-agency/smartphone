#include <ma.h>
#include <MAUtil/String.h>
#include <MAUtil/Moblet.h>
#include <NativeUI/Widgets.h>

#include "views/login.h"

using namespace MAUtil;
using namespace NativeUI;

class ZeitkitTimer : public Moblet
{
	private:
		View::Login* mLoginScreen;

	public:
		ZeitkitTimer()
		{
			mLoginScreen = new View::Login();
			mLoginScreen->show();
		}

		virtual ~ZeitkitTimer()
		{
			delete mLoginScreen;
		}

		void ZeitkitTimer::closeEvent() GCCATTRIB(noreturn)
		{
			delete mLoginScreen;
			mLoginScreen = NULL;

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
