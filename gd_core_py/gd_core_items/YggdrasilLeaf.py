# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import *  # noqa: F401,F403

from .. import _registry as _R




class YggdrasilLeaf_2(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/YggdrasilLeaf.gd"

	def _init_fields(self):
		super()._init_fields()
		self.manaUsed = 0
		self.manaNeeded = None


	def canAffect(self, item):
		return item.hasType(_R.C("CoreConst").Type.Nature)


	def onPrepare(self):
		self.manaUsed = 0

		self.connectForCombat(self.character(), "character_mana_changed", "onManaChanged")


	def onCombatStart(self):
		self.giveMana(self.getP1() * len(self.getAffectedItems()))
		self.giveRegeneration(self.getP2() * len(self.getAffectedItems()))
		self.activate()


	def onManaChanged(self, amount, event):
		if amount < 0 and event.getParam("used", False):
			# ★ np26fH：gd 的 manaUsed 是 int 推断变量、信号 amount 也是 int
			#   （mana int 计数）→ int/int 整除 → activations 恒 int。py 侧事件
			#   amount 为 float（mana 系统 float 化），直加会让 manaUsed 变 float、
			#   _div(float,int)=真除 → activations 1.2/1.4 浮动 → heal 29/34/24
			#   波动（run1151_r13 实证）。截断回 int 对齐 gd。
			self.manaUsed += int(- amount)
			activations = _div(self.manaUsed, self.manaNeeded)
			self.manaUsed %= self.manaNeeded
			if activations >= 1:
				self.heal(self.getP_m("heal") * activations, event)
				self.cleanseRandomDebuffs(self.getP5() * activations, event)
				self.activate()

	def _readyInit(self):
		super()._readyInit()
		self.manaNeeded = int(self.getP3())


_R.reg("res://gd_core_items/YggdrasilLeaf.gd", YggdrasilLeaf_2)
_R.reg("YggdrasilLeaf", YggdrasilLeaf_2)
