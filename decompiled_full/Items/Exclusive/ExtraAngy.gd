extends Item

var activated: bool
var battleRageDur: float

func onPrepare():
	activated = false
	
	connectForCombat(character(), "battle_rage_started", "onBattleRageStarted")
	connectForCombat(character(), "battle_rage_ended", "onBattleRageEnded")

func preCombatStart():
	.preCombatStart()
	deactivateCooldown()

func onBattleRageStarted(event):
	if not activated:
		battleRageDur = event.getParam("duration", 0)

func onBattleRageEnded(_event):
	if not activated:
		activated = true
		
		activateCooldown()

func doCooldownEffect():
	var dur = battleRageDur * getP_m("dur") / 100.0
	character().startBattleRage(self, dur, null, false)
	onAfterEffectFinished()
	
