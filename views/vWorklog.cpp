#include "vWorklog.h"
#include "../manager.h"

using namespace View;
using namespace NativeUI;

const unsigned int Worklog::mMainLayoutBgColor = 0x00EC5A47;
const char* Worklog::mInstructionsText = "Create a new worklog.";
const unsigned int Worklog::mInstructionsFontColor = 0x00FFFFFF;
const char* Worklog::mTrackerButtonLabel = "Stop tracking";
const char* Worklog::mStartTimeBoxPlaceholder = "Start time";
const char* Worklog::mEndTimeBoxPlaceholder = "End time";
const char* Worklog::mReasonBoxPlaceholder = "The reason, e.g. \"Finish feature 1.\"";
const char* Worklog::mSubmitButtonLabel = "Submit this worklog";

const char* Worklog::Dialog::mSubmitButtonLabel = "OK";

Worklog::Worklog(Manager::Worklog* manager) : manager(manager), Screen()
{
	createUI();

	mSubmitButton->addButtonListener(this);
	mTrackerButton->addButtonListener(this);
	mStartTimeBox->addEditBoxListener(this);
	mEndTimeBox->addEditBoxListener(this);
	mReasonBox->addEditBoxListener(this);
}

Worklog::~Worklog()
{
	mSubmitButton->removeButtonListener(this);
	mTrackerButton->removeButtonListener(this);
	mStartTimeBox->removeEditBoxListener(this);
	mEndTimeBox->removeEditBoxListener(this);
	mReasonBox->removeEditBoxListener(this);

	delete mStartTimeDialog;
	delete mEndTimeDialog;
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
	VerticalLayout* layout;
	DatePicker* date;
	TimePicker* time;
	Button* button;

	mMainLayout = new VerticalLayout();
	mMainLayout->fillSpaceHorizontally();
	mMainLayout->fillSpaceVertically();
	mMainLayout->setScrollable(true);
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
	mStartTimeBox->setMaxLength(0);
	mMainLayout->addChild(mStartTimeBox);

	mStartTimeDialog = new Worklog::Dialog(this);

	mEndTimeBox = new EditBox();
	mEndTimeBox->fillSpaceHorizontally();
	mEndTimeBox->wrapContentVertically();
	mEndTimeBox->setPlaceholder(mEndTimeBoxPlaceholder);
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
}

void Worklog::updateTime(Dialog* source)
{
	char time[64];
	source->timeToString(time, sizeof(time));
	(source == mStartTimeDialog ? mStartTimeBox : mEndTimeBox)->setPlaceholder(MAUtil::String(time) + (source == mStartTimeDialog ? " (start)" : " (end)"));
}

void Worklog::validateTime()
{
	if (mStartTimeDialog->timeToUnix() > mEndTimeDialog->timeToUnix())
	{
		mStartTimeDialog->timeFrom(mEndTimeDialog);
		updateTime(mStartTimeDialog);
	}
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
		validateTime();
	}
}

void Worklog::Dialog::buttonClicked(Widget* button)
{
	mDialog->hide();
	worklog->updateTime(this);
	worklog->validateTime();
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
	updateTime(mStartTimeDialog);
	Screen::show();
}

