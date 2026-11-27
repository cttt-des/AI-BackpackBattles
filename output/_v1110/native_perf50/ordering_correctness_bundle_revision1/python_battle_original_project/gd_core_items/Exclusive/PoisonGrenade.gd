extends Item
var poisonCritActive: bool
var tween: SceneTreeTween
var poison
var selfPoison
var cdAdvance
var luckNeeded
var light
var lightAni

func onPrepare():
	setState(false)
	
	connectForCombat(character(), "character_lucky_changed", "onLuckChanged")
	

func doCooldownEffect():
	inflictPoison(poison)
	selfInflictPoison(selfPoison)
	onAfterEffectFinished()
	


func onChargeReceived(_charge):
	advanceCooldownSeconds(cdAdvance)
	miniActivate()


func onLuckChanged(amount, event):
	if amount > 0 and not poisonCritActive and character().getLucky() >= luckNeeded:
		opponent().changePoisonCritChancePercent(getChance())
		setState(true)
	
	elif amount < 0 and poisonCritActive and character().getLucky() < luckNeeded:
		opponent().changePoisonCritChancePercent( - getChance())
		setState(false)


func onShopEntered():
	pass

func onStateChanged(_poisonCritActive):
	poisonCritActive = _poisonCritActive
	if poisonCritActive:
		pass
		
	else:
		pass
		

func _readyInit():
	._readyInit()
	poison = int(getP("poison"))
	selfPoison = int(getP("poison2"))
	cdAdvance = getP("cdadvance")
	luckNeeded = int(getP("luckt"))
