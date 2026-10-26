# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Squirrel(_R.C("res://gd_core_items/Exclusive/ForestFriend.gd")):

	resource_path = "res://gd_core_items/Exclusive/Squirrel.gd"


	def doCooldownEffect(self):
		self.stealRandomBuff(1)
		self.activate()


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
		pass


_R.reg("res://gd_core_items/Exclusive/Squirrel.gd", Exclusive__Squirrel)
_R.reg("Squirrel", Exclusive__Squirrel)
