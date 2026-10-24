extends LocalizedControl

const RIGHT_BORDER = 1890
const TOP_BORDER = 30

func init(key: String, control: Node, offset: Vector2 = Vector2.ZERO):
	translationKey = key
	updateLocale()
	call_deferred("positionLabel", control, offset)

func positionLabel(control, offset):
	rect_global_position = control.rect_global_position
	rect_global_position.x += control.rect_size.x * 0.5
	rect_global_position.x -= rect_size.x * 0.5
	rect_global_position += offset
	
	var difToRightBorder = RIGHT_BORDER - (rect_global_position.x + rect_size.x)
	if difToRightBorder < 0:
		rect_global_position.x += difToRightBorder
	
	var difToTopBorder = TOP_BORDER - rect_global_position.y
	if difToTopBorder > 0:
		rect_global_position.y += difToTopBorder
	
	
