#pragma once
#include "stdafx.h"
bool First_start = true;
void fisrt_start()
{
	using namespace Mod_Hub_Base;

	g_YtdLoader->init();
	g_YtdLoader->loadYtd(Documents_Patha() + /*this ytd file path*/"\\MH_BAse_.ytd", /*this is your file*/"MH_BAse_.ytd"); // this start/booting upp your ytd file
	/*TO CHANGE THE SETTINGS IN THE MAIN TITLE GO THERE AND YOU WILL FIND 
	YTD_Stream_Texture AND YTD_Texture_Name
	AND THERE YOU EDIT IN YOUR CUSTOM NAMES DOME.*/
	notify_Custom((char*)Mod_Menu_Name"", " ~g~Loaded!!");
}
namespace Mod_Hub_Base
{
	void main() {

		while (true) {
			Menu::Checks::Controlls();
			Menu::scrollbar_Rainbow();
			Menu::Toggle_Rainbow();
			Menu::Rainbow_Title();
			/* Features */
			Function_update_Loop();
			if (First_start)
			{
				fisrt_start();
				First_start = false;
			}

			switch (Menu::Settings::currentMenu) {

			case mainmenu:
			{
				Menu::Title("Home");
				Menu::MenuOption("Local", Local);
				Menu::MenuOption("Online Session", Online);
				Menu::MenuOption("Settings", Settings);
				if (Menu::Option("Unload " Mod_Menu_Name)) { Mod_running = false; }
			}
			break;

#pragma region Local Menu
			case Local:
			{
				Menu::Title("Self Menu");
				Menu::Toggle("Godmode", Godmode);
				Menu::Toggle("Invisible", Invisible);
			}
			break;
#pragma endregion

#pragma region Online Session Menu
			case Online:
			{
				Menu::Title("Online Session");
				for (int i = 0; i < 32; ++i)
				{
					if (ENTITY::DOES_ENTITY_EXIST(PLAYER::GET_PLAYER_PED(i)))
					{
						Menu::MenuOption(PLAYER::GET_PLAYER_NAME(i), PlayerMenu) ? g_SelectedPlayer = i : NULL;
					}
				}
			}
			break;
#pragma endregion

#pragma region Online Player Session Menu
			case PlayerMenu:
			{
				Menu::Title(PLAYER::GET_PLAYER_NAME(g_SelectedPlayer));
			}
			break;
#pragma endregion

#pragma region Settings Menu
			case Settings:
			{
				Menu::Title("Settings");
				Menu::MenuOption("Theme", Theme_Options);
				Menu::MenuOption("Title ~y~Options", Title_Options);
				Menu::MenuOption("~g~Toggle ~y~Options", ToggleOptions);
				Menu::MenuOption("Scroller ~y~Options", Scroller_Options);
				if (Menu::Option("MenuX plus")) {
					if (Menu::Settings::menuX < 0.8f) Menu::Settings::menuX += 0.01f;
				}
				if (Menu::Option("MenuX minus")) {
					if (Menu::Settings::menuX > 0.17f) Menu::Settings::menuX -= 0.01f;
				}
				Menu::Toggle("Anti CEO Kick", Protections::Anti_CEO_Kick);
				Menu::Toggle("Script Event Log", g_LogScriptEvents);
				if (Menu::Option("~r~Quit GTA??", "exit gta")) exit(0);
			}
			break;
#pragma endregion Settings Menu

#pragma region Settings Theme Menu
			case Theme_Options:
			{
				Menu::Title("Title Options");
				if (Menu::Option("Green"))
				{
					Menu::Settings::scroller.r = 0, Menu::Settings::scroller.g = 255, Menu::Settings::scroller.b = 0,
						Menu::Settings::HeaderTextColor.r = 0, Menu::Settings::HeaderTextColor.g = 255, Menu::Settings::HeaderTextColor.b = 0,
						Menu::Settings::Toggle_Raindow.r = 0, Menu::Settings::Toggle_Raindow.g = 255, Menu::Settings::Toggle_Raindow.b = 0;
				}
			}
			break;
#pragma endregion Settings Theme Menu end

#pragma region Settings Title Menu
			case Title_Options:
			{
				Menu::Title("Title Options");
				Menu::Toggle("Title Rainbow", Menu::Rainbowmenu_titleBool);
			}
			break;
#pragma endregion Settings Scroller Menu end

#pragma region Settings Toogle Menu
			case ToggleOptions:
			{
				Menu::Title("On/Off Toggle");
				Menu::Toggle("Toggle Rainbow", Menu::Toggle_RainbowBool);
				if (Menu::Option("~g~ON ~w~/ ~r~OFF ~w~switch")) { if (Menu::YesNoSwitch) { Menu::YesNoSwitch = false; } if (Menu::IconSwitch) { Menu::IconSwitch = false; } if (Menu::plopSwitch) { Menu::plopSwitch = false; }  Menu::OnOffSwitch = true; notify_Original((char*)"~g~ON ~w~/ ~r~OFF ~gold~Switches ~w~: ~g~Activated"); }
				if (Menu::Option("~g~YES ~w~/ ~r~NO ~w~switch")) { if (Menu::OnOffSwitch) { Menu::OnOffSwitch = false; } if (Menu::IconSwitch) { Menu::IconSwitch = false; } if (Menu::plopSwitch) { Menu::plopSwitch = false; }  Menu::YesNoSwitch = true; notify_Original((char*)"~g~YES ~w~/ ~r~NO ~gold~Switches ~w~: ~g~Activated"); }
				if (Menu::Option("~b~Icon ~w~switch")) { if (Menu::OnOffSwitch) { Menu::OnOffSwitch = false; } if (Menu::YesNoSwitch) { Menu::YesNoSwitch = false; } if (Menu::plopSwitch) { Menu::plopSwitch = false; }  Menu::IconSwitch = true; notify_Original((char*)"~b~ICON ~gold~Switches ~w~: ~g~Activated"); }
				if (Menu::Option("~b~Plop Icon ~w~switch")) { if (Menu::OnOffSwitch) { Menu::OnOffSwitch = false; } if (Menu::YesNoSwitch) { Menu::YesNoSwitch = false; } if (Menu::IconSwitch) { Menu::IconSwitch = false; }  Menu::plopSwitch = true;  notify_Original((char*)"~b~Plop  ~gold~Switches ~w~: ~g~Activated"); }
			}
			break;
#pragma endregion Settings Toogle Menu end

#pragma region Settings Scroller Menu
			case Scroller_Options:
			{
				Menu::Title("Scroller Options");
				Menu::Toggle("Anime scroller", Menu::Settings::Animescroll);
				Menu::Toggle("Scroller Rainbow", Menu::Scrollbar_Rainbow);
				if (Menu::Option("Green")) { Menu::Settings::scroller.r = 0, Menu::Settings::scroller.g = 255, Menu::Settings::scroller.b = 0; }
			}
			break;
#pragma endregion Settings Scroller Menu end
			}
			Menu::End();
			WAIT(0);
		}
	}

	void ScriptMain() {
		srand(GetTickCount());
		main();
	}
}
