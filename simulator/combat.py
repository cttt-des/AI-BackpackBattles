# -*- coding: utf-8 -*-
"""combat.py — 战斗引擎主循环（对齐 Core/Game.gd + Interface/CombatTimer/CombatTimer.gd）

流程还原：
1. prepareItems: 双方 prepare + 物品 prepare（含被动）
2. activateItems (COMBAT_DELAY=2.5s 后):
   combat_start 信号 → combatTimer.start() → 双方 combatStart → item.preCombatStart
   → item.combatStart（on_start）→ item.postCombatStart
3. 主循环（60Hz）:
   物品 _physics_process（冷却推进 → trigger）→ 角色 _physics_process（体力恢复）
   → TickTimer 1s onTick（回血/中毒）→ 疲劳计时
4. endCombat: OPPONENT.curHealth<=0 → 玩家胜

物品触发顺序（对齐 Game.finishSwitchingToCombat）:
  items.shuffle() → sort by getTriggerPriority() desc
"""
from __future__ import annotations

import math
import random
from typing import Any, Dict, List, Optional

from .rng import BalancedRng
from .character import Character
from .item import Item
from .events import CombatLog
from .data import is_bag_data

# CombatTimer 常量（对齐 Interface/CombatTimer/CombatTimer.gd）
FATIGUE_TIME = 17.0          # 总战斗时限
FATIGUE_START_DELAY = 3.0    # fatigueStartTimer.start(FATIGUE_TIME - 3) → 14s 启动疲劳
FATIGUE_TICK_INITIAL = 3.0   # 首次疲劳伤害在 17s（14s 后 3s）
FATIGUE_TICK_FAST = 1.0      # 之后每 1s 一次
FATIGUE_SLOW_TIME = 60.0     # combatTime < 60 用 0.1 增长，之后 0.2

COMBAT_DELAY = 2.5           # Game.COMBAT_DELAY（回合切换倒计时，combatTimer 启动前不计时，
                              # 日志时间戳以 combat_time 为基准从 0 开始，不含此延迟）
TICK_RATE = 60.0
DELTA = 1.0 / TICK_RATE


class CombatEngine:
    """单场战斗模拟"""

    def __init__(self, player_lineup: Dict[str, Any], opponent_lineup: Dict[str, Any],
                 item_db: Optional[Dict[str, Dict]] = None,
                 character_db: Optional[Dict[str, Dict]] = None,
                 seed: Optional[int] = None,
                 max_time: float = 90.0):
        self.rng = random.Random(seed)
        self._seed = seed
        self.seed = seed
        self.player_rng = random.Random(seed if seed is not None else None)
        self.opponent_rng = random.Random((seed + 0x9E3779B9) if seed is not None else None)
        self.item_db = item_db or {}
        self.character_db = character_db or {}
        self.max_time = max_time
        self.fight_ended = False
        self.log = CombatLog(combat_delay=COMBAT_DELAY, tick_rate=TICK_RATE)

        # ---- 角色属性（含回合 HP 成长）----
        pc = self._character_stats(player_lineup)
        oc = self._character_stats(opponent_lineup)
        self.player = Character(0, player_lineup.get('meta', {}).get('name', '玩家'),
                                pc['health'], pc['stamina'], pc['regen'],
                                log=self.log, base_rng=self.player_rng)
        self.opponent = Character(1, opponent_lineup.get('meta', {}).get('name', '对手'),
                                  oc['health'], oc['stamina'], oc['regen'],
                                  log=self.log, base_rng=self.opponent_rng)
        self.player.set_opponent(self.opponent)
        self.opponent.set_opponent(self.player)

        # ---- 物品（各用所属角色 RNG）----
        self.player_items = self._make_items(player_lineup.get('backpack', {}).get('items', []),
                                             self.player_rng)
        self.opponent_items = self._make_items(opponent_lineup.get('backpack', {}).get('items', []),
                                               self.opponent_rng)
        self.player_inventory = self._place_items(self.player_items, player_lineup)
        self.opponent_inventory = self._place_items(self.opponent_items, opponent_lineup)
        self.player.set_items(self.player_items)
        self.opponent.set_items(self.opponent_items)

        # ---- 联动构建（对齐 Item.gd addToInventory：物品放入背包即建立影响关系
        #      并触发 onAffectedItemAdded，早于 prepare/onPrepare）----
        for it in self.player_items + self.opponent_items:
            it.log = self.log
        self._build_linkage(self.player_items)
        self._build_linkage(self.opponent_items)

        # ---- 疲劳状态（CombatTimer）----
        self.fatigue_started = False
        self.fatigue_counter = 0
        self.fatigue_next_tick = FATIGUE_TIME - FATIGUE_START_DELAY   # 14s
        self.fatigue_interval = FATIGUE_TICK_INITIAL                   # 3s
        self.combat_time = 0.0
        self.tick_counter = 0

        self.winner: Optional[Character] = None
        self.win_reason: str = ''
        self.player_hp_history: List[Dict[str, Any]] = []

    # ---------------- 数据解析 ----------------
    def _character_stats(self, lineup: Dict[str, Any]) -> Dict[str, float]:
        """角色属性：class_modifiers 覆盖 > characters.json > 默认；含回合成长"""
        character = lineup.get('character', 'Adventurer')
        mods = lineup.get('class_modifiers') or {}
        db_char = self.character_db.get(character, {})
        base_health = mods.get('health', db_char.get('health', 25.0))
        stamina = mods.get('stamina', db_char.get('stamina', 5.0))
        regen = mods.get('stamina_regen', db_char.get('regen', 1.0))

        # 回合 HP 成长（对齐 Game.getMaxHealthInRound / getHealthGain）
        override = lineup.get('health_override')
        if override is not None:
            health = float(override)
        else:
            rnd = int(lineup.get('round', 1))
            health = float(base_health)
            for i in range(2, rnd + 1):
                if i >= 15:
                    health += 30
                elif i >= 10:
                    health += 20
                elif i >= 5:
                    health += 15
                else:
                    health += 10
        return {'health': health, 'stamina': float(stamina), 'regen': float(regen)}

    def _make_items(self, entries: List[Dict], rng, parent_bag=None) -> List[Item]:
        """按阵容条目建物品；递归 contents（袋内物品，对齐场景树父子结构）"""
        items = []
        for e in entries:
            key = e.get('id')
            data = self.item_db.get(key)
            if data is None:
                continue
            d = dict(data)
            d['gems'] = e.get('gems', [])
            it = Item(key, d, base_rng=rng)
            it._lineup_entry = e          # 同名物品多份时按序对应
            if parent_bag is not None:
                it._bag_parent = parent_bag
            items.append(it)
            contents = e.get('contents') or []
            if contents:
                it._contents_items = self._make_items(contents, rng, parent_bag=it)
                items.extend(it._contents_items)
        return items

    def _place_items(self, items: List[Item], lineup: Dict) -> 'GridInventory':
        """把物品摆到背包网格（对齐 lineup row/col/rotation），并挂载宝石

        背包判定以物品库 category=='bag' 为准（is_bag_data），阵容 container
        标志仅作补充——背包必须占 bags 底层，普通物品才能压其上（放入包内）。

        袋内物品（_bag_parent 非空）摆到袋占格上（filled 层，对齐游戏
        「物品放进包内」：filledCells 与 bagCells 同格并存，Bag.gd
        getItemsInside 即查袋占格上的 filled 层）。阵容给了 row/col 就用
        绝对坐标（须落在袋占格内），否则在袋占格内 first-fit。
        """
        from .grid import GridInventory, rotate_and_normalize
        bp = lineup.get('backpack', {})
        grid_cfg = bp.get('grid') or {'rows': 7, 'cols': 10}
        inv = GridInventory(int(grid_cfg.get('rows', 7)), int(grid_cfg.get('cols', 10)))
        for it in items:
            if getattr(it, '_bag_parent', None) is not None:
                continue          # 袋内物品随后按袋占格摆放
            e = getattr(it, '_lineup_entry', None) or {}
            it.set_grid_position(int(e.get('row', 0) or 0), int(e.get('col', 0) or 0),
                                 int(e.get('rotation', 0) or 0), inventory=inv,
                                 is_bag=is_bag_data(self.item_db.get(it.key))
                                 or bool(e.get('container', False)))
            it.mount_gems(e.get('gems') or [], self.item_db)
        # 袋内物品：摆到所属袋的占格上
        for it in items:
            bag = getattr(it, '_bag_parent', None)
            if bag is None or not bag.occupied_cells:
                continue
            e = getattr(it, '_lineup_entry', None) or {}
            it.mount_gems(e.get('gems') or [], self.item_db)
            bag_cells = set(bag.occupied_cells)
            rot = int(e.get('rotation', 0) or 0)
            row, col = e.get('row'), e.get('col')
            if row is not None and col is not None:
                it.set_grid_position(int(row), int(col), rot, inventory=inv, is_bag=False)
                if bag_cells.issuperset(it.occupied_cells):
                    continue
                inv.remove_item(it, it.occupied_cells, is_bag=False)  # 落在袋外 → first-fit
            g = ((self.item_db.get(it.key) or {}).get('grid') or {})
            shape = rotate_and_normalize([tuple(c) for c in (g.get('collision_cells') or [[0, 0]])], rot)
            placed = False
            for (r0, c0) in bag.occupied_cells:
                abs_cells = {(r0 + dy, c0 + dx) for (dx, dy) in shape}
                if bag_cells.issuperset(abs_cells) and not (abs_cells & inv.filled.keys()):
                    it.set_grid_position(r0, c0, rot, inventory=inv, is_bag=False)
                    placed = True
                    break
            if not placed:
                # 兜底：袋占格已被同袋物品占满时仍放入首格（游戏存档数据保证一致）
                r0, c0 = bag.occupied_cells[0]
                it.set_grid_position(r0, c0, rot, inventory=inv, is_bag=False)
        return inv

    def _build_linkage(self, items: List[Item]):
        """建立背包内的物品联动关系。

        对齐 Items/Item.gd addToInventory(~1340)：cacheAffectedCells() 之后
        对每个颜色遍历 getAffectedItems(color)，登记并回调
        onAffectedItemAdded(item, color)。引擎是一次性摆好背包，故等价于
        「逐个放入」后的最终状态；战斗期缓存仍由 Item.prepare() 负责快照。

        袋内（inside）联动：遍历 getAffectedItemsInside()（实时路径，摆放已完成），
        回调 onAffectedItemInsideAdded(other)；袋子的 prepare 会再缓存一次
        （对齐 Bag.gd prepare），供战斗期 onPrepare 使用。
        """
        for color in (0, 2, 4, 7):
            for it in items:
                try:
                    affected = it.get_affected_items_nocache(color)
                except Exception:  # noqa: BLE001
                    continue
                for other in affected:
                    if other is None or other is it:
                        continue
                    it.on_affected_item_added(other, color)

        # 袋内联动落地下桩（B3：containment 建模后自动激活）
        for it in items:
            try:
                inside = it.get_affected_items_inside()
            except Exception:  # noqa: BLE001
                continue
            for other in inside:
                if other is None or other is it:
                    continue
                it.on_affected_item_inside_added(other)

    # ---------------- 战斗主流程 ----------------
    def run(self) -> 'CombatEngine':
        # 对齐 Game.gd combatEnd 的 ropeSpeedups/cubeAdvanced.clear()（Game.gd:2970）：
        # 战斗级全局状态每场清空，保证场与场之间隔离
        from .behavior import BEHAVIOR_GLOBALS
        _game = BEHAVIOR_GLOBALS['Game']
        _game.ropeSpeedups.clear()
        _game.cubeAdvanced.clear()
        # EventBus 派发依赖的战斗上下文（对齐 Game.combatLog / Game.fightEnded）
        _game.combatLog = self.log
        _game.fightEnded = False

        # prepareItems: 双方 prepare + 物品 prepare（含被动叠加）
        self.player.prepare(self.log)
        self.opponent.prepare(self.log)
        for it in self.player_items + self.opponent_items:
            it.log = self.log
            it.prepare()

        # activateItems: 触发顺序 = shuffle 后按 TriggerPriority 降序
        all_items = self.player_items + self.opponent_items
        random.Random(self.rng.randint(0, 2**32)).shuffle(all_items)
        all_items.sort(key=lambda it: it.trigger_priority, reverse=True)
        self.ordered_items = all_items

        self.log.combat_start(0.0)
        self.player.combat_start()
        self.opponent.combat_start()
        for it in all_items:
            it.pre_combat_start()
        for it in all_items:
            it.combat_start()
        for it in all_items:
            it.post_combat_start()

        self._record_hp()

        while not self.fight_ended and self.combat_time < self.max_time:
            self._tick()

        if not self.fight_ended:
            self._end_fight(None, 'timeout')
        return self

    # ---------------- 主循环 ----------------
    def _tick(self):
        self.tick_counter += 1
        self.combat_time = self.tick_counter * DELTA
        now = self.combat_time
        self.log.current_time = now

        # 1. 物品冷却（每物品独立 _physics_process）
        for it in self.ordered_items:
            if it.character is None or it.character.is_dead:
                continue
            it.physics_tick(DELTA, now)
            if self._check_death():
                return

        # 2. 角色物理帧（体力恢复 + 眩晕计时）
        for ch in (self.player, self.opponent):
            if ch.is_dead:
                continue
            ch.character_tick(DELTA)

        # 3. onTick（TickTimer 1s）
        for ch in (self.player, self.opponent):
            if ch.is_dead:
                continue
            ch.tick_timer_remaining -= DELTA
            if ch.tick_timer_remaining <= 0:
                ch.on_tick(now)
                ch.tick_timer_remaining = 1.0
                if self._check_death():
                    return

        # 4. buff 临时栈超时
        for ch in (self.player, self.opponent):
            for buff in ch.buffs.values():
                buff.process_timeouts(now, self.log, ch.name())

        # 5. 疲劳（CombatTimer）
        self._fatigue_tick(now)
        if self._check_death():
            return

        # 6. HP 历史采样
        if self.tick_counter % 15 == 0:
            self._record_hp()

    def _check_death(self) -> bool:
        if self.player.is_dead or self.opponent.is_dead:
            self._end_by_death()
            return True
        return False

    def _end_by_death(self):
        """endCombat 死亡判定：OPPONENT.curHealth<=0 → 玩家胜（含同死）"""
        if self.opponent.is_dead:
            self._end_fight(self.player, 'death')
        else:
            self._end_fight(self.opponent, 'death')

    # ---------------- 疲劳（CombatTimer 还原） ----------------
    def _fatigue_tick(self, now: float):
        self.fatigue_next_tick -= DELTA
        if self.fatigue_next_tick > 0:
            return
        if not self.fatigue_started:
            # startFatigue(): counter=0, tickTimer.start(3)
            self.fatigue_started = True
            self.fatigue_counter = 0
            self.fatigue_interval = FATIGUE_TICK_INITIAL
            self.log.fatigue_start(now)
        else:
            self._deal_fatigue_damage(now)
        self.fatigue_next_tick = self.fatigue_interval

    def _deal_fatigue_damage(self, now: float):
        """dealFatigueDamage — 疲劳伤害递增；先 OPPONENT 后 PLAYER"""
        if self.combat_time < FATIGUE_SLOW_TIME:
            self.fatigue_counter += 1 + math.floor(0.1 * self.fatigue_counter)
        else:
            self.fatigue_counter += 1 + math.floor(0.2 * self.fatigue_counter)

        # 双方独立伤害 = counter + 各自 bonusFatigueDamage
        p_dmg = max(0, self.fatigue_counter + self.player.get_bonus_fatigue_damage())
        o_dmg = max(0, self.fatigue_counter + self.opponent.get_bonus_fatigue_damage())
        self.opponent.take_fatigue_damage(o_dmg, now)
        self.player.take_fatigue_damage(p_dmg, now)
        self.fatigue_interval = FATIGUE_TICK_FAST
        self.log.fatigue_damage(now, self.fatigue_counter, p_dmg, o_dmg)

    # ---------------- 结束 ----------------
    def _end_fight(self, winner: Optional[Character], reason: str):
        if self.fight_ended:
            return
        self.fight_ended = True
        # 对齐 Game.fightEnded：EventBus 派发在战斗结束后停止（EventBus.gd:93）
        from .behavior import BEHAVIOR_GLOBALS
        BEHAVIOR_GLOBALS['Game'].fightEnded = True
        self.winner = winner
        self.win_reason = reason
        if winner is None:
            # 超时按剩余血量判定
            p_hp = self.player.get_current_health()
            o_hp = self.opponent.get_current_health()
            if p_hp > o_hp:
                self.winner = self.player
            elif o_hp > p_hp:
                self.winner = self.opponent
            else:
                self.winner = self.player
        # 结算后 HP（对齐 combatEndDeferred: 败者归 0，胜者至少 1）
        if self.winner is self.player:
            self.opponent.set_current_health_safe(0)
            self.player.set_current_health_safe(max(1, self.player.get_current_health()))
        else:
            self.player.set_current_health_safe(0)
            self.opponent.set_current_health_safe(max(1, self.opponent.get_current_health()))
        now = self.combat_time
        self.log.combat_end(now, 'player' if self.winner.is_player() else 'opponent', reason)

    # ---------------- 结果 ----------------
    def _record_hp(self):
        now = round(self.combat_time, 2)
        self.player_hp_history.append({
            "t": now,
            "player": round(self.player.get_current_health(), 1),
            "opponent": round(self.opponent.get_current_health(), 1),
        })

    def player_wins(self) -> bool:
        return self.winner is not None and self.winner.is_player()

    def summary(self) -> Dict[str, Any]:
        return {
            'winner': 'player' if self.player_wins() else 'opponent',
            'reason': self.win_reason,
            'time': round(self.combat_time, 2),
            'fatigue_counter': self.fatigue_counter,
            'player': {
                'name': self.player.display_name(),
                'hp': round(self.player.get_current_health(), 1),
                'max_hp': round(self.player.get_max_health(), 1),
                'stamina': round(self.player.get_current_stamina(), 1),
                'dead': self.player.is_dead,
                'buffs': self.player.get_buff_snapshot(),
                'stats': dict(self.player.stats),
            },
            'opponent': {
                'name': self.opponent.display_name(),
                'hp': round(self.opponent.get_current_health(), 1),
                'max_hp': round(self.opponent.get_max_health(), 1),
                'stamina': round(self.opponent.get_current_stamina(), 1),
                'dead': self.opponent.is_dead,
                'buffs': self.opponent.get_buff_snapshot(),
                'stats': dict(self.opponent.stats),
            },
            'timeline': {'hp_history': self.player_hp_history},
        }

    def result_json(self) -> Dict[str, Any]:
        s = self.summary()
        return {
            'version': 1,
            'meta': {
                'seed': self._seed,
                'fight_time': s['time'],
                'winner': s['winner'],
                'reason': s['reason'],
                'fatigue_counter': s['fatigue_counter'],
                'num_events': len(self.log.events),
            },
            'player': s['player'],
            'opponent': s['opponent'],
            'timeline': s['timeline'],
        }
