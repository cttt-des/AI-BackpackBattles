# np4_HOLD — run1347_r18 Holdall 开局格挡分歧留档（blocked）

日期：2026-10-18
卡片：修复·Holdall开局格挡（目标场 run1347_r18）
结论：**blocked** —— 根因落在 `assets/battle_items.json` 的 `classes` 数据层（文件面之外），
gd_core_items/ 的 Holdall 脚本与 oracle 逐字一致、无可改处。未做任何代码改动（无备份需要还原）。

## 1. 分歧事实（本卡给定 + 现场复核）

- 事件首分歧 ev=15 t=0：oracle `Holdall` 出 type=100 Block amount=16（ev15，owner=1；
  对手侧镜像同款 ev48）；gd 同位置是 `Snowball` Cold 2，且**全场 0 条 Holdall 事件**（两侧都没有）。
  证据：`output/oracle/probe/np3_or4b/run1347_r18/events.json` vs
  `output/oracle/align/np3c/run1347_r18/events.json`（json `.events` 全表扫描）。
- 抽取首分歧第 450 抽（`python -X utf8 tools/_probe_draw_diff.py
  output/oracle/probe/np3_or4b/run1347_r18/rng_log.txt output/oracle/align/np3c/run1347_r18/rng_trace.txt 15`）：
  449 抽前逐抽全对齐；@450 O 出 `(-10,10)`、G 出 `(0.9,1.1)`——gd 少了 Holdall
  giveBlock/activate 分支对应的抽取，后续整体错位。与「gd 侧 Holdall 整个没触发」一致。

## 2. 脚本面对读（结论：无差异、无可改）

- `oracle/Items/Exclusive/Holdall.gd:3-10` 与 `gd_core_items/Exclusive/Holdall.gd:3-11`：
  `canApplyEffect = toItem.isNeutral()`；`onCombatStart: block = getBlock() * getNumAffectedInside()，
  >0 才 giveBlock+activate`。两文件 diff 仅空行/注释。
- 调用链两侧一致：`Bag.getNumAffectedInside`（oracle/Items/Bag.gd:281-286 ≙
  gd_core_items/Bag.gd:185-189）→ `getAffectedItemsInside`（oracle Bag.gd:176-192 ≙ gd Bag.gd:100-111，
  内含 `if not placed: return []` 与缓存回退）→ `canApplyEffect`。
- `getBlock()`：oracle/Items/Item.gd:3956-3957 `return descriptor.block` ≙
  gd_core/CoreItem.gd:1354-1357。`isNeutral()`：oracle/Items/ItemDescriptor.gd:160-161
  `classes == StuffedClasses.Neutral(127)` ≙ gd_core/CoreItemData.gd:221-222。

## 3. 根因定性：包内物品 classes 数据错（assets 层，非内核、非 gd_core_items）

gd 侧装配（`gd_core_test/oracle_align_cases.json` run1347 条目，现场读取）：

- Holdall occupied = [[4,0],[4,1],[5,0],[5,1],[6,0],[6,1]]（6 格，3×2）。
- 包内（占格相交）4 件：Spectral Dagger(4,0)、Steel Dragon(4,1)、Tiger Rune(6,0)、Shaman Mask(6,1)。
- `assets/battle_items.json` classes：Spectral Dagger=**0**、Steel Dragon=**0**、Tiger Rune=**4**、
  Shaman Mask=**4** —— 无一为 127(Neutral) ⇒ gd `getNumAffectedInside()=0` ⇒ `block=0` ⇒
  走不进 `if block > 0` ⇒ 无事件。与观察完全吻合。

oracle 侧反推 amount=16：

- Holdall block=8（battle_items.json 与解密 CSV 一致）；**crafted 不翻倍**——全语料按 crafted
  分组统计（现场脚本）：crafted=False 的 Holdall amount 集合={24,32}，crafted=True={8,16,24,32,40}，
  8/24/40 均非 16 的倍数 ⇒ 排除「crafted block×2」⇒ 16=8×**2**，oracle 真值把包内恰好 2 件当 Neutral。
- 哪 2 件？run782_r18（gd==oracle 场，gdcore 根）夹具几何：包内={Heroic Potion(127), Tiger Rune,
  Steel Dragon}，双方都只数 1（=Heroic Potion）⇒ **oracle 真值 Steel Dragon、Tiger Rune 非 127**。
  ⇒ run1347 的 2 件 = **Spectral Dagger 与 Shaman Mask 在 oracle 真值里 classes==127**，
  而 battle_items.json 给的是 0 与 4。
- gd 链路本身是好的：gdcore 根 346 个 Holdall 事件对比中，除 run1347 外全部 gd==oracle
  （如 run1352_r13：oracle N=4 == DB 中立数 4；run1371_r18：3==3）。唯一翻车场正是这四件数据错的场。

## 4. 数据层的三条伴生事实（修复时必须知道）

1. **解密 CSV 不可当真源**：`decompiled_full/Sheets/CSV/ItemData_e.csv` 的 `shop` 列与 oracle
   真值大面积不符——已证反例：Stone Helm（CSV shop='no'，语料 run1352 计入 ⇒ 真值 127；
   battle_items.json=127 ✓）、Falcon Blade（run1371 计入 ⇒ 127；JSON=127 ✓）、Snowball（run1099 计入）。
   真源 `oracle/Sheets/CSV/ItemData_e.csv` 是 GDEC 加密（现场探测头字节 `GDEC`），离线读不了；
   `class_override` 列解密版仅 7 行非空，显然残缺。
2. **gd 消费点**：`gd_core/CoreItemData.gd:326` `o.classes = int(d.get("classes", 0))` 直接吃
   battle_items.json；`gd_core/CoreItemData.gd:221-222` isNeutral 判 `==127`。
   `tools/enrich_classes.py`（读解密 CSV shop 列）不是现库 classes 的来源（Snowball CSV='no'→应 0，
   库里=127），来源待考——修数据时先把 provenance 查清，别拿 enrich_classes 重跑覆盖。
3. **包中包不计入**：oracle 把「包内的包」排除在计数外（run1568_r18：包内 DB 中立 4 件 =
   Fanny Pack(bag)+Heroic Potion+Strong Heroic Potion×2，oracle 只数 3=非 bag 的 3 件；
   该场在 gdcore 根 gd==oracle）⇒ gd 现行为与 oracle 同口径，**不是本分歧的因子**，
   但做第 5 节的全量约束求解时必须带上这条规则，否则解不出唯一真值集。

## 5. 可能解法（留给后续数据卡 / 内核卡）

1. **主修（数据面）**：把 `assets/battle_items.json` 的 classes 改成 oracle 真值。已钉死的两个键：
   Spectral Dagger 0→127、Shaman Mask 4→127（run1347 双侧量守恒 + run782 排除法）。
   同批建议全语料约束求解（用「包中包不计入」+ 宝石 socket 后 occupiedCells 清空两条规则重建几何）
   把 172 个 Holdall 约束全解干净；解密 CSV 不可作依据，真源在 GDEC（oracle/Sheets/CSV/）。
   改完须重生 `assets/gd_core_runtime.json`（tools/gen_gd_core_data.py，脚本统一执行）。
2. **py 侧独立缺陷（另一张卡）**：`output/oracle/align/py/` 全部 172 个 Holdall 事件对比
   oracle=N、gd(py)=0（含 run1347、run1044 等本已对齐场）——gd_core_py/simulator 引擎里
   Holdall 从不触发或 isNeutral 恒假，与本次 GDScript 侧分歧无关，别混在一个修复里。
3. **不建议**：在 gd_core_items/Exclusive/Holdall.gd 里手写物品白名单绕过 classes——
   会偏离 oracle 脚本逐字移植口径，且污染 Twine.gd 等其他 isNeutral 消费方。

## 6. 本卡动作清单

- 未改任何代码 ⇒ 无备份写入 output/_round_patches/np4_HOLD/（空）。
- 回归电池 REG 九场未跑（未改码，无回归面；脚本统一执行属验证方职责）。
- 判据未放宽：分歧定位全部基于渲染事件（events.json canonical 对读）与逐抽 diff 工具。
