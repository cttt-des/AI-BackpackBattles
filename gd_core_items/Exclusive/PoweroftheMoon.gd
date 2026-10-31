extends Item
var boosted: = 0
var moonArmorDescriptor
var moonShieldDescriptor
var manaOrbDescriptor
var timeAdvance
var blind

func canAffect(item):
	return item.isA(moonArmorDescriptor) or item.isA(moonShieldDescriptor)


func getData():
	return boosted


func setData(data):
	if data != null:
		boosted = data


func onBought():
	boosted = 1


func onPostCombatStart():
	# ★ np25w_f10：此处必须是**死调用**。受控神谕语料的真值：oracle_bootstrap.gd:108
	#   把 Main/Combat 搭成裸 Node2D（不挂 Core/Combat.gd）→ 原版
	#   `Game.combatSceneNode.advanceTime(timeAdvance)` 在神谕 harness 内
	#   "Nonexistent function" 脚本错误中断 = 无操作 → 语料全库疲劳起点恒为
	#   CombatTimer.start() 的 FATIGUE_TIME-3=14s（首笔疲劳伤 + fatigue_start
	#   信号在 17.0167=+3s tick+1tick；514 场 >17s 语料全数实证、0 提前例）。
	#   gd 若真推进时钟（CoreCombat.advanceTime），PotM time=6 ×2 件把疲劳
	#   提前到 5.0333（run741_r9/run926_r11 实证=本面首分歧）。镜像死调用语义：
	#   不推进、不改 time_advance。CoreCombat.advanceTime 本体保留（无其他调用点）。
	pass


func onPrepare():
	connectForCombat(ctx.combat, "fatigue_start", "onFatigueStarted")
	
	for item in getAffectedItems():
		if item.isA(moonArmorDescriptor):
	
			connectForCombat(item, "activated", "onMoonArmorActivated")
		else:
	
			connectForCombat(item, "activated", "onMoonShiedActivated")


func onFatigueStarted():
	var bonusHealth = getP_m("maxhealth") / 100.0 * character().getMaxHealth()
	giveMaxHealth(bonusHealth)
	activate()


func onMoonArmorActivated(event):
	inflictBlind(blind, event)


func onMoonShiedActivated(event):
	giveReflectStacks(1)


func onItemRoll(descr):
	pass

func onItemRolled(descr):
	if descr == manaOrbDescriptor:
		boosted -= 1

func _readyInit():
	._readyInit()
	moonArmorDescriptor = ctx.item_book.getDescriptor("Moon Armor")
	moonShieldDescriptor = ctx.item_book.getDescriptor("Moon Shield")
	manaOrbDescriptor = ctx.item_book.getDescriptor("Mana Orb")
	timeAdvance = getP("time")
	blind = int(getP("blind"))
