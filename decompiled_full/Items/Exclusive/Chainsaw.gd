extends Weapon

const sawFrames = [
	preload("res://Items/Exclusive/Sprites/Chainsaw0.png"), 
	preload("res://Items/Exclusive/Sprites/Chainsaw1.png"), 
	preload("res://Items/Exclusive/Sprites/Chainsaw2.png"), 
	preload("res://Items/Exclusive/Sprites/Chainsaw3.png")
]

const pickupSound = preload("res://Assets/Sound/Chainsaw.ogg")
const sawSpeed: = 8.0

onready var removeBuffs: = getP("buffs") / 100.0
onready var slowdown: = getP("slow") / 100.0
onready var sawAnimation = $Icon / AnimationPlayer

var sawFrame = 0
var sawTween: SceneTreeTween

func onPrepare():
	setState(false)

func onPreDealDamage_early(damageRes: DamageResult):
	if damageRes.hasHit():
		if numCharges > 0:
			stealBuffsFraction(removeBuffs, 1000)
		else:
			removeBuffsFraction(removeBuffs, 1000)
		
		reduceSpeed(slowdown)

func pickup(pickupType = PickupType.Grabbed):
	.pickup(pickupType)
	sawAnimation.play("Saw")
	sawTween = Util.refreshTween(sawTween)
	sawTween.tween_property(sawAnimation, "playback_speed", sawSpeed, 0.5).from(0.0)

func drop():
	var res = .drop()
	sawTween = Util.refreshTween(sawTween)
	sawTween.tween_property(sawAnimation, "playback_speed", 0.0, 1.0)
	sawTween.tween_callback(sawAnimation, "stop")
	
	return res

func setSawTexture():
	sawFrame += 1
	sawFrame %= 4
	sprite.texture = sawFrames[sawFrame]
	updateShadowTexture()

func onChargeReceived(_charge):
	if numCharges == 1:
		setState(true)
		playPickupSound()

func onChargeLeft(_charge):
	if numCharges == 0:
		setState(false)

func onShopEntered():
	onStateChanged(false)

func onStateChanged(charged):
	if charged:
		sawAnimation.play("Saw")
		sawAnimation.playback_speed = sawSpeed
	else:
		sawAnimation.stop()

func playPickupSound():
	Sound.playSound(pickupSound, 0, Util.randPitch(0.1) + 0.1)
