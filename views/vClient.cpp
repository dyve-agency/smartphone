#include "vClient.h"
#include "../manager.h"
#include "../main.h"

using namespace View;
using namespace NativeUI;

const unsigned int Client::mMainLayoutBgColor = 0x00EC5A47;
const char* Client::mInstructionsText = "Select a client below.";
const unsigned int Client::mInstructionsFontColor = 0x00FFFFFF;
const unsigned int Client::mClientListFontColor = 0x00FFFFFF;
const char* Client::mAlertBoxNoClientsLabel = "You have not yet created a client. Please do so on zeitkit.com first.\n";

Client::Client(Manager::Client* manager) : manager(manager), mSelectedClient(0), Screen()
{
	createUI();

	mClientList->addListViewListener(this);
}

Client::~Client()
{
	mClientList->removeListViewListener(this);

	delete mAlertBox;
}

void Client::createUI()
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

	mClientList = new ListView();
	mClientList->fillSpaceHorizontally();
	mClientList->fillSpaceVertically();
	mMainLayout->addChild(mClientList);

	mAlertBox = new Utils::Alert(mAlertBoxNoClientsLabel);

	//mMainLayout->setScrollable(true);
}

void Client::listViewItemClicked(ListView* listView, ListViewItem* listViewItem)
{
	mSelectedClient = reinterpret_cast<unsigned int>(listViewItem->getData());
	Manager::main->mWorklog.view->show();
}

void Client::show()
{
	MAUtil::Vector<ListViewItem*>::iterator it;

	for (it = mClients.begin(); it != mClients.end(); ++it)
		mClientList->removeChild(*it);

	mClients.clear();

	const MAUtil::Vector<Controller::Client::ClientData>& clients = manager->controller->getClients();
	MAUtil::Vector<Controller::Client::ClientData>::const_iterator it2;

	for (it2 = clients.begin(); it2 != clients.end(); ++it2)
	{
		ListViewItem* item = new ListViewItem();
		item->setData(reinterpret_cast<void*>(it2->id));
		item->setText(it2->name);
		item->setFontColor(mClientListFontColor);
		mClientList->addChild(item);
		mClients.add(item);
	}

	mClientList->requestFocus();
	Screen::show();
}

void Client::callbackClients()
{
	if (!Manager::main->mLogin.controller->isAuthenticated())
		Manager::main->mLogin.view->show();
	else if (!manager->controller->getClients().size())
	{
		Manager::main->mLogin.view->show();
		mAlertBox->show();
	}
	else
		show();
}
