# C4QUAD（K11/K18/K21/K22 四物品包泳道）取证收口

## 结论
四物品（DoomCap / GoldArmor / SpellScrollLight / Snowmaster）脚本与神谕逐行同构，**卡面内零可修差**；
八场红全由卡面外三域造成 → status=blocked（详见 output/alignment_fix_log.md「r35 K11/K18/K21/K22 取证」节）。

## 逐物品
| 物品 | 场 | 首分歧 | 根因域 | 卡面外落点 |
|---|---|---|---|---|
| DoomCap | run741_r9 | idx99 | A: PotM advanceTime→疲劳 5.033s（语料恒 17.017s） | CoreCombat.advanceTime / PotM / harness 骨架 |
| DoomCap | run1036_r18 | idx451 | C: Burning Banner 盲批 py 早 1 tick 整弹 | CoreBuff 四分支模型残差（K01） |
| GoldArmor | run986_r12 | idx235 | B: Lightsaber idle_frame 饥饿→语料恒单 proc，py 复触发 | CoreUtil.callNextFrame / Lightsaber / harness |
| GoldArmor | run1377_r13 | idx164 | C: Light Goobert 盲批早弹→净化账/给块分叉 | CoreBuff（K01） |
| SpellScrollLight | run1191_r13 | idx86 | A: 同上（下游才轮到其 idx86 净化保护 +1 protected） | 同 A |
| SpellScrollLight | run1192_r14 | idx165 | A: 同上 | 同 A |
| Snowmaster | run1231_r18 | idx195 | C: Goobert 盲批早弹（语料 5.3 弹-4，py 4.467 弹-7） | CoreBuff（K01） |
| Snowmaster | run1444_r18 | idx330 | C: Frostbolt 冷批早弹→resisted 翻转 | CoreBuff（K01） |

## 关键证据（本泳道实跑）
- canon 对拍：import tools/verify_oracle.py 纯函数（canonical_stream/_tuple_of），语料
  output/oracle/fights/<case>/events.json vs output/oracle/align/py/<case>/events.json；
  八场复算首分歧 99/451/235/164/86/165/195/330 与 alignment.json 精确同位。
- 语料全库扫描（917 场，python 只读）：Lightsaber 每场每 owner used-proc 恒 1（0 多 proc）；
  疲劳首发 <17s 的 137 场阵容均无 PotM（另一机制，疑跨场计时器残留，移交 K01）。
- 语料疲劳 t0 恒 17.017（含 PotM 场）；run1191 语料 idx345/347 PotM T19+152@17.017 证明
  fatigue_start 连接有效、advanceTime 无效（oracle_bootstrap.gd:108 Combat=无脚本 Node2D）。
- 物品事件两侧内容全同（run1036 O451=P452；run986 py244/245=O235/236 仅移位）。

## 根因假设（三域，均已在语料侧定谳）
- 域A（PotM/疲劳，run741_r9+run1191_r13+run1192_r14）：gd 真实现 advanceTime(6)（CoreCombat.gd:469），
  语料侧 advanceTime 无_op（oracle_bootstrap.gd:108 Combat 节点无脚本）→ 疲劳 5.033 vs 17.017。
- 域B（Lightsaber idle_frame，run986_r12）：语料阻塞 tick 循环下 idle_frame 永不发
  （oracle_fight.gd:697 + Util.gd:814）→ endBlindingLight 永不跑 → 语料光剑恒单 proc；
  gd 忠实模拟 ctx.defer（CoreUtil.gd:191，:176 注释自证）→ py 复触发带歪全流。
- 域C（盲/冷批相位，run1036_r18+run1377_r13+run1231_r18+run1444_r18）：CoreBuff.gd:524-641
  四分支计时器模型残差，py 早 1 tick 整批弹 → 净化账/给块/抗性翻转级联 = K01/C01 挂起域。

## 反例（防误读的关键反证，均在语料侧实测）
- 反例①：「PotM 在语料中完全不生效」——假。run1191 语料 idx345/347 有 PotM T19+152@17.017：
  fatigue_start 连接有效，仅 advanceTime 一段被骨架吞掉（修正本泳道早期只扫前 6 条 T19 的误读）。
- 反例②：「DoomCap/GoldArmor/Snowmaster 自身施加有时序差」——假。首分歧事件两侧逐字节同：
  run1036 O451=P452（Doom Cap T108+3）、run986 py244/245=O235/236（Gold Armor 净化-2+块25，仅移位）、
  run1444 两侧 6.000s Snowmaster +1 同（仅 resisted 标志为下游噪声）。
- 反例③：「语料疲劳恒不提前」——假。全库 137 场疲劳 <17s（如 run1019_r11@3.317），但其阵容均无
  PotM，另有机制（疑跨场计时器残留）→ 提前疲劳≠advanceTime 生效，勿据此类场推翻域A。

## 建议（移交后续卡/K01 研究域）
- 域A 裁决题：对齐目标是语料——需决策 gd_core 是否把 advanceTime 降级为语料语义
  （弃真游戏保语料）；落点 CoreCombat.advanceTime 或 PotM.onPostCombatStart（均非本卡面）。
- 域B 同构裁决：callNextFrame 是否按语料「饥饿」语义停用（会连锁影响全库 callNextFrame 消费点，
  须全库影响面评估后再动）。
- 域C 归 K01/C01 续关：建议用本泳道四场（+1 tick 整批弹位）作四分支模型的标定新样本；
  137 场早疲劳场的计时器跨场残留机制应并入 K01 一并攻关。
- 任一域收口后由后续卡复验八场（预期 3+1+4 随域级联转绿）。

## 纪律
gd_core_items 8 文件零修改；无备份目录；gd_to_py.py 未跑；未跑 Godot/verify_oracle.py 主流程；
oracle/ 与 output/oracle/fights/ 只读。本轮=取证（不验证），裁决归验证员串行通道。
