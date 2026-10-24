extends Resource
class_name CharacterClass

export (int) var health = 30
export (int) var stamina = 5
export (int) var gold = 10
export (Array, Resource) var startingItems
export (Array, Resource) var startingItems2
export (Array, Resource) var startingItems3
export (PackedScene) var notUnlockedSprite
export (Color) var color

var sprite
var chibiSprite
var runStartSounds = []
var buySounds = []
var roundStartSounds = []
var winRoundSounds = []
var loseRoundSounds = []
var clickedSounds = []
var attackSounds = []
var damagedSounds = []
var battleRageSound = null

const spriteFormat = "res://CharacterClasses/{class}/{class}Sprite.tscn"
const chibiSpriteFormat = "res://CharacterClasses/{class}/{class}ChibiSprite.tscn"

func loadFiles(classIdentifier: String):
	loadSounds(classIdentifier)
	sprite = load(spriteFormat.format({"class": classIdentifier}))
	chibiSprite = load(chibiSpriteFormat.format({"class": classIdentifier}))

func loadSounds(classIdentifier: String):
	var dir = Directory.new()
	var directories = []
	var files = []
	var path = "res://Assets/Sound/" + classIdentifier
	if dir.open(path) == OK:
		dir.list_dir_begin(true, false)
		Util.addDirectoryContents(dir, files, directories)
		
		for fileName in files:
			
			if fileName.ends_with(".ogg.import"):
				fileName = fileName.trim_suffix(".import")
				if "StartRun" in fileName:
					runStartSounds.push_back(load(fileName))
				elif "Buy" in fileName:
					buySounds.push_back(load(fileName))
				elif "RoundStart" in fileName:
					roundStartSounds.push_back(load(fileName))
				elif "WinRound" in fileName:
					winRoundSounds.push_back(load(fileName))
				elif "LoseRound" in fileName:
					loseRoundSounds.push_back(load(fileName))
				elif "Clicked" in fileName:
					clickedSounds.push_back(load(fileName))
				
				
				elif "Attack" in fileName:
					attackSounds.push_back(load(fileName))
				elif "BattleRage" in fileName:
					battleRageSound = load(fileName)

func getRunStartSound():
	if runStartSounds.empty(): return null
	return Util.pickRandomElement(runStartSounds)

func getBuySound():
	if buySounds.empty(): return null
	return Util.pickRandomElement(buySounds)

func getRoundStartSound():
	if roundStartSounds.empty(): return null
	return Util.pickRandomElement(roundStartSounds)

func getWinRoundSound():
	if winRoundSounds.empty(): return null
	return Util.pickRandomElement(winRoundSounds)

func getLoseRoundSound():
	if loseRoundSounds.empty(): return null
	return Util.pickRandomElement(loseRoundSounds)

func getClickedSound():
	if clickedSounds.empty(): return null
	return Util.pickRandomElement(clickedSounds)

func getAttackSound():
	if attackSounds.empty(): return null
	return Util.pickRandomElement(attackSounds)

func getDamagedSound():
	if damagedSounds.empty(): return null
	return Util.pickRandomElement(damagedSounds)

func getStartingItems(loadout):
	if loadout == Game.Loadout.Loadout1:
		return startingItems
	elif loadout == Game.Loadout.Loadout2:
		return startingItems2
	else:
		return startingItems3

func getStartingBag(loadout) -> ItemDescriptor:
	var items = getStartingItems(loadout)
	return ItemBook.getDescriptor(items[0].itemName)
