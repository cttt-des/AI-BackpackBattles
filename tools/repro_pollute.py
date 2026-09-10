# -*- coding: utf-8 -*-
"""repro_pollute.py — 定位 main() 中 ancestor_entries['Item'] 被污染的时点。"""
import sys, json, os
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, ROOT)
import simulator.extract_items as E

db = json.load(open(E.DB_PATH, encoding='utf-8'))
items = db.get('items', db)
idx = E.scan_scripts()
anc = {}
orig = E._build_script_entry
state = {'clean': None}

def spy(path, idx_, anc_, **kw):
    r = orig(path, idx_, anc_, **kw)
    stem = E.stem_of(path)
    if stem == 'Item':
        dirty = 'triggerTime' in r['methods'].get('_onready_init', '')
        if state['clean'] is False and dirty:
            print("!!! Item entry became DIRTY when building", path, "skip==ITEM_SKIP:",
                  kw.get('skip_list') is E.ITEM_SKIP_METHODS)
        state['clean'] = dirty
    # 检测：任何 item 的构建把 anc['Item'] 覆盖
    if 'Item' in anc_ and 'triggerTime' in anc_['Item']['methods'].get('_onready_init', ''):
        pass
    return r

E._build_script_entry = spy

# 记录 anc['Item'] 何时变脏：在每个物品 build_behavior 前后检查
def pollute_watch(key, sp):
    before = 'triggerTime' in anc.get('Item', {}).get('methods', {}).get('_onready_init', '')
    E.build_behavior(sp, idx, anc)
    after = 'triggerTime' in anc.get('Item', {}).get('methods', {}).get('_onready_init', '')
    if after and not before:
        print(f"POLLUTED BY ITEM: {key} (script={items[key].get('script')})")

for key in items:
    scr = items[key].get("script")
    sp = None
    if scr:
        norm = scr[:-3].lower().replace(" ", "") if scr.endswith(".gd") else scr.lower().replace(" ", "")
        sp = idx.get(norm)
    if sp is None:
        sp = E.match_script_key(key, idx)
    if sp is None:
        continue
    pollute_watch(key, sp)

final = 'triggerTime' in anc.get('Item', {}).get('methods', {}).get('_onready_init', '')
print("final anc['Item'] dirty:", final)
