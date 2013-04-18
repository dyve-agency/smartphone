#ifndef VIEW_WEBVIEW_H
#define VIEW_WEBVIEW_H

#include <maapi.h>
#include <MAUtil/util.h>
#include <NativeUI/Widgets.h>
#include <MAHeaders.h>

namespace Manager
{
	class Webview;
}

namespace View
{
	class Webview : public NativeUI::Screen, public NativeUI::WebViewListener
	{
		private:
			Manager::Webview* manager;

			NativeUI::VerticalLayout* mMainLayout;
			NativeUI::WebView* mWebview;

			static const unsigned int mMainLayoutBgColor;

			void createUI();

			virtual void webViewContentLoading(NativeUI::WebView* webView, const int webViewState);

		public:
			Webview(Manager::Webview* manager);
			~Webview();

			void callJS(const MAUtil::String& JS) { mWebview->callJS(JS); }
			void openURL(const MAUtil::String& url) { mWebview->openURL(url); }
	};
}

#endif
