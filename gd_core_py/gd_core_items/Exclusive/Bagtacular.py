# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__Bagtacular(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/Bagtacular.gd"

	def _init_fields(self):
		super()._init_fields()
		self.affectedBagDescriptors = None


	def canAffect_global(self, item):
		return item.descriptor in self.affectedBagDescriptors

	def _readyInit(self):
		super()._readyInit()
		self.affectedBagDescriptors = {
		self.ctx.item_book.getDescriptor("Fanny Pack"): True, 
		self.ctx.item_book.getDescriptor("Stamina Sack"): True, 
		self.ctx.item_book.getDescriptor("Potion Belt"): True, 
		self.ctx.item_book.getDescriptor("Protective Purse"): True
	}


_R.reg("res://gd_core_items/Exclusive/Bagtacular.gd", Exclusive__Bagtacular)
_R.reg("Bagtacular", Exclusive__Bagtacular)
