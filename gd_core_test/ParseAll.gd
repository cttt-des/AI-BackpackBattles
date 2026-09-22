extends SceneTree

# 批量加载 gd_core 全部脚本，一次性暴露所有文件的解析错误。
# Godot 每个脚本只报第一个 parse error，故此处逐文件 load 以最大化覆盖。
# 用法: godot --no-window --path gd_core_test --script ParseAll.gd

const FILES = [
	"res://gd_core/CoreConst.gd",
	"res://gd_core/CoreRng.gd",
	"res://gd_core/CoreEvent.gd",
	"res://gd_core/CoreEventBus.gd",
	"res://gd_core/CoreHooks.gd",
	"res://gd_core/CoreCombatLog.gd",
	"res://gd_core/CoreItemData.gd",
	"res://gd_core/CoreDamageSource.gd",
	"res://gd_core/CoreDamageResult.gd",
	"res://gd_core/CoreBuff.gd",
	"res://gd_core/CoreItem.gd",
	"res://gd_core/CoreCharacter.gd",
	"res://gd_core/CoreContext.gd",
	"res://gd_core/CoreCombat.gd",
]


func _init() -> void:
	print("PARSEALL: begin")
	var bad = 0
	for f in FILES:
		var s = load(f)
		if s == null:
			bad += 1
			print("PARSEALL: FAIL   ", f)
		else:
			print("PARSEALL: ok     ", f, "  methods=", s.get_script_method_list().size())
	print("PARSEALL: done, failed=", bad, "/", FILES.size())
	quit(0 if bad == 0 else 1)
