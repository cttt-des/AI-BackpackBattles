extends Item
var spikes

func onPrepare():
	connectForCombat(character(), "battle_rage_started", "onBattleRageStarted")
	character().addBattleRageDuration(getP_m("dur_rage"))


func onBattleRageStarted(event):
	giveSpikes(spikes, event)
	activate()

func _readyInit():
	._readyInit()
	spikes = int(getP("spikes"))
