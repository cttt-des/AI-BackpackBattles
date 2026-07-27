# Backpack Battles Bridge Script
# This script runs as an autoload inside the game process.
# It starts a TCP server on localhost that the external Python bot connects to.
# The bridge reads game state through Godot's API and executes commands.
#
# Protocol: JSON messages over TCP, newline-delimited.
# Request:  {"cmd": "command_name", "args": {...}}
# Response: {"ok": true, "data": {...}} or {"ok": false, "error": "message"}

extends Node

const PORT = 19527
const HOST = "127.0.0.1"

var server: TCP_Server
var clients: Array = []
var scan_cache: Dictionary = {}

func _ready():
	server = TCP_Server.new()
	var err = server.listen(PORT, HOST)
	if err != OK:
		print("[Bridge] Failed to start server on port %d: %d" % [PORT, err])
		return
	print("[Bridge] TCP server listening on %s:%d" % [HOST, PORT])
	set_process(true)

func _process(_delta):
	if server.is_connection_available():
		var client = server.take_connection()
		clients.append(client)
		print("[Bridge] Client connected: %s" % str(client.get_connected_address()))
		_send_json(client, {"type": "hello", "msg": "Backpack Battles Bridge v1.0"})

	for i in range(clients.size() - 1, -1, -1):
		var client = clients[i]
		if not client.is_connected_to_host():
			clients.remove(i)
			continue
		var available = client.get_available_bytes()
		if available > 0:
			var data = client.get_utf8_string(available)
			_handle_messages(client, data)

func _handle_messages(client, data):
	for line in data.split("\n", false):
		line = line.strip_edges()
		if line.empty():
			continue
		var parsed = JSON.parse(line)
		if parsed.error != OK:
			_send_json(client, {"ok": false, "error": "Invalid JSON"})
			continue
		var response = _handle_command(parsed.result)
		_send_json(client, response)

func _send_json(client, data):
	var text = JSON.print(data) + "\n"
	client.put_utf8_string(text)

# ─── Command Handler ───

func _handle_command(msg):
	var cmd = msg.get("cmd", "")
	var args = msg.get("args", {})
	
	match cmd:
		"ping":
			return {"ok": true, "data": {"pong": true}}
		
		"scan_tree":
			return {"ok": true, "data": _scan_tree()}
		
		"scan_autoloads":
			return {"ok": true, "data": _scan_autoloads()}
		
		"get_node_properties":
			return {"ok": true, "data": _get_node_properties(args.get("path", ""))}
		
		"get_node_methods":
			return {"ok": true, "data": _get_node_methods(args.get("path", ""))}
		
		"get_property":
			return {"ok": true, "data": _get_property(args.get("path", ""), args.get("property", ""))}
		
		"set_property":
			return {"ok": true, "data": _set_property(args.get("path", ""), args.get("property", ""), args.get("value"))}
		
		"call_method":
			return {"ok": true, "data": _call_method(args.get("path", ""), args.get("method", ""), args.get("args", []))}
		
		"get_game_state":
			return {"ok": true, "data": _get_game_state()}
		
		"get_shop_state":
			return {"ok": true, "data": _get_shop_state()}
		
		"get_inventory_state":
			return {"ok": true, "data": _get_inventory_state()}
		
		"get_player_state":
			return {"ok": true, "data": _get_player_state()}
		
		"simulate_click":
			return {"ok": true, "data": _simulate_click(args.get("x", 0), args.get("y", 0))}
		
		"simulate_drag":
			return {"ok": true, "data": _simulate_drag(args.get("from_x", 0), args.get("from_y", 0), args.get("to_x", 0), args.get("to_y", 0))}
		
		"simulate_key":
			return {"ok": true, "data": _simulate_key(args.get("key", ""), args.get("pressed", true))}
		
		"screenshot":
			return {"ok": true, "data": _take_screenshot()}
		
		"find_node":
			return {"ok": true, "data": _find_node_info(args.get("name", ""))}
		
		"get_children":
			return {"ok": true, "data": _get_children(args.get("path", ""))}
		
		# ─── BPB AI 增强：联动 + 价格读取 ───
		"get_item_details":
			return {"ok": true, "data": _get_item_details(args.get("zone", "all"))}
		"get_shop_offers":
			return {"ok": true, "data": _get_shop_offers()}
		"get_backpack_items_full":
			return {"ok": true, "data": _get_backpack_items_full()}
		"get_connector_data":
			return {"ok": true, "data": _get_connector_data(args.get("item_path", ""))}
		"get_item_price":
			return {"ok": true, "data": _get_item_price(args.get("item_path", ""))}
		"get_full_game_state":
			return {"ok": true, "data": _get_full_game_state()}
		
		_:
			return {"ok": false, "error": "Unknown command: " + cmd}

# ─── Tree Scanning ───

func _scan_tree():
	var root = get_tree().get_root()
	return _scan_node(root, "", 0, 5)

func _scan_node(node, path, depth, max_depth):
	var info = {
		"path": path if path else "/",
		"name": node.name,
		"type": node.get_class(),
		"visible": _is_visible(node),
		"script": _get_script_path(node),
		"children": []
	}
	
	if depth < max_depth:
		for child in node.get_children():
			var child_path = path + "/" + child.name
			info["children"].append(_scan_node(child, child_path, depth + 1, max_depth))
	
	return info

func _scan_autoloads():
	var result = {}
	var root = get_tree().get_root()
	for child in root.get_children():
		# Autoloads are direct children of root
		var info = {
			"name": child.name,
			"type": child.get_class(),
			"script": _get_script_path(child),
			"properties": _get_all_properties(child),
			"methods": _get_all_methods(child)
		}
		result[child.name] = info
	return result

# ─── Property & Method Access ───

func _get_node_properties(path):
	var node = _find_node_by_path(path)
	if not node:
		return {"error": "Node not found: " + path}
	return {"properties": _get_all_properties(node)}

func _get_node_methods(path):
	var node = _find_node_by_path(path)
	if not node:
		return {"error": "Node not found: " + path}
	return {"methods": _get_all_methods(node)}

func _get_property(path, property):
	var node = _find_node_by_path(path)
	if not node:
		return {"error": "Node not found: " + path}
	if not property in node:
		return {"error": "Property not found: " + property}
	var val = node.get(property)
	return {"value": _serialize_variant(val)}

func _set_property(path, property, value):
	var node = _find_node_by_path(path)
	if not node:
		return {"error": "Node not found: " + path}
	node.set(property, _deserialize_variant(value))
	return {"success": true}

func _call_method(path, method, args):
	var node = _find_node_by_path(path)
	if not node:
		return {"error": "Node not found: " + path}
	if not node.has_method(method):
		return {"error": "Method not found: " + method}
	
	var godot_args = []
	for a in args:
		godot_args.append(_deserialize_variant(a))
	
	var result = node.call(method, godot_args)
	return {"result": _serialize_variant(result)}

func _get_all_properties(node):
	var props = {}
	var list = node.get_property_list()
	for p in list:
		var name = p.name
		if name.begins_with("_") or name in ["script", "resource_local_to_scene"]:
			continue
		if p.usage & (PROPERTY_USAGE_STORAGE | PROPERTY_USAGE_EDITOR | PROPERTY_USAGE_DEFAULT):
			var val = null
			var err_msg = ""
			if name in node:
				val = _safe_get(node, name)
			if val != null or err_msg.empty():
				props[name] = val
	return props

func _safe_get(node, prop):
	var val = null
	match typeof(node.get(prop)):
		TYPE_OBJECT:
			val = _get_script_path(node.get(prop))
		TYPE_ARRAY:
			var arr = []
			for item in node.get(prop):
				arr.append(_serialize_variant(item))
			val = arr
		TYPE_VECTOR2:
			val = {"x": node.get(prop).x, "y": node.get(prop).y}
		TYPE_VECTOR3:
			val = {"x": node.get(prop).x, "y": node.get(prop).y, "z": node.get(prop).z}
		TYPE_COLOR:
			val = {"r": node.get(prop).r, "g": node.get(prop).g, "b": node.get(prop).b, "a": node.get(prop).a}
		TYPE_NODE_PATH:
			val = str(node.get(prop))
		TYPE_DICTIONARY:
			var dict = {}
			for key in node.get(prop):
				dict[str(key)] = _serialize_variant(node.get(prop)[key])
			val = dict
		_:
			val = node.get(prop)
	return val

func _get_all_methods(node):
	var methods = []
	for m in node.get_method_list():
		methods.append(m.name)
	return methods

# ─── Game State Reading ───

func _get_game_state():
	var state = {}
	
	# Access Game autoload singleton
	var game = get_node_or_null("/root/Game")
	if game:
		state["game"] = _get_all_properties(game)
		state["game_methods"] = _get_all_methods(game)
	
	# Access ItemBook autoload
	var item_book = get_node_or_null("/root/ItemBook")
	if item_book:
		state["item_book_methods"] = _get_all_methods(item_book)
	
	# Access RunDatabase
	var run_db = get_node_or_null("/root/RunDatabase")
	if run_db:
		state["run_database"] = _get_all_properties(run_db)
	
	return state

func _get_shop_state():
	var state = {}
	var root = get_tree().get_root()
	
	# Find Main node
	var main = root.get_node_or_null("Main")
	if not main:
		return {"error": "Main node not found"}
	
	# Find Shop node
	var shop = main.get_node_or_null("Shop")
	if shop:
		state["shop_visible"] = shop.visible
		state["shop_properties"] = _get_all_properties(shop)
		state["shop_methods"] = _get_all_methods(shop)
		
		# Get shop offers
		var offers = []
		for i in range(1, 6):
			var offer = shop.get_node_or_null("ShopOffer" + str(i))
			if offer:
				offers.append({
					"name": offer.name,
					"visible": offer.visible,
					"properties": _get_all_properties(offer),
					"methods": _get_all_methods(offer)
				})
		state["offers"] = offers
		
		# Get reroll button
		var reroll = shop.get_node_or_null("Reroll")
		if reroll:
			state["reroll"] = {
				"visible": reroll.visible,
				"properties": _get_all_properties(reroll)
			}
		
		# Get start combat button
		var start_btn = shop.get_node_or_null("StartCombatButton")
		if start_btn:
			state["start_combat_button"] = {
				"visible": start_btn.visible,
				"disabled": start_btn.disabled if "disabled" in start_btn else false,
				"properties": _get_all_properties(start_btn)
			}
		
		# Get storage box
		var storage = shop.get_node_or_null("Storagebox")
		if storage:
			state["storage"] = {
				"visible": storage.visible,
				"properties": _get_all_properties(storage)
			}
		
		# Get sellbox
		var sellbox = shop.get_node_or_null("Sellbox")
		if sellbox:
			state["sellbox"] = {
				"visible": sellbox.visible,
				"properties": _get_all_properties(sellbox)
			}
		
		# Get items (YSort)
		var items = shop.get_node_or_null("Items")
		if items:
			var item_list = []
			for child in items.get_children():
				item_list.append({
					"name": child.name,
					"type": child.get_class(),
					"position": {"x": child.position.x, "y": child.position.y},
					"script": _get_script_path(child),
					"properties": _get_all_properties(child)
				})
			state["items"] = item_list
		
		# Get grid storage
		var grid_storage = shop.get_node_or_null("GridStorage")
		if grid_storage:
			state["grid_storage"] = {
				"visible": grid_storage.visible,
				"properties": _get_all_properties(grid_storage)
			}
	
	return state

func _get_inventory_state():
	var state = {}
	var root = get_tree().get_root()
	var main = root.get_node_or_null("Main")
	if not main:
		return {"error": "Main node not found"}
	
	# Find Player node
	var player = main.get_node_or_null("Player")
	if player:
		state["player"] = {
			"properties": _get_all_properties(player),
			"methods": _get_all_methods(player)
		}
		
		# Look for inventory/backpack in player's children
		for child in player.get_children():
			if "inventory" in child.name.to_lower() or "backpack" in child.name.to_lower():
				state[child.name] = _get_all_properties(child)
	
	# Also check Game autoload for inventory
	var game = get_node_or_null("/root/Game")
	if game:
		# Try to find inventory-related properties
		for prop in game.get_property_list():
			if "inventory" in prop.name.to_lower() or "backpack" in prop.name.to_lower():
				state["game_" + prop.name] = _serialize_variant(_safe_get(game, prop.name))
	
	return state

func _get_player_state():
	var state = {}
	var root = get_tree().get_root()
	var main = root.get_node_or_null("Main")
	if not main:
		return {"error": "Main node not found"}
	
	var player = main.get_node_or_null("Player")
	if not player:
		return {"error": "Player node not found"}
	
	state["properties"] = _get_all_properties(player)
	state["methods"] = _get_all_methods(player)
	
	# Check ShopUI for displayed stats
	var shop_ui = player.get_node_or_null("ShopUI")
	if shop_ui:
		var ui_state = {}
		# Gold counter
		var gold = shop_ui.get_node_or_null("Gold")
		if gold:
			ui_state["gold"] = _get_all_properties(gold)
		# Health
		var health = shop_ui.get_node_or_null("Health")
		if health:
			ui_state["health"] = _get_all_properties(health)
		# Round counter
		var ingame = shop_ui.get_node_or_null("Ingame")
		if ingame:
			var round_node = ingame.get_node_or_null("Round")
			if round_node:
				var round_label = round_node.get_node_or_null("Label")
				if round_label and "text" in round_label:
					ui_state["round"] = round_label.text
			var wins_node = ingame.get_node_or_null("Wins")
			if wins_node:
				var wins_label = wins_node.get_node_or_null("Label")
				if wins_label and "text" in wins_label:
					ui_state["wins"] = wins_label.text
			var tries_node = ingame.get_node_or_null("Tries")
			if tries_node:
				var tries_label = tries_node.get_node_or_null("Label")
				if tries_label and "text" in tries_label:
					ui_state["tries"] = tries_label.text
		state["ui"] = ui_state
	
	return state

# ─── Input Simulation ───

func _simulate_click(x, y):
	var ev = InputEventMouseButton.new()
	ev.position = Vector2(x, y)
	ev.button_index = BUTTON_LEFT
	ev.pressed = true
	Input.parse_input_event(ev)
	yield(get_tree().create_timer(0.05), "timeout")
	ev.pressed = false
	Input.parse_input_event(ev)
	return {"success": true, "x": x, "y": y}

func _simulate_drag(from_x, from_y, to_x, to_y):
	# Press
	var ev = InputEventMouseButton.new()
	ev.position = Vector2(from_x, from_y)
	ev.button_index = BUTTON_LEFT
	ev.pressed = true
	Input.parse_input_event(ev)
	
	# Move
	yield(get_tree().create_timer(0.05), "timeout")
	var move_ev = InputEventMouseMotion.new()
	move_ev.position = Vector2(to_x, to_y)
	move_ev.relative = Vector2(to_x - from_x, to_y - from_y)
	Input.parse_input_event(move_ev)
	
	# Release
	yield(get_tree().create_timer(0.05), "timeout")
	ev.position = Vector2(to_x, to_y)
	ev.pressed = false
	Input.parse_input_event(ev)
	
	return {"success": true, "from": {"x": from_x, "y": from_y}, "to": {"x": to_x, "y": to_y}}

func _simulate_key(key_str, pressed):
	var ev = InputEventKey.new()
	ev.scancode = OS.find_scancode_from_string(key_str)
	ev.pressed = pressed
	Input.parse_input_event(ev)
	return {"success": true, "key": key_str, "pressed": pressed}

# ─── Screenshot ───

func _take_screenshot():
	var img = get_viewport().get_texture().get_data()
	img.flip_y()
	var bytes = img.save_png_to_buffer()
	# Encode as base64
	var base64 = Marshalls.raw_to_base64(bytes)
	return {"width": img.get_width(), "height": img.get_height(), "format": "png", "base64_size": bytes.size()}

# ─── Node Finding ───

func _find_node_by_path(path):
	if path.begins_with("/root/"):
		return get_node_or_null(path)
	
	var root = get_tree().get_root()
	if path.begins_with("/"):
		return root.get_node_or_null(path.substr(1))
	
	# Try to find by name
	return root.get_node_or_null(path)

func _find_node_info(name):
	var root = get_tree().get_root()
	var results = []
	_find_nodes_recursive(root, name, "", results)
	return {"matches": results}

func _find_nodes_recursive(node, target_name, current_path, results):
	if node.name == target_name:
		results.append({
			"path": current_path + "/" + node.name,
			"type": node.get_class(),
			"script": _get_script_path(node),
			"visible": _is_visible(node)
		})
	for child in node.get_children():
		_find_nodes_recursive(child, target_name, current_path + "/" + node.name, results)

func _get_children(path):
	var node = _find_node_by_path(path)
	if not node:
		return {"error": "Node not found: " + path}
	var children = []
	for child in node.get_children():
		children.append({
			"name": child.name,
			"type": child.get_class(),
			"script": _get_script_path(child),
			"visible": _is_visible(child)
		})
	return {"children": children}

# ─── BPB AI Enhanced: Synergy + Price Reading ───

func _get_item_details(zone = "all"):
	"""读取指定区域物品的所有脚本属性，包括价格、连接器数据等。"""
	var result = {}
	var main = get_tree().get_root().get_node_or_null("Main")
	if not main:
		return {"error": "Main not found, are you in-game?"}
	
	if zone == "all" or zone == "backpack":
		result["backpack"] = _read_zone_items(main, "Player", "backpack")
	if zone == "all" or zone == "shop":
		result["shop"] = _read_zone_items(main, "Shop/Items", "shop")
	if zone == "all" or zone == "storage":
		result["storage"] = _read_zone_items(main, "Shop/Storagebox", "storage")
	
	return result

func _read_zone_items(main, node_path, zone_name):
	"""读取指定节点的所有物品子节点及其属性。"""
	var parent = main.get_node_or_null(node_path)
	if not parent:
		return []
	
	var items = []
	for child in parent.get_children():
		if child.get_script() == null:
			continue
		var info = {
			"name": child.name,
			"type": child.get_class(),
			"position": {"x": child.position.x, "y": child.position.y},
			"rotation": child.rotation if "rotation" in child else 0,
			"zone": zone_name,
		}
		
		# 读取脚本所有可访问属性
		var props = _safe_get_all_properties(child)
		info["properties"] = props
		
		# 尝试读取价格（常见属性名）
		for price_key in ["price", "item_price", "base_price", "gold_cost", "cost", "sell_price"]:
			if price_key in props:
				info["price"] = props[price_key]
				break
		
		# 尝试读取联动数据（常见属性名）
		for conn_key in ["connector", "connector_type", "synergy_type", "ConnectType"]:
			if conn_key in props:
				info["connector"] = props[conn_key]
				break
		
		# 尝试读取脚本路径
		var script = child.get_script()
		if script:
			info["script_path"] = script.resource_path
		
		items.append(info)
	
	return items

func _safe_get_all_properties(node):
	"""获取节点所有属性，安全处理各种类型。"""
	var props = {}
	var list = node.get_property_list()
	for p in list:
		var name = p.name
		if name.begins_with("_") or name in ["script", "resource_local_to_scene"]:
			continue
		if name in node and node.get(name) != null:
			props[name] = _serialize_variant(node.get(name))
	return props

func _get_shop_offers():
	"""读取商店所有 ShopOffer 节点的详细数据。"""
	var result = {}
	var main = get_tree().get_root().get_node_or_null("Main")
	if not main:
		return {"error": "Main not found"}
	
	var shop = main.get_node_or_null("Shop")
	if not shop:
		return {"error": "Shop not found, are you in shop phase?"}
	
	result["shop_properties"] = _get_all_properties(shop)
	
	var offers = []
	for child in shop.get_children():
		if "ShopOffer" in child.name or child.get_class() == "ShopOffer":
			var offer_data = {
				"name": child.name,
				"visible": child.visible if "visible" in child else false,
				"properties": _safe_get_all_properties(child),
			}
			offers.append(offer_data)
	result["offers"] = offers
	
	# 商店已购物品
	var items = shop.get_node_or_null("Items")
	if items:
		var item_list = []
		for child in items.get_children():
			item_list.append({
				"name": child.name,
				"position": {"x": child.position.x, "y": child.position.y},
				"properties": _safe_get_all_properties(child),
			})
		result["shop_items"] = item_list
	
	return result

func _get_backpack_items_full():
	"""读取背包所有物品的完整属性（含脚本运行时成员）。"""
	var main = get_tree().get_root().get_node_or_null("Main")
	if not main:
		return {"error": "Main not found"}
	
	var player = main.get_node_or_null("Player")
	if not player:
		return {"error": "Player not found"}
	
	var items = []
	for child in player.get_children():
		if child.get_script() == null:
			continue
		items.append({
			"name": child.name,
			"position": {"x": child.position.x, "y": child.position.y},
			"rotation": child.rotation if "rotation" in child else 0,
			"properties": _safe_get_all_properties(child),
		})
	
	return {"items": items}

func _get_connector_data(item_path):
	"""读取指定物品节点的连接器（联动）数据。
	
	参数 item_path: Godot 路径如 "/root/Main/Player/Long Sword"
	"""
	var node = _find_node_by_path(item_path)
	if not node:
		return {"error": "Node not found: " + item_path}
	
	var data = {
		"name": node.name,
		"properties": _safe_get_all_properties(node),
	}
	
	# 尝试查找连接器子节点
	for child in node.get_children():
		if "connector" in child.name.to_lower() or child.get_class() == "Connector":
			data["connector_node"] = {
				"name": child.name,
				"position": {"x": child.position.x, "y": child.position.y},
				"visible": child.visible,
				"scale": {"x": child.scale.x, "y": child.scale.y},
				"properties": _safe_get_all_properties(child),
			}
			# 读取 texture 路径
			if "texture" in child and child.texture:
				data["connector_node"]["texture_path"] = child.texture.resource_path
	
	return data

func _get_item_price(item_path):
	"""读取指定物品节点的价格。"""
	var node = _find_node_by_path(item_path)
	if not node:
		return {"error": "Node not found: " + item_path}
	
	var props = _safe_get_all_properties(node)
	var price = null
	
	# 遍历所有常见价格属性名
	for key in ["price", "item_price", "base_price", "gold_cost", "cost",
				"sell_price", "buy_price", "member_price", "Price", "Cost"]:
		if key in props:
			price = props[key]
			break
	
	if price == null:
		# 兜底：全部整数属性中可能是价格的
		for k in props:
			if typeof(props[k]) == TYPE_INT and props[k] > 0 and props[k] < 100000:
				if price == null or props[k] > price:
					price = {"candidate": props[k], "key": k}
	
	return {
		"item_path": item_path,
		"name": node.name,
		"price": price,
		"all_properties": props,
	}

func _get_full_game_state():
	"""读取完整游戏状态（含联动+价格）。"""
	var result = {}
	
	# 基础游戏状态
	var game = get_node_or_null("/root/Game")
	if game:
		result["game_properties"] = _safe_get_all_properties(game)
	
	# 物品细节（三个区域）
	result["items"] = _get_item_details("all")
	
	# 商店报价
	result["shop"] = _get_shop_offers()
	
	# 玩家状态
	var main = get_tree().get_root().get_node_or_null("Main")
	if main:
		var player = main.get_node_or_null("Player")
		if player:
			result["player_properties"] = _safe_get_all_properties(player)
	
	return result

func _is_visible(node):
	if node is CanvasItem:
		return node.visible
	elif node is Node:
		return true
	return false

func _get_script_path(node):
	var script = node.get_script()
	if script:
		return script.resource_path
	return ""

func _serialize_variant(val):
	match typeof(val):
		TYPE_NIL:
			return null
		TYPE_BOOL, TYPE_INT, TYPE_REAL, TYPE_STRING:
			return val
		TYPE_VECTOR2:
			return {"x": val.x, "y": val.y}
		TYPE_VECTOR3:
			return {"x": val.x, "y": val.y, "z": val.z}
		TYPE_COLOR:
			return {"r": val.r, "g": val.g, "b": val.b, "a": val.a}
		TYPE_ARRAY:
			var arr = []
			for item in val:
				arr.append(_serialize_variant(item))
			return arr
		TYPE_DICTIONARY:
			var dict = {}
			for key in val:
				dict[str(key)] = _serialize_variant(val[key])
			return dict
		TYPE_OBJECT:
			if val:
				return {"type": "object", "class": val.get_class(), "script": _get_script_path(val)}
			return null
		TYPE_NODE_PATH:
			return str(val)
		_:
			return str(val)

func _deserialize_variant(val):
	if val == null:
		return null
	if typeof(val) == TYPE_DICTIONARY:
		if val.has("x") and val.has("y"):
			if val.has("z"):
				return Vector3(val.x, val.y, val.z)
			else:
				return Vector2(val.x, val.y)
		if val.has("r") and val.has("g") and val.has("b"):
			return Color(val.r, val.g, val.b, val.get("a", 1.0))
	return val
