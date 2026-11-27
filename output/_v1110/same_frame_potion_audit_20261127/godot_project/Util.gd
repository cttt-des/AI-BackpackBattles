extends Node
func dictAppend(dict: Dictionary, key, value) -> void :
	if key in dict:
		dict[key].append(value)
	else:
		dict[key] = [value]
