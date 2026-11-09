# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py
"""按 extends 依赖拓扑序导入全部模块（基类先注册，与 Godot 加载次序同义）。"""

from . import _registry  # noqa: F401
from . import _rt  # noqa: F401


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
        for rel in _ITEM_ORDER:
            if rel.rsplit('/', 1)[-1][:-3] == stem:
                stack = [rel]
                while stack:
                    r0 = stack.pop()
                    if r0 not in want:
                        want.add(r0)
                        stack.extend(_ITEM_PARENTS.get(r0, ()))
                break
    if 'gd_core_items/Item.gd' in want:
        try:
            import gd_core_py.gd_core_items.Item  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Item.gd', repr(exc)))
    if 'gd_core_items/Card.gd' in want:
        try:
            import gd_core_py.gd_core_items.Card  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Card.gd', repr(exc)))
    if 'gd_core_items/RangerCollar.gd' in want:
        try:
            import gd_core_py.gd_core_items.RangerCollar  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/RangerCollar.gd', repr(exc)))
    if 'gd_core_items/Stone.gd' in want:
        try:
            import gd_core_py.gd_core_items.Stone  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Stone.gd', repr(exc)))
    if 'gd_core_items/Food.gd' in want:
        try:
            import gd_core_py.gd_core_items.Food  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Food.gd', repr(exc)))
    if 'gd_core_items/Goobert.gd' in want:
        try:
            import gd_core_py.gd_core_items.Goobert  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Goobert.gd', repr(exc)))
    if 'gd_core_items/Weapon.gd' in want:
        try:
            import gd_core_py.gd_core_items.Weapon  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Weapon.gd', repr(exc)))
    if 'gd_core_items/Dagger.gd' in want:
        try:
            import gd_core_py.gd_core_items.Dagger  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Dagger.gd', repr(exc)))
    if 'gd_core_items/Bow.gd' in want:
        try:
            import gd_core_py.gd_core_items.Bow  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Bow.gd', repr(exc)))
    if 'gd_core_items/Gems/Gem.gd' in want:
        try:
            import gd_core_py.gd_core_items.Gems.Gem  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Gems/Gem.gd', repr(exc)))
    if 'gd_core_items/Potion.gd' in want:
        try:
            import gd_core_py.gd_core_items.Potion  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Potion.gd', repr(exc)))
    if 'gd_core_items/Pan.gd' in want:
        try:
            import gd_core_py.gd_core_items.Pan  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Pan.gd', repr(exc)))
    if 'gd_core_items/Bag.gd' in want:
        try:
            import gd_core_py.gd_core_items.Bag  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Bag.gd', repr(exc)))
    if 'gd_core_items/Piggybank.gd' in want:
        try:
            import gd_core_py.gd_core_items.Piggybank  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Piggybank.gd', repr(exc)))
    if 'gd_core_items/Shield.gd' in want:
        try:
            import gd_core_py.gd_core_items.Shield  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Shield.gd', repr(exc)))
    if 'gd_core_items/DragonEgg.gd' in want:
        try:
            import gd_core_py.gd_core_items.DragonEgg  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/DragonEgg.gd', repr(exc)))
    if 'gd_core_items/LeatherHelm.gd' in want:
        try:
            import gd_core_py.gd_core_items.LeatherHelm  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/LeatherHelm.gd', repr(exc)))
    if 'gd_core_items/HealthPotion.gd' in want:
        try:
            import gd_core_py.gd_core_items.HealthPotion  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/HealthPotion.gd', repr(exc)))
    if 'gd_core_items/PestilenceFlask.gd' in want:
        try:
            import gd_core_py.gd_core_items.PestilenceFlask  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/PestilenceFlask.gd', repr(exc)))
    if 'gd_core_items/StoneSkinPotion.gd' in want:
        try:
            import gd_core_py.gd_core_items.StoneSkinPotion  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/StoneSkinPotion.gd', repr(exc)))
    if 'gd_core_items/AceofSpades.gd' in want:
        try:
            import gd_core_py.gd_core_items.AceofSpades  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/AceofSpades.gd', repr(exc)))
    if 'gd_core_items/AcornCollar.gd' in want:
        try:
            import gd_core_py.gd_core_items.AcornCollar  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/AcornCollar.gd', repr(exc)))
    if 'gd_core_items/ArtifactStoneCold.gd' in want:
        try:
            import gd_core_py.gd_core_items.ArtifactStoneCold  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/ArtifactStoneCold.gd', repr(exc)))
    if 'gd_core_items/ArtifactStoneHeat.gd' in want:
        try:
            import gd_core_py.gd_core_items.ArtifactStoneHeat  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/ArtifactStoneHeat.gd', repr(exc)))
    if 'gd_core_items/BagofStones.gd' in want:
        try:
            import gd_core_py.gd_core_items.BagofStones  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/BagofStones.gd', repr(exc)))
    if 'gd_core_items/Banana.gd' in want:
        try:
            import gd_core_py.gd_core_items.Banana  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Banana.gd', repr(exc)))
    if 'gd_core_items/BloodAmulet.gd' in want:
        try:
            import gd_core_py.gd_core_items.BloodAmulet  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/BloodAmulet.gd', repr(exc)))
    if 'gd_core_items/BloodGoobert.gd' in want:
        try:
            import gd_core_py.gd_core_items.BloodGoobert  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/BloodGoobert.gd', repr(exc)))
    if 'gd_core_items/Bloodthorne.gd' in want:
        try:
            import gd_core_py.gd_core_items.Bloodthorne  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Bloodthorne.gd', repr(exc)))
    if 'gd_core_items/BloodyDagger.gd' in want:
        try:
            import gd_core_py.gd_core_items.BloodyDagger  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/BloodyDagger.gd', repr(exc)))
    if 'gd_core_items/Blueberries.gd' in want:
        try:
            import gd_core_py.gd_core_items.Blueberries  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Blueberries.gd', repr(exc)))
    if 'gd_core_items/BowandArrow.gd' in want:
        try:
            import gd_core_py.gd_core_items.BowandArrow  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/BowandArrow.gd', repr(exc)))
    if 'gd_core_items/BoxofRiches.gd' in want:
        try:
            import gd_core_py.gd_core_items.BoxofRiches  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/BoxofRiches.gd', repr(exc)))
    if 'gd_core_items/Broom.gd' in want:
        try:
            import gd_core_py.gd_core_items.Broom  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Broom.gd', repr(exc)))
    if 'gd_core_items/BurningCoal.gd' in want:
        try:
            import gd_core_py.gd_core_items.BurningCoal  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/BurningCoal.gd', repr(exc)))
    if 'gd_core_items/BurningTorch.gd' in want:
        try:
            import gd_core_py.gd_core_items.BurningTorch  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/BurningTorch.gd', repr(exc)))
    if 'gd_core_items/Carrot.gd' in want:
        try:
            import gd_core_py.gd_core_items.Carrot  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Carrot.gd', repr(exc)))
    if 'gd_core_items/CarrotGoobert.gd' in want:
        try:
            import gd_core_py.gd_core_items.CarrotGoobert  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/CarrotGoobert.gd', repr(exc)))
    if 'gd_core_items/ClawsofAttack.gd' in want:
        try:
            import gd_core_py.gd_core_items.ClawsofAttack  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/ClawsofAttack.gd', repr(exc)))
    if 'gd_core_items/Coins.gd' in want:
        try:
            import gd_core_py.gd_core_items.Coins  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Coins.gd', repr(exc)))
    if 'gd_core_items/CorruptedArmor.gd' in want:
        try:
            import gd_core_py.gd_core_items.CorruptedArmor  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/CorruptedArmor.gd', repr(exc)))
    if 'gd_core_items/CritwoodStaff.gd' in want:
        try:
            import gd_core_py.gd_core_items.CritwoodStaff  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/CritwoodStaff.gd', repr(exc)))
    if 'gd_core_items/Crossblades.gd' in want:
        try:
            import gd_core_py.gd_core_items.Crossblades  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Crossblades.gd', repr(exc)))
    if 'gd_core_items/Crown.gd' in want:
        try:
            import gd_core_py.gd_core_items.Crown  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Crown.gd', repr(exc)))
    if 'gd_core_items/CursedDagger.gd' in want:
        try:
            import gd_core_py.gd_core_items.CursedDagger  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/CursedDagger.gd', repr(exc)))
    if 'gd_core_items/CursedHairComb.gd' in want:
        try:
            import gd_core_py.gd_core_items.CursedHairComb  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/CursedHairComb.gd', repr(exc)))
    if 'gd_core_items/CustomerCard.gd' in want:
        try:
            import gd_core_py.gd_core_items.CustomerCard  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/CustomerCard.gd', repr(exc)))
    if 'gd_core_items/DancingDragon.gd' in want:
        try:
            import gd_core_py.gd_core_items.DancingDragon  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/DancingDragon.gd', repr(exc)))
    if 'gd_core_items/DarkestLotus.gd' in want:
        try:
            import gd_core_py.gd_core_items.DarkestLotus  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/DarkestLotus.gd', repr(exc)))
    if 'gd_core_items/Darksaber.gd' in want:
        try:
            import gd_core_py.gd_core_items.Darksaber  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Darksaber.gd', repr(exc)))
    if 'gd_core_items/DeathScythe.gd' in want:
        try:
            import gd_core_py.gd_core_items.DeathScythe  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/DeathScythe.gd', repr(exc)))
    if 'gd_core_items/DeckofCards.gd' in want:
        try:
            import gd_core_py.gd_core_items.DeckofCards  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/DeckofCards.gd', repr(exc)))
    if 'gd_core_items/DemonicFlask.gd' in want:
        try:
            import gd_core_py.gd_core_items.DemonicFlask  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/DemonicFlask.gd', repr(exc)))
    if 'gd_core_items/DjinnLamp.gd' in want:
        try:
            import gd_core_py.gd_core_items.DjinnLamp  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/DjinnLamp.gd', repr(exc)))
    if 'gd_core_items/Eggscalibur.gd' in want:
        try:
            import gd_core_py.gd_core_items.Eggscalibur  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Eggscalibur.gd', repr(exc)))
    if 'gd_core_items/EvilCap.gd' in want:
        try:
            import gd_core_py.gd_core_items.EvilCap  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/EvilCap.gd', repr(exc)))
    if 'gd_core_items/FalconBlade.gd' in want:
        try:
            import gd_core_py.gd_core_items.FalconBlade  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/FalconBlade.gd', repr(exc)))
    if 'gd_core_items/FancyFencingRapier.gd' in want:
        try:
            import gd_core_py.gd_core_items.FancyFencingRapier  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/FancyFencingRapier.gd', repr(exc)))
    if 'gd_core_items/Fanfare.gd' in want:
        try:
            import gd_core_py.gd_core_items.Fanfare  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Fanfare.gd', repr(exc)))
    if 'gd_core_items/FannyPack.gd' in want:
        try:
            import gd_core_py.gd_core_items.FannyPack  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/FannyPack.gd', repr(exc)))
    if 'gd_core_items/Flute.gd' in want:
        try:
            import gd_core_py.gd_core_items.Flute  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Flute.gd', repr(exc)))
    if 'gd_core_items/FlyAgaric.gd' in want:
        try:
            import gd_core_py.gd_core_items.FlyAgaric  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/FlyAgaric.gd', repr(exc)))
    if 'gd_core_items/Garlic.gd' in want:
        try:
            import gd_core_py.gd_core_items.Garlic  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Garlic.gd', repr(exc)))
    if 'gd_core_items/GingerbreadMan.gd' in want:
        try:
            import gd_core_py.gd_core_items.GingerbreadMan  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/GingerbreadMan.gd', repr(exc)))
    if 'gd_core_items/GlovesofHaste.gd' in want:
        try:
            import gd_core_py.gd_core_items.GlovesofHaste  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/GlovesofHaste.gd', repr(exc)))
    if 'gd_core_items/Greatsword.gd' in want:
        try:
            import gd_core_py.gd_core_items.Greatsword  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Greatsword.gd', repr(exc)))
    if 'gd_core_items/Hammer.gd' in want:
        try:
            import gd_core_py.gd_core_items.Hammer  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Hammer.gd', repr(exc)))
    if 'gd_core_items/HealingHerbs.gd' in want:
        try:
            import gd_core_py.gd_core_items.HealingHerbs  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/HealingHerbs.gd', repr(exc)))
    if 'gd_core_items/HeartContainer.gd' in want:
        try:
            import gd_core_py.gd_core_items.HeartContainer  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/HeartContainer.gd', repr(exc)))
    if 'gd_core_items/HeartofDarkness.gd' in want:
        try:
            import gd_core_py.gd_core_items.HeartofDarkness  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/HeartofDarkness.gd', repr(exc)))
    if 'gd_core_items/HeroLongsword.gd' in want:
        try:
            import gd_core_py.gd_core_items.HeroLongsword  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/HeroLongsword.gd', repr(exc)))
    if 'gd_core_items/HeroSword.gd' in want:
        try:
            import gd_core_py.gd_core_items.HeroSword  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/HeroSword.gd', repr(exc)))
    if 'gd_core_items/HeroicPotion.gd' in want:
        try:
            import gd_core_py.gd_core_items.HeroicPotion  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/HeroicPotion.gd', repr(exc)))
    if 'gd_core_items/HoloFireLizard.gd' in want:
        try:
            import gd_core_py.gd_core_items.HoloFireLizard  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/HoloFireLizard.gd', repr(exc)))
    if 'gd_core_items/HolyArmor.gd' in want:
        try:
            import gd_core_py.gd_core_items.HolyArmor  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/HolyArmor.gd', repr(exc)))
    if 'gd_core_items/HolySpear.gd' in want:
        try:
            import gd_core_py.gd_core_items.HolySpear  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/HolySpear.gd', repr(exc)))
    if 'gd_core_items/HungryBlade.gd' in want:
        try:
            import gd_core_py.gd_core_items.HungryBlade  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/HungryBlade.gd', repr(exc)))
    if 'gd_core_items/Jynxtorquilla.gd' in want:
        try:
            import gd_core_py.gd_core_items.Jynxtorquilla  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Jynxtorquilla.gd', repr(exc)))
    if 'gd_core_items/LeatherArmor.gd' in want:
        try:
            import gd_core_py.gd_core_items.LeatherArmor  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/LeatherArmor.gd', repr(exc)))
    if 'gd_core_items/LeatherBoots.gd' in want:
        try:
            import gd_core_py.gd_core_items.LeatherBoots  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/LeatherBoots.gd', repr(exc)))
    if 'gd_core_items/LightGoobert.gd' in want:
        try:
            import gd_core_py.gd_core_items.LightGoobert  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/LightGoobert.gd', repr(exc)))
    if 'gd_core_items/Lightsaber.gd' in want:
        try:
            import gd_core_py.gd_core_items.Lightsaber  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Lightsaber.gd', repr(exc)))
    if 'gd_core_items/LuckyBow.gd' in want:
        try:
            import gd_core_py.gd_core_items.LuckyBow  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/LuckyBow.gd', repr(exc)))
    if 'gd_core_items/LuckyClover.gd' in want:
        try:
            import gd_core_py.gd_core_items.LuckyClover  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/LuckyClover.gd', repr(exc)))
    if 'gd_core_items/LuckyPiggy.gd' in want:
        try:
            import gd_core_py.gd_core_items.LuckyPiggy  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/LuckyPiggy.gd', repr(exc)))
    if 'gd_core_items/MagicStaff.gd' in want:
        try:
            import gd_core_py.gd_core_items.MagicStaff  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/MagicStaff.gd', repr(exc)))
    if 'gd_core_items/MagicTorch.gd' in want:
        try:
            import gd_core_py.gd_core_items.MagicTorch  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/MagicTorch.gd', repr(exc)))
    if 'gd_core_items/ManaOrb.gd' in want:
        try:
            import gd_core_py.gd_core_items.ManaOrb  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/ManaOrb.gd', repr(exc)))
    if 'gd_core_items/ManaPotion.gd' in want:
        try:
            import gd_core_py.gd_core_items.ManaPotion  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/ManaPotion.gd', repr(exc)))
    if 'gd_core_items/Manathirst.gd' in want:
        try:
            import gd_core_py.gd_core_items.Manathirst  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Manathirst.gd', repr(exc)))
    if 'gd_core_items/MoonShield.gd' in want:
        try:
            import gd_core_py.gd_core_items.MoonShield  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/MoonShield.gd', repr(exc)))
    if 'gd_core_items/MrStruggles.gd' in want:
        try:
            import gd_core_py.gd_core_items.MrStruggles  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/MrStruggles.gd', repr(exc)))
    if 'gd_core_items/Pandamonium.gd' in want:
        try:
            import gd_core_py.gd_core_items.Pandamonium  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Pandamonium.gd', repr(exc)))
    if 'gd_core_items/PiercingArrow.gd' in want:
        try:
            import gd_core_py.gd_core_items.PiercingArrow  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/PiercingArrow.gd', repr(exc)))
    if 'gd_core_items/Pineapple.gd' in want:
        try:
            import gd_core_py.gd_core_items.Pineapple  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Pineapple.gd', repr(exc)))
    if 'gd_core_items/PlatinCustomerCard.gd' in want:
        try:
            import gd_core_py.gd_core_items.PlatinCustomerCard  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/PlatinCustomerCard.gd', repr(exc)))
    if 'gd_core_items/PocketSand.gd' in want:
        try:
            import gd_core_py.gd_core_items.PocketSand  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/PocketSand.gd', repr(exc)))
    if 'gd_core_items/PoisonBow.gd' in want:
        try:
            import gd_core_py.gd_core_items.PoisonBow  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/PoisonBow.gd', repr(exc)))
    if 'gd_core_items/PoisonDagger.gd' in want:
        try:
            import gd_core_py.gd_core_items.PoisonDagger  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/PoisonDagger.gd', repr(exc)))
    if 'gd_core_items/PoisonGoobert.gd' in want:
        try:
            import gd_core_py.gd_core_items.PoisonGoobert  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/PoisonGoobert.gd', repr(exc)))
    if 'gd_core_items/PoisonIvy.gd' in want:
        try:
            import gd_core_py.gd_core_items.PoisonIvy  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/PoisonIvy.gd', repr(exc)))
    if 'gd_core_items/PotionBelt.gd' in want:
        try:
            import gd_core_py.gd_core_items.PotionBelt  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/PotionBelt.gd', repr(exc)))
    if 'gd_core_items/Present.gd' in want:
        try:
            import gd_core_py.gd_core_items.Present  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Present.gd', repr(exc)))
    if 'gd_core_items/ProtectivePurse.gd' in want:
        try:
            import gd_core_py.gd_core_items.ProtectivePurse  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/ProtectivePurse.gd', repr(exc)))
    if 'gd_core_items/Pumpkin.gd' in want:
        try:
            import gd_core_py.gd_core_items.Pumpkin  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Pumpkin.gd', repr(exc)))
    if 'gd_core_items/RainbowGoobert.gd' in want:
        try:
            import gd_core_py.gd_core_items.RainbowGoobert  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/RainbowGoobert.gd', repr(exc)))
    if 'gd_core_items/RainbowGoobertRanger.gd' in want:
        try:
            import gd_core_py.gd_core_items.RainbowGoobertRanger  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/RainbowGoobertRanger.gd', repr(exc)))
    if 'gd_core_items/RangerBag.gd' in want:
        try:
            import gd_core_py.gd_core_items.RangerBag  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/RangerBag.gd', repr(exc)))
    if 'gd_core_items/RibSawBlade.gd' in want:
        try:
            import gd_core_py.gd_core_items.RibSawBlade  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/RibSawBlade.gd', repr(exc)))
    if 'gd_core_items/RubyChonk.gd' in want:
        try:
            import gd_core_py.gd_core_items.RubyChonk  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/RubyChonk.gd', repr(exc)))
    if 'gd_core_items/RubyEgg.gd' in want:
        try:
            import gd_core_py.gd_core_items.RubyEgg  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/RubyEgg.gd', repr(exc)))
    if 'gd_core_items/RubyWhelp.gd' in want:
        try:
            import gd_core_py.gd_core_items.RubyWhelp  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/RubyWhelp.gd', repr(exc)))
    if 'gd_core_items/ShieldofValor.gd' in want:
        try:
            import gd_core_py.gd_core_items.ShieldofValor  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/ShieldofValor.gd', repr(exc)))
    if 'gd_core_items/Shovel.gd' in want:
        try:
            import gd_core_py.gd_core_items.Shovel  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Shovel.gd', repr(exc)))
    if 'gd_core_items/Spear.gd' in want:
        try:
            import gd_core_py.gd_core_items.Spear  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Spear.gd', repr(exc)))
    if 'gd_core_items/SpectralDagger.gd' in want:
        try:
            import gd_core_py.gd_core_items.SpectralDagger  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/SpectralDagger.gd', repr(exc)))
    if 'gd_core_items/SpikedShield.gd' in want:
        try:
            import gd_core_py.gd_core_items.SpikedShield  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/SpikedShield.gd', repr(exc)))
    if 'gd_core_items/StaffofUnhealing.gd' in want:
        try:
            import gd_core_py.gd_core_items.StaffofUnhealing  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/StaffofUnhealing.gd', repr(exc)))
    if 'gd_core_items/StaminaSack.gd' in want:
        try:
            import gd_core_py.gd_core_items.StaminaSack  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/StaminaSack.gd', repr(exc)))
    if 'gd_core_items/SteelGoobert.gd' in want:
        try:
            import gd_core_py.gd_core_items.SteelGoobert  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/SteelGoobert.gd', repr(exc)))
    if 'gd_core_items/StoneHelm.gd' in want:
        try:
            import gd_core_py.gd_core_items.StoneHelm  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/StoneHelm.gd', repr(exc)))
    if 'gd_core_items/StorageCoffin.gd' in want:
        try:
            import gd_core_py.gd_core_items.StorageCoffin  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/StorageCoffin.gd', repr(exc)))
    if 'gd_core_items/StrongDemonicFlask.gd' in want:
        try:
            import gd_core_py.gd_core_items.StrongDemonicFlask  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/StrongDemonicFlask.gd', repr(exc)))
    if 'gd_core_items/StrongHealthPotion.gd' in want:
        try:
            import gd_core_py.gd_core_items.StrongHealthPotion  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/StrongHealthPotion.gd', repr(exc)))
    if 'gd_core_items/StrongPestilenceFlask.gd' in want:
        try:
            import gd_core_py.gd_core_items.StrongPestilenceFlask  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/StrongPestilenceFlask.gd', repr(exc)))
    if 'gd_core_items/StrongStoneSkinPotion.gd' in want:
        try:
            import gd_core_py.gd_core_items.StrongStoneSkinPotion  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/StrongStoneSkinPotion.gd', repr(exc)))
    if 'gd_core_items/TheFool.gd' in want:
        try:
            import gd_core_py.gd_core_items.TheFool  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/TheFool.gd', repr(exc)))
    if 'gd_core_items/TheLovers.gd' in want:
        try:
            import gd_core_py.gd_core_items.TheLovers  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/TheLovers.gd', repr(exc)))
    if 'gd_core_items/ThornBow.gd' in want:
        try:
            import gd_core_py.gd_core_items.ThornBow  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/ThornBow.gd', repr(exc)))
    if 'gd_core_items/ThornWhip.gd' in want:
        try:
            import gd_core_py.gd_core_items.ThornWhip  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/ThornWhip.gd', repr(exc)))
    if 'gd_core_items/Torch.gd' in want:
        try:
            import gd_core_py.gd_core_items.Torch  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Torch.gd', repr(exc)))
    if 'gd_core_items/VampiricArmor.gd' in want:
        try:
            import gd_core_py.gd_core_items.VampiricArmor  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/VampiricArmor.gd', repr(exc)))
    if 'gd_core_items/VampiricGloves.gd' in want:
        try:
            import gd_core_py.gd_core_items.VampiricGloves  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/VampiricGloves.gd', repr(exc)))
    if 'gd_core_items/VampiricScythe.gd' in want:
        try:
            import gd_core_py.gd_core_items.VampiricScythe  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/VampiricScythe.gd', repr(exc)))
    if 'gd_core_items/VillainSword.gd' in want:
        try:
            import gd_core_py.gd_core_items.VillainSword  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/VillainSword.gd', repr(exc)))
    if 'gd_core_items/WalrusTusk.gd' in want:
        try:
            import gd_core_py.gd_core_items.WalrusTusk  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/WalrusTusk.gd', repr(exc)))
    if 'gd_core_items/Whetstone.gd' in want:
        try:
            import gd_core_py.gd_core_items.Whetstone  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Whetstone.gd', repr(exc)))
    if 'gd_core_items/White-EyesBlueDragon.gd' in want:
        try:
            import gd_core_py.gd_core_items.White_EyesBlueDragon  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/White-EyesBlueDragon.gd', repr(exc)))
    if 'gd_core_items/Wolpertinger.gd' in want:
        try:
            import gd_core_py.gd_core_items.Wolpertinger  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Wolpertinger.gd', repr(exc)))
    if 'gd_core_items/WoodenBuckler.gd' in want:
        try:
            import gd_core_py.gd_core_items.WoodenBuckler  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/WoodenBuckler.gd', repr(exc)))
    if 'gd_core_items/WoodenSword.gd' in want:
        try:
            import gd_core_py.gd_core_items.WoodenSword  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/WoodenSword.gd', repr(exc)))
    if 'gd_core_items/YggdrasilLeaf.gd' in want:
        try:
            import gd_core_py.gd_core_items.YggdrasilLeaf  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/YggdrasilLeaf.gd', repr(exc)))
    if 'gd_core_items/Exclusive/AcornAce.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.AcornAce  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/AcornAce.gd', repr(exc)))
    if 'gd_core_items/Exclusive/AmethystEgg.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.AmethystEgg  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/AmethystEgg.gd', repr(exc)))
    if 'gd_core_items/Exclusive/AmethystWhelp.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.AmethystWhelp  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/AmethystWhelp.gd', repr(exc)))
    if 'gd_core_items/Exclusive/AmuletUnidentified.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.AmuletUnidentified  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/AmuletUnidentified.gd', repr(exc)))
    if 'gd_core_items/Exclusive/AmuletofAgility.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.AmuletofAgility  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/AmuletofAgility.gd', repr(exc)))
    if 'gd_core_items/Exclusive/AmuletofAlchemy.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.AmuletofAlchemy  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/AmuletofAlchemy.gd', repr(exc)))
    if 'gd_core_items/Exclusive/AmuletofDarkness.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.AmuletofDarkness  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/AmuletofDarkness.gd', repr(exc)))
    if 'gd_core_items/Exclusive/AmuletofFeasting.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.AmuletofFeasting  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/AmuletofFeasting.gd', repr(exc)))
    if 'gd_core_items/Exclusive/AmuletofFortune.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.AmuletofFortune  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/AmuletofFortune.gd', repr(exc)))
    if 'gd_core_items/Exclusive/AmuletofLife.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.AmuletofLife  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/AmuletofLife.gd', repr(exc)))
    if 'gd_core_items/Exclusive/AmuletofLight.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.AmuletofLight  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/AmuletofLight.gd', repr(exc)))
    if 'gd_core_items/Exclusive/AmuletofSteel.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.AmuletofSteel  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/AmuletofSteel.gd', repr(exc)))
    if 'gd_core_items/Exclusive/AmuletoftheWild.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.AmuletoftheWild  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/AmuletoftheWild.gd', repr(exc)))
    if 'gd_core_items/Exclusive/AngelCrystal.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.AngelCrystal  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/AngelCrystal.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Anvil.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Anvil  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Anvil.gd', repr(exc)))
    if 'gd_core_items/Exclusive/ArcaneBoots.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.ArcaneBoots  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/ArcaneBoots.gd', repr(exc)))
    if 'gd_core_items/Exclusive/ArcaneIntellect.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.ArcaneIntellect  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/ArcaneIntellect.gd', repr(exc)))
    if 'gd_core_items/Exclusive/CouragePuppy.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.CouragePuppy  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/CouragePuppy.gd', repr(exc)))
    if 'gd_core_items/Exclusive/ArmoredCouragePuppy.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.ArmoredCouragePuppy  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/ArmoredCouragePuppy.gd', repr(exc)))
    if 'gd_core_items/Exclusive/PowerPuppy.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.PowerPuppy  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/PowerPuppy.gd', repr(exc)))
    if 'gd_core_items/Exclusive/ArmoredPowerPuppy.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.ArmoredPowerPuppy  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/ArmoredPowerPuppy.gd', repr(exc)))
    if 'gd_core_items/Exclusive/WisdomPuppy.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.WisdomPuppy  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/WisdomPuppy.gd', repr(exc)))
    if 'gd_core_items/Exclusive/ArmoredWisdomPuppy.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.ArmoredWisdomPuppy  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/ArmoredWisdomPuppy.gd', repr(exc)))
    if 'gd_core_items/Exclusive/ArtifactStoneDeath.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.ArtifactStoneDeath  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/ArtifactStoneDeath.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Automanaton.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Automanaton  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Automanaton.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Axe.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Axe  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Axe.gd', repr(exc)))
    if 'gd_core_items/Exclusive/BadgerRune.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.BadgerRune  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/BadgerRune.gd', repr(exc)))
    if 'gd_core_items/Exclusive/SpiritCompanion.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.SpiritCompanion  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/SpiritCompanion.gd', repr(exc)))
    if 'gd_core_items/Exclusive/BadgerSpirit.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.BadgerSpirit  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/BadgerSpirit.gd', repr(exc)))
    if 'gd_core_items/Exclusive/BagofGiving.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.BagofGiving  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/BagofGiving.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Bagtacular.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Bagtacular  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Bagtacular.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Battery.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Battery  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Battery.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Bazooka.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Bazooka  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Bazooka.gd', repr(exc)))
    if 'gd_core_items/Exclusive/BerserkerBag.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.BerserkerBag  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/BerserkerBag.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Bewitchment.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Bewitchment  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Bewitchment.gd', repr(exc)))
    if 'gd_core_items/Exclusive/BigBloodthorne.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.BigBloodthorne  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/BigBloodthorne.gd', repr(exc)))
    if 'gd_core_items/Exclusive/BionicArmor.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.BionicArmor  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/BionicArmor.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Cube.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Cube  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Cube.gd', repr(exc)))
    if 'gd_core_items/Exclusive/BismuthCube.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.BismuthCube  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/BismuthCube.gd', repr(exc)))
    if 'gd_core_items/Exclusive/BloodManipulation.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.BloodManipulation  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/BloodManipulation.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Bomb.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Bomb  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Bomb.gd', repr(exc)))
    if 'gd_core_items/Exclusive/BookofBasics.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.BookofBasics  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/BookofBasics.gd', repr(exc)))
    if 'gd_core_items/Exclusive/BookofDarkness.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.BookofDarkness  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/BookofDarkness.gd', repr(exc)))
    if 'gd_core_items/Exclusive/BookofIce.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.BookofIce  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/BookofIce.gd', repr(exc)))
    if 'gd_core_items/Exclusive/BookofLight.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.BookofLight  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/BookofLight.gd', repr(exc)))
    if 'gd_core_items/Exclusive/BookofNature.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.BookofNature  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/BookofNature.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Boomerang.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Boomerang  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Boomerang.gd', repr(exc)))
    if 'gd_core_items/Exclusive/BowlofTreats.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.BowlofTreats  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/BowlofTreats.gd', repr(exc)))
    if 'gd_core_items/Exclusive/BoxofProsperity.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.BoxofProsperity  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/BoxofProsperity.gd', repr(exc)))
    if 'gd_core_items/Exclusive/BrassKnuckles.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.BrassKnuckles  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/BrassKnuckles.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Broccoli.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Broccoli  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Broccoli.gd', repr(exc)))
    if 'gd_core_items/Exclusive/BroccoliGoobert.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.BroccoliGoobert  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/BroccoliGoobert.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Broccotree.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Broccotree  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Broccotree.gd', repr(exc)))
    if 'gd_core_items/Exclusive/BurningBanner.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.BurningBanner  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/BurningBanner.gd', repr(exc)))
    if 'gd_core_items/Exclusive/BurningSword.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.BurningSword  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/BurningSword.gd', repr(exc)))
    if 'gd_core_items/Exclusive/BurningBlade.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.BurningBlade  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/BurningBlade.gd', repr(exc)))
    if 'gd_core_items/Exclusive/BurningSpikes.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.BurningSpikes  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/BurningSpikes.gd', repr(exc)))
    if 'gd_core_items/Exclusive/BustedBlade.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.BustedBlade  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/BustedBlade.gd', repr(exc)))
    if 'gd_core_items/Exclusive/BuytheHolyLight.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.BuytheHolyLight  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/BuytheHolyLight.gd', repr(exc)))
    if 'gd_core_items/Exclusive/CapofBrilliance.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.CapofBrilliance  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/CapofBrilliance.gd', repr(exc)))
    if 'gd_core_items/Exclusive/CatSpirit.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.CatSpirit  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/CatSpirit.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Cauldron.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Cauldron  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Cauldron.gd', repr(exc)))
    if 'gd_core_items/Exclusive/ChainWhip.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.ChainWhip  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/ChainWhip.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Chainsaw.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Chainsaw  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Chainsaw.gd', repr(exc)))
    if 'gd_core_items/Exclusive/ChargeSplitter.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.ChargeSplitter  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/ChargeSplitter.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Cheese.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Cheese  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Cheese.gd', repr(exc)))
    if 'gd_core_items/Exclusive/CheeseGoobert.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.CheeseGoobert  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/CheeseGoobert.gd', repr(exc)))
    if 'gd_core_items/Exclusive/ChessBoard.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.ChessBoard  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/ChessBoard.gd', repr(exc)))
    if 'gd_core_items/Exclusive/ChessMaster.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.ChessMaster  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/ChessMaster.gd', repr(exc)))
    if 'gd_core_items/Exclusive/ChiliGoobert.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.ChiliGoobert  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/ChiliGoobert.gd', repr(exc)))
    if 'gd_core_items/Exclusive/ChiliPepper.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.ChiliPepper  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/ChiliPepper.gd', repr(exc)))
    if 'gd_core_items/Exclusive/ChromeCube.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.ChromeCube  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/ChromeCube.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Cog.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Cog  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Cog.gd', repr(exc)))
    if 'gd_core_items/Exclusive/CogBadge.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.CogBadge  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/CogBadge.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Coil.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Coil  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Coil.gd', repr(exc)))
    if 'gd_core_items/Exclusive/ConTrapTron.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.ConTrapTron  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/ConTrapTron.gd', repr(exc)))
    if 'gd_core_items/Exclusive/CriticalPoison.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.CriticalPoison  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/CriticalPoison.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Crow.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Crow  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Crow.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Cthulhu.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Cthulhu  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Cthulhu.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Cubert.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Cubert  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Cubert.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Cupcake.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Cupcake  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Cupcake.gd', repr(exc)))
    if 'gd_core_items/Exclusive/CupcakeDragon.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.CupcakeDragon  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/CupcakeDragon.gd', repr(exc)))
    if 'gd_core_items/Exclusive/CupcakeGoobert.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.CupcakeGoobert  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/CupcakeGoobert.gd', repr(exc)))
    if 'gd_core_items/Exclusive/CupcakeStaff.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.CupcakeStaff  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/CupcakeStaff.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Daggerang.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Daggerang  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Daggerang.gd', repr(exc)))
    if 'gd_core_items/Exclusive/DarkLantern.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.DarkLantern  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/DarkLantern.gd', repr(exc)))
    if 'gd_core_items/Exclusive/DarkRitual.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.DarkRitual  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/DarkRitual.gd', repr(exc)))
    if 'gd_core_items/Exclusive/DeathLotus.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.DeathLotus  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/DeathLotus.gd', repr(exc)))
    if 'gd_core_items/Exclusive/DeerTotem.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.DeerTotem  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/DeerTotem.gd', repr(exc)))
    if 'gd_core_items/Exclusive/DevouringSphere.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.DevouringSphere  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/DevouringSphere.gd', repr(exc)))
    if 'gd_core_items/Exclusive/DigDeeper.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.DigDeeper  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/DigDeeper.gd', repr(exc)))
    if 'gd_core_items/Exclusive/DivinePotion.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.DivinePotion  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/DivinePotion.gd', repr(exc)))
    if 'gd_core_items/Exclusive/DoomCap.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.DoomCap  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/DoomCap.gd', repr(exc)))
    if 'gd_core_items/Exclusive/DoubleAxe.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.DoubleAxe  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/DoubleAxe.gd', repr(exc)))
    if 'gd_core_items/Exclusive/DoubleRainbow.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.DoubleRainbow  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/DoubleRainbow.gd', repr(exc)))
    if 'gd_core_items/Exclusive/DraconicOrb.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.DraconicOrb  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/DraconicOrb.gd', repr(exc)))
    if 'gd_core_items/Exclusive/DragonClaws.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.DragonClaws  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/DragonClaws.gd', repr(exc)))
    if 'gd_core_items/Exclusive/DragonKnight.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.DragonKnight  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/DragonKnight.gd', repr(exc)))
    if 'gd_core_items/Exclusive/DragonNest.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.DragonNest  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/DragonNest.gd', repr(exc)))
    if 'gd_core_items/Exclusive/DragonSet.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.DragonSet  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/DragonSet.gd', repr(exc)))
    if 'gd_core_items/Exclusive/DragonscaleArmor.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.DragonscaleArmor  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/DragonscaleArmor.gd', repr(exc)))
    if 'gd_core_items/Exclusive/DragonskinBoots.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.DragonskinBoots  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/DragonskinBoots.gd', repr(exc)))
    if 'gd_core_items/Exclusive/DualWielding.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.DualWielding  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/DualWielding.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Eat-o-matic.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Eat_o_matic  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Eat-o-matic.gd', repr(exc)))
    if 'gd_core_items/Exclusive/EchoingBattlecry.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.EchoingBattlecry  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/EchoingBattlecry.gd', repr(exc)))
    if 'gd_core_items/Exclusive/ElectricTorch.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.ElectricTorch  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/ElectricTorch.gd', repr(exc)))
    if 'gd_core_items/Exclusive/ElephantRune.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.ElephantRune  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/ElephantRune.gd', repr(exc)))
    if 'gd_core_items/Exclusive/EmeraldEgg.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.EmeraldEgg  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/EmeraldEgg.gd', repr(exc)))
    if 'gd_core_items/Exclusive/EmeraldWhelp.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.EmeraldWhelp  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/EmeraldWhelp.gd', repr(exc)))
    if 'gd_core_items/Exclusive/EmployeeUniform.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.EmployeeUniform  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/EmployeeUniform.gd', repr(exc)))
    if 'gd_core_items/Exclusive/EnchantedWeapons.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.EnchantedWeapons  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/EnchantedWeapons.gd', repr(exc)))
    if 'gd_core_items/Exclusive/EnergyConversion.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.EnergyConversion  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/EnergyConversion.gd', repr(exc)))
    if 'gd_core_items/Exclusive/EngineerBag2.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.EngineerBag2  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/EngineerBag2.gd', repr(exc)))
    if 'gd_core_items/Exclusive/EngineerBox.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.EngineerBox  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/EngineerBox.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Everburning.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Everburning  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Everburning.gd', repr(exc)))
    if 'gd_core_items/Exclusive/EvilHat.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.EvilHat  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/EvilHat.gd', repr(exc)))
    if 'gd_core_items/Exclusive/ExtraAngy.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.ExtraAngy  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/ExtraAngy.gd', repr(exc)))
    if 'gd_core_items/Exclusive/ExtraBags.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.ExtraBags  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/ExtraBags.gd', repr(exc)))
    if 'gd_core_items/Exclusive/FalseLife.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.FalseLife  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/FalseLife.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Fedora.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Fedora  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Fedora.gd', repr(exc)))
    if 'gd_core_items/Exclusive/FirePit.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.FirePit  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/FirePit.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Shelly.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Shelly  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Shelly.gd', repr(exc)))
    if 'gd_core_items/Exclusive/FireShelly.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.FireShelly  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/FireShelly.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Flame.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Flame  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Flame.gd', repr(exc)))
    if 'gd_core_items/Exclusive/FlameBadge.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.FlameBadge  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/FlameBadge.gd', repr(exc)))
    if 'gd_core_items/Exclusive/FlameWhip.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.FlameWhip  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/FlameWhip.gd', repr(exc)))
    if 'gd_core_items/Exclusive/ForestDragon.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.ForestDragon  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/ForestDragon.gd', repr(exc)))
    if 'gd_core_items/Exclusive/ForestFriend.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.ForestFriend  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/ForestFriend.gd', repr(exc)))
    if 'gd_core_items/Exclusive/ForgingHammer.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.ForgingHammer  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/ForgingHammer.gd', repr(exc)))
    if 'gd_core_items/Exclusive/FortunasKiss.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.FortunasKiss  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/FortunasKiss.gd', repr(exc)))
    if 'gd_core_items/Exclusive/FriendlyFire.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.FriendlyFire  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/FriendlyFire.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Toad.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Toad  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Toad.gd', repr(exc)))
    if 'gd_core_items/Exclusive/FrogPrince.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.FrogPrince  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/FrogPrince.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Frostbite.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Frostbite  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Frostbite.gd', repr(exc)))
    if 'gd_core_items/Exclusive/FrozenBuckler.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.FrozenBuckler  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/FrozenBuckler.gd', repr(exc)))
    if 'gd_core_items/Exclusive/FrozenFlame.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.FrozenFlame  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/FrozenFlame.gd', repr(exc)))
    if 'gd_core_items/Exclusive/FullBodyProtection.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.FullBodyProtection  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/FullBodyProtection.gd', repr(exc)))
    if 'gd_core_items/Exclusive/FurciferPrime.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.FurciferPrime  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/FurciferPrime.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Generator.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Generator  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Generator.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Ghost.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Ghost  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Ghost.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Gigawatz.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Gigawatz  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Gigawatz.gd', repr(exc)))
    if 'gd_core_items/Exclusive/GirlPower.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.GirlPower  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/GirlPower.gd', repr(exc)))
    if 'gd_core_items/Exclusive/GoldArmor.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.GoldArmor  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/GoldArmor.gd', repr(exc)))
    if 'gd_core_items/Exclusive/GoldCube.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.GoldCube  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/GoldCube.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Halberd.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Halberd  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Halberd.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Hardwood.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Hardwood  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Hardwood.gd', repr(exc)))
    if 'gd_core_items/Exclusive/HawkRune.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.HawkRune  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/HawkRune.gd', repr(exc)))
    if 'gd_core_items/Exclusive/HeartShield.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.HeartShield  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/HeartShield.gd', repr(exc)))
    if 'gd_core_items/Exclusive/HeartoftheCards.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.HeartoftheCards  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/HeartoftheCards.gd', repr(exc)))
    if 'gd_core_items/Exclusive/HeavyDrinking.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.HeavyDrinking  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/HeavyDrinking.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Hedgehog.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Hedgehog  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Hedgehog.gd', repr(exc)))
    if 'gd_core_items/Exclusive/HeroShield.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.HeroShield  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/HeroShield.gd', repr(exc)))
    if 'gd_core_items/Exclusive/HogusBogus.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.HogusBogus  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/HogusBogus.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Holdall.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Holdall  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Holdall.gd', repr(exc)))
    if 'gd_core_items/Exclusive/HolyCollar.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.HolyCollar  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/HolyCollar.gd', repr(exc)))
    if 'gd_core_items/Exclusive/HyperHedgehog.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.HyperHedgehog  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/HyperHedgehog.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Hypercube.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Hypercube  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Hypercube.gd', repr(exc)))
    if 'gd_core_items/Exclusive/IceArmor.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.IceArmor  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/IceArmor.gd', repr(exc)))
    if 'gd_core_items/Exclusive/IceDragon.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.IceDragon  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/IceDragon.gd', repr(exc)))
    if 'gd_core_items/Exclusive/IceFlower.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.IceFlower  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/IceFlower.gd', repr(exc)))
    if 'gd_core_items/Exclusive/InnerPower.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.InnerPower  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/InnerPower.gd', repr(exc)))
    if 'gd_core_items/Exclusive/InvestmentOpportunity.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.InvestmentOpportunity  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/InvestmentOpportunity.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Joker.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Joker  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Joker.gd', repr(exc)))
    if 'gd_core_items/Exclusive/JustStats.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.JustStats  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/JustStats.gd', repr(exc)))
    if 'gd_core_items/Exclusive/JynxStaff.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.JynxStaff  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/JynxStaff.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Katana.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Katana  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Katana.gd', repr(exc)))
    if 'gd_core_items/Exclusive/KingCrown.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.KingCrown  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/KingCrown.gd', repr(exc)))
    if 'gd_core_items/Exclusive/KingGoobert.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.KingGoobert  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/KingGoobert.gd', repr(exc)))
    if 'gd_core_items/Exclusive/KingoftheBling.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.KingoftheBling  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/KingoftheBling.gd', repr(exc)))
    if 'gd_core_items/Exclusive/KnifetoMeetYou.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.KnifetoMeetYou  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/KnifetoMeetYou.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Laboratory.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Laboratory  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Laboratory.gd', repr(exc)))
    if 'gd_core_items/Exclusive/LeafBadge.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.LeafBadge  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/LeafBadge.gd', repr(exc)))
    if 'gd_core_items/Exclusive/LevelUp.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.LevelUp  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/LevelUp.gd', repr(exc)))
    if 'gd_core_items/Exclusive/LightFlower.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.LightFlower  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/LightFlower.gd', repr(exc)))
    if 'gd_core_items/Exclusive/LightningPotion.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.LightningPotion  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/LightningPotion.gd', repr(exc)))
    if 'gd_core_items/Exclusive/LightningStaff.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.LightningStaff  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/LightningStaff.gd', repr(exc)))
    if 'gd_core_items/Exclusive/LittleMimic.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.LittleMimic  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/LittleMimic.gd', repr(exc)))
    if 'gd_core_items/Exclusive/LongSpear.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.LongSpear  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/LongSpear.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Lootbox.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Lootbox  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Lootbox.gd', repr(exc)))
    if 'gd_core_items/Exclusive/LuckyCat.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.LuckyCat  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/LuckyCat.gd', repr(exc)))
    if 'gd_core_items/Exclusive/LuckyShortbow.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.LuckyShortbow  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/LuckyShortbow.gd', repr(exc)))
    if 'gd_core_items/Exclusive/MageHat.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.MageHat  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/MageHat.gd', repr(exc)))
    if 'gd_core_items/Exclusive/MagicBadge.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.MagicBadge  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/MagicBadge.gd', repr(exc)))
    if 'gd_core_items/Exclusive/MagicCollar.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.MagicCollar  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/MagicCollar.gd', repr(exc)))
    if 'gd_core_items/Exclusive/MagicMirror.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.MagicMirror  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/MagicMirror.gd', repr(exc)))
    if 'gd_core_items/Exclusive/MagicRing.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.MagicRing  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/MagicRing.gd', repr(exc)))
    if 'gd_core_items/Exclusive/MagiteccArmor.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.MagiteccArmor  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/MagiteccArmor.gd', repr(exc)))
    if 'gd_core_items/Exclusive/ManaCrystal.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.ManaCrystal  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/ManaCrystal.gd', repr(exc)))
    if 'gd_core_items/Exclusive/ManaMastery.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.ManaMastery  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/ManaMastery.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Mananana.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Mananana  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Mananana.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Markswoman.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Markswoman  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Markswoman.gd', repr(exc)))
    if 'gd_core_items/Exclusive/MechaBat.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.MechaBat  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/MechaBat.gd', repr(exc)))
    if 'gd_core_items/Exclusive/MegaClover.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.MegaClover  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/MegaClover.gd', repr(exc)))
    if 'gd_core_items/Exclusive/MercuryElemental.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.MercuryElemental  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/MercuryElemental.gd', repr(exc)))
    if 'gd_core_items/Exclusive/MissFortune.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.MissFortune  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/MissFortune.gd', repr(exc)))
    if 'gd_core_items/Exclusive/MoltenDagger.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.MoltenDagger  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/MoltenDagger.gd', repr(exc)))
    if 'gd_core_items/Exclusive/MoltenGreatsword.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.MoltenGreatsword  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/MoltenGreatsword.gd', repr(exc)))
    if 'gd_core_items/Exclusive/MoltenSpear.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.MoltenSpear  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/MoltenSpear.gd', repr(exc)))
    if 'gd_core_items/Exclusive/MoltenSpear2.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.MoltenSpear2  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/MoltenSpear2.gd', repr(exc)))
    if 'gd_core_items/Exclusive/MoonArmor.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.MoonArmor  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/MoonArmor.gd', repr(exc)))
    if 'gd_core_items/Exclusive/MoreStats.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.MoreStats  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/MoreStats.gd', repr(exc)))
    if 'gd_core_items/Exclusive/MrsStruggles.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.MrsStruggles  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/MrsStruggles.gd', repr(exc)))
    if 'gd_core_items/Exclusive/MushroomFarm.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.MushroomFarm  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/MushroomFarm.gd', repr(exc)))
    if 'gd_core_items/Exclusive/NoRushPlease.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.NoRushPlease  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/NoRushPlease.gd', repr(exc)))
    if 'gd_core_items/Exclusive/NullBlade.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.NullBlade  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/NullBlade.gd', repr(exc)))
    if 'gd_core_items/Exclusive/ObsidianDragon.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.ObsidianDragon  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/ObsidianDragon.gd', repr(exc)))
    if 'gd_core_items/Exclusive/OilLamp.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.OilLamp  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/OilLamp.gd', repr(exc)))
    if 'gd_core_items/Exclusive/OnionCutter.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.OnionCutter  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/OnionCutter.gd', repr(exc)))
    if 'gd_core_items/Exclusive/OwlSpirit.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.OwlSpirit  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/OwlSpirit.gd', repr(exc)))
    if 'gd_core_items/Exclusive/ParadiseBirb.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.ParadiseBirb  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/ParadiseBirb.gd', repr(exc)))
    if 'gd_core_items/Exclusive/PerpetuumMobile.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.PerpetuumMobile  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/PerpetuumMobile.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Phoenix.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Phoenix  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Phoenix.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Phoenix2.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Phoenix2  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Phoenix2.gd', repr(exc)))
    if 'gd_core_items/Exclusive/PiggyPinata.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.PiggyPinata  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/PiggyPinata.gd', repr(exc)))
    if 'gd_core_items/Exclusive/PiggyofRiches.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.PiggyofRiches  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/PiggyofRiches.gd', repr(exc)))
    if 'gd_core_items/Exclusive/PineProtector.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.PineProtector  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/PineProtector.gd', repr(exc)))
    if 'gd_core_items/Exclusive/PlasticCube.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.PlasticCube  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/PlasticCube.gd', repr(exc)))
    if 'gd_core_items/Exclusive/PoisonFrog.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.PoisonFrog  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/PoisonFrog.gd', repr(exc)))
    if 'gd_core_items/Exclusive/PoisonGrenade.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.PoisonGrenade  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/PoisonGrenade.gd', repr(exc)))
    if 'gd_core_items/Exclusive/PoisonShortbow.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.PoisonShortbow  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/PoisonShortbow.gd', repr(exc)))
    if 'gd_core_items/Exclusive/PoisonSpear.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.PoisonSpear  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/PoisonSpear.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Pop.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Pop  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Pop.gd', repr(exc)))
    if 'gd_core_items/Exclusive/PortableAltar.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.PortableAltar  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/PortableAltar.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Pot.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Pot  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Pot.gd', repr(exc)))
    if 'gd_core_items/Exclusive/PoweroftheMoon.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.PoweroftheMoon  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/PoweroftheMoon.gd', repr(exc)))
    if 'gd_core_items/Exclusive/PrismaticSword.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.PrismaticSword  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/PrismaticSword.gd', repr(exc)))
    if 'gd_core_items/Exclusive/PrismaticWand.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.PrismaticWand  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/PrismaticWand.gd', repr(exc)))
    if 'gd_core_items/Exclusive/PuzzleBadge.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.PuzzleBadge  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/PuzzleBadge.gd', repr(exc)))
    if 'gd_core_items/Exclusive/PuzzlebagJ.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.PuzzlebagJ  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/PuzzlebagJ.gd', repr(exc)))
    if 'gd_core_items/Exclusive/PuzzlebagL.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.PuzzlebagL  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/PuzzlebagL.gd', repr(exc)))
    if 'gd_core_items/Exclusive/PuzzlebagS.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.PuzzlebagS  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/PuzzlebagS.gd', repr(exc)))
    if 'gd_core_items/Exclusive/PuzzlebagT.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.PuzzlebagT  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/PuzzlebagT.gd', repr(exc)))
    if 'gd_core_items/Exclusive/PuzzlebagZ.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.PuzzlebagZ  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/PuzzlebagZ.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Puzzlebox.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Puzzlebox  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Puzzlebox.gd', repr(exc)))
    if 'gd_core_items/Exclusive/RainbowBadge.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.RainbowBadge  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/RainbowBadge.gd', repr(exc)))
    if 'gd_core_items/Exclusive/RainbowGoobertAdventurer.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.RainbowGoobertAdventurer  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/RainbowGoobertAdventurer.gd', repr(exc)))
    if 'gd_core_items/Exclusive/RainbowGoobertBerserker.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.RainbowGoobertBerserker  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/RainbowGoobertBerserker.gd', repr(exc)))
    if 'gd_core_items/Exclusive/RainbowGoobertEngineer.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.RainbowGoobertEngineer  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/RainbowGoobertEngineer.gd', repr(exc)))
    if 'gd_core_items/Exclusive/RainbowGoobertMage.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.RainbowGoobertMage  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/RainbowGoobertMage.gd', repr(exc)))
    if 'gd_core_items/Exclusive/RainbowGoobertPyromancer.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.RainbowGoobertPyromancer  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/RainbowGoobertPyromancer.gd', repr(exc)))
    if 'gd_core_items/Exclusive/RainbowOrb.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.RainbowOrb  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/RainbowOrb.gd', repr(exc)))
    if 'gd_core_items/Exclusive/RainbowPotion.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.RainbowPotion  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/RainbowPotion.gd', repr(exc)))
    if 'gd_core_items/Exclusive/RandomLoadoutBag.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.RandomLoadoutBag  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/RandomLoadoutBag.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Rat.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Rat  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Rat.gd', repr(exc)))
    if 'gd_core_items/Exclusive/RatChef.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.RatChef  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/RatChef.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Recombobulator.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Recombobulator  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Recombobulator.gd', repr(exc)))
    if 'gd_core_items/Exclusive/RelicCase.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.RelicCase  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/RelicCase.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Repeater.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Repeater  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Repeater.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Resistor.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Resistor  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Resistor.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Reverse.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Reverse  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Reverse.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Robodog.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Robodog  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Robodog.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Rope.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Rope  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Rope.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Sandbag.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Sandbag  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Sandbag.gd', repr(exc)))
    if 'gd_core_items/Exclusive/SapphireEgg.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.SapphireEgg  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/SapphireEgg.gd', repr(exc)))
    if 'gd_core_items/Exclusive/SapphireWhelp.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.SapphireWhelp  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/SapphireWhelp.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Scale.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Scale  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Scale.gd', repr(exc)))
    if 'gd_core_items/Exclusive/ScholarBag.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.ScholarBag  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/ScholarBag.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Scissorswords.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Scissorswords  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Scissorswords.gd', repr(exc)))
    if 'gd_core_items/Exclusive/SealtheDeal.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.SealtheDeal  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/SealtheDeal.gd', repr(exc)))
    if 'gd_core_items/Exclusive/SerpentStaff.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.SerpentStaff  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/SerpentStaff.gd', repr(exc)))
    if 'gd_core_items/Exclusive/SewingCase.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.SewingCase  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/SewingCase.gd', repr(exc)))
    if 'gd_core_items/Exclusive/ShamanMask.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.ShamanMask  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/ShamanMask.gd', repr(exc)))
    if 'gd_core_items/Exclusive/ShellTotem.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.ShellTotem  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/ShellTotem.gd', repr(exc)))
    if 'gd_core_items/Exclusive/ShepherdsCrook.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.ShepherdsCrook  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/ShepherdsCrook.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Shielded.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Shielded  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Shielded.gd', repr(exc)))
    if 'gd_core_items/Exclusive/ShinyMantle.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.ShinyMantle  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/ShinyMantle.gd', repr(exc)))
    if 'gd_core_items/Exclusive/ShinyShell.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.ShinyShell  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/ShinyShell.gd', repr(exc)))
    if 'gd_core_items/Exclusive/SkullBadge.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.SkullBadge  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/SkullBadge.gd', repr(exc)))
    if 'gd_core_items/Exclusive/SliceofBread.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.SliceofBread  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/SliceofBread.gd', repr(exc)))
    if 'gd_core_items/Exclusive/SliceofToast.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.SliceofToast  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/SliceofToast.gd', repr(exc)))
    if 'gd_core_items/Exclusive/SlimeTime.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.SlimeTime  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/SlimeTime.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Sloth.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Sloth  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Sloth.gd', repr(exc)))
    if 'gd_core_items/Exclusive/SmellyBarrier.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.SmellyBarrier  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/SmellyBarrier.gd', repr(exc)))
    if 'gd_core_items/Exclusive/SmithingForDummies.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.SmithingForDummies  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/SmithingForDummies.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Snake.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Snake  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Snake.gd', repr(exc)))
    if 'gd_core_items/Exclusive/SnowStick.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.SnowStick  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/SnowStick.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Snowball.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Snowball  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Snowball.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Snowcake.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Snowcake  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Snowcake.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Snowman.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Snowman  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Snowman.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Snowmaster.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Snowmaster  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Snowmaster.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Solaris.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Solaris  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Solaris.gd', repr(exc)))
    if 'gd_core_items/Exclusive/SpeakwithAnimals.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.SpeakwithAnimals  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/SpeakwithAnimals.gd', repr(exc)))
    if 'gd_core_items/Exclusive/SpellScrollDark.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.SpellScrollDark  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/SpellScrollDark.gd', repr(exc)))
    if 'gd_core_items/Exclusive/SpellScrollFrostbolt.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.SpellScrollFrostbolt  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/SpellScrollFrostbolt.gd', repr(exc)))
    if 'gd_core_items/Exclusive/SpellScrollIce.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.SpellScrollIce  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/SpellScrollIce.gd', repr(exc)))
    if 'gd_core_items/Exclusive/SpellScrollLight.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.SpellScrollLight  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/SpellScrollLight.gd', repr(exc)))
    if 'gd_core_items/Exclusive/SpellScrollNature.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.SpellScrollNature  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/SpellScrollNature.gd', repr(exc)))
    if 'gd_core_items/Exclusive/SpicyBanana.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.SpicyBanana  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/SpicyBanana.gd', repr(exc)))
    if 'gd_core_items/Exclusive/SpikedCollar.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.SpikedCollar  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/SpikedCollar.gd', repr(exc)))
    if 'gd_core_items/Exclusive/SpikedStaff.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.SpikedStaff  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/SpikedStaff.gd', repr(exc)))
    if 'gd_core_items/Exclusive/SpikedWall.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.SpikedWall  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/SpikedWall.gd', repr(exc)))
    if 'gd_core_items/Exclusive/SpintoWin.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.SpintoWin  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/SpintoWin.gd', repr(exc)))
    if 'gd_core_items/Exclusive/SpiritBells.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.SpiritBells  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/SpiritBells.gd', repr(exc)))
    if 'gd_core_items/Exclusive/SpringLoader.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.SpringLoader  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/SpringLoader.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Squirrel.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Squirrel  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Squirrel.gd', repr(exc)))
    if 'gd_core_items/Exclusive/SquirrelArcher.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.SquirrelArcher  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/SquirrelArcher.gd', repr(exc)))
    if 'gd_core_items/Exclusive/StaffofFire.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.StaffofFire  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/StaffofFire.gd', repr(exc)))
    if 'gd_core_items/Exclusive/StarofCourage.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.StarofCourage  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/StarofCourage.gd', repr(exc)))
    if 'gd_core_items/Exclusive/SteelDragon.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.SteelDragon  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/SteelDragon.gd', repr(exc)))
    if 'gd_core_items/Exclusive/StoneArmor.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.StoneArmor  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/StoneArmor.gd', repr(exc)))
    if 'gd_core_items/Exclusive/StoneBadge.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.StoneBadge  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/StoneBadge.gd', repr(exc)))
    if 'gd_core_items/Exclusive/StoneGloves.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.StoneGloves  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/StoneGloves.gd', repr(exc)))
    if 'gd_core_items/Exclusive/StoneGolem.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.StoneGolem  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/StoneGolem.gd', repr(exc)))
    if 'gd_core_items/Exclusive/StoneShoes.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.StoneShoes  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/StoneShoes.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Stoned.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Stoned  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Stoned.gd', repr(exc)))
    if 'gd_core_items/Exclusive/StrongDivinePotion.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.StrongDivinePotion  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/StrongDivinePotion.gd', repr(exc)))
    if 'gd_core_items/Exclusive/VampiricPotion.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.VampiricPotion  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/VampiricPotion.gd', repr(exc)))
    if 'gd_core_items/Exclusive/StrongVampiricPotion.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.StrongVampiricPotion  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/StrongVampiricPotion.gd', repr(exc)))
    if 'gd_core_items/Exclusive/SunArmor.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.SunArmor  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/SunArmor.gd', repr(exc)))
    if 'gd_core_items/Exclusive/SunShield.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.SunShield  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/SunShield.gd', repr(exc)))
    if 'gd_core_items/Exclusive/TeslaCoil.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.TeslaCoil  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/TeslaCoil.gd', repr(exc)))
    if 'gd_core_items/Exclusive/ThornElemental.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.ThornElemental  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/ThornElemental.gd', repr(exc)))
    if 'gd_core_items/Exclusive/ThornShortbow.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.ThornShortbow  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/ThornShortbow.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Thornbloom.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Thornbloom  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Thornbloom.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Thornburst.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Thornburst  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Thornburst.gd', repr(exc)))
    if 'gd_core_items/Exclusive/ThorsHammer.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.ThorsHammer  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/ThorsHammer.gd', repr(exc)))
    if 'gd_core_items/Exclusive/ThunderDrake.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.ThunderDrake  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/ThunderDrake.gd', repr(exc)))
    if 'gd_core_items/Exclusive/TigerRune.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.TigerRune  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/TigerRune.gd', repr(exc)))
    if 'gd_core_items/Exclusive/TimeDilator.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.TimeDilator  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/TimeDilator.gd', repr(exc)))
    if 'gd_core_items/Exclusive/TimeMelting.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.TimeMelting  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/TimeMelting.gd', repr(exc)))
    if 'gd_core_items/Exclusive/TimePendant.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.TimePendant  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/TimePendant.gd', repr(exc)))
    if 'gd_core_items/Exclusive/ToastGoobert.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.ToastGoobert  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/ToastGoobert.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Toolbox.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Toolbox  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Toolbox.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Turtle.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Turtle  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Turtle.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Twine.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Twine  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Twine.gd', repr(exc)))
    if 'gd_core_items/Exclusive/TwineBadge.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.TwineBadge  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/TwineBadge.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Ukulele.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Ukulele  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Ukulele.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Ultima.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Ultima  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Ultima.gd', repr(exc)))
    if 'gd_core_items/Exclusive/UnidentifiedSkill.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.UnidentifiedSkill  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/UnidentifiedSkill.gd', repr(exc)))
    if 'gd_core_items/Exclusive/UniquelyUnique.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.UniquelyUnique  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/UniquelyUnique.gd', repr(exc)))
    if 'gd_core_items/Exclusive/VampiricCollar.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.VampiricCollar  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/VampiricCollar.gd', repr(exc)))
    if 'gd_core_items/Exclusive/VineweaveBasket.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.VineweaveBasket  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/VineweaveBasket.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Wand.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Wand  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Wand.gd', repr(exc)))
    if 'gd_core_items/Exclusive/WandofDissonance.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.WandofDissonance  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/WandofDissonance.gd', repr(exc)))
    if 'gd_core_items/Exclusive/WarScythe.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.WarScythe  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/WarScythe.gd', repr(exc)))
    if 'gd_core_items/Exclusive/WaterElemental.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.WaterElemental  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/WaterElemental.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Whetstone3.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Whetstone3  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Whetstone3.gd', repr(exc)))
    if 'gd_core_items/Exclusive/WingedBoots.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.WingedBoots  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/WingedBoots.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Wisp.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Wisp  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Wisp.gd', repr(exc)))
    if 'gd_core_items/Exclusive/WolfBadge.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.WolfBadge  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/WolfBadge.gd', repr(exc)))
    if 'gd_core_items/Exclusive/WolfEmblem.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.WolfEmblem  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/WolfEmblem.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Wrench.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Wrench  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Wrench.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Chess/ChessPiece.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Chess.ChessPiece  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Chess/ChessPiece.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Chess/BlackBishop.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Chess.BlackBishop  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Chess/BlackBishop.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Chess/BlackKing.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Chess.BlackKing  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Chess/BlackKing.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Chess/BlackKnight.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Chess.BlackKnight  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Chess/BlackKnight.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Chess/BlackPawn.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Chess.BlackPawn  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Chess/BlackPawn.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Chess/BlackQueen.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Chess.BlackQueen  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Chess/BlackQueen.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Chess/BlackRook.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Chess.BlackRook  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Chess/BlackRook.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Chess/WhiteBishop.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Chess.WhiteBishop  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Chess/WhiteBishop.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Chess/WhiteKing.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Chess.WhiteKing  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Chess/WhiteKing.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Chess/WhiteKnight.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Chess.WhiteKnight  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Chess/WhiteKnight.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Chess/WhitePawn.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Chess.WhitePawn  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Chess/WhitePawn.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Chess/WhiteQueen.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Chess.WhiteQueen  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Chess/WhiteQueen.gd', repr(exc)))
    if 'gd_core_items/Exclusive/Chess/WhiteRook.gd' in want:
        try:
            import gd_core_py.gd_core_items.Exclusive.Chess.WhiteRook  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Exclusive/Chess/WhiteRook.gd', repr(exc)))
    if 'gd_core_items/Gems/Amethyst.gd' in want:
        try:
            import gd_core_py.gd_core_items.Gems.Amethyst  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Gems/Amethyst.gd', repr(exc)))
    if 'gd_core_items/Gems/CorruptedCrystal.gd' in want:
        try:
            import gd_core_py.gd_core_items.Gems.CorruptedCrystal  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Gems/CorruptedCrystal.gd', repr(exc)))
    if 'gd_core_items/Gems/Emerald.gd' in want:
        try:
            import gd_core_py.gd_core_items.Gems.Emerald  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Gems/Emerald.gd', repr(exc)))
    if 'gd_core_items/Gems/LumpofCoal.gd' in want:
        try:
            import gd_core_py.gd_core_items.Gems.LumpofCoal  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Gems/LumpofCoal.gd', repr(exc)))
    if 'gd_core_items/Gems/Ruby.gd' in want:
        try:
            import gd_core_py.gd_core_items.Gems.Ruby  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Gems/Ruby.gd', repr(exc)))
    if 'gd_core_items/Gems/Sapphire.gd' in want:
        try:
            import gd_core_py.gd_core_items.Gems.Sapphire  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Gems/Sapphire.gd', repr(exc)))
    if 'gd_core_items/Gems/Skull.gd' in want:
        try:
            import gd_core_py.gd_core_items.Gems.Skull  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Gems/Skull.gd', repr(exc)))
    if 'gd_core_items/Gems/Topaz.gd' in want:
        try:
            import gd_core_py.gd_core_items.Gems.Topaz  # noqa: F401
        except Exception as exc:  # noqa: BLE001
            failed.append(('gd_core_items/Gems/Topaz.gd', repr(exc)))
    return failed
