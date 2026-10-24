# np7_GP · Girl Power 几何修正受阻留档（2026-10-19）

## 尝试
以 oracle/Items/Exclusive/GirlPower.tscn:39 tile_data（y*65536+x 解码；cell=3 collision (-1,0)、
cell=4 affected 15 格）为真值修正 assets/battle_items.json GP grid：collision [[-1,-1]]→[[-1,0]]、
affected 去掉 [-1,0] 加入 [-1,1]。再生双表后四场验证（np7_d）：

- run597_r18 ev=101 / run608_r18 ev=147 / run613_r18 ev=85 / run729_r14 ev=30——四场全红，
  且形态一致：oracle 的 GP 首激活（type102/106 @2.2-2.8s）在 gd 侧**更晚**（原基线此四场首分歧
  也是 GP 相位，修后相位差反向扩大）。已回滚（affected/collision 恢复原值+再生）。

## 定性
json grid 的 [a,b] 与 tscn (x,y) 存在**轴映射歧义**：直接 (a=x, b=y) 映射使 gd 的
getNumAffectedItems 减小 ⇒ 首激活更晚；而 r36 隔离实验（handoff §6）在 affected 加 [3,0] 曾使
run608 全对齐——两者矛盾说明真值变换不止平移一格，还含轴交换/翻转（handoff 已警示
「(x=col,y=row) 与 16 位打包解码」与 90°/270° 三场坐标系不一致）。

## 可能解法（供以后认领）
1. 逐场穷举：对 run608 单场，把 tscn 15 格做 8 种刚体变换（轴交换×翻转）×offset 归一，逐一
   跑定向腿，取首激活=3.4833/3.5333/6.8 的变换（r36 已知目标值）。
2. 或读 oracle 运行时 getAffectedCells_tilemap 的返回（probe 仪器 dump，np6_A1_rook 的
   probe_cells.gd 已有同款模板）直接拿真值相对坐标，绕过 tscn 解码。
3. 修后必须过 REG 九场（GP classes 无涉，风险低）。

## 现状
GP grid 维持原值；四场仍属 Girl Power 簇红场（r38 digest 4 场）。
