#pragma once
#include "types.h"
extern enum ProMenus;


enum class Header_Type : std::int32_t
{
	Static = 0,
	Gradient = 1,
	Game_YTD = 2,
	Game_YTD_2 = 3,
	YTD = 4,
};

enum class Font : std::int32_t
{
	ChaletLondon = 0,
	HouseScript = 1,
	Monospace = 2,
	Wingdings = 3,
	ChaletComprimeCologne = 4,
	Pricedown = 7
};

namespace Menu
{
	using namespace Mod_Hub_Base;
	// Rainbow bools
	extern bool Scrollbar_Rainbow;
	extern bool Toggle_RainbowBool;
	extern bool Rainbowmenu_titleBool;

	// toggle
	extern bool OnOffSwitch;
	extern bool YesNoSwitch;
	extern bool IconSwitch;
	extern bool plopSwitch;

	namespace Drawing {
		void Text(char* text, RGBAF rgbaf, VECTOR2 position, VECTOR2_2 size, bool center);
		void Title(char* text, RGBAF rgbaf, VECTOR2 position, VECTOR2_2 size, bool center);
		void Rect(float x, float y, float width, float height, RGBA color);
		void Rect(RGBA color, VECTOR2 position, VECTOR2_2 size);
		void Draw_Spriter(std::string Streamedtexture, std::string textureName, float x, float y, float width, float height, float rotation, RGBA color);
		void Draw_Spriter(std::string Streamedtexture, std::string textureName, float x, float y, float width, float height, float rotation, int r, int g, int b, int a);
	}
	namespace Settings {
		extern bool selectPressed;
		extern bool leftPressed;
		extern bool rightPressed;
		extern bool center;
		extern bool controllerinput;
		extern bool Animescroll;

		extern int maxVisOptions;
		extern int currentOption;
		extern int optionCount;

		extern ProMenus currentMenu;
		extern int menuLevel;
		extern int optionsArray[1000];
		extern ProMenus menusArray[1000];

		extern float menuX;
		extern float menuY;
		extern float menuXscale;
		extern RGBAF count;
		extern RGBAF titleText;
		extern RGBA titleRect;
		extern RGBAF breakText;
		extern RGBAF optionText;
		extern RGBA selectedText;
		extern RGBAF arrow;
		extern RGBAF integre;
		extern RGBA optionRect;
		extern RGBA endoptionRect;
		extern RGBA scroller;
		extern RGBA line;
		extern RGBA primary;
		extern RGBA secondary;
		extern RGBA Toggle_Raindow;

		extern RGBA color;

		// Draw
		extern float drawBaseY;

		// Header
		extern float HeaderHeight;
		extern bool Header_Text;
		extern float HeaderTextSize;
		extern Font HeaderFont;
		extern RGBA HeaderBackgroundColor;
		extern RGBA HeaderTextColor;
		extern Header_Type Header_Type_Switch;

		extern bool HeaderGradientTransparent;
		extern bool HeaderGradientFlip;
		extern float HeaderGradientStretch;
		extern float HeaderGradientFiller;
		extern RGBA HeaderGradientColorLeft;
		extern RGBA HeaderGradientColorRight;

		// Options
		extern float OptionHeight;
		extern float OptionTextSize;
		extern Font OptionFont;
		extern float OptionPadding;
		extern RGBA OptionSelectedTextColor;
		extern RGBA OptionUnselectedTextColor;
		extern RGBA OptionSelectedBackgroundColor;
		extern RGBA OptionSelectedBackgroundColor2;
		extern RGBA OptionUnselectedBackgroundColor;
		extern RGBA OptionUnselectedBackgroundColor2;

		// Submenu bar
		extern float SubmenuBarHeight;
		extern float SubmenuBarTextSize;
		extern Font SubmenuBarFont;
		extern float SubmenuBarPadding;
		extern RGBA SubmenuBarBackgroundColor;
		extern RGBA SubmenuBarTextColor;

		// Footer

		extern float FooterHeight;
		extern float FooterSpriteSize;
		extern RGBA FooterBackgroundColor;
		extern RGBA FooterSpriteColor;

		extern float size;

		extern float Width;

		// Description
		extern float DescriptionHeightPadding;
		extern float DescriptionHeight;
		extern float DescriptionTextSize;
		extern Font DescriptionFont;
		extern RGBA DescriptionBackgroundColor;
		extern RGBA DescriptionTextColor;
		extern float DescriptionSpriteSize;
		extern float DescriptionPadding;
		extern RGBA DescriptionSpriteColor;

		// HUD COLORS
		extern RGBA HUD_COLOUR_PAUSE_RGB;

		extern int keyPressDelay;
		extern int keyPressPreviousTick;
		extern int keyPressDelay2;
		extern int keyPressPreviousTick2;
		extern int keyPressDelay3;
		extern int keyPressPreviousTick3;
		extern int openKey;
		extern int backKey;
		extern int upKey;
		extern int downKey;
		extern int leftKey;
		extern int rightKey;
		extern int selectKey;
		extern int arrowupKey;
		extern int arrowdownKey;
		extern int arrowleftKey;
		extern int arrowrightKey;
		extern int enterKey;
		extern int deleteKey;
		extern int openpress;
		extern int downpress;
		extern int uppress;
		extern int backpress;
		extern int click;
		extern int leftpress;
		extern int rightpress;



	}
	namespace MenuLevelHandler {
		void MoveMenu(ProMenus menu);
		void BackMenu();
	}
	namespace Checks {
		void Controlls();
	}
	namespace Tools {
		char* StringToChar(std::string string);
	}
	namespace Files {
		void WriteStringToIni(std::string string, std::string file, std::string app, std::string key);
		std::string ReadStringFromIni(std::string file, std::string app, std::string key);
		void WriteIntToIni(int intValue, std::string file, std::string app, std::string key);
		int ReadIntFromIni(std::string file, std::string app, std::string key);
		void WriteFloatToIni(float floatValue, std::string file, std::string app, std::string key);
		float ReadFloatFromIni(std::string file, std::string app, std::string key);
		void WriteBoolToIni(bool b00l, std::string file, std::string app, std::string key);
		bool ReadBoolFromIni(std::string file, std::string app, std::string key);
	}
	void HUD_COLOUR_PAUSE_Rainbow();
	void scrollbar_Rainbow();
	void Toggle_Rainbow();
	void Rainbow_Title();
	void Title(char* title);
	void info(char* description);
	void OptionInfo(char* description);
	void Vehicle(std::string texture1, std::string texture2);
	void Speedometer(char* text);
	void fps(char* text);
	void AddSmallTitle(char* text);
	void AddSmallInfo(char* text, short line);
	void AddSmallTitle2(char* text);
	void AddSmallInfo2(char* text, short line);
	void AddSmallTitle3(char* text);
	void AddSmallInfo3(char* text, short line);
	bool Break(char* option);
	bool Option(char* option);
	bool Option(char* option, char* description);
	bool Option(char* option, std::function<void()> function);
	bool MenuOption(char* option, ProMenus newSub);
	bool MenuOption(char* option, ProMenus newSub, std::function<void()> function);
	bool Toggle(char* option, bool& b00l);
	bool Int(char* option, int& _int, int min, int max);
	bool Int(char* option, int& _int, int min, int max, int step);
	bool Int(char* option, int& _int, int min, int max, std::function<void()> function);
	bool Int(char* option, int& _int, int min, int max, int step, std::function<void()> function);
	bool Float(char* option, float& _float, int min, int max);
	bool Float(char* option, float& _float, int min, int max, int step);
	bool Float(char* option, float& _float, int min, int max, std::function<void()> function);
	bool Float(char* option, float& _float, int min, int max, int step, std::function<void()> function);
	bool IntVector(char* option, std::vector<int> Vector, int& position);
	bool IntVector(char* option, std::vector<int> Vector, int& position, std::function<void()> function);
	bool FloatVector(char* option, std::vector<float> Vector, int& position);
	bool FloatVector(char* option, std::vector<float> Vector, int& position, std::function<void()> function);
	bool StringVector(char* option, std::vector<std::string> Vector, int& position);
	bool StringVector(char* option, std::vector<std::string> Vector, int& position, std::function<void()> function);
	bool StringVector(char* option, std::vector<char*> Vector, int& position);
	bool StringVector(char* option, std::vector<char*> Vector, int& position, std::function<void()> function);
	bool Teleport(char* option, Vector3 coords);
	bool Teleport(char* option, Vector3 coords, std::function<void()> function);
	void End();

}