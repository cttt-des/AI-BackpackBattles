extends Node
# =============================================================================
# SilentWolfStub — 神谕桩（受控神谕工作流 Phase 2 桩化记录 #2）
# =============================================================================
# 原版 addons/silent_wolf 是在线榜单 SDK（api.silentwolf.com）。
# 红线：神谕永不联网、永不进排名模式——整个 autoload 替换为空实现。
# 原版唯一的调用方是 Core/RunDatabase.gd（已被 RunDatabaseStub 取代），
# 故本桩只需提供一个安全的 Scores 形状，任何调用都会 fail-fast。
# =============================================================================

var Scores = null


class DummyScores:
	func get_high_scores(_n, _board):
		push_error("[ORACLE-STUB] SilentWolf.Scores.get_high_scores 不应在神谕中被调用")
	func persist_score(_a, _b, _c, _d):
		push_error("[ORACLE-STUB] SilentWolf.Scores.persist_score 不应在神谕中被调用")


func _ready() -> void:
	Scores = DummyScores.new()


func configure(_params: Dictionary) -> void:
	# 原版：设置 api_key / game_id 并初始化 HTTP 节点。神谕：无网络，空实现。
	pass
