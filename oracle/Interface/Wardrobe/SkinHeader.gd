extends FocusGrabbingTextureButton

var skin: CharacterSkin

func setSkin(_skin: CharacterSkin):
	skin = _skin
	texture_normal = skin.icon
	texture_hover = skin.icon_hovered

func onHover():
	.onHover()
	Game.wardrobe.onSkinIconHovered(self)

func onHoverEnd():
	if isHovered:
		.onHoverEnd()
		Game.wardrobe.onSkinIconUnhovered(self)

func onPressed():
	.onPressed()
	Game.wardrobe.onSkinIconSelected(self)
