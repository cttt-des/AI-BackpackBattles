# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py

from ..._rt import (  # noqa: F401

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
	from ..._rt import GodotObject  # 纯 py 补绑；编译态 pxd 已预绑

from ... import _registry as _R
if "_base_cls_Exclusive__ShinyMantle" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__ShinyMantle





class Exclusive__ShinyMantle(_base_cls_Exclusive__ShinyMantle):

	resource_path = "res://gd_core_items/Exclusive/ShinyMantle.gd"

	def _init_fields(self):
		super()._init_fields()
		self._invuProcced = 0
		self.gemDurFactor = 0.0
		self.manaNeeded = None
		self.activationParticles = None
		self.buffTimer = None
		self.blind = None
		self.manaNeeded_base = None
		self.manaCostIncrease = None
		self.maxUses = None

	@property
	def invuProcced(self):
		return self._invuProcced
	@invuProcced.setter
	def invuProcced(self, v):
		self._invuProcced = int(v)

	def canAffect(self, item):
		return not item.isBag()


	def readyToFuse(self):
		return not (not self.bondedIngredients)


	def onFusingFinished(self, validBonds):
		super().onFusingFinished(validBonds)

	def getCounterValue(self):
		_iter__loc = _iter
		gold = 0
		inv = self.inventory if self.placed else self.ctx.player.INVENTORY
		for item in _iter__loc(inv.getItemsAndGems()):
			if item.isGem():
				gold += item.getPrice()

		if self.dragged:
			for gem in _iter__loc(self.getGemsNoNull()):
				gold += gem.getPrice()

		return gold


	def onPrepare(self):
		self.connectForCombat(self.character(), "character_invulnerable_start", "onInvuStarted")



		self.manaNeeded = self.manaNeeded_base
		self.invuProcced = 0
		self.gemDurFactor = floor(_div(self.getCounterValue(), self.getP('gold')))
		self.setState(False)




	def doCooldownEffect(self):
		if self.character().isVulnerable() and self.character().getMana() >= self.manaNeeded:
			self.setState(True)
			self.invuProcced += 1
			invuDur = self.getP_m("dur_base") + self.getP_m("dur_bonus") * self.gemDurFactor
			self.buffTimer.start(invuDur)
			event = self.character().makeInvulnerable(invuDur, self)
			self.useMana(self.manaNeeded, event)
			self.manaNeeded += self.manaCostIncrease

			if self.invuProcced == self.maxUses:
				self.onAfterEffectFinished()
				return

		self.activate()






	def onInvuStarted(self, event):
		self.inflictBlind(self.blind, event)










	def onStateChanged(self, invuActive):
		if invuActive:
			pass
		else:
			pass


	def buffEnded(self):
		self.setState(False)


	def onCombatEnd(self):
		self.buffTimer.stop()


	def onShopEntered(self):
		self.onStateChanged(False)

	def _readyInit(self):
		super()._readyInit()
		self.buffTimer = self.newItemTimer("BuffTimer", "buffEnded", False)
		self.blind = int(self.getP("blind"))
		self.manaNeeded_base = int(self.getP("manat"))
		self.manaCostIncrease = int(self.getP("mana"))
		self.maxUses = int(self.getP("max"))


_R.reg("res://gd_core_items/Exclusive/ShinyMantle.gd", Exclusive__ShinyMantle)
_R.reg("ShinyMantle", Exclusive__ShinyMantle)
