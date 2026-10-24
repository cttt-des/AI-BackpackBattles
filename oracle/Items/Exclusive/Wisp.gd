extends Gem

const pickupSound = preload("res://Assets/Sound/Wisp1.wav")
const dropSound = preload("res://Assets/Sound/Wisp2.wav")
const gemColor = Color(0.783203, 0.972054, 1)

onready var luck: = int(getP("luck"))
onready var regen: = int(getP("regen"))
onready var natureSpeed: = getP("speed") / 100.0
onready var damageForSpikes: = int(getP("dam"))
onready var spikes: = int(getP("spikes"))

var damageAcc: int

func hasCooldown() -> bool:
	return (getGemMode() == GemMode.Inventory or 
			getGemMode() == GemMode.Armor)

func canAffect(item):
	return item.hasType(Type.Nature)

func prepareInventory():
	addSpeed(getNumAffectedItems() * natureSpeed)

func prepareWeapon():
	damageAcc = 0
	connectForCombat(socket.getItem(), "attacked", "onAttack")

func onAttack(damageRes: DamageResult):
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
	Sound.playSound_process(pickupSound, - 8, Util.randPitch(0.1))

func playDropSound(volume = 0):
	volume += impactSoundVolume
	Sound.playSound(dropSound, volume - 8, Util.randPitch(0.1))
