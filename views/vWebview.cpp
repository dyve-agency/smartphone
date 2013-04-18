#include "vWebview.h"
#include "../manager.h"
#include "../main.h"

using namespace View;
using namespace NativeUI;

const unsigned int Webview::mMainLayoutBgColor = 0x00333333;

Webview::Webview(Manager::Webview* manager) : manager(manager), Screen()
{
	createUI();

	mWebview->addWebViewListener(this);
}

Webview::~Webview()
{
	mWebview->removeWebViewListener(this);
}

void Webview::createUI()
{
	mMainLayout = new VerticalLayout();
	mMainLayout->fillSpaceHorizontally();
	mMainLayout->fillSpaceVertically();
	mMainLayout->setBackgroundColor(mMainLayoutBgColor);

	Screen::setMainWidget(mMainLayout);

	mWebview = new WebView();
	mWebview->fillSpaceHorizontally();
	mWebview->fillSpaceVertically();
	mMainLayout->addChild(mWebview);
}

void Webview::webViewContentLoading(WebView* webView, const int webViewState)
{
	if (webViewState == MAW_CONSTANT_DONE)
	{
		if (webView->getURL().find(manager->controller->pageCreateClient()) != MAUtil::String::npos)
		{
			const MAUtil::String& auth_token = Manager::main->mLogin.controller->getAuthToken();

			MAUtil::String JS = "var input = document.createElement('input'); input.setAttribute('value', '" + auth_token + "'); input.setAttribute('name', 'access_token'); input.setAttribute('type', 'hidden'); document.getElementById('new_client').appendChild(input);";
			mWebview->callJS(JS);
		}
		else if (webView->getURL().find(manager->controller->pageRegister()) == MAUtil::String::npos)
		{
			if (Manager::main->mLogin.controller->isAuthenticated())
				Manager::main->mClient.controller->actionClients();
			else
				Manager::main->mLogin.view->show();
		}
	}
}

void Webview::webViewHookInvoked(WebView* webView, int hookType, MAHandle urlData)
{

}
