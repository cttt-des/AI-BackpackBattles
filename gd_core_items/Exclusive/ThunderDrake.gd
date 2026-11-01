extends Weapon
var active: bool
var curHitCount: int
var lightningMultiplicity: Dictionary
var numHits
var buffSpeed
var buffTimer
var buffParticles

func canAffect_lightning(item):
	return item.hasCooldown() or item.reactsToCharges()


func onPrepare():
	setState(false)
	curHitCount = 0
	lightningMultiplicity = countItemsInAffectedCells_cached(CoreConst.Affected.Lightning)


func onDealtDamage(damageRes: CoreDamageResult):
	if damageRes.hasHit():
		curHitCount += 1
		
		if curHitCount == numHits:
			
			
			if active:
				for item in _lightningOrdered():
					item.chargeLeft(self)
					zapItem(item)
			else:
				setState(true)
				for item in _lightningOrdered():
					item.addSpeed(buffSpeed * lightningMultiplicity[item])
					zapItem(item)
				
			buffTimer.stop()
			buffTimer.start(getP_m("dur"))
			curHitCount = 0


# ★ np31W2：TD 的 Lightning 受影响循环序=tile_data 静态涂色序（x 分组升、
#   组内 y 降）——1097 fAffC oracle 实测；TD 是全场唯一 Lightning 色遍历者，
#   局部排序副本零全局风险（全局按色分曾致 -62 退步已回滚 9c447568）。
func _lightningOrdered():
	var arr = getAffectedItems(CoreConst.Affected.Lightning)
	arr.sort_custom(CoreUtil, "vec2_tile_data")
	return arr


func zapItem(item):
	item.chargeReceived(self)
	if item.hasOnChargeReceivedEffect:
		# ★ np27 破案（EVENT state 哨兵+GCOIL/ZDBG 双桩，run1102_r13）：原版此处
		#   ObjectPool.instance(Util.zapScene)+zap.zap(...) → Zap.gd:32 的
		#   randf_range(4.0,4.02)（1 抽=2 步）——转写剥表现层时把 rng 消耗一并
		#   剥掉：oracle 偷1(Coil×2 层 106) 后 zap 2 步（-8602→7014，PCG 全链
		#   自洽）→ 偷2 pick(2,1)；gd 无 zap → 偷2 pick(3,0) → 偷栈类型分叉
		#   （语料 106/105/104 v gd 106/106/101）。补消耗（表现层照剥）。
		ctx.rng.randf_range(4.0, 4.02)
		var targetPos = item.getGlobalCenter()


func onBuffEnded():
	setState(false)
	
	for item in _lightningOrdered():
		item.reduceSpeed(buffSpeed * lightningMultiplicity[item])
		item.chargeLeft(self)


func onCombatEnd():
	buffTimer.stop()


func onShopEntered():
	onStateChanged(false)


func onStateChanged(chargeActive):
	active = chargeActive
	if chargeActive:
		pass
	else:
		pass


func getCraftingOffset(forDirection):
	match forDirection:
		CoreConst.FaceDirection.UP:
			return Vector2( - 1, - 1)
		CoreConst.FaceDirection.DOWN:
			return Vector2.ZERO
		CoreConst.FaceDirection.LEFT:
			return Vector2( - 1, 0)
		CoreConst.FaceDirection.RIGHT:
			return Vector2(0, - 1)

func _readyInit():
	._readyInit()
	numHits = int(getP("hits"))
	buffSpeed = getP("speed") / 100.0
	buffTimer = newItemTimer("BuffTimer", "onBuffEnded", false)
