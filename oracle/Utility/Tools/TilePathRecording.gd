tool
extends TileMap

export (bool) var recording = false setget setRecording

var tiles = []

func set_cell(x: int, y: int, tile: int, flip_x: bool = false, flip_y: bool = false, 
	transpose: bool = false, autotile_coord: Vector2 = Vector2(0, 0)):
	
	if tile != - 1 and recording:
		var vec = Vector2(x, y)
		if not vec in tiles:
			tiles.push_back(vec)
	
			print(x, ",", y)

func invertDictionary(dict: Dictionary) -> Dictionary:
	var invertedDict = Dictionary()
	for key in dict:
		invertedDict[dict[key]] = key
	return invertedDict

func setRecording(_recording: bool):
	recording = _recording
	if not recording:
		
		var string = "["
		for tile in tiles:
			string += str("Vector2", tile, ",")
		
		string[string.length() - 1] = "]"
		print(string)
		
	tiles.clear()





