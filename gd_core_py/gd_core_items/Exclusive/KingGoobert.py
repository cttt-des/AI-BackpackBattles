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
if "_base_cls_Exclusive__KingGoobert" not in globals():
	from ..Goobert import Goobert_2 as _base_cls_Exclusive__KingGoobert





class Exclusive__KingGoobert(_base_cls_Exclusive__KingGoobert):

	resource_path = "res://gd_core_items/Exclusive/KingGoobert.gd"

	CrownState = EnumDict("CrownState", {"Inactive": 0, "Active": 1, "Used": 2})



	def _init_fields(self):
		super()._init_fields()
		self._invuCharges = 0
		self.protectedBuffs = None
		self.manaCost = None
		self.activationParticles = None
		self.buffTimer = None
		self.light = None

	@property
	def invuCharges(self):
		return self._invuCharges
	@invuCharges.setter
	def invuCharges(self, v):
		self._invuCharges = int(v)

	def prepare(self):
		gemPower = _div(self.getP('gempower'), 100.0)
		for gem in _iter(self.getGemsNoNull()):
			gem.changeGemPower(gemPower)

		self.invuCharges = self.getP("charges")
		self.setState(self.CrownState.Inactive)
		super().prepare()


	def doCooldownEffect(self):
		self.character().changeBuffProtectStacks(self.protectedBuffs)
		self.heal()
		if self.invuCharges > 0 and self.character().isVulnerable() and self.checkMana(self.manaCost):
			self.invuCharges -= 1
			self.setState(self.CrownState.Active, True)
			invuDur = self.getP_m("dur_invu")
			event = self.character().makeInvulnerable(invuDur, self)
			self.buffTimer.start(invuDur)
			self.useMana(self.manaCost, event)


	def buffEnded(self):
		if self.invuCharges > 0:
			self.setState(self.CrownState.Inactive, True)
		else:
			self.setState(self.CrownState.Used, True)


	def onCombatEnd(self):
		self.buffTimer.stop()


	def onShopEntered(self):
		self.onStateChanged(self.CrownState.Inactive)


	def onStateChanged(self, _crownState):
		if _crownState == self.CrownState.Inactive:
			pass

		elif _crownState == self.CrownState.Active:
			pass

		else:
			pass

	def _readyInit(self):
		super()._readyInit()
		self.protectedBuffs = self.getP("buffs")
		self.manaCost = self.getP("mana")
		self.buffTimer = self.newItemTimer("BuffTimer", "buffEnded", False)


_R.reg("res://gd_core_items/Exclusive/KingGoobert.gd", Exclusive__KingGoobert)
_R.reg("KingGoobert", Exclusive__KingGoobert)
