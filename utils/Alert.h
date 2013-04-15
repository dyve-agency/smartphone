#ifndef ALERT_H
#define ALERT_H

#include <maapi.h>
#include <MAUtil/util.h>
#include <NativeUI/Widgets.h>
#include <MAHeaders.h>

namespace Utils
{
	class Alert : public NativeUI::ButtonListener
	{
		private:
			private:
				NativeUI::Dialog* mDialog;
				NativeUI::VerticalLayout* mMainLayout;
				NativeUI::Label* mLabel;
				NativeUI::Button* mSubmitButton;

				static const char* mSubmitButtonLabel;

				void createUI(const char* mLabelText);

				virtual void buttonClicked(NativeUI::Widget* button) { mDialog->hide(); }

			public:
				Alert(const char* mLabelText);
				~Alert();

				void show() { mDialog->show(); }
				void hide() { mDialog->hide(); }
				void setText(const char* mLabelText) { mLabel->setText(mLabelText); }
	};
}

#endif
