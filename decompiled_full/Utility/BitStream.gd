extends Reference
class_name BitStream

var bits: Array
var currentBit = 0
var last_bit: int

static func binaryCeil(number):
	return pow(2, ceil(Util.log2(number)))

func clear():
	bits.clear()
	currentBit = 0
	last_bit = 0

func bitsLeft():
	return bits.size() - currentBit
	

func serializeInt(num: int, bitSize: int = 64) -> String:
	clear()
	pushBitsize(num, bitSize)
	return toGodotString()

func deserializeInt(serialized: String, bitSize: int = 64) -> int:
	clear()
	fromGodotString(serialized)
	return pullBitsize(bitSize)


func deserializeIntArray(serialized: String, bitSize: int = 64) -> Array:
	clear()
	fromGodotString(serialized)
	var arr = []
	for serialiedInt in serialized:
		arr.push_back(pullBitsize(bitSize))
	return arr

func serializeIntArray(arr: Array, bitSize: int = 64) -> String:
	clear()
	for num in arr:
		pushBitsize(num, bitSize)
	return toGodotString()

func serializeString(string: String) -> String:
	clear()
	for byte in string.to_utf8():
		pushBitsize(byte, 8)
	return toGodotString()

func deserializeString(string: String) -> String:
	var byteArr = PoolByteArray()
	clear()
	fromGodotString(string)
	for i in bits.size() / 8:
		byteArr.push_back(pullBitsize(8))
	
	return byteArr.get_string_from_utf8()

func push(value: int, rangeMax: int):
	if Game.EDITOR:
		assert (value < rangeMax)
	var numBits = ceil(Util.log2(rangeMax))
	for digit in range(numBits - 1, - 1, - 1):
		var bit = value & (1 << digit)
		pushBit(bit)

func pushBitsize(value: int, numBits: int):
	for digit in range(numBits - 1, - 1, - 1):
		var bit = value & (1 << digit)
		pushBit(bit)


func pushBit(bit: int):
	bit = min(bit, 1)
	bits.push_back(bit)
	last_bit += 1



func pull(rangeMax: int) -> int:
	var numBits = ceil(Util.log2(rangeMax))
	var value = 0
	for digit in range(numBits - 1, - 1, - 1):
		if currentBit == last_bit:
			return - 1
		value += bits[currentBit] << digit
		currentBit += 1

	return value

func pullBitsize(numBits: int) -> int:
	var value = 0
	for digit in range(numBits - 1, - 1, - 1):
		if currentBit == last_bit:
			return - 1
		value += bits[currentBit] << digit
		currentBit += 1

	return value

func pprint():
	var string = ""
	for bit in bits:
		string += str(bit)
	return string

func toByteArray():
	var byteArray = PoolByteArray()
	var digitCount = 0
	var value = 0
	for bit in bits:
		digitCount += 1
		value = (value << 1) + int(bit)
		if digitCount == 8:
			digitCount = 0
			byteArray.append(value)
			value = 0
	if digitCount > 0:
		byteArray.append(value << (8 - digitCount))
	
	
	
	
	
	
	
	
	return byteArray
	
func fromByteArray(byteArray: PoolByteArray):
	bits.clear()
	last_bit = 0
	for byte in byteArray:
		for digit in range(7, - 1, - 1):
			pushBit(byte & (1 << digit))
	return self

func toGodotString_legacy() -> String:
	var string = ""
	var byteArray = toByteArray()
	for byte in byteArray:
		string += char(byte + 65)
	return string

func fromGodotString_legacy(string: String):
	var byteArray = PoolByteArray()
	for c in string:
		byteArray.push_back(ord(c) - 65)
	fromByteArray(byteArray)

const BASE64OFFSET = 62

func toGodotString() -> String:
	var byteArray = PoolByteArray()
	var digitCount = 0
	var value = 0
	for bit in bits:
		digitCount += 1
		value = (value << 1) + int(bit)
		if digitCount == 6:
			digitCount = 0
			byteArray.append(value + BASE64OFFSET)
			value = 0
	if digitCount > 0:
		byteArray.append((value << (6 - digitCount)) + BASE64OFFSET)
	
	return byteArray.get_string_from_ascii()


func fromGodotString(string: String):
	var byteArray = string.to_ascii()
	for byte in byteArray:
		var offsetByte = byte - BASE64OFFSET
		if offsetByte < 0 or offsetByte > 63:
			return false
		for digit in range(5, - 1, - 1):
			pushBit(offsetByte & (1 << digit))
	return true

func toUtf8() -> String:
	var byteArray = toByteArray()
	var file = File.new()
	file.open("user://score.dat", File.WRITE_READ)
	file.store_buffer(byteArray)
	var string = file.get_as_text(false)
	print("utf8: ", string)
	file.close()
	return string

func fromUtf8(utf8String: String):
	fromByteArray(utf8String.to_utf8())
	print("num bits after conversion: ", bits.size())
	
func toAsciiString() -> String:
	print("num bits before conversion: ", bits.size())
	var byteArray = toByteArray()
	print(byteArray)
	return byteArray.get_string_from_ascii()

func fromAsciiString(string: String):
	print("ascii: ", string)
	var byteArray = string.to_ascii()
	print("converted byte array: ", byteArray)
	fromByteArray(byteArray)
	print("num bits after conversion: ", bits.size())
	

func fromString(string):
	bits.clear()
	last_bit = 0
	for s in string:
		if s == "1":
			pushBit(1)
		else:
			pushBit(0)
