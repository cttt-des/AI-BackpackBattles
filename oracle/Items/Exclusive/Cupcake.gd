extends Food

onready var numBuffs: = int(getP("buffs"))










func doCooldownEffect():
	heal()
	giveMostBuffs(numBuffs)







	activate()

