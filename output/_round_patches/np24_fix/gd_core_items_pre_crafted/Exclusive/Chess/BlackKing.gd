extends ChessPiece
var weaponSpeed
var buffs

func onPrepare():
	if board != null:
		connectForCombat(board, "piece_captured", "onAnyPieceCaptured")


func doCapturingEffect(_eliminatedPiece):
	for item in inventory.getItems():
		if item.isWeapon():
			item.addSpeed(weaponSpeed)


func onAnyPieceCaptured(capturingPiece, _eliminatedPiece):
	if capturingPiece.pieceColor == PieceColor.Black:
		if capturingPiece.numCaptures == 1:
			removeRandomBuffs(buffs)
		else:
			removeRandomBuffs(1)

func _readyInit():
	._readyInit()
	weaponSpeed = getP("speed") / 100.0
	buffs = int(getP("buffs"))
