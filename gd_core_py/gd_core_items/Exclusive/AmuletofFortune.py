# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__AmuletofFortune(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/AmuletofFortune.gd"

	def _init_fields(self):
		super()._init_fields()
		self.bonusChance = None
		self.numBuffs = None

	amuletColor = Color(0.266667, 0.960784, 0.667953)

	def canAffect(self, item):
		return item.canModifyChance()


	def onPrepare(self):
		_iter__loc = _iter
		_aff = self.getAffectedItems()
		# ★ np51㊳终⑪ 增伤面探针（GD_FORTPROBE 门控，零 rng 消耗）
		if _os_environ_get("GD_FORTPROBE") != "":
			_names = ""
			for _a in (_aff if _aff.__class__ is list else _iter__loc(_aff)):
				_names += String(_a.descriptor.identifier) + ","
			print("[FORT] t=prepare bonusChance=", self.bonusChance, " affected=", _names,
					" mult=", self.bonusChancePercent_mult)
		for item in (_aff if _aff.__class__ is list else _iter__loc(_aff)):
			item.addBonusChance(self.bonusChance)


	def doCooldownEffect(self):
		self.giveMostBuffs(self.numBuffs)
		self.onAfterEffectFinished()


	def getTriggerPriority(self):
		return _H_1 + 5

	def _readyInit(self):
		super()._readyInit()
		self.bonusChance = self.getP("chance")
		self.numBuffs = int(self.getP("buffs"))
		pass



_R.reg("res://gd_core_items/Exclusive/AmuletofFortune.gd", Exclusive__AmuletofFortune)
_R.reg("AmuletofFortune", Exclusive__AmuletofFortune)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").Priority.High
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
