#include "pch.h"
#include "MainPage.xaml.h"
#if __has_include("MainPage.g.cpp")
#include "MainPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::VisualWinUI3::implementation
{
    void MainPage::Refresh(const wchar_t* s)
    {
        m_propertyChanged(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ s });
    }

	void MainPage::OnNew(IInspectable const&, IInspectable const&)
	{
		winrt::VisualWinUI3::MainWindow CreateWi();
		CreateWi();

	}
	void MainPage::OnOpen(IInspectable const&, IInspectable const&)
	{

	}
	void MainPage::OnSave(IInspectable const&, IInspectable const&)
	{

	}
	void MainPage::OnExit(IInspectable const&, IInspectable const&)
	{
		PostMessage((HWND)wnd(), WM_CLOSE, 0, 0);
	}
	void MainPage::OnSaveAs(IInspectable const&, IInspectable const&)
	{

	}
 

}
