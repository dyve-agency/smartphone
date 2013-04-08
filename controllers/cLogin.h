#ifndef CONTROLLER_LOGIN_H
#define CONTROLLER_LOGIN_H

#include <maapi.h>
#include <MAUtil/util.h>

namespace Manager
{
	class Login;
}

namespace Controller
{
	class Login
	{
		private:
			Manager::Login* manager;

		public:
			Login(Manager::Login* manager);
			~Login();

			void actionSubmit();
	};
}

#endif
