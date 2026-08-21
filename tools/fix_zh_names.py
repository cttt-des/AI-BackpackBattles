# -*- coding: utf-8 -*-
"""修正错位中文名（比例映射错误产物）。基于英文名直译 + override 词汇模式 + 游戏机制。"""
import json

DB = 'assets/battle_items.json'
OV = 'assets/zh_override.json'

FIX = {
 'Stone':'石头','Walrus Tusk':'海象长牙','Shovel':'铁锹','Shelly':'贝壳',
 'Magic Staff':'魔法法杖','Holdall':'大旅行包','Eggscalibur':'蛋神剑','Magic Torch':'魔法火把',
 'Stone Helm':'石制头盔','Djinn Lamp':'神灯','Darksaber':'黑暗之剑','Thornbloom':'荆棘花剑',
 'Rainbow Badge':'彩虹徽章','Pumpkin':'南瓜','Cubert':'方块仔','Pop':'爆米花',
 'Cthulhu':'克苏鲁','Snowcake':'雪饼','Ranger Bag':'游侠背包','Lucky Piggy':'幸运存钱罐',
 'Critwood Staff':'暴击木杖','Poison Ivy':'剧毒常春藤','Squirrel Archer':'松鼠射手','Rat Chef':'老鼠厨师',
 'Deck of Cards':'牌堆','The Fool':'愚者','Holo Fire Lizard':'全息火焰蜥蜴','Ruby Chonk':'红宝石胖龙',
 'Doom Cap':'厄运菇','Flame':'火焰','Chili Pepper':'红辣椒','Draconic Orb':'龙之宝珠',
 'Sun Armor':'太阳护甲','Sun Shield':'太阳之盾','Molten Dagger':'熔岩匕首','Flame Whip':'火焰鞭',
 'Dark Lantern':'黑暗提灯','Ice Armor':'寒冰护甲','Frozen Buckler':'冰冻圆盾','Axe':'斧头',
 'Spiked Collar':'尖刺项圈','Spiked Staff':'尖刺法杖','Wolf Emblem':'狼徽章','Shaman Mask':'萨满面具',
 'Courage Puppy':'勇气狼崽','Wisdom Puppy':'智慧狼崽','Power Puppy':'力量狼崽','Hawk Rune':'猎鹰符文',
 'Tiger Rune':'猛虎符文','Just Stats':'面板加成','Goobling':'黏宝宝','Uniquely Unique':'独一无二',
 'Dig Deeper':'深挖','Girl Power':'女孩力量','Double Rainbow':'双重彩虹','False Life':'虚假生命',
 'More Stats':'更多加成','Bagtacular':'背包盛宴','Extra Angy':'怒上加怒','Dragon Set':'巨龙套装',
 'Level Up':'升级','Scholar Bag':'学者背包','Puzzlebox':'谜题盒','Chess Board':'棋盘',
 'White Pawn':'白兵','Black Pawn':'黑兵','White Knight':'白马','Black Knight':'黑马',
 'Black Bishop':'黑象','Black Rook':'黑车','White Queen':'白后','Black Queen':'黑后',
 'Black King':'黑王','Cupcake':'纸杯蛋糕','Ice Flower':'冰花','Null Blade':'虚无之刃',
 'Cupcake Goobert':'纸杯蛋糕黏黏','Mage Hat':'法师帽','Spirit Bells':'灵魂铃铛','Twine':'麻绳',
 'Rope':'绳索','Employee Uniform':'员工制服','Jynx Staff':'厄运法杖','Scale':'天平',
 'Mecha Bat':'机械蝙蝠','Lightning Staff':'闪电法杖','Con-Trap-Tron':'陷阱机器人','Thunder Drake':'雷龙',
 'Magitecc Armor':'魔法科技护甲','Arcane Boots':'奥术之靴','Gigawatz':'吉瓦兹','Perpetuum Mobile':'永动机',
 'Hogus Bogus':'霍格斯博格斯','Inner Power':'内在力量','Wisp':'幽光',
}

db = json.load(open(DB, encoding='utf-8'))
items = db.get('items', db)
ov = json.load(open(OV, encoding='utf-8'))

applied = 0
missing = []
for k, zh in FIX.items():
    if k in items:
        items[k]['zh'] = zh
        ov[k] = zh          # 并入人工修正表（长期锚点）
        applied += 1
    else:
        missing.append(k)

json.dump(db, open(DB, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
json.dump(ov, open(OV, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
print(f'修正 {applied}/{len(FIX)} 条 | 未找到: {missing}')
print('override 现共', len(ov), '条')
