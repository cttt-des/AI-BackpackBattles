tool
extends Resource
class_name ControllerSettings

enum Devices{
	LUNA, 
	OUYA, 
	PS3, 
	PS4, 
	PS5, 
	STADIA, 
	STEAM, 
	SWITCH, 
	JOYCON, 
	XBOX360, 
	XBOXONE, 
	XBOXSERIES, 
	STEAM_DECK
}



export (Devices) var joypad_fallback = Devices.XBOX360



export (float, 0.0, 1.0) var joypad_deadzone: = 0.5


export (bool) var allow_mouse_remap: = true



export (int, 0, 10000) var mouse_min_movement: = 200


export (String, DIR) var custom_asset_dir: = ""


export (Script) var custom_mapper: Script
