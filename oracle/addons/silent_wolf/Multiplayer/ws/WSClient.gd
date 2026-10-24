extends Node

const SWLogger = preload("res://addons/silent_wolf/utils/SWLogger.gd")


export var websocket_url = "wss://ws.silentwolfmp.com/server"
export var ws_room_init_url = "wss://ws.silentwolfmp.com/init"

signal ws_client_ready


var _client = WebSocketClient.new()

func _ready():
	SWLogger.debug("Entering MPClient _ready function")
	
	_client.connect("connection_closed", self, "_closed")
	_client.connect("connection_error", self, "_closed")
	_client.connect("connection_established", self, "_connected")
	
	
	
	_client.connect("data_received", self, "_on_data")

	
	var err = _client.connect_to_url(websocket_url)
	if err != OK:
		
		print("Unable to connect to WS server")
		set_process(false)
	emit_signal("ws_client_ready")

func _closed(was_clean = false):
	
	
	SWLogger.debug("WS connection closed, clean: " + str(was_clean))
	set_process(false)

func _connected(proto = ""):
	
	
	
	print("Connected with protocol: ", proto)
	
	
	
	
	


func _on_data():
	
	
	
	
	print("Got data from WS server: ", _client.get_peer(1).get_packet().get_string_from_utf8())


func _process(delta):
	
	
	_client.poll()



func send_to_server(message_type, data):
	data["message_type"] = message_type
	print("Sending data to server: " + str(data))
	_client.get_peer(1).put_packet(str(JSON.print(data)).to_utf8())


func init_mp_session(player_name):
	print("WSClient init_mp_session, sending initialisation packet to server")
	var init_packet = {
		"player_name": player_name
	}
	return send_to_server("init", init_packet)
	

func create_room():
	pass
