#include "vLogin.h"
#include "../manager.h"

using namespace View;
using namespace NativeUI;

const unsigned int Login::mMainLayoutBgColor = 0x00EC5A47;
const char* Login::mInstructionsText = "Welcome to Zeitkit worklog tracker! Enter your login details below. If you don't have an account with us, our system will create one for you.";
const unsigned int Login::mInstructionsFontColor = 0x00FFFFFF;
const char* Login::mStatusText = "";
const unsigned int Login::mStatusFontColor = 0x00205081;
const char* Login::mMailBoxPlaceholder = "Your email here";
const char* Login::mPasswordBoxPlaceholder = "Your password here";
const char* Login::mSubmitButtonLabel = "Start now";
const char* Login::mSubmitButtonErrorMissingMail = "Please enter your e-mail address!";
const char* Login::mSubmitButtonErrorMissingPwd = "Please enter your password!";

Login::Login(Manager::Login* manager) : manager(manager), Screen()
{
	createUI();

	mSubmitButton->addButtonListener(this);
	mMailBox->addEditBoxListener(this);
	mPasswordBox->addEditBoxListener(this);
}

Login::~Login()
{
	mSubmitButton->removeButtonListener(this);
	mMailBox->removeEditBoxListener(this);
	mPasswordBox->removeEditBoxListener(this);
}

void Login::createUI()
{
	mMainLayout = new VerticalLayout();
	mMainLayout->fillSpaceHorizontally();
	mMainLayout->fillSpaceVertically();
	mMainLayout->setBackgroundColor(mMainLayoutBgColor);

	Screen::setMainWidget(mMainLayout);

	mLogo = new Image();
	mLogo->setImage(ZEITKIT_LOGO);
	mLogo->fillSpaceHorizontally();
	mLogo->setScaleMode(IMAGE_SCALE_PRESERVE_ASPECT);
	mMainLayout->addChild(mLogo);

	mInstructions = new Label();
	mInstructions->fillSpaceHorizontally();
	mInstructions->wrapContentVertically();
	mInstructions->setText(mInstructionsText);
	mInstructions->setFontColor(mInstructionsFontColor);
	mMainLayout->addChild(mInstructions);

	mStatus = new Label();
	mStatus->fillSpaceHorizontally();
	mStatus->wrapContentVertically();
	mStatus->setText(mStatusText);
	mStatus->setFontColor(mStatusFontColor);
	mMainLayout->addChild(mStatus);

	mMailBox = new EditBox();
	mMailBox->fillSpaceHorizontally();
	mMailBox->wrapContentVertically();
	mMailBox->setInputMode(EDIT_BOX_INPUT_MODE_EMAILADDR);
	mMailBox->setPlaceholder(mMailBoxPlaceholder);
	mMainLayout->addChild(mMailBox);

	mPasswordBox = new EditBox();
	mPasswordBox->fillSpaceHorizontally();
	mPasswordBox->wrapContentVertically();
	mPasswordBox->setInputFlag(EDIT_BOX_INPUT_FLAG_PASSWORD);
	mPasswordBox->setPlaceholder(mPasswordBoxPlaceholder);
	mMainLayout->addChild(mPasswordBox);

	mSubmitButton = new Button();
	mSubmitButton->fillSpaceHorizontally();
	mSubmitButton->wrapContentVertically();
	mSubmitButton->setTextHorizontalAlignment(MAW_ALIGNMENT_CENTER);
	mSubmitButton->setTextVerticalAlignment(MAW_ALIGNMENT_CENTER);
	mSubmitButton->setText(mSubmitButtonLabel);
	mMainLayout->addChild(mSubmitButton);
}

void Login::buttonClicked(Widget* button)
{
	if (button == mSubmitButton)
	{
		MAUtil::String mail = mMailBox->getText();
		MAUtil::String pwd = mPasswordBox->getText();

		if (!mail.length())
		{
			mStatus->setText(mSubmitButtonErrorMissingMail);
			return;
		}

		if (!pwd.length())
		{
			mStatus->setText(mSubmitButtonErrorMissingPwd);
			return;
		}

		mStatus->setText("");
		mMailBox->hideKeyboard();
		mPasswordBox->hideKeyboard();
		manager->controller->actionSubmit(mail, pwd);
	}
}

void Login::editBoxReturn(EditBox* editBox)
{
	mMailBox->hideKeyboard();
	mPasswordBox->hideKeyboard();
}

