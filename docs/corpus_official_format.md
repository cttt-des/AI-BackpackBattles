# bpb.iotun.com 语料解码（官方格式）

> **重要修正**：本文档取代早期的 `corpus_items_decoder.md`。
> 早期版本靠手工猜字节，得出过**错误结论**（以为语料是"去重轨迹"）。
> 作者后来公开了官方解码器 `decode_corpus.py` 和 `README.md`，下面以官方为准。

## 一、数据概况（本项目只入库日期分片）

| 项目 | 数值 |
|---|---|
| **入库分片** | **49 个日期分片**（2026-09-17 ~ 2026-11-04） |
| **入库局数** | **55,352** |
| **入库轮次** | **744,549** |
| **入库物品行** | **19,669,553** |
| 版本 | 全部 1.1.9 |
| 库体积 | 3.0 GB |

> **undated 分片暂不解析**（用户决定）。它包含 613,226 局，需要时用
> `ingest_corpus(..., dated_only=False)` 显式开启。
> 注意 `undated_parts/` 与 `undated.bin.gz` 是同一份数据，任选其一，不要重复统计。

入库口径与官方 README 完全吻合：局数 55,352、轮数 744,549 ✅

## 二、正确的解码方式

### 直接使用官方解码器

```bash
python decode_corpus.py 2026-09-27.bin.gz -o runs.jsonl
python decode_corpus.py 2026-09-27.bin.gz --limit 2 --pretty
python decode_corpus.py --all corpus/shards --summary
```

输出一行一局的 JSON，可直接 `json.loads` / `pandas.read_json(lines=True)` / jq 读。

### 为什么不要自己解析

格式是「自定义二进制帧容器 + gzip」，帧内是 TLV。我早期尝试手工解析，
把 `0x10 + face` 当成物品标志——那其实是 `packed(16) + face(0..3)` 的巧合位组合。
结果：遇到带宝石、带附加字段的物品就整体错位，还错误地得出了"语料是轨迹不是快照"的结论。

**官方 `rounds` 就是逐轮完整快照**，我此前的判断是错的。

## 三、字段说明（官方）

| 字段 | 含义 |
|---|---|
| `rating` | 段位分 |
| `class` | 0 Ranger / 1 Reaper / 2 Berserker / 3 Pyromancer / 4 Mage / 5 Adventurer / 6 Engineer |
| `entry_version` | 游戏版本（全部 1.1.9） |
| `results` | 18 位：**0=胜 / 1=负 / 2=平 / 3=未进行** |
| `rounds` | **逐轮快照**，第 i 项 = 第 i+1 轮**战斗前**盘面 |
| `rounds[i].health` | 血量**上限**（战斗掉血不在语料里） |
| `rounds[i].stamina` | 耐力上限 |
| `rounds[i].items` | 该轮**全量**物品 |
| `items[].gid/x/y/f` | 物品编号 / 左上角格坐标 / 朝向(0-3) |
| `items[].g` / `pd` | 镶孔宝石编号列表 / 宝石朝向串（可选） |
| `run_id` | 排行榜 UUID（**undated 里是占位值 `"1"`**） |
| `corpus_key` | **去重身份键**，undated 必须用这个 |
| `score_seq` | 采集序号 |
| `snapshots` / `sources` / `source` | 采集快照名 / 来源（`sw`） |
| `pool` / `main_pool` | `ranked`；`rating >= 300` 的主池标记 |
| `problems` / `meta_ok` | 解析问题计数 / 元数据校验位（正常 0 / true） |
| `values` | 逐轮阵容价值（参照值） |

**棋盘**：`(x, y)` 是 9 列 × 7 行棋盘的左上角格坐标，`(0,0)` 在左上。

## 四、与游戏原生数据的对照验证

用 `runs_steam.cache`（游戏自己下载的排行榜缓存）对照官方解码结果：

```
官方: {gid:68, x:3, y:2, f:0}   ← 第一轮
游戏: {gid:68, x:3, y:2, f:0}   ✅ 一致
```

官方解码器的 `rounds[i].items` 与游戏 bitstream 解出的摆盘**逐件吻合**。

## 五、我们这边的实现

`gripper/src/bpb_research/corpus/`：

| 模块 | 作用 |
|---|---|
| `official.py` | 直接包装官方解码器（`iter_rows` / `iter_corpus` / `summarize`） |
| `store_official.py` | 可选入库到 SQLite（批量插入 + 延迟建索引） |

```python
from bpb_research.corpus.official import iter_rows, summarize
from pathlib import Path

for row in iter_rows(Path("database/corpus/2026-09-27.bin.gz")):
    print(row["rating"], len(row["rounds"]), "轮")
```

### 入库性能

| 方式 | 速率 |
|---|---|
| 逐条 `execute` | 10 局/秒 |
| **批量 `executemany` + 延迟建索引** | **约 78 局/秒** |

日期分片（55,352 局）实际入库耗时约 12 分钟，产出 3.0 GB。

### 数据库结构（已精简）

```sql
corpus_runs   -- 13 列：record_key/rating/rating_bucket/class_id/class_name/
              --        snapshots_json/results_json/values_json/
              --        rounds_played/round_snapshots/items_total/score_seq/shard
corpus_rounds -- 5 列：record_key/round_no/health/stamina/item_count
corpus_items  -- 9 列：record_key/round_no/seq/gid/x/y/face/gems_json/pd
```

去重键 `record_key`（= 官方 `corpus_key`）。

**精简掉的零信息量字段**（2026-11-06 清理，库从 5.50 GB → 3.83 GB）：

| 删除字段 | 原因 |
|---|---|
| `player_name` | 全空（官方脱敏） |
| `run_id` / `corpus_key` | 与 `record_key` 完全等价 |
| `entry_version` | 全为 1.1.9 |
| `pool` | 全为 ranked |
| `source` / `sources_json` | 全为 sw |
| `problems` | 全为 0 |
| `meta_ok` | 全为 1 |
| `main_pool` | 可由 `rating >= 300` 推导 |

> 需要这些字段时重新入库即可（`store_official.py` 的 SCHEMA 已同步精简；
> 若要恢复旧字段，从 `database/corpus/` 重跑入库）。

## 六、数据限制（官方明确说明）

- **没有过程信息**：商店买了什么、刷新几次、金币多少、物品怎么挪动——都没有
- **`health` 是上限**，不是战斗剩余血量
- **只有 1.1.9 版本**
- 同一局在多快照重复时会去重，保留更完整的一份

### 能做什么

| 用途 | 可行性 |
|---|---|
| 逐轮摆盘（物品+坐标+朝向+宝石） | ✅ **完整可用** |
| 段位/职业/轮次胜负分析 | ✅ |
| 物品使用频次与位置偏好 | ✅ |
| **局内决策（买卖/刷新/金币）** | ❌ 语料不含 |

## 七、md5 核对

官方提供 `SHA256SUMS`（177 条），逐文件可校验：

```bash
sha256sum -c SHA256SUMS
```

全部主分片合并指纹：`b3c3507ab7a4b2c8e767e7122d89ca9e64c7a64a50b7490143dc56ebe497aaad`

## 八、旧文档作废

`docs/corpus_items_decoder.md` 中的以下结论**已推翻**：

- ❌ "语料记录的是去重轨迹，无法还原逐轮摆盘" → **错误**，官方 rounds 就是完整快照
- ❌ "field = 0x10 + face" → 那是 packed 位标志的巧合
- ❌ "平均 139.5 物品/记录" → 实际应按轮统计