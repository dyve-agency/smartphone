#ifndef MANAGER_LOGIN_H
#define MANAGER_LOGIN_H

#include "controllers/cLogin.h"
#include "views/vLogin.h"

#include "views/vWorklog.h"

class ZeitkitTimer;

namespace Manager
{
	static ZeitkitTimer* main;

	class Login
	{
		public:
			Login() : view(new View::Login(this)), controller(new Controller::Login(this))  {}
			~Login() { free(); }
			void free() { delete controller; delete view; controller = NULL; view = NULL; }

			Controller::Login* controller;
			View::Login* view;
	};

	class Worklog
	{
		public:
			Worklog() : view(new View::Worklog(this)) {}
			~Worklog() { free(); }
			void free() { delete view; view = NULL; }

			//Controller::Worklog* controller;
			View::Worklog* view;
	};
}

#endif
