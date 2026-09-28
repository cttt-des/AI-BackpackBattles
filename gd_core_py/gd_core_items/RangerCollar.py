# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class RangerCollar(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/RangerCollar.gd"

	def _init_fields(self):
		super()._init_fields()
		self.affectedItems = None
		self.acornAceDescriptor = None


	def prepare(self):
		self.affectedItems = self.getAffectedItems()
		numAces = self.countAllInInventoryOfType(self.acornAceDescriptor)
		if numAces > 0:
			staminaReduction = numAces * - self.acornAceDescriptor.getP("stamina")
			for item in _iter(self.affectedItems):
				item.changeStaminaFactor(staminaReduction)
		super().prepare()

	def _readyInit(self):
		super()._readyInit()
		self.acornAceDescriptor = self.ctx.item_book.getDescriptor("Acorn Ace")


_R.reg("res://gd_core_items/RangerCollar.gd", RangerCollar)
_R.reg("RangerCollar", RangerCollar)
_R.reg("RangerCollar", RangerCollar)
