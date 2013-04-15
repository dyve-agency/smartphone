#include "Alert.h"

using namespace Utils;
using namespace NativeUI;

const char* Alert::mSubmitButtonLabel = "OK";

Alert::Alert(const char* mLabelText)
{
	createUI(mLabelText);

	mSubmitButton->addButtonListener(this);
}

Alert::~Alert()
{
	mSubmitButton->removeButtonListener(this);

	delete mDialog;
}

void Alert::createUI(const char* mLabelText)
{
	mDialog = new Dialog();
	mDialog->canBeDismissed(false);

	mMainLayout = new VerticalLayout();
	mMainLayout->fillSpaceHorizontally();
	mMainLayout->fillSpaceVertically();
	mDialog->setMainWidget(mMainLayout);

	mLabel = new Label();
	mLabel->fillSpaceHorizontally();
	mLabel->wrapContentVertically();
	mLabel->setText(mLabelText);
	mMainLayout->addChild(mLabel);

	mSubmitButton = new Button();
	mSubmitButton->fillSpaceHorizontally();
	mSubmitButton->wrapContentVertically();
	mSubmitButton->setTextHorizontalAlignment(MAW_ALIGNMENT_CENTER);
	mSubmitButton->setTextVerticalAlignment(MAW_ALIGNMENT_CENTER);
	mSubmitButton->setText(mSubmitButtonLabel);
	mMainLayout->addChild(mSubmitButton);
}
