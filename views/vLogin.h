#ifndef VIEW_LOGIN_H
#define VIEW_LOGIN_H

#include <maapi.h>
#include <MAUtil/util.h>
#include <NativeUI/Widgets.h>

namespace Manager
{
	class Login;
}

namespace View
{
	class Login : public NativeUI::Screen, public NativeUI::ButtonListener, public NativeUI::EditBoxListener
	{
		private:
			Manager::Login* manager;

			NativeUI::VerticalLayout* mMainLayout;
			NativeUI::Label* mInstructions;
			NativeUI::EditBox* mMailBox;
			NativeUI::EditBox* mPasswordBox;
			NativeUI::Button* mSubmitButton;

			static unsigned int mMainLayoutBgColor;
			static const char* mInstructionsText;
			static const char* mSubmitButtonLabel;

			void createUI();

			virtual void buttonClicked(NativeUI::Widget* button);
			virtual void editBoxReturn(NativeUI::EditBox* editBox);

		public:
			Login(Manager::Login* manager);
			~Login();
	};
}

#endif
