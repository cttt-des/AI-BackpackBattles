extends Weapon

const pickupSound = preload("res://Assets/Sound/Water1.wav")
const dropSound = preload("res://Assets/Sound/Water2.wav")

onready var coldParticles = $Icon / ColdParticles
onready var distortion = $Distortion
onready var manaOnHit: = int(getP("mana"))
onready var bonusManaOnHit: = int(getP("mana2"))
onready var iceSpeed: = getP("speed") / 100.0
onready var bonusDam: = getP("dam")
onready var coldOnHit: = int(getP("cold"))

onready var manaNeeded1: = int(getP("manat1"))
onready var manaNeeded2: = int(getP("manat2"))
onready var manaNeeded3: = int(getP("manat3"))

var manaUsed: int
var activeEffects: = 0




func _ready():
	if ownerType == Owner.GridStorage:
		distortion.hide()
	else:
		distortion.show()

func canAffect(item):
	return item.hasType(Type.Nature)

func canAffect_secondary(item):
	return item.hasType(Type.Ice)

func onPrepare():
	connectForCombat(character(), "character_mana_changed", "onManaChanged")
	manaUsed = 0
	addSpeed(iceSpeed * getNumAffectedItems(Affected.Secondary))
	activeEffects = 0
	setState(activeEffects)

func onManaChanged(amount, event):
	if (amount < 0 and 
		event.type == Game.EventType.Mana and 
		event.getParam("used", false)):
		
		manaUsed += abs(amount)
		
		var before = activeEffects
		
		if activeEffects == 0 and manaUsed >= manaNeeded1:
			activeEffects = 1
		
		if activeEffects == 1 and manaUsed >= manaNeeded2:
			activeEffects = 2
			addBonusDamage(bonusDam)
		
		if activeEffects == 2 and manaUsed >= manaNeeded3:
			activeEffects = 3
		
		if before != activeEffects:
			setState(activeEffects)

func onDealtDamage(damageRes: DamageResult):
	if damageRes.hasHit():
		var mana = manaOnHit
		var chance = getChance() * getNumAffectedItems()
		if rollChance(chance):
			mana += bonusManaOnHit
		giveMana(mana, damageRes.event)
		
		if activeEffects >= 1:
			heal(getP_m("heal"), damageRes.event)
		if activeEffects == 3:
			inflictCold(coldOnHit, damageRes.event)

func onShopEntered():
	onStateChanged(0)

func onStateChanged(_activeEffects: int):
	activeEffects = _activeEffects
	if activeEffects == 3:
		coldParticles.activate()
	else:
		coldParticles.deactivate()


func getDescription(wrapInColor = true):
	var descr = .getDescription(wrapInColor)
	var colors = [Util.triggerColor, Util.triggerColor, Util.triggerColor]
	
	if placed:
		for i in activeEffects:
			colors[i] = Util.modifiedColor
	
	descr = getModeDescription(descr, colors, false, wrapInColor)
	return descr

func playPickupSound():
	Sound.playSound_process(pickupSound, - 4, Util.randPitch(0.1))

func playDropSound(volume = 0):
	volume += impactSoundVolume
	Sound.playSound(dropSound, volume - 4, Util.randPitch(0.1))
