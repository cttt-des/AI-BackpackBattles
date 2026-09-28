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
		if self.faceDirection == _R.C("CoreConst").FaceDirection.UP:
				self.giveHeat(self.heat)
		elif self.faceDirection == _R.C("CoreConst").FaceDirection.RIGHT:
				self.giveLucky(self.luck)
		elif self.faceDirection == _R.C("CoreConst").FaceDirection.DOWN:
				self.giveRegeneration(self.regen)
		elif self.faceDirection == _R.C("CoreConst").FaceDirection.LEFT:
				self.giveMana(self.mana)
		self.activate()


	def gainsStack(self, stackType):
		if self.faceDirection == _R.C("CoreConst").FaceDirection.UP:
				return stackType == _R.C("CoreConst").Stack.Heat
		elif self.faceDirection == _R.C("CoreConst").FaceDirection.RIGHT:
				return stackType == _R.C("CoreConst").Stack.Lucky
		elif self.faceDirection == _R.C("CoreConst").FaceDirection.DOWN:
				return stackType == _R.C("CoreConst").Stack.Regeneration
		elif self.faceDirection == _R.C("CoreConst").FaceDirection.LEFT:
				return stackType == _R.C("CoreConst").Stack.Mana
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
