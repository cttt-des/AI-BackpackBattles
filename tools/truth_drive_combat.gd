extends SceneTree

func dump_event(e) -> String:
    var d = {}
    for p in e.get_property_list():
        var n = p.name
        if n.begins_with("_") or n in ["script", "RefCounted", "Built-in script"]:
            continue
        d[n] = str(e.get(n))
    return to_json(d)

func place(game, side, items: Array):
    var inv = game.get(side).get("INVENTORY")
    for it in inv.call("getItems"):
        inv.call("removeItem", it)
        it.queue_free()
    var ib = get_root().get_node_or_null("ItemBook")
    var pos = 0
    for name in items:
        var inst = ib.call("instantiateItem", name)
        if inst == null:
            print("PLACE FAIL: ", name)
            continue
        var ok = inv.call("tryAddItem", inst)
        if not ok:
            print("PLACE FULL at: ", name)
            break
        pos += 1

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
    game.call("finishSwitchingToCombat")
    for i in range(5):
        yield(self, "idle_frame")
    # COMBAT_DELAY(2.5s≈150帧) 之前注入固定阵容
    place(game, "PLAYER", ["Wooden Sword", "Lucky Clover", "Wooden Sword"])
    place(game, "OPPONENT", ["Wooden Sword", "Lucky Clover", "Wooden Sword"])
    print("CB6: placed. p=", game.get("PLAYER").get("INVENTORY").call("getItems").size(),
          " o=", game.get("OPPONENT").get("INVENTORY").call("getItems").size())
    var clog = game.get("combatLog")
    var seen = 0
    var lines = []
    for i in range(3000):
        yield(self, "idle_frame")
        if clog:
            var evs = clog.get("events")
            while seen < evs.size():
                lines.append(dump_event(evs[seen]))
                seen += 1
        if game.get("fightEnded"):
            break
    var f = File.new()
    f.open("user://truth_S42.jsonl", File.WRITE)
    for l in lines:
        f.store_line(l)
    f.close()
    print("CB6: fightEnded=", game.get("fightEnded"), " events=", lines.size())
    quit(0)
