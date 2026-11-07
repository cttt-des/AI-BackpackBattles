extends "res://gd_core_items/LeatherHelm.gd"
var blind

func onPrepare():
	pass


func onPreCombatStart():
	if not ctx.sandbag_active:
		ctx.sandbag_active = true
		.onPreCombatStart()
		opponent().changeDamageResistance(damReduction)
	elif buffsActive > 0:
		ctx.util.changeTimer(buffTimer, getBuffDur())


func onCombatStart():
	inflictBlind(blind)
	giveStacks(character(), CoreConst.EventType.Blind, blind)
	activate()


func buffEnded():
	if buffsActive > 0:
		.buffEnded()
		opponent().changeDamageResistance( - damReduction)
		ctx.sandbag_active = false



func _readyInit():
	._readyInit()
	# ★ np49（run602_r14 fd@334）：oracle 的 Sandbag.tscn BuffTimer=**普通 one_shot
	#   Timer（无脚本）+ timeout→buffEnded**（Exclusive/Sandbag.tscn:70-73,89——区别于
	#   父类 LeatherHelm.tscn 的 MultiTimer+multi_timeout）。此前继承 LH 的
	#   newItemTimer(..., multi=true)：changeTimer 延长（start(t+left)）走 CoreTimer
	#   multi 运行中分支=仅 push timestamps、引擎读数不改写 ⇒ 注册表 eng==e[1] 不
	#   重同步 ⇒ 按原截止期提前 fire（EB 回声 changeTimer@5.5 后 SB 仍 7.017 炸，
	#   oracle 实证 eng→8.5167 重同步、14.017 才炸）→ damageResistance 窗口错位
	#   → 14 处疲劳 dmg 分歧。修=按 tscn 真身重建为非 multi。
	buffTimer = newItemTimer("BuffTimer", "buffEnded", false)
	blind = int(getP("blind"))
