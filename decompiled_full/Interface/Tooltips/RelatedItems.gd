extends "res://Interface/Tooltips/TooltipItemLayout.gd"

onready var header = $RelatedHeader

var maxWidth = 420

func setItem(item, tooltip):
	var relatedItems = item.getRelatedItems()
	var maxRowHeight = item.getRelatedItemHeight()
	var itemsPerRow = int(min(item.getRelatedItemColumns(), relatedItems.size()))
	
	rect_min_size.x = maxWidth
	
	var usableWidth = maxWidth - MARGIN * 0.5
	var itemWidth = usableWidth / itemsPerRow
	var itemSize = Vector2(itemWidth, maxRowHeight - MARGIN * 0.5)
	
	var rowI = 0
	var columnI = 0
	var widestRow = 0
	var rowWidth = 0
	
	for descriptor in relatedItems:
		
		var relatedItem = addItem(descriptor, itemSize, tooltip)
		addedItems.push_back(relatedItem)
		var actualSize = relatedItem.getTextureSize()
		rowWidth += itemWidth
		
		relatedItem.position = Vector2(columnI * itemWidth + 0.5 * itemWidth, 
			header.rect_size.y + rowI * maxRowHeight + 0.5 * maxRowHeight)
		
		columnI += 1
		if columnI == itemsPerRow:
			columnI = 0
			rowI += 1
			if rowWidth > widestRow:
				widestRow = rowWidth
			rowWidth = 0
	
	if rowWidth > widestRow:
		widestRow = rowWidth
	
	var slack = usableWidth - widestRow
	for item in addedItems:
		item.position.x += slack * 0.5
	
	
	var numRows = ceil(relatedItems.size() / float(itemsPerRow))
	rect_min_size.y = header.rect_size.y + maxRowHeight * numRows + 20
