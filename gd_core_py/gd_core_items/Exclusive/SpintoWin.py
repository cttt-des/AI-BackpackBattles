# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__SpintoWin(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/SpintoWin.gd"

	def _init_fields(self):
		super()._init_fields()
		self.heat = None
		self.luck = None
		self.regen = None
		self.mana = None
		self.frame = None
		self.skillLight = None

	colors = {
		_R.C("CoreConst").FaceDirection.UP: Color(0.941176, 0.489231, 0.301961), 
		_R.C("CoreConst").FaceDirection.RIGHT: Color(0.301961, 0.941176, 0.41682), 
		_R.C("CoreConst").FaceDirection.DOWN: Color(0.941176, 0.301961, 0.513726), 
		_R.C("CoreConst").FaceDirection.LEFT: Color(0.320312, 0.466339, 1)
	}
	neutralColor = Color(1, 1, 1, 0.364706)

	def ready_deferred(self):
		super().ready_deferred()
		self.updateColor()


	def updateColor(self):
		pass








	def getDescription(self, wrapInColor=True):
		descr = super().getDescription(wrapInColor)
		colors = [self.ctx.util.inactiveColor, self.ctx.util.inactiveColor, self.ctx.util.inactiveColor, self.ctx.util.inactiveColor]
		gold = None

		if self.placed:
			colors[self.faceDirection] = self.ctx.util.modifiedColor

		descr = self.getModeDescription(descr, colors, False, wrapInColor)

		return descr


	def doCooldownEffect(self):
		if self.faceDirection == _H_1:
				self.giveHeat(self.heat)
		elif self.faceDirection == _H_2:
				self.giveLucky(self.luck)
		elif self.faceDirection == _H_4:
				self.giveRegeneration(self.regen)
		elif self.faceDirection == _H_6:
				self.giveMana(self.mana)
		self.activate()


	def gainsStack(self, stackType):
		if self.faceDirection == _H_1:
				return stackType == _H_3
		elif self.faceDirection == _H_2:
				return stackType == _H_5
		elif self.faceDirection == _H_4:
				return stackType == _H_7
		elif self.faceDirection == _H_6:
				return stackType == _H_8
		return False


	def rotateTo(self, targetRotation, duration=0.15):
		super().rotateTo(targetRotation, duration)
		self.updateColor()







	def setFaceDirectionInstant(self, _faceDirection):
		super().setFaceDirectionInstant(_faceDirection)
		self.updateColor()

	def _readyInit(self):
		super()._readyInit()
		self.heat = int(self.getP("heat"))
		self.luck = int(self.getP("luck"))
		self.regen = int(self.getP("regen"))
		self.mana = int(self.getP("mana"))


_R.reg("res://gd_core_items/Exclusive/SpintoWin.gd", Exclusive__SpintoWin)
_R.reg("SpintoWin", Exclusive__SpintoWin)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
    _H_1 = _R.C("CoreConst").FaceDirection.UP
except AttributeError as _he:
    _H_1 = _HoistPending(_he)
try:
    _H_2 = _R.C("CoreConst").FaceDirection.RIGHT
except AttributeError as _he:
    _H_2 = _HoistPending(_he)
try:
    _H_3 = _R.C("CoreConst").Stack.Heat
except AttributeError as _he:
    _H_3 = _HoistPending(_he)
try:
    _H_4 = _R.C("CoreConst").FaceDirection.DOWN
except AttributeError as _he:
    _H_4 = _HoistPending(_he)
try:
    _H_5 = _R.C("CoreConst").Stack.Lucky
except AttributeError as _he:
    _H_5 = _HoistPending(_he)
try:
    _H_6 = _R.C("CoreConst").FaceDirection.LEFT
except AttributeError as _he:
    _H_6 = _HoistPending(_he)
try:
    _H_7 = _R.C("CoreConst").Stack.Regeneration
except AttributeError as _he:
    _H_7 = _HoistPending(_he)
try:
    _H_8 = _R.C("CoreConst").Stack.Mana
except AttributeError as _he:
    _H_8 = _HoistPending(_he)
