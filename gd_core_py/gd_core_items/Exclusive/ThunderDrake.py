# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__ThunderDrake(_R.C("res://gd_core_items/Weapon.gd")):

	resource_path = "res://gd_core_items/Exclusive/ThunderDrake.gd"

	def _init_fields(self):
		super()._init_fields()
		self.active = False
		self.curHitCount = 0
		self.lightningMultiplicity = {}
		self.numHits = None
		self.buffSpeed = None
		self.buffTimer = None
		self.buffParticles = None


	def canAffect_lightning(self, item):
		return item.hasCooldown() or item.reactsToCharges()


	def onPrepare(self):
		self.setState(False)
		self.curHitCount = 0
		self.lightningMultiplicity = self.countItemsInAffectedCells_cached(_R.C("CoreConst").Affected.Lightning)


	def onDealtDamage(self, damageRes):
		if damageRes.hasHit():
			self.curHitCount += 1

			if self.curHitCount == self.numHits:


				if self.active:
					for item in _iter(self.getAffectedItems(_R.C("CoreConst").Affected.Lightning)):
						item.chargeLeft(self)
						self.zapItem(item)
				else:
					self.setState(True)
					for item in _iter(self.getAffectedItems(_R.C("CoreConst").Affected.Lightning)):
						item.addSpeed(self.buffSpeed * self.lightningMultiplicity[item])
						self.zapItem(item)

				self.buffTimer.stop()
				self.buffTimer.start(self.getP_m("dur"))
				self.curHitCount = 0


	def zapItem(self, item):
		item.chargeReceived(self)
		if item.hasOnChargeReceivedEffect:
			targetPos = item.getGlobalCenter()


	def onBuffEnded(self):
		self.setState(False)

		for item in _iter(self.getAffectedItems(_R.C("CoreConst").Affected.Lightning)):
			item.reduceSpeed(self.buffSpeed * self.lightningMultiplicity[item])
			item.chargeLeft(self)


	def onCombatEnd(self):
		self.buffTimer.stop()


	def onShopEntered(self):
		self.onStateChanged(False)


	def onStateChanged(self, chargeActive):
		self.active = chargeActive
		if chargeActive:
			pass
		else:
			pass


	def getCraftingOffset(self, forDirection):
		if forDirection == _R.C("CoreConst").FaceDirection.UP:
				return Vector2( - 1, - 1)
		elif forDirection == _R.C("CoreConst").FaceDirection.DOWN:
				return Vector2.ZERO
		elif forDirection == _R.C("CoreConst").FaceDirection.LEFT:
				return Vector2( - 1, 0)
		elif forDirection == _R.C("CoreConst").FaceDirection.RIGHT:
				return Vector2(0, - 1)

	def _readyInit(self):
		super()._readyInit()
		self.numHits = int(self.getP("hits"))
		self.buffSpeed = _div(self.getP('speed'), 100.0)
		self.buffTimer = self.newItemTimer("BuffTimer", "onBuffEnded", False)


_R.reg("res://gd_core_items/Exclusive/ThunderDrake.gd", Exclusive__ThunderDrake)
_R.reg("ThunderDrake", Exclusive__ThunderDrake)
