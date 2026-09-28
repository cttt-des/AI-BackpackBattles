# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class CoreEvent(GodotObject):

	resource_path = "res://gd_core/CoreEvent.gd"

	Target = EnumDict("Target", {"Player": 0, "Opponent": 1})



	def _init_fields(self):
		super()._init_fields()
		self.id = 0
		self.timestamp = None
		self.parentEvent = None
		self.origin = None
		self.type = None
		self.target = None
		self.params = {}
		self.formatParams = {}

	# =============================================================================
	# CoreEvent.gd — 无头战斗内核：战斗事件
	# =============================================================================
	# 对齐源码：Core/CombatEvent.gd（全文 208 行）
	#
	# 保留（参与判定/被物品行为读取）：id / timestamp / parentEvent / origin / type /
	#   target / params，以及 getType / setTarget / setParam / getParam / getAmount /
	#   getAmountWithDefault / hasParam / getMainActor / getOrigin / fromCharacter / getDepth
	#
	# 剥离内容（纯呈现，判定不读）：
	#   · formatParams 的文案填充（Util.tra / Util.getIcon / 颜色包裹）
	#   · asText()（HTML/魔法文本渲染，1279 行的 CombatLog 职责）
	#   · damageColor* 常量与 damageFormat
	#   → 事项：`formatParams` 字段保留但不填充，避免任何外部代码因字段缺失崩溃。
	# =============================================================================





	def _init(self, _id, _timestamp=0.0, _parentEvent=None, _origin=None, _type=None):

		self.id = _id
		self.timestamp = _timestamp
		self.parentEvent = _parentEvent
		self.origin = _origin
		self.type = _type


	def getType(self):
		return self.type


	def setTarget(self, _target):
		self.target = _target


	def setParam(self, paramName, paramVal):
		self.params[paramName] = paramVal


	def getParam(self, paramName, default):
		return self.params.get(paramName, default)


	def getAmount(self):
		return self.params["amount"]


	def getAmountWithDefault(self, default):
		return self.params.get("amount", default)


	def hasParam(self, param):
		return param in self.params


	def getMainActor(self):
		if isinstance(self.origin, _R.C("CoreItem")):
			return self.origin.character().playerId
		elif self.target:
			return self.target
		else:
			return _R.C("CoreCharacter").ID.PLAYER


	def getOrigin(self):
		return self.origin


	def fromCharacter(self, character):
		return isinstance(self.origin, _R.C("CoreItem")) and self.origin.character() == character


	def getDepth(self):
		if self.parentEvent:
			return self.parentEvent.getDepth() + 1
		else:
			return 0


_R.reg("res://gd_core/CoreEvent.gd", CoreEvent)
_R.reg("CoreEvent", CoreEvent)
_R.reg("CoreEvent", CoreEvent)
