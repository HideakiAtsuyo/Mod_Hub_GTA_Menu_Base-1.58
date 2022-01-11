#pragma once
namespace Mod_Hub_Base
{
	extern bool Godmode;
	extern bool Invisible;


	void Function_update_Loop();



	//=================
	// PED FUNCTIONS
	//=================

	Ped ClonePed(Ped ped);
	Ped CreatePed(char* PedName, Vector3 SpawnCoordinates, int ped_type, bool network_handle);

	//Animations
	void LoadAnim(char* dict);
	void playAnimation(Ped ped, bool loop, char* dict, char* anim);

	//SKINS
	bool applyChosenSkin(std::string skinName);

	//CONTROL
	void RequestControlOfEnt(Entity entity);

	//FORCE
	void ApplyForceToEntity(Entity e, float x, float y, float z);

	//CALM PEDS
	void set_all_nearby_peds_to_calm();

	//NEARBY PEDS
	std::set<Ped> getNearbyPeds();
	void update_nearby_peds(Ped playerPed, int count);

	//VEHICLE
	bool get_vehicle_keyboard_result(uint* outModel);

	//little one-line function called '$' to convert $TRING into a hash-key:
	Hash $(std::string str);

	//Converts Radians to Degrees
	float degToRad(float degs);

	//quick function to get-coords-of-entity:
	Vector3 coordsOf(Entity entity);

	//quick function to get distance between 2 points:
	float distanceBetween(Vector3 A, Vector3 B);

	//quick "get random int in range 0-x" function:
	int rndInt(int start, int end);

	//KEYBOARD
	std::string show_keyboard(char* title_id, char* prepopulated_text);

	//VECTOR/FLOAT
	Vector3 rot_to_direction(Vector3* rot);
	Vector3 add(Vector3* vectorA, Vector3* vectorB);
	Vector3 multiply(Vector3* vector, float x);
	float get_distance(Vector3* pointA, Vector3* pointB);
	float get_vector_length(Vector3* vector);

	//NOTIFICATION
	void notifyBottom(char* fmt, ...);
	void notifyBottom(std::string str);
	void notifyMap(char* fmt, ...);
	void notifyMap(std::string str);
	void notifyCenter(char* fmt, ...);
	void notifyCenter(std::string str);
	void update_status_text();
	void notifyleft(char* msg);
	void notify_Custom(char* Head_txt, char* fmt, ...);
	void notify_Original(char* fmt, ...);
	void notify_Red(char* fmt, ...);
	void notify_Green(char* fmt, ...);

	// Header
	extern bool HeaderImage;
	char* Add_Strings(char* string1, char* string2);
	std::string Documents_Patha();

	//DRAWING FUNCTIONS
	void draw_rect(float A_0, float A_1, float A_2, float A_3, int A_4, int A_5, int A_6, int A_7);
	void draw_menu_line(std::string caption, float lineWidth, float lineHeight, float lineTop, float lineLeft, float textLeft, bool active, bool title, bool rescaleText = true);
}