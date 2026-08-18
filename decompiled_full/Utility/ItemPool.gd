extends Reference
class_name ItemPool

var pool: Array
var topIndex: int
var sellPrice: = false
var deleteAfterDraw: bool = false

func resetPool():
	pool.clear()

func addItem(item):
	if not item.isReleased():
		print("missing item: ", item.itemIndex)
		return
	pool.push_back(item)

func sortItems():
	pool.sort_custom(ItemSorter, "sortPrice")
	topIndex = pool.size() - 1

func resetPrice():
	topIndex = pool.size() - 1


func setPrice(price: int):
	for i in range(topIndex, 0, - 1):
		if sellPrice:
			if pool[i].getSellPrice() <= price:
				break
		else:
			if pool[i].getPrice() <= price:
				break
		topIndex -= 1

func removeItem(index):
	pool.remove(index)
	if index <= topIndex:
		topIndex -= 1

func getItem(index):
	var item = pool[index]
	if deleteAfterDraw or item.canOnlyExistOnce():
		removeItem(index)
	
	if (ItemBook.isSpiritCompanion(item) and 
		not ItemBook.isItemOwned(ItemBook.spiritBellsDescriptor)):
		
		Util.eprint("Removing spirit companions from pool")
		for spiritCompanion in ItemBook.spiritCompanionDescriptors:
			var i = pool.find(spiritCompanion)
			if i != - 1:
				removeItem(i)
	
	return item

func getRandomItem():
	var index = Util.rng.randi_range(0, topIndex)
	return getItem(index)


func getRandomItemWithinQuantile(quantile: float):
	var lowerBound = int(topIndex * quantile)
	return getItem(Util.rng.randi_range(lowerBound, topIndex))

func getRandomItemTopHeavy(topQuantileChance = 0.9, topQuantile = 0.5):
	if Util.flip(topQuantileChance):
		return getRandomItemWithinQuantile(topQuantile)
	else:
		return getRandomItem()

func printPool():
	print("POOL START")
	for item in pool:
		print(item.getName())
	print("POOL END")

class ItemSorter:
	static func sortPrice(item1, item2):
		return item1.getPrice() < item2.getPrice()
