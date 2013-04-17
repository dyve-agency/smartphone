#ifndef VIEW_WORKLOG_H
#define VIEW_WORKLOG_H

#include <maapi.h>
#include <MAUtil/util.h>
#include <NativeUI/Widgets.h>
#include <MAHeaders.h>
#include <MAP/DateTime.h>

#include "../utils/Alert.h"

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

					NativeUI::Date getDate() { return mDatePicker->getDate(); }
					void setDate(const NativeUI::Date& date) { mDatePicker->setDate(date); }
					int getHour() { return mTimePicker->getHour(); }
					void setHour(int hour) { mTimePicker->setHour(hour); }
					int getMinute() { return mTimePicker->getMinute(); }
					void setMinute(int minute) { mTimePicker->setMinute(minute); }

					void timeToString(char* buffer, unsigned int len)
					{
						// snprintf
						sprintf(buffer, "%02d.%02d.%04d %02d:%02d", mDatePicker->getDayOfMonth(), mDatePicker->getMonth(), mDatePicker->getYear(), mTimePicker->getHour(), mTimePicker->getMinute());
					}

					void timeToNow()
					{
						MAPUtil::DateTime now = MAPUtil::DateTime::now();

						NativeUI::Date date;
						date.day = now.getDay();
						date.month = now.getMonth();
						date.year = now.getYear() + 1900;

						setDate(date);
						setHour(now.getHour());
						setMinute(now.getMinute());
					}

					void timeFrom(Dialog* other)
					{
						setDate(other->getDate());
						setHour(other->getHour());
						setMinute(other->getMinute());
					}

					time_t timeToUnix()
					{
						NativeUI::Date date = getDate();
						MAPUtil::DateTime date_(date.year - 1900, date.month, date.day, getHour(), getMinute(), 0);
						return date_.getTicks();
					}
			};

			NativeUI::VerticalLayout* mMainLayout;
			NativeUI::Image* mLogo;
			NativeUI::Image* mSeparator;
			NativeUI::Label* mInstructions;
			NativeUI::Button* mClientButton;
			NativeUI::Button* mTrackerButton;
			NativeUI::EditBox* mStartTimeBox;
			Dialog* mStartTimeDialog;
			NativeUI::EditBox* mEndTimeBox;
			Dialog* mEndTimeDialog;
			NativeUI::EditBox* mReasonBox;
			NativeUI::Button* mSubmitButton;
			Utils::Alert* mAlertBox;

			static const unsigned int mMainLayoutBgColor;
			static const unsigned int mLogoWidth;
			static const unsigned int mLogoHeight;
			static const char* mInstructionsText;
			static const unsigned int mInstructionsFontColor;
			static const char* mClientButtonLabel;
			static const char* mTrackerButtonLabel;
			static const char* mStartTimeBoxPlaceholder;
			static const char* mEndTimeBoxPlaceholder;
			static const char* mReasonBoxPlaceholder;
			static const char* mSubmitButtonLabel;
			static const char* mAlertBoxSuccessLabel;
			static const char* mAlertBoxFailureLabel;
			static const char* mAlertBoxTimeErrorLabel;

			void createUI();
			void updateTime(Dialog* source);
			bool validateTime();

			virtual void buttonClicked(NativeUI::Widget* button);
			virtual void editBoxReturn(NativeUI::EditBox* editBox);
			virtual void editBoxEditingDidBegin(NativeUI::EditBox* editBox);

		public:
			Worklog(Manager::Worklog* manager);
			~Worklog();

			virtual void show();

			void callbackWorklog(bool success);
	};
}

#endif
