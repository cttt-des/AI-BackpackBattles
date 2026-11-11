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
if "_base_cls_Exclusive__Pop" not in globals():
	from ..Weapon import Weapon_2 as _base_cls_Exclusive__Pop





class Exclusive__Pop(_base_cls_Exclusive__Pop):

	resource_path = "res://gd_core_items/Exclusive/Pop.gd"

	def _init_fields(self):
		super()._init_fields()
		self.previousSpeedBonus = 0.0
		self.speedPerMana = None
		self.maxSpeedBonus = None


	def onPrepare(self):
		self.previousSpeedBonus = 0
		self.connectForCombat(self.character(), "character_mana_changed", "onManaChanged")


	def onManaChanged(self, _amount, _event):
		speed = min(self.maxSpeedBonus, self.speedPerMana * self.character().getMana())
		if speed - self.previousSpeedBonus != 0:
			self.addSpeed(speed - self.previousSpeedBonus)
			self.previousSpeedBonus = speed


	def playPickupSound(self):
		# decomp Items/Exclusive/Pop.gd:21 Sound.playSound_process(popSound, 4, Util.randPitch(0.15))——GDScript 实参求值即消耗：randPitch 1 抽
		self.ctx.rng.randf_range(0.9, 1.1)
		pass


	def playDropSound(self, volume=0):
		volume += self.impactSoundVolume

		# decomp Items/Exclusive/Pop.gd:25 Sound.playSound(popSound, volume - 0, Util.randPitch(0.15))——GDScript 实参求值即消耗：randPitch 1 抽
		self.ctx.rng.randf_range(0.9, 1.1)
	def _readyInit(self):
		_div__loc = _div
		super()._readyInit()
		self.speedPerMana = _div__loc(self.getP('speed'), 100.0)
		self.maxSpeedBonus = _div__loc(self.getP('max'), 100.0)


_R.reg("res://gd_core_items/Exclusive/Pop.gd", Exclusive__Pop)
_R.reg("Pop", Exclusive__Pop)
