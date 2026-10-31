extends Item
var manaUsed = 0
var manaNeeded

func canAffect(item):
	return item.hasType(CoreConst.Type.Nature)


func onPrepare():
	manaUsed = 0
	
	connectForCombat(character(), "character_mana_changed", "onManaChanged")


func onCombatStart():
	giveMana(getP1() * getAffectedItems().size())
	giveRegeneration(getP2() * getAffectedItems().size())
	activate()
	

func onManaChanged(amount, event):
	if amount < 0 and event.getParam("used", false):
		# ★ np26fH：显式 int 截断（GDScript 语义冗余、py 转写必需）——py 侧事件
		#   amount 为 float（mana 系统 float 化），直加会把 manaUsed 浮化、
		#   _div(float,int)=真除 → activations 浮动 → heal 29/34/24 波动
		#   （run1151_r13 定谳）。gd 侧 int(int) 无害；gd_to_py 转写自带。
		manaUsed += int(- amount)
		var activations = manaUsed / manaNeeded
		manaUsed %= manaNeeded
		if activations >= 1:
			heal(getP_m("heal") * activations, event)
			cleanseRandomDebuffs(getP5() * activations, event)
			activate()

func _readyInit():
	._readyInit()
	manaNeeded = int(getP3())
