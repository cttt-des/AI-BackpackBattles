"""Add passive chess choice traces only to two disposable comparison projects."""
from pathlib import Path
import shutil


stage = Path(__file__).resolve().parent
projects = [
    (stage / "native_controlled_chess_project", stage / "native_controlled_chess_trace_project"),
    (stage / "full_corpus/expand/project", stage / "native_oracle_chess_trace_project"),
]


def instrument(source):
    for target in ("activePieces", "captureCells", "moveCells"):
        lines = source.splitlines(keepends=True)
        count = 0
        for i in range(len(lines) - 1, -1, -1):
            if lines[i].strip() != f"{target}.shuffle()":
                continue
            indent = lines[i][:len(lines[i]) - len(lines[i].lstrip())]
            arg = "null" if target == "activePieces" else "piece"
            phase = f"{target}:{i + 1}"
            lines.insert(i + 1, indent + f'_chess_trace("{phase}:after", {target}, {arg})\n')
            lines.insert(i, indent + f'_chess_trace("{phase}:before", {target}, {arg})\n')
            count += 1
        assert count == (2 if target == "captureCells" else 1), target
        source = "".join(lines)
    return source + '''

func _chess_trace(label, values, piece):
	var row := []
	for value in values:
		if value is Vector2:
			row.append([int(value.x), int(value.y)])
		else:
			row.append([value.getName(), str(value.occupiedCells[0])])
	print("[CHESS] ", JSON.print([round(Game.combatTimer.combatTime * 60), ownerType,
		str(occupiedCells[0]), label, piece.getName() if piece != null else "", row]))
'''


for original, destination in projects:
    assert original.is_dir() and not destination.exists(), destination
    shutil.copytree(original, destination)
    path = destination / "Items/Exclusive/ChessBoard.gd"
    path.write_text(instrument(path.read_text("utf8")), encoding="utf8", newline="\n")
