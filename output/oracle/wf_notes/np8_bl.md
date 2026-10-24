# np8_bl · 盲批早 N tick 机制全景留档（轮2 深挖，2026-10-19）

## 已钉死的 oracle 机制（一手证据）
1. **注册表动态收编**：战斗中新建 Timer 节点经 `_on_node_added`（oracle_fight.gd:985-988）登记
   [left,left]；`_on_node_removed` 擦除（:991-993）。rebuild 期（:957-976）一次性收集静止 Timer。
2. **驱动语义**（drive_timers :880-905）：每遍 `e[1]=eng`（引擎读数快照）；eng≠e[1]（外部
   start/changeTimer）→ 影子 e[0]=eng 重同步；否则 e[0]-=dt。fire=e[0]<=0。
3. **新建 Timer 的重同步延迟**：node_added 时若 Timer 尚未 start（Buff.gd 先 add_child 再
   start），登记 [0,0] → 下一驱动遍 eng≠e[1] 才重同步到 dur ⇒ 新批实际倒数起点=创建后的
   第一个驱动遍（0-1 帧 grace）。
4. oracle 每批=独立 Timer 节点（Buff.gd:32-35），各自倒数各自 fire；gd=单计时器+批列表
   （tos=[amount@expire]）FIRE 时 POP（np8_a BSCHED 实测）。

## run986 对表数据（np8_a trace vs 语料）
- 前 4 个 FIRE 对齐（5.017×2/6.017×2）；**oracle 在 2.033/2.067/4.100/4.150 有 109 负事件
  而 gd FIRE 序列无**——这些是净化（CLEANSE）弹出，非到期 fire；gd 6.533s0 的 Banner 批
  在 oracle 轴无同刻对应（oracle 最近=6.483o1 与 7.100o0）。
- 每侧多批+净化交织，逐批对齐需 origin 级过滤（BSCHED 桩不带 origin 名——改进桩可加）。

## 下一步（供以后认领）
1. BSCHED 桩加 origin/side→owner 映射与批 source（GAIN 来源物品），oracle 侧事件按 origin
   过滤出 Banner/Goobert 到期序列，双侧逐批对表定差。
2. 重点验证「新建 Timer 重同步延迟」在 gd 的对应（gd GAIN 即从 dur 倒数=**早 0-1 帧**；
   与实测早 3-7 tick 不完全吻合 ⇒ 主差疑在 POP 选批/多批同刻次序而非单纯倒数起点）。
3. ⚠CoreBuff 历史敏感：单笔+run634/run688 反例锚+REG 九场闸门。

## 现状
未改码；REG 基线未动；r39 全量在跑。
