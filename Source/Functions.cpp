#include "stdafx.h"
namespace Mod_Hub_Base
{
	// here is some diffrent toggle bool options
	bool Godmode = false;
	void godmode()
	{//-----------------------get plyer ped id; this bool Godmode is Controling is to true and false 
		ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), Godmode);
	}

	bool Invisible = false;
	void invisible(bool toggle)
	{
		if (toggle/*when this toggle is getting verifiyed by a real bool its gonna work*/)
		{
			ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), false, 0);
		}
		else
		{
			ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), true, 0);
		}
	}

	// here you take all your void´s that you want update loop on :)
	void Function_update_Loop()
	{
		godmode();
		invisible(/*now is that bool toggle verified bt bool Invisible so this bool have now controll over invisible(bool toggle)*/Invisible);
	}



	std::set<Ped> lastSeenPeds;

	//=================
	// PED FUNCTIONS
	//=================

	Ped ClonePed(Ped ped)
	{
		if (ENTITY::DOES_ENTITY_EXIST(ped) && !ENTITY::IS_ENTITY_DEAD(ped))
		{
			return PED::CLONE_PED(ped, ENTITY::GET_ENTITY_HEADING(ped), 1, 1);
		}

		return 0;
	}

	Ped CreatePed(char* PedName, Vector3 SpawnCoordinates, int ped_type, bool network_handle)
	{
		Ped NewPed;
		int PedHash = GAMEPLAY::GET_HASH_KEY(PedName);
		if (STREAMING::IS_MODEL_IN_CDIMAGE(PedHash))
		{
			if (STREAMING::IS_MODEL_VALID(PedHash))
			{
				STREAMING::REQUEST_MODEL(PedHash);
				while (!STREAMING::HAS_MODEL_LOADED(PedHash)) WAIT(0);

				NewPed = PED::CREATE_PED(ped_type, PedHash, SpawnCoordinates.x, SpawnCoordinates.y, SpawnCoordinates.z, 0, network_handle, 1);
				STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(PedHash);
				return NewPed;
			}
		}

		return -1;
	}

	//Animations
	void LoadAnim(char* dict)
	{
		int tick = 0;
		STREAMING::REQUEST_ANIM_DICT(dict);
		while (tick < 100 && !STREAMING::HAS_ANIM_DICT_LOADED(dict))
		{
			tick++;
			WAIT(0);
		}
	}

	void playAnimation(Ped ped, bool loop, char* dict, char* anim)
	{
		LoadAnim(dict);
		int a = -1;
		int b = 1;

		if (!loop)
		{
			a = 1;
			b = 0;
		}

		AI::TASK_PLAY_ANIM(ped, dict, anim, 10000.0f, -1.5f, a, b, 0.445f, false, false, false);

	}

	//Skins
	bool applyChosenSkin(DWORD model)
	{
		if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_VALID(model))
		{
			STREAMING::REQUEST_MODEL(model);
			while (!STREAMING::HAS_MODEL_LOADED(model))
			{
				WAIT(0);
			}

			Vehicle veh = NULL;
			if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), 0))
			{
				veh = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
			}

			PLAYER::SET_PLAYER_MODEL(PLAYER::PLAYER_ID(), model);
			//PED::SET_PED_RANDOM_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID(), FALSE);
			PED::SET_PED_DEFAULT_COMPONENT_VARIATION(PLAYER::PLAYER_PED_ID());
			WAIT(0);

			if (veh != NULL)
			{
				PED::SET_PED_INTO_VEHICLE(PLAYER::PLAYER_PED_ID(), veh, -1);
			}

			WAIT(100);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);

			return true;
		}
		return false;
	}

	bool applyChosenSkin(std::string skinName)
	{
		DWORD model = GAMEPLAY::GET_HASH_KEY((char*)skinName.c_str());
		return applyChosenSkin(model);
	}

	//CONTROL
	void RequestControlOfid(Entity netid)
	{
		int tick = 0;

		while (!NETWORK::NETWORK_HAS_CONTROL_OF_NETWORK_ID(netid) && tick <= 25)
		{
			NETWORK::NETWORK_REQUEST_CONTROL_OF_NETWORK_ID(netid);
			tick++;
		}
	}

	void RequestControlOfEnt(Entity entity)
	{
		int tick = 0;
		while (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(entity) && tick <= 25)
		{
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(entity);
			tick++;
		}
		if (NETWORK::NETWORK_IS_SESSION_STARTED())
		{
			int netID = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(entity);
			RequestControlOfid(netID);
			NETWORK::SET_NETWORK_ID_CAN_MIGRATE(netID, 1);
		}
	}

	//FORCE
	void ApplyForceToEntity(Entity e, float x, float y, float z)
	{
		if (e != PLAYER::PLAYER_PED_ID() && NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(e) == FALSE)
		{
			RequestControlOfEnt(e);
		}

		ENTITY::APPLY_FORCE_TO_ENTITY(e, 1, x, y, z, 0, 0, 0, 0, 1, 1, 1, 0, 1);

	}

	//NEARBY PEDS
	std::set<Ped> getNearbyPeds()
	{
		return lastSeenPeds;
	}

	void update_nearby_peds(Ped playerPed, int count)
	{
		const int numElements = count;
		const int arrSize = numElements * 2 + 2;

		Ped* peds = new Ped[arrSize];
		peds[0] = numElements;
		int found = PED::GET_PED_NEARBY_PEDS(playerPed, peds, -1);

		for (int i = 0; i < found; i++)
		{
			int offsettedID = i * 2 + 2;

			if (!ENTITY::DOES_ENTITY_EXIST(peds[offsettedID]))
			{
				continue;
			}

			Ped xped = peds[offsettedID];

			bool inSet = lastSeenPeds.find(xped) != lastSeenPeds.end();
			if (!inSet)
			{
				lastSeenPeds.insert(xped);
			}
		}

		std::set<Ped>::iterator it;
		for (it = lastSeenPeds.begin(); it != lastSeenPeds.end();)
		{
			if (!ENTITY::DOES_ENTITY_EXIST(*it))
			{
				lastSeenPeds.erase(it++);
			}
			else
			{
				++it;
			}
		}

		delete peds;
	}

	//CALM PEDS
	void set_all_nearby_peds_to_calm()
	{
		for each (Ped xped in lastSeenPeds)
		{
			PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(xped, true);
			PED::SET_PED_FLEE_ATTRIBUTES(xped, 0, 0);
			PED::SET_PED_COMBAT_ATTRIBUTES(xped, 17, 1);
		}
	}

	//Converts Radians to Degrees
	float degToRad(float degs)
	{
		return degs * 3.141592653589793f / 180.f;
	}

	//little one-line function called '$' to convert $TRING into a hash-key:
	Hash $(std::string str) {
		return GAMEPLAY::GET_HASH_KEY(&str[0u]);
	}

	// quick function to get - coords - of - entity:
	Vector3 coordsOf(Entity entity) {
		return ENTITY::GET_ENTITY_COORDS(entity, 1);
	}

	//quick function to get distance between 2 points: eg - if (distanceBetween(coordsOf(player), targetCoords) < 50)
	float distanceBetween(Vector3 A, Vector3 B) {
		return GAMEPLAY::GET_DISTANCE_BETWEEN_COORDS(A.x, A.y, A.z, B.x, B.y, B.z, 1);
	}

	//quick "get random int in range 0-x" function:
	int rndInt(int start, int end) {
		return GAMEPLAY::GET_RANDOM_INT_IN_RANGE(start, end);
	}

	//In Game KEYBOARD
	std::string show_keyboard(char* title_id, char* prepopulated_text)
	{
		DWORD time = GetTickCount() + 400;
		while (GetTickCount() < time)
		{
			WAIT(0);
		}

		GAMEPLAY::DISPLAY_ONSCREEN_KEYBOARD(true, (title_id == NULL ? "HUD_TITLE" : title_id), "", (prepopulated_text == NULL ? "" : prepopulated_text), "", "", "", 64);

		while (GAMEPLAY::UPDATE_ONSCREEN_KEYBOARD() == 0)
		{
			WAIT(0);
		}

		std::stringstream ss;
		if (!GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT())
		{
			return std::string("");
		}
		else
		{
			return std::string(GAMEPLAY::GET_ONSCREEN_KEYBOARD_RESULT());
		}
	}

	//VEHICLE
	static std::string lastvehmodel("");
	bool get_vehicle_keyboard_result(uint* outModel)
	{
		std::string result = show_keyboard("FMMC_KEY_TIP", &lastvehmodel[0]);
		if (!result.empty())
		{
			uint model = $(result);
			if (!STREAMING::IS_MODEL_IN_CDIMAGE(model) || !STREAMING::IS_MODEL_A_VEHICLE(model))
			{
				lastvehmodel = "";
				//notifyBottom("~HUD_COLOUR_RED~Not A Valid Model!");
				return false;
			}

			else
			{
				STREAMING::REQUEST_MODEL(model);
				DWORD now = GetTickCount();
				while (!STREAMING::HAS_MODEL_LOADED(model) && GetTickCount() < now + 5000)
				{
					WAIT(0);
				}

				if (!STREAMING::HAS_MODEL_LOADED(model))
				{
					lastvehmodel = "";
					std::ostringstream ss2;
					ss2 << "~HUD_COLOUR_RED~ Timed out requesting  " << result << " : 0x" << model;
					//				notifyBottom(ss2.str());
					return false;
				}

				lastvehmodel = result;
				*outModel = model;
				return true;
			}

		}

		return false;
	}

	//VECTOR AND FLOAT FUNCTIONS
	Vector3 rot_to_direction(Vector3* rot) {
		float radiansZ = rot->z * 0.0174532924f;
		float radiansX = rot->x * 0.0174532924f;
		float num = abs((float)cos((double)radiansX));
		Vector3 dir;
		dir.x = (float)((double)((float)(-(float)sin((double)radiansZ))) * (double)num);
		dir.y = (float)((double)((float)cos((double)radiansZ)) * (double)num);
		dir.z = (float)sin((double)radiansX);
		return dir;
	}

	Vector3 add(Vector3* vectorA, Vector3* vectorB) {
		Vector3 result;
		result.x = vectorA->x;
		result.y = vectorA->y;
		result.z = vectorA->z;
		result.x += vectorB->x;
		result.y += vectorB->y;
		result.z += vectorB->z;
		return result;
	}

	Vector3 multiply(Vector3* vector, float x) {
		Vector3 result;
		result.x = vector->x;
		result.y = vector->y;
		result.z = vector->z;
		result.x *= x;
		result.y *= x;
		result.z *= x;
		return result;
	}

	float get_distance(Vector3* pointA, Vector3* pointB) {
		float a_x = pointA->x;
		float a_y = pointA->y;
		float a_z = pointA->z;
		float b_x = pointB->x;
		float b_y = pointB->y;
		float b_z = pointB->z;
		double x_ba = (double)(b_x - a_x);
		double y_ba = (double)(b_y - a_y);
		double z_ba = (double)(b_z - a_z);
		double y_2 = y_ba * y_ba;
		double x_2 = x_ba * x_ba;
		double sum_2 = y_2 + x_2;
		return(float)sqrt(sum_2 + z_ba);
	}

	float get_vector_length(Vector3* vector) {
		double x = (double)vector->x;
		double y = (double)vector->y;
		double z = (double)vector->z;
		return(float)sqrt(x * x + y * y + z * z);
	}

	//NOTIFICATIONS
	/*
	Colours:
	~r~ = Red
	~b~ = Blue
	~g~ = Green
	~y~ = Yellow
	~p~ = Purple
	~o~ = Orange
	~c~ = Grey
	~m~ = Dark Grey
	~u~ = Black
	~n~ = Skip Line
	~s~ = White
	~d~ = dark blue
	~f~ = light blue
	~l~ = black
	~t~ = gray
	~v~ = black

	Fonts:
	~italic~ = italic font
	~bold~ = bold font
	*/


	// 1 WHITE
	// 2 
	// 5 Grey
	// 6 Red
	// 7 lös röd
	// 8 dark red

	void notify_Custom(char* Head_txt, char* fmt, ...)
	{
		char buf[2048] = { 0 };
		va_list va_alist;

		va_start(va_alist, fmt);
		vsprintf_s(buf, fmt, va_alist);
		va_end(va_alist);
		//
		char buff2[2048] = { 0 };
		sprintf_s(buff2, "%s", buf);

		UI::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
		UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(fmt);
		UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2("MH_BAse_.ytd", "Mod_Hub_Logo_Icon", false, 1, "Mod Hub", Head_txt, 1, "", 9, 0); //  can create a custom ytd icon
		UI::END_TEXT_COMMAND_THEFEED_POST_TICKER(8000, 0);


		//UI::_SET_NOTIFICATION_MESSAGE("Mod_Hub_Logo_Icon", "Mod_Hub_Logo_Icon", 1, 9, 1, Head_txt, fmt);
	/*	UI::_SET_NOTIFICATION_MESSAGE_CLAN_TAG_2("Mod_Hub_Logo_Icon", "Mod_Hub_Logo_Icon", 1, 8, Mod_Menu_Base_Name, Head_txt, 1, "Best Menu", 9, 0);
		UI::END_TEXT_COMMAND_THEFEED_POST_TICKER(FALSE, FALSE);*/

	} void notify_Report(std::string str1, std::string str) { notify_Report(&str1[0], &str[0]); }

	void notify_Original(char* fmt, ...)
	{
		char buf[2048] = { 0 };
		va_list va_alist;

		va_start(va_alist, fmt);
		vsprintf_s(buf, fmt, va_alist);
		va_end(va_alist);
		//
		char buff2[2048] = { 0 };
		sprintf_s(buff2, "%s", buf);

		UI::_SET_NOTIFICATION_BACKGROUND_COLOR(5);
		UI::_SET_NOTIFICATION_FLASH_COLOR(255, 255, 255, 255);
		UI::BEGIN_TEXT_COMMAND_THEFEED_POST((char*)"STRING");
		UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(buff2);
		UI::END_TEXT_COMMAND_THEFEED_POST_TICKER(1, 1);
	} void notify_Original(std::string str) { notify_Original(&str[0]); }

	void notify_Red(char* fmt, ...)
	{
		char buf[2048] = { 0 };
		va_list va_alist;

		va_start(va_alist, fmt);
		vsprintf_s(buf, fmt, va_alist);
		va_end(va_alist);
		//
		char buff2[2048] = { 0 };
		sprintf_s(buff2, "%s", buf);

		UI::_SET_NOTIFICATION_BACKGROUND_COLOR(5);
		UI::_SET_NOTIFICATION_FLASH_COLOR(255, 0, 0, 255);
		UI::BEGIN_TEXT_COMMAND_THEFEED_POST((char*)"STRING");
		UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(buff2);
		UI::END_TEXT_COMMAND_THEFEED_POST_TICKER(1, 1);
	} void notify_Red(std::string str) { notify_Red(&str[0]); }

	void notify_Green(char* fmt, ...)
	{
		char buf[2048] = { 0 };
		va_list va_alist;

		va_start(va_alist, fmt);
		vsprintf_s(buf, fmt, va_alist);
		va_end(va_alist);
		//
		char buff2[2048] = { 0 };
		sprintf_s(buff2, "%s", buf);

		UI::_SET_NOTIFICATION_BACKGROUND_COLOR(5);
		UI::_SET_NOTIFICATION_FLASH_COLOR(0, 255, 0, 255);
		UI::BEGIN_TEXT_COMMAND_THEFEED_POST((char*)"STRING");
		UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(buff2);
		UI::END_TEXT_COMMAND_THEFEED_POST_TICKER(1, 1);
	} void notify_Green(std::string str) { notify_Green(&str[0]); }

	char status_text[2048] = { 0 };
	void update_status_text()
	{
		if (GetTickCount() < 2500)
		{
			UI::SET_TEXT_FONT(0);
			UI::SET_TEXT_SCALE(0.55f, 0.55f);
			UI::SET_TEXT_COLOUR(255, 255, 255, 255);
			UI::SET_TEXT_WRAP(0.0f, 1.0f);
			UI::SET_TEXT_CENTRE(1);
			UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
			UI::SET_TEXT_EDGE(1, 0, 0, 0, 205);
			UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
			UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(status_text);
			UI::END_TEXT_COMMAND_DISPLAY_TEXT(0.5, 0.5);
		}
	}

	void notifyleft(char* msg)
	{
		UI::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
		UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(msg);
		UI::END_TEXT_COMMAND_THEFEED_POST_TICKER(2000, 1);
	}

	void notifyBottom(char* fmt, ...)
	{
		char buf[2048] = { 0 };
		va_list va_alist;

		va_start(va_alist, fmt);
		vsprintf_s(buf, fmt, va_alist);
		va_end(va_alist);

		char buff2[2048] = { 0 };
		sprintf_s(buff2, "%s", buf);

		UI::BEGIN_TEXT_COMMAND_PRINT("STRING");
		UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(buff2);
		UI::END_TEXT_COMMAND_PRINT(4000, 1);
	}	void notifyBottom(std::string str) { notifyBottom(&str[0]); }

	void notifyMap(char* fmt, ...)
	{
		char buf[2048] = { 0 };
		va_list va_alist;

		va_start(va_alist, fmt);
		vsprintf_s(buf, fmt, va_alist);
		va_end(va_alist);

		char buff2[2048] = { 0 };
		sprintf_s(buff2, "%s", buf);

		UI::SET_TEXT_OUTLINE();
		UI::BEGIN_TEXT_COMMAND_THEFEED_POST("STRING");
		UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(buff2);
		UI::END_TEXT_COMMAND_THEFEED_POST_TICKER(FALSE, FALSE);
	}	void notifyMap(std::string str) { notifyMap(&str[0]); }

	void notifyCenter(char* fmt, ...)
	{
		char buf[2048] = { 0 };
		va_list va_alist;

		va_start(va_alist, fmt);
		vsprintf_s(buf, fmt, va_alist);
		va_end(va_alist);

		sprintf_s(status_text, "%s", buf);
	}	void notifyCenter(std::string str) { notifyCenter(&str[0]); }

	//DRAWING FUNCTIONS
	void draw_rect(float A_0, float A_1, float A_2, float A_3, int A_4, int A_5, int A_6, int A_7)
	{
		GRAPHICS::DRAW_RECT((A_0 + (A_2 * 0.5f)), (A_1 + (A_3 * 0.5f)), A_2, A_3, A_4, A_5, A_6, A_7);
	}

	void draw_menu_line(std::string caption, float lineWidth, float lineHeight, float lineTop, float lineLeft, float textLeft, bool active, bool title, bool rescaleText)
	{
		// default values
		int text_col[4] = { 255, 255, 255, 255 },
			rect_col[4] = { 0, 0, 0, 80 };
		float text_scale = 0.30f;
		int font = 0;
		bool outline = true;
		bool dropshadow = true;

		// correcting values for active line
		if (active)
		{

			outline = false;
			dropshadow = true;
			text_col[0] = 0;
			text_col[1] = 0;
			text_col[2] = 0;
			text_col[3] = 255;

			rect_col[0] = 255;
			rect_col[1] = 255;
			rect_col[2] = 255;
			rect_col[3] = 80;

			if (rescaleText)text_scale = 0.30f;
		}

		if (title)
		{
			outline = true;
			dropshadow = true;
			text_col[0] = 255;
			text_col[1] = 255;
			text_col[2] = 255;
			text_col[3] = 255;

			rect_col[0] = 93;
			rect_col[1] = 182;
			rect_col[2] = 229;
			rect_col[2] = 255;

			if (rescaleText)text_scale = 0.36f;
			font = 0;
		}

		int screen_w, screen_h;
		GRAPHICS::GET_SCREEN_RESOLUTION(&screen_w, &screen_h);

		textLeft += lineLeft;

		float lineWidthScaled = lineWidth / (float)screen_w; // line width
		float lineTopScaled = lineTop / (float)screen_h; // line top offset
		float textLeftScaled = textLeft / (float)screen_w; // text left offset
		float lineHeightScaled = lineHeight / (float)screen_h; // line height

		float lineLeftScaled = lineLeft / (float)screen_w;

		// this is how it's done in original scripts

		// text upper part
		UI::SET_TEXT_FONT(font);
		UI::SET_TEXT_SCALE(0.0, text_scale);
		UI::SET_TEXT_COLOUR(text_col[0], text_col[1], text_col[2], text_col[3]);
		UI::SET_TEXT_CENTRE(0);
		if (outline)
		{
			UI::SET_TEXT_EDGE(1, 255, 215, 0, 255); //UI::SET_TEXT_OUTLINE();
		}

		if (dropshadow)
		{
			UI::SET_TEXT_DROPSHADOW(5, 0, 78, 255, 255);
		}
		UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
		UI::BEGIN_TEXT_COMMAND_DISPLAY_TEXT("STRING");
		UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME((LPSTR)caption.c_str());
		UI::END_TEXT_COMMAND_DISPLAY_TEXT(textLeftScaled, (((lineTopScaled + 0.00278f) + lineHeightScaled) - 0.005f));

		// text lower part
		UI::SET_TEXT_FONT(font);
		UI::SET_TEXT_SCALE(0.0, text_scale);
		UI::SET_TEXT_COLOUR(text_col[0], text_col[1], text_col[2], text_col[3]);
		UI::SET_TEXT_CENTRE(0);
		if (outline)
		{
			UI::SET_TEXT_EDGE(1, 255, 215, 0, 255); //UI::SET_TEXT_OUTLINE();
		}

		if (dropshadow)
		{
			UI::SET_TEXT_DROPSHADOW(5, 0, 78, 255, 255);
		}
		UI::SET_TEXT_EDGE(0, 0, 0, 0, 0);
		UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME((LPSTR)caption.c_str());
		int num25 = UI::_GET_TEXT_SCREEN_LINE_COUNT(textLeftScaled, (((lineTopScaled + 0.00278f) + lineHeightScaled) - 0.005f));

		// rect
		draw_rect(lineLeftScaled, lineTopScaled + (0.00278f),
			lineWidthScaled, ((((float)(num25)*UI::_GET_TEXT_SCALE_HEIGHT(text_scale, 0)) + (lineHeightScaled * 1.0f)) + 0.005f),
			rect_col[0], rect_col[1], rect_col[2], rect_col[3]);
	}

	// Good Header Options

	bool HeaderImage = 1;

	char str[69];
	char* Add_Strings(char* string1, char* string2)
	{
		memset(str, 0, sizeof(str));
		strcpy_s(str, "");
		strcpy_s(str, string1);
		strcat_s(str, string2);
		return str;
	}
	std::string Documents_Patha()
	{
		wchar_t Folder[1024];
		HRESULT hr = SHGetFolderPathW(nullptr, CSIDL_APPDATA, nullptr, 0, Folder);
		if (SUCCEEDED(hr))
		{
			char str[1024];
			wcstombs(str, Folder, 1023);
			return Add_Strings(str, (char*)_strdup(Menu_Path.c_str())); // this is your Folder where its going to fint your ytd file
		}
		return "";
	}
}