extends Gem

const gemColor = Color(3, 2.501563, 0.8)

onready var vampChance: = getP("chance_vamp")
onready var vampirism: = int(getP("vampirism"))
onready var buffsNeeded: = int(getP("buffs"))
onready var blockForBuffs: = int(getP("block"))
var buffCounter = 0

func canModifyChance() -> bool:
	return true

func prepareInventory():
	for item in inventory.getItemsAndGems():
		item.changeAmplificiationChancePercent_allBuffs(getChance())

func prepareWeapon():
	connectForCombat(socket.getItem(), "pre_deal_damage_late", "preAttack")

func preAttack(damageRes: DamageResult):
	if damageRes.hasHit() and rollChance(vampChance):
		giveVampirism(vampirism)
		miniActivate()

func prepareArmor():
	buffCounter = 0
	connectToCharacterBuffs("onBuffsChanged")

func onBuffsChanged(amount, event):
	if amount > 0:
		buffCounter += amount
		var relBuffs = buffCounter / buffsNeeded
		var block = relBuffs * blockForBuffs
		buffCounter %= buffsNeeded
		if block > 0:
			giveBlock(getGemPower() * block, event)
			showCooldownSmooth(relBuffs, true)
		else:
			showCooldownSmooth(relBuffs, false)

func onHotSwapHoverWithGemEnd():
	gemAnimation.play("RuneShine")
