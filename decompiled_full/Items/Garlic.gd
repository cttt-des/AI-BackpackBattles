extends Food


var extraBlock: = 0

func doCooldownEffect():
	giveBlock(getBlock() + extraBlock)
	if rollChance():
		removeVampirism(getP1())
	activate()

func onShopEntered():
	extraBlock = 0

func addBonusBlock(_extraBlock):
	extraBlock += _extraBlock
