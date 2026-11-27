# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py
"""按 extends 依赖拓扑序导入全部模块（基类先注册，与 Godot 加载次序同义）。"""

from . import _registry  # noqa: F401
from . import _rt  # noqa: F401


def _stem2mod_rows():
    return [
        ('CoreItem', 'gd_core_py.gd_core.CoreItem'),
        ('Item', 'gd_core_py.gd_core_items.Item'),
        ('Card', 'gd_core_py.gd_core_items.Card'),
        ('AceofSpades', 'gd_core_py.gd_core.AceofSpades'),
        ('RangerCollar', 'gd_core_py.gd_core_items.RangerCollar'),
        ('AcornCollar', 'gd_core_py.gd_core.AcornCollar'),
        ('Stone', 'gd_core_py.gd_core_items.Stone'),
        ('ArtifactStoneCold', 'gd_core_py.gd_core.ArtifactStoneCold'),
        ('ArtifactStoneHeat', 'gd_core_py.gd_core.ArtifactStoneHeat'),
        ('Bag', 'gd_core_py.gd_core.Bag'),
        ('BagofStones', 'gd_core_py.gd_core.BagofStones'),
        ('Food', 'gd_core_py.gd_core_items.Food'),
        ('Banana', 'gd_core_py.gd_core.Banana'),
        ('BloodAmulet', 'gd_core_py.gd_core.BloodAmulet'),
        ('Goobert', 'gd_core_py.gd_core_items.Goobert'),
        ('BloodGoobert', 'gd_core_py.gd_core.BloodGoobert'),
        ('Weapon', 'gd_core_py.gd_core_items.Weapon'),
        ('Bloodthorne', 'gd_core_py.gd_core.Bloodthorne'),
        ('Dagger', 'gd_core_py.gd_core_items.Dagger'),
        ('BloodyDagger', 'gd_core_py.gd_core.BloodyDagger'),
        ('Blueberries', 'gd_core_py.gd_core.Blueberries'),
        ('Bow', 'gd_core_py.gd_core.Bow'),
        ('Bow', 'gd_core_py.gd_core_items.Bow'),
        ('BowandArrow', 'gd_core_py.gd_core.BowandArrow'),
        ('BoxofRiches', 'gd_core_py.gd_core.BoxofRiches'),
        ('Broom', 'gd_core_py.gd_core.Broom'),
        ('Gem', 'gd_core_py.gd_core_items.Gems.Gem'),
        ('BurningCoal', 'gd_core_py.gd_core.BurningCoal'),
        ('BurningTorch', 'gd_core_py.gd_core.BurningTorch'),
        ('Card', 'gd_core_py.gd_core.Card'),
        ('Carrot', 'gd_core_py.gd_core.Carrot'),
        ('CarrotGoobert', 'gd_core_py.gd_core.CarrotGoobert'),
        ('ClawsofAttack', 'gd_core_py.gd_core.ClawsofAttack'),
        ('CoreBuff', 'gd_core_py.gd_core.CoreBuff'),
        ('CoreCharacter', 'gd_core_py.gd_core.CoreCharacter'),
        ('CoreCombat', 'gd_core_py.gd_core.CoreCombat'),
        ('CoreCombatLog', 'gd_core_py.gd_core.CoreCombatLog'),
        ('CoreConst', 'gd_core_py.gd_core.CoreConst'),
        ('CoreContext', 'gd_core_py.gd_core.CoreContext'),
        ('CoreDamageResult', 'gd_core_py.gd_core.CoreDamageResult'),
        ('CoreDamageSource', 'gd_core_py.gd_core.CoreDamageSource'),
        ('CoreEvent', 'gd_core_py.gd_core.CoreEvent'),
        ('CoreEventBus', 'gd_core_py.gd_core.CoreEventBus'),
        ('CoreGrid', 'gd_core_py.gd_core.CoreGrid'),
        ('CoreHooks', 'gd_core_py.gd_core.CoreHooks'),
        ('CoreItemBook', 'gd_core_py.gd_core.CoreItemBook'),
        ('CoreItemData', 'gd_core_py.gd_core.CoreItemData'),
        ('CoreRng', 'gd_core_py.gd_core.CoreRng'),
        ('CoreTimer', 'gd_core_py.gd_core.CoreTimer'),
        ('CoreUtil', 'gd_core_py.gd_core.CoreUtil'),
        ('CorruptedArmor', 'gd_core_py.gd_core.CorruptedArmor'),
        ('CritwoodStaff', 'gd_core_py.gd_core.CritwoodStaff'),
        ('Crossblades', 'gd_core_py.gd_core.Crossblades'),
        ('Crown', 'gd_core_py.gd_core.Crown'),
        ('CursedDagger', 'gd_core_py.gd_core.CursedDagger'),
        ('CursedHairComb', 'gd_core_py.gd_core.CursedHairComb'),
        ('CustomerCard', 'gd_core_py.gd_core.CustomerCard'),
        ('Dagger', 'gd_core_py.gd_core.Dagger'),
        ('DancingDragon', 'gd_core_py.gd_core.DancingDragon'),
        ('DarkestLotus', 'gd_core_py.gd_core.DarkestLotus'),
        ('Darksaber', 'gd_core_py.gd_core.Darksaber'),
        ('DeathScythe', 'gd_core_py.gd_core.DeathScythe'),
        ('DeckofCards', 'gd_core_py.gd_core.DeckofCards'),
        ('Potion', 'gd_core_py.gd_core_items.Potion'),
        ('DemonicFlask', 'gd_core_py.gd_core.DemonicFlask'),
        ('DjinnLamp', 'gd_core_py.gd_core.DjinnLamp'),
        ('DragonEgg', 'gd_core_py.gd_core.DragonEgg'),
        ('Pan', 'gd_core_py.gd_core_items.Pan'),
        ('Eggscalibur', 'gd_core_py.gd_core.Eggscalibur'),
        ('EvilCap', 'gd_core_py.gd_core.EvilCap'),
        ('FalconBlade', 'gd_core_py.gd_core.FalconBlade'),
        ('FancyFencingRapier', 'gd_core_py.gd_core.FancyFencingRapier'),
        ('Fanfare', 'gd_core_py.gd_core.Fanfare'),
        ('Bag', 'gd_core_py.gd_core_items.Bag'),
        ('FannyPack', 'gd_core_py.gd_core.FannyPack'),
        ('Flute', 'gd_core_py.gd_core.Flute'),
        ('FlyAgaric', 'gd_core_py.gd_core.FlyAgaric'),
        ('Food', 'gd_core_py.gd_core.Food'),
        ('Garlic', 'gd_core_py.gd_core.Garlic'),
        ('GingerbreadMan', 'gd_core_py.gd_core.GingerbreadMan'),
        ('GlovesofHaste', 'gd_core_py.gd_core.GlovesofHaste'),
        ('Goobert', 'gd_core_py.gd_core.Goobert'),
        ('Greatsword', 'gd_core_py.gd_core.Greatsword'),
        ('Hammer', 'gd_core_py.gd_core.Hammer'),
        ('HealingHerbs', 'gd_core_py.gd_core.HealingHerbs'),
        ('HealthPotion', 'gd_core_py.gd_core.HealthPotion'),
        ('HeartContainer', 'gd_core_py.gd_core.HeartContainer'),
        ('HeartofDarkness', 'gd_core_py.gd_core.HeartofDarkness'),
        ('HeroLongsword', 'gd_core_py.gd_core.HeroLongsword'),
        ('HeroSword', 'gd_core_py.gd_core.HeroSword'),
        ('HeroicPotion', 'gd_core_py.gd_core.HeroicPotion'),
        ('HoloFireLizard', 'gd_core_py.gd_core.HoloFireLizard'),
        ('HolyArmor', 'gd_core_py.gd_core.HolyArmor'),
        ('HolySpear', 'gd_core_py.gd_core.HolySpear'),
        ('HungryBlade', 'gd_core_py.gd_core.HungryBlade'),
        ('Item', 'gd_core_py.gd_core.Item'),
        ('Jynxtorquilla', 'gd_core_py.gd_core.Jynxtorquilla'),
        ('LeatherArmor', 'gd_core_py.gd_core.LeatherArmor'),
        ('LeatherBoots', 'gd_core_py.gd_core.LeatherBoots'),
        ('LeatherHelm', 'gd_core_py.gd_core.LeatherHelm'),
        ('LightGoobert', 'gd_core_py.gd_core.LightGoobert'),
        ('Lightsaber', 'gd_core_py.gd_core.Lightsaber'),
        ('LuckyBow', 'gd_core_py.gd_core.LuckyBow'),
        ('LuckyClover', 'gd_core_py.gd_core.LuckyClover'),
        ('Piggybank', 'gd_core_py.gd_core_items.Piggybank'),
        ('LuckyPiggy', 'gd_core_py.gd_core.LuckyPiggy'),
        ('MagicStaff', 'gd_core_py.gd_core.MagicStaff'),
        ('MagicTorch', 'gd_core_py.gd_core.MagicTorch'),
        ('ManaOrb', 'gd_core_py.gd_core.ManaOrb'),
        ('ManaPotion', 'gd_core_py.gd_core.ManaPotion'),
        ('Manathirst', 'gd_core_py.gd_core.Manathirst'),
        ('Shield', 'gd_core_py.gd_core_items.Shield'),
        ('MoonShield', 'gd_core_py.gd_core.MoonShield'),
        ('MrStruggles', 'gd_core_py.gd_core.MrStruggles'),
        ('Pan', 'gd_core_py.gd_core.Pan'),
        ('Pandamonium', 'gd_core_py.gd_core.Pandamonium'),
        ('PestilenceFlask', 'gd_core_py.gd_core.PestilenceFlask'),
        ('PiercingArrow', 'gd_core_py.gd_core.PiercingArrow'),
        ('Piggybank', 'gd_core_py.gd_core.Piggybank'),
        ('Pineapple', 'gd_core_py.gd_core.Pineapple'),
        ('PlatinCustomerCard', 'gd_core_py.gd_core.PlatinCustomerCard'),
        ('PocketSand', 'gd_core_py.gd_core.PocketSand'),
        ('PoisonBow', 'gd_core_py.gd_core.PoisonBow'),
        ('PoisonDagger', 'gd_core_py.gd_core.PoisonDagger'),
        ('PoisonGoobert', 'gd_core_py.gd_core.PoisonGoobert'),
        ('PoisonIvy', 'gd_core_py.gd_core.PoisonIvy'),
        ('Potion', 'gd_core_py.gd_core.Potion'),
        ('PotionBelt', 'gd_core_py.gd_core.PotionBelt'),
        ('Present', 'gd_core_py.gd_core.Present'),
        ('ProtectivePurse', 'gd_core_py.gd_core.ProtectivePurse'),
        ('Pumpkin', 'gd_core_py.gd_core.Pumpkin'),
        ('RainbowGoobert', 'gd_core_py.gd_core.RainbowGoobert'),
        ('RainbowGoobertRanger', 'gd_core_py.gd_core.RainbowGoobertRanger'),
        ('RangerBag', 'gd_core_py.gd_core.RangerBag'),
        ('RangerCollar', 'gd_core_py.gd_core.RangerCollar'),
        ('RibSawBlade', 'gd_core_py.gd_core.RibSawBlade'),
        ('RubyChonk', 'gd_core_py.gd_core.RubyChonk'),
        ('DragonEgg', 'gd_core_py.gd_core_items.DragonEgg'),
        ('RubyEgg', 'gd_core_py.gd_core.RubyEgg'),
        ('RubyWhelp', 'gd_core_py.gd_core.RubyWhelp'),
        ('Shield', 'gd_core_py.gd_core.Shield'),
        ('ShieldofValor', 'gd_core_py.gd_core.ShieldofValor'),
        ('Shovel', 'gd_core_py.gd_core.Shovel'),
        ('Spear', 'gd_core_py.gd_core.Spear'),
        ('SpectralDagger', 'gd_core_py.gd_core.SpectralDagger'),
        ('SpikedShield', 'gd_core_py.gd_core.SpikedShield'),
        ('StaffofUnhealing', 'gd_core_py.gd_core.StaffofUnhealing'),
        ('StaminaSack', 'gd_core_py.gd_core.StaminaSack'),
        ('SteelGoobert', 'gd_core_py.gd_core.SteelGoobert'),
        ('Stone', 'gd_core_py.gd_core.Stone'),
        ('LeatherHelm', 'gd_core_py.gd_core_items.LeatherHelm'),
        ('StoneHelm', 'gd_core_py.gd_core.StoneHelm'),
        ('StoneSkinPotion', 'gd_core_py.gd_core.StoneSkinPotion'),
        ('StorageCoffin', 'gd_core_py.gd_core.StorageCoffin'),
        ('StrongDemonicFlask', 'gd_core_py.gd_core.StrongDemonicFlask'),
        ('HealthPotion', 'gd_core_py.gd_core_items.HealthPotion'),
        ('StrongHealthPotion', 'gd_core_py.gd_core.StrongHealthPotion'),
        ('PestilenceFlask', 'gd_core_py.gd_core_items.PestilenceFlask'),
        ('StrongPestilenceFlask', 'gd_core_py.gd_core.StrongPestilenceFlask'),
        ('StoneSkinPotion', 'gd_core_py.gd_core_items.StoneSkinPotion'),
        ('StrongStoneSkinPotion', 'gd_core_py.gd_core.StrongStoneSkinPotion'),
        ('TheFool', 'gd_core_py.gd_core.TheFool'),
        ('TheLovers', 'gd_core_py.gd_core.TheLovers'),
        ('ThornBow', 'gd_core_py.gd_core.ThornBow'),
        ('ThornWhip', 'gd_core_py.gd_core.ThornWhip'),
        ('Torch', 'gd_core_py.gd_core.Torch'),
        ('VampiricArmor', 'gd_core_py.gd_core.VampiricArmor'),
        ('VampiricGloves', 'gd_core_py.gd_core.VampiricGloves'),
        ('VampiricScythe', 'gd_core_py.gd_core.VampiricScythe'),
        ('VillainSword', 'gd_core_py.gd_core.VillainSword'),
        ('WalrusTusk', 'gd_core_py.gd_core.WalrusTusk'),
        ('Weapon', 'gd_core_py.gd_core.Weapon'),
        ('Whetstone', 'gd_core_py.gd_core.Whetstone'),
        ('White_EyesBlueDragon', 'gd_core_py.gd_core.White_EyesBlueDragon'),
        ('Wolpertinger', 'gd_core_py.gd_core.Wolpertinger'),
        ('WoodenBuckler', 'gd_core_py.gd_core.WoodenBuckler'),
        ('WoodenSword', 'gd_core_py.gd_core.WoodenSword'),
        ('YggdrasilLeaf', 'gd_core_py.gd_core.YggdrasilLeaf'),
        ('AceofSpades', 'gd_core_py.gd_core_items.AceofSpades'),
        ('AcornCollar', 'gd_core_py.gd_core_items.AcornCollar'),
        ('ArtifactStoneCold', 'gd_core_py.gd_core_items.ArtifactStoneCold'),
        ('ArtifactStoneHeat', 'gd_core_py.gd_core_items.ArtifactStoneHeat'),
        ('BagofStones', 'gd_core_py.gd_core_items.BagofStones'),
        ('Banana', 'gd_core_py.gd_core_items.Banana'),
        ('BloodAmulet', 'gd_core_py.gd_core_items.BloodAmulet'),
        ('BloodGoobert', 'gd_core_py.gd_core_items.BloodGoobert'),
        ('Bloodthorne', 'gd_core_py.gd_core_items.Bloodthorne'),
        ('BloodyDagger', 'gd_core_py.gd_core_items.BloodyDagger'),
        ('Blueberries', 'gd_core_py.gd_core_items.Blueberries'),
        ('BowandArrow', 'gd_core_py.gd_core_items.BowandArrow'),
        ('BoxofRiches', 'gd_core_py.gd_core_items.BoxofRiches'),
        ('Broom', 'gd_core_py.gd_core_items.Broom'),
        ('BurningCoal', 'gd_core_py.gd_core_items.BurningCoal'),
        ('BurningTorch', 'gd_core_py.gd_core_items.BurningTorch'),
        ('Carrot', 'gd_core_py.gd_core_items.Carrot'),
        ('CarrotGoobert', 'gd_core_py.gd_core_items.CarrotGoobert'),
        ('ClawsofAttack', 'gd_core_py.gd_core_items.ClawsofAttack'),
        ('Coins', 'gd_core_py.gd_core_items.Coins'),
        ('CorruptedArmor', 'gd_core_py.gd_core_items.CorruptedArmor'),
        ('CritwoodStaff', 'gd_core_py.gd_core_items.CritwoodStaff'),
        ('Crossblades', 'gd_core_py.gd_core_items.Crossblades'),
        ('Crown', 'gd_core_py.gd_core_items.Crown'),
        ('CursedDagger', 'gd_core_py.gd_core_items.CursedDagger'),
        ('CursedHairComb', 'gd_core_py.gd_core_items.CursedHairComb'),
        ('CustomerCard', 'gd_core_py.gd_core_items.CustomerCard'),
        ('DancingDragon', 'gd_core_py.gd_core_items.DancingDragon'),
        ('DarkestLotus', 'gd_core_py.gd_core_items.DarkestLotus'),
        ('Darksaber', 'gd_core_py.gd_core_items.Darksaber'),
        ('DeathScythe', 'gd_core_py.gd_core_items.DeathScythe'),
        ('DeckofCards', 'gd_core_py.gd_core_items.DeckofCards'),
        ('DemonicFlask', 'gd_core_py.gd_core_items.DemonicFlask'),
        ('DjinnLamp', 'gd_core_py.gd_core_items.DjinnLamp'),
        ('Eggscalibur', 'gd_core_py.gd_core_items.Eggscalibur'),
        ('EvilCap', 'gd_core_py.gd_core_items.EvilCap'),
        ('FalconBlade', 'gd_core_py.gd_core_items.FalconBlade'),
        ('FancyFencingRapier', 'gd_core_py.gd_core_items.FancyFencingRapier'),
        ('Fanfare', 'gd_core_py.gd_core_items.Fanfare'),
        ('FannyPack', 'gd_core_py.gd_core_items.FannyPack'),
        ('Flute', 'gd_core_py.gd_core_items.Flute'),
        ('FlyAgaric', 'gd_core_py.gd_core_items.FlyAgaric'),
        ('Garlic', 'gd_core_py.gd_core_items.Garlic'),
        ('GingerbreadMan', 'gd_core_py.gd_core_items.GingerbreadMan'),
        ('GlovesofHaste', 'gd_core_py.gd_core_items.GlovesofHaste'),
        ('Greatsword', 'gd_core_py.gd_core_items.Greatsword'),
        ('Hammer', 'gd_core_py.gd_core_items.Hammer'),
        ('HealingHerbs', 'gd_core_py.gd_core_items.HealingHerbs'),
        ('HeartContainer', 'gd_core_py.gd_core_items.HeartContainer'),
        ('HeartofDarkness', 'gd_core_py.gd_core_items.HeartofDarkness'),
        ('HeroLongsword', 'gd_core_py.gd_core_items.HeroLongsword'),
        ('HeroSword', 'gd_core_py.gd_core_items.HeroSword'),
        ('HeroicPotion', 'gd_core_py.gd_core_items.HeroicPotion'),
        ('HoloFireLizard', 'gd_core_py.gd_core_items.HoloFireLizard'),
        ('HolyArmor', 'gd_core_py.gd_core_items.HolyArmor'),
        ('HolySpear', 'gd_core_py.gd_core_items.HolySpear'),
        ('HungryBlade', 'gd_core_py.gd_core_items.HungryBlade'),
        ('Jynxtorquilla', 'gd_core_py.gd_core_items.Jynxtorquilla'),
        ('LeatherArmor', 'gd_core_py.gd_core_items.LeatherArmor'),
        ('LeatherBoots', 'gd_core_py.gd_core_items.LeatherBoots'),
        ('LightGoobert', 'gd_core_py.gd_core_items.LightGoobert'),
        ('Lightsaber', 'gd_core_py.gd_core_items.Lightsaber'),
        ('LuckyBow', 'gd_core_py.gd_core_items.LuckyBow'),
        ('LuckyClover', 'gd_core_py.gd_core_items.LuckyClover'),
        ('LuckyPiggy', 'gd_core_py.gd_core_items.LuckyPiggy'),
        ('MagicStaff', 'gd_core_py.gd_core_items.MagicStaff'),
        ('MagicTorch', 'gd_core_py.gd_core_items.MagicTorch'),
        ('ManaOrb', 'gd_core_py.gd_core_items.ManaOrb'),
        ('ManaPotion', 'gd_core_py.gd_core_items.ManaPotion'),
        ('Manathirst', 'gd_core_py.gd_core_items.Manathirst'),
        ('MoonShield', 'gd_core_py.gd_core_items.MoonShield'),
        ('MrStruggles', 'gd_core_py.gd_core_items.MrStruggles'),
        ('Pandamonium', 'gd_core_py.gd_core_items.Pandamonium'),
        ('PiercingArrow', 'gd_core_py.gd_core_items.PiercingArrow'),
        ('Pineapple', 'gd_core_py.gd_core_items.Pineapple'),
        ('PlatinCustomerCard', 'gd_core_py.gd_core_items.PlatinCustomerCard'),
        ('PocketSand', 'gd_core_py.gd_core_items.PocketSand'),
        ('PoisonBow', 'gd_core_py.gd_core_items.PoisonBow'),
        ('PoisonDagger', 'gd_core_py.gd_core_items.PoisonDagger'),
        ('PoisonGoobert', 'gd_core_py.gd_core_items.PoisonGoobert'),
        ('PoisonIvy', 'gd_core_py.gd_core_items.PoisonIvy'),
        ('PotionBelt', 'gd_core_py.gd_core_items.PotionBelt'),
        ('Present', 'gd_core_py.gd_core_items.Present'),
        ('ProtectivePurse', 'gd_core_py.gd_core_items.ProtectivePurse'),
        ('Pumpkin', 'gd_core_py.gd_core_items.Pumpkin'),
        ('RainbowGoobert', 'gd_core_py.gd_core_items.RainbowGoobert'),
        ('RainbowGoobertRanger', 'gd_core_py.gd_core_items.RainbowGoobertRanger'),
        ('RangerBag', 'gd_core_py.gd_core_items.RangerBag'),
        ('RibSawBlade', 'gd_core_py.gd_core_items.RibSawBlade'),
        ('RubyChonk', 'gd_core_py.gd_core_items.RubyChonk'),
        ('RubyEgg', 'gd_core_py.gd_core_items.RubyEgg'),
        ('RubyWhelp', 'gd_core_py.gd_core_items.RubyWhelp'),
        ('ShieldofValor', 'gd_core_py.gd_core_items.ShieldofValor'),
        ('Shovel', 'gd_core_py.gd_core_items.Shovel'),
        ('Spear', 'gd_core_py.gd_core_items.Spear'),
        ('SpectralDagger', 'gd_core_py.gd_core_items.SpectralDagger'),
        ('SpikedShield', 'gd_core_py.gd_core_items.SpikedShield'),
        ('StaffofUnhealing', 'gd_core_py.gd_core_items.StaffofUnhealing'),
        ('StaminaSack', 'gd_core_py.gd_core_items.StaminaSack'),
        ('SteelGoobert', 'gd_core_py.gd_core_items.SteelGoobert'),
        ('StoneHelm', 'gd_core_py.gd_core_items.StoneHelm'),
        ('StorageCoffin', 'gd_core_py.gd_core_items.StorageCoffin'),
        ('StrongDemonicFlask', 'gd_core_py.gd_core_items.StrongDemonicFlask'),
        ('StrongHealthPotion', 'gd_core_py.gd_core_items.StrongHealthPotion'),
        ('StrongPestilenceFlask', 'gd_core_py.gd_core_items.StrongPestilenceFlask'),
        ('StrongStoneSkinPotion', 'gd_core_py.gd_core_items.StrongStoneSkinPotion'),
        ('TheFool', 'gd_core_py.gd_core_items.TheFool'),
        ('TheLovers', 'gd_core_py.gd_core_items.TheLovers'),
        ('ThornBow', 'gd_core_py.gd_core_items.ThornBow'),
        ('ThornWhip', 'gd_core_py.gd_core_items.ThornWhip'),
        ('Torch', 'gd_core_py.gd_core_items.Torch'),
        ('VampiricArmor', 'gd_core_py.gd_core_items.VampiricArmor'),
        ('VampiricGloves', 'gd_core_py.gd_core_items.VampiricGloves'),
        ('VampiricScythe', 'gd_core_py.gd_core_items.VampiricScythe'),
        ('VillainSword', 'gd_core_py.gd_core_items.VillainSword'),
        ('WalrusTusk', 'gd_core_py.gd_core_items.WalrusTusk'),
        ('Whetstone', 'gd_core_py.gd_core_items.Whetstone'),
        ('White_EyesBlueDragon', 'gd_core_py.gd_core_items.White_EyesBlueDragon'),
        ('Wolpertinger', 'gd_core_py.gd_core_items.Wolpertinger'),
        ('WoodenBuckler', 'gd_core_py.gd_core_items.WoodenBuckler'),
        ('WoodenSword', 'gd_core_py.gd_core_items.WoodenSword'),
        ('YggdrasilLeaf', 'gd_core_py.gd_core_items.YggdrasilLeaf'),
        ('AcornAce', 'gd_core_py.gd_core_items.Exclusive.AcornAce'),
        ('AmethystEgg', 'gd_core_py.gd_core_items.Exclusive.AmethystEgg'),
        ('AmethystWhelp', 'gd_core_py.gd_core_items.Exclusive.AmethystWhelp'),
        ('AmuletUnidentified', 'gd_core_py.gd_core_items.Exclusive.AmuletUnidentified'),
        ('AmuletofAgility', 'gd_core_py.gd_core_items.Exclusive.AmuletofAgility'),
        ('AmuletofAlchemy', 'gd_core_py.gd_core_items.Exclusive.AmuletofAlchemy'),
        ('AmuletofDarkness', 'gd_core_py.gd_core_items.Exclusive.AmuletofDarkness'),
        ('AmuletofFeasting', 'gd_core_py.gd_core_items.Exclusive.AmuletofFeasting'),
        ('AmuletofFortune', 'gd_core_py.gd_core_items.Exclusive.AmuletofFortune'),
        ('AmuletofLife', 'gd_core_py.gd_core_items.Exclusive.AmuletofLife'),
        ('AmuletofLight', 'gd_core_py.gd_core_items.Exclusive.AmuletofLight'),
        ('AmuletofSteel', 'gd_core_py.gd_core_items.Exclusive.AmuletofSteel'),
        ('AmuletoftheWild', 'gd_core_py.gd_core_items.Exclusive.AmuletoftheWild'),
        ('AngelCrystal', 'gd_core_py.gd_core_items.Exclusive.AngelCrystal'),
        ('Anvil', 'gd_core_py.gd_core_items.Exclusive.Anvil'),
        ('ArcaneBoots', 'gd_core_py.gd_core_items.Exclusive.ArcaneBoots'),
        ('ArcaneIntellect', 'gd_core_py.gd_core_items.Exclusive.ArcaneIntellect'),
        ('CouragePuppy', 'gd_core_py.gd_core_items.Exclusive.CouragePuppy'),
        ('ArmoredCouragePuppy', 'gd_core_py.gd_core_items.Exclusive.ArmoredCouragePuppy'),
        ('PowerPuppy', 'gd_core_py.gd_core_items.Exclusive.PowerPuppy'),
        ('ArmoredPowerPuppy', 'gd_core_py.gd_core_items.Exclusive.ArmoredPowerPuppy'),
        ('WisdomPuppy', 'gd_core_py.gd_core_items.Exclusive.WisdomPuppy'),
        ('ArmoredWisdomPuppy', 'gd_core_py.gd_core_items.Exclusive.ArmoredWisdomPuppy'),
        ('ArtifactStoneDeath', 'gd_core_py.gd_core_items.Exclusive.ArtifactStoneDeath'),
        ('Automanaton', 'gd_core_py.gd_core_items.Exclusive.Automanaton'),
        ('Axe', 'gd_core_py.gd_core_items.Exclusive.Axe'),
        ('BadgerRune', 'gd_core_py.gd_core_items.Exclusive.BadgerRune'),
        ('SpiritCompanion', 'gd_core_py.gd_core_items.Exclusive.SpiritCompanion'),
        ('BadgerSpirit', 'gd_core_py.gd_core_items.Exclusive.BadgerSpirit'),
        ('BagofGiving', 'gd_core_py.gd_core_items.Exclusive.BagofGiving'),
        ('Bagtacular', 'gd_core_py.gd_core_items.Exclusive.Bagtacular'),
        ('Battery', 'gd_core_py.gd_core_items.Exclusive.Battery'),
        ('Bazooka', 'gd_core_py.gd_core_items.Exclusive.Bazooka'),
        ('BerserkerBag', 'gd_core_py.gd_core_items.Exclusive.BerserkerBag'),
        ('Bewitchment', 'gd_core_py.gd_core_items.Exclusive.Bewitchment'),
        ('BigBloodthorne', 'gd_core_py.gd_core_items.Exclusive.BigBloodthorne'),
        ('BionicArmor', 'gd_core_py.gd_core_items.Exclusive.BionicArmor'),
        ('Cube', 'gd_core_py.gd_core_items.Exclusive.Cube'),
        ('BismuthCube', 'gd_core_py.gd_core_items.Exclusive.BismuthCube'),
        ('BloodManipulation', 'gd_core_py.gd_core_items.Exclusive.BloodManipulation'),
        ('Bomb', 'gd_core_py.gd_core_items.Exclusive.Bomb'),
        ('BookofBasics', 'gd_core_py.gd_core_items.Exclusive.BookofBasics'),
        ('BookofDarkness', 'gd_core_py.gd_core_items.Exclusive.BookofDarkness'),
        ('BookofIce', 'gd_core_py.gd_core_items.Exclusive.BookofIce'),
        ('BookofLight', 'gd_core_py.gd_core_items.Exclusive.BookofLight'),
        ('BookofNature', 'gd_core_py.gd_core_items.Exclusive.BookofNature'),
        ('Boomerang', 'gd_core_py.gd_core_items.Exclusive.Boomerang'),
        ('BowlofTreats', 'gd_core_py.gd_core_items.Exclusive.BowlofTreats'),
        ('BoxofProsperity', 'gd_core_py.gd_core_items.Exclusive.BoxofProsperity'),
        ('BrassKnuckles', 'gd_core_py.gd_core_items.Exclusive.BrassKnuckles'),
        ('Broccoli', 'gd_core_py.gd_core_items.Exclusive.Broccoli'),
        ('BroccoliGoobert', 'gd_core_py.gd_core_items.Exclusive.BroccoliGoobert'),
        ('Broccotree', 'gd_core_py.gd_core_items.Exclusive.Broccotree'),
        ('BurningBanner', 'gd_core_py.gd_core_items.Exclusive.BurningBanner'),
        ('BurningSword', 'gd_core_py.gd_core_items.Exclusive.BurningSword'),
        ('BurningBlade', 'gd_core_py.gd_core_items.Exclusive.BurningBlade'),
        ('BurningSpikes', 'gd_core_py.gd_core_items.Exclusive.BurningSpikes'),
        ('BustedBlade', 'gd_core_py.gd_core_items.Exclusive.BustedBlade'),
        ('BuytheHolyLight', 'gd_core_py.gd_core_items.Exclusive.BuytheHolyLight'),
        ('CapofBrilliance', 'gd_core_py.gd_core_items.Exclusive.CapofBrilliance'),
        ('CatSpirit', 'gd_core_py.gd_core_items.Exclusive.CatSpirit'),
        ('Cauldron', 'gd_core_py.gd_core_items.Exclusive.Cauldron'),
        ('ChainWhip', 'gd_core_py.gd_core_items.Exclusive.ChainWhip'),
        ('Chainsaw', 'gd_core_py.gd_core_items.Exclusive.Chainsaw'),
        ('ChargeSplitter', 'gd_core_py.gd_core_items.Exclusive.ChargeSplitter'),
        ('Cheese', 'gd_core_py.gd_core_items.Exclusive.Cheese'),
        ('CheeseGoobert', 'gd_core_py.gd_core_items.Exclusive.CheeseGoobert'),
        ('ChessBoard', 'gd_core_py.gd_core_items.Exclusive.ChessBoard'),
        ('ChessMaster', 'gd_core_py.gd_core_items.Exclusive.ChessMaster'),
        ('ChiliGoobert', 'gd_core_py.gd_core_items.Exclusive.ChiliGoobert'),
        ('ChiliPepper', 'gd_core_py.gd_core_items.Exclusive.ChiliPepper'),
        ('ChromeCube', 'gd_core_py.gd_core_items.Exclusive.ChromeCube'),
        ('Cog', 'gd_core_py.gd_core_items.Exclusive.Cog'),
        ('CogBadge', 'gd_core_py.gd_core_items.Exclusive.CogBadge'),
        ('Coil', 'gd_core_py.gd_core_items.Exclusive.Coil'),
        ('ConTrapTron', 'gd_core_py.gd_core_items.Exclusive.ConTrapTron'),
        ('CriticalPoison', 'gd_core_py.gd_core_items.Exclusive.CriticalPoison'),
        ('Crow', 'gd_core_py.gd_core_items.Exclusive.Crow'),
        ('Cthulhu', 'gd_core_py.gd_core_items.Exclusive.Cthulhu'),
        ('Cubert', 'gd_core_py.gd_core_items.Exclusive.Cubert'),
        ('Cupcake', 'gd_core_py.gd_core_items.Exclusive.Cupcake'),
        ('CupcakeDragon', 'gd_core_py.gd_core_items.Exclusive.CupcakeDragon'),
        ('CupcakeGoobert', 'gd_core_py.gd_core_items.Exclusive.CupcakeGoobert'),
        ('CupcakeStaff', 'gd_core_py.gd_core_items.Exclusive.CupcakeStaff'),
        ('Daggerang', 'gd_core_py.gd_core_items.Exclusive.Daggerang'),
        ('DarkLantern', 'gd_core_py.gd_core_items.Exclusive.DarkLantern'),
        ('DarkRitual', 'gd_core_py.gd_core_items.Exclusive.DarkRitual'),
        ('DeathLotus', 'gd_core_py.gd_core_items.Exclusive.DeathLotus'),
        ('DeerTotem', 'gd_core_py.gd_core_items.Exclusive.DeerTotem'),
        ('DevouringSphere', 'gd_core_py.gd_core_items.Exclusive.DevouringSphere'),
        ('DigDeeper', 'gd_core_py.gd_core_items.Exclusive.DigDeeper'),
        ('DivinePotion', 'gd_core_py.gd_core_items.Exclusive.DivinePotion'),
        ('DoomCap', 'gd_core_py.gd_core_items.Exclusive.DoomCap'),
        ('DoubleAxe', 'gd_core_py.gd_core_items.Exclusive.DoubleAxe'),
        ('DoubleRainbow', 'gd_core_py.gd_core_items.Exclusive.DoubleRainbow'),
        ('DraconicOrb', 'gd_core_py.gd_core_items.Exclusive.DraconicOrb'),
        ('DragonClaws', 'gd_core_py.gd_core_items.Exclusive.DragonClaws'),
        ('DragonKnight', 'gd_core_py.gd_core_items.Exclusive.DragonKnight'),
        ('DragonNest', 'gd_core_py.gd_core_items.Exclusive.DragonNest'),
        ('DragonSet', 'gd_core_py.gd_core_items.Exclusive.DragonSet'),
        ('DragonscaleArmor', 'gd_core_py.gd_core_items.Exclusive.DragonscaleArmor'),
        ('DragonskinBoots', 'gd_core_py.gd_core_items.Exclusive.DragonskinBoots'),
        ('DualWielding', 'gd_core_py.gd_core_items.Exclusive.DualWielding'),
        ('Eat_o_matic', 'gd_core_py.gd_core_items.Exclusive.Eat_o_matic'),
        ('EchoingBattlecry', 'gd_core_py.gd_core_items.Exclusive.EchoingBattlecry'),
        ('ElectricTorch', 'gd_core_py.gd_core_items.Exclusive.ElectricTorch'),
        ('ElephantRune', 'gd_core_py.gd_core_items.Exclusive.ElephantRune'),
        ('EmeraldEgg', 'gd_core_py.gd_core_items.Exclusive.EmeraldEgg'),
        ('EmeraldWhelp', 'gd_core_py.gd_core_items.Exclusive.EmeraldWhelp'),
        ('EmployeeUniform', 'gd_core_py.gd_core_items.Exclusive.EmployeeUniform'),
        ('EnchantedWeapons', 'gd_core_py.gd_core_items.Exclusive.EnchantedWeapons'),
        ('EnergyConversion', 'gd_core_py.gd_core_items.Exclusive.EnergyConversion'),
        ('EngineerBag2', 'gd_core_py.gd_core_items.Exclusive.EngineerBag2'),
        ('EngineerBox', 'gd_core_py.gd_core_items.Exclusive.EngineerBox'),
        ('Everburning', 'gd_core_py.gd_core_items.Exclusive.Everburning'),
        ('EvilHat', 'gd_core_py.gd_core_items.Exclusive.EvilHat'),
        ('ExtraAngy', 'gd_core_py.gd_core_items.Exclusive.ExtraAngy'),
        ('ExtraBags', 'gd_core_py.gd_core_items.Exclusive.ExtraBags'),
        ('FalseLife', 'gd_core_py.gd_core_items.Exclusive.FalseLife'),
        ('Fedora', 'gd_core_py.gd_core_items.Exclusive.Fedora'),
        ('FirePit', 'gd_core_py.gd_core_items.Exclusive.FirePit'),
        ('Shelly', 'gd_core_py.gd_core_items.Exclusive.Shelly'),
        ('FireShelly', 'gd_core_py.gd_core_items.Exclusive.FireShelly'),
        ('Flame', 'gd_core_py.gd_core_items.Exclusive.Flame'),
        ('FlameBadge', 'gd_core_py.gd_core_items.Exclusive.FlameBadge'),
        ('FlameWhip', 'gd_core_py.gd_core_items.Exclusive.FlameWhip'),
        ('ForestDragon', 'gd_core_py.gd_core_items.Exclusive.ForestDragon'),
        ('ForestFriend', 'gd_core_py.gd_core_items.Exclusive.ForestFriend'),
        ('ForgingHammer', 'gd_core_py.gd_core_items.Exclusive.ForgingHammer'),
        ('FortunasKiss', 'gd_core_py.gd_core_items.Exclusive.FortunasKiss'),
        ('FriendlyFire', 'gd_core_py.gd_core_items.Exclusive.FriendlyFire'),
        ('Toad', 'gd_core_py.gd_core_items.Exclusive.Toad'),
        ('FrogPrince', 'gd_core_py.gd_core_items.Exclusive.FrogPrince'),
        ('Frostbite', 'gd_core_py.gd_core_items.Exclusive.Frostbite'),
        ('FrozenBuckler', 'gd_core_py.gd_core_items.Exclusive.FrozenBuckler'),
        ('FrozenFlame', 'gd_core_py.gd_core_items.Exclusive.FrozenFlame'),
        ('FullBodyProtection', 'gd_core_py.gd_core_items.Exclusive.FullBodyProtection'),
        ('FurciferPrime', 'gd_core_py.gd_core_items.Exclusive.FurciferPrime'),
        ('Generator', 'gd_core_py.gd_core_items.Exclusive.Generator'),
        ('Ghost', 'gd_core_py.gd_core_items.Exclusive.Ghost'),
        ('Gigawatz', 'gd_core_py.gd_core_items.Exclusive.Gigawatz'),
        ('GirlPower', 'gd_core_py.gd_core_items.Exclusive.GirlPower'),
        ('GoldArmor', 'gd_core_py.gd_core_items.Exclusive.GoldArmor'),
        ('GoldCube', 'gd_core_py.gd_core_items.Exclusive.GoldCube'),
        ('Halberd', 'gd_core_py.gd_core_items.Exclusive.Halberd'),
        ('Hardwood', 'gd_core_py.gd_core_items.Exclusive.Hardwood'),
        ('HawkRune', 'gd_core_py.gd_core_items.Exclusive.HawkRune'),
        ('HeartShield', 'gd_core_py.gd_core_items.Exclusive.HeartShield'),
        ('HeartoftheCards', 'gd_core_py.gd_core_items.Exclusive.HeartoftheCards'),
        ('HeavyDrinking', 'gd_core_py.gd_core_items.Exclusive.HeavyDrinking'),
        ('Hedgehog', 'gd_core_py.gd_core_items.Exclusive.Hedgehog'),
        ('HeroShield', 'gd_core_py.gd_core_items.Exclusive.HeroShield'),
        ('HogusBogus', 'gd_core_py.gd_core_items.Exclusive.HogusBogus'),
        ('Holdall', 'gd_core_py.gd_core_items.Exclusive.Holdall'),
        ('HolyCollar', 'gd_core_py.gd_core_items.Exclusive.HolyCollar'),
        ('HyperHedgehog', 'gd_core_py.gd_core_items.Exclusive.HyperHedgehog'),
        ('Hypercube', 'gd_core_py.gd_core_items.Exclusive.Hypercube'),
        ('IceArmor', 'gd_core_py.gd_core_items.Exclusive.IceArmor'),
        ('IceDragon', 'gd_core_py.gd_core_items.Exclusive.IceDragon'),
        ('IceFlower', 'gd_core_py.gd_core_items.Exclusive.IceFlower'),
        ('InnerPower', 'gd_core_py.gd_core_items.Exclusive.InnerPower'),
        ('InvestmentOpportunity', 'gd_core_py.gd_core_items.Exclusive.InvestmentOpportunity'),
        ('Joker', 'gd_core_py.gd_core_items.Exclusive.Joker'),
        ('JustStats', 'gd_core_py.gd_core_items.Exclusive.JustStats'),
        ('JynxStaff', 'gd_core_py.gd_core_items.Exclusive.JynxStaff'),
        ('Katana', 'gd_core_py.gd_core_items.Exclusive.Katana'),
        ('KingCrown', 'gd_core_py.gd_core_items.Exclusive.KingCrown'),
        ('KingGoobert', 'gd_core_py.gd_core_items.Exclusive.KingGoobert'),
        ('KingoftheBling', 'gd_core_py.gd_core_items.Exclusive.KingoftheBling'),
        ('KnifetoMeetYou', 'gd_core_py.gd_core_items.Exclusive.KnifetoMeetYou'),
        ('Laboratory', 'gd_core_py.gd_core_items.Exclusive.Laboratory'),
        ('LeafBadge', 'gd_core_py.gd_core_items.Exclusive.LeafBadge'),
        ('LevelUp', 'gd_core_py.gd_core_items.Exclusive.LevelUp'),
        ('LightFlower', 'gd_core_py.gd_core_items.Exclusive.LightFlower'),
        ('LightningPotion', 'gd_core_py.gd_core_items.Exclusive.LightningPotion'),
        ('LightningStaff', 'gd_core_py.gd_core_items.Exclusive.LightningStaff'),
        ('LittleMimic', 'gd_core_py.gd_core_items.Exclusive.LittleMimic'),
        ('LongSpear', 'gd_core_py.gd_core_items.Exclusive.LongSpear'),
        ('Lootbox', 'gd_core_py.gd_core_items.Exclusive.Lootbox'),
        ('LuckyCat', 'gd_core_py.gd_core_items.Exclusive.LuckyCat'),
        ('LuckyShortbow', 'gd_core_py.gd_core_items.Exclusive.LuckyShortbow'),
        ('MageHat', 'gd_core_py.gd_core_items.Exclusive.MageHat'),
        ('MagicBadge', 'gd_core_py.gd_core_items.Exclusive.MagicBadge'),
        ('MagicCollar', 'gd_core_py.gd_core_items.Exclusive.MagicCollar'),
        ('MagicMirror', 'gd_core_py.gd_core_items.Exclusive.MagicMirror'),
        ('MagicRing', 'gd_core_py.gd_core_items.Exclusive.MagicRing'),
        ('MagiteccArmor', 'gd_core_py.gd_core_items.Exclusive.MagiteccArmor'),
        ('ManaCrystal', 'gd_core_py.gd_core_items.Exclusive.ManaCrystal'),
        ('ManaMastery', 'gd_core_py.gd_core_items.Exclusive.ManaMastery'),
        ('Mananana', 'gd_core_py.gd_core_items.Exclusive.Mananana'),
        ('Markswoman', 'gd_core_py.gd_core_items.Exclusive.Markswoman'),
        ('MechaBat', 'gd_core_py.gd_core_items.Exclusive.MechaBat'),
        ('MegaClover', 'gd_core_py.gd_core_items.Exclusive.MegaClover'),
        ('MercuryElemental', 'gd_core_py.gd_core_items.Exclusive.MercuryElemental'),
        ('MissFortune', 'gd_core_py.gd_core_items.Exclusive.MissFortune'),
        ('MoltenDagger', 'gd_core_py.gd_core_items.Exclusive.MoltenDagger'),
        ('MoltenGreatsword', 'gd_core_py.gd_core_items.Exclusive.MoltenGreatsword'),
        ('MoltenSpear', 'gd_core_py.gd_core_items.Exclusive.MoltenSpear'),
        ('MoltenSpear2', 'gd_core_py.gd_core_items.Exclusive.MoltenSpear2'),
        ('MoonArmor', 'gd_core_py.gd_core_items.Exclusive.MoonArmor'),
        ('MoreStats', 'gd_core_py.gd_core_items.Exclusive.MoreStats'),
        ('MrsStruggles', 'gd_core_py.gd_core_items.Exclusive.MrsStruggles'),
        ('MushroomFarm', 'gd_core_py.gd_core_items.Exclusive.MushroomFarm'),
        ('NoRushPlease', 'gd_core_py.gd_core_items.Exclusive.NoRushPlease'),
        ('NullBlade', 'gd_core_py.gd_core_items.Exclusive.NullBlade'),
        ('ObsidianDragon', 'gd_core_py.gd_core_items.Exclusive.ObsidianDragon'),
        ('OilLamp', 'gd_core_py.gd_core_items.Exclusive.OilLamp'),
        ('OnionCutter', 'gd_core_py.gd_core_items.Exclusive.OnionCutter'),
        ('OwlSpirit', 'gd_core_py.gd_core_items.Exclusive.OwlSpirit'),
        ('ParadiseBirb', 'gd_core_py.gd_core_items.Exclusive.ParadiseBirb'),
        ('PerpetuumMobile', 'gd_core_py.gd_core_items.Exclusive.PerpetuumMobile'),
        ('Phoenix', 'gd_core_py.gd_core_items.Exclusive.Phoenix'),
        ('Phoenix2', 'gd_core_py.gd_core_items.Exclusive.Phoenix2'),
        ('PiggyPinata', 'gd_core_py.gd_core_items.Exclusive.PiggyPinata'),
        ('PiggyofRiches', 'gd_core_py.gd_core_items.Exclusive.PiggyofRiches'),
        ('PineProtector', 'gd_core_py.gd_core_items.Exclusive.PineProtector'),
        ('PlasticCube', 'gd_core_py.gd_core_items.Exclusive.PlasticCube'),
        ('PoisonFrog', 'gd_core_py.gd_core_items.Exclusive.PoisonFrog'),
        ('PoisonGrenade', 'gd_core_py.gd_core_items.Exclusive.PoisonGrenade'),
        ('PoisonShortbow', 'gd_core_py.gd_core_items.Exclusive.PoisonShortbow'),
        ('PoisonSpear', 'gd_core_py.gd_core_items.Exclusive.PoisonSpear'),
        ('Pop', 'gd_core_py.gd_core_items.Exclusive.Pop'),
        ('PortableAltar', 'gd_core_py.gd_core_items.Exclusive.PortableAltar'),
        ('Pot', 'gd_core_py.gd_core_items.Exclusive.Pot'),
        ('PoweroftheMoon', 'gd_core_py.gd_core_items.Exclusive.PoweroftheMoon'),
        ('PrismaticSword', 'gd_core_py.gd_core_items.Exclusive.PrismaticSword'),
        ('PrismaticWand', 'gd_core_py.gd_core_items.Exclusive.PrismaticWand'),
        ('PuzzleBadge', 'gd_core_py.gd_core_items.Exclusive.PuzzleBadge'),
        ('PuzzlebagJ', 'gd_core_py.gd_core_items.Exclusive.PuzzlebagJ'),
        ('PuzzlebagL', 'gd_core_py.gd_core_items.Exclusive.PuzzlebagL'),
        ('PuzzlebagS', 'gd_core_py.gd_core_items.Exclusive.PuzzlebagS'),
        ('PuzzlebagT', 'gd_core_py.gd_core_items.Exclusive.PuzzlebagT'),
        ('PuzzlebagZ', 'gd_core_py.gd_core_items.Exclusive.PuzzlebagZ'),
        ('Puzzlebox', 'gd_core_py.gd_core_items.Exclusive.Puzzlebox'),
        ('RainbowBadge', 'gd_core_py.gd_core_items.Exclusive.RainbowBadge'),
        ('RainbowGoobertAdventurer', 'gd_core_py.gd_core_items.Exclusive.RainbowGoobertAdventurer'),
        ('RainbowGoobertBerserker', 'gd_core_py.gd_core_items.Exclusive.RainbowGoobertBerserker'),
        ('RainbowGoobertEngineer', 'gd_core_py.gd_core_items.Exclusive.RainbowGoobertEngineer'),
        ('RainbowGoobertMage', 'gd_core_py.gd_core_items.Exclusive.RainbowGoobertMage'),
        ('RainbowGoobertPyromancer', 'gd_core_py.gd_core_items.Exclusive.RainbowGoobertPyromancer'),
        ('RainbowOrb', 'gd_core_py.gd_core_items.Exclusive.RainbowOrb'),
        ('RainbowPotion', 'gd_core_py.gd_core_items.Exclusive.RainbowPotion'),
        ('RandomLoadoutBag', 'gd_core_py.gd_core_items.Exclusive.RandomLoadoutBag'),
        ('Rat', 'gd_core_py.gd_core_items.Exclusive.Rat'),
        ('RatChef', 'gd_core_py.gd_core_items.Exclusive.RatChef'),
        ('Recombobulator', 'gd_core_py.gd_core_items.Exclusive.Recombobulator'),
        ('RelicCase', 'gd_core_py.gd_core_items.Exclusive.RelicCase'),
        ('Repeater', 'gd_core_py.gd_core_items.Exclusive.Repeater'),
        ('Resistor', 'gd_core_py.gd_core_items.Exclusive.Resistor'),
        ('Reverse', 'gd_core_py.gd_core_items.Exclusive.Reverse'),
        ('Robodog', 'gd_core_py.gd_core_items.Exclusive.Robodog'),
        ('Rope', 'gd_core_py.gd_core_items.Exclusive.Rope'),
        ('Sandbag', 'gd_core_py.gd_core_items.Exclusive.Sandbag'),
        ('SapphireEgg', 'gd_core_py.gd_core_items.Exclusive.SapphireEgg'),
        ('SapphireWhelp', 'gd_core_py.gd_core_items.Exclusive.SapphireWhelp'),
        ('Scale', 'gd_core_py.gd_core_items.Exclusive.Scale'),
        ('ScholarBag', 'gd_core_py.gd_core_items.Exclusive.ScholarBag'),
        ('Scissorswords', 'gd_core_py.gd_core_items.Exclusive.Scissorswords'),
        ('SealtheDeal', 'gd_core_py.gd_core_items.Exclusive.SealtheDeal'),
        ('SerpentStaff', 'gd_core_py.gd_core_items.Exclusive.SerpentStaff'),
        ('SewingCase', 'gd_core_py.gd_core_items.Exclusive.SewingCase'),
        ('ShamanMask', 'gd_core_py.gd_core_items.Exclusive.ShamanMask'),
        ('ShellTotem', 'gd_core_py.gd_core_items.Exclusive.ShellTotem'),
        ('ShepherdsCrook', 'gd_core_py.gd_core_items.Exclusive.ShepherdsCrook'),
        ('Shielded', 'gd_core_py.gd_core_items.Exclusive.Shielded'),
        ('ShinyMantle', 'gd_core_py.gd_core_items.Exclusive.ShinyMantle'),
        ('ShinyShell', 'gd_core_py.gd_core_items.Exclusive.ShinyShell'),
        ('SkullBadge', 'gd_core_py.gd_core_items.Exclusive.SkullBadge'),
        ('SliceofBread', 'gd_core_py.gd_core_items.Exclusive.SliceofBread'),
        ('SliceofToast', 'gd_core_py.gd_core_items.Exclusive.SliceofToast'),
        ('SlimeTime', 'gd_core_py.gd_core_items.Exclusive.SlimeTime'),
        ('Sloth', 'gd_core_py.gd_core_items.Exclusive.Sloth'),
        ('SmellyBarrier', 'gd_core_py.gd_core_items.Exclusive.SmellyBarrier'),
        ('SmithingForDummies', 'gd_core_py.gd_core_items.Exclusive.SmithingForDummies'),
        ('Snake', 'gd_core_py.gd_core_items.Exclusive.Snake'),
        ('SnowStick', 'gd_core_py.gd_core_items.Exclusive.SnowStick'),
        ('Snowball', 'gd_core_py.gd_core_items.Exclusive.Snowball'),
        ('Snowcake', 'gd_core_py.gd_core_items.Exclusive.Snowcake'),
        ('Snowman', 'gd_core_py.gd_core_items.Exclusive.Snowman'),
        ('Snowmaster', 'gd_core_py.gd_core_items.Exclusive.Snowmaster'),
        ('Solaris', 'gd_core_py.gd_core_items.Exclusive.Solaris'),
        ('SpeakwithAnimals', 'gd_core_py.gd_core_items.Exclusive.SpeakwithAnimals'),
        ('SpellScrollDark', 'gd_core_py.gd_core_items.Exclusive.SpellScrollDark'),
        ('SpellScrollFrostbolt', 'gd_core_py.gd_core_items.Exclusive.SpellScrollFrostbolt'),
        ('SpellScrollIce', 'gd_core_py.gd_core_items.Exclusive.SpellScrollIce'),
        ('SpellScrollLight', 'gd_core_py.gd_core_items.Exclusive.SpellScrollLight'),
        ('SpellScrollNature', 'gd_core_py.gd_core_items.Exclusive.SpellScrollNature'),
        ('SpicyBanana', 'gd_core_py.gd_core_items.Exclusive.SpicyBanana'),
        ('SpikedCollar', 'gd_core_py.gd_core_items.Exclusive.SpikedCollar'),
        ('SpikedStaff', 'gd_core_py.gd_core_items.Exclusive.SpikedStaff'),
        ('SpikedWall', 'gd_core_py.gd_core_items.Exclusive.SpikedWall'),
        ('SpintoWin', 'gd_core_py.gd_core_items.Exclusive.SpintoWin'),
        ('SpiritBells', 'gd_core_py.gd_core_items.Exclusive.SpiritBells'),
        ('SpringLoader', 'gd_core_py.gd_core_items.Exclusive.SpringLoader'),
        ('Squirrel', 'gd_core_py.gd_core_items.Exclusive.Squirrel'),
        ('SquirrelArcher', 'gd_core_py.gd_core_items.Exclusive.SquirrelArcher'),
        ('StaffofFire', 'gd_core_py.gd_core_items.Exclusive.StaffofFire'),
        ('StarofCourage', 'gd_core_py.gd_core_items.Exclusive.StarofCourage'),
        ('SteelDragon', 'gd_core_py.gd_core_items.Exclusive.SteelDragon'),
        ('StoneArmor', 'gd_core_py.gd_core_items.Exclusive.StoneArmor'),
        ('StoneBadge', 'gd_core_py.gd_core_items.Exclusive.StoneBadge'),
        ('StoneGloves', 'gd_core_py.gd_core_items.Exclusive.StoneGloves'),
        ('StoneGolem', 'gd_core_py.gd_core_items.Exclusive.StoneGolem'),
        ('StoneShoes', 'gd_core_py.gd_core_items.Exclusive.StoneShoes'),
        ('Stoned', 'gd_core_py.gd_core_items.Exclusive.Stoned'),
        ('StrongDivinePotion', 'gd_core_py.gd_core_items.Exclusive.StrongDivinePotion'),
        ('VampiricPotion', 'gd_core_py.gd_core_items.Exclusive.VampiricPotion'),
        ('StrongVampiricPotion', 'gd_core_py.gd_core_items.Exclusive.StrongVampiricPotion'),
        ('SunArmor', 'gd_core_py.gd_core_items.Exclusive.SunArmor'),
        ('SunShield', 'gd_core_py.gd_core_items.Exclusive.SunShield'),
        ('TeslaCoil', 'gd_core_py.gd_core_items.Exclusive.TeslaCoil'),
        ('ThornElemental', 'gd_core_py.gd_core_items.Exclusive.ThornElemental'),
        ('ThornShortbow', 'gd_core_py.gd_core_items.Exclusive.ThornShortbow'),
        ('Thornbloom', 'gd_core_py.gd_core_items.Exclusive.Thornbloom'),
        ('Thornburst', 'gd_core_py.gd_core_items.Exclusive.Thornburst'),
        ('ThorsHammer', 'gd_core_py.gd_core_items.Exclusive.ThorsHammer'),
        ('ThunderDrake', 'gd_core_py.gd_core_items.Exclusive.ThunderDrake'),
        ('TigerRune', 'gd_core_py.gd_core_items.Exclusive.TigerRune'),
        ('TimeDilator', 'gd_core_py.gd_core_items.Exclusive.TimeDilator'),
        ('TimeMelting', 'gd_core_py.gd_core_items.Exclusive.TimeMelting'),
        ('TimePendant', 'gd_core_py.gd_core_items.Exclusive.TimePendant'),
        ('ToastGoobert', 'gd_core_py.gd_core_items.Exclusive.ToastGoobert'),
        ('Toolbox', 'gd_core_py.gd_core_items.Exclusive.Toolbox'),
        ('Turtle', 'gd_core_py.gd_core_items.Exclusive.Turtle'),
        ('Twine', 'gd_core_py.gd_core_items.Exclusive.Twine'),
        ('TwineBadge', 'gd_core_py.gd_core_items.Exclusive.TwineBadge'),
        ('Ukulele', 'gd_core_py.gd_core_items.Exclusive.Ukulele'),
        ('Ultima', 'gd_core_py.gd_core_items.Exclusive.Ultima'),
        ('UnidentifiedSkill', 'gd_core_py.gd_core_items.Exclusive.UnidentifiedSkill'),
        ('UniquelyUnique', 'gd_core_py.gd_core_items.Exclusive.UniquelyUnique'),
        ('VampiricCollar', 'gd_core_py.gd_core_items.Exclusive.VampiricCollar'),
        ('VineweaveBasket', 'gd_core_py.gd_core_items.Exclusive.VineweaveBasket'),
        ('Wand', 'gd_core_py.gd_core_items.Exclusive.Wand'),
        ('WandofDissonance', 'gd_core_py.gd_core_items.Exclusive.WandofDissonance'),
        ('WarScythe', 'gd_core_py.gd_core_items.Exclusive.WarScythe'),
        ('WaterElemental', 'gd_core_py.gd_core_items.Exclusive.WaterElemental'),
        ('Whetstone3', 'gd_core_py.gd_core_items.Exclusive.Whetstone3'),
        ('WingedBoots', 'gd_core_py.gd_core_items.Exclusive.WingedBoots'),
        ('Wisp', 'gd_core_py.gd_core_items.Exclusive.Wisp'),
        ('WolfBadge', 'gd_core_py.gd_core_items.Exclusive.WolfBadge'),
        ('WolfEmblem', 'gd_core_py.gd_core_items.Exclusive.WolfEmblem'),
        ('Wrench', 'gd_core_py.gd_core_items.Exclusive.Wrench'),
        ('ChessPiece', 'gd_core_py.gd_core_items.Exclusive.Chess.ChessPiece'),
        ('BlackBishop', 'gd_core_py.gd_core_items.Exclusive.Chess.BlackBishop'),
        ('BlackKing', 'gd_core_py.gd_core_items.Exclusive.Chess.BlackKing'),
        ('BlackKnight', 'gd_core_py.gd_core_items.Exclusive.Chess.BlackKnight'),
        ('BlackPawn', 'gd_core_py.gd_core_items.Exclusive.Chess.BlackPawn'),
        ('BlackQueen', 'gd_core_py.gd_core_items.Exclusive.Chess.BlackQueen'),
        ('BlackRook', 'gd_core_py.gd_core_items.Exclusive.Chess.BlackRook'),
        ('WhiteBishop', 'gd_core_py.gd_core_items.Exclusive.Chess.WhiteBishop'),
        ('WhiteKing', 'gd_core_py.gd_core_items.Exclusive.Chess.WhiteKing'),
        ('WhiteKnight', 'gd_core_py.gd_core_items.Exclusive.Chess.WhiteKnight'),
        ('WhitePawn', 'gd_core_py.gd_core_items.Exclusive.Chess.WhitePawn'),
        ('WhiteQueen', 'gd_core_py.gd_core_items.Exclusive.Chess.WhiteQueen'),
        ('WhiteRook', 'gd_core_py.gd_core_items.Exclusive.Chess.WhiteRook'),
        ('Amethyst', 'gd_core_py.gd_core_items.Gems.Amethyst'),
        ('CorruptedCrystal', 'gd_core_py.gd_core_items.Gems.CorruptedCrystal'),
        ('Emerald', 'gd_core_py.gd_core_items.Gems.Emerald'),
        ('LumpofCoal', 'gd_core_py.gd_core_items.Gems.LumpofCoal'),
        ('Ruby', 'gd_core_py.gd_core_items.Gems.Ruby'),
        ('Sapphire', 'gd_core_py.gd_core_items.Gems.Sapphire'),
        ('Skull', 'gd_core_py.gd_core_items.Gems.Skull'),
        ('Topaz', 'gd_core_py.gd_core_items.Gems.Topaz'),
    ]


_STEM2MOD = dict(_stem2mod_rows())


def load_all():
    """导入全部 gd 模块。返回导入失败清单（空 = 全部成功）。"""
    failed = []
    try:
        import gd_core_py.gd_core.CoreItem  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/CoreItem.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Item  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Item.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Card  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Card.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.AceofSpades  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/AceofSpades.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.RangerCollar  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/RangerCollar.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.AcornCollar  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/AcornCollar.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Stone  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Stone.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.ArtifactStoneCold  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/ArtifactStoneCold.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.ArtifactStoneHeat  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/ArtifactStoneHeat.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Bag  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Bag.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.BagofStones  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/BagofStones.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Food  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Food.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Banana  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Banana.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.BloodAmulet  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/BloodAmulet.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Goobert  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Goobert.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.BloodGoobert  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/BloodGoobert.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Weapon  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Weapon.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Bloodthorne  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Bloodthorne.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Dagger  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Dagger.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.BloodyDagger  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/BloodyDagger.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Blueberries  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Blueberries.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Bow  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Bow.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Bow  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Bow.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.BowandArrow  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/BowandArrow.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.BoxofRiches  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/BoxofRiches.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Broom  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Broom.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Gems.Gem  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Gems/Gem.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.BurningCoal  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/BurningCoal.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.BurningTorch  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/BurningTorch.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Card  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Card.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Carrot  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Carrot.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.CarrotGoobert  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/CarrotGoobert.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.ClawsofAttack  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/ClawsofAttack.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.CoreBuff  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/CoreBuff.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.CoreCharacter  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/CoreCharacter.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.CoreCombat  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/CoreCombat.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.CoreCombatLog  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/CoreCombatLog.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.CoreConst  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/CoreConst.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.CoreContext  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/CoreContext.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.CoreDamageResult  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/CoreDamageResult.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.CoreDamageSource  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/CoreDamageSource.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.CoreEvent  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/CoreEvent.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.CoreEventBus  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/CoreEventBus.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.CoreGrid  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/CoreGrid.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.CoreHooks  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/CoreHooks.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.CoreItemBook  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/CoreItemBook.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.CoreItemData  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/CoreItemData.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.CoreRng  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/CoreRng.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.CoreTimer  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/CoreTimer.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.CoreUtil  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/CoreUtil.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.CorruptedArmor  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/CorruptedArmor.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.CritwoodStaff  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/CritwoodStaff.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Crossblades  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Crossblades.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Crown  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Crown.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.CursedDagger  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/CursedDagger.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.CursedHairComb  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/CursedHairComb.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.CustomerCard  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/CustomerCard.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Dagger  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Dagger.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.DancingDragon  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/DancingDragon.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.DarkestLotus  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/DarkestLotus.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Darksaber  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Darksaber.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.DeathScythe  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/DeathScythe.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.DeckofCards  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/DeckofCards.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Potion  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Potion.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.DemonicFlask  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/DemonicFlask.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.DjinnLamp  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/DjinnLamp.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.DragonEgg  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/DragonEgg.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Pan  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Pan.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Eggscalibur  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Eggscalibur.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.EvilCap  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/EvilCap.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.FalconBlade  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/FalconBlade.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.FancyFencingRapier  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/FancyFencingRapier.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Fanfare  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Fanfare.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Bag  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Bag.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.FannyPack  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/FannyPack.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Flute  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Flute.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.FlyAgaric  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/FlyAgaric.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Food  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Food.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Garlic  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Garlic.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.GingerbreadMan  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/GingerbreadMan.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.GlovesofHaste  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/GlovesofHaste.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Goobert  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Goobert.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Greatsword  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Greatsword.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Hammer  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Hammer.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.HealingHerbs  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/HealingHerbs.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.HealthPotion  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/HealthPotion.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.HeartContainer  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/HeartContainer.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.HeartofDarkness  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/HeartofDarkness.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.HeroLongsword  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/HeroLongsword.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.HeroSword  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/HeroSword.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.HeroicPotion  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/HeroicPotion.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.HoloFireLizard  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/HoloFireLizard.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.HolyArmor  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/HolyArmor.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.HolySpear  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/HolySpear.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.HungryBlade  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/HungryBlade.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Item  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Item.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Jynxtorquilla  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Jynxtorquilla.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.LeatherArmor  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/LeatherArmor.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.LeatherBoots  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/LeatherBoots.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.LeatherHelm  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/LeatherHelm.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.LightGoobert  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/LightGoobert.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Lightsaber  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Lightsaber.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.LuckyBow  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/LuckyBow.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.LuckyClover  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/LuckyClover.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Piggybank  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Piggybank.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.LuckyPiggy  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/LuckyPiggy.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.MagicStaff  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/MagicStaff.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.MagicTorch  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/MagicTorch.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.ManaOrb  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/ManaOrb.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.ManaPotion  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/ManaPotion.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Manathirst  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Manathirst.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Shield  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Shield.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.MoonShield  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/MoonShield.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.MrStruggles  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/MrStruggles.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Pan  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Pan.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Pandamonium  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Pandamonium.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.PestilenceFlask  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/PestilenceFlask.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.PiercingArrow  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/PiercingArrow.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Piggybank  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Piggybank.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Pineapple  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Pineapple.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.PlatinCustomerCard  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/PlatinCustomerCard.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.PocketSand  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/PocketSand.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.PoisonBow  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/PoisonBow.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.PoisonDagger  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/PoisonDagger.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.PoisonGoobert  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/PoisonGoobert.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.PoisonIvy  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/PoisonIvy.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Potion  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Potion.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.PotionBelt  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/PotionBelt.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Present  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Present.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.ProtectivePurse  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/ProtectivePurse.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Pumpkin  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Pumpkin.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.RainbowGoobert  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/RainbowGoobert.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.RainbowGoobertRanger  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/RainbowGoobertRanger.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.RangerBag  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/RangerBag.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.RangerCollar  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/RangerCollar.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.RibSawBlade  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/RibSawBlade.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.RubyChonk  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/RubyChonk.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.DragonEgg  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/DragonEgg.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.RubyEgg  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/RubyEgg.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.RubyWhelp  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/RubyWhelp.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Shield  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Shield.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.ShieldofValor  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/ShieldofValor.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Shovel  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Shovel.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Spear  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Spear.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.SpectralDagger  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/SpectralDagger.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.SpikedShield  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/SpikedShield.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.StaffofUnhealing  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/StaffofUnhealing.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.StaminaSack  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/StaminaSack.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.SteelGoobert  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/SteelGoobert.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Stone  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Stone.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.LeatherHelm  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/LeatherHelm.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.StoneHelm  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/StoneHelm.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.StoneSkinPotion  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/StoneSkinPotion.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.StorageCoffin  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/StorageCoffin.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.StrongDemonicFlask  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/StrongDemonicFlask.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.HealthPotion  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/HealthPotion.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.StrongHealthPotion  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/StrongHealthPotion.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.PestilenceFlask  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/PestilenceFlask.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.StrongPestilenceFlask  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/StrongPestilenceFlask.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.StoneSkinPotion  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/StoneSkinPotion.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.StrongStoneSkinPotion  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/StrongStoneSkinPotion.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.TheFool  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/TheFool.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.TheLovers  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/TheLovers.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.ThornBow  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/ThornBow.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.ThornWhip  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/ThornWhip.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Torch  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Torch.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.VampiricArmor  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/VampiricArmor.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.VampiricGloves  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/VampiricGloves.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.VampiricScythe  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/VampiricScythe.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.VillainSword  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/VillainSword.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.WalrusTusk  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/WalrusTusk.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Weapon  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Weapon.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Whetstone  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Whetstone.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.White_EyesBlueDragon  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/White-EyesBlueDragon.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Wolpertinger  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Wolpertinger.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.WoodenBuckler  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/WoodenBuckler.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.WoodenSword  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/WoodenSword.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.YggdrasilLeaf  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/YggdrasilLeaf.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.AceofSpades  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/AceofSpades.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.AcornCollar  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/AcornCollar.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.ArtifactStoneCold  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/ArtifactStoneCold.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.ArtifactStoneHeat  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/ArtifactStoneHeat.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.BagofStones  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/BagofStones.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Banana  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Banana.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.BloodAmulet  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/BloodAmulet.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.BloodGoobert  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/BloodGoobert.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Bloodthorne  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Bloodthorne.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.BloodyDagger  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/BloodyDagger.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Blueberries  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Blueberries.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.BowandArrow  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/BowandArrow.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.BoxofRiches  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/BoxofRiches.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Broom  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Broom.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.BurningCoal  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/BurningCoal.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.BurningTorch  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/BurningTorch.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Carrot  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Carrot.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.CarrotGoobert  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/CarrotGoobert.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.ClawsofAttack  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/ClawsofAttack.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Coins  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Coins.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.CorruptedArmor  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/CorruptedArmor.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.CritwoodStaff  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/CritwoodStaff.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Crossblades  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Crossblades.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Crown  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Crown.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.CursedDagger  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/CursedDagger.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.CursedHairComb  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/CursedHairComb.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.CustomerCard  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/CustomerCard.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.DancingDragon  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/DancingDragon.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.DarkestLotus  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/DarkestLotus.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Darksaber  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Darksaber.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.DeathScythe  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/DeathScythe.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.DeckofCards  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/DeckofCards.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.DemonicFlask  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/DemonicFlask.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.DjinnLamp  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/DjinnLamp.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Eggscalibur  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Eggscalibur.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.EvilCap  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/EvilCap.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.FalconBlade  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/FalconBlade.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.FancyFencingRapier  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/FancyFencingRapier.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Fanfare  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Fanfare.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.FannyPack  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/FannyPack.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Flute  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Flute.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.FlyAgaric  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/FlyAgaric.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Garlic  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Garlic.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.GingerbreadMan  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/GingerbreadMan.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.GlovesofHaste  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/GlovesofHaste.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Greatsword  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Greatsword.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Hammer  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Hammer.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.HealingHerbs  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/HealingHerbs.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.HeartContainer  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/HeartContainer.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.HeartofDarkness  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/HeartofDarkness.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.HeroLongsword  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/HeroLongsword.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.HeroSword  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/HeroSword.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.HeroicPotion  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/HeroicPotion.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.HoloFireLizard  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/HoloFireLizard.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.HolyArmor  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/HolyArmor.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.HolySpear  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/HolySpear.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.HungryBlade  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/HungryBlade.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Jynxtorquilla  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Jynxtorquilla.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.LeatherArmor  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/LeatherArmor.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.LeatherBoots  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/LeatherBoots.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.LightGoobert  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/LightGoobert.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Lightsaber  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Lightsaber.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.LuckyBow  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/LuckyBow.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.LuckyClover  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/LuckyClover.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.LuckyPiggy  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/LuckyPiggy.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.MagicStaff  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/MagicStaff.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.MagicTorch  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/MagicTorch.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.ManaOrb  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/ManaOrb.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.ManaPotion  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/ManaPotion.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Manathirst  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Manathirst.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.MoonShield  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/MoonShield.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.MrStruggles  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/MrStruggles.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Pandamonium  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Pandamonium.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.PiercingArrow  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/PiercingArrow.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Pineapple  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Pineapple.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.PlatinCustomerCard  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/PlatinCustomerCard.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.PocketSand  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/PocketSand.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.PoisonBow  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/PoisonBow.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.PoisonDagger  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/PoisonDagger.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.PoisonGoobert  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/PoisonGoobert.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.PoisonIvy  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/PoisonIvy.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.PotionBelt  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/PotionBelt.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Present  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Present.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.ProtectivePurse  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/ProtectivePurse.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Pumpkin  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Pumpkin.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.RainbowGoobert  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/RainbowGoobert.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.RainbowGoobertRanger  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/RainbowGoobertRanger.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.RangerBag  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/RangerBag.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.RibSawBlade  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/RibSawBlade.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.RubyChonk  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/RubyChonk.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.RubyEgg  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/RubyEgg.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.RubyWhelp  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/RubyWhelp.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.ShieldofValor  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/ShieldofValor.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Shovel  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Shovel.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Spear  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Spear.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.SpectralDagger  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/SpectralDagger.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.SpikedShield  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/SpikedShield.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.StaffofUnhealing  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/StaffofUnhealing.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.StaminaSack  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/StaminaSack.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.SteelGoobert  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/SteelGoobert.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.StoneHelm  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/StoneHelm.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.StorageCoffin  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/StorageCoffin.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.StrongDemonicFlask  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/StrongDemonicFlask.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.StrongHealthPotion  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/StrongHealthPotion.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.StrongPestilenceFlask  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/StrongPestilenceFlask.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.StrongStoneSkinPotion  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/StrongStoneSkinPotion.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.TheFool  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/TheFool.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.TheLovers  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/TheLovers.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.ThornBow  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/ThornBow.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.ThornWhip  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/ThornWhip.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Torch  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Torch.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.VampiricArmor  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/VampiricArmor.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.VampiricGloves  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/VampiricGloves.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.VampiricScythe  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/VampiricScythe.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.VillainSword  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/VillainSword.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.WalrusTusk  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/WalrusTusk.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Whetstone  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Whetstone.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.White_EyesBlueDragon  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/White-EyesBlueDragon.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Wolpertinger  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Wolpertinger.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.WoodenBuckler  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/WoodenBuckler.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.WoodenSword  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/WoodenSword.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.YggdrasilLeaf  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/YggdrasilLeaf.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.AcornAce  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/AcornAce.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.AmethystEgg  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/AmethystEgg.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.AmethystWhelp  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/AmethystWhelp.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.AmuletUnidentified  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/AmuletUnidentified.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.AmuletofAgility  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/AmuletofAgility.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.AmuletofAlchemy  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/AmuletofAlchemy.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.AmuletofDarkness  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/AmuletofDarkness.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.AmuletofFeasting  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/AmuletofFeasting.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.AmuletofFortune  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/AmuletofFortune.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.AmuletofLife  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/AmuletofLife.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.AmuletofLight  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/AmuletofLight.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.AmuletofSteel  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/AmuletofSteel.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.AmuletoftheWild  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/AmuletoftheWild.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.AngelCrystal  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/AngelCrystal.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Anvil  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Anvil.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.ArcaneBoots  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/ArcaneBoots.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.ArcaneIntellect  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/ArcaneIntellect.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.CouragePuppy  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/CouragePuppy.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.ArmoredCouragePuppy  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/ArmoredCouragePuppy.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.PowerPuppy  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/PowerPuppy.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.ArmoredPowerPuppy  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/ArmoredPowerPuppy.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.WisdomPuppy  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/WisdomPuppy.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.ArmoredWisdomPuppy  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/ArmoredWisdomPuppy.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.ArtifactStoneDeath  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/ArtifactStoneDeath.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Automanaton  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Automanaton.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Axe  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Axe.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.BadgerRune  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/BadgerRune.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.SpiritCompanion  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/SpiritCompanion.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.BadgerSpirit  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/BadgerSpirit.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.BagofGiving  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/BagofGiving.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Bagtacular  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Bagtacular.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Battery  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Battery.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Bazooka  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Bazooka.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.BerserkerBag  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/BerserkerBag.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Bewitchment  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Bewitchment.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.BigBloodthorne  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/BigBloodthorne.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.BionicArmor  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/BionicArmor.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Cube  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Cube.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.BismuthCube  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/BismuthCube.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.BloodManipulation  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/BloodManipulation.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Bomb  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Bomb.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.BookofBasics  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/BookofBasics.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.BookofDarkness  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/BookofDarkness.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.BookofIce  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/BookofIce.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.BookofLight  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/BookofLight.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.BookofNature  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/BookofNature.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Boomerang  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Boomerang.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.BowlofTreats  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/BowlofTreats.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.BoxofProsperity  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/BoxofProsperity.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.BrassKnuckles  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/BrassKnuckles.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Broccoli  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Broccoli.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.BroccoliGoobert  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/BroccoliGoobert.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Broccotree  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Broccotree.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.BurningBanner  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/BurningBanner.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.BurningSword  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/BurningSword.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.BurningBlade  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/BurningBlade.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.BurningSpikes  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/BurningSpikes.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.BustedBlade  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/BustedBlade.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.BuytheHolyLight  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/BuytheHolyLight.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.CapofBrilliance  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/CapofBrilliance.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.CatSpirit  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/CatSpirit.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Cauldron  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Cauldron.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.ChainWhip  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/ChainWhip.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Chainsaw  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Chainsaw.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.ChargeSplitter  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/ChargeSplitter.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Cheese  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Cheese.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.CheeseGoobert  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/CheeseGoobert.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.ChessBoard  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/ChessBoard.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.ChessMaster  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/ChessMaster.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.ChiliGoobert  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/ChiliGoobert.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.ChiliPepper  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/ChiliPepper.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.ChromeCube  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/ChromeCube.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Cog  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Cog.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.CogBadge  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/CogBadge.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Coil  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Coil.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.ConTrapTron  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/ConTrapTron.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.CriticalPoison  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/CriticalPoison.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Crow  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Crow.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Cthulhu  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Cthulhu.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Cubert  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Cubert.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Cupcake  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Cupcake.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.CupcakeDragon  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/CupcakeDragon.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.CupcakeGoobert  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/CupcakeGoobert.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.CupcakeStaff  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/CupcakeStaff.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Daggerang  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Daggerang.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.DarkLantern  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/DarkLantern.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.DarkRitual  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/DarkRitual.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.DeathLotus  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/DeathLotus.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.DeerTotem  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/DeerTotem.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.DevouringSphere  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/DevouringSphere.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.DigDeeper  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/DigDeeper.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.DivinePotion  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/DivinePotion.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.DoomCap  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/DoomCap.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.DoubleAxe  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/DoubleAxe.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.DoubleRainbow  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/DoubleRainbow.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.DraconicOrb  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/DraconicOrb.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.DragonClaws  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/DragonClaws.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.DragonKnight  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/DragonKnight.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.DragonNest  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/DragonNest.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.DragonSet  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/DragonSet.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.DragonscaleArmor  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/DragonscaleArmor.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.DragonskinBoots  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/DragonskinBoots.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.DualWielding  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/DualWielding.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Eat_o_matic  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Eat-o-matic.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.EchoingBattlecry  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/EchoingBattlecry.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.ElectricTorch  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/ElectricTorch.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.ElephantRune  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/ElephantRune.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.EmeraldEgg  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/EmeraldEgg.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.EmeraldWhelp  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/EmeraldWhelp.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.EmployeeUniform  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/EmployeeUniform.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.EnchantedWeapons  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/EnchantedWeapons.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.EnergyConversion  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/EnergyConversion.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.EngineerBag2  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/EngineerBag2.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.EngineerBox  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/EngineerBox.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Everburning  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Everburning.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.EvilHat  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/EvilHat.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.ExtraAngy  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/ExtraAngy.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.ExtraBags  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/ExtraBags.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.FalseLife  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/FalseLife.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Fedora  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Fedora.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.FirePit  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/FirePit.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Shelly  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Shelly.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.FireShelly  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/FireShelly.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Flame  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Flame.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.FlameBadge  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/FlameBadge.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.FlameWhip  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/FlameWhip.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.ForestDragon  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/ForestDragon.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.ForestFriend  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/ForestFriend.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.ForgingHammer  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/ForgingHammer.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.FortunasKiss  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/FortunasKiss.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.FriendlyFire  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/FriendlyFire.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Toad  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Toad.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.FrogPrince  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/FrogPrince.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Frostbite  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Frostbite.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.FrozenBuckler  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/FrozenBuckler.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.FrozenFlame  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/FrozenFlame.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.FullBodyProtection  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/FullBodyProtection.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.FurciferPrime  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/FurciferPrime.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Generator  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Generator.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Ghost  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Ghost.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Gigawatz  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Gigawatz.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.GirlPower  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/GirlPower.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.GoldArmor  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/GoldArmor.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.GoldCube  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/GoldCube.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Halberd  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Halberd.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Hardwood  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Hardwood.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.HawkRune  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/HawkRune.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.HeartShield  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/HeartShield.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.HeartoftheCards  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/HeartoftheCards.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.HeavyDrinking  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/HeavyDrinking.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Hedgehog  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Hedgehog.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.HeroShield  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/HeroShield.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.HogusBogus  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/HogusBogus.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Holdall  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Holdall.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.HolyCollar  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/HolyCollar.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.HyperHedgehog  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/HyperHedgehog.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Hypercube  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Hypercube.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.IceArmor  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/IceArmor.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.IceDragon  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/IceDragon.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.IceFlower  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/IceFlower.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.InnerPower  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/InnerPower.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.InvestmentOpportunity  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/InvestmentOpportunity.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Joker  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Joker.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.JustStats  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/JustStats.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.JynxStaff  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/JynxStaff.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Katana  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Katana.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.KingCrown  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/KingCrown.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.KingGoobert  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/KingGoobert.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.KingoftheBling  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/KingoftheBling.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.KnifetoMeetYou  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/KnifetoMeetYou.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Laboratory  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Laboratory.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.LeafBadge  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/LeafBadge.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.LevelUp  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/LevelUp.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.LightFlower  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/LightFlower.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.LightningPotion  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/LightningPotion.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.LightningStaff  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/LightningStaff.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.LittleMimic  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/LittleMimic.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.LongSpear  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/LongSpear.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Lootbox  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Lootbox.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.LuckyCat  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/LuckyCat.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.LuckyShortbow  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/LuckyShortbow.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.MageHat  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/MageHat.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.MagicBadge  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/MagicBadge.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.MagicCollar  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/MagicCollar.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.MagicMirror  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/MagicMirror.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.MagicRing  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/MagicRing.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.MagiteccArmor  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/MagiteccArmor.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.ManaCrystal  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/ManaCrystal.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.ManaMastery  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/ManaMastery.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Mananana  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Mananana.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Markswoman  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Markswoman.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.MechaBat  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/MechaBat.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.MegaClover  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/MegaClover.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.MercuryElemental  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/MercuryElemental.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.MissFortune  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/MissFortune.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.MoltenDagger  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/MoltenDagger.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.MoltenGreatsword  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/MoltenGreatsword.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.MoltenSpear  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/MoltenSpear.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.MoltenSpear2  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/MoltenSpear2.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.MoonArmor  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/MoonArmor.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.MoreStats  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/MoreStats.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.MrsStruggles  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/MrsStruggles.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.MushroomFarm  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/MushroomFarm.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.NoRushPlease  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/NoRushPlease.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.NullBlade  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/NullBlade.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.ObsidianDragon  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/ObsidianDragon.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.OilLamp  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/OilLamp.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.OnionCutter  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/OnionCutter.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.OwlSpirit  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/OwlSpirit.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.ParadiseBirb  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/ParadiseBirb.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.PerpetuumMobile  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/PerpetuumMobile.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Phoenix  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Phoenix.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Phoenix2  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Phoenix2.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.PiggyPinata  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/PiggyPinata.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.PiggyofRiches  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/PiggyofRiches.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.PineProtector  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/PineProtector.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.PlasticCube  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/PlasticCube.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.PoisonFrog  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/PoisonFrog.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.PoisonGrenade  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/PoisonGrenade.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.PoisonShortbow  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/PoisonShortbow.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.PoisonSpear  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/PoisonSpear.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Pop  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Pop.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.PortableAltar  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/PortableAltar.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Pot  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Pot.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.PoweroftheMoon  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/PoweroftheMoon.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.PrismaticSword  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/PrismaticSword.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.PrismaticWand  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/PrismaticWand.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.PuzzleBadge  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/PuzzleBadge.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.PuzzlebagJ  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/PuzzlebagJ.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.PuzzlebagL  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/PuzzlebagL.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.PuzzlebagS  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/PuzzlebagS.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.PuzzlebagT  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/PuzzlebagT.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.PuzzlebagZ  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/PuzzlebagZ.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Puzzlebox  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Puzzlebox.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.RainbowBadge  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/RainbowBadge.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.RainbowGoobertAdventurer  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/RainbowGoobertAdventurer.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.RainbowGoobertBerserker  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/RainbowGoobertBerserker.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.RainbowGoobertEngineer  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/RainbowGoobertEngineer.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.RainbowGoobertMage  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/RainbowGoobertMage.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.RainbowGoobertPyromancer  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/RainbowGoobertPyromancer.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.RainbowOrb  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/RainbowOrb.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.RainbowPotion  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/RainbowPotion.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.RandomLoadoutBag  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/RandomLoadoutBag.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Rat  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Rat.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.RatChef  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/RatChef.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Recombobulator  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Recombobulator.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.RelicCase  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/RelicCase.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Repeater  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Repeater.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Resistor  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Resistor.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Reverse  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Reverse.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Robodog  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Robodog.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Rope  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Rope.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Sandbag  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Sandbag.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.SapphireEgg  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/SapphireEgg.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.SapphireWhelp  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/SapphireWhelp.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Scale  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Scale.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.ScholarBag  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/ScholarBag.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Scissorswords  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Scissorswords.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.SealtheDeal  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/SealtheDeal.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.SerpentStaff  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/SerpentStaff.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.SewingCase  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/SewingCase.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.ShamanMask  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/ShamanMask.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.ShellTotem  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/ShellTotem.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.ShepherdsCrook  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/ShepherdsCrook.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Shielded  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Shielded.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.ShinyMantle  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/ShinyMantle.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.ShinyShell  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/ShinyShell.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.SkullBadge  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/SkullBadge.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.SliceofBread  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/SliceofBread.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.SliceofToast  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/SliceofToast.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.SlimeTime  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/SlimeTime.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Sloth  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Sloth.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.SmellyBarrier  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/SmellyBarrier.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.SmithingForDummies  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/SmithingForDummies.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Snake  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Snake.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.SnowStick  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/SnowStick.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Snowball  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Snowball.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Snowcake  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Snowcake.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Snowman  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Snowman.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Snowmaster  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Snowmaster.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Solaris  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Solaris.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.SpeakwithAnimals  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/SpeakwithAnimals.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.SpellScrollDark  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/SpellScrollDark.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.SpellScrollFrostbolt  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/SpellScrollFrostbolt.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.SpellScrollIce  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/SpellScrollIce.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.SpellScrollLight  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/SpellScrollLight.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.SpellScrollNature  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/SpellScrollNature.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.SpicyBanana  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/SpicyBanana.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.SpikedCollar  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/SpikedCollar.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.SpikedStaff  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/SpikedStaff.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.SpikedWall  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/SpikedWall.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.SpintoWin  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/SpintoWin.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.SpiritBells  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/SpiritBells.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.SpringLoader  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/SpringLoader.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Squirrel  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Squirrel.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.SquirrelArcher  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/SquirrelArcher.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.StaffofFire  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/StaffofFire.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.StarofCourage  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/StarofCourage.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.SteelDragon  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/SteelDragon.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.StoneArmor  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/StoneArmor.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.StoneBadge  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/StoneBadge.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.StoneGloves  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/StoneGloves.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.StoneGolem  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/StoneGolem.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.StoneShoes  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/StoneShoes.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Stoned  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Stoned.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.StrongDivinePotion  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/StrongDivinePotion.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.VampiricPotion  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/VampiricPotion.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.StrongVampiricPotion  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/StrongVampiricPotion.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.SunArmor  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/SunArmor.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.SunShield  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/SunShield.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.TeslaCoil  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/TeslaCoil.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.ThornElemental  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/ThornElemental.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.ThornShortbow  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/ThornShortbow.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Thornbloom  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Thornbloom.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Thornburst  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Thornburst.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.ThorsHammer  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/ThorsHammer.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.ThunderDrake  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/ThunderDrake.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.TigerRune  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/TigerRune.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.TimeDilator  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/TimeDilator.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.TimeMelting  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/TimeMelting.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.TimePendant  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/TimePendant.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.ToastGoobert  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/ToastGoobert.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Toolbox  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Toolbox.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Turtle  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Turtle.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Twine  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Twine.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.TwineBadge  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/TwineBadge.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Ukulele  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Ukulele.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Ultima  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Ultima.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.UnidentifiedSkill  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/UnidentifiedSkill.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.UniquelyUnique  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/UniquelyUnique.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.VampiricCollar  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/VampiricCollar.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.VineweaveBasket  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/VineweaveBasket.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Wand  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Wand.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.WandofDissonance  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/WandofDissonance.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.WarScythe  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/WarScythe.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.WaterElemental  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/WaterElemental.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Whetstone3  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Whetstone3.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.WingedBoots  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/WingedBoots.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Wisp  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Wisp.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.WolfBadge  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/WolfBadge.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.WolfEmblem  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/WolfEmblem.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Wrench  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Wrench.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Chess.ChessPiece  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Chess/ChessPiece.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Chess.BlackBishop  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Chess/BlackBishop.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Chess.BlackKing  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Chess/BlackKing.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Chess.BlackKnight  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Chess/BlackKnight.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Chess.BlackPawn  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Chess/BlackPawn.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Chess.BlackQueen  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Chess/BlackQueen.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Chess.BlackRook  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Chess/BlackRook.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Chess.WhiteBishop  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Chess/WhiteBishop.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Chess.WhiteKing  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Chess/WhiteKing.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Chess.WhiteKnight  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Chess/WhiteKnight.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Chess.WhitePawn  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Chess/WhitePawn.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Chess.WhiteQueen  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Chess/WhiteQueen.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Exclusive.Chess.WhiteRook  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Exclusive/Chess/WhiteRook.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Gems.Amethyst  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Gems/Amethyst.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Gems.CorruptedCrystal  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Gems/CorruptedCrystal.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Gems.Emerald  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Gems/Emerald.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Gems.LumpofCoal  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Gems/LumpofCoal.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Gems.Ruby  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Gems/Ruby.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Gems.Sapphire  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Gems/Sapphire.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Gems.Skull  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Gems/Skull.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Gems.Topaz  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Gems/Topaz.gd', repr(exc)))
    return failed


# 物品树 extends 父链（生成期从 GDScript extends 段提取，仅 items 树内父）
_ITEM_PARENTS = {
    'gd_core_items/Card.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/RangerCollar.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Stone.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Food.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Goobert.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Weapon.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Dagger.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Bow.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Gems/Gem.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Potion.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Pan.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Bag.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Piggybank.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Shield.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/DragonEgg.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/LeatherHelm.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/HealthPotion.gd': ['gd_core_items/Item.gd', 'gd_core_items/Potion.gd'],
    'gd_core_items/PestilenceFlask.gd': ['gd_core_items/Item.gd', 'gd_core_items/Potion.gd'],
    'gd_core_items/StoneSkinPotion.gd': ['gd_core_items/Item.gd', 'gd_core_items/Potion.gd'],
    'gd_core_items/AceofSpades.gd': ['gd_core_items/Card.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/AcornCollar.gd': ['gd_core_items/Item.gd', 'gd_core_items/RangerCollar.gd'],
    'gd_core_items/ArtifactStoneCold.gd': ['gd_core_items/Item.gd', 'gd_core_items/Stone.gd'],
    'gd_core_items/ArtifactStoneHeat.gd': ['gd_core_items/Item.gd', 'gd_core_items/Stone.gd'],
    'gd_core_items/BagofStones.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Banana.gd': ['gd_core_items/Food.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/BloodAmulet.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/BloodGoobert.gd': ['gd_core_items/Goobert.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Bloodthorne.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/BloodyDagger.gd': ['gd_core_items/Dagger.gd', 'gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Blueberries.gd': ['gd_core_items/Food.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/BowandArrow.gd': ['gd_core_items/Bow.gd', 'gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/BoxofRiches.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Broom.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/BurningCoal.gd': ['gd_core_items/Gems/Gem.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/BurningTorch.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Carrot.gd': ['gd_core_items/Food.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/CarrotGoobert.gd': ['gd_core_items/Goobert.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/ClawsofAttack.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Coins.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/CorruptedArmor.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/CritwoodStaff.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Crossblades.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Crown.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/CursedDagger.gd': ['gd_core_items/Dagger.gd', 'gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/CursedHairComb.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/CustomerCard.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/DancingDragon.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/DarkestLotus.gd': ['gd_core_items/Card.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Darksaber.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/DeathScythe.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/DeckofCards.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/DemonicFlask.gd': ['gd_core_items/Item.gd', 'gd_core_items/Potion.gd'],
    'gd_core_items/DjinnLamp.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Eggscalibur.gd': ['gd_core_items/Item.gd', 'gd_core_items/Pan.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/EvilCap.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/FalconBlade.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/FancyFencingRapier.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Fanfare.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/FannyPack.gd': ['gd_core_items/Bag.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Flute.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/FlyAgaric.gd': ['gd_core_items/Food.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Garlic.gd': ['gd_core_items/Food.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/GingerbreadMan.gd': ['gd_core_items/Food.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/GlovesofHaste.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Greatsword.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Hammer.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/HealingHerbs.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/HeartContainer.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/HeartofDarkness.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/HeroLongsword.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/HeroSword.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/HeroicPotion.gd': ['gd_core_items/Item.gd', 'gd_core_items/Potion.gd'],
    'gd_core_items/HoloFireLizard.gd': ['gd_core_items/Card.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/HolyArmor.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/HolySpear.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/HungryBlade.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Jynxtorquilla.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/LeatherArmor.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/LeatherBoots.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/LightGoobert.gd': ['gd_core_items/Goobert.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Lightsaber.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/LuckyBow.gd': ['gd_core_items/Bow.gd', 'gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/LuckyClover.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/LuckyPiggy.gd': ['gd_core_items/Item.gd', 'gd_core_items/Piggybank.gd'],
    'gd_core_items/MagicStaff.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/MagicTorch.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/ManaOrb.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/ManaPotion.gd': ['gd_core_items/Item.gd', 'gd_core_items/Potion.gd'],
    'gd_core_items/Manathirst.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/MoonShield.gd': ['gd_core_items/Item.gd', 'gd_core_items/Shield.gd'],
    'gd_core_items/MrStruggles.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Pandamonium.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/PiercingArrow.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Pineapple.gd': ['gd_core_items/Food.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/PlatinCustomerCard.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/PocketSand.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/PoisonBow.gd': ['gd_core_items/Bow.gd', 'gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/PoisonDagger.gd': ['gd_core_items/Dagger.gd', 'gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/PoisonGoobert.gd': ['gd_core_items/Goobert.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/PoisonIvy.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/PotionBelt.gd': ['gd_core_items/Bag.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Present.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/ProtectivePurse.gd': ['gd_core_items/Bag.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Pumpkin.gd': ['gd_core_items/Food.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/RainbowGoobert.gd': ['gd_core_items/Goobert.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/RainbowGoobertRanger.gd': ['gd_core_items/Goobert.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/RangerBag.gd': ['gd_core_items/Bag.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/RibSawBlade.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/RubyChonk.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/RubyEgg.gd': ['gd_core_items/DragonEgg.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/RubyWhelp.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/ShieldofValor.gd': ['gd_core_items/Item.gd', 'gd_core_items/Shield.gd'],
    'gd_core_items/Shovel.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Spear.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/SpectralDagger.gd': ['gd_core_items/Dagger.gd', 'gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/SpikedShield.gd': ['gd_core_items/Item.gd', 'gd_core_items/Shield.gd'],
    'gd_core_items/StaffofUnhealing.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/StaminaSack.gd': ['gd_core_items/Bag.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/SteelGoobert.gd': ['gd_core_items/Goobert.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/StoneHelm.gd': ['gd_core_items/Item.gd', 'gd_core_items/LeatherHelm.gd'],
    'gd_core_items/StorageCoffin.gd': ['gd_core_items/Bag.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/StrongDemonicFlask.gd': ['gd_core_items/Item.gd', 'gd_core_items/Potion.gd'],
    'gd_core_items/StrongHealthPotion.gd': ['gd_core_items/HealthPotion.gd', 'gd_core_items/Item.gd', 'gd_core_items/Potion.gd'],
    'gd_core_items/StrongPestilenceFlask.gd': ['gd_core_items/Item.gd', 'gd_core_items/PestilenceFlask.gd', 'gd_core_items/Potion.gd'],
    'gd_core_items/StrongStoneSkinPotion.gd': ['gd_core_items/Item.gd', 'gd_core_items/Potion.gd', 'gd_core_items/StoneSkinPotion.gd'],
    'gd_core_items/TheFool.gd': ['gd_core_items/Card.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/TheLovers.gd': ['gd_core_items/Card.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/ThornBow.gd': ['gd_core_items/Bow.gd', 'gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/ThornWhip.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Torch.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/VampiricArmor.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/VampiricGloves.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/VampiricScythe.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/VillainSword.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/WalrusTusk.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Whetstone.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/White-EyesBlueDragon.gd': ['gd_core_items/Card.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Wolpertinger.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/WoodenBuckler.gd': ['gd_core_items/Item.gd', 'gd_core_items/Shield.gd'],
    'gd_core_items/WoodenSword.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/YggdrasilLeaf.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/AcornAce.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/AmethystEgg.gd': ['gd_core_items/DragonEgg.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/AmethystWhelp.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/AmuletUnidentified.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/AmuletofAgility.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/AmuletofAlchemy.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/AmuletofDarkness.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/AmuletofFeasting.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/AmuletofFortune.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/AmuletofLife.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/AmuletofLight.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/AmuletofSteel.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/AmuletoftheWild.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/AngelCrystal.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Anvil.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/ArcaneBoots.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/ArcaneIntellect.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/CouragePuppy.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/ArmoredCouragePuppy.gd': ['gd_core_items/Exclusive/CouragePuppy.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/PowerPuppy.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/ArmoredPowerPuppy.gd': ['gd_core_items/Exclusive/PowerPuppy.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/WisdomPuppy.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/ArmoredWisdomPuppy.gd': ['gd_core_items/Exclusive/WisdomPuppy.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/ArtifactStoneDeath.gd': ['gd_core_items/Item.gd', 'gd_core_items/Stone.gd'],
    'gd_core_items/Exclusive/Automanaton.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/Axe.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/BadgerRune.gd': ['gd_core_items/Gems/Gem.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/SpiritCompanion.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/BadgerSpirit.gd': ['gd_core_items/Exclusive/SpiritCompanion.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/BagofGiving.gd': ['gd_core_items/Bag.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Bagtacular.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Battery.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Bazooka.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/BerserkerBag.gd': ['gd_core_items/Bag.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Bewitchment.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/BigBloodthorne.gd': ['gd_core_items/Greatsword.gd', 'gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/BionicArmor.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Cube.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/BismuthCube.gd': ['gd_core_items/Exclusive/Cube.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/BloodManipulation.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Bomb.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/BookofBasics.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/BookofDarkness.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/BookofIce.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/BookofLight.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/BookofNature.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Boomerang.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/BowlofTreats.gd': ['gd_core_items/Food.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/BoxofProsperity.gd': ['gd_core_items/Bag.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/BrassKnuckles.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/Broccoli.gd': ['gd_core_items/Food.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/BroccoliGoobert.gd': ['gd_core_items/Goobert.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Broccotree.gd': ['gd_core_items/Food.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/BurningBanner.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/BurningSword.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/BurningBlade.gd': ['gd_core_items/Exclusive/BurningSword.gd', 'gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/BurningSpikes.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/BustedBlade.gd': ['gd_core_items/Greatsword.gd', 'gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/BuytheHolyLight.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/CapofBrilliance.gd': ['gd_core_items/Item.gd', 'gd_core_items/LeatherHelm.gd'],
    'gd_core_items/Exclusive/CatSpirit.gd': ['gd_core_items/Exclusive/SpiritCompanion.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Cauldron.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/ChainWhip.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/Chainsaw.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/ChargeSplitter.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Cheese.gd': ['gd_core_items/Food.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/CheeseGoobert.gd': ['gd_core_items/Goobert.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/ChessBoard.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/ChessMaster.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/ChiliGoobert.gd': ['gd_core_items/Goobert.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/ChiliPepper.gd': ['gd_core_items/Food.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/ChromeCube.gd': ['gd_core_items/Exclusive/Cube.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Cog.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/CogBadge.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Coil.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/ConTrapTron.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/CriticalPoison.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Crow.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Cthulhu.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Cubert.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Cupcake.gd': ['gd_core_items/Food.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/CupcakeDragon.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/CupcakeGoobert.gd': ['gd_core_items/Goobert.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/CupcakeStaff.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/Daggerang.gd': ['gd_core_items/Dagger.gd', 'gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/DarkLantern.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/DarkRitual.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/DeathLotus.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/DeerTotem.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/DevouringSphere.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/DigDeeper.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/DivinePotion.gd': ['gd_core_items/Item.gd', 'gd_core_items/Potion.gd'],
    'gd_core_items/Exclusive/DoomCap.gd': ['gd_core_items/Food.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/DoubleAxe.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/DoubleRainbow.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/DraconicOrb.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/DragonClaws.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/DragonKnight.gd': ['gd_core_items/Item.gd', 'gd_core_items/RubyWhelp.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/DragonNest.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/DragonSet.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/DragonscaleArmor.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/DragonskinBoots.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/DualWielding.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Eat-o-matic.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/EchoingBattlecry.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/ElectricTorch.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/ElephantRune.gd': ['gd_core_items/Gems/Gem.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/EmeraldEgg.gd': ['gd_core_items/DragonEgg.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/EmeraldWhelp.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/EmployeeUniform.gd': ['gd_core_items/Item.gd', 'gd_core_items/LeatherArmor.gd'],
    'gd_core_items/Exclusive/EnchantedWeapons.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/EnergyConversion.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/EngineerBag2.gd': ['gd_core_items/Bag.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/EngineerBox.gd': ['gd_core_items/Bag.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Everburning.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/EvilHat.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/ExtraAngy.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/ExtraBags.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/FalseLife.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Fedora.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/FirePit.gd': ['gd_core_items/Bag.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Shelly.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/FireShelly.gd': ['gd_core_items/Exclusive/Shelly.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Flame.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/FlameBadge.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/FlameWhip.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/ForestDragon.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/ForestFriend.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/ForgingHammer.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/FortunasKiss.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/FriendlyFire.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Toad.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/FrogPrince.gd': ['gd_core_items/Exclusive/Toad.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Frostbite.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/FrozenBuckler.gd': ['gd_core_items/Item.gd', 'gd_core_items/Shield.gd'],
    'gd_core_items/Exclusive/FrozenFlame.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/FullBodyProtection.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/FurciferPrime.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Generator.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Ghost.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Gigawatz.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/GirlPower.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/GoldArmor.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/GoldCube.gd': ['gd_core_items/Exclusive/Cube.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Halberd.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/Hardwood.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/HawkRune.gd': ['gd_core_items/Gems/Gem.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/HeartShield.gd': ['gd_core_items/Item.gd', 'gd_core_items/Shield.gd'],
    'gd_core_items/Exclusive/HeartoftheCards.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/HeavyDrinking.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Hedgehog.gd': ['gd_core_items/Exclusive/ForestFriend.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/HeroShield.gd': ['gd_core_items/Item.gd', 'gd_core_items/Shield.gd', 'gd_core_items/WoodenBuckler.gd'],
    'gd_core_items/Exclusive/HogusBogus.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Holdall.gd': ['gd_core_items/Bag.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/HolyCollar.gd': ['gd_core_items/Item.gd', 'gd_core_items/RangerCollar.gd'],
    'gd_core_items/Exclusive/HyperHedgehog.gd': ['gd_core_items/Exclusive/ForestFriend.gd', 'gd_core_items/Exclusive/Hedgehog.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Hypercube.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/IceArmor.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/IceDragon.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/IceFlower.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/InnerPower.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/InvestmentOpportunity.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Joker.gd': ['gd_core_items/Card.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/JustStats.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/JynxStaff.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/Katana.gd': ['gd_core_items/Item.gd', 'gd_core_items/RibSawBlade.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/KingCrown.gd': ['gd_core_items/Crown.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/KingGoobert.gd': ['gd_core_items/Goobert.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/KingoftheBling.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/KnifetoMeetYou.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Laboratory.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/LeafBadge.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/LevelUp.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/LightFlower.gd': ['gd_core_items/Food.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/LightningPotion.gd': ['gd_core_items/Item.gd', 'gd_core_items/Potion.gd'],
    'gd_core_items/Exclusive/LightningStaff.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/LittleMimic.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/LongSpear.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/Lootbox.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/LuckyCat.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/LuckyShortbow.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/MageHat.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/MagicBadge.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/MagicCollar.gd': ['gd_core_items/Item.gd', 'gd_core_items/RangerCollar.gd'],
    'gd_core_items/Exclusive/MagicMirror.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/MagicRing.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/MagiteccArmor.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/ManaCrystal.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/ManaMastery.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Mananana.gd': ['gd_core_items/Food.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Markswoman.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/MechaBat.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/MegaClover.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/MercuryElemental.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/MissFortune.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/MoltenDagger.gd': ['gd_core_items/Dagger.gd', 'gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/MoltenGreatsword.gd': ['gd_core_items/Greatsword.gd', 'gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/MoltenSpear.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/MoltenSpear2.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/MoonArmor.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/MoreStats.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/MrsStruggles.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/MushroomFarm.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/NoRushPlease.gd': ['gd_core_items/Item.gd', 'gd_core_items/LeatherHelm.gd'],
    'gd_core_items/Exclusive/NullBlade.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/ObsidianDragon.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/OilLamp.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/OnionCutter.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/OwlSpirit.gd': ['gd_core_items/Exclusive/SpiritCompanion.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/ParadiseBirb.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/PerpetuumMobile.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Phoenix.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/Phoenix2.gd': ['gd_core_items/Exclusive/Phoenix.gd', 'gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/PiggyPinata.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/PiggyofRiches.gd': ['gd_core_items/BoxofRiches.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/PineProtector.gd': ['gd_core_items/Item.gd', 'gd_core_items/Shield.gd', 'gd_core_items/SpikedShield.gd'],
    'gd_core_items/Exclusive/PlasticCube.gd': ['gd_core_items/Exclusive/Cube.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/PoisonFrog.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/PoisonGrenade.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/PoisonShortbow.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/PoisonSpear.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/Pop.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/PortableAltar.gd': ['gd_core_items/Bag.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Pot.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/PoweroftheMoon.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/PrismaticSword.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/PrismaticWand.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/PuzzleBadge.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/PuzzlebagJ.gd': ['gd_core_items/Bag.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/PuzzlebagL.gd': ['gd_core_items/Bag.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/PuzzlebagS.gd': ['gd_core_items/Bag.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/PuzzlebagT.gd': ['gd_core_items/Bag.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/PuzzlebagZ.gd': ['gd_core_items/Bag.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Puzzlebox.gd': ['gd_core_items/Bag.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/RainbowBadge.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/RainbowGoobertAdventurer.gd': ['gd_core_items/Goobert.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/RainbowGoobertBerserker.gd': ['gd_core_items/Goobert.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/RainbowGoobertEngineer.gd': ['gd_core_items/Goobert.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/RainbowGoobertMage.gd': ['gd_core_items/Goobert.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/RainbowGoobertPyromancer.gd': ['gd_core_items/Goobert.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/RainbowOrb.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/RainbowPotion.gd': ['gd_core_items/Item.gd', 'gd_core_items/Potion.gd'],
    'gd_core_items/Exclusive/RandomLoadoutBag.gd': ['gd_core_items/Bag.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Rat.gd': ['gd_core_items/Exclusive/ForestFriend.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/RatChef.gd': ['gd_core_items/Exclusive/ForestFriend.gd', 'gd_core_items/Exclusive/Rat.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Recombobulator.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/RelicCase.gd': ['gd_core_items/Bag.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Repeater.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Resistor.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Reverse.gd': ['gd_core_items/Card.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Robodog.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Rope.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Sandbag.gd': ['gd_core_items/Item.gd', 'gd_core_items/LeatherHelm.gd'],
    'gd_core_items/Exclusive/SapphireEgg.gd': ['gd_core_items/DragonEgg.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/SapphireWhelp.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/Scale.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/ScholarBag.gd': ['gd_core_items/Bag.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Scissorswords.gd': ['gd_core_items/Item.gd', 'gd_core_items/Lightsaber.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/SealtheDeal.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/SerpentStaff.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/SewingCase.gd': ['gd_core_items/Bag.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/ShamanMask.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/ShellTotem.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/ShepherdsCrook.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Shielded.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/ShinyMantle.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/ShinyShell.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/SkullBadge.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/SliceofBread.gd': ['gd_core_items/Food.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/SliceofToast.gd': ['gd_core_items/Food.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/SlimeTime.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Sloth.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/SmellyBarrier.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/SmithingForDummies.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Snake.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/SnowStick.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/Snowball.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Snowcake.gd': ['gd_core_items/Food.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Snowman.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Snowmaster.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Solaris.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/SpeakwithAnimals.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/SpellScrollDark.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/SpellScrollFrostbolt.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/SpellScrollIce.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/SpellScrollLight.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/SpellScrollNature.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/SpicyBanana.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/SpikedCollar.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/SpikedStaff.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/SpikedWall.gd': ['gd_core_items/Item.gd', 'gd_core_items/Shield.gd', 'gd_core_items/SpikedShield.gd'],
    'gd_core_items/Exclusive/SpintoWin.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/SpiritBells.gd': ['gd_core_items/Item.gd', 'gd_core_items/LeatherHelm.gd'],
    'gd_core_items/Exclusive/SpringLoader.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Squirrel.gd': ['gd_core_items/Exclusive/ForestFriend.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/SquirrelArcher.gd': ['gd_core_items/Exclusive/ForestFriend.gd', 'gd_core_items/Exclusive/Squirrel.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/StaffofFire.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/StarofCourage.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/SteelDragon.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/StoneArmor.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/StoneBadge.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/StoneGloves.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/StoneGolem.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/StoneShoes.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Stoned.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/StrongDivinePotion.gd': ['gd_core_items/Exclusive/DivinePotion.gd', 'gd_core_items/Item.gd', 'gd_core_items/Potion.gd'],
    'gd_core_items/Exclusive/VampiricPotion.gd': ['gd_core_items/Item.gd', 'gd_core_items/Potion.gd'],
    'gd_core_items/Exclusive/StrongVampiricPotion.gd': ['gd_core_items/Exclusive/VampiricPotion.gd', 'gd_core_items/Item.gd', 'gd_core_items/Potion.gd'],
    'gd_core_items/Exclusive/SunArmor.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/SunShield.gd': ['gd_core_items/Item.gd', 'gd_core_items/Shield.gd'],
    'gd_core_items/Exclusive/TeslaCoil.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/ThornElemental.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/ThornShortbow.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/Thornbloom.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/Thornburst.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/ThorsHammer.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/ThunderDrake.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/TigerRune.gd': ['gd_core_items/Gems/Gem.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/TimeDilator.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/TimeMelting.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/TimePendant.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/ToastGoobert.gd': ['gd_core_items/Goobert.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Toolbox.gd': ['gd_core_items/Bag.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Turtle.gd': ['gd_core_items/Item.gd', 'gd_core_items/LeatherHelm.gd'],
    'gd_core_items/Exclusive/Twine.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/TwineBadge.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Ukulele.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Ultima.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/UnidentifiedSkill.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/UniquelyUnique.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/VampiricCollar.gd': ['gd_core_items/Item.gd', 'gd_core_items/RangerCollar.gd'],
    'gd_core_items/Exclusive/VineweaveBasket.gd': ['gd_core_items/Bag.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Wand.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/WandofDissonance.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/WarScythe.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/WaterElemental.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/Whetstone3.gd': ['gd_core_items/Item.gd', 'gd_core_items/Whetstone.gd'],
    'gd_core_items/Exclusive/WingedBoots.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Wisp.gd': ['gd_core_items/Gems/Gem.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/WolfBadge.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/WolfEmblem.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Wrench.gd': ['gd_core_items/Item.gd', 'gd_core_items/Weapon.gd'],
    'gd_core_items/Exclusive/Chess/ChessPiece.gd': ['gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Chess/BlackBishop.gd': ['gd_core_items/Exclusive/Chess/ChessPiece.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Chess/BlackKing.gd': ['gd_core_items/Exclusive/Chess/ChessPiece.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Chess/BlackKnight.gd': ['gd_core_items/Exclusive/Chess/ChessPiece.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Chess/BlackPawn.gd': ['gd_core_items/Exclusive/Chess/ChessPiece.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Chess/BlackQueen.gd': ['gd_core_items/Exclusive/Chess/ChessPiece.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Chess/BlackRook.gd': ['gd_core_items/Exclusive/Chess/ChessPiece.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Chess/WhiteBishop.gd': ['gd_core_items/Exclusive/Chess/ChessPiece.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Chess/WhiteKing.gd': ['gd_core_items/Exclusive/Chess/ChessPiece.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Chess/WhiteKnight.gd': ['gd_core_items/Exclusive/Chess/ChessPiece.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Chess/WhitePawn.gd': ['gd_core_items/Exclusive/Chess/ChessPiece.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Chess/WhiteQueen.gd': ['gd_core_items/Exclusive/Chess/ChessPiece.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Exclusive/Chess/WhiteRook.gd': ['gd_core_items/Exclusive/Chess/ChessPiece.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Gems/Amethyst.gd': ['gd_core_items/Gems/Gem.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Gems/CorruptedCrystal.gd': ['gd_core_items/Gems/Gem.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Gems/Emerald.gd': ['gd_core_items/Gems/Gem.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Gems/LumpofCoal.gd': ['gd_core_items/Gems/Gem.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Gems/Ruby.gd': ['gd_core_items/Gems/Gem.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Gems/Sapphire.gd': ['gd_core_items/Gems/Gem.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Gems/Skull.gd': ['gd_core_items/Gems/Gem.gd', 'gd_core_items/Item.gd'],
    'gd_core_items/Gems/Topaz.gd': ['gd_core_items/Gems/Gem.gd', 'gd_core_items/Item.gd'],
}

# items 树拓扑序（load_all 同序的子序列，基类先于子类）
_ITEM_ORDER = [
    'gd_core_items/Item.gd',
    'gd_core_items/Card.gd',
    'gd_core_items/RangerCollar.gd',
    'gd_core_items/Stone.gd',
    'gd_core_items/Food.gd',
    'gd_core_items/Goobert.gd',
    'gd_core_items/Weapon.gd',
    'gd_core_items/Dagger.gd',
    'gd_core_items/Bow.gd',
    'gd_core_items/Gems/Gem.gd',
    'gd_core_items/Potion.gd',
    'gd_core_items/Pan.gd',
    'gd_core_items/Bag.gd',
    'gd_core_items/Piggybank.gd',
    'gd_core_items/Shield.gd',
    'gd_core_items/DragonEgg.gd',
    'gd_core_items/LeatherHelm.gd',
    'gd_core_items/HealthPotion.gd',
    'gd_core_items/PestilenceFlask.gd',
    'gd_core_items/StoneSkinPotion.gd',
    'gd_core_items/AceofSpades.gd',
    'gd_core_items/AcornCollar.gd',
    'gd_core_items/ArtifactStoneCold.gd',
    'gd_core_items/ArtifactStoneHeat.gd',
    'gd_core_items/BagofStones.gd',
    'gd_core_items/Banana.gd',
    'gd_core_items/BloodAmulet.gd',
    'gd_core_items/BloodGoobert.gd',
    'gd_core_items/Bloodthorne.gd',
    'gd_core_items/BloodyDagger.gd',
    'gd_core_items/Blueberries.gd',
    'gd_core_items/BowandArrow.gd',
    'gd_core_items/BoxofRiches.gd',
    'gd_core_items/Broom.gd',
    'gd_core_items/BurningCoal.gd',
    'gd_core_items/BurningTorch.gd',
    'gd_core_items/Carrot.gd',
    'gd_core_items/CarrotGoobert.gd',
    'gd_core_items/ClawsofAttack.gd',
    'gd_core_items/Coins.gd',
    'gd_core_items/CorruptedArmor.gd',
    'gd_core_items/CritwoodStaff.gd',
    'gd_core_items/Crossblades.gd',
    'gd_core_items/Crown.gd',
    'gd_core_items/CursedDagger.gd',
    'gd_core_items/CursedHairComb.gd',
    'gd_core_items/CustomerCard.gd',
    'gd_core_items/DancingDragon.gd',
    'gd_core_items/DarkestLotus.gd',
    'gd_core_items/Darksaber.gd',
    'gd_core_items/DeathScythe.gd',
    'gd_core_items/DeckofCards.gd',
    'gd_core_items/DemonicFlask.gd',
    'gd_core_items/DjinnLamp.gd',
    'gd_core_items/Eggscalibur.gd',
    'gd_core_items/EvilCap.gd',
    'gd_core_items/FalconBlade.gd',
    'gd_core_items/FancyFencingRapier.gd',
    'gd_core_items/Fanfare.gd',
    'gd_core_items/FannyPack.gd',
    'gd_core_items/Flute.gd',
    'gd_core_items/FlyAgaric.gd',
    'gd_core_items/Garlic.gd',
    'gd_core_items/GingerbreadMan.gd',
    'gd_core_items/GlovesofHaste.gd',
    'gd_core_items/Greatsword.gd',
    'gd_core_items/Hammer.gd',
    'gd_core_items/HealingHerbs.gd',
    'gd_core_items/HeartContainer.gd',
    'gd_core_items/HeartofDarkness.gd',
    'gd_core_items/HeroLongsword.gd',
    'gd_core_items/HeroSword.gd',
    'gd_core_items/HeroicPotion.gd',
    'gd_core_items/HoloFireLizard.gd',
    'gd_core_items/HolyArmor.gd',
    'gd_core_items/HolySpear.gd',
    'gd_core_items/HungryBlade.gd',
    'gd_core_items/Jynxtorquilla.gd',
    'gd_core_items/LeatherArmor.gd',
    'gd_core_items/LeatherBoots.gd',
    'gd_core_items/LightGoobert.gd',
    'gd_core_items/Lightsaber.gd',
    'gd_core_items/LuckyBow.gd',
    'gd_core_items/LuckyClover.gd',
    'gd_core_items/LuckyPiggy.gd',
    'gd_core_items/MagicStaff.gd',
    'gd_core_items/MagicTorch.gd',
    'gd_core_items/ManaOrb.gd',
    'gd_core_items/ManaPotion.gd',
    'gd_core_items/Manathirst.gd',
    'gd_core_items/MoonShield.gd',
    'gd_core_items/MrStruggles.gd',
    'gd_core_items/Pandamonium.gd',
    'gd_core_items/PiercingArrow.gd',
    'gd_core_items/Pineapple.gd',
    'gd_core_items/PlatinCustomerCard.gd',
    'gd_core_items/PocketSand.gd',
    'gd_core_items/PoisonBow.gd',
    'gd_core_items/PoisonDagger.gd',
    'gd_core_items/PoisonGoobert.gd',
    'gd_core_items/PoisonIvy.gd',
    'gd_core_items/PotionBelt.gd',
    'gd_core_items/Present.gd',
    'gd_core_items/ProtectivePurse.gd',
    'gd_core_items/Pumpkin.gd',
    'gd_core_items/RainbowGoobert.gd',
    'gd_core_items/RainbowGoobertRanger.gd',
    'gd_core_items/RangerBag.gd',
    'gd_core_items/RibSawBlade.gd',
    'gd_core_items/RubyChonk.gd',
    'gd_core_items/RubyEgg.gd',
    'gd_core_items/RubyWhelp.gd',
    'gd_core_items/ShieldofValor.gd',
    'gd_core_items/Shovel.gd',
    'gd_core_items/Spear.gd',
    'gd_core_items/SpectralDagger.gd',
    'gd_core_items/SpikedShield.gd',
    'gd_core_items/StaffofUnhealing.gd',
    'gd_core_items/StaminaSack.gd',
    'gd_core_items/SteelGoobert.gd',
    'gd_core_items/StoneHelm.gd',
    'gd_core_items/StorageCoffin.gd',
    'gd_core_items/StrongDemonicFlask.gd',
    'gd_core_items/StrongHealthPotion.gd',
    'gd_core_items/StrongPestilenceFlask.gd',
    'gd_core_items/StrongStoneSkinPotion.gd',
    'gd_core_items/TheFool.gd',
    'gd_core_items/TheLovers.gd',
    'gd_core_items/ThornBow.gd',
    'gd_core_items/ThornWhip.gd',
    'gd_core_items/Torch.gd',
    'gd_core_items/VampiricArmor.gd',
    'gd_core_items/VampiricGloves.gd',
    'gd_core_items/VampiricScythe.gd',
    'gd_core_items/VillainSword.gd',
    'gd_core_items/WalrusTusk.gd',
    'gd_core_items/Whetstone.gd',
    'gd_core_items/White-EyesBlueDragon.gd',
    'gd_core_items/Wolpertinger.gd',
    'gd_core_items/WoodenBuckler.gd',
    'gd_core_items/WoodenSword.gd',
    'gd_core_items/YggdrasilLeaf.gd',
    'gd_core_items/Exclusive/AcornAce.gd',
    'gd_core_items/Exclusive/AmethystEgg.gd',
    'gd_core_items/Exclusive/AmethystWhelp.gd',
    'gd_core_items/Exclusive/AmuletUnidentified.gd',
    'gd_core_items/Exclusive/AmuletofAgility.gd',
    'gd_core_items/Exclusive/AmuletofAlchemy.gd',
    'gd_core_items/Exclusive/AmuletofDarkness.gd',
    'gd_core_items/Exclusive/AmuletofFeasting.gd',
    'gd_core_items/Exclusive/AmuletofFortune.gd',
    'gd_core_items/Exclusive/AmuletofLife.gd',
    'gd_core_items/Exclusive/AmuletofLight.gd',
    'gd_core_items/Exclusive/AmuletofSteel.gd',
    'gd_core_items/Exclusive/AmuletoftheWild.gd',
    'gd_core_items/Exclusive/AngelCrystal.gd',
    'gd_core_items/Exclusive/Anvil.gd',
    'gd_core_items/Exclusive/ArcaneBoots.gd',
    'gd_core_items/Exclusive/ArcaneIntellect.gd',
    'gd_core_items/Exclusive/CouragePuppy.gd',
    'gd_core_items/Exclusive/ArmoredCouragePuppy.gd',
    'gd_core_items/Exclusive/PowerPuppy.gd',
    'gd_core_items/Exclusive/ArmoredPowerPuppy.gd',
    'gd_core_items/Exclusive/WisdomPuppy.gd',
    'gd_core_items/Exclusive/ArmoredWisdomPuppy.gd',
    'gd_core_items/Exclusive/ArtifactStoneDeath.gd',
    'gd_core_items/Exclusive/Automanaton.gd',
    'gd_core_items/Exclusive/Axe.gd',
    'gd_core_items/Exclusive/BadgerRune.gd',
    'gd_core_items/Exclusive/SpiritCompanion.gd',
    'gd_core_items/Exclusive/BadgerSpirit.gd',
    'gd_core_items/Exclusive/BagofGiving.gd',
    'gd_core_items/Exclusive/Bagtacular.gd',
    'gd_core_items/Exclusive/Battery.gd',
    'gd_core_items/Exclusive/Bazooka.gd',
    'gd_core_items/Exclusive/BerserkerBag.gd',
    'gd_core_items/Exclusive/Bewitchment.gd',
    'gd_core_items/Exclusive/BigBloodthorne.gd',
    'gd_core_items/Exclusive/BionicArmor.gd',
    'gd_core_items/Exclusive/Cube.gd',
    'gd_core_items/Exclusive/BismuthCube.gd',
    'gd_core_items/Exclusive/BloodManipulation.gd',
    'gd_core_items/Exclusive/Bomb.gd',
    'gd_core_items/Exclusive/BookofBasics.gd',
    'gd_core_items/Exclusive/BookofDarkness.gd',
    'gd_core_items/Exclusive/BookofIce.gd',
    'gd_core_items/Exclusive/BookofLight.gd',
    'gd_core_items/Exclusive/BookofNature.gd',
    'gd_core_items/Exclusive/Boomerang.gd',
    'gd_core_items/Exclusive/BowlofTreats.gd',
    'gd_core_items/Exclusive/BoxofProsperity.gd',
    'gd_core_items/Exclusive/BrassKnuckles.gd',
    'gd_core_items/Exclusive/Broccoli.gd',
    'gd_core_items/Exclusive/BroccoliGoobert.gd',
    'gd_core_items/Exclusive/Broccotree.gd',
    'gd_core_items/Exclusive/BurningBanner.gd',
    'gd_core_items/Exclusive/BurningSword.gd',
    'gd_core_items/Exclusive/BurningBlade.gd',
    'gd_core_items/Exclusive/BurningSpikes.gd',
    'gd_core_items/Exclusive/BustedBlade.gd',
    'gd_core_items/Exclusive/BuytheHolyLight.gd',
    'gd_core_items/Exclusive/CapofBrilliance.gd',
    'gd_core_items/Exclusive/CatSpirit.gd',
    'gd_core_items/Exclusive/Cauldron.gd',
    'gd_core_items/Exclusive/ChainWhip.gd',
    'gd_core_items/Exclusive/Chainsaw.gd',
    'gd_core_items/Exclusive/ChargeSplitter.gd',
    'gd_core_items/Exclusive/Cheese.gd',
    'gd_core_items/Exclusive/CheeseGoobert.gd',
    'gd_core_items/Exclusive/ChessBoard.gd',
    'gd_core_items/Exclusive/ChessMaster.gd',
    'gd_core_items/Exclusive/ChiliGoobert.gd',
    'gd_core_items/Exclusive/ChiliPepper.gd',
    'gd_core_items/Exclusive/ChromeCube.gd',
    'gd_core_items/Exclusive/Cog.gd',
    'gd_core_items/Exclusive/CogBadge.gd',
    'gd_core_items/Exclusive/Coil.gd',
    'gd_core_items/Exclusive/ConTrapTron.gd',
    'gd_core_items/Exclusive/CriticalPoison.gd',
    'gd_core_items/Exclusive/Crow.gd',
    'gd_core_items/Exclusive/Cthulhu.gd',
    'gd_core_items/Exclusive/Cubert.gd',
    'gd_core_items/Exclusive/Cupcake.gd',
    'gd_core_items/Exclusive/CupcakeDragon.gd',
    'gd_core_items/Exclusive/CupcakeGoobert.gd',
    'gd_core_items/Exclusive/CupcakeStaff.gd',
    'gd_core_items/Exclusive/Daggerang.gd',
    'gd_core_items/Exclusive/DarkLantern.gd',
    'gd_core_items/Exclusive/DarkRitual.gd',
    'gd_core_items/Exclusive/DeathLotus.gd',
    'gd_core_items/Exclusive/DeerTotem.gd',
    'gd_core_items/Exclusive/DevouringSphere.gd',
    'gd_core_items/Exclusive/DigDeeper.gd',
    'gd_core_items/Exclusive/DivinePotion.gd',
    'gd_core_items/Exclusive/DoomCap.gd',
    'gd_core_items/Exclusive/DoubleAxe.gd',
    'gd_core_items/Exclusive/DoubleRainbow.gd',
    'gd_core_items/Exclusive/DraconicOrb.gd',
    'gd_core_items/Exclusive/DragonClaws.gd',
    'gd_core_items/Exclusive/DragonKnight.gd',
    'gd_core_items/Exclusive/DragonNest.gd',
    'gd_core_items/Exclusive/DragonSet.gd',
    'gd_core_items/Exclusive/DragonscaleArmor.gd',
    'gd_core_items/Exclusive/DragonskinBoots.gd',
    'gd_core_items/Exclusive/DualWielding.gd',
    'gd_core_items/Exclusive/Eat-o-matic.gd',
    'gd_core_items/Exclusive/EchoingBattlecry.gd',
    'gd_core_items/Exclusive/ElectricTorch.gd',
    'gd_core_items/Exclusive/ElephantRune.gd',
    'gd_core_items/Exclusive/EmeraldEgg.gd',
    'gd_core_items/Exclusive/EmeraldWhelp.gd',
    'gd_core_items/Exclusive/EmployeeUniform.gd',
    'gd_core_items/Exclusive/EnchantedWeapons.gd',
    'gd_core_items/Exclusive/EnergyConversion.gd',
    'gd_core_items/Exclusive/EngineerBag2.gd',
    'gd_core_items/Exclusive/EngineerBox.gd',
    'gd_core_items/Exclusive/Everburning.gd',
    'gd_core_items/Exclusive/EvilHat.gd',
    'gd_core_items/Exclusive/ExtraAngy.gd',
    'gd_core_items/Exclusive/ExtraBags.gd',
    'gd_core_items/Exclusive/FalseLife.gd',
    'gd_core_items/Exclusive/Fedora.gd',
    'gd_core_items/Exclusive/FirePit.gd',
    'gd_core_items/Exclusive/Shelly.gd',
    'gd_core_items/Exclusive/FireShelly.gd',
    'gd_core_items/Exclusive/Flame.gd',
    'gd_core_items/Exclusive/FlameBadge.gd',
    'gd_core_items/Exclusive/FlameWhip.gd',
    'gd_core_items/Exclusive/ForestDragon.gd',
    'gd_core_items/Exclusive/ForestFriend.gd',
    'gd_core_items/Exclusive/ForgingHammer.gd',
    'gd_core_items/Exclusive/FortunasKiss.gd',
    'gd_core_items/Exclusive/FriendlyFire.gd',
    'gd_core_items/Exclusive/Toad.gd',
    'gd_core_items/Exclusive/FrogPrince.gd',
    'gd_core_items/Exclusive/Frostbite.gd',
    'gd_core_items/Exclusive/FrozenBuckler.gd',
    'gd_core_items/Exclusive/FrozenFlame.gd',
    'gd_core_items/Exclusive/FullBodyProtection.gd',
    'gd_core_items/Exclusive/FurciferPrime.gd',
    'gd_core_items/Exclusive/Generator.gd',
    'gd_core_items/Exclusive/Ghost.gd',
    'gd_core_items/Exclusive/Gigawatz.gd',
    'gd_core_items/Exclusive/GirlPower.gd',
    'gd_core_items/Exclusive/GoldArmor.gd',
    'gd_core_items/Exclusive/GoldCube.gd',
    'gd_core_items/Exclusive/Halberd.gd',
    'gd_core_items/Exclusive/Hardwood.gd',
    'gd_core_items/Exclusive/HawkRune.gd',
    'gd_core_items/Exclusive/HeartShield.gd',
    'gd_core_items/Exclusive/HeartoftheCards.gd',
    'gd_core_items/Exclusive/HeavyDrinking.gd',
    'gd_core_items/Exclusive/Hedgehog.gd',
    'gd_core_items/Exclusive/HeroShield.gd',
    'gd_core_items/Exclusive/HogusBogus.gd',
    'gd_core_items/Exclusive/Holdall.gd',
    'gd_core_items/Exclusive/HolyCollar.gd',
    'gd_core_items/Exclusive/HyperHedgehog.gd',
    'gd_core_items/Exclusive/Hypercube.gd',
    'gd_core_items/Exclusive/IceArmor.gd',
    'gd_core_items/Exclusive/IceDragon.gd',
    'gd_core_items/Exclusive/IceFlower.gd',
    'gd_core_items/Exclusive/InnerPower.gd',
    'gd_core_items/Exclusive/InvestmentOpportunity.gd',
    'gd_core_items/Exclusive/Joker.gd',
    'gd_core_items/Exclusive/JustStats.gd',
    'gd_core_items/Exclusive/JynxStaff.gd',
    'gd_core_items/Exclusive/Katana.gd',
    'gd_core_items/Exclusive/KingCrown.gd',
    'gd_core_items/Exclusive/KingGoobert.gd',
    'gd_core_items/Exclusive/KingoftheBling.gd',
    'gd_core_items/Exclusive/KnifetoMeetYou.gd',
    'gd_core_items/Exclusive/Laboratory.gd',
    'gd_core_items/Exclusive/LeafBadge.gd',
    'gd_core_items/Exclusive/LevelUp.gd',
    'gd_core_items/Exclusive/LightFlower.gd',
    'gd_core_items/Exclusive/LightningPotion.gd',
    'gd_core_items/Exclusive/LightningStaff.gd',
    'gd_core_items/Exclusive/LittleMimic.gd',
    'gd_core_items/Exclusive/LongSpear.gd',
    'gd_core_items/Exclusive/Lootbox.gd',
    'gd_core_items/Exclusive/LuckyCat.gd',
    'gd_core_items/Exclusive/LuckyShortbow.gd',
    'gd_core_items/Exclusive/MageHat.gd',
    'gd_core_items/Exclusive/MagicBadge.gd',
    'gd_core_items/Exclusive/MagicCollar.gd',
    'gd_core_items/Exclusive/MagicMirror.gd',
    'gd_core_items/Exclusive/MagicRing.gd',
    'gd_core_items/Exclusive/MagiteccArmor.gd',
    'gd_core_items/Exclusive/ManaCrystal.gd',
    'gd_core_items/Exclusive/ManaMastery.gd',
    'gd_core_items/Exclusive/Mananana.gd',
    'gd_core_items/Exclusive/Markswoman.gd',
    'gd_core_items/Exclusive/MechaBat.gd',
    'gd_core_items/Exclusive/MegaClover.gd',
    'gd_core_items/Exclusive/MercuryElemental.gd',
    'gd_core_items/Exclusive/MissFortune.gd',
    'gd_core_items/Exclusive/MoltenDagger.gd',
    'gd_core_items/Exclusive/MoltenGreatsword.gd',
    'gd_core_items/Exclusive/MoltenSpear.gd',
    'gd_core_items/Exclusive/MoltenSpear2.gd',
    'gd_core_items/Exclusive/MoonArmor.gd',
    'gd_core_items/Exclusive/MoreStats.gd',
    'gd_core_items/Exclusive/MrsStruggles.gd',
    'gd_core_items/Exclusive/MushroomFarm.gd',
    'gd_core_items/Exclusive/NoRushPlease.gd',
    'gd_core_items/Exclusive/NullBlade.gd',
    'gd_core_items/Exclusive/ObsidianDragon.gd',
    'gd_core_items/Exclusive/OilLamp.gd',
    'gd_core_items/Exclusive/OnionCutter.gd',
    'gd_core_items/Exclusive/OwlSpirit.gd',
    'gd_core_items/Exclusive/ParadiseBirb.gd',
    'gd_core_items/Exclusive/PerpetuumMobile.gd',
    'gd_core_items/Exclusive/Phoenix.gd',
    'gd_core_items/Exclusive/Phoenix2.gd',
    'gd_core_items/Exclusive/PiggyPinata.gd',
    'gd_core_items/Exclusive/PiggyofRiches.gd',
    'gd_core_items/Exclusive/PineProtector.gd',
    'gd_core_items/Exclusive/PlasticCube.gd',
    'gd_core_items/Exclusive/PoisonFrog.gd',
    'gd_core_items/Exclusive/PoisonGrenade.gd',
    'gd_core_items/Exclusive/PoisonShortbow.gd',
    'gd_core_items/Exclusive/PoisonSpear.gd',
    'gd_core_items/Exclusive/Pop.gd',
    'gd_core_items/Exclusive/PortableAltar.gd',
    'gd_core_items/Exclusive/Pot.gd',
    'gd_core_items/Exclusive/PoweroftheMoon.gd',
    'gd_core_items/Exclusive/PrismaticSword.gd',
    'gd_core_items/Exclusive/PrismaticWand.gd',
    'gd_core_items/Exclusive/PuzzleBadge.gd',
    'gd_core_items/Exclusive/PuzzlebagJ.gd',
    'gd_core_items/Exclusive/PuzzlebagL.gd',
    'gd_core_items/Exclusive/PuzzlebagS.gd',
    'gd_core_items/Exclusive/PuzzlebagT.gd',
    'gd_core_items/Exclusive/PuzzlebagZ.gd',
    'gd_core_items/Exclusive/Puzzlebox.gd',
    'gd_core_items/Exclusive/RainbowBadge.gd',
    'gd_core_items/Exclusive/RainbowGoobertAdventurer.gd',
    'gd_core_items/Exclusive/RainbowGoobertBerserker.gd',
    'gd_core_items/Exclusive/RainbowGoobertEngineer.gd',
    'gd_core_items/Exclusive/RainbowGoobertMage.gd',
    'gd_core_items/Exclusive/RainbowGoobertPyromancer.gd',
    'gd_core_items/Exclusive/RainbowOrb.gd',
    'gd_core_items/Exclusive/RainbowPotion.gd',
    'gd_core_items/Exclusive/RandomLoadoutBag.gd',
    'gd_core_items/Exclusive/Rat.gd',
    'gd_core_items/Exclusive/RatChef.gd',
    'gd_core_items/Exclusive/Recombobulator.gd',
    'gd_core_items/Exclusive/RelicCase.gd',
    'gd_core_items/Exclusive/Repeater.gd',
    'gd_core_items/Exclusive/Resistor.gd',
    'gd_core_items/Exclusive/Reverse.gd',
    'gd_core_items/Exclusive/Robodog.gd',
    'gd_core_items/Exclusive/Rope.gd',
    'gd_core_items/Exclusive/Sandbag.gd',
    'gd_core_items/Exclusive/SapphireEgg.gd',
    'gd_core_items/Exclusive/SapphireWhelp.gd',
    'gd_core_items/Exclusive/Scale.gd',
    'gd_core_items/Exclusive/ScholarBag.gd',
    'gd_core_items/Exclusive/Scissorswords.gd',
    'gd_core_items/Exclusive/SealtheDeal.gd',
    'gd_core_items/Exclusive/SerpentStaff.gd',
    'gd_core_items/Exclusive/SewingCase.gd',
    'gd_core_items/Exclusive/ShamanMask.gd',
    'gd_core_items/Exclusive/ShellTotem.gd',
    'gd_core_items/Exclusive/ShepherdsCrook.gd',
    'gd_core_items/Exclusive/Shielded.gd',
    'gd_core_items/Exclusive/ShinyMantle.gd',
    'gd_core_items/Exclusive/ShinyShell.gd',
    'gd_core_items/Exclusive/SkullBadge.gd',
    'gd_core_items/Exclusive/SliceofBread.gd',
    'gd_core_items/Exclusive/SliceofToast.gd',
    'gd_core_items/Exclusive/SlimeTime.gd',
    'gd_core_items/Exclusive/Sloth.gd',
    'gd_core_items/Exclusive/SmellyBarrier.gd',
    'gd_core_items/Exclusive/SmithingForDummies.gd',
    'gd_core_items/Exclusive/Snake.gd',
    'gd_core_items/Exclusive/SnowStick.gd',
    'gd_core_items/Exclusive/Snowball.gd',
    'gd_core_items/Exclusive/Snowcake.gd',
    'gd_core_items/Exclusive/Snowman.gd',
    'gd_core_items/Exclusive/Snowmaster.gd',
    'gd_core_items/Exclusive/Solaris.gd',
    'gd_core_items/Exclusive/SpeakwithAnimals.gd',
    'gd_core_items/Exclusive/SpellScrollDark.gd',
    'gd_core_items/Exclusive/SpellScrollFrostbolt.gd',
    'gd_core_items/Exclusive/SpellScrollIce.gd',
    'gd_core_items/Exclusive/SpellScrollLight.gd',
    'gd_core_items/Exclusive/SpellScrollNature.gd',
    'gd_core_items/Exclusive/SpicyBanana.gd',
    'gd_core_items/Exclusive/SpikedCollar.gd',
    'gd_core_items/Exclusive/SpikedStaff.gd',
    'gd_core_items/Exclusive/SpikedWall.gd',
    'gd_core_items/Exclusive/SpintoWin.gd',
    'gd_core_items/Exclusive/SpiritBells.gd',
    'gd_core_items/Exclusive/SpringLoader.gd',
    'gd_core_items/Exclusive/Squirrel.gd',
    'gd_core_items/Exclusive/SquirrelArcher.gd',
    'gd_core_items/Exclusive/StaffofFire.gd',
    'gd_core_items/Exclusive/StarofCourage.gd',
    'gd_core_items/Exclusive/SteelDragon.gd',
    'gd_core_items/Exclusive/StoneArmor.gd',
    'gd_core_items/Exclusive/StoneBadge.gd',
    'gd_core_items/Exclusive/StoneGloves.gd',
    'gd_core_items/Exclusive/StoneGolem.gd',
    'gd_core_items/Exclusive/StoneShoes.gd',
    'gd_core_items/Exclusive/Stoned.gd',
    'gd_core_items/Exclusive/StrongDivinePotion.gd',
    'gd_core_items/Exclusive/VampiricPotion.gd',
    'gd_core_items/Exclusive/StrongVampiricPotion.gd',
    'gd_core_items/Exclusive/SunArmor.gd',
    'gd_core_items/Exclusive/SunShield.gd',
    'gd_core_items/Exclusive/TeslaCoil.gd',
    'gd_core_items/Exclusive/ThornElemental.gd',
    'gd_core_items/Exclusive/ThornShortbow.gd',
    'gd_core_items/Exclusive/Thornbloom.gd',
    'gd_core_items/Exclusive/Thornburst.gd',
    'gd_core_items/Exclusive/ThorsHammer.gd',
    'gd_core_items/Exclusive/ThunderDrake.gd',
    'gd_core_items/Exclusive/TigerRune.gd',
    'gd_core_items/Exclusive/TimeDilator.gd',
    'gd_core_items/Exclusive/TimeMelting.gd',
    'gd_core_items/Exclusive/TimePendant.gd',
    'gd_core_items/Exclusive/ToastGoobert.gd',
    'gd_core_items/Exclusive/Toolbox.gd',
    'gd_core_items/Exclusive/Turtle.gd',
    'gd_core_items/Exclusive/Twine.gd',
    'gd_core_items/Exclusive/TwineBadge.gd',
    'gd_core_items/Exclusive/Ukulele.gd',
    'gd_core_items/Exclusive/Ultima.gd',
    'gd_core_items/Exclusive/UnidentifiedSkill.gd',
    'gd_core_items/Exclusive/UniquelyUnique.gd',
    'gd_core_items/Exclusive/VampiricCollar.gd',
    'gd_core_items/Exclusive/VineweaveBasket.gd',
    'gd_core_items/Exclusive/Wand.gd',
    'gd_core_items/Exclusive/WandofDissonance.gd',
    'gd_core_items/Exclusive/WarScythe.gd',
    'gd_core_items/Exclusive/WaterElemental.gd',
    'gd_core_items/Exclusive/Whetstone3.gd',
    'gd_core_items/Exclusive/WingedBoots.gd',
    'gd_core_items/Exclusive/Wisp.gd',
    'gd_core_items/Exclusive/WolfBadge.gd',
    'gd_core_items/Exclusive/WolfEmblem.gd',
    'gd_core_items/Exclusive/Wrench.gd',
    'gd_core_items/Exclusive/Chess/ChessPiece.gd',
    'gd_core_items/Exclusive/Chess/BlackBishop.gd',
    'gd_core_items/Exclusive/Chess/BlackKing.gd',
    'gd_core_items/Exclusive/Chess/BlackKnight.gd',
    'gd_core_items/Exclusive/Chess/BlackPawn.gd',
    'gd_core_items/Exclusive/Chess/BlackQueen.gd',
    'gd_core_items/Exclusive/Chess/BlackRook.gd',
    'gd_core_items/Exclusive/Chess/WhiteBishop.gd',
    'gd_core_items/Exclusive/Chess/WhiteKing.gd',
    'gd_core_items/Exclusive/Chess/WhiteKnight.gd',
    'gd_core_items/Exclusive/Chess/WhitePawn.gd',
    'gd_core_items/Exclusive/Chess/WhiteQueen.gd',
    'gd_core_items/Exclusive/Chess/WhiteRook.gd',
    'gd_core_items/Gems/Amethyst.gd',
    'gd_core_items/Gems/CorruptedCrystal.gd',
    'gd_core_items/Gems/Emerald.gd',
    'gd_core_items/Gems/LumpofCoal.gd',
    'gd_core_items/Gems/Ruby.gd',
    'gd_core_items/Gems/Sapphire.gd',
    'gd_core_items/Gems/Skull.gd',
    'gd_core_items/Gems/Topaz.gd',
]

# items 树 stem → rel（生成期断言无重名；load_for 的 O(1) 索引）
_ITEM_STEM = {
    'Item': 'gd_core_items/Item.gd',
    'Card': 'gd_core_items/Card.gd',
    'RangerCollar': 'gd_core_items/RangerCollar.gd',
    'Stone': 'gd_core_items/Stone.gd',
    'Food': 'gd_core_items/Food.gd',
    'Goobert': 'gd_core_items/Goobert.gd',
    'Weapon': 'gd_core_items/Weapon.gd',
    'Dagger': 'gd_core_items/Dagger.gd',
    'Bow': 'gd_core_items/Bow.gd',
    'Gem': 'gd_core_items/Gems/Gem.gd',
    'Potion': 'gd_core_items/Potion.gd',
    'Pan': 'gd_core_items/Pan.gd',
    'Bag': 'gd_core_items/Bag.gd',
    'Piggybank': 'gd_core_items/Piggybank.gd',
    'Shield': 'gd_core_items/Shield.gd',
    'DragonEgg': 'gd_core_items/DragonEgg.gd',
    'LeatherHelm': 'gd_core_items/LeatherHelm.gd',
    'HealthPotion': 'gd_core_items/HealthPotion.gd',
    'PestilenceFlask': 'gd_core_items/PestilenceFlask.gd',
    'StoneSkinPotion': 'gd_core_items/StoneSkinPotion.gd',
    'AceofSpades': 'gd_core_items/AceofSpades.gd',
    'AcornCollar': 'gd_core_items/AcornCollar.gd',
    'ArtifactStoneCold': 'gd_core_items/ArtifactStoneCold.gd',
    'ArtifactStoneHeat': 'gd_core_items/ArtifactStoneHeat.gd',
    'BagofStones': 'gd_core_items/BagofStones.gd',
    'Banana': 'gd_core_items/Banana.gd',
    'BloodAmulet': 'gd_core_items/BloodAmulet.gd',
    'BloodGoobert': 'gd_core_items/BloodGoobert.gd',
    'Bloodthorne': 'gd_core_items/Bloodthorne.gd',
    'BloodyDagger': 'gd_core_items/BloodyDagger.gd',
    'Blueberries': 'gd_core_items/Blueberries.gd',
    'BowandArrow': 'gd_core_items/BowandArrow.gd',
    'BoxofRiches': 'gd_core_items/BoxofRiches.gd',
    'Broom': 'gd_core_items/Broom.gd',
    'BurningCoal': 'gd_core_items/BurningCoal.gd',
    'BurningTorch': 'gd_core_items/BurningTorch.gd',
    'Carrot': 'gd_core_items/Carrot.gd',
    'CarrotGoobert': 'gd_core_items/CarrotGoobert.gd',
    'ClawsofAttack': 'gd_core_items/ClawsofAttack.gd',
    'Coins': 'gd_core_items/Coins.gd',
    'CorruptedArmor': 'gd_core_items/CorruptedArmor.gd',
    'CritwoodStaff': 'gd_core_items/CritwoodStaff.gd',
    'Crossblades': 'gd_core_items/Crossblades.gd',
    'Crown': 'gd_core_items/Crown.gd',
    'CursedDagger': 'gd_core_items/CursedDagger.gd',
    'CursedHairComb': 'gd_core_items/CursedHairComb.gd',
    'CustomerCard': 'gd_core_items/CustomerCard.gd',
    'DancingDragon': 'gd_core_items/DancingDragon.gd',
    'DarkestLotus': 'gd_core_items/DarkestLotus.gd',
    'Darksaber': 'gd_core_items/Darksaber.gd',
    'DeathScythe': 'gd_core_items/DeathScythe.gd',
    'DeckofCards': 'gd_core_items/DeckofCards.gd',
    'DemonicFlask': 'gd_core_items/DemonicFlask.gd',
    'DjinnLamp': 'gd_core_items/DjinnLamp.gd',
    'Eggscalibur': 'gd_core_items/Eggscalibur.gd',
    'EvilCap': 'gd_core_items/EvilCap.gd',
    'FalconBlade': 'gd_core_items/FalconBlade.gd',
    'FancyFencingRapier': 'gd_core_items/FancyFencingRapier.gd',
    'Fanfare': 'gd_core_items/Fanfare.gd',
    'FannyPack': 'gd_core_items/FannyPack.gd',
    'Flute': 'gd_core_items/Flute.gd',
    'FlyAgaric': 'gd_core_items/FlyAgaric.gd',
    'Garlic': 'gd_core_items/Garlic.gd',
    'GingerbreadMan': 'gd_core_items/GingerbreadMan.gd',
    'GlovesofHaste': 'gd_core_items/GlovesofHaste.gd',
    'Greatsword': 'gd_core_items/Greatsword.gd',
    'Hammer': 'gd_core_items/Hammer.gd',
    'HealingHerbs': 'gd_core_items/HealingHerbs.gd',
    'HeartContainer': 'gd_core_items/HeartContainer.gd',
    'HeartofDarkness': 'gd_core_items/HeartofDarkness.gd',
    'HeroLongsword': 'gd_core_items/HeroLongsword.gd',
    'HeroSword': 'gd_core_items/HeroSword.gd',
    'HeroicPotion': 'gd_core_items/HeroicPotion.gd',
    'HoloFireLizard': 'gd_core_items/HoloFireLizard.gd',
    'HolyArmor': 'gd_core_items/HolyArmor.gd',
    'HolySpear': 'gd_core_items/HolySpear.gd',
    'HungryBlade': 'gd_core_items/HungryBlade.gd',
    'Jynxtorquilla': 'gd_core_items/Jynxtorquilla.gd',
    'LeatherArmor': 'gd_core_items/LeatherArmor.gd',
    'LeatherBoots': 'gd_core_items/LeatherBoots.gd',
    'LightGoobert': 'gd_core_items/LightGoobert.gd',
    'Lightsaber': 'gd_core_items/Lightsaber.gd',
    'LuckyBow': 'gd_core_items/LuckyBow.gd',
    'LuckyClover': 'gd_core_items/LuckyClover.gd',
    'LuckyPiggy': 'gd_core_items/LuckyPiggy.gd',
    'MagicStaff': 'gd_core_items/MagicStaff.gd',
    'MagicTorch': 'gd_core_items/MagicTorch.gd',
    'ManaOrb': 'gd_core_items/ManaOrb.gd',
    'ManaPotion': 'gd_core_items/ManaPotion.gd',
    'Manathirst': 'gd_core_items/Manathirst.gd',
    'MoonShield': 'gd_core_items/MoonShield.gd',
    'MrStruggles': 'gd_core_items/MrStruggles.gd',
    'Pandamonium': 'gd_core_items/Pandamonium.gd',
    'PiercingArrow': 'gd_core_items/PiercingArrow.gd',
    'Pineapple': 'gd_core_items/Pineapple.gd',
    'PlatinCustomerCard': 'gd_core_items/PlatinCustomerCard.gd',
    'PocketSand': 'gd_core_items/PocketSand.gd',
    'PoisonBow': 'gd_core_items/PoisonBow.gd',
    'PoisonDagger': 'gd_core_items/PoisonDagger.gd',
    'PoisonGoobert': 'gd_core_items/PoisonGoobert.gd',
    'PoisonIvy': 'gd_core_items/PoisonIvy.gd',
    'PotionBelt': 'gd_core_items/PotionBelt.gd',
    'Present': 'gd_core_items/Present.gd',
    'ProtectivePurse': 'gd_core_items/ProtectivePurse.gd',
    'Pumpkin': 'gd_core_items/Pumpkin.gd',
    'RainbowGoobert': 'gd_core_items/RainbowGoobert.gd',
    'RainbowGoobertRanger': 'gd_core_items/RainbowGoobertRanger.gd',
    'RangerBag': 'gd_core_items/RangerBag.gd',
    'RibSawBlade': 'gd_core_items/RibSawBlade.gd',
    'RubyChonk': 'gd_core_items/RubyChonk.gd',
    'RubyEgg': 'gd_core_items/RubyEgg.gd',
    'RubyWhelp': 'gd_core_items/RubyWhelp.gd',
    'ShieldofValor': 'gd_core_items/ShieldofValor.gd',
    'Shovel': 'gd_core_items/Shovel.gd',
    'Spear': 'gd_core_items/Spear.gd',
    'SpectralDagger': 'gd_core_items/SpectralDagger.gd',
    'SpikedShield': 'gd_core_items/SpikedShield.gd',
    'StaffofUnhealing': 'gd_core_items/StaffofUnhealing.gd',
    'StaminaSack': 'gd_core_items/StaminaSack.gd',
    'SteelGoobert': 'gd_core_items/SteelGoobert.gd',
    'StoneHelm': 'gd_core_items/StoneHelm.gd',
    'StorageCoffin': 'gd_core_items/StorageCoffin.gd',
    'StrongDemonicFlask': 'gd_core_items/StrongDemonicFlask.gd',
    'StrongHealthPotion': 'gd_core_items/StrongHealthPotion.gd',
    'StrongPestilenceFlask': 'gd_core_items/StrongPestilenceFlask.gd',
    'StrongStoneSkinPotion': 'gd_core_items/StrongStoneSkinPotion.gd',
    'TheFool': 'gd_core_items/TheFool.gd',
    'TheLovers': 'gd_core_items/TheLovers.gd',
    'ThornBow': 'gd_core_items/ThornBow.gd',
    'ThornWhip': 'gd_core_items/ThornWhip.gd',
    'Torch': 'gd_core_items/Torch.gd',
    'VampiricArmor': 'gd_core_items/VampiricArmor.gd',
    'VampiricGloves': 'gd_core_items/VampiricGloves.gd',
    'VampiricScythe': 'gd_core_items/VampiricScythe.gd',
    'VillainSword': 'gd_core_items/VillainSword.gd',
    'WalrusTusk': 'gd_core_items/WalrusTusk.gd',
    'Whetstone': 'gd_core_items/Whetstone.gd',
    'White-EyesBlueDragon': 'gd_core_items/White-EyesBlueDragon.gd',
    'Wolpertinger': 'gd_core_items/Wolpertinger.gd',
    'WoodenBuckler': 'gd_core_items/WoodenBuckler.gd',
    'WoodenSword': 'gd_core_items/WoodenSword.gd',
    'YggdrasilLeaf': 'gd_core_items/YggdrasilLeaf.gd',
    'AcornAce': 'gd_core_items/Exclusive/AcornAce.gd',
    'AmethystEgg': 'gd_core_items/Exclusive/AmethystEgg.gd',
    'AmethystWhelp': 'gd_core_items/Exclusive/AmethystWhelp.gd',
    'AmuletUnidentified': 'gd_core_items/Exclusive/AmuletUnidentified.gd',
    'AmuletofAgility': 'gd_core_items/Exclusive/AmuletofAgility.gd',
    'AmuletofAlchemy': 'gd_core_items/Exclusive/AmuletofAlchemy.gd',
    'AmuletofDarkness': 'gd_core_items/Exclusive/AmuletofDarkness.gd',
    'AmuletofFeasting': 'gd_core_items/Exclusive/AmuletofFeasting.gd',
    'AmuletofFortune': 'gd_core_items/Exclusive/AmuletofFortune.gd',
    'AmuletofLife': 'gd_core_items/Exclusive/AmuletofLife.gd',
    'AmuletofLight': 'gd_core_items/Exclusive/AmuletofLight.gd',
    'AmuletofSteel': 'gd_core_items/Exclusive/AmuletofSteel.gd',
    'AmuletoftheWild': 'gd_core_items/Exclusive/AmuletoftheWild.gd',
    'AngelCrystal': 'gd_core_items/Exclusive/AngelCrystal.gd',
    'Anvil': 'gd_core_items/Exclusive/Anvil.gd',
    'ArcaneBoots': 'gd_core_items/Exclusive/ArcaneBoots.gd',
    'ArcaneIntellect': 'gd_core_items/Exclusive/ArcaneIntellect.gd',
    'CouragePuppy': 'gd_core_items/Exclusive/CouragePuppy.gd',
    'ArmoredCouragePuppy': 'gd_core_items/Exclusive/ArmoredCouragePuppy.gd',
    'PowerPuppy': 'gd_core_items/Exclusive/PowerPuppy.gd',
    'ArmoredPowerPuppy': 'gd_core_items/Exclusive/ArmoredPowerPuppy.gd',
    'WisdomPuppy': 'gd_core_items/Exclusive/WisdomPuppy.gd',
    'ArmoredWisdomPuppy': 'gd_core_items/Exclusive/ArmoredWisdomPuppy.gd',
    'ArtifactStoneDeath': 'gd_core_items/Exclusive/ArtifactStoneDeath.gd',
    'Automanaton': 'gd_core_items/Exclusive/Automanaton.gd',
    'Axe': 'gd_core_items/Exclusive/Axe.gd',
    'BadgerRune': 'gd_core_items/Exclusive/BadgerRune.gd',
    'SpiritCompanion': 'gd_core_items/Exclusive/SpiritCompanion.gd',
    'BadgerSpirit': 'gd_core_items/Exclusive/BadgerSpirit.gd',
    'BagofGiving': 'gd_core_items/Exclusive/BagofGiving.gd',
    'Bagtacular': 'gd_core_items/Exclusive/Bagtacular.gd',
    'Battery': 'gd_core_items/Exclusive/Battery.gd',
    'Bazooka': 'gd_core_items/Exclusive/Bazooka.gd',
    'BerserkerBag': 'gd_core_items/Exclusive/BerserkerBag.gd',
    'Bewitchment': 'gd_core_items/Exclusive/Bewitchment.gd',
    'BigBloodthorne': 'gd_core_items/Exclusive/BigBloodthorne.gd',
    'BionicArmor': 'gd_core_items/Exclusive/BionicArmor.gd',
    'Cube': 'gd_core_items/Exclusive/Cube.gd',
    'BismuthCube': 'gd_core_items/Exclusive/BismuthCube.gd',
    'BloodManipulation': 'gd_core_items/Exclusive/BloodManipulation.gd',
    'Bomb': 'gd_core_items/Exclusive/Bomb.gd',
    'BookofBasics': 'gd_core_items/Exclusive/BookofBasics.gd',
    'BookofDarkness': 'gd_core_items/Exclusive/BookofDarkness.gd',
    'BookofIce': 'gd_core_items/Exclusive/BookofIce.gd',
    'BookofLight': 'gd_core_items/Exclusive/BookofLight.gd',
    'BookofNature': 'gd_core_items/Exclusive/BookofNature.gd',
    'Boomerang': 'gd_core_items/Exclusive/Boomerang.gd',
    'BowlofTreats': 'gd_core_items/Exclusive/BowlofTreats.gd',
    'BoxofProsperity': 'gd_core_items/Exclusive/BoxofProsperity.gd',
    'BrassKnuckles': 'gd_core_items/Exclusive/BrassKnuckles.gd',
    'Broccoli': 'gd_core_items/Exclusive/Broccoli.gd',
    'BroccoliGoobert': 'gd_core_items/Exclusive/BroccoliGoobert.gd',
    'Broccotree': 'gd_core_items/Exclusive/Broccotree.gd',
    'BurningBanner': 'gd_core_items/Exclusive/BurningBanner.gd',
    'BurningSword': 'gd_core_items/Exclusive/BurningSword.gd',
    'BurningBlade': 'gd_core_items/Exclusive/BurningBlade.gd',
    'BurningSpikes': 'gd_core_items/Exclusive/BurningSpikes.gd',
    'BustedBlade': 'gd_core_items/Exclusive/BustedBlade.gd',
    'BuytheHolyLight': 'gd_core_items/Exclusive/BuytheHolyLight.gd',
    'CapofBrilliance': 'gd_core_items/Exclusive/CapofBrilliance.gd',
    'CatSpirit': 'gd_core_items/Exclusive/CatSpirit.gd',
    'Cauldron': 'gd_core_items/Exclusive/Cauldron.gd',
    'ChainWhip': 'gd_core_items/Exclusive/ChainWhip.gd',
    'Chainsaw': 'gd_core_items/Exclusive/Chainsaw.gd',
    'ChargeSplitter': 'gd_core_items/Exclusive/ChargeSplitter.gd',
    'Cheese': 'gd_core_items/Exclusive/Cheese.gd',
    'CheeseGoobert': 'gd_core_items/Exclusive/CheeseGoobert.gd',
    'ChessBoard': 'gd_core_items/Exclusive/ChessBoard.gd',
    'ChessMaster': 'gd_core_items/Exclusive/ChessMaster.gd',
    'ChiliGoobert': 'gd_core_items/Exclusive/ChiliGoobert.gd',
    'ChiliPepper': 'gd_core_items/Exclusive/ChiliPepper.gd',
    'ChromeCube': 'gd_core_items/Exclusive/ChromeCube.gd',
    'Cog': 'gd_core_items/Exclusive/Cog.gd',
    'CogBadge': 'gd_core_items/Exclusive/CogBadge.gd',
    'Coil': 'gd_core_items/Exclusive/Coil.gd',
    'ConTrapTron': 'gd_core_items/Exclusive/ConTrapTron.gd',
    'CriticalPoison': 'gd_core_items/Exclusive/CriticalPoison.gd',
    'Crow': 'gd_core_items/Exclusive/Crow.gd',
    'Cthulhu': 'gd_core_items/Exclusive/Cthulhu.gd',
    'Cubert': 'gd_core_items/Exclusive/Cubert.gd',
    'Cupcake': 'gd_core_items/Exclusive/Cupcake.gd',
    'CupcakeDragon': 'gd_core_items/Exclusive/CupcakeDragon.gd',
    'CupcakeGoobert': 'gd_core_items/Exclusive/CupcakeGoobert.gd',
    'CupcakeStaff': 'gd_core_items/Exclusive/CupcakeStaff.gd',
    'Daggerang': 'gd_core_items/Exclusive/Daggerang.gd',
    'DarkLantern': 'gd_core_items/Exclusive/DarkLantern.gd',
    'DarkRitual': 'gd_core_items/Exclusive/DarkRitual.gd',
    'DeathLotus': 'gd_core_items/Exclusive/DeathLotus.gd',
    'DeerTotem': 'gd_core_items/Exclusive/DeerTotem.gd',
    'DevouringSphere': 'gd_core_items/Exclusive/DevouringSphere.gd',
    'DigDeeper': 'gd_core_items/Exclusive/DigDeeper.gd',
    'DivinePotion': 'gd_core_items/Exclusive/DivinePotion.gd',
    'DoomCap': 'gd_core_items/Exclusive/DoomCap.gd',
    'DoubleAxe': 'gd_core_items/Exclusive/DoubleAxe.gd',
    'DoubleRainbow': 'gd_core_items/Exclusive/DoubleRainbow.gd',
    'DraconicOrb': 'gd_core_items/Exclusive/DraconicOrb.gd',
    'DragonClaws': 'gd_core_items/Exclusive/DragonClaws.gd',
    'DragonKnight': 'gd_core_items/Exclusive/DragonKnight.gd',
    'DragonNest': 'gd_core_items/Exclusive/DragonNest.gd',
    'DragonSet': 'gd_core_items/Exclusive/DragonSet.gd',
    'DragonscaleArmor': 'gd_core_items/Exclusive/DragonscaleArmor.gd',
    'DragonskinBoots': 'gd_core_items/Exclusive/DragonskinBoots.gd',
    'DualWielding': 'gd_core_items/Exclusive/DualWielding.gd',
    'Eat-o-matic': 'gd_core_items/Exclusive/Eat-o-matic.gd',
    'EchoingBattlecry': 'gd_core_items/Exclusive/EchoingBattlecry.gd',
    'ElectricTorch': 'gd_core_items/Exclusive/ElectricTorch.gd',
    'ElephantRune': 'gd_core_items/Exclusive/ElephantRune.gd',
    'EmeraldEgg': 'gd_core_items/Exclusive/EmeraldEgg.gd',
    'EmeraldWhelp': 'gd_core_items/Exclusive/EmeraldWhelp.gd',
    'EmployeeUniform': 'gd_core_items/Exclusive/EmployeeUniform.gd',
    'EnchantedWeapons': 'gd_core_items/Exclusive/EnchantedWeapons.gd',
    'EnergyConversion': 'gd_core_items/Exclusive/EnergyConversion.gd',
    'EngineerBag2': 'gd_core_items/Exclusive/EngineerBag2.gd',
    'EngineerBox': 'gd_core_items/Exclusive/EngineerBox.gd',
    'Everburning': 'gd_core_items/Exclusive/Everburning.gd',
    'EvilHat': 'gd_core_items/Exclusive/EvilHat.gd',
    'ExtraAngy': 'gd_core_items/Exclusive/ExtraAngy.gd',
    'ExtraBags': 'gd_core_items/Exclusive/ExtraBags.gd',
    'FalseLife': 'gd_core_items/Exclusive/FalseLife.gd',
    'Fedora': 'gd_core_items/Exclusive/Fedora.gd',
    'FirePit': 'gd_core_items/Exclusive/FirePit.gd',
    'Shelly': 'gd_core_items/Exclusive/Shelly.gd',
    'FireShelly': 'gd_core_items/Exclusive/FireShelly.gd',
    'Flame': 'gd_core_items/Exclusive/Flame.gd',
    'FlameBadge': 'gd_core_items/Exclusive/FlameBadge.gd',
    'FlameWhip': 'gd_core_items/Exclusive/FlameWhip.gd',
    'ForestDragon': 'gd_core_items/Exclusive/ForestDragon.gd',
    'ForestFriend': 'gd_core_items/Exclusive/ForestFriend.gd',
    'ForgingHammer': 'gd_core_items/Exclusive/ForgingHammer.gd',
    'FortunasKiss': 'gd_core_items/Exclusive/FortunasKiss.gd',
    'FriendlyFire': 'gd_core_items/Exclusive/FriendlyFire.gd',
    'Toad': 'gd_core_items/Exclusive/Toad.gd',
    'FrogPrince': 'gd_core_items/Exclusive/FrogPrince.gd',
    'Frostbite': 'gd_core_items/Exclusive/Frostbite.gd',
    'FrozenBuckler': 'gd_core_items/Exclusive/FrozenBuckler.gd',
    'FrozenFlame': 'gd_core_items/Exclusive/FrozenFlame.gd',
    'FullBodyProtection': 'gd_core_items/Exclusive/FullBodyProtection.gd',
    'FurciferPrime': 'gd_core_items/Exclusive/FurciferPrime.gd',
    'Generator': 'gd_core_items/Exclusive/Generator.gd',
    'Ghost': 'gd_core_items/Exclusive/Ghost.gd',
    'Gigawatz': 'gd_core_items/Exclusive/Gigawatz.gd',
    'GirlPower': 'gd_core_items/Exclusive/GirlPower.gd',
    'GoldArmor': 'gd_core_items/Exclusive/GoldArmor.gd',
    'GoldCube': 'gd_core_items/Exclusive/GoldCube.gd',
    'Halberd': 'gd_core_items/Exclusive/Halberd.gd',
    'Hardwood': 'gd_core_items/Exclusive/Hardwood.gd',
    'HawkRune': 'gd_core_items/Exclusive/HawkRune.gd',
    'HeartShield': 'gd_core_items/Exclusive/HeartShield.gd',
    'HeartoftheCards': 'gd_core_items/Exclusive/HeartoftheCards.gd',
    'HeavyDrinking': 'gd_core_items/Exclusive/HeavyDrinking.gd',
    'Hedgehog': 'gd_core_items/Exclusive/Hedgehog.gd',
    'HeroShield': 'gd_core_items/Exclusive/HeroShield.gd',
    'HogusBogus': 'gd_core_items/Exclusive/HogusBogus.gd',
    'Holdall': 'gd_core_items/Exclusive/Holdall.gd',
    'HolyCollar': 'gd_core_items/Exclusive/HolyCollar.gd',
    'HyperHedgehog': 'gd_core_items/Exclusive/HyperHedgehog.gd',
    'Hypercube': 'gd_core_items/Exclusive/Hypercube.gd',
    'IceArmor': 'gd_core_items/Exclusive/IceArmor.gd',
    'IceDragon': 'gd_core_items/Exclusive/IceDragon.gd',
    'IceFlower': 'gd_core_items/Exclusive/IceFlower.gd',
    'InnerPower': 'gd_core_items/Exclusive/InnerPower.gd',
    'InvestmentOpportunity': 'gd_core_items/Exclusive/InvestmentOpportunity.gd',
    'Joker': 'gd_core_items/Exclusive/Joker.gd',
    'JustStats': 'gd_core_items/Exclusive/JustStats.gd',
    'JynxStaff': 'gd_core_items/Exclusive/JynxStaff.gd',
    'Katana': 'gd_core_items/Exclusive/Katana.gd',
    'KingCrown': 'gd_core_items/Exclusive/KingCrown.gd',
    'KingGoobert': 'gd_core_items/Exclusive/KingGoobert.gd',
    'KingoftheBling': 'gd_core_items/Exclusive/KingoftheBling.gd',
    'KnifetoMeetYou': 'gd_core_items/Exclusive/KnifetoMeetYou.gd',
    'Laboratory': 'gd_core_items/Exclusive/Laboratory.gd',
    'LeafBadge': 'gd_core_items/Exclusive/LeafBadge.gd',
    'LevelUp': 'gd_core_items/Exclusive/LevelUp.gd',
    'LightFlower': 'gd_core_items/Exclusive/LightFlower.gd',
    'LightningPotion': 'gd_core_items/Exclusive/LightningPotion.gd',
    'LightningStaff': 'gd_core_items/Exclusive/LightningStaff.gd',
    'LittleMimic': 'gd_core_items/Exclusive/LittleMimic.gd',
    'LongSpear': 'gd_core_items/Exclusive/LongSpear.gd',
    'Lootbox': 'gd_core_items/Exclusive/Lootbox.gd',
    'LuckyCat': 'gd_core_items/Exclusive/LuckyCat.gd',
    'LuckyShortbow': 'gd_core_items/Exclusive/LuckyShortbow.gd',
    'MageHat': 'gd_core_items/Exclusive/MageHat.gd',
    'MagicBadge': 'gd_core_items/Exclusive/MagicBadge.gd',
    'MagicCollar': 'gd_core_items/Exclusive/MagicCollar.gd',
    'MagicMirror': 'gd_core_items/Exclusive/MagicMirror.gd',
    'MagicRing': 'gd_core_items/Exclusive/MagicRing.gd',
    'MagiteccArmor': 'gd_core_items/Exclusive/MagiteccArmor.gd',
    'ManaCrystal': 'gd_core_items/Exclusive/ManaCrystal.gd',
    'ManaMastery': 'gd_core_items/Exclusive/ManaMastery.gd',
    'Mananana': 'gd_core_items/Exclusive/Mananana.gd',
    'Markswoman': 'gd_core_items/Exclusive/Markswoman.gd',
    'MechaBat': 'gd_core_items/Exclusive/MechaBat.gd',
    'MegaClover': 'gd_core_items/Exclusive/MegaClover.gd',
    'MercuryElemental': 'gd_core_items/Exclusive/MercuryElemental.gd',
    'MissFortune': 'gd_core_items/Exclusive/MissFortune.gd',
    'MoltenDagger': 'gd_core_items/Exclusive/MoltenDagger.gd',
    'MoltenGreatsword': 'gd_core_items/Exclusive/MoltenGreatsword.gd',
    'MoltenSpear': 'gd_core_items/Exclusive/MoltenSpear.gd',
    'MoltenSpear2': 'gd_core_items/Exclusive/MoltenSpear2.gd',
    'MoonArmor': 'gd_core_items/Exclusive/MoonArmor.gd',
    'MoreStats': 'gd_core_items/Exclusive/MoreStats.gd',
    'MrsStruggles': 'gd_core_items/Exclusive/MrsStruggles.gd',
    'MushroomFarm': 'gd_core_items/Exclusive/MushroomFarm.gd',
    'NoRushPlease': 'gd_core_items/Exclusive/NoRushPlease.gd',
    'NullBlade': 'gd_core_items/Exclusive/NullBlade.gd',
    'ObsidianDragon': 'gd_core_items/Exclusive/ObsidianDragon.gd',
    'OilLamp': 'gd_core_items/Exclusive/OilLamp.gd',
    'OnionCutter': 'gd_core_items/Exclusive/OnionCutter.gd',
    'OwlSpirit': 'gd_core_items/Exclusive/OwlSpirit.gd',
    'ParadiseBirb': 'gd_core_items/Exclusive/ParadiseBirb.gd',
    'PerpetuumMobile': 'gd_core_items/Exclusive/PerpetuumMobile.gd',
    'Phoenix': 'gd_core_items/Exclusive/Phoenix.gd',
    'Phoenix2': 'gd_core_items/Exclusive/Phoenix2.gd',
    'PiggyPinata': 'gd_core_items/Exclusive/PiggyPinata.gd',
    'PiggyofRiches': 'gd_core_items/Exclusive/PiggyofRiches.gd',
    'PineProtector': 'gd_core_items/Exclusive/PineProtector.gd',
    'PlasticCube': 'gd_core_items/Exclusive/PlasticCube.gd',
    'PoisonFrog': 'gd_core_items/Exclusive/PoisonFrog.gd',
    'PoisonGrenade': 'gd_core_items/Exclusive/PoisonGrenade.gd',
    'PoisonShortbow': 'gd_core_items/Exclusive/PoisonShortbow.gd',
    'PoisonSpear': 'gd_core_items/Exclusive/PoisonSpear.gd',
    'Pop': 'gd_core_items/Exclusive/Pop.gd',
    'PortableAltar': 'gd_core_items/Exclusive/PortableAltar.gd',
    'Pot': 'gd_core_items/Exclusive/Pot.gd',
    'PoweroftheMoon': 'gd_core_items/Exclusive/PoweroftheMoon.gd',
    'PrismaticSword': 'gd_core_items/Exclusive/PrismaticSword.gd',
    'PrismaticWand': 'gd_core_items/Exclusive/PrismaticWand.gd',
    'PuzzleBadge': 'gd_core_items/Exclusive/PuzzleBadge.gd',
    'PuzzlebagJ': 'gd_core_items/Exclusive/PuzzlebagJ.gd',
    'PuzzlebagL': 'gd_core_items/Exclusive/PuzzlebagL.gd',
    'PuzzlebagS': 'gd_core_items/Exclusive/PuzzlebagS.gd',
    'PuzzlebagT': 'gd_core_items/Exclusive/PuzzlebagT.gd',
    'PuzzlebagZ': 'gd_core_items/Exclusive/PuzzlebagZ.gd',
    'Puzzlebox': 'gd_core_items/Exclusive/Puzzlebox.gd',
    'RainbowBadge': 'gd_core_items/Exclusive/RainbowBadge.gd',
    'RainbowGoobertAdventurer': 'gd_core_items/Exclusive/RainbowGoobertAdventurer.gd',
    'RainbowGoobertBerserker': 'gd_core_items/Exclusive/RainbowGoobertBerserker.gd',
    'RainbowGoobertEngineer': 'gd_core_items/Exclusive/RainbowGoobertEngineer.gd',
    'RainbowGoobertMage': 'gd_core_items/Exclusive/RainbowGoobertMage.gd',
    'RainbowGoobertPyromancer': 'gd_core_items/Exclusive/RainbowGoobertPyromancer.gd',
    'RainbowOrb': 'gd_core_items/Exclusive/RainbowOrb.gd',
    'RainbowPotion': 'gd_core_items/Exclusive/RainbowPotion.gd',
    'RandomLoadoutBag': 'gd_core_items/Exclusive/RandomLoadoutBag.gd',
    'Rat': 'gd_core_items/Exclusive/Rat.gd',
    'RatChef': 'gd_core_items/Exclusive/RatChef.gd',
    'Recombobulator': 'gd_core_items/Exclusive/Recombobulator.gd',
    'RelicCase': 'gd_core_items/Exclusive/RelicCase.gd',
    'Repeater': 'gd_core_items/Exclusive/Repeater.gd',
    'Resistor': 'gd_core_items/Exclusive/Resistor.gd',
    'Reverse': 'gd_core_items/Exclusive/Reverse.gd',
    'Robodog': 'gd_core_items/Exclusive/Robodog.gd',
    'Rope': 'gd_core_items/Exclusive/Rope.gd',
    'Sandbag': 'gd_core_items/Exclusive/Sandbag.gd',
    'SapphireEgg': 'gd_core_items/Exclusive/SapphireEgg.gd',
    'SapphireWhelp': 'gd_core_items/Exclusive/SapphireWhelp.gd',
    'Scale': 'gd_core_items/Exclusive/Scale.gd',
    'ScholarBag': 'gd_core_items/Exclusive/ScholarBag.gd',
    'Scissorswords': 'gd_core_items/Exclusive/Scissorswords.gd',
    'SealtheDeal': 'gd_core_items/Exclusive/SealtheDeal.gd',
    'SerpentStaff': 'gd_core_items/Exclusive/SerpentStaff.gd',
    'SewingCase': 'gd_core_items/Exclusive/SewingCase.gd',
    'ShamanMask': 'gd_core_items/Exclusive/ShamanMask.gd',
    'ShellTotem': 'gd_core_items/Exclusive/ShellTotem.gd',
    'ShepherdsCrook': 'gd_core_items/Exclusive/ShepherdsCrook.gd',
    'Shielded': 'gd_core_items/Exclusive/Shielded.gd',
    'ShinyMantle': 'gd_core_items/Exclusive/ShinyMantle.gd',
    'ShinyShell': 'gd_core_items/Exclusive/ShinyShell.gd',
    'SkullBadge': 'gd_core_items/Exclusive/SkullBadge.gd',
    'SliceofBread': 'gd_core_items/Exclusive/SliceofBread.gd',
    'SliceofToast': 'gd_core_items/Exclusive/SliceofToast.gd',
    'SlimeTime': 'gd_core_items/Exclusive/SlimeTime.gd',
    'Sloth': 'gd_core_items/Exclusive/Sloth.gd',
    'SmellyBarrier': 'gd_core_items/Exclusive/SmellyBarrier.gd',
    'SmithingForDummies': 'gd_core_items/Exclusive/SmithingForDummies.gd',
    'Snake': 'gd_core_items/Exclusive/Snake.gd',
    'SnowStick': 'gd_core_items/Exclusive/SnowStick.gd',
    'Snowball': 'gd_core_items/Exclusive/Snowball.gd',
    'Snowcake': 'gd_core_items/Exclusive/Snowcake.gd',
    'Snowman': 'gd_core_items/Exclusive/Snowman.gd',
    'Snowmaster': 'gd_core_items/Exclusive/Snowmaster.gd',
    'Solaris': 'gd_core_items/Exclusive/Solaris.gd',
    'SpeakwithAnimals': 'gd_core_items/Exclusive/SpeakwithAnimals.gd',
    'SpellScrollDark': 'gd_core_items/Exclusive/SpellScrollDark.gd',
    'SpellScrollFrostbolt': 'gd_core_items/Exclusive/SpellScrollFrostbolt.gd',
    'SpellScrollIce': 'gd_core_items/Exclusive/SpellScrollIce.gd',
    'SpellScrollLight': 'gd_core_items/Exclusive/SpellScrollLight.gd',
    'SpellScrollNature': 'gd_core_items/Exclusive/SpellScrollNature.gd',
    'SpicyBanana': 'gd_core_items/Exclusive/SpicyBanana.gd',
    'SpikedCollar': 'gd_core_items/Exclusive/SpikedCollar.gd',
    'SpikedStaff': 'gd_core_items/Exclusive/SpikedStaff.gd',
    'SpikedWall': 'gd_core_items/Exclusive/SpikedWall.gd',
    'SpintoWin': 'gd_core_items/Exclusive/SpintoWin.gd',
    'SpiritBells': 'gd_core_items/Exclusive/SpiritBells.gd',
    'SpringLoader': 'gd_core_items/Exclusive/SpringLoader.gd',
    'Squirrel': 'gd_core_items/Exclusive/Squirrel.gd',
    'SquirrelArcher': 'gd_core_items/Exclusive/SquirrelArcher.gd',
    'StaffofFire': 'gd_core_items/Exclusive/StaffofFire.gd',
    'StarofCourage': 'gd_core_items/Exclusive/StarofCourage.gd',
    'SteelDragon': 'gd_core_items/Exclusive/SteelDragon.gd',
    'StoneArmor': 'gd_core_items/Exclusive/StoneArmor.gd',
    'StoneBadge': 'gd_core_items/Exclusive/StoneBadge.gd',
    'StoneGloves': 'gd_core_items/Exclusive/StoneGloves.gd',
    'StoneGolem': 'gd_core_items/Exclusive/StoneGolem.gd',
    'StoneShoes': 'gd_core_items/Exclusive/StoneShoes.gd',
    'Stoned': 'gd_core_items/Exclusive/Stoned.gd',
    'StrongDivinePotion': 'gd_core_items/Exclusive/StrongDivinePotion.gd',
    'VampiricPotion': 'gd_core_items/Exclusive/VampiricPotion.gd',
    'StrongVampiricPotion': 'gd_core_items/Exclusive/StrongVampiricPotion.gd',
    'SunArmor': 'gd_core_items/Exclusive/SunArmor.gd',
    'SunShield': 'gd_core_items/Exclusive/SunShield.gd',
    'TeslaCoil': 'gd_core_items/Exclusive/TeslaCoil.gd',
    'ThornElemental': 'gd_core_items/Exclusive/ThornElemental.gd',
    'ThornShortbow': 'gd_core_items/Exclusive/ThornShortbow.gd',
    'Thornbloom': 'gd_core_items/Exclusive/Thornbloom.gd',
    'Thornburst': 'gd_core_items/Exclusive/Thornburst.gd',
    'ThorsHammer': 'gd_core_items/Exclusive/ThorsHammer.gd',
    'ThunderDrake': 'gd_core_items/Exclusive/ThunderDrake.gd',
    'TigerRune': 'gd_core_items/Exclusive/TigerRune.gd',
    'TimeDilator': 'gd_core_items/Exclusive/TimeDilator.gd',
    'TimeMelting': 'gd_core_items/Exclusive/TimeMelting.gd',
    'TimePendant': 'gd_core_items/Exclusive/TimePendant.gd',
    'ToastGoobert': 'gd_core_items/Exclusive/ToastGoobert.gd',
    'Toolbox': 'gd_core_items/Exclusive/Toolbox.gd',
    'Turtle': 'gd_core_items/Exclusive/Turtle.gd',
    'Twine': 'gd_core_items/Exclusive/Twine.gd',
    'TwineBadge': 'gd_core_items/Exclusive/TwineBadge.gd',
    'Ukulele': 'gd_core_items/Exclusive/Ukulele.gd',
    'Ultima': 'gd_core_items/Exclusive/Ultima.gd',
    'UnidentifiedSkill': 'gd_core_items/Exclusive/UnidentifiedSkill.gd',
    'UniquelyUnique': 'gd_core_items/Exclusive/UniquelyUnique.gd',
    'VampiricCollar': 'gd_core_items/Exclusive/VampiricCollar.gd',
    'VineweaveBasket': 'gd_core_items/Exclusive/VineweaveBasket.gd',
    'Wand': 'gd_core_items/Exclusive/Wand.gd',
    'WandofDissonance': 'gd_core_items/Exclusive/WandofDissonance.gd',
    'WarScythe': 'gd_core_items/Exclusive/WarScythe.gd',
    'WaterElemental': 'gd_core_items/Exclusive/WaterElemental.gd',
    'Whetstone3': 'gd_core_items/Exclusive/Whetstone3.gd',
    'WingedBoots': 'gd_core_items/Exclusive/WingedBoots.gd',
    'Wisp': 'gd_core_items/Exclusive/Wisp.gd',
    'WolfBadge': 'gd_core_items/Exclusive/WolfBadge.gd',
    'WolfEmblem': 'gd_core_items/Exclusive/WolfEmblem.gd',
    'Wrench': 'gd_core_items/Exclusive/Wrench.gd',
    'ChessPiece': 'gd_core_items/Exclusive/Chess/ChessPiece.gd',
    'BlackBishop': 'gd_core_items/Exclusive/Chess/BlackBishop.gd',
    'BlackKing': 'gd_core_items/Exclusive/Chess/BlackKing.gd',
    'BlackKnight': 'gd_core_items/Exclusive/Chess/BlackKnight.gd',
    'BlackPawn': 'gd_core_items/Exclusive/Chess/BlackPawn.gd',
    'BlackQueen': 'gd_core_items/Exclusive/Chess/BlackQueen.gd',
    'BlackRook': 'gd_core_items/Exclusive/Chess/BlackRook.gd',
    'WhiteBishop': 'gd_core_items/Exclusive/Chess/WhiteBishop.gd',
    'WhiteKing': 'gd_core_items/Exclusive/Chess/WhiteKing.gd',
    'WhiteKnight': 'gd_core_items/Exclusive/Chess/WhiteKnight.gd',
    'WhitePawn': 'gd_core_items/Exclusive/Chess/WhitePawn.gd',
    'WhiteQueen': 'gd_core_items/Exclusive/Chess/WhiteQueen.gd',
    'WhiteRook': 'gd_core_items/Exclusive/Chess/WhiteRook.gd',
    'Amethyst': 'gd_core_items/Gems/Amethyst.gd',
    'CorruptedCrystal': 'gd_core_items/Gems/CorruptedCrystal.gd',
    'Emerald': 'gd_core_items/Gems/Emerald.gd',
    'LumpofCoal': 'gd_core_items/Gems/LumpofCoal.gd',
    'Ruby': 'gd_core_items/Gems/Ruby.gd',
    'Sapphire': 'gd_core_items/Gems/Sapphire.gd',
    'Skull': 'gd_core_items/Gems/Skull.gd',
    'Topaz': 'gd_core_items/Gems/Topaz.gd',
}

# items 树 (rel, 模块路径)，拓扑序——load_for 按需循环导入
_ITEM_MODULES = [
    ('gd_core_items/Item.gd', 'gd_core_py.gd_core_items.Item'),
    ('gd_core_items/Card.gd', 'gd_core_py.gd_core_items.Card'),
    ('gd_core_items/RangerCollar.gd', 'gd_core_py.gd_core_items.RangerCollar'),
    ('gd_core_items/Stone.gd', 'gd_core_py.gd_core_items.Stone'),
    ('gd_core_items/Food.gd', 'gd_core_py.gd_core_items.Food'),
    ('gd_core_items/Goobert.gd', 'gd_core_py.gd_core_items.Goobert'),
    ('gd_core_items/Weapon.gd', 'gd_core_py.gd_core_items.Weapon'),
    ('gd_core_items/Dagger.gd', 'gd_core_py.gd_core_items.Dagger'),
    ('gd_core_items/Bow.gd', 'gd_core_py.gd_core_items.Bow'),
    ('gd_core_items/Gems/Gem.gd', 'gd_core_py.gd_core_items.Gems.Gem'),
    ('gd_core_items/Potion.gd', 'gd_core_py.gd_core_items.Potion'),
    ('gd_core_items/Pan.gd', 'gd_core_py.gd_core_items.Pan'),
    ('gd_core_items/Bag.gd', 'gd_core_py.gd_core_items.Bag'),
    ('gd_core_items/Piggybank.gd', 'gd_core_py.gd_core_items.Piggybank'),
    ('gd_core_items/Shield.gd', 'gd_core_py.gd_core_items.Shield'),
    ('gd_core_items/DragonEgg.gd', 'gd_core_py.gd_core_items.DragonEgg'),
    ('gd_core_items/LeatherHelm.gd', 'gd_core_py.gd_core_items.LeatherHelm'),
    ('gd_core_items/HealthPotion.gd', 'gd_core_py.gd_core_items.HealthPotion'),
    ('gd_core_items/PestilenceFlask.gd', 'gd_core_py.gd_core_items.PestilenceFlask'),
    ('gd_core_items/StoneSkinPotion.gd', 'gd_core_py.gd_core_items.StoneSkinPotion'),
    ('gd_core_items/AceofSpades.gd', 'gd_core_py.gd_core_items.AceofSpades'),
    ('gd_core_items/AcornCollar.gd', 'gd_core_py.gd_core_items.AcornCollar'),
    ('gd_core_items/ArtifactStoneCold.gd', 'gd_core_py.gd_core_items.ArtifactStoneCold'),
    ('gd_core_items/ArtifactStoneHeat.gd', 'gd_core_py.gd_core_items.ArtifactStoneHeat'),
    ('gd_core_items/BagofStones.gd', 'gd_core_py.gd_core_items.BagofStones'),
    ('gd_core_items/Banana.gd', 'gd_core_py.gd_core_items.Banana'),
    ('gd_core_items/BloodAmulet.gd', 'gd_core_py.gd_core_items.BloodAmulet'),
    ('gd_core_items/BloodGoobert.gd', 'gd_core_py.gd_core_items.BloodGoobert'),
    ('gd_core_items/Bloodthorne.gd', 'gd_core_py.gd_core_items.Bloodthorne'),
    ('gd_core_items/BloodyDagger.gd', 'gd_core_py.gd_core_items.BloodyDagger'),
    ('gd_core_items/Blueberries.gd', 'gd_core_py.gd_core_items.Blueberries'),
    ('gd_core_items/BowandArrow.gd', 'gd_core_py.gd_core_items.BowandArrow'),
    ('gd_core_items/BoxofRiches.gd', 'gd_core_py.gd_core_items.BoxofRiches'),
    ('gd_core_items/Broom.gd', 'gd_core_py.gd_core_items.Broom'),
    ('gd_core_items/BurningCoal.gd', 'gd_core_py.gd_core_items.BurningCoal'),
    ('gd_core_items/BurningTorch.gd', 'gd_core_py.gd_core_items.BurningTorch'),
    ('gd_core_items/Carrot.gd', 'gd_core_py.gd_core_items.Carrot'),
    ('gd_core_items/CarrotGoobert.gd', 'gd_core_py.gd_core_items.CarrotGoobert'),
    ('gd_core_items/ClawsofAttack.gd', 'gd_core_py.gd_core_items.ClawsofAttack'),
    ('gd_core_items/Coins.gd', 'gd_core_py.gd_core_items.Coins'),
    ('gd_core_items/CorruptedArmor.gd', 'gd_core_py.gd_core_items.CorruptedArmor'),
    ('gd_core_items/CritwoodStaff.gd', 'gd_core_py.gd_core_items.CritwoodStaff'),
    ('gd_core_items/Crossblades.gd', 'gd_core_py.gd_core_items.Crossblades'),
    ('gd_core_items/Crown.gd', 'gd_core_py.gd_core_items.Crown'),
    ('gd_core_items/CursedDagger.gd', 'gd_core_py.gd_core_items.CursedDagger'),
    ('gd_core_items/CursedHairComb.gd', 'gd_core_py.gd_core_items.CursedHairComb'),
    ('gd_core_items/CustomerCard.gd', 'gd_core_py.gd_core_items.CustomerCard'),
    ('gd_core_items/DancingDragon.gd', 'gd_core_py.gd_core_items.DancingDragon'),
    ('gd_core_items/DarkestLotus.gd', 'gd_core_py.gd_core_items.DarkestLotus'),
    ('gd_core_items/Darksaber.gd', 'gd_core_py.gd_core_items.Darksaber'),
    ('gd_core_items/DeathScythe.gd', 'gd_core_py.gd_core_items.DeathScythe'),
    ('gd_core_items/DeckofCards.gd', 'gd_core_py.gd_core_items.DeckofCards'),
    ('gd_core_items/DemonicFlask.gd', 'gd_core_py.gd_core_items.DemonicFlask'),
    ('gd_core_items/DjinnLamp.gd', 'gd_core_py.gd_core_items.DjinnLamp'),
    ('gd_core_items/Eggscalibur.gd', 'gd_core_py.gd_core_items.Eggscalibur'),
    ('gd_core_items/EvilCap.gd', 'gd_core_py.gd_core_items.EvilCap'),
    ('gd_core_items/FalconBlade.gd', 'gd_core_py.gd_core_items.FalconBlade'),
    ('gd_core_items/FancyFencingRapier.gd', 'gd_core_py.gd_core_items.FancyFencingRapier'),
    ('gd_core_items/Fanfare.gd', 'gd_core_py.gd_core_items.Fanfare'),
    ('gd_core_items/FannyPack.gd', 'gd_core_py.gd_core_items.FannyPack'),
    ('gd_core_items/Flute.gd', 'gd_core_py.gd_core_items.Flute'),
    ('gd_core_items/FlyAgaric.gd', 'gd_core_py.gd_core_items.FlyAgaric'),
    ('gd_core_items/Garlic.gd', 'gd_core_py.gd_core_items.Garlic'),
    ('gd_core_items/GingerbreadMan.gd', 'gd_core_py.gd_core_items.GingerbreadMan'),
    ('gd_core_items/GlovesofHaste.gd', 'gd_core_py.gd_core_items.GlovesofHaste'),
    ('gd_core_items/Greatsword.gd', 'gd_core_py.gd_core_items.Greatsword'),
    ('gd_core_items/Hammer.gd', 'gd_core_py.gd_core_items.Hammer'),
    ('gd_core_items/HealingHerbs.gd', 'gd_core_py.gd_core_items.HealingHerbs'),
    ('gd_core_items/HeartContainer.gd', 'gd_core_py.gd_core_items.HeartContainer'),
    ('gd_core_items/HeartofDarkness.gd', 'gd_core_py.gd_core_items.HeartofDarkness'),
    ('gd_core_items/HeroLongsword.gd', 'gd_core_py.gd_core_items.HeroLongsword'),
    ('gd_core_items/HeroSword.gd', 'gd_core_py.gd_core_items.HeroSword'),
    ('gd_core_items/HeroicPotion.gd', 'gd_core_py.gd_core_items.HeroicPotion'),
    ('gd_core_items/HoloFireLizard.gd', 'gd_core_py.gd_core_items.HoloFireLizard'),
    ('gd_core_items/HolyArmor.gd', 'gd_core_py.gd_core_items.HolyArmor'),
    ('gd_core_items/HolySpear.gd', 'gd_core_py.gd_core_items.HolySpear'),
    ('gd_core_items/HungryBlade.gd', 'gd_core_py.gd_core_items.HungryBlade'),
    ('gd_core_items/Jynxtorquilla.gd', 'gd_core_py.gd_core_items.Jynxtorquilla'),
    ('gd_core_items/LeatherArmor.gd', 'gd_core_py.gd_core_items.LeatherArmor'),
    ('gd_core_items/LeatherBoots.gd', 'gd_core_py.gd_core_items.LeatherBoots'),
    ('gd_core_items/LightGoobert.gd', 'gd_core_py.gd_core_items.LightGoobert'),
    ('gd_core_items/Lightsaber.gd', 'gd_core_py.gd_core_items.Lightsaber'),
    ('gd_core_items/LuckyBow.gd', 'gd_core_py.gd_core_items.LuckyBow'),
    ('gd_core_items/LuckyClover.gd', 'gd_core_py.gd_core_items.LuckyClover'),
    ('gd_core_items/LuckyPiggy.gd', 'gd_core_py.gd_core_items.LuckyPiggy'),
    ('gd_core_items/MagicStaff.gd', 'gd_core_py.gd_core_items.MagicStaff'),
    ('gd_core_items/MagicTorch.gd', 'gd_core_py.gd_core_items.MagicTorch'),
    ('gd_core_items/ManaOrb.gd', 'gd_core_py.gd_core_items.ManaOrb'),
    ('gd_core_items/ManaPotion.gd', 'gd_core_py.gd_core_items.ManaPotion'),
    ('gd_core_items/Manathirst.gd', 'gd_core_py.gd_core_items.Manathirst'),
    ('gd_core_items/MoonShield.gd', 'gd_core_py.gd_core_items.MoonShield'),
    ('gd_core_items/MrStruggles.gd', 'gd_core_py.gd_core_items.MrStruggles'),
    ('gd_core_items/Pandamonium.gd', 'gd_core_py.gd_core_items.Pandamonium'),
    ('gd_core_items/PiercingArrow.gd', 'gd_core_py.gd_core_items.PiercingArrow'),
    ('gd_core_items/Pineapple.gd', 'gd_core_py.gd_core_items.Pineapple'),
    ('gd_core_items/PlatinCustomerCard.gd', 'gd_core_py.gd_core_items.PlatinCustomerCard'),
    ('gd_core_items/PocketSand.gd', 'gd_core_py.gd_core_items.PocketSand'),
    ('gd_core_items/PoisonBow.gd', 'gd_core_py.gd_core_items.PoisonBow'),
    ('gd_core_items/PoisonDagger.gd', 'gd_core_py.gd_core_items.PoisonDagger'),
    ('gd_core_items/PoisonGoobert.gd', 'gd_core_py.gd_core_items.PoisonGoobert'),
    ('gd_core_items/PoisonIvy.gd', 'gd_core_py.gd_core_items.PoisonIvy'),
    ('gd_core_items/PotionBelt.gd', 'gd_core_py.gd_core_items.PotionBelt'),
    ('gd_core_items/Present.gd', 'gd_core_py.gd_core_items.Present'),
    ('gd_core_items/ProtectivePurse.gd', 'gd_core_py.gd_core_items.ProtectivePurse'),
    ('gd_core_items/Pumpkin.gd', 'gd_core_py.gd_core_items.Pumpkin'),
    ('gd_core_items/RainbowGoobert.gd', 'gd_core_py.gd_core_items.RainbowGoobert'),
    ('gd_core_items/RainbowGoobertRanger.gd', 'gd_core_py.gd_core_items.RainbowGoobertRanger'),
    ('gd_core_items/RangerBag.gd', 'gd_core_py.gd_core_items.RangerBag'),
    ('gd_core_items/RibSawBlade.gd', 'gd_core_py.gd_core_items.RibSawBlade'),
    ('gd_core_items/RubyChonk.gd', 'gd_core_py.gd_core_items.RubyChonk'),
    ('gd_core_items/RubyEgg.gd', 'gd_core_py.gd_core_items.RubyEgg'),
    ('gd_core_items/RubyWhelp.gd', 'gd_core_py.gd_core_items.RubyWhelp'),
    ('gd_core_items/ShieldofValor.gd', 'gd_core_py.gd_core_items.ShieldofValor'),
    ('gd_core_items/Shovel.gd', 'gd_core_py.gd_core_items.Shovel'),
    ('gd_core_items/Spear.gd', 'gd_core_py.gd_core_items.Spear'),
    ('gd_core_items/SpectralDagger.gd', 'gd_core_py.gd_core_items.SpectralDagger'),
    ('gd_core_items/SpikedShield.gd', 'gd_core_py.gd_core_items.SpikedShield'),
    ('gd_core_items/StaffofUnhealing.gd', 'gd_core_py.gd_core_items.StaffofUnhealing'),
    ('gd_core_items/StaminaSack.gd', 'gd_core_py.gd_core_items.StaminaSack'),
    ('gd_core_items/SteelGoobert.gd', 'gd_core_py.gd_core_items.SteelGoobert'),
    ('gd_core_items/StoneHelm.gd', 'gd_core_py.gd_core_items.StoneHelm'),
    ('gd_core_items/StorageCoffin.gd', 'gd_core_py.gd_core_items.StorageCoffin'),
    ('gd_core_items/StrongDemonicFlask.gd', 'gd_core_py.gd_core_items.StrongDemonicFlask'),
    ('gd_core_items/StrongHealthPotion.gd', 'gd_core_py.gd_core_items.StrongHealthPotion'),
    ('gd_core_items/StrongPestilenceFlask.gd', 'gd_core_py.gd_core_items.StrongPestilenceFlask'),
    ('gd_core_items/StrongStoneSkinPotion.gd', 'gd_core_py.gd_core_items.StrongStoneSkinPotion'),
    ('gd_core_items/TheFool.gd', 'gd_core_py.gd_core_items.TheFool'),
    ('gd_core_items/TheLovers.gd', 'gd_core_py.gd_core_items.TheLovers'),
    ('gd_core_items/ThornBow.gd', 'gd_core_py.gd_core_items.ThornBow'),
    ('gd_core_items/ThornWhip.gd', 'gd_core_py.gd_core_items.ThornWhip'),
    ('gd_core_items/Torch.gd', 'gd_core_py.gd_core_items.Torch'),
    ('gd_core_items/VampiricArmor.gd', 'gd_core_py.gd_core_items.VampiricArmor'),
    ('gd_core_items/VampiricGloves.gd', 'gd_core_py.gd_core_items.VampiricGloves'),
    ('gd_core_items/VampiricScythe.gd', 'gd_core_py.gd_core_items.VampiricScythe'),
    ('gd_core_items/VillainSword.gd', 'gd_core_py.gd_core_items.VillainSword'),
    ('gd_core_items/WalrusTusk.gd', 'gd_core_py.gd_core_items.WalrusTusk'),
    ('gd_core_items/Whetstone.gd', 'gd_core_py.gd_core_items.Whetstone'),
    ('gd_core_items/White-EyesBlueDragon.gd', 'gd_core_py.gd_core_items.White_EyesBlueDragon'),
    ('gd_core_items/Wolpertinger.gd', 'gd_core_py.gd_core_items.Wolpertinger'),
    ('gd_core_items/WoodenBuckler.gd', 'gd_core_py.gd_core_items.WoodenBuckler'),
    ('gd_core_items/WoodenSword.gd', 'gd_core_py.gd_core_items.WoodenSword'),
    ('gd_core_items/YggdrasilLeaf.gd', 'gd_core_py.gd_core_items.YggdrasilLeaf'),
    ('gd_core_items/Exclusive/AcornAce.gd', 'gd_core_py.gd_core_items.Exclusive.AcornAce'),
    ('gd_core_items/Exclusive/AmethystEgg.gd', 'gd_core_py.gd_core_items.Exclusive.AmethystEgg'),
    ('gd_core_items/Exclusive/AmethystWhelp.gd', 'gd_core_py.gd_core_items.Exclusive.AmethystWhelp'),
    ('gd_core_items/Exclusive/AmuletUnidentified.gd', 'gd_core_py.gd_core_items.Exclusive.AmuletUnidentified'),
    ('gd_core_items/Exclusive/AmuletofAgility.gd', 'gd_core_py.gd_core_items.Exclusive.AmuletofAgility'),
    ('gd_core_items/Exclusive/AmuletofAlchemy.gd', 'gd_core_py.gd_core_items.Exclusive.AmuletofAlchemy'),
    ('gd_core_items/Exclusive/AmuletofDarkness.gd', 'gd_core_py.gd_core_items.Exclusive.AmuletofDarkness'),
    ('gd_core_items/Exclusive/AmuletofFeasting.gd', 'gd_core_py.gd_core_items.Exclusive.AmuletofFeasting'),
    ('gd_core_items/Exclusive/AmuletofFortune.gd', 'gd_core_py.gd_core_items.Exclusive.AmuletofFortune'),
    ('gd_core_items/Exclusive/AmuletofLife.gd', 'gd_core_py.gd_core_items.Exclusive.AmuletofLife'),
    ('gd_core_items/Exclusive/AmuletofLight.gd', 'gd_core_py.gd_core_items.Exclusive.AmuletofLight'),
    ('gd_core_items/Exclusive/AmuletofSteel.gd', 'gd_core_py.gd_core_items.Exclusive.AmuletofSteel'),
    ('gd_core_items/Exclusive/AmuletoftheWild.gd', 'gd_core_py.gd_core_items.Exclusive.AmuletoftheWild'),
    ('gd_core_items/Exclusive/AngelCrystal.gd', 'gd_core_py.gd_core_items.Exclusive.AngelCrystal'),
    ('gd_core_items/Exclusive/Anvil.gd', 'gd_core_py.gd_core_items.Exclusive.Anvil'),
    ('gd_core_items/Exclusive/ArcaneBoots.gd', 'gd_core_py.gd_core_items.Exclusive.ArcaneBoots'),
    ('gd_core_items/Exclusive/ArcaneIntellect.gd', 'gd_core_py.gd_core_items.Exclusive.ArcaneIntellect'),
    ('gd_core_items/Exclusive/CouragePuppy.gd', 'gd_core_py.gd_core_items.Exclusive.CouragePuppy'),
    ('gd_core_items/Exclusive/ArmoredCouragePuppy.gd', 'gd_core_py.gd_core_items.Exclusive.ArmoredCouragePuppy'),
    ('gd_core_items/Exclusive/PowerPuppy.gd', 'gd_core_py.gd_core_items.Exclusive.PowerPuppy'),
    ('gd_core_items/Exclusive/ArmoredPowerPuppy.gd', 'gd_core_py.gd_core_items.Exclusive.ArmoredPowerPuppy'),
    ('gd_core_items/Exclusive/WisdomPuppy.gd', 'gd_core_py.gd_core_items.Exclusive.WisdomPuppy'),
    ('gd_core_items/Exclusive/ArmoredWisdomPuppy.gd', 'gd_core_py.gd_core_items.Exclusive.ArmoredWisdomPuppy'),
    ('gd_core_items/Exclusive/ArtifactStoneDeath.gd', 'gd_core_py.gd_core_items.Exclusive.ArtifactStoneDeath'),
    ('gd_core_items/Exclusive/Automanaton.gd', 'gd_core_py.gd_core_items.Exclusive.Automanaton'),
    ('gd_core_items/Exclusive/Axe.gd', 'gd_core_py.gd_core_items.Exclusive.Axe'),
    ('gd_core_items/Exclusive/BadgerRune.gd', 'gd_core_py.gd_core_items.Exclusive.BadgerRune'),
    ('gd_core_items/Exclusive/SpiritCompanion.gd', 'gd_core_py.gd_core_items.Exclusive.SpiritCompanion'),
    ('gd_core_items/Exclusive/BadgerSpirit.gd', 'gd_core_py.gd_core_items.Exclusive.BadgerSpirit'),
    ('gd_core_items/Exclusive/BagofGiving.gd', 'gd_core_py.gd_core_items.Exclusive.BagofGiving'),
    ('gd_core_items/Exclusive/Bagtacular.gd', 'gd_core_py.gd_core_items.Exclusive.Bagtacular'),
    ('gd_core_items/Exclusive/Battery.gd', 'gd_core_py.gd_core_items.Exclusive.Battery'),
    ('gd_core_items/Exclusive/Bazooka.gd', 'gd_core_py.gd_core_items.Exclusive.Bazooka'),
    ('gd_core_items/Exclusive/BerserkerBag.gd', 'gd_core_py.gd_core_items.Exclusive.BerserkerBag'),
    ('gd_core_items/Exclusive/Bewitchment.gd', 'gd_core_py.gd_core_items.Exclusive.Bewitchment'),
    ('gd_core_items/Exclusive/BigBloodthorne.gd', 'gd_core_py.gd_core_items.Exclusive.BigBloodthorne'),
    ('gd_core_items/Exclusive/BionicArmor.gd', 'gd_core_py.gd_core_items.Exclusive.BionicArmor'),
    ('gd_core_items/Exclusive/Cube.gd', 'gd_core_py.gd_core_items.Exclusive.Cube'),
    ('gd_core_items/Exclusive/BismuthCube.gd', 'gd_core_py.gd_core_items.Exclusive.BismuthCube'),
    ('gd_core_items/Exclusive/BloodManipulation.gd', 'gd_core_py.gd_core_items.Exclusive.BloodManipulation'),
    ('gd_core_items/Exclusive/Bomb.gd', 'gd_core_py.gd_core_items.Exclusive.Bomb'),
    ('gd_core_items/Exclusive/BookofBasics.gd', 'gd_core_py.gd_core_items.Exclusive.BookofBasics'),
    ('gd_core_items/Exclusive/BookofDarkness.gd', 'gd_core_py.gd_core_items.Exclusive.BookofDarkness'),
    ('gd_core_items/Exclusive/BookofIce.gd', 'gd_core_py.gd_core_items.Exclusive.BookofIce'),
    ('gd_core_items/Exclusive/BookofLight.gd', 'gd_core_py.gd_core_items.Exclusive.BookofLight'),
    ('gd_core_items/Exclusive/BookofNature.gd', 'gd_core_py.gd_core_items.Exclusive.BookofNature'),
    ('gd_core_items/Exclusive/Boomerang.gd', 'gd_core_py.gd_core_items.Exclusive.Boomerang'),
    ('gd_core_items/Exclusive/BowlofTreats.gd', 'gd_core_py.gd_core_items.Exclusive.BowlofTreats'),
    ('gd_core_items/Exclusive/BoxofProsperity.gd', 'gd_core_py.gd_core_items.Exclusive.BoxofProsperity'),
    ('gd_core_items/Exclusive/BrassKnuckles.gd', 'gd_core_py.gd_core_items.Exclusive.BrassKnuckles'),
    ('gd_core_items/Exclusive/Broccoli.gd', 'gd_core_py.gd_core_items.Exclusive.Broccoli'),
    ('gd_core_items/Exclusive/BroccoliGoobert.gd', 'gd_core_py.gd_core_items.Exclusive.BroccoliGoobert'),
    ('gd_core_items/Exclusive/Broccotree.gd', 'gd_core_py.gd_core_items.Exclusive.Broccotree'),
    ('gd_core_items/Exclusive/BurningBanner.gd', 'gd_core_py.gd_core_items.Exclusive.BurningBanner'),
    ('gd_core_items/Exclusive/BurningSword.gd', 'gd_core_py.gd_core_items.Exclusive.BurningSword'),
    ('gd_core_items/Exclusive/BurningBlade.gd', 'gd_core_py.gd_core_items.Exclusive.BurningBlade'),
    ('gd_core_items/Exclusive/BurningSpikes.gd', 'gd_core_py.gd_core_items.Exclusive.BurningSpikes'),
    ('gd_core_items/Exclusive/BustedBlade.gd', 'gd_core_py.gd_core_items.Exclusive.BustedBlade'),
    ('gd_core_items/Exclusive/BuytheHolyLight.gd', 'gd_core_py.gd_core_items.Exclusive.BuytheHolyLight'),
    ('gd_core_items/Exclusive/CapofBrilliance.gd', 'gd_core_py.gd_core_items.Exclusive.CapofBrilliance'),
    ('gd_core_items/Exclusive/CatSpirit.gd', 'gd_core_py.gd_core_items.Exclusive.CatSpirit'),
    ('gd_core_items/Exclusive/Cauldron.gd', 'gd_core_py.gd_core_items.Exclusive.Cauldron'),
    ('gd_core_items/Exclusive/ChainWhip.gd', 'gd_core_py.gd_core_items.Exclusive.ChainWhip'),
    ('gd_core_items/Exclusive/Chainsaw.gd', 'gd_core_py.gd_core_items.Exclusive.Chainsaw'),
    ('gd_core_items/Exclusive/ChargeSplitter.gd', 'gd_core_py.gd_core_items.Exclusive.ChargeSplitter'),
    ('gd_core_items/Exclusive/Cheese.gd', 'gd_core_py.gd_core_items.Exclusive.Cheese'),
    ('gd_core_items/Exclusive/CheeseGoobert.gd', 'gd_core_py.gd_core_items.Exclusive.CheeseGoobert'),
    ('gd_core_items/Exclusive/ChessBoard.gd', 'gd_core_py.gd_core_items.Exclusive.ChessBoard'),
    ('gd_core_items/Exclusive/ChessMaster.gd', 'gd_core_py.gd_core_items.Exclusive.ChessMaster'),
    ('gd_core_items/Exclusive/ChiliGoobert.gd', 'gd_core_py.gd_core_items.Exclusive.ChiliGoobert'),
    ('gd_core_items/Exclusive/ChiliPepper.gd', 'gd_core_py.gd_core_items.Exclusive.ChiliPepper'),
    ('gd_core_items/Exclusive/ChromeCube.gd', 'gd_core_py.gd_core_items.Exclusive.ChromeCube'),
    ('gd_core_items/Exclusive/Cog.gd', 'gd_core_py.gd_core_items.Exclusive.Cog'),
    ('gd_core_items/Exclusive/CogBadge.gd', 'gd_core_py.gd_core_items.Exclusive.CogBadge'),
    ('gd_core_items/Exclusive/Coil.gd', 'gd_core_py.gd_core_items.Exclusive.Coil'),
    ('gd_core_items/Exclusive/ConTrapTron.gd', 'gd_core_py.gd_core_items.Exclusive.ConTrapTron'),
    ('gd_core_items/Exclusive/CriticalPoison.gd', 'gd_core_py.gd_core_items.Exclusive.CriticalPoison'),
    ('gd_core_items/Exclusive/Crow.gd', 'gd_core_py.gd_core_items.Exclusive.Crow'),
    ('gd_core_items/Exclusive/Cthulhu.gd', 'gd_core_py.gd_core_items.Exclusive.Cthulhu'),
    ('gd_core_items/Exclusive/Cubert.gd', 'gd_core_py.gd_core_items.Exclusive.Cubert'),
    ('gd_core_items/Exclusive/Cupcake.gd', 'gd_core_py.gd_core_items.Exclusive.Cupcake'),
    ('gd_core_items/Exclusive/CupcakeDragon.gd', 'gd_core_py.gd_core_items.Exclusive.CupcakeDragon'),
    ('gd_core_items/Exclusive/CupcakeGoobert.gd', 'gd_core_py.gd_core_items.Exclusive.CupcakeGoobert'),
    ('gd_core_items/Exclusive/CupcakeStaff.gd', 'gd_core_py.gd_core_items.Exclusive.CupcakeStaff'),
    ('gd_core_items/Exclusive/Daggerang.gd', 'gd_core_py.gd_core_items.Exclusive.Daggerang'),
    ('gd_core_items/Exclusive/DarkLantern.gd', 'gd_core_py.gd_core_items.Exclusive.DarkLantern'),
    ('gd_core_items/Exclusive/DarkRitual.gd', 'gd_core_py.gd_core_items.Exclusive.DarkRitual'),
    ('gd_core_items/Exclusive/DeathLotus.gd', 'gd_core_py.gd_core_items.Exclusive.DeathLotus'),
    ('gd_core_items/Exclusive/DeerTotem.gd', 'gd_core_py.gd_core_items.Exclusive.DeerTotem'),
    ('gd_core_items/Exclusive/DevouringSphere.gd', 'gd_core_py.gd_core_items.Exclusive.DevouringSphere'),
    ('gd_core_items/Exclusive/DigDeeper.gd', 'gd_core_py.gd_core_items.Exclusive.DigDeeper'),
    ('gd_core_items/Exclusive/DivinePotion.gd', 'gd_core_py.gd_core_items.Exclusive.DivinePotion'),
    ('gd_core_items/Exclusive/DoomCap.gd', 'gd_core_py.gd_core_items.Exclusive.DoomCap'),
    ('gd_core_items/Exclusive/DoubleAxe.gd', 'gd_core_py.gd_core_items.Exclusive.DoubleAxe'),
    ('gd_core_items/Exclusive/DoubleRainbow.gd', 'gd_core_py.gd_core_items.Exclusive.DoubleRainbow'),
    ('gd_core_items/Exclusive/DraconicOrb.gd', 'gd_core_py.gd_core_items.Exclusive.DraconicOrb'),
    ('gd_core_items/Exclusive/DragonClaws.gd', 'gd_core_py.gd_core_items.Exclusive.DragonClaws'),
    ('gd_core_items/Exclusive/DragonKnight.gd', 'gd_core_py.gd_core_items.Exclusive.DragonKnight'),
    ('gd_core_items/Exclusive/DragonNest.gd', 'gd_core_py.gd_core_items.Exclusive.DragonNest'),
    ('gd_core_items/Exclusive/DragonSet.gd', 'gd_core_py.gd_core_items.Exclusive.DragonSet'),
    ('gd_core_items/Exclusive/DragonscaleArmor.gd', 'gd_core_py.gd_core_items.Exclusive.DragonscaleArmor'),
    ('gd_core_items/Exclusive/DragonskinBoots.gd', 'gd_core_py.gd_core_items.Exclusive.DragonskinBoots'),
    ('gd_core_items/Exclusive/DualWielding.gd', 'gd_core_py.gd_core_items.Exclusive.DualWielding'),
    ('gd_core_items/Exclusive/Eat-o-matic.gd', 'gd_core_py.gd_core_items.Exclusive.Eat_o_matic'),
    ('gd_core_items/Exclusive/EchoingBattlecry.gd', 'gd_core_py.gd_core_items.Exclusive.EchoingBattlecry'),
    ('gd_core_items/Exclusive/ElectricTorch.gd', 'gd_core_py.gd_core_items.Exclusive.ElectricTorch'),
    ('gd_core_items/Exclusive/ElephantRune.gd', 'gd_core_py.gd_core_items.Exclusive.ElephantRune'),
    ('gd_core_items/Exclusive/EmeraldEgg.gd', 'gd_core_py.gd_core_items.Exclusive.EmeraldEgg'),
    ('gd_core_items/Exclusive/EmeraldWhelp.gd', 'gd_core_py.gd_core_items.Exclusive.EmeraldWhelp'),
    ('gd_core_items/Exclusive/EmployeeUniform.gd', 'gd_core_py.gd_core_items.Exclusive.EmployeeUniform'),
    ('gd_core_items/Exclusive/EnchantedWeapons.gd', 'gd_core_py.gd_core_items.Exclusive.EnchantedWeapons'),
    ('gd_core_items/Exclusive/EnergyConversion.gd', 'gd_core_py.gd_core_items.Exclusive.EnergyConversion'),
    ('gd_core_items/Exclusive/EngineerBag2.gd', 'gd_core_py.gd_core_items.Exclusive.EngineerBag2'),
    ('gd_core_items/Exclusive/EngineerBox.gd', 'gd_core_py.gd_core_items.Exclusive.EngineerBox'),
    ('gd_core_items/Exclusive/Everburning.gd', 'gd_core_py.gd_core_items.Exclusive.Everburning'),
    ('gd_core_items/Exclusive/EvilHat.gd', 'gd_core_py.gd_core_items.Exclusive.EvilHat'),
    ('gd_core_items/Exclusive/ExtraAngy.gd', 'gd_core_py.gd_core_items.Exclusive.ExtraAngy'),
    ('gd_core_items/Exclusive/ExtraBags.gd', 'gd_core_py.gd_core_items.Exclusive.ExtraBags'),
    ('gd_core_items/Exclusive/FalseLife.gd', 'gd_core_py.gd_core_items.Exclusive.FalseLife'),
    ('gd_core_items/Exclusive/Fedora.gd', 'gd_core_py.gd_core_items.Exclusive.Fedora'),
    ('gd_core_items/Exclusive/FirePit.gd', 'gd_core_py.gd_core_items.Exclusive.FirePit'),
    ('gd_core_items/Exclusive/Shelly.gd', 'gd_core_py.gd_core_items.Exclusive.Shelly'),
    ('gd_core_items/Exclusive/FireShelly.gd', 'gd_core_py.gd_core_items.Exclusive.FireShelly'),
    ('gd_core_items/Exclusive/Flame.gd', 'gd_core_py.gd_core_items.Exclusive.Flame'),
    ('gd_core_items/Exclusive/FlameBadge.gd', 'gd_core_py.gd_core_items.Exclusive.FlameBadge'),
    ('gd_core_items/Exclusive/FlameWhip.gd', 'gd_core_py.gd_core_items.Exclusive.FlameWhip'),
    ('gd_core_items/Exclusive/ForestDragon.gd', 'gd_core_py.gd_core_items.Exclusive.ForestDragon'),
    ('gd_core_items/Exclusive/ForestFriend.gd', 'gd_core_py.gd_core_items.Exclusive.ForestFriend'),
    ('gd_core_items/Exclusive/ForgingHammer.gd', 'gd_core_py.gd_core_items.Exclusive.ForgingHammer'),
    ('gd_core_items/Exclusive/FortunasKiss.gd', 'gd_core_py.gd_core_items.Exclusive.FortunasKiss'),
    ('gd_core_items/Exclusive/FriendlyFire.gd', 'gd_core_py.gd_core_items.Exclusive.FriendlyFire'),
    ('gd_core_items/Exclusive/Toad.gd', 'gd_core_py.gd_core_items.Exclusive.Toad'),
    ('gd_core_items/Exclusive/FrogPrince.gd', 'gd_core_py.gd_core_items.Exclusive.FrogPrince'),
    ('gd_core_items/Exclusive/Frostbite.gd', 'gd_core_py.gd_core_items.Exclusive.Frostbite'),
    ('gd_core_items/Exclusive/FrozenBuckler.gd', 'gd_core_py.gd_core_items.Exclusive.FrozenBuckler'),
    ('gd_core_items/Exclusive/FrozenFlame.gd', 'gd_core_py.gd_core_items.Exclusive.FrozenFlame'),
    ('gd_core_items/Exclusive/FullBodyProtection.gd', 'gd_core_py.gd_core_items.Exclusive.FullBodyProtection'),
    ('gd_core_items/Exclusive/FurciferPrime.gd', 'gd_core_py.gd_core_items.Exclusive.FurciferPrime'),
    ('gd_core_items/Exclusive/Generator.gd', 'gd_core_py.gd_core_items.Exclusive.Generator'),
    ('gd_core_items/Exclusive/Ghost.gd', 'gd_core_py.gd_core_items.Exclusive.Ghost'),
    ('gd_core_items/Exclusive/Gigawatz.gd', 'gd_core_py.gd_core_items.Exclusive.Gigawatz'),
    ('gd_core_items/Exclusive/GirlPower.gd', 'gd_core_py.gd_core_items.Exclusive.GirlPower'),
    ('gd_core_items/Exclusive/GoldArmor.gd', 'gd_core_py.gd_core_items.Exclusive.GoldArmor'),
    ('gd_core_items/Exclusive/GoldCube.gd', 'gd_core_py.gd_core_items.Exclusive.GoldCube'),
    ('gd_core_items/Exclusive/Halberd.gd', 'gd_core_py.gd_core_items.Exclusive.Halberd'),
    ('gd_core_items/Exclusive/Hardwood.gd', 'gd_core_py.gd_core_items.Exclusive.Hardwood'),
    ('gd_core_items/Exclusive/HawkRune.gd', 'gd_core_py.gd_core_items.Exclusive.HawkRune'),
    ('gd_core_items/Exclusive/HeartShield.gd', 'gd_core_py.gd_core_items.Exclusive.HeartShield'),
    ('gd_core_items/Exclusive/HeartoftheCards.gd', 'gd_core_py.gd_core_items.Exclusive.HeartoftheCards'),
    ('gd_core_items/Exclusive/HeavyDrinking.gd', 'gd_core_py.gd_core_items.Exclusive.HeavyDrinking'),
    ('gd_core_items/Exclusive/Hedgehog.gd', 'gd_core_py.gd_core_items.Exclusive.Hedgehog'),
    ('gd_core_items/Exclusive/HeroShield.gd', 'gd_core_py.gd_core_items.Exclusive.HeroShield'),
    ('gd_core_items/Exclusive/HogusBogus.gd', 'gd_core_py.gd_core_items.Exclusive.HogusBogus'),
    ('gd_core_items/Exclusive/Holdall.gd', 'gd_core_py.gd_core_items.Exclusive.Holdall'),
    ('gd_core_items/Exclusive/HolyCollar.gd', 'gd_core_py.gd_core_items.Exclusive.HolyCollar'),
    ('gd_core_items/Exclusive/HyperHedgehog.gd', 'gd_core_py.gd_core_items.Exclusive.HyperHedgehog'),
    ('gd_core_items/Exclusive/Hypercube.gd', 'gd_core_py.gd_core_items.Exclusive.Hypercube'),
    ('gd_core_items/Exclusive/IceArmor.gd', 'gd_core_py.gd_core_items.Exclusive.IceArmor'),
    ('gd_core_items/Exclusive/IceDragon.gd', 'gd_core_py.gd_core_items.Exclusive.IceDragon'),
    ('gd_core_items/Exclusive/IceFlower.gd', 'gd_core_py.gd_core_items.Exclusive.IceFlower'),
    ('gd_core_items/Exclusive/InnerPower.gd', 'gd_core_py.gd_core_items.Exclusive.InnerPower'),
    ('gd_core_items/Exclusive/InvestmentOpportunity.gd', 'gd_core_py.gd_core_items.Exclusive.InvestmentOpportunity'),
    ('gd_core_items/Exclusive/Joker.gd', 'gd_core_py.gd_core_items.Exclusive.Joker'),
    ('gd_core_items/Exclusive/JustStats.gd', 'gd_core_py.gd_core_items.Exclusive.JustStats'),
    ('gd_core_items/Exclusive/JynxStaff.gd', 'gd_core_py.gd_core_items.Exclusive.JynxStaff'),
    ('gd_core_items/Exclusive/Katana.gd', 'gd_core_py.gd_core_items.Exclusive.Katana'),
    ('gd_core_items/Exclusive/KingCrown.gd', 'gd_core_py.gd_core_items.Exclusive.KingCrown'),
    ('gd_core_items/Exclusive/KingGoobert.gd', 'gd_core_py.gd_core_items.Exclusive.KingGoobert'),
    ('gd_core_items/Exclusive/KingoftheBling.gd', 'gd_core_py.gd_core_items.Exclusive.KingoftheBling'),
    ('gd_core_items/Exclusive/KnifetoMeetYou.gd', 'gd_core_py.gd_core_items.Exclusive.KnifetoMeetYou'),
    ('gd_core_items/Exclusive/Laboratory.gd', 'gd_core_py.gd_core_items.Exclusive.Laboratory'),
    ('gd_core_items/Exclusive/LeafBadge.gd', 'gd_core_py.gd_core_items.Exclusive.LeafBadge'),
    ('gd_core_items/Exclusive/LevelUp.gd', 'gd_core_py.gd_core_items.Exclusive.LevelUp'),
    ('gd_core_items/Exclusive/LightFlower.gd', 'gd_core_py.gd_core_items.Exclusive.LightFlower'),
    ('gd_core_items/Exclusive/LightningPotion.gd', 'gd_core_py.gd_core_items.Exclusive.LightningPotion'),
    ('gd_core_items/Exclusive/LightningStaff.gd', 'gd_core_py.gd_core_items.Exclusive.LightningStaff'),
    ('gd_core_items/Exclusive/LittleMimic.gd', 'gd_core_py.gd_core_items.Exclusive.LittleMimic'),
    ('gd_core_items/Exclusive/LongSpear.gd', 'gd_core_py.gd_core_items.Exclusive.LongSpear'),
    ('gd_core_items/Exclusive/Lootbox.gd', 'gd_core_py.gd_core_items.Exclusive.Lootbox'),
    ('gd_core_items/Exclusive/LuckyCat.gd', 'gd_core_py.gd_core_items.Exclusive.LuckyCat'),
    ('gd_core_items/Exclusive/LuckyShortbow.gd', 'gd_core_py.gd_core_items.Exclusive.LuckyShortbow'),
    ('gd_core_items/Exclusive/MageHat.gd', 'gd_core_py.gd_core_items.Exclusive.MageHat'),
    ('gd_core_items/Exclusive/MagicBadge.gd', 'gd_core_py.gd_core_items.Exclusive.MagicBadge'),
    ('gd_core_items/Exclusive/MagicCollar.gd', 'gd_core_py.gd_core_items.Exclusive.MagicCollar'),
    ('gd_core_items/Exclusive/MagicMirror.gd', 'gd_core_py.gd_core_items.Exclusive.MagicMirror'),
    ('gd_core_items/Exclusive/MagicRing.gd', 'gd_core_py.gd_core_items.Exclusive.MagicRing'),
    ('gd_core_items/Exclusive/MagiteccArmor.gd', 'gd_core_py.gd_core_items.Exclusive.MagiteccArmor'),
    ('gd_core_items/Exclusive/ManaCrystal.gd', 'gd_core_py.gd_core_items.Exclusive.ManaCrystal'),
    ('gd_core_items/Exclusive/ManaMastery.gd', 'gd_core_py.gd_core_items.Exclusive.ManaMastery'),
    ('gd_core_items/Exclusive/Mananana.gd', 'gd_core_py.gd_core_items.Exclusive.Mananana'),
    ('gd_core_items/Exclusive/Markswoman.gd', 'gd_core_py.gd_core_items.Exclusive.Markswoman'),
    ('gd_core_items/Exclusive/MechaBat.gd', 'gd_core_py.gd_core_items.Exclusive.MechaBat'),
    ('gd_core_items/Exclusive/MegaClover.gd', 'gd_core_py.gd_core_items.Exclusive.MegaClover'),
    ('gd_core_items/Exclusive/MercuryElemental.gd', 'gd_core_py.gd_core_items.Exclusive.MercuryElemental'),
    ('gd_core_items/Exclusive/MissFortune.gd', 'gd_core_py.gd_core_items.Exclusive.MissFortune'),
    ('gd_core_items/Exclusive/MoltenDagger.gd', 'gd_core_py.gd_core_items.Exclusive.MoltenDagger'),
    ('gd_core_items/Exclusive/MoltenGreatsword.gd', 'gd_core_py.gd_core_items.Exclusive.MoltenGreatsword'),
    ('gd_core_items/Exclusive/MoltenSpear.gd', 'gd_core_py.gd_core_items.Exclusive.MoltenSpear'),
    ('gd_core_items/Exclusive/MoltenSpear2.gd', 'gd_core_py.gd_core_items.Exclusive.MoltenSpear2'),
    ('gd_core_items/Exclusive/MoonArmor.gd', 'gd_core_py.gd_core_items.Exclusive.MoonArmor'),
    ('gd_core_items/Exclusive/MoreStats.gd', 'gd_core_py.gd_core_items.Exclusive.MoreStats'),
    ('gd_core_items/Exclusive/MrsStruggles.gd', 'gd_core_py.gd_core_items.Exclusive.MrsStruggles'),
    ('gd_core_items/Exclusive/MushroomFarm.gd', 'gd_core_py.gd_core_items.Exclusive.MushroomFarm'),
    ('gd_core_items/Exclusive/NoRushPlease.gd', 'gd_core_py.gd_core_items.Exclusive.NoRushPlease'),
    ('gd_core_items/Exclusive/NullBlade.gd', 'gd_core_py.gd_core_items.Exclusive.NullBlade'),
    ('gd_core_items/Exclusive/ObsidianDragon.gd', 'gd_core_py.gd_core_items.Exclusive.ObsidianDragon'),
    ('gd_core_items/Exclusive/OilLamp.gd', 'gd_core_py.gd_core_items.Exclusive.OilLamp'),
    ('gd_core_items/Exclusive/OnionCutter.gd', 'gd_core_py.gd_core_items.Exclusive.OnionCutter'),
    ('gd_core_items/Exclusive/OwlSpirit.gd', 'gd_core_py.gd_core_items.Exclusive.OwlSpirit'),
    ('gd_core_items/Exclusive/ParadiseBirb.gd', 'gd_core_py.gd_core_items.Exclusive.ParadiseBirb'),
    ('gd_core_items/Exclusive/PerpetuumMobile.gd', 'gd_core_py.gd_core_items.Exclusive.PerpetuumMobile'),
    ('gd_core_items/Exclusive/Phoenix.gd', 'gd_core_py.gd_core_items.Exclusive.Phoenix'),
    ('gd_core_items/Exclusive/Phoenix2.gd', 'gd_core_py.gd_core_items.Exclusive.Phoenix2'),
    ('gd_core_items/Exclusive/PiggyPinata.gd', 'gd_core_py.gd_core_items.Exclusive.PiggyPinata'),
    ('gd_core_items/Exclusive/PiggyofRiches.gd', 'gd_core_py.gd_core_items.Exclusive.PiggyofRiches'),
    ('gd_core_items/Exclusive/PineProtector.gd', 'gd_core_py.gd_core_items.Exclusive.PineProtector'),
    ('gd_core_items/Exclusive/PlasticCube.gd', 'gd_core_py.gd_core_items.Exclusive.PlasticCube'),
    ('gd_core_items/Exclusive/PoisonFrog.gd', 'gd_core_py.gd_core_items.Exclusive.PoisonFrog'),
    ('gd_core_items/Exclusive/PoisonGrenade.gd', 'gd_core_py.gd_core_items.Exclusive.PoisonGrenade'),
    ('gd_core_items/Exclusive/PoisonShortbow.gd', 'gd_core_py.gd_core_items.Exclusive.PoisonShortbow'),
    ('gd_core_items/Exclusive/PoisonSpear.gd', 'gd_core_py.gd_core_items.Exclusive.PoisonSpear'),
    ('gd_core_items/Exclusive/Pop.gd', 'gd_core_py.gd_core_items.Exclusive.Pop'),
    ('gd_core_items/Exclusive/PortableAltar.gd', 'gd_core_py.gd_core_items.Exclusive.PortableAltar'),
    ('gd_core_items/Exclusive/Pot.gd', 'gd_core_py.gd_core_items.Exclusive.Pot'),
    ('gd_core_items/Exclusive/PoweroftheMoon.gd', 'gd_core_py.gd_core_items.Exclusive.PoweroftheMoon'),
    ('gd_core_items/Exclusive/PrismaticSword.gd', 'gd_core_py.gd_core_items.Exclusive.PrismaticSword'),
    ('gd_core_items/Exclusive/PrismaticWand.gd', 'gd_core_py.gd_core_items.Exclusive.PrismaticWand'),
    ('gd_core_items/Exclusive/PuzzleBadge.gd', 'gd_core_py.gd_core_items.Exclusive.PuzzleBadge'),
    ('gd_core_items/Exclusive/PuzzlebagJ.gd', 'gd_core_py.gd_core_items.Exclusive.PuzzlebagJ'),
    ('gd_core_items/Exclusive/PuzzlebagL.gd', 'gd_core_py.gd_core_items.Exclusive.PuzzlebagL'),
    ('gd_core_items/Exclusive/PuzzlebagS.gd', 'gd_core_py.gd_core_items.Exclusive.PuzzlebagS'),
    ('gd_core_items/Exclusive/PuzzlebagT.gd', 'gd_core_py.gd_core_items.Exclusive.PuzzlebagT'),
    ('gd_core_items/Exclusive/PuzzlebagZ.gd', 'gd_core_py.gd_core_items.Exclusive.PuzzlebagZ'),
    ('gd_core_items/Exclusive/Puzzlebox.gd', 'gd_core_py.gd_core_items.Exclusive.Puzzlebox'),
    ('gd_core_items/Exclusive/RainbowBadge.gd', 'gd_core_py.gd_core_items.Exclusive.RainbowBadge'),
    ('gd_core_items/Exclusive/RainbowGoobertAdventurer.gd', 'gd_core_py.gd_core_items.Exclusive.RainbowGoobertAdventurer'),
    ('gd_core_items/Exclusive/RainbowGoobertBerserker.gd', 'gd_core_py.gd_core_items.Exclusive.RainbowGoobertBerserker'),
    ('gd_core_items/Exclusive/RainbowGoobertEngineer.gd', 'gd_core_py.gd_core_items.Exclusive.RainbowGoobertEngineer'),
    ('gd_core_items/Exclusive/RainbowGoobertMage.gd', 'gd_core_py.gd_core_items.Exclusive.RainbowGoobertMage'),
    ('gd_core_items/Exclusive/RainbowGoobertPyromancer.gd', 'gd_core_py.gd_core_items.Exclusive.RainbowGoobertPyromancer'),
    ('gd_core_items/Exclusive/RainbowOrb.gd', 'gd_core_py.gd_core_items.Exclusive.RainbowOrb'),
    ('gd_core_items/Exclusive/RainbowPotion.gd', 'gd_core_py.gd_core_items.Exclusive.RainbowPotion'),
    ('gd_core_items/Exclusive/RandomLoadoutBag.gd', 'gd_core_py.gd_core_items.Exclusive.RandomLoadoutBag'),
    ('gd_core_items/Exclusive/Rat.gd', 'gd_core_py.gd_core_items.Exclusive.Rat'),
    ('gd_core_items/Exclusive/RatChef.gd', 'gd_core_py.gd_core_items.Exclusive.RatChef'),
    ('gd_core_items/Exclusive/Recombobulator.gd', 'gd_core_py.gd_core_items.Exclusive.Recombobulator'),
    ('gd_core_items/Exclusive/RelicCase.gd', 'gd_core_py.gd_core_items.Exclusive.RelicCase'),
    ('gd_core_items/Exclusive/Repeater.gd', 'gd_core_py.gd_core_items.Exclusive.Repeater'),
    ('gd_core_items/Exclusive/Resistor.gd', 'gd_core_py.gd_core_items.Exclusive.Resistor'),
    ('gd_core_items/Exclusive/Reverse.gd', 'gd_core_py.gd_core_items.Exclusive.Reverse'),
    ('gd_core_items/Exclusive/Robodog.gd', 'gd_core_py.gd_core_items.Exclusive.Robodog'),
    ('gd_core_items/Exclusive/Rope.gd', 'gd_core_py.gd_core_items.Exclusive.Rope'),
    ('gd_core_items/Exclusive/Sandbag.gd', 'gd_core_py.gd_core_items.Exclusive.Sandbag'),
    ('gd_core_items/Exclusive/SapphireEgg.gd', 'gd_core_py.gd_core_items.Exclusive.SapphireEgg'),
    ('gd_core_items/Exclusive/SapphireWhelp.gd', 'gd_core_py.gd_core_items.Exclusive.SapphireWhelp'),
    ('gd_core_items/Exclusive/Scale.gd', 'gd_core_py.gd_core_items.Exclusive.Scale'),
    ('gd_core_items/Exclusive/ScholarBag.gd', 'gd_core_py.gd_core_items.Exclusive.ScholarBag'),
    ('gd_core_items/Exclusive/Scissorswords.gd', 'gd_core_py.gd_core_items.Exclusive.Scissorswords'),
    ('gd_core_items/Exclusive/SealtheDeal.gd', 'gd_core_py.gd_core_items.Exclusive.SealtheDeal'),
    ('gd_core_items/Exclusive/SerpentStaff.gd', 'gd_core_py.gd_core_items.Exclusive.SerpentStaff'),
    ('gd_core_items/Exclusive/SewingCase.gd', 'gd_core_py.gd_core_items.Exclusive.SewingCase'),
    ('gd_core_items/Exclusive/ShamanMask.gd', 'gd_core_py.gd_core_items.Exclusive.ShamanMask'),
    ('gd_core_items/Exclusive/ShellTotem.gd', 'gd_core_py.gd_core_items.Exclusive.ShellTotem'),
    ('gd_core_items/Exclusive/ShepherdsCrook.gd', 'gd_core_py.gd_core_items.Exclusive.ShepherdsCrook'),
    ('gd_core_items/Exclusive/Shielded.gd', 'gd_core_py.gd_core_items.Exclusive.Shielded'),
    ('gd_core_items/Exclusive/ShinyMantle.gd', 'gd_core_py.gd_core_items.Exclusive.ShinyMantle'),
    ('gd_core_items/Exclusive/ShinyShell.gd', 'gd_core_py.gd_core_items.Exclusive.ShinyShell'),
    ('gd_core_items/Exclusive/SkullBadge.gd', 'gd_core_py.gd_core_items.Exclusive.SkullBadge'),
    ('gd_core_items/Exclusive/SliceofBread.gd', 'gd_core_py.gd_core_items.Exclusive.SliceofBread'),
    ('gd_core_items/Exclusive/SliceofToast.gd', 'gd_core_py.gd_core_items.Exclusive.SliceofToast'),
    ('gd_core_items/Exclusive/SlimeTime.gd', 'gd_core_py.gd_core_items.Exclusive.SlimeTime'),
    ('gd_core_items/Exclusive/Sloth.gd', 'gd_core_py.gd_core_items.Exclusive.Sloth'),
    ('gd_core_items/Exclusive/SmellyBarrier.gd', 'gd_core_py.gd_core_items.Exclusive.SmellyBarrier'),
    ('gd_core_items/Exclusive/SmithingForDummies.gd', 'gd_core_py.gd_core_items.Exclusive.SmithingForDummies'),
    ('gd_core_items/Exclusive/Snake.gd', 'gd_core_py.gd_core_items.Exclusive.Snake'),
    ('gd_core_items/Exclusive/SnowStick.gd', 'gd_core_py.gd_core_items.Exclusive.SnowStick'),
    ('gd_core_items/Exclusive/Snowball.gd', 'gd_core_py.gd_core_items.Exclusive.Snowball'),
    ('gd_core_items/Exclusive/Snowcake.gd', 'gd_core_py.gd_core_items.Exclusive.Snowcake'),
    ('gd_core_items/Exclusive/Snowman.gd', 'gd_core_py.gd_core_items.Exclusive.Snowman'),
    ('gd_core_items/Exclusive/Snowmaster.gd', 'gd_core_py.gd_core_items.Exclusive.Snowmaster'),
    ('gd_core_items/Exclusive/Solaris.gd', 'gd_core_py.gd_core_items.Exclusive.Solaris'),
    ('gd_core_items/Exclusive/SpeakwithAnimals.gd', 'gd_core_py.gd_core_items.Exclusive.SpeakwithAnimals'),
    ('gd_core_items/Exclusive/SpellScrollDark.gd', 'gd_core_py.gd_core_items.Exclusive.SpellScrollDark'),
    ('gd_core_items/Exclusive/SpellScrollFrostbolt.gd', 'gd_core_py.gd_core_items.Exclusive.SpellScrollFrostbolt'),
    ('gd_core_items/Exclusive/SpellScrollIce.gd', 'gd_core_py.gd_core_items.Exclusive.SpellScrollIce'),
    ('gd_core_items/Exclusive/SpellScrollLight.gd', 'gd_core_py.gd_core_items.Exclusive.SpellScrollLight'),
    ('gd_core_items/Exclusive/SpellScrollNature.gd', 'gd_core_py.gd_core_items.Exclusive.SpellScrollNature'),
    ('gd_core_items/Exclusive/SpicyBanana.gd', 'gd_core_py.gd_core_items.Exclusive.SpicyBanana'),
    ('gd_core_items/Exclusive/SpikedCollar.gd', 'gd_core_py.gd_core_items.Exclusive.SpikedCollar'),
    ('gd_core_items/Exclusive/SpikedStaff.gd', 'gd_core_py.gd_core_items.Exclusive.SpikedStaff'),
    ('gd_core_items/Exclusive/SpikedWall.gd', 'gd_core_py.gd_core_items.Exclusive.SpikedWall'),
    ('gd_core_items/Exclusive/SpintoWin.gd', 'gd_core_py.gd_core_items.Exclusive.SpintoWin'),
    ('gd_core_items/Exclusive/SpiritBells.gd', 'gd_core_py.gd_core_items.Exclusive.SpiritBells'),
    ('gd_core_items/Exclusive/SpringLoader.gd', 'gd_core_py.gd_core_items.Exclusive.SpringLoader'),
    ('gd_core_items/Exclusive/Squirrel.gd', 'gd_core_py.gd_core_items.Exclusive.Squirrel'),
    ('gd_core_items/Exclusive/SquirrelArcher.gd', 'gd_core_py.gd_core_items.Exclusive.SquirrelArcher'),
    ('gd_core_items/Exclusive/StaffofFire.gd', 'gd_core_py.gd_core_items.Exclusive.StaffofFire'),
    ('gd_core_items/Exclusive/StarofCourage.gd', 'gd_core_py.gd_core_items.Exclusive.StarofCourage'),
    ('gd_core_items/Exclusive/SteelDragon.gd', 'gd_core_py.gd_core_items.Exclusive.SteelDragon'),
    ('gd_core_items/Exclusive/StoneArmor.gd', 'gd_core_py.gd_core_items.Exclusive.StoneArmor'),
    ('gd_core_items/Exclusive/StoneBadge.gd', 'gd_core_py.gd_core_items.Exclusive.StoneBadge'),
    ('gd_core_items/Exclusive/StoneGloves.gd', 'gd_core_py.gd_core_items.Exclusive.StoneGloves'),
    ('gd_core_items/Exclusive/StoneGolem.gd', 'gd_core_py.gd_core_items.Exclusive.StoneGolem'),
    ('gd_core_items/Exclusive/StoneShoes.gd', 'gd_core_py.gd_core_items.Exclusive.StoneShoes'),
    ('gd_core_items/Exclusive/Stoned.gd', 'gd_core_py.gd_core_items.Exclusive.Stoned'),
    ('gd_core_items/Exclusive/StrongDivinePotion.gd', 'gd_core_py.gd_core_items.Exclusive.StrongDivinePotion'),
    ('gd_core_items/Exclusive/VampiricPotion.gd', 'gd_core_py.gd_core_items.Exclusive.VampiricPotion'),
    ('gd_core_items/Exclusive/StrongVampiricPotion.gd', 'gd_core_py.gd_core_items.Exclusive.StrongVampiricPotion'),
    ('gd_core_items/Exclusive/SunArmor.gd', 'gd_core_py.gd_core_items.Exclusive.SunArmor'),
    ('gd_core_items/Exclusive/SunShield.gd', 'gd_core_py.gd_core_items.Exclusive.SunShield'),
    ('gd_core_items/Exclusive/TeslaCoil.gd', 'gd_core_py.gd_core_items.Exclusive.TeslaCoil'),
    ('gd_core_items/Exclusive/ThornElemental.gd', 'gd_core_py.gd_core_items.Exclusive.ThornElemental'),
    ('gd_core_items/Exclusive/ThornShortbow.gd', 'gd_core_py.gd_core_items.Exclusive.ThornShortbow'),
    ('gd_core_items/Exclusive/Thornbloom.gd', 'gd_core_py.gd_core_items.Exclusive.Thornbloom'),
    ('gd_core_items/Exclusive/Thornburst.gd', 'gd_core_py.gd_core_items.Exclusive.Thornburst'),
    ('gd_core_items/Exclusive/ThorsHammer.gd', 'gd_core_py.gd_core_items.Exclusive.ThorsHammer'),
    ('gd_core_items/Exclusive/ThunderDrake.gd', 'gd_core_py.gd_core_items.Exclusive.ThunderDrake'),
    ('gd_core_items/Exclusive/TigerRune.gd', 'gd_core_py.gd_core_items.Exclusive.TigerRune'),
    ('gd_core_items/Exclusive/TimeDilator.gd', 'gd_core_py.gd_core_items.Exclusive.TimeDilator'),
    ('gd_core_items/Exclusive/TimeMelting.gd', 'gd_core_py.gd_core_items.Exclusive.TimeMelting'),
    ('gd_core_items/Exclusive/TimePendant.gd', 'gd_core_py.gd_core_items.Exclusive.TimePendant'),
    ('gd_core_items/Exclusive/ToastGoobert.gd', 'gd_core_py.gd_core_items.Exclusive.ToastGoobert'),
    ('gd_core_items/Exclusive/Toolbox.gd', 'gd_core_py.gd_core_items.Exclusive.Toolbox'),
    ('gd_core_items/Exclusive/Turtle.gd', 'gd_core_py.gd_core_items.Exclusive.Turtle'),
    ('gd_core_items/Exclusive/Twine.gd', 'gd_core_py.gd_core_items.Exclusive.Twine'),
    ('gd_core_items/Exclusive/TwineBadge.gd', 'gd_core_py.gd_core_items.Exclusive.TwineBadge'),
    ('gd_core_items/Exclusive/Ukulele.gd', 'gd_core_py.gd_core_items.Exclusive.Ukulele'),
    ('gd_core_items/Exclusive/Ultima.gd', 'gd_core_py.gd_core_items.Exclusive.Ultima'),
    ('gd_core_items/Exclusive/UnidentifiedSkill.gd', 'gd_core_py.gd_core_items.Exclusive.UnidentifiedSkill'),
    ('gd_core_items/Exclusive/UniquelyUnique.gd', 'gd_core_py.gd_core_items.Exclusive.UniquelyUnique'),
    ('gd_core_items/Exclusive/VampiricCollar.gd', 'gd_core_py.gd_core_items.Exclusive.VampiricCollar'),
    ('gd_core_items/Exclusive/VineweaveBasket.gd', 'gd_core_py.gd_core_items.Exclusive.VineweaveBasket'),
    ('gd_core_items/Exclusive/Wand.gd', 'gd_core_py.gd_core_items.Exclusive.Wand'),
    ('gd_core_items/Exclusive/WandofDissonance.gd', 'gd_core_py.gd_core_items.Exclusive.WandofDissonance'),
    ('gd_core_items/Exclusive/WarScythe.gd', 'gd_core_py.gd_core_items.Exclusive.WarScythe'),
    ('gd_core_items/Exclusive/WaterElemental.gd', 'gd_core_py.gd_core_items.Exclusive.WaterElemental'),
    ('gd_core_items/Exclusive/Whetstone3.gd', 'gd_core_py.gd_core_items.Exclusive.Whetstone3'),
    ('gd_core_items/Exclusive/WingedBoots.gd', 'gd_core_py.gd_core_items.Exclusive.WingedBoots'),
    ('gd_core_items/Exclusive/Wisp.gd', 'gd_core_py.gd_core_items.Exclusive.Wisp'),
    ('gd_core_items/Exclusive/WolfBadge.gd', 'gd_core_py.gd_core_items.Exclusive.WolfBadge'),
    ('gd_core_items/Exclusive/WolfEmblem.gd', 'gd_core_py.gd_core_items.Exclusive.WolfEmblem'),
    ('gd_core_items/Exclusive/Wrench.gd', 'gd_core_py.gd_core_items.Exclusive.Wrench'),
    ('gd_core_items/Exclusive/Chess/ChessPiece.gd', 'gd_core_py.gd_core_items.Exclusive.Chess.ChessPiece'),
    ('gd_core_items/Exclusive/Chess/BlackBishop.gd', 'gd_core_py.gd_core_items.Exclusive.Chess.BlackBishop'),
    ('gd_core_items/Exclusive/Chess/BlackKing.gd', 'gd_core_py.gd_core_items.Exclusive.Chess.BlackKing'),
    ('gd_core_items/Exclusive/Chess/BlackKnight.gd', 'gd_core_py.gd_core_items.Exclusive.Chess.BlackKnight'),
    ('gd_core_items/Exclusive/Chess/BlackPawn.gd', 'gd_core_py.gd_core_items.Exclusive.Chess.BlackPawn'),
    ('gd_core_items/Exclusive/Chess/BlackQueen.gd', 'gd_core_py.gd_core_items.Exclusive.Chess.BlackQueen'),
    ('gd_core_items/Exclusive/Chess/BlackRook.gd', 'gd_core_py.gd_core_items.Exclusive.Chess.BlackRook'),
    ('gd_core_items/Exclusive/Chess/WhiteBishop.gd', 'gd_core_py.gd_core_items.Exclusive.Chess.WhiteBishop'),
    ('gd_core_items/Exclusive/Chess/WhiteKing.gd', 'gd_core_py.gd_core_items.Exclusive.Chess.WhiteKing'),
    ('gd_core_items/Exclusive/Chess/WhiteKnight.gd', 'gd_core_py.gd_core_items.Exclusive.Chess.WhiteKnight'),
    ('gd_core_items/Exclusive/Chess/WhitePawn.gd', 'gd_core_py.gd_core_items.Exclusive.Chess.WhitePawn'),
    ('gd_core_items/Exclusive/Chess/WhiteQueen.gd', 'gd_core_py.gd_core_items.Exclusive.Chess.WhiteQueen'),
    ('gd_core_items/Exclusive/Chess/WhiteRook.gd', 'gd_core_py.gd_core_items.Exclusive.Chess.WhiteRook'),
    ('gd_core_items/Gems/Amethyst.gd', 'gd_core_py.gd_core_items.Gems.Amethyst'),
    ('gd_core_items/Gems/CorruptedCrystal.gd', 'gd_core_py.gd_core_items.Gems.CorruptedCrystal'),
    ('gd_core_items/Gems/Emerald.gd', 'gd_core_py.gd_core_items.Gems.Emerald'),
    ('gd_core_items/Gems/LumpofCoal.gd', 'gd_core_py.gd_core_items.Gems.LumpofCoal'),
    ('gd_core_items/Gems/Ruby.gd', 'gd_core_py.gd_core_items.Gems.Ruby'),
    ('gd_core_items/Gems/Sapphire.gd', 'gd_core_py.gd_core_items.Gems.Sapphire'),
    ('gd_core_items/Gems/Skull.gd', 'gd_core_py.gd_core_items.Gems.Skull'),
    ('gd_core_items/Gems/Topaz.gd', 'gd_core_py.gd_core_items.Gems.Topaz'),
]


def load_core():
    """档一：gd_core/ 树全部模块 + 其行为基类闭包（战斗判定面）。返回失败清单。"""
    failed = []
    try:
        import gd_core_py.gd_core.CoreItem  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/CoreItem.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Item  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Item.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Card  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Card.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.AceofSpades  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/AceofSpades.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.RangerCollar  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/RangerCollar.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.AcornCollar  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/AcornCollar.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Stone  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Stone.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.ArtifactStoneCold  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/ArtifactStoneCold.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.ArtifactStoneHeat  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/ArtifactStoneHeat.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Bag  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Bag.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.BagofStones  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/BagofStones.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Food  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Food.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Banana  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Banana.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.BloodAmulet  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/BloodAmulet.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Goobert  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Goobert.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.BloodGoobert  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/BloodGoobert.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Weapon  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Weapon.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Bloodthorne  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Bloodthorne.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Dagger  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Dagger.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.BloodyDagger  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/BloodyDagger.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Blueberries  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Blueberries.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Bow  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Bow.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Bow  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Bow.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.BowandArrow  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/BowandArrow.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.BoxofRiches  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/BoxofRiches.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Broom  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Broom.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Gems.Gem  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Gems/Gem.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.BurningCoal  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/BurningCoal.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.BurningTorch  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/BurningTorch.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Card  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Card.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Carrot  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Carrot.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.CarrotGoobert  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/CarrotGoobert.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.ClawsofAttack  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/ClawsofAttack.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.CoreBuff  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/CoreBuff.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.CoreCharacter  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/CoreCharacter.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.CoreCombat  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/CoreCombat.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.CoreCombatLog  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/CoreCombatLog.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.CoreConst  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/CoreConst.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.CoreContext  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/CoreContext.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.CoreDamageResult  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/CoreDamageResult.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.CoreDamageSource  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/CoreDamageSource.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.CoreEvent  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/CoreEvent.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.CoreEventBus  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/CoreEventBus.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.CoreGrid  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/CoreGrid.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.CoreHooks  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/CoreHooks.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.CoreItemBook  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/CoreItemBook.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.CoreItemData  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/CoreItemData.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.CoreRng  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/CoreRng.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.CoreTimer  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/CoreTimer.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.CoreUtil  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/CoreUtil.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.CorruptedArmor  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/CorruptedArmor.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.CritwoodStaff  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/CritwoodStaff.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Crossblades  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Crossblades.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Crown  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Crown.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.CursedDagger  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/CursedDagger.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.CursedHairComb  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/CursedHairComb.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.CustomerCard  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/CustomerCard.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Dagger  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Dagger.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.DancingDragon  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/DancingDragon.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.DarkestLotus  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/DarkestLotus.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Darksaber  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Darksaber.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.DeathScythe  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/DeathScythe.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.DeckofCards  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/DeckofCards.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Potion  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Potion.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.DemonicFlask  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/DemonicFlask.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.DjinnLamp  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/DjinnLamp.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.DragonEgg  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/DragonEgg.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Pan  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Pan.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Eggscalibur  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Eggscalibur.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.EvilCap  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/EvilCap.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.FalconBlade  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/FalconBlade.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.FancyFencingRapier  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/FancyFencingRapier.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Fanfare  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Fanfare.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Bag  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Bag.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.FannyPack  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/FannyPack.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Flute  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Flute.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.FlyAgaric  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/FlyAgaric.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Food  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Food.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Garlic  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Garlic.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.GingerbreadMan  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/GingerbreadMan.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.GlovesofHaste  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/GlovesofHaste.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Goobert  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Goobert.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Greatsword  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Greatsword.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Hammer  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Hammer.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.HealingHerbs  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/HealingHerbs.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.HealthPotion  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/HealthPotion.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.HeartContainer  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/HeartContainer.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.HeartofDarkness  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/HeartofDarkness.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.HeroLongsword  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/HeroLongsword.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.HeroSword  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/HeroSword.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.HeroicPotion  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/HeroicPotion.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.HoloFireLizard  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/HoloFireLizard.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.HolyArmor  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/HolyArmor.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.HolySpear  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/HolySpear.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.HungryBlade  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/HungryBlade.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Item  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Item.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Jynxtorquilla  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Jynxtorquilla.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.LeatherArmor  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/LeatherArmor.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.LeatherBoots  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/LeatherBoots.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.LeatherHelm  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/LeatherHelm.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.LightGoobert  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/LightGoobert.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Lightsaber  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Lightsaber.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.LuckyBow  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/LuckyBow.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.LuckyClover  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/LuckyClover.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Piggybank  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Piggybank.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.LuckyPiggy  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/LuckyPiggy.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.MagicStaff  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/MagicStaff.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.MagicTorch  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/MagicTorch.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.ManaOrb  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/ManaOrb.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.ManaPotion  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/ManaPotion.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Manathirst  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Manathirst.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Shield  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Shield.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.MoonShield  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/MoonShield.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.MrStruggles  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/MrStruggles.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Pan  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Pan.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Pandamonium  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Pandamonium.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.PestilenceFlask  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/PestilenceFlask.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.PiercingArrow  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/PiercingArrow.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Piggybank  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Piggybank.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Pineapple  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Pineapple.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.PlatinCustomerCard  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/PlatinCustomerCard.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.PocketSand  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/PocketSand.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.PoisonBow  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/PoisonBow.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.PoisonDagger  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/PoisonDagger.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.PoisonGoobert  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/PoisonGoobert.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.PoisonIvy  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/PoisonIvy.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Potion  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Potion.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.PotionBelt  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/PotionBelt.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Present  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Present.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.ProtectivePurse  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/ProtectivePurse.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Pumpkin  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Pumpkin.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.RainbowGoobert  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/RainbowGoobert.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.RainbowGoobertRanger  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/RainbowGoobertRanger.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.RangerBag  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/RangerBag.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.RangerCollar  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/RangerCollar.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.RibSawBlade  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/RibSawBlade.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.RubyChonk  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/RubyChonk.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.DragonEgg  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/DragonEgg.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.RubyEgg  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/RubyEgg.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.RubyWhelp  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/RubyWhelp.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Shield  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Shield.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.ShieldofValor  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/ShieldofValor.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Shovel  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Shovel.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Spear  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Spear.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.SpectralDagger  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/SpectralDagger.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.SpikedShield  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/SpikedShield.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.StaffofUnhealing  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/StaffofUnhealing.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.StaminaSack  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/StaminaSack.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.SteelGoobert  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/SteelGoobert.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Stone  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Stone.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.LeatherHelm  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/LeatherHelm.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.StoneHelm  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/StoneHelm.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.StoneSkinPotion  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/StoneSkinPotion.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.StorageCoffin  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/StorageCoffin.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.StrongDemonicFlask  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/StrongDemonicFlask.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.HealthPotion  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/HealthPotion.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.StrongHealthPotion  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/StrongHealthPotion.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.PestilenceFlask  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/PestilenceFlask.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.StrongPestilenceFlask  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/StrongPestilenceFlask.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.StoneSkinPotion  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/StoneSkinPotion.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.StrongStoneSkinPotion  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/StrongStoneSkinPotion.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.TheFool  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/TheFool.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.TheLovers  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/TheLovers.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.ThornBow  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/ThornBow.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.ThornWhip  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/ThornWhip.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Torch  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Torch.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.VampiricArmor  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/VampiricArmor.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.VampiricGloves  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/VampiricGloves.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.VampiricScythe  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/VampiricScythe.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.VillainSword  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/VillainSword.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.WalrusTusk  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/WalrusTusk.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Weapon  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Weapon.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Whetstone  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Whetstone.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.White_EyesBlueDragon  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/White-EyesBlueDragon.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.Wolpertinger  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/Wolpertinger.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.WoodenBuckler  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/WoodenBuckler.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.WoodenSword  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/WoodenSword.gd', repr(exc)))
    try:
        import gd_core_py.gd_core.YggdrasilLeaf  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/YggdrasilLeaf.gd', repr(exc)))
    return failed


def load_for(scripts):
    """档二：按阵容脚本路径补导 items 祖先闭包。幂等；须先 load_core()。"""
    failed = []
    want = set()
    for s in scripts or ():
        stem = str(s).rsplit('/', 1)[-1]
        if stem.endswith('.gd'):
            stem = stem[:-3]
        rel = _ITEM_STEM.get(stem)
        if rel is None:
            continue
        stack = [rel]
        while stack:
            r0 = stack.pop()
            if r0 not in want:
                want.add(r0)
                stack.extend(_ITEM_PARENTS.get(r0, ()))
    # 拓扑序逐项导入（与原先静态 if 链同序，仅保留「按需」约束）
    for rel, mod in _ITEM_MODULES:
        if rel not in want:
            continue
        try:
            __import__(mod)
        except Exception as exc:  # noqa: BLE001
            failed.append((rel, repr(exc)))
    return failed


# ── M2-1 空钩子剥离清单（生成器发射；勿手改）──
STRIPPED_HOOKS = ['activateBuffCounter', 'addMetric', 'applyImpulse', 'damageAnimation', 'onClassChanged', 'onHealthChangedUI', 'onItemRotated', 'onItemTypeChanged', 'onMaxStaminaChangedUI', 'playActivateAnimation', 'playActivationAnimation', 'playActivationSound', 'playAffectedPlacedAnimation', 'playAttackAnimation', 'playBattleRageAnimation', 'playCharacterSound', 'playDropSound', 'playFatigueSound', 'playInvulnerableAnimation', 'playOutOfStaminaAnimation', 'playWinLoseAnimation', 'previewCanAffect', 'previewCellCollision', 'previewCells', 'queueTooltipUpdate', 'resetZ', 'sendCharge', 'showCooldown', 'showCooldownSmooth', 'snapshotCharacterStat', 'snapshotDamageDealt', 'snapshotGlobalStat', 'snapshotItemState', 'snapshotItemTooltipStat', 'snapshotMetric', 'snapshotStack', 'spawnBuffLabel', 'spawnBuffLabel_item', 'spawnLabel', 'spawnLabelOnItem', 'spawnMissLabel', 'spawnNumberLabel', 'spawnProtectedLabel', 'spawnReflectLabel', 'spawnResistedLabel', 'updateDamageMeter']
