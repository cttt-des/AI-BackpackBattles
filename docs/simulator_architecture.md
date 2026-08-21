# 背包乱斗战斗模拟器 — JSON 架构规范 v3

> 本文档定义战斗模拟器的三套 JSON 架构：**阵容文件（输入）**、**物品库（静态数据）**、
> **战斗日志 + 战斗结果（输出）**。
> 战斗逻辑对齐 `decompiled_full/` 解包源码（Core/Character.gd、Core/Game.gd、Core/Buff.gd、
> Items/Item.gd、Utility/DamageSource.gd、Interface/CombatTimer/CombatTimer.gd）。
> 生成日期：2026-08-18

---

## 目录

1. [设计原则](#1-设计原则)
2. [阵容文件（输入）](#2-阵容文件输入)
3. [物品库（静态数据）](#3-物品库静态数据)
4. [效果 DSL](#4-效果-dsl)
5. [战斗日志（输出）](#5-战斗日志输出)
6. [战斗结果（输出）](#6-战斗结果输出)
7. [CLI 用法](#7-cli-用法)
8. [与解包源码的映射](#8-与解包源码的映射)
9. [已知差距与 TODO](#9-已知差距与-todo)

---

## 1. 设计原则

- **以解包源码为唯一权威**：所有数值、公式、触发顺序均从 `decompiled_full/` 源码逐行翻译，不臆测。
- **数据结构对齐游戏 descriptor**：物品库字段名尽量贴近 `ItemDescriptor.gd` 的字段
  （`minDam`/`maxDam`/`cd`/`accuracy`/`staminaCost`/`block`/`params`）。
- **输入输出分离**：阵容文件只描述"谁带了什么"（不含逻辑），物品库描述"物品是什么"（静态），
  战斗日志描述"发生了什么"（过程），战斗结果描述"结局"（结论）。
- **版本化**：所有 JSON 带 `version` 字段，未来升级不破坏旧文件。

---

## 2. 阵容文件（输入）

> 由 GUI「导出阵容」生成，或手工编写。**一场战斗需要两个阵容文件**（玩家 + 对手）。

### 2.1 完整示例

```json
{
  "version": 3,
  "meta": {
    "name": "玩家阵容-示例",
    "source": "gui_export",
    "created_at": "2026-08-18T18:00:00+08:00",
    "unknown_items": []
  },
  "character": "Ranger",
  "round": 5,
  "class_modifiers": {
    "health": 25,
    "stamina": 5,
    "stamina_regen": 1.0,
    "gold": 13
  },
  "health_override": null,
  "backpack": {
    "grid": { "rows": 7, "cols": 10 },
    "items": [
      {
        "id": "WoodenSword",
        "row": 2,
        "col": 3,
        "rotation": 0,
        "quantity": 1,
        "container": false,
        "contents": [],
        "gems": []
      },
      {
        "id": "LeatherBag",
        "row": 0,
        "col": 0,
        "rotation": 0,
        "quantity": 1,
        "container": true,
        "contents": [
          { "id": "Dagger", "row": 0, "col": 0, "rotation": 0, "quantity": 1, "gems": [] }
        ],
        "gems": []
      }
    ]
  },
  "storage": []
}
```

### 2.2 字段说明

| 字段 | 类型 | 必填 | 说明 |
|---|---|---|---|
| `version` | int | ✓ | 固定 `3` |
| `meta.name` | str | | 阵容名（日志展示用） |
| `meta.source` | str | | `gui_export` / `manual` |
| `character` | str | ✓ | 职业 key（见 `assets/characters.json`） |
| `round` | int | ✓ | 当前回合（用于 HP 成长计算） |
| `class_modifiers` | obj | | 覆盖职业基础值；缺省时从 `characters.json` 读取 |
| `class_modifiers.health` | int | | 基础最大 HP（角色 `.tres` 中 `health`，全职业 25） |
| `class_modifiers.stamina` | int | | 基础最大体力（默认 5） |
| `class_modifiers.stamina_regen` | float | | 体力恢复/秒（默认 1.0） |
| `health_override` | int/null | | 直接指定本场战斗 HP（无视回合成长），测试用 |
| `backpack.grid` | obj | ✓ | 背包尺寸 |
| `backpack.items` | array | ✓ | 摆盘物品列表 |
| `backpack.items[].id` | str | ✓ | 物品 key（必须存在于物品库） |
| `backpack.items[].row/col` | int | ✓ | 左上角格坐标 |
| `backpack.items[].rotation` | int | | 旋转角度（0/90/180/270） |
| `backpack.items[].quantity` | int | | 数量（默认 1） |
| `backpack.items[].container` | bool | | 是否为背包容器 |
| `backpack.items[].contents` | array | | 容器内物品（递归同构） |
| `backpack.items[].gems` | array | | 镶嵌宝石（`["Ruby", "Sapphire"]`） |
| `storage` | array | | 储物箱物品（战斗不参与，预留） |

### 2.3 回合 HP 成长（对齐 Game.getMaxHealthInRound）

```
基础 HP = class_modifiers.health（默认 25）
从第 2 回合起每回合增加：
  回合 >= 15 → +30
  回合 >= 10 → +20
  回合 >= 5  → +15
  其他       → +10
```

模拟器实际 HP = 基础 HP + 第 2..round 回合的成长总和（`health_override` 非空时直接采用）。

---

## 3. 物品库（静态数据）

> 文件：`assets/battle_items.json`（`{"items": {...}}`），由 `simulator/build_data.py` 从
> `assets/items_db_sim.json`（483 个真实物品的 wiki 数据）生成，并叠加解包脚本的行为推导。

### 3.1 完整示例

```json
{
  "items": {
    "Dagger": {
      "key": "Dagger",
      "zh": "匕首",
      "size": [1, 2],
      "category": "weapon",
      "damage_type": "melee",
      "min_dam": 2,
      "max_dam": 5,
      "cd": 1.0,
      "accuracy": 95,
      "crit": 0.0,
      "stamina_cost": 0.8,
      "block": 0,
      "trigger_priority": 0,
      "types": ["weapon", "melee"],
      "effect": { "type": "attack" },
      "effects": [],
      "triggers": [],
      "on_start": null,
      "passive": null,
      "source": "wiki",
      "script": "Dagger.gd"
    },
    "Banana": {
      "key": "Banana",
      "zh": "香蕉",
      "size": [2, 2],
      "category": "food",
      "damage_type": "effect",
      "min_dam": 0,
      "max_dam": 0,
      "cd": 5.0,
      "accuracy": 100,
      "crit": 0.0,
      "stamina_cost": 0.0,
      "block": 0,
      "trigger_priority": 0,
      "types": ["food"],
      "effect": {
        "effects": [
          { "type": "heal", "amount": 4 },
          { "type": "gain_stamina", "amount": 1 }
        ]
      },
      "effects": [],
      "triggers": [],
      "on_start": null,
      "passive": { "regen": 3 },
      "source": "wiki",
      "script": "Banana.gd"
    }
  }
}
```

### 3.2 字段说明

| 字段 | 类型 | 说明 |
|---|---|---|
| `key` | str | 物品标识（英文，与脚本文件名一致） |
| `zh` | str | 中文名 |
| `size` | [int,int] | 占格尺寸 [宽,高] |
| `category` | str | `weapon`/`food`/`potion`/`shield`/`bag`/`armor`/`utility`/`pet` |
| `damage_type` | str | `melee`/`ranged`/`effect`（伤害源类型） |
| `min_dam` / `max_dam` | int | 基础伤害范围 |
| `cd` | float | 基础冷却秒数（0 = 无冷却不自动触发） |
| `accuracy` | float | 命中率 % |
| `crit` | float | 额外暴击率 %（物品自带） |
| `stamina_cost` | float | 每次攻击消耗体力 |
| `block` | int | 格挡值（盾牌） |
| `trigger_priority` | int | 触发优先级（对齐 Item.getTriggerPriority） |
| `types` | [str] | 物品类型标签（weapon/melee/ranged/food/potion/bag/shield...） |
| `effect` | obj | 冷却触发的效果（doCooldownEffect 语义，见 §4） |
| `effects` | [obj] | 附加效果（与 effect 合并执行） |
| `triggers` | [obj] | 条件触发器（对齐 connectForCombat，见 §4.2） |
| `on_start` | obj/null | 战斗开始时效果（onCombatStart） |
| `passive` | obj/null | 被动数值（如食物 `{"regen": 3}`，战斗开始前叠加） |
| `source` | str | 数值来源：`wiki`/`script`/`TODO` |
| `script` | str | 对应解包脚本文件名 |

---

## 4. 效果 DSL

> 物品行为用声明式 DSL 描述，引擎解释执行。对齐解包脚本的
> `doCooldownEffect()` / `onTriggerPotion()` / `connectForCombat()` 语义。

### 4.1 冷却触发效果（effect / effects[]）

`effect` 是单个效果对象，或 `{"effects": [...]}` 组合列表。每个效果对象：

```json
{ "type": "attack" }
{ "type": "heal", "amount": 4 }
{ "type": "gain_stamina", "amount": 1 }
{ "type": "deal_effect_damage", "amount": 6, "source_type": "effect" }
{ "type": "gain_stacks", "buff": "poison", "amount": 2, "target": "opponent" }
{ "type": "gain_stacks", "buff": "block", "amount": 3, "target": "self" }
{ "type": "drain_stamina", "amount": 1, "target": "opponent" }
{ "type": "stun", "duration": 1.5, "target": "opponent" }
{ "type": "gain_max_health", "amount": 5 }
{ "type": "give_crit_tokens", "amount": 1 }
{ "type": "give_dodge", "amount": 1 }
{ "type": "change_damage_resistance", "amount": 10 }
{ "type": "change_damage_reduction", "amount": 2 }
{ "type": "empower_weapons", "amount": 1 }
{ "type": "cleanse_debuff", "buff": "poison", "amount": 3 }
{ "type": "random_buff", "options": ["block", "stamina", "lucky"] }
{ "type": "fatigue_damage", "amount": 1 }
```

通用字段：

| 字段 | 说明 |
|---|---|
| `type` | 效果类型（下表） |
| `amount` | 数值 |
| `target` | `self`（默认，效果施加者）/ `opponent` |
| `buff` | buff 类型名：`block`/`lucky`/`regen`/`vampirism`/`spikes`/`mana`/`empower`/`heat`/`poison`/`blind`/`cold` |
| `source_type` | 伤害源类型（`melee`/`ranged`/`effect`） |
| `duration` | 眩晕/临时栈时长（秒） |
| `chance` | 概率（0-100，缺省 100） |

### 4.2 条件触发器（triggers[]）

对齐 `onPrepare()` 里的 `connectForCombat(character(), "character_damaged", "onDamaged")`：

```json
{
  "on": "character_damaged",
  "source": "self",              // self / opponent
  "if": { "relative_health_lt": 0.5 },
  "action": { "type": "consume_and_effect", "effect": { "type": "heal", "amount": 25 } }
}
```

| 字段 | 说明 |
|---|---|
| `on` | 触发事件：`character_damaged` / `character_healed` / `character_stunned` / `character_pre_use_stamina` / `pre_take_damage` / `character_attacked` / `on_tick` |
| `source` | 监听对象：`self` / `opponent` |
| `if` | 条件（缺省恒真） |
| `action` | 触发动作（效果 DSL 或 `consume_and_effect` 药水语义） |
| `consume` | 药水：动作执行后置空 |

### 4.3 战斗开始效果（on_start）

对齐 `onCombatStart()`，战斗开始瞬间执行一次：

```json
{ "on_start": { "type": "gain_stacks", "buff": "vampirism", "amount": 1, "target": "self" } }
```

### 4.4 武器模板（Weapon）

`category=weapon` 且 `effect.type=attack` 时，引擎走 Weapon 模板（对齐 Weapon.gd）：

```
doCooldownEffect():
    if useStamina(stamina_cost) == Sufficient:   # 体力不足 → 记录 OutOfStamina，不攻击
        attack()
attack():
    damageSource.updateItem(self)
    res = character().dealDamage(damageSource)   # 命中/暴击/格挡/反伤/吸血全流程
    activate()
```

---

## 5. 战斗日志（输出）

> 输出文件：`<阵容A>_vs_<阵容B>_log.json`
> 事件模型对齐 `Core/CombatEvent.gd` + `Core/CombatLog.gd` 的 `createEvent_*` 系列。

```json
{
  "version": 1,
  "meta": {
    "seed": 42,
    "tick_rate": 60,
    "combat_delay": 2.5,
    "max_time": 90.0,
    "started_at": "2026-08-18T18:10:00+08:00"
  },
  "setup": {
    "player": { "name": "玩家阵容-示例", "character": "Ranger", "max_health": 25, "stamina": 5, "items": ["WoodenSword", "LeatherBag"] },
    "opponent": { "name": "对手阵容", "character": "Ranger", "max_health": 25, "stamina": 5, "items": ["Dagger"] }
  },
  "events": [
    {
      "id": 0,
      "t": 2.50,
      "type": "combat_start",
      "actor": null,
      "target": null,
      "origin": null,
      "params": {}
    },
    {
      "id": 1,
      "t": 2.50,
      "type": "stack_gain",
      "actor": "player",
      "target": "player",
      "origin": "Banana",
      "params": { "buff": "regen", "amount": 3, "permanent": true }
    },
    {
      "id": 2,
      "t": 2.52,
      "type": "attack",
      "actor": "player",
      "target": "opponent",
      "origin": "Dagger",
      "params": { "hit": true, "critical": false, "damage": 4, "health_damage": 4, "block_absorbed": 0, "stamina": 4.2 }
    },
    {
      "id": 3,
      "t": 2.52,
      "type": "missed",
      "actor": "opponent",
      "target": "player",
      "origin": "WoodenSword",
      "params": {}
    },
    {
      "id": 4,
      "t": 3.50,
      "type": "tick",
      "actor": "player",
      "params": { "kind": "regen", "amount": 3 }
    },
    {
      "id": 5,
      "t": 14.00,
      "type": "fatigue_start",
      "params": {}
    },
    {
      "id": 6,
      "t": 17.00,
      "type": "fatigue_damage",
      "params": { "counter": 1, "player_damage": 1, "opponent_damage": 1 }
    },
    {
      "id": 7,
      "t": 18.00,
      "type": "death",
      "actor": "opponent",
      "params": {}
    }
  ]
}
```

### 5.1 事件类型（type）

| type | 含义 | 关键 params |
|---|---|---|
| `combat_start` | 战斗开始（COMBAT_DELAY=2.5s 后） | |
| `combat_end` | 战斗结束 | `winner`, `reason` |
| `stack_gain` / `stack_lose` | buff 栈增减 | `buff`, `amount`, `permanent`, `duration` |
| `stack_timeout` | 临时栈超时 | `buff`, `amount` |
| `attack` | 攻击命中 | `hit`, `critical`, `damage`, `health_damage`, `block_absorbed` |
| `critical` | 暴击（damage 已乘倍率） | 同 attack |
| `missed` | 未命中 | |
| `spikes` | 反伤 | `damage` |
| `vampirism` | 吸血 | `amount` |
| `heal` | 治疗 | `amount`, `overheal` |
| `unhealing` | 不治反伤 | `damage` |
| `stamina_gain` / `stamina_use` / `stamina_drain` | 体力变化 | `amount` |
| `out_of_stamina` | 体力耗尽（未攻击） | |
| `stun` / `stun_end` | 眩晕 | `duration` |
| `invulnerable_start` / `invulnerable_end` | 无敌 | `duration` |
| `block_break` | 格挡被击破 | `amount` |
| `tick` | 每 1s tick（回血/中毒） | `kind` (`regen`/`poison`), `amount` |
| `fatigue_start` | 疲劳开始（14s） | |
| `fatigue_damage` | 疲劳伤害 | `counter`, `player_damage`, `opponent_damage` |
| `item_activate` | 物品激活（技能动画事件） | |
| `death` | 角色死亡 | |
| `reincarnate` | 复活 | `amount` |

### 5.2 事件字段

| 字段 | 说明 |
|---|---|
| `id` | 自增序号（对齐 CombatEvent.id） |
| `t` | 战斗时间（秒，含 COMBAT_DELAY 偏移） |
| `type` | 事件类型 |
| `actor` | 行动方：`player` / `opponent` / null |
| `target` | 受影响方：`player` / `opponent` / null |
| `origin` | 来源物品 key / 来源类型 |
| `params` | 结构化参数（上表） |
| `parent` | 父事件 id（触发链，对齐 parentEvent，可选） |

---

## 6. 战斗结果（输出）

> 输出文件：`<阵容A>_vs_<阵容B>_result.json`

```json
{
  "version": 1,
  "meta": {
    "seed": 42,
    "fight_time": 18.02,
    "winner": "player",
    "reason": "death",
    "fatigue_counter": 2,
    "num_events": 128
  },
  "player": {
    "name": "玩家阵容-示例",
    "character": "Ranger",
    "max_health": 25,
    "health": 25,
    "dead": false,
    "stamina": 4.6,
    "buffs": { "regen": 3, "poison": 0 },
    "stats": {
      "damage_dealt": 32,
      "damage_taken": 18,
      "healing_done": 4,
      "crits": 1,
      "misses": 2,
      "activations": 5,
      "out_of_stamina": 0
    }
  },
  "opponent": {
    "name": "对手阵容",
    "character": "Ranger",
    "max_health": 25,
    "health": 0,
    "dead": true,
    "stamina": 0.0,
    "buffs": { "poison": 1 },
    "stats": {
      "damage_dealt": 10,
      "damage_taken": 32,
      "healing_done": 0,
      "crits": 0,
      "misses": 1,
      "activations": 3,
      "out_of_stamina": 1
    }
  },
  "timeline": {
    "first_blood": 2.52,
    "last_event_t": 18.02,
    "hp_history": [
      { "t": 2.5, "player": 25, "opponent": 25 },
      { "t": 5.0, "player": 25, "opponent": 21 }
    ]
  }
}
```

### 6.1 胜负判定（对齐 Game.endCombat）

```
OPPONENT.curHealth <= 0  → 玩家胜 (Win)
否则                     → 玩家负 (Loss)
```

- `reason`: `death`（一方 HP≤0）/ `fatigue`（疲劳致死）/ `timeout`（超过 max_time 兜底，按剩余 HP 高者胜）
- 双方同时死亡 → 玩家胜（原版 OPPONENT.curHealth<=0 判定优先）

---

## 7. CLI 用法

```bash
# 战斗：两个阵容文件
python -m simulator.simulate lineup_A.json lineup_B.json
python -m simulator.simulate lineup_A.json lineup_B.json --seed 42 --outdir output/

# 输出
#   output/lineupA_vs_lineupB_log.json     战斗过程日志
#   output/lineupA_vs_lineupB_result.json  战斗结果
#   output/lineupA_vs_lineupB_log.txt      人类可读日志

# 蒙特卡洛：多次取样
python -m simulator.simulate lineup_A.json lineup_B.json --runs 100
```

---

## 8. 与解包源码的映射

| 模拟器组件 | 解包源码 | 还原要点 |
|---|---|---|
| `simulator/combat.py` | `Core/Game.gd` (prepareItems/activateItems/endCombat) + `Interface/CombatTimer/CombatTimer.gd` | 战斗生命周期、疲劳计时、胜负判定 |
| `simulator/character.py` | `Core/Character.gd` | takeDamage 全流程、命中/暴击/格挡、反伤/吸血、体力、onTick |
| `simulator/buff.py` | `Core/Buff.gd` | 栈增减、抗性/反射、临时栈超时 |
| `simulator/item.py` | `Items/Item.gd` + Weapon/Food/Potion/Shield | 冷却推进、trigger、doCooldownEffect、体力消耗 |
| `simulator/damage.py` | `Utility/DamageSource.gd` + `DamageResult.gd` | 伤害源 flags/类型、暴击倍率（BASE_CRIT_SEVERITY=2.0） |
| `simulator/rng.py` | `Utility/BalancedRandom.gd` | 平衡随机（accuracyRng/critRng） |
| `simulator/events.py` | `Core/CombatEvent.gd` + `CombatLog.gd` | 事件模型、日志输出 |

### 关键公式（源码直译）

```
冷却推进:   triggerTime -= delta * getSpeed()        # Item._physics_process
getSpeed:   speed_ = (heat - cold) * 0.02
            modified = 1.0 + speed_  (speed_ >= 0)
                      1.0 / (1.0 - speed_)  (speed_ < 0)
            clamp(modified, 0.1, 10.0)
冷却随机:   adjustCooldown = cd * uniform(0.95, 1.05)
命中率:     getAccuracy = base_accuracy + bonus_accuracy + (lucky - blind) * 5
伤害:       randDamage = randint(getMinDamage, getMaxDamage)
            getMinDamage = ceil(minDam + bonusMinDam) + empower
                          * typedDamageFactor  * bonusDamageFactor
暴击:       damage *= critSeverity (=2.0)
抗性:       damage = round(damage * (1 - clamp(damageResistance/100, -10, 1)))
减伤:       damage -= damageReduction (仅攻击类)
格挡:       Block 栈优先吸收
反伤:       spikeDam = min(spikes, round(damage * spikesLimit))
吸血:       healAmount = min(vampirism, round(damage * vampLimit))
体力恢复:   1.0/s（每物理帧 addStamina(regen * delta)）
tick:       每 1s：偶数 tick 回血(regen)，奇数 tick 中毒(poison)
疲劳:       14s 开始；17s 首次伤害 counter=1+floor(0.1*counter)；
            之后每 1s，counter += 1+floor(0.1*counter)（<60s）或 1+floor(0.2*counter)
```

---

## 9. 已知差距与 TODO

1. **物品数值精度**：当前 `battle_items.json` 数值来自 wiki（`items_db_sim.json`），部分物品
   （合成/联动类）数值标注 `TODO`，需从加密 `ItemData_e.csv`（GDEC+sheetKey 混淆）提取后补齐。
2. **联动/合成物品**：受物品影响格子（affected cells）的联动效果（如笛子加速、链式触发）
   尚未在 DSL 中完整表达，`affected` 机制为 TODO。
3. **护盾/反伤限制**：`meleeSpikesLimit` 等限制系数已建模，但物品赋予途径待全量枚举。
4. **宝石系统**：`gems[]` 已入阵容格式，引擎解析为 TODO。
5. **职业专属机制**：狂战士之怒、工程师电荷、焰术使热量等职业被动为 TODO。
6. **可复现性**：BalancedRng 已实现；物品触发顺序 = shuffle 后按 TriggerPriority 降序，
   已在引擎还原（seed 固定可复现）。
