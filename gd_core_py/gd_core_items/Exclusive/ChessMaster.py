# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import *  # noqa: F401,F403

from ... import _registry as _R




class Exclusive__ChessMaster(_R.C("res://gd_core_items/Item.gd")):

	resource_path = "res://gd_core_items/Exclusive/ChessMaster.gd"

	def _init_fields(self):
		super()._init_fields()
		self.speed_v = None

	firstKnightRound = 1
	firstRookRound = 6
	firstQueenRound = 14

	def onPrepare(self):
		chessboards = self.getAllInInventoryOfType(self.ctx.item_book.getDescriptor("Chess Board"))
		if not (not chessboards):
			chessboards[0].addSpeed(self.speed_v)


	def onShopEntered(self):
		pass

	def _readyInit(self):
		super()._readyInit()
		self.speed_v = _div(self.getP('speed'), 100.0)


_R.reg("res://gd_core_items/Exclusive/ChessMaster.gd", Exclusive__ChessMaster)
_R.reg("ChessMaster", Exclusive__ChessMaster)
