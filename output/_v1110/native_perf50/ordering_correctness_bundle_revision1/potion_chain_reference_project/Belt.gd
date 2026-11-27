extends "res://ItemStub.gd"
var numConsumed = 0
func isTypeInInventory(_type):
    return false
func giveRandomBuffs(_amount):
    trace.push_back("buff:Belt")
func cleanseRandomDebuffs(_amount):
    trace.push_back("cleanse:Belt")
func activate(_a = null, _b = true, _c = false, _d = null):
    pass
func onPotionEmptied(_potion):
	var numBuffs: = 0
	var active = false
	numConsumed += 1
	
	if numConsumed == 1:
		numBuffs = 1
		active = true
		
	elif numConsumed == 4:
		cleanseRandomDebuffs(getP1())
		active = true
	
	if isTypeInInventory(ItemBook.bagtacularDescriptor):
		numBuffs += int(ItemBook.bagtacularDescriptor.getP("buffs"))
		active = true
	
	if numBuffs > 0:
		giveRandomBuffs(numBuffs)
	
	if active:
		activate()
