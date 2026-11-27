extends "res://test.gd"

func first():
    var extra = ["shrink","erase_current","erase_future","replace_future","clear_then_append","clear_dictionary","replace_array","append64","nested_append","nested_clear","append_ended","already_ended","delayed"]
    if not scenario in extra:
        .first()
        return
    trace.push_back(1)
    var id = EventBus.getEmissionID(emitter, EventBus.signalIDs["test"])
    var listeners = EventBus.connections[id]
    if scenario == "shrink":
        listeners.resize(1)
    elif scenario == "erase_current":
        listeners.remove(0)
    elif scenario == "erase_future":
        listeners.remove(1)
    elif scenario == "replace_future":
        listeners[1] = listeners[2]
    elif scenario == "clear_then_append":
        listeners.clear()
        EventBus.connectEvent(emitter,"test",self,"third")
    elif scenario == "clear_dictionary":
        EventBus.disconnectAll()
    elif scenario == "replace_array":
        EventBus.connections[id] = [funcref(self,"third")]
    elif scenario == "append64":
        for i in range(64):
            var watcher = keep(Watcher.new())
            watcher.trace = trace
            watcher.tag = i + 3
            EventBus.connectEvent(emitter,"test",watcher,"mark")
    elif scenario == "nested_append" and not nested:
        nested = true
        EventBus.connectEvent(emitter,"test",self,"third")
        EventBus.emitSignal(emitter,"test")
    elif scenario == "nested_clear":
        if not nested:
            nested = true
            EventBus.emitSignal(emitter,"test")
        else:
            listeners.clear()
    elif scenario == "append_ended":
        EventBus.connectEvent(emitter,"test",self,"third")
        Game.fightEnded = true
    elif scenario == "delayed":
        EventBus.connectEvent(emitter,"test",self,"third")

func extra_case(name):
    reset()
    scenario = name
    nested = false
    emitter = keep(Node.new())
    EventBus.connectEvent(emitter,"test",self,"first")
    EventBus.connectEvent(emitter,"test",self,"second")
    if name in ["erase_current","erase_future","replace_future"]:
        EventBus.connectEvent(emitter,"test",self,"third")
    if name == "already_ended":
        Game.fightEnded = true
    if name == "delayed":
        EventBus.setLoggingMode(2)
    EventBus.emitSignal(emitter,"test")
    if name == "delayed":
        EventBus.flushLoggingQueue()
    if name == "replace_array":
        EventBus.emitSignal(emitter,"test")
    return trace.duplicate()

func compare(a,b):
    trace.push_back(a.index)
    trace.push_back(b.index)
    return a.priority > b.priority

func run():
    var potions = []
    for reverse_order in [false,true]:
        for cost in [2,5,10]:
            potions.push_back(potion_case("heroic",reverse_order,cost))
        potions.push_back(potion_case("health",reverse_order,0))
    for kind in ["linked","without_activate","repeat_empty","trigger_empty"]:
        potions.push_back(potion_case(kind,false,0))
    var bus = {}
    for name in ["ordinary","append","clear","nested","ended"]:
        bus[name] = bus_case(name)
    var bus_extra = {}
    for name in ["shrink","erase_current","erase_future","replace_future","clear_then_append","clear_dictionary","replace_array","append64","nested_append","nested_clear","append_ended","already_ended","delayed"]:
        bus_extra[name] = extra_case(name)
    var file = File.new()
    assert(file.open("res://sort_cases.json",File.READ) == OK)
    var cases = JSON.parse(file.get_as_text()).result
    file.close()
    var results = []
    for keys in cases:
        var items = []
        for i in range(keys.size()):
            var item = SortItem.new()
            item.index = i
            item.priority = keys[i]
            items.push_back(item)
        trace = []
        items.sort_custom(self,"compare")
        var order = []
        for item in items:
            order.push_back(item.index)
        results.push_back({"order":order,"comparisons":trace.duplicate()})
    var output = File.new()
    assert(output.open("res://original_result.json",File.WRITE) == OK)
    output.store_string(JSON.print({"potions":potions,"bus":bus,"bus_extra":bus_extra,"sort_cases":results}))
    output.close()
    print("Original ordering reference written: " + str(results.size()) + " sorting cases")
    reset()
    get_tree().quit()
