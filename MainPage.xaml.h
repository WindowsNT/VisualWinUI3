#pragma once

#include "MainPage.g.h"
#include "BlankWindow.g.h"
#include "project.h"

namespace winrt::VisualWinUI3::implementation
{
    struct MainPage : MainPageT<MainPage>
    {
        MainPage()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        winrt::event_token PropertyChanged(winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
        {
            return m_propertyChanged.add(handler);
        }
        void PropertyChanged(winrt::event_token const& token) noexcept
        {
            m_propertyChanged.remove(token);
        }
        static winrt::hstring txt(long jx)
        {
            return s(jx);
        }

		long long _wnd = 0;
        long long wnd()
        {
            return _wnd;
        }

		void wnd(long long value)
		{
			_wnd = value;
		}

        winrt::event<Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;
        void Refresh(std::vector<std::wstring> strs);
        void Refresh(const wchar_t* s = L"");
        void OnNew(IInspectable const&, IInspectable const&);
        void OnOpen(IInspectable const&, IInspectable const&);
        void OnSave(IInspectable const&, IInspectable const&);
        void OnExit(IInspectable const&, IInspectable const&);
        void OnSaveAs(IInspectable const&, IInspectable const&);

     

    };
}

namespace winrt::VisualWinUI3::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {
    };
}
