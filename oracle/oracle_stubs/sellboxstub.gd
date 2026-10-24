extends Area2D
# =============================================================================
# SellboxStub — 神谕桩（受控神谕工作流 Phase 2 桩化记录 #9）
# =============================================================================
# 原版 Interface/Sellbox.gd 是 Main.tscn 内联的出售箱（Area2D 大场景，含栗子
# 动画/交易 UI），神谕不加载 Main.tscn 也没有出售流程。战斗路径对 Game.SELLBOX
# 的真实需要只有：signal calc_trade_chance（物品 addToInventory 时
# Util.connectIfExists 连接用）与 tradeChance/tradeBonusValue 读数。
# 其余成员（sellItem/openSound…）在神谕中不存在，被调用即 fail-fast。
# =============================================================================

signal calc_trade_chance

var tradeChance := 0.0
var tradeBonusValue := 0.0
var openSound = null
var closeSound = null


func getItems() -> Array:
	return []


func getItemsAndGems() -> Array:
	return []


func getGoldPos() -> Vector2:
	return Vector2.ZERO


func isHovered() -> bool:
	return false
