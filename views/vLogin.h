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
			NativeUI::Label* mStatus;
			NativeUI::EditBox* mMailBox;
			NativeUI::EditBox* mPasswordBox;
			NativeUI::Button* mSubmitButton;

			static const unsigned int mMainLayoutBgColor;
			static const char* mInstructionsText;
			static const char* mStatusText;
			static const unsigned int mStatusFontColor;
			static const char* mSubmitButtonLabel;
			static const char* mSubmitButtonErrorMissingMail;
			static const char* mSubmitButtonErrorMissingPwd;

			void createUI();

			virtual void buttonClicked(NativeUI::Widget* button);
			virtual void editBoxReturn(NativeUI::EditBox* editBox);

		public:
			Login(Manager::Login* manager);
			~Login();
	};
}

#endif
