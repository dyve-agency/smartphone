#include "vWorklog.h"
#include "../manager.h"
#include "../main.h"

using namespace View;
using namespace NativeUI;

const unsigned int Worklog::mMainLayoutBgColor = 0x00333333;
const unsigned int Worklog::mLogoWidth = 143;
const unsigned int Worklog::mLogoHeight = 37;
const char* Worklog::mInstructionsText = "Create a new worklog for ";
const unsigned int Worklog::mInstructionsFontColor = 0x00FFFFFF;
const char* Worklog::mClientButtonLabel = "Change client";
const char* Worklog::mTrackerButtonLabel = "Stop tracking";
const char* Worklog::mStartTimeBoxPlaceholder = "Start time";
const unsigned int Worklog::mStartTimeBoxPlaceholderFontColor = 0x00FFFFFF;
const char* Worklog::mEndTimeBoxPlaceholder = "End time";
const unsigned int Worklog::mEndTimeBoxPlaceholderFontColor = 0x00FFFFFF;
const char* Worklog::mReasonBoxPlaceholder = "What did you do?\n* finish feature 1\n* fix bug 2\n* fix computer problem: restart";
const char* Worklog::mSubmitButtonLabel = "Submit this worklog";
const char* Worklog::mAlertBoxSuccessLabel = "Worklog has been successfully submitted!\nView a full list on Zeitkit.com.\n";
const char* Worklog::mAlertBoxFailureLabel = "Oops, something went wrong. Sorry!\n";
const char* Worklog::mAlertBoxTimeErrorLabel = "The end time time must be greater than the start time!\n";

const char* Worklog::Dialog::mSubmitButtonLabel = "OK";

Worklog::Worklog(Manager::Worklog* manager) : manager(manager), Screen()
{
	createUI();

	mSubmitButton->addButtonListener(this);
	mClientButton->addButtonListener(this);
	mTrackerButton->addButtonListener(this);
	mStartTimeBox->addEditBoxListener(this);
	mEndTimeBox->addEditBoxListener(this);
	mReasonBox->addEditBoxListener(this);
}

Worklog::~Worklog()
{
	mSubmitButton->removeButtonListener(this);
	mClientButton->removeButtonListener(this);
	mTrackerButton->removeButtonListener(this);
	mStartTimeBox->removeEditBoxListener(this);
	mEndTimeBox->removeEditBoxListener(this);
	mReasonBox->removeEditBoxListener(this);

	delete mStartTimeDialog;
	delete mEndTimeDialog;
	delete mAlertBox;
}

Worklog::Dialog::Dialog(Worklog::Worklog* worklog) : worklog(worklog)
{
	createUI();

	mSubmitButton->addButtonListener(this);
}

Worklog::Dialog::~Dialog()
{
	mSubmitButton->removeButtonListener(this);

	delete mDialog;
}

void Worklog::createUI()
{
	mMainLayout = new VerticalLayout();
	mMainLayout->fillSpaceHorizontally();
	mMainLayout->fillSpaceVertically();
	mMainLayout->setBackgroundColor(mMainLayoutBgColor);

	Screen::setMainWidget(mMainLayout);

	mLogo = new Image();
	mLogo->setImage(ZEITKIT_LOGO);
	mLogo->setWidth(mLogoWidth);
	mLogo->setHeight(mLogoHeight);
	mLogo->setScaleMode(IMAGE_SCALE_XY);
	mMainLayout->addChild(mLogo);

	mSeparator = new Image();
	mSeparator->setImage(SEPARATOR_LINE);
	mSeparator->fillSpaceHorizontally();
	mSeparator->setScaleMode(IMAGE_SCALE_XY);
	mMainLayout->addChild(mSeparator);

	mInstructions = new Label();
	mInstructions->fillSpaceHorizontally();
	mInstructions->wrapContentVertically();
	mInstructions->setText(mInstructionsText);
	mInstructions->setFontColor(mInstructionsFontColor);
	mMainLayout->addChild(mInstructions);

	mClientButton = new Button();
	mClientButton->fillSpaceHorizontally();
	mClientButton->wrapContentVertically();
	mClientButton->setTextHorizontalAlignment(MAW_ALIGNMENT_CENTER);
	mClientButton->setTextVerticalAlignment(MAW_ALIGNMENT_CENTER);
	mClientButton->setText(mClientButtonLabel);
	mMainLayout->addChild(mClientButton);

	mTrackerButton = new Button();
	mTrackerButton->fillSpaceHorizontally();
	mTrackerButton->wrapContentVertically();
	mTrackerButton->setTextHorizontalAlignment(MAW_ALIGNMENT_CENTER);
	mTrackerButton->setTextVerticalAlignment(MAW_ALIGNMENT_CENTER);
	mTrackerButton->setText(mTrackerButtonLabel);
	mMainLayout->addChild(mTrackerButton);

	mStartTimeBox = new EditBox();
	mStartTimeBox->fillSpaceHorizontally();
	mStartTimeBox->wrapContentVertically();
	mStartTimeBox->setPlaceholder(mStartTimeBoxPlaceholder);
	mStartTimeBox->setPlaceholderFontColor(mStartTimeBoxPlaceholderFontColor);
	mStartTimeBox->setMaxLength(0);
	mMainLayout->addChild(mStartTimeBox);

	mStartTimeDialog = new Worklog::Dialog(this);

	mEndTimeBox = new EditBox();
	mEndTimeBox->fillSpaceHorizontally();
	mEndTimeBox->wrapContentVertically();
	mEndTimeBox->setPlaceholder(mEndTimeBoxPlaceholder);
	mEndTimeBox->setPlaceholderFontColor(mEndTimeBoxPlaceholderFontColor);
	mEndTimeBox->setMaxLength(0);
	mMainLayout->addChild(mEndTimeBox);

	mEndTimeDialog = new Worklog::Dialog(this);

	mReasonBox = new EditBox(EDIT_BOX_MULTI_LINE);
	mReasonBox->fillSpaceHorizontally();
	mReasonBox->wrapContentVertically();
	mReasonBox->setPlaceholder(mReasonBoxPlaceholder);
	mReasonBox->setInputMode(EDIT_BOX_INPUT_MODE_ANY);
	mReasonBox->setLinesNumber(8);
	mMainLayout->addChild(mReasonBox);

	mSubmitButton = new Button();
	mSubmitButton->fillSpaceHorizontally();
	mSubmitButton->wrapContentVertically();
	mSubmitButton->setTextHorizontalAlignment(MAW_ALIGNMENT_CENTER);
	mSubmitButton->setTextVerticalAlignment(MAW_ALIGNMENT_CENTER);
	mSubmitButton->setText(mSubmitButtonLabel);
	mMainLayout->addChild(mSubmitButton);

	mAlertBox = new Utils::Alert("");

	mMainLayout->setScrollable(true);
}

void Worklog::updateTime(Dialog* source)
{
	char time[64];
	source->timeToString(time, sizeof(time));
	(source == mStartTimeDialog ? mStartTimeBox : mEndTimeBox)->setPlaceholder(MAUtil::String(time) + (source == mStartTimeDialog ? " (start)" : " (end)"));
}

bool Worklog::validateTime()
{
	return mStartTimeDialog->timeToUnix() <= mEndTimeDialog->timeToUnix();
}

void Worklog::Dialog::createUI()
{
	mDialog = new NativeUI::Dialog();
	mDialog->canBeDismissed(false);

	mMainLayout = new VerticalLayout();
	mMainLayout->fillSpaceHorizontally();
	mMainLayout->fillSpaceVertically();
	mDialog->setMainWidget(mMainLayout);

	mDatePicker = new DatePicker();
	mDatePicker->fillSpaceHorizontally();
	mDatePicker->wrapContentVertically();
	mMainLayout->addChild(mDatePicker);

	mTimePicker = new TimePicker();
	mTimePicker->fillSpaceHorizontally();
	mTimePicker->wrapContentVertically();
	mMainLayout->addChild(mTimePicker);

	mSubmitButton = new Button();
	mSubmitButton->fillSpaceHorizontally();
	mSubmitButton->wrapContentVertically();
	mSubmitButton->setTextHorizontalAlignment(MAW_ALIGNMENT_CENTER);
	mSubmitButton->setTextVerticalAlignment(MAW_ALIGNMENT_CENTER);
	mSubmitButton->setText(mSubmitButtonLabel);
	mMainLayout->addChild(mSubmitButton);
}

void Worklog::buttonClicked(Widget* button)
{
	if (button == mTrackerButton)
	{
		mEndTimeDialog->timeToNow();
		updateTime(mEndTimeDialog);

		if (!validateTime())
		{
			mStartTimeDialog->timeFrom(mEndTimeDialog);
			updateTime(mStartTimeDialog);
		}
	}
	else if (button == mClientButton)
		Manager::main->mClient.view->show();
	else if (button == mSubmitButton)
	{
		unsigned int start = mStartTimeDialog->timeToUnix();
		unsigned int end = mEndTimeDialog->timeToUnix();

		if (start == end)
		{
			mAlertBox->setText(mAlertBoxTimeErrorLabel);
			mAlertBox->show();
			return;
		}

		mSubmitButton->setEnabled(false);
		manager->controller->actionSubmit(start, end, Manager::main->mClient.view->getSelectedClient(), mReasonBox->getText());
	}
}

void Worklog::Dialog::buttonClicked(Widget* button)
{
	mDialog->hide();

	Dialog* other = this == worklog->mEndTimeDialog ? worklog->mStartTimeDialog : worklog->mEndTimeDialog;

	worklog->updateTime(this);

	if (!worklog->validateTime())
	{
		other->timeFrom(this);
		worklog->updateTime(other);
	}
}

void Worklog::editBoxReturn(EditBox* editBox)
{

}

void Worklog::editBoxEditingDidBegin(EditBox* editBox)
{
	if (editBox == mStartTimeBox)
	{
		mStartTimeBox->hideKeyboard();
		mStartTimeDialog->show();
	}
	else if (editBox == mEndTimeBox)
	{
		mEndTimeBox->hideKeyboard();
		mEndTimeDialog->show();
	}
}

void Worklog::show()
{
	mStartTimeDialog->timeToNow();
	mEndTimeDialog->timeToNow();
	updateTime(mStartTimeDialog);
	mEndTimeBox->setPlaceholder(mEndTimeBoxPlaceholder);

	mInstructions->setText(MAUtil::String(mInstructionsText) + Manager::main->mClient.controller->getClient(Manager::main->mClient.view->getSelectedClient())->name + ".");

	Screen::show();
}

void Worklog::callbackWorklog(bool success)
{
	mSubmitButton->setEnabled(true);

	if (success)
	{
		mReasonBox->setText("");
		mStartTimeDialog->timeToNow();
		mEndTimeDialog->timeToNow();
		updateTime(mStartTimeDialog);
		mEndTimeBox->setPlaceholder(mEndTimeBoxPlaceholder);

		mAlertBox->setText(mAlertBoxSuccessLabel);
	}
	else
		mAlertBox->setText(mAlertBoxFailureLabel);

	mAlertBox->show();
}
