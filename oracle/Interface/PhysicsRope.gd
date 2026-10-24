extends Node2D

signal reroll

const NUM_SEGMENTS = 10
const MAX_PULL = 200.0
const PULL_UP_SPEED = 5.0
const segmentScene = preload("res://Interface/RopeSegment.tscn")

onready var ropeHolder = $RopeHolder
onready var line2D = $Line2D
onready var ropeEndSegment = $End
onready var tag = $Tag
onready var tagSprite = $Tag / Tag
onready var tagAnimation = $Tag / Cost / AnimationPlayer
onready var tagCostLabel = $Tag / Cost

var segments: = []
var joints: = []
var jointPositionNodes: = []
var jointPositions: = []
var draggedSegment = null
var pulledY: float
var rerollReadyTime: = 0.0
var hovered: = 0
var curEndY = 0

func _ready():
	Game.connect("switch_to_shop", self, "onSwitchToShop")
	InputBlocker.connect("inputs_blocked", self, "endDrag")
	
	ropeHolder.position = Vector2(0, 0)
	
	for i in NUM_SEGMENTS:
		var segment = segmentScene.instance()
		if curEndY > 300.0:
			segment.LENGTH = 30
		else:
			segment.LENGTH = 60
		
		addSegment(segment)
	
	
	Util.reparent(tag, segments[ - 3])
	tag.position = Vector2.ZERO
	
	addSegment(ropeEndSegment)
	
	for i in NUM_SEGMENTS:
		var joint: PinJoint2D = PinJoint2D.new()
		
		
		if i == 0:
			joint.node_a = ropeHolder.get_path()
		else:
			joint.node_a = segments[i - 1].get_path()
		
		joint.node_b = segments[i].get_path()
		joint.position = segments[i].getStartPos()
		joint.softness = 0.2
		
		add_child(joint)
		joints.push_back(joint)
	
	var endJoint = PinJoint2D.new()
	endJoint.node_a = segments[ - 1].get_path()
	endJoint.node_b = ropeEndSegment.get_path()
	endJoint.position = ropeEndSegment.getStartPos()
	endJoint.softness = 0.1
	add_child(endJoint)
	joints.push_back(endJoint)
	
	segments.push_back(ropeEndSegment)
	
	jointPositionNodes.push_back(ropeHolder)
	for segment in segments:
		jointPositionNodes.push_back(segment.end)
	
	for joint in joints:
		jointPositions.push_back(joint.position)

func onSwitchToShop():
	reset()

func reset():
	rerollReadyTime = Util.time + 0.2
	Game.rerollRope.instancePhysicsRope()

	
	





func addSegment(segment):
	if not segment.is_inside_tree():
		add_child(segment)
		segments.push_back(segment)
	segment.position = Vector2(0, curEndY + segment.getLength() * 0.5)
	curEndY += segment.getLength()
	segment.rope = self
	segment.clickArea.connect("gui_input", self, "gui_input_segment", [segment])

func isGrabbed():
	return draggedSegment != null

func _physics_process(delta):
	
	var difToStart = segments[ - 1].global_position.distance_to(ropeHolder.global_position)
	if difToStart > 1000:
		print("Reroll rope reset ", difToStart)
		reset()
		return
	
	line2D.clear_points()
	var points = []
	for segment in jointPositionNodes:
		points.push_back(segment.global_position - global_position)
		
	
	var smoothed = catmull_rom_spline(points, 10)
	smoothed.invert()
	for point in smoothed:
		line2D.add_point(point)
	
	if draggedSegment != null:
		
		var clampedMousePos = getClampedMousePos()
		var pull = Util.getMousePosInWindow().y - clampedMousePos.y
		
		if pull > 0:
			pulledY = min(MAX_PULL, pulledY + pull)
			if pulledY == MAX_PULL:
				rerollReadyTime = Util.time + 0.2
				endDrag()
				emit_signal("reroll")
		else:
			pulledY = max(0, pulledY - PULL_UP_SPEED)
	else:
		pulledY = max(0, pulledY - PULL_UP_SPEED)
		
	ropeHolder.position.y = pulledY



func getClampedMousePos() -> Vector2:
	var draggedSegmentIndex = segments.find(draggedSegment)
	var length = 20
	for i in draggedSegmentIndex + 1:
		length += segments[i].getLength()
		
	var ropeHolderToMouse = Util.getMousePosInWindow() - ropeHolder.global_position
	
	return ropeHolder.global_position + ropeHolderToMouse.limit_length(length)

func gui_input_segment(event, segment):
	if rerollReadyTime > Util.time:
		return
	
	if Util.isClickEvent(event):
		if (Game.isShopActive() and 
			not Game.draggedItem and 
			Util.time > Game.lastItemDropTime + 0.5):
			
			
			draggedSegment = segment
			draggedSegment.startDrag()
			Game.cancelSwitch()
	
	elif Util.isClickReleaseEvent(event):
		endDrag()
	
	elif Util.isRightClick(event):
		Game.rerollRope.switchToStiffRope()
		rerollReadyTime = Util.time + 0.2
		

func endDrag():
	if draggedSegment != null:
		
		draggedSegment.endDrag()
	draggedSegment = null
	modulate = Color.white

func onHovered(segment):
	hovered += 1
	modulate = Color(1.2, 1.2, 1.2, 1)

func onHoveredEnd(segment):
	hovered -= 1
	if hovered == 0 and draggedSegment == null:
		modulate = Color.white

func catmull_rom_spline(_points: Array, resolution: int = 10, 
	extrapolate_end_points = true) -> Array:
	
	var points = _points.duplicate()
	if extrapolate_end_points:
		points.insert(0, points[0] - (points[1] - points[0]))
		points.append(points[ - 1] + (points[ - 1] - points[ - 2]))
	
	var smooth_points: = Array()
	if points.size() < 4:
		return points

	for i in range(1, points.size() - 2):
		var p0 = points[i - 1]
		var p1 = points[i]
		var p2 = points[i + 1]
		var p3 = points[i + 2]
		
		for t in range(0, resolution):
			var tt = t / float(resolution)
			var tt2 = tt * tt
			var tt3 = tt2 * tt
			var q = (0.5 * (
				(2.0 * p1)
				+ ( - p0 + p2) * tt
				+ (2.0 * p0 - 5.0 * p1 + 4 * p2 - p3) * tt2
				+ ( - p0 + 3.0 * p1 - 3.0 * p2 + p3) * tt3
			))
			
			smooth_points.append(q)

	return smooth_points
