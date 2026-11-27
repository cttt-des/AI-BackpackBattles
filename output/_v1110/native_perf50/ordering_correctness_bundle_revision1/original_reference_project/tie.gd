extends "res://test.gd"
func run():
    reset()
    var actor = keep(load("res://Actor.gd").new())
    var a = make_potion("res://Heroic.gd", actor, "A", 4)
    var b = make_potion("res://Heroic.gd", actor, "B", 4)
    var items = [a]
    for i in range(15):
        var filler = SortItem.new()
        filler.priority = 0
        filler.index = i
        items.push_back(filler)
    items.push_back(b)
    items.sort_custom(self, "compare")
    for item in items:
        if item.has_method("onPrepare"):
            item.onPrepare()
    actor.useStamina(2)
    print("TIE_RESULT=" + JSON.print({"trace":trace,"full":[a.isFull,b.isFull]}))
    reset()
    get_tree().quit()
