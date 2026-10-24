extends SceneTree
# =============================================================================
# oracle_fight.gd — 受控神谕批量重放（原版引擎 + 原版 1.1.8 反编译脚本）
# =============================================================================
# 运行方式（全程无头后台，无任何可见窗口）：
#   output/godot36/Godot_v3.6-stable_win64.exe --headless --path oracle --script oracle_fight.gd
#
# 批量语义（对照任务书）：
#   1) 读 res://fights.json（用例数组 case_id/seed/run_id/round_id），单进程内
#      顺序跑完全部用例——绝不逐场起进程。环境变量 ORACLE_FIGHT_LIMIT=N 可裁剪
#      为 N 场「按玩家职业分层轮转」的样本（保序）；不设则全量。
#      断点续跑（幂等，无条件生效）：output/oracle/fights/<case_id>/events.json
#      已存在且事件非空的用例直接跳过——支持超时/中断后原地继续。
#   2a) 阵容装配：oracle/data/history.db（本地只读快照）→ 拷贝到隔离 user:// →
#       原版 godot-sqlite 打开 → 原版 BuildHistoryData.addRoundData/getRoundData
#       → 原版 RunData.deserializeItems（deserializeRound 的解码核心，零失真）。
#       玩家侧 = 原版 Game.startHistoryRun 逐句（1.1.8 @ Core/Game.gd:2402-2427，
#       去 UI 过场）；对手侧 = 原版 Game.finishSwitchingToCombat 的标记对手分支
#       （@2582-2588）+ 原版 Game.initHistoryOpponent（@2829-2858）逐行调用。
#   2b) ★ 确定性约定（两侧模拟器必须逐条复刻）：
#       · 每场开始：先复用 PLAYER（instanceCharacter，其「职业切换」tween 的
#         2 次 rng 消耗被有意放在播种前 → 被本场 seed 重置，模拟器无需复刻），
#         然后任何物品实例创建之前：Util.rng.seed = seed（PCG32 全链重置）+
#         全局链 seed(seed)（Array.shuffle/pick_random 消费引擎全局链）。
#       · 播种后的链上消耗，固定次序 = 代码调用次序：
#         玩家物品逐件实例（Item.gd:472 每件 BalancedRng.new() 消耗 2 步，宝石同）
#         → 对手 Character 实例（Character.gd:94-97 四个 BalancedRng = 8 步）→
#         对手物品逐件（同玩家）→ 开战（prepareItems 的 onPrepare 钩子、
#         activateItems 的 preCombatStart/combatStart/postCombatStart 钩子）。
#         两侧装配均按 buildInfo 反序列化流顺序经原版 sort_BagOrder（袋优先，
#         Core/Game.gd:5387-5388）后的顺序执行，最终装配顺序原样 dump 进
#         lineups.json（模拟器侧直接按该顺序重建即可）。
#   2c) ★ 手动 tick 循环突破实时速度：主循环完全停摆（阻塞在本次调用里），以
#       固定 dt=1/60 逐 tick 驱动战斗，直到判胜（Game.fightEnded）或 5400 tick
#       （90s 游戏时间）上限。每 tick 的驱动面 = 原版引擎一个物理帧等价路径，
#       按场景树次序（引擎同帧语义：physics 全部节点 → 物理 Timer → 空闲 Timer
#       → SceneTreeTimer）：
#         ① Util 时钟（等价 Utility/Util.gd:145-157 的 _physics_process：
#            time/frameCounter；_process 的 clockTime；鼠标跟踪不需要）
#         ② 对手角色 Core/Character.gd:1029（眩晕倒计时 + 体力再生）
#         ③ 对手物品 Items/Item.gd:4437（冷却推进 + trigger()；仅
#            is_physics_processing() 的物品——与引擎调度面一致）
#         ④ CombatTimer Interface/CombatTimer/CombatTimer.gd:139-141（combatTime
#            += dt，即事件时间戳源 getTimeStamp @143）
#         ⑤ 玩家角色 + 物品（同 ②③）
#         ⑥ 物理型 Timer（Buff 临时层数计时器，Core/Buff.gd:35）
#         ⑦ 空闲型 Timer（角色 TickTimer=1s 再生/毒素、疲劳 FatigueStartTimer/
#            FatigueTickTimer、激怒/无敌计时、Character.tscn 场内全部 Timer）
#         ⑧ SceneTreeTimer（Util.callDelayed 系：物品 z 回落、龙蛋孵化
#            Items/DragonEgg.gd:65、闪烁动画 Items/Animations/FlickerAnimation.gd:14…）
#       战斗判定链不动：角色死亡 → character_died → Game.endCombat（原版）。
#       判胜即冻结：挂起的延迟调用不再补发（原版战斗事件在 fightEnded 后同样
#       不再入日志）。
#   2d) 每场 dump：output/oracle/fights/<case_id>/events.json（原版
#       CombatLog.events 全量：type/时间戳/origin/params）、lineups.json（双方
#       装配后阵容，保留装配顺序）、result.txt（结果摘要 + 全部桩化记录）。
#   3) ★ 红线硬保证（不变式，违者断言失败）：
#       · 绝不加载主游戏场景 Main.tscn——排名/休闲/在线入口在神谕内物理不存在。
#         根下 "Main" 是 oracle_bootstrap.gd 程序化搭的最小战斗骨架（空节点 +
#         原版 CombatTimer/CombatLog 脚本），与主场景文件无关；本脚本首尾各一条
#         ResourceLoader.has_cached 断言自证。
#       · 绝不联网：SilentWolf/RunDatabase/CrazySDK/Steam 四 autoload 已桩化
#         （oracle_stubs/，桩化记录见各文件头）；无任何 HTTP/Steam 调用路径。
#       · 绝不写 Steam 版游戏目录：数据源是本地快照拷贝，且先复制到隔离 user://
#         再打开（原快照只读）。config/name=BackpackBattlesOracle 与玩家存档隔离。
#   4) 效率：手动 tick 下每场毫秒-秒级；跑完后对首场做同种子复跑做确定性自证。
#
# 与原版的偏离（全部记录进每场 result.txt 的 modifications）：
#   [M1] Util.callDelayed/setDelayed 系在原版行为之上追加登记（oracleDelayedTimers），
#        供本脚本驱动 SceneTreeTimer——正常主循环下登记是纯增量，行为不变
#        （oracle/Utility/Util.gd「ORACLE HARNESS」区块）。
#   [M2] Util.changeTimer / CombatTimer.advanceTime / Buff 三处读 Timer 剩余时，
#        手动 tick 期间以注册表剩余为准（Util.oracleTimeLeft）——阻塞循环里引擎
#        读数冻结，不桥接则等价语义被破坏。
#   [M3] oracle_bootstrap.gd 补挂疲劳链两条 [connection]（等价 Main.tscn:14984-14985）。
#   [M4] 开战过场（sceneAnimation/ShopToCombat 动画、shopToCombat 角色入场动画、
#        call_deferred(prepareItems) + callDelayed(activateItems, 2.5s)）压缩为
#        顺序调用——延迟期间无 rng 消耗点、无事件产生，逐 tick 等价；
#        combatTime 在 activateItems 前清零（等价 onCombatSceneEntered 的
#        combatTime=0），事件时间戳从 0 起（gd_core 同约定）。
#   [M5] UI/音频单例（Sound/动画/飘字）照常调用但输出进虚空（无头音频 dummy、
#        节点不入屏）；其 rng 消耗（攻击动画 playAttackAnimation 等）按原版保留
#        ——两侧模拟器须复刻（见 docs/rng_truth.md §1.4-4）。
# =============================================================================

const DT := 1.0 / 60.0
const MAX_TICKS := 5400          # 90s 游戏时间 = 5400 tick
const WALL_CAP_USEC := 240_000_000  # 单场墙钟上限（错误刷屏的最坏场兜底，防日志膨胀）
const HEAD_NOTE := "ORACLE-BATCH: 受控神谕批量重放（无头）| 不加载 Main.tscn | 不联网 | 不进排名/休闲/在线"

# autoload / 脚本引用（_initialize 里填；解析期不出现游戏全局类名——--script 主循环
# 脚本先于 autoload 解析，引用游戏类名会引爆 Game↔Item 脚本环，实测 cyclic-reference）
var G = null            # Game 节点
var U = null            # Util 节点
var IB = null           # ItemBook 节点
var BHData = null       # BuildHistoryData 脚本
var RDScript = null     # RunData 脚本（static deserializeItems）
var ItemScript = null   # Item 脚本（Owner 枚举）
var CT = null           # CombatTimer 节点（战斗时钟/疲劳链宿主）

var dummy = null                    # Game.buildHistory 只读假体（见类定义）
var out_root := ""                  # …/output/oracle/fights
var cases: Array = []
var runs: Dictionary = {}
var _in_battle := false             # tick 循环期间为真（node_added 过滤用）
var _in_warmup := false             # 暖场丢弃场期间为真（不落盘不计失败）
var batch_failures: Array = []      # [case_id + 原因]
var batch_rows: Array = []          # 每场一行摘要
var batch_meta := {}                # skipped_resume/blacklist/dropped_preflight（summary 如实汇报）
var _report: Array = []
var batch_t0 := 0


# 只读假体：替代未打开的 BuildHistory UI 单例（Game.finishSwitchingToCombat 与
# initHistoryOpponent 读 markedOpponentData/markedOpponentRound——正是原版
# 「历史记录里标记对手再开战」的入口，我们程序化写入同样的字段）
class DummyBuildHistory:
	var isOpen := false
	var markedOpponentData = null
	var markedOpponentRound := - 1


func say(line: String) -> void :
	print(line)
	_report.push_back(line)


func fail_case(case_id: String, msg: String) -> void :
	if _in_warmup:
		return
	batch_failures.push_back(case_id + ": " + msg)
	say("    [FAIL] " + case_id + " — " + msg)


# 红线自证：不满足任一条即拒绝开跑（release 版 assert 不生效，见 _initialize 注释）
func red_line_check() -> bool :
	var ok := true
	if ResourceLoader.has_cached("res://Core/Main.tscn"):
		push_error("[RED-LINE] Main.tscn 已进资源缓存——受控神谕不允许")
		say("[RED-LINE] Main.tscn 已进资源缓存——受控神谕不允许")
		ok = false
	var main = root.get_node_or_null("Main")
	if main == null or not ("fully_built" in main):
		push_error("[RED-LINE] 根下缺 oracle_bootstrap 程序化 Main 骨架（检查 project.godot autoload 的 Bootstrap 项）")
		say("[RED-LINE] 根下缺 oracle_bootstrap 程序化 Main 骨架（检查 project.godot autoload 的 Bootstrap 项）")
		ok = false
	return ok


func _initialize() -> void :
	say(HEAD_NOTE)
	# ★ 本二进制是 release 版，GDScript assert() 被编译剔除 → 红线自证必须用
	#   显式 fail-fast（写明原因并退出非零），不能依赖 assert。
	if not red_line_check():
		quit(1)
		return
	G = root.get_node("Game")
	U = root.get_node("Util")
	IB = root.get_node("ItemBook")
	BHData = load("res://Interface/BuildHistory/BuildHistoryData.gd")
	RDScript = load("res://Utility/RunData.gd")
	ItemScript = load("res://Items/Item.gd")
	CT = G.combatTimer   # Game.gd:245 onready → Main/Combat/UI/%CombatTimer（引导骨架内）
	dummy = DummyBuildHistory.new()
	# Timer 注册表维护：树增删即登记/注销（战斗中生成的动画/飘字计时器不漏驱动）
	connect("node_added", self, "_on_node_added")
	connect("node_removed", self, "_on_node_removed")
	connect("physics_frame", self, "_on_physics_frame")


func _on_physics_frame() -> void :
	if _report.size() > 1:
		return
	# 等引导阶段 2（CombatLog 补挂、ItemLibrary 就位）完成——见 oracle_bootstrap.gd
	var boot = root.get_node_or_null("Main")
	if boot == null or not boot.fully_built or G.PLAYER == null:
		return
	_report.push_back("start")   # 防重入闸门（后续帧直接返回）
	run_batch()


# ─────────────────────────── 批量主流程 ───────────────────────────

func run_batch() -> void :
	batch_t0 = OS.get_ticks_usec()
	say("[1] 读用例 res://fights.json")
	if not read_cases():
		finish_batch()
		return
	say("    用例 %d 场" % cases.size())

	# 可选定向（ORACLE_ONLY_CASES=id1,id2,…）：只跑指定用例（保 fights.json 顺序）。
	# 阶段1 试点用（docs/alignment_fix_workflow.md §2）：按物品数选
	# 中位/最大/最小各一先做逐行比对，修完再放全量。
	var only_ids := {}
	for only_id in OS.get_environment("ORACLE_ONLY_CASES").split(",", false):
		only_ids[only_id] = true
	if not only_ids.empty():
		var only_kept: Array = []
		for c in cases:
			if only_ids.has(String(c["case_id"])):
				only_kept.push_back(c)
		cases = only_kept
		say("    ★ 定向：ORACLE_ONLY_CASES → %d 场" % cases.size())

	say("[2] 读历史库（本地快照 → user:// 隔离副本，原版插件 + 原版 BuildHistoryData）")
	runs = load_history_runs()
	if runs.empty():
		finish_batch()
		return
	say("    共 %d 条 run" % runs.size())

	# 一次性引导必须先于预检：原版 RunData.deserializeStream 读
	# Game.PLAYER.INVENTORY.MAX_SIZE（位宽）与 Game.itemLibrary.getInstance
	#（持久化位宽），两者在此刻都还不存在 → 先建骨架引用并实例化 PLAYER。
	say("[3] 一次性引导（原版 startHistoryRun 的模式/单例前提）")
	G.setMode(G.Mode.History)                     # 原版 startHistoryRun 第一句
	G.itemLibrary = root.get_node("Main").G_itemLibrary   # [ORACLE 桩化记录 #8b]
	G.SELLBOX = root.get_node("Main").G_SELLBOX           # [ORACLE 桩化记录 #8]
	G.STORAGEBOX = root.get_node("Main").G_STORAGEBOX     # [ORACLE 桩化记录 #8]
	G.buildHistory = dummy                        # [ORACLE 桩化记录 #5] 只读假体
	G.state = G.State.Combat                      # 等价 onSceneAnimationFinished(ShopToCombat)
	if not cases.empty():
		var first_run = runs.get(int(cases[0]["run_id"]), null)
		if first_run != null:
			G.instanceCharacter(first_run.classI)   # 预检需要 PLAYER.INVENTORY 存在

	# 可选裁剪在 runs 载入后执行：分层需要 run 的职业字段
	var limit := int(OS.get_environment("ORACLE_FIGHT_LIMIT"))
	if limit > 0 and limit < cases.size():
		cases = stratified_sample(cases, limit)
		say("    ★ 裁剪：ORACLE_FIGHT_LIMIT=%d → 分层样本 %d 场（按玩家职业轮转，保序）"
				% [limit, cases.size()])

	# ★ [M11] 进程配额（ORACLE_FIGHT_CHUNK=N，0=不限）：跑满 N 场即优雅退出，
	#   由外层驱动重入续跑。原因：阻塞循环里 MessageQueue 只能在帧末 flush，
	#   call_deferred/queue_free/request_ready 消息跨场累积（实测 ~116 场 ≈ 6 万条
	#   后队列溢出内刷，陈旧目标逐条刷 "Object was deleted while awaiting a
	#   callback"，单场 532s/831MB）。配额退出 = 帧末一次干净的 flush，
	#   断点续跑语义不变（resume 幂等）。
	var chunk := int(OS.get_environment("ORACLE_FIGHT_CHUNK"))

	# 病例黑名单（ORACLE_SKIP_CASES，逗号分隔）：实测 run697_r15 为纯续航镜像
	# 对局（护身符袋/缝纫包等 53 件），战斗无法判胜且某些原生调用严重劣化
	# （每 tick 错误刷屏 + 墙钟远超兜底），跳过并在 summary 如实报告。
	var skip_list := {}
	for skip_id in OS.get_environment("ORACLE_SKIP_CASES").split(",", false):
		skip_list[skip_id] = true

	# 断点续跑（任务书约定 1，幂等、无条件生效）：output/oracle/fights/<case_id>/
	# events.json 已存在且事件非空（event_count>0）的用例直接跳过——支持超时/中断后
	# 原地继续。events.json 存在但事件为空（历史失败残迹）不跳过，自动重跑自愈。
	var kept2: Array = []
	var skipped := 0
	var blacklist := 0
	for c in cases:
		var cid := String(c["case_id"])
		# ★ lineups-only 模式：resume 判据 = lineups.json 已是 snapshot 2（宝石
		#   真值版）——events 完成与否与此无关；配合 ORACLE_FIGHT_CHUNK 分块
		#   续跑（lineups-only 旁路战斗循环，MessageQueue 只能靠配额退出 flush）。
		if _lineups_only:
			if lineups_snapshot_done(cid):
				skipped += 1
				continue
		elif case_events_done(cid):
			skipped += 1
			continue
		if skip_list.has(cid):
			blacklist += 1
			continue
		kept2.push_back(c)
	say("    [resume] 已完成跳过 %d 场 / 黑名单 %d 场，待跑 %d 场"
			% [skipped, blacklist, kept2.size()])
	batch_meta["skipped_resume"] = skipped
	batch_meta["blacklist"] = blacklist
	cases = kept2

	# 预检：用原版反序列化逐场试解码（镜像对手同 run 同回合 → 只测一次）。
	# 库内 run 版本横跨 1.1.4–1.1.9，旧版本条目的物品位宽/索引空间与当前
	# ItemBook 不一致 → 解码失败场剔除，数量与清单如实写进 summary（不伪装跑通）。
	var kept: Array = []
	var dropped: Array = []
	for c in cases:
		if case_decode_ok(int(c["run_id"]), int(c["round_id"])):
			kept.push_back(c)
		else:
			dropped.push_back(String(c["case_id"]))
	var total0 := kept.size() + dropped.size()
	say("    [预检] 可解码 %d / %d；剔除 %d 场（旧版本索引空间不符或回合缺失）"
			% [kept.size(), total0, dropped.size()])
	if not dropped.empty():
		say("    [预检] 剔除清单: " + str(dropped))
		var fh2 = File.new()
		fh2.open(out_root.plus_file("_preflight_dropped.txt"), File.WRITE)
		fh2.store_string(PoolStringArray(dropped).join("\n") + "\n")
		fh2.close()
	batch_meta["dropped_preflight"] = dropped.size()
	cases = kept

	# ★ 暖场：正式批量前先跑一场并丢弃全部产物。首场战斗带着进程冷启动残留
	#   （boot 期遗留的延迟调用、首次资源实例化、动画节点池空转等），与后续场次
	#   行为不同（实测：首场激活期创建 9 个 playAni 动画条目，第二场为 0）——
	#   会让「同种子复跑」与「场间逐位一致」失真。暖场后所有正式场都处于稳态。
	if not cases.empty():
		say("    [暖场] 丢弃场（不计入批量、不落盘）")
		var warm = run_case(cases[0], true)
		say("    [暖场] 完成（%s，%d ticks）" % [warm["status"], warm["ticks"]])

	var first_res = null
	var chunk_exit := false
	for i in range(cases.size()):
		var c: Dictionary = cases[i]
		var t0 = OS.get_ticks_usec()
		var res = run_case(c)
		var ms = (OS.get_ticks_usec() - t0) / 1000.0
		var row = "[%4d/%d] %-16s %-8s ticks=%4d t=%6.2fs events=%4d %6.0f ms" % [
			i + 1, cases.size(), c["case_id"], res["status"], res["ticks"],
			res["combat_time"], res["events"], ms]
		batch_rows.push_back(row)
		say("  " + row)
		# 防卡死心跳（任务书约定 1）：每 10 场向 stdout flush 一次进度。
		# release 版默认缓冲 stdout，project.godot 已设 run/flush_stdout_on_print=true
		# → print 即冲；另写 _progress.txt（File.close 即落盘）双保险，
		# 外部看门狗凭任一均可判断进程是否存活、断点续跑到哪。
		if (i + 1) % 10 == 0:
			var prog = "done=%d/%d" % [i + 1, cases.size()]
			print(prog)
			var pf = File.new()
			if pf.open(out_root.plus_file("_progress.txt"), File.WRITE) == OK:
				# ★ 3.6 的 API 是小驼峰 get_process_id（曾误写 get_process_ID →
				#   SCRIPT ERROR 中止 run_batch 本帧 → 主循环脱管空转刷屏，实测致命）
				pf.store_string("%s  (pid=%d elapsed=%.0fs)\n" % [prog, OS.get_process_id(),
						(OS.get_ticks_usec() - batch_t0) / 1000000.0])
				pf.close()
		if i == 0:
			first_res = res
			# ★ 确定性自证：紧邻复跑首场（同为暖态、逐场等价起点），事件 JSON
			#   逐字节比对。紧邻复跑验证「每场状态归一」；跨全场距离的复跑另在
			#   批量结束后追加一次并如实报告漂移（见 finish_batch 前的 drift 检查）。
			#   lineups-only 模式无战斗可复跑，旁路。
			if first_res["status"] == "ok" and not _lineups_only:
				determinism_check(cases[0], "adjacent")
		# [M11] 进程配额：本进程跑满即优雅退出，剩余用例交给下一次续跑
		if chunk > 0 and (i + 1) % chunk == 0 and i + 1 < cases.size():
			chunk_exit = true
			say("[chunk] 本进程配额 %d 场已满（done=%d/%d），优雅退出；重跑自动续接"
					% [chunk, i + 1, cases.size()])
			break

	# 确定性自证（远距）：批量尾再复跑首场，报告与首跑的漂移（若有）
	# [M11] 配额退出时跳过——case[0] 属于本进程首场，其紧邻复跑已覆盖；
	# 远距复跑的语义只在"全量单进程"下成立。
	if not chunk_exit and cases.size() > 1 and first_res != null and first_res["status"] == "ok" \
			and not _lineups_only:
		determinism_check(cases[0], "end-of-batch")

	finish_batch()


func read_cases() -> bool :
	var fh = File.new()
	if not fh.file_exists("res://fights.json"):
		batch_failures.push_back("缺 res://fights.json")
		return false
	fh.open("res://fights.json", File.READ)
	var parsed = parse_json(fh.get_as_text())
	fh.close()
	if typeof(parsed) != TYPE_DICTIONARY or not (parsed.get("cases", []) is Array):
		batch_failures.push_back("fights.json 格式错误")
		return false
	cases = parsed["cases"]
	out_root = ProjectSettings.globalize_path("res://..").plus_file("output/oracle/fights")
	# ★ ORACLE_FIGHTS_ROOT：诊断复跑的输出重定向（必须给绝对路径）。
	#   冻结语料 output/oracle/fights/ 只读——rng 探针/复跑诊断一律重定向到
	#   output/oracle/probe/ 下（ORACLE_ONLY_CASES 选场 + ORACLE_DEBUG 出
	#   rng_log.txt + ORACLE_STACKTRACE 附逐抽调用栈）；探针产物里的 events.json
	#   与冻结语料逐字节对照即得确定性自证。不设此变量=行为不变（写冻结语料目录，
	#   仅批量补跑场景使用）。
	var probe_root := OS.get_environment("ORACLE_FIGHTS_ROOT")
	if probe_root != "":
		out_root = ProjectSettings.globalize_path(probe_root)
	var d = Directory.new()
	if not d.dir_exists(out_root):
		d.make_dir_recursive(out_root)
	return true


# 分层采样：先按玩家 run 的职业分组（组内保 fights.json 顺序），再按组轮转取 N 场。
# 只依赖 runs 已载入的 classI，不引入任何随机。
func stratified_sample(all_cases: Array, limit: int) -> Array :
	var by_class := {}
	var order: Array = []
	for c in all_cases:
		var run = runs.get(int(c["run_id"]), null)
		var cls: int = run.classI if run != null else - 1
		if not by_class.has(cls):
			by_class[cls] = []
			order.push_back(cls)
		by_class[cls].push_back(c)
	var picked: Array = []
	while picked.size() < limit and not order.empty():
		for cls in order:
			if by_class[cls].empty():
				continue
			picked.push_back(by_class[cls].pop_front())
			if picked.size() >= limit:
				break
	return picked


# ★ lineups-only 批量的续跑判据：lineups.json 已是 snapshot 2（宝石真值版）
func lineups_snapshot_done(case_id: String) -> bool :
	var fh = File.new()
	var p = out_root.plus_file(case_id).plus_file("lineups.json")
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
	# r34：snapshot 3 = +crafted 物品效果真值（MagicRing 族 effects）。旧 2 仍算
	# 完成于战斗重放；lineups-only 批量（ORACLE_LINEUPS_ONLY）只在 >=3 时跳过，
	# 旧 2 会重导。战斗重放路径不判 3（effects 不影响重放本身——重放从史重建）。
	if _lineups_only:
		return int(parsed.get("snapshot", 0)) >= 3
	return int(parsed.get("snapshot", 0)) >= 2


# 断点续跑判据（任务书约定 1）：events.json 已存在且事件非空（event_count>0）
# ★ 阶段1 追加：还要求 rng_state.txt 已导出——老批量（无 state 导出）的场次
#   视为未完成，自动重跑补导出（events 因逐场确定性应逐字节不变）。
func case_events_done(case_id: String) -> bool :
	var p = out_root.plus_file(case_id).plus_file("events.json")
	var fh = File.new()
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
	if int(parsed.get("event_count", 0)) <= 0:
		return false
	return fh.file_exists(out_root.plus_file(case_id).plus_file("rng_state.txt"))


# 预检：该 (run, round) 用原版 BuildHistoryData.getRoundData +
# RunData.deserializeItems 能否零失真解码（镜像对手同数据，测一次即够）
func case_decode_ok(run_id: int, round_id: int) -> bool :
	var run = runs.get(run_id, null)
	if run == null:
		return false
	var rnd = run.getRoundData(round_id)
	if rnd == null:
		return false
	var ver: String = run.getVersionString()
	var deser = RDScript.deserializeItems(rnd.items, ver)
	if deser == null:
		say("    [预检-调试] run %d r%d ver=%s 书目条目=%d buildInfo len=%d" %
				[run_id, round_id, ver, IB.getNumItems(), rnd.items.length()])
	return deser != null


# 读历史库 → 原版 BuildHistoryData 表（复刻 BuildHistoryDB.readRunHistory 的查询与
# 装配；反序列化本身全部走原版类，见 run_case）
func load_history_runs() -> Dictionary :
	# 1) 拷贝快照到隔离 user://（绝不打开原快照，保持只读）
	var src = ProjectSettings.globalize_path("res://data/history.db")
	var dst = ProjectSettings.globalize_path("user://oracle_history.db")
	var dir = Directory.new()
	if dir.file_exists(dst):
		dir.remove(dst)
	var cp_err = dir.copy(src, dst)
	if cp_err != OK:
		batch_failures.push_back("history.db 拷贝失败 err=" + str(cp_err))
		return {}

	# 2) 原版 godot-sqlite 插件打开
	var SQLite = load("res://addons/godot-sqlite/bin/gdsqlite.gdns")
	var db = SQLite.new()
	db.verbosity_level = 0
	db.path = dst
	db.open_db()
	if db.error_message != "":
		batch_failures.push_back("sqlite 打开失败: " + db.error_message)
		return {}

	var out = {}
	db.query("select * from runData;")
	for row in db.query_result:
		var bh = BHData.new()
		bh.version = row["version"]
		bh.time = row["time"]
		bh.customRules = row["custom"]
		bh.classI = row["class"]
		bh.loadout = row["loadout"]
		bh.id = row["runID"]
		bh.subclassIndex = row["subclass"]
		bh.skill1Index = row["skill1"]
		bh.skill2Index = row["skill2"]
		var rank = row["rank"]
		if rank == - 1:
			bh.mode = G.Mode.Unranked
		elif rank == - 2:
			bh.mode = G.Mode.Lobbies
		else:
			bh.mode = G.Mode.Ranked
			bh.rating = rank
		out[bh.id] = bh

	db.query("select * from roundData;")
	for row in db.query_result:
		var run = out.get(row["runID"], null)
		if run == null:
			continue
		var valid = true
		for entry in row:
			if row[entry] == null:
				valid = false
				break
		if not valid:
			continue
		# 原版 BuildHistoryData.addRoundData
		run.addRoundData(row["roundID"], row["result"], row["tries"],
				row["health"], row["stamina"], row["buildInfo"])
	db.close_db()
	return out


# ─────────────────────────── 单场 ───────────────────────────

func run_case(c: Dictionary, warmup := false) -> Dictionary :
	var case_id: String = c["case_id"]
	var seed_value: int = int(c["seed"])
	var run_id: int = int(c["run_id"])
	var round_id: int = int(c["round_id"])
	# 对手缺省镜像：同 run 同回合（fights.json 的 opponent_rule）
	var opp_run_id: int = int(c["opp_run_id"]) if c.has("opp_run_id") else run_id
	var opp_round_id: int = int(c["opp_round_id"]) if c.has("opp_round_id") else round_id
	var dir = out_root.plus_file(case_id)
	var res = {"status": "FAIL", "ticks": 0, "combat_time": 0.0, "events": 0,
			"winner": "-", "seed": seed_value, "run_id": run_id,
			"round_id": round_id, "opp_run_id": opp_run_id,
			"opp_round_id": opp_round_id, "dir": dir}
	if not warmup:
		var d = Directory.new()
		if not d.dir_exists(dir):
			d.make_dir_recursive(dir)
	_in_warmup = warmup   # 暖场期间：不落盘、不计失败（见各 dump/fail 函数）

	if not runs.has(run_id) or not runs.has(opp_run_id):
		fail_case(case_id, "run 不在历史库中: %d / %d" % [run_id, opp_run_id])
		write_case_result(res, ["run 缺失"])
		return res

	# ── 玩家角色复用（原版 startHistoryRun 的 instanceCharacter）──────────
	# ★ 放在播种之前：instanceCharacter 只在「职业切换」分支消耗 rng 两次
	#   （Game.gd:2271-2275 的入场 tween），该消耗若落在播种后会随「上一场的
	#   职业」漂移，破坏跨场确定性；放在播种前则被本场 seed() 完全重置，
	#   两侧模拟器也无需复刻它。PLAYER 的物品实例在播种后才创建（约定 2b）。
	var player_run = runs[run_id]
	G.curHistoryData = player_run
	G.curRound = round_id
	G.wins = player_run.getWins(round_id - 1)
	G.losses = player_run.getLosses(round_id - 1)
	G.tries = G.MAX_TRIES if round_id == 1 else player_run.getTries(round_id - 1)
	# ★ 确定性：清空对象池与预实例化缓存。池内容取决于进程启动以来的帧历史
	#   （ItemBook._process 每帧池化若干物品场景；ObjectPool.returnInstance 战斗
	#   中回填动画实例）——不可复现，且 ObjectPool.instance 对「池内节点
	#   （request_ready 重跑 _ready）」与「新建节点」的行为不同（实测激活期
	#   playAni 动画条目 9 个 vs 0 个）。清空后每场全部走空池「新建实例」分支，
	#   与冷启动逐位等价，跨场、跨进程确定性成立。
	#   ★ [M9] 池内节点是游离孤儿（不在树上，无帧回收）：直接丢引用等于泄漏
	#     （实测一场 61s 战斗退出时拆 ~15 万节点）。逐个 free 后再清字典。
	var pool = root.get_node("ObjectPool")
	for key in pool.instances.keys():
		for inst in pool.instances[key]:
			if is_instance_valid(inst) and not inst.is_inside_tree():
				inst.free()
	pool.instances.clear()
	IB.preparedItemInstances.clear()
	IB.prepareQueue.clear()
	G.instanceCharacter(player_run.classI)
	G.get_node("/root/CustomRules").fromString(player_run.customRules)

	# ── ★ 确定性种子：任何物品实例创建之前（约定 2b）────────────────────
	U.rng.seed = seed_value
	seed(seed_value)   # 引擎全局链（Array.shuffle/pick_random 消费，原版同源）
	U.oracleRngTrace = _dbg_delayed
	U.oracleRngStack = OS.get_environment("ORACLE_STACKTRACE") != ""
	U.oracleRngLog = []

	var p_round = player_run.getRoundData(round_id)
	if p_round == null:
		fail_case(case_id, "run %d 无第 %d 回合" % [run_id, round_id])
		write_case_result(res, ["玩家回合缺失"])
		return res
	var p_deser = RDScript.deserializeItems(p_round.items, player_run.getVersionString())
	if p_deser == null:
		fail_case(case_id, "run %d 回合 %d 反序列化失败" % [run_id, round_id])
		write_case_result(res, ["玩家反序列化失败"])
		return res
	var p_tuples = p_deser["items"]
	G.PLAYER.INVENTORY.createFromItemTuples(p_tuples, ItemScript.Owner.PlayerInventory)
	G.PLAYER.setMaxHealth(p_round.health)
	G.PLAYER.setMaxStamina(p_round.stamina)
	G.initRoundResults()

	# ── 对手实例化（原版 finishSwitchingToCombat @ Game.gd:2581-2588）──────
	G.OPPONENT = G.opponentScene.instance()
	G.OPPONENT.playerId = G.OPPONENT.ID.OPPONENT
	G.PLAYER.setOpponent(G.OPPONENT)
	G.OPPONENT.setOpponent(G.PLAYER)
	G.OPPONENT.connect("character_died", G, "endCombat")   # 原版判胜链
	G.OPPONENT.position = Vector2(1920 - G.playerCombatPos, 880)
	G.opponentNode.add_child(G.OPPONENT)

	# ── 对手装配：走原版 initHistoryOpponent 逐行（标记对手路径）──────────
	var opp_run = runs[opp_run_id]
	dummy.markedOpponentData = opp_run
	dummy.markedOpponentRound = opp_round_id
	if G.initHistoryOpponent() == - 1:
		fail_case(case_id, "对手装配失败（initHistoryOpponent == -1，sus run）")
		teardown_case()
		write_case_result(res, ["对手装配失败"])
		return res
	G.curOpponentData = {"class": opp_run.classI}

	# ── 开战（原版 finishSwitchingToCombat 尾段 @ Game.gd:2671-2694）──────
	_reset_combat_log()                       # 事件数组清零（批量内每场独立）
	G.fightEnded = false
	G.numTimesOutOfStamina = 0
	# 原版 @2681-2682：emit shop_closed / switching_to_combat——前者挂着
	# CombatLog.onPrepare（Core/CombatLog.gd:86），负责给双方每件物品建统计
	# 条目（statLogger.prepareItem）；不发它，战斗期 logItemStat 全部字典未命中
	# → 原版物品代码在 snapshotItemTooltipStat 处中断，行为被破坏。
	G.emit_signal("shop_closed")
	G.emit_signal("switching_to_combat")
	CT.combatTime = 0.0                       # [M4] 等价 onCombatSceneEntered 的 combatTime=0
	CT.initialize()
	# 原版：物品序列 duplicate → shuffle（全局链）→ sort_TriggerPriority
	var playerItems = G.PLAYER.INVENTORY.getItems().duplicate()
	playerItems.shuffle()
	playerItems.sort_custom(G.ItemSort, "sort_TriggerPriority")
	var opponentItems = G.OPPONENT.INVENTORY.getItems().duplicate()
	opponentItems.shuffle()
	opponentItems.sort_custom(G.ItemSort, "sort_TriggerPriority")
	# ── ★ ORACLE_LINEUPS_ONLY：装配完成即导 lineups 并收场 ──────────────────
	#   宝石快照补全专用（2026-10-08）：不写 rng_state、不 prepare/activate、
	#   不进 tick 循环、不 dump events——除 lineups.json 外不触碰任何语料文件。
	if _lineups_only:
		dump_lineups(dir, res)
		teardown_case()
		res["status"] = "ok"
		return res
	# ── ★ 阶段1 rng state 导出（docs/alignment_fix_workflow.md §2 阶段1）──────
	# 战斗装配（双方角色 + 全部物品实例）完成后、开战序列（prepareItems 的
	# BalancedRng 重置 + onPrepare 钩子、activateItems 的 preCombatStart/
	# combatStart/postCombatStart 钩子）与首次 tick 之前：把 Util.rng 的
	# (seed, state) 双 u64 落盘。模拟器侧用 set_state 语义（docs/rng_truth.md
	# §2.3：直写 PCG state 字，不前进不重播，下一次 rand() 从该值前进）从该
	# state 起跑开战序列 + 逐 tick 判定链——绕开装配期消耗差异，隔离战斗期。
	# 关键机制：此刻双方 BalancedRng 尚未重置、其 expectedWins 依赖装配期各自
	# 的链位；但两侧都在 prepareItems 里同点重置（原版 Item.gd:3345-3351
	# chanceRng/damageRangeRng.reset + Character.gd:294-317 四个角色 rng.reset；
	# 内核 gd_core/CoreItem.gd:531-535 / CoreCharacter.gd:259-265 同序同点），
	# 重置后 Per-object 平衡器状态归零，链 state 即唯一决定后续每次掷点。
	if not warmup:
		var rsf = File.new()
		rsf.open(dir.plus_file("rng_state.txt"), File.WRITE)
		rsf.store_string("seed=%d\nstate=%d\n" % [U.rng.get_seed(), U.rng.state])
		rsf.close()

	G.prepareItems(playerItems + opponentItems)
	# [M4] 原版 call_deferred(prepareItems) + callDelayed(activateItems, 2.5s)：
	# 延迟期间无 rng 消耗、无事件，顺序调用逐 tick 等价
	G.activateItems(playerItems + opponentItems)

	# 装配后阵容 dump（保留装配顺序）
	dump_lineups(dir, res)

	# ── ★ 手动 tick 循环（约定 2c）────────────────────────────────────
	rebuild_timer_registry()
	_in_battle = true
	var case_t0 := OS.get_ticks_usec()
	var ticks := 0
	var lockup := false
	var stop_reason := "tick 上限 %d" % MAX_TICKS
	_cur_tick_states = []
	while not G.fightEnded and ticks < MAX_TICKS:
		var tick_t0 := OS.get_ticks_usec()
		tick_battle(DT, ticks + 1)
		ticks += 1
		_cur_tick_states.push_back(U.rng.get_state())
		# ★ ORACLE_TRACE_ITEM：<物品名>——逐 tick dump 该物品 triggerTime/speed
		#   （F7 1-tick 漂移定位；harness 侧，零 rng 消耗）
		var _ti := OS.get_environment("ORACLE_TRACE_ITEM")
		if _ti != "":
			for _side in [["P", G.PLAYER.INVENTORY], ["O", G.OPPONENT.INVENTORY]]:
				for _it in _side[1].getItems():
					if _it.getName() == _ti:
						_f7_trace.append("%s %d %.9f %.9f %.9f %d %.9f" % [_side[0], ticks + 1, _it.triggerTime, _it.getSpeed(), _it.iterationCooldown, int(_it.is_physics_processing()), CT.combatTime])

		# ★ [M10] 长战斗中途清扫瞬态节点宿主（每 60 tick = 1 游戏秒）：
		#   2.7 万事件级战斗里 Labels（伤害飘字）/ItemAnimations（激活动画）
		#   子节点线性累积（原版由帧内 returnAfter 归还池，阻塞循环下归还定时器
		#   多数到点前战斗已结束），每个 addChild 都在变大节点上登记 → tick 成本
		#   随事件量爬升 → 触墙钟闸截断（实测 run1124/1125_r18 55s 游戏时即止）。
		#   归还池（有 poolingHandle）或直接释放——纯视觉节点，事件流/rng 零交互。
		if ticks % 60 == 0:
			var opool = root.get_node("ObjectPool")
			for sp in ["Main/UI/Labels", "Main/Combat/ItemAnimations"]:
				var sn = root.get_node_or_null(sp)
				if sn != null and sn.get_child_count() > 400:
					for stray in sn.get_children():
						if is_instance_valid(stray):
							if "poolingHandle" in stray:
								opool.returnInstance(stray)
							else:
								stray.free()
		# ★ 防卡死三闸（每 tick 检查；健康 tick ≈ 1-2ms，下面的阈值碰不到）：
		#   a) 单 tick 墙钟 > 5s → 该 tick 内有失控循环/错误风暴，标记 lockup 立即止损
		#   b) 单场墙钟 > 60s → 提前判停（原版无此上限，纯兜底防日志膨胀）。
		#      ★ 实测定 60s 的原因：2.7 万事件级战斗每事件排队数十条 Control 布局
		#      消息（_update_callback/_update_minimum_size），约 90 万条/32MB 就把
		#      MessageQueue 填满 → 引擎内刷溢出 dump（3.5GB stdout + 逐条陈旧目标
		#      报错，实测单场 9 分钟 I/O）。60s 墙钟在绝大多数溢出前止损；
		#      被截断的战斗照常 dump 已产生的事件（status=timeout，如实记录）。
		#   c) 事件数 > 25000 → 同理判停（消息量与事件数同阶增长的双保险）
		var t_now = OS.get_ticks_usec()
		if t_now - tick_t0 > 5_000_000:
			lockup = true
			say("    [lockup] tick %d 单 tick 墙钟 %.1fs——tick 内失控循环，止损判停"
					% [ticks, (t_now - tick_t0) / 1000000.0])
			break
		if t_now - case_t0 > 60_000_000:
			stop_reason = "墙钟闸 60s"
			say("    [watchdog] 墙钟超 60s，提前判停（原版无此上限，纯兜底防消息队列溢出 dump）")
			break
		if G.combatLog.events.size() > 25000:
			stop_reason = "事件闸 25000"
			say("    [watchdog] 事件数超 25000，提前判停（防消息队列溢出 dump，纯兜底）")
			break
	_in_battle = false
	# ★ 逐 tick 链状态落盘（ORACLE_DEBUG 时）：与内核 OracleAlignBattle 的
	#   tick_states.txt 同构（每物理 tick 结束时的 Util.rng.state），供跨引擎
	#   「首个分叉 tick」定位——事件级 diff 只能给事件粒度，tick 级直指漏抽/
	#   多抽的那一帧。
	if _dbg_delayed and not _in_warmup:
		var tf = File.new()
		tf.open(dir.plus_file("tick_states.txt"), File.WRITE)
		var trows := []
		for s in _cur_tick_states:
			trows.append(String(s))
		tf.store_string(PoolStringArray(trows).join("\n") + "\n")
		tf.close()

	# ★ ORACLE_TRACE_ITEM 曲线一次落盘（F7 定位仪）
	if OS.get_environment("ORACLE_TRACE_ITEM") != "" and _f7_trace.size() > 0:
		var _f7f = File.new()
		_f7f.open(dir.plus_file("item_trace.txt"), File.WRITE)
		_f7f.store_string(PoolStringArray(_f7_trace).join("|") + "|")
		_f7f.close()
	# 相邻复跑分歧定位：第一处分叉的 tick
	if not _prev_tick_states.empty() and _dbg_ticks:
		var n = min(_prev_tick_states.size(), _cur_tick_states.size())
		for k in range(n):
			if _prev_tick_states[k] != _cur_tick_states[k]:
				say("    [tick-diverge] first at tick %d (prev=%s cur=%s)" %
						[k + 1, _prev_tick_states[k], _cur_tick_states[k]])
				break
	_prev_tick_states = _cur_tick_states

	res["ticks"] = ticks
	res["combat_time"] = CT.combatTime

	# 原版 endCombat 里 call_deferred("combatEndDeferred")——阻塞循环无帧，手动补
	if G.fightEnded:
		G.combatEndDeferred()
		var result = G.getLastRoundResult()
		res["winner"] = ("player" if result == G.RoundResult.Win
				else "opponent" if result == G.RoundResult.Loss else "draw")
	else:
		res["status"] = "lockup" if lockup else "timeout"
		fail_case(case_id, ("单 tick 失控（lockup，止损于 tick %d）" % ticks) if lockup
				else "未判胜即止损（%s，于 tick %d / %.0fs 游戏时间）"
					% [stop_reason, ticks, CT.combatTime])

	var events = G.combatLog.events
	res["events"] = events.size()
	dump_events(events, dir, res)
	if events.empty():
		res["status"] = "no-events"
		fail_case(case_id, "events.json 为空——事件流没有产生，视为未跑通")
	elif res["status"] != "timeout" and res["status"] != "lockup":
		res["status"] = "ok"

	var hp_line = "player_hp=%.0f/%d opponent_hp=%.0f/%d fatigue=%d" % [
		G.PLAYER.getCurrentHealth(), G.PLAYER.maxHealth,
		G.OPPONENT.getCurrentHealth(), G.OPPONENT.maxHealth, CT.fatigueCounter]
	write_case_result(res, [hp_line])

	if _dbg_delayed and not _in_warmup:
		var lg = File.new()
		lg.open(dir.plus_file("rng_log.txt"), File.WRITE)
		var rows := []
		for e in U.oracleRngLog:
			# 第 7 列 = 调用栈（ORACLE_STACKTRACE=1 时存在）
			if e.size() > 6:
				rows.append("%d %s %s %s => %s @t=%.3f | %s" % [e[0], e[1], e[2], e[3], e[4], e[5], e[6]])
			else:
				rows.append("%d %s %s %s => %s @t=%.3f" % [e[0], e[1], e[2], e[3], e[4], e[5]])
		lg.store_string(PoolStringArray(rows).join("\n") + "\n")
		lg.close()
	U.oracleRngTrace = false
	# ── 场间清场（等价原版 freeOpponent/returnToShop，阻塞循环下立即释放）──
	teardown_case()
	return res


func tick_battle(dt: float, n := 0) -> void :
	# ① Util 全局时钟（等价 Util.gd:145-157；_process 的 clockTime 一并推进；
	#    鼠标跟踪与暂停判定不需要——神谕全程不暂停）
	U.clockTime += dt
	U.time += dt
	U.frameCounter += 1
	var s0 = U.rng.get_state() if _dbg_ticks else 0
	# ②③ 对手角色 + 其物品（场景树次序：Main/Combat/Opponent 先于 Main/Player）
	var opp = G.OPPONENT
	if opp.is_physics_processing():
		opp._physics_process(dt)
	for item in opp.INVENTORY.getItems():
		if item.is_physics_processing():
			var sa = U.rng.get_state() if (n == _trace_tick) else 0
			item._physics_process(dt)
			if n == _trace_tick and U.rng.get_state() != sa:
				print("[eat] t=%.3f OPP item %s" % [U.time, item.getName()])
	# ④ CombatTimer（combatTime += dt，事件时间戳源）
	if CT.is_physics_processing():
		CT._physics_process(dt)
	# ⑤ 玩家角色 + 其物品
	var p = G.PLAYER
	if p.is_physics_processing():
		p._physics_process(dt)
	for item in p.INVENTORY.getItems():
		if item.is_physics_processing():
			var sa = U.rng.get_state() if (n == _trace_tick) else 0
			item._physics_process(dt)
			if n == _trace_tick and U.rng.get_state() != sa:
				print("[eat] t=%.3f PLR item %s" % [U.time, item.getName()])
	# ⑥⑦ Timer 节点（先物理型后空闲型——引擎两个 pass 的先后次序）
	var s_items = U.rng.get_state() if _dbg_ticks else 0
	drive_timers(true, dt)
	drive_timers(false, dt)
	# ⑧ SceneTreeTimer（Util.callDelayed 注册表；判胜即冻结）
	var s_timers = U.rng.get_state() if _dbg_ticks else 0
	drive_delayed(dt)
	if _dbg_ticks:
		var s1 = U.rng.get_state()
		if s1 != s0:
			print("[rng-eat] t=%.3f itemphase=%s timerphase=%s delayedphase=%s"
					% [U.time, str(s_items != s0), str(s_timers != s_items),
					str(s1 != s_timers)])


# Timer 节点驱动：引擎侧 get_time_left() 在阻塞循环里冻结，故注册表自记剩余；
# 引擎读数变化 = 外部 start()/stop()（同步信号处理里发生）→ 下一 tick 重同步。
# 到点次序复刻原版 Timer::_process：one_shot 先自停再派发 timeout；循环计时器
# 若处理器未重启则按 wait_time 续接（Godot 3.6 Timer::start(t) 会 set_wait_time(t)
# 并写 time_left → 处理器重启与否以 emit 后引擎读数/停走状态判定，阻塞循环下
# 引擎读数只被 start()/stop() 改写，判定是精确的——唯一歧义「start(与旧值同秒)」
# 通过先 stop() 归零消解：restart 的 start() 总会把 time_left 从 0 改成新值）。
func drive_timers(physics_pass: bool, dt: float) -> void :
	var reg: Dictionary = U.oracleTimerLefts
	for timer in reg.keys():
		var e: Array = reg[timer]
		if not is_instance_valid(timer) or not timer.is_inside_tree():
			reg.erase(timer)
			continue
		if _dbg_ticks and U.time >= 41.3 and U.time <= 41.9 \
				and String(timer.get_path()).find("/Character/@") >= 0:
			print("[timer-tick] pass=%s t=%.4f %s e0=%.4f eng=%.4f stopped=%s" % [str(physics_pass), U.time, timer.get_path(), e[0], timer.get_time_left(), str(timer.is_stopped())])
		if timer.is_stopped():
			e[0] = - 1.0
			continue
		if (timer.process_mode == Timer.TIMER_PROCESS_PHYSICS) != physics_pass:
			continue
		var eng = timer.get_time_left()
		if eng != e[1]:
			if _dbg_ticks and String(timer.get_path()).find("/Character/") >= 0:
				print("[bt-resync] t=%.4f %s eng=%.4f old_e0=%.4f old_e1=%.4f" % [U.time, timer.get_path(), eng, e[0], e[1]])
			e[0] = eng            # 外部 start()/changeTimer() → 重同步
		else:
			e[0] = e[0] - dt
		e[1] = eng
		if e[0] > 0.0:
			continue
		# 到点：复刻引擎 one_shot 自停 → 派发 → 循环计时器兜底续接
		if _dbg_ticks:
			if String(timer.get_path()).find("BuffTimer") >= 0 or String(timer.get_path()).find("Invulnerability") >= 0:
				print("[timer-fire-dbg] t=%.4f %s e0=%.6f eng=%.6f" % [U.time, timer.get_path(), e[0], timer.get_time_left()])
			print("[timer-fire] t=%.3f %s" % [U.time, timer.get_path()])
		timer.stop()
		timer.emit_signal("timeout")
		if not is_instance_valid(timer):
			reg.erase(timer)
			continue
		if not timer.is_stopped():
			e[0] = timer.get_time_left()   # 处理器重启了（start(x) → time_left=x）
			e[1] = e[0]
		elif not timer.is_one_shot():
			var w = timer.get_wait_time()  # 循环计时器：引擎语义 time_left = wait_time
			timer.start(w)
			e[0] = w
			e[1] = w
		else:
			e[0] = - 1.0


# SceneTreeTimer（Util.callDelayed/setDelayed 注册表）驱动；判胜后不再补发 [M4]
var _dbg_delayed := OS.get_environment("ORACLE_DEBUG") != ""
var _dbg_ticks := OS.get_environment("ORACLE_DEBUG") != ""
var _trace_tick := int(OS.get_environment("ORACLE_TRACE_TICK"))
# ★ ORACLE_LINEUPS_ONLY=1：只装配 + 导 lineups.json（宝石快照补全用），不重跑
#   战斗——events.json / rng_state.txt / rng_log.txt / result.txt 一概不碰，语料
#   events 保持冻结。resume 判定与 determinism 复跑在本模式下旁路。
var _lineups_only := OS.get_environment("ORACLE_LINEUPS_ONLY") != ""
var _prev_tick_states: Array = []   # 上一场逐 tick 的链状态（相邻复跑分歧定位）
var _cur_tick_states: Array = []
var _f7_trace := []

func drive_delayed(dt: float) -> void :
	var keep: Array = []
	for e in U.oracleDelayedTimers:
		e[1] -= dt
		if e[1] > 0.0:
			keep.push_back(e)
			continue
		if G.fightEnded:
			continue
		if _dbg_delayed:
			print("[cd-fire] t=%.3f created=%.3f %s" % [U.time, e[2], str(e[3])])
		if is_instance_valid(e[0]):
			e[0].emit_signal("timeout")
	U.oracleDelayedTimers = keep


# 战斗启动前重建 Timer 注册表（覆盖装配期创建的 Buff/物品计时器）
func rebuild_timer_registry() -> void :
	U.oracleTimerLefts.clear()
	# ★ 确定性归一 [M6]：Character 的 Mirroring/Sprite/AnimationSpeedTimer 是
	#   待机动画随机化器（randAnimationSpeed：每 2-5s 消耗 2 次链抽取）。
	#   对手场景每场新建（autostart → 开局 1s 必发）；PLAYER 的则跨场存活、
	#   冻结在上一场某次 start(2..5) 的读数上——同一战斗在第 2 场与第 N 场的
	#   发火时刻不同，链位置随之漂移（实测伤害掷点分叉的根源）。
	#   神谕约定：该纯视觉计时器在战斗中一律停用（两侧模拟器同约定）。
	for c in [G.PLAYER, G.OPPONENT]:
		if c != null and is_instance_valid(c):
			var t = c.get("idleAniSpeedTimer")
			if t != null and is_instance_valid(t):
				t.stop()
	_collect_timers(root.get_node("Main"))


func _collect_timers(node) -> void :
	for child in node.get_children():
		if child is Timer:
			var left = child.get_time_left()
			U.oracleTimerLefts[child] = [left, left]
			# ★ 临时诊断（ORACLE_RNG_DEBUG=1）：登记次序 dump（驱动次序=字典插入序）
			if OS.get_environment("ORACLE_RNG_DEBUG") != "":
				print("[timer-reg] physics=%s left=%.3f %s"
						% [str(child.process_mode == Timer.TIMER_PROCESS_PHYSICS), left, child.get_path()])
		_collect_timers(child)


func _on_node_added(node) -> void :
	if _in_battle and node is Timer:
		var left = node.get_time_left()
		U.oracleTimerLefts[node] = [left, left]


func _on_node_removed(node) -> void :
	if node is Timer:
		U.oracleTimerLefts.erase(node)


# 场间清场：等价原版 freeOpponent（Game.gd:3555-3562）+ CombatToShop 过场的
# cleanse（见下），queue_free 改 free（阻塞循环无帧）
func teardown_case() -> void :
	# 原版每场战斗结束后经 CombatToShop 过场调 Character.cleanse
	#（Core/Character.gd:255-257 call_deferred("cleanse")）：清零临时血/增益、
	# isDead、体力再生并回满。批量循环没有过场 → 手动补，否则 PLAYER 把
	# temporaryMaxHealthGain 等状态带进下一场，破坏跨场确定性。
	if is_instance_valid(G.PLAYER):
		G.PLAYER.cleanse()
	if G.OPPONENT != null:
		G.OPPONENT.INVENTORY.deleteItems()
		var opp_inv = G.OPPONENT.INVENTORY
		G.OPPONENT.free()
		opp_inv.free()
		G.OPPONENT = null
		IB.opponentItems.clear()
	if G.curOpponentData != null:
		G.curOpponentData.clear()
	# ★ [M9] 每场收尾清扫两类瞬态节点宿主（原版由 returnAfter/池化在帧内回收，
	#   阻塞循环下 drive_delayed 已回收大部分；判胜后丢弃的挂起项由这里兜底）：
	#   ItemAnimations（物品激活动画）与 Labels（伤害飘字）。两者每场从零开始。
	for spawn_path in ["Main/Combat/ItemAnimations", "Main/UI/Labels"]:
		var spawner = root.get_node_or_null(spawn_path)
		if spawner != null:
			for stray in spawner.get_children():
				if is_instance_valid(stray):
					stray.free()
	U.oracleTimerLefts.clear()
	U.oracleDelayedTimers.clear()
	_flush_queued(root)


# 阻塞循环没有帧消化 queue_free 队列 → 逐树立即释放（原版由帧尾等价完成）
func _flush_queued(node) -> void :
	if node == root:
		for child in root.get_children():
			_flush_queued(child)
		return
	var children = node.get_children()
	for child in children:
		if is_instance_valid(child):
			_flush_queued(child)
	if is_instance_valid(node) and node.is_queued_for_deletion():
		node.free()


# 逐字段等价原版 CombatLog.clear()（Core/CombatLog.gd:135-166）的战斗数据面，
# 跳过 UI 件（滚动容器/伤害图表/日志行节点池）——神谕骨架里它们是无脚本占位
# 节点，且批量场景无需其视觉状态；战斗数据（事件/统计/时间戳）全部等价清零。
# ★ [M8] 追加 clear() 的节点归还半段（:141-146 close/activeLine/container 子节点
#   逐个 ObjectPool.returnInstance）：神谕走 delayedLogList 快路径时容器应恒空，
#   此归还段是防泄漏保险（阻塞循环下节点无帧可回收，漏一个就跨场累积——
#   实测一场 61s/15405 事件的战斗在退出时拆了 ~15 万节点）。
#   不直接调原版 clear()：它在 scrollEnabled 行会被 3.6 属性名差异
#   （scroll_enabled）打断、其后半段全部跳过（反编译名 vs 3.6 API 的既有分歧）。
func _reset_combat_log() -> void :
	var clog = G.combatLog
	clog.close()
	clog.hideArrow()
	clog.activeLine = null
	clog.events.clear()
	clog.eventNum = - 1
	clog.delayedLogList.clear()
	clog.delayListDone = 0
	clog.timestamps.clear()
	clog.logLines.clear()
	for line in clog.container.get_children():
		clog.container.remove_child(line)
		root.get_node("ObjectPool").returnInstance(line)
	clog.activeItemState.clear()
	clog.activeCharacterStats = [[], []]
	clog.eventsLogged = 0
	for i in 2:
		clog.statLoggers[i].clear()


# ─────────────────────────── 确定性自证 ───────────────────────────

func determinism_check(c: Dictionary, tag: String) -> void :
	say("[5] 确定性自证（%s）：首场同种子复跑" % tag)
	var dir = out_root.plus_file(String(c["case_id"]))
	var first = File.new()
	var first_path = dir.plus_file("events.json")
	if not first.file_exists(first_path):
		say("    跳过（首场 events.json 不存在）")
		return
	first.open(first_path, File.READ)
	var first_text = first.get_as_text()
	first.close()
	# 首跑抽取日志留档（与 events_first.json 同理）
	var rl = File.new()
	if rl.file_exists(dir.plus_file("rng_log.txt")):
		rl.open(dir.plus_file("rng_log.txt"), File.READ)
		var rtxt = rl.get_as_text()
		rl.close()
		var rc = File.new()
		rc.open(dir.plus_file("rng_log_first.txt"), File.WRITE)
		rc.store_string(rtxt)
		rc.close()
	# 逐 tick 链状态对比：定位复跑与首跑的第一处分叉 tick
	var states_before: Array = _cur_tick_states
	var rerun = run_case(c)
	# ★ [dbg] 复跑若在 run_case 内被脚本错误打断会返回 null——就地大声化，
	#   防止"确定性自证静默消失"（2026-10-06 实测：复跑段仅 29KB 即止，判定行缺失）
	if rerun == null:
		say("    [dbg] rerun run_case 返回 null——run_case 内部脚本错误中止（见上方最后一个 SCRIPT ERROR）")
	if _dbg_ticks:
		var n2 = min(states_before.size(), _cur_tick_states.size())
		for k in range(n2):
			if states_before[k] != _cur_tick_states[k]:
				say("    [tick-diverge] 首个分叉 tick = %d（用 ORACLE_TRACE_TICK=%d 复跑可定位消费点）"
						% [k + 1, k + 1])
				break
	var second = File.new()
	second.open(dir.plus_file("events.json"), File.READ)
	var second_text = second.get_as_text()
	second.close()
	# 首跑文本留档，便于人工 diff 定位分歧点
	var keep = File.new()
	keep.open(dir.plus_file("events_first.json"), File.WRITE)
	keep.store_string(first_text)
	keep.close()
	if rerun["status"] == "ok" and second_text == first_text:
		say("    同种子复跑事件流逐字节一致 ✓（%s，%s）" % [c["case_id"], tag])
	else:
		# 远距复跑的漂移如实记录（不作为批量失败——紧邻复跑才是归一性判据）
		if tag == "end-of-batch":
			say("    [漂移] 远距复跑与首跑存在差异（详见上方紧邻复跑结论；" +
					"跨全场距离的状态漂移如实报告）")
			return
		batch_failures.push_back("%s: 同种子复跑不一致（%s）" % [c["case_id"], tag])
		say("    [FAIL] 同种子复跑不一致！（首跑留档 events_first.json 供 diff）")
		var a = JSON.parse(first_text).result
		var b = JSON.parse(second_text).result
		if a != null and b != null:
			var ae: Array = a["events"]
			var be: Array = b["events"]
			say("    首跑事件 " + str(ae.size()) + " @t=" + str(a["combat_time"])
					+ " / 复跑事件 " + str(be.size()) + " @t=" + str(b["combat_time"]))
			for k in range(min(ae.size(), be.size())):
				if str(ae[k]) != str(be[k]):
					say("    首个分歧事件 #" + str(k) + ": " + str(ae[k]).substr(0, 260))
					say("    复跑同序事件 #" + str(k) + ": " + str(be[k]).substr(0, 260))
					break
			if ae.size() != be.size():
				say("    事件数不同：" + str(ae.size()) + " vs " + str(be.size()))
	# 复跑的落盘覆盖了首场结果——语义无差（同种子同结果），result.txt 重写一致


func finish_batch() -> void :
	var secs = (OS.get_ticks_usec() - batch_t0) / 1000000.0
	say("")
	say("[6] 批量结束：用时 %.1fs" % secs)
	for r in batch_rows:
		say("  " + r)
	say("")
	var ok := batch_failures.empty()
	if ok:
		say("ORACLE-BATCH: PASS（本进程实跑 %d 场全部 events.json 非空；resume 跳过 %d / 黑名单 %d / 预检剔除 %d——累计核验见 _batch_summary.txt）"
				% [cases.size(), int(batch_meta.get("skipped_resume", 0)),
				int(batch_meta.get("blacklist", 0)), int(batch_meta.get("dropped_preflight", 0))])
	else:
		say("ORACLE-BATCH: FAIL（%d 项）" % batch_failures.size())
		for f in batch_failures:
			say("  - " + f)
	write_summary(secs, ok)
	say("")
	# 红线自证收尾：全程未加载主场景（release 版 assert 无效 → 显式检查）
	if ResourceLoader.has_cached("res://Core/Main.tscn"):
		say("[RED-LINE] 收尾自证失败：Main.tscn 进了资源缓存！")
		ok = false
	quit(0 if ok else 1)


func write_summary(secs: float, ok: bool) -> void :
	var fh = File.new()
	fh.open(out_root.plus_file("_batch_summary.txt"), File.WRITE)
	var lines := [
		"受控神谕批量结果", "status=%s" % ("PASS" if ok else "FAIL"),
		"cases=%d" % cases.size(), "failures=%d" % batch_failures.size(),
		"wall_seconds=%.1f" % secs,
		"resume_skipped=%d" % int(batch_meta.get("skipped_resume", 0)),
		"blacklist=%d" % int(batch_meta.get("blacklist", 0)),
		"dropped_preflight=%d" % int(batch_meta.get("dropped_preflight", 0)),
		"godot_script=oracle/oracle_fight.gd (1.1.8 反编译全量工程，批量手动 tick)",
		"", "── 每场摘要 ──",
	]
	lines.append_array(batch_rows)
	if not batch_failures.empty():
		lines.push_back("")
		lines.push_back("── 失败清单 ──")
		for f in batch_failures:
			lines.push_back("  - " + f)
	lines.push_back("")
	lines.push_back("── 桩化/偏离记录（每场 result.txt 同步携带） ──")
	lines.append_array(harness_notes())
	fh.store_string(PoolStringArray(lines).join("\n") + "\n")
	fh.close()


func harness_notes() -> Array :
	return [
		"- [桩] SilentWolf/RunDatabase/CrazySDK/Steam autoload 空实现（oracle_stubs/，禁网，见各文件头）",
		"- [桩] Main.tscn 不加载；根下 Main 为 oracle_bootstrap.gd 程序化战斗骨架（含 [M3] 疲劳链连接）",
		"- [桩] Game.buildHistory 只读假体（isOpen=false；markedOpponent* 程序化写入）",
		"- [桩] Game.SELLBOX/STORAGEBOX/ItemLibrary 最小桩/原版件（oracle_bootstrap.gd #8/#8b）",
		"- [M1] Util.callDelayed/setDelayed 系追加 SceneTreeTimer 登记（oracle_fight 驱动）",
		"- [M2] Util.changeTimer/CombatTimer.advanceTime/Buff 读计时器剩余时以注册表为准（Util.oracleTimeLeft）",
		"- [M4] 开战 UI 过场压缩为顺序调用；combatTime 事件戳从 0 起（gd_core 同约定）",
		"- [M6] 战斗中停用 Character 待机动画随机化计时器（AnimationSpeedTimer，纯视觉；跨场链漂移根源）",
		"- [M6b] 每场装配前清空 ObjectPool.instances 与 ItemBook 预实例化缓存（池内容随启动帧数变化，不可复现）",
		"- [M6c] 每场收尾补 Character.cleanse（等价原版 CombatToShop 过场），防临时状态跨场泄漏",
		"- [M7] 暖场一场丢弃（不计批量不落盘），冲洗进程冷启动一次性状态；确定性自证=紧邻复跑+批尾复跑逐字节比对",
		"- [M8] _reset_combat_log 补齐原版 clear() 的节点归还半段（close/activeLine/日志行容器→ObjectPool）；不直接调 clear()，其 scrollEnabled 行因 3.6 属性名差异会打断后半段",
		"- [M9] 防泄漏三件套：池孤儿逐个 free（原仅丢引用）、场末清扫 ItemAnimations/Labels 瞬态节点、[M2] 基础上每 tick 墙钟/单 tick 尖峰双闸（5s/120s）止损失控场",
		"- [M10] 长战斗每 60 tick 清扫 Labels/ItemAnimations（>400 子节点归还池/释放）——纯视觉节点，防 2.7 万事件级战斗 tick 成本爬升触墙钟闸",
		"- [M11] 进程配额 ORACLE_FIGHT_CHUNK（外层驱动续跑）：阻塞循环下 MessageQueue 只能帧末 flush，跨场累积至溢出会逐条刷陈旧目标错误；配额退出=干净 flush，resume 幂等续接",
		"- [M12] 兜底三闸（每 tick 检查）：单 tick 墙钟>5s(lockup)/单场墙钟>60s/事件数>25000——2.7 万事件级战斗每事件排队数十条 Control 布局消息，约 90 万条触发 MessageQueue 溢出 dump（3.5GB）；被截断的战斗照常 dump 已产生事件，status 如实标 timeout",
		"- [M5] UI/音频照常调用但入虚空；其 Util.rng 消耗按原版保留（docs/rng_truth.md §1.4-4）",
		"- 隔离：config/name=BackpackBattlesOracle；history.db 用本地快照副本（原快照只读）",
	]


# ─────────────────────────── dump ───────────────────────────

func _jsonable(o):
	return _jsonable_impl(o, 0)


func _jsonable_impl(o, depth: int):
	if o == null:
		return null
	if o is bool or o is int or o is float or o is String:
		return o
	if o is Vector2:
		return {"kind": "vec2", "x": o.x, "y": o.y}
	if o is Dictionary:
		if depth > 6:
			return "…"
		var d = {}
		for k in o:
			d[String(k)] = _jsonable_impl(o[k], depth + 1)
		return d
	if o is Array:
		if depth > 6:
			return "…"
		var a = []
		for v in o:
			a.push_back(_jsonable_impl(v, depth + 1))
		return a
	# 宝石：socket 身份折叠在宿主上（对齐 gd_core_test HookProbe._ekey 的判据）
	var sock = o.get("socket")
	if sock != null:
		var sid := - 1
		var gs = sock.get("gems")
		if gs != null:
			for i in range(gs.size()):
				if gs[i] == o:
					sid = i
					break
		return {"kind": "gem", "host": _jsonable_impl(sock, depth + 1),
				"socket_index": sid}
	# GDScript 的 `is` 不接受脚本变量，改用鸭子判据：物品必有 getTopLeftCell 与
	# descriptor；角色（Character）没有 descriptor。
	if o.has_method("getTopLeftCell") and "descriptor" in o:
		var tl = o.getTopLeftCell()
		return {"kind": "item", "name": String(o.getName()),
				"identifier": String(o.descriptor.identifier),
				"owner_type": int(o.ownerType), "top_left": {"x": tl.x, "y": tl.y}}
	if "playerId" in o:
		return {"kind": "character", "player_id": int(o.playerId)}
	if o.has_method("getName"):
		return {"kind": "object", "name": String(o.getName())}
	# ★ 3.6 没有 String(Object) 构造（原写法每跑必炸），str() 才合法；对象里若
	#   带实例 ID 会让同种子复跑的逐字节比对失真，此处只留类名字串。
	return {"kind": "unknown", "str": str(o).split(":")[0].substr(0, 80)}


func dump_events(events: Array, dir: String, res: Dictionary) -> void :
	if _in_warmup:
		return
	var out = []
	for event in events:
		var parent_id = - 1
		if event.parentEvent != null:
			parent_id = event.parentEvent.id
		var type_name = String(event.getType())
		if G.EventType.has(event.getType()):
			type_name = U.enumToString(G.EventType, event.getType())
		out.push_back({
			"id": event.id,
			"type": event.getType(),
			"type_name": type_name,
			"timestamp": event.timestamp,
			"origin": _jsonable(event.getOrigin()),
			"target": _jsonable(event.target),
			"parent_id": parent_id,
			"params": _jsonable(event.params),
		})
	var path = dir.plus_file("events.json")
	var fh = File.new()
	fh.open(path, File.WRITE)
	fh.store_string(JSON.print({
		"seed": res["seed"], "run_id": res["run_id"], "round_id": res["round_id"],
		"opp_run_id": res["opp_run_id"], "opp_round_id": res["opp_round_id"],
		"combat_time": res["combat_time"], "ticks": res["ticks"],
		"winner": res["winner"],
		"event_count": out.size(), "events": out}, "  "))
	fh.close()


func dump_lineups(dir: String, res: Dictionary) -> void :
	if _in_warmup:
		return
	var p = snapshot_side(G.PLAYER)
	var o = snapshot_side(G.OPPONENT)
	var path = dir.plus_file("lineups.json")
	var fh = File.new()
	fh.open(path, File.WRITE)
	fh.store_string(JSON.print({
		"seed": res["seed"], "run_id": res["run_id"], "round_id": res["round_id"],
		"opp_run_id": res["opp_run_id"], "opp_round_id": res["opp_round_id"],
		"phase": "assembled",
		# ★ 快照版次：2 = 宝石真值（Item.getGems()，identifier 身份）。旧导出无
		#   此字段（gems 恒空）——lineups-only 批量的 resume 判据用。
		#   3 = +crafted 物品效果真值（r34，MagicRing 族 effects 数组）。
		"snapshot": 3,
		"assembly_order_note": "items 数组即装配（实例创建）顺序：buildInfo 反序列化流顺序经原版 sort_BagOrder 后的顺序，两侧模拟器按此顺序重建",
		"player": p, "opponent": o}, "  "))
	fh.close()


func _item_snapshot(item) -> Dictionary :
	var tl = item.getTopLeftCell()
	var gems = []
	# ★ 宝石真值：原版宝石存在 sockets 子节点里（Item.gd:3013-3019 getGems =
	#   [socket.getGem() for socket in sockets]），Item **没有** `gems` 成员——
	#   旧实现 `item.get("gems")` 恒 null → lineups.json 的 gems 恒空，夹具装配
	#   的宝石面整个丢失（2026-10-08 发现）。改走 getGems()，宝石身份用
	#   descriptor.identifier（与 battle_items.json 键一致，getName 是显示名）。
	for g in item.getGems():
		gems.push_back(null if g == null else String(g.descriptor.identifier))
	# ★ r34 crafted 效果真值（snapshot 3）：MagicRing 族实例的 effects 数组
	#   （RingEffect{triggerType,stackType}）。重放从史重建——wasJustCrafted 走
	#   合成路径不 roll；模拟器侧没有史，必须按此真值直接注入效果，否则
	#   现场重 roll 消耗链位且效果与史不符（run635 戒指缺 Every → 少一次
	#   adjustCooldown → DK 热量翻转链移位 → C05/C06/C23A 全族）。
	var effects = []
	if item.get("effects") != null:
		for eff in item.get("effects"):
			if eff != null:
				effects.push_back({
					"triggerType": int(eff.triggerType),
					"stackType": int(eff.stackType),
				})
	# ★ r35 crafted 真值（snapshot 4）：descriptor.isCraftedItem()——
	#   originatingRecipes 非空（配方图在 ItemBook 注册，类型级属性）。
	#   gd_core 的配方图从未导出（CoreItemData 已知缺口注释）→ isCraftedItem
	#   恒假 → Cog.gd giveBlock(block×numAffected) 计数差（run683 14v7）。
	return {
		"name": String(item.getName()),
		"identifier": String(item.descriptor.identifier),
		"owner_type": int(item.ownerType),
		"top_left": {"x": tl.x, "y": tl.y},
		"face_direction": int(item.faceDirection),
		"gems": gems,
		"effects": effects,
		"crafted": bool(item.descriptor.isCraftedItem()),
	}


func snapshot_side(chr) -> Dictionary :
	var items = []
	for it in chr.INVENTORY.getItems():
		items.push_back(_item_snapshot(it))
	return {
		"class": int(chr.characterClass),
		"class_name": U.enumToString(G.Classes_Full, chr.characterClass),
		"max_health": chr.maxHealth,
		"current_health": chr.getCurrentHealth(),
		"base_max_stamina": chr.baseMaxStamina,
		"max_stamina": chr.maxStamina,
		"items": items,
	}


func write_case_result(res: Dictionary, extra_lines: Array) -> void :
	if _in_warmup:
		return
	var lines := [
		"受控神谕单场结果",
		"status=%s" % res["status"],
		"case_id=%s" % String(res["dir"]).get_file(),
		"seed=%d" % res["seed"],
		"run_id=%d round_id=%d" % [res["run_id"], res["round_id"]],
		"opp_run_id=%d opp_round_id=%d" % [res["opp_run_id"], res["opp_round_id"]],
		"winner=%s" % res["winner"],
		"combat_time=%.2f" % res["combat_time"],
		"ticks=%d (dt=1/60, 上限 %d)" % [res["ticks"], MAX_TICKS],
		"event_count=%d" % res["events"],
		"godot_script=oracle/oracle_fight.gd (1.1.8 反编译全量工程)",
		"version=%s%s" % [G.VERSION, G.SUBVERSION],
	]
	lines.append_array(extra_lines)
	lines.push_back("modifications=")
	lines.append_array(harness_notes())
	var fh = File.new()
	fh.open(String(res["dir"]).plus_file("result.txt"), File.WRITE)
	fh.store_string(PoolStringArray(lines).join("\n") + "\n")
	fh.close()
