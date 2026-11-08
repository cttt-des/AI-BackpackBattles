extends AnimationPlayer

export var ani = "Flicker"
export var minDist = 0.1
export var maxDist = 3.0
export var minSpeed = 0.3
export var maxSpeed = 1.0

func _ready():
	# ★ np51㊳ harness 修正：UI ItemLibrary 展示实例的 flicker 是 UI 噪声，
	#   其 delay/speed 抽不应消耗战斗判定链（真实游戏 UI 库亦无战斗链语义）。
	#   跳过 connect+首播 → 无 callDelayed 注册、无战斗窗发火、无链消耗。
	if str(get_path()).find("/UI/ItemLibrary/") != -1:
		return
	connect("animation_finished", self, "onAnimationEnded")
	onAnimationEnded(ani)


func onAnimationEnded(aniName):
	var d = Util.rng.randf_range(minDist, maxDist)
	# ★ np51㊳终⑤ fire-time 取证探针（ORACLE_FLKPROBE 门控，零 rng 消耗）
	if OS.get_environment("ORACLE_FLKPROBE") != "":
		print("[FLKD] path=", get_path(), " delay=", d)
	Util.callDelayed(self, "playAni", d)

func playAni():
	var spd = Util.rng.randf_range(minSpeed, maxSpeed)
	playback_speed = spd
	play(ani)
	if OS.get_environment("ORACLE_FLKPROBE") != "":
		print("[FLKD-ani] path=", get_path(), " t=", Util.time, " pre=", spd)
