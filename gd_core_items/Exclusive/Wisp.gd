extends Gem
const gemColor = Color(0.783203, 0.972054, 1)
var damageAcc: int
var luck
var regen
var natureSpeed
var damageForSpikes
var spikes

func hasCooldown() -> bool:
	return (getGemMode() == GemMode.Inventory or 
			getGemMode() == GemMode.Armor)


func canAffect(item):
	return item.hasType(CoreConst.Type.Nature)


func prepareInventory():
	addSpeed(getNumAffectedItems() * natureSpeed)


func prepareWeapon():
	damageAcc = 0
	connectForCombat(socket.getItem(), "attacked", "onAttack")


func onAttack(damageRes: CoreDamageResult):
	if damageRes.hasHit():
		damageAcc += damageRes.damage
		var numProccs = damageAcc / damageForSpikes
		if numProccs > 0:
			damageAcc %= damageForSpikes
			giveSpikes(spikes * numProccs)
			miniActivate()


func combatStart():
	match getGemMode():
		GemMode.Inventory:
			baseCooldownOverride = getBaseCooldownIndex(0)
		GemMode.Armor:
			baseCooldownOverride = getBaseCooldownIndex(1)
	.combatStart()


func doCooldownEffect():
	match getGemMode():
		GemMode.Inventory:
			giveLucky(luck)
			giveRegeneration(regen)
			onAfterEffectFinished()
			
		GemMode.Armor:
			var bonusHealth = getP_m("maxhealth") / 100.0 * character().getCurrentHealth()
			bonusHealth *= getGemPower()
			giveMaxHealth(bonusHealth)
			onAfterEffectFinished(false)
			consumed = true
			miniActivate()


func playPickupSound():
	pass


func playDropSound(volume = 0):
	volume += impactSoundVolume

func _readyInit():
	._readyInit()
	luck = int(getP("luck"))
	regen = int(getP("regen"))
	natureSpeed = getP("speed") / 100.0
	damageForSpikes = int(getP("dam"))
	spikes = int(getP("spikes"))
