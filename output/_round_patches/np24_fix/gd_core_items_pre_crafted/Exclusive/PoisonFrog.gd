extends Item
var affectedItemsDict: Dictionary
var gainedBuffs: int
var usedBuffs: int
var gainedThreshold: int
var usedThreshold: int
var poison
var mana

func canAffect(item):
	return item.gainsBuffs() or item.usesBuffs()


func onPrepare():
	affectedItemsDict.clear()
	for item in getAffectedItems():
		affectedItemsDict[item] = true
	connectToCharacterBuffs("onBuffsChanged")
	gainedBuffs = 0
	usedBuffs = 0
	

func onBuffsChanged(amount, event):
	if event.getOrigin() in affectedItemsDict:
		if amount > 0:
			gainedBuffs += amount
			var ticks = gainedBuffs / gainedThreshold
			if ticks > 0:
				heal()
				
				
				gainedBuffs %= gainedThreshold
				miniActivate()
				
		else:
			
			usedBuffs += int(abs(amount))
			var ticks = usedBuffs / usedThreshold
			if ticks > 0:
				inflictPoison(ticks * poison, event)
				giveMana(ticks * mana, event)
				usedBuffs %= usedThreshold
				miniActivate()


func doCooldownEffect():
	inflictPoison(getP("poison2"))
	giveMana(getP("mana2"))
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
	gainedThreshold = getP("gained")
	usedThreshold = getP("used")
	poison = int(getP("poison"))
	mana = int(getP("mana"))
