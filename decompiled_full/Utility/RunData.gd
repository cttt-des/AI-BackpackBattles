extends Reference
class_name RunData

const NUM_PROPERTIES = 10
var corrupted = false
var runId
var encodedName: String
var rating: float
var playerId: String
var results: Array
var characterClass: int
var loadout: int
var rounds: Array
var entryVersion = ""
var chibiStyle: bool
var skins = []


var mmScore = 0.0

enum DeserializeResult{
	VERSION_TOO_NEW, 
	VERSION_TOO_OLD, 
	VERSION_OK
}

enum Validity{
	Ok, 
	Questionable, 
	Invalid, 
	TooManyUniques
}

func serialize():
	var data = [
		runId, 
		encodedName, 
		rating, 
		playerId, 
		results, 
		characterClass, 
		rounds, 
		entryVersion, 
		chibiStyle, 
		skins.duplicate()]
	if data.size() != NUM_PROPERTIES:
		print("!! serialization failed")
	return data

func fromSerialized(data: Array):
	
	if data.size() == NUM_PROPERTIES:
		if null in data:
			Util.eprint("found null in ", data)
			return - 1
		
		runId = data[0]
		encodedName = data[1]
		rating = data[2]
		playerId = data[3]
		results = data[4]
		characterClass = data[5]
		rounds = data[6]
		entryVersion = data[7]
		var res = checkVersion()
		
		if res == DeserializeResult.VERSION_OK:
			chibiStyle = data[8]
			skins = data[9]
			return 0
	
	return - 1

func checkVersion():
	if not Util.laterOrEqual(entryVersion, Game.leaderboardBreakingVersion):
		return DeserializeResult.VERSION_TOO_OLD
	if Util.later(entryVersion, Game.VERSION):
		return DeserializeResult.VERSION_TOO_NEW
	else:
		return DeserializeResult.VERSION_OK

func deserializeMetadata(string: String):
	var bitStream = BitStream.new()
	var res = bitStream.fromGodotString(string)
	if not res:
		Util.eassert(false)
		return DeserializeResult.VERSION_TOO_OLD
	
	entryVersion += String(bitStream.pull(4)) + "."
	entryVersion += String(bitStream.pull(16)) + "."
	entryVersion += String(bitStream.pull(64))
	var versionRes = checkVersion()
	
	if versionRes == DeserializeResult.VERSION_OK:
		for i in Game.getMaxNumberOfRounds():
			results.push_back(bitStream.pull(Game.RoundResult.size()))
		
		var withNewClasses = Util.laterOrEqual(entryVersion, "1.0.0")
		
		
		var data = deserializeCharacterData(bitStream, withNewClasses)
		characterClass = data[0]
		loadout = data[1]
		chibiStyle = data[2]
		skins = data[3]
		
		
		
		
		
	return versionRes

static func serializeCharacterData(addToBitstream: BitStream, 
	withNewClasses: bool) -> void :
	
	if withNewClasses:
		addToBitstream.push(Game.curClass, Game.Classes_Full.size())
	else:
		addToBitstream.push(Game.curClass, Game.Classes.size())
		
	var _loadout = Game.curLoadout
	if Game.randomCharacter:
		_loadout = Game.Loadout.RandomCharacter
	addToBitstream.push(_loadout, Game.Loadout.size())
	
	addToBitstream.push(int(Game.getChibiMode()), 2)
	for slot in Game.SkinSlot.size():
		addToBitstream.push(Game.getSelectedSkin(slot), SkinBook.MAX_SKINS)

static func deserializeCharacterData(bitStream, withNewClasses: bool):
	var _characterClass
	if withNewClasses:
		_characterClass = bitStream.pull(Game.Classes_Full.size())
	else:
		_characterClass = bitStream.pull(Game.Classes.size())
	var _loadout = bitStream.pull(Game.Loadout.size())
	var _chibi = bool(bitStream.pull(2))
	var _skins = []
	for slot in Game.SkinSlot.size():
		_skins.push_back(bitStream.pull(SkinBook.MAX_SKINS))
	
	return [_characterClass, _loadout, _chibi, _skins]


const dictIndex = ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17"]

func parseRounds(wholeRun: Dictionary):
	for index in dictIndex:
		if index in wholeRun:
			rounds.push_back(wholeRun[index])
		else:
			break

func deserializeRound(roundIndex):
	return createRoundDict(rounds[roundIndex - 1], characterClass, 
		loadout, encodedName, chibiStyle, skins.duplicate(), entryVersion)

func deserializeItemsOfRound(roundIndex):
	return deserializeItems(rounds[roundIndex - 1], entryVersion)

static func deserializeItems(metadataString: String, version):
	var bitStream = BitStream.new()
	var res = bitStream.fromGodotString(metadataString)
	if not res:
		if Game.EDITOR:
			assert (false)
		return null
	
	return deserializeStream(bitStream, version)

func getDecodedName() -> String:
	return Util.sharedBitstream.deserializeString(encodedName)

static func createRoundDict(metadataString: String, 
	_characterClass, _loadout, _name, _chibiStyle, _skins, 
	version, nameIsEncoded: bool = true):
	
	var roundData = deserializeItems(metadataString, version)
	if roundData == null:
		return null
	
	if roundData:
		roundData["class"] = _characterClass
		roundData["loadout"] = _loadout
		var decodedName
		if nameIsEncoded:
			decodedName = Util.sharedBitstream.deserializeString(_name)
		else:
			decodedName = _name
		roundData["name"] = Game.limitName(decodedName)
		roundData["chibi"] = _chibiStyle
		roundData["skins"] = _skins
	return roundData
	
static func deserializeStream(bitStream: BitStream, version):
	
	var roundData = Dictionary()
	
	var health = bitStream.pull(Game.MAX_HEALTH)
	if health == - 1:
		return null
	roundData["health"] = health
	
	var stamina = bitStream.pull(Game.MAX_STAMINA)
	if stamina == - 1:
		return null
	roundData["stamina"] = stamina
	
	var totalNumItems: int
	
	if Util.laterOrEqual(version, "1.1.0"):
		totalNumItems = ItemBook.getNumItems()
	else:
		totalNumItems = 510
	
	var itemTuples = []
	while bitStream.bitsLeft() >= 8:
		var index = bitStream.pull(totalNumItems)
		if index >= totalNumItems or index == - 1:
			if Game.EDITOR:
				Util.eprint("Invalid item index ", index)
			return null
		
		var descriptor = ItemBook.getDescriptorFromIndex(index)
		
		if not descriptor.scene:
			if Game.EDITOR:
				Util.eprint("Invalid item (no scene) ", descriptor.getName())
			return null
		
		var topLeftCellPos = Vector2(
			bitStream.pull(Game.PLAYER.INVENTORY.MAX_SIZE.x), 
			bitStream.pull(Game.PLAYER.INVENTORY.MAX_SIZE.y))
		var faceDirection: int = bitStream.pull(4)
		
		if topLeftCellPos.x < 0 or topLeftCellPos.y < 0 or faceDirection < 0:
			return null
		
		var itemData: = {}
		itemData["d"] = descriptor
		itemData["c"] = topLeftCellPos
		itemData["f"] = faceDirection
		
		var numSockets = ItemBook.getNumSockets(index)
		if numSockets > 0:
			var hasGems = bitStream.pull(2)
			if hasGems == 1:
				var gems = []
				for socketI in numSockets:
					var gemIndex = bitStream.pull(RunDatabase.totalNumGems)
					if gemIndex >= ItemBook.getNumGems() and gemIndex != RunDatabase.emptySocketId:
						return null
					gems.push_back(gemIndex)
		
				itemData["g"] = gems
		
		var instance = Game.itemLibrary.getInstance(descriptor)
		if instance.has_method("getDataPersistent"):
			var numBits = instance.getDataPersistentBits()
			
			var dataAsInt = bitStream.pullBitsize(numBits)
			var bitStream2 = BitStream.new()
			bitStream2.pushBitsize(dataAsInt, numBits)
			itemData["pd"] = bitStream2.toGodotString()
			
		
		itemTuples.push_back(itemData)
		
	roundData["items"] = itemTuples
	
	return roundData

func getNumRounds() -> int:
	return rounds.size()


func getWinsAtRound(roundNum: int) -> int:
	var wins = 0
	for roundI in roundNum:
		if results[roundI] == Game.RoundResult.Win:
			wins += 1
	return wins

func getRoundResult(roundNum: int) -> int:
	return results[roundNum - 1]


func countItems(untilRound):
	var itemCounter: = []
	itemCounter.resize(ItemBook.getNumItems())
	itemCounter.fill(0)
	for roundI in untilRound:
		var roundData = deserializeRound(roundI)
		if roundData == null:
			return null
		for itemData in roundData["items"]:
			itemCounter[itemData["d"].itemIndex] += 1
	return itemCounter

func countDescriptor(itemDataArray, descriptor):
	var num = 0
	for itemData in itemDataArray:
		if itemData["d"] == descriptor:
			num += 1
	
	return num


const GOLD_SUS_FACTOR1 = 0.9
const GOLD_SUS_FACTOR2 = 1.1
const GOLD_SUS_FACTOR3 = 1.25
const GOLD_INVALID_FACTOR = 1.3
const GOLD_LOW_FACTOR = 0.5
var inventoryPrice = 0
var goldInRound = 0


const raritiesPerRound = [
	[0, 0, 0], 
	[1, 0, 0], 
	[2, 0, 0], 
	[99, 1, 0], 
	[99, 2, 0], 
	[99, 99, 1], 
	[99, 99, 2], 
]


func isValid(currentRound: int):
	var validity = Validity.Ok
	var numQuestionable = 0
	
	
	for roundNum in range(1, getNumRounds() + 1):
		var validity2 = isRoundValid(roundNum, currentRound)
		if validity2 == Validity.Invalid:
			Util.eprint("Run invalid 1")
			return Validity.Invalid
		elif validity2 == Validity.Questionable:
			if roundNum == currentRound:
				Util.eprint("Run invalid 2")
				return Validity.Invalid
			numQuestionable += 1


	
	var questionableRate = numQuestionable / float(getNumRounds())
	Util.eprint("questionableRate: ", questionableRate)
	if questionableRate > 0.3:
		Util.eprint("Run invalid 3")
		return Validity.Invalid
	
	return validity

func isAvailableForClassOrAppropriated(descriptor, itemCounter) -> bool:
	if descriptor.isAvailableFor(characterClass):
		return true
	else:
		
		for item in descriptor.appropriatingItems:
			if itemCounter[item.itemIndex] != 0:
				return true
	return false

func isRoundValid(roundNum: int, currentRound: int):
	var validity = Validity.Ok
	
	if not Game.isClassUnlocked(characterClass):
		Util.eprint("Encountered sus run. 5")
		return Validity.Invalid
	
	var roundData = deserializeRound(roundNum)
	
	if not roundData:
		Util.eprint("Encountered sus run. 6")
		return Validity.Invalid
	
	if roundData["health"] != Game.getMaxHealthInRound(roundData["class"], roundNum):
		Util.eprint("Encountered sus run. 1")
		
		return Validity.Invalid
	
	
	if roundData["stamina"] > 20:
		Util.eprint("Encountered sus run. 2")
		return Validity.Invalid
	
	
	var numUniques = 0
	var uniqueLimit = 1
	uniqueLimit += countDescriptor(roundData["items"], ItemBook.platinCardDescriptor)
	uniqueLimit += countDescriptor(roundData["items"], ItemBook.uniquelyUniqueDescriptor) * ItemBook.uniquelyUniqueDescriptor.getP("uniquest")
	var ownUniques = ItemBook.getNumInventoryUniques()
	var numSubclassUniques = 0
	var bonusStamina = 0
	var numRarity = [0, 0, 0]
	
	var itemCounter = countItems(roundNum)
	if itemCounter == null:
		Util.eprint("Encountered sus run. 11")
		return Validity.Invalid
	
	inventoryPrice = 0
	for itemTuple in roundData["items"]:
		var descriptor = itemTuple["d"]
		if not isAvailableForClassOrAppropriated(descriptor, itemCounter):
			
			Util.eprint(descriptor.getName(), " illegal for class ", Game.getClassName(characterClass))
			Util.eprint("Encountered sus run. 4")
			return Validity.Invalid
		
		if descriptor.canOnlyExistOnce():
			if countDescriptor(roundData["items"], descriptor) > 1:
				Util.eprint("Encountered sus run. 9")
				return Validity.Invalid
		
		if descriptor.getRarity() == Item.Rarity.Unique:
			if countDescriptor(roundData["items"], descriptor) > 1:
				Util.eprint("Encountered sus run. 9b")
				return Validity.Invalid
		
		if not Game.BETA:
			if descriptor.randomUniquePool:
				numUniques += 1
				if numUniques > uniqueLimit:
					Util.eprint("Encountered sus run. 7")
					return Validity.Invalid
				elif currentRound == roundNum:
					if numUniques >= 1 and ownUniques == 0 and Util.flip(0.5):
						Util.eprint("Encountered sus run. 7c")
						validity = Validity.Questionable
		
		if descriptor.isSubclassItem():
			numSubclassUniques += 1
			
			if numSubclassUniques > 0 and roundNum < Game.SUBCLASS_ROUND:
				Util.eprint("Encountered sus run. 12")
				return Validity.Invalid
			elif numSubclassUniques > 1:
				Util.eprint("Encountered sus run. 12b")
				return Validity.Invalid
		
		if ((descriptor.rarity == Item.Rarity.Epic or 
			descriptor.rarity == Item.Rarity.Legendary or 
			descriptor.rarity == Item.Rarity.Godly) and 
			roundNum < raritiesPerRound.size()):
			
			
			var offsetRarity = descriptor.rarity - Item.Rarity.Epic
			numRarity[offsetRarity] += 1
		
		if descriptor.identifier == "Stamina Sack":
			bonusStamina += 1
		
		inventoryPrice += descriptor.price
	
		if "g" in itemTuple:
			for gemIndex in itemTuple["g"]:
				if gemIndex >= ItemBook.getNumGems() and gemIndex != RunDatabase.emptySocketId:
					Util.eprint("Encountered sus run. 13")
					return Validity.Invalid
				if gemIndex != RunDatabase.emptySocketId:
					var gemDescriptor = ItemBook.getGemForIndex(gemIndex)
					if not isAvailableForClassOrAppropriated(gemDescriptor, itemCounter):
						Util.eprint("Encountered sus run. 4g")
						return Validity.Invalid
					if gemDescriptor.randomUniquePool:
						numUniques += 1
						if numUniques > uniqueLimit:
							Util.eprint("Encountered sus run. 7b")
							return Validity.Invalid
						elif numUniques == 1 and ownUniques == 0:
							if Util.flip(0.6):
								validity = Validity.TooManyUniques
					inventoryPrice += gemDescriptor.price
	
	goldInRound = 0
	goldInRound = Game.getGainedGold(roundData["class"], roundNum)
	
	if roundNum == 1:
		goldInRound *= GOLD_SUS_FACTOR1
	elif roundNum <= 3:
		goldInRound *= GOLD_SUS_FACTOR2
	else:
		goldInRound *= GOLD_SUS_FACTOR3
		
	
	
	
	if loadout == Game.Loadout.RandomLoadout or Game.Loadout.RandomCharacter:
		goldInRound += max(Game.getStartInventoryPrice(roundData["class"], Game.Loadout.Loadout1), 
									Game.getStartInventoryPrice(roundData["class"], Game.Loadout.Loadout2))
		goldInRound += 2
		
	else:
		goldInRound += Game.getStartInventoryPrice(roundData["class"], loadout)
	
	var lowerBound = goldInRound * GOLD_LOW_FACTOR
	var upperBound = goldInRound * GOLD_INVALID_FACTOR
	
	
	goldInRound = floor(goldInRound)
	
	
	if inventoryPrice > upperBound:
		Util.eprint("Encountered sus run. 3c round ", currentRound)
		return Validity.Invalid
	if inventoryPrice > goldInRound:
		Util.eprint("Encountered sus run. 3")
		validity = Validity.Questionable
	elif inventoryPrice < lowerBound:
		Util.eprint("Encountered sus run. 3b")
		validity = Validity.Questionable
	
	if roundNum < raritiesPerRound.size():
		for rarity in raritiesPerRound[0].size():
			if numRarity[rarity] > raritiesPerRound[roundNum - 1][rarity]:
				Util.eprint("Encountered sus run. 10 in round " + String(roundNum))
				validity = Validity.Questionable
	
	
	
	if 5 + bonusStamina != roundData["stamina"]:
		Util.eprint("Encountered sus run. 2b")
		
		
		return Validity.Invalid
	
	return validity
	






func fromSilentWolfScore(score: Dictionary):
	for field in swFields:
		if not field in score.metadata:
			Util.eprint("no field ", field)
			return DeserializeResult.VERSION_TOO_OLD
				
	runId = score.score_id
	return fromData(score.player_name, score.metadata)
	
func fromSteamScore(dict: Dictionary, lobbyMode: bool):
	if not lobbyMode:
		for field in steamFields:
			if not field in dict:
				Util.eprint("no field ", field)
				return DeserializeResult.VERSION_TOO_OLD
	
	runId = dict["ugc"]
	return fromData(dict["p"], dict, lobbyMode)

const VERSION_FIELD = "d"
const sharedFields = [VERSION_FIELD, "r", "id", "0", "1", "2", "3", "4"]
const swFields = sharedFields
const steamFields = sharedFields + ["ugc", "p"]


func fromData(playername, run: Dictionary, lobbyMode: bool = false):
	encodedName = playername
	
	var metaData = run.get(VERSION_FIELD)
	if not metaData:
		return DeserializeResult.VERSION_TOO_OLD
	
	var res = deserializeMetadata(metaData)
	if res != DeserializeResult.VERSION_OK:
		return res
	
	rating = run.get("r", - 1000)
	
	playerId = run.get("id", "")
	
	parseRounds(run)
	
	return DeserializeResult.VERSION_OK
