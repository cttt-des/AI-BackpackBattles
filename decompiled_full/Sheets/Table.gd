extends Reference
class_name Table

var colums = Dictionary()

func loadFromCsv(filepath: String, key = null):
	var file = File.new()
	if key != null:
		file.open_encrypted(filepath, file.READ, key)
	else:
		file.open(filepath, file.READ)
		
	var header = file.get_csv_line()
	
	
	for entry in header:
		colums[entry] = []
	
	var headerArr = colums.keys()

	while not file.eof_reached():
		var line = file.get_csv_line()
		for i in line.size():
			var relevantHeader = headerArr[i]
			
			colums[relevantHeader].append(line[i])

	file.close()
	return self

func isEqual(header: String, line: int, to):
	
	return colums[header][line] == to

func getStr(header: String, line: int):
	return colums[header][line]

func getFlags(header: String, enu: Dictionary, line: int):
	var split = getStr(header, line).replace(" ", "").split(",")
	var flags = 0
	for flag in split:
		if flag != "":
			flags += enu[flag]
	return flags

func getEnu(header: String, enu: Dictionary, line: int, default = null):
	var stringVal = getStr(header, line)
	stringVal = stringVal.replace(" ", "")
	if enu.has(stringVal):
		return enu[stringVal]
	else:
		return default

func getEnuStuffed(header: String, enu: Dictionary, line: int, default = null):
	var list = getStr(header, line)
	if list == "":
		return default
	
	var enuVal: = 0
	list = list.replace(" ", "")
	for entry in list.split(","):
		assert (enu.has(entry))
		enuVal += enu[entry]
	
	return enuVal

func getInt(header: String, line: int, default = null):
	var entry = getStr(header, line)
	if entry == "":
		return default
	else:
		return int(entry)
	
func getFloat(header: String, line: int, default = null):
	var entry = getStr(header, line)
	if entry == "":
		return default
	else:
		return float(entry)

func getParamName(header: String, line: int, default = ""):
	var entry = getStr(header, line)
	if entry != "":
		var slice = entry.get_slice(":", 1)
		if slice == "":
			print("malformed parameter")
		elif slice != entry:
			return slice
	return default


func fill(owner: Object, attribute: String, line: int):
	var sheetVariable = colums[attribute][line]
	if sheetVariable == "":
		return
	var owner_variable = owner.get(attribute)
	if typeof(owner_variable) == TYPE_INT:
		owner.set(attribute, int(sheetVariable))
	elif typeof(owner_variable) == TYPE_REAL:
		owner.set(attribute, float(sheetVariable))
	elif typeof(owner_variable) == TYPE_STRING:
		owner.set(attribute, sheetVariable)
		
func fillList(owner: Object, attributeList: Array, line: int):
	for attribute in attributeList:
		fill(owner, attribute, line)
		

func getHeaders():
	return colums.keys()

func countRows():
	return colums.values()[0].size()

func getIntList(header: String) -> Array:
	var col = colums[header]
	var ints = []
	ints.resize(col.size())
	for line in col.size():
		ints[line] = int(col[line])
	return ints



