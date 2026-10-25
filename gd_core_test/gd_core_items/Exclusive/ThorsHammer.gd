extends Weapon
var effectDmgSource
var manaNeeded
var effectDmg
var blind

func onDealtDamage(damageRes: CoreDamageResult):
	if damageRes.hasHit():
		if rollChance():
			stun(getP_m("dur_stun"), damageRes.event)
		
		if character().getMana() >= manaNeeded:
			var event = useMana(manaNeeded, damageRes.event)
			dealEffectDamage(effectDmg, event, effectDmgSource)
			var duration = getP_m("dur_blind")
			giveStacksTemporary(opponent(), CoreConst.EventType.Blind, 
				blind, duration, event)

func _readyInit():
	._readyInit()
	manaNeeded = int(getP("manat"))
	effectDmg = int(getP("dam"))
	blind = int(getP("blind"))
	effectDmgSource = CoreDamageSource.new().init(self, 
		CoreDamageSource.Type.Effect, effectDmg)

