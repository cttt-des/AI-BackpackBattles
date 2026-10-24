extends Node2D
# =============================================================================
# StorageboxStub — 神谕桩（受控神谕工作流 Phase 2 桩化记录 #9b）
# =============================================================================
# 原版 Interface/Storagebox.gd 是 Main.tscn 内联的储物箱（含碰撞区/动画）。
# 战斗路径对 Game.STORAGEBOX 的真实需要：getItems/getItemsAndGems
# （ItemBook.getOwnedItems 统计）、center（飘字定位）。
# removeItem/pushItemsToStorage 等（商店流程）在神谕中不存在，调用即 fail-fast。
# =============================================================================

var items := []


func getItems() -> Array:
	return items


func getItemsAndGems() -> Array:
	return items.duplicate()


func center() -> Vector2:
	return Vector2.ZERO
