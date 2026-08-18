extends Node2D

var frameCounter = 0
var time = 0.0
var clockTime = 0.0
var rng = RandomNumberGenerator.new()
var file = File.new()
var translationCache: = {}
var sharedBitstream: = BitStream.new()
var sharedDirectory: = Directory.new()
var mouseVelocity: Vector2
var lastMousePos: Vector2

const paramColor = Color(1, 0.890196, 0.219608)
var paramColor_html = paramColor.to_html(false)
const modifiedColor = Color(0.544922, 1, 0.562698)
const negativeColor = Color(1, 0.7052, 0.34375)
const inactiveColor = Color.gray
const triggerColor = Color(0.935547, 0.783836, 0.579235)
const red = Color(0.988281, 0.55661, 0.449219)

var statColors = [
	paramColor, 
	modifiedColor, 
	negativeColor
]

const weaponIcons = {
	Item.Stat.MaxDamage: preload("res://Interface/Tooltips/Icon_Damage.png"), 
	Item.Stat.Accuracy: preload("res://Interface/Tooltips/Icon_Accuracy.png"), 
	Item.Stat.Cooldown: preload("res://Interface/Tooltips/Icon_Cooldown.png"), 
	Item.Stat.StaminaCost: preload("res://Interface/Tooltips/Icon_Stamina.png"), 
	Item.Stat.CritChance: preload("res://Interface/Tooltips/Icon_CritChance.png")
}

var statIcons: Dictionary

var bannerGradients: Dictionary
var uniqueTooltipTextures: Dictionary
var uniqueTooltipDivider: Dictionary
var uniqueTooltipIcon: Dictionary



var defaultFonts = Dictionary()

const popupMessageScene = preload("res://Interface/PopupMessage.tscn")

const zapScene = preload("res://Items/Animations/Zap.tscn")

const baskervilleRegular = preload("res://Assets/Fonts/LibreBaskerville-Regular.ttf")
const baskervilleBold = preload("res://Assets/Fonts/LibreBaskerville-Bold.ttf")
const milonga = preload("res://Assets/Fonts/Milonga-Regular.ttf")
const glassAniqua = preload("res://Assets/Fonts/GlassAntiqua-Regular.ttf")

const latinFonts = [baskervilleBold, baskervilleRegular, milonga, glassAniqua]


var chineseFallbackFont
var chineseFont1
var chineseFont2
var japaneseFallbackFont
var japaneseFont1
var japaneseFont2
var koreanFallbackFont
var koreanFont1
var traditionalChineseFont1

var russianFont1
var russianFont2
var russianFallbackFont

func _ready():
	OS.set_window_title(ProjectSettings.get_setting("application/config/name"))
	pause_mode = Node.PAUSE_MODE_PROCESS
	randomize()
	rng.randomize()
	
	for icon in icons:
		iconTextures[icon] = load(icons[icon])
	
	if not OS.has_feature("web"):
		
		chineseFallbackFont = load("res://Assets/Fonts/Localized/ChineseFallbackFont.tres")
		chineseFont1 = load("res://Assets/Fonts/Localized/NotoSansSC-Regular_.otf")
		chineseFont2 = load("res://Assets/Fonts/Localized/ChineseDisplay-Regular.ttf")
		japaneseFallbackFont = load("res://Assets/Fonts/Localized/JapaneseFallbackFont.tres")
		japaneseFont1 = load("res://Assets/Fonts/Localized/NotoSansJP-Regular.ttf")
		japaneseFont2 = load("res://Assets/Fonts/Localized/HannariMincho-Regular.otf")
		koreanFont1 = load("res://Assets/Fonts/Localized/NotoSansKR-Regular.ttf")
		koreanFallbackFont = load("res://Assets/Fonts/Localized/KoreanFallbackFont.tres")
		traditionalChineseFont1 = load("res://Assets/Fonts/Localized/NotoSansTC-Regular.ttf")
		russianFont1 = load("res://Assets/Fonts/Localized/NotoSerif-Regular.ttf")
		russianFont2 = load("res://Assets/Fonts/Localized/kurale-regular.otf")
		russianFallbackFont = load("res://Assets/Fonts/Localized/RussianFallbackFont.tres")
		




		
	prepareFonts()
	
	var reversed = invertDictionary(ItemDescriptor.StuffedClasses)
	for classI in ItemDescriptor.StuffedClasses.values():
		if classI > 0 and classI < ItemDescriptor.StuffedClasses.Neutral:
			uniqueTooltipTextures[classI] = load(str("res://Interface/Tooltips/TooltipBase_", reversed[classI], ".png"))
			uniqueTooltipDivider[classI] = load(str("res://Interface/Tooltips/Divider_", reversed[classI], ".png"))
			uniqueTooltipIcon[classI] = load(str("res://Interface/Tooltips/TooltipIcon_", reversed[classI], ".png"))
			if Game.isClassUnlockedStuffed(classI):
				bannerGradients[classI] = load(str("res://CharacterClasses/", reversed[classI], "/BannerGradient.tres"))
	
	uniqueTooltipTextures[ItemDescriptor.StuffedClasses.Neutral] = load("res://Interface/Tooltips/TooltipBase_Unique.png")
	uniqueTooltipDivider[ItemDescriptor.StuffedClasses.Neutral] = load("res://Interface/Tooltips/Divider2_Unique.png")
	

var damageNumberFonts: Array
const baseDamageNumberFont: DynamicFont = preload("res://Interface/DamageNumbers/DamageNumberBaseFont.tres")

func prepareFonts():
	damageNumberFonts.resize(201)

	var sizes = [60, 65, 70, 75, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200]
	for i in sizes.size():
		var size = sizes[i]
		var font = baseDamageNumberFont.duplicate()
		font.size = size
		font.outline_size = size / 25.0 + 2.5
		damageNumberFonts[size] = font
		var label = Label.new()
		label.add_to_group("NotLocalized")
		add_child(label)
		label.set("custom_fonts/font", font)
		label.text = "-+1234567890"
		callNextFrame(label, "queue_free")
		
		if i == sizes.size() - 1:
			break
		
		var nextSize = sizes[i + 1]
		for sizeI in range(size + 1, nextSize):
			damageNumberFonts[sizeI] = font


func _process(delta):
	clockTime += delta

func _physics_process(delta):
	
	if not get_tree().paused:
		frameCounter += 1
		time += delta
	
	var curMousePos = getMousePosInWindow()
	mouseVelocity = (curMousePos - lastMousePos)
	lastMousePos = curMousePos

func getMouseSpeed() -> float:
	return mouseVelocity.length()

func getFrameCounter_process():
	return Engine.get_physics_frames()

func angleDif(angle1, angle2):
	var angle = abs(angle1 - angle2)
	if angle > 180.0:
		return 360.0 - angle
	return angle

func rotDif(rot1, rot2):
	var rot = abs(rot1 - rot2)
	if rot > PI:
		return 2 * PI - rot
	return rot

func randInBox(xRange, yRange) -> Vector2:
	return Vector2(rng.randf_range( - xRange, xRange), rng.randf_range( - yRange, yRange))

func randInCircle(radius: float) -> Vector2:
	return Vector2(rng.randf_range(0, radius), 0).rotated(rng.randf_range(0, 2 * PI))

var debugOnlyCounter = 0

func debugOnly(val = true):
	
	if debugOnlyCounter > 3:
		print("DEBUG ONLY - ", val)
	
	debugOnlyCounter += 1
	
	if not OS.has_feature("editor"):
		return false
		
	return val

func eprint(text, arg1 = null, arg2 = null, arg3 = null):
	if OS.has_feature("editor"):
		if arg3 != null:
			print("-", text, arg1, arg2, arg3)
		elif arg2 != null:
			print("-", text, arg1, arg2)
		elif arg1 != null:
			print("-", text, arg1)
		else:
			print("-", text)

func eassert(toTest: bool = false):
	if OS.has_feature("editor"):
		assert (toTest)
	


func tra(key: String) -> String:
	var translation = translationCache.get(key, null)
	
	if translation == null:
		translation = tr(key)
		if translation == key:
			translation = ""
		translationCache[key] = translation
		
	return translation

func updateLocale():
	updateAllFonts()
	translationCache.clear()

func updateLocaleInSubtree(node):
	if node.is_in_group("Localized"):
		localizeFonts(node)
		node.updateLocale()
	
	for child in node.get_children():
		updateLocaleInSubtree(child)









const nonBreakingSpace = " "
const zeroWidthSpace = "​"

func tr_nbs(key: String) -> String:
	return tr(key)





func tra_nbs(key: String) -> String:
	return tra(key)





func equals(val1, val2) -> bool:
	return typeof(val1) == typeof(val2) and val1 == val2

func addSign(numberVal) -> String:
	if numberVal > 0:
		return "+" + str(numberVal)
	else:
		return str(numberVal)

func addPlus(numberVal) -> String:
	if numberVal >= 0:
		return "+" + str(numberVal)
	else:
		return str(numberVal)

func toBinary(intValue: int) -> String:
	var bin_str: String = ""
	while intValue > 0:
		bin_str = str(intValue & 1) + bin_str
		intValue = intValue >> 1
	return bin_str

func countOnes(num, maxBits = 64) -> int:
	var numOnes = 0
	for i in maxBits:
		if num & (1 << i) > 0:
			numOnes += 1
	return numOnes

func bitIncludes(doesBin1, includeBin2):
	return ( ~ doesBin1 & includeBin2) == 0

func addDirectoryContents(dir: Directory, files: Array, directories: Array):
	var file_name = dir.get_next()
	
	while (file_name != ""):
		var path = dir.get_current_dir() + "/" + file_name
		
		if dir.current_is_dir():
			var subDir = Directory.new()
			subDir.open(path)
			subDir.list_dir_begin(true, false)
			directories.append(path)
			addDirectoryContents(subDir, files, directories)
		else:
			files.append(path)
			
		file_name = dir.get_next()
			
	dir.list_dir_end()

func writeVarToFile(filePath, content):
	var tempPath = filePath + ".tmp"
	var err = writeVarToFile_simple(tempPath, content)
	if err == OK:
		var dir = Directory.new()
		err = dir.rename(tempPath, filePath)
		assert (err == OK)
	return err

func writeVarToFile_simple(filePath, content):
	var err = file.open(filePath, File.WRITE)
	if err == OK:
		file.store_var(content)
		file.close()
	else:
		assert (false)
	return err

func hasDLL(dllName) -> bool:
	if Game.EDITOR: return true
	var exePath = OS.get_executable_path()
	var exeDir = exePath.get_base_dir()
	var dir = Directory.new()
	if dir.open(exeDir) == OK:
		if OS.has_feature("Windows"):
			return dir.file_exists(dllName + ".dll")
		elif OS.has_feature("X11"):
			return dir.file_exists(dllName + ".so")
	return false

func generateRandomString(length) -> String:
	var string = ""
	for i in length:
		string += char(rng.randi_range(35, 126))
	
	return string

const colorFormat = "[color=#{col}]{text}[/color]"

const smartColorFormat = "[sc len={length} color=#{col}]{text}[/sc]"





func highlight(text) -> String:
	return wrapInColor(String(text), paramColor)

var wrapDict = {"col": "", "text": ""}
func wrapInColor(text: String, color: Color) -> String:
	return colorFormat.format({
		"col": color.to_html(false), 
		"text": text
	})

func wrapInColor_html(text, color: String) -> String:
	wrapDict["col"] = color
	wrapDict["text"] = text
	return colorFormat.format(wrapDict)

func wrapInColor_fixed(text: String, color: Color) -> String:
	return smartColorFormat.format({
			"col": color.to_html(false), 
			"length": text.length(), 
			"text": text
		})









func removeDollarCommands(text: String) -> String:
	var iterations = 0
	var dollarPos = - 1
	while true:
		if iterations == 100:
			print("Endless loop, probably } missing ", text)
			eassert()
			break
		iterations += 1
		
		
		dollarPos = text.find("$", 0)
		if dollarPos == - 1:
			break
		
		
		var refEndPos = findFirstNonLatinLetterOrNumber(text, dollarPos + 1)
		var reference = text.substr(dollarPos + 1, refEndPos - dollarPos - 1)
		var replacement = ""
		
		if reference == "rage":
			pass
		
		if text[refEndPos] == "[":
			var closingBracketPos = ItemToolTip.findClosingBracket(text, refEndPos + 1)
			
			replacement += substr(text, refEndPos + 1, closingBracketPos - 1)
			
			refEndPos = closingBracketPos + 1
		
		if reference in icons and not reference in iconsWithoutTranslation:
			var translated = tra(reference + "_NAME")
			if translated == "":
				translated = tra(str("TYPE_", reference.capitalize(), "_NAME"))
			if translated == "":
				translated = tra(reference.capitalize() + "_NAME")
				
			replacement = str(translated, replacement)
		
		text = str(text.substr(0, dollarPos), replacement, text.substr(refEndPos))
	
	text = text.replace("\\~", "")
	text = text.replace("\n", "")
	text = text.replace("  ", " ")
	
	return text

func longTo2Ints(long: int) -> PoolIntArray:
	var arr = PoolIntArray()
	arr.push_back(long >> 32)
	arr.push_back(long)
	
	return arr

func twoIntsToLong(arr: PoolIntArray) -> int:
	var upper: int = (arr[0] << 32)
	var lower: int = arr[1]
	if lower < 0:
		lower = lower + (1 << 32)
	
	return upper + lower

func absv(vec: Vector2):
	return Vector2(abs(vec.x), abs(vec.y))

func pickRandomElement(array: Array):
	return array[rng.randi_range(0, array.size() - 1)]

func getArrayElement(array: Array, index: int, default = null):
	if index > array.size() - 1:
		return default
	else:
		return array[index]

func nDimArrayGet(array: Array, indices: Array, default = null):
	var arrayLevel = array
	for index in indices:
		if index < arrayLevel.size():
			arrayLevel = arrayLevel[index]
		else:
			return default
	
	return arrayLevel

func findAll(array: Array, value) -> Array:
	var results = []
	var index = 0
	while true:
		index = array.find(value, index)
		if index != - 1:
			results.push_back(index)
			index += 1
		else:
			break
	
	return results

func log2(number):
	return log(number) / log(2)

func loadSheetAsArray(filepath) -> Array:
	file.open(filepath, file.READ)
	var header = file.get_csv_line()
	var arr = Array()
	while not file.eof_reached():
		var line = file.get_csv_line()
		if line.size() > 1:
			arr.append(line)
	file.close()
		
	return [header, arr]
	
func filterDuplicates(arr: Array) -> Array:
	var dict = Dictionary()
	for a in arr:
		dict[a] = true
	return dict.keys()

func hasDuplicates(arr: Array) -> bool:
	var dict = Dictionary()
	for a in arr:
		if a in dict:
			return true
		dict[a] = true
	return false

func countDuplicates(arr: Array) -> int:
	var before = arr.size()
	var filtered = filterDuplicates(arr)
	return before - filtered.size()

func filterNull(arr: Array) -> Array:
	var nonNull = []
	for element in arr:
		if element != null:
			nonNull.push_back(element)
	return nonNull

func subtractArr(a: Array, b: Array) -> Array:
	var result: = []
	var bag: = {}
	for item in b:
		if not bag.has(item):
			bag[item] = 0
		bag[item] += 1
	for item in a:
		if bag.has(item):
			bag[item] -= 1
			if bag[item] == 0:
				bag.erase(item)
		else:
			result.append(item)
	return result


func subtractDictFromArray(a: Array, b: Dictionary) -> Array:
	var result: = []
	for item in a:
		if not b.has(item):
			result.append(item)
	return result

func findFirstOf(string: String, stringsToFind: Array, startIndex: int = 0):
	var firstIndex = INF
	for stringToFind in stringsToFind:
		var index2 = string.find(stringToFind, startIndex)
		if index2 != - 1:
			firstIndex = min(firstIndex, index2)
	
	if firstIndex == INF:
		firstIndex = - 1
	
	return firstIndex



func isLatinLetterOrNumber(character: String):
	var ascii = ord(character)
	return ((ascii >= 65 and ascii <= 122) or 
			(ascii >= 48 and ascii <= 57))

func isNonLatinLetterOrNumber(string: String):
	if string == "[":
		return true
	
	if (string == "%"):
		return false
	
	return not isLatinLetterOrNumber(string)
	

func findFirstNonLatinLetterOrNumber(string: String, startIndex: int = 0):
	for i in range(startIndex, string.length()):
		var ascii = ord(string[i])
		
		
		if string[i] == "[":
			return i
		if ( not (ascii >= 65 and ascii <= 122) and 
			not (ascii >= 48 and ascii <= 57) and 
			not (string[i] == "%")):
			
			return i
	return - 1

func findHighlightEnd(string: String, startIndex: int = 0):
	var length: int = string.length()
	for i in range(startIndex, length):
		var character = string[i]
		var ascii: int = ord(character)
		
		
		if character == "[":
			return i
		
		
		if character == nonBreakingSpace or character == " ":
			if length > i:
				if string[i + 1] == "%":
					return i + 2
				
				
				var translatedSecond = tra("FORMAT_Second")
				var secondLength: int = translatedSecond.length()
				if length < i + secondLength:
					return i
				for j in secondLength:
					
					if string[i + j + 1] != translatedSecond[j]:
						return i
				
				
				var candidateEnd = i + secondLength + 1
				if length > candidateEnd:
					if not string[candidateEnd] in [".", ",", ":", ";", "(", ")", " ", "?", "!", nonBreakingSpace]:
						return i
				return candidateEnd
			
			return i
		
		if ( not (ascii >= 65 and ascii <= 122) and 
			not (ascii >= 48 and ascii <= 57) and 
			not (character == "%")):
			
			return i
	return length

func findWholeWord(text, searchTerm):
	var from = 0
	var length = searchTerm.length()
	while true:
		var startPos = text.findn(searchTerm, from)
		if startPos == - 1:
			return - 1
		if isLatinLetterOrNumber(text[startPos + length]):
			
			from = startPos + 1
		else:
			return startPos



func substr(string: String, from: int, to: int):
	return string.substr(from, to - from + 1)


func replaceSubstr(string: String, from: int, to: int, replacement: String):
	var newString = string.substr(0, from)
	newString += replacement
	newString += string.substr(to + 1)
	return newString

func later(version, thanVersion) -> bool:
	if version == thanVersion:
		return false
	return laterOrEqual(version, thanVersion)


func laterOrEqual(saveStateVersion, breakingVersion) -> bool:
	var split1 = saveStateVersion.split(".")
	var split2 = breakingVersion.split(".")
	for i in split1.size():
		var number1 = int(split1[i])
		var number2 = int(split2[i])
		if number1 > number2:
			return true
		elif number1 < number2:
			return false
		
	
	return true

func randRange(from: float, to: float) -> float:
	return rng.randf_range(from, to)

func randPitch(variation = 0.05) -> float:
	return rng.randf_range(1 - variation, 1 + variation)

const mouseButtons = {
	BUTTON_LEFT: "MOUSE_LEFT", 
	BUTTON_RIGHT: "MOUSE_RIGHT", 
	BUTTON_MIDDLE: "MOUSE_MIDDLE", 
	BUTTON_WHEEL_UP: "MOUSE_WHEEL", 
	
	
	BUTTON_XBUTTON1: "MOUSE4", 
	BUTTON_XBUTTON2: "MOUSE5", 
	
}

onready var mouseButtonsInverted = invertDictionary(mouseButtons)

func connectIfExists(emitter, signalName, listener, methodname, binds = [], flags = 0):
	if listener.has_method(methodname):
		emitter.connect(signalName, listener, methodname, binds, flags)
	
func tryConnect(emitter, signalName, listener, methodname, binds = [], flags = 0):
	if not emitter.is_connected(signalName, listener, methodname):
		emitter.connect(signalName, listener, methodname, binds, flags)

func tryDisconnect(emitter, signalName, listener, methodname):
	if emitter.is_connected(signalName, listener, methodname):
		emitter.disconnect(signalName, listener, methodname)

func setConnected(connected: bool, emitter, signalName, listener, methodname):
	if connected:
		tryConnect(emitter, signalName, listener, methodname)
	else:
		tryDisconnect(emitter, signalName, listener, methodname)

func setDelayed(target, propertyName, value, delay):
	var timer = get_tree().create_timer(delay, false)
	timer.connect("timeout", target, "set", [propertyName, value], CONNECT_ONESHOT)

func setDelayed_process(target, propertyName, delay, value):
	var timer = get_tree().create_timer(delay, true)
	timer.connect("timeout", target, "set", [propertyName, value], CONNECT_ONESHOT)

func callDelayed(target, methodName, delay, binds = []):
	var timer = get_tree().create_timer(delay, false)
	timer.connect("timeout", target, methodName, binds, CONNECT_ONESHOT)

func callDelayed_process(target, methodName, delay, binds = []):
	var timer = get_tree().create_timer(delay, true)
	timer.connect("timeout", target, methodName, binds, CONNECT_ONESHOT)


func callNextFrame(target, methodName, arguments = []):
	get_tree().connect("idle_frame", target, methodName, arguments, CONNECT_ONESHOT)

func finishTimer(timer: Timer):
	if not timer.is_stopped():
		timer.stop()
		for c in timer.get_signal_connection_list("timeout"):
			if c.binds.empty():
				c.target.call(c.method)
			else:
				c.target.callv(c.method, c.binds)

func isTweenRunning(tween: SceneTreeTween):
	return is_instance_valid(tween) and tween.is_valid()

func killTween(tween: SceneTreeTween):
	if is_instance_valid(tween):
		tween.kill()

func finishTween(tween: SceneTreeTween):
	if isTweenRunning(tween):
		tween.custom_step(10000)

func refreshTween(tween: SceneTreeTween) -> SceneTreeTween:
	killTween(tween)
	return create_tween()

func ensureTween(tween: SceneTreeTween) -> SceneTreeTween:
	if not isTweenRunning(tween):
		return refreshTween(tween)
	return tween

func tweenMethodCurve(tween: SceneTreeTween, node: Node, methodName: String, 
	fromVal, toVal, duration: float, curve: Curve):
		
	tween.tween_method(self, "lerpPosCurve", 0.0, 1.0, duration, 
		[node, methodName, fromVal, toVal, curve])

func isChristmas() -> bool:
	var date = OS.get_date()
	return (date.month == 12 or (date.month == 1 and date.day < 7))

func lerpPosCurve(interpolationPoint: float, node, methodName, fromVal, toVal, curve: Curve):
	var eased = curve.interpolate_baked(interpolationPoint)
	var val = lerp(fromVal, toVal, eased)
	node.call(methodName, val)

func moveParable(tween: SceneTreeTween, node, xMovement, yOffset, 
	dur, phase1Factor = 0.5):
	
	var phase1Dur = dur * phase1Factor
	var phase2Dur = dur - phase1Dur
	tween.set_parallel()
	
	tween.tween_property(node, "global_position:x", 
		node.global_position.x + xMovement, dur)
	
	tween.tween_property(node, "global_position:y", 
		node.global_position.y + yOffset, phase1Dur
		).set_trans(Tween.TRANS_QUAD).set_ease(Tween.EASE_OUT)

	tween.tween_property(node, "global_position:y", 
		node.global_position.y, phase2Dur
		).set_trans(Tween.TRANS_QUAD).set_ease(Tween.EASE_IN
		).from(node.global_position.y + yOffset).set_delay(phase1Dur)

func grabFocus(control):
	if Game.usingController:
		control.grab_focus()

func releaseFocus(control):
	if Game.usingController:
		control.release_focus()

func invertDictionary(dict: Dictionary) -> Dictionary:
	var invertedDict = Dictionary()
	for key in dict:
		invertedDict[dict[key]] = key
	return invertedDict

func arrayAsIndexDict(array: Array) -> Dictionary:
	var invertedDict = Dictionary()
	for i in array.size():
		invertedDict[array[i]] = i
	return invertedDict

func hashDictionary(dict: Dictionary) -> int:
	var keys: Array = dict.keys()
	keys.sort()
	var hashingContext = HashingContext.new()
	hashingContext.start(HashingContext.HASH_MD5)
	
	for key in keys:
		hashingContext.update(var2bytes(dict[key]))
	
	var hash_long = hashingContext.finish()
	
	var streamPeer = StreamPeerBuffer.new()
	streamPeer.put_data(hash_long)
	
	
	streamPeer.seek(0)
	
	return streamPeer.get_64()

func reparent(node, newParent):
	var pos = node.global_position
	var rot = node.global_rotation
	node.get_parent().remove_child(node)
	newParent.add_child(node)
	node.global_position = pos
	node.global_rotation = rot

func getGlobalZ(target: Node2D) -> int:
	var node = target
	var z_index = 0
	while node and node is Node2D:
		z_index += node.z_index
		if not node.z_as_relative:
			break
		node = node.get_parent()
	return z_index

const NUMBERLABEL_SCENE = preload("res://Interface/DamageNumbers/DamageNumber.tscn")
const BUFFLABEL_SCENE = preload("res://Interface/DamageNumbers/BuffLabel.tscn")









func randBuffLabelDir() -> Vector2:
	return Vector2(0, rng.randf_range( - 75, - 120))

func spawnNumberLabel(type: int, globalPosition: Vector2, 
	direction: Vector2, amount: int = 0):
	
	var numberLabel = ObjectPool.instance(NUMBERLABEL_SCENE)
	numberLabel.position = globalPosition
	
	Game.UINode.add_child(numberLabel)
	numberLabel.linear_velocity = direction
	numberLabel.spawnNumber(type, amount)


func spawnLabelOnItem(type: int, item, amount):
	if not is_instance_valid(item):
		print("spawnLabelOnItem null ", Util.enumToString(Game.EventType, type))
		return
	
	var buffLabel = ObjectPool.instance(BUFFLABEL_SCENE)
	var pos = item.getNextFreeLabelPosition()
	buffLabel.position = pos
	Game.UINode.add_child(buffLabel)
	buffLabel.linear_velocity = Vector2(0, - 75)
	buffLabel.spawnLabelOnItem(type, amount)

func spawnStatLabelOnItem(stat: int, item, amount, onOpponent = false):
	if amount == 0: return
	
	if not is_instance_valid(item):
		print("spawnStatLabelOnItem null ", Util.enumToString(Character.Stat, stat))
		return
	
	var buffLabel = ObjectPool.instance(BUFFLABEL_SCENE)
	var pos = item.getNextFreeLabelPosition()
	buffLabel.position = pos
	Game.UINode.add_child(buffLabel)
	buffLabel.linear_velocity = Vector2(0, - 75)
	buffLabel.spawnStatLabelOnItem(stat, amount, onOpponent)


func spawnBuffLabel(type: int, globalPosition: Vector2, amount = 0):
	var buffLabel = ObjectPool.instance(BUFFLABEL_SCENE)
	buffLabel.position = globalPosition
	Game.UINode.add_child(buffLabel)
	buffLabel.linear_velocity = randBuffLabelDir()
	buffLabel.spawnLabel(type, amount)


func spawnBuffLabel_item(type: int, item, amount, appliedToOpponent: bool):
	if not Settings.getVal(Settings.Setting.buff_labels): return
	
	var buffLabel = ObjectPool.instance(BUFFLABEL_SCENE)
	var pos = item.getNextFreeLabelPosition()
	buffLabel.position = pos
	Game.UINode.add_child(buffLabel)
	buffLabel.linear_velocity = Vector2(0, - 75)
	buffLabel.spawnLabel(type, amount, buffLabel.ChangeType.Gain, appliedToOpponent)

func spawnMissLabel(globalPosition: Vector2, direction: Vector2):
	var buffLabel = ObjectPool.instance(BUFFLABEL_SCENE)
	buffLabel.position = globalPosition
	Game.UINode.add_child(buffLabel)
	buffLabel.linear_velocity = direction
	buffLabel.spawnLabel(Game.EventType.MissedAttack)

func spawnResistedLabel(type: int, globalPosition: Vector2, amount = 0):
	if not Settings.getVal(Settings.Setting.buff_labels): return
	
	var label = ObjectPool.instance(BUFFLABEL_SCENE)
	label.position = globalPosition
	Game.UINode.add_child(label)
	label.linear_velocity = randBuffLabelDir()
	label.spawnLabel(type, amount, label.ChangeType.Resisted)

func spawnProtectedLabel(type: int, globalPosition: Vector2, amount = 0):
	if not Settings.getVal(Settings.Setting.buff_labels): return
	
	var label = ObjectPool.instance(BUFFLABEL_SCENE)
	label.position = globalPosition
	Game.UINode.add_child(label)
	label.linear_velocity = randBuffLabelDir()
	label.spawnLabel(type, amount, label.ChangeType.Protected)

func spawnReflectLabel(type: int, globalPosition: Vector2, amount = 0):
	if not Settings.getVal(Settings.Setting.buff_labels): return
	
	var label = ObjectPool.instance(BUFFLABEL_SCENE)
	label.position = globalPosition
	Game.UINode.add_child(label)
	label.linear_velocity = randBuffLabelDir()
	label.spawnLabel(type, amount, label.ChangeType.Reflected)

func dictAdd(dict: Dictionary, key, val = 1, base = 0) -> int:
	var newVal = dict.get(key, base) + val
	dict[key] = newVal
	return newVal

func dictSub(dict: Dictionary, key, val = 1) -> int:
	var val2 = dict.get(key, 0) - val
	if val2 <= 0:
		dict.erase(key)
	else:
		dict[key] = val2
	return val2

func dictAddDict(dict1: Dictionary, dict2: Dictionary) -> void :
	for key in dict2:
		dictAdd(dict1, key, dict2[key])

func dictAppend(dict: Dictionary, key, value) -> void :
	if key in dict:
		dict[key].append(value)
	else:
		dict[key] = [value]

func dictErase(dict: Dictionary, key, valueToErase) -> void :
	if key in dict:
		var arr = dict[key]
		arr.erase(valueToErase)
		if arr.empty():
			dict.erase(key)

func dictPop(dict: Dictionary, key):
	if key in dict:
		var arr = dict[key]
		var value = arr.pop_back()
		if arr.empty():
			dict.erase(key)
		return value
	else:
		return null

func flatten(arr: Array) -> Array:
	var flattened = []
	for inner in arr:
		flattened.append_array(inner)
	return flattened

func roll(maximum = 100.0) -> float:
	return rng.randf_range(0, maximum)

func flip(chance = 0.5) -> bool:
	return rng.randf() <= chance

func flipPercent(chance) -> bool:
	return roll() <= chance


func flipRound(chance) -> int:
	return int(floor(chance) + int(flip(fmod(chance, 1.0))))


func flipWeighted(weights: Array) -> int:
	var sum = 0.0
	for weight in weights:
		sum += weight
		
	var val = rng.randf_range(0, sum)
	var subsum = 0.0
	for i in weights.size():
		subsum += weights[i]
		if subsum >= val:
			return i
	
	return weights.size()

func isBetween(number, leftBorder, rightBorder) -> bool:
	return number > leftBorder and number < rightBorder

func floorStepify(value: float, step: float) -> float:
	return stepify(value - 0.5 * step + 1e-05, step)

func unset(binaryVar, flag):
	return binaryVar & ~ flag
	
func disconnectAll(object):
	var connections = object.get_incoming_connections()
	for c in connections:
		
		
		if c.signal_name != "tree_entered" and c.signal_name != "tree_exiting":
			c.source.disconnect(c.signal_name, object, c.method_name)

func disconnectSignal(object, signalName: String):
	var connections = object.get_incoming_connections()
	for c in connections:
		if c.signal_name == signalName:
			c.source.disconnect(c.signal_name, object, c.method_name)

func getRemainingAnimationTime(animation: AnimationPlayer) -> float:
	var remainingTime = 0.0
	if animation.is_playing():
		remainingTime = animation.current_animation_length - animation.current_animation_position
	return remainingTime

func stretchSpriteToWidth(sprite, widthInPixels: float):
	var currentSize = sprite.texture.get_size().x
	sprite.scale.x = widthInPixels / currentSize

func clampToRect(pos: Vector2, rect: Rect2) -> Vector2:
	pos.x = clamp(pos.x, rect.position.x, rect.end.x)
	pos.y = clamp(pos.y, rect.position.y, rect.end.y)
	return pos

func getMousePosInWindow() -> Vector2:
	return clampToScreen(get_global_mouse_position())

func clampToScreen(pos: Vector2) -> Vector2:
	var rect = get_viewport_rect()
	return clampToRect(pos, rect)

func enumToString(enu: Dictionary, value: int) -> String:
	var inverted = invertDictionary(enu)
	return inverted[value]

const iconSizes = {
	"spikes": 25, 
	"vampirism": 23, 
	"poison": 28, 
	"regen": 28, 
	"bl": 28, 
	"lucky": 28, 
	"blind": 25, 
	"mana": 28, 
	"gold": 30, 
	"heat": 28, 
	"cold": 28, 
	"empower": 28, 
	"affected3": 30, 
	"affected2": 30, 
	"affected": 30, 
	"empty": 30
}

const icons = {
	"gold": "res://Assets/GoldCoin2.png", 
	"affected3": "res://Assets/Tertiary_icon.png", 
	"affected2": "res://Assets/SecondaryStar_icon.png", 
	"affected": "res://Assets/Star.png", 
	"empty": "res://Assets/EmptyStar.png", 
	"spikes": "res://Interface/Tooltips/Icon_Spikes.png", 
	"vampirism": "res://Interface/Tooltips/Icon_Vampirism.png", 
	"poison": "res://Interface/Tooltips/Icon_Poison.png", 
	"regen": "res://Interface/Tooltips/Icon_Regeneration.png", 
	"bl": "res://Interface/Tooltips/Icon_Block.png", 
	"lucky": "res://Interface/Tooltips/Icon_Lucky.png", 
	"blind": "res://Interface/Tooltips/Icon_Blind.png", 
	"mana": "res://Interface/Tooltips/Icon_Mana.png", 
	"heat": "res://Interface/Tooltips/Icon_Heat.png", 
	"cold": "res://Interface/Tooltips/Icon_Cold.png", 
	"empower": "res://Interface/Tooltips/Icon_Empower.png", 
	"melee": "res://Interface/Tooltips/Icon_Melee.png", 
	"ranged": "res://Interface/Tooltips/Icon_Ranged.png", 
	"effect": "res://Interface/Tooltips/Icon_Effect.png", 
	"dark": "res://Interface/Tooltips/Icon_Dark.png", 
	"holy": "res://Interface/Tooltips/Icon_Holy.png", 
	"nature": "res://Interface/Tooltips/Icon_Nature.png", 
	"vampiric": "res://Interface/Tooltips/Icon_Vampiric.png", 
	"fire": "res://Interface/Tooltips/Icon_Fire.png", 
	"ice": "res://Interface/Tooltips/Icon_Ice.png", 
	"magic": "res://Interface/Tooltips/Icon_Magic.png", 
	"treasure": "res://Interface/Tooltips/Icon_Treasure.png", 
	"musical": "res://Interface/Tooltips/Icon_Musical.png", 
	"lightning": "res://Assets/Icon_Lightning.png", 
	
	"engineer": "res://Assets/TitleScreen/EngineerIcon.png"
}

const iconsWithoutTranslation = {
	"affected": true, "affected2": true, "affected3": true
}

var iconTextures: Dictionary

const imgFormat = "[i][img=0x{0}]{1}[/img][/i]"

func getIcon(keyword, size = null):
	if not icons.has(keyword): return null
	
	if size:
		return imgFormat.format([size, icons[keyword]])
	else:
		return imgFormat.format([iconSizes.get(keyword, 28), icons[keyword]])

func imageToBbcode(pathToImage: String, size: int) -> String:
	return imgFormat.format([size, pathToImage])

func getControllerIconBbcode(action, size: int = 40):
	var icon = ControllerIcons.getIconFromAction(action)
	return imageToBbcode(icon, size)




















func getIconTexture(keyword):
	if not icons.has(keyword): return null
	return load(icons[keyword])

func getAllChildren(node) -> Array:
	var arr = []
	walkChildren(node, arr)
	return arr

func walkChildren(node, arr):
	for child in node.get_children():
		arr.push_back(child)
		walkChildren(child, arr)

func removeLocalizedNode(node):
	defaultFonts.erase(node)
	for child in node.get_children():
		removeLocalizedNode(child)

func updateAllFonts():
	localizeFonts(get_tree().get_root())

const localizedTypes = {
	"Label": true, 
	"Button": true, 
	"CheckBox": true, 
	"RichTextLabel": true, 
	"LineEdit": true, 
	"ItemList": true
}

func localizeFonts(node):
	if not is_instance_valid(node):
		return







	if node.get_class() in localizedTypes:
		
		if node.is_in_group("NotLocalized"):
			return
		
		
		
		if not node in defaultFonts:
			
			var fontData = FontData.new()
			defaultFonts[node] = fontData
			
			fontData.setFont(getNormalFont(node))
			fontData.setBoldFont(getBoldFont(node))
		
		var locale = TranslationServer.get_locale()
		var defaultFontData: FontData = defaultFonts[node]
		if defaultFontData.curLocale != locale:
			defaultFontData.curLocale = locale
			
			setCorrespondingFont(node, defaultFontData)
	
	for child in node.get_children():
		localizeFonts(child)

func setCorrespondingFont(node, defaultFontData: FontData):
	var locale = TranslationServer.get_locale()
	
	var replaceNormal = false
	var replaceBold = false
	var normalFont = getNormalFont(node)
	var boldFont = getBoldFont(node)
	
	
	if locale == "zh_Hans_CN":
		if normalFont:
			replaceNormal = not isSimplifiedChinese(normalFont)
		if boldFont:
			replaceBold = not isSimplifiedChinese(boldFont)
	elif locale == "zh_Hant_TW":
		if normalFont:
			replaceNormal = not isTraditionalChinese(normalFont)
		if boldFont:
			replaceBold = not isTraditionalChinese(boldFont)
	elif locale == "ja":
		if normalFont:
			replaceNormal = not isJapanese(normalFont)
		if boldFont:
			replaceBold = not isJapanese(boldFont)
	elif locale == "ko":
		if normalFont:
			replaceNormal = not isKorean(normalFont)
		if boldFont:
			replaceBold = not isKorean(boldFont)
	elif locale == "ru":
		if normalFont:
			replaceNormal = not isRussian(normalFont)
		if boldFont:
			replaceBold = not isRussian(boldFont)
	else:
		if normalFont:
			replaceNormal = not isDefaultFont(normalFont) or normalFont.size != defaultFontData.size
		if boldFont:
			replaceBold = not isDefaultFont(boldFont) or boldFont.size != defaultFontData.bold_size
	
	if not replaceNormal and not replaceBold: return
	
	
	if replaceNormal:
		normalFont = normalFont.duplicate()
		defaultFontData.applyToFont(normalFont)
		setNormalFont(node, normalFont)
	
	if replaceBold:
		boldFont = boldFont.duplicate()
		defaultFontData.applyToBoldFont(boldFont)
		setBoldFont(node, boldFont)
	
	if locale == "zh_Hans_CN":
		if replaceNormal:
			makeSimplifiedChinese(normalFont)
		if replaceBold:
			makeSimplifiedChinese(boldFont)
	elif locale == "zh_Hant_TW":
		if replaceNormal:
			makeTraditionalChinese(normalFont)
		if replaceBold:
			makeTraditionalChinese(boldFont)
	elif locale == "ja":
		if replaceNormal:
			makeJapanese(normalFont)
		if replaceBold:
			makeJapanese(boldFont)
	elif locale == "ko":
		if replaceNormal:
			makeKorean(normalFont)
		if replaceBold:
			makeKorean(boldFont)
	elif locale == "ru":
		if replaceNormal:
			makeRussian(normalFont)
		if replaceBold:
			makeRussian(boldFont)
	
	if replaceNormal:
		normalFont.update_changes()
	if replaceBold:
		boldFont.update_changes()

func isDefaultFont(font: DynamicFont):
	return font.font_data in latinFonts

func makeSimplifiedChinese(font: DynamicFont):


	if (font.font_data == baskervilleRegular or 
		font.font_data == baskervilleBold):
		font.font_data = chineseFont1
		font.extra_spacing_top -= 6
	else:
		font.font_data = chineseFont2
		font.extra_spacing_bottom -= 6

func isSimplifiedChinese(font: DynamicFont):
	return font.font_data == chineseFont1 or font.font_data == chineseFont2

func makeTraditionalChinese(font: DynamicFont):
	if (font.font_data == baskervilleRegular or 
		font.font_data == baskervilleBold):
		font.font_data = traditionalChineseFont1
		font.extra_spacing_top -= 6
	else:
		font.font_data = chineseFont2
		font.extra_spacing_bottom -= 6

func isTraditionalChinese(font: DynamicFont):
	return font.font_data == traditionalChineseFont1 or font.font_data == chineseFont2

func makeJapanese(font: DynamicFont):
	if (font.font_data == baskervilleRegular or 
		font.font_data == baskervilleBold):
		font.font_data = japaneseFont1
		font.extra_spacing_top -= 5
		font.extra_spacing_bottom -= 3
	else:
		font.font_data = japaneseFont2
		
		font.size -= 2

func isJapanese(font: DynamicFont):
	return font.font_data == japaneseFont1 or font.font_data == japaneseFont2

func makeKorean(font: DynamicFont):
	if (font.font_data == baskervilleRegular or 
		font.font_data == baskervilleBold):
		font.font_data = koreanFont1
		font.extra_spacing_top -= 5
		font.extra_spacing_bottom -= 3
	else:
		font.font_data = koreanFont1
		font.extra_spacing_top -= 5
		font.size -= 2

func isKorean(font: DynamicFont):
	return font.font_data == koreanFont1

func isRussian(font: DynamicFont):
	return font.font_data == russianFont1 or font.font_data == russianFont2
	
func makeRussian(font: DynamicFont):
	if (font.font_data == baskervilleRegular or 
		font.font_data == baskervilleBold):
		font.font_data = russianFont1
		font.extra_spacing_top -= 6
		font.extra_spacing_bottom -= 3
	else:
		font.font_data = russianFont2
		font.extra_spacing_top -= 6
		font.size -= 2

func getSizedFont(font: DynamicFont, sizeChange: int) -> DynamicFont:
	var newFont = font.duplicate()
	newFont.size += sizeChange
	return newFont

func isControlWithSingleFont(node):
	return node is Label or node is Button or node is LineEdit or node is ItemList

func getNormalFont(node):
	if isControlWithSingleFont(node):
		return node.get("custom_fonts/font")
	elif node is RichTextLabel:
		return node.get("custom_fonts/normal_font")

func getBoldFont(node):
	return node.get("custom_fonts/bold_font")

func setNormalFont(node, font: DynamicFont):
	if isControlWithSingleFont(node):
		node.set("custom_fonts/font", font)
	elif node is RichTextLabel:
		node.set("custom_fonts/normal_font", font)

func setBoldFont(node, font: DynamicFont):
	node.set("custom_fonts/bold_font", font)

func addFallbackFonts(font: DynamicFont):
	if not OS.has_feature("web"):
		font.add_fallback(chineseFallbackFont)
		font.add_fallback(japaneseFallbackFont)
		font.add_fallback(koreanFallbackFont)
		font.add_fallback(russianFallbackFont)

func hasSpaceBeforePercent() -> bool:
	return TranslationServer.get_locale() in ["fr", "es"]

func hasSpaceBeforeSeconds() -> bool:
	return TranslationServer.get_locale() in ["fr", "pt_BR", "es"]

func createPulse(pulseScene, item, pos):
	var pulse = ObjectPool.instance(pulseScene)
	item.get_parent().add_child(pulse)
	pulse.z_index = item.z_index
	pulse.global_position = pos
	pulse.get_node("AnimationPlayer").play("Activate")

func isItem(object) -> bool:
	return object is Item

func isItemDescriptor(object) -> bool:
	return object is ItemDescriptor

func isBag(object) -> bool:
	return object is Bag

func getRarityEnum():
	return Item.Rarity

func getTypeEnum():
	return Item.Type

func getNodesForAllClasses(parent, pathFormat):
	var nodes: = []
	nodes.resize(Game.Classes_Full.size())
	for className in Game.Classes_Full:
		nodes[Game.Classes_Full[className]] = parent.get_node(pathFormat.format({"class": className}))
	return nodes

var console = null

func logSteamDeck(arg1, arg2 = null, arg3 = null, arg4 = null):
	if not SteamHelper.STEAMDECK or not Game.PLAYTEST: return
	var text = str(arg1)
	if arg2 != null:
		text += str(arg2)
	if arg3 != null:
		text += str(arg3)
	if arg4 != null:
		text += str(arg4)
	
	if not console:
		console = load("res://Utility/Debug/SteamdeckDebug.tscn").instance()
		Game.UINode.add_child(console)
	
	console.logText(text)

func showScreenKeyboard(lineEdit: LineEdit):
	if SteamHelper.STEAMDECK:
		lineEdit.caret_position = lineEdit.text.length()
		
		var res = Steam.showFloatingGamepadTextInput(0, 
			0, 500, 1000, 100)
		
		
		

func isActionPressed(actionName: String, checkController: bool = true) -> bool:
	if InputBlocker.isActive(): return false
	if Input.is_action_pressed(actionName): return true
	if checkController and Input.is_action_pressed(actionName + "_controller"): return true
	return false

func isActionJustPressed(actionName: String, checkController: bool = true) -> bool:
	if InputBlocker.isActive(): return false
	if Input.is_action_just_pressed(actionName): return true
	if checkController and Input.is_action_just_pressed(actionName + "_controller"): return true
	return false

func isAction_event(event: InputEvent, actionName: String) -> bool:
	return (event.is_action(actionName) or 
			event.is_action(actionName + "_controller"))

func isActionPressed_event(event: InputEvent, actionName: String) -> bool:
	return (event.is_action_pressed(actionName) or 
			event.is_action_pressed(actionName + "_controller"))

func isActionReleased_event(event: InputEvent, actionName: String) -> bool:
	return (event.is_action_released(actionName) or 
			event.is_action_released(actionName + "_controller"))

func isClickEvent(event: InputEvent) -> bool:
	return ((event.is_action_pressed("ui_accept") or 
		isActionPressed_event(event, "grab_item") or 
		(event is InputEventScreenTouch and event.pressed)))

func isClickReleaseEvent(event: InputEvent) -> bool:
	return ((event.is_action_released("ui_accept") or 
		isActionReleased_event(event, "grab_item") or 
		(event is InputEventScreenTouch and not event.pressed)))

func isRightClickReleaseEvent(event: InputEvent) -> bool:
	return (event is InputEventMouseButton and 
		event.button_index == BUTTON_RIGHT and 
		not event.is_pressed())

func isRightClick(event: InputEvent) -> bool:
	return (event is InputEventMouseButton and 
	event.is_pressed() and event.button_index == BUTTON_RIGHT)

func isKeyOrJoyButton(event: InputEvent) -> bool:
	return (event is InputEventKey or event is InputEventJoypadButton or event is InputEventJoypadMotion)

func sendAction(action: String, pressed: bool):
	var a = InputEventAction.new()
	a.action = action
	a.pressed = pressed
	Input.parse_input_event(a)

func getTextForEvent(event, translate: bool) -> String:
	if event is InputEventKey:
		
		
		var text = event.as_text()
		if text.length() > 1:
			var scancode
			if event.physical_scancode != 0:
				scancode = OS.keyboard_get_scancode_from_physical(event.physical_scancode)
			else:
				scancode = event.scancode
			
			var translationKey = "KEY_" + OS.get_scancode_string(scancode)
			var t = tra(translationKey)
			if t == "":
				t = OS.get_scancode_string(scancode)
				if event.control:
					t = str(tra("KEY_Control"), "+", t)
				return t
			else:
				if translate:
					if event.control:
						t = str(tra("KEY_Control"), "+", t)
					return t
				else:
					return translationKey
		else:
			if text == " ":
				if translate:
					return tra("KEY_Space")
				else:
					return "KEY_Space"
			elif text.length() == 1:
				return text.capitalize()
	
	elif event is InputEventMouseButton:
		if event.button_index in Util.mouseButtons:
			return Util.mouseButtons[event.button_index]
	
	return ""



func changeTimer(timer: Timer, t: float):
	var timeLeft = timer.get_time_left()
	timer.start(t + timeLeft)

func showPopupMessage(translationKey, formatParams = null, duration = 3.0):
	var popup = ObjectPool.instance(popupMessageScene)
	Game.tooltipsNode.add_child(popup)
	popup.duration = duration
	popup.setParams(formatParams)
	popup.setText(translationKey)


func sortDict(dict: Dictionary, shuffleBeforeSort = false) -> Array:
	var sorted: Array = dict.keys()
	if shuffleBeforeSort:
		sorted.shuffle()
	var dictSorter = DictSorter.new(dict)
	sorted.sort_custom(dictSorter, "sort")
	return sorted

func sortArrayByDict(array: Array, dict: Dictionary) -> Array:

	var dictSorter = DictSorter.new(dict)
	array.sort_custom(dictSorter, "sort")
	return array

func sortArrayByDict_reverse(array: Array, dict: Dictionary) -> Array:

	var dictSorter = DictSorter.new(dict)
	array.sort_custom(dictSorter, "sort_reverse")
	return array

func getInteractableNodes(root: Node) -> Array:
	var nodes: = []
	walkInteractableNodes(root, nodes)
	return nodes

func walkInteractableNodes(node: Node, nodes: Array):
	for child in node.get_children():
		if (child is BaseButton or 
			child is LineEdit or 
			child is Slider):
			nodes.push_back(child)
		walkInteractableNodes(child, nodes)

func isControlEnabled(node: Control) -> bool:
	if node is BaseButton:
		return not node.disabled
	elif node is LineEdit:
		return node.editable
	return true

class DictSorter:
	var dict: Dictionary
	
	func _init(_dict):
		dict = _dict
	
	func sort(key1, key2):
		return dict[key1] > dict[key2]
		
	func sort_reverse(key1, key2):
		return dict[key1] < dict[key2]






























