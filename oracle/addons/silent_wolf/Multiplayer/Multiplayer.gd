extends Node

onready var WSClient = Node.new()

var mp_ws_ready = false
var mp_session_started = false

var mp_player_name = ""


func _ready():
	mp_ws_ready = false
	mp_session_started = false
	var ws_client_script = load("res://addons/silent_wolf/Multiplayer/ws/WSClient.gd")
	WSClient.set_script(ws_client_script)
	add_child(WSClient)


func init_mp_session(player_name):
	
	WSClient.init_mp_session(player_name)
	
	
	


func _send_init_message():
	WSClient.init_mp_session(mp_player_name)
	mp_ws_ready = true
	mp_session_started = true


func send(data: Dictionary):
	
	print("Attempting to send data to web socket server")
	if WSClient.is_inside_tree():
		
		print("Sending data to web socket server...")
		WSClient.send_to_server("update", data)
