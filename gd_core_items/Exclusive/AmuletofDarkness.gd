extends Item
const amuletColor = Color(0.580392, 0.266667, 0.960784)
var damageAcc: int
var damageThreshold

func canAffect(item):
	return item.canActivate()


func onPrepare():
	damageAcc = 0
	connectForCombat(opponent(), "character_attacked", "onOpponentDamaged")
	
	for item in getAffectedItems():
		# ★ np51㊳终⑭ 触发面探针（GD_AODPROBE 门控，零 rng 消耗）
		if OS.get_environment("GD_AODPROBE") != "":
			print("[AOD-prep] affected=", String(item.descriptor.identifier))
		connectForCombat(item, "activated", "onItemActivated")


func onItemActivated(event):
	# ★ np51㊳终⑭ 触发面探针（GD_AODPROBE 门控，零 rng 消耗）
	if OS.get_environment("GD_AODPROBE") != "":
		print("[AOD-trig] t=", ctx.time)
	if OS.get_environment("GD_CHUPROBE") != "":
		ctx.rng.debug_flip_tag = "AOD t=" + str(ctx.time)
	if rollChance():
		var dam = descriptor.minDam
		var res = dealEffectDamage(dam)
		activate()


func onOpponentDamaged(damageRes: CoreDamageResult):
	if damageRes.hasHit() and damageRes.damageSource.isEffectDamage():
		damageAcc += damageRes.damage
		
		var proccs = damageAcc / damageThreshold
		if proccs > 0:
			damageAcc %= damageThreshold
			inflictRandomDebuffs(proccs)
			miniActivate()

func _readyInit():
	._readyInit()
	damageThreshold = int(getP("damt"))
	damageSource = CoreDamageSource.new().setItem(self)

