extends Item

onready var poison: = int(getP("poison"))
onready var selfPoison: = int(getP("poison2"))
onready var cdAdvance: = getP("cdadvance")
onready var luckNeeded: = int(getP("luckt"))
onready var light = $Icon / Light
onready var lightAni = $Icon / AnimationPlayer

var poisonCritActive: bool
var tween: SceneTreeTween

func onPrepare():
	lightAni.stop()
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
	
	onStateChanged(false)
	Util.callDelayed(lightAni, "play", 0.2, ["Idle"])

func onStateChanged(_poisonCritActive):
	poisonCritActive = _poisonCritActive
	tween = Util.refreshTween(tween)
	if poisonCritActive:
		tween.tween_property(light, "self_modulate:a", 0.15, 0.1)
		
	else:
		tween.tween_property(light, "self_modulate:a", 0.0, 0.2)
		
