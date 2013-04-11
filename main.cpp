#include "main.h"

using namespace MAUtil;
using namespace NativeUI;

extern "C" int MAMain()
{
	ZeitkitTimer* zeitkit = new ZeitkitTimer();
	Moblet::run(zeitkit);
	delete zeitkit;
	return 0;
}
