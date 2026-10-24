extends ItemToolTip

const singleIconPos = Vector2(295, 37)
const dualIconOffset = 25

const skillTexture = preload("res://Interface/Tooltips/TooltipBase_Skill.png")
const skillDivider = preload("res://Interface/Tooltips/Divider_Skill.png")
const dualClassMat = preload("res://Interface/Tooltips/MulticlassTooltip.material")

var icon1
var icon2

func preset():
	.preset()
	icon1 = $Icon
	icon2 = $Icon2

func setItem(_item):
	if _item.descriptor.isTreasure():
		self.texture = Util.uniqueTooltipTextures[_item.descriptor.StuffedClasses.Neutral]
		divider1.texture = Util.uniqueTooltipDivider[_item.descriptor.StuffedClasses.Neutral]
	
	elif _item.hasType(_item.Type.Skill) and _item.descriptor.classes == _item.descriptor.StuffedClasses.Neutral:
		self.texture = skillTexture
		divider1.texture = skillDivider
	else:
		var classesAsArr = _item.descriptor.getClassesAsArray()
		
		
		self.texture = Util.uniqueTooltipTextures[classesAsArr[0]]
		divider1.texture = Util.uniqueTooltipDivider[classesAsArr[0]]
		icon1.show()
		icon1.position = singleIconPos
		icon1.texture = Util.uniqueTooltipIcon[classesAsArr[0]]
		
		if classesAsArr.size() == 2:
			var mat = dualClassMat.duplicate()
			set_material(mat)
			mat.set_shader_param("tex2", Util.uniqueTooltipTextures[classesAsArr[1]])
			
			
			var dividerMat = dualClassMat.duplicate()
			dividerMat.set_shader_param("tex2", Util.uniqueTooltipDivider[classesAsArr[1]])
			divider1.set_material(dividerMat)
			
			icon1.position = singleIconPos - Vector2(dualIconOffset, 0)
			icon2.show()
			icon2.texture = Util.uniqueTooltipIcon[classesAsArr[1]]
			icon2.position = singleIconPos + Vector2(dualIconOffset, 0)
	
	.setItem(_item)


func discard():
	set_material(null)
	divider1.set_material(null)
	icon1.hide()
	icon2.hide()
	.discard()
