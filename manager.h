#ifndef MANAGER_LOGIN_H
#define MANAGER_LOGIN_H

#include "controllers/cLogin.h"
#include "views/vLogin.h"

namespace Manager
{
	class Login
	{
		public:
			Login() : controller(new Controller::Login(this)), view(new View::Login(this)) {}
			~Login() { free(); }
			void free() { delete controller; delete view; controller = NULL; view = NULL; }

			Controller::Login* controller;
			View::Login* view;
	};
}

#endif
