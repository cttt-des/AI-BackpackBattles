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
	from ..._rt import GodotObject  # 纯 py 补绑；编译态 pxd 已预绑

from ... import _registry as _R
if "_base_cls_Exclusive__HogusBogus" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__HogusBogus





class Exclusive__HogusBogus(_base_cls_Exclusive__HogusBogus):

	resource_path = "res://gd_core_items/Exclusive/HogusBogus.gd"

	def _init_fields(self):
		super()._init_fields()
		self._phase = 0
		self.maxStaminaUsed = None
		self.buffsPerStamina = None

	@property
	def phase(self):
		return self._phase
	@phase.setter
	def phase(self, v):
		self._phase = int(v)

	def onPrepare(self):
		self.phase = 0


	def trigger(self):
		self.setState(self.phase + 1)
		super().trigger()




	def canUseStamina(self):
		return True


	def doCooldownEffect(self):
		_div__loc = _div
		if self.phase == 1:
			curStamina = self.character().getCurrentStamina()
			step = _div__loc(1.0, self.buffsPerStamina)
			if curStamina >= step:
				numProccs = floor(_div__loc(curStamina, step))
				staminaToUse = min(curStamina, min(numProccs * step, self.maxStaminaUsed))
				self.useStamina(staminaToUse)
				self.giveRandomBuffs(gd_round(staminaToUse * self.buffsPerStamina))
			self.activate()

		elif self.phase == 2:
			self.stun(self.getP_m("dur_stun"))
			self.character().stun(self.getP_m("dur_self_stun"), self)
			self.activate()

		else:
			curHealth = self.opponent().getCurrentHealth()
			self.heal(_div__loc(curHealth * self.getP_m('heal'), 100.0))
			self.onAfterEffectFinished()


	def onStateChanged(self, _phase):
		_phase = int(_phase)
		self.phase = _phase
		if self.phase == 0:
			self.baseCooldownOverride = self.getBaseCooldownIndex(0)
		elif self.phase < 3:
			self.baseCooldownOverride = self.getBaseCooldownIndex(self.phase) - self.getBaseCooldownIndex(self.phase - 1)


	def _readyInit(self):
		super()._readyInit()
		self.maxStaminaUsed = self.getP("stamina")
		self.buffsPerStamina = self.getP("buffs")


_R.reg("res://gd_core_items/Exclusive/HogusBogus.gd", Exclusive__HogusBogus)
_R.reg("HogusBogus", Exclusive__HogusBogus)
