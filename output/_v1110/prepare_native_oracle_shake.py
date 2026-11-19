"""Observe critical-label births in an isolated source Oracle project."""
from pathlib import Path
import argparse
import shutil


stage = Path(__file__).resolve().parent
parser = argparse.ArgumentParser()
parser.add_argument("--source", default="full_corpus/expand/project")
parser.add_argument("--out", default="native_oracle_shake_project")
args = parser.parse_args()
source = (stage / args.source).resolve()
target = (stage / args.out).resolve()
assert source.is_relative_to(stage) and (source / "project.godot").is_file()
assert target.parent == stage and target.name.startswith("native_oracle_") and not target.exists()
shutil.copytree(source, target)

util = target / "Utility/Util.gd"
text = util.read_text("utf8")
for start, end, item in (("func spawnNumberLabel(", "func spawnLabelOnItem(", False),
                         ("func spawnLabelOnItem(", "func spawnStatLabelOnItem(", True)):
    begin = text.index(start)
    finish = text.index(end, begin)
    body = text[begin:finish]
    anchor = "\tvar pos = item.getNextFreeLabelPosition()\n" if item else "\tvar numberLabel = ObjectPool.instance(NUMBERLABEL_SCENE)\n"
    assert body.count(anchor) == 1, start
    body = body.replace(anchor, anchor + '''\tif oracleNativeCriticalShake and type == Game.EventType.CriticalDamage:
\t\tcollectCriticalShake(%s)
''' % str(item).lower())
    text = text[:begin] + body + text[finish:]
text += "\n\nvar oracleNativeCriticalShake := false\n\n" + (stage / "native_critical_shake.gd.inc").read_text("utf8")
util.write_text(text, encoding="utf8", newline="\n")
