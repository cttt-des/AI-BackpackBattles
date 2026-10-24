extends Node

var poolingHandle

func preset():
	pass

func returnToObjectPool():
	ObjectPool.returnInstance(self)

