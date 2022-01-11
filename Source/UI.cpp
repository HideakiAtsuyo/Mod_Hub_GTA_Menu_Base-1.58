#include "stdafx.h"

namespace Menu
{
	using namespace Mod_Hub_Base;



	float rotation = 0.f;

	// Draw
	float drawBaseY{};

	// Header
	float HeaderHeight = 0.1f;
	bool Header_Text = true;
	float HeaderTextSize = 1.f;
	Font HeaderFont = Font::HouseScript;
	RGBA Menu::Settings::HeaderBackgroundColor{ 2, 130, 53, 255 };
	RGBA Menu::Settings::HeaderTextColor{ 0, 254, 0, 255 };
	Header_Type Header_Type_Switch = Header_Type::YTD;

	bool HeaderGradientTransparent = false;
	bool HeaderGradientFlip = false;
	float HeaderGradientStretch = 0.f;
	float HeaderGradientFiller = 0.f;
	RGBA Menu::Settings::HeaderGradientColorLeft{ 0, 186, 255, 255 };
	RGBA Menu::Settings::HeaderGradientColorRight{ 252, 0, 255, 255 };

	// Footer
	float FooterHeight = 0.04f;
	float FooterSpriteSize = 0.025f;
	RGBA Menu::Settings::FooterBackgroundColor{ 10, 10, 10, 200 };
	RGBA Menu::Settings::FooterSpriteColor{ 255, 255, 255, 255 };

	float size = FooterSpriteSize;

	float Width = 0.24f;


	// Submenu bar
	float SubmenuBarHeight = 0.04f;
	float SubmenuBarTextSize = 0.4f;
	Font Menu::Settings::SubmenuBarFont = Font::ChaletLondon;
	float SubmenuBarPadding = 2.1f;
	RGBA Menu::Settings::SubmenuBarBackgroundColor{ 0, 0, 0, 220 };
	RGBA Menu::Settings::SubmenuBarTextColor{ 255, 255, 255, 255 };

	// Description
	float DescriptionHeightPadding = 0.01f;
	float DescriptionHeight = 0.033f;
	float DescriptionTextSize = 0.28f;
	Font Menu::Settings::DescriptionFont = Font::ChaletLondon;
	RGBA Menu::Settings::DescriptionBackgroundColor{ 0, 0, 0, 120 };
	RGBA Menu::Settings::DescriptionTextColor{ 255, 255, 255, 255 };
	float DescriptionSpriteSize = 0.025f;
	float DescriptionPadding = 2.1f;
	RGBA Menu::Settings::DescriptionSpriteColor{ 255, 255, 255, 255 };


	void Menu::Drawing::Text(char* text, RGBAF rgbaf, VECTOR2 position, VECTOR2_2 size, bool center)
	{
		UI::SET_TEXT_CENTRE(center);
		UI::SET_TEXT_COLOUR(rgbaf.r, rgbaf.g, rgbaf.b, rgbaf.a);
		UI::SET_TEXT_FONT(rgbaf.f);
		UI::SET_TEXT_SCALE(size.w, size.h);
		UI::SET_TEXT_DROPSHADOW(1, 0, 0, 0, 0);
		UI::SET_TEXT_EDGE(1, 0, 0, 0, 0);
		UI::SET_TEXT_OUTLINE();
		UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
		UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
		UI::END_TEXT_COMMAND_DISPLAY_TEXT(position.x, position.y);
	}

	void DrawLeftText(char* text, float x, float y, float size, Font font, RGBA color, bool outline, bool shadow)
	{
		UI::SET_TEXT_SCALE(size, size);
		UI::SET_TEXT_FONT(static_cast<int>(font));
		UI::SET_TEXT_COLOUR(color.r, color.g, color.b, color.a);
		if (outline)
			UI::SET_TEXT_OUTLINE();
		if (shadow)
			UI::SET_TEXT_DROP_SHADOW();

		UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
		UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
		UI::END_TEXT_COMMAND_DISPLAY_TEXT(x, y);
	}
	void DrawCenteredText(char* text, float x, float y, float size, Font font, RGBA color, bool outline, bool shadow)
	{
		UI::SET_TEXT_CENTRE(true);
		DrawLeftText(text, x, y, size, font, color, outline, shadow);
	}

	void Menu::Drawing::Draw_Spriter(std::string Streamedtexture, std::string textureName, float x, float y, float width, float height, float rotation, RGBA color)
	{
		if (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED((char*)Streamedtexture.c_str()))
		{
			GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT((char*)Streamedtexture.c_str(), false);
		}
		else
		{
			GRAPHICS::DRAW_SPRITE((char*)Streamedtexture.c_str(), (char*)textureName.c_str(), x, y, width, height, rotation, color.r, color.g, color.b, color.a);
		}
	}

	void Menu::Drawing::Rect(RGBA color, VECTOR2 position, VECTOR2_2 size)
	{
		GRAPHICS::DRAW_RECT(position.x, position.y, size.w, size.h, color.r, color.g, color.b, color.a);
	}

	void Menu::Drawing::Rect(float x, float y, float width, float height, RGBA color)
	{
		GRAPHICS::DRAW_RECT(x, y, width, height, color.r, color.g, color.b, color.a);
	}

	bool Rainbowmenu_titleBool = true;
	void Rainbow_Title()
	{
		if (Rainbowmenu_titleBool)
		{
			if (Menu::Settings::HeaderTextColor.r > 0 && Menu::Settings::HeaderTextColor.b == 0)
			{
				Menu::Settings::HeaderTextColor.r--;
				Menu::Settings::HeaderTextColor.g++;
			}
			if (Menu::Settings::HeaderTextColor.g > 0 && Menu::Settings::HeaderTextColor.r == 0)
			{
				Menu::Settings::HeaderTextColor.g--;
				Menu::Settings::HeaderTextColor.b++;
			}
			if (Menu::Settings::HeaderTextColor.b > 0 && Menu::Settings::HeaderTextColor.g == 0)
			{
				Menu::Settings::HeaderTextColor.r++;
				Menu::Settings::HeaderTextColor.b--;
			}
			(Menu::Settings::HeaderTextColor.r, Menu::Settings::HeaderTextColor.g, Menu::Settings::HeaderTextColor.b);
		}
	}

	bool Toggle_RainbowBool = true;
	void Toggle_Rainbow()
	{
		if (Toggle_RainbowBool)
		{
			if (Menu::Settings::Toggle_Raindow.r > 0 && Menu::Settings::Toggle_Raindow.b == 0)
			{
				Menu::Settings::Toggle_Raindow.r--;
				Menu::Settings::Toggle_Raindow.g++;
			}
			if (Menu::Settings::Toggle_Raindow.g > 0 && Menu::Settings::Toggle_Raindow.r == 0)
			{
				Menu::Settings::Toggle_Raindow.g--;
				Menu::Settings::Toggle_Raindow.b++;
			}
			if (Menu::Settings::Toggle_Raindow.b > 0 && Menu::Settings::Toggle_Raindow.g == 0)
			{
				Menu::Settings::Toggle_Raindow.r++;
				Menu::Settings::Toggle_Raindow.b--;
			}
			(Menu::Settings::Toggle_Raindow.r, Menu::Settings::Toggle_Raindow.g, Menu::Settings::Toggle_Raindow.b);
		}
	}

	bool Scrollbar_Rainbow = true;
	void scrollbar_Rainbow()
	{
		if (Scrollbar_Rainbow)
		{
			if (Menu::Settings::scroller.r > 0 && Menu::Settings::scroller.b == 0)
			{
				Menu::Settings::scroller.r--;
				Menu::Settings::scroller.g++;
			}
			if (Menu::Settings::scroller.g > 0 && Menu::Settings::scroller.r == 0)
			{
				Menu::Settings::scroller.g--;
				Menu::Settings::scroller.b++;
			}
			if (Menu::Settings::scroller.b > 0 && Menu::Settings::scroller.g == 0)
			{
				Menu::Settings::scroller.r++;
				Menu::Settings::scroller.b--;
			}
			(Menu::Settings::scroller.r, Menu::Settings::scroller.g, Menu::Settings::scroller.b);
		}
	}

	float OptionHeight = 0.04f;



	float Menu::Settings::menuXscale = 0.24f;
	int prevOption = 0;
	float prevf;
	float ScrollerSpeed = 0.01f;
	const auto animscroll = [](int* prev, const int cur) {
		if (prevf == NULL)
			prevf = *prev * 0.04f + 0.2212f;
		const auto curf = cur * 0.04f + 0.2212f;
		if (Menu::Settings::currentOption <= Menu::Settings::maxVisOptions && Menu::Settings::optionCount <= Menu::Settings::maxVisOptions) {
			if (*prev != cur)
			{
				if (prevf < curf)
				{
					if (prevf + ScrollerSpeed > curf)
						prevf = prevf + (curf - prevf);
					else
						prevf = prevf + ScrollerSpeed;
					GRAPHICS::DRAW_RECT(Menu::Settings::menuX, prevf, Settings::menuXscale, 0.04f, Settings::scroller.r, Menu::Settings::scroller.g, Menu::Settings::scroller.b, Menu::Settings::scroller.a);
					if (prevf >= curf)
					{
						prevf = curf;
						*prev = cur;
					}
				}
				if (prevf > curf)
				{
					if (prevf - ScrollerSpeed < curf)
						prevf = prevf - (prevf - curf);
					prevf = prevf - ScrollerSpeed;
					GRAPHICS::DRAW_RECT(Menu::Settings::menuX, prevf, Settings::menuXscale, 0.04f, Settings::scroller.r, Menu::Settings::scroller.g, Menu::Settings::scroller.b, Menu::Settings::scroller.a);
					if (prevf <= curf)
					{
						prevf = curf;
						*prev = cur;
					}
				}
			}
			else
			{
				*prev = cur;
				GRAPHICS::DRAW_RECT(Menu::Settings::menuX, cur * 0.04f + 0.2212f, Menu::Settings::menuXscale - 0.000f, 0.04f, Settings::scroller.r, Menu::Settings::scroller.g, Menu::Settings::scroller.b, Menu::Settings::scroller.a);
			}
		}
		else if ((Menu::Settings::optionCount > (Menu::Settings::currentOption - Menu::Settings::maxVisOptions)) && Menu::Settings::optionCount <= Menu::Settings::currentOption) {
			GRAPHICS::DRAW_RECT(Menu::Settings::menuX, ((Menu::Settings::optionCount - (Menu::Settings::currentOption - Menu::Settings::maxVisOptions)) * 0.04f + 0.2212f), Width, OptionHeight, Settings::scroller.r, Menu::Settings::scroller.g, Menu::Settings::scroller.b, Menu::Settings::scroller.a);
			if (prevf < curf)
			{
				if (prevf + ScrollerSpeed > curf)
					prevf = prevf + (curf - prevf);
				else
					prevf = prevf + ScrollerSpeed;
				GRAPHICS::DRAW_RECT(Menu::Settings::menuX, ((Menu::Settings::optionCount - (Menu::Settings::currentOption - Menu::Settings::maxVisOptions)) * 0.04f + 0.2212f), Width, OptionHeight, Settings::scroller.r, Menu::Settings::scroller.g, Menu::Settings::scroller.b, Menu::Settings::scroller.a);
				if (prevf >= curf)
				{
					prevf = curf;
					*prev = cur;
				}
			}
			if (prevf > curf)
			{
				if (prevf - ScrollerSpeed < curf)
					prevf = prevf - (prevf - curf);
				prevf = prevf - ScrollerSpeed;
				GRAPHICS::DRAW_RECT(Menu::Settings::menuX, ((Menu::Settings::optionCount - (Menu::Settings::currentOption - Menu::Settings::maxVisOptions)) * 0.04f + 0.2212f), Width, OptionHeight, Settings::scroller.r, Menu::Settings::scroller.g, Menu::Settings::scroller.b, Menu::Settings::scroller.a);
				if (prevf <= curf)
				{
					prevf = curf;
					*prev = cur;
				}
			}
		}
	};

	float gGlareDir;
	float conv360(float base, float min, float max)
	{
		float fVar0;
		if (min == max) return min;
		fVar0 = max - min;
		base -= SYSTEM::ROUND(base - min / fVar0) * fVar0;
		if (base < min) base += fVar0;
		return base;
	}

	Vector2 GetSpriteScale(float size)
	{
		int x;
		int y;
		GRAPHICS::_GET_ACTIVE_SCREEN_RESOLUTION(&x, &y);

		return { (static_cast<float>(y) / static_cast<float>(x)) * size, size };
	}

	float GetTextHeight(Font font, float size)
	{
		return UI::_GET_TEXT_SCALE_HEIGHT(size, static_cast<int>(font));
	}

	RGBA color{ 255, 255, 255, 255 };

	float Menu::Settings::menuX = 0.8f;
	float Menu::Settings::menuY = 0.100f;

	bool Menu::Settings::Animescroll = true;
	bool Menu::Settings::selectPressed = false;
	bool Menu::Settings::leftPressed = false;
	bool Menu::Settings::rightPressed = false;
	bool firstopen = true;
	int Menu::Settings::maxVisOptions = 11;
	int Menu::Settings::currentOption = 0;
	int Menu::Settings::optionCount = 0;
	ProMenus Menu::Settings::currentMenu;
	int Menu::Settings::menuLevel = 0;
	int Menu::Settings::optionsArray[1000];
	ProMenus Menu::Settings::menusArray[1000];

	// Options
	float OptionTextSize = 0.35f;
	Font OptionFont = Font::ChaletLondon;
	float OptionPadding = 2.1f;
	RGBA Menu::Settings::OptionUnselectedBackgroundColor{ 0, 0, 0, 160 };
	RGBA Menu::Settings::scroller{ 0, 110, 0, 255 };

	RGBAF Menu::Settings::count{ 255, 255, 255, 255, 6 };
	RGBAF Menu::Settings::titleText{ 255, 255, 255, 255, 7 };
	RGBA Menu::Settings::titleRect{ 100, 0, 0, 255 };
	RGBAF Menu::Settings::optionText{ 255, 255, 255, 255, 0 };
	RGBAF Menu::Settings::breakText{ 255, 255, 255, 255, 0 };
	RGBAF Menu::Settings::arrow{ 255, 255, 255, 255, 3 };                          // Mod Menu Colors 
	RGBA Menu::Settings::optionRect{ 0, 0, 0, 130 };
	RGBA Menu::Settings::endoptionRect{ 0, 0, 0, 200 };
	RGBAF Menu::Settings::integre{ 255, 255, 255, 255, 2 };
	RGBA Menu::Settings::line{ 255, 255, 255, 255 };
	RGBA Menu::Settings::primary{ 255, 0, 0 };
	RGBA Menu::Settings::secondary{ 0, 255, 0 };
	RGBA Menu::Settings::Toggle_Raindow{ 0, 200, 0, 255 };

	RGBA Menu::Settings::HUD_COLOUR_PAUSE_RGB{ 0, 100, 0, 255 };

	void Menu::Title(char* title)
	{
		switch (Header_Type_Switch)
		{
		case Header_Type::Static:
			if (Header_Text)
			{
				DrawCenteredText(
					Mod_Menu_Name,
					Settings::menuX,
					drawBaseY + (HeaderHeight / 0.665f) - (GetTextHeight(HeaderFont, HeaderTextSize) / 2.f),
					HeaderTextSize,
					HeaderFont,
					Menu::Settings::HeaderTextColor,
					false, true);
			}
			Drawing::Rect(
				Settings::menuX,
				drawBaseY + (HeaderHeight / 0.665f), Width,
				HeaderHeight,
				Menu::Settings::HeaderBackgroundColor);
			break;

		case Header_Type::Gradient:
			if (Header_Text)
			{
				DrawCenteredText(
					Mod_Menu_Name,
					Settings::menuX,
					drawBaseY + (HeaderHeight / 0.665f) - (GetTextHeight(HeaderFont, HeaderTextSize) / 2.f),
					HeaderTextSize,
					HeaderFont,
					Menu::Settings::HeaderTextColor,
					false, true);
			}
			for (std::size_t i = 0; i < (HeaderGradientTransparent ? 1 : 20); ++i)
			{
				Drawing::Draw_Spriter(
					"aircraft_dials",
					"aircraft_dials_g0",
					Settings::menuX - (HeaderGradientStretch / 2.f),
					drawBaseY + (HeaderHeight / 0.665f),
					Width + HeaderGradientStretch + HeaderGradientFiller,
					HeaderHeight,
					HeaderGradientFlip ? 0.f : 180.f,
					Menu::Settings::HeaderGradientColorRight);
				Drawing::Draw_Spriter(
					"aircraft_dials",
					"aircraft_dials_g0",
					Settings::menuX + (HeaderGradientStretch / 2.f),
					drawBaseY + (HeaderHeight / 0.665f),
					Width + HeaderGradientStretch + HeaderGradientFiller,
					HeaderHeight,
					HeaderGradientFlip ? 180.f : 0.f,
					Menu::Settings::HeaderGradientColorLeft);
			}
			break;

		case Header_Type::Game_YTD:
			for (std::size_t i = 0; i < (HeaderGradientTransparent ? 1 : 20); ++i)
			{
				Drawing::Draw_Spriter("arcadeui_kitty_claw", "arcadeui_kitty_claw", Settings::menuX - (HeaderGradientStretch / 2.f),
					drawBaseY + (HeaderHeight + 0.05f),
					Width + HeaderGradientStretch + HeaderGradientFiller,
					HeaderHeight,
					0,
					color);
			}
			break;

		case Header_Type::Game_YTD_2:
			for (std::size_t i = 0; i < (HeaderGradientTransparent ? 1 : 20); ++i)
			{
				Drawing::Draw_Spriter("commonmenu", "gradient_nav", Settings::menuX - (HeaderGradientStretch / 2.f),
					drawBaseY + (HeaderHeight + 0.05f),
					Width + HeaderGradientStretch + HeaderGradientFiller,
					HeaderHeight,
					0,
					color);
			}
			break;

		case Header_Type::YTD:
			for (std::size_t i = 0; i < (HeaderGradientTransparent ? 1 : 20); ++i)
			{
				string YTD_Stream_Texture = "MH_BAse_"; // your ytd file name dont use .ytd here
				string YTD_Texture_Name = "MH_Base_TxName"; // your texture name in your ytd file

				Drawing::Draw_Spriter(YTD_Stream_Texture, YTD_Texture_Name, Settings::menuX - (HeaderGradientStretch / 2.f),
					drawBaseY + (HeaderHeight + 0.05f),
					Width + HeaderGradientStretch + HeaderGradientFiller,
					HeaderHeight,
					0,
					color);
			}
			break;
		}

		Drawing::Text(title, { 120, 120, 120, 255 }, { Settings::menuX - /*x = side>*/(Width / SubmenuBarPadding), /*y = upp>*/ drawBaseY + (SubmenuBarHeight / 0.182f) - (GetTextHeight(Menu::Settings::SubmenuBarFont, SubmenuBarTextSize) / 1.5f) }, { 0.42f, 0.42f }, false);

		Drawing::Rect(Settings::menuX,
			drawBaseY + (SubmenuBarHeight / 0.1815f), // 0.182f
			Width, SubmenuBarHeight, // Width and Bar Height
			{ 30, 30, 30, 220 }); // color 


		// Disable Controls
		UI::HIDE_HELP_TEXT_THIS_FRAME();
		CAM::SET_CINEMATIC_BUTTON_ACTIVE(0);
		UI::HIDE_HUD_COMPONENT_THIS_FRAME(10);
		UI::HIDE_HUD_COMPONENT_THIS_FRAME(6);
		UI::HIDE_HUD_COMPONENT_THIS_FRAME(7);
		UI::HIDE_HUD_COMPONENT_THIS_FRAME(9);
		UI::HIDE_HUD_COMPONENT_THIS_FRAME(8);
		CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_NEXT_CAMERA, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_CHARACTER_WHEEL, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_MELEE_ATTACK_LIGHT, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_MELEE_ATTACK_HEAVY, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_MULTIPLAYER_INFO, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_PHONE, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_MELEE_ATTACK_ALTERNATE, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_VEH_CIN_CAM, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_MAP_POI, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_PHONE, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_VEH_RADIO_WHEEL, true);
		CONTROLS::DISABLE_CONTROL_ACTION(2, INPUT_VEH_HEADLIGHT, true);
	}

	bool Menu::Option(char* option, char* description) // not done Yet [comes in next updt]
	{
		Settings::optionCount++;
		auto spriteSize = GetSpriteScale(DescriptionSpriteSize);
		bool onThis = Settings::currentOption == Settings::optionCount ? true : false;


		if (Settings::currentOption <= 11 && Settings::optionCount <= 11)
		{
			Drawing::Text(option, Settings::optionText, { Settings::menuX - 0.115f, (Settings::optionCount) * 0.040f + 0.2047f }, { 0.4f, 0.4f }, false);
			Drawing::Rect(Menu::Settings::OptionUnselectedBackgroundColor, { Settings::menuX, (Settings::optionCount) * 0.040f + 0.2212f }, { Width, OptionHeight });
			if (!Settings::Animescroll)
			{
				onThis ? Drawing::Rect(Settings::scroller, { Settings::menuX, (Settings::optionCount) * 0.040f + 0.2212f }, { Width, OptionHeight }) : NULL;
			}
		}
		else if (Settings::optionCount > (Settings::currentOption - 11) && Settings::optionCount <= Settings::currentOption)
		{
			Drawing::Text(option, Settings::optionText, { Settings::menuX - 0.115f, (Settings::optionCount - (Settings::currentOption - 11)) * 0.040f + 0.2047f }, { 0.4f, 0.4f }, false);
			Drawing::Rect(Menu::Settings::OptionUnselectedBackgroundColor, { Settings::menuX,  (Settings::optionCount - (Settings::currentOption - 11)) * 0.040f + 0.2212f }, { Width, OptionHeight });
			if (!Settings::Animescroll)
			{
				onThis ? Drawing::Rect(Settings::scroller, { Settings::menuX,  (Settings::optionCount - (Settings::currentOption - 11)) * 0.040f + 0.2212f }, { Width, OptionHeight }) : NULL;
			}
		}
		if (Settings::Animescroll)
			if (onThis)
				animscroll(&prevOption, Settings::currentOption);

		if (Settings::currentOption == Settings::optionCount)
		{
			if (Settings::selectPressed)
			{
				return true;
			}
		}
		return false;
	}
	bool Menu::Option(char* option)
	{
		Settings::optionCount++;
		bool onThis = Settings::currentOption == Settings::optionCount ? true : false;
		if (Settings::currentOption <= 11 && Settings::optionCount <= 11)
		{
			Drawing::Text(option, Settings::optionText, { Settings::menuX - 0.115f, (Settings::optionCount) * 0.040f + 0.2047f }, { 0.4f, 0.4f }, false);
			Drawing::Rect(Menu::Settings::OptionUnselectedBackgroundColor, { Settings::menuX, (Settings::optionCount) * 0.040f + 0.2212f }, { Width, OptionHeight });
			if (Settings::Animescroll == false)
			{
				onThis ? Drawing::Rect(Settings::scroller, { Settings::menuX, (Settings::optionCount) * 0.040f + 0.2212f }, { Width, OptionHeight }) : NULL;
			}
		}
		else if (Settings::optionCount > (Settings::currentOption - 11) && Settings::optionCount <= Settings::currentOption)
		{
			Drawing::Text(option, Settings::optionText, { Settings::menuX - 0.115f, (Settings::optionCount - (Settings::currentOption - 11)) * 0.040f + 0.2047f }, { 0.4f, 0.4f }, false);
			Drawing::Rect(Menu::Settings::OptionUnselectedBackgroundColor, { Settings::menuX,  (Settings::optionCount - (Settings::currentOption - 11)) * 0.040f + 0.2212f }, { Width, OptionHeight });
			if (Settings::Animescroll == false)
			{
				onThis ? Drawing::Rect(Settings::scroller, { Settings::menuX,  (Settings::optionCount - (Settings::currentOption - 11)) * 0.040f + 0.2212f }, { Width, OptionHeight }) : NULL;
			}
		}
		if (Settings::Animescroll)
			if (onThis)
				animscroll(&prevOption, Settings::currentOption);

		if (Settings::currentOption == Settings::optionCount)
		{
			if (Settings::selectPressed)
			{
				return true;
			}
		}
		return false;
	}

	bool Menu::Option(char* option, std::function<void()> function)
	{
		Option(option);

		if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
			function();
			return true;
		}
		return false;
	}

	bool Menu::Break(char* option)
	{
		Settings::optionCount++;
		bool onThis = Settings::currentOption == Settings::optionCount ? true : false;
		if (Settings::currentOption <= 11 && Settings::optionCount <= 11)
		{
			Drawing::Text(option, Settings::breakText, { Settings::menuX - .028f, (Settings::optionCount) * 0.040f + 0.2047f }, { 0.4f, 0.4f }, false);
			Drawing::Rect(Settings::optionRect, { Settings::menuX, (Settings::optionCount) * 0.040f + 0.2212f }, { Width, OptionHeight });
		}
		else if (Settings::optionCount > (Settings::currentOption - 11) && Settings::optionCount <= Settings::currentOption)
		{
			Drawing::Text(option, Settings::breakText, { Settings::menuX, (Settings::optionCount - (Settings::currentOption - 11)) * 0.040f + 0.2047f }, { 0.4f, 0.4f }, false);
			Drawing::Rect(Settings::optionRect, { Settings::menuX,  (Settings::optionCount - (Settings::currentOption - 11)) * 0.040f + 0.2212f }, { Width, OptionHeight });
		}
		return false;
	}
	bool Menu::MenuOption(char* option, ProMenus newSub)
	{
		Option(option);

		if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
			Drawing::Draw_Spriter("commonmenu", "arrowright", Settings::menuX + 0.099f, Settings::optionCount * 0.040f + 0.2215f, drawBaseY + (FooterHeight / 2.f), 0.035f, rotation, Menu::Settings::FooterSpriteColor);
		else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
			Drawing::Draw_Spriter("commonmenu", "arrowright", Settings::menuX + 0.099f, (Settings::optionCount - (Settings::currentOption - 11)) * 0.040f + 0.2215f, drawBaseY + (FooterHeight / 2.f), 0.035f, rotation, Menu::Settings::FooterSpriteColor);

		if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
			MenuLevelHandler::MoveMenu(newSub);
			return true;
		}
		return false;
	}

	bool Menu::OnOffSwitch = false;
	bool Menu::YesNoSwitch = false;
	bool Menu::IconSwitch = true;
	bool Menu::plopSwitch = false;

	bool Menu::Toggle(char* option, bool& b00l)
	{
		if (Menu::OnOffSwitch)
		{
			Option(option);
			if (b00l)
			{
				if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
					Drawing::Text(b00l ? "~g~ON" : "~r~OFF", Settings::optionText, { Settings::menuX + 0.1f, Settings::optionCount * 0.04f + 0.2055f }, { 0.40f, 0.40f }, true); // 0.35 // 0.125 // 0.45
				else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
					Drawing::Text(b00l ? "~g~ON" : "~r~OFF", Settings::optionText, { Settings::menuX + 0.1f, Settings::optionCount * 0.04f + 0.2055f }, { 0.40f, 0.40f }, true);
			}
			else
			{
				if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
					Drawing::Text(b00l ? "~g~ON" : "~r~OFF", Settings::optionText, { Settings::menuX + 0.1f, Settings::optionCount * 0.04f + 0.2055f }, { 0.40f, 0.40f }, true);
				else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
					Drawing::Text(b00l ? "~g~ON" : "~r~OFF", Settings::optionText, { Settings::menuX + 0.1f, Settings::optionCount * 0.04f + 0.2055f }, { 0.40f, 0.40f }, true);
			}
			if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
				b00l ^= 1;
				return true;
			}
		}

		if (Menu::YesNoSwitch)
		{
			Option(option);
			if (b00l)
			{
				if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
					Drawing::Text(b00l ? "~g~YES" : "~r~NO", Settings::optionText, { Settings::menuX + 0.1f, Settings::optionCount * 0.04f + 0.2055f }, { 0.40f, 0.40f }, true); // 0.35 // 0.125 // 0.45
				else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
					Drawing::Text(b00l ? "~g~YES" : "~r~NO", Settings::optionText, { Settings::menuX + 0.1f, Settings::optionCount * 0.04f + 0.2055f }, { 0.40f, 0.40f }, true);
			}
			else
			{
				if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
					Drawing::Text(b00l ? "~g~YES" : "~r~NO", Settings::optionText, { Settings::menuX + 0.1f, Settings::optionCount * 0.04f + 0.2055f }, { 0.40f, 0.40f }, true);
				else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
					Drawing::Text(b00l ? "~g~YES" : "~r~NO", Settings::optionText, { Settings::menuX + 0.1f, Settings::optionCount * 0.04f + 0.2055f }, { 0.40f, 0.40f }, true);
			}
			if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
				b00l ^= 1;
				return true;
			}
		}

		if (Menu::IconSwitch)
		{
			Option(option);
			if (b00l)
			{
				if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
					Drawing::Draw_Spriter("commonmenu", "shop_tick_icon", Settings::menuX + 0.1f, (Settings::optionCount * 0.04f + 0.221f), 0.023f, 0.047f, 0, { Settings::Toggle_Raindow });
				else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
					Drawing::Draw_Spriter("commonmenu", "shop_tick_icon", Settings::menuX + 0.1f, ((Settings::optionCount - (Settings::currentOption - 11)) * 0.04f + 0.221f), 0.03f, 0.054f, 0, { Settings::Toggle_Raindow });

				if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
					Drawing::Draw_Spriter("commonmenu", "shop_box_blankb", Settings::menuX + 0.1f, (Settings::optionCount * 0.04f + 0.221f), 0.03f, 0.054f, 0, { 57, 25, 23, 255 });
				else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
					Drawing::Draw_Spriter("commonmenu", "shop_box_blankb", Settings::menuX + 0.1f, ((Settings::optionCount - (Settings::currentOption - 11)) * 0.04f + 0.221f), 0.016f, 0.028f, 0, { 57, 25, 23, 255 });
			}
			else
			{
				if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
					Drawing::Draw_Spriter("commonmenu", "shop_box_crossb", Settings::menuX + 0.1f, (Settings::optionCount * 0.04f + 0.221f), 0.025f, 0.037f, 0, { 255, 0, 0, 255 });
				else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
					Drawing::Draw_Spriter("commonmenu", "shop_box_crossb", Settings::menuX + 0.1f, ((Settings::optionCount - (Settings::currentOption - 11)) * 0.04f + 0.221f), 0.025f, 0.037f, 0, { 255, 0, 0, 255 });
			}
			if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
				b00l ^= 1;
				return true;
			}
		}

		if (Menu::plopSwitch)
		{
			Option(option);
			if (b00l)
			{
				if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
					Drawing::Draw_Spriter("shared", "medaldot_32", Settings::menuX + 0.1f, (Settings::optionCount * 0.04f + 0.221f), 0.025f, 0.037f, 0, { Settings::Toggle_Raindow });
				else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
					Drawing::Draw_Spriter("shared", "medaldot_32", Settings::menuX + 0.1f, ((Settings::optionCount - (Settings::currentOption - 11)) * 0.04f + 0.221f), 0.025f, 0.037f, 0, { Settings::Toggle_Raindow });
			}
			else
			{
				if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
					Drawing::Draw_Spriter("shared", "emptydot_32", Settings::menuX + 0.1f, (Settings::optionCount * 0.04f + 0.221f), 0.025f, 0.037f, 0, { 255, 0, 0, 255 });
				else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
					Drawing::Draw_Spriter("shared", "emptydot_32", Settings::menuX + 0.1f, ((Settings::optionCount - (Settings::currentOption - 11)) * 0.04f + 0.221f), 0.025f, 0.037f, 0, { 255, 0, 0, 255 });
			}
			if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
				b00l ^= 1;
				return true;
			}
		}
		return false;
	}


	bool Menu::Int(char* option, int& _int, int min, int max)
	{
		Option(option);

		if (Settings::optionCount == Settings::currentOption) {
			if (Settings::leftPressed) {
				_int < max ? _int++ : _int = min;
			}
			if (Settings::rightPressed) {
				_int >= min ? _int-- : _int = max;
			}
			_int < min ? _int = max : _int > max ? _int = min : NULL;
		}

		if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
			Drawing::Text(Tools::StringToChar("[ " + std::to_string(_int) + std::string(" <=> ") + std::to_string(max) + " ]"), Settings::integre, { Settings::menuX + 0.085f, Settings::optionCount * 0.04f + 0.207f }, { 0.4f, 0.4f }, true);
		else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
			Drawing::Text(Tools::StringToChar("[ " + std::to_string(_int) + std::string(" <=> ") + std::to_string(max) + " ]"), Settings::integre, { Settings::menuX + 0.085f, (Settings::optionCount - (Settings::currentOption - 11)) * 0.04f + 0.207f }, { 0.4f, 0.4f }, true);

		if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
		else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
		else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
		return false;
	}
	bool Menu::Int(char* option, int& _int, int min, int max, int step)
	{
		Option(option);

		if (Settings::optionCount == Settings::currentOption) {
			if (Settings::leftPressed) {
				_int < max ? _int += step : _int = min;
			}
			if (Settings::rightPressed) {
				_int >= min ? _int -= step : _int = max;
			}
			_int < min ? _int = max : _int > max ? _int = min : NULL;
		}

		if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
			Drawing::Text(Tools::StringToChar("[ " + std::to_string(_int) + " <=> " + std::to_string(max) + " ]"), Settings::integre, { Settings::menuX + 0.085f, Settings::optionCount * 0.04f + 0.207f }, { 0.4f, 0.4f }, true);
		else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
			Drawing::Text(Tools::StringToChar("[ " + std::to_string(_int) + " <=> " + std::to_string(max) + " ]"), Settings::integre, { Settings::menuX + 0.085f, (Settings::optionCount - (Settings::currentOption - 11)) * 0.04f + 0.207f }, { 0.4f, 0.4f }, true);

		if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
		else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
		else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
		return false;
	}
#pragma warning(disable: 4244)
	bool Menu::Float(char* option, float& _float, int min, int max)
	{
		Option(option);

		if (Settings::optionCount == Settings::currentOption) {
			if (Settings::leftPressed) {
				_float <= min ? _float = max : _float -= 0.1f;
			}
			if (Settings::rightPressed) {
				_float >= max ? _float = min : _float += 0.1f;
			}
			_float < min ? _float = max : _float > max ? _float = min : NULL;
		}

		if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
			Drawing::Text(Tools::StringToChar(std::to_string(_float)), Settings::optionText, { Settings::menuX + 0.085f, Settings::optionCount * 0.04f + 0.207f }, { 0.4f, 0.4f }, true);
		else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
			Drawing::Text(Tools::StringToChar(std::to_string(_float)), Settings::optionText, { Settings::menuX + 0.085f, (Settings::optionCount - (Settings::currentOption - 11)) * 0.04f + 0.207f }, { 0.4f, 0.4f }, true);

		if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
		else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
		else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
		return false;
	}
	bool Menu::Float(char* option, float& _float, int min, int max, int step)
	{
		Option(option);

		if (Settings::optionCount == Settings::currentOption) {
			if (Settings::leftPressed) {
				_float <= min ? _float = max : _float -= 0.1f;
			}
			if (Settings::rightPressed) {
				_float >= max ? _float = min : _float += 0.1f;
			}
			_float < min ? _float = max : _float > max ? _float = min : NULL;
		}

		if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
			Drawing::Text(Tools::StringToChar(std::to_string(_float)), Settings::optionText, { Settings::menuX + 0.085f, Settings::optionCount * 0.04f + 0.207f }, { 0.4f, 0.4f }, true);
		else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
			Drawing::Text(Tools::StringToChar(std::to_string(_float)), Settings::optionText, { Settings::menuX + 0.085f, (Settings::optionCount - (Settings::currentOption - 11)) * 0.04f + 0.207f }, { 0.4f, 0.4f }, true);

		if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
		else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
		else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
		return false;
	}
#pragma warning(default: 4244)
#pragma warning(disable: 4267)
	bool Menu::IntVector(char* option, std::vector<int> Vector, int& position)
	{
		Option(option);

		if (Settings::optionCount == Settings::currentOption) {
			int max = Vector.size() - 1;
			int min = 0;
			if (Settings::leftPressed) {
				position >= 1 ? position-- : position = max;
			}
			if (Settings::rightPressed) {
				position < max ? position++ : position = min;
			}
		}

		if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
			Drawing::Text(Tools::StringToChar(std::to_string(Vector[position])), Settings::optionText, { Settings::menuX + 0.085f, Settings::optionCount * 0.04f + 0.207f }, { 0.5f, 0.5f }, true);
		else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
			Drawing::Text(Tools::StringToChar(std::to_string(Vector[position])), Settings::optionText, { Settings::menuX + 0.085f, (Settings::optionCount - (Settings::currentOption - 11)) * 0.04f + 0.207f }, { 0.5f, 0.5f }, true);

		if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
		else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
		else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
		return false;
	}
	bool Menu::FloatVector(char* option, std::vector<float> Vector, int& position)
	{
		Option(option);

		if (Settings::optionCount == Settings::currentOption) {
			size_t max = Vector.size() - 1;
			int min = 0;
			if (Settings::leftPressed) {
				position >= 1 ? position-- : position = max;
			}
			if (Settings::rightPressed) {
				position < max ? position++ : position = min;
			}
		}

		if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
			Drawing::Text(Tools::StringToChar(std::to_string(Vector[position])), Settings::optionText, { Settings::menuX + 0.085f, Settings::optionCount * 0.04f + 0.207f }, { 0.4f, 0.4f }, true);
		else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
			Drawing::Text(Tools::StringToChar(std::to_string(Vector[position])), Settings::optionText, { Settings::menuX + 0.085f, (Settings::optionCount - (Settings::currentOption - 11)) * 0.04f + 0.207f }, { 0.4f, 0.4f }, true);

		if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
		else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
		else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
		return false;
	}
	bool Menu::StringVector(char* option, std::vector<std::string> Vector, int& position)
	{
		Option(option);

		if (Settings::optionCount == Settings::currentOption) {
			size_t max = Vector.size() - 1;
			int min = 0;
			if (Settings::leftPressed) {
				position >= 1 ? position-- : position = max;
			}
			if (Settings::rightPressed) {
				position < max ? position++ : position = min;
			}
		}

		if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
			Drawing::Text(Tools::StringToChar((Vector[position])), Settings::optionText, { Settings::menuX + 0.085f, Settings::optionCount * 0.04f + 0.207f }, { 0.4f, 0.4f }, true);
		else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
			Drawing::Text(Tools::StringToChar((Vector[position])), Settings::optionText, { Settings::menuX + 0.085f, (Settings::optionCount - (Settings::currentOption - 11)) * 0.04f + 0.207f }, { 0.4f, 0.4f }, true);

		if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
		else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
		else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
		return false;
	}
	bool Menu::StringVector(char* option, std::vector<char*> Vector, int& position)
	{
		Option(option);

		if (Settings::optionCount == Settings::currentOption) {
			size_t max = Vector.size() - 1;
			int min = 0;
			if (Settings::leftPressed) {
				position >= 1 ? position-- : position = max;
			}
			if (Settings::rightPressed) {
				position < max ? position++ : position = min;
			}
		}

		if (Settings::currentOption <= Settings::maxVisOptions && Settings::optionCount <= Settings::maxVisOptions)
			Drawing::Text(((Vector[position])), Settings::optionText, { Settings::menuX + 0.085f, Settings::optionCount * 0.04f + 0.207f }, { 0.4f, 0.4f }, true);
		else if (Settings::optionCount > Settings::currentOption - Settings::maxVisOptions && Settings::optionCount <= Settings::currentOption)
			Drawing::Text(((Vector[position])), Settings::optionText, { Settings::menuX + 0.085f, (Settings::optionCount - (Settings::currentOption - 11)) * 0.04f + 0.207f }, { 0.4f, 0.4f }, true);

		if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) return true;
		else if (Settings::optionCount == Settings::currentOption && Settings::leftPressed) return true;
		else if (Settings::optionCount == Settings::currentOption && Settings::rightPressed) return true;
		return false;
	}
#pragma warning(default: 4267)
	bool Menu::Teleport(char* option, Vector3 coords)
	{
		Option(option);

		if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
			Entity handle;
			PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false) ? handle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID()) : PLAYER::PLAYER_PED_ID();
			ENTITY::SET_ENTITY_COORDS(handle, coords.x, coords.y, coords.z, false, false, false, false);
			return true;
		}
		return false;
	}
	bool Menu::Teleport(char* option, Vector3 coords, std::function<void()> function)
	{
		Teleport(option, coords);

		if (Settings::optionCount == Settings::currentOption && Settings::selectPressed) {
			function();
			return true;
		}
		return false;
	}

	void Menu::End()
	{
		int opcount = Settings::optionCount;
		int currop = Settings::currentOption;
		if (opcount >= 11) {
			Drawing::Text(Tools::StringToChar(std::to_string(currop) + " / " + std::to_string(opcount)), { 120, 120, 120, 255 }, { Settings::menuX + 0.078f, 11 * 0.0187f }, { SubmenuBarTextSize, SubmenuBarTextSize }, true);
			Drawing::Rect(Settings::menuX, (11 + 1) * 0.040f + 0.221f, Width, FooterHeight, { 20, 20, 20, 220 });
			if (currop == 1)
			{
				Drawing::Draw_Spriter("commonmenu", "arrowright", Settings::menuX, ((11 + 1) * 0.04f + 0.222f), 0.020f, 0.035f, 90, Menu::Settings::FooterSpriteColor);
			}
			else if (currop == opcount)
			{
				Drawing::Draw_Spriter("commonmenu", "arrowright", Settings::menuX, ((11 + 1) * 0.04f + 0.221f), 0.020f, 0.035f, -90, Menu::Settings::FooterSpriteColor);
			}
			else
			{
				Drawing::Draw_Spriter("commonmenu", "shop_arrows_upanddown", Settings::menuX, ((11 + 1) * 0.04f + 0.22f), 0.020f, 0.035f, 180, Menu::Settings::FooterSpriteColor);
			}
		}
		else if (opcount > 0) {
			Drawing::Text(Tools::StringToChar(std::to_string(currop) + " / " + std::to_string(opcount)), { 120, 120, 120, 255 }, { Settings::menuX + 0.078f, 11 * 0.0187f }, { SubmenuBarTextSize, SubmenuBarTextSize }, true);
			Drawing::Rect(Settings::menuX, (Settings::optionCount + 1) * 0.040f + 0.221f, Width, FooterHeight, { 20, 20, 20, 220 });
			if (currop == 1)
			{
				Drawing::Draw_Spriter("commonmenu", "arrowright", Settings::menuX, ((Settings::optionCount + 1) * 0.040f + 0.222f), 0.020f, 0.035f, 90, Menu::Settings::FooterSpriteColor);
			}
			else if (currop == opcount)
			{
				Drawing::Draw_Spriter("commonmenu", "arrowright", Settings::menuX, ((Settings::optionCount + 1) * 0.040f + 0.221f), 0.020f, 0.035f, -90, Menu::Settings::FooterSpriteColor);
			}
			else
			{
				Drawing::Draw_Spriter("commonmenu", "shop_arrows_upanddown", Settings::menuX, ((Settings::optionCount + 1) * 0.040f + 0.22f), 0.020f, 0.035f, 180, Menu::Settings::FooterSpriteColor);
			}
		}
	}

	void PlaySoundFrontend_default(char* sound_name)
	{
		AUDIO::PLAY_SOUND_FRONTEND(-1, sound_name, "HUD_FRONTEND_DEFAULT_SOUNDSET", 0);
	}
	void PlaySoundFrontend_default2(char* sound_name)
	{
		AUDIO::PLAY_SOUND_FRONTEND(-1, sound_name, "DLC_HEIST_BIOLAB_PREP_HACKING_SOUNDS", 0);
	}

	int Menu::Settings::keyPressDelay = 200;
	int Menu::Settings::keyPressPreviousTick = GetTickCount();
	int Menu::Settings::keyPressDelay2 = 100;
	int Menu::Settings::keyPressPreviousTick2 = GetTickCount();
	int Menu::Settings::keyPressDelay3 = 140;
	int Menu::Settings::keyPressPreviousTick3 = GetTickCount();
	int Menu::Settings::openKey = VK_F4;
	int Menu::Settings::backKey = VK_NUMPAD0;
	int Menu::Settings::upKey = VK_NUMPAD8;
	int Menu::Settings::downKey = VK_NUMPAD2;
	int Menu::Settings::leftKey = VK_NUMPAD4;
	int Menu::Settings::rightKey = VK_NUMPAD6;
	int Menu::Settings::selectKey = VK_NUMPAD5;
	int Menu::Settings::arrowupKey = VK_UP;
	int Menu::Settings::arrowdownKey = VK_DOWN;
	int Menu::Settings::arrowleftKey = VK_LEFT;
	int Menu::Settings::arrowrightKey = VK_RIGHT;
	int Menu::Settings::enterKey = VK_RETURN;
	int Menu::Settings::deleteKey = VK_BACK;

#pragma endregion

	bool Menu::Settings::controllerinput = true;
	void Menu::Checks::Controlls()
	{
		Settings::selectPressed = false;
		Settings::leftPressed = false;
		Settings::rightPressed = false;
		if (GetTickCount() - Settings::keyPressPreviousTick > Settings::keyPressDelay) {
			if (GetTickCount() - Settings::keyPressPreviousTick2 > Settings::keyPressDelay2) {
				if (GetTickCount() - Settings::keyPressPreviousTick3 > Settings::keyPressDelay3) {
					if (IsKeyPressed(Menu::Settings::openKey) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlScriptRB) && CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlPhoneRight) && Settings::controllerinput) {
						Settings::menuLevel == 0 ? MenuLevelHandler::MoveMenu(ProMenus::mainmenu) : Settings::menuLevel == 1 ? MenuLevelHandler::BackMenu() : NULL;
						Settings::keyPressPreviousTick = GetTickCount();
					}
					else if (IsKeyPressed(Menu::Settings::backKey) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendCancel) && Settings::controllerinput) {
						Settings::menuLevel > 0 ? MenuLevelHandler::BackMenu() : NULL;
						if (Settings::menuLevel > 0)
							PlaySoundFrontend_default("BACK");

						Settings::keyPressPreviousTick = GetTickCount();
					}
					else if (IsKeyPressed(Menu::Settings::upKey) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendUp) && Settings::controllerinput) {
						Settings::currentOption > 1 ? Settings::currentOption-- : Settings::currentOption = Settings::optionCount;
						if (Settings::menuLevel > 0)
							PlaySoundFrontend_default("NAV_UP_DOWN");

						Settings::keyPressPreviousTick2 = GetTickCount();
					}
					else if (IsKeyPressed(Menu::Settings::downKey) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendDown) && Settings::controllerinput) {
						Settings::currentOption < Settings::optionCount ? Settings::currentOption++ : Settings::currentOption = 1;
						if (Settings::menuLevel > 0)
							PlaySoundFrontend_default("NAV_UP_DOWN");

						Settings::keyPressPreviousTick2 = GetTickCount();
					}
					else if (IsKeyPressed(Menu::Settings::rightKey) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlPhoneRight) && Settings::controllerinput) {
						Settings::leftPressed = true;
						if (Settings::menuLevel > 0)
							PlaySoundFrontend_default("NAV_UP_DOWN");

						Settings::keyPressPreviousTick3 = GetTickCount();
					}
					else if (IsKeyPressed(Menu::Settings::leftKey) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlPhoneLeft) && Settings::controllerinput) {
						Settings::rightPressed = true;
						if (Settings::menuLevel > 0)
							PlaySoundFrontend_default("NAV_UP_DOWN");

						Settings::keyPressPreviousTick3 = GetTickCount();
					}
					else if (IsKeyPressed(Menu::Settings::selectKey) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept) && Settings::controllerinput) {
						Settings::selectPressed = true;
						if (Settings::menuLevel > 0)
							PlaySoundFrontend_default("SELECT");

						Settings::keyPressPreviousTick = GetTickCount();
					}
				}
			}
		}
		Settings::optionCount = 0;
	}
#pragma warning(default : 4018)
	void Menu::MenuLevelHandler::MoveMenu(ProMenus menu)
	{
		Settings::menusArray[Settings::menuLevel] = Settings::currentMenu;
		Settings::optionsArray[Settings::menuLevel] = Settings::currentOption;
		Settings::menuLevel++;
		Settings::currentMenu = menu;
		Settings::currentOption = 1;
	}

	void Menu::MenuLevelHandler::BackMenu()
	{
		Settings::menuLevel--;
		Settings::currentMenu = Settings::menusArray[Settings::menuLevel];
		Settings::currentOption = Settings::optionsArray[Settings::menuLevel];
	}

	char* Menu::Tools::StringToChar(std::string string)
	{
		return _strdup(string.c_str());
	}

	void Menu::Files::WriteStringToIni(std::string string, std::string file, std::string app, std::string key)
	{
		WritePrivateProfileStringA(app.c_str(), key.c_str(), string.c_str(), file.c_str());
	}

	std::string Menu::Files::ReadStringFromIni(std::string file, std::string app, std::string key)
	{
		char buf[100];
		GetPrivateProfileStringA(app.c_str(), key.c_str(), "NULL", buf, 100, file.c_str());
		return (std::string)buf;
	}

	void Menu::Files::WriteIntToIni(int intValue, std::string file, std::string app, std::string key)
	{
		WriteStringToIni(std::to_string(intValue), file, app, key);
	}

	int Menu::Files::ReadIntFromIni(std::string file, std::string app, std::string key)
	{
		return std::stoi(ReadStringFromIni(file, app, key));
	}

	void Menu::Files::WriteFloatToIni(float floatValue, std::string file, std::string app, std::string key)
	{
		WriteStringToIni((std::to_string(floatValue)), file, app, key);
	}

	float Menu::Files::ReadFloatFromIni(std::string file, std::string app, std::string key)
	{
		return std::stof(ReadStringFromIni(file, app, key));
	}

	void Menu::Files::WriteBoolToIni(bool b00l, std::string file, std::string app, std::string key)
	{
		WriteStringToIni(b00l ? "true" : "false", file, app, key);
	}

	bool Menu::Files::ReadBoolFromIni(std::string file, std::string app, std::string key)
	{
		return ReadStringFromIni(file, app, key) == "true" ? true : false;
	}

	void Menu::Speedometer(char* text)
	{
		Drawing::Text(text, Settings::titleText, { 0.84f, 0.8800f }, { 0.70f, 0.70f }, false);
	}
	void Menu::fps(char* text)
	{
		Drawing::Text(text, Settings::optionText, { 0.84f, 0.050f }, { 0.70f, 0.70f }, false);
	}

	void Menu::OptionInfo(char* description) {
		auto currentOPtion = Settings::currentOption;
		auto optionCount = Settings::optionCount;
		VECTOR2 position = { Settings::menuX, (optionCount + 2) * 0.035f + Settings::menuY + 0.0547f };
		VECTOR2 t_position = { Settings::menuX - 0.09f, (optionCount + 2) * 0.035f + Settings::menuY + 0.0410f };
		VECTOR2_2 size = { Settings::menuXscale, 0.035f };
		if (!GAMEPLAY::IS_STRING_NULL_OR_EMPTY(const_cast<char*>((char*)description))) {
			//Drawing::Rect({ 0, 0, 0, 175 }, position, size);
			//Drawing::Text(const_cast<char*>((char*)description), { 255, 255, 255, 255, 4 }, t_position, { 0.41f, 0.41f }, false);
		}
	}
}