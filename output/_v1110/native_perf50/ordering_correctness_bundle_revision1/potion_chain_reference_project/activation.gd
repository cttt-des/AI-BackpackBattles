extends "res://test.gd"
func make_items(keys):
    var items = []
    for i in range(keys.size()):
        var item = SortItem.new()
        item.index = i
        item.priority = keys[i]
        items.push_back(item)
    return items
func indices(items):
    var result = []
    for item in items:
        result.push_back(item.index)
    return result
func run():
    var input = File.new()
    assert(input.open("res://activation_cases.json",File.READ) == OK)
    var cases = JSON.parse(input.get_as_text()).result
    input.close()
    var results = []
    for case in cases:
        seed(int(case["seed"]))
        var player = make_items(case["player"])
        player.shuffle()
        var ps = indices(player)
        player.sort_custom(self,"compare")
        var opponent = make_items(case["opponent"])
        opponent.shuffle()
        var os = indices(opponent)
        opponent.sort_custom(self,"compare")
        results.push_back({"player_shuffle":ps,"player_sorted":indices(player),"opponent_shuffle":os,"opponent_sorted":indices(opponent)})
    var output = File.new()
    assert(output.open("res://activation_result.json",File.WRITE) == OK)
    output.store_string(JSON.print(results))
    output.close()
    get_tree().quit()
