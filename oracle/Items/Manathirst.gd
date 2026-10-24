extends Weapon

onready var filling = $Icon / ManathirstInner
onready var fillingGlow = $Icon / ManathirstInnerGlow
onready var fillingHeight = filling.texture.get_size().y
onready var fillingAnimation = $LifestealAnimation
onready var manaNeededForLifesteal = getP1()
onready var dam: = getP("dam")
onready var mana: = int(getP("mana"))


var manaGained: int
var fillingTween

func onPrepare():
	manaGained = 0
	
	connectForCombat(character(), "character_mana_changed", "onManaChanged")
	tweenFilling(0)

func tweenFilling(relHeight: float):
	var height = fillingHeight * relHeight
	Util.killTween(fillingTween)
	fillingTween = create_tween().set_parallel()
	fillingTween.tween_property(filling, "region_rect:size:y", height, 0.2)
	fillingTween.tween_property(filling, "region_rect:position:y", fillingHeight - height, 0.2)
	fillingTween.tween_property(fillingGlow, "region_rect:size:y", height, 0.2)
	fillingTween.tween_property(fillingGlow, "region_rect:position:y", fillingHeight - height, 0.2)

func onManaChanged(amount, event):
	if amount > 0:
		manaGained += amount
		if manaGained >= manaNeededForLifesteal:
			manaGained -= manaNeededForLifesteal
			stealLife(dam + character().getVampirism(), getP_m("lifesteal") / 100.0, event)
			fillingAnimation.play("StealLife")
		
		var relHeight = manaGained / manaNeededForLifesteal
		tweenFilling(relHeight)

func onDealtDamage(damageRes: DamageResult):
	if damageRes.hasHit():
		giveMana(mana, damageRes.event)

func onShopEntered():
	tweenFilling(1)
