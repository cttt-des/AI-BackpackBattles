extends Reference
class_name BalancedRng

var expectedWins = Util.rng.randf_range(0.2, - 0.2)
var wins = 0
var balancedness = 3.0
var lastResult = false

func _init(startBias = 0.0):
	expectedWins += startBias

func setBias(bias):
	expectedWins += bias

func rollPercent(target) -> bool:
	return roll(target / 100.0)

func roll(target) -> bool:
	if target <= 0: return false
	elif target >= 1: return true
	
	var chance = target
	
	var dif = expectedWins - wins
	if dif > 0.3:
		chance *= balancedness * min(1.0, dif)
	elif dif < - 0.3:
		chance /= balancedness * min(1.0, - dif)
	
	expectedWins += target
	
	if lastResult and target < 0.4:
		
		chance *= 0.5
		
		
	elif not lastResult and target > 0.6:
		
		chance *= 2.0
		
		
	
	var result = Util.flip(chance)
	
	
	lastResult = result
	
	if result:
		wins += 1
		return true
	else:
		return false
	

var extraLuck = 0.0
var lastTarget = 0.0
var accChance = 0.0
const luckBalance = 0.2

func roll2(target) -> bool:
	if target <= 0:
		return false
	elif target >= 1:
		return true
	




	var chance = target + extraLuck * 0.3
	
	
	
	if Util.flip(chance):
		extraLuck -= 1.0 - target
		return true
	else:
		extraLuck += target
		return false

func roll1(target) -> bool:
	if target <= 0:
		return false
	elif target >= 1:
		return true
	




	
	accChance += target - lastTarget
	extraLuck += clamp(accChance, 0, 1) - target
	
	lastTarget = target
	
	if Util.flip(accChance):
		accChance = target - extraLuck
		return true
	else:
		accChance += luckBalance
		return false

func reset():
	expectedWins = 0.0
	wins = 0
	lastResult = false
	
	extraLuck = 0.0
	accChance = 0.0
	lastTarget = 0.0
	
