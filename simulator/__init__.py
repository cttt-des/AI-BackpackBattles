# simulator - Backpack Battles 战斗模拟器
"""
基于解密的原版源码（decompiled_full/）100% 还原战斗逻辑。

数据源:
- 战斗机制: decompiled_full/Core/Character.gd, Items/Item.gd, Core/Buff.gd,
            Interface/CombatTimer/CombatTimer.gd, Utility/DamageSource.gd,
            Utility/DamageResult.gd, Sheets/ItemBook.gd
- 物品数值: assets/battle_items.json（来源 items_db_sim.json + 物品脚本，权威版待 ItemData_e.csv）
- 角色数值: assets/characters.json

设计说明:
- 实时 tick 引擎（60 tick/s），每个物品独立冷却自动触发（原版 _physics_process）
- 伤害结算链完整复刻 takeDamage：命中→闪避→随机伤害→疲劳加成→暴击→
  抗性减伤→固定减伤→无敌→格挡
- 疲劳机制：17 秒开始，3 秒后 1 秒一递增，双方掉血
- Buff 系统：增益/净化/抗性/反射/临时栈
"""
