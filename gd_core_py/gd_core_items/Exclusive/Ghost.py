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
if "_base_cls_Exclusive__Ghost" not in globals():
	from ..Item import Item_2 as _base_cls_Exclusive__Ghost





class Exclusive__Ghost(_base_cls_Exclusive__Ghost):

	resource_path = "res://gd_core_items/Exclusive/Ghost.gd"

	def _init_fields(self):
		super()._init_fields()
		self.unhealing = None
		self.activationParticles = None


	def onPrepare(self):
		self.character().giveUnhealing(self.unhealing)


	def doCooldownEffect(self):
		useEvents = self.useRandomBuffs(1)
		if useEvents != None:
			self.heal(self.getP_m("heal"), useEvents[0])
		self.activate()


	def playPickupSound(self):
		# decomp Items/Exclusive/Ghost.gd:20 Sound.playSound_process(pickupSound, - 4, Util.randPitch(0.3) - 0.1)——GDScript 实参求值即消耗：randPitch 1 抽
		self.ctx.rng.randf_range(0.9, 1.1)
		pass


	def playDropSound(self, volume=0):
		volume += self.impactSoundVolume

		# decomp Items/Exclusive/Ghost.gd:24 Sound.playSound(dropSound, volume - 4, Util.randPitch(0.3) - 0.1)——GDScript 实参求值即消耗：randPitch 1 抽
		self.ctx.rng.randf_range(0.9, 1.1)
	def _readyInit(self):
		super()._readyInit()
		self.unhealing = _div(self.getP('unhealing'), 100.0)


_R.reg("res://gd_core_items/Exclusive/Ghost.gd", Exclusive__Ghost)
_R.reg("Ghost", Exclusive__Ghost)
