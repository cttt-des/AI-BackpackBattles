extends Item
var poison
var luckPerPet

func canAffect(item):
	return item.hasType(CoreConst.Type.Pet)


func onPrepare():
	connectForCombat(character(), "character_lucky_changed", "onLuckyChanged")


func onCombatStart():
	var numPets = getNumAffectedItems()
	giveLucky(numPets * luckPerPet)
	giveMaxHealth(numPets * getP_m("maxhealth"))
	activate()


func onLuckyChanged(amount, event):
	var protectChance = amount * getChance()
	opponent().changeProtectionChance(CoreConst.EventType.Poison, protectChance)


func doCooldownEffect():
	inflictPoison(poison)
	activate()


func playPickupSound():
	# ★ np24：音高抽=无日志裸抽——oracle 原版此行=Util.rng.randf_range 直连
	#   （不经 rng_trace 包装 ⇒ 不落 rng_log），gd 误译为记帐版 ctx.rng（多记）。
	#   run576_r14 首支断点（Snake 激活音高 #215 多一行，+67 pitch 族的实证点）。
	ctx.rng.rng.randf_range(0.9, 1.1)


func playDropSound(volume = 0):
	volume += impactSoundVolume
	# ★ np24：音高抽=无日志裸抽——oracle 原版此行=Util.rng.randf_range 直连
	#   （不经 rng_trace 包装 ⇒ 不落 rng_log），gd 误译为记帐版 ctx.rng（多记）。
	#   run576_r14 首支断点（Snake 激活音高 #215 多一行，+67 pitch 族的实证点）。
	ctx.rng.rng.randf_range(0.9, 1.1)






































func _readyInit():
	._readyInit()
	poison = getP("poison")
	luckPerPet = getP("luck")
