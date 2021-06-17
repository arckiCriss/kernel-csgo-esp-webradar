#define _CRT_SECURE_NO_WARNINGS

#ifndef FOverlay_H
#define FOverlay_H

#include <windows.h>
#include <stdio.h>
#include <dwmapi.h> 
#include <d2d1.h>
#include <dwrite.h>
#include <vector>
#include <string>
#include <chrono>
#include <map>

#pragma comment(lib, "Dwrite")

#pragma comment(lib, "Dwmapi.lib") 
#pragma comment(lib, "d2d1.lib")


#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS

class FOverlay
{
public:
	auto window_set_style()-> void;
	auto window_set_transparency()-> void;
	auto window_set_top_most()-> void;
	auto retrieve_window()->HWND;
	auto window_init()->BOOL;
	auto d2d_shutdown()-> void;
	auto init_d2d()->BOOL;
	auto begin_scene()-> void;
	auto end_scene()-> void;
	auto clear_scene()-> void;
	auto clear_screen()-> void;
	auto draw_line(int x1, int y1, int x2, int y2) -> void;
	auto draw_text_with_bg(int x, int y, ID2D1SolidColorBrush* fg_brush, ID2D1SolidColorBrush* bg_brush, const char* str, ...) -> void;
	auto draw_text(int x, int y, ID2D1SolidColorBrush* c_brush, const char* str, ...) -> void;
	auto draw_filled_rectangle(int left, int top, int right, int bottom, ID2D1SolidColorBrush* c_brush) -> void;
	auto draw_rectangle(int left, int top, int right, int bottom, ID2D1SolidColorBrush* c_brush) -> void;
	auto draw_filled_circle(float x, float  y, float radius, ID2D1SolidColorBrush* c_brush) -> void;
};

extern ID2D1SolidColorBrush* brush;
extern ID2D1SolidColorBrush* red_brush;
extern ID2D1SolidColorBrush* green_brush;
extern ID2D1SolidColorBrush* yellow_brush;
extern ID2D1SolidColorBrush* black_brush;
extern ID2D1SolidColorBrush* cyan_brush;

extern ID2D1SolidColorBrush* AliceBlue_brush;
extern ID2D1SolidColorBrush* AntiqueWhite_brush;
extern ID2D1SolidColorBrush* Aqua_brush;
extern ID2D1SolidColorBrush* Aquamarine_brush;
extern ID2D1SolidColorBrush* Azure_brush;
extern ID2D1SolidColorBrush* Beige_brush;
extern ID2D1SolidColorBrush* Bisque_brush;
extern ID2D1SolidColorBrush* Black_brush;
extern ID2D1SolidColorBrush* BlanchedAlmond_brush;
extern ID2D1SolidColorBrush* Blue_brush;
extern ID2D1SolidColorBrush* BlueViolet_brush;
extern ID2D1SolidColorBrush* Brown_brush;
extern ID2D1SolidColorBrush* BurlyWood_brush;
extern ID2D1SolidColorBrush* CadetBlue_brush;
extern ID2D1SolidColorBrush* Chartreuse_brush;
extern ID2D1SolidColorBrush* Chocolate_brush;
extern ID2D1SolidColorBrush* Coral_brush;
extern ID2D1SolidColorBrush* CornflowerBlue_brush;
extern ID2D1SolidColorBrush* Cornsilk_brush;
extern ID2D1SolidColorBrush* Crimson_brush;
extern ID2D1SolidColorBrush* Cyan_brush;
extern ID2D1SolidColorBrush* DarkBlue_brush;
extern ID2D1SolidColorBrush* DarkCyan_brush;
extern ID2D1SolidColorBrush* DarkGoldenrod_brush;
extern ID2D1SolidColorBrush* DarkGray_brush;
extern ID2D1SolidColorBrush* DarkGreen_brush;
extern ID2D1SolidColorBrush* DarkKhaki_brush;
extern ID2D1SolidColorBrush* DarkMagenta_brush;
extern ID2D1SolidColorBrush* DarkOliveGreen_brush;
extern ID2D1SolidColorBrush* DarkOrange_brush;
extern ID2D1SolidColorBrush* DarkOrchid_brush;
extern ID2D1SolidColorBrush* DarkRed_brush;
extern ID2D1SolidColorBrush* DarkSalmon_brush;
extern ID2D1SolidColorBrush* DarkSeaGreen_brush;
extern ID2D1SolidColorBrush* DarkSlateBlue_brush;
extern ID2D1SolidColorBrush* DarkSlateGray_brush;
extern ID2D1SolidColorBrush* DarkTurquoise_brush;
extern ID2D1SolidColorBrush* DarkViolet_brush;
extern ID2D1SolidColorBrush* DeepPink_brush;
extern ID2D1SolidColorBrush* DeepSkyBlue_brush;
extern ID2D1SolidColorBrush* DimGray_brush;
extern ID2D1SolidColorBrush* DodgerBlue_brush;
extern ID2D1SolidColorBrush* Firebrick_brush;
extern ID2D1SolidColorBrush* FloralWhite_brush;
extern ID2D1SolidColorBrush* ForestGreen_brush;
extern ID2D1SolidColorBrush* Fuchsia_brush;
extern ID2D1SolidColorBrush* Gainsboro_brush;
extern ID2D1SolidColorBrush* GhostWhite_brush;
extern ID2D1SolidColorBrush* Gold_brush;
extern ID2D1SolidColorBrush* Goldenrod_brush;
extern ID2D1SolidColorBrush* Gray_brush;
extern ID2D1SolidColorBrush* Green_brush;
extern ID2D1SolidColorBrush* GreenYellow_brush;
extern ID2D1SolidColorBrush* Honeydew_brush;
extern ID2D1SolidColorBrush* HotPink_brush;
extern ID2D1SolidColorBrush* IndianRed_brush;
extern ID2D1SolidColorBrush* Indigo_brush;
extern ID2D1SolidColorBrush* Ivory_brush;
extern ID2D1SolidColorBrush* Khaki_brush;
extern ID2D1SolidColorBrush* Lavender_brush;
extern ID2D1SolidColorBrush* LavenderBlush_brush;
extern ID2D1SolidColorBrush* LawnGreen_brush;
extern ID2D1SolidColorBrush* LemonChiffon_brush;
extern ID2D1SolidColorBrush* LightBlue_brush;
extern ID2D1SolidColorBrush* LightCoral_brush;
extern ID2D1SolidColorBrush* LightCyan_brush;
extern ID2D1SolidColorBrush* LightGoldenrodYellow_brush;
extern ID2D1SolidColorBrush* LightGreen_brush;
extern ID2D1SolidColorBrush* LightGray_brush;
extern ID2D1SolidColorBrush* LightPink_brush;
extern ID2D1SolidColorBrush* LightSalmon_brush;
extern ID2D1SolidColorBrush* LightSeaGreen_brush;
extern ID2D1SolidColorBrush* LightSkyBlue_brush;
extern ID2D1SolidColorBrush* LightSlateGray_brush;
extern ID2D1SolidColorBrush* LightSteelBlue_brush;
extern ID2D1SolidColorBrush* LightYellow_brush;
extern ID2D1SolidColorBrush* Lime_brush;
extern ID2D1SolidColorBrush* LimeGreen_brush;
extern ID2D1SolidColorBrush* Linen_brush;
extern ID2D1SolidColorBrush* Magenta_brush;
extern ID2D1SolidColorBrush* Maroon_brush;
extern ID2D1SolidColorBrush* MediumAquamarine_brush;
extern ID2D1SolidColorBrush* MediumBlue_brush;
extern ID2D1SolidColorBrush* MediumOrchid_brush;
extern ID2D1SolidColorBrush* MediumPurple_brush;
extern ID2D1SolidColorBrush* MediumSeaGreen_brush;
extern ID2D1SolidColorBrush* MediumSlateBlue_brush;
extern ID2D1SolidColorBrush* MediumSpringGreen_brush;
extern ID2D1SolidColorBrush* MediumTurquoise_brush;
extern ID2D1SolidColorBrush* MediumVioletRed_brush;
extern ID2D1SolidColorBrush* MidnightBlue_brush;
extern ID2D1SolidColorBrush* MintCream_brush;
extern ID2D1SolidColorBrush* MistyRose_brush;
extern ID2D1SolidColorBrush* Moccasin_brush;
extern ID2D1SolidColorBrush* NavajoWhite_brush;
extern ID2D1SolidColorBrush* Navy_brush;
extern ID2D1SolidColorBrush* OldLace_brush;
extern ID2D1SolidColorBrush* Olive_brush;
extern ID2D1SolidColorBrush* OliveDrab_brush;
extern ID2D1SolidColorBrush* Orange_brush;
extern ID2D1SolidColorBrush* OrangeRed_brush;
extern ID2D1SolidColorBrush* Orchid_brush;
extern ID2D1SolidColorBrush* PaleGoldenrod_brush;
extern ID2D1SolidColorBrush* PaleGreen_brush;
extern ID2D1SolidColorBrush* PaleTurquoise_brush;
extern ID2D1SolidColorBrush* PaleVioletRed_brush;
extern ID2D1SolidColorBrush* PapayaWhip_brush;
extern ID2D1SolidColorBrush* PeachPuff_brush;
extern ID2D1SolidColorBrush* Peru_brush;
extern ID2D1SolidColorBrush* Pink_brush;
extern ID2D1SolidColorBrush* Plum_brush;
extern ID2D1SolidColorBrush* PowderBlue_brush;
extern ID2D1SolidColorBrush* Purple_brush;
extern ID2D1SolidColorBrush* Red_brush;
extern ID2D1SolidColorBrush* RosyBrown_brush;
extern ID2D1SolidColorBrush* RoyalBlue_brush;
extern ID2D1SolidColorBrush* SaddleBrown_brush;
extern ID2D1SolidColorBrush* Salmon_brush;
extern ID2D1SolidColorBrush* SandyBrown_brush;
extern ID2D1SolidColorBrush* SeaGreen_brush;
extern ID2D1SolidColorBrush* SeaShell_brush;
extern ID2D1SolidColorBrush* Sienna_brush;
extern ID2D1SolidColorBrush* Silver_brush;
extern ID2D1SolidColorBrush* SkyBlue_brush;
extern ID2D1SolidColorBrush* SlateBlue_brush;
extern ID2D1SolidColorBrush* SlateGray_brush;
extern ID2D1SolidColorBrush* Snow_brush;
extern ID2D1SolidColorBrush* SpringGreen_brush;
extern ID2D1SolidColorBrush* SteelBlue_brush;
extern ID2D1SolidColorBrush* Tan_brush;
extern ID2D1SolidColorBrush* Teal_brush;
extern ID2D1SolidColorBrush* Thistle_brush;
extern ID2D1SolidColorBrush* Tomato_brush;
extern ID2D1SolidColorBrush* Turquoise_brush;
extern ID2D1SolidColorBrush* Violet_brush;
extern ID2D1SolidColorBrush* Wheat_brush;
extern ID2D1SolidColorBrush* White_brush;
extern ID2D1SolidColorBrush* WhiteSmoke_brush;
extern ID2D1SolidColorBrush* Yellow_brush;
extern ID2D1SolidColorBrush* YellowGreen_brush;
extern ID2D1SolidColorBrush* LessBlack_brush;

#endif

