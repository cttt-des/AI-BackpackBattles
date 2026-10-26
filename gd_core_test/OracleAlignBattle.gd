# =============================================================================
# OracleAlignBattle.gd — 受控神谕三方对齐：gd_core(Godot) 侧批量重放
# （docs/oracle_workflow.md Phase 3；宿主 = tools/verify_oracle.py）
# =============================================================================
# 目的：对 output/oracle/fights/<case>/ 的每场神谕用例，用 gd_core 无头内核在
#   同 (阵容, seed) 下复现整场，导出与神谕 events.json **同 schema** 的事件流，
#   供 tools/verify_oracle.py 做三方逐行比对（oracle ↔ gd_core ↔ gd_core_py）。
#
# 与 TruthBattle.gd 的差异：
#   · 用例来自 res://oracle_align_cases.json（tools/gen_fixture_from_lineup.py
#     --oracle 生成，items 数组 = 神谕 lineups.json 的装配顺序），描述符表运行时
#     读 res://item_battle_fixture.json（同 ItemBattle.gd 的 int() 化口径）；
#   · ★ 激活顺序用**真 Godot 引擎机制**现场复刻神谕：原版开战前
#     duplicate → shuffle → sort_TriggerPriority（Game.gd:3011-3020）走引擎
#     全局链（docs/rng_truth.md §1.4-2），神谕在每场前 seed(S)（oracle_fight.gd
#     :537）。本脚本同样 seed(S) 后对**下标数组** shuffle（与神谕对物品数组
#     shuffle 的比较子结果序列完全一致 → 同一排列），再按 TriggerPriority
#     sort_custom（同一非稳定 introsort）→ 终序与神谕逐位相同；
#   · startBattle(…, preordered=true) 直通该终序（内核不 shuffle、不排序、
#     不消耗 ctx.rng —— gd_core/CoreCombat.gd 的对齐分支）；
#   · ctx.below_master = true（np24 终谳：探针 rng_log 实证录制走了 0.975 对手分支——
#     run574_r7/run570_r18/run582_r15 三场探针 events≡语料后其 rng_log 显示冷却批
#     = 玩家侧全 (0.95,1.05) + 对手侧全 (0.975,1.05)，见 run_case 内注）；
#   · ctx.cur_round = 回合数（LevelUp.onPrepare 消费，对齐原版 Game.curRound）；
#   · 事件捕获在 hooks.logEvent 处按 ctx.fight_ended 闸断（对齐原版
#     CombatLog.gd:266-267 logEvent 的 fightEnded 早退：判胜后事件不再入日志，
#     但 id 照常被 createEvent 消耗——神谕 dump 的 id 空洞即此来源）；
#   · 判胜后补一条合成的 Win/Loss 终局事件（对齐原版 CombatLog.onCombatEnd →
#     logWin/logLoss(afterFightAllowed=true)，oracle/Core/CombatLog.gd:194-204；
#     id 取 ctx.combat_log.eventNum+1，即「该场下一个 createEvent 的 id」——
#     与神谕同一分配器，事件数逐位同链时 id 也一致）。
#
# 运行（全程无头）：
#   output/godot36/Godot_v3.6-stable_win64.exe --headless --path gd_core_test \
#       --script OracleAlignBattle.gd
# 环境变量：
#   ORACLE_ALIGN_OUT      输出目录（默认 <repo>/output/oracle/align/gdcore）
#   ORACLE_ALIGN_LIMIT    只跑前 N 场（冒烟）
#   ORACLE_ALIGN_CHUNK    本进程最多跑 N 场即优雅退出（断点续跑）
#   ORACLE_ALIGN_SELFCHECK=1  首场跑完立即同种子复跑逐字节自证（默认开）
# 断点续跑（幂等）：<out>/<case_id>/events.json 已存在且 event_count>0 → 跳过。
# =============================================================================
extends SceneTree

const MAX_TICKS := 5400          # 90s 游戏时间（与神谕 MAX_TICKS 同值）
const MAX_TIME := 90.0
# ★ np17-B 暖场闩键控表（R 簇 5 场，np16_fix §3 现行树+现行语料逐抽重锚）：这五场
#   的语料是 2026-10-21 32 场重录中暖场**超时截断**的 5 场（np14_fix §1：watchdog
#   break 不走 endCombat ⇒ PLAYER 节点 attackMovingForward 暖场置真后永不复位，
#   oracle/Core/Character.gd:341 的复位在 combatEnd 里、超时路径不达 ⇒ 正式场玩家
#   首次武器攻跳本体 5 抽）。gd 单场进程无暖场 → 跑满 5 抽 → 伤害掷错位
#   （906@258 / 1125@370 / 1409@373 / 696@395；1371 掷链全同+「伤 9 不可达」论证）。
#   本表 = 对脏录音的**受控补偿**（录制工件补偿，非内核语义）：仅表内场生效、仅
#   玩家侧 attack_moving_forward 初始置真；零 rng；内核该标志本就无战斗内复位路径
#   （CoreCharacter.attackMovingForward_reset 为空实现），与闩死语义一致。隔离开关
#   ORACLE_ALIGN_NO_WARM_LATCH=1 恢复无闩行为（REG 红时单笔隔离用）。
#   ★ np22 重录后摘除 696/1371 两键：两场新语料（output/oracle/fights_pre_r52/
#   备份后替换）= ORACLE_NOLIMIT 抬闸全长重录的干净形状——暖场自然收尾
#   （combatEndDeferred 跑通：闩复位/EventBus 断连/fatigue 归零），无闩残留，
#   本表对两场不再适用。906/1125/1409 三键保留（旧语料未重录，闩补偿仍需）。
const WARM_LATCH_PLAYERS := {
	# np23 全清空：新语料干净形状
}
# ★ np18-C 永久栈暖场收割键控表（run702_r18@423 / run1022_r18@1386 定谳，
#   np18_fix §3）：这两场的语料=录制管线第 3 次执行（ok+确定性自证），其
#   首分歧=跨执行 permanentStacks 残留——oracle Buff.reset()（combatEnd→
#   Character.cleanse 链）不清 permanentStacks（oracle/Core/Buff.gd:52-57 vs
#   :8 permanentStacks 字段），上一执行战斗内永久栈增益（AoD/Skull Badge 类
#   无 duration Stack 事件）带进本执行 ⇒ 净化 loseStacks 走「先永久」支
#   （oracle/Core/Buff.gd:255-256）吃掉残留，临时批原封；gd 单执行进程
#   permanentStacks=0 ⇒ 同一笔净化拆了临时批 ⇒ 首分歧（702：LG Blind TO
#   -7 语料 v -6 gd；1022：语料多 Banner Blind TO -1 @13.0333）。
#   实证：np18 现树管线复放（暖场+正式，probe/np18_r18）在 423/1386 前与
#   语料逐位同（PvsO@1590/@2456），gd 腿同位即歧——残留面复现成立。
#   本表 = 宿主侧管线复刻：键控场先跑一遍完整暖场（同 case 同 seed，干净
#   语义），收割其终局玩家 permanentStacks，再灌入正式场玩家 buff——与
#   oracle「执行间唯一存活态=permanentStacks」逐面同构（fixed-point：
#   语料 cert exec2≡exec3 ⇒ 一次收割即稳态值；收割值≥1 即复现语料在
#   消耗点的可见行为）。仅表内场生效；隔离开关
#   ORACLE_ALIGN_NO_PERM_HARVEST=1 恢复单执行行为（单笔隔离用）。
#   已知边界：暖场收割=gd 干净整场终局值，其后段若与 oracle 干净执行有
#   内核差则可能污染计数（np18_fix §3.4）；702/1022 语料在更后段
#   （1590/2456）与现树管线再歧——本笔预期把首分歧推到该位而非清零。
const PERM_STACK_HARVEST := {
	"run702_r18": true, "run1022_r18": true,
	# ★ np22：重录两场（新语料=ORACLE_NOLIMIT 全长录制，exec3 携带 exec2 终局
	#   permanentStacks 残留）。收割管线=录制残差的同构复刻：暖场递归跑完整干净
	#   战斗（NP22_REC_EV_GATE 抬闸下自然终局=录制暖场形状），收割终局玩家
	#   permanentStacks 灌入正式场。run696 实测残差零可见面（np22_r1 守门双腿
	#   PASS）不入表。
	"run1371_r18": true, "run1444_r18": true,
}
# ★ np20-C 永久栈残留校正值（PERM_STACK_HARVEST 收割值的 canonical 封闭推导覆盖，
#   np20_round2 升级批准面）：收割值=gd 净跑暖场终局，≠ oracle 语料录制执行
#   实际携带的残留——run702 收割 25 vs 真值 1（高估），run1022 收割 1 vs 真值
#   6（低估）。双向失真源=「两引擎净跑终局态不等」（上注 np18_fix §3.4 已知
#   边界的定谳）。真值由 canonical 事件面算术封闭推导，并经机械模拟器复验
#   （规则=oracle/Core/Buff.gd loseStacks「先永久、临时先删 timeout 最远者」
#   + onTimeout 弹批，逐条 type=109 timeout 事件与推导批账比对）：
#     run702_r18 PLAYER Blind(109) = 1：34/34 弹批吻合（-6@971 / -6@1085 /
#       -6@1365 / -6@1486 / -6@1773 五处深清洗 partial 全部由此值解释）；
#       R=0 在 233 失配、R≥2 在 971 起失配，0..4 内唯一。
#     run1022_r18 PLAYER Blind(109) = 6：50/50 弹批吻合；R≤3 在 1118（语料
#       Banner TO -1 弹批丢失，即现首分歧位）失配，R=4/5 在 1226/1357
#       NO-BATCH；R=6 起全洁（P 不再耗尽，弹批对 R 不再敏感，取最小值）。
#   仅本表键控场生效（键 ⊆ PERM_STACK_HARVEST）；零 rng 消耗（播种前纯字段
#   写）；隔离开关沿用 ORACLE_ALIGN_NO_PERM_HARVEST=1（关收割即关本覆盖，
#   单笔隔离用）。
const PERM_STACK_OVERRIDE := {
	"run702_r18": {109: 1},
	"run1022_r18": {109: 6},
	# ★ np22（1444 见 PERM_STACK_HARVEST np22 增行注）：暖场收割（=exec1 干净
	#   终局）Cold(110)=0，但新语料=exec3 携带 exec2 终局残差——exec2 带着
	#   exec1 残差（100:129/106:83/…）跑出的净化路径使自身终局 Cold 残差 ≥1
	#   （@330 Snowmaster 净化 -1 需先吃永久，否则拆临时批 → gd 多弹 Frostbolt
	#   Cold TO -2 @5.9833）。本表在收割之上仅覆写 110 一维（np20 体例：类内
	#   值以守门对拍定谳）。
	"run1444_r18": {110: 1},
}
# ★ np21-R5 双执行拓扑键控表（run1125_r18 首场落地；授权面=np20 ①「忠实补偿：
#   gd 对拍腿复刻双执行共享 bus/日志拓扑」，用户已批）：
#   五场语料（run1125/1409/906/696/1371_r18）= 2026-10-21 单场单进程重录的
#   「暖场（watchdog 截断）+正式」第 2 次执行。暖场 break 不走 endCombat ⇒
#   oracle 三重清理跳过：attackMovingForward 未复位（np17-B WARM_LATCH_PLAYERS
#   已偿）、permanentStacks 未清（np18-C 语义，np20 ① 实测五场该残留恰为零）、
#   EventBus.disconnectAll 未跑（本表）。EventBus 是进程全局单例
#   （oracle/Utility/EventBus.gd 全文）且 PLAYER 节点跨执行复用
#   （oracle_fight.gd:563-590 instanceCharacter 复用）⇒ 暖场物品对 PLAYER 信号
#   的连接全部存活，正式场每次该类信号双份投递（连接序=陈旧先于新鲜；陈旧
#   应答量带暖场累积态）。语料实证（run1125 证据包）：AoA(t105) 121 对 +
#   FL(t19) 915 对、其余 type/物品零成对；干净对照 4 场成对数=0 ⇒ 双发系暖场
#   残留、非本征行为。
#   复刻管线（逐字段与录制进程机理同构）：
#     1) 暖场：同 case 同 seed 独立 ctx 完整执行（=录制进程第 1 次执行语义：
#        无闩/无任何键控补偿/无 rng_state 注入，全链自 seed 起跑），到事件闸
#        T_w 即断、不跑任何收尾（T_w=25000 事件=暖场侧同闸，np18_diag 复放
#        实测暖场 2878 ticks 截于事件闸，语料 result.txt status=timeout 同构）；
#     2) 收割：暖场玩家 permanentStacks 灌入正式玩家（teardown 的 cleanse 不清
#        permanentStacks，oracle/Core/Buff.gd:52-57 vs :8；预期空集，非零即忠实）；
#     3) 泄漏：正式装配后、startBattle 前，把暖场 bus 连接台账中「发射体=暖场
#        玩家 && 接收体=玩家侧物品」的连接按暖场时序挂上正式 bus（发射体映射
#        为正式玩家——oracle 里二者是同一节点）；暖场对手侧接收体已随对手节点
#        释放（teardown G.OPPONENT.free()+INVENTORY.deleteItems，oracle_fight.gd
#        :1004-1009）、暖场对手/物品发射体在正式场不再发射——均不嫁接（神谕
#        实证零投递）。陈旧接收体 ctx/character_ 改指正式 ctx/正式玩家（oracle：
#        节点复用 ⇒ 天然指向；语料实证陈旧应答入正式日志）；damageSource/
#        chanceRng/damageRangeRng 的抽源改指正式 ctx.rng（oracle：二者包着进程
#        全局 Util.rng，陈旧处理器消耗正式链 rng——run696@79/run1371@137 链级
#        错位证据）。BalancedRng 平衡态（wins/expectedWins/lastResult）保留暖场
#        值（oracle 同实例跨执行存活；prepareItems 的重置只遍历正式物品清单）。
#     4) θ（闩中途复位）：run1125 不引入——证据包本体攻击扫描唯一带本体=
#        对手 owner3 首攻（draw#489@1.317 对应事件[84] owner_type=3），玩家侧
#        108 攻全程闩死，θ 无锚点；np17_fix §5.2-2 对 1125 的复位记载与 owner
#        归侧相悖，以逐行扫描为准（1409/696 的复位结论不受影响，待各自证据包
#        复核后再入表）。
#   仅表内场生效；隔离开关 ORACLE_ALIGN_NO_R5_DUAL_EXEC=1（置非空值关闭）恢复
#   单执行行为。全部参数语料侧封闭推导，逐场增行。
#   run1409_r18（np21-R5 第二场，证据包定谳）：T_w=事件闸 25000（暖场/正式
#   双双事件闸截断，同 harness 探针暖场 2473 ticks/41.2s 参考）；θ=N/A——探针
#   全场 400 攻唯一本体=对手 owner3 首攻（probe event#27 @ts1.0333，EVENT 行序
#   ↔events 序号一一对应铁证），玩家恒闩（np17 §5.2-2 把 1409 归入复位簇系
#   对激活期相邻双 (0.9,1.1) 的误归，以逐行扫描为准）；双发面=AoL-19 玩家
#   全双 208 对 + AoA-105 于 Egg/ManaOrb-spend 路径全双 254 对、FF-spend 路径
#   陈旧零退/单发（分 buffType 的 usedStacks 分数残留演化，嫁接自动复现）、
#   Egg-105 48/48 对称双笔=合法双蛋机制勿注入；语料↔探针首差 idx306（AoA 陈旧
#   量 2 v 4，纯状态分叉零抽差）——gd 干净暖场与语料录制批的暖场同为确定性
#   执行（1125 实证：gd 暖场陈旧量逐位命中语料，oracle 自家探针反而偏），
#   以守门判定为准。
const R5_DUAL_EXEC := {
	# np23 全清空：新语料干净形状
}
# ★ np22 重录场正式腿事件闸对位抬闸：三场新语料以 ORACLE_NOLIMIT=1（事件闸
#   200000）全长录制（暖场自然收尾、正式场自然终局），gd 正式腿必须同闸
#   对位——否则在旧 M12 常数 25000 处截断而语料全长继续 → 伪长度分歧
#   （run685 length 簇同型）。1444 全长 1030 远不及闸，键控为录制工件对位
#   的同构记录。仅 np22 三键控，其余 911 场维持 M12=25000 零变化；py 腿
#   同键镜像（tools/verify_oracle.py PY_NP22_REC_EV_GATE → 引擎
#   formal_ev_gate 参数）。
const NP22_REC_EV_GATE := {
	"run696_r18": 200000, "run1371_r18": 200000, "run1444_r18": 200000,
}
# ★（阶段2）旧 ORACLE_SCENE_DRAWS=14 校准常数已删除：它是 run579_r18 单场拟合的
#   「装配期不可见消耗」补丁，全量 917 场实测装配差为 0..444 步（非常数）。
#   真实构成已逻辑一致还原进内核（output/_probe_assembly_steps.py 逐场零残差）：
#     · 物品/宝石实例 = 场景双绑定 2×BalancedRng = 4 步（CoreItem.setup，Item.gd:472
#       经 Item.tscn/Gem.tscn 根绑定 + 覆盖脚本重绑定各跑一遍成员初始化器）；
#     · FlickerAnimation 子节点物品入树 +2 步（CoreItem._readyInit，
#       Items/Animations/FlickerAnimation.gd:13-15 的 callDelayed 实参求值）；
#     · 对手 Character 实例化 4×BalancedRng = 8 步（Character.gd:94-97，
#       神谕在播种后实例化对手——内核同序）；
#     · Character.tscn 场景图 _ready 面实测 0 步（stage 探针 stage6）。


# ── 事件捕获探针：logEvent 是内核唯一事件出口（CoreCombatLog.logEvent →
#    ctx.hooks.logEvent / CoreEventBus.emitAndLog 亦同）。序列化成神谕
#    events.json 的同 schema 记录（oracle_fight.gd::dump_events 同构）。 ──
class CaptureProbe extends CoreHooks:
	var rows := []              # 序列化事件记录（Dictionary）
	var gate_ctx = null         # 开战后赋值；fight_ended 后不再收（对齐原版闸）

	func logEvent(event) -> void :
		if gate_ctx != null and bool(gate_ctx.fight_ended):
			return              # 原版 CombatLog.logEvent 的 fightEnded 早退（:266-267）
		if event != null:
			rows.append(_record(event))

	func _record(event) -> Dictionary:
		var parent_id := - 1
		if event.parentEvent != null:
			parent_id = int(event.parentEvent.id)
		var tn := String(event.getType())
		var etk = gate_ctx.event_type_keys
		if etk != null and etk.has(int(event.getType())):
			tn = String(etk[int(event.getType())])
		return {
			"id": int(event.id),
			"type": int(event.getType()),
			"type_name": tn,
			"timestamp": float(event.timestamp),
			"origin": _j(event.getOrigin()),
			"target": _j(event.target),
			"parent_id": parent_id,
			"params": _j(event.params),
		}

	# oracle_fight.gd::_jsonable_impl 同构（宝石宿主折叠判据一致：先查 socket）
	# ★ gem origin 转录（round8）：原版 gem.socket 是 GemSocket2 节点
	#   （decompiled_full/Items/GemSocket.gd=class Socket：单数 gem、无 gems 数组、
	#   无 descriptor/getTopLeftCell → _jsonable_impl 折叠 {kind:unknown,str} 且
	#   socket_index 恒 -1）。神谕语料实证：21164/21164 个 gem origin 全为
	#   host={kind:unknown,str:GemSocket2} socket_index=-1（全语料扫描）。
	#   内核把 socket 身份折叠进宿主物品（CoreItem.setGem 的 gem.socket=self，
	#   gd_core/CoreItem.gd:2786-2806，闸门10已验等价）——dump 层把该折叠 item
	#   还原成原版序列化形状，非判定放宽（run570 idx34 首分歧即此）。
	func _j(o, depth: int = 0) :
		if o == null:
			return null
		if o is bool or o is int or o is float or o is String:
			return o
		if o is Vector2:
			return {"x": o.x, "y": o.y}
		if o is Dictionary:
			if depth > 6:
				return "…"
			var d = {}
			for k in o:
				d[String(k)] = _j(o[k], depth + 1)
			return d
		if o is Array:
			if depth > 6:
				return "…"
			var a = []
			for v in o:
				a.push_back(_j(v, depth + 1))
				return a
		var sock = o.get("socket")
		if sock != null:
			return {"kind": "gem",
					"host": {"kind": "unknown", "str": "GemSocket2"},
					"socket_index": -1}
		if o.has_method("getTopLeftCell") and "descriptor" in o:
			var tl = o.getTopLeftCell()
			return {"kind": "item", "name": String(o.getName()),
					"identifier": String(o.descriptor.identifier),
					"owner_type": int(o.ownerType),
					"top_left": {"x": tl.x, "y": tl.y}}
		if "playerId" in o:
			return {"kind": "character", "player_id": int(o.playerId)}
		if o.has_method("getName"):
			return {"kind": "object", "name": String(o.getName())}
		return {"kind": "unknown", "str": str(o).split(":")[0].substr(0, 80)}


# 下标排序器：与原版 Game.ItemSort.sort_TriggerPriority 同一比较子
# （item1.getTriggerPriority() > item2.getTriggerPriority()），作用于下标数组
# ——introsort 只由比较子结果驱动，对下标排序与对物品排序给出同一排列。
class IdxSort:
	var prio := []

	func by_trigger_priority(a, b) -> bool :
		return prio[int(a)] > prio[int(b)]


var _report := []
var _descr_cache := {}
var _script_cache := {}
var _table := {}            # item_battle_fixture.json
# 神谕语料根（每场 rng_state.txt 的来源）；_init 里填
var _fights_root := ""


func say(line: String) -> void :
	print(line)
	_report.push_back(line)


func vlist(cells: Array) -> Array:
	var out := []
	for c in cells:
		out.push_back(Vector2(int(c[0]), int(c[1])))
	return out


func descriptor_of(ctx, key: String) -> CoreItemData:
	# ★ 描述符全局唯一（Item.isA 靠引用相等；跨场复用同一实例）
	if _descr_cache.has(key):
		return ctx.item_book.register(_descr_cache[key])
	var d: Dictionary = _table["items"][key]["descr"]
	var made = CoreItemData.new().fromDict({
		"name": d["name"],
		"identifier": d["identifier"],
		"minDam": int(d["minDam"]),
		"maxDam": int(d["maxDam"]),
		"cd": float(d["cd"]),
		"extraCds": d["extraCds"],
		"accuracy": float(d["accuracy"]),
		"staminaCost": float(d["staminaCost"]),
		"block": int(d["block"]),
		"price": int(d["price"]),
		"rarity": int(d["rarity"]),
		"classes": int(d["classes"]),
		"canActivate": bool(d["canActivate"]),
		"chance": float(d["chance"]),
		"chance2": float(d["chance2"]),
		"types": iarr(d["types"]),
		"tags": int(d["tags"]),
		"params": d["params"],
		"namedParams": d["namedParams"],
		# 配方图（tools/enrich_recipes.py）：战斗语义只消费非空性
		#（isCraftedItem → Cog/Anvil 的 canAffect），CoreItemData.fromDict 原生读此键
		"originatingRecipes": d.get("originatingRecipes", []),
		# 攻击动画场景（tools/enrich_animation_scene.py）：playAnimation 的闸。
		#   ★ np24 终谳更正：探针 rng_log 三场 (-100,100)=0 行并非「块未消耗」——
		#   神谕 ItemAnimation.gd 直连 Util.rng（无日志），块照常消耗（run574
		#   注入实验 4 笔裸抽精确命中神谕值，见 gd_core/CoreItem.gd activate ②）。
		#   数据面照夹具原值传递，内核以裸抽对位。
		"animationScene": bool(d.get("animationScene", false)),
		"animSpeedMin": float(d.get("animSpeedMin", 0.8)),
		"animSpeedMax": float(d.get("animSpeedMax", 1.2)),
		# FlickerAnimation 子节点（tools/enrich_flicker_animation.py，阶段2 装配期
		# 对齐）：入树 +2 步 + 战斗期 playAni +2 步（CoreItem._readyInit/flickerPlayAni）
		"flickerAni": bool(d.get("flickerAni", false)),
		"flickerMinDist": float(d.get("flickerMinDist", 0.1)),
		"flickerMaxDist": float(d.get("flickerMaxDist", 3.0)),
		"flickerMinSpeed": float(d.get("flickerMinSpeed", 0.3)),
		"flickerMaxSpeed": float(d.get("flickerMaxSpeed", 1.0)),
		# 连接器/宝石 _ready 抽（同阶段2 装配期对齐，消费点 CoreItem._readyInit）
		"connectorReadyRoll": bool(d.get("connectorReadyRoll", false)),
		"gemRoll": bool(d.get("gemRoll", false)),
		# 随机 unique 池（tools/enrich_unique_pool.py）：isTreasure() 的唯一依据
		#（Item.gd:5723-5724 ← ItemBook.gd:899-901 shop=="unique"）
		"randomUniquePool": bool(d.get("randomUniquePool", false)),
		# gained/removed/usedStacks（round10；对齐 ItemBook.gd:877-879 的
		# table.getFlags("gain"/"remove"/"use", Item.Stack, line)。此前字段子集
		# 漏传 → gd 侧恒 0：Toad/PoisonFrog 阈值网络 canAfect=gainsBuffs() or
		# usesBuffs() 全哑（run575_r18 实证：神谕 idx3 Toad 治疗 7 缺失，而 py
		# 侧补数据后已逐位命中神谕 idx3=7.0）。消费面 CoreItem.gd:5383/5393/5399
		"gainedStacks": int(d.get("gainedStacks", 0)),
		"removedStacks": int(d.get("removedStacks", 0)),
		"usedStacks": int(d.get("usedStacks", 0)),
		# 战怒描述符（oracle rage_dump_tmp.gd）：isBattleRageItem 判定面
		"hasBattleRageEffect": bool(d.get("hasBattleRageEffect", false)),
		# 场景绑定深度（tools/enrich_scene_depth.py）：setup() chanceRng 次数
		"sceneDepth": int(d.get("sceneDepth", 2)),
	})
	_descr_cache[key] = made
	return ctx.item_book.register(made)


func iarr(a: Array) -> Array:
	var out := []
	for x in a:
		out.push_back(int(x))
	return out


func script_of(path: String):
	if _script_cache.has(path):
		return _script_cache[path]
	var s = load(path)
	_script_cache[path] = s
	return s


func new_character(ctx, pid: int, side: Dictionary) -> CoreCharacter:
	var c = CoreCharacter.new(ctx, pid)
	c.characterClass = int(side["class"])
	c.setMaxHealth(int(side["health"]))
	c.setCurrentHealth(int(side["health"]))
	c.maxStamina = float(side["stamina"])
	c.baseMaxStamina = float(side["base_max_stamina"])
	c.baseStaminaRegen = float(side["regen"])
	c.staminaRegen = float(side["regen"])
	c.fillUpStamina()
	return c


# 装配一件物品并入包（装配序 = 夹具 items 数组顺序）。失败返回 null。
func place_one(ctx, chr, entry: Dictionary, owner_type: int):
	var key: String = entry["key"]
	var path: String = entry["script"]
	var script_obj = script_of(path)
	if script_obj == null:
		say("FAIL 脚本无法加载：%s（物品 %s）" % [path, key])
		return null
	var it = script_obj.new()
	if it.get_script() == null or it.get_script().resource_path != path:
		say("FAIL 脚本不匹配：%s（物品 %s）" % [path, key])
		return null
	it.setup(ctx, descriptor_of(ctx, key), chr)
	# ★ np24 簇A①：socket 数 = **神谕实例真值**（entry["gems"] 数组长度），非夹具
	#   容量。原版 sockets = $Icon/Sockets.get_children()（Item.gd:309）——实例场景
	#   决定，可少于描述符容量；lineups 快照（oracle_fight.gd::_item_snapshot）按
	#   「每 socket 一条、空槽记 null」逐位导出，故 len(entry["gems"]) 即实例
	#   Socket 节点数（空 [null]=1 空槽、[]=0 槽，全语料 case↔lineups 长度零残差
	#   实证）。此前按夹具 capacity 建槽：①空槽语义丢失（Leather Bag 类 0 槽实例
	#   被建出 1 槽，getNumSockets/hasGems 面失真）；②夹具 sockets 已改由数据面
	#   出处（np23 后置 0，容量不再可信），按它建槽会致 setGem 越界全灭（宝石
	#   装配 0 颗、countSocketedGems 恒 0）。宝石装配必须只依赖 case 条目真值。
	for _i in range((entry["gems"] as Array).size()):
		it.gems.push_back(null)
	it.collisionCells = vlist(entry["collision"])
	var aff := {}
	for color in entry["affected"].keys():
		aff[int(color)] = vlist(entry["affected"][color])
	it.affectedTileCells = aff
	it.occupiedCells = vlist(entry["occupied"])
	it.ownerType = owner_type
	# ★ 朝向（战斗判定输入，CoreConst.FaceDirection 0..3 = 顺时针 1/4 圈）：
	#   夹具条目的 rotation 是度数（gen_fixture_from_lineup.py 由神谕 face_direction
	#   ×90 得到）。此前内核恒 UP——电荷路径（Battery.chargeCells 等**本地格**
	#   常量，经 Item.getGlobalPointsForCells 的节点旋转变换映射进背包）与
	#   SpintoWin/LongSpear/RainbowPotion 的朝向分流全部按 0° 计算。
	it.faceDirection = int(entry["rotation"]) / 90
	# 原版次序：_ready 先于 addItem；宝石在宿主入包之后 setGem
	it._readyInit()
	# ★ np17-A 隔离开关：ORACLE_ALIGN_NO_CRAFTED_REORDER=1 → 恢复 np17 前
	#   （覆写先于 addItem）次序，单笔隔离用。缺省走下方挪序分支。
	var np17_no_reorder := OS.get_environment("ORACLE_ALIGN_NO_CRAFTED_REORDER") != ""
	if np17_no_reorder and entry.get("effects") != null and it.has_method("setCraftedEffects"):
		it.setCraftedEffects(entry["effects"])
	# ★ np24：crafted 实例真值须在 addItem 前注入——currentAffectedItems 在放置期
	#   按 canAffect_color（isCrafted）增量入账，晚注入会被半径快照过滤
	#   （run871 Anvil numCrafted 2 v 4 定谳）。
	if entry.has("crafted"):
		it.crafted_instance = 1 if bool(entry["crafted"]) else 0
	chr.inventory.addItem(it, it.occupiedCells)
	for gi in range((entry["gems"] as Array).size()):
		var g = entry["gems"][gi]
		if g == null:
			continue
		var gem = place_gem(ctx, chr, g, owner_type)
		if gem != null:
			it.setGem(gi, gem)
	# ★ np17-A crafted 效果真值覆写挪序（run948_r18 定谳，np16_fix §2 证据链）：
	#   oracle 元组循环（oracle/Core/Inventory.gd:1001-1035 createFromItemTuples）
	#   次序 = 实例化/add_child（→_ready→MagicRing randEffects **随机** ringTypes，
	#   MagicRing.gd:167-176）→ addItem（item_added 广播，CA 按随机类型判授予，
	#   oracle/Items/Item.gd:1428-1474）→ 宝石 → setData（真值 ringTypes →
	#   onItemTypeChanged 广播 → 已窗内者只走保留性复检 Item.gd:1477-1500，不再
	#   授予）。宿主此前在 addItem 前覆写 ⇒ 广播时已真值 ⇒ CA 直接授予 ⇒
	#   SR(5,3) P 侧 dyn 多授（gd 双侧 Dark 6/6 vs oracle P5/O6）→ 0.6 平衡悬崖
	#   → 攻 1 proc 分叉（run948@42）。挪至 addItem+宝石后镜像原版元组序；
	#   _readyInit 的 roll 照常消耗链位（与神谕重放同序），setCraftedEffects 零
	#   rng、链位中性。仅 MagicRing 族有此方法；effects=null（旧夹具/无效果物品）
	#   跳过。
	if not np17_no_reorder and entry.get("effects") != null and it.has_method("setCraftedEffects"):
		it.setCraftedEffects(entry["effects"])
	return it


func place_gem(ctx, chr, g: Dictionary, owner_type: int):
	var key: String = g["key"]
	var script_obj = script_of(g["script"])
	if script_obj == null:
		say("FAIL 宝石脚本无法加载：%s（%s）" % [g["script"], key])
		return null
	var gem = script_obj.new()
	gem.setup(ctx, descriptor_of(ctx, key), chr)
	for _i in range(int(_table["items"][key]["sockets"])):
		gem.gems.push_back(null)
	gem.collisionCells = [Vector2(0, 0)]
	gem.affectedTileCells = {}
	gem.occupiedCells = []
	gem.ownerType = owner_type
	gem._readyInit()
	return gem


# ★ 激活顺序复刻（与 oracle_fight.gd:589-595 逐机制等价）：
#   seed(S) → playerItems.shuffle() → sort_TriggerPriority
#          → opponentItems.shuffle() → sort_TriggerPriority
#   全局链只有这一个播种点、两条 shuffle 连续消费——下标数组版与物品数组版
#   的链消耗与比较子结果序列完全一致（shuffle 不看元素内容）。
func activation_order(seed_value: int, p_items: Array, o_items: Array) -> Dictionary:
	seed(seed_value)
	var p_idx := []
	for i in range(p_items.size()):
		p_idx.push_back(i)
	var o_idx := []
	for i in range(o_items.size()):
		o_idx.push_back(i)
	var ps := IdxSort.new()
	for it in p_items:
		ps.prio.push_back(int(it.getTriggerPriority()))
	p_idx.shuffle()
	p_idx.sort_custom(ps, "by_trigger_priority")
	var os := IdxSort.new()
	for it in o_items:
		os.prio.push_back(int(it.getTriggerPriority()))
	o_idx.shuffle()
	o_idx.sort_custom(os, "by_trigger_priority")
	return {"player": p_idx, "opponent": o_idx}


func by_order(items: Array, order: Array) -> Array:
	var out := []
	for i in order:
		out.push_back(items[int(i)])
	return out


# ── ★ 阶段1 rng state 读取（docs/alignment_fix_workflow.md §2 阶段1）──────────
# 神谕在「战斗装配完成后、开战序列与首次 tick 之前」导出的
# output/oracle/fights/<case_id>/rng_state.txt（oracle_fight.gd，双 u64：
# seed=<get_seed()> / state=<Util.rng.state>）。GDScript int 是有符号 64 位
# 视角，state 为 u64 溢出时为负——Godot 的 state setter 直通 pcg.state 字
# （按 2^64 回绕），原值赋回去即逐位还原，无需手工归一。
# 返回空串 = 文件缺失（调用方 fail-fast：state 注入是阶段1 的判定前提，
# 静默退回 seed 重放会让「对齐」变成假阳性）。
func read_rng_state(case_id: String) -> String:
	var p = _fights_root.plus_file(case_id).plus_file("rng_state.txt")
	var fh = File.new()
	if not fh.file_exists(p):
		return ""
	fh.open(p, File.READ)
	var txt = fh.get_as_text()
	fh.close()
	for ln in txt.split("\n", false):
		if ln.begins_with("state="):
			return ln.substr(6)
	return ""


func run_case(c: Dictionary, out_root: String, perm_warm := false, r5_warm := false) -> Dictionary:
	var case_id: String = c["case_id"]
	var seed_value: int = int(c["seed"])
	var dir = out_root.plus_file(case_id)
	# ★ np3 修：tick 循环期的 item_trace 写盘需要目录先在（此前目录在战后
	#   events.json 落盘前才创建 → ORACLE_TRACE_ITEM 全程 "File must be opened
	#   before use"，item_trace.txt 恒缺失）。幂等创建提前到此处。
	var _d0 = Directory.new()
	if not _d0.dir_exists(dir):
		_d0.make_dir_recursive(dir)
	var res = {"status": "FAIL", "case_id": case_id, "seed": seed_value,
			"ticks": 0, "combat_time": 0.0, "events": 0, "winner": "-", "dir": dir}

	var probe = CaptureProbe.new()
	var ctx = CoreContext.new(seed_value, probe)
	# ★ 标签视觉抽开关（round19）：每录制场的标签视觉设置不同
	#  （oracle rng_log randInBox 行数：run570=696 vs run569=0），夹具生成期
	#   按 fights/<case>/rng_log.txt 的 randInBox 行数写入 label_rng（缺省 true）。
	#   链消耗必须逐场对齐该设置（run569 实证：标签 OFF 场 gd 多耗
	#   randInBox 抽自 #197 起漂移）。
	if c.has("label_rng"):
		ctx.label_rng_enabled = bool(c["label_rng"])
	probe.gate_ctx = ctx
	# ★ np24：deferred 冲刷关闭（对位录制 [M11]：阻塞循环无帧，战斗内
	#   call_deferred 永不执行——run574 Deck of Cards 卡链零启动实证；
	#   机理与开关见 gd_core/CoreContext.gd flushDeferred 注）。
	ctx.deferred_flush_enabled = false
	# ★ np24：EngineerBox 接力死亡镜像（机理见 CoreContext.gd eb_relay_mirrored 注；
	#   录制侧 EB ChargeTimer 首弹 1 次/侧、队列不推进，接力重发射=0）。
	ctx.eb_relay_mirrored = true
	# np21-R5：暖场 ctx 打开连接台账（键控见 R5_DUAL_EXEC 表注； CoreEventBus
	#   connect_journal 默认关，正式/非键控路径零扰动）
	if r5_warm:
		ctx.bus.connect_journal_enabled = true
	# ★ np24 终谳（探针 rng_log）：below_master=true + cur_round=回合数。
	#   run574_r7/run570_r18/run582_r15 三场探针（events≡语料，判据=守门前置
	#   通过）rng_log 实证开战冷却批 = 玩家侧全 (0.95,1.05) + 对手侧全
	#   (0.975,1.05) ⇒ 录制时 isBelowLeague(Master)=真。此前「族A 对手全 +1
	#   tick ⇒ 映射应 (0.95,1.05)」的推断被证伪：同 J₀ 下 gd FFR 速度 1.06 而
	#   oracle 实测需 ~1.07（1.4·0.985024/(78/60)），±1 tick 的真根源是对手
	#   速度面差（族A 同签名），非冷却映射；±0.2 命中/暴击偏置随本开关在位。
	ctx.below_master = true
	ctx.cur_round = int(c["round_id"])

	# ★ 装配期链约定（对齐 oracle_fight.gd:505-537 的实证语义）：
	#   神谕复用 PLAYER（其角色构造的链消耗发生在本场播种前，被 seed 抹除），
	#   随后任何物品实例创建之前 Util.rng.seed = S。内核照做：先构造玩家角色
	#   （8 步 BalancedRng），再重播种抹掉它，然后补神谕场景装配的额外消耗，
	#   最后构造对手角色（神谕的对手场景在播种后实例化，消耗照常入链）。
	var trace_on := OS.get_environment("ORACLE_ALIGN_TRACE") != ""
	# ★ np18-C 永久栈暖场收割（表与机理见文件头 PERM_STACK_HARVEST 注）：
	#   键控场先跑一遍完整干净暖场（独立输出目录，不触正式产物），收割其
	#   终局玩家 permanentStacks；正式场玩家构造后灌入。暖场=独立 ctx，链位
	#   对正式场零影响（正式场播种与 rng_state 注入在其后照常执行）。
	var harvested_perm := {}
	# np21-R5 存活连接包（[emitter 映射后无需保留, signalName, receiver, method]）
	var r5_journal := []
	# np21-R5 第四残留：暖场截断时的疲劳计数（>0 ⇒ 正式 hasFatigueStarted 恒真）
	var r5_fatigue := 0
	if perm_warm or r5_warm:
		pass
	elif OS.get_environment("ORACLE_ALIGN_NO_PERM_HARVEST") == "" \
			and PERM_STACK_HARVEST.has(case_id):
		var wres = run_case(c, out_root.plus_file("_np18_permwarm"), true)
		var wp = wres.get("_player")
		if wp != null:
			for bt in wp.buffs:
				harvested_perm[bt] = int(wp.buffs[bt].permanentStacks)
		say("  [perm-harvest] %s 暖场 status=%s 永久栈=%s"
				% [case_id, str(wres.get("status")), str(harvested_perm)])
	# ★ np21-R5 双执行暖场（表与管线见文件头 R5_DUAL_EXEC 注）：独立 ctx 跑一遍
	#   干净第 1 次执行，截于事件闸 T_w、不清理；收割暖场玩家 permanentStacks
	#   （teardown 的 cleanse 不清永久栈——np18-C 语义）与存活连接（发射体=
	#   暖场玩家 && 接收体=玩家侧物品；暖场自然终局时 oracle 会跑 combatEndDeferred
	#   → disconnectAll，连接清空 ⇒ 不嫁接）。暖场递归自身禁止一切键控补偿
	#   （r5_warm=true 分支，见下方各键控点）。
	#   ★ 第四残留（fatigueCounter，本轮 gd↔语料@269 定谳）：oracle 的
	#   CombatTimer 是跨执行共享节点，fatigueCounter 只在 combatEnd() 复位
	#   （oracle/Interface/CombatTimer/CombatTimer.gd:98-99；start()/initialize()
	#   均不复位）。暖场 2878 ticks=47.97s > FATIGUE_TIME=17 ⇒ 暖场已入疲劳、
	#   截断不复位 ⇒ 正式场 hasFatigueStarted()（=fatigueCounter>0，:181-182）
	#   自 t=0 即真——语料 Owl Spirit 首个冷却即走 fatiguemana 分支（入场
	#   round(8×1)=8+放大掷，语料 12/11/10… v gd 干净场 mana=2 分支 2-4；
	#   oracle 复放 np21_r5 逐位复现语料 25006 事件、8 连 roll 掷点闭环）。
	#   值不敏感论证：正式 t=14 的 startFatigue 把 counter 复位 0
	#   （CombatTimer.gd:145-151 = CoreCombat.gd:437-441 同构），故残留值只经由
	#   「>0 ⇒ hasFatigueStarted」面可观测——注入暖场截断值即可，暖场两引擎
	#   截断 tick 差异（3095 v 2878）不影响本面。startBattle 已把 counter 清 0
	#   （CoreCombat.gd:149）、activateItems 只清 flag 不清 counter（:247），
	#   故注入点=startBattle 之后、tick 循环之前。
	if not perm_warm and not r5_warm \
			and OS.get_environment("ORACLE_ALIGN_NO_R5_DUAL_EXEC") == "" \
			and R5_DUAL_EXEC.has(case_id):
		var wres5 = run_case(c, out_root.plus_file("_r5_warmup"), false, true)
		var wp5 = wres5.get("_player")
		var wctx5 = wres5.get("_ctx")
		if wp5 != null and wctx5 != null:
			for bt in wp5.buffs:
				harvested_perm[bt] = int(wp5.buffs[bt].permanentStacks)
			if not bool(wres5.get("fight_ended")):
				# 第四残留只在截断路径存活（自然终局时 oracle endCombat→
				# CT.combatEnd() 会把 fatigueCounter 复位 0，:98-99）
				if wctx5.combat != null:
					r5_fatigue = int(wctx5.combat.fatigue_counter)
				for entry in wctx5.bus.connect_journal:
					if entry[0] == wp5 and entry[2] != null \
							and int(entry[2].ownerType) == CoreConst.Owner.PlayerInventory:
						r5_journal.push_back(entry)
		say("  [r5-warm] %s 暖场 status=%s ticks=%s events=%s 自然终局=%s 存活连接=%d 疲劳计数=%d 永久栈=%s"
				% [case_id, str(wres5.get("status")), str(wres5.get("ticks")),
					str(wres5.get("events")), str(wres5.get("fight_ended")),
					r5_journal.size(), r5_fatigue, str(harvested_perm)])
	var p = new_character(ctx, CoreCharacter.ID.PLAYER, c["player"])
	# ★ np18-C：收割值灌入（在播种/装配之前，零 rng 消耗——纯字段写）
	for bt in harvested_perm:
		if p.buffs.has(bt):
			p.buffs[bt].permanentStacks = int(harvested_perm[bt])
	# ★ np20-C：canonical 推导残留覆盖（表与推导见 PERM_STACK_OVERRIDE 注；
	#   暖场递归跑 perm_warm=true 时不生效——暖场必须保持干净语义）
	if not perm_warm and not r5_warm \
			and OS.get_environment("ORACLE_ALIGN_NO_PERM_HARVEST") == "" \
			and PERM_STACK_OVERRIDE.has(case_id):
		var _ov: Dictionary = PERM_STACK_OVERRIDE[case_id]
		for bt in _ov:
			if p.buffs.has(bt):
				p.buffs[bt].permanentStacks = int(_ov[bt])
	# ★ np17-B 暖场闩键控（表与机理见文件头 WARM_LATCH_PLAYERS 注）：脏录音受控
	#   补偿——仅键控场表内场生效，玩家初始即处「暖场残留」态；零 rng 消耗。
	#   np21-R5：暖场递归（r5_warm=true = 录制进程第 1 次执行）不适用——闩是
	#   第 2 次执行的残留，第 1 次执行玩家为净态。
	if not perm_warm and not r5_warm \
			and OS.get_environment("ORACLE_ALIGN_NO_WARM_LATCH") == "" \
			and WARM_LATCH_PLAYERS.has(case_id):
		p.attack_moving_forward = true
	ctx.rng.rng.seed = seed_value
	# ★ 逐抽追踪自播种即开启（阶段2）：装配期的每次链抽取都进 rng_trace.txt，
	#   与神谕 rng_log.txt（含装配期包装抽）做子序列值对齐用。
	if trace_on:
		ctx.rng.oracle_trace = true
	# （阶段2）播种后不再补空转：装配期消耗=内核物品双绑定+Flicker 入树+对手
	# 角色 8 步，已与神谕逐场零残差（见文件头 ORACLE_SCENE_DRAWS 删除说明）。
	# ★ 阶段3 次序修正（oracle_fight.gd:567-597 实证）：播种后的装配次序必须是
	#   「玩家物品（startHistoryRun:2711 createFromItemTuples，post-seed）→
	#   对手角色（finishSwitchingToCombat:2581 opponentScene.instance()，8 步
	#   BalancedRng）→ 对手物品（initHistoryOpponent）」——此前对手角色的 8 步
	#   插在玩家物品之前，总步数虽同（阶段2 状态零残差），但每个装配抽取的
	#   **值**随链位漂移；入树抽取（Flicker/Connector/Gem）的值作为 callDelayed
	#   时长等侧效应泄漏进战斗期，注入后无法对齐（run1122_r11 逐抽对位实证：
	#   玩家 Oil Lamp 闪烁时长 2.586 vs 神谕 1.521）。
	# ★ 描述符预注册（2026-10-10 round 修复：isA 身份链占位符缺口）：
	#   CoreItemBook.getDescriptor 对未注册名惰性造「零值占位实例」，装配层
	#   register 随后用真实数据**换掉**表项——早于真实注册拿到占位引用的物品
	#   （Buy the Holy Light._readyInit 的 getDescriptor("Oil Lamp")，装配序在
	#   灯之前的场次）此后 isA 恒 false（Item.isA = 引用相等），canAffect 的
	#   全局灯面静默失效：run634_r18 玩家灯缺 +0.40 speed（BtHL onPrepare
	#   addSpeed），冷却恒慢 → idx140 激活缺失 → idx141 龙伤 3v5 链式漂移。
	#   真游戏里全部物品共享同一份 .tres 描述符资源，不存在「先占位后换实例」。
	#   修法 = 放置任何物品（含宝石）前，把本场两侧全部真实描述符先注册进
	#   item_book，占位窗口归零。纯数据面操作，零 rng 消耗。
	for _pre_side in [c["player"], c["opponent"]]:
		for _pre_e in _pre_side["items"]:
			descriptor_of(ctx, _pre_e["key"])
			for _pre_g in _pre_e["gems"]:
				if _pre_g != null and typeof(_pre_g) == TYPE_DICTIONARY:
					descriptor_of(ctx, _pre_g["key"])

	# ★ op6 修复（Stone×29 簇根因）：原版时序=角色（含 INVENTORY）先于任何物品
	#   装配（Game.startHistoryRun 先 instanceCharacter，物品后入包）。此前玩家
	#   物品 place_one 先于 combat.setup（ctx.player 在 setup 内才绑定）→
	#   BagofStones.getAffectedCellsAfterRotate_primary 读 ctx.player.INVENTORY
	#   时 ctx.player 为 null → affected 空缓存 → setBagOfStones 不达 →
	#   Stone.ammunition 停 1 → 首击 ==0 → onAfterEffectFinished 永冻
	#   （run569_r11 CDSPY 实证 deact t=3.233 amm=0）。
	#   op6 不变量保持方式（r17 批2 通道 A 重排）：ctx.player / ctx.combat 仍在
	#   玩家物品装配**之前**绑定（下方直赋，combat.setup 稍后补完整接线）。
	# ★ 阶段3 装配次序落地（oracle_fight.gd:567-597 实证；run818_r5 raw 级对位
	#   定谳，r17 批2 通道 A）：神谕播种后的装配次序 =
	#   「玩家物品（raw0-41）→ 对手角色 4 抽 BalancedRng（raw42-45，
	#   Character.gd:94-97）→ 对手物品（raw46-87）」——此前对手角色的 4 抽
	#   （new_character→CoreCharacter._init，CoreCharacter.gd:207-210）插在
	#   玩家物品之前（gd raw0-3），玩家侧每笔装配抽取整体 +4 插位：窗口内
	#   ctor/ready 抽互换 raw → BalancedRng expectedWins ctor 值差 → 战斗期
	#   值差族（run628_r14 idx37 O8/G11 纯值差、run818_r5 idx70 dmg 16vs17、
	#   Flicker callDelayed 延迟值/Connector/Gem 装配值同理）。
	#   r14「ready 抽未内联」误诊纠正：raw 级复核对读（output/oracle/align/
	#   gdcore/run818_r5/rng_trace.txt vs probe/r14_dd/run818_r5/rng_log_first.txt）
	#   证明两侧逐物品本就是 [2 ctor][ready] 紧邻结构（gd F@20/23/26、conn@43
	#   == oracle 16/19/22、39 各 +4 的纯平移），唯对手角色块错位——_readyInit
	#   段零改动。安全性：全工程装配期钩子（_readyInit/onAddToInventory/
	#   onItemAdded/getAffectedCellsAfterRotate*）零处读 ctx.opponent/ctx.combat
	#   （r17 批2 全量扫描）；CoreItem.addToInventory 的 ownerType 判定对
	#   ctx.opponent 判空（CoreItem.gd:591-594）且 place_one 显式传 ownerType。
	var combat = CoreCombat.new(ctx)
	combat.max_time = MAX_TIME
	ctx.player = p
	ctx.combat = combat
	var p_items := []
	for e in c["player"]["items"]:
		var it = place_one(ctx, p, e, CoreConst.Owner.PlayerInventory)
		if it == null:
			res["status"] = "assembly-fail"
			return res
		p_items.push_back(it)
	# 对手角色 4 抽落神谕位：玩家物品之后、对手物品之前
	var o = new_character(ctx, CoreCharacter.ID.OPPONENT, c["opponent"])
	combat.setup(p, o)      # 完整接线（ctx.player/ctx.combat 重赋值幂等）
	var o_items := []
	for e in c["opponent"]["items"]:
		var it = place_one(ctx, o, e, CoreConst.Owner.Opponent)
		if it == null:
			res["status"] = "assembly-fail"
			return res
		o_items.push_back(it)
	# ★ 对齐 Game.initHistoryOpponent:2857-2858（RECALC-O-TAIL 铁证）：
	# 对手装配尾部显式 recalculateMaxStamina——数 INVENTORY 袋（run592 OPP
	# max=7 sacks=2 / run813 OPP max=7 sacks=2）。PLAYER 侧无此步（跨场
	# queued 残留 → deferred recalc 恒早退 → max=快照基值）。
	o.recalculateMaxStamina()

	var order := activation_order(seed_value, p_items, o_items)
	res["activation_order"] = order
	# ★ 阶段1 神谕 rng state 注入：装配（角色+物品实例）完成后、startBattle 的
	#   prepareItems/activateItems 与逐 tick 判定链之前，把神谕捕获的 Util.rng
	#   state 直灌内核（ctx.set_state → rng.state 直写，不前进不重播）——绕开
	#   装配期消耗差异，隔离战斗期。机制前提：两侧 prepareItems 同点把全部
	#   BalancedRng 重置归零（原版 Item.gd:3345-3351 / Character.gd:294-317；
	#   内核 CoreItem.gd:531 / CoreCharacter.gd:259），链 state 唯一决定后续掷点。
	# ★ 阶段2 无注入模式（ORACLE_ALIGN_NO_INJECT=1）：不读 rng_state.txt、不
	#   set_state——装配期消耗面已与神谕逐场零残差，从 seed 起跑整条链即为
	#   阶段2 的判定本体（docs/alignment_fix_workflow.md §2 阶段2 退出标准）。
	#   默认关 = 阶段1 注入行为不变。
	#   np21-R5：暖场（r5_warm）恒走无注入——录制进程第 1 次执行从 seed 起跑
	#   全链（rng_state.txt 是第 2 次执行装配后导出的，对暖场是未来状态）。
	var no_inject := r5_warm or OS.get_environment("ORACLE_ALIGN_NO_INJECT") != ""
	if no_inject:
		res["rng_state_injected"] = false
	else:
		var rng_state_txt := read_rng_state(case_id)
		if rng_state_txt.empty():
			say("FAIL %s 缺 rng_state.txt（%s）——先重跑神谕批量补导出"
					% [case_id, _fights_root])
			res["status"] = "missing-rng-state"
			return res
		ctx.set_state(int(rng_state_txt))

	# 物品要在 combat.setup() 之后装；preordered=true 直通激活顺序
	# ★ 阶段2 装配对齐探针（ORACLE_ALIGN_DUMP_STATE=1）：无注入模式下把
	#   startBattle 前的链状态落盘，与神谕 rng_state.txt 直接对表——
	#   逐位一致 = 装配期消耗面（次数+次序合并效果）完全等价。
	if OS.get_environment("ORACLE_ALIGN_DUMP_STATE") != "":
		var d2 = Directory.new()
		if not d2.dir_exists(dir):
			d2.make_dir_recursive(dir)
		var sf = File.new()
		sf.open(dir.plus_file("kernel_state.txt"), File.WRITE)
		sf.store_string("seed=%d" % ctx.rng.rng.get_seed())
		sf.store_string("state=%d" % ctx.rng.rng.state)

		sf.close()
	# ★ np21-R5 连接泄漏嫁接（管线与证据链见文件头 R5_DUAL_EXEC 表注）：把暖场
	#   存活连接按暖场时序挂上正式 bus——发射体映射为正式玩家（oracle 里 PLAYER
	#   节点跨执行复用，暖场连接的发射体与正式发射体是同一节点）；此刻正式侧
	#   onPrepare 连接尚未建立（startBattle→prepareItems 才连）⇒ 追加即天然
	#   「陈旧先于新鲜」，与语料投递序一致。陈旧接收体（含宝石）的 ctx/character_
	#   与三处抽源改指正式侧（oracle：节点/Util.rng 进程级共享 ⇒ 天然指向正式；
	#   陈旧处理器消耗正式链 rng、应答入正式日志——run696@79/run1371@137 旁证）。
	#   BalancedRng 平衡态保留暖场值（正式 prepareItems 重置只遍历正式清单）。
	#   纯内存字段写 + bus 连接表追加，零 rng 消耗。
	var stale_receivers := {}
	if r5_journal.size() > 0:
		for entry in r5_journal:
			ctx.bus.connectEvent(p, String(entry[1]), entry[2], String(entry[3]))
			if not stale_receivers.has(entry[2].get_instance_id()):
				stale_receivers[entry[2].get_instance_id()] = entry[2]
		for _rid in stale_receivers:
			var _rcv = stale_receivers[_rid]
			_rcv.ctx = ctx
			_rcv.character_ = p
			if _rcv.damageSource != null:
				_rcv.damageSource._rng = ctx.rng
			if _rcv.chanceRng != null:
				_rcv.chanceRng._rng = ctx.rng
			if _rcv.damageRangeRng != null:
				_rcv.damageRangeRng._rng = ctx.rng
		var _rcv_names := []
		for _rid0 in stale_receivers:
			_rcv_names.push_back(String(stale_receivers[_rid0].descriptor.identifier))
		say("  [r5-graft] %s 陈旧连接 %d 条（接收体 %d 个：%s）挂正式 bus（陈旧先于新鲜）"
				% [case_id, r5_journal.size(), stale_receivers.size(), str(_rcv_names)])
	# ★ np21-R5 陈旧标签槽占用键控（run1371 定谳）：暖场截断在高事件密度
	#   尾段，陈旧实例的 buffLabelPositionTimestamps 五槽在截断时刻普遍处于
	#   「刚占用」态（语料/探针首跑在首个陈旧应答标签即走回退分支 randInBox
	#   (30,30)，gd 干净暖场尾部标签密度不足走了空槽分支 (10,10)→链值即歧，
	#   np21r5_dbg16 draw452 实证）。复刻=嫁接时把陈旧接收体五槽置「刚占用」
	#   （ts=ctx.time+1.5，0.5s 后自然回收，此后按真实演化）。纯字段写。
	var _r5_busy_labels := bool(R5_DUAL_EXEC.get(case_id, {}).get("stale_label_slots_busy", false)) 			and not r5_warm
	if _r5_busy_labels and stale_receivers.size() > 0:
		for _rid3 in stale_receivers:
			var _rcv3 = stale_receivers[_rid3]
			for _si in range(_rcv3.buffLabelPositionTimestamps.size()):
				_rcv3.buffLabelPositionTimestamps[_si] = ctx.time + 2.5
	# ★ np21-R5 stale_used_stacks 键控覆盖（np20-C canonical 封闭推导同型；
	#   表注见 R5_DUAL_EXEC 对应行）：gd 干净暖场收官值 ≠ 语料录制批（旧树）
	#   收官值时，按语料事件面推导真值覆盖陈旧实例计数器（仅该一维——
	#   entries 序列等价类内任取值等价；net-p 无需覆盖，见推导注）。
	var _r5_ov: Dictionary = R5_DUAL_EXEC.get(case_id, {}).get("stale_used_stacks", {})
	if r5_journal.size() > 0 and not _r5_ov.empty():
		for _rid2 in stale_receivers:
			var _rcv2 = stale_receivers[_rid2]
			if _rcv2.descriptor == null or not _r5_ov.has(String(_rcv2.descriptor.identifier)):
				continue
			var _bt_ov: Dictionary = _r5_ov[String(_rcv2.descriptor.identifier)]
			for _bt in _bt_ov:
				if _rcv2.usedStacks != null and _rcv2.usedStacks.has(int(_bt)):
					_rcv2.usedStacks[int(_bt)] = float(_bt_ov[_bt])
		say("  [r5-graft] %s 陈旧计数器覆盖：%s" % [case_id, str(_r5_ov)])

	combat.startBattle(by_order(p_items, order["player"]),
			by_order(o_items, order["opponent"]), true)

	# ★ np21-R5 第四残留注入（fatigueCounter，机理与值不敏感论证见上方
	#   [r5-warm] 块注）：startBattle 已清 counter（CoreCombat.gd:149）、其后
	#   activateItems 只清 flag 不清 counter（:247），故此处注入后仅经
	#   hasFatigueStarted()（=counter>0）面可观测；t=14 startFatigue 照常复位。
	#   纯字段写，零 rng 消耗。
	if r5_fatigue > 0:
		combat.fatigue_counter = r5_fatigue

	var ticks := 0
	var tick_states := []
	# ★ oracle M12 事件数闸对位（oracle_fight.gd:742-744：events.size()>25000
	#   → 提前判停，status=timeout，已产生事件照常 dump；winner 不判胜）。
	#   gd 此前缺此闸 → length×6 簇（run685_r18 等事件前缀 25030 逐位同、
	#   oracle status=timeout/winner=-，gd 继续跑到自然终局 → 事件数与
	#   渲染战报长度分歧）。核 gd 事件计数源=combat_log（对齐 oracle
	#   combatLog.events）。
	#   np21-R5：暖场（r5_warm）用表内 T_w 闸（=暖场截断点，语料侧封闭推导，
	#   见 R5_DUAL_EXEC 表注）；np22 重录三场正式腿用 NP22_REC_EV_GATE 对位
	#   抬闸（录制工件对位，见该表注）；其余场维持 M12 常数 25000。
	var ev_gate := int(NP22_REC_EV_GATE.get(case_id, 25000))
	if r5_warm:
		ev_gate = int(R5_DUAL_EXEC[case_id]["warm_event_gate"])
	# np21-R5 一次性 θ 复位（run1371 键控）：表内 theta_time 时刻把玩家闩
	#   复位一次，此后首攻跑完整本体并自动再闩（playAttackAnimation 尾部
	#   attack_moving_forward=true）。纯字段写，零 rng 消耗。
	var r5_theta_t := float(R5_DUAL_EXEC.get(case_id, {}).get("theta_time", -1.0))
	if r5_warm:
		r5_theta_t = -1.0
	# ★ np21-R5 stale_timer_left 键控（run1444 定谳，见 R5_DUAL_EXEC 表注）：
	#   暖场自然收尾时 PLAYER 复用节点的 Buff 计时器引擎残差（teardown 只 stop
	#   不清 wait/time_left）。注入点=activateItems 之后首个 tick（开战延迟
	#   2.5s 末的 activateItems 尾 character.resetTimersSync 会清更早的注入）
	#   ⇒ tick 循环内 one-shot（激活当拍末）。命中 ①' 旧剩余续扣支。零 rng。
	var _r5_stl: Dictionary = R5_DUAL_EXEC.get(case_id, {}).get("stale_timer_left", {})
	var _r5_stl_done := r5_warm or _r5_stl.empty()
	while not combat.fight_ended and ticks < MAX_TICKS:
		combat.physicsTick(CoreContext.PHYSICS_DELTA)
		ticks += 1
		if not _r5_stl_done and combat.activated:
			_r5_stl_done = true
			for _bt5 in _r5_stl:
				if p.buffs.has(int(_bt5)):
					var _sb = p.buffs[int(_bt5)]
					_sb._timer_active = false
					_sb._timer_left = float(_r5_stl[_bt5])
					_sb._timer_e0 = float(_r5_stl[_bt5])
					_sb._timer_e1 = 3.0
			say("  [r5-stl] %s 激活后注入=%s" % [case_id, str(_r5_stl)])
		if r5_theta_t >= 0.0 and combat.combat_time >= r5_theta_t:
			if p.attack_moving_forward:
				p.attack_moving_forward = false
			r5_theta_t = -1.0
		if probe.rows.size() > ev_gate:
			if r5_warm:
				print("[watchdog-gd][r5-warm] 暖场事件数超 %d，截断（保留实例不清理）" % ev_gate)
			else:
				print("[watchdog-gd] 事件数超 %d，提前判停（M12 对位）" % ev_gate)
			break
		# ★ np2 trace 死因诊断桩（零链消耗，ORACLE_RNG_DIAG=1 开启）：每 60 tick
		#   记录 rng 实例 id / oracle_trace 开关 / 账长 / 链态——定位「战斗中段
		#   trace 全停」是开关翻转、实例替换还是账清空（np2a/np2b 双进程竞写
		#   干扰下的 run695 811 行谜团取证）。
		if trace_on and OS.get_environment("ORACLE_RNG_DIAG") != "" and ticks % 60 == 0:
			print("[RNGDIAG] tick=%d t=%.3f inst=%d trace=%s log=%d state=%d ev=%d" % [
				ticks, combat.combat_time, ctx.rng.get_instance_id(),
				str(ctx.rng.oracle_trace), ctx.rng.oracle_trace_log.size(),
				ctx.rng.rng.state, probe.rows.size()])
		# ★ 逐 tick 链状态（与神谕 oracle_fight.gd 的 _cur_tick_states 同构：
		#   每物理 tick 结束时的 Util.rng.state）——跨引擎「首个分叉 tick」
		#   定位用（ORACLE_ALIGN_TICKS=1 时落盘）。
		if trace_on:
			tick_states.push_back(ctx.rng.rng.state)
			# ★ ORACLE_TRACE_ITEM：逐 tick dump 目标物品 triggerTime/speed
			#   （F7 1-tick 漂移定位；harness 侧，零 rng 消耗）
			var _ti := OS.get_environment("ORACLE_TRACE_ITEM")
			if _ti != "":
				if ticks == 1:
					var _cnt := 0
					var _nm := []
					for _chr in [combat.player, combat.opponent]:
						_cnt += _chr.inventory.getItems().size()
						for _it in _chr.inventory.getItems():
							_nm.push_back(_it.descriptor.identifier)
					print("[F7DBG-K] items=%d first=%s match=%s" % [_cnt, str(_nm.slice(0, 5)), str(_nm.has(_ti))])
				var _rows := []
				for _chr in [combat.player, combat.opponent]:
					for _it in _chr.inventory.getItems():
						if _it.descriptor.identifier == _ti:
							_rows.append("%d %.9f %.9f %.9f %d %d %.9f" % [ticks + 1, _it.triggerTime,
									_it.getSpeed(), _it.iterationCooldown, int(_it.isCooldownActive()), int(_it.ownerType), combat.combat_time])
				if _rows.size() > 0:
					var _tf2 := File.new()
					if ticks == 1:
						_tf2.open(dir.plus_file("item_trace.txt"), File.WRITE)
					else:
						_tf2.open(dir.plus_file("item_trace.txt"), File.READ_WRITE)
						_tf2.seek_end()
					_tf2.store_string(PoolStringArray(_rows).join("|") + "|")
					_tf2.close()
	res["ticks"] = ticks
	res["combat_time"] = float(combat.combat_time)
	res["fight_ended"] = bool(combat.fight_ended)
	res["timed_out"] = bool(combat.timed_out)
	res["player_hp"] = float(p.curHealth)
	res["player_max_hp"] = float(p.maxHealth)
	res["opponent_hp"] = float(o.curHealth)
	res["opponent_max_hp"] = float(o.maxHealth)

	if combat.fight_ended:
		var w = combat.winner()
		res["winner"] = "player" if w.playerId == CoreCharacter.ID.PLAYER else "opponent"
		# 合成终局事件（对齐原版 CombatLog.onCombatEnd → logWin/logLoss：
		# afterFightAllowed=true 绕过 fightEnded 闸；id = 下一个 createEvent 的 id）
		var is_win: bool = res["winner"] == "player"
		var etype: int = 111 if is_win else 112
		probe.rows.append({
			"id": int(ctx.combat_log.eventNum) + 1,
			"type": etype,
			"type_name": "Win" if is_win else "Loss",
			"timestamp": float(combat.combat_time),
			"origin": etype,
			"target": null,
			"parent_id": - 1,
			"params": {},
		})
	else:
		res["status"] = "timeout"

	res["events"] = probe.rows.size()
	if probe.rows.empty():
		res["status"] = "no-events"
	# ★ np18-C：玩家引用仅随内存字典返回（供暖场收割读取 permanentStacks），
	#   不进 events.json payload（payload 为显式字段表）。
	#   np21-R5：附带返回 ctx（暖场连接台账/嫁接消费；同样仅内存引用）。
	res["_player"] = p
	res["_ctx"] = ctx

	var d = Directory.new()
	if not d.dir_exists(dir):
		d.make_dir_recursive(dir)
	var fh = File.new()
	var payload = {
		"case_id": case_id, "seed": seed_value, "round_id": int(c["round_id"]),
		"below_master": true, "preordered": true,
		"rng_state_injected": not no_inject,
		"no_inject": no_inject,
		"combat_time": res["combat_time"], "ticks": res["ticks"],
		"fight_ended": res["fight_ended"], "timed_out": res["timed_out"],
		"winner": res["winner"],
		"player_hp": res["player_hp"], "player_max_hp": res["player_max_hp"],
		"opponent_hp": res["opponent_hp"], "opponent_max_hp": res["opponent_max_hp"],
		"activation_order": order,
		"event_count": probe.rows.size(), "events": probe.rows,
	}
	if fh.open(dir.plus_file("events.json"), File.WRITE) == OK:
		fh.store_string(JSON.print(payload, "  "))
		fh.close()
	else:
		res["status"] = "io-fail"
	if trace_on and not ctx.rng.oracle_trace_log.empty():
		var tf = File.new()
		if tf.open(dir.plus_file("rng_trace.txt"), File.WRITE) == OK:
			# ★ 流式逐行写（np2 修）：此前先攒 rows 数组再 PoolStringArray.join，
			#   大赛（10 万+抽）join 阶段整进程静默崩溃 → rng_trace.txt 恒 0 字节
			#   （run977/run695 实证，events.json 已完整写出后死在 trace 步）。
			# ★ np2 修2：行按实际元数拼接——取证桩行（LGPROC/LGDEC/BSCHED 等直
			#   push 的 4 元素标记）此前硬取 e[4] → 格式化脚本错误**中断写循环**，
			#   trace 从首个 4 元素行起截断（run695 恒 811 行实锤：LG 首proc 恰在
			#   t=0.667）。标记行非数值抽，对拍工具本就过滤，格式宽松即可。
			for e in ctx.rng.oracle_trace_log:
				if e.size() >= 5:
					# 栈签名（ORACLE_ALIGN_STACKTRACE=1 时第 6 列）逐抽附调用方
					if e.size() > 5:
						tf.store_line("%d %s %s %s => %s | %s" % [e[0], e[1], e[2], e[3], e[4], e[5]])
					else:
						tf.store_line("%d %s %s %s => %s" % [e[0], e[1], e[2], e[3], e[4]])
				else:
					var parts := []
					for v in e:
						parts.append(str(v))
					tf.store_line(PoolStringArray(parts).join(" "))
			tf.close()
	if trace_on and not tick_states.empty():
		var sf = File.new()
		if sf.open(dir.plus_file("tick_states.txt"), File.WRITE) == OK:
			var srows := []
			for s in tick_states:
				srows.append(String(s))
			sf.store_string(PoolStringArray(srows).join("\n") + "\n")
			sf.close()
	if res["status"] == "FAIL":
		res["status"] = "ok"
	return res


func _init() -> void :
	say("ORACLE-ALIGN(gd_core): 受控神谕三方对齐——gd_core 侧批量重放（无头）")
	var t0 := OS.get_ticks_usec()

	var fh = File.new()
	if not fh.file_exists("res://oracle_align_cases.json"):
		say("FAIL 缺 res://oracle_align_cases.json（先跑 tools/gen_fixture_from_lineup.py --oracle）")
		quit(1)
		return
	fh.open("res://oracle_align_cases.json", File.READ)
	var parsed = parse_json(fh.get_as_text())
	fh.close()
	if typeof(parsed) != TYPE_DICTIONARY or not (parsed.get("cases", []) is Array):
		say("FAIL oracle_align_cases.json 格式错误")
		quit(1)
		return
	var cases: Array = parsed["cases"]

	# 可选定向（ORACLE_ALIGN_CASES=id1,id2,…）：只跑指定用例（保文件顺序）。
	# 阶段1 试点用（docs/alignment_fix_workflow.md §2）：按物品数选
	# 中位/最大/最小各一先做逐行比对。
	var only_ids := {}
	for only_id in OS.get_environment("ORACLE_ALIGN_CASES").split(",", false):
		only_ids[only_id] = true
	if not only_ids.empty():
		var only_kept: Array = []
		for c in cases:
			if only_ids.has(String(c["case_id"])):
				only_kept.push_back(c)
		cases = only_kept
		say("★ 定向：ORACLE_ALIGN_CASES → %d 场" % cases.size())

	var tf = File.new()
	tf.open("res://item_battle_fixture.json", File.READ)
	_table = parse_json(tf.get_as_text())
	tf.close()
	if _table == null or not _table.has("items"):
		say("FAIL item_battle_fixture.json 缺 items 表")
		quit(1)
		return

	var out_root = OS.get_environment("ORACLE_ALIGN_OUT")
	if out_root.empty():
		out_root = ProjectSettings.globalize_path("res://..").plus_file("output/oracle/align/gdcore")
	var d = Directory.new()
	if not d.dir_exists(out_root):
		d.make_dir_recursive(out_root)
	# 神谕语料根（rng_state.txt 来源）——gd_core_test 的 res://.. 即仓库根
	_fights_root = ProjectSettings.globalize_path("res://..").plus_file("output/oracle/fights")

	# 断点续跑（幂等）：events.json 已存在且 event_count>0 → 跳过
	var limit := int(OS.get_environment("ORACLE_ALIGN_LIMIT"))
	var chunk := int(OS.get_environment("ORACLE_ALIGN_CHUNK"))
	var pending: Array = []
	var skipped := 0
	for c in cases:
		if limit > 0 and pending.size() >= limit:
			break
		if case_done(out_root.plus_file(String(c["case_id"]))):
			skipped += 1
			continue
		pending.push_back(c)
	say("用例 %d 场（resume 跳过 %d，本进程待跑 %d）" % [cases.size(), skipped, pending.size()])

	var fails: Array = []
	var first_done := false
	var first_summary := ""
	var selfcheck := OS.get_environment("ORACLE_ALIGN_SELFCHECK") != "0"
	var run_here := 0
	for i in range(pending.size()):
		var c: Dictionary = pending[i]
		var t1 = OS.get_ticks_usec()
		var res = run_case(c, out_root)
		run_here += 1
		var ms = (OS.get_ticks_usec() - t1) / 1000.0
		var row = "[%4d/%d] %-16s %-8s ticks=%4d t=%6.2f ev=%5d %6.0f ms" % [
			i + 1, pending.size(), c["case_id"], res["status"], int(res["ticks"]),
			float(res["combat_time"]), int(res["events"]), ms]
		say("  " + row)
		if res["status"] != "ok":
			fails.append(String(c["case_id"]) + ": " + String(res["status"]))
		if not first_done and res["status"] == "ok":
			first_done = true
			if selfcheck:
				# 确定性自证：同种子紧邻复跑，事件 JSON 逐字节比对（神谕 [M7] 同款）
				var p1 = out_root.plus_file(String(c["case_id"])).plus_file("events.json")
				var f1 = File.new()
				f1.open(p1, File.READ)
				var first_text = f1.get_as_text()
				f1.close()
				var res2 = run_case(c, out_root)
				var f2 = File.new()
				f2.open(p1, File.READ)
				var second_text = f2.get_as_text()
				f2.close()
				if res2["status"] == "ok" and second_text == first_text:
					say("  [selfcheck] %s 同种子复跑逐字节一致 ✓" % String(c["case_id"]))
				else:
					fails.append(String(c["case_id"]) + ": selfcheck-复跑不一致")
					say("  [selfcheck] FAIL %s 复跑不一致（首跑留档见上）" % String(c["case_id"]))
				first_summary = "（selfcheck 已消耗一次复跑）"
		if chunk > 0 and run_here >= chunk:
			say("[chunk] 本进程配额 %d 场已满，优雅退出；重跑自动续接" % chunk)
			break

	var secs = (OS.get_ticks_usec() - t0) / 1000000.0
	var ok := fails.empty()
	say("")
	say("ORACLE-ALIGN(gd_core): %s（实跑 %d 场，跳过 %d，用时 %.1fs%s）"
			% ["PASS" if ok else "FAIL", run_here, skipped, secs, first_summary])
	for f in fails:
		say("  - " + f)
	var rf = File.new()
	if rf.open(out_root.plus_file("_align_gd_summary.txt"), File.WRITE) == OK:
		rf.store_string(PoolStringArray(_report).join("\n") + "\n")
		rf.close()
	quit(0 if ok else 1)


# 断点续跑判据：events.json 存在且 event_count>0
func case_done(dir: String) -> bool :
	var fh = File.new()
	var p = dir.plus_file("events.json")
	if not fh.file_exists(p):
		return false
	fh.open(p, File.READ)
	var txt = fh.get_as_text()
	fh.close()
	if txt.empty():
		return false
	var parsed = parse_json(txt)
	if typeof(parsed) != TYPE_DICTIONARY:
		return false
	return int(parsed.get("event_count", 0)) > 0
