# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from .._rt import (  # noqa: F401

    Color,
    Dictionary,
    EnumDict,
    FuncRef,
    GD_DEFAULT,
    INF,
    NAN,
    Node,
    Node2D,
    OS_has_feature,
    Object,
    PCG32,
    PI,
    PoolStringArray,
    RandomNumberGenerator,
    Reference,
    Resource,
    Signal,
    String,
    TAU,
    TYPE_VECTOR2,
    Vector2,
    Vector3,
    _HoistPending,
    _bind_battle,
    _div,
    _dup,
    _erase,
    _fill,
    _find,
    _gd_fmt,
    _gd_range,
    _gd_str,
    _get_slice,
    _gid,
    _has_behavior_cache_get,
    _has_behavior_cache_put,
    _hash,
    _invert,
    _iter,
    _join,
    _load,
    _mod,
    _os_environ_get,
    _pick_random,
    _pop_at,
    _resize,
    _shuffle,
    _sort_custom,
    _strv,
    _substr,
    ceil,
    clamp,
    deg2rad,
    f32,
    floor,
    fmod,
    gd_round,
    get_stack,
    inverse_lerp,
    is_equal_approx,
    is_instance_valid,
    lerp,
    move_toward,
    posmod,
    pow,
    rad2deg,
    randomize,
    round,
    sign,
    smoothstep,
    snapped,
    sqrt,
    stepify,
    tr,
    typeof,
    wrapf,
    wrapi
,
)

if "GodotObject" not in globals():
	from .._rt import GodotObject  # 纯 py 补绑；编译态 pxd 已预绑

from .. import _registry as _R
if "_base_cls_Card_2" not in globals():
	from .Item import Item_2 as _base_cls_Card_2





class Card_2(_base_cls_Card_2):

	resource_path = "res://gd_core_items/Card.gd"

	def _init_fields(self):
		super()._init_fields()
		self.back = None
		self.activeFront = None
		self.curActivationDelay = 0.0
		self.faceUp = True
		self.activating = False
		self.chainPosition = - 1
		self.deck = None
		self.cardAnimation = None
		self.front = None
		self.connector = None
		self.notInChainMark = None


	def setFaceUp(self):
		if not self.faceUp:
			self.faceUp = True


	def setFaceDown(self):
		if self.faceUp:
			self.faceUp = False


	def updateTexture(self):
		if self.faceUp:
			if self.deck and self.activeFront and self.cardSecondaryEffectActive():
				pass
			else:
				pass
		else:
			pass


	def cardSecondaryEffectActive(self):
		return False


	def canAffect(self, item):
		if self.placed:
			return (self.deck and 
				item.hasType(_H_2) and 
				(item.chainPosition > self.chainPosition or item.chainPosition == - 1))
		else:
			return item.hasType(_H_2) and not item.deck


	def prepare(self):
		super().prepare()
		self.setState(False)


	def preCombatStart(self):
		super().preCombatStart()
		self.deactivateCooldown()


	def getNextCard(self):


		affected = self.getItemsInAffectedCells_cached()
		if not (not affected) and affected[0].hasType(_H_2):
			return affected[0]
		else:
			return None


	def startActivation(self):
		if self.activating or self.faceUp:
			return

		self.activating = True
		self.iterationCooldown = self.getCooldown()
		self.triggerTime = self.iterationCooldown
		self.activateCooldown()
		self.ctx.combat_log.snapshotItemTooltipStat(self, _H_1)



	def playActivationAnimation(self, aniType=GD_DEFAULT, consume=False):
		if aniType is GD_DEFAULT:
			aniType = self.descriptor.activationAni
		pass



	def onStateChanged(self, _faceUp):
		if _faceUp:

			if self.faceUp:
				pass
			else:
				pass
		else:
			if self.faceUp:
				pass

		self.faceUp = _faceUp


	def doRevealEffect(self):
		pass


	def trigger(self):
		self.activating = False
		self.showCooldown(0)
		nextCard = self.getNextCard()
		if nextCard:
			nextCard.startActivation()

		self.triggerTime = self.iterationCooldown

		self.setState(True, True)
		self.deactivateCooldown()
		self.doRevealEffect()




	def combatEnd(self):
		super().combatEnd()
		self.activating = False


	def shopEntered(self, craft):
		super().shopEntered(craft)
		self.setFaceUp()


	def addToInventory(self, _inventory, _occupiedCells, _placedByPlayer):
		super().addToInventory(_inventory, _occupiedCells, _placedByPlayer)


	def onRemoveFromInventory(self):
		self.deck = None
		self.updateTexture()



	def notifyChainPosition(self, _deck, _chainPos, chainLength):
		self.chainPosition = _chainPos

		if self.chainPosition == - 1:
			self.deck = None
			if self.placed:
				pass
		else:
			self.deck = _deck

			if self.chainPosition != chainLength - 1:
				pass
			else:
				pass

		self.updateTexture()



	def getDescription(self, wrapInColor=True):
		descr = super().getDescription(wrapInColor)
		return self.getCardDescription(descr)


	def getCardDescription(self, descr):
		if self.deck:
			descr += "\n\n" + self.insertParameter(self.ctx.util.tra("CARD_COUNT"), "num", self.chainPosition, _H_3, False)
		elif self.placed:
			descr += "\n\n" + self.ctx.util.wrapInColor(self.ctx.util.tra("CARD_HINT"), self.ctx.util.paramColor)

		return descr

	def _readyInit(self):
		super()._readyInit()
		pass


_R.reg("res://gd_core_items/Card.gd", Card_2)
_R.reg("Card", Card_2)
_R.reg("Card", Card_2)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").ItemStat.Cooldown
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
try:
	_H_2 = _R.C("CoreConst").Type.Card
except AttributeError as _he:
	_H_2 = _HoistPending(_he)
try:
	_H_3 = _R.C("CoreConst").StatModified.No
except AttributeError as _he:
	_H_3 = _HoistPending(_he)
