#!/usr/bin/env bash
# 批录完成后的一键收口：抬闸三场重录→还原→夹具再生→verify 全量→读数
set -e
cd "D:/文件资料/学习/自动背包AI"
export APPDATA="D:\\文件资料\\学习\\自动背包AI\\output\\_recovery\\appdata"

echo "=== ① 批录完整性 ==="
N=$(ls output/oracle/fights | wc -l)
echo "语料场数: $N"
[ "$N" -lt 914 ] && { echo "不足914，中止"; exit 1; }

echo "=== ② 抬闸重录三场（np22 协议）==="
python -X utf8 output/_recovery/_gate_lift.py apply
for c in run696_r18 run1371_r18 run1444_r18; do
  rm -rf "output/oracle/fights/$c"
  ORACLE_FIGHTS_ROOT="D:/文件资料/学习/自动背包AI/output/oracle/fights" \
  ORACLE_ONLY_CASES=$c ORACLE_FIGHT_CHUNK=0 \
  timeout 2400 output/godot36/Godot_v3.6-stable_win64.exe \
    --headless --audio-driver Dummy --path oracle --script oracle_fight.gd \
    1>/dev/null 2>output/_recovery/reroute_$c.err.log
  echo "$c rc=$? events=$(python -X utf8 -c "import json;print(json.load(open('output/oracle/fights/$c/events.json',encoding='utf-8'))['event_count'])" 2>/dev/null)"
done
python -X utf8 output/_recovery/_gate_lift.py revert

echo "=== ③ 夹具再生 ==="
python -X utf8 tools/gen_fixture_from_lineup.py --lineup-out output/oracle/align/lineups --batch-out gd_core_test/oracle_align_cases.json 2>&1 | tail -3

echo "=== ④ verify 全量 ==="
python -X utf8 tools/verify_oracle.py --force 2>&1 | tail -15

echo "=== ⑤ 终数 ==="
python -X utf8 -c "
import json
d=json.load(open('output/oracle/alignment.json',encoding='utf-8'))
red=[c['caseId'] for c in d['perCase'] if c['match']!='三方一致']
print('aligned:',d['aligned'],'/',d['total'],'| 红:',len(red))
print(';'.join(red[:40]))
"
