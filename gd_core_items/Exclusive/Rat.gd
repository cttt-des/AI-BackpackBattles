extends "res://gd_core_items/Exclusive/ForestFriend.gd"
var poison: int
var blind: int

func initRat():
	damageSource = CoreDamageSource.new().setItem(self)
	poison = int(getP("poison"))
	blind = int(getP("blind"))


func doCooldownEffect():
	var dam = descriptor.minDam
	var res = dealEffectDamage(dam)
	if rollChance():
		inflictPoison(poison, res.event)
	if rollChance2():
		inflictBlind(blind, res.event)
		
	activate(res)


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
	initRat()

