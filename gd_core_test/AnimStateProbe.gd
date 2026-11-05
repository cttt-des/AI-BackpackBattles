# =============================================================================
# AnimStateProbe.gd — AnimationPlayer.current_animation 语义实测（np46 逐案隔离）
# 目的：确定「停止播放后 current_animation 是否残留动画名」与
#       「set_current_animation("") 是否安全复位为空串」——决定 oracle_fight.gd
#       逐案隔离里 damageAnimation 残留态的复位写法（gd_core fresh 语义=""）。
# =============================================================================
extends SceneTree


func _initialize() -> void :
	var ap := AnimationPlayer.new()
	root.add_child(ap)
	var anim := Animation.new()
	anim.length = 10.0
	var track := anim.add_track(Animation.TYPE_VALUE)
	anim.track_set_path(track, NodePath(".:rotation"))
	anim.track_insert_key(track, 0.0, 0.0)
	anim.track_insert_key(track, 5.0, 1.0)
	ap.add_animation("Poison", anim)
	var anim2 := Animation.new()
	anim2.length = 10.0
	ap.add_animation("Hit", anim2)

	print("[probe] fresh current_animation=「%s」" % ap.current_animation)
	ap.play("Poison")
	print("[probe] after play(Poison) =「%s」" % ap.current_animation)
	ap.stop()
	print("[probe] after stop() =「%s」" % ap.current_animation)
	ap.play("Hit")
	print("[probe] after play(Hit) =「%s」" % ap.current_animation)
	ap.current_animation = ""
	print("[probe] after set \"\" =「%s」" % ap.current_animation)
	ap.play("Poison")
	ap.seek(20.0, true)   # 播过头（动画结束）
	ap.advance(20.0)
	print("[probe] after advance past end =「%s」" % ap.current_animation)
	ap.play("Poison")
	ap.play("Hit")
	print("[probe] after play(Hit) over Poison =「%s」" % ap.current_animation)
	quit(0)
