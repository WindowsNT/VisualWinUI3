#include <pch.h>

const wchar_t* ttitle = L"Visual WinUI3";
std::shared_ptr<XML3::XML> SettingsX;
std::wstring datafolder;

#include "property.hpp"


bool is_light_theme() {
    // based on https://stackoverflow.com/questions/51334674/how-to-detect-windows-10-light-dark-mode-in-win32-application

    // The value is expected to be a REG_DWORD, which is a signed 32-bit little-endian
    char buffer[4];
    DWORD cbData = 4;
    RegGetValueW(
        HKEY_CURRENT_USER,
        L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
        L"AppsUseLightTheme",
        RRF_RT_REG_DWORD, // expected value type
        nullptr,
        buffer,
        &cbData);

    // convert bytes written to our buffer to an int, assuming little-endian
    auto i = int(buffer[3] << 24 |
        buffer[2] << 16 |
        buffer[1] << 8 |
        buffer[0]);

    return i == 1;
}


CComPtr<IWICImagingFactory> wbfact;

void SaveWic(IWICBitmapSource* src, const wchar_t* out)
{
    if (!wbfact)
        CoCreateInstance(CLSID_WICImagingFactory, 0, CLSCTX_INPROC_SERVER,
            __uuidof(IWICImagingFactory), (void**)&wbfact);

    CComPtr<IWICBitmapEncoder> wicBitmapEncoder;
    wbfact->CreateEncoder(GUID_ContainerFormatPng, 0, &wicBitmapEncoder);
	CComPtr<IWICStream> stream;
	wbfact->CreateStream(&stream);  

	stream->InitializeFromFilename(out, GENERIC_WRITE);
	wicBitmapEncoder->Initialize(stream, WICBitmapEncoderNoCache);
	CComPtr<IWICBitmapFrameEncode> wicFrameEncode;
	wicBitmapEncoder->CreateNewFrame(&wicFrameEncode, 0);
	wicFrameEncode->Initialize(0);
	UINT W = 0, H = 0;
	src->GetSize(&W, &H);
	wicFrameEncode->SetSize(W, H);
    GUID g2 = GUID_WICPixelFormat32bppBGRA;
	wicFrameEncode->SetPixelFormat(&g2);
	wicFrameEncode->WriteSource(src, 0);
	wicFrameEncode->Commit();
	wicBitmapEncoder->Commit();

}
CComPtr<IWICBitmap> LoadWic(const wchar_t* o)
{
	if (!wbfact)
		CoCreateInstance(CLSID_WICImagingFactory, 0, CLSCTX_INPROC_SERVER,
			__uuidof(IWICImagingFactory), (void**)&wbfact);
	CComPtr<IWICBitmapDecoder> pDecoder = NULL;
	CComPtr<IWICBitmapFrameDecode> pSource = NULL;

	auto hr = wbfact->CreateDecoderFromFilename(
		o,
		NULL, GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
	);
	if (FAILED(hr)) return {};
	hr = pDecoder->GetFrame(0, &pSource);
	if (FAILED(hr)) return {};

    CComPtr<IWICBitmap> bix;
    wbfact->CreateBitmapFromSource(pSource, WICBitmapCacheOnDemand, &bix);
    return bix;
}



#include "english.hpp"


const wchar_t* s(size_t idx)
{
    if (idx > MAX_LANG)
        return L"";
    return z_strings[idx];
}

// **********

std::vector<std::shared_ptr<PROPERTY>> CreatePropertiesFor(winrt::Microsoft::UI::Xaml::UIElement e)
{
	std::vector<std::shared_ptr<PROPERTY>> p;
	if (!e)
		return p;

	if (1)
	{
		std::shared_ptr<DOUBLE_PROPERTY> op = std::make_shared<DOUBLE_PROPERTY>();
		op->g = L"UIElement";
		op->n = L"Opacity";
		op->mmin = 0.0;
		op->mmax = 1.0;
		op->value = e.Opacity();
		op->def = 1.0;
		p.push_back(op);
	}

	return p;
}

std::vector<std::shared_ptr<PROPERTY>> CreatePropertiesFor(winrt::Microsoft::UI::Xaml::FrameworkElement e)
{
	std::vector<std::shared_ptr<PROPERTY>> p;
	if (!e)
		return p;

	if (1)
	{
		std::shared_ptr<DOUBLE_PROPERTY> op = std::make_shared<DOUBLE_PROPERTY>();
		op->g = L"FrameworkElement";
		op->n = L"MinWidth";
		op->mmin = 0.0;
		op->mmax = 10000;
		op->value = std::nan("");
		op->def = std::nan("");
		p.push_back(op);
	}
	if (1)
	{
		std::shared_ptr<DOUBLE_PROPERTY> op = std::make_shared<DOUBLE_PROPERTY>();
		op->n = L"MinHeight";
		op->mmin = 0.0;
		op->mmax = 10000;
		op->value = std::nan("");
		op->def = std::nan("");
		p.push_back(op);
	}

	return p;
}

void ApplyPropertiesFor(winrt::Microsoft::UI::Xaml::UIElement e, std::vector <std::shared_ptr<PROPERTY>> props)
{
	if (!e)
		return;
	for (auto& p : props)
	{
		if (p->n == L"Opacity")
		{
			auto op = std::dynamic_pointer_cast<DOUBLE_PROPERTY>(p);
			if (op)
			{
				e.Opacity(op->value);
			}
		}
	}
}

void ApplyPropertiesFor(winrt::Microsoft::UI::Xaml::FrameworkElement e, std::vector <std::shared_ptr<PROPERTY>> props)
{
	if (!e)
		return;
	for (auto& p : props)
	{
		if (p->n == L"MinWidth")
		{
			auto op = std::dynamic_pointer_cast<DOUBLE_PROPERTY>(p);
			if (op && !std::isnan(op->value))
			{
				e.MinWidth(op->value);
			}
		}	
		if (p->n == L"MinHeight")
		{
			auto op = std::dynamic_pointer_cast<DOUBLE_PROPERTY>(p);
			if (op && !std::isnan(op->value))
			{
				e.MinHeight(op->value);
			}
		}
	}
}

void LoadXMLPropertiesfor(XML3::XMLElement& ee, std::vector <std::shared_ptr<PROPERTY>> props)
{
	for (auto& p : props)
	{
		auto what = p->xmln;
		if (what.empty())
			what = p->n;

		if (1)
		{
			auto opx = std::dynamic_pointer_cast<DOUBLE_PROPERTY>(p);
			if (opx)
			{
				auto op = ee.FindVariableZ(XML3::XMLU(what.c_str()).bc(), false);
				opx->value = opx->def;
				if (op)
					opx->value = op->GetValueDouble(opx->def);
			}
		}
		if (1)
		{
			auto opx = std::dynamic_pointer_cast<LIST_PROPERTY>(p);
			if (opx)
			{
				auto op = ee.FindVariableZ(XML3::XMLU(what.c_str()).bc(), false);
				if (op)
					opx->SelectedIndex = op->GetValueLongLong();
			}
		}
		if (1)
		{
			auto opx = std::dynamic_pointer_cast<STRING_PROPERTY>(p);
			if (opx)
			{
				auto op = ee.FindVariableZ(XML3::XMLU(what.c_str()).bc(), false);
				opx->value = opx->def;
				if (op)
					opx->value = op->GetWideValue();
			}
		}
	}

}

void XMLPropertiesFor(XML3::XMLElement& ee,std::vector <std::shared_ptr<PROPERTY>> props)
{
	for (auto& p : props)
	{
		auto what = p->xmln;
		if (what.empty())
			what = p->n;

		if (1)
		{
			auto opx = std::dynamic_pointer_cast<DOUBLE_PROPERTY>(p);
			if (opx && opx->value != opx->def && !std::isnan(opx->value))
			{
				auto& op = ee.AddVariable(XML3::XMLU(what.c_str()).bc());
				op.SetValueDouble(opx->value);
			}
		}

		if (1)
		{
			auto opx = std::dynamic_pointer_cast<LIST_PROPERTY>(p);
			if (opx)
			{
				auto& op = ee.AddVariable(XML3::XMLU(what.c_str()).bc());
				op.SetValueULongLong(opx->SelectedIndex);
			}
		}

		if (1)
		{
			auto opx = std::dynamic_pointer_cast<STRING_PROPERTY>(p);
			if (opx && opx->value != opx->def)
			{
				auto& op = ee.AddVariable(XML3::XMLU(what.c_str()).bc());
				op.SetWideValue(opx->value.c_str());
			}
		}

	}
}

