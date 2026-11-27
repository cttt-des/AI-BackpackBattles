extends "res://test.gd"
var nested_b
func consume_b(_potion):
    nested_b.consumePotion()
func chain_case(kind):
    reset()
    var actor = keep(load("res://Actor.gd").new())
    var a = make_potion("res://Heroic.gd",actor,"A",4)
    var b = make_potion("res://Heroic.gd",actor,"B",4)
    var belt = keep(load("res://Belt.gd").new())
    belt.label = "Belt"
    belt.character_ = actor
    belt.trace = trace
    connect_marker(belt,"activated","activated:Belt")
    EventBus.connectEvent(a,"potion_emptied",belt,"onPotionEmptied")
    EventBus.connectEvent(b,"potion_emptied",belt,"onPotionEmptied")
    if kind == "four_drinks":
        var c = make_potion("res://Heroic.gd",actor,"C",4)
        var d = make_potion("res://Heroic.gd",actor,"D",4)
        EventBus.connectEvent(c,"potion_emptied",belt,"onPotionEmptied")
        EventBus.connectEvent(d,"potion_emptied",belt,"onPotionEmptied")
        for potion in [a,b,c,d]:
            potion.consumePotion()
        a.consumePotion()
    elif kind == "without_activate":
        a.consumePotion(null,false)
    elif kind == "trigger_empty":
        a.isFull = false
        a.triggerPotion()
    else:
        if kind in ["linked","nested_linked"]:
            a.affected = [b]
        if kind in ["nested","nested_linked"]:
            nested_b = b
            EventBus.connectEvent(a,"potion_triggered",self,"consume_b")
        a.consumePotion()
    return {"trace":trace.duplicate(),"full":[a.isFull,b.isFull],"numConsumed":belt.numConsumed}
func run():
    var rows = {}
    for kind in ["four_drinks","without_activate","trigger_empty","linked","nested","nested_linked"]:
        rows[kind] = chain_case(kind)
    var normal = load("res://Health.gd").new()
    var strong = load("res://StrongHealth.gd").new()
    rows["health_priorities"] = [normal.getTriggerPriority(),strong.getTriggerPriority()]
    normal.free()
    strong.free()
    var output = File.new()
    assert(output.open("res://potion_chain_result.json",File.WRITE) == OK)
    output.store_string(JSON.print(rows))
    output.close()
    reset()
    get_tree().quit()
