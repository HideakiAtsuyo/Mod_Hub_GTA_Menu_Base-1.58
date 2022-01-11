#ifdef __SC_VERSION__
#define ADDRESS_WORLD 0x2328EC8 //42
#define ADDRESS_WAYPOINT 0x1F7F400 //wtb a (mini)map struct
#define ADDRESS_OBJECTIVE 0x1F7F4B0
#define ADDRESS_AMMO 0x0F706C5 //Ammo dec code; 41 2B D1 E8; 90 90 90 E8
#define ADDRESS_MAGAZINE 0x0F70680 //Magazine dec code; 41 2B C9 3B C8 0F; 90 90 90 3B C8 0F
#endif
#ifdef __STEAM_VERSION__
#define ADDRESS_WORLD 0x232BC00
#define ADDRESS_WAYPOINT 0x1F82460
#define ADDRESS_OBJECTIVE 0x1F82510
#define ADDRESS_AMMO 0x0F71C38
#define ADDRESS_MAGAZINE 0x0F71C7D
#endif

//offset from WORLD
#define OFFSET_PLAYER 0x08 //playerbase

//entity offsets
#define OFFSET_ENTITY_POSBASE 0x30 //base of a structure that contains entity coords
#define OFFSET_ENTITY_POSBASE_POS 0x50 //vector3
#define OFFSET_ENTITY_POS 0x90 //vector3
#define OFFSET_ENTITY_HEALTH 0x280 //entity health (except for vehicles); float cur, float max
#define OFFSET_ENTITY_HEALTH_MAX 0x2A0 //they moved this away from curHealth in 1.36 :(
#define OFFSET_ENTITY_ATTACKER 0x2A8 //base to a list of the last 3 entities that attacked the current entity
#define OFFSET_ENTITY_GOD 0x189 //godmode; on = 1, off = 0; byte

//player (entity) offsets
#define OFFSET_PLAYER_MONEY 0x2640 //Money stuff
#define OFFSET_PLAYER_ARMOR 0x14B8 //armour
#define OFFSET_PLAYER_INFO 0x10C8 //0x10B8 old //playerInfo struct
#define OFFSET_PLAYER_INFO_WANTED_CAN_CHANGE 0x71C //fWantedCanChange
#define OFFSET_PLAYER_INFO_WANTED 0x868 //0x848 old one //wanted level; DWORD
#define OFFSET_PLAYER_INFO_RUN_SPD 0xCD0 //run speed; def 1; float
#define OFFSET_PLAYER_INFO_SWIM_SPD 0x150 //swim speed; def 1; float
#define OFFSET_PLAYER_INFO_FRAMEFLAGS 0x1F8 //0x190//frame flags; DWORD
#define OFFSET_PLAYER_INFO_STAMINA 0xC00 //fStamina, fStaminaMax
#define OFFSET_PLAYER_NAME 0x84 //0x7C old
#define OFFSET_PLAYER_RAGDOLL 0x10A8 //byte; CPed.noRagdoll: 0x20 = off; 0x00/0x01 = on
#define OFFSET_PLAYER_SEATBELT 0x13EC //0x140C //byte; CPed.seatBelt: 0xC8 = off; 0xC9 = on
#define OFFSET_PLAYER_INVEHICLE 0x146B

//vehicle offsets
#define OFFSET_PLAYER_VEHICLE 0xD28 //ptr to last used vehicle
#define OFFSET_VEHICLE_HEALTH 0x189 //vehicle health; 0.f-1000.f
#define OFFSET_VEHICLE_GRAVITY 0xB7C //if doesnt work change to 0x0B4C //fGravity
#define OFFSET_VEHICLE_BULLETPROOF_TIRES 0x883 //if doesnt work try //0x085B //btBulletproofTires; (btBulletproofTires & 0x20) ? true : false
#define OFFSET_VEHICLE_HANDLING 0x938 //0x918
#define OFFSET_VEHICLE_HANDLING_ACCELERATION 0x4C
#define OFFSET_VEHICLE_HANDLING_BRAKEFORCE 0x6C
#define OFFSET_VEHICLE_HANDLING_TRACTION_CURVE_MIN 0xB8 //0x90 //fTractionCurveMin
#define OFFSET_VEHICLE_HANDLING_DEFORM_MULTIPLIER 0xF8 //fDeformationDamageMult
#define OFFSET_VEHICLE_HANDLING_UPSHIFT 0x58
#define OFFSET_VEHICLE_HANDLING_SUSPENSION_FORCE 0xBC //fSuspensionForce
#define OFFSET_VEHICLE_HEADLIGHT_COLOR 0x406 // from 0 to 12


//weapon offsetsOFFSET_WEAPON_CURRENT
#define OFFSET_WEAPON_BODY_ARMOR 0x14E0 // use like this m8 : { 0x08, 0x14E0 }
#define OFFSET_WEAPON_MANAGER 0x10D8 //from playerbase
#define OFFSET_WEAPON_CURRENT 0x20 //from weapon manager
#define OFFSET_WEAPON_AMMOINFO 0x48 //from weaponbase
#define OFFSET_WEAPON_AMMOINFO_MAX 0x28 //ammoinfo
#define OFFSET_WEAPON_AMMOINFO_CUR_1 0x08 //ptr lvl 1, ptr 1
#define OFFSET_WEAPON_AMMOINFO_CUR_2 0x00 //ptr tr lvl 2, ptr 1
#define OFFSET_WEAPON_AMMOINFO_CURAMMO 0x18 //offset to cur ammo
#define OFFSET_WEAPON_AMMOINFO_TYPE 0x0C //offset to projectile type?
#define OFFSET_WEAPON_SPREAD 0x70 //float set to 0
#define OFFSET_WEAPON_BULLET_DMG 0x98 //float times 10 (so when 0, it will stay 0)
#define OFFSET_WEAPON_RELOAD_MULTIPLIER 0x114 //float times 10
#define OFFSET_WEAPON_RECOIL 0x2A4 //float set to 0
#define OFFSET_WEAPON_MODEL_HASH 0x14
#define OFFSET_WEAPON_NAME_HASH 0x10
#define OFFSET_WEAPON_RELOAD_VEHICLE 0x110
#define OFFSET_WEAPON_RANGE 0x25C
#define OFFSET_WEAPON_SPINUP 0x124
#define OFFSET_WEAPON_SPIN 0x128
#define OFFSET_WEAPON_BULLET_BATCH 0x100 //dwBulletInBatch
#define OFFSET_WEAPON_MUZZLE_VELOCITY 0xFC //fMuzzleVelocity
#define OFFSET_WEAPON_BATCH_SPREAD 0x104 //fBatchSpread
#define OFFSET_ATTACKER_DISTANCE 0x18