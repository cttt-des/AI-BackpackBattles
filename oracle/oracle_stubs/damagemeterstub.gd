extends Control
# =============================================================================
# [ORACLE 桩化记录 #9] DamageMeter / FilterPanel 占位桩（受控神谕）
# =============================================================================
# 原版：res://Interface/DamageMeter/DamageMeter.gd（extends ResizableControl，
# 重量级伤害图表 UI）与商店 FilterPanel。神谕不渲染 UI，此前骨架用无脚本
# Control 占位 → Core/CombatLog.gd 的战斗路径每次调用下列方法都抛
# SCRIPT ERROR 并**中止调用函数**，实测每场刷 2-6 MB 错误文本（批量日志
# 因此膨胀到数十 GB 量级），且大量错误打印显著拖慢单场耗时。
#
# 本桩按原版方法签名逐个空实现：只吞调用、不碰任何战斗状态 —— CombatLog
# 的执行流因此恢复与原版一致（原版这些调用成功返回，后续行照常执行）。
# 原版调用点（Core/CombatLog.gd）：
#   :98-105  connect("drag_start"/"drag_end", …)   → 需要同名信号
#   :149-152 clear / clearPlots
#   :205-206 createPlot
#   :316-351 unhighlightSource / highlightSource
#   :462-463 setTime
#   :648-650 updateMeter(event, statLogger)
#   :929-931 onShow
# 与战斗判定/事件流零交互：这些方法在原版只写 UI 图表，不产生事件、
# 不消耗 Util.rng（已核对 DamageMeter.gd 全文，无 rng/CombatEvent 写入）。
# =============================================================================

signal drag_start
signal drag_end


func clear() -> void :
	pass


func clearPlots() -> void :
	pass


func createPlot() -> void :
	pass


func setTime(_time) -> void :
	pass


func updateMeter(_event, _statLogger) -> void :
	pass


func highlightSource(_source) -> void :
	pass


func unhighlightSource(_source) -> void :
	pass


func onShow() -> void :
	pass
