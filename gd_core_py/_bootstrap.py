# -*- coding: utf-8 -*-
# 自动生成，勿手改。生成器：tools/gd_to_py.py
"""按 extends 依赖拓扑序导入全部模块（基类先注册，与 Godot 加载次序同义）。"""

from . import _registry  # noqa: F401
from . import _rt  # noqa: F401


def load_all():
    """导入全部 gd 模块。返回导入失败清单（空 = 全部成功）。"""
    failed = []
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
        import gd_core_py.gd_core.CoreItem  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core/CoreItem.gd', repr(exc)))
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
        import gd_core_py.gd_core_items.Item  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Item.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Card  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Card.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.AceofSpades  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/AceofSpades.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.RangerCollar  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/RangerCollar.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.AcornCollar  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/AcornCollar.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Stone  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Stone.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.ArtifactStoneCold  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/ArtifactStoneCold.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.ArtifactStoneHeat  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/ArtifactStoneHeat.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Bag  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Bag.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.BagofStones  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/BagofStones.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Food  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Food.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Banana  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Banana.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.BloodAmulet  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/BloodAmulet.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Goobert  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Goobert.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.BloodGoobert  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/BloodGoobert.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Weapon  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Weapon.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Bloodthorne  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Bloodthorne.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Dagger  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Dagger.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.BloodyDagger  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/BloodyDagger.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Blueberries  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Blueberries.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Bow  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Bow.gd', repr(exc)))
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
        import gd_core_py.gd_core_items.Gems.Gem  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Gems/Gem.gd', repr(exc)))
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
        import gd_core_py.gd_core_items.Potion  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Potion.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.DemonicFlask  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/DemonicFlask.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.DjinnLamp  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/DjinnLamp.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.DragonEgg  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/DragonEgg.gd', repr(exc)))
    try:
        import gd_core_py.gd_core_items.Pan  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Pan.gd', repr(exc)))
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
        import gd_core_py.gd_core_items.HealthPotion  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/HealthPotion.gd', repr(exc)))
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
        import gd_core_py.gd_core_items.LeatherHelm  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/LeatherHelm.gd', repr(exc)))
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
        import gd_core_py.gd_core_items.Piggybank  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Piggybank.gd', repr(exc)))
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
        import gd_core_py.gd_core_items.Shield  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/Shield.gd', repr(exc)))
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
        import gd_core_py.gd_core_items.PestilenceFlask  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/PestilenceFlask.gd', repr(exc)))
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
        import gd_core_py.gd_core_items.StoneSkinPotion  # noqa: F401
    except Exception as exc:  # noqa: BLE001
        failed.append(('gd_core_items/StoneSkinPotion.gd', repr(exc)))
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
