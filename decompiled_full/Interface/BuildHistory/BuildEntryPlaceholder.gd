extends Control

const entryScene = preload("res://Interface/BuildHistory/BuildEntry.tscn")

var poolingHandle
var data
var entry = null
var entryIndex: int = - 1

func preset():
	var visNotifier = $VisibilityNotifier2D
	visNotifier.connect("screen_entered", self, "onVisible")
	visNotifier.connect("screen_exited", self, "onInvisible")

func setHistoryData(_data, _entryIndex: int = - 1):
	data = _data
	entryIndex = _entryIndex

func initEntry():
	if entry == null:
		entry = ObjectPool.instance(entryScene)
		add_child(entry)
		entry.setHistoryData(data, entryIndex)

func onVisible():
	initEntry()

func onInvisible():
	if entry != null and not entry.selected:
		entry.returnToObjectPool()
		entry = null


func returnToObjectPool():
	if entry != null:
		entry.returnToObjectPool()
		entry = null
	
	ObjectPool.returnInstance(self)

