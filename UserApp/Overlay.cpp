#include "overlay.h"

#define MAX_CLASSNAME 255
#define MAX_WNDNAME 255

static HWND win;
struct WindowsFinderParams {
    DWORD pidOwner = NULL;
    std::wstring wndClassName = L"";
    std::wstring wndName = L"";
    RECT pos = { 0, 0, 0, 0 };
    POINT res = { 0, 0 };
    float percentAllScreens = 0.0f;
    float percentMainScreen = 0.0f;
    DWORD style = NULL;
    DWORD styleEx = NULL;
    bool satisfyAllCriteria = false;
    std::vector<HWND> hwnds;
};
/*
Window functions
*/

auto FOverlay::window_set_style() -> void {
    int i = 0;

    i = (int)GetWindowLong(win, -20);

    SetWindowLongPtr(win, -20, (LONG_PTR)(i | 0x20));
}

auto FOverlay::window_set_transparency() -> void {
    MARGINS margin;
    UINT opacity_flag, color_key_flag, color_key = 0;
    UINT opacity = 0;

    margin.cyBottomHeight = -1;
    margin.cxLeftWidth = -1;
    margin.cxRightWidth = -1;
    margin.cyTopHeight = -1;

    DwmExtendFrameIntoClientArea(win, &margin);

    opacity_flag = 0x02;
    color_key_flag = 0x01;
    color_key = 0x000000;
    opacity = 0xFF;

    SetLayeredWindowAttributes(win, color_key, opacity, opacity_flag);
}

auto FOverlay::window_set_top_most() -> void {
    bool flag = SetWindowPos(win, HWND_TOPMOST, 0, 0, 0, 0, 0x0002 | 0x0001);
}

auto FOverlay::retrieve_window() -> HWND { return win; }



auto FOverlay::window_init() -> BOOL {
    win = FindWindow("CEF-OSC-WIDGET", "NVIDIA GeForce Overlay");
    if (!win)
        return FALSE;

    FOverlay::window_set_style();
    FOverlay::window_set_transparency();
    FOverlay::window_set_top_most();
    ShowWindow(win, SW_SHOW);

    return TRUE;
}

/*
Overlay functions
*/

ID2D1Factory* d2d_factory;
ID2D1HwndRenderTarget* tar;
IDWriteFactory* write_factory;
ID2D1SolidColorBrush* brush;
ID2D1SolidColorBrush* red_brush;
ID2D1SolidColorBrush* green_brush;
ID2D1SolidColorBrush* yellow_brush;
ID2D1SolidColorBrush* black_brush;
ID2D1SolidColorBrush* cyan_brush;




IDWriteTextFormat* format;
ID2D1SolidColorBrush* AliceBlue_brush;
ID2D1SolidColorBrush* AntiqueWhite_brush;
ID2D1SolidColorBrush* Aqua_brush;
ID2D1SolidColorBrush* Aquamarine_brush;
ID2D1SolidColorBrush* Azure_brush;
ID2D1SolidColorBrush* Beige_brush;
ID2D1SolidColorBrush* Bisque_brush;
ID2D1SolidColorBrush* Black_brush;
ID2D1SolidColorBrush* BlanchedAlmond_brush;
ID2D1SolidColorBrush* Blue_brush;
ID2D1SolidColorBrush* BlueViolet_brush;
ID2D1SolidColorBrush* Brown_brush;
ID2D1SolidColorBrush* BurlyWood_brush;
ID2D1SolidColorBrush* CadetBlue_brush;
ID2D1SolidColorBrush* Chartreuse_brush;
ID2D1SolidColorBrush* Chocolate_brush;
ID2D1SolidColorBrush* Coral_brush;
ID2D1SolidColorBrush* CornflowerBlue_brush;
ID2D1SolidColorBrush* Cornsilk_brush;
ID2D1SolidColorBrush* Crimson_brush;
ID2D1SolidColorBrush* Cyan_brush;
ID2D1SolidColorBrush* DarkBlue_brush;
ID2D1SolidColorBrush* DarkCyan_brush;
ID2D1SolidColorBrush* DarkGoldenrod_brush;
ID2D1SolidColorBrush* DarkGray_brush;
ID2D1SolidColorBrush* DarkGreen_brush;
ID2D1SolidColorBrush* DarkKhaki_brush;
ID2D1SolidColorBrush* DarkMagenta_brush;
ID2D1SolidColorBrush* DarkOliveGreen_brush;
ID2D1SolidColorBrush* DarkOrange_brush;
ID2D1SolidColorBrush* DarkOrchid_brush;
ID2D1SolidColorBrush* DarkRed_brush;
ID2D1SolidColorBrush* DarkSalmon_brush;
ID2D1SolidColorBrush* DarkSeaGreen_brush;
ID2D1SolidColorBrush* DarkSlateBlue_brush;
ID2D1SolidColorBrush* DarkSlateGray_brush;
ID2D1SolidColorBrush* DarkTurquoise_brush;
ID2D1SolidColorBrush* DarkViolet_brush;
ID2D1SolidColorBrush* DeepPink_brush;
ID2D1SolidColorBrush* DeepSkyBlue_brush;
ID2D1SolidColorBrush* DimGray_brush;
ID2D1SolidColorBrush* DodgerBlue_brush;
ID2D1SolidColorBrush* Firebrick_brush;
ID2D1SolidColorBrush* FloralWhite_brush;
ID2D1SolidColorBrush* ForestGreen_brush;
ID2D1SolidColorBrush* Fuchsia_brush;
ID2D1SolidColorBrush* Gainsboro_brush;
ID2D1SolidColorBrush* GhostWhite_brush;
ID2D1SolidColorBrush* Gold_brush;
ID2D1SolidColorBrush* Goldenrod_brush;
ID2D1SolidColorBrush* Gray_brush;
ID2D1SolidColorBrush* Green_brush;
ID2D1SolidColorBrush* GreenYellow_brush;
ID2D1SolidColorBrush* Honeydew_brush;
ID2D1SolidColorBrush* HotPink_brush;
ID2D1SolidColorBrush* IndianRed_brush;
ID2D1SolidColorBrush* Indigo_brush;
ID2D1SolidColorBrush* Ivory_brush;
ID2D1SolidColorBrush* Khaki_brush;
ID2D1SolidColorBrush* Lavender_brush;
ID2D1SolidColorBrush* LavenderBlush_brush;
ID2D1SolidColorBrush* LawnGreen_brush;
ID2D1SolidColorBrush* LemonChiffon_brush;
ID2D1SolidColorBrush* LightBlue_brush;
ID2D1SolidColorBrush* LightCoral_brush;
ID2D1SolidColorBrush* LightCyan_brush;
ID2D1SolidColorBrush* LightGoldenrodYellow_brush;
ID2D1SolidColorBrush* LightGreen_brush;
ID2D1SolidColorBrush* LightGray_brush;
ID2D1SolidColorBrush* LightPink_brush;
ID2D1SolidColorBrush* LightSalmon_brush;
ID2D1SolidColorBrush* LightSeaGreen_brush;
ID2D1SolidColorBrush* LightSkyBlue_brush;
ID2D1SolidColorBrush* LightSlateGray_brush;
ID2D1SolidColorBrush* LightSteelBlue_brush;
ID2D1SolidColorBrush* LightYellow_brush;
ID2D1SolidColorBrush* Lime_brush;
ID2D1SolidColorBrush* LimeGreen_brush;
ID2D1SolidColorBrush* Linen_brush;
ID2D1SolidColorBrush* Magenta_brush;
ID2D1SolidColorBrush* Maroon_brush;
ID2D1SolidColorBrush* MediumAquamarine_brush;
ID2D1SolidColorBrush* MediumBlue_brush;
ID2D1SolidColorBrush* MediumOrchid_brush;
ID2D1SolidColorBrush* MediumPurple_brush;
ID2D1SolidColorBrush* MediumSeaGreen_brush;
ID2D1SolidColorBrush* MediumSlateBlue_brush;
ID2D1SolidColorBrush* MediumSpringGreen_brush;
ID2D1SolidColorBrush* MediumTurquoise_brush;
ID2D1SolidColorBrush* MediumVioletRed_brush;
ID2D1SolidColorBrush* MidnightBlue_brush;
ID2D1SolidColorBrush* MintCream_brush;
ID2D1SolidColorBrush* MistyRose_brush;
ID2D1SolidColorBrush* Moccasin_brush;
ID2D1SolidColorBrush* NavajoWhite_brush;
ID2D1SolidColorBrush* Navy_brush;
ID2D1SolidColorBrush* OldLace_brush;
ID2D1SolidColorBrush* Olive_brush;
ID2D1SolidColorBrush* OliveDrab_brush;
ID2D1SolidColorBrush* Orange_brush;
ID2D1SolidColorBrush* OrangeRed_brush;
ID2D1SolidColorBrush* Orchid_brush;
ID2D1SolidColorBrush* PaleGoldenrod_brush;
ID2D1SolidColorBrush* PaleGreen_brush;
ID2D1SolidColorBrush* PaleTurquoise_brush;
ID2D1SolidColorBrush* PaleVioletRed_brush;
ID2D1SolidColorBrush* PapayaWhip_brush;
ID2D1SolidColorBrush* PeachPuff_brush;
ID2D1SolidColorBrush* Peru_brush;
ID2D1SolidColorBrush* Pink_brush;
ID2D1SolidColorBrush* Plum_brush;
ID2D1SolidColorBrush* PowderBlue_brush;
ID2D1SolidColorBrush* Purple_brush;
ID2D1SolidColorBrush* Red_brush;
ID2D1SolidColorBrush* RosyBrown_brush;
ID2D1SolidColorBrush* RoyalBlue_brush;
ID2D1SolidColorBrush* SaddleBrown_brush;
ID2D1SolidColorBrush* Salmon_brush;
ID2D1SolidColorBrush* SandyBrown_brush;
ID2D1SolidColorBrush* SeaGreen_brush;
ID2D1SolidColorBrush* SeaShell_brush;
ID2D1SolidColorBrush* Sienna_brush;
ID2D1SolidColorBrush* Silver_brush;
ID2D1SolidColorBrush* SkyBlue_brush;
ID2D1SolidColorBrush* SlateBlue_brush;
ID2D1SolidColorBrush* SlateGray_brush;
ID2D1SolidColorBrush* Snow_brush;
ID2D1SolidColorBrush* SpringGreen_brush;
ID2D1SolidColorBrush* SteelBlue_brush;
ID2D1SolidColorBrush* Tan_brush;
ID2D1SolidColorBrush* Teal_brush;
ID2D1SolidColorBrush* Thistle_brush;
ID2D1SolidColorBrush* Tomato_brush;
ID2D1SolidColorBrush* Turquoise_brush;
ID2D1SolidColorBrush* Violet_brush;
ID2D1SolidColorBrush* Wheat_brush;
ID2D1SolidColorBrush* White_brush;
ID2D1SolidColorBrush* WhiteSmoke_brush;
ID2D1SolidColorBrush* Yellow_brush;
ID2D1SolidColorBrush* YellowGreen_brush;
ID2D1SolidColorBrush* LessBlack_brush;


auto FOverlay::d2d_shutdown() -> void {
    // Release
    tar->Release();
    write_factory->Release();
    brush->Release();
    red_brush->Release();
    green_brush->Release();
}

auto FOverlay::init_d2d() -> BOOL {
    HRESULT ret;
    RECT rc;

    // Initialize D2D here
    ret = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &d2d_factory);
    if (FAILED(ret))
        return FALSE;

    ret =
        DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory),
            (IUnknown**)(&write_factory));
    if (FAILED(ret))
        return FALSE;

    write_factory->CreateTextFormat(
        L"Verdana", NULL, DWRITE_FONT_WEIGHT_BOLD, DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL, 9.0, L"en-us", &format);

    GetClientRect(FOverlay::retrieve_window(), &rc);

    ret = d2d_factory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(
            D2D1_RENDER_TARGET_TYPE_DEFAULT,
            D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN,
                D2D1_ALPHA_MODE_PREMULTIPLIED)),
        D2D1::HwndRenderTargetProperties(
            FOverlay::retrieve_window(),
            D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top)),
        &tar);
    if (FAILED(ret))
        return FALSE;

    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &red_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Green), &green_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Yellow), &yellow_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &black_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Cyan), &cyan_brush);

    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::AliceBlue), &AliceBlue_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::AntiqueWhite), &AntiqueWhite_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Aqua), &Aqua_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Aquamarine), &Aquamarine_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Azure), &Azure_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Beige), &Beige_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Bisque), &Bisque_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &Black_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::BlanchedAlmond), &BlanchedAlmond_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Blue), &Blue_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::BlueViolet), &BlueViolet_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Brown), &Brown_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::BurlyWood), &BurlyWood_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::CadetBlue), &CadetBlue_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Chartreuse), &Chartreuse_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Chocolate), &Chocolate_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Coral), &Coral_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::CornflowerBlue), &CornflowerBlue_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Cornsilk), &Cornsilk_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Crimson), &Crimson_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Cyan), &Cyan_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DarkBlue), &DarkBlue_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DarkCyan), &DarkCyan_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DarkGoldenrod), &DarkGoldenrod_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DarkGray), &DarkGray_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DarkGreen), &DarkGreen_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DarkKhaki), &DarkKhaki_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DarkMagenta), &DarkMagenta_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DarkOliveGreen), &DarkOliveGreen_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DarkOrange), &DarkOrange_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DarkOrchid), &DarkOrchid_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DarkRed), &DarkRed_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DarkSalmon), &DarkSalmon_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DarkSeaGreen), &DarkSeaGreen_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DarkSlateBlue), &DarkSlateBlue_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DarkSlateGray), &DarkSlateGray_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DarkTurquoise), &DarkTurquoise_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DarkViolet), &DarkViolet_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DeepPink), &DeepPink_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DeepSkyBlue), &DeepSkyBlue_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DimGray), &DimGray_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::DodgerBlue), &DodgerBlue_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Firebrick), &Firebrick_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::FloralWhite), &FloralWhite_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::ForestGreen), &ForestGreen_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Fuchsia), &Fuchsia_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Gainsboro), &Gainsboro_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::GhostWhite), &GhostWhite_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Gold), &Gold_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Goldenrod), &Goldenrod_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Gray), &Gray_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Green), &Green_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::GreenYellow), &GreenYellow_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Honeydew), &Honeydew_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::HotPink), &HotPink_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::IndianRed), &IndianRed_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Indigo), &Indigo_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Ivory), &Ivory_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Khaki), &Khaki_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Lavender), &Lavender_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LavenderBlush), &LavenderBlush_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LawnGreen), &LawnGreen_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LemonChiffon), &LemonChiffon_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightBlue), &LightBlue_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightCoral), &LightCoral_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightCyan), &LightCyan_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightGoldenrodYellow), &LightGoldenrodYellow_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightGreen), &LightGreen_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightGray), &LightGray_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightPink), &LightPink_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightSalmon), &LightSalmon_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightSeaGreen), &LightSeaGreen_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightSkyBlue), &LightSkyBlue_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightSlateGray), &LightSlateGray_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightSteelBlue), &LightSteelBlue_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightYellow), &LightYellow_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Lime), &Lime_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LimeGreen), &LimeGreen_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Linen), &Linen_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Magenta), &Magenta_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Maroon), &Maroon_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::MediumAquamarine), &MediumAquamarine_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::MediumBlue), &MediumBlue_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::MediumOrchid), &MediumOrchid_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::MediumPurple), &MediumPurple_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::MediumSeaGreen), &MediumSeaGreen_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::MediumSlateBlue), &MediumSlateBlue_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::MediumSpringGreen), &MediumSpringGreen_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::MediumTurquoise), &MediumTurquoise_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::MediumVioletRed), &MediumVioletRed_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::MidnightBlue), &MidnightBlue_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::MintCream), &MintCream_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::MistyRose), &MistyRose_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Moccasin), &Moccasin_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::NavajoWhite), &NavajoWhite_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Navy), &Navy_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::OldLace), &OldLace_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Olive), &Olive_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::OliveDrab), &OliveDrab_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Orange), &Orange_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::OrangeRed), &OrangeRed_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Orchid), &Orchid_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::PaleGoldenrod), &PaleGoldenrod_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::PaleGreen), &PaleGreen_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::PaleTurquoise), &PaleTurquoise_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::PaleVioletRed), &PaleVioletRed_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::PapayaWhip), &PapayaWhip_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::PeachPuff), &PeachPuff_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Peru), &Peru_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Pink), &Pink_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Plum), &Plum_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::PowderBlue), &PowderBlue_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Purple), &Purple_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &Red_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::RosyBrown), &RosyBrown_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::RoyalBlue), &RoyalBlue_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::SaddleBrown), &SaddleBrown_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Salmon), &Salmon_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::SandyBrown), &SandyBrown_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::SeaGreen), &SeaGreen_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::SeaShell), &SeaShell_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Sienna), &Sienna_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Silver), &Silver_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::SkyBlue), &SkyBlue_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::SlateBlue), &SlateBlue_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::SlateGray), &SlateGray_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Snow), &Snow_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::SpringGreen), &SpringGreen_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::SteelBlue), &SteelBlue_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Tan), &Tan_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Teal), &Teal_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Thistle), &Thistle_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Tomato), &Tomato_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Turquoise), &Turquoise_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Violet), &Violet_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Wheat), &Wheat_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &White_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::WhiteSmoke), &WhiteSmoke_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Yellow), &Yellow_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::YellowGreen), &YellowGreen_brush);
    tar->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black, 0.5f), &LessBlack_brush);

    return TRUE;
}

auto FOverlay::begin_scene() -> void { tar->BeginDraw(); }

auto FOverlay::end_scene() -> void { tar->EndDraw(); }

auto FOverlay::clear_scene() -> void { tar->Clear(); }


auto FOverlay::draw_text_with_bg(int x, int y, ID2D1SolidColorBrush* fg_brush, ID2D1SolidColorBrush* bg_brush, const char* str, ...) -> void
{
    char buf[4096];
    int len = 0;
    wchar_t b[256];

    // if (!draw) // no need for it.
    //	 return;

    va_list arg_list;
    va_start(arg_list, str);
    vsnprintf(buf, sizeof(buf), str, arg_list);
    va_end(arg_list);

    len = strlen(buf);
    mbstowcs(b, buf, len);



    float clippedWidth = x < 0 ? 1980 + x : 1980 - x;
    float clippedHeight = y < 0 ? 1080 + y : 1080 - y;

    if (clippedWidth <= 9)
    {
        clippedWidth = 1980;
    }
    if (clippedHeight <= 9)
    {
        clippedHeight = 1080;
    }



    IDWriteTextLayout* textlayout;
    write_factory->CreateTextLayout(b, len, format, clippedWidth, clippedHeight, &textlayout);

    D2D1_RECT_F rect;


    float fontsize = 9;
    DWRITE_TEXT_RANGE textrange;
    textrange.startPosition = 0;
    textrange.length = len;

    textlayout->SetFontSize(fontsize, textrange);
    textlayout->GetFontSize(0, &fontsize, &textrange);
    float modifier = fontsize * 0.25f;

    rect.left = x - modifier;
    rect.top = y - modifier;
    DWRITE_TEXT_METRICS text_matrics;
    textlayout->GetMetrics(&text_matrics);
    rect.right = x + text_matrics.width + modifier;
    rect.bottom = y + text_matrics.height + modifier;


    draw_filled_rectangle(rect.left, rect.top, rect.right, rect.bottom, bg_brush);

    tar->DrawText(b, len, format, D2D1::RectF(x, y, 1920, 1080), fg_brush,
        D2D1_DRAW_TEXT_OPTIONS_NONE, DWRITE_MEASURING_MODE_NATURAL);


}

auto FOverlay::draw_filled_circle(float x, float  y, float radius, ID2D1SolidColorBrush* c_brush) -> void {

    D2D1_ELLIPSE ellipse;
    D2D1_POINT_2F p;
    p.x = x;
    p.y = y;
    ellipse.point = p;
    ellipse.radiusX = radius;
    ellipse.radiusY = radius;

    tar->FillEllipse(ellipse, c_brush);

}

auto FOverlay::draw_filled_rectangle(int left, int top, int right, int bottom, ID2D1SolidColorBrush* c_brush) -> void {

    D2D1_RECT_F rect;

    rect.left = left;
    rect.right = right;
    rect.top = top;
    rect.bottom = bottom;

    tar->FillRectangle(rect, c_brush);

}

auto FOverlay::draw_rectangle(int left, int top, int right, int bottom, ID2D1SolidColorBrush* c_brush) -> void {

    D2D1_RECT_F rect;

    rect.left = left;
    rect.right = right;
    rect.top = top;
    rect.bottom = bottom;

    tar->DrawRectangle(rect, c_brush, 1);

}

auto FOverlay::draw_text(int x, int y, ID2D1SolidColorBrush* c_brush, const char* str, ...) -> void {
    char buf[4096];
    int len = 0;
    wchar_t b[256];

    va_list arg_list;
    va_start(arg_list, str);
    vsnprintf(buf, sizeof(buf), str, arg_list);
    va_end(arg_list);


    len = strlen(buf);
    mbstowcs(b, buf, len);

    tar->DrawText(b, len, format, D2D1::RectF(x, y, 1920, 1080), c_brush,
        D2D1_DRAW_TEXT_OPTIONS_NONE, DWRITE_MEASURING_MODE_NATURAL);
}


auto FOverlay::draw_line(int x1, int y1, int x2, int y2) -> void {

    D2D1_POINT_2F start;
    D2D1_POINT_2F end;
    start.x = x1;
    start.y = y1;

    end.x = x2;
    end.y = y2;

    tar->DrawLine(start, end, brush);

}

auto FOverlay::clear_screen() -> void {
    FOverlay::begin_scene();
    FOverlay::clear_scene();
    FOverlay::end_scene();
}