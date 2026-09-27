extends SceneTree

# 批量加载 gd_core 全部脚本，一次性暴露所有文件的解析错误。
# Godot 每个脚本只报第一个 parse error，故此处逐文件 load 以最大化覆盖。
# 用法: godot --no-window --path gd_core_test --script ParseAll.gd

const FILES = [
	"res://gd_core/CoreConst.gd",
	"res://gd_core/CoreUtil.gd",
	"res://gd_core/CoreRng.gd",
	"res://gd_core/CoreEvent.gd",
	"res://gd_core/CoreEventBus.gd",
	"res://gd_core/CoreHooks.gd",
	"res://gd_core/CoreCombatLog.gd",
	"res://gd_core/CoreItemData.gd",
	"res://gd_core/CoreGrid.gd",
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
		# ★ load() 对有解析错误的脚本**不一定返回 null**：Godot 会回一个残缺脚本对象，
		#   其 get_script_method_list() 为空。只判 null 会漏掉真错误（曾漏掉 CoreCharacter
		#   的一处语法错误，闸门假通过），故把「方法数为 0」一并判失败。
		var n = 0 if s == null else s.get_script_method_list().size()
		if s == null or n == 0:
			bad += 1
			print("PARSEALL: FAIL   ", f, "  (empty script: 解析错误或类未加载)")
		else:
			print("PARSEALL: ok     ", f, "  methods=", n)
	print("PARSEALL: done, failed=", bad, "/", FILES.size())
	quit(0 if bad == 0 else 1)
