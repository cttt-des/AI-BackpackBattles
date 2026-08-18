extends Reference
class_name StatHistory

var eventNumbers = []
var values = []

func addValue(eventNum, value):
	if values.empty() or not Util.equals(values[ - 1], value):
		eventNumbers.push_back(eventNum)
		values.push_back(value)

func hasData() -> bool:
	return eventNumbers.size() > 1

func clear():
	eventNumbers.clear()
	values.clear()

func getValueAt(eventNum):
	
	if eventNum < 0:
		return values[0]
	
	if eventNumbers[ - 1] <= eventNum:
		return values[ - 1]
	
	var index = eventNumbers.bsearch(eventNum, false) - 1
	return values[index]

func getLastEntryBefore(eventNum):


	
	var index = eventNumbers.bsearch(eventNum, false) - 1
	return [eventNumbers[index], values[index]]

func addValueAcc(eventNum, value):
	var curValue = 0
	if not values.empty():
		curValue = values[ - 1]
	addValue(eventNum, curValue + value)
