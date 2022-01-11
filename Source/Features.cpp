#include "stdafx.h"
//#include "utils.h"


/*Vector3 rot_to_direction(Vector3*rot) {
	float radiansZ = rot->z*0.0174532924f;
	float radiansX = rot->x*0.0174532924f;
	float num = abs((float)cos((double)radiansX));
	Vector3 dir;
	dir.x = (float)((double)((float)(-(float)sin((double)radiansZ)))*(double)num);
	dir.y = (float)((double)((float)cos((double)radiansZ))*(double)num);
	dir.z = (float)sin((double)radiansX);
	return dir;
}
Vector3 add(Vector3*vectorA, Vector3*vectorB) {
	Vector3 result;
	result.x = vectorA->x;
	result.y = vectorA->y;
	result.z = vectorA->z;
	result.x += vectorB->x;
	result.y += vectorB->y;
	result.z += vectorB->z;
	return result;
}
Vector3 multiply(Vector3*vector, float x) {
	Vector3 result;
	result.x = vector->x;
	result.y = vector->y;
	result.z = vector->z;
	result.x *= x;
	result.y *= x;
	result.z *= x;
	return result;
}
float get_distance(Vector3*pointA, Vector3*pointB) {
	float a_x = pointA->x;
	float a_y = pointA->y;
	float a_z = pointA->z;
	float b_x = pointB->x;
	float b_y = pointB->y;
	float b_z = pointB->z;
	double x_ba = (double)(b_x - a_x);
	double y_ba = (double)(b_y - a_y);
	double z_ba = (double)(b_z - a_z);
	double y_2 = y_ba*y_ba;
	double x_2 = x_ba*x_ba;
	double sum_2 = y_2 + x_2;
	return(float)sqrt(sum_2 + z_ba);
}
float get_vector_length(Vector3*vector) {
	double x = (double)vector->x;
	double y = (double)vector->y;
	double z = (double)vector->z;
	return(float)sqrt(x*x + y*y + z*z);
}
float Get3DDistance(Vector3 a, Vector3 b) {
	float x = pow((a.x - b.x), 2);
	float y = pow((a.y - b.y), 2);
	float z = pow((a.z - b.z), 2);
	return sqrt(x + y + z);
}
Vector3 addVector(Vector3 vector, Vector3 vector2) {
	vector.x += vector2.x;
	vector.y += vector2.y;
	vector.z += vector2.z;
	vector._paddingx += vector2._paddingx;
	vector._paddingy += vector2._paddingy;
	vector._paddingz += vector2._paddingz;
	return vector;
}
Vector3 multiplyVector(Vector3 vector, float inc) {
	vector.x *= inc;
	vector.y *= inc;
	vector.z *= inc;
	vector._paddingx *= inc;
	vector._paddingy *= inc;
	vector._paddingz *= inc;
	return vector;
}
double DegreeToRadian(double n) {
	return n * 0.017453292519943295;
}
Vector3 RotationToDirection(Vector3 rot) {
	double num = DegreeToRadian(rot.z);
	double num2 = DegreeToRadian(rot.x);
	double val = cos(num2);
	double num3 = abs(val);
	rot.x = (float)(-(float)sin(num) * num3);
	rot.y = (float)(cos(num) * num3);
	rot.z = (float)sin(num2);
	return rot;

}*/
       //             TUTOIAL HOW TO ADD a TOGGLE 1. go to Features.h ----> and define the name of the bool there (for example : extern bool examplebool;
         //                                                                                                                      void example(bool toggle);
       //             2. Go to Features.cpp ------> and write for example: bool Features::examplebool = false; or true; (depends on what you want. Normal is [false])
       //                                                                 void Features::example(bool toggle) { 
     //                                                                     The feature.............
    //                                                                      }
//                     (3). When you want to loop the bool write it in "UpdateLoop()" Example : examplebool ? example(true) : NULL;
void Features::UpdateLoop()
{
	Godmode ? godmode(true) : NULL;

	Ghostmode ? ghostmode(true) : NULL;

	Superjump ? superjump(true) : NULL;

	Neverwanted ? neverwanted(true) : NULL;

	rainbowmenu ? Rainbowmenu(true) : NULL;

	// examplebool ? example(true) : NULL;

}
/*bool Features::examplebool = false;
void Features::example(bool toggle)
{
	Your Feature.......
}*/
bool Features::Godmode = false;
void Features::godmode(bool toggle) {
	if (toggle == true)
	{
		
	}
	else
	{
		
	}
}
bool Features::Ghostmode = false;
void Features::ghostmode(bool toggle)
{
	if (toggle == true)
	{
		ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), false, 0);
	}
	else
	{
		ENTITY::SET_ENTITY_VISIBLE(PLAYER::PLAYER_PED_ID(), true, 0);
	}
}
bool Features::Superjump = false;
void Features::superjump(bool toggle)
{
	Player playerPed = PLAYER::PLAYER_PED_ID();
	GAMEPLAY::SET_SUPER_JUMP_THIS_FRAME(PLAYER::PLAYER_ID());
	GAMEPLAY::SET_SUPER_JUMP_THIS_FRAME(playerPed);
}
bool Features::Neverwanted = false;
void Features::neverwanted(bool toggle)
{
	 // The Memory Function for this Option changed so i used the Natives this Native is maybe detected i will show you how to make a option using the memory below : 
}
                                                                 // Memory::set_value<int>({ OFFSET_PLAYER, OFFSET_PLAYER_INFO, OFFSET_PLAYER_INFO_WANTED }, 0); That is a Memory Feature when you find the new hash for the never wanted offset change it in Structs.h!!
bool Features::rainbowmenu = false;
void Features::Rainbowmenu(bool toggle)
{
	if (Menu::Settings::titleRect.r > 0 && Menu::Settings::titleRect.b == 0, Menu::Settings::scroller.r > 0 && Menu::Settings::scroller.b == 0)
	{
		Menu::Settings::titleRect.r--;
		Menu::Settings::titleRect.g++;
		Menu::Settings::scroller.r--;
		Menu::Settings::scroller.g++;
	}
	if (Menu::Settings::titleRect.g > 0 && Menu::Settings::titleRect.r == 0, Menu::Settings::scroller.g > 0 && Menu::Settings::scroller.r == 0)
	{
		Menu::Settings::titleRect.g--;
		Menu::Settings::titleRect.b++;
		Menu::Settings::scroller.g--;
		Menu::Settings::scroller.b++;
	}
	if (Menu::Settings::titleRect.b > 0 && Menu::Settings::titleRect.g == 0, Menu::Settings::scroller.b > 0 && Menu::Settings::scroller.g == 0)
	{
		Menu::Settings::titleRect.r++;
		Menu::Settings::titleRect.b--;
		Menu::Settings::scroller.r++;
		Menu::Settings::scroller.b--;
	}
	(Menu::Settings::titleRect.r, Menu::Settings::titleRect.g, Menu::Settings::titleRect.b);
	(Menu::Settings::scroller.r, Menu::Settings::scroller.g, Menu::Settings::scroller.b);
}