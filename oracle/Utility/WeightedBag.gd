extends Reference
class_name WeightedBag

var weightSums = []
var acc






func prepare(_weights: Array) -> void :
	weightSums.clear()
	acc = 0
	for weight in _weights:
		acc += weight
		weightSums.push_back(acc)
		


func roll():
	var rand = Util.rng.randf_range(0.0, acc)
	var index = weightSums.bsearch(rand)
	
	if index >= weightSums.size():
		Util.eassert()
		index = weightSums.size() - 1
	return index


func rollOnce(_weights: Array):
	prepare(_weights)
	return roll()
