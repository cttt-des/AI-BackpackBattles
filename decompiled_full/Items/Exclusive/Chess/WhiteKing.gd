extends ChessPiece

onready var empower: = int(getP("empower"))
onready var buffs: = int(getP("buffs"))

func onPrepare():
	if board != null:
		connectForCombat(board, "piece_captured", "onAnyPieceCaptured")

func doCapturingEffect(_eliminatedPiece):
	return giveEmpower(empower)

func onAnyPieceCaptured(capturingPiece, _eliminatedPiece):
	if capturingPiece.pieceColor == PieceColor.White:
		if capturingPiece.numCaptures == 1:
			giveRandomBuffs(buffs)
		else:
			giveRandomBuffs(1)
