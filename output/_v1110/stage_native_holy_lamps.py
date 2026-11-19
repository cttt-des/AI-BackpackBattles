"""Preserve the Holy marker granted by Buy the Holy Light during assembly."""
from pathlib import Path


sim = Path(__file__).resolve().parent / "sim_native"
relative = Path("gd_core_items/Exclusive/BuytheHolyLight.gd")
source = (sim / relative).read_text("utf8")
start = source.index("func onAddToInventory():\n")
end = source.index("func onItemRoll", start)
source = source[:start] + '''func onAddToInventory():
	for item in inventory.getItems():
		_tagLamp(item)

func onItemAdded(item):
	.onItemAdded(item)
	_tagLamp(item)

func onItemRemoved(item):
	.onItemRemoved(item)
	if isLamp(item):
		item.removeDynamicType(CoreConst.Type.Holy, self)

func onRemoveFromInventory():
	if inventory != null:
		for item in inventory.getItems():
			if isLamp(item):
				item.removeDynamicType(CoreConst.Type.Holy, self)

func _tagLamp(item):
	if isLamp(item) and not item.hasDynamicType(CoreConst.Type.Holy, self):
		item.addDynamicType(CoreConst.Type.Holy, self)


''' + source[end:]
for root in (sim, sim / "gd_core_test", sim / "native_sim_cpp"):
    (root / relative).write_text(source, encoding="utf8", newline="\n")
