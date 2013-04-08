#include "vLogin.h"
#include "../manager.h"

using namespace View;
using namespace NativeUI;

unsigned int Login::mMainLayoutBgColor = 0x00EC5A47;
const char* Login::mInstructionsText = "Welcome to Zeitkit worklog tracker! Enter your login details below. If you don't have an account with us, our system will create one for you.";
const char* Login::mSubmitButtonLabel = "Submit";

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

	mInstructions = new Label();
	mInstructions->fillSpaceHorizontally();
	mInstructions->wrapContentVertically();
	mInstructions->setText(mInstructionsText);
	mMainLayout->addChild(mInstructions);

	mMailBox = new EditBox();
	mMailBox->fillSpaceHorizontally();
	mMailBox->wrapContentVertically();
	mMailBox->setInputMode(EDIT_BOX_INPUT_MODE_EMAILADDR);
	mMainLayout->addChild(mMailBox);

	mPasswordBox = new EditBox();
	mPasswordBox->fillSpaceHorizontally();
	mPasswordBox->wrapContentVertically();
	mPasswordBox->setInputFlag(EDIT_BOX_INPUT_FLAG_PASSWORD);
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
		mMailBox->hideKeyboard();
		mPasswordBox->hideKeyboard();

		manager->controller->actionSubmit();
	}
}

void Login::editBoxReturn(EditBox* editBox)
{
	mMailBox->hideKeyboard();
	mPasswordBox->hideKeyboard();

	manager->controller->actionSubmit();
}
