extends Node
# =============================================================================
# oracle_bootstrap.gd — 受控神谕引导（受控神谕工作流 Phase 2）
# =============================================================================
# 作用：让 Core/Game.gd 的 onready 链 `root.get_node("Main")` 及其后继全部命中，
# 原版 Game._ready 才能完整跑起来（classResources、fatigueDamageSource、
# combatLog、combatTimer 等战斗必需状态都在 _ready 里装配）。
#
# ★ 实现方式：本引导 autoload 把**自己改名成 "Main"**，战斗路径引用的最小骨架
# 作为自己的子节点程序化搭建。不能另建节点挂到根下——autoload 批量入树期间
# root 正在 "busy setting up children"，add_child(root) 会被拒绝（实测）。
#
# ★ 装配纪律：先以**游离状态**把子树拼完整，最后才 add_child 进树——
#   _ready 只在首次入树时触发，若先把父节点入树再补子节点，父节点脚本的
#   onready（$ 子节点引用）会全部落空（实测 CombatTimer/CombatLog 均踩过）。
#   带场景唯一名（%）的节点必须先设 owner 再开 unique_name_in_owner。
#
# 两阶段装配（兄弟 autoload 的 _ready 按树序触发，Game 排在本引导之后）：
#   阶段 1（本 _ready）：搭全部空骨架 —— Game 的 onready 链只要求节点存在。
#   阶段 2（call_deferred，待所有 autoload 就绪后再补挂带脚本的 CombatLog）：
#     Core/CombatLog.gd 的 onready 引用 Game.combatSceneNode（Game._ready 之后
#     才有效），故它的 _ready 必须晚于 Game._ready。阶段 2 完成后置
#     fully_built = true，oracle_fight.gd 以此为开跑闸门。
#
# 红线断言（神谕的合法性由以下不变式保证）：
#   1. 本脚本绝不 load()/instance() res://Core/Main.tscn —— 那是主游戏场景，
#      含商店/标题界面/排名与休闲入口。这里的 "Main" 是纯程序化骨架，
#      每个节点都在 build_skeleton() 里有注释说明"谁引用它"。
#   2. 排名/休闲/在线入口在神谕内不存在：SilentWolf/RunDatabase/CrazySDK/
#      Steam 已在 project.godot 里替换为 oracle_stubs/ 下的空实现（见桩文件
#      头部的桩化记录）。骨架中没有任何可交互 UI、没有开战流程、没有网络节点。
#   3. 带脚本的节点仅限战斗必需：CombatTimer（疲劳判负链）、CombatLog
#      （事件日志）、Sellbox/Storagebox/ItemLibrary（物品装配路径引用的原版
#      单例宿主，见 build_combat_log 内桩化记录）。
# =============================================================================

var fully_built := false
var G_itemLibrary = null
var G_SELLBOX = null
var G_STORAGEBOX = null
var G_combatLog = null


func _ready() -> void :
	# 红线自证：主游戏场景此刻不应已被加载进资源缓存
	assert(not ResourceLoader.has_cached("res://Core/Main.tscn"))

	# 让 root.get_node("Main") 命中本引导节点（见文件头说明）
	name = "Main"
	build_skeleton(self)

	# 阶段 2：所有 autoload _ready 完毕后（deferred 队列在首帧处理）补挂
	# CombatLog / Sellbox / Storagebox / ItemLibrary
	call_deferred("build_combat_log")
	print("[ORACLE] 程序化 Main 骨架已搭好（未加载 Main.tscn）")


# 游离创建：不入树、不设 owner
func _n(klass, name_of, script_path = null):
	var n = klass.new()
	n.name = name_of
	if script_path != null:
		n.set_script(load(script_path))
	return n


func _add_anim(anim_player: AnimationPlayer, anim_name: String) -> void :
	anim_player.add_animation(anim_name, Animation.new())


func build_skeleton(main) -> void :
	# ── Game.gd onready 逐条对应（全部先游离拼装、最后入树）────────────────

	# Combat 子树：Game.combatSceneNode / opponentNode / combatUINode /
	#              combatAnimationsNode；CombatTimer（原版脚本，疲劳判负链）
	var ct = _n(Node2D, "CombatTimer", "res://Interface/CombatTimer/CombatTimer.gd")
	var fst = _n(Timer, "FatigueStartTimer")
	fst.one_shot = true                                 # 原版 start(FATIGUE_TIME-3) 只响一次
	ct.add_child(fst)
	ct.add_child(_n(Label, "Time"))                     # timeLabel
	ct.add_child(_n(Label, "Speed"))                    # speedLabel
	ct.add_child(_n(HSlider, "SpeedSlider"))            # speedSlider
	ct.add_child(_n(Button, "PauseButton"))             # pauseButton
	ct.add_child(_n(Button, "FastButton"))              # fastButton
	ct.add_child(_n(AnimationPlayer, "AnimationPlayer")) # animation
	var ftt = _n(Timer, "FatigueTickTimer")             # fatigueTickTimer
	ftt.one_shot = true                                 # 原版 Main.tscn:9910（dealFatigueDamage 里 start(1) 续）
	# 疲劳链连接：等价原版 Main.tscn:14984-14985 的 [connection]
	#   FatigueStartTimer.timeout → CombatTimer.startFatigue
	#   FatigueTickTimer.timeout  → CombatTimer.dealFatigueDamage
	# （此前缺失 → 90s 后永不疲劳，战斗永不了结）
	fst.connect("timeout", ct, "startFatigue")
	ftt.connect("timeout", ct, "dealFatigueDamage")
	ct.add_child(ftt)

	var fatigue = _n(Node2D, "Fatigue")
	fatigue.add_child(_n(AnimationPlayer, "AnimationPlayer"))  # CombatTimer.fatigueAnimation
	fatigue.add_child(_n(Label, "Counter"))                    # fatigueLabel

	var cui = _n(Node, "UI")                            # combatUINode
	cui.add_child(ct)                                   # %CombatTimer
	cui.add_child(fatigue)
	cui.add_child(_n(Control, "CombatLogButtonHint"))   # %CombatLogButtonHint
	var logtut = _n(AnimationPlayer, "CombatLogTutorialAnimation")
	_add_anim(logtut, "Tutorial")                       # CombatLog.tutorialAni 防播错
	cui.add_child(logtut)

	var combat = _n(Node2D, "Combat")                   # Game.combatSceneNode
	combat.add_child(_n(Node2D, "Opponent"))            # opponentNode：对手角色/物品挂载点
	combat.add_child(cui)
	combat.add_child(_n(Node2D, "ItemAnimations"))      # combatAnimationsNode：物品动画挂载点

	# Shop 子树：Game.shopSceneNode 及其后继（商店逻辑不存在，纯占位）
	var shop = _n(Node2D, "Shop")
	shop.add_child(_n(Node2D, "Items"))                 # shopItemYSort
	shop.add_child(_n(Node2D, "GoldPos"))               # goldPos
	shop.add_child(_n(Node2D, "SpeechBubble"))          # speechBubble
	var scb = _n(Button, "StartCombatButton")
	scb.add_child(_n(AnimationPlayer, "AnimationPlayer"))  # startCombatButtonAni
	shop.add_child(scb)
	shop.add_child(_n(Node2D, "ShopKeeper"))            # shopKeeper
	var reroll = _n(Node2D, "Reroll")
	reroll.add_child(_n(Node2D, "RerollRope"))          # rerollRope
	var ilt = _n(AnimationPlayer, "ItemLibraryTutorial")
	_add_anim(ilt, "Tutorial")                          # %ItemLibraryTutorial
	shop.add_child(ilt)

	# UI 子树：Game.UINode / labelsNode / tooltipsNode / recipeTooltipsNode /
	#          connectingLabel / undoStack；CombatLog 在阶段 2 补挂
	var ui = _n(Control, "UI")
	ui.add_child(_n(Node2D, "Labels"))                  # labelsNode：伤害/增益飘字挂载点
	ui.add_child(_n(Control, "Tooltips"))               # tooltipsNode（战斗中不悬停，仅占位）
	ui.add_child(_n(Control, "RecipeTooltips"))         # recipeTooltipsNode
	var conn = _n(Control, "ConnectingLabel")           # connectingLabel
	conn.visible = false
	ui.add_child(conn)
	ui.add_child(_n(Control, "UndoStack"))              # undoStack
	var logwrap = _n(Control, "CombatLog")              # Game.combatLog 的父占位
	logwrap.visible = true                              # CombatLog._ready 首行 get_parent().show()
	ui.add_child(logwrap)

	# CombatLog：原版 Core/CombatLog.gd。游离拼好整棵子树再入树。
	var clog = _n(Control, "CombatLog", "res://Core/CombatLog.gd")
	clog.visible = false                                # 不显示日志 → logEvent 走 delayedLogList
	var scroll = _n(ScrollContainer, "ScrollContainer")
	scroll.add_child(_n(VBoxContainer, "VBoxContainer"))  # container
	clog.add_child(scroll)
	clog.add_child(_n(Control, "LineArrow"))            # lineArrow
	clog.add_child(_n(Control, "HoverHint"))            # hoverHint
	clog.add_child(_n(Control, "DragHint"))             # dragHint
	# [ORACLE 桩化记录 #9] 伤害仪表原版是 DamageMeter.gd 重量级 UI；占位 Control
	# 会让 CombatLog 战斗路径每次调用都 SCRIPT ERROR 中止并刷屏（见桩文件头）。
	# 换成等签名空实现桩：控制流与原版一致（调用成功返回），零战斗状态。
	clog.add_child(_n(Control, "PlayerDamageMeter", "res://oracle_stubs/DamageMeterStub.gd"))    # playerDmgMeter
	clog.add_child(_n(Control, "OpponentDamageMeter", "res://oracle_stubs/DamageMeterStub.gd"))  # opponentDmgMeter
	clog.add_child(_n(Button, "PlayerButton"))          # playerButton
	clog.add_child(_n(Button, "OpponentButton"))        # opponentButton
	var filter = _n(Control, "FilterPanel", "res://oracle_stubs/DamageMeterStub.gd")  # filterPanel [桩化记录 #9：drag_start/drag_end 信号]
	filter.add_child(_n(LineEdit, "Searchbar"))         # searchBar（search_text_changed 信号）
	clog.add_child(filter)
	clog.add_child(_n(Control, "AboveLog"))             # tooltipNode
	var st = _n(Timer, "ScrollTimer")                   # scrollTimer
	st.one_shot = true
	clog.add_child(st)
	clog.add_child(_n(Button, "CloseButton"))           # closeButton
	var btut = _n(AnimationPlayer, "TutorialAni")       # buttonTutorialAni
	_add_anim(btut, "Tutorial")
	clog.add_child(btut)
	# ★ clog 保持游离，阶段 2 才挂进 logwrap：它的 onready 引用
	#   Game.combatSceneNode，必须晚于 Game._ready（见 build_combat_log）。
	G_combatLog = clog

	# 组装入树（此刻起各脚本 _ready 才触发，子节点已齐）
	main.add_child(_n(Node, "SplashscreenAnimation"))   # splashScreenAnimation
	main.add_child(_n(Node, "SceneAnimation"))          # sceneAnimation（UI 过场，神谕不播）
	main.add_child(combat)
	main.add_child(shop)
	main.add_child(ui)
	main.add_child(_n(Node2D, "Player"))                # playerNode：玩家角色/物品挂载点
	main.add_child(_n(Node, "PlayerNodeAnimation"))     # playerNodeAnimation
	main.add_child(_n(Node, "TitleScreen"))             # titleScreen（空占位，无入口逻辑）

	# 场景唯一名注册：先设 owner 再开 unique_name_in_owner
	for n in [ct, cui.get_node("CombatLogButtonHint"), logtut, ilt]:
		n.owner = main
		n.unique_name_in_owner = true
	# 其余骨架节点也登记 owner（owner 只要求是树内祖先）
	for node in main.get_children():
		set_owner_recursive(node, main)


func set_owner_recursive(node, owner) -> void :
	node.owner = owner
	for c in node.get_children():
		set_owner_recursive(c, owner)


func build_combat_log() -> void :
	# 阶段 1 组装好的 CombatLog 子树此刻才入树（它的 onready 引用
	# Game.combatSceneNode，必须晚于 Game._ready，见 build_skeleton 注释）
	get_node("UI/CombatLog").add_child(G_combatLog)
	# Game.combatLog 的 onready 在启动时求值（当时本节点尚未入树 → null），
	# 入树后补挂到 Game 上（等价于原版 onready 的最终结果）
	get_node("/root/Game").combatLog = G_combatLog

	# [ORACLE 桩化记录 #8] Game.SELLBOX / Game.STORAGEBOX 原版由 Main.tscn 内联的
	# Sellbox/Storagebox 节点 _ready 挂到 Game 上（无独立 tscn）；物品装配与统计
	# 路径引用它们。神谕挂最小桩（见 oracle_stubs/ 对应文件）。
	var sellbox = _n(Area2D, "Sellbox", "res://oracle_stubs/SellboxStub.gd")
	get_node("Shop").add_child(sellbox)
	G_SELLBOX = sellbox
	var storagebox = _n(Node2D, "Storagebox", "res://oracle_stubs/StorageboxStub.gd")
	get_node("Shop").add_child(storagebox)
	G_STORAGEBOX = storagebox

	# [ORACLE 桩化记录 #8b] Game.itemLibrary 原版由商店 UI 的 ItemLibraryButton
	# _ready 创建；RunData.deserializeStream 需要 itemLibrary.getInstance(descriptor)
	# 判定物品持久化位宽。神谕按原版方式创建（ItemLibrary.init 会自行挪到
	# Game.UINode 下并在下一帧移除，仅借它的 items 字典）。
	var lib = load("res://Interface/ItemLibrary/ItemLibrary.tscn").instance()
	G_itemLibrary = lib
	lib.init()

	fully_built = true
	print("[ORACLE] CombatLog/Sellbox/Storagebox/ItemLibrary 已补挂，神谕骨架就绪")
