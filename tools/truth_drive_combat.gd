extends SceneTree

func dump_event(e) -> String:
    var d = {}
    for p in e.get_property_list():
        var n = p.name
        if n.begins_with("_") or n in ["script", "RefCounted", "Built-in script"]:
            continue
        d[n] = str(e.get(n))
    return to_json(d)

func sort_prio(a, b):
    return a.call("getTriggerPriority") > b.call("getTriggerPriority")

func place(game, side, spec: Array):
    var inv = game.get(side).get("INVENTORY")
    inv.call("reset")  # 等价 instanceCharacter 里的清库（正确处理袋与格子）
    var ib = get_root().get_node_or_null("ItemBook")
    for entry in spec:
        var inst = ib.call("instantiateItem", entry[0])
        if inst == null:
            print("PLACE FAIL: ", entry[0]); continue
        game.get(side).add_child(inst)  # 必须先入树：_ready 初始化 gems/damageSource 等
        inst.name = entry[0] + "_" + side  # 防重名（@后缀会撞字典键）
        inv.call("addItemByTopLeft", inst, Vector2(entry[2], entry[1]))

func _init():
    var main = load("res://Core/Main.tscn").instance()
    get_root().add_child(main)
    var game = get_root().get_node_or_null("Game")
    for i in range(8):
        yield(self, "idle_frame")
    game.call("truth_late_init")
    game.initPlayer()
    game.call("startFreshRun", 0)
    for i in range(300):
        yield(self, "idle_frame")
    var util = get_root().get_node_or_null("Util")
    util.get("rng").seed = 777
    seed(777)
    # ── 手工组装战斗（等价 finishSwitchingToCombat 的战斗核心，跳过存档/网络/对手匹配）──
    var opp = load("res://Core/Opponent.tscn").instance()
    opp.set("playerId", opp.get("ID").OPPONENT)
    game.get("PLAYER").call("setOpponent", opp)
    opp.call("setOpponent", game.get("PLAYER"))
    opp.connect("character_died", game, "endCombat")
    opp.position = Vector2(1920 - game.get("playerCombatPos"), 880)
    game.get("opponentNode").add_child(opp)
    game.set("OPPONENT", opp)
    opp.call("setClass", game.get("curClass"), game.call("getEffectiveChibiMode"))
    opp.set("curHealth", opp.get("maxHealth"))  # initOpponent 的 deserialize 会带回血量；手工路径须显式补
    var spec = [["Wooden Sword", 0, 0], ["Lucky Clover", 0, 2], ["Pan", 0, 4]]
    place(game, "PLAYER", spec)
    place(game, "OPPONENT", spec)
    game.set("fightEnded", false)
    game.get("combatTimer").call("initialize")
    game.get("PLAYER").call("shopToCombat")
    var pi = game.get("PLAYER").get("INVENTORY").call("getItems").duplicate()
    pi.shuffle(); pi.sort_custom(self, "sort_prio")
    var oi = opp.get("INVENTORY").call("getItems").duplicate()
    oi.shuffle(); oi.sort_custom(self, "sort_prio")
    var all = pi + oi
    print("CB9: p=", pi.size(), " o=", oi.size())
    # 内联 prepare/activate 序列（等价 prepareItems/activateItems）
    game.get("PLAYER").call("prepare")
    opp.call("prepare")
    for it in all:
        it.call("prepare")
    print("CB9: prepared  opp_hp=", opp.get("curHealth"), "/", opp.get("maxHealth"), " p_hp=", game.get("PLAYER").get("curHealth"), "/", game.get("PLAYER").get("maxHealth"))
    for i in range(150):   # COMBAT_DELAY 2.5s
        yield(self, "idle_frame")
    game.get("combatTimer").call("start")
    game.get("PLAYER").call("combatStart")
    opp.call("combatStart")
    for it in all:
        it.call("preCombatStart")
    for it in all:
        it.call("combatStart")
    for it in all:
        it.call("postCombatStart")
    print("CB9: activated  opp_hp=", opp.get("curHealth"), "/", opp.get("maxHealth"))
    var clog = game.get("combatLog")
    var seen = 0
    var lines = []
    var to_meta = []
    for e in spec:
        to_meta.append({"name": e[0], "row": e[1], "col": e[2], "rotation": 0, "gems": []})
    var meta = {"schema_version": 1, "fight_seed": 777, "round": game.get("curRound"),
                "character": "Ranger", "p_items": to_meta, "o_items": to_meta}
    lines.append(to_json(meta))
    for i in range(4000):
        yield(self, "idle_frame")
        if clog:
            var evs = clog.get("events")
            while seen < evs.size():
                lines.append(dump_event(evs[seen]))
                seen += 1
        if game.get("fightEnded"):
            break
    var pl = game.get("PLAYER"); var op2 = game.get("OPPONENT")
    lines.append(to_json({"_result": {"p_hp": pl.get("curHealth"), "o_hp": op2.get("curHealth"),
                                      "fight_ended": game.get("fightEnded")}}))
    var f = File.new()
    f.open("user://truth_fight.jsonl", File.WRITE)
    for l in lines:
        f.store_line(l)
    f.close()
    print("CB9: ended=", game.get("fightEnded"), " events=", lines.size() - 2,
          " p_hp=", pl.get("curHealth"), " o_hp=", op2.get("curHealth"))
    quit(0)
