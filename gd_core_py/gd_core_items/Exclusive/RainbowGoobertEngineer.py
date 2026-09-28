# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__RainbowGoobertEngineer(_R.C("res://gd_core_items/Goobert.gd")):

	resource_path = "res://gd_core_items/Exclusive/RainbowGoobertEngineer.gd"

	def _init_fields(self):
		super()._init_fields()
		self.vampirism = None
		self.regen = None
		self.stamina = None
		self.blind = None
		self.dambonus = None


	def doCooldownEffect(self):
		self.giveBlock()
		self.heal()
		self.giveStamina(self.stamina)
		self.giveVampirism(self.vampirism)
		self.giveRegeneration(self.regen)
		self.inflictBlind(self.blind)

		for item in _iter(self.getAffectedItems()):
			if item.canBeEmpowered():
				item.addBonusDamage(self.dambonus)

	def _readyInit(self):
		super()._readyInit()
		self.vampirism = int(self.getP("vampirism"))
		self.regen = int(self.getP("regen"))
		self.stamina = self.getP("stamina")
		self.blind = int(self.getP("blind"))
		self.dambonus = self.getP("dambonus")


_R.reg("res://gd_core_items/Exclusive/RainbowGoobertEngineer.gd", Exclusive__RainbowGoobertEngineer)
_R.reg("RainbowGoobertEngineer", Exclusive__RainbowGoobertEngineer)
