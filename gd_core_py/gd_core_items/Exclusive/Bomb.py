# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Bomb(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/Bomb.gd"

	def _init_fields(self):
		super()._init_fields()
		self.activationParticles = None
		self.damFactor = None


	def doCooldownEffect(self):
		if self.useStamina() == _R.C("CoreConst").StaminaResult.Sufficient:
			self.ctx.bus.setLoggingMode(self.ctx.bus.LoggingMode.Delayed)
			removedBuffs = 0
			for buff in _iter(_R.C("CoreConst").getBuffs()):
				numStacks = self.character().getStacks(buff)
				removedBuffs += numStacks
				self.character().useStacks(buff, numStacks, self)
			self.ctx.bus.flushLoggingQueue()

			self.opponent().changeDamageResistance( - self.damFactor * removedBuffs)

			dam = self.descriptor.minDam
			damageRes = self.dealEffectDamage(dam)
			self.onAfterEffectFinished()

	def _readyInit(self):
		super()._readyInit()
		self.damFactor = self.getP("dam")
		self.damageSource = _R.C("CoreDamageSource")().setItem(self)



_R.reg("res://gd_core_items/Exclusive/Bomb.gd", Exclusive__Bomb)
_R.reg("Bomb", Exclusive__Bomb)
