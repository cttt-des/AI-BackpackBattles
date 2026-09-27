# =============================================================================
# LineupFixture.gd — 真实阵容夹具（由 tools/gen_lineup_fixture.py 生成，勿手改）
# =============================================================================
# 数据来源：assets/battle_items.json（物品静态数据 + tscn 网格）
#           lineups/*.json（真实阵容摆盘）
#           gd_core/CoreConst.gd（Type/Tag/Rarity/Classes 枚举，唯一真值源）
#           extracted/Items/*.tscn（socket 数 = GemSocket 实例个数）
#
# 几何约定与推导过程见 tools/gen_lineup_fixture.py 文件头；GDScript 侧
# 向量一律 Vector2(x=col, y=row)，与 CoreItem/CoreGrid 一致。
#
# 覆盖 16 个物品、8 个阵容。
# =============================================================================
extends Reference
class_name LineupFixture


const ITEMS := {
	"Amulet of the Wild": {
		"name": "Amulet of the Wild",
		"identifier": "Amulet of the Wild",
		"minDam": 0,
		"maxDam": 0,
		"cd": 5.0,
		"extraCds": [],
		"accuracy": 100.0,
		"staminaCost": 0.0,
		"block": 0,
		"price": 6,
		"rarity": 1,
		"classes": 0,
		"canActivate": true,
		"chance": 0.0,
		"chance2": 0.0,
		"types": [10, 26],
		"tags": 0,
		"params": [4.0, 50.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
		"namedParams": {
			"spikes": 4.0,
			"spikedam": 50.0
		},
		"sockets": 1
	},
	"Banana": {
		"name": "Banana",
		"identifier": "Banana",
		"minDam": 0,
		"maxDam": 0,
		"cd": 5.0,
		"extraCds": [],
		"accuracy": 100.0,
		"staminaCost": 0.0,
		"block": 0,
		"price": 3,
		"rarity": 0,
		"classes": 127,
		"canActivate": true,
		"chance": 0.0,
		"chance2": 0.0,
		"types": [2, 26],
		"tags": 0,
		"params": [4.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
		"namedParams": {
			"heal": 4.0
		},
		"sockets": 1
	},
	"Blood Amulet": {
		"name": "Blood Amulet",
		"identifier": "Blood Amulet",
		"minDam": 0,
		"maxDam": 0,
		"cd": 0.0,
		"extraCds": [],
		"accuracy": 100.0,
		"staminaCost": 0.0,
		"block": 0,
		"price": 8,
		"rarity": 3,
		"classes": 127,
		"canActivate": true,
		"chance": 0.0,
		"chance2": 0.0,
		"types": [10, 24],
		"tags": 0,
		"params": [2.0, 20.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
		"namedParams": {
			"vampirism": 2.0,
			"maxhealth": 20.0
		},
		"sockets": 1
	},
	"Chipped Ruby": {
		"name": "Chipped Ruby",
		"identifier": "Chipped Ruby",
		"minDam": 0,
		"maxDam": 0,
		"cd": 5.0,
		"extraCds": [],
		"accuracy": 100.0,
		"staminaCost": 0.0,
		"block": 0,
		"price": 1,
		"rarity": 0,
		"classes": 0,
		"canActivate": true,
		"chance": 0.0,
		"chance2": 0.0,
		"types": [13],
		"tags": 1,
		"params": [7.0, 10.0, 4.0, 150.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
		"namedParams": {
			"lifesteal_weapon": 7.0,
			"healamp": 10.0,
			"flatsteal": 4.0,
			"lifesteal_factor": 150.0
		},
		"sockets": 0
	},
	"Cursed Dagger": {
		"name": "Cursed Dagger",
		"identifier": "Cursed Dagger",
		"minDam": 4,
		"maxDam": 7,
		"cd": 2.8,
		"extraCds": [],
		"accuracy": 95.0,
		"staminaCost": 0.0,
		"block": 0,
		"price": 10,
		"rarity": 5,
		"classes": 2,
		"canActivate": true,
		"chance": 1.0,
		"chance2": 0.0,
		"types": [4, 19, 25],
		"tags": 0,
		"params": [2.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
		"namedParams": {
			"debuffs": 2.0,
			"accuracy": 1.0
		},
		"sockets": 2
	},
	"Dagger": {
		"name": "Dagger",
		"identifier": "Dagger",
		"minDam": 2,
		"maxDam": 5,
		"cd": 3.5,
		"extraCds": [],
		"accuracy": 95.0,
		"staminaCost": 0.0,
		"block": 0,
		"price": 4,
		"rarity": 1,
		"classes": 127,
		"canActivate": true,
		"chance": 0.0,
		"chance2": 0.0,
		"types": [4, 19],
		"tags": 0,
		"params": [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
		"namedParams": {},
		"sockets": 2
	},
	"Flame Badge": {
		"name": "Flame Badge",
		"identifier": "Flame Badge",
		"minDam": 0,
		"maxDam": 0,
		"cd": 0.0,
		"extraCds": [],
		"accuracy": 100.0,
		"staminaCost": 0.0,
		"block": 0,
		"price": 5,
		"rarity": 5,
		"classes": 127,
		"canActivate": true,
		"chance": 0.0,
		"chance2": 0.0,
		"types": [10],
		"tags": 0,
		"params": [6.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
		"namedParams": {
			"heat": 6.0
		},
		"sockets": 1
	},
	"Garlic": {
		"name": "Garlic",
		"identifier": "Garlic",
		"minDam": 0,
		"maxDam": 0,
		"cd": 4.0,
		"extraCds": [],
		"accuracy": 100.0,
		"staminaCost": 0.0,
		"block": 3,
		"price": 2,
		"rarity": 0,
		"classes": 127,
		"canActivate": true,
		"chance": 30.0,
		"chance2": 0.0,
		"types": [2, 26],
		"tags": 0,
		"params": [1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
		"namedParams": {},
		"sockets": 1
	},
	"Greatsword": {
		"name": "Greatsword",
		"identifier": "Greatsword",
		"minDam": 40,
		"maxDam": 50,
		"cd": 5.0,
		"extraCds": [],
		"accuracy": 90.0,
		"staminaCost": 5.0,
		"block": 0,
		"price": 14,
		"rarity": 4,
		"classes": 127,
		"canActivate": true,
		"chance": 0.0,
		"chance2": 0.0,
		"types": [4, 19],
		"tags": 0,
		"params": [5.0, 2.0, 2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
		"namedParams": {
			"empowert": 5.0,
			"stamina": 2.0,
			"cd": 2.0
		},
		"sockets": 5
	},
	"Health Potion": {
		"name": "Health Potion",
		"identifier": "Health Potion",
		"minDam": 0,
		"maxDam": 0,
		"cd": 0.0,
		"extraCds": [],
		"accuracy": 100.0,
		"staminaCost": 0.0,
		"block": 0,
		"price": 4,
		"rarity": 1,
		"classes": 127,
		"canActivate": true,
		"chance": 0.0,
		"chance2": 0.0,
		"types": [11],
		"tags": 0,
		"params": [50.0, 12.0, 4.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
		"namedParams": {
			"heal": 12.0
		},
		"sockets": 1
	},
	"Leather Armor": {
		"name": "Leather Armor",
		"identifier": "Leather Armor",
		"minDam": 0,
		"maxDam": 0,
		"cd": 0.0,
		"extraCds": [],
		"accuracy": 100.0,
		"staminaCost": 0.0,
		"block": 45,
		"price": 7,
		"rarity": 1,
		"classes": 127,
		"canActivate": true,
		"chance": 0.0,
		"chance2": 0.0,
		"types": [6],
		"tags": 0,
		"params": [3.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
		"namedParams": {
			"resist": 3.0
		},
		"sockets": 3
	},
	"Magic Badge": {
		"name": "Magic Badge",
		"identifier": "Magic Badge",
		"minDam": 0,
		"maxDam": 0,
		"cd": 0.0,
		"extraCds": [],
		"accuracy": 100.0,
		"staminaCost": 0.0,
		"block": 0,
		"price": 5,
		"rarity": 5,
		"classes": 127,
		"canActivate": true,
		"chance": 30.0,
		"chance2": 0.0,
		"types": [10, 23],
		"tags": 0,
		"params": [5.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
		"namedParams": {
			"mana": 5.0
		},
		"sockets": 1
	},
	"Poison Bow": {
		"name": "Poison Bow",
		"identifier": "Poison Bow",
		"minDam": 11,
		"maxDam": 14,
		"cd": 3.0,
		"extraCds": [],
		"accuracy": 85.0,
		"staminaCost": 1.2,
		"block": 0,
		"price": 13,
		"rarity": 3,
		"classes": 0,
		"canActivate": true,
		"chance": 0.0,
		"chance2": 0.0,
		"types": [4, 20, 26],
		"tags": 512,
		"params": [5.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
		"namedParams": {
			"damforpoison": 5.0
		},
		"sockets": 2
	},
	"Stone": {
		"name": "Stone",
		"identifier": "Stone",
		"minDam": 2,
		"maxDam": 4,
		"cd": 2.5,
		"extraCds": [],
		"accuracy": 70.0,
		"staminaCost": 0.0,
		"block": 0,
		"price": 1,
		"rarity": 0,
		"classes": 127,
		"canActivate": true,
		"chance": 0.0,
		"chance2": 0.0,
		"types": [4, 20, 26],
		"tags": 2,
		"params": [4.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
		"namedParams": {
			"blockremoval": 4.0
		},
		"sockets": 1
	},
	"Stone Armor": {
		"name": "Stone Armor",
		"identifier": "Stone Armor",
		"minDam": 0,
		"maxDam": 0,
		"cd": 4.0,
		"extraCds": [],
		"accuracy": 100.0,
		"staminaCost": 0.0,
		"block": 120,
		"price": 13,
		"rarity": 3,
		"classes": 0,
		"canActivate": true,
		"chance": 0.0,
		"chance2": 0.0,
		"types": [6],
		"tags": 0,
		"params": [1.0, 2.0, 50.0, 20.0, 40.0, 0.0, 0.0, 0.0, 0.0, 0.0],
		"namedParams": {
			"spikes": 1.0,
			"empower": 2.0,
			"healtht": 50.0,
			"staminacost": 20.0,
			"blockperhealth": 40.0
		},
		"sockets": 3
	},
	"Vampiric Potion": {
		"name": "Vampiric Potion",
		"identifier": "Vampiric Potion",
		"minDam": 0,
		"maxDam": 0,
		"cd": 0.0,
		"extraCds": [],
		"accuracy": 100.0,
		"staminaCost": 0.0,
		"block": 0,
		"price": 8,
		"rarity": 3,
		"classes": 0,
		"canActivate": true,
		"chance": 0.0,
		"chance2": 0.0,
		"types": [11, 24],
		"tags": 1,
		"params": [80.0, 3.0, 15.0, 100.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0],
		"namedParams": {
			"healtht": 80.0,
			"vampirism": 3.0,
			"dam": 15.0,
			"lifesteal": 100.0
		},
		"sockets": 1
	},
}

const LINEUPS := {
	"lineup_armor_wall": {
		"name": "Armor Wall",
		"class": 5,
		"round": 1,
		"health": 25.0,
		"stamina": 5.0,
		"regen": 1.0,
		"items": [
			{
						"row": 0,
						"col": 0,
						"rot": 0,
						"occupied": [[0, 0], [0, 1], [1, 0], [1, 1], [2, 0], [2, 1]],
						"collision": [[0, 0], [0, 1], [0, 2], [1, 0], [1, 1], [1, 2]],
						"affected": {},
						"key": "Stone Armor",
						"script": "res://gd_core_items/Exclusive/StoneArmor.gd",
						"bagslot": false,
						"storage": false,
						"gems": []
					},
			{
						"row": 0,
						"col": 2,
						"rot": 0,
						"occupied": [[0, 2], [0, 3], [1, 2], [1, 3], [2, 2], [2, 3], [3, 2]],
						"collision": [[2, 0], [2, 1], [2, 2], [2, 3], [3, 0], [3, 1], [3, 2]],
						"affected": {},
						"key": "Greatsword",
						"script": "res://gd_core_items/Greatsword.gd",
						"bagslot": false,
						"storage": false,
						"gems": []
					},
			{
						"row": 0,
						"col": 4,
						"rot": 0,
						"occupied": [[0, 4], [1, 4]],
						"collision": [[4, 0], [4, 1]],
						"affected": {},
						"key": "Health Potion",
						"script": "res://gd_core_items/HealthPotion.gd",
						"bagslot": false,
						"storage": false,
						"gems": []
					},
			{
						"row": 0,
						"col": 5,
						"rot": 0,
						"occupied": [[0, 5], [1, 5]],
						"collision": [[5, 0], [5, 1]],
						"affected": {
							0: [[4, 0], [4, 1], [5, -1], [5, 2], [6, 0], [6, 1]]
						},
						"key": "Garlic",
						"script": "res://gd_core_items/Garlic.gd",
						"bagslot": false,
						"storage": false,
						"gems": []
					},
			{
						"row": 0,
						"col": 6,
						"rot": 0,
						"occupied": [[0, 6], [1, 6], [1, 7]],
						"collision": [[6, 0], [6, 1], [7, 1]],
						"affected": {
							0: [[5, 0], [5, 1], [6, -1], [6, 2], [7, 0], [7, 2], [8, 1]]
						},
						"key": "Banana",
						"script": "res://gd_core_items/Banana.gd",
						"bagslot": false,
						"storage": false,
						"gems": []
					},
		],
	},
	"lineup_cursed_reaper": {
		"name": "Cursed Reaper",
		"class": 1,
		"round": 1,
		"health": 25.0,
		"stamina": 5.0,
		"regen": 1.0,
		"items": [
			{
						"row": 0,
						"col": 0,
						"rot": 0,
						"occupied": [[0, 0], [1, 0]],
						"collision": [[0, 0], [0, 1]],
						"affected": {
							0: [[0, -1], [1, -1], [1, 0], [1, 1]]
						},
						"key": "Cursed Dagger",
						"script": "res://gd_core_items/CursedDagger.gd",
						"bagslot": false,
						"storage": false,
						"gems": []
					},
			{
						"row": 0,
						"col": 1,
						"rot": 0,
						"occupied": [[0, 1], [1, 1]],
						"collision": [[1, 0], [1, 1]],
						"affected": {
							0: [[1, -1], [2, -1], [2, 0], [2, 1]]
						},
						"key": "Cursed Dagger",
						"script": "res://gd_core_items/CursedDagger.gd",
						"bagslot": false,
						"storage": false,
						"gems": []
					},
			{
						"row": 0,
						"col": 2,
						"rot": 0,
						"occupied": [[0, 2], [1, 2]],
						"collision": [[2, 0], [2, 1]],
						"affected": {},
						"key": "Vampiric Potion",
						"script": "res://gd_core_items/Exclusive/VampiricPotion.gd",
						"bagslot": false,
						"storage": false,
						"gems": []
					},
			{
						"row": 0,
						"col": 3,
						"rot": 0,
						"occupied": [[0, 3]],
						"collision": [[3, 0]],
						"affected": {},
						"key": "Blood Amulet",
						"script": "res://gd_core_items/BloodAmulet.gd",
						"bagslot": false,
						"storage": false,
						"gems": []
					},
			{
						"row": 0,
						"col": 4,
						"rot": 0,
						"occupied": [[0, 4], [1, 4]],
						"collision": [[4, 0], [4, 1]],
						"affected": {
							0: [[3, 0], [3, 1], [4, -1], [4, 2], [5, 0], [5, 1]]
						},
						"key": "Garlic",
						"script": "res://gd_core_items/Garlic.gd",
						"bagslot": false,
						"storage": false,
						"gems": []
					},
		],
	},
	"lineup_dagger_swarm": {
		"name": "Dagger Swarm",
		"class": 5,
		"round": 1,
		"health": 25.0,
		"stamina": 5.0,
		"regen": 1.0,
		"items": [
			{
						"row": 0,
						"col": 0,
						"rot": 0,
						"occupied": [[0, 0], [1, 0]],
						"collision": [[0, 0], [0, 1]],
						"affected": {},
						"key": "Dagger",
						"script": "res://gd_core_items/Dagger.gd",
						"bagslot": false,
						"storage": false,
						"gems": []
					},
			{
						"row": 0,
						"col": 1,
						"rot": 0,
						"occupied": [[0, 1], [1, 1]],
						"collision": [[1, 0], [1, 1]],
						"affected": {},
						"key": "Dagger",
						"script": "res://gd_core_items/Dagger.gd",
						"bagslot": false,
						"storage": false,
						"gems": []
					},
			{
						"row": 0,
						"col": 2,
						"rot": 0,
						"occupied": [[0, 2], [1, 2]],
						"collision": [[2, 0], [2, 1]],
						"affected": {},
						"key": "Dagger",
						"script": "res://gd_core_items/Dagger.gd",
						"bagslot": false,
						"storage": false,
						"gems": []
					},
			{
						"row": 0,
						"col": 3,
						"rot": 0,
						"occupied": [[0, 3], [1, 3]],
						"collision": [[3, 0], [3, 1]],
						"affected": {
							0: [[2, 0], [2, 1], [3, -1], [3, 2], [4, 0], [4, 1]]
						},
						"key": "Garlic",
						"script": "res://gd_core_items/Garlic.gd",
						"bagslot": false,
						"storage": false,
						"gems": []
					},
			{
						"row": 0,
						"col": 4,
						"rot": 0,
						"occupied": [[0, 4], [1, 4], [1, 5]],
						"collision": [[4, 0], [4, 1], [5, 1]],
						"affected": {
							0: [[3, 0], [3, 1], [4, -1], [4, 2], [5, 0], [5, 2], [6, 1]]
						},
						"key": "Banana",
						"script": "res://gd_core_items/Banana.gd",
						"bagslot": false,
						"storage": false,
						"gems": []
					},
			{
						"row": 0,
						"col": 6,
						"rot": 0,
						"occupied": [[0, 6], [1, 6]],
						"collision": [[6, 0], [6, 1]],
						"affected": {},
						"key": "Health Potion",
						"script": "res://gd_core_items/HealthPotion.gd",
						"bagslot": false,
						"storage": false,
						"gems": []
					},
		],
	},
	"lineup_gem_test": {
		"name": "gem_test",
		"class": 0,
		"round": 3,
		"health": 60.0,
		"stamina": 5.0,
		"regen": 1.0,
		"items": [
			{
						"row": 0,
						"col": 0,
						"rot": 0,
						"occupied": [[0, 0], [1, 0]],
						"collision": [[0, 0], [0, 1]],
						"affected": {
							0: [[0, -1], [1, -1], [1, 0], [1, 1]]
						},
						"key": "Cursed Dagger",
						"script": "res://gd_core_items/CursedDagger.gd",
						"bagslot": false,
						"storage": false,
						"gems": ["Chipped Ruby"],
						"gemScripts": ["res://gd_core_items/Gems/Ruby.gd"]
					},
			{
						"row": 2,
						"col": 0,
						"rot": 0,
						"occupied": [[2, 0]],
						"collision": [[0, 2]],
						"affected": {
							0: [[0, 1]]
						},
						"key": "Amulet of the Wild",
						"script": "res://gd_core_items/Exclusive/AmuletoftheWild.gd",
						"bagslot": false,
						"storage": false,
						"gems": []
					},
		],
	},
	"lineup_greatsword_tank": {
		"name": "Greatsword Tank",
		"class": 2,
		"round": 1,
		"health": 25.0,
		"stamina": 5.0,
		"regen": 1.0,
		"items": [
			{
						"row": 0,
						"col": 0,
						"rot": 0,
						"occupied": [[0, 0], [0, 1], [1, 0], [1, 1], [2, 0], [2, 1], [3, 0]],
						"collision": [[0, 0], [0, 1], [0, 2], [0, 3], [1, 0], [1, 1], [1, 2]],
						"affected": {},
						"key": "Greatsword",
						"script": "res://gd_core_items/Greatsword.gd",
						"bagslot": false,
						"storage": false,
						"gems": []
					},
			{
						"row": 0,
						"col": 2,
						"rot": 0,
						"occupied": [[0, 2], [0, 3], [1, 2], [1, 3], [2, 2], [2, 3]],
						"collision": [[2, 0], [2, 1], [2, 2], [3, 0], [3, 1], [3, 2]],
						"affected": {},
						"key": "Leather Armor",
						"script": "res://gd_core_items/LeatherArmor.gd",
						"bagslot": false,
						"storage": false,
						"gems": []
					},
			{
						"row": 0,
						"col": 4,
						"rot": 0,
						"occupied": [[0, 4]],
						"collision": [[4, 0]],
						"affected": {},
						"key": "Stone",
						"script": "res://gd_core_items/Stone.gd",
						"bagslot": false,
						"storage": false,
						"gems": []
					},
			{
						"row": 0,
						"col": 5,
						"rot": 0,
						"occupied": [[0, 5]],
						"collision": [[5, 0]],
						"affected": {},
						"key": "Stone",
						"script": "res://gd_core_items/Stone.gd",
						"bagslot": false,
						"storage": false,
						"gems": []
					},
			{
						"row": 0,
						"col": 6,
						"rot": 0,
						"occupied": [[0, 6], [1, 6]],
						"collision": [[6, 0], [6, 1]],
						"affected": {},
						"key": "Health Potion",
						"script": "res://gd_core_items/HealthPotion.gd",
						"bagslot": false,
						"storage": false,
						"gems": []
					},
			{
						"row": 0,
						"col": 7,
						"rot": 0,
						"occupied": [[0, 7], [1, 7]],
						"collision": [[7, 0], [7, 1]],
						"affected": {
							0: [[6, 0], [6, 1], [7, -1], [7, 2], [8, 0], [8, 1]]
						},
						"key": "Garlic",
						"script": "res://gd_core_items/Garlic.gd",
						"bagslot": false,
						"storage": false,
						"gems": []
					},
		],
	},
	"lineup_mage_badges": {
		"name": "Mage Badges",
		"class": 3,
		"round": 1,
		"health": 25.0,
		"stamina": 5.0,
		"regen": 1.0,
		"items": [
			{
						"row": 0,
						"col": 0,
						"rot": 0,
						"occupied": [[0, 0]],
						"collision": [[0, 0]],
						"affected": {
							0: [[-2, 0], [-1, -2], [-1, -1], [-1, 0], [0, -2], [0, -1], [1, -1], [1, 0], [2, 0]]
						},
						"key": "Magic Badge",
						"script": "res://gd_core_items/Exclusive/MagicBadge.gd",
						"bagslot": false,
						"storage": false,
						"gems": []
					},
			{
						"row": 0,
						"col": 1,
						"rot": 0,
						"occupied": [[0, 1]],
						"collision": [[1, 0]],
						"affected": {},
						"key": "Flame Badge",
						"script": "res://gd_core_items/Exclusive/FlameBadge.gd",
						"bagslot": false,
						"storage": false,
						"gems": []
					},
			{
						"row": 0,
						"col": 2,
						"rot": 0,
						"occupied": [[0, 2], [1, 2]],
						"collision": [[2, 0], [2, 1]],
						"affected": {},
						"key": "Health Potion",
						"script": "res://gd_core_items/HealthPotion.gd",
						"bagslot": false,
						"storage": false,
						"gems": []
					},
			{
						"row": 0,
						"col": 3,
						"rot": 0,
						"occupied": [[0, 3], [1, 3]],
						"collision": [[3, 0], [3, 1]],
						"affected": {},
						"key": "Health Potion",
						"script": "res://gd_core_items/HealthPotion.gd",
						"bagslot": false,
						"storage": false,
						"gems": []
					},
			{
						"row": 0,
						"col": 4,
						"rot": 0,
						"occupied": [[0, 4]],
						"collision": [[4, 0]],
						"affected": {},
						"key": "Stone",
						"script": "res://gd_core_items/Stone.gd",
						"bagslot": false,
						"storage": false,
						"gems": []
					},
			{
						"row": 0,
						"col": 5,
						"rot": 0,
						"occupied": [[0, 5], [1, 5], [1, 6]],
						"collision": [[5, 0], [5, 1], [6, 1]],
						"affected": {
							0: [[4, 0], [4, 1], [5, -1], [5, 2], [6, 0], [6, 2], [7, 1]]
						},
						"key": "Banana",
						"script": "res://gd_core_items/Banana.gd",
						"bagslot": false,
						"storage": false,
						"gems": []
					},
		],
	},
	"lineup_poison_bow": {
		"name": "Poison Bow",
		"class": 0,
		"round": 1,
		"health": 25.0,
		"stamina": 5.0,
		"regen": 1.0,
		"items": [
			{
						"row": 0,
						"col": 0,
						"rot": 0,
						"occupied": [[0, 1], [1, 0], [1, 1], [1, 2], [2, 1]],
						"collision": [[0, 1], [1, 0], [1, 1], [1, 2], [2, 1]],
						"affected": {
							0: [[3, 1]]
						},
						"key": "Poison Bow",
						"script": "res://gd_core_items/PoisonBow.gd",
						"bagslot": false,
						"storage": false,
						"gems": []
					},
			{
						"row": 0,
						"col": 0,
						"rot": 0,
						"occupied": [[0, 0]],
						"collision": [[0, 0]],
						"affected": {
							0: [[0, -1]]
						},
						"key": "Amulet of the Wild",
						"script": "res://gd_core_items/Exclusive/AmuletoftheWild.gd",
						"bagslot": false,
						"storage": false,
						"gems": []
					},
			{
						"row": 0,
						"col": 3,
						"rot": 0,
						"occupied": [[0, 3], [1, 3]],
						"collision": [[3, 0], [3, 1]],
						"affected": {},
						"key": "Health Potion",
						"script": "res://gd_core_items/HealthPotion.gd",
						"bagslot": false,
						"storage": false,
						"gems": []
					},
			{
						"row": 0,
						"col": 4,
						"rot": 0,
						"occupied": [[0, 4], [1, 4]],
						"collision": [[4, 0], [4, 1]],
						"affected": {},
						"key": "Health Potion",
						"script": "res://gd_core_items/HealthPotion.gd",
						"bagslot": false,
						"storage": false,
						"gems": []
					},
			{
						"row": 0,
						"col": 5,
						"rot": 0,
						"occupied": [[0, 5], [1, 5], [1, 6]],
						"collision": [[5, 0], [5, 1], [6, 1]],
						"affected": {
							0: [[4, 0], [4, 1], [5, -1], [5, 2], [6, 0], [6, 2], [7, 1]]
						},
						"key": "Banana",
						"script": "res://gd_core_items/Banana.gd",
						"bagslot": false,
						"storage": false,
						"gems": []
					},
		],
	},
	"lineup_potion_link_test": {
		"name": "potion_link_test",
		"class": 0,
		"round": 3,
		"health": 60.0,
		"stamina": 5.0,
		"regen": 1.0,
		"items": [
			{
						"row": 1,
						"col": 1,
						"rot": 0,
						"occupied": [[1, 1], [2, 1]],
						"collision": [[1, 1], [1, 2]],
						"affected": {},
						"key": "Health Potion",
						"script": "res://gd_core_items/HealthPotion.gd",
						"bagslot": false,
						"storage": false,
						"gems": []
					},
			{
						"row": 0,
						"col": 0,
						"rot": 0,
						"occupied": [[0, 0], [1, 0]],
						"collision": [[0, 0], [0, 1]],
						"affected": {},
						"key": "Health Potion",
						"script": "res://gd_core_items/HealthPotion.gd",
						"bagslot": false,
						"storage": false,
						"gems": []
					},
		],
	},
}
