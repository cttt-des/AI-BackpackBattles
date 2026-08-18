extends Reference
class_name Counter

var dict: Dictionary

func empty() -> bool:
	return dict.empty()

func fromCounter(c):
	dict = c.dict.duplicate()
	return self

func clear() -> void :
	dict.clear()

func add(key, amount = 1) -> void :
	if dict.has(key):
		dict[key] += amount
	else:
		dict[key] = amount

func remove(key, amount: int = 1) -> void :
	var newVal = dict.get(key, 0) - amount
	if newVal <= 0:
		dict.erase(key)
	else:
		set(key, newVal)
		

func set(key, amount: int) -> void :
	dict[key] = amount

func get(key) -> int:
	return dict.get(key, 0)

func has(key) -> bool:
	return dict.has(key)

func addList(keys: Array) -> void :
	for key in keys:
		add(key)

func removeList(keys: Array) -> void :
	for key in keys:
		remove(key)

func addDict(_dict: Dictionary) -> void :
	for key in _dict:
		add(key, _dict[key])

func removeDict(_dict: Dictionary) -> void :
	for key in _dict:
		remove(key, _dict[key])

func countAll() -> int:
	var sum = 0
	for key in dict:
		sum += dict[key]
	return sum
	
func addCounter(counter) -> void :
	addDict(counter.dict)

func removeCounter(counter) -> void :
	removeDict(counter.dict)

func isDictIn(_dict: Dictionary) -> bool:
	for key in _dict:
		if dict.get(key, 0) < _dict[key]:
			return false
	return true

func isCounterIn(counter) -> bool:
	return isDictIn(counter.dict)

func getKeys() -> Array:
	return dict.keys()

func getValues() -> Array:
	return dict.values()

func printDict():
	print(dict)

func printItems():
	for key in dict:
		print(key.getName(), ": ", dict[key])
