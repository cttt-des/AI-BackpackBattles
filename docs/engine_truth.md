# 引擎战斗真值规范（engine_truth.md）

> 新引擎 `engine/` 的唯一实现依据。每条规则均给出反编译源码 `文件:行号`，
> 实现与测试必须能对照到本表。源码根：`decompiled_full/`（v1.1.7）。

## 1. 战斗主循环（Core/Game.gd + Core/CombatTimer.gd）

| 规则 | 真值 | 依据 |
|---|---|---|
| 战斗激活序列 | 玩家/对手物品各自 `duplicate()→shuffle()→按 TriggerPriority 降序`；`prepareItems` 全量 → `callDelayed 2.5s 后 activateItems` | Game.gd:3011-3024, COMBAT_DELAY=201 |
| activateItems 三阶段 | `combat_start` 信号 → 双方 `combatStart()` → 全物品 `preCombatStart()` → 全物品 `combatStart()` → 全物品 `postCombatStart()` | Game.gd:3264-3280 |
| 冷却推进 | 每物理帧（60Hz）`triggerTime -= delta * getSpeed()`；角色眩晕时完全冻结 | Item.gd:4453-4458 |
| 触发 | `iterationCooldown = adjustCooldown(); triggerTime += iterationCooldown; doCooldownEffect(); doubleActivationChance>0 且 flip → 再执行一次` | Item.gd:4426-4433 |
| 角色每帧 | 眩晕倒计时递减；`addStamina(staminaRegen * delta)`（基础 1.0/s） | Character.gd:1029-1035 |
| 1s Tick | TickTimer 每 1s：`tickCounter % 2 == 0 → heal(getRegeneration())`，否则 `takeDamage(poison)`；栈不消耗 | Character.gd:401-414, Character.tscn:1632 |
| 疲劳时序 | FATIGUE_TIME=17：开战 14s 预警（17-3），第 17s 首击，之后每 1s | CombatTimer.gd:4,114-120,145-151 |
| 疲劳增量 | `counter += 1 + floor(0.1*counter)`；combatTime≥60 后系数 0.2。序列 1,2,3,4,5,7,8,10,12,14,17,20,… | CombatTimer.gd:153-179 |
| 疲劳结算顺序 | 先 OPPONENT 后 PLAYER | CombatTimer.gd:167-168 |
| 疲劳伤害源 | flags 仅 CanBeBlocked；附加 `bonusFatigueDamage` | CombatTimer.gd:161, Character.gd:539 |
| 判胜 | 结束瞬间 `OPPONENT.curHealth <= 0 → Win`（双方同帧死=玩家胜）；无时限判负 | Game.gd:3282-3310 |
| 收尾 | `EventBus.disconnectAll()` → 双方 combatEnd → 胜方血 max(1,hp)、败方 0 → 全物品 combatEnd | Game.gd:3312-3377 |
| 死亡 | `isDead=true` + `character_died`；isDead 后 takeDamage 直接返回 | Character.gd:997-999,504 |

## 2. 角色层（Core/Character.gd）

### takeDamage 全链（495-653，顺序即真值）
1. isDead 直接返回（504）
2. `attackEffectCount = 1 + origin.rollDoubleAttackEffect()`（连击只放大三个 pre/dealt 钩子次数，511-514）
3. 命中：`CanMiss` 才掷 `accuracyRng.rollPercent(accuracy)`；命中后 `dodgeStacks>0` → 扣 1 闪避翻转为 miss（516-523）
4. `preDealDamage_early` × count（530-534）
5. 命中时 `damage += damageSource.randDamage()`（平衡区间；武器实时取 min/max 并刷新暴击率，536-537）
6. Fatigue 类型 + `bonusFatigueDamage`（539-540）
7. 暴击：`canCrit 且 critChancePercent>0` → `critRng.rollPercent`；无概率则查攻方 `critTokens` → 再查**防守方** critTokens 代打（549-555）；暴击受 `critResistRng.rollPercent(critResistance)` 抵抗（含 critResistStacks 扣减）；成功 `damage *= critSeverity(默认2.0)`（542-561, DamageResult.gd:28）
8. 抗性：`clamp(damageResistance/100, -10, 1)` 对**一切伤害**（含毒/疲劳/尖刺）乘 `(1-r)` 后 round（563-564）
9. 平坦 `damageReduction` 仅 isAttack（567-569）
10. `invulnerable → damage=0`（571-572）
11. EventBus `pre_take_damage`（盾牌 applyDamageReduction 挂此处，574）→ `damage -= damageReduction; max(0)`（576-578）
12. `preDealDamage_late` × count（580-586）
13. 格挡（589-597）：`damage > block → health -= damage-block; loseBlock(block)`；否则 `loseBlock(damage); healthDamage=0`
14. 扣血、日志、`character_attacked/character_damaged` 事件（629-638）
15. 攻击且有钩子 → `item.onDealtDamage(damageRes)` × count（642-646）
16. `curHealth<=0 → death()`（648-649）
17. `applySpikes`（命中+伤害>0+可触发；`min(spikes, round(damage*limit))`，近/远/效果各自 limit；反弹源可格挡可暴击，651, 709-724）
- **吸血**在攻方 `dealDamage → applyVampirism`：`heal(min(vamp, round(damage*vampLimit)))`（482-487, 726-737）
- **heal**：`×healingEfficiency → round → clamp(maxHealth+temporaryMaxHealth)`；Unhealing 反噬 `ceil(amount*unhealing*(1+typedFactor))`（739-772）
- **loseHealth** 直接扣血不吃减伤（854-869）

### 体力
- `useStamina`：先发 `character_pre_use_stamina`（allowStaminaOverflow 窗口可救场）；足够→扣+发 `character_used_stamina` 返回 Sufficient；不足→Insufficient **不扣**（825-839）
- 武器：体力不足 → 本次不攻击但冷却已重置（Weapon.gd:11-13）
- 临时上限 `maxStamina + temporaryMaxStamina`（791-792）

### Buff（Core/Buff.gd + Game.EventType 100..110）
- Block=100..Cold=110；`getBuffs=[101..107]`，`getDebuffs=[108..110]`；MAX：Block=100000 其余 10000（38-41）
- gainTemporary：抗性逐栈 `flipPercent`；减益逐栈反射（递归 + debuffReflectStacks 吸收）；resistStacks/buffProtectStacks 吸收；`duration<0` 永久否则临时栈 `(amount, Util.time+duration)`；计时器取最早到期（76-196）
- loseStacks：净化保护 flip → resistStacks → buffProtectStacks（非 Block）→ **先永久后临时，临时先删 timeout 最远的**（199-280）
- 数值入口 `giveStacks = round(amount * buffPowers[type])`（Item.gd:4958）
- 各栈效果：Regen 偶秒回血/Poison 奇秒毒伤（不耗栈）；Block 按需扣；Vampirism/Spikes 按伤害结算 `min` 栈数；Lucky/Blind `(lucky-blind)*5` 命中；Empower 加武器伤害（仅 canBeEmpowered）；Heat/Cold `(heat-cold)*0.02` 全冷却；Mana 纯资源（Character.gd:1350-1354, Item.gd:3759）
- 眩晕 `stunResisted()`（stunResistanceRng）否则 `max(当前, dur)`（1071-1083）
- 战怒：无 BattleRage 标签物品的角色开局从 isBattleRageItem 随机选一件，5s 后开大持续 4s（46-47, 312-326）

## 3. 物品层（Items/Item.gd 6573 行）

### 枚举
- Type 29 种（34-67）；Tag 位标志 None=0,Lifesteal=1,Stone=2,Scroll=8,Dragon=16,Staff=32,BattleRage=64,Singular=128,Transient=256,Bow=512（83-94）
- Stack：Block=1..Cold=1024，Buff=254，Debuff=1792（96-112）
- Priority：Lowest=-10000,Low=-1000,Normal=0,High=1000,Highest=10000（69-75）

### 冷却
- `hasCooldown = cd != 0`；`getModifiedCooldown = cd / getSpeed()`（3762, 3798）
- `getSpeed：s=speedScale+(heat-cold)*0.02; s>=0?1+s:1/(1-s); clamp(0.1,10)`（3742-3757）
- **adjustCooldown：玩家 `cd×randf(0.95,1.05)`；对手（低于大师）`cd×randf(0.975,1.05)`**（3805-3812）
- preCombatStart：`iterationCooldown=adjustCooldown(); triggerTime=iterationCooldown`（3375-3385）
- extraCds：`getBaseCooldownIndex(0)=cd, i>0→extraCds[i-1]`（3774-3778）
- 中途改基 CD 保进度比例：`triggerTime/iterationCooldown`（4438-4451）
- 一次性：onAfterEffectFinished → deactivateCooldown + consume（5330）

### activate / 信号
- 同帧限流：每物品每帧最多 3 次 activate（4697-4702）
- activate → EventBus "activated"（非 bag）（4710）
- EventBus：按 (源实例, 信号) 定向派发；`Game.fightEnded` 后丢弃；战斗结束 disconnectAll（93-94, 128-130）
- `trigger()` 只调 doCooldownEffect **不调 activate**——"activated" 只有脚本显式 activate()/Weapon.attack 才发（4426, 4710；Goobert 计数联动的关键契约）

### 概率/参数
- `getP(i)`：int 下标→params[]，字符串→namedParams；`getP_m(name) = (base + paramAdd) * paramMult`，base=名首段（ItemDescriptor.gd:107,138-142）
- chance/chance2 两独立槽，共享 chanceRng 与乘法加成；`rollChance = chanceRng.rollPercent(clamp(base+add乘 mult,0,100))`（3849-3877, 4407-4411）
- 暴击 critSeverity 默认 2.0（482）；critTokens 攻守双方可用（549-555）
- dealEffectDamage 不经自己 dealDamage（无自身吸血）但触发对手全链（4138-4141）

### 宝石（Gems/Gem.gd）
- GemMode：Weapon=0/Armor=1/Inventory=2；Inventory 模式自有冷却循环；Weapon 模式挂宿主 "attacked"；Armor 模式直接改角色属性（293-323; Ruby.gd 实例）
- 宿主 API：getGems/setGem；Item prepare/combatStart/combatEnd 透传宝石（3015-3057）

### 袋子（Bag.gd）
- extensionCells = 内部格；getItemsInside = filled 层查占格（158-161）；getAffectedItemsInside 按 canApplyEffect 过滤（176-187）；prepare 缓存（217-224）
- getBagMultiplicity 默认 1（294）；战斗内袋子不 tick

### 电荷（Engineer）
- sendCharge：ElectricalCharge 沿 cells 逐格；进入格 → onChargeEnteredCell + 宿主 chargeReceived/chargeLeft（numCharges±1 + 钩子）（5147-5163）
- changeChargedItemStat：`flat + (cellIndex-2)*valPerTile` 进/出差分（5168-5183）

## 4. 随机数（Utility/Util.gd + BalancedRandom.gd + BalancedRange.gd）
- 全局 `Util.rng`（每局 randomize，无固定种子——模拟器用可控 seed 等价替代）
- `roll(max=100)=randf_range(0,max)`；`flip(chance)=rng.randf() <= chance`（**<=**）；`flipPercent=roll()<=chance`（1004-1030）
- **BalancedRandom.roll(target)**：`expectedWins 初始 randf(-0.2,0.2)`；`dif=expectedWins-wins`；`dif>0.3→chance*=3*min(1,dif)`；`dif<-0.3→chance/=3*min(1,-dif)`；`expectedWins+=target`；防连击 `lastResult and target<0.4→chance*=0.5`；防连败 `not lastResult and target>0.6→chance*=2.0`；`flip(chance)`（18-52）
- 联赛偏置：低于大师，玩家 accuracy/crit rng setBias(-0.2)，对手 +0.2（Character.gd:304-310）
- BalancedRange：伤害区间累积器，|acc|≥1 时向均值修正（保持长期均值）
- 物品 chanceRng/damageRangeRng、角色四 rng：**每场 prepare 全部 reset**（Item.gd:3365, Character.gd:299）

## 5. 数据流（Sheets/CSV/ItemData_e.csv → ItemDescriptor）
- p1..p10：含 `,` → 子参数表 `v:name,v2:name2`；否则 `值:名` 同时写 params[]/namedParams[名]，paramBases=首段基名（ItemBook.gd:855-875, ItemDescriptor.gd:107）
- cd 逗号分隔：首个=cd 其余 extraCds（826-830）；tags=getFlags(Tag)（841）
- gain/remove/use → gainedStacks/removedStacks/usedStacks 位标志（877-879）
- canActivate="no" → false（881-882）；shop 列 → classes 位掩码（''/unique/special→Neutral127，no→0，Class>Sub→1<<idx，技能 Class,Class N→sum）
- type："Melee Weapon"→[Weapon]+Melee deferred；extraTypes 追加（755-769）
- 卖价 = ceil(price*0.5)（239-243）

## 6. 关键契约（新引擎必须保持的排序/不变量）
1. takeDamage 17 步顺序不可换（格挡在减伤后、扣血前）
2. 暴击乘倍率发生在抗性**之前**（563 行随后取整）
3. "activated" 只由显式 activate()/Weapon.attack 发出；trigger() 不发
4. EventBus 在 fightEnded 后丢弃全部派发
5. 每场战斗 RNG 全 reset（平衡统计不跨场）
6. activate 同帧限流 3 次
7. 疲劳先对手后玩家；疲劳源只可格挡
8. 双方冷却独立无先后手；唯一随机开局序 = shuffle+TriggerPriority
