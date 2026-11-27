extends Node

var trace = []
var objects = []
var nested = false
var scenario = ""
var emitter

class Watcher extends Node:
    var trace
    var tag
    func mark(_argument = null):
        trace.push_back(tag)

class SortItem extends Reference:
    var index
    var priority
    func getTriggerPriority():
        return priority

func compare(a, b):
    return a.getTriggerPriority() > b.getTriggerPriority()

func _init():
    call_deferred("run")

func keep(object):
    objects.push_back(object)
    return object

func connect_marker(item, signal_name, tag):
    var watcher = keep(Watcher.new())
    watcher.trace = trace
    watcher.tag = tag
    EventBus.connectEvent(item, signal_name, watcher, "mark")

func reset():
    EventBus.disconnectAll()
    Game.fightEnded = false
    trace = []
    for object in objects:
        object.free()
    objects.clear()

func make_potion(script, actor, label, amount):
    var potion = keep(load(script).new())
    potion.character_ = actor
    potion.label = label
    potion.strength = amount
    for sig in ["potion_triggered", "activated", "potion_emptied"]:
        connect_marker(potion, sig, sig + ":" + label)
    return potion

func potion_case(kind, reverse_order, cost):
    reset()
    var actor = keep(load("res://Actor.gd").new())
    var script = "res://Health.gd" if kind == "health" else "res://Heroic.gd"
    var amount = 20 if kind == "health" else 4
    var a = make_potion(script, actor, "A", amount)
    var b = make_potion(script, actor, "B", amount)
    if kind == "heroic" or kind == "health":
        var ordered = [b, a] if reverse_order else [a, b]
        for potion in ordered:
            potion.onPrepare()
        if kind == "heroic":
            actor.useStamina(cost)
        else:
            EventBus.emitSignal(actor, "character_damaged", [1, null])
    elif kind == "linked":
        a.affected = [b]
        a.consumePotion()
    elif kind == "without_activate":
        a.consumePotion(null, false)
    elif kind == "repeat_empty":
        a.consumePotion()
        a.consumePotion()
    elif kind == "trigger_empty":
        a.isFull = false
        a.triggerPotion()
    return {"kind":kind,"reverse":reverse_order,"cost":cost,"trace":trace.duplicate(),"full":[a.isFull,b.isFull],"stamina":actor.curStamina,"health":actor.curHealth}

func first():
    trace.push_back(1)
    if scenario == "append":
        EventBus.connectEvent(emitter, "test", self, "third")
    elif scenario == "clear":
        var id = EventBus.getEmissionID(emitter, EventBus.signalIDs["test"])
        EventBus.connections[id].clear()
    elif scenario == "nested" and not nested:
        nested = true
        EventBus.emitSignal(emitter, "test")
    elif scenario == "ended":
        Game.fightEnded = true

func second():
    trace.push_back(2)

func third():
    trace.push_back(3)

func bus_case(name):
    reset()
    scenario = name
    nested = false
    emitter = keep(Node.new())
    EventBus.connectEvent(emitter, "test", self, "first")
    EventBus.connectEvent(emitter, "test", self, "second")
    EventBus.emitSignal(emitter, "test")
    return trace.duplicate()

func run():
    var potions = []
    for reverse_order in [false, true]:
        for cost in [2, 5, 10]:
            potions.push_back(potion_case("heroic", reverse_order, cost))
        potions.push_back(potion_case("health", reverse_order, 0))
    for kind in ["linked", "without_activate", "repeat_empty", "trigger_empty"]:
        potions.push_back(potion_case(kind, false, 0))
    var bus = {}
    for name in ["ordinary", "append", "clear", "nested", "ended"]:
        bus[name] = bus_case(name)
    var sorts = []
    for length in [16, 17, 32, 40, 80]:
        for mode in range(4):
            var items = []
            for i in range(length):
                var item = SortItem.new()
                item.index = i
                item.priority = 0 if mode == 0 else ((i * 7 + mode) % (mode + 1)) * 1000
                items.push_back(item)
            items.sort_custom(self, "compare")
            var order = []
            for item in items:
                order.push_back(item.index)
            sorts.push_back({"length":length,"mode":mode,"order":order})
    print("AUDIT_RESULT=" + JSON.print({"potions":potions,"bus":bus,"sorts":sorts}))
    reset()
    get_tree().quit()
