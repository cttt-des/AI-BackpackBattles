extends ChessPiece

onready var weaponSpeed: = getP("speed") / 100.0
onready var buffs: = int(getP("buffs"))

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
