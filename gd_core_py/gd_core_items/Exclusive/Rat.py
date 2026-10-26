# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Rat(_R.C("res://gd_core_items/Exclusive/ForestFriend.gd")):

	resource_path = "res://gd_core_items/Exclusive/Rat.gd"

	def _init_fields(self):
		super()._init_fields()
		self._poison = 0
		self._blind = 0

	@property
	def poison(self):
		return self._poison
	@poison.setter
	def poison(self, v):
		self._poison = int(v)
	@property
	def blind(self):
		return self._blind
	@blind.setter
	def blind(self, v):
		self._blind = int(v)

	def initRat(self):
		self.damageSource = _R.C("CoreDamageSource")().setItem(self)
		self.poison = int(self.getP("poison"))
		self.blind = int(self.getP("blind"))


	def doCooldownEffect(self):
		dam = self.descriptor.minDam
		res = self.dealEffectDamage(dam)
		if self.rollChance():
			self.inflictPoison(self.poison, res.event)
		if self.rollChance2():
			self.inflictBlind(self.blind, res.event)

		self.activate(res)


	def playPickupSound(self):
		# ★ np24：音高抽=无日志裸抽——oracle 原版此行=Util.rng.randf_range 直连
		#   （不经 rng_trace 包装 ⇒ 不落 rng_log），gd 误译为记帐版 ctx.rng（多记）。
		#   run576_r14 首支断点（Snake 激活音高 #215 多一行，+67 pitch 族的实证点）。
		self.ctx.rng.rng.randf_range(0.9, 1.1)


	def playDropSound(self, volume=0):
		volume += self.impactSoundVolume
		# ★ np24：音高抽=无日志裸抽——oracle 原版此行=Util.rng.randf_range 直连
		#   （不经 rng_trace 包装 ⇒ 不落 rng_log），gd 误译为记帐版 ctx.rng（多记）。
		#   run576_r14 首支断点（Snake 激活音高 #215 多一行，+67 pitch 族的实证点）。
		self.ctx.rng.rng.randf_range(0.9, 1.1)

	def _readyInit(self):
		super()._readyInit()
		self.initRat()



_R.reg("res://gd_core_items/Exclusive/Rat.gd", Exclusive__Rat)
_R.reg("Rat", Exclusive__Rat)
