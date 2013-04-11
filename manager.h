#ifndef MANAGER_LOGIN_H
#define MANAGER_LOGIN_H

#include "controllers/cLogin.h"
#include "views/vLogin.h"

#include "views/vWorklog.h"

class ZeitkitTimer;

namespace Manager
{
	class Login
	{
		public:
			Login(ZeitkitTimer* main) : main(main), view(new View::Login(this)), controller(new Controller::Login(this))  {}
			~Login() { free(); }
			void free() { delete controller; delete view; controller = NULL; view = NULL; }

			ZeitkitTimer* main;
			Controller::Login* controller;
			View::Login* view;
	};

	class Worklog
	{
		public:
			Worklog(ZeitkitTimer* main) : main(main), view(new View::Worklog(this)) {}
			~Worklog() { free(); }
			void free() { delete view; view = NULL; }

			ZeitkitTimer* main;
			//Controller::Worklog* controller;
			View::Worklog* view;
	};
}

#endif
