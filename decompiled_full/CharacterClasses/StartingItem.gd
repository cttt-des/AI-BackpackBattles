extends Resource
class_name StartingItem

export (String) var itemName
export (Item.FaceDirection) var faceDirection
export (Vector2) var topLeftCell

func getTranslatedItemName() -> String:
	return Util.tra(itemName + "_NAME")
