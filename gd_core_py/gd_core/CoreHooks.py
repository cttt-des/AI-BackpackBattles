# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class CoreHooks(GodotObject):

	resource_path = "res://gd_core/CoreHooks.gd"

	# =============================================================================
	# CoreHooks.gd — 无头战斗内核：外部副作用钩子（解耦用）
	# =============================================================================
	# 这是本次「精简 + 解耦」的核心手法：
	#   原版把 视觉/动画/粒子/tween/shader/z_index、音效、UI 悬停/拖拽/预览、
	#   战斗日志快照 直接内联写在战斗判定函数里，导致战斗逻辑无法脱离场景树运行。
	#   gd_core 把这些调用一律改为对本钩子对象的调用，默认实现全部为空，
	#   因此判定路径不再触碰任何渲染/音频/UI/节点 API。
	#
	# 保真约束：
	#   · 钩子**不在任何 if 条件里**参与判定（全部为纯尾部副作用调用）；
	#   · 因此空实现与真实实现的判定结果完全一致 —— 这是本方案可证明保真的前提。
	#   · 若某处原版把副作用写进了条件（例如 `if animation.current_animation != "Poison"`），
	#     该行不会进入钩子，而是整体删除并在真值表里记为「纯表现分支」，因为它不影响
	#     任何被判定读取的量。
	#
	# 需要真实视觉效果时（例如注入回游戏进程内运行），继承本类并覆写即可。
	# =============================================================================


	# ── 物品层表现 ──

	def showCooldown(self, item, progress):
		pass


	# 对齐 Item.gd:5298-5320（tween 着色器进度条）；判定侧只关心「效果是否结束」。
	def showCooldownSmooth(self, item, progress, fill=False):
		pass


	def resetZ(self, item):
		pass


	def playActivationAnimation(self, item, aniType, consume):
		pass


	def playActivationSound(self, item):
		pass


	def playDropSound(self, item, volume):
		pass


	def spawnLabel(self, item, type, damage):
		pass


	def queueTooltipUpdate(self, item):
		pass


	def activateBuffCounter(self, character, type):
		pass


	def playOutOfStaminaAnimation(self, item):
		pass


	def playStunAnimation(self, character, duration):
		pass


	# ── 战斗计时器（CombatTimer）表现 ──

	def playFatigueAnimation(self, name):
		pass


	def playFatigueSound(self):
		pass


	# ── 角色层表现 ──

	def playAttackAnimation(self, character, distance=None):
		pass


	def playActivateAnimation(self, character):
		pass


	# 对齐 Item.gd:1409-1419（新物品被纳入受影响集时的提示动画）
	def playAffectedPlacedAnimation(self, item, newItemIsAffected):
		pass


	# ── 角色状态表现 ──

	# 对齐 Character.gd:1002-1011（胜负粒子 + 动画）
	def playWinLoseAnimation(self, character, isWin):
		pass


	# 对齐 Character.gd:198-215 的表现部分（nameBanner 贴图 / setSprite 换精灵）
	def onClassChanged(self, character, classResource):
		pass


	# 对齐 Character.gd:1574-1583（战怒粒子/光环动画/职业战怒吼声）
	def playBattleRageAnimation(self, character, rageStart):
		pass


	# 对齐 Character.gd:1058-1064（无敌泡泡动画/可见性）
	def playInvulnerableAnimation(self, character, invu):
		pass


	# ── 物品朝向／放置预览（内核只保留字段语义，表现交给宿主）──
	# 旋转后重绘（对齐 Item.gd:1963-1996 的尾部表现：粒子/音效/Game.onItemRotated）
	def onItemRotated(self, item):
		pass


	# 对齐 Item.gd:1857-1875 区间的预览格冲突着色
	def previewCellCollision(self, item):
		pass


	# 对齐 Item.gd:2124-2131 的预览格着色
	def previewCells(self, item):
		pass


	# 对齐 Item.gd:2211 的预览受影响提示
	def previewCanAffect(self, item):
		pass


	def spawnLabel_character(self, character, type, damage, item=None):
		pass


	def spawnReflectLabel(self, type, reflected):
		pass


	def spawnResistedLabel(self, type, resisted):
		pass


	def spawnProtectedLabel(self, type, protected):
		pass


	def spawnBuffLabel_item(self, type, item, amount, appliedToOpponent):
		pass


	def spawnBuffLabel(self, type, pos):
		pass


	def spawnNumberLabel(self, type, pos, direction, damage):
		pass


	def spawnMissLabel(self, pos, direction):
		pass


	def damageAnimation(self, character, kind, speed=1.0):
		pass


	def playCharacterSound(self, character, stream, volume=0, pitch=1.0, force=False):
		pass


	def onHealthChangedUI(self, character):
		pass


	def onMaxStaminaChangedUI(self, character):
		pass


	# 对齐 Util.spawnLabelOnItem(type, item, amount)（Util.gd 中的物品飘字）
	def spawnLabelOnItem(self, type, item, amount):
		pass


	# 对齐 Inventory.onItemTypeChanged（动态类型增删后的背包刷新）
	def onItemTypeChanged(self, item):
		pass


	# 对齐 ElectricalCharge 动画（Item.sendCharge 的电荷传播表现）
	def sendCharge(self, item, cells, duration, event):
		pass


	def applyImpulse(self, item, offset, impulse):
		pass


	# ── 统计埋点（数值型，可选实现） ──

	def addMetric(self, item, metricIndex, amount):
		pass


	def snapshotItemTooltipStat(self, item, statType, playerId=None, withNextEvent=False, event=None):
		pass


	def snapshotItemState(self, item, state, withNextEvent, event):
		pass


	def snapshotItemMetric(self, item, metricIndex, playerId=None, withNextEvent=False):
		pass


	def snapshotCharacterStat(self, character, statType, withNextEvent=False, event=None):
		pass


	def snapshotStack(self, character, type):
		pass


	def snapshotDamageDealt(self, playerId, type, damage):
		pass


	def snapshotGlobalStat(self, stat, newValue):
		pass


	def snapshotMetric(self, playerId, metric, eventType, value):
		pass


	def updateDamageMeter(self, playerId, event):
		pass


	# ── 战斗日志 ──

	def logEvent(self, event):
		pass


_R.reg("res://gd_core/CoreHooks.gd", CoreHooks)
_R.reg("CoreHooks", CoreHooks)
_R.reg("CoreHooks", CoreHooks)
