# gripper 采集链路（Windows 修复版）

原工程是 WSL + uv + Godot 导出包注入，本机不适用。这里是**已实测跑通**的 Windows 实现。

## 一键使用

双击 **`一键刷新采集.bat`** → 输入间隔（默认 **60** 分钟）与轮数（0=无限）→ 完全后台运行。
停止：`停止采集.bat`。

## 数据来源与规模

只读 `%APPDATA%/Godot/app_userdata/Backpack Battles/runs_steam.cache`。
**必须经 Steam 启动**游戏（`steam://rungameid/2427700`），游戏才会自己拉排行榜。

实测：启动后 **39~80 秒**缓存刷新，**每轮几乎全是新数据**（滚动窗口）：

| 采集轮次 | 累计场次 | Master+ |
|---|---|---|
| 1 轮 | 2000 | 64 |
| 2 轮 | 4000 | 125 |

## 排行榜口径（重要）

- 榜单 `bpb-runs3`，score 是**递增上传序号**，取前 2000 条 = **最近上传的 2000 局**
- **不是**"最高分 2000 名"，也**不按段位筛选**
- 实测分布：Diamond 33%、Platinum 24%、Gold 12%、Master+ 约 3%
- `statisticsMode = 60000` 是**死代码**（`Statistics.gd` 不在游戏包里），无法开启
- 扩大采集量唯一可行路径 = **定时反复采集累积**（每次刷新都是新对局）

## 数据库字段

### runs 表

| 字段 | 含义 | 备注 |
|---|---|---|
| `run_id` | `source:缓存sha:序号` | 主键 |
| `rating` | 段位积分 | **核心字段**，-1000 = 未排名 |
| `rating_bucket` | 段位名 | Bronze～Grandma |
| `class_id` / `class_name` | 职业 | flag5 → Classes_Full 枚举 |
| `player_name` | 玩家名（**原始编码态**） | 6bit+62 偏移 |
| `player_name_decoded` | 玩家名（**解码后可读**） | suzuki / flos / 中文名 |
| `player_id` | 每场唯一随机串 | 实测 2000 场 2000 个不同值，**不可作玩家维度** |
| `record_version` | 记录版本 | 如 1.1.9 |
| `outcome_json` | 逐轮结果 | 0=负 1=胜 3=未到 |
| `chibi` | 是否 Q 版造型 | 1/0 |
| `skins_json` | 皮肤槽位 | `[Head,Weapon,Body,Special,Shoes]`，各 0-15 |
| `rounds` | 局数 | |
| `content_sha` | 内容指纹 | 跨批次去重 |

### rounds 表

`run_id, round_no, health, stamina, items_json, result`

### items 表

`run_id, round_no, slot, name, x, y, face, gid, gems_json`

## 缓存数组的完整字段语义

来自 `RunData.serialize()` / `fromSerialized()`，10 个元素逐一对应：

| 下标 | 字段 | 含义 |
|---|---|---|
| [0] | runId | 榜上序号（全为 1） |
| [1] | encodedName | 玩家名（编码态） |
| [2] | rating | 段位分（-1000=未排名） |
| [3] | playerId | **每场随机**，不是固定玩家标识 |
| [4] | results | 18 轮结果码（0负/1胜/3未到） |
| [5] | characterClass | 职业 ID（0-6） |
| [6] | rounds | **逐轮 bitstream 数组**（真正的摆盘数据） |
| [7] | entryVersion | 记录版本（1.1.9） |
| [8] | chibiStyle | 是否 Q 版 |
| [9] | skins | 5 个皮肤槽：Head/Weapon/Body/Special/Shoes |

## 职业映射（flag5）

游戏 `Game.gd` 的 `Classes_Full` 枚举，实测验证：

| flag5 | 职业 | 验证依据 |
|---|---|---|
| 0 | Ranger | Ranger Bag |
| 1 | Reaper | 无专属包 |
| 2 | Berserker | Berserker Bag |
| 3 | Pyromancer | 无专属包 |
| 4 | Mage | Scholar Bag |
| 5 | Adventurer | Bag of Giving |
| 6 | Engineer | Engineer Bag 2 |

## 技术要点（都是踩过的坑）

| 问题 | 真相 | 对策 |
|---|---|---|
| 必须经 Steam 启动 | 直跑 exe 时 Steam 虽 status:1，但不认"游戏运行中"，不下发排行榜 | `steam://rungameid/2427700` |
| 启动弹 3 次 `OpenMem failed` | 搜狗输入法**注入游戏的 DLL** 调的 MessageBox（类 `#32770`） | 看门狗检测到就发 `BM_CLICK` 按掉 |
| 不用鼠标 | 会抢用户光标 | 全程 Win32 消息 |
| 缓存二进制难解析 | Godot `store_var` 格式，手工解析会错位 | **让 Godot 自己 `get_var()` 导出 JSON** |

### 缓存结构（Godot get_var 出来的）

每条 run = 10 元素数组：

```
[0] int 标记      [1] 玩家名(str)   [2] rating(float)  [3] 短串
[4] 18元素结果码  [5] 职业ID(int)   [6] 逐轮bitstream数组  ← 真正的摆盘数据
[7] 版本(str)     [8] bool          [9] 5元素数组(皮肤?)
```

**注意 `[3]` 不是 metadata**（只有十几字符），逐轮数据在 `[6]`。

## 采集流程

```
Steam 启动 → 看门狗按弹窗 → 等缓存刷新(240s) → 关游戏
→ Godot 导出 JSON(含 rating) → 解码摆盘 → 按内容指纹去重 → 入库 → 导出
```

## 产物

- `database/staging.sqlite`：runs / rounds / items
- `database/dataset/`：runs.jsonl / items.jsonl / stats.json
- `output/collect_logs/run_*.log`：运行日志
- `output/last_run.json`：最近结果

## 自检

```bash
cd gripper/src && python -m bpb_research.collect.selftest
```

## 只读约束

原游戏目录**零写入**。弹窗处理只发窗口消息，不改游戏文件、不动鼠标。
