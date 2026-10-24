# GEN1 修复卡收口：战斗中物品生成/替换引擎链（r35 K05/K07/K14/K15 族）

日期：2026-10-17　泳道：修复手-GEN1　卡面文件=gd_core/CoreGrid.gd、gd_core/CoreItemData.gd、gd_core_items/Exclusive/AmuletofFeasting.gd、gd_core_items/Exclusive/AmuletUnidentified.gd 及各自 gd_core_py 镜像

## 根因

战斗中物品生成/替换引擎链在 gd_core 整体缺失（定谳复验成立）：

1. `gd_core/CoreGrid.gd` 无 replaceItem（oracle 参考=oracle/Core/Inventory.gd:803-827）。
2. `gd_core/CoreItemData.gd` 无 generateItem（oracle 参考=oracle/Sheets/ItemBook.gd:408-413，=instantiateItem+统计）。
3. `gd_core/CoreItem.gd:3353` placeGeneratedItem 为 pass 空桩。
4. gd 双护符脚本是死桩：AmuletofFeasting.getReplaceDescriptor 恒 null（oracle=ItemBook.getFoodOfRarity，ItemBook.gd:1437-1444）；AmuletUnidentified.identifyAmulet=pass（oracle :16-37=generateItem+inventory.replaceItem）。同族旁证：DragonEgg.hatch_deferred（oracle Items/DragonEgg.gd:76=replaceItem+generateItem，gd=pass）、Lootbox.generateItems（gd=pass）。

doCooldownEffect 链核对结论：oracle 侧 Feasting/Unidentified 均**无** doCooldownEffect 覆写，替换触发面在现 oracle 树=商店购买（Shop.gd:869/881）/拖放入包（onDropped→identifyAmulet）/合成（Recipe.gd:238），Item.trigger→doCooldownEffect（Item.gd:4409-4424）不达它们；gd 战斗 drop 链全 no-op（gd_core_items/Item.gd:918）→ 战斗内两侧当前均无自然触发点。本轮落地=引擎判定面+护符入口面，战斗触发接线属装配/触发层后续卡。

## 修改

- CoreGrid.gd：+aroundOffsets（Inventory.gd:42 九方向逐字）/+canAddItemCells（:203-219 战斗子集）/+addItemByTopLeft/+replaceItem（:803-827 步骤序逐字对齐，通知序=clearItemCells→items.erase→全体 onItemRemoved；零 rng；getCraftingOffset/discard 带 has_method 守卫）。
- CoreItemData.gd：+generateItem（resolveBehaviorScript().new()→setup 双绑定 BalancedRng 惯例（sceneDepth 下限 2）→_readyInit；不入包，由调用方 replaceItem 落格）+resolveBehaviorScript（gd_core_items 与 oracle Items 同构布局，Exclusive 优先→根目录→回退 Item.gd；字面量按「斜杠贴引号/%s」安全形态拆写规避转写器 / 字符兜底误判）。
- AmuletUnidentified.gd：identifyAmulet=oracle :16-37 判定面（pickRandomElement 恒 1 抽→generateItem→replaceItem/discard→finishReplacement）+AMULET_NAMES 九名（ItemBook.gd:108-118 逐字）+amuletDescriptors。
- AmuletofFeasting.gd：getReplaceDescriptor=getFoodOfRarity 判定面（Epic flip±1→pickRandomElement；池=注册表内同稀有度实注册 Food 描述符按实例去重；抽序恒定，池空退化 null=改前行为）。
- py 镜像：tools/gd_to_py.py 全树重转写×2（幂等复验）；修复初转毁伤「res://gd_core_items/Exclusive」→res://_div(...)（改 gd 源字面量形态后复转）；python -m py_compile 四镜像 4/4 过；print 桩 0；git 面恰=卡面 8 文件。
- 备份：output/_round_patches/wf_genitem/*.gd.bak（md5 校验后才动刀）。

## 验证数

- 回归电池 7 场（run570_r18,run1160_r18,run1029_r2,run862_r18,run813_r12,run635_r18,run732_r12 中判定行=run570_r18,run1160_r18,run1029_r2,run862_r18,run813_r12,run635_r12,run732_r12）：**全绿，回归红场=[]**。
- 本批 aligned=7/16；16=9 目标+7 回归，7 绿全为回归场。
- 工检开局：9 验证场在 output/oracle/alignment.json 全 `oracle≠gdcore`，无一三方一致。

## 残余（目标场 9 场红，判定=green 收口按规则记录）

目标场 run907_r15,run1126_r5,run846_r11,run895_r10,run686_r18,run1375_r11,run1083_r18,run1198_r18,run1410_r18 残余红。归因（GEN1 取证实录）：

1. **代际漂移（主因，先于行为差）**：corpus events.json（10-07 03:31）与今日重导 lineups.json（10-17 12:22）/gd 夹具 oracle_align_cases.json（10-17 16:07）在格位级物品身份不一致。实证 run895_r10：corpus 事件多出物品是格位实体 Amulet of Light@(5,5)/False Life@(0,3)/Spicy Banana@(5,6)/Pine Protector@(2,2)；今日夹具同格位=Time Melting@(5,6)/Blueberries@(1,3) 且无任何护符。与台账 r35 K03「corpus↔树漂移」同族。引擎链修完也造不出 corpus 时代的另一批物品——需 oracle 侧同代际重放 events 后再判。
2. **装配层义务未接**：生成族描述符（食物/护符族）须预注册进 ctx.item_book（否则 getDescriptor 惰性占位=零值数值）；战斗内触发点（谁调 getReplaceDescriptor/identifyAmulet/replaceItem）须装配/触发层接线——均在后续卡文件面。
3. 抽消耗面已按「与注册完整度无关」设计（flip/pick 次数恒定），装配层接线后不会因池退化二次伤链。
