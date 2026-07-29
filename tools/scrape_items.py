"""Scrape item data from the 旅法师营地 Backpack Battles item database.

Usage:
  python tools/scrape_items.py [--start ID] [--end ID]

Fetches item data and saves to simulator/items_db_scraped.json
"""
import json
import os
import re
import time
import urllib.request
import urllib.error

BASE_URL = "https://www.iyingdi.com/tz/tool/backpackBattles/{id}?lang=zh-cn"
KNOWN_IDS = list(range(1, 260))  # Approximate range


def fetch_item(item_id):
    """Fetch one item page and extract data."""
    url = BASE_URL.format(id=item_id)
    try:
        req = urllib.request.Request(url, headers={
            "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) "
                          "AppleWebKit/537.36 (KHTML, like Gecko) "
                          "Chrome/120.0.0.0 Safari/537.36"
        })
        with urllib.request.urlopen(req, timeout=10) as resp:
            html = resp.read().decode("utf-8")
    except Exception as e:
        return None

    # Extract item name
    name = ""
    m = re.search(r'<title>(.+?)_旅法师营地</title>', html)
    if m:
        name = m.group(1).strip()

    if not name:
        return None

    data = {"id": item_id, "zh": name}

    # Category
    m = re.search(r'类别：</td><td>(.+?)</td>', html)
    if m:
        data["category"] = m.group(1).strip()

    # Price
    m = re.search(r'价格：</td><td>(\d+)</td>', html)
    if m:
        data["price"] = int(m.group(1))

    # Damage
    m = re.search(r'伤害：(\d+)-(\d+)\s*\((.+?)\)', html)
    if m:
        data["damage_min"] = int(m.group(1))
        data["damage_max"] = int(m.group(2))

    # Stamina
    m = re.search(r'耐力消耗：([\d.]+)\s*\(([\d.]+)/s\)', html)
    if m:
        data["stamina_cost"] = float(m.group(1))
        data["stamina_ps"] = float(m.group(2))

    # Hit rate
    m = re.search(r'命中率：(\d+)%', html)
    if m:
        data["hit_rate"] = int(m.group(1))

    # Cooldown
    m = re.search(r'冷却：([\d.]+)s', html)
    if m:
        data["cooldown"] = float(m.group(1))

    return data


def main():
    import sys
    start_id = int(sys.argv[1]) if len(sys.argv) > 1 else 1
    end_id = int(sys.argv[2]) if len(sys.argv) > 2 else max(KNOWN_IDS)

    results = []
    for iid in range(start_id, end_id + 1):
        d = fetch_item(iid)
        if d:
            results.append(d)
            print(f"  {iid}: {d['zh']} ({d.get('category','?')})")
        time.sleep(0.3)  # Rate limiting

    out_path = os.path.join(
        os.path.dirname(os.path.dirname(os.path.abspath(__file__))),
        "simulator", "items_db_scraped.json"
    )
    json.dump(results, open(out_path, "w", encoding="utf-8"),
              ensure_ascii=False, indent=2)
    print(f"\nFetched {len(results)} items → {out_path}")


if __name__ == "__main__":
    main()
