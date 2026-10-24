# np9_L2 · Girl Power 四场首分歧根因定谳（轮9，2026-10-20，阶段1 离线分析+oracle probe 对跑）

## 结论（一句话）

四场（run597_r18/run608_r18/run613_r18/run729_r14）首分歧 **不是旋转语义**：oracle 与 gd 夹具的
GP 库内受影响格集在 rot0/90/270 三种朝向下**逐格相同**（probe 实测，零差异）；唯一分歧源 =
**配方类继承（calcClassAvailability）从未落库**——受影响格内若干配方合成物的 `classes` 在
battle_items.json 仍为原始 0（None），oracle 运行时按配方继承已折算为非零（2/4/1），gd/py 两腿
直读原始值 → `isClassItem()` 判假 → GP 的 nAff 少 1～2 → `onPrepare` 的 addSpeed 变小 →
GP 首激活系统性偏晚（四场全部命中 idx30/85/101/147，oracle type102/106 提前）。

**np8 遗留的「nAff 15v16 之谜」与「占格中心旋转」假设就此消解**：r36 的「加 [3,0]」缺口已被
现行夹具生成链吸收（placement_of 的 `-min` 归一化恰等价 oracle to_global 的 CollisionMap(40,40)
+半格偏移换算），现行 fixture 的 GP affected 集四场与 oracle 真值**全同**；np8 轮4 两向旋转试验
劣化正是因为格集本来就对、再旋即错。

## 证据链（全部本次实跑/实读）

### 1. 首分歧事件（gd 侧为隔离工程现跑，非陈旧产物）

gd 隔离工程命令（产物在 probe 目录）：
```
ORACLE_ALIGN_CASES=run608_r18 ORACLE_ALIGN_SELFCHECK=0 \
ORACLE_ALIGN_OUT=<probe>/np9_L2/gd608_base ./output/godot36/Godot_v3.6-stable_win64.exe \
  --headless --path gd_core_probe --script OracleAlignBattle.gd
```
- run608_r18：首分歧 idx147 = oracle `106@3.4833 Girl Power` vs gd `105@3.5 Blueberries`
  （gd GP 首激活 4.2，全程 8 次 vs oracle 18 次）。
- run597_r18：idx101 = oracle `102@2.7667 Girl Power` vs gd `110@2.7833 Frostbite`（gd GP 首 3.2167）。
- run613_r18：idx85 = oracle `106@2.8667 Girl Power` vs gd `1@2.8667 Steel Dragon`（gd GP 首 4.05）。
- run729_r14：idx30 = oracle `106@2.2167 Girl Power` vs gd `105@2.4333 Spectral Dagger`（gd GP 首 2.5）。

### 2. oracle 运行时真值（probe_gp_np9.gd，模板=np8_K17/probe_gp.gd）

```
PROBE_RUN=<608|597|613|729> PROBE_ROUND=<18|18|18|14> PROBE_OUT=<probe>/np9_L2/gp_<run>_oracle*.txt \
ORACLE_FIGHTS_ROOT=<probe>/np9_L2/case<run> ./output/godot36/Godot_v3.6-stable_win64.exe \
  --headless --audio-driver Dummy --path oracle --script <probe>/np9_L2/probe_gp_np9.gd
```
四场 GP（player 侧，opponent 同构）：
| 场 | rot | occ | oracle affLive(库内) vs 夹具 affected | oracle nAff | 差异类物品（oracle classes vs 夹具） |
|---|---|---|---|---|---|
| 608 | 0 | (0,3) | **逐格相同**（15 格） | 3 | Strong Vampiric Potion **2 vs 0** |
| 597 | 90 | (4,2) | **逐格相同**（15 格） | 4 | Strong Vampiric Potion **2 vs 0** |
| 613 | 270 | (8,3) | **逐格相同**（含越界格 (6,-1)/(9,3) 原样保留） | 4 | Steel Dragon **4 vs 0**、Whetstone3 **4 vs 0** |
| 729 | 270 | (4,6) | **逐格相同**（15 格） | 6 | Vampiric Collar **1 vs 0** |

CLS dump 实测（oracle 运行时 `descriptor.classes`）：Strong Vampiric Potion=2(recipes=1)、
Steel Dragon=4(recipes=1)、Whetstone3=4(recipes=2)、Vampiric Collar=1(recipes=3)、
Toad=2、Staff of Unhealing=2、Shaman Mask=4、Badger Rune=4、Forging Hammer=4、Twine=32、
Chili Goobert=8、Cog=64、Scale=32；非类物品（Frostbite/Mana Orb/Rainbow Orb/King Crown 等）=127。

时序自洽校验（cd=7.0，speed=0.35×nAff，首激活≈7/(1+0.35n)）：
608 oracle n=3→3.41≈3.4833 ✓（gd n=2→4.12≈4.2 ✓）；597 n=4→2.92≈2.7667 ✓（gd n=3→3.41≈3.2167 ✓）；
613 n=4→2.92≈2.8667 ✓（gd n=2→4.12≈4.05 ✓）；729 n=6→2.26≈2.2167 ✓（gd n=5→2.55≈2.5 ✓）。

### 3. 根因定位（file:line）

**oracle 语义（真值面）**：`oracle/Items/ItemDescriptor.gd:180-202` `calcClassAvailability()`：
1. gateItem 分支：`classes==None` → `classes = gateItem.classes`；
2. 配方分支：`originatingRecipes` 非空 → 每条配方 `recipeClasses = Neutral(127)` 逐成分
   `&= ingredient.classes`（成分集=`Recipe.getAllIngredients()`，oracle/Utility/Recipe.gd:290），
   再 `classes |= recipeClasses`；
3. 兜底 `Undefined → None`。
调用点：`oracle/Sheets/ItemBook.gd:1141`（表构建后）+ `:1305-1320`（**按合成深度序**再过一遍，
浅层先收敛 ⇒ 传递链成立）。
传递链示例（608 实测吻合）：Vampiric Potion(0→127，配住 Strong Health Potion127×Blood Amulet127)
→ Strong Vampiric Potion(0→ 127&127&Cauldron(2)=2 ✓ probe 实测 2)。

**gd/py 缺失面**：`gd_core/CoreItemData.gd:326` `o.classes = int(d.get("classes", 0))` 直读原值，
全类无 calcClassAvailability 等价物；`gd_core/CoreItemData.gd:226-228` isClassItem 判原始值。
py 同构：`gd_core_py/gd_core/CoreItemData.py:316-324`。装配层 `gd_core_test/OracleAlignBattle.gd:172-227`
descriptor_of 原样透传（含 originatingRecipes 字段但不参与 classes 计算）。

**数据面（病灶）**：`assets/battle_items.json` 现值 Strong Vampiric Potion/Vampiric Potion/
Steel Dragon/Whetstone3/Vampiric Collar classes 均为 0（HEAD 亦 0 ⇒ 继承轮**从未落库**，非近期回退）。
`tools/enrich_classes.py:65-124` 已实现同款不动点继承（round3），但在当前库上从未生效。
本次离线模拟（只对当前库做继承不动点，2 轮收敛）：**恰 25 件**变更
（Strong Vampiric Potion 0→2、Vampiric Potion 0→127、Steel Dragon/Whetstone2/Whetstone3 0→4、
Vampiric/Magic/Holy Collar 0→1、Coins/Box of Prosperity/Holdall 0→127、Chain Whip/Dragonscale Armor/
Dragon Claws/Dragonskin Boots/Busted Blade/Armored×3 Puppy 0→4、Cap of Brilliance/Arcane Boots/
Thors Hammer/Automanaton/Mananana 0→64、Halberd 0→4），四场涉及的 4 件全部在列且值与 oracle
probe 实测逐一吻合。
⚠ 整库重跑 `tools/enrich_classes.py` 不可取：`--check` 实测报 CSV 基座漂移 231 件 + 继承/gate 256 件，
爆炸半径远超继承语义本身。

### 4. REG 安全性论证

REG 九场当前全绿（np8_gp.md「REG 基线未动」）。对这 25 件，gd 现值≠oracle 真值 ⇒ 若 REG 场内
存在其 class 状态消费点，REG 早已红。故 REG 绿 ⇒ 九场内无消费点 ⇒ 只加位（0→非零，false→true
方向）的继承补丁不可能打破 REG 九场。回归风险残余：继承补丁落库后个别目标场可能在 GP 之后
**出现新的更晚分歧**（其他 class 状态消费者），属预期内的「真值前移」，按既定流程逐场处理。

## 补丁方案（数据面最小修，越面声明）

1. **数据面（不在本卡文件面内 → 本卡 blocked）**：对 `assets/battle_items.json` 只做
   `tools/enrich_classes.py::apply_recipe_inheritance` 的不动点继承（预期 25 件，禁碰 CSV 基座
   重解析分支），落库前备份至 `output/_round_patches/np9_L2/`。
2. **派生表重生成**：`tools/gen_gd_core_data.py`（gd_core_runtime.json）+
   `tools/gen_fixture_from_lineup.py`（item_battle_fixture.json / oracle_align_cases.json，
   gd_core_test 与 gd_core_probe 两份）。
3. **验证**：REG 九场（脚本腿）+ 四目标场；gd/py/oracle 三方逐行比对。core 侧
   （CoreItem.gd/CoreItemData.gd）与装配层 place_one **零改动**。
4. 若继承后目标场仍有更晚分歧：回到本 probe 仪器（probe_gp_np9.gd 可复用）逐场续查，
   与 GP 语义无关。

## 本卡纪律遵守

- 阶段1 禁改文件：**产线零改动**（git status 仅会话前既有变更）。新增产物仅在：
  `output/oracle/probe/np9_L2/`（probe_gp_np9.gd、gp_<run>_oracle*.txt、case<run>/、
  gd608_base/、gd3_base/）与本笔记。
- output/oracle/fights/ 与 oracle/ 只读未动；REG 腿未跑（由脚本统一跑）；未 commit/push。
- 隔离工程 gd_core_probe 仅**运行**未改（内核文件与产线 diff=38 行且全为 np2/np3 trace 写盘
  差异，战斗语义同源；place_one/affected 通路逐行核对一致）。

## 产物索引

- `output/oracle/probe/np9_L2/probe_gp_np9.gd`：probe 仪器（np8_K17/probe_gp.gd 模板 + 库内
  affected 集/nAff/classes dump）。
- `gp_608_oracle.txt / gp_608_oracle2.txt / gp_597_oracle.txt / gp_613_oracle.txt / gp_729_oracle.txt`：
  四场 oracle 真值（GP tlmap/affLive/affCached/itemsIn/affectedItems/nAffDistinct/CLS）。
- `gd608_base/run608_r18/events.json`、`gd3_base/<3 场>/events.json`：gd 隔离工程现跑基线。
