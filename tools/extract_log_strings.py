# -*- coding: utf-8 -*-
"""extract_log_strings.py — 提取战斗日志模板（LOG_* 翻译）生成 assets/log_strings.json

原理：
- 战斗日志行文本由 CombatEvent.asText() 生成：key = "LOG_" + EventType 名 + 变体
  （Gain_/Lose_/USE_BUFF/NULLIFY_BUFF/RESIST_DEBUFF/PROTECT_*/REFLECT_* + _SELF/_TEMP/_OPPONENT），
  文本 = Util.tra(key).format({origin/actor/target/amount/buff/debuff/duration/...})
- LOG_* 文本存于 Interface.*.translation（PHashTranslation）。key 只存 hash，
  GDRE 反编译的 Interface.csv 行 key 为 <!MissingKey:N:...> 哨兵 → 需按 key hash
  主动查询。
- 本脚本暴力标定 Interface 表的 hash_table 起点/大小，按 Godot String::hash()
  （djb2: h=5381; h = h*33 + c）枚举全部候选 key，命中后取 en/zh 文本。

用法: python tools/extract_log_strings.py
输出: assets/log_strings.json {"LOG_xxx": {"en": ..., "zh": ...}, ...}
"""
import json
import os
import struct
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
from smaz_dict import smaz_decompress  # noqa: E402

TR_EN = "C:/tmp/bb_tr/Sheets/CSV/Interface.en.translation"
TR_ZH = "C:/tmp/bb_tr/Sheets/CSV/Interface.zh_Hans_CN.translation"
OUT = os.path.join(ROOT, "assets", "log_strings.json")


def parse_generic(path):
    """暴力标定 hash_table 起点/大小，返回 {str_hash: text}；取恢复成功率最高的参数"""
    d = open(path, "rb").read()
    best = ({}, 0, 0, 0)
    primes = [n for n in range(293, 1600)
              if all(n % p for p in range(2, int(n ** 0.5) + 1))]
    for ht_size in primes:
        for ht_off in range(180, 500, 4):
            o = ht_off + ht_size * 4
            if o + 8 > len(d):
                continue
            size, func = struct.unpack('<iI', d[o:o + 8])
            if not (0 < size <= 4000) or func > 5000:
                continue
            o += 8
            elems = []
            ok = True
            for _ in range(size):
                if o + 16 > len(d):
                    ok = False
                    break
                key, soff, cs, us = struct.unpack('<IIII', d[o:o + 16])
                if cs > len(d):
                    ok = False
                    break
                elems.append((key, soff, cs, us))
                o += 16
            if not ok or len(elems) < 8:
                continue
            S = o
            got = {}
            for key, soff, cs, us in elems:
                try:
                    s = smaz_decompress(d[S + soff:S + soff + cs]).decode('utf-8')
                    if s:
                        got[key] = s
                except Exception:
                    pass
            if len(got) > len(best[0]):
                best = (got, ht_off, ht_size, len(elems))
                if len(got) >= len(elems) - 2:   # 几乎全恢复，提前结束
                    break
        else:
            continue
        break
    return best


def godot_hash(s: str) -> int:
    h = 5381
    for ch in s:
        h = (h * 33 + ord(ch)) & 0xFFFFFFFF
    return h


def main():
    en, en_off, en_size, en_n = parse_generic(TR_EN)
    zh, zh_off, zh_size, zh_n = parse_generic(TR_ZH)
    print(f"Interface.en: {len(en)}/{en_n} 恢复 (HT_OFF={en_off}, HT_SIZE={en_size})")
    print(f"Interface.zh: {len(zh)}/{zh_n} 恢复 (HT_OFF={zh_off}, HT_SIZE={zh_size})")
    if not en:
        raise SystemExit("Interface.en 解析失败")

    # ---- 枚举 CombatEvent.asText() 的全部候选 key（CombatEvent.gd:90-190 真值） ----
    type_keys = [
        "Activation", "DealDamage", "CriticalDamage", "MissedAttack", "TakeDamage",
        "LoseHealth", "AttackSpeed", "InvulnerableStart", "InvulnerableEnd",
        "Stun", "StunResisted", "CriticalResisted", "Health", "Stamina",
        "DrainStamina", "OutofStamina", "DamageBuff", "DamReduction", "DamIncrease",
        "TemporaryMaxHealth", "TemporaryMaxStamina", "BattleRageStart",
        "BattleRageEnd", "Reincarnate", "CooldownAdvance", "Unhealing", "Fatigue",
        "Block", "Lucky", "Regeneration", "Vampirism", "Spikes", "Mana",
        "Empower", "Heat", "Poison", "Blind", "Cold", "Win", "Loss",
    ]
    buffs = [t for t in type_keys if t not in (
        "Activation", "DealDamage", "CriticalDamage", "MissedAttack",
        "TakeDamage", "LoseHealth", "AttackSpeed", "InvulnerableStart",
        "InvulnerableEnd", "Stun", "StunResisted", "CriticalResisted",
        "Health", "Stamina", "DrainStamina", "OutofStamina",
        "TemporaryMaxHealth", "TemporaryMaxStamina", "BattleRageStart",
        "BattleRageEnd", "Reincarnate", "CooldownAdvance", "Win", "Loss")]
    debuffs = ["Stun", "Poison", "Blind", "Cold"]        # Game.isDebuff 真值

    keys = {"LOG_PLAYER", "LOG_OPPONENT"}
    for t in type_keys:
        keys.add("LOG_" + t)
        keys.add("LOG_" + t + "_TYPED")
        keys.add("LOG_" + t + "_TEMP")
    for t in buffs + debuffs:
        for base in ("GAIN_", "LOSE_"):
            k = "LOG_" + base + ("BUFF" if t in buffs else "DEBUFF")
            keys |= {k, k + "_SELF", k + "_TEMP", k + "_OPPONENT"}
        keys.add("LOG_REFLECT_" + ("BUFF" if t in buffs else "DEBUFF"))
        keys.add("LOG_REFLECT_RESIST")
    keys |= {"LOG_USE_BUFF", "LOG_NULLIFY_BUFF", "LOG_RESIST_DEBUFF",
             "LOG_PROTECT_BUFF", "LOG_PROTECT_DEBUFF", "LOG_BuffTimeout"}

    out = {}
    for k in sorted(keys):
        h = godot_hash(k)
        e, z = en.get(h), zh.get(h)
        if e or z:
            out[k] = {"en": e or "", "zh": z or ""}

    print(f"候选 key {len(keys)}，命中 {len(out)}")
    for k in ("LOG_DealDamage", "LOG_ATTACK" if "LOG_ATTACK" in out else "LOG_Activation",
              "LOG_GAIN_BUFF", "LOG_LOSE_DEBUFF", "LOG_PLAYER", "LOG_Fatigue"):
        if k in out:
            print(f"  {k}: en={out[k]['en']!r} zh={out[k]['zh']!r}")
    with open(OUT, "w", encoding="utf-8") as f:
        json.dump(out, f, ensure_ascii=False, indent=1, sort_keys=True)
    print(f"已写出 {OUT}")


if __name__ == "__main__":
    main()
