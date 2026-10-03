# 一致性验证对接接口（真值机 ↔ engine/）

> 模拟器（engine/ 商店域 + 真值机自动化）**尚未完工**。本文冻结两边的对接契约，
> 使任一侧完成后可直接对接：真值键、输出 schema、对齐要求、diff 工具用法。
> 协议依据：[consistency_verification.md](consistency_verification.md)；
> 真值机状态：[truth_machine_bootstrap.md](truth_machine_bootstrap.md)。

## 1. 真值键（一次对局的最小完备描述）

```json
{
  "schema_version": 1,
  "fight_seed": 777,          // 开战前 Util.rng.seed + 全局 seed() 的值
  "round": 1,                 // 回合数（影响疲劳系数/属性成长）
  "character": "Ranger",      // 双方同一职业（镜像对局）；非镜像需 p_character/o_character
  "p_items": [{"name": "Wooden Sword", "row": 0, "col": 0, "rotation": 0, "gems": []}],
  "o_items": [{"name": "Wooden Sword", "row": 0, "col": 0, "rotation": 0, "gems": []}]
}
```

- **确定性边界**：跨进程同键复现被 Godot 3 字符串哈希随机化阻断；精确对照须在
  **同一 Godot 进程内**捕获/恢复 `Util.rng.state` 完成 A/B 重放（协议 v2）。
  跨进程对比降级为统计一致性（胜率/分布，协议阶段 3）。
- 物品坐标为背包格子 (row, col)，rotation 0/1，gems 为宝石名列表。
  当前真值机摆位用 `addItemByTopLeft`（顶左格），引擎 lineup 同语义。

## 2. 双方输出 schema（JSONL：首行 meta，其余为事件）

### 真值机（游戏侧，tools/truth_drive_combat.gd）

```jsonl
{"fight_seed":777,"round":1,"p_items":[...],"o_items":[...]}
{"type":1,"timestamp":1.35,"origin":"Wooden Sword_PLAYER","params":"{damage:1}","target":"0", ...}
```

- `type`：游戏 `Game.EventType` 枚举整数值（Game.gd:443 起；
  0=Activation 1=DealDamage 2=CriticalDamage 3=MissedAttack 4=TakeDamage
  12=Health 13=Stamina 99=Fatigue 100=Block 101=Lucky …）；
- `timestamp`：战斗内秒（physics 帧累计）；
- `origin`：源物品节点名（探针已做唯一化：`名称_SIDE`）；
- `params`：字符串化的 Dictionary（如 `{damage:2}` `{amount:1, reflected:False}`）。

### engine/（被测侧，tools/dump_engine_fight.py）

```jsonl
{"schema_version":1,"engine":"engine","fight_seed":777,"round":1,"character":"Ranger",
 "p_items":[...],"o_items":[...],
 "result":{"winner":"player|opponent","fight_time":8.53,"p_hp":4,"o_hp":0}}
{"t":1.4,"type":"attack","actor":"player","target":"opponent","params":{"damage":2,"crit":false,"missed":false}}
```

- `type` 为语义字符串（combat_start/item_activate/attack/missed/stack_gain/death/...）；
- `actor` 为 player/opponent（diff 工具负责与真值 origin 后缀 `_PLAYER/_OPPONENT` 对齐）；
- meta 行由 `--character/--round` 及阵容文件回显生成（见 §4 对齐要求）。

## 3. 事件映射（diff 工具的归一化层）

| 真值 type | engine type | 比对字段 |
|---|---|---|
| 1 DealDamage | attack（hit=true） | damage、时间(±0.05s)、源、暴击(2↔crit) |
| 2 CriticalDamage | attack（crit=true） | 同上 |
| 3 MissedAttack | missed | 时间、源 |
| 4 TakeDamage | （attack 的 health_damage） | 合并进 attack 行比对 |
| 99 Fatigue | attack（actor=疲劳源）/ stack | 伤害值序列 |
| 12 Health | heal（如有） | amount |
| 0 Activation | item_activate | 计数（按源） |

v1 只比对 **结局（胜负/双方血量/时长）+ DealDamage 序列**；其余事件类型计数差异列为提示项。

## 4. 对齐要求（跑 diff 前的检查单，未对齐时 diff 只报 ALIGNMENT）

- [ ] **角色三围一致**：character 同名 → maxHealth/maxStamina/staminaRegen 相等
      （首战教训：游戏侧 Ranger 30hp vs 引擎 lineup 25hp，胜负分歧由配置不符造成）；
- [ ] **物品集与位置一致**：双方 name/row/col/rotation/gems 逐项相等；
- [ ] **fight_seed 语义一致**：引擎用同值初始化其战斗 RNG 链
      （BalancedRng×4 + chanceRng/damageRangeRng 全部 reset 自该种子）；
- [ ] **round 一致**（疲劳 60s 系数、属性成长）。

## 5. 工具链（对接点）

```bash
# 1. 真值侧（Godot 3.6.2 headless；产物在 %APPDATA%\Godot\app_userdata\Backpack Battles\truth_fight.jsonl）
Godot_v3.6.2 --no-window --script tools/truth_drive_combat.gd --path <godot_project>\decompiled_full

# 2. 引擎侧（生成 lineup 后）
python tools/dump_engine_fight.py p.json o.json --seed 777 --character Ranger --round 1 -o engine_fight.jsonl

# 3. 差分（输出偏差报告 JSON + Markdown）
python tools/consistency_diff.py truth_fight.jsonl engine_fight.jsonl -o report
```

## 6. 未完工清单（任一侧完成后对接）

| 侧 | 缺什么 | 对接影响 |
|---|---|---|
| 真值机 | 同进程 A/B 重放（协议 v2：捕获/恢复 Util.rng.state）；探针参数化（从 lineup JSON 读阵容，含 gems/rotation/非镜像双职业）；战斗收尾写 result 块（winner/hp/time） | 无协议 v2 则只能统计级对比；无参数化则只能硬编码阵容 |
| engine/ | 商店域未移植（rollItems/促销/合成）；lineup 加载 character 三核对齐真值；战斗 RNG 从 fight_seed 初始化的明确入口 | 商店验证无从对起；角色不符会报 ALIGNMENT |
| diff 工具 | v1 仅结局+伤害序列；事件全类型映射、按物品归因、统计模式（N 场胜率/分布 KS）为 v2 | 绳索/Goobert 类时序问题需要全事件映射才能定位 |
