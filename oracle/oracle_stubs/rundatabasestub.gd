extends Node
# =============================================================================
# RunDatabaseStub — 神谕桩（受控神谕工作流 Phase 2 桩化记录 #1）
# =============================================================================
# 原版 Core/RunDatabase.gd 在 _ready 里做三件事与神谕冲突：
#   1. SilentWolf.configure + sendRunRequest → 无头环境里会向
#      api.silentwolf.com 发起 HTTP 请求（在线榜单）。红线：神谕永不联网。
#   2. SteamLeaderboard / Lobbies 节点——排名/休闲/联机入口，红线：不得存在。
#   3. 连接 Game 的 run 信号做缓存写盘——神谕不开 run，用不到。
# 战斗路径上真正被引用的只有两个常量性成员（RunData.deserializeStream 读
# 宝石索引上限用）与一个损坏回调，这里按原版语义最小实现：
#   - totalNumGems / emptySocketId：与原版 RunDatabase.gd:45-46 相同的公式
#   - notifyOpponentCorrupt()：原版只在网络对手损坏时弹回，神谕无网络对手，
#     保留空实现以维持 Game.addOpponentItem 的调用面
# 其余成员（getNextOpponentData / sortOpponents / pushRun …）在神谕中不存在，
# 任何对它们的调用都是 bug，直接断言失败（fail-fast）。
# =============================================================================

var steamLeaderboard = null        # 恒 null：神谕无 Steam 榜单
var lobbies = null                 # 恒 null：神谕无休闲大厅
var rounds = []                    # 保留原版字段（serializeRound 路径不使用）
var facedNoConnectionDarkReflection: int = 0
var statisticsMode = false

# 对齐原版 onready 计算（RunDatabase.gd:45-46）
onready var totalNumGems = BitStream.binaryCeil(ItemBook.getNumGems() + 1)
onready var emptySocketId = totalNumGems - 1


func notifyOpponentCorrupt():
	# 原版：pop_back 最近网络对手。神谕对手来自本地 history.db，无网络对手。
	print("[ORACLE-STUB] notifyOpponentCorrupt called (no-op in oracle)")


func getRoundData(_roundNum):
	# 原版返回本轮 run 的序列化回合（网络对战记录用）。神谕不开 run。
	push_error("[ORACLE-STUB] RunDatabase.getRoundData 不应在神谕中被调用")
	return null


func getLeaderboard():
	push_error("[ORACLE-STUB] RunDatabase.getLeaderboard 不应在神谕中被调用")
	return ""
