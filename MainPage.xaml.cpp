#include "pch.h"
#include "MainPage.xaml.h"
#if __has_include("MainPage.g.cpp")
#include "MainPage.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Microsoft::UI::Xaml::Controls;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::VisualWinUI3::implementation
{
    void MainPage::Refresh(const wchar_t* s)
    {
        m_propertyChanged(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ s });
    }
	void MainPage::Refresh2(winrt::hstring s)
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
		if (!project)
			return;
		if (!project->root)
			return;
		if (project->file.empty())
		{
			OnSaveAs(nullptr, nullptr);
			return;
		}
		DeleteFile(project->file.c_str());
		XML3::XML x(project->file.c_str());
		project->Ser(x.GetRootElement());
		x.Save();
	}
	void MainPage::OnExit(IInspectable const&, IInspectable const&)
	{
		PostMessage((HWND)wnd(), WM_CLOSE, 0, 0);
	}
	void MainPage::OnSaveAs(IInspectable const&, IInspectable const&)
	{
		OPENFILENAME of = { 0 };
		of.lStructSize = sizeof(of);
		of.hwndOwner = (HWND)0;
		of.lpstrFilter = L"*.vwui3\0*.vwui3\0\0";
		std::vector<wchar_t> fnx(10000);
		of.lpstrFile = fnx.data();
		of.nMaxFile = 10000;
		of.lpstrDefExt = L"vwui3";
		of.Flags = OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;
		if (!GetSaveFileName(&of))
			return;
		project->file = fnx.data();
		if (project->file.empty())
			return;
		OnSave(nullptr, nullptr);
	}
 


	void MainPage::Build(UIElement iroot, std::shared_ptr<XITEM> root)
	{
		if (!root || !iroot)
			return;

		auto ni = root->Create();
		if (!ni)
			return;

		root->ApplyProperties();

		// Add to panel
		auto ipanel = iroot.as<Panel>();
		if (!ipanel)
			return;
		auto chi = ipanel.Children();
		auto sz = chi.Size();
		chi.Clear();
		chi = ipanel.Children();
		sz = chi.Size();
		chi.Append(ni.as<UIElement>());

		for (auto& r : root->children)
		{
			Build(ni,r);
		}
	}

	void MainPage::PageLoaded(IInspectable const&, IInspectable const&)
	{
		if (__argc > 1)
		{
			if (!project)
				project = std::make_shared<PROJECT>();
			if (GetFileAttributes(__wargv[1]) == 0xFFFFFFFF)
				return;
			project->file = __wargv[1];
			XML3::XML xx(project->file.c_str());
			project->Unser(*xx.GetRootElement().GetChildren()[0]);
			Build();
		}
	}

	void MainPage::Build()
	{
		auto topnv = Content().as<Panel>();
		auto root = topnv.FindName(L"PutRoot").as<StackPanel>();
		if (!project)
			return;
		if (!project->root)
			return;
		Build(root,project->root);
		Refresh(L"PropertyItems");
		Refresh(L"PropertyTypeSelector");
	}

	

	winrt::Microsoft::UI::Xaml::Controls::DataTemplateSelector MainPage::PropertyTypeSelector()
	{
		auto m = VisualWinUI3::ItemSelector();
		return m;
	}

	winrt::Windows::Foundation::Collections::IObservableVector<winrt::VisualWinUI3::Item> MainPage::PropertyItems()
	{
		auto children = single_threaded_observable_vector<VisualWinUI3::Item>();
		if (!SelectedItem)
			return children;

		// Put the properties of this item
		for (auto pro : SelectedItem->properties)
		{
			auto double_type = std::dynamic_pointer_cast<DOUBLE_PROPERTY>(pro);
			if (double_type)
			{
				VisualWinUI3::Item item;
				item.PropertyX((long long)double_type.get());
				item.Type(PT_DOUBLE);
				item.Name1(pro->n);
				item.Number0(double_type->value);
				item.Number1(double_type->mmin);
				item.Number2(double_type->mmax);
				children.Append(item);
			}
			auto list_type = std::dynamic_pointer_cast<LIST_PROPERTY>(pro);
			if (list_type)
			{
				VisualWinUI3::Item item;
				item.PropertyX((long long)list_type.get());
				item.Type(PT_LIST);
				auto its = item.xitems();
				for(auto& e : list_type->Items)
				{
					its.Append(e.c_str());
				}
				item.Name1(pro->n);
				children.Append(item);
			}
		}

		return children;
	}


	void MainPage::E_XAML(IInspectable const&, IInspectable const&)
	{
		if (!project)
			return;
		if (!project->root)
			return;

		auto el = project->root->SaveEl();
		auto s = el.Serialize();
		MessageBoxA(0, s.c_str(), 0, 0);
	}

	void MainPage::I_StackPanel(IInspectable const&, IInspectable const&)
	{
		if (!project)
			project = std::make_shared<PROJECT>();
		if (!project->root)
		{
			project->root = std::make_shared<ITEM_STACKPANEL>();
			SelectedItem = project->root;
		}
		else
		if (SelectedItem)
		{
			auto j = std::make_shared<ITEM_STACKPANEL>();
			SelectedItem->children.push_back(j);
			SelectedItem = j;
		}
		Build();
	}

	void MainPage::I_Button(IInspectable const&, IInspectable const&)
	{
		if (!project) return;
		if (!project->root) return;
		if (!SelectedItem) return;

		auto j = std::make_shared<ITEM_BUTTON>();
		SelectedItem->children.push_back(j);
		SelectedItem = j;
		Build();
	}

}



extern std::map<HWND, winrt::Windows::Foundation::IInspectable> windows;

void UnselectAll(std::shared_ptr<XITEM> r)
{
	if (!r)
		return;

	r->Unselect();
	for (auto& c : r->children)
	{
		UnselectAll(c);
	}
}

bool RootLoop(std::shared_ptr<XITEM> r, XITEM* xit)
{
	if (!r || !xit)
		return false;

	if (r.get() == xit)
	{
		SelectedItem = r;
		SelectedItem->Select();
		return true;
	}

	for (auto& c : r->children)
	{
		if (RootLoop(c, xit))
			return true;
	}
	return false;
}
void GenericTap(winrt::Windows::Foundation::IInspectable it)
{
	for (auto& wi : windows)
	{
		auto the_window = wi.second.as<winrt::VisualWinUI3::MainWindow>();

		// Find the MainPage for it
		auto tnv = the_window.Content().as<winrt::Microsoft::UI::Xaml::Controls::NavigationView>();
		if (!tnv)
			continue;

		auto fr = tnv.FindName(L"contentFrame").as<winrt::Microsoft::UI::Xaml::Controls::Frame>();
		if (!fr)
			continue;
		auto main_page = fr.Content().as<winrt::VisualWinUI3::MainPage>();
		if (!main_page)
			continue;


		auto ui = it.as<winrt::Microsoft::UI::Xaml::FrameworkElement>();
		if (!ui)
			continue;

		auto Tag = winrt::unbox_value<long long>(ui.Tag());
		if (!Tag)
			continue;

		XITEM* ir = (XITEM*)Tag;
		if (!ir)
			continue;

		PROJECT* prj = (PROJECT*)main_page.ProjectPtr();
		if (!prj)
			continue;
		if (!prj->root)
			continue;
		UnselectAll(prj->root);

		if (RootLoop(prj->root, ir))
		{
			main_page.Refresh2(L"PropertyItems");
			return;
		}

	}

}
