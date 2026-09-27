extends Weapon
var manaGained: int
var fillingTween
var filling
var fillingGlow
var fillingHeight
var fillingAnimation
var manaNeededForLifesteal
var dam
var mana

func onPrepare():
	manaGained = 0
	
	connectForCombat(character(), "character_mana_changed", "onManaChanged")
	tweenFilling(0)


func tweenFilling(relHeight: float):
	pass

func onManaChanged(amount, event):
	if amount > 0:
		manaGained += amount
		if manaGained >= manaNeededForLifesteal:
			manaGained -= manaNeededForLifesteal
			stealLife(dam + character().getVampirism(), getP_m("lifesteal") / 100.0, event)
		
		var relHeight = manaGained / manaNeededForLifesteal
		tweenFilling(relHeight)


func onDealtDamage(damageRes: CoreDamageResult):
	if damageRes.hasHit():
		giveMana(mana, damageRes.event)


func onShopEntered():
	tweenFilling(1)

func _readyInit():
	._readyInit()
	manaNeededForLifesteal = getP1()
	dam = getP("dam")
	mana = int(getP("mana"))
