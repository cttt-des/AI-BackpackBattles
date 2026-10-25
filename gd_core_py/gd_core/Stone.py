# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class Stone(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core/Stone.gd"

	def _init_fields(self):
		super()._init_fields()
		self._ammunition = 0
		self._bonusDamage = 0

	@property
	def ammunition(self):
		return self._ammunition
	@ammunition.setter
	def ammunition(self, v):
		self._ammunition = int(v)
	@property
	def bonusDamage(self):
		return self._bonusDamage
	@bonusDamage.setter
	def bonusDamage(self, v):
		self._bonusDamage = int(v)

	def combatEnd(self):
		super().combatEnd()
		self.ammunition = 1


	def setBagOfStones(self):
		self.ammunition = 9000


	def onPreDealDamage_late(self, damageRes):

		self.preHit()



	def preHit(self):
		self.removeBlock(self.getP1())


	def doCooldownEffect(self):
		if self.ammunition >= 1 and self.useStamina() == _R.C("CoreConst").StaminaResult.Sufficient:
			self.ammunition -= 1

			res = self.dealDamage()

			if self.ammunition == 0:
				self.onAfterEffectFinished(False)
				self.consume(res)
			else:
				self.activate(res)


	def onDealtDamage(self, damageRes):
		if damageRes.hasHit():
			self.onHit()



	def onHit(self):
		pass

	def _readyInit(self):
		super()._readyInit()
		self.damageSource = _R.C("CoreDamageSource")().setItem(self)
		self.ammunition = 1



_R.reg("res://gd_core/Stone.gd", Stone)
_R.reg("Stone", Stone)
