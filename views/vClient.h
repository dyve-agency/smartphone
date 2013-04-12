#ifndef CLIENT_LOGIN_H
#define CLIENT_LOGIN_H

#include <maapi.h>
#include <MAUtil/util.h>
#include <NativeUI/Widgets.h>
#include <MAHeaders.h>

namespace Manager
{
	class Client;
}

namespace View
{
	class Client : public NativeUI::Screen, public NativeUI::ListViewListener
	{
		private:
			Manager::Client* manager;

			NativeUI::VerticalLayout* mMainLayout;
			NativeUI::Image* mLogo;
			NativeUI::Label* mInstructions;
			NativeUI::ListView* mClientList;

			MAUtil::Vector<NativeUI::ListViewItem*> mClients;
			unsigned int mSelectedClient;

			static const unsigned int mMainLayoutBgColor;
			static const char* mInstructionsText;
			static const unsigned int mInstructionsFontColor;
			static const unsigned int mClientListFontColor;

			void createUI();

			virtual void listViewItemClicked(NativeUI::ListView* listView, NativeUI::ListViewItem* listViewItem);

		public:
			Client(Manager::Client* manager);
			~Client();

			virtual void show();

			unsigned int getSelectedClient() { return mSelectedClient; }
			void callbackClients();
	};
}

#endif
