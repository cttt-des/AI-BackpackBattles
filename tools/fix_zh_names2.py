# -*- coding: utf-8 -*-
"""补齐 199 个未翻译物品的中文名（英文名直译 + 游戏机制 + 社区常用名）。"""
import json

DB = 'assets/battle_items.json'
OV = 'assets/zh_override.json'

TR = {
 'Healing Herbs':'草药','Customer Card':'顾客卡','Amulet of Feasting':'盛宴护符',
 'Amulet of Agility':'敏捷护符','Hungry Blade':'饥饿之刃','Leather Helm':'皮制头盔',
 'Stone Skin Potion':'石肤药水','Unstable Recombobulator':'不稳定重组器','Snowman':'雪人',
 'Claws of Attack':'攻击之爪','Platin Customer Card':'白金顾客卡','Sandbag':'沙袋',
 'Box of Prosperity':'繁荣之箱','Rib Saw Blade':'肋骨锯刃','Shield of Valor':'勇气之盾',
 'Pineapple':'菠萝','Jynx torquilla':'鹃头蜂虎','Strong Stone Skin Potion':'强力石肤药水',
 'Manathirst':'嗜蓝之刃','Spectral Dagger':'幽魂匕首','Pandamonium':'熊猫闹剧',
 'Evil Cap':'邪恶帽','Stone Gloves':'石头手套','Fanfare':'号角',
 'Protective Purse':'防护钱包','Fancy Fencing Rapier':'花式击剑细剑','Crown':'王冠',
 'Wolpertinger':'鹿角翼兔','Rainbow Orb':'彩虹宝珠','Heart of Darkness':'黑暗之心',
 'Prismatic Sword':'棱彩之剑','Winged Boots':'翼靴','Paradise Birb':'天堂小鸟',
 'Random Loadout Bag':'随机装备包','Star of Courage':'勇气之星','Twine Badge':'麻绳徽章',
 'Artifact Stone Cold':'寒冰神器石','Vampiric Scythe':'吸血镰刀','Villain Sword':'反派之剑',
 'Skull':'头骨','Artifact Stone Heat':'烈焰神器石','Gingerbread Man':'姜饼人',
 'Dancing Dragon':'舞龙','Stable Recombobulator':'稳定重组器','Artifact Stone Death':'死亡神器石',
 'Ghost':'幽灵','Time Dilator':'时间膨胀器','Little Mimic':'小宝箱怪',
 'Bomb':'炸弹','Repeater':'连发弩','Thorn Shortbow':'荆棘短弓',
 'Lucky Shortbow':'幸运短弓','Poison Shortbow':'剧毒短弓','Carrot Goobert':'胡萝卜黏黏',
 'Thorn Bow':'荆棘弓','Lucky Bow':'幸运弓','Snowmaster':'雪之大师',
 'Vampiric Collar':'吸血项圈','Magic Collar':'魔法项圈','Holy Collar':'神圣项圈',
 'Rainbow Goobert Ranger':'彩虹游侠黏黏','Piercing Arrow':'贯穿箭','Yggdrasil Leaf':'世界树之叶',
 'Fly Agaric':'毒蝇伞','The Lovers':'恋人','Ace of Spades':'黑桃A',
 'Reverse':'反转','White-Eyes Blue Dragon':'青眼白龙','Joker':'小丑',
 'Darkest Lotus':'至暗之莲','Poison Goobert':'剧毒黏黏','Staff of Unhealing':'不可治愈之杖',
 'Poison Frog':'剧毒青蛙','Rainbow Goobert':'彩虹黏黏','Cursed Hair Comb':'诅咒发梳',
 'Mr Struggles':'挣扎先生','Mrs Struggles':'挣扎女士','Miss Fortune':'噩运小姐',
 'Portable Altar':'便携祭坛','Burning Sword':'燃烧之剑','Burning Blade':'燃烧之刃',
 'Chili Goobert':'辣椒黏黏','Obsidian Dragon':'黑曜石龙','Molten Greatsword':'熔岩巨剑',
 'Fire Shelly':'火焰贝壳','Rainbow Goobert Pyromancer':'彩虹火法黏黏','Friendly Fire':'友军之火',
 'Frozen Flame':'冻结之焰','Spell Scroll Frostbolt':'寒冰箭卷轴','Frostbite':'冻伤',
 'Berserker Bag':'狂战士背包','Forging Hammer':'锻造锤','Dragonscale Armor':'龙鳞护甲',
 'Dragon Claws':'龙爪','Dragonskin Boots':'龙皮靴','Busted Blade':'破损之刃',
 'Rainbow Goobert Berserker':'彩虹狂战黏黏','Deer Totem':'鹿图腾',
 'Armored Courage Puppy':'装甲勇气狼崽','Armored Wisdom Puppy':'装甲智慧狼崽',
 'Armored Power Puppy':'装甲力量狼崽','Badger Rune':'獾符文','Elephant Rune':'象符文',
 'Unidentified Skill':'未鉴定技能','Spicy Banana':'辣香蕉','Smelly Barrier':'臭气屏障',
 'Piggy Pinata':'存钱罐皮纳塔','Investment Opportunity':'投资机会','Slime Time':'黏黏时刻',
 'Smithing For Dummies':'锻造入门','Knife to Meet You':'刀光剑影','Extra Bags':'额外背包',
 'Shielded':'持盾','Thornburst':'荆棘爆发','Heavy Drinking':'痛饮',
 'Mana Mastery':'法力精通','Blood Manipulation':'鲜血支配','Echoing Battlecry':'回响战嚎',
 'Enchanted Weapons':'附魔武器','No Rush Please':'别急','Fortunas Kiss':'命运之吻',
 'Buy the Holy Light':'购买圣光','Time Melting':'时间融化','Full Body Protection':'全身防护',
 'Heart of the Cards':'卡组之心','Everburning':'永恒燃烧','Arcane Intellect':'奥术智慧',
 'Ultima':'究极术','Dual Wielding':'双持','White Bishop':'白象',
 'White King':'白王','Wand':'魔杖','Book of Basics':'基础之书',
 'Spell Scroll Ice':'冰霜卷轴','Spell Scroll Nature':'自然卷轴','Spell Scroll Light':'光之卷轴',
 'Spell Scroll Dark':'暗之卷轴','Book of Nature':'自然之书','Book of Ice':'寒冰之书',
 'Book of Ice New':'寒冰之书·新','Magic Mirror':'魔法镜','Light Flower':'光之花',
 'Devouring Sphere':'吞噬之球','Cat Spirit':'猫灵','Owl Spirit':'猫头鹰之灵',
 'Badger Spirit':'獾灵','Prismatic Wand':'棱彩魔杖','Rainbow Goobert Mage':'彩虹法师黏黏',
 'Shiny Mantle':'闪亮披风','Evil Hat':'邪恶礼帽','Boomerang':'回旋镖',
 'Piggy of Riches':'财富存钱罐','Big Bloodthorne':'大血棘','Broccoli':'西兰花',
 'Lootbox':'战利品箱','Rainbow Goobert Adventurer':'彩虹冒险者黏黏','Scissorswords':'剪刀剑',
 'Long Spear':'长矛','Mercury Elemental':'水银元素','Engineer Box':'工程师工具箱',
 'Engineer Bag 2':'工程师背包II','Resistor':'电阻器','Slice of Bread':'面包片',
 'Slice of Toast':'吐司片','Rainbow Goobert Engineer':'彩虹工程师黏黏','Electric Torch':'电击火把',
 'Robodog':'机器狗','Bazooka':'火箭筒','Poison Grenade':'剧毒手雷',
 'Spring Loader':'弹簧装填器','Eat-o-matic':'自动进食机','Laboratory':'实验室',
 'Thors Hammer':'雷神之锤','Automanaton':'自动傀儡','Mananana':'魔力香蕉',
 'Critical Poison':'暴击剧毒','Burning Spikes':'燃烧尖刺','Spin to Win':'旋转取胜',
 'Energy Conversion':'能量转换','Bewitchment':'魅惑','Chess Master':'棋圣',
 'Speak with Animals':'与兽交谈','Seal the Deal':'一锤定音','King of the Bling':'闪耀之王',
 'Molten Spear2':'熔岩长矛II','Phoenix2':'凤凰II','Whetstone2':'磨刀石II',
 'Whetstone3':'磨刀石III','Steel Dragon':'钢铁龙','Superior Ring':'高级戒指',
 'Broccotree':'西兰花树','Cupcake Dragon':'纸杯蛋糕龙','Wand of Dissonance':'失调魔杖',
 'Pine Protector':'松树守卫','Onion Cutter':'洋葱切割器','Pot':'锅',
 'Furcifer Prime':'变色龙宗师','Angel Crystal':'天使水晶','Lightning Potion':'闪电药水',
}

db = json.load(open(DB, encoding='utf-8'))
items = db.get('items', db)
ov = json.load(open(OV, encoding='utf-8'))

applied = 0
missing = []
for k, zh in TR.items():
    if k in items:
        items[k]['zh'] = zh
        ov[k] = zh
        applied += 1
    else:
        missing.append(k)

# 中文名唯一性检查
zh_map = {}
dup = []
for k, v in items.items():
    z = v.get('zh', '')
    if z:
        zh_map.setdefault(z, []).append(k)
for z, ks in zh_map.items():
    if len(ks) > 1:
        dup.append((z, ks))

json.dump(db, open(DB, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
json.dump(ov, open(OV, 'w', encoding='utf-8'), ensure_ascii=False, indent=1)
print(f'补齐 {applied}/{len(TR)} | 未找到: {missing}')
print('override 现共', len(ov), '条')
print('中文名重复项:', len(dup))
for z, ks in dup[:20]:
    print('  %s: %s' % (z, ks))
