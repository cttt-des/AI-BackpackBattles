extends Dagger
var poison

func onPreDealDamage_early(damageRes: CoreDamageResult):
	if damageRes.hasHit():
		inflictPoison(poison)

func _readyInit():
	._readyInit()
	poison = int(getP1())
