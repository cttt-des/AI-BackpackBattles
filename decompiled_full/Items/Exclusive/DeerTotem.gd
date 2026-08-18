extends Item

onready var normalTex = sprite.texture
const activeTex = preload("res://Items/Exclusive/Sprites/DeerTotem_active.png")

func canAffect(item):
	return item.hasType(Type.Nature)

func onPrepare():
	setState(false)
	character().changeDamageResistance(getP1())
	
	var numNatureItems = getNumAffectedItems()
	character().addBattleRageDuration(getP_m("dur_rage") * numNatureItems)
	
	connectForCombat(character(), "battle_rage_started", "onBattleRageStarted")
	connectForCombat(character(), "battle_rage_ended", "onBattleRageEnded")

func preCombatStart():
	.preCombatStart()
	deactivateCooldown()

func onBattleRageStarted(_event):
	setState(true)
	activateCooldown()

func onBattleRageEnded(_event):
	setState(false)
	deactivateCooldown()

func doCooldownEffect():
	heal()
	giveMana(getP4())
	
	activate()

func onShopEntered():
	onStateChanged(false)

func onStateChanged(active):
	if active:
		setTexture(activeTex)
	else:
		setTexture(normalTex)
		
func getTriggerPriority() -> int:
	return Priority.Highest
