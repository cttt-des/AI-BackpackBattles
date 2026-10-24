# np7_explore · 三簇七场探查留档（2026-10-19）

## 统一签名（重大发现）
七场定向（np7_i）中 **5 场的 gd 侧首分歧=盲批（Burning Banner / Light Goobert）提前 3-4 tick
插入**：
- run1073_r12 ev654：gd Banner -1 @12.70 vs O Chili +2 @12.767（早 4 tick）
- run1167_r18 ev531：gd Goobert -7 @5.2833 vs O Chili +1 同刻（早插入）
- run1231_r18 ev195：gd Goobert -7 @4.4667 vs O Snowmaster +1 同刻
- run986_r12 ev271：gd Banner -1 @6.5333 vs O False Life heal @6.65（早 7 tick）
- run688_r10 ev222：gd Banner -1 @9.8833 vs O 耐力耗尽 @9.9333（早 3 tick）
连同 run977_r18 尾段（ev2563 同刻弹层 -9 vs -10）、run1444_r18（Spell Scroll Frostbolt 相位差）、
run1126_r5（Lightning Staff 伤害 11——疑装配链值流家族）、run1303_r18（Devouring Sphere 激活序）。

⇒ **「盲批/临时栈到期系统性早 3-7 tick」大概率是下一个统一类级根因**，横跨 r38 digest 的
Banner/Goobert 主簇残余与 FalseLife/Chili/Snowmaster 三簇。注意 np5_K1 曾用 run688/run634 锚
证伪"统一+1 tick"——本轮证据表明差的不是恒 1 tick 而是 3-7 tick 变量，旧证伪不排除本机制。

## 可能解法（供以后认领，⚠CoreBuff 历史敏感）
1. 取 run986（最早窗 6.53）与 run688（9.88）双锚，dump gd BSCHED 标记 vs oracle probe
   （ORACLE_RNG_DEBUG=1 timer-reg dump）同批的登记 left/驱动路径，定位 gd 提前的精确机制
   （疑：gd triggerTime<=0 判定的浮点累计 vs oracle Timer wait_time 的离散帧语义；或批登记
   时刻差一帧）。
2. 修复面预期=CoreBuff/_tick 或 CoreTimer 驱动边界；改前必取 run634/run688 反例锚（r23 先例）。
3. run1126 疑 K17 装配家族（见 np7_K17.md）；run1303 疑激活序家族。

## 现状
七场维持红；REG 全绿基线未动。
