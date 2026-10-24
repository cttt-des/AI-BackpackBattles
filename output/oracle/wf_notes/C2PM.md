# K19/K23 PM 魔法/充能 ×4 取证修复笔记（修复手-C2PM，2026-10-17）

场：run1101_r18(idx172)、run1280_r18(idx150)、run1331_r18(idx112)、run1530_r18(idx122)。
结论：**fixed**（卡面内修复，未跑正式验证）。

## 一、分歧形态（语料对拍实证）

方法同 C1MF：`output/oracle/fights/<场>/events.json` vs
`output/oracle/align/gdcore/<场>/events.json` difflib 全事件对拍
（key=timestamp/type/origin.name/params/parent）。

- 四场首分歧均为 PM（Perpetuum Mobile）首个 doCooldownEffect 组缺失/迟到：
  - run1101（t=3.35）：O 有 PM T105 amount=8 + T13 stamina=0.7 + T0 激活；
    G 直接跳到 Thunder Drake（damage 10 vs O 5——魔法层数差传导）。
  - run1280（t=4.633）：O 有 PM T105×2（resisted 1+实得 2）+T107+T13 0.3；
    G 无（在跑 Charge Splitter T107）。
  - run1331（t=3.8）：O 有 PM T13 stamina=0.3+T0；G 无（跳到 t=3.9167）。
  - run1530（t=3.6167/3.6333）：双方两个 PM 各一组 T13 0.3+T0；G 全缺。
- **G 侧 PM 并非零事件**：开场 T20（giveMaxStaminaTemporary 2）+T0 两侧逐字同构
  → onCombatStart 链与 _readyInit 参数化（stamina=2/refund=30%/speed=30%）完好。
- G 侧 PM 首个周期触发**迟到近一倍**：run1331 O 3.8s vs G 6.9s；G 首触发返还账
  为累积大头（T105×5+T107×3+T13×0.8）——周期慢→账久积→一次吐大。

## 二、机制链（代码对读+py 重放实证）

- PM 周期机：`gd_core/CoreItem.gd:631-641` preCombatStart（hasCooldown →
  iterationCooldown=adjustCooldown、triggerTime 同值、activateCooldown）→
  physicsTick（:736-743，`triggerTime -= delta*getSpeed()`）→ trigger（:878-885）→
  PM 覆写 doCooldownEffect（giveStacks+giveStamina+activate）。↔
  `oracle/Items/Item.gd:3360-3370,4413-4425` 同构。
- 速度面：`gd_core/CoreItem.gd:376-398` getSpeed = 1+speed_（speed_≥0），
  speed_=speedScale+(heat−cold)×0.02；speedScale 只由 PM.onPrepare 的
  `addSpeed(speed_v × getNumAffectedItems())` 注入（PerpetuumMobile.gd:21）。
  ↔ `oracle/Items/Item.gd:3729-3752,4865-4870` 同构。
- **py 重放实证**（gd_core_py 单场装配后内存查，未落盘）：
  run1331_r18 双方 PM `speedScale=0.0、numAffected=0、affected=[]`（修前）；
  修复后 `speedScale=0.9、numAffected=3`（affected=Spin to Win/Charge Splitter/Coil）。
- 摆位（run1331 lineups v3）：双方 PM (r0,c4)，Primary affected 4 格=上越界空+
  左(0,3)+右(0,5)+下(1,4)。该三格被 4 格 Leather Bag 占据，**袋内容物**
  Charge Splitter(class 64)、Spin to Win(96)、Coil(64) 与袋共格——内核
  getItemsInCells 返回袋内容物（全部含 Engineer 位 64）。oracle 反推
  numAffected=3 → speed 1.9 → 周期≈4.4s（含 adjustCooldown randf 0.95-1.05 与
  heat 修正，与 O 语料 3.35-4.63s 吻合）；G 侧 numAffected=0 → speed 1.0 →
  周期≈8.4s，与 G 语料 6.9-7.2s（含 heat-cold 修正）吻合。

## 三、根因（定谳）

`gd_core/CoreItemData.gd:223-224`：

```gdscript
func isAvailableFor(classId: int) -> bool:
	return (classes & classId) != 0
```

丢原版 stuffed 转换。oracle `oracle/Items/ItemDescriptor.gd:86,153-155`：

```gdscript
static func stuffClassIndex(classI): return 1 << classI
func isAvailableFor(classId): return isAvailableForStuffed(stuffClassIndex(classId))
func isAvailableForStuffed(classId): return bool(classes & classId)
```

调用链 `Item.isClassItem(Classes_Full.Engineer=6)`（两侧 Item 层同构，
`gd_core/CoreItem.gd:1601` ↔ `oracle/Items/Item.gd:973`）：
`descriptor.isClassItem() and descriptor.isAvailableFor(6)`。

- oracle：stuff(6)=64 → `classes(64) & 64` = True ✓
- gd/py：`(64 & 6) == 0` → **恒 False** ✗

→ PM.canAffect（PerpetuumMobile.gd:9-10）对一切 Engineer 类物品恒假 →
numAffected=0 → addSpeed(0) → 周期慢近一倍 → 四场首分歧。

排除面：
- _readyInit 参数化 vs onready 等价性（卡面提示面）：两侧开场 T20 stamina=2
  逐字同构，参数传递完好，排除。
- getAffectedItems/getItemsInCells/格子账：py 实证返回袋内容物正确，排除。
- activate/cooldown 开关：setCooldownActive(false) 仅 combatEnd；构造后查询
  cdActive=False 系 activateItems 延迟 2.5s 未跑（查询时机），排除。
- stamina/refund 数值面：T13 金额与 usedStacks 累积形态 O 侧自洽，排除。

## 四、修复（卡面文件面内，行为等价内联）

根因文件 `CoreItemData.gd/.py` 不在本卡文件面（ gd_core_items/Exclusive/
PerpetuumMobile.gd + py 镜像），**未动**；Laboratory.gd 同域隐患一并记档。

`gd_core_items/Exclusive/PerpetuumMobile.gd:9-19` canAffect 改为内联 oracle
Item.isClassItem(6) 完整语义（行为逐位等价，绕过内核缺陷谓词）：

```gdscript
return item.descriptor.isClassItem() and (item.descriptor.classes & (1 << CoreConst.Classes_Full.Engineer)) != 0
```

- 与 oracle `isClassItem(6)` 同果：isClassItem() 门（剔 Neutral=127/None=0）+
  `classes & (1<<6)`。内联 `1 <<` 不依赖 isAvailableFor 未来语义——若日后
  CoreItemData.isAvailableFor 补上 stuffClassIndex（正确修法，届时 Laboratory
  一并愈），本行结果不变，无潜伏冲突。
- py 镜像：`python tools/gd_to_py.py` 全树重转写（先 `--check` 确认过期面仅
  本卡 1 文件，其他泳道 gd/py 同步，无覆盖风险），转写后 `--check` 全绿。
- 备份：`output/_round_patches/wf_C2PM/PerpetuumMobile.gd.bak`、
  `PerpetuumMobile.py.bak`（修前原样）。

## 五、修后自证（gd_core_py 重放，非正式验证）

正式判定归验证员串行通道；以下为内存重放（不落 align/py）：

| 场 | py_events | oracle_events | winner(py/oracle) |
|---|---|---|---|
| run1331_r18 | 636 | 636 | opponent/opponent ✓ |
| run1280_r18 | 778 | 778 | player/player ✓ |
| run1530_r18 | 578 | 578 | player/player ✓ |
| run1101_r18 | 892 | 961 | opponent/opponent ✓ |

run1331 PM 事件 39=oracle 39（修前 28）；首触发=T13 stamina 0.3（=O[112] t=3.8）。
**run1101 残余**：事件数未全同（892<961），赢家已对。临时口径线性扫描至
t=0 段只见转录口径噪声（int/float、origin 折叠 null vs key），残余真差
需验证员 canonical/_origin_canon 口径定位（疑次级面：该场 17s+ 长战，后段
物品交互）；不在本卡文件面再扩。

## 六、脏残留检查

改动面：`gd_core_items/Exclusive/PerpetuumMobile.gd`（canAffect 一处+注释）、
`gd_core_py/gd_core_items/Exclusive/PerpetuumMobile.py`（gd_to_py 重转写产物）。
gd_core/CoreItemData.gd/.py 未动（文件面外）。零探针/trace/print 桩。
本轮全部对拍/重放为内存级（python），未写 align 任何目录、未跑 Godot、
未跑 verify_oracle.py、未动夹具。
