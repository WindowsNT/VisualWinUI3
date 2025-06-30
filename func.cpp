#include <pch.h>


const wchar_t* ttitle = L"Visual WinUI3";
std::shared_ptr<XML3::XML> SettingsX;
std::wstring datafolder;


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
