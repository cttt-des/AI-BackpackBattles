extends Reference
class_name BalancedRange

var acc = 0.0

func reset():
	acc = 0.0

func randIntRange(from: int, to: int) -> int:
	var rng = Util.rng.randi_range(from, to)
	var expected: float = 0.5 * (from + to)
	
	var dif: float = rng - expected
	
	
	
	
	if acc >= 1:
		var malus = min(rng - from, int(acc))
		acc -= malus
		rng -= malus
		
		
	elif acc <= - 1:
		var bonus = min(to - rng, int(abs(acc)))
		acc += bonus
		rng += bonus
		
	
	acc += dif
	
	return rng
























