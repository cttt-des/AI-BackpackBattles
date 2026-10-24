extends Line2D
class_name PlotLine

const pointScene = preload("res://Interface/DamageMeter/PlotLinePoint.tscn")

var poolingHandle
var dataPoints = []
var symbol: Texture
var pointNode

func preset():
	pointNode = $Points
	clear_points()

func returnToObjectPool():
	show()
	clear_points()
	
	for dataPoint in dataPoints:
		ObjectPool.returnInstance(dataPoint, pointScene)
	
	dataPoints.clear()
	ObjectPool.returnInstance(self, poolingHandle)

func setColor(color: Color):
	modulate = color

func setSymbol(_symbol: Texture):
	symbol = _symbol

func addPoint(atPos: Vector2):
	atPos.y *= - 1
	
	add_point(atPos)
	
	if atPos != Vector2.ZERO:
		var newPoint = ObjectPool.instance(pointScene)
		pointNode.add_child(newPoint)
		dataPoints.push_back(newPoint)
		newPoint.rect_position = atPos - newPoint.rect_size * 0.5
		newPoint.setSymbol(symbol)

func flatline(untilX):
	add_point(Vector2(untilX, points[ - 1].y))
