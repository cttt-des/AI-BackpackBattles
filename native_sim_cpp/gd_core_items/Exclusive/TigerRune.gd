extends Gem
const gemColor = Color(3, 2.501563, 0.8)
var buffCounter = 0
var vampChance
var vampirism
var buffsNeeded
var blockForBuffs

func canModifyChance() -> bool:
	return true


func prepareInventory():
	for item in inventory.getItemsAndGems():
		item.changeAmplificiationChancePercent_allBuffs(getChance())


func prepareWeapon():
	connectForCombat(socket.getItem(), "pre_deal_damage_late", "preAttack")


func preAttack(damageRes: CoreDamageResult):
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
	pass

func _readyInit():
	._readyInit()
	vampChance = getP("chance_vamp")
	vampirism = int(getP("vampirism"))
	buffsNeeded = int(getP("buffs"))
	blockForBuffs = int(getP("block"))
