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
if "_base_cls_Exclusive__SerpentStaff" not in globals():
	from ..Weapon import Weapon_2 as _base_cls_Exclusive__SerpentStaff





class Exclusive__SerpentStaff(_base_cls_Exclusive__SerpentStaff):

	resource_path = "res://gd_core_items/Exclusive/SerpentStaff.gd"

	def _init_fields(self):
		super()._init_fields()
		self.damageAcc = 0
		self.manaUseEvents = []
		self.manaCost = None
		self.permDamBonus = None
		self.poison = None
		self.damageForPoison = None


	def onPrepare(self):
		self.manaUseEvents.clear()
		self.opponent().changeResistChance(_H_1, - self.getChance())


	def onPreDealDamage_early(self, damageRes):
		manaUseEvent = self.tryUseMana(self.manaCost)
		if manaUseEvent != None:
			self.addBonusDamage(self.permDamBonus)
			self.manaUseEvents.append(manaUseEvent)


	def onDealtDamage(self, damageRes):
		if damageRes.hasHit() and not (not self.manaUseEvents):
			self.damageAcc += damageRes.damage
			curPoison = _div(self.damageAcc, self.damageForPoison)
			if curPoison > 0:
				self.damageAcc %= self.damageForPoison
				self.inflictPoison(curPoison, damageRes.event)
			self.manaUseEvents.pop()

	def _readyInit(self):
		super()._readyInit()
		self.manaCost = self.getP("mana")
		self.permDamBonus = self.getP("dam")
		self.poison = self.getP("poison")
		self.damageForPoison = int(self.getP("damforpoison"))


_R.reg("res://gd_core_items/Exclusive/SerpentStaff.gd", Exclusive__SerpentStaff)
_R.reg("SerpentStaff", Exclusive__SerpentStaff)


# ── S3-C4 类引用提升（生成器发射；目标=唯一 stem/祖先/gd_core 树，模块末绑定）──
try:
	_H_1 = _R.C("CoreConst").EventType.Poison
except AttributeError as _he:
	_H_1 = _HoistPending(_he)
