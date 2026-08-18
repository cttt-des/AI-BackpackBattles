extends Item

const activationPulse = preload("res://Items/Particles/ManaOrbActivationPulse.tscn")

var stackTypes: Array
var activated: bool
var bonusBuffs: int

onready var mana: = int(getP1())
onready var manaNeeded: int = getP2()
onready var buffs: = int(getP3())
onready var light = $Icon / ManaOrbGlow

func _ready():
	stackTypes = Game.getBuffs()
	stackTypes.erase(Game.EventType.Mana)
	
func canAffect(item):
	return item.canActivate()

func onPrepare():
	bonusBuffs = 0
	setState(false)
	for item in getAffectedItems():
		connectForCombat(item, "activated", "onItemActivated")
	connectForCombat(character(), "character_mana_changed", "onManaChanged")

func onItemActivated(event):
	if rollChance():
		miniActivate()
		giveMana(mana)

func onManaChanged(amount, triggerEvent):
	if not activated and amount > 0 and character().getMana() >= manaNeeded:
		setState(true)
		var event = useMana(manaNeeded, triggerEvent)
		giveRandomBuffs(buffs + bonusBuffs, event, stackTypes)
		activate()
		var pulse = ObjectPool.instance(activationPulse)
		add_child(pulse)
		var ani = pulse.get_node("AnimationPlayer")
		ani.play("Activate")
		

func onShopEntered():
	onStateChanged(false)

func addBonusRandomBuffs(amount: int):
	bonusBuffs += amount

func onStateChanged(_activated: bool):
	activated = _activated
	light.visible = not activated
