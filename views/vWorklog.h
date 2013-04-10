#ifndef VIEW_WORKLOG_H
#define VIEW_WORKLOG_H

#include <maapi.h>
#include <MAUtil/util.h>
#include <NativeUI/Widgets.h>
#include <MAHeaders.h>

namespace Manager
{
	class Worklog;
}

namespace View
{
	class Worklog : public NativeUI::Screen, public NativeUI::ButtonListener, public NativeUI::EditBoxListener
	{
		private:
			Manager::Worklog* manager;

			class Dialog : public NativeUI::ButtonListener
			{
				private:
					Worklog* worklog;
					NativeUI::Dialog* mDialog;
					NativeUI::VerticalLayout* mMainLayout;
					NativeUI::DatePicker* mDatePicker;
					NativeUI::TimePicker* mTimePicker;
					NativeUI::Button* mSubmitButton;

					static const char* mSubmitButtonLabel;

					void createUI();

					virtual void buttonClicked(NativeUI::Widget* button);

				public:
					Dialog(Worklog* worklog);
					~Dialog();

					void show() { mDialog->show(); }
					void hide() { mDialog->hide(); }
			};

			NativeUI::VerticalLayout* mMainLayout;
			NativeUI::Image* mLogo;
			NativeUI::Label* mInstructions;
			NativeUI::Button* mTrackerButton;
			NativeUI::EditBox* mStartTimeBox;
			Dialog* mStartTimeDialog;
			NativeUI::EditBox* mEndTimeBox;
			Dialog* mEndTimeDialog;
			NativeUI::EditBox* mReasonBox;
			NativeUI::Button* mSubmitButton;

			static const unsigned int mMainLayoutBgColor;
			static const char* mInstructionsText;
			static const unsigned int mInstructionsFontColor;
			static const char* mTrackerButtonLabel;
			static const char* mStartTimeBoxPlaceholder;
			static const char* mEndTimeBoxPlaceholder;
			static const char* mReasonBoxPlaceholder;
			static const char* mSubmitButtonLabel;

			void createUI();

			virtual void buttonClicked(NativeUI::Widget* button);
			virtual void editBoxReturn(NativeUI::EditBox* editBox);
			virtual void editBoxEditingDidBegin(NativeUI::EditBox* editBox);

		public:
			Worklog(Manager::Worklog* manager);
			~Worklog();
	};
}

#endif
