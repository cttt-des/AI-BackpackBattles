# -*- coding: utf-8 -*-
"""repro_main.py — 复现 extract_items.main 的 class_methods 输出，检查过滤是否生效。"""
import sys, json, os
ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, ROOT)
import simulator.extract_items as E

captured = {}
orig = json.dump
def spy(obj, fp, *a, **k):
    captured['db'] = obj
    return orig(obj, fp, *a, **k)
json.dump = spy
E.main()
cm = captured['db']['class_methods']
print('descriptor in dumped Item:', 'descriptor' in cm['Item']['methods']['_onready_init'])
