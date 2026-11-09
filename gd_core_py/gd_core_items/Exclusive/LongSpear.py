# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__LongSpear(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/LongSpear.gd"

	def _init_fields(self):
		super()._init_fields()
		self.blockRemoval = None
		self.damResistance = None


	def addToStorageBox(self, addImpulse=True, tweenBouncyness=True, checkCollisions=True, targetPos=None, speed=1.0, secondCheck=False):

		curDir = self.faceDirection
		if self.faceDirection == _H_1 or self.faceDirection == _H_2:
			self.setFaceDirectionInstant(_H_3)
			super().addToStorageBox(addImpulse, tweenBouncyness, checkCollisions, targetPos, speed, secondCheck)
			self.setFaceDirectionInstant(curDir)
			self.setFaceDirection(_H_3)
		else:
			super().addToStorageBox(addImpulse, tweenBouncyness, checkCollisions, targetPos, speed, secondCheck)




	def affectsEmpty(self, color):
		return True


	def canAffect(self, item):
		return False


	def onPrepare(self):
		self.blockRemoval = self.getP("block") * self.getNumEmptyAffectedCells()


	def onPreDealDamage_early(self, damageRes):
		if damageRes.hasHit():
			self.removeBlock(self.blockRemoval)
			self.opponent().changeDamageResistance( - self.damResistance)

	def _readyInit(self):
		super()._readyInit()
		self.damResistance = self.getP("dam")


_R.reg("res://gd_core_items/Exclusive/LongSpear.gd", Exclusive__LongSpear)
_R.reg("LongSpear", Exclusive__LongSpear)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
    _H_1 = _R.C("CoreConst").FaceDirection.LEFT
except AttributeError as _he:
    _H_1 = _HoistPending(_he)
try:
    _H_2 = _R.C("CoreConst").FaceDirection.RIGHT
except AttributeError as _he:
    _H_2 = _HoistPending(_he)
try:
    _H_3 = _R.C("CoreConst").FaceDirection.UP
except AttributeError as _he:
    _H_3 = _HoistPending(_he)
