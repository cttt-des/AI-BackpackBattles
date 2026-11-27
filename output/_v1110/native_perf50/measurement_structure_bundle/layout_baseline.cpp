#include <cstdio>
#include <cstddef>
#include "gen/hdrs/Gd__gd_core__AceofSpades.hpp"
#include "gen/hdrs/Gd__gd_core__AcornCollar.hpp"
#include "gen/hdrs/Gd__gd_core__ArtifactStoneCold.hpp"
#include "gen/hdrs/Gd__gd_core__ArtifactStoneHeat.hpp"
#include "gen/hdrs/Gd__gd_core__Bag.hpp"
#include "gen/hdrs/Gd__gd_core__BagofStones.hpp"
#include "gen/hdrs/Gd__gd_core__Banana.hpp"
#include "gen/hdrs/Gd__gd_core__BloodAmulet.hpp"
#include "gen/hdrs/Gd__gd_core__BloodGoobert.hpp"
#include "gen/hdrs/Gd__gd_core__Bloodthorne.hpp"
#include "gen/hdrs/Gd__gd_core__BloodyDagger.hpp"
#include "gen/hdrs/Gd__gd_core__Blueberries.hpp"
#include "gen/hdrs/Gd__gd_core__Bow.hpp"
#include "gen/hdrs/Gd__gd_core__BowandArrow.hpp"
#include "gen/hdrs/Gd__gd_core__BoxofRiches.hpp"
#include "gen/hdrs/Gd__gd_core__Broom.hpp"
#include "gen/hdrs/Gd__gd_core__BurningCoal.hpp"
#include "gen/hdrs/Gd__gd_core__BurningTorch.hpp"
#include "gen/hdrs/Gd__gd_core__Card.hpp"
#include "gen/hdrs/Gd__gd_core__Carrot.hpp"
#include "gen/hdrs/Gd__gd_core__CarrotGoobert.hpp"
#include "gen/hdrs/Gd__gd_core__ClawsofAttack.hpp"
#include "gen/hdrs/Gd__gd_core__CoreBuff.hpp"
#include "gen/hdrs/Gd__gd_core__CoreBuff__INNER__TemporaryStacks.hpp"
#include "gen/hdrs/Gd__gd_core__CoreCharacter.hpp"
#include "gen/hdrs/Gd__gd_core__CoreCombat.hpp"
#include "gen/hdrs/Gd__gd_core__CoreCombat__INNER__CoreItemSort.hpp"
#include "gen/hdrs/Gd__gd_core__CoreCombatLog.hpp"
#include "gen/hdrs/Gd__gd_core__CoreConst.hpp"
#include "gen/hdrs/Gd__gd_core__CoreContext.hpp"
#include "gen/hdrs/Gd__gd_core__CoreContext__INNER__NativeFlicker.hpp"
#include "gen/hdrs/Gd__gd_core__CoreDamageResult.hpp"
#include "gen/hdrs/Gd__gd_core__CoreDamageSource.hpp"
#include "gen/hdrs/Gd__gd_core__CoreEvent.hpp"
#include "gen/hdrs/Gd__gd_core__CoreEventBus.hpp"
#include "gen/hdrs/Gd__gd_core__CoreGrid.hpp"
#include "gen/hdrs/Gd__gd_core__CoreHooks.hpp"
#include "gen/hdrs/Gd__gd_core__CoreItem.hpp"
#include "gen/hdrs/Gd__gd_core__CoreItem__INNER__CoreElectricalCharge.hpp"
#include "gen/hdrs/Gd__gd_core__CoreItem__INNER__CoreSignalConnection.hpp"
#include "gen/hdrs/Gd__gd_core__CoreItemBook.hpp"
#include "gen/hdrs/Gd__gd_core__CoreItemData.hpp"
#include "gen/hdrs/Gd__gd_core__CoreRng.hpp"
#include "gen/hdrs/Gd__gd_core__CoreRng__INNER__BalancedRange.hpp"
#include "gen/hdrs/Gd__gd_core__CoreRng__INNER__BalancedRng.hpp"
#include "gen/hdrs/Gd__gd_core__CoreTimer.hpp"
#include "gen/hdrs/Gd__gd_core__CoreUtil.hpp"
#include "gen/hdrs/Gd__gd_core__CoreUtil__INNER__DictSorter.hpp"
#include "gen/hdrs/Gd__gd_core__CorruptedArmor.hpp"
#include "gen/hdrs/Gd__gd_core__CritwoodStaff.hpp"
#include "gen/hdrs/Gd__gd_core__Crossblades.hpp"
#include "gen/hdrs/Gd__gd_core__Crown.hpp"
#include "gen/hdrs/Gd__gd_core__CursedDagger.hpp"
#include "gen/hdrs/Gd__gd_core__CursedHairComb.hpp"
#include "gen/hdrs/Gd__gd_core__CustomerCard.hpp"
#include "gen/hdrs/Gd__gd_core__Dagger.hpp"
#include "gen/hdrs/Gd__gd_core__DancingDragon.hpp"
#include "gen/hdrs/Gd__gd_core__DarkestLotus.hpp"
#include "gen/hdrs/Gd__gd_core__Darksaber.hpp"
#include "gen/hdrs/Gd__gd_core__DeathScythe.hpp"
#include "gen/hdrs/Gd__gd_core__DeckofCards.hpp"
#include "gen/hdrs/Gd__gd_core__DemonicFlask.hpp"
#include "gen/hdrs/Gd__gd_core__DjinnLamp.hpp"
#include "gen/hdrs/Gd__gd_core__DragonEgg.hpp"
#include "gen/hdrs/Gd__gd_core__Eggscalibur.hpp"
#include "gen/hdrs/Gd__gd_core__EvilCap.hpp"
#include "gen/hdrs/Gd__gd_core__FalconBlade.hpp"
#include "gen/hdrs/Gd__gd_core__FancyFencingRapier.hpp"
#include "gen/hdrs/Gd__gd_core__Fanfare.hpp"
#include "gen/hdrs/Gd__gd_core__FannyPack.hpp"
#include "gen/hdrs/Gd__gd_core__Flute.hpp"
#include "gen/hdrs/Gd__gd_core__FlyAgaric.hpp"
#include "gen/hdrs/Gd__gd_core__Food.hpp"
#include "gen/hdrs/Gd__gd_core__Garlic.hpp"
#include "gen/hdrs/Gd__gd_core__GingerbreadMan.hpp"
#include "gen/hdrs/Gd__gd_core__GlovesofHaste.hpp"
#include "gen/hdrs/Gd__gd_core__Goobert.hpp"
#include "gen/hdrs/Gd__gd_core__Greatsword.hpp"
#include "gen/hdrs/Gd__gd_core__Hammer.hpp"
#include "gen/hdrs/Gd__gd_core__HealingHerbs.hpp"
#include "gen/hdrs/Gd__gd_core__HealthPotion.hpp"
#include "gen/hdrs/Gd__gd_core__HeartContainer.hpp"
#include "gen/hdrs/Gd__gd_core__HeartofDarkness.hpp"
#include "gen/hdrs/Gd__gd_core__HeroicPotion.hpp"
#include "gen/hdrs/Gd__gd_core__HeroLongsword.hpp"
#include "gen/hdrs/Gd__gd_core__HeroSword.hpp"
#include "gen/hdrs/Gd__gd_core__HoloFireLizard.hpp"
#include "gen/hdrs/Gd__gd_core__HolyArmor.hpp"
#include "gen/hdrs/Gd__gd_core__HolySpear.hpp"
#include "gen/hdrs/Gd__gd_core__HungryBlade.hpp"
#include "gen/hdrs/Gd__gd_core__Item.hpp"
#include "gen/hdrs/Gd__gd_core__Item__INNER__SignalConnection.hpp"
#include "gen/hdrs/Gd__gd_core__Jynxtorquilla.hpp"
#include "gen/hdrs/Gd__gd_core__LeatherArmor.hpp"
#include "gen/hdrs/Gd__gd_core__LeatherBoots.hpp"
#include "gen/hdrs/Gd__gd_core__LeatherHelm.hpp"
#include "gen/hdrs/Gd__gd_core__LightGoobert.hpp"
#include "gen/hdrs/Gd__gd_core__Lightsaber.hpp"
#include "gen/hdrs/Gd__gd_core__LuckyBow.hpp"
#include "gen/hdrs/Gd__gd_core__LuckyClover.hpp"
#include "gen/hdrs/Gd__gd_core__LuckyPiggy.hpp"
#include "gen/hdrs/Gd__gd_core__MagicStaff.hpp"
#include "gen/hdrs/Gd__gd_core__MagicTorch.hpp"
#include "gen/hdrs/Gd__gd_core__ManaOrb.hpp"
#include "gen/hdrs/Gd__gd_core__ManaPotion.hpp"
#include "gen/hdrs/Gd__gd_core__Manathirst.hpp"
#include "gen/hdrs/Gd__gd_core__MoonShield.hpp"
#include "gen/hdrs/Gd__gd_core__MrStruggles.hpp"
#include "gen/hdrs/Gd__gd_core__Pan.hpp"
#include "gen/hdrs/Gd__gd_core__Pandamonium.hpp"
#include "gen/hdrs/Gd__gd_core__PestilenceFlask.hpp"
#include "gen/hdrs/Gd__gd_core__PiercingArrow.hpp"
#include "gen/hdrs/Gd__gd_core__Piggybank.hpp"
#include "gen/hdrs/Gd__gd_core__Pineapple.hpp"
#include "gen/hdrs/Gd__gd_core__PlatinCustomerCard.hpp"
#include "gen/hdrs/Gd__gd_core__PocketSand.hpp"
#include "gen/hdrs/Gd__gd_core__PoisonBow.hpp"
#include "gen/hdrs/Gd__gd_core__PoisonDagger.hpp"
#include "gen/hdrs/Gd__gd_core__PoisonGoobert.hpp"
#include "gen/hdrs/Gd__gd_core__PoisonIvy.hpp"
#include "gen/hdrs/Gd__gd_core__Potion.hpp"
#include "gen/hdrs/Gd__gd_core__PotionBelt.hpp"
#include "gen/hdrs/Gd__gd_core__Present.hpp"
#include "gen/hdrs/Gd__gd_core__ProtectivePurse.hpp"
#include "gen/hdrs/Gd__gd_core__Pumpkin.hpp"
#include "gen/hdrs/Gd__gd_core__RainbowGoobert.hpp"
#include "gen/hdrs/Gd__gd_core__RainbowGoobertRanger.hpp"
#include "gen/hdrs/Gd__gd_core__RangerBag.hpp"
#include "gen/hdrs/Gd__gd_core__RangerCollar.hpp"
#include "gen/hdrs/Gd__gd_core__RibSawBlade.hpp"
#include "gen/hdrs/Gd__gd_core__RubyChonk.hpp"
#include "gen/hdrs/Gd__gd_core__RubyEgg.hpp"
#include "gen/hdrs/Gd__gd_core__RubyWhelp.hpp"
#include "gen/hdrs/Gd__gd_core__Shield.hpp"
#include "gen/hdrs/Gd__gd_core__ShieldofValor.hpp"
#include "gen/hdrs/Gd__gd_core__Shovel.hpp"
#include "gen/hdrs/Gd__gd_core__Spear.hpp"
#include "gen/hdrs/Gd__gd_core__SpectralDagger.hpp"
#include "gen/hdrs/Gd__gd_core__SpikedShield.hpp"
#include "gen/hdrs/Gd__gd_core__StaffofUnhealing.hpp"
#include "gen/hdrs/Gd__gd_core__StaminaSack.hpp"
#include "gen/hdrs/Gd__gd_core__SteelGoobert.hpp"
#include "gen/hdrs/Gd__gd_core__Stone.hpp"
#include "gen/hdrs/Gd__gd_core__StoneHelm.hpp"
#include "gen/hdrs/Gd__gd_core__StoneSkinPotion.hpp"
#include "gen/hdrs/Gd__gd_core__StorageCoffin.hpp"
#include "gen/hdrs/Gd__gd_core__StrongDemonicFlask.hpp"
#include "gen/hdrs/Gd__gd_core__StrongHealthPotion.hpp"
#include "gen/hdrs/Gd__gd_core__StrongPestilenceFlask.hpp"
#include "gen/hdrs/Gd__gd_core__StrongStoneSkinPotion.hpp"
#include "gen/hdrs/Gd__gd_core__TheFool.hpp"
#include "gen/hdrs/Gd__gd_core__TheLovers.hpp"
#include "gen/hdrs/Gd__gd_core__ThornBow.hpp"
#include "gen/hdrs/Gd__gd_core__ThornWhip.hpp"
#include "gen/hdrs/Gd__gd_core__Torch.hpp"
#include "gen/hdrs/Gd__gd_core__VampiricArmor.hpp"
#include "gen/hdrs/Gd__gd_core__VampiricGloves.hpp"
#include "gen/hdrs/Gd__gd_core__VampiricScythe.hpp"
#include "gen/hdrs/Gd__gd_core__VillainSword.hpp"
#include "gen/hdrs/Gd__gd_core__WalrusTusk.hpp"
#include "gen/hdrs/Gd__gd_core__Weapon.hpp"
#include "gen/hdrs/Gd__gd_core__Whetstone.hpp"
#include "gen/hdrs/Gd__gd_core__White_EyesBlueDragon.hpp"
#include "gen/hdrs/Gd__gd_core__Wolpertinger.hpp"
#include "gen/hdrs/Gd__gd_core__WoodenBuckler.hpp"
#include "gen/hdrs/Gd__gd_core__WoodenSword.hpp"
#include "gen/hdrs/Gd__gd_core__YggdrasilLeaf.hpp"
#include "gen/hdrs/Gd__gd_core_items__AceofSpades.hpp"
#include "gen/hdrs/Gd__gd_core_items__AcornCollar.hpp"
#include "gen/hdrs/Gd__gd_core_items__ArtifactStoneCold.hpp"
#include "gen/hdrs/Gd__gd_core_items__ArtifactStoneHeat.hpp"
#include "gen/hdrs/Gd__gd_core_items__Bag.hpp"
#include "gen/hdrs/Gd__gd_core_items__BagofStones.hpp"
#include "gen/hdrs/Gd__gd_core_items__Banana.hpp"
#include "gen/hdrs/Gd__gd_core_items__BloodAmulet.hpp"
#include "gen/hdrs/Gd__gd_core_items__BloodGoobert.hpp"
#include "gen/hdrs/Gd__gd_core_items__Bloodthorne.hpp"
#include "gen/hdrs/Gd__gd_core_items__BloodyDagger.hpp"
#include "gen/hdrs/Gd__gd_core_items__Blueberries.hpp"
#include "gen/hdrs/Gd__gd_core_items__Bow.hpp"
#include "gen/hdrs/Gd__gd_core_items__BowandArrow.hpp"
#include "gen/hdrs/Gd__gd_core_items__BoxofRiches.hpp"
#include "gen/hdrs/Gd__gd_core_items__Broom.hpp"
#include "gen/hdrs/Gd__gd_core_items__BurningCoal.hpp"
#include "gen/hdrs/Gd__gd_core_items__BurningTorch.hpp"
#include "gen/hdrs/Gd__gd_core_items__Card.hpp"
#include "gen/hdrs/Gd__gd_core_items__Carrot.hpp"
#include "gen/hdrs/Gd__gd_core_items__CarrotGoobert.hpp"
#include "gen/hdrs/Gd__gd_core_items__ClawsofAttack.hpp"
#include "gen/hdrs/Gd__gd_core_items__Coins.hpp"
#include "gen/hdrs/Gd__gd_core_items__CorruptedArmor.hpp"
#include "gen/hdrs/Gd__gd_core_items__CritwoodStaff.hpp"
#include "gen/hdrs/Gd__gd_core_items__Crossblades.hpp"
#include "gen/hdrs/Gd__gd_core_items__Crown.hpp"
#include "gen/hdrs/Gd__gd_core_items__CursedDagger.hpp"
#include "gen/hdrs/Gd__gd_core_items__CursedHairComb.hpp"
#include "gen/hdrs/Gd__gd_core_items__CustomerCard.hpp"
#include "gen/hdrs/Gd__gd_core_items__Dagger.hpp"
#include "gen/hdrs/Gd__gd_core_items__DancingDragon.hpp"
#include "gen/hdrs/Gd__gd_core_items__DarkestLotus.hpp"
#include "gen/hdrs/Gd__gd_core_items__Darksaber.hpp"
#include "gen/hdrs/Gd__gd_core_items__DeathScythe.hpp"
#include "gen/hdrs/Gd__gd_core_items__DeckofCards.hpp"
#include "gen/hdrs/Gd__gd_core_items__DemonicFlask.hpp"
#include "gen/hdrs/Gd__gd_core_items__DjinnLamp.hpp"
#include "gen/hdrs/Gd__gd_core_items__DragonEgg.hpp"
#include "gen/hdrs/Gd__gd_core_items__Eggscalibur.hpp"
#include "gen/hdrs/Gd__gd_core_items__EvilCap.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__AcornAce.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__AmethystEgg.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__AmethystWhelp.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__AmuletofAgility.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__AmuletofAlchemy.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__AmuletofDarkness.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__AmuletofFeasting.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__AmuletofFortune.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__AmuletofLife.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__AmuletofLight.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__AmuletofSteel.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__AmuletoftheWild.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__AmuletUnidentified.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__AngelCrystal.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Anvil.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__ArcaneBoots.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__ArcaneIntellect.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__ArmoredCouragePuppy.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__ArmoredPowerPuppy.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__ArmoredWisdomPuppy.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__ArtifactStoneDeath.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Automanaton.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Axe.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__BadgerRune.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__BadgerSpirit.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__BagofGiving.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Bagtacular.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Battery.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Bazooka.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__BerserkerBag.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Bewitchment.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__BigBloodthorne.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__BionicArmor.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__BismuthCube.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__BloodManipulation.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Bomb.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__BookofBasics.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__BookofDarkness.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__BookofIce.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__BookofLight.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__BookofNature.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Boomerang.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__BowlofTreats.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__BoxofProsperity.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__BrassKnuckles.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Broccoli.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__BroccoliGoobert.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Broccotree.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__BurningBanner.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__BurningBlade.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__BurningSpikes.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__BurningSword.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__BustedBlade.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__BuytheHolyLight.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__CapofBrilliance.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__CatSpirit.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Cauldron.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Chainsaw.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__ChainWhip.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__ChargeSplitter.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Cheese.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__CheeseGoobert.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Chess__BlackBishop.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Chess__BlackKing.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Chess__BlackKnight.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Chess__BlackPawn.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Chess__BlackQueen.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Chess__BlackRook.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Chess__ChessPiece.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Chess__WhiteBishop.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Chess__WhiteKing.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Chess__WhiteKnight.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Chess__WhitePawn.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Chess__WhiteQueen.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Chess__WhiteRook.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__ChessBoard.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__ChessMaster.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__ChiliGoobert.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__ChiliPepper.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__ChromeCube.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Cog.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__CogBadge.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Coil.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__ConTrapTron.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__CouragePuppy.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__CriticalPoison.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Crow.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Cthulhu.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Cube.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Cubert.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Cupcake.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__CupcakeDragon.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__CupcakeGoobert.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__CupcakeStaff.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Daggerang.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__DarkLantern.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__DarkRitual.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__DeathLotus.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__DeerTotem.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__DevouringSphere.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__DigDeeper.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__DivinePotion.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__DoomCap.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__DoubleAxe.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__DoubleRainbow.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__DraconicOrb.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__DragonClaws.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__DragonKnight.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__DragonNest.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__DragonscaleArmor.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__DragonSet.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__DragonskinBoots.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__DualWielding.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Eat_o_matic.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__EchoingBattlecry.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__ElectricTorch.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__ElephantRune.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__EmeraldEgg.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__EmeraldWhelp.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__EmployeeUniform.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__EnchantedWeapons.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__EnergyConversion.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__EngineerBag2.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__EngineerBox.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Everburning.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__EvilHat.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__ExtraAngy.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__ExtraBags.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__FalseLife.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Fedora.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__FirePit.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__FireShelly.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Flame.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__FlameBadge.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__FlameWhip.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__ForestDragon.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__ForestFriend.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__ForgingHammer.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__FortunasKiss.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__FriendlyFire.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__FrogPrince.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Frostbite.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__FrozenBuckler.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__FrozenFlame.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__FullBodyProtection.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__FurciferPrime.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Generator.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Ghost.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Gigawatz.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__GirlPower.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__GoldArmor.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__GoldCube.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Halberd.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Hardwood.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__HawkRune.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__HeartoftheCards.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__HeartShield.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__HeavyDrinking.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Hedgehog.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__HeroShield.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__HogusBogus.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Holdall.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__HolyCollar.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Hypercube.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__HyperHedgehog.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__IceArmor.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__IceDragon.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__IceFlower.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__InnerPower.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__InvestmentOpportunity.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Joker.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__JustStats.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__JynxStaff.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Katana.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__KingCrown.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__KingGoobert.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__KingoftheBling.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__KnifetoMeetYou.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Laboratory.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__LeafBadge.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__LevelUp.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__LightFlower.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__LightningPotion.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__LightningStaff.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__LittleMimic.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__LongSpear.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Lootbox.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__LuckyCat.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__LuckyShortbow.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__MageHat.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__MagicBadge.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__MagicCollar.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__MagicMirror.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__MagicRing.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__MagiteccArmor.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__ManaCrystal.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__ManaMastery.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Mananana.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Markswoman.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__MechaBat.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__MegaClover.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__MercuryElemental.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__MissFortune.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__MoltenDagger.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__MoltenGreatsword.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__MoltenSpear.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__MoltenSpear2.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__MoonArmor.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__MoreStats.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__MrsStruggles.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__MushroomFarm.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__NoRushPlease.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__NullBlade.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__ObsidianDragon.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__OilLamp.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__OnionCutter.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__OwlSpirit.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__ParadiseBirb.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__PerpetuumMobile.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Phoenix.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Phoenix2.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__PiggyofRiches.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__PiggyPinata.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__PineProtector.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__PlasticCube.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__PoisonFrog.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__PoisonGrenade.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__PoisonShortbow.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__PoisonSpear.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Pop.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__PortableAltar.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Pot.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__PoweroftheMoon.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__PowerPuppy.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__PrismaticSword.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__PrismaticWand.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__PuzzleBadge.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__PuzzlebagJ.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__PuzzlebagL.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__PuzzlebagS.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__PuzzlebagT.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__PuzzlebagZ.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Puzzlebox.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__RainbowBadge.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__RainbowGoobertAdventurer.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__RainbowGoobertBerserker.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__RainbowGoobertEngineer.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__RainbowGoobertMage.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__RainbowGoobertPyromancer.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__RainbowOrb.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__RainbowPotion.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__RandomLoadoutBag.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Rat.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__RatChef.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Recombobulator.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__RelicCase.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Repeater.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Resistor.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Reverse.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Robodog.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Rope.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Sandbag.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__SapphireEgg.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__SapphireWhelp.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Scale.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__ScholarBag.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Scissorswords.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__SealtheDeal.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__SerpentStaff.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__SewingCase.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__ShamanMask.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__ShellTotem.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Shelly.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__ShepherdsCrook.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Shielded.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__ShinyMantle.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__ShinyShell.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__SkullBadge.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__SliceofBread.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__SliceofToast.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__SlimeTime.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Sloth.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__SmellyBarrier.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__SmithingForDummies.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Snake.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Snowball.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Snowcake.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Snowman.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Snowmaster.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__SnowStick.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Solaris.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__SpeakwithAnimals.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__SpellScrollDark.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__SpellScrollFrostbolt.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__SpellScrollIce.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__SpellScrollLight.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__SpellScrollNature.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__SpicyBanana.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__SpikedCollar.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__SpikedStaff.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__SpikedWall.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__SpintoWin.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__SpiritBells.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__SpiritCompanion.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__SpringLoader.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Squirrel.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__SquirrelArcher.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__StaffofFire.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__StarofCourage.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__SteelDragon.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__StoneArmor.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__StoneBadge.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Stoned.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__StoneGloves.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__StoneGolem.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__StoneShoes.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__StrongDivinePotion.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__StrongVampiricPotion.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__SunArmor.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__SunShield.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__TeslaCoil.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Thornbloom.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Thornburst.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__ThornElemental.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__ThornShortbow.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__ThorsHammer.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__ThunderDrake.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__TigerRune.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__TimeDilator.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__TimeMelting.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__TimePendant.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Toad.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__ToastGoobert.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Toolbox.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Turtle.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Twine.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__TwineBadge.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Ukulele.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Ultima.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__UnidentifiedSkill.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__UniquelyUnique.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__VampiricCollar.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__VampiricPotion.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__VineweaveBasket.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Wand.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__WandofDissonance.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__WarScythe.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__WaterElemental.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Whetstone3.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__WingedBoots.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__WisdomPuppy.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Wisp.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__WolfBadge.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__WolfEmblem.hpp"
#include "gen/hdrs/Gd__gd_core_items__Exclusive__Wrench.hpp"
#include "gen/hdrs/Gd__gd_core_items__FalconBlade.hpp"
#include "gen/hdrs/Gd__gd_core_items__FancyFencingRapier.hpp"
#include "gen/hdrs/Gd__gd_core_items__Fanfare.hpp"
#include "gen/hdrs/Gd__gd_core_items__FannyPack.hpp"
#include "gen/hdrs/Gd__gd_core_items__Flute.hpp"
#include "gen/hdrs/Gd__gd_core_items__FlyAgaric.hpp"
#include "gen/hdrs/Gd__gd_core_items__Food.hpp"
#include "gen/hdrs/Gd__gd_core_items__Garlic.hpp"
#include "gen/hdrs/Gd__gd_core_items__Gems__Amethyst.hpp"
#include "gen/hdrs/Gd__gd_core_items__Gems__CorruptedCrystal.hpp"
#include "gen/hdrs/Gd__gd_core_items__Gems__Emerald.hpp"
#include "gen/hdrs/Gd__gd_core_items__Gems__Gem.hpp"
#include "gen/hdrs/Gd__gd_core_items__Gems__LumpofCoal.hpp"
#include "gen/hdrs/Gd__gd_core_items__Gems__Ruby.hpp"
#include "gen/hdrs/Gd__gd_core_items__Gems__Sapphire.hpp"
#include "gen/hdrs/Gd__gd_core_items__Gems__Skull.hpp"
#include "gen/hdrs/Gd__gd_core_items__Gems__Topaz.hpp"
#include "gen/hdrs/Gd__gd_core_items__GingerbreadMan.hpp"
#include "gen/hdrs/Gd__gd_core_items__GlovesofHaste.hpp"
#include "gen/hdrs/Gd__gd_core_items__Goobert.hpp"
#include "gen/hdrs/Gd__gd_core_items__Greatsword.hpp"
#include "gen/hdrs/Gd__gd_core_items__Hammer.hpp"
#include "gen/hdrs/Gd__gd_core_items__HealingHerbs.hpp"
#include "gen/hdrs/Gd__gd_core_items__HealthPotion.hpp"
#include "gen/hdrs/Gd__gd_core_items__HeartContainer.hpp"
#include "gen/hdrs/Gd__gd_core_items__HeartofDarkness.hpp"
#include "gen/hdrs/Gd__gd_core_items__HeroicPotion.hpp"
#include "gen/hdrs/Gd__gd_core_items__HeroLongsword.hpp"
#include "gen/hdrs/Gd__gd_core_items__HeroSword.hpp"
#include "gen/hdrs/Gd__gd_core_items__HoloFireLizard.hpp"
#include "gen/hdrs/Gd__gd_core_items__HolyArmor.hpp"
#include "gen/hdrs/Gd__gd_core_items__HolySpear.hpp"
#include "gen/hdrs/Gd__gd_core_items__HungryBlade.hpp"
#include "gen/hdrs/Gd__gd_core_items__Item.hpp"
#include "gen/hdrs/Gd__gd_core_items__Item__INNER__SignalConnection.hpp"
#include "gen/hdrs/Gd__gd_core_items__Jynxtorquilla.hpp"
#include "gen/hdrs/Gd__gd_core_items__LeatherArmor.hpp"
#include "gen/hdrs/Gd__gd_core_items__LeatherBoots.hpp"
#include "gen/hdrs/Gd__gd_core_items__LeatherHelm.hpp"
#include "gen/hdrs/Gd__gd_core_items__LightGoobert.hpp"
#include "gen/hdrs/Gd__gd_core_items__Lightsaber.hpp"
#include "gen/hdrs/Gd__gd_core_items__LuckyBow.hpp"
#include "gen/hdrs/Gd__gd_core_items__LuckyClover.hpp"
#include "gen/hdrs/Gd__gd_core_items__LuckyPiggy.hpp"
#include "gen/hdrs/Gd__gd_core_items__MagicStaff.hpp"
#include "gen/hdrs/Gd__gd_core_items__MagicTorch.hpp"
#include "gen/hdrs/Gd__gd_core_items__ManaOrb.hpp"
#include "gen/hdrs/Gd__gd_core_items__ManaPotion.hpp"
#include "gen/hdrs/Gd__gd_core_items__Manathirst.hpp"
#include "gen/hdrs/Gd__gd_core_items__MoonShield.hpp"
#include "gen/hdrs/Gd__gd_core_items__MrStruggles.hpp"
#include "gen/hdrs/Gd__gd_core_items__Pan.hpp"
#include "gen/hdrs/Gd__gd_core_items__Pandamonium.hpp"
#include "gen/hdrs/Gd__gd_core_items__PestilenceFlask.hpp"
#include "gen/hdrs/Gd__gd_core_items__PiercingArrow.hpp"
#include "gen/hdrs/Gd__gd_core_items__Piggybank.hpp"
#include "gen/hdrs/Gd__gd_core_items__Pineapple.hpp"
#include "gen/hdrs/Gd__gd_core_items__PlatinCustomerCard.hpp"
#include "gen/hdrs/Gd__gd_core_items__PocketSand.hpp"
#include "gen/hdrs/Gd__gd_core_items__PoisonBow.hpp"
#include "gen/hdrs/Gd__gd_core_items__PoisonDagger.hpp"
#include "gen/hdrs/Gd__gd_core_items__PoisonGoobert.hpp"
#include "gen/hdrs/Gd__gd_core_items__PoisonIvy.hpp"
#include "gen/hdrs/Gd__gd_core_items__Potion.hpp"
#include "gen/hdrs/Gd__gd_core_items__PotionBelt.hpp"
#include "gen/hdrs/Gd__gd_core_items__Present.hpp"
#include "gen/hdrs/Gd__gd_core_items__ProtectivePurse.hpp"
#include "gen/hdrs/Gd__gd_core_items__Pumpkin.hpp"
#include "gen/hdrs/Gd__gd_core_items__RainbowGoobert.hpp"
#include "gen/hdrs/Gd__gd_core_items__RainbowGoobertRanger.hpp"
#include "gen/hdrs/Gd__gd_core_items__RangerBag.hpp"
#include "gen/hdrs/Gd__gd_core_items__RangerCollar.hpp"
#include "gen/hdrs/Gd__gd_core_items__RibSawBlade.hpp"
#include "gen/hdrs/Gd__gd_core_items__RubyChonk.hpp"
#include "gen/hdrs/Gd__gd_core_items__RubyEgg.hpp"
#include "gen/hdrs/Gd__gd_core_items__RubyWhelp.hpp"
#include "gen/hdrs/Gd__gd_core_items__Shield.hpp"
#include "gen/hdrs/Gd__gd_core_items__ShieldofValor.hpp"
#include "gen/hdrs/Gd__gd_core_items__Shovel.hpp"
#include "gen/hdrs/Gd__gd_core_items__Spear.hpp"
#include "gen/hdrs/Gd__gd_core_items__SpectralDagger.hpp"
#include "gen/hdrs/Gd__gd_core_items__SpikedShield.hpp"
#include "gen/hdrs/Gd__gd_core_items__StaffofUnhealing.hpp"
#include "gen/hdrs/Gd__gd_core_items__StaminaSack.hpp"
#include "gen/hdrs/Gd__gd_core_items__SteelGoobert.hpp"
#include "gen/hdrs/Gd__gd_core_items__Stone.hpp"
#include "gen/hdrs/Gd__gd_core_items__StoneHelm.hpp"
#include "gen/hdrs/Gd__gd_core_items__StoneSkinPotion.hpp"
#include "gen/hdrs/Gd__gd_core_items__StorageCoffin.hpp"
#include "gen/hdrs/Gd__gd_core_items__StrongDemonicFlask.hpp"
#include "gen/hdrs/Gd__gd_core_items__StrongHealthPotion.hpp"
#include "gen/hdrs/Gd__gd_core_items__StrongPestilenceFlask.hpp"
#include "gen/hdrs/Gd__gd_core_items__StrongStoneSkinPotion.hpp"
#include "gen/hdrs/Gd__gd_core_items__TheFool.hpp"
#include "gen/hdrs/Gd__gd_core_items__TheLovers.hpp"
#include "gen/hdrs/Gd__gd_core_items__ThornBow.hpp"
#include "gen/hdrs/Gd__gd_core_items__ThornWhip.hpp"
#include "gen/hdrs/Gd__gd_core_items__Torch.hpp"
#include "gen/hdrs/Gd__gd_core_items__VampiricArmor.hpp"
#include "gen/hdrs/Gd__gd_core_items__VampiricGloves.hpp"
#include "gen/hdrs/Gd__gd_core_items__VampiricScythe.hpp"
#include "gen/hdrs/Gd__gd_core_items__VillainSword.hpp"
#include "gen/hdrs/Gd__gd_core_items__WalrusTusk.hpp"
#include "gen/hdrs/Gd__gd_core_items__Weapon.hpp"
#include "gen/hdrs/Gd__gd_core_items__Whetstone.hpp"
#include "gen/hdrs/Gd__gd_core_items__White_EyesBlueDragon.hpp"
#include "gen/hdrs/Gd__gd_core_items__Wolpertinger.hpp"
#include "gen/hdrs/Gd__gd_core_items__WoodenBuckler.hpp"
#include "gen/hdrs/Gd__gd_core_items__WoodenSword.hpp"
#include "gen/hdrs/Gd__gd_core_items__YggdrasilLeaf.hpp"
int main(){
std::printf("{\"classes\":{");
std::printf("\"Gd__gd_core__AceofSpades\":[%zu,%zu]",sizeof(Gd__gd_core__AceofSpades),alignof(Gd__gd_core__AceofSpades));
std::printf(",\"Gd__gd_core__AcornCollar\":[%zu,%zu]",sizeof(Gd__gd_core__AcornCollar),alignof(Gd__gd_core__AcornCollar));
std::printf(",\"Gd__gd_core__ArtifactStoneCold\":[%zu,%zu]",sizeof(Gd__gd_core__ArtifactStoneCold),alignof(Gd__gd_core__ArtifactStoneCold));
std::printf(",\"Gd__gd_core__ArtifactStoneHeat\":[%zu,%zu]",sizeof(Gd__gd_core__ArtifactStoneHeat),alignof(Gd__gd_core__ArtifactStoneHeat));
std::printf(",\"Gd__gd_core__Bag\":[%zu,%zu]",sizeof(Gd__gd_core__Bag),alignof(Gd__gd_core__Bag));
std::printf(",\"Gd__gd_core__BagofStones\":[%zu,%zu]",sizeof(Gd__gd_core__BagofStones),alignof(Gd__gd_core__BagofStones));
std::printf(",\"Gd__gd_core__Banana\":[%zu,%zu]",sizeof(Gd__gd_core__Banana),alignof(Gd__gd_core__Banana));
std::printf(",\"Gd__gd_core__BloodAmulet\":[%zu,%zu]",sizeof(Gd__gd_core__BloodAmulet),alignof(Gd__gd_core__BloodAmulet));
std::printf(",\"Gd__gd_core__BloodGoobert\":[%zu,%zu]",sizeof(Gd__gd_core__BloodGoobert),alignof(Gd__gd_core__BloodGoobert));
std::printf(",\"Gd__gd_core__Bloodthorne\":[%zu,%zu]",sizeof(Gd__gd_core__Bloodthorne),alignof(Gd__gd_core__Bloodthorne));
std::printf(",\"Gd__gd_core__BloodyDagger\":[%zu,%zu]",sizeof(Gd__gd_core__BloodyDagger),alignof(Gd__gd_core__BloodyDagger));
std::printf(",\"Gd__gd_core__Blueberries\":[%zu,%zu]",sizeof(Gd__gd_core__Blueberries),alignof(Gd__gd_core__Blueberries));
std::printf(",\"Gd__gd_core__Bow\":[%zu,%zu]",sizeof(Gd__gd_core__Bow),alignof(Gd__gd_core__Bow));
std::printf(",\"Gd__gd_core__BowandArrow\":[%zu,%zu]",sizeof(Gd__gd_core__BowandArrow),alignof(Gd__gd_core__BowandArrow));
std::printf(",\"Gd__gd_core__BoxofRiches\":[%zu,%zu]",sizeof(Gd__gd_core__BoxofRiches),alignof(Gd__gd_core__BoxofRiches));
std::printf(",\"Gd__gd_core__Broom\":[%zu,%zu]",sizeof(Gd__gd_core__Broom),alignof(Gd__gd_core__Broom));
std::printf(",\"Gd__gd_core__BurningCoal\":[%zu,%zu]",sizeof(Gd__gd_core__BurningCoal),alignof(Gd__gd_core__BurningCoal));
std::printf(",\"Gd__gd_core__BurningTorch\":[%zu,%zu]",sizeof(Gd__gd_core__BurningTorch),alignof(Gd__gd_core__BurningTorch));
std::printf(",\"Gd__gd_core__Card\":[%zu,%zu]",sizeof(Gd__gd_core__Card),alignof(Gd__gd_core__Card));
std::printf(",\"Gd__gd_core__Carrot\":[%zu,%zu]",sizeof(Gd__gd_core__Carrot),alignof(Gd__gd_core__Carrot));
std::printf(",\"Gd__gd_core__CarrotGoobert\":[%zu,%zu]",sizeof(Gd__gd_core__CarrotGoobert),alignof(Gd__gd_core__CarrotGoobert));
std::printf(",\"Gd__gd_core__ClawsofAttack\":[%zu,%zu]",sizeof(Gd__gd_core__ClawsofAttack),alignof(Gd__gd_core__ClawsofAttack));
std::printf(",\"Gd__gd_core__CoreBuff\":[%zu,%zu]",sizeof(Gd__gd_core__CoreBuff),alignof(Gd__gd_core__CoreBuff));
std::printf(",\"Gd__gd_core__CoreBuff__INNER__TemporaryStacks\":[%zu,%zu]",sizeof(Gd__gd_core__CoreBuff__INNER__TemporaryStacks),alignof(Gd__gd_core__CoreBuff__INNER__TemporaryStacks));
std::printf(",\"Gd__gd_core__CoreCharacter\":[%zu,%zu]",sizeof(Gd__gd_core__CoreCharacter),alignof(Gd__gd_core__CoreCharacter));
std::printf(",\"Gd__gd_core__CoreCombat\":[%zu,%zu]",sizeof(Gd__gd_core__CoreCombat),alignof(Gd__gd_core__CoreCombat));
std::printf(",\"Gd__gd_core__CoreCombat__INNER__CoreItemSort\":[%zu,%zu]",sizeof(Gd__gd_core__CoreCombat__INNER__CoreItemSort),alignof(Gd__gd_core__CoreCombat__INNER__CoreItemSort));
std::printf(",\"Gd__gd_core__CoreCombatLog\":[%zu,%zu]",sizeof(Gd__gd_core__CoreCombatLog),alignof(Gd__gd_core__CoreCombatLog));
std::printf(",\"Gd__gd_core__CoreConst\":[%zu,%zu]",sizeof(Gd__gd_core__CoreConst),alignof(Gd__gd_core__CoreConst));
std::printf(",\"Gd__gd_core__CoreContext\":[%zu,%zu]",sizeof(Gd__gd_core__CoreContext),alignof(Gd__gd_core__CoreContext));
std::printf(",\"Gd__gd_core__CoreContext__INNER__NativeFlicker\":[%zu,%zu]",sizeof(Gd__gd_core__CoreContext__INNER__NativeFlicker),alignof(Gd__gd_core__CoreContext__INNER__NativeFlicker));
std::printf(",\"Gd__gd_core__CoreDamageResult\":[%zu,%zu]",sizeof(Gd__gd_core__CoreDamageResult),alignof(Gd__gd_core__CoreDamageResult));
std::printf(",\"Gd__gd_core__CoreDamageSource\":[%zu,%zu]",sizeof(Gd__gd_core__CoreDamageSource),alignof(Gd__gd_core__CoreDamageSource));
std::printf(",\"Gd__gd_core__CoreEvent\":[%zu,%zu]",sizeof(Gd__gd_core__CoreEvent),alignof(Gd__gd_core__CoreEvent));
std::printf(",\"Gd__gd_core__CoreEventBus\":[%zu,%zu]",sizeof(Gd__gd_core__CoreEventBus),alignof(Gd__gd_core__CoreEventBus));
std::printf(",\"Gd__gd_core__CoreGrid\":[%zu,%zu]",sizeof(Gd__gd_core__CoreGrid),alignof(Gd__gd_core__CoreGrid));
std::printf(",\"Gd__gd_core__CoreHooks\":[%zu,%zu]",sizeof(Gd__gd_core__CoreHooks),alignof(Gd__gd_core__CoreHooks));
std::printf(",\"Gd__gd_core__CoreItem\":[%zu,%zu]",sizeof(Gd__gd_core__CoreItem),alignof(Gd__gd_core__CoreItem));
std::printf(",\"Gd__gd_core__CoreItem__INNER__CoreElectricalCharge\":[%zu,%zu]",sizeof(Gd__gd_core__CoreItem__INNER__CoreElectricalCharge),alignof(Gd__gd_core__CoreItem__INNER__CoreElectricalCharge));
std::printf(",\"Gd__gd_core__CoreItem__INNER__CoreSignalConnection\":[%zu,%zu]",sizeof(Gd__gd_core__CoreItem__INNER__CoreSignalConnection),alignof(Gd__gd_core__CoreItem__INNER__CoreSignalConnection));
std::printf(",\"Gd__gd_core__CoreItemBook\":[%zu,%zu]",sizeof(Gd__gd_core__CoreItemBook),alignof(Gd__gd_core__CoreItemBook));
std::printf(",\"Gd__gd_core__CoreItemData\":[%zu,%zu]",sizeof(Gd__gd_core__CoreItemData),alignof(Gd__gd_core__CoreItemData));
std::printf(",\"Gd__gd_core__CoreRng\":[%zu,%zu]",sizeof(Gd__gd_core__CoreRng),alignof(Gd__gd_core__CoreRng));
std::printf(",\"Gd__gd_core__CoreRng__INNER__BalancedRange\":[%zu,%zu]",sizeof(Gd__gd_core__CoreRng__INNER__BalancedRange),alignof(Gd__gd_core__CoreRng__INNER__BalancedRange));
std::printf(",\"Gd__gd_core__CoreRng__INNER__BalancedRng\":[%zu,%zu]",sizeof(Gd__gd_core__CoreRng__INNER__BalancedRng),alignof(Gd__gd_core__CoreRng__INNER__BalancedRng));
std::printf(",\"Gd__gd_core__CoreTimer\":[%zu,%zu]",sizeof(Gd__gd_core__CoreTimer),alignof(Gd__gd_core__CoreTimer));
std::printf(",\"Gd__gd_core__CoreUtil\":[%zu,%zu]",sizeof(Gd__gd_core__CoreUtil),alignof(Gd__gd_core__CoreUtil));
std::printf(",\"Gd__gd_core__CoreUtil__INNER__DictSorter\":[%zu,%zu]",sizeof(Gd__gd_core__CoreUtil__INNER__DictSorter),alignof(Gd__gd_core__CoreUtil__INNER__DictSorter));
std::printf(",\"Gd__gd_core__CorruptedArmor\":[%zu,%zu]",sizeof(Gd__gd_core__CorruptedArmor),alignof(Gd__gd_core__CorruptedArmor));
std::printf(",\"Gd__gd_core__CritwoodStaff\":[%zu,%zu]",sizeof(Gd__gd_core__CritwoodStaff),alignof(Gd__gd_core__CritwoodStaff));
std::printf(",\"Gd__gd_core__Crossblades\":[%zu,%zu]",sizeof(Gd__gd_core__Crossblades),alignof(Gd__gd_core__Crossblades));
std::printf(",\"Gd__gd_core__Crown\":[%zu,%zu]",sizeof(Gd__gd_core__Crown),alignof(Gd__gd_core__Crown));
std::printf(",\"Gd__gd_core__CursedDagger\":[%zu,%zu]",sizeof(Gd__gd_core__CursedDagger),alignof(Gd__gd_core__CursedDagger));
std::printf(",\"Gd__gd_core__CursedHairComb\":[%zu,%zu]",sizeof(Gd__gd_core__CursedHairComb),alignof(Gd__gd_core__CursedHairComb));
std::printf(",\"Gd__gd_core__CustomerCard\":[%zu,%zu]",sizeof(Gd__gd_core__CustomerCard),alignof(Gd__gd_core__CustomerCard));
std::printf(",\"Gd__gd_core__Dagger\":[%zu,%zu]",sizeof(Gd__gd_core__Dagger),alignof(Gd__gd_core__Dagger));
std::printf(",\"Gd__gd_core__DancingDragon\":[%zu,%zu]",sizeof(Gd__gd_core__DancingDragon),alignof(Gd__gd_core__DancingDragon));
std::printf(",\"Gd__gd_core__DarkestLotus\":[%zu,%zu]",sizeof(Gd__gd_core__DarkestLotus),alignof(Gd__gd_core__DarkestLotus));
std::printf(",\"Gd__gd_core__Darksaber\":[%zu,%zu]",sizeof(Gd__gd_core__Darksaber),alignof(Gd__gd_core__Darksaber));
std::printf(",\"Gd__gd_core__DeathScythe\":[%zu,%zu]",sizeof(Gd__gd_core__DeathScythe),alignof(Gd__gd_core__DeathScythe));
std::printf(",\"Gd__gd_core__DeckofCards\":[%zu,%zu]",sizeof(Gd__gd_core__DeckofCards),alignof(Gd__gd_core__DeckofCards));
std::printf(",\"Gd__gd_core__DemonicFlask\":[%zu,%zu]",sizeof(Gd__gd_core__DemonicFlask),alignof(Gd__gd_core__DemonicFlask));
std::printf(",\"Gd__gd_core__DjinnLamp\":[%zu,%zu]",sizeof(Gd__gd_core__DjinnLamp),alignof(Gd__gd_core__DjinnLamp));
std::printf(",\"Gd__gd_core__DragonEgg\":[%zu,%zu]",sizeof(Gd__gd_core__DragonEgg),alignof(Gd__gd_core__DragonEgg));
std::printf(",\"Gd__gd_core__Eggscalibur\":[%zu,%zu]",sizeof(Gd__gd_core__Eggscalibur),alignof(Gd__gd_core__Eggscalibur));
std::printf(",\"Gd__gd_core__EvilCap\":[%zu,%zu]",sizeof(Gd__gd_core__EvilCap),alignof(Gd__gd_core__EvilCap));
std::printf(",\"Gd__gd_core__FalconBlade\":[%zu,%zu]",sizeof(Gd__gd_core__FalconBlade),alignof(Gd__gd_core__FalconBlade));
std::printf(",\"Gd__gd_core__FancyFencingRapier\":[%zu,%zu]",sizeof(Gd__gd_core__FancyFencingRapier),alignof(Gd__gd_core__FancyFencingRapier));
std::printf(",\"Gd__gd_core__Fanfare\":[%zu,%zu]",sizeof(Gd__gd_core__Fanfare),alignof(Gd__gd_core__Fanfare));
std::printf(",\"Gd__gd_core__FannyPack\":[%zu,%zu]",sizeof(Gd__gd_core__FannyPack),alignof(Gd__gd_core__FannyPack));
std::printf(",\"Gd__gd_core__Flute\":[%zu,%zu]",sizeof(Gd__gd_core__Flute),alignof(Gd__gd_core__Flute));
std::printf(",\"Gd__gd_core__FlyAgaric\":[%zu,%zu]",sizeof(Gd__gd_core__FlyAgaric),alignof(Gd__gd_core__FlyAgaric));
std::printf(",\"Gd__gd_core__Food\":[%zu,%zu]",sizeof(Gd__gd_core__Food),alignof(Gd__gd_core__Food));
std::printf(",\"Gd__gd_core__Garlic\":[%zu,%zu]",sizeof(Gd__gd_core__Garlic),alignof(Gd__gd_core__Garlic));
std::printf(",\"Gd__gd_core__GingerbreadMan\":[%zu,%zu]",sizeof(Gd__gd_core__GingerbreadMan),alignof(Gd__gd_core__GingerbreadMan));
std::printf(",\"Gd__gd_core__GlovesofHaste\":[%zu,%zu]",sizeof(Gd__gd_core__GlovesofHaste),alignof(Gd__gd_core__GlovesofHaste));
std::printf(",\"Gd__gd_core__Goobert\":[%zu,%zu]",sizeof(Gd__gd_core__Goobert),alignof(Gd__gd_core__Goobert));
std::printf(",\"Gd__gd_core__Greatsword\":[%zu,%zu]",sizeof(Gd__gd_core__Greatsword),alignof(Gd__gd_core__Greatsword));
std::printf(",\"Gd__gd_core__Hammer\":[%zu,%zu]",sizeof(Gd__gd_core__Hammer),alignof(Gd__gd_core__Hammer));
std::printf(",\"Gd__gd_core__HealingHerbs\":[%zu,%zu]",sizeof(Gd__gd_core__HealingHerbs),alignof(Gd__gd_core__HealingHerbs));
std::printf(",\"Gd__gd_core__HealthPotion\":[%zu,%zu]",sizeof(Gd__gd_core__HealthPotion),alignof(Gd__gd_core__HealthPotion));
std::printf(",\"Gd__gd_core__HeartContainer\":[%zu,%zu]",sizeof(Gd__gd_core__HeartContainer),alignof(Gd__gd_core__HeartContainer));
std::printf(",\"Gd__gd_core__HeartofDarkness\":[%zu,%zu]",sizeof(Gd__gd_core__HeartofDarkness),alignof(Gd__gd_core__HeartofDarkness));
std::printf(",\"Gd__gd_core__HeroicPotion\":[%zu,%zu]",sizeof(Gd__gd_core__HeroicPotion),alignof(Gd__gd_core__HeroicPotion));
std::printf(",\"Gd__gd_core__HeroLongsword\":[%zu,%zu]",sizeof(Gd__gd_core__HeroLongsword),alignof(Gd__gd_core__HeroLongsword));
std::printf(",\"Gd__gd_core__HeroSword\":[%zu,%zu]",sizeof(Gd__gd_core__HeroSword),alignof(Gd__gd_core__HeroSword));
std::printf(",\"Gd__gd_core__HoloFireLizard\":[%zu,%zu]",sizeof(Gd__gd_core__HoloFireLizard),alignof(Gd__gd_core__HoloFireLizard));
std::printf(",\"Gd__gd_core__HolyArmor\":[%zu,%zu]",sizeof(Gd__gd_core__HolyArmor),alignof(Gd__gd_core__HolyArmor));
std::printf(",\"Gd__gd_core__HolySpear\":[%zu,%zu]",sizeof(Gd__gd_core__HolySpear),alignof(Gd__gd_core__HolySpear));
std::printf(",\"Gd__gd_core__HungryBlade\":[%zu,%zu]",sizeof(Gd__gd_core__HungryBlade),alignof(Gd__gd_core__HungryBlade));
std::printf(",\"Gd__gd_core__Item\":[%zu,%zu]",sizeof(Gd__gd_core__Item),alignof(Gd__gd_core__Item));
std::printf(",\"Gd__gd_core__Item__INNER__SignalConnection\":[%zu,%zu]",sizeof(Gd__gd_core__Item__INNER__SignalConnection),alignof(Gd__gd_core__Item__INNER__SignalConnection));
std::printf(",\"Gd__gd_core__Jynxtorquilla\":[%zu,%zu]",sizeof(Gd__gd_core__Jynxtorquilla),alignof(Gd__gd_core__Jynxtorquilla));
std::printf(",\"Gd__gd_core__LeatherArmor\":[%zu,%zu]",sizeof(Gd__gd_core__LeatherArmor),alignof(Gd__gd_core__LeatherArmor));
std::printf(",\"Gd__gd_core__LeatherBoots\":[%zu,%zu]",sizeof(Gd__gd_core__LeatherBoots),alignof(Gd__gd_core__LeatherBoots));
std::printf(",\"Gd__gd_core__LeatherHelm\":[%zu,%zu]",sizeof(Gd__gd_core__LeatherHelm),alignof(Gd__gd_core__LeatherHelm));
std::printf(",\"Gd__gd_core__LightGoobert\":[%zu,%zu]",sizeof(Gd__gd_core__LightGoobert),alignof(Gd__gd_core__LightGoobert));
std::printf(",\"Gd__gd_core__Lightsaber\":[%zu,%zu]",sizeof(Gd__gd_core__Lightsaber),alignof(Gd__gd_core__Lightsaber));
std::printf(",\"Gd__gd_core__LuckyBow\":[%zu,%zu]",sizeof(Gd__gd_core__LuckyBow),alignof(Gd__gd_core__LuckyBow));
std::printf(",\"Gd__gd_core__LuckyClover\":[%zu,%zu]",sizeof(Gd__gd_core__LuckyClover),alignof(Gd__gd_core__LuckyClover));
std::printf(",\"Gd__gd_core__LuckyPiggy\":[%zu,%zu]",sizeof(Gd__gd_core__LuckyPiggy),alignof(Gd__gd_core__LuckyPiggy));
std::printf(",\"Gd__gd_core__MagicStaff\":[%zu,%zu]",sizeof(Gd__gd_core__MagicStaff),alignof(Gd__gd_core__MagicStaff));
std::printf(",\"Gd__gd_core__MagicTorch\":[%zu,%zu]",sizeof(Gd__gd_core__MagicTorch),alignof(Gd__gd_core__MagicTorch));
std::printf(",\"Gd__gd_core__ManaOrb\":[%zu,%zu]",sizeof(Gd__gd_core__ManaOrb),alignof(Gd__gd_core__ManaOrb));
std::printf(",\"Gd__gd_core__ManaPotion\":[%zu,%zu]",sizeof(Gd__gd_core__ManaPotion),alignof(Gd__gd_core__ManaPotion));
std::printf(",\"Gd__gd_core__Manathirst\":[%zu,%zu]",sizeof(Gd__gd_core__Manathirst),alignof(Gd__gd_core__Manathirst));
std::printf(",\"Gd__gd_core__MoonShield\":[%zu,%zu]",sizeof(Gd__gd_core__MoonShield),alignof(Gd__gd_core__MoonShield));
std::printf(",\"Gd__gd_core__MrStruggles\":[%zu,%zu]",sizeof(Gd__gd_core__MrStruggles),alignof(Gd__gd_core__MrStruggles));
std::printf(",\"Gd__gd_core__Pan\":[%zu,%zu]",sizeof(Gd__gd_core__Pan),alignof(Gd__gd_core__Pan));
std::printf(",\"Gd__gd_core__Pandamonium\":[%zu,%zu]",sizeof(Gd__gd_core__Pandamonium),alignof(Gd__gd_core__Pandamonium));
std::printf(",\"Gd__gd_core__PestilenceFlask\":[%zu,%zu]",sizeof(Gd__gd_core__PestilenceFlask),alignof(Gd__gd_core__PestilenceFlask));
std::printf(",\"Gd__gd_core__PiercingArrow\":[%zu,%zu]",sizeof(Gd__gd_core__PiercingArrow),alignof(Gd__gd_core__PiercingArrow));
std::printf(",\"Gd__gd_core__Piggybank\":[%zu,%zu]",sizeof(Gd__gd_core__Piggybank),alignof(Gd__gd_core__Piggybank));
std::printf(",\"Gd__gd_core__Pineapple\":[%zu,%zu]",sizeof(Gd__gd_core__Pineapple),alignof(Gd__gd_core__Pineapple));
std::printf(",\"Gd__gd_core__PlatinCustomerCard\":[%zu,%zu]",sizeof(Gd__gd_core__PlatinCustomerCard),alignof(Gd__gd_core__PlatinCustomerCard));
std::printf(",\"Gd__gd_core__PocketSand\":[%zu,%zu]",sizeof(Gd__gd_core__PocketSand),alignof(Gd__gd_core__PocketSand));
std::printf(",\"Gd__gd_core__PoisonBow\":[%zu,%zu]",sizeof(Gd__gd_core__PoisonBow),alignof(Gd__gd_core__PoisonBow));
std::printf(",\"Gd__gd_core__PoisonDagger\":[%zu,%zu]",sizeof(Gd__gd_core__PoisonDagger),alignof(Gd__gd_core__PoisonDagger));
std::printf(",\"Gd__gd_core__PoisonGoobert\":[%zu,%zu]",sizeof(Gd__gd_core__PoisonGoobert),alignof(Gd__gd_core__PoisonGoobert));
std::printf(",\"Gd__gd_core__PoisonIvy\":[%zu,%zu]",sizeof(Gd__gd_core__PoisonIvy),alignof(Gd__gd_core__PoisonIvy));
std::printf(",\"Gd__gd_core__Potion\":[%zu,%zu]",sizeof(Gd__gd_core__Potion),alignof(Gd__gd_core__Potion));
std::printf(",\"Gd__gd_core__PotionBelt\":[%zu,%zu]",sizeof(Gd__gd_core__PotionBelt),alignof(Gd__gd_core__PotionBelt));
std::printf(",\"Gd__gd_core__Present\":[%zu,%zu]",sizeof(Gd__gd_core__Present),alignof(Gd__gd_core__Present));
std::printf(",\"Gd__gd_core__ProtectivePurse\":[%zu,%zu]",sizeof(Gd__gd_core__ProtectivePurse),alignof(Gd__gd_core__ProtectivePurse));
std::printf(",\"Gd__gd_core__Pumpkin\":[%zu,%zu]",sizeof(Gd__gd_core__Pumpkin),alignof(Gd__gd_core__Pumpkin));
std::printf(",\"Gd__gd_core__RainbowGoobert\":[%zu,%zu]",sizeof(Gd__gd_core__RainbowGoobert),alignof(Gd__gd_core__RainbowGoobert));
std::printf(",\"Gd__gd_core__RainbowGoobertRanger\":[%zu,%zu]",sizeof(Gd__gd_core__RainbowGoobertRanger),alignof(Gd__gd_core__RainbowGoobertRanger));
std::printf(",\"Gd__gd_core__RangerBag\":[%zu,%zu]",sizeof(Gd__gd_core__RangerBag),alignof(Gd__gd_core__RangerBag));
std::printf(",\"Gd__gd_core__RangerCollar\":[%zu,%zu]",sizeof(Gd__gd_core__RangerCollar),alignof(Gd__gd_core__RangerCollar));
std::printf(",\"Gd__gd_core__RibSawBlade\":[%zu,%zu]",sizeof(Gd__gd_core__RibSawBlade),alignof(Gd__gd_core__RibSawBlade));
std::printf(",\"Gd__gd_core__RubyChonk\":[%zu,%zu]",sizeof(Gd__gd_core__RubyChonk),alignof(Gd__gd_core__RubyChonk));
std::printf(",\"Gd__gd_core__RubyEgg\":[%zu,%zu]",sizeof(Gd__gd_core__RubyEgg),alignof(Gd__gd_core__RubyEgg));
std::printf(",\"Gd__gd_core__RubyWhelp\":[%zu,%zu]",sizeof(Gd__gd_core__RubyWhelp),alignof(Gd__gd_core__RubyWhelp));
std::printf(",\"Gd__gd_core__Shield\":[%zu,%zu]",sizeof(Gd__gd_core__Shield),alignof(Gd__gd_core__Shield));
std::printf(",\"Gd__gd_core__ShieldofValor\":[%zu,%zu]",sizeof(Gd__gd_core__ShieldofValor),alignof(Gd__gd_core__ShieldofValor));
std::printf(",\"Gd__gd_core__Shovel\":[%zu,%zu]",sizeof(Gd__gd_core__Shovel),alignof(Gd__gd_core__Shovel));
std::printf(",\"Gd__gd_core__Spear\":[%zu,%zu]",sizeof(Gd__gd_core__Spear),alignof(Gd__gd_core__Spear));
std::printf(",\"Gd__gd_core__SpectralDagger\":[%zu,%zu]",sizeof(Gd__gd_core__SpectralDagger),alignof(Gd__gd_core__SpectralDagger));
std::printf(",\"Gd__gd_core__SpikedShield\":[%zu,%zu]",sizeof(Gd__gd_core__SpikedShield),alignof(Gd__gd_core__SpikedShield));
std::printf(",\"Gd__gd_core__StaffofUnhealing\":[%zu,%zu]",sizeof(Gd__gd_core__StaffofUnhealing),alignof(Gd__gd_core__StaffofUnhealing));
std::printf(",\"Gd__gd_core__StaminaSack\":[%zu,%zu]",sizeof(Gd__gd_core__StaminaSack),alignof(Gd__gd_core__StaminaSack));
std::printf(",\"Gd__gd_core__SteelGoobert\":[%zu,%zu]",sizeof(Gd__gd_core__SteelGoobert),alignof(Gd__gd_core__SteelGoobert));
std::printf(",\"Gd__gd_core__Stone\":[%zu,%zu]",sizeof(Gd__gd_core__Stone),alignof(Gd__gd_core__Stone));
std::printf(",\"Gd__gd_core__StoneHelm\":[%zu,%zu]",sizeof(Gd__gd_core__StoneHelm),alignof(Gd__gd_core__StoneHelm));
std::printf(",\"Gd__gd_core__StoneSkinPotion\":[%zu,%zu]",sizeof(Gd__gd_core__StoneSkinPotion),alignof(Gd__gd_core__StoneSkinPotion));
std::printf(",\"Gd__gd_core__StorageCoffin\":[%zu,%zu]",sizeof(Gd__gd_core__StorageCoffin),alignof(Gd__gd_core__StorageCoffin));
std::printf(",\"Gd__gd_core__StrongDemonicFlask\":[%zu,%zu]",sizeof(Gd__gd_core__StrongDemonicFlask),alignof(Gd__gd_core__StrongDemonicFlask));
std::printf(",\"Gd__gd_core__StrongHealthPotion\":[%zu,%zu]",sizeof(Gd__gd_core__StrongHealthPotion),alignof(Gd__gd_core__StrongHealthPotion));
std::printf(",\"Gd__gd_core__StrongPestilenceFlask\":[%zu,%zu]",sizeof(Gd__gd_core__StrongPestilenceFlask),alignof(Gd__gd_core__StrongPestilenceFlask));
std::printf(",\"Gd__gd_core__StrongStoneSkinPotion\":[%zu,%zu]",sizeof(Gd__gd_core__StrongStoneSkinPotion),alignof(Gd__gd_core__StrongStoneSkinPotion));
std::printf(",\"Gd__gd_core__TheFool\":[%zu,%zu]",sizeof(Gd__gd_core__TheFool),alignof(Gd__gd_core__TheFool));
std::printf(",\"Gd__gd_core__TheLovers\":[%zu,%zu]",sizeof(Gd__gd_core__TheLovers),alignof(Gd__gd_core__TheLovers));
std::printf(",\"Gd__gd_core__ThornBow\":[%zu,%zu]",sizeof(Gd__gd_core__ThornBow),alignof(Gd__gd_core__ThornBow));
std::printf(",\"Gd__gd_core__ThornWhip\":[%zu,%zu]",sizeof(Gd__gd_core__ThornWhip),alignof(Gd__gd_core__ThornWhip));
std::printf(",\"Gd__gd_core__Torch\":[%zu,%zu]",sizeof(Gd__gd_core__Torch),alignof(Gd__gd_core__Torch));
std::printf(",\"Gd__gd_core__VampiricArmor\":[%zu,%zu]",sizeof(Gd__gd_core__VampiricArmor),alignof(Gd__gd_core__VampiricArmor));
std::printf(",\"Gd__gd_core__VampiricGloves\":[%zu,%zu]",sizeof(Gd__gd_core__VampiricGloves),alignof(Gd__gd_core__VampiricGloves));
std::printf(",\"Gd__gd_core__VampiricScythe\":[%zu,%zu]",sizeof(Gd__gd_core__VampiricScythe),alignof(Gd__gd_core__VampiricScythe));
std::printf(",\"Gd__gd_core__VillainSword\":[%zu,%zu]",sizeof(Gd__gd_core__VillainSword),alignof(Gd__gd_core__VillainSword));
std::printf(",\"Gd__gd_core__WalrusTusk\":[%zu,%zu]",sizeof(Gd__gd_core__WalrusTusk),alignof(Gd__gd_core__WalrusTusk));
std::printf(",\"Gd__gd_core__Weapon\":[%zu,%zu]",sizeof(Gd__gd_core__Weapon),alignof(Gd__gd_core__Weapon));
std::printf(",\"Gd__gd_core__Whetstone\":[%zu,%zu]",sizeof(Gd__gd_core__Whetstone),alignof(Gd__gd_core__Whetstone));
std::printf(",\"Gd__gd_core__White_EyesBlueDragon\":[%zu,%zu]",sizeof(Gd__gd_core__White_EyesBlueDragon),alignof(Gd__gd_core__White_EyesBlueDragon));
std::printf(",\"Gd__gd_core__Wolpertinger\":[%zu,%zu]",sizeof(Gd__gd_core__Wolpertinger),alignof(Gd__gd_core__Wolpertinger));
std::printf(",\"Gd__gd_core__WoodenBuckler\":[%zu,%zu]",sizeof(Gd__gd_core__WoodenBuckler),alignof(Gd__gd_core__WoodenBuckler));
std::printf(",\"Gd__gd_core__WoodenSword\":[%zu,%zu]",sizeof(Gd__gd_core__WoodenSword),alignof(Gd__gd_core__WoodenSword));
std::printf(",\"Gd__gd_core__YggdrasilLeaf\":[%zu,%zu]",sizeof(Gd__gd_core__YggdrasilLeaf),alignof(Gd__gd_core__YggdrasilLeaf));
std::printf(",\"Gd__gd_core_items__AceofSpades\":[%zu,%zu]",sizeof(Gd__gd_core_items__AceofSpades),alignof(Gd__gd_core_items__AceofSpades));
std::printf(",\"Gd__gd_core_items__AcornCollar\":[%zu,%zu]",sizeof(Gd__gd_core_items__AcornCollar),alignof(Gd__gd_core_items__AcornCollar));
std::printf(",\"Gd__gd_core_items__ArtifactStoneCold\":[%zu,%zu]",sizeof(Gd__gd_core_items__ArtifactStoneCold),alignof(Gd__gd_core_items__ArtifactStoneCold));
std::printf(",\"Gd__gd_core_items__ArtifactStoneHeat\":[%zu,%zu]",sizeof(Gd__gd_core_items__ArtifactStoneHeat),alignof(Gd__gd_core_items__ArtifactStoneHeat));
std::printf(",\"Gd__gd_core_items__Bag\":[%zu,%zu]",sizeof(Gd__gd_core_items__Bag),alignof(Gd__gd_core_items__Bag));
std::printf(",\"Gd__gd_core_items__BagofStones\":[%zu,%zu]",sizeof(Gd__gd_core_items__BagofStones),alignof(Gd__gd_core_items__BagofStones));
std::printf(",\"Gd__gd_core_items__Banana\":[%zu,%zu]",sizeof(Gd__gd_core_items__Banana),alignof(Gd__gd_core_items__Banana));
std::printf(",\"Gd__gd_core_items__BloodAmulet\":[%zu,%zu]",sizeof(Gd__gd_core_items__BloodAmulet),alignof(Gd__gd_core_items__BloodAmulet));
std::printf(",\"Gd__gd_core_items__BloodGoobert\":[%zu,%zu]",sizeof(Gd__gd_core_items__BloodGoobert),alignof(Gd__gd_core_items__BloodGoobert));
std::printf(",\"Gd__gd_core_items__Bloodthorne\":[%zu,%zu]",sizeof(Gd__gd_core_items__Bloodthorne),alignof(Gd__gd_core_items__Bloodthorne));
std::printf(",\"Gd__gd_core_items__BloodyDagger\":[%zu,%zu]",sizeof(Gd__gd_core_items__BloodyDagger),alignof(Gd__gd_core_items__BloodyDagger));
std::printf(",\"Gd__gd_core_items__Blueberries\":[%zu,%zu]",sizeof(Gd__gd_core_items__Blueberries),alignof(Gd__gd_core_items__Blueberries));
std::printf(",\"Gd__gd_core_items__Bow\":[%zu,%zu]",sizeof(Gd__gd_core_items__Bow),alignof(Gd__gd_core_items__Bow));
std::printf(",\"Gd__gd_core_items__BowandArrow\":[%zu,%zu]",sizeof(Gd__gd_core_items__BowandArrow),alignof(Gd__gd_core_items__BowandArrow));
std::printf(",\"Gd__gd_core_items__BoxofRiches\":[%zu,%zu]",sizeof(Gd__gd_core_items__BoxofRiches),alignof(Gd__gd_core_items__BoxofRiches));
std::printf(",\"Gd__gd_core_items__Broom\":[%zu,%zu]",sizeof(Gd__gd_core_items__Broom),alignof(Gd__gd_core_items__Broom));
std::printf(",\"Gd__gd_core_items__BurningCoal\":[%zu,%zu]",sizeof(Gd__gd_core_items__BurningCoal),alignof(Gd__gd_core_items__BurningCoal));
std::printf(",\"Gd__gd_core_items__BurningTorch\":[%zu,%zu]",sizeof(Gd__gd_core_items__BurningTorch),alignof(Gd__gd_core_items__BurningTorch));
std::printf(",\"Gd__gd_core_items__Card\":[%zu,%zu]",sizeof(Gd__gd_core_items__Card),alignof(Gd__gd_core_items__Card));
std::printf(",\"Gd__gd_core_items__Carrot\":[%zu,%zu]",sizeof(Gd__gd_core_items__Carrot),alignof(Gd__gd_core_items__Carrot));
std::printf(",\"Gd__gd_core_items__CarrotGoobert\":[%zu,%zu]",sizeof(Gd__gd_core_items__CarrotGoobert),alignof(Gd__gd_core_items__CarrotGoobert));
std::printf(",\"Gd__gd_core_items__ClawsofAttack\":[%zu,%zu]",sizeof(Gd__gd_core_items__ClawsofAttack),alignof(Gd__gd_core_items__ClawsofAttack));
std::printf(",\"Gd__gd_core_items__Coins\":[%zu,%zu]",sizeof(Gd__gd_core_items__Coins),alignof(Gd__gd_core_items__Coins));
std::printf(",\"Gd__gd_core_items__CorruptedArmor\":[%zu,%zu]",sizeof(Gd__gd_core_items__CorruptedArmor),alignof(Gd__gd_core_items__CorruptedArmor));
std::printf(",\"Gd__gd_core_items__CritwoodStaff\":[%zu,%zu]",sizeof(Gd__gd_core_items__CritwoodStaff),alignof(Gd__gd_core_items__CritwoodStaff));
std::printf(",\"Gd__gd_core_items__Crossblades\":[%zu,%zu]",sizeof(Gd__gd_core_items__Crossblades),alignof(Gd__gd_core_items__Crossblades));
std::printf(",\"Gd__gd_core_items__Crown\":[%zu,%zu]",sizeof(Gd__gd_core_items__Crown),alignof(Gd__gd_core_items__Crown));
std::printf(",\"Gd__gd_core_items__CursedDagger\":[%zu,%zu]",sizeof(Gd__gd_core_items__CursedDagger),alignof(Gd__gd_core_items__CursedDagger));
std::printf(",\"Gd__gd_core_items__CursedHairComb\":[%zu,%zu]",sizeof(Gd__gd_core_items__CursedHairComb),alignof(Gd__gd_core_items__CursedHairComb));
std::printf(",\"Gd__gd_core_items__CustomerCard\":[%zu,%zu]",sizeof(Gd__gd_core_items__CustomerCard),alignof(Gd__gd_core_items__CustomerCard));
std::printf(",\"Gd__gd_core_items__Dagger\":[%zu,%zu]",sizeof(Gd__gd_core_items__Dagger),alignof(Gd__gd_core_items__Dagger));
std::printf(",\"Gd__gd_core_items__DancingDragon\":[%zu,%zu]",sizeof(Gd__gd_core_items__DancingDragon),alignof(Gd__gd_core_items__DancingDragon));
std::printf(",\"Gd__gd_core_items__DarkestLotus\":[%zu,%zu]",sizeof(Gd__gd_core_items__DarkestLotus),alignof(Gd__gd_core_items__DarkestLotus));
std::printf(",\"Gd__gd_core_items__Darksaber\":[%zu,%zu]",sizeof(Gd__gd_core_items__Darksaber),alignof(Gd__gd_core_items__Darksaber));
std::printf(",\"Gd__gd_core_items__DeathScythe\":[%zu,%zu]",sizeof(Gd__gd_core_items__DeathScythe),alignof(Gd__gd_core_items__DeathScythe));
std::printf(",\"Gd__gd_core_items__DeckofCards\":[%zu,%zu]",sizeof(Gd__gd_core_items__DeckofCards),alignof(Gd__gd_core_items__DeckofCards));
std::printf(",\"Gd__gd_core_items__DemonicFlask\":[%zu,%zu]",sizeof(Gd__gd_core_items__DemonicFlask),alignof(Gd__gd_core_items__DemonicFlask));
std::printf(",\"Gd__gd_core_items__DjinnLamp\":[%zu,%zu]",sizeof(Gd__gd_core_items__DjinnLamp),alignof(Gd__gd_core_items__DjinnLamp));
std::printf(",\"Gd__gd_core_items__DragonEgg\":[%zu,%zu]",sizeof(Gd__gd_core_items__DragonEgg),alignof(Gd__gd_core_items__DragonEgg));
std::printf(",\"Gd__gd_core_items__Eggscalibur\":[%zu,%zu]",sizeof(Gd__gd_core_items__Eggscalibur),alignof(Gd__gd_core_items__Eggscalibur));
std::printf(",\"Gd__gd_core_items__EvilCap\":[%zu,%zu]",sizeof(Gd__gd_core_items__EvilCap),alignof(Gd__gd_core_items__EvilCap));
std::printf(",\"Gd__gd_core_items__Exclusive__AcornAce\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__AcornAce),alignof(Gd__gd_core_items__Exclusive__AcornAce));
std::printf(",\"Gd__gd_core_items__Exclusive__AmethystEgg\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__AmethystEgg),alignof(Gd__gd_core_items__Exclusive__AmethystEgg));
std::printf(",\"Gd__gd_core_items__Exclusive__AmethystWhelp\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__AmethystWhelp),alignof(Gd__gd_core_items__Exclusive__AmethystWhelp));
std::printf(",\"Gd__gd_core_items__Exclusive__AmuletofAgility\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__AmuletofAgility),alignof(Gd__gd_core_items__Exclusive__AmuletofAgility));
std::printf(",\"Gd__gd_core_items__Exclusive__AmuletofAlchemy\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__AmuletofAlchemy),alignof(Gd__gd_core_items__Exclusive__AmuletofAlchemy));
std::printf(",\"Gd__gd_core_items__Exclusive__AmuletofDarkness\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__AmuletofDarkness),alignof(Gd__gd_core_items__Exclusive__AmuletofDarkness));
std::printf(",\"Gd__gd_core_items__Exclusive__AmuletofFeasting\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__AmuletofFeasting),alignof(Gd__gd_core_items__Exclusive__AmuletofFeasting));
std::printf(",\"Gd__gd_core_items__Exclusive__AmuletofFortune\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__AmuletofFortune),alignof(Gd__gd_core_items__Exclusive__AmuletofFortune));
std::printf(",\"Gd__gd_core_items__Exclusive__AmuletofLife\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__AmuletofLife),alignof(Gd__gd_core_items__Exclusive__AmuletofLife));
std::printf(",\"Gd__gd_core_items__Exclusive__AmuletofLight\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__AmuletofLight),alignof(Gd__gd_core_items__Exclusive__AmuletofLight));
std::printf(",\"Gd__gd_core_items__Exclusive__AmuletofSteel\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__AmuletofSteel),alignof(Gd__gd_core_items__Exclusive__AmuletofSteel));
std::printf(",\"Gd__gd_core_items__Exclusive__AmuletoftheWild\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__AmuletoftheWild),alignof(Gd__gd_core_items__Exclusive__AmuletoftheWild));
std::printf(",\"Gd__gd_core_items__Exclusive__AmuletUnidentified\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__AmuletUnidentified),alignof(Gd__gd_core_items__Exclusive__AmuletUnidentified));
std::printf(",\"Gd__gd_core_items__Exclusive__AngelCrystal\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__AngelCrystal),alignof(Gd__gd_core_items__Exclusive__AngelCrystal));
std::printf(",\"Gd__gd_core_items__Exclusive__Anvil\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Anvil),alignof(Gd__gd_core_items__Exclusive__Anvil));
std::printf(",\"Gd__gd_core_items__Exclusive__ArcaneBoots\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__ArcaneBoots),alignof(Gd__gd_core_items__Exclusive__ArcaneBoots));
std::printf(",\"Gd__gd_core_items__Exclusive__ArcaneIntellect\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__ArcaneIntellect),alignof(Gd__gd_core_items__Exclusive__ArcaneIntellect));
std::printf(",\"Gd__gd_core_items__Exclusive__ArmoredCouragePuppy\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__ArmoredCouragePuppy),alignof(Gd__gd_core_items__Exclusive__ArmoredCouragePuppy));
std::printf(",\"Gd__gd_core_items__Exclusive__ArmoredPowerPuppy\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__ArmoredPowerPuppy),alignof(Gd__gd_core_items__Exclusive__ArmoredPowerPuppy));
std::printf(",\"Gd__gd_core_items__Exclusive__ArmoredWisdomPuppy\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__ArmoredWisdomPuppy),alignof(Gd__gd_core_items__Exclusive__ArmoredWisdomPuppy));
std::printf(",\"Gd__gd_core_items__Exclusive__ArtifactStoneDeath\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__ArtifactStoneDeath),alignof(Gd__gd_core_items__Exclusive__ArtifactStoneDeath));
std::printf(",\"Gd__gd_core_items__Exclusive__Automanaton\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Automanaton),alignof(Gd__gd_core_items__Exclusive__Automanaton));
std::printf(",\"Gd__gd_core_items__Exclusive__Axe\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Axe),alignof(Gd__gd_core_items__Exclusive__Axe));
std::printf(",\"Gd__gd_core_items__Exclusive__BadgerRune\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__BadgerRune),alignof(Gd__gd_core_items__Exclusive__BadgerRune));
std::printf(",\"Gd__gd_core_items__Exclusive__BadgerSpirit\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__BadgerSpirit),alignof(Gd__gd_core_items__Exclusive__BadgerSpirit));
std::printf(",\"Gd__gd_core_items__Exclusive__BagofGiving\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__BagofGiving),alignof(Gd__gd_core_items__Exclusive__BagofGiving));
std::printf(",\"Gd__gd_core_items__Exclusive__Bagtacular\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Bagtacular),alignof(Gd__gd_core_items__Exclusive__Bagtacular));
std::printf(",\"Gd__gd_core_items__Exclusive__Battery\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Battery),alignof(Gd__gd_core_items__Exclusive__Battery));
std::printf(",\"Gd__gd_core_items__Exclusive__Bazooka\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Bazooka),alignof(Gd__gd_core_items__Exclusive__Bazooka));
std::printf(",\"Gd__gd_core_items__Exclusive__BerserkerBag\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__BerserkerBag),alignof(Gd__gd_core_items__Exclusive__BerserkerBag));
std::printf(",\"Gd__gd_core_items__Exclusive__Bewitchment\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Bewitchment),alignof(Gd__gd_core_items__Exclusive__Bewitchment));
std::printf(",\"Gd__gd_core_items__Exclusive__BigBloodthorne\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__BigBloodthorne),alignof(Gd__gd_core_items__Exclusive__BigBloodthorne));
std::printf(",\"Gd__gd_core_items__Exclusive__BionicArmor\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__BionicArmor),alignof(Gd__gd_core_items__Exclusive__BionicArmor));
std::printf(",\"Gd__gd_core_items__Exclusive__BismuthCube\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__BismuthCube),alignof(Gd__gd_core_items__Exclusive__BismuthCube));
std::printf(",\"Gd__gd_core_items__Exclusive__BloodManipulation\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__BloodManipulation),alignof(Gd__gd_core_items__Exclusive__BloodManipulation));
std::printf(",\"Gd__gd_core_items__Exclusive__Bomb\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Bomb),alignof(Gd__gd_core_items__Exclusive__Bomb));
std::printf(",\"Gd__gd_core_items__Exclusive__BookofBasics\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__BookofBasics),alignof(Gd__gd_core_items__Exclusive__BookofBasics));
std::printf(",\"Gd__gd_core_items__Exclusive__BookofDarkness\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__BookofDarkness),alignof(Gd__gd_core_items__Exclusive__BookofDarkness));
std::printf(",\"Gd__gd_core_items__Exclusive__BookofIce\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__BookofIce),alignof(Gd__gd_core_items__Exclusive__BookofIce));
std::printf(",\"Gd__gd_core_items__Exclusive__BookofLight\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__BookofLight),alignof(Gd__gd_core_items__Exclusive__BookofLight));
std::printf(",\"Gd__gd_core_items__Exclusive__BookofNature\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__BookofNature),alignof(Gd__gd_core_items__Exclusive__BookofNature));
std::printf(",\"Gd__gd_core_items__Exclusive__Boomerang\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Boomerang),alignof(Gd__gd_core_items__Exclusive__Boomerang));
std::printf(",\"Gd__gd_core_items__Exclusive__BowlofTreats\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__BowlofTreats),alignof(Gd__gd_core_items__Exclusive__BowlofTreats));
std::printf(",\"Gd__gd_core_items__Exclusive__BoxofProsperity\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__BoxofProsperity),alignof(Gd__gd_core_items__Exclusive__BoxofProsperity));
std::printf(",\"Gd__gd_core_items__Exclusive__BrassKnuckles\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__BrassKnuckles),alignof(Gd__gd_core_items__Exclusive__BrassKnuckles));
std::printf(",\"Gd__gd_core_items__Exclusive__Broccoli\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Broccoli),alignof(Gd__gd_core_items__Exclusive__Broccoli));
std::printf(",\"Gd__gd_core_items__Exclusive__BroccoliGoobert\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__BroccoliGoobert),alignof(Gd__gd_core_items__Exclusive__BroccoliGoobert));
std::printf(",\"Gd__gd_core_items__Exclusive__Broccotree\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Broccotree),alignof(Gd__gd_core_items__Exclusive__Broccotree));
std::printf(",\"Gd__gd_core_items__Exclusive__BurningBanner\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__BurningBanner),alignof(Gd__gd_core_items__Exclusive__BurningBanner));
std::printf(",\"Gd__gd_core_items__Exclusive__BurningBlade\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__BurningBlade),alignof(Gd__gd_core_items__Exclusive__BurningBlade));
std::printf(",\"Gd__gd_core_items__Exclusive__BurningSpikes\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__BurningSpikes),alignof(Gd__gd_core_items__Exclusive__BurningSpikes));
std::printf(",\"Gd__gd_core_items__Exclusive__BurningSword\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__BurningSword),alignof(Gd__gd_core_items__Exclusive__BurningSword));
std::printf(",\"Gd__gd_core_items__Exclusive__BustedBlade\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__BustedBlade),alignof(Gd__gd_core_items__Exclusive__BustedBlade));
std::printf(",\"Gd__gd_core_items__Exclusive__BuytheHolyLight\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__BuytheHolyLight),alignof(Gd__gd_core_items__Exclusive__BuytheHolyLight));
std::printf(",\"Gd__gd_core_items__Exclusive__CapofBrilliance\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__CapofBrilliance),alignof(Gd__gd_core_items__Exclusive__CapofBrilliance));
std::printf(",\"Gd__gd_core_items__Exclusive__CatSpirit\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__CatSpirit),alignof(Gd__gd_core_items__Exclusive__CatSpirit));
std::printf(",\"Gd__gd_core_items__Exclusive__Cauldron\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Cauldron),alignof(Gd__gd_core_items__Exclusive__Cauldron));
std::printf(",\"Gd__gd_core_items__Exclusive__Chainsaw\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Chainsaw),alignof(Gd__gd_core_items__Exclusive__Chainsaw));
std::printf(",\"Gd__gd_core_items__Exclusive__ChainWhip\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__ChainWhip),alignof(Gd__gd_core_items__Exclusive__ChainWhip));
std::printf(",\"Gd__gd_core_items__Exclusive__ChargeSplitter\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__ChargeSplitter),alignof(Gd__gd_core_items__Exclusive__ChargeSplitter));
std::printf(",\"Gd__gd_core_items__Exclusive__Cheese\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Cheese),alignof(Gd__gd_core_items__Exclusive__Cheese));
std::printf(",\"Gd__gd_core_items__Exclusive__CheeseGoobert\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__CheeseGoobert),alignof(Gd__gd_core_items__Exclusive__CheeseGoobert));
std::printf(",\"Gd__gd_core_items__Exclusive__Chess__BlackBishop\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Chess__BlackBishop),alignof(Gd__gd_core_items__Exclusive__Chess__BlackBishop));
std::printf(",\"Gd__gd_core_items__Exclusive__Chess__BlackKing\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Chess__BlackKing),alignof(Gd__gd_core_items__Exclusive__Chess__BlackKing));
std::printf(",\"Gd__gd_core_items__Exclusive__Chess__BlackKnight\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Chess__BlackKnight),alignof(Gd__gd_core_items__Exclusive__Chess__BlackKnight));
std::printf(",\"Gd__gd_core_items__Exclusive__Chess__BlackPawn\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Chess__BlackPawn),alignof(Gd__gd_core_items__Exclusive__Chess__BlackPawn));
std::printf(",\"Gd__gd_core_items__Exclusive__Chess__BlackQueen\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Chess__BlackQueen),alignof(Gd__gd_core_items__Exclusive__Chess__BlackQueen));
std::printf(",\"Gd__gd_core_items__Exclusive__Chess__BlackRook\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Chess__BlackRook),alignof(Gd__gd_core_items__Exclusive__Chess__BlackRook));
std::printf(",\"Gd__gd_core_items__Exclusive__Chess__ChessPiece\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Chess__ChessPiece),alignof(Gd__gd_core_items__Exclusive__Chess__ChessPiece));
std::printf(",\"Gd__gd_core_items__Exclusive__Chess__WhiteBishop\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Chess__WhiteBishop),alignof(Gd__gd_core_items__Exclusive__Chess__WhiteBishop));
std::printf(",\"Gd__gd_core_items__Exclusive__Chess__WhiteKing\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Chess__WhiteKing),alignof(Gd__gd_core_items__Exclusive__Chess__WhiteKing));
std::printf(",\"Gd__gd_core_items__Exclusive__Chess__WhiteKnight\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Chess__WhiteKnight),alignof(Gd__gd_core_items__Exclusive__Chess__WhiteKnight));
std::printf(",\"Gd__gd_core_items__Exclusive__Chess__WhitePawn\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Chess__WhitePawn),alignof(Gd__gd_core_items__Exclusive__Chess__WhitePawn));
std::printf(",\"Gd__gd_core_items__Exclusive__Chess__WhiteQueen\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Chess__WhiteQueen),alignof(Gd__gd_core_items__Exclusive__Chess__WhiteQueen));
std::printf(",\"Gd__gd_core_items__Exclusive__Chess__WhiteRook\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Chess__WhiteRook),alignof(Gd__gd_core_items__Exclusive__Chess__WhiteRook));
std::printf(",\"Gd__gd_core_items__Exclusive__ChessBoard\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__ChessBoard),alignof(Gd__gd_core_items__Exclusive__ChessBoard));
std::printf(",\"Gd__gd_core_items__Exclusive__ChessMaster\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__ChessMaster),alignof(Gd__gd_core_items__Exclusive__ChessMaster));
std::printf(",\"Gd__gd_core_items__Exclusive__ChiliGoobert\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__ChiliGoobert),alignof(Gd__gd_core_items__Exclusive__ChiliGoobert));
std::printf(",\"Gd__gd_core_items__Exclusive__ChiliPepper\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__ChiliPepper),alignof(Gd__gd_core_items__Exclusive__ChiliPepper));
std::printf(",\"Gd__gd_core_items__Exclusive__ChromeCube\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__ChromeCube),alignof(Gd__gd_core_items__Exclusive__ChromeCube));
std::printf(",\"Gd__gd_core_items__Exclusive__Cog\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Cog),alignof(Gd__gd_core_items__Exclusive__Cog));
std::printf(",\"Gd__gd_core_items__Exclusive__CogBadge\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__CogBadge),alignof(Gd__gd_core_items__Exclusive__CogBadge));
std::printf(",\"Gd__gd_core_items__Exclusive__Coil\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Coil),alignof(Gd__gd_core_items__Exclusive__Coil));
std::printf(",\"Gd__gd_core_items__Exclusive__ConTrapTron\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__ConTrapTron),alignof(Gd__gd_core_items__Exclusive__ConTrapTron));
std::printf(",\"Gd__gd_core_items__Exclusive__CouragePuppy\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__CouragePuppy),alignof(Gd__gd_core_items__Exclusive__CouragePuppy));
std::printf(",\"Gd__gd_core_items__Exclusive__CriticalPoison\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__CriticalPoison),alignof(Gd__gd_core_items__Exclusive__CriticalPoison));
std::printf(",\"Gd__gd_core_items__Exclusive__Crow\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Crow),alignof(Gd__gd_core_items__Exclusive__Crow));
std::printf(",\"Gd__gd_core_items__Exclusive__Cthulhu\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Cthulhu),alignof(Gd__gd_core_items__Exclusive__Cthulhu));
std::printf(",\"Gd__gd_core_items__Exclusive__Cube\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Cube),alignof(Gd__gd_core_items__Exclusive__Cube));
std::printf(",\"Gd__gd_core_items__Exclusive__Cubert\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Cubert),alignof(Gd__gd_core_items__Exclusive__Cubert));
std::printf(",\"Gd__gd_core_items__Exclusive__Cupcake\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Cupcake),alignof(Gd__gd_core_items__Exclusive__Cupcake));
std::printf(",\"Gd__gd_core_items__Exclusive__CupcakeDragon\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__CupcakeDragon),alignof(Gd__gd_core_items__Exclusive__CupcakeDragon));
std::printf(",\"Gd__gd_core_items__Exclusive__CupcakeGoobert\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__CupcakeGoobert),alignof(Gd__gd_core_items__Exclusive__CupcakeGoobert));
std::printf(",\"Gd__gd_core_items__Exclusive__CupcakeStaff\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__CupcakeStaff),alignof(Gd__gd_core_items__Exclusive__CupcakeStaff));
std::printf(",\"Gd__gd_core_items__Exclusive__Daggerang\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Daggerang),alignof(Gd__gd_core_items__Exclusive__Daggerang));
std::printf(",\"Gd__gd_core_items__Exclusive__DarkLantern\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__DarkLantern),alignof(Gd__gd_core_items__Exclusive__DarkLantern));
std::printf(",\"Gd__gd_core_items__Exclusive__DarkRitual\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__DarkRitual),alignof(Gd__gd_core_items__Exclusive__DarkRitual));
std::printf(",\"Gd__gd_core_items__Exclusive__DeathLotus\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__DeathLotus),alignof(Gd__gd_core_items__Exclusive__DeathLotus));
std::printf(",\"Gd__gd_core_items__Exclusive__DeerTotem\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__DeerTotem),alignof(Gd__gd_core_items__Exclusive__DeerTotem));
std::printf(",\"Gd__gd_core_items__Exclusive__DevouringSphere\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__DevouringSphere),alignof(Gd__gd_core_items__Exclusive__DevouringSphere));
std::printf(",\"Gd__gd_core_items__Exclusive__DigDeeper\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__DigDeeper),alignof(Gd__gd_core_items__Exclusive__DigDeeper));
std::printf(",\"Gd__gd_core_items__Exclusive__DivinePotion\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__DivinePotion),alignof(Gd__gd_core_items__Exclusive__DivinePotion));
std::printf(",\"Gd__gd_core_items__Exclusive__DoomCap\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__DoomCap),alignof(Gd__gd_core_items__Exclusive__DoomCap));
std::printf(",\"Gd__gd_core_items__Exclusive__DoubleAxe\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__DoubleAxe),alignof(Gd__gd_core_items__Exclusive__DoubleAxe));
std::printf(",\"Gd__gd_core_items__Exclusive__DoubleRainbow\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__DoubleRainbow),alignof(Gd__gd_core_items__Exclusive__DoubleRainbow));
std::printf(",\"Gd__gd_core_items__Exclusive__DraconicOrb\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__DraconicOrb),alignof(Gd__gd_core_items__Exclusive__DraconicOrb));
std::printf(",\"Gd__gd_core_items__Exclusive__DragonClaws\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__DragonClaws),alignof(Gd__gd_core_items__Exclusive__DragonClaws));
std::printf(",\"Gd__gd_core_items__Exclusive__DragonKnight\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__DragonKnight),alignof(Gd__gd_core_items__Exclusive__DragonKnight));
std::printf(",\"Gd__gd_core_items__Exclusive__DragonNest\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__DragonNest),alignof(Gd__gd_core_items__Exclusive__DragonNest));
std::printf(",\"Gd__gd_core_items__Exclusive__DragonscaleArmor\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__DragonscaleArmor),alignof(Gd__gd_core_items__Exclusive__DragonscaleArmor));
std::printf(",\"Gd__gd_core_items__Exclusive__DragonSet\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__DragonSet),alignof(Gd__gd_core_items__Exclusive__DragonSet));
std::printf(",\"Gd__gd_core_items__Exclusive__DragonskinBoots\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__DragonskinBoots),alignof(Gd__gd_core_items__Exclusive__DragonskinBoots));
std::printf(",\"Gd__gd_core_items__Exclusive__DualWielding\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__DualWielding),alignof(Gd__gd_core_items__Exclusive__DualWielding));
std::printf(",\"Gd__gd_core_items__Exclusive__Eat_o_matic\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Eat_o_matic),alignof(Gd__gd_core_items__Exclusive__Eat_o_matic));
std::printf(",\"Gd__gd_core_items__Exclusive__EchoingBattlecry\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__EchoingBattlecry),alignof(Gd__gd_core_items__Exclusive__EchoingBattlecry));
std::printf(",\"Gd__gd_core_items__Exclusive__ElectricTorch\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__ElectricTorch),alignof(Gd__gd_core_items__Exclusive__ElectricTorch));
std::printf(",\"Gd__gd_core_items__Exclusive__ElephantRune\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__ElephantRune),alignof(Gd__gd_core_items__Exclusive__ElephantRune));
std::printf(",\"Gd__gd_core_items__Exclusive__EmeraldEgg\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__EmeraldEgg),alignof(Gd__gd_core_items__Exclusive__EmeraldEgg));
std::printf(",\"Gd__gd_core_items__Exclusive__EmeraldWhelp\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__EmeraldWhelp),alignof(Gd__gd_core_items__Exclusive__EmeraldWhelp));
std::printf(",\"Gd__gd_core_items__Exclusive__EmployeeUniform\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__EmployeeUniform),alignof(Gd__gd_core_items__Exclusive__EmployeeUniform));
std::printf(",\"Gd__gd_core_items__Exclusive__EnchantedWeapons\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__EnchantedWeapons),alignof(Gd__gd_core_items__Exclusive__EnchantedWeapons));
std::printf(",\"Gd__gd_core_items__Exclusive__EnergyConversion\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__EnergyConversion),alignof(Gd__gd_core_items__Exclusive__EnergyConversion));
std::printf(",\"Gd__gd_core_items__Exclusive__EngineerBag2\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__EngineerBag2),alignof(Gd__gd_core_items__Exclusive__EngineerBag2));
std::printf(",\"Gd__gd_core_items__Exclusive__EngineerBox\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__EngineerBox),alignof(Gd__gd_core_items__Exclusive__EngineerBox));
std::printf(",\"Gd__gd_core_items__Exclusive__Everburning\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Everburning),alignof(Gd__gd_core_items__Exclusive__Everburning));
std::printf(",\"Gd__gd_core_items__Exclusive__EvilHat\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__EvilHat),alignof(Gd__gd_core_items__Exclusive__EvilHat));
std::printf(",\"Gd__gd_core_items__Exclusive__ExtraAngy\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__ExtraAngy),alignof(Gd__gd_core_items__Exclusive__ExtraAngy));
std::printf(",\"Gd__gd_core_items__Exclusive__ExtraBags\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__ExtraBags),alignof(Gd__gd_core_items__Exclusive__ExtraBags));
std::printf(",\"Gd__gd_core_items__Exclusive__FalseLife\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__FalseLife),alignof(Gd__gd_core_items__Exclusive__FalseLife));
std::printf(",\"Gd__gd_core_items__Exclusive__Fedora\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Fedora),alignof(Gd__gd_core_items__Exclusive__Fedora));
std::printf(",\"Gd__gd_core_items__Exclusive__FirePit\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__FirePit),alignof(Gd__gd_core_items__Exclusive__FirePit));
std::printf(",\"Gd__gd_core_items__Exclusive__FireShelly\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__FireShelly),alignof(Gd__gd_core_items__Exclusive__FireShelly));
std::printf(",\"Gd__gd_core_items__Exclusive__Flame\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Flame),alignof(Gd__gd_core_items__Exclusive__Flame));
std::printf(",\"Gd__gd_core_items__Exclusive__FlameBadge\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__FlameBadge),alignof(Gd__gd_core_items__Exclusive__FlameBadge));
std::printf(",\"Gd__gd_core_items__Exclusive__FlameWhip\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__FlameWhip),alignof(Gd__gd_core_items__Exclusive__FlameWhip));
std::printf(",\"Gd__gd_core_items__Exclusive__ForestDragon\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__ForestDragon),alignof(Gd__gd_core_items__Exclusive__ForestDragon));
std::printf(",\"Gd__gd_core_items__Exclusive__ForestFriend\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__ForestFriend),alignof(Gd__gd_core_items__Exclusive__ForestFriend));
std::printf(",\"Gd__gd_core_items__Exclusive__ForgingHammer\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__ForgingHammer),alignof(Gd__gd_core_items__Exclusive__ForgingHammer));
std::printf(",\"Gd__gd_core_items__Exclusive__FortunasKiss\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__FortunasKiss),alignof(Gd__gd_core_items__Exclusive__FortunasKiss));
std::printf(",\"Gd__gd_core_items__Exclusive__FriendlyFire\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__FriendlyFire),alignof(Gd__gd_core_items__Exclusive__FriendlyFire));
std::printf(",\"Gd__gd_core_items__Exclusive__FrogPrince\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__FrogPrince),alignof(Gd__gd_core_items__Exclusive__FrogPrince));
std::printf(",\"Gd__gd_core_items__Exclusive__Frostbite\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Frostbite),alignof(Gd__gd_core_items__Exclusive__Frostbite));
std::printf(",\"Gd__gd_core_items__Exclusive__FrozenBuckler\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__FrozenBuckler),alignof(Gd__gd_core_items__Exclusive__FrozenBuckler));
std::printf(",\"Gd__gd_core_items__Exclusive__FrozenFlame\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__FrozenFlame),alignof(Gd__gd_core_items__Exclusive__FrozenFlame));
std::printf(",\"Gd__gd_core_items__Exclusive__FullBodyProtection\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__FullBodyProtection),alignof(Gd__gd_core_items__Exclusive__FullBodyProtection));
std::printf(",\"Gd__gd_core_items__Exclusive__FurciferPrime\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__FurciferPrime),alignof(Gd__gd_core_items__Exclusive__FurciferPrime));
std::printf(",\"Gd__gd_core_items__Exclusive__Generator\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Generator),alignof(Gd__gd_core_items__Exclusive__Generator));
std::printf(",\"Gd__gd_core_items__Exclusive__Ghost\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Ghost),alignof(Gd__gd_core_items__Exclusive__Ghost));
std::printf(",\"Gd__gd_core_items__Exclusive__Gigawatz\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Gigawatz),alignof(Gd__gd_core_items__Exclusive__Gigawatz));
std::printf(",\"Gd__gd_core_items__Exclusive__GirlPower\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__GirlPower),alignof(Gd__gd_core_items__Exclusive__GirlPower));
std::printf(",\"Gd__gd_core_items__Exclusive__GoldArmor\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__GoldArmor),alignof(Gd__gd_core_items__Exclusive__GoldArmor));
std::printf(",\"Gd__gd_core_items__Exclusive__GoldCube\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__GoldCube),alignof(Gd__gd_core_items__Exclusive__GoldCube));
std::printf(",\"Gd__gd_core_items__Exclusive__Halberd\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Halberd),alignof(Gd__gd_core_items__Exclusive__Halberd));
std::printf(",\"Gd__gd_core_items__Exclusive__Hardwood\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Hardwood),alignof(Gd__gd_core_items__Exclusive__Hardwood));
std::printf(",\"Gd__gd_core_items__Exclusive__HawkRune\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__HawkRune),alignof(Gd__gd_core_items__Exclusive__HawkRune));
std::printf(",\"Gd__gd_core_items__Exclusive__HeartoftheCards\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__HeartoftheCards),alignof(Gd__gd_core_items__Exclusive__HeartoftheCards));
std::printf(",\"Gd__gd_core_items__Exclusive__HeartShield\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__HeartShield),alignof(Gd__gd_core_items__Exclusive__HeartShield));
std::printf(",\"Gd__gd_core_items__Exclusive__HeavyDrinking\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__HeavyDrinking),alignof(Gd__gd_core_items__Exclusive__HeavyDrinking));
std::printf(",\"Gd__gd_core_items__Exclusive__Hedgehog\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Hedgehog),alignof(Gd__gd_core_items__Exclusive__Hedgehog));
std::printf(",\"Gd__gd_core_items__Exclusive__HeroShield\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__HeroShield),alignof(Gd__gd_core_items__Exclusive__HeroShield));
std::printf(",\"Gd__gd_core_items__Exclusive__HogusBogus\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__HogusBogus),alignof(Gd__gd_core_items__Exclusive__HogusBogus));
std::printf(",\"Gd__gd_core_items__Exclusive__Holdall\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Holdall),alignof(Gd__gd_core_items__Exclusive__Holdall));
std::printf(",\"Gd__gd_core_items__Exclusive__HolyCollar\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__HolyCollar),alignof(Gd__gd_core_items__Exclusive__HolyCollar));
std::printf(",\"Gd__gd_core_items__Exclusive__Hypercube\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Hypercube),alignof(Gd__gd_core_items__Exclusive__Hypercube));
std::printf(",\"Gd__gd_core_items__Exclusive__HyperHedgehog\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__HyperHedgehog),alignof(Gd__gd_core_items__Exclusive__HyperHedgehog));
std::printf(",\"Gd__gd_core_items__Exclusive__IceArmor\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__IceArmor),alignof(Gd__gd_core_items__Exclusive__IceArmor));
std::printf(",\"Gd__gd_core_items__Exclusive__IceDragon\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__IceDragon),alignof(Gd__gd_core_items__Exclusive__IceDragon));
std::printf(",\"Gd__gd_core_items__Exclusive__IceFlower\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__IceFlower),alignof(Gd__gd_core_items__Exclusive__IceFlower));
std::printf(",\"Gd__gd_core_items__Exclusive__InnerPower\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__InnerPower),alignof(Gd__gd_core_items__Exclusive__InnerPower));
std::printf(",\"Gd__gd_core_items__Exclusive__InvestmentOpportunity\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__InvestmentOpportunity),alignof(Gd__gd_core_items__Exclusive__InvestmentOpportunity));
std::printf(",\"Gd__gd_core_items__Exclusive__Joker\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Joker),alignof(Gd__gd_core_items__Exclusive__Joker));
std::printf(",\"Gd__gd_core_items__Exclusive__JustStats\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__JustStats),alignof(Gd__gd_core_items__Exclusive__JustStats));
std::printf(",\"Gd__gd_core_items__Exclusive__JynxStaff\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__JynxStaff),alignof(Gd__gd_core_items__Exclusive__JynxStaff));
std::printf(",\"Gd__gd_core_items__Exclusive__Katana\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Katana),alignof(Gd__gd_core_items__Exclusive__Katana));
std::printf(",\"Gd__gd_core_items__Exclusive__KingCrown\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__KingCrown),alignof(Gd__gd_core_items__Exclusive__KingCrown));
std::printf(",\"Gd__gd_core_items__Exclusive__KingGoobert\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__KingGoobert),alignof(Gd__gd_core_items__Exclusive__KingGoobert));
std::printf(",\"Gd__gd_core_items__Exclusive__KingoftheBling\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__KingoftheBling),alignof(Gd__gd_core_items__Exclusive__KingoftheBling));
std::printf(",\"Gd__gd_core_items__Exclusive__KnifetoMeetYou\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__KnifetoMeetYou),alignof(Gd__gd_core_items__Exclusive__KnifetoMeetYou));
std::printf(",\"Gd__gd_core_items__Exclusive__Laboratory\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Laboratory),alignof(Gd__gd_core_items__Exclusive__Laboratory));
std::printf(",\"Gd__gd_core_items__Exclusive__LeafBadge\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__LeafBadge),alignof(Gd__gd_core_items__Exclusive__LeafBadge));
std::printf(",\"Gd__gd_core_items__Exclusive__LevelUp\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__LevelUp),alignof(Gd__gd_core_items__Exclusive__LevelUp));
std::printf(",\"Gd__gd_core_items__Exclusive__LightFlower\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__LightFlower),alignof(Gd__gd_core_items__Exclusive__LightFlower));
std::printf(",\"Gd__gd_core_items__Exclusive__LightningPotion\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__LightningPotion),alignof(Gd__gd_core_items__Exclusive__LightningPotion));
std::printf(",\"Gd__gd_core_items__Exclusive__LightningStaff\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__LightningStaff),alignof(Gd__gd_core_items__Exclusive__LightningStaff));
std::printf(",\"Gd__gd_core_items__Exclusive__LittleMimic\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__LittleMimic),alignof(Gd__gd_core_items__Exclusive__LittleMimic));
std::printf(",\"Gd__gd_core_items__Exclusive__LongSpear\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__LongSpear),alignof(Gd__gd_core_items__Exclusive__LongSpear));
std::printf(",\"Gd__gd_core_items__Exclusive__Lootbox\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Lootbox),alignof(Gd__gd_core_items__Exclusive__Lootbox));
std::printf(",\"Gd__gd_core_items__Exclusive__LuckyCat\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__LuckyCat),alignof(Gd__gd_core_items__Exclusive__LuckyCat));
std::printf(",\"Gd__gd_core_items__Exclusive__LuckyShortbow\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__LuckyShortbow),alignof(Gd__gd_core_items__Exclusive__LuckyShortbow));
std::printf(",\"Gd__gd_core_items__Exclusive__MageHat\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__MageHat),alignof(Gd__gd_core_items__Exclusive__MageHat));
std::printf(",\"Gd__gd_core_items__Exclusive__MagicBadge\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__MagicBadge),alignof(Gd__gd_core_items__Exclusive__MagicBadge));
std::printf(",\"Gd__gd_core_items__Exclusive__MagicCollar\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__MagicCollar),alignof(Gd__gd_core_items__Exclusive__MagicCollar));
std::printf(",\"Gd__gd_core_items__Exclusive__MagicMirror\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__MagicMirror),alignof(Gd__gd_core_items__Exclusive__MagicMirror));
std::printf(",\"Gd__gd_core_items__Exclusive__MagicRing\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__MagicRing),alignof(Gd__gd_core_items__Exclusive__MagicRing));
std::printf(",\"Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect),alignof(Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect));
std::printf(",\"Gd__gd_core_items__Exclusive__MagiteccArmor\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__MagiteccArmor),alignof(Gd__gd_core_items__Exclusive__MagiteccArmor));
std::printf(",\"Gd__gd_core_items__Exclusive__ManaCrystal\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__ManaCrystal),alignof(Gd__gd_core_items__Exclusive__ManaCrystal));
std::printf(",\"Gd__gd_core_items__Exclusive__ManaMastery\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__ManaMastery),alignof(Gd__gd_core_items__Exclusive__ManaMastery));
std::printf(",\"Gd__gd_core_items__Exclusive__Mananana\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Mananana),alignof(Gd__gd_core_items__Exclusive__Mananana));
std::printf(",\"Gd__gd_core_items__Exclusive__Markswoman\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Markswoman),alignof(Gd__gd_core_items__Exclusive__Markswoman));
std::printf(",\"Gd__gd_core_items__Exclusive__MechaBat\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__MechaBat),alignof(Gd__gd_core_items__Exclusive__MechaBat));
std::printf(",\"Gd__gd_core_items__Exclusive__MegaClover\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__MegaClover),alignof(Gd__gd_core_items__Exclusive__MegaClover));
std::printf(",\"Gd__gd_core_items__Exclusive__MercuryElemental\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__MercuryElemental),alignof(Gd__gd_core_items__Exclusive__MercuryElemental));
std::printf(",\"Gd__gd_core_items__Exclusive__MissFortune\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__MissFortune),alignof(Gd__gd_core_items__Exclusive__MissFortune));
std::printf(",\"Gd__gd_core_items__Exclusive__MoltenDagger\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__MoltenDagger),alignof(Gd__gd_core_items__Exclusive__MoltenDagger));
std::printf(",\"Gd__gd_core_items__Exclusive__MoltenGreatsword\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__MoltenGreatsword),alignof(Gd__gd_core_items__Exclusive__MoltenGreatsword));
std::printf(",\"Gd__gd_core_items__Exclusive__MoltenSpear\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__MoltenSpear),alignof(Gd__gd_core_items__Exclusive__MoltenSpear));
std::printf(",\"Gd__gd_core_items__Exclusive__MoltenSpear2\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__MoltenSpear2),alignof(Gd__gd_core_items__Exclusive__MoltenSpear2));
std::printf(",\"Gd__gd_core_items__Exclusive__MoonArmor\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__MoonArmor),alignof(Gd__gd_core_items__Exclusive__MoonArmor));
std::printf(",\"Gd__gd_core_items__Exclusive__MoreStats\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__MoreStats),alignof(Gd__gd_core_items__Exclusive__MoreStats));
std::printf(",\"Gd__gd_core_items__Exclusive__MrsStruggles\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__MrsStruggles),alignof(Gd__gd_core_items__Exclusive__MrsStruggles));
std::printf(",\"Gd__gd_core_items__Exclusive__MushroomFarm\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__MushroomFarm),alignof(Gd__gd_core_items__Exclusive__MushroomFarm));
std::printf(",\"Gd__gd_core_items__Exclusive__NoRushPlease\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__NoRushPlease),alignof(Gd__gd_core_items__Exclusive__NoRushPlease));
std::printf(",\"Gd__gd_core_items__Exclusive__NullBlade\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__NullBlade),alignof(Gd__gd_core_items__Exclusive__NullBlade));
std::printf(",\"Gd__gd_core_items__Exclusive__ObsidianDragon\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__ObsidianDragon),alignof(Gd__gd_core_items__Exclusive__ObsidianDragon));
std::printf(",\"Gd__gd_core_items__Exclusive__OilLamp\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__OilLamp),alignof(Gd__gd_core_items__Exclusive__OilLamp));
std::printf(",\"Gd__gd_core_items__Exclusive__OnionCutter\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__OnionCutter),alignof(Gd__gd_core_items__Exclusive__OnionCutter));
std::printf(",\"Gd__gd_core_items__Exclusive__OwlSpirit\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__OwlSpirit),alignof(Gd__gd_core_items__Exclusive__OwlSpirit));
std::printf(",\"Gd__gd_core_items__Exclusive__ParadiseBirb\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__ParadiseBirb),alignof(Gd__gd_core_items__Exclusive__ParadiseBirb));
std::printf(",\"Gd__gd_core_items__Exclusive__PerpetuumMobile\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__PerpetuumMobile),alignof(Gd__gd_core_items__Exclusive__PerpetuumMobile));
std::printf(",\"Gd__gd_core_items__Exclusive__Phoenix\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Phoenix),alignof(Gd__gd_core_items__Exclusive__Phoenix));
std::printf(",\"Gd__gd_core_items__Exclusive__Phoenix2\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Phoenix2),alignof(Gd__gd_core_items__Exclusive__Phoenix2));
std::printf(",\"Gd__gd_core_items__Exclusive__PiggyofRiches\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__PiggyofRiches),alignof(Gd__gd_core_items__Exclusive__PiggyofRiches));
std::printf(",\"Gd__gd_core_items__Exclusive__PiggyPinata\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__PiggyPinata),alignof(Gd__gd_core_items__Exclusive__PiggyPinata));
std::printf(",\"Gd__gd_core_items__Exclusive__PineProtector\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__PineProtector),alignof(Gd__gd_core_items__Exclusive__PineProtector));
std::printf(",\"Gd__gd_core_items__Exclusive__PlasticCube\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__PlasticCube),alignof(Gd__gd_core_items__Exclusive__PlasticCube));
std::printf(",\"Gd__gd_core_items__Exclusive__PoisonFrog\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__PoisonFrog),alignof(Gd__gd_core_items__Exclusive__PoisonFrog));
std::printf(",\"Gd__gd_core_items__Exclusive__PoisonGrenade\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__PoisonGrenade),alignof(Gd__gd_core_items__Exclusive__PoisonGrenade));
std::printf(",\"Gd__gd_core_items__Exclusive__PoisonShortbow\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__PoisonShortbow),alignof(Gd__gd_core_items__Exclusive__PoisonShortbow));
std::printf(",\"Gd__gd_core_items__Exclusive__PoisonSpear\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__PoisonSpear),alignof(Gd__gd_core_items__Exclusive__PoisonSpear));
std::printf(",\"Gd__gd_core_items__Exclusive__Pop\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Pop),alignof(Gd__gd_core_items__Exclusive__Pop));
std::printf(",\"Gd__gd_core_items__Exclusive__PortableAltar\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__PortableAltar),alignof(Gd__gd_core_items__Exclusive__PortableAltar));
std::printf(",\"Gd__gd_core_items__Exclusive__Pot\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Pot),alignof(Gd__gd_core_items__Exclusive__Pot));
std::printf(",\"Gd__gd_core_items__Exclusive__PoweroftheMoon\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__PoweroftheMoon),alignof(Gd__gd_core_items__Exclusive__PoweroftheMoon));
std::printf(",\"Gd__gd_core_items__Exclusive__PowerPuppy\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__PowerPuppy),alignof(Gd__gd_core_items__Exclusive__PowerPuppy));
std::printf(",\"Gd__gd_core_items__Exclusive__PrismaticSword\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__PrismaticSword),alignof(Gd__gd_core_items__Exclusive__PrismaticSword));
std::printf(",\"Gd__gd_core_items__Exclusive__PrismaticWand\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__PrismaticWand),alignof(Gd__gd_core_items__Exclusive__PrismaticWand));
std::printf(",\"Gd__gd_core_items__Exclusive__PuzzleBadge\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__PuzzleBadge),alignof(Gd__gd_core_items__Exclusive__PuzzleBadge));
std::printf(",\"Gd__gd_core_items__Exclusive__PuzzlebagJ\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__PuzzlebagJ),alignof(Gd__gd_core_items__Exclusive__PuzzlebagJ));
std::printf(",\"Gd__gd_core_items__Exclusive__PuzzlebagL\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__PuzzlebagL),alignof(Gd__gd_core_items__Exclusive__PuzzlebagL));
std::printf(",\"Gd__gd_core_items__Exclusive__PuzzlebagS\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__PuzzlebagS),alignof(Gd__gd_core_items__Exclusive__PuzzlebagS));
std::printf(",\"Gd__gd_core_items__Exclusive__PuzzlebagT\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__PuzzlebagT),alignof(Gd__gd_core_items__Exclusive__PuzzlebagT));
std::printf(",\"Gd__gd_core_items__Exclusive__PuzzlebagZ\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__PuzzlebagZ),alignof(Gd__gd_core_items__Exclusive__PuzzlebagZ));
std::printf(",\"Gd__gd_core_items__Exclusive__Puzzlebox\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Puzzlebox),alignof(Gd__gd_core_items__Exclusive__Puzzlebox));
std::printf(",\"Gd__gd_core_items__Exclusive__RainbowBadge\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__RainbowBadge),alignof(Gd__gd_core_items__Exclusive__RainbowBadge));
std::printf(",\"Gd__gd_core_items__Exclusive__RainbowGoobertAdventurer\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__RainbowGoobertAdventurer),alignof(Gd__gd_core_items__Exclusive__RainbowGoobertAdventurer));
std::printf(",\"Gd__gd_core_items__Exclusive__RainbowGoobertBerserker\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__RainbowGoobertBerserker),alignof(Gd__gd_core_items__Exclusive__RainbowGoobertBerserker));
std::printf(",\"Gd__gd_core_items__Exclusive__RainbowGoobertEngineer\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__RainbowGoobertEngineer),alignof(Gd__gd_core_items__Exclusive__RainbowGoobertEngineer));
std::printf(",\"Gd__gd_core_items__Exclusive__RainbowGoobertMage\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__RainbowGoobertMage),alignof(Gd__gd_core_items__Exclusive__RainbowGoobertMage));
std::printf(",\"Gd__gd_core_items__Exclusive__RainbowGoobertPyromancer\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__RainbowGoobertPyromancer),alignof(Gd__gd_core_items__Exclusive__RainbowGoobertPyromancer));
std::printf(",\"Gd__gd_core_items__Exclusive__RainbowOrb\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__RainbowOrb),alignof(Gd__gd_core_items__Exclusive__RainbowOrb));
std::printf(",\"Gd__gd_core_items__Exclusive__RainbowPotion\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__RainbowPotion),alignof(Gd__gd_core_items__Exclusive__RainbowPotion));
std::printf(",\"Gd__gd_core_items__Exclusive__RandomLoadoutBag\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__RandomLoadoutBag),alignof(Gd__gd_core_items__Exclusive__RandomLoadoutBag));
std::printf(",\"Gd__gd_core_items__Exclusive__Rat\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Rat),alignof(Gd__gd_core_items__Exclusive__Rat));
std::printf(",\"Gd__gd_core_items__Exclusive__RatChef\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__RatChef),alignof(Gd__gd_core_items__Exclusive__RatChef));
std::printf(",\"Gd__gd_core_items__Exclusive__Recombobulator\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Recombobulator),alignof(Gd__gd_core_items__Exclusive__Recombobulator));
std::printf(",\"Gd__gd_core_items__Exclusive__RelicCase\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__RelicCase),alignof(Gd__gd_core_items__Exclusive__RelicCase));
std::printf(",\"Gd__gd_core_items__Exclusive__Repeater\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Repeater),alignof(Gd__gd_core_items__Exclusive__Repeater));
std::printf(",\"Gd__gd_core_items__Exclusive__Resistor\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Resistor),alignof(Gd__gd_core_items__Exclusive__Resistor));
std::printf(",\"Gd__gd_core_items__Exclusive__Reverse\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Reverse),alignof(Gd__gd_core_items__Exclusive__Reverse));
std::printf(",\"Gd__gd_core_items__Exclusive__Robodog\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Robodog),alignof(Gd__gd_core_items__Exclusive__Robodog));
std::printf(",\"Gd__gd_core_items__Exclusive__Rope\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Rope),alignof(Gd__gd_core_items__Exclusive__Rope));
std::printf(",\"Gd__gd_core_items__Exclusive__Sandbag\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Sandbag),alignof(Gd__gd_core_items__Exclusive__Sandbag));
std::printf(",\"Gd__gd_core_items__Exclusive__SapphireEgg\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__SapphireEgg),alignof(Gd__gd_core_items__Exclusive__SapphireEgg));
std::printf(",\"Gd__gd_core_items__Exclusive__SapphireWhelp\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__SapphireWhelp),alignof(Gd__gd_core_items__Exclusive__SapphireWhelp));
std::printf(",\"Gd__gd_core_items__Exclusive__Scale\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Scale),alignof(Gd__gd_core_items__Exclusive__Scale));
std::printf(",\"Gd__gd_core_items__Exclusive__ScholarBag\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__ScholarBag),alignof(Gd__gd_core_items__Exclusive__ScholarBag));
std::printf(",\"Gd__gd_core_items__Exclusive__Scissorswords\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Scissorswords),alignof(Gd__gd_core_items__Exclusive__Scissorswords));
std::printf(",\"Gd__gd_core_items__Exclusive__SealtheDeal\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__SealtheDeal),alignof(Gd__gd_core_items__Exclusive__SealtheDeal));
std::printf(",\"Gd__gd_core_items__Exclusive__SerpentStaff\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__SerpentStaff),alignof(Gd__gd_core_items__Exclusive__SerpentStaff));
std::printf(",\"Gd__gd_core_items__Exclusive__SewingCase\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__SewingCase),alignof(Gd__gd_core_items__Exclusive__SewingCase));
std::printf(",\"Gd__gd_core_items__Exclusive__ShamanMask\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__ShamanMask),alignof(Gd__gd_core_items__Exclusive__ShamanMask));
std::printf(",\"Gd__gd_core_items__Exclusive__ShellTotem\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__ShellTotem),alignof(Gd__gd_core_items__Exclusive__ShellTotem));
std::printf(",\"Gd__gd_core_items__Exclusive__Shelly\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Shelly),alignof(Gd__gd_core_items__Exclusive__Shelly));
std::printf(",\"Gd__gd_core_items__Exclusive__ShepherdsCrook\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__ShepherdsCrook),alignof(Gd__gd_core_items__Exclusive__ShepherdsCrook));
std::printf(",\"Gd__gd_core_items__Exclusive__Shielded\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Shielded),alignof(Gd__gd_core_items__Exclusive__Shielded));
std::printf(",\"Gd__gd_core_items__Exclusive__ShinyMantle\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__ShinyMantle),alignof(Gd__gd_core_items__Exclusive__ShinyMantle));
std::printf(",\"Gd__gd_core_items__Exclusive__ShinyShell\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__ShinyShell),alignof(Gd__gd_core_items__Exclusive__ShinyShell));
std::printf(",\"Gd__gd_core_items__Exclusive__SkullBadge\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__SkullBadge),alignof(Gd__gd_core_items__Exclusive__SkullBadge));
std::printf(",\"Gd__gd_core_items__Exclusive__SliceofBread\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__SliceofBread),alignof(Gd__gd_core_items__Exclusive__SliceofBread));
std::printf(",\"Gd__gd_core_items__Exclusive__SliceofToast\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__SliceofToast),alignof(Gd__gd_core_items__Exclusive__SliceofToast));
std::printf(",\"Gd__gd_core_items__Exclusive__SlimeTime\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__SlimeTime),alignof(Gd__gd_core_items__Exclusive__SlimeTime));
std::printf(",\"Gd__gd_core_items__Exclusive__Sloth\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Sloth),alignof(Gd__gd_core_items__Exclusive__Sloth));
std::printf(",\"Gd__gd_core_items__Exclusive__SmellyBarrier\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__SmellyBarrier),alignof(Gd__gd_core_items__Exclusive__SmellyBarrier));
std::printf(",\"Gd__gd_core_items__Exclusive__SmithingForDummies\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__SmithingForDummies),alignof(Gd__gd_core_items__Exclusive__SmithingForDummies));
std::printf(",\"Gd__gd_core_items__Exclusive__Snake\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Snake),alignof(Gd__gd_core_items__Exclusive__Snake));
std::printf(",\"Gd__gd_core_items__Exclusive__Snowball\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Snowball),alignof(Gd__gd_core_items__Exclusive__Snowball));
std::printf(",\"Gd__gd_core_items__Exclusive__Snowcake\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Snowcake),alignof(Gd__gd_core_items__Exclusive__Snowcake));
std::printf(",\"Gd__gd_core_items__Exclusive__Snowman\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Snowman),alignof(Gd__gd_core_items__Exclusive__Snowman));
std::printf(",\"Gd__gd_core_items__Exclusive__Snowmaster\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Snowmaster),alignof(Gd__gd_core_items__Exclusive__Snowmaster));
std::printf(",\"Gd__gd_core_items__Exclusive__SnowStick\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__SnowStick),alignof(Gd__gd_core_items__Exclusive__SnowStick));
std::printf(",\"Gd__gd_core_items__Exclusive__Solaris\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Solaris),alignof(Gd__gd_core_items__Exclusive__Solaris));
std::printf(",\"Gd__gd_core_items__Exclusive__SpeakwithAnimals\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__SpeakwithAnimals),alignof(Gd__gd_core_items__Exclusive__SpeakwithAnimals));
std::printf(",\"Gd__gd_core_items__Exclusive__SpellScrollDark\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__SpellScrollDark),alignof(Gd__gd_core_items__Exclusive__SpellScrollDark));
std::printf(",\"Gd__gd_core_items__Exclusive__SpellScrollFrostbolt\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__SpellScrollFrostbolt),alignof(Gd__gd_core_items__Exclusive__SpellScrollFrostbolt));
std::printf(",\"Gd__gd_core_items__Exclusive__SpellScrollIce\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__SpellScrollIce),alignof(Gd__gd_core_items__Exclusive__SpellScrollIce));
std::printf(",\"Gd__gd_core_items__Exclusive__SpellScrollLight\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__SpellScrollLight),alignof(Gd__gd_core_items__Exclusive__SpellScrollLight));
std::printf(",\"Gd__gd_core_items__Exclusive__SpellScrollNature\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__SpellScrollNature),alignof(Gd__gd_core_items__Exclusive__SpellScrollNature));
std::printf(",\"Gd__gd_core_items__Exclusive__SpicyBanana\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__SpicyBanana),alignof(Gd__gd_core_items__Exclusive__SpicyBanana));
std::printf(",\"Gd__gd_core_items__Exclusive__SpikedCollar\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__SpikedCollar),alignof(Gd__gd_core_items__Exclusive__SpikedCollar));
std::printf(",\"Gd__gd_core_items__Exclusive__SpikedStaff\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__SpikedStaff),alignof(Gd__gd_core_items__Exclusive__SpikedStaff));
std::printf(",\"Gd__gd_core_items__Exclusive__SpikedWall\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__SpikedWall),alignof(Gd__gd_core_items__Exclusive__SpikedWall));
std::printf(",\"Gd__gd_core_items__Exclusive__SpintoWin\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__SpintoWin),alignof(Gd__gd_core_items__Exclusive__SpintoWin));
std::printf(",\"Gd__gd_core_items__Exclusive__SpiritBells\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__SpiritBells),alignof(Gd__gd_core_items__Exclusive__SpiritBells));
std::printf(",\"Gd__gd_core_items__Exclusive__SpiritCompanion\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__SpiritCompanion),alignof(Gd__gd_core_items__Exclusive__SpiritCompanion));
std::printf(",\"Gd__gd_core_items__Exclusive__SpringLoader\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__SpringLoader),alignof(Gd__gd_core_items__Exclusive__SpringLoader));
std::printf(",\"Gd__gd_core_items__Exclusive__Squirrel\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Squirrel),alignof(Gd__gd_core_items__Exclusive__Squirrel));
std::printf(",\"Gd__gd_core_items__Exclusive__SquirrelArcher\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__SquirrelArcher),alignof(Gd__gd_core_items__Exclusive__SquirrelArcher));
std::printf(",\"Gd__gd_core_items__Exclusive__StaffofFire\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__StaffofFire),alignof(Gd__gd_core_items__Exclusive__StaffofFire));
std::printf(",\"Gd__gd_core_items__Exclusive__StarofCourage\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__StarofCourage),alignof(Gd__gd_core_items__Exclusive__StarofCourage));
std::printf(",\"Gd__gd_core_items__Exclusive__SteelDragon\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__SteelDragon),alignof(Gd__gd_core_items__Exclusive__SteelDragon));
std::printf(",\"Gd__gd_core_items__Exclusive__StoneArmor\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__StoneArmor),alignof(Gd__gd_core_items__Exclusive__StoneArmor));
std::printf(",\"Gd__gd_core_items__Exclusive__StoneBadge\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__StoneBadge),alignof(Gd__gd_core_items__Exclusive__StoneBadge));
std::printf(",\"Gd__gd_core_items__Exclusive__Stoned\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Stoned),alignof(Gd__gd_core_items__Exclusive__Stoned));
std::printf(",\"Gd__gd_core_items__Exclusive__StoneGloves\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__StoneGloves),alignof(Gd__gd_core_items__Exclusive__StoneGloves));
std::printf(",\"Gd__gd_core_items__Exclusive__StoneGolem\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__StoneGolem),alignof(Gd__gd_core_items__Exclusive__StoneGolem));
std::printf(",\"Gd__gd_core_items__Exclusive__StoneShoes\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__StoneShoes),alignof(Gd__gd_core_items__Exclusive__StoneShoes));
std::printf(",\"Gd__gd_core_items__Exclusive__StrongDivinePotion\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__StrongDivinePotion),alignof(Gd__gd_core_items__Exclusive__StrongDivinePotion));
std::printf(",\"Gd__gd_core_items__Exclusive__StrongVampiricPotion\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__StrongVampiricPotion),alignof(Gd__gd_core_items__Exclusive__StrongVampiricPotion));
std::printf(",\"Gd__gd_core_items__Exclusive__SunArmor\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__SunArmor),alignof(Gd__gd_core_items__Exclusive__SunArmor));
std::printf(",\"Gd__gd_core_items__Exclusive__SunShield\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__SunShield),alignof(Gd__gd_core_items__Exclusive__SunShield));
std::printf(",\"Gd__gd_core_items__Exclusive__TeslaCoil\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__TeslaCoil),alignof(Gd__gd_core_items__Exclusive__TeslaCoil));
std::printf(",\"Gd__gd_core_items__Exclusive__Thornbloom\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Thornbloom),alignof(Gd__gd_core_items__Exclusive__Thornbloom));
std::printf(",\"Gd__gd_core_items__Exclusive__Thornburst\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Thornburst),alignof(Gd__gd_core_items__Exclusive__Thornburst));
std::printf(",\"Gd__gd_core_items__Exclusive__ThornElemental\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__ThornElemental),alignof(Gd__gd_core_items__Exclusive__ThornElemental));
std::printf(",\"Gd__gd_core_items__Exclusive__ThornShortbow\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__ThornShortbow),alignof(Gd__gd_core_items__Exclusive__ThornShortbow));
std::printf(",\"Gd__gd_core_items__Exclusive__ThorsHammer\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__ThorsHammer),alignof(Gd__gd_core_items__Exclusive__ThorsHammer));
std::printf(",\"Gd__gd_core_items__Exclusive__ThunderDrake\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__ThunderDrake),alignof(Gd__gd_core_items__Exclusive__ThunderDrake));
std::printf(",\"Gd__gd_core_items__Exclusive__TigerRune\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__TigerRune),alignof(Gd__gd_core_items__Exclusive__TigerRune));
std::printf(",\"Gd__gd_core_items__Exclusive__TimeDilator\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__TimeDilator),alignof(Gd__gd_core_items__Exclusive__TimeDilator));
std::printf(",\"Gd__gd_core_items__Exclusive__TimeMelting\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__TimeMelting),alignof(Gd__gd_core_items__Exclusive__TimeMelting));
std::printf(",\"Gd__gd_core_items__Exclusive__TimePendant\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__TimePendant),alignof(Gd__gd_core_items__Exclusive__TimePendant));
std::printf(",\"Gd__gd_core_items__Exclusive__Toad\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Toad),alignof(Gd__gd_core_items__Exclusive__Toad));
std::printf(",\"Gd__gd_core_items__Exclusive__ToastGoobert\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__ToastGoobert),alignof(Gd__gd_core_items__Exclusive__ToastGoobert));
std::printf(",\"Gd__gd_core_items__Exclusive__Toolbox\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Toolbox),alignof(Gd__gd_core_items__Exclusive__Toolbox));
std::printf(",\"Gd__gd_core_items__Exclusive__Turtle\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Turtle),alignof(Gd__gd_core_items__Exclusive__Turtle));
std::printf(",\"Gd__gd_core_items__Exclusive__Twine\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Twine),alignof(Gd__gd_core_items__Exclusive__Twine));
std::printf(",\"Gd__gd_core_items__Exclusive__TwineBadge\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__TwineBadge),alignof(Gd__gd_core_items__Exclusive__TwineBadge));
std::printf(",\"Gd__gd_core_items__Exclusive__Ukulele\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Ukulele),alignof(Gd__gd_core_items__Exclusive__Ukulele));
std::printf(",\"Gd__gd_core_items__Exclusive__Ultima\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Ultima),alignof(Gd__gd_core_items__Exclusive__Ultima));
std::printf(",\"Gd__gd_core_items__Exclusive__UnidentifiedSkill\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__UnidentifiedSkill),alignof(Gd__gd_core_items__Exclusive__UnidentifiedSkill));
std::printf(",\"Gd__gd_core_items__Exclusive__UniquelyUnique\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__UniquelyUnique),alignof(Gd__gd_core_items__Exclusive__UniquelyUnique));
std::printf(",\"Gd__gd_core_items__Exclusive__VampiricCollar\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__VampiricCollar),alignof(Gd__gd_core_items__Exclusive__VampiricCollar));
std::printf(",\"Gd__gd_core_items__Exclusive__VampiricPotion\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__VampiricPotion),alignof(Gd__gd_core_items__Exclusive__VampiricPotion));
std::printf(",\"Gd__gd_core_items__Exclusive__VineweaveBasket\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__VineweaveBasket),alignof(Gd__gd_core_items__Exclusive__VineweaveBasket));
std::printf(",\"Gd__gd_core_items__Exclusive__Wand\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Wand),alignof(Gd__gd_core_items__Exclusive__Wand));
std::printf(",\"Gd__gd_core_items__Exclusive__WandofDissonance\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__WandofDissonance),alignof(Gd__gd_core_items__Exclusive__WandofDissonance));
std::printf(",\"Gd__gd_core_items__Exclusive__WarScythe\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__WarScythe),alignof(Gd__gd_core_items__Exclusive__WarScythe));
std::printf(",\"Gd__gd_core_items__Exclusive__WaterElemental\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__WaterElemental),alignof(Gd__gd_core_items__Exclusive__WaterElemental));
std::printf(",\"Gd__gd_core_items__Exclusive__Whetstone3\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Whetstone3),alignof(Gd__gd_core_items__Exclusive__Whetstone3));
std::printf(",\"Gd__gd_core_items__Exclusive__WingedBoots\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__WingedBoots),alignof(Gd__gd_core_items__Exclusive__WingedBoots));
std::printf(",\"Gd__gd_core_items__Exclusive__WisdomPuppy\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__WisdomPuppy),alignof(Gd__gd_core_items__Exclusive__WisdomPuppy));
std::printf(",\"Gd__gd_core_items__Exclusive__Wisp\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Wisp),alignof(Gd__gd_core_items__Exclusive__Wisp));
std::printf(",\"Gd__gd_core_items__Exclusive__WolfBadge\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__WolfBadge),alignof(Gd__gd_core_items__Exclusive__WolfBadge));
std::printf(",\"Gd__gd_core_items__Exclusive__WolfEmblem\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__WolfEmblem),alignof(Gd__gd_core_items__Exclusive__WolfEmblem));
std::printf(",\"Gd__gd_core_items__Exclusive__Wrench\":[%zu,%zu]",sizeof(Gd__gd_core_items__Exclusive__Wrench),alignof(Gd__gd_core_items__Exclusive__Wrench));
std::printf(",\"Gd__gd_core_items__FalconBlade\":[%zu,%zu]",sizeof(Gd__gd_core_items__FalconBlade),alignof(Gd__gd_core_items__FalconBlade));
std::printf(",\"Gd__gd_core_items__FancyFencingRapier\":[%zu,%zu]",sizeof(Gd__gd_core_items__FancyFencingRapier),alignof(Gd__gd_core_items__FancyFencingRapier));
std::printf(",\"Gd__gd_core_items__Fanfare\":[%zu,%zu]",sizeof(Gd__gd_core_items__Fanfare),alignof(Gd__gd_core_items__Fanfare));
std::printf(",\"Gd__gd_core_items__FannyPack\":[%zu,%zu]",sizeof(Gd__gd_core_items__FannyPack),alignof(Gd__gd_core_items__FannyPack));
std::printf(",\"Gd__gd_core_items__Flute\":[%zu,%zu]",sizeof(Gd__gd_core_items__Flute),alignof(Gd__gd_core_items__Flute));
std::printf(",\"Gd__gd_core_items__FlyAgaric\":[%zu,%zu]",sizeof(Gd__gd_core_items__FlyAgaric),alignof(Gd__gd_core_items__FlyAgaric));
std::printf(",\"Gd__gd_core_items__Food\":[%zu,%zu]",sizeof(Gd__gd_core_items__Food),alignof(Gd__gd_core_items__Food));
std::printf(",\"Gd__gd_core_items__Garlic\":[%zu,%zu]",sizeof(Gd__gd_core_items__Garlic),alignof(Gd__gd_core_items__Garlic));
std::printf(",\"Gd__gd_core_items__Gems__Amethyst\":[%zu,%zu]",sizeof(Gd__gd_core_items__Gems__Amethyst),alignof(Gd__gd_core_items__Gems__Amethyst));
std::printf(",\"Gd__gd_core_items__Gems__CorruptedCrystal\":[%zu,%zu]",sizeof(Gd__gd_core_items__Gems__CorruptedCrystal),alignof(Gd__gd_core_items__Gems__CorruptedCrystal));
std::printf(",\"Gd__gd_core_items__Gems__Emerald\":[%zu,%zu]",sizeof(Gd__gd_core_items__Gems__Emerald),alignof(Gd__gd_core_items__Gems__Emerald));
std::printf(",\"Gd__gd_core_items__Gems__Gem\":[%zu,%zu]",sizeof(Gd__gd_core_items__Gems__Gem),alignof(Gd__gd_core_items__Gems__Gem));
std::printf(",\"Gd__gd_core_items__Gems__LumpofCoal\":[%zu,%zu]",sizeof(Gd__gd_core_items__Gems__LumpofCoal),alignof(Gd__gd_core_items__Gems__LumpofCoal));
std::printf(",\"Gd__gd_core_items__Gems__Ruby\":[%zu,%zu]",sizeof(Gd__gd_core_items__Gems__Ruby),alignof(Gd__gd_core_items__Gems__Ruby));
std::printf(",\"Gd__gd_core_items__Gems__Sapphire\":[%zu,%zu]",sizeof(Gd__gd_core_items__Gems__Sapphire),alignof(Gd__gd_core_items__Gems__Sapphire));
std::printf(",\"Gd__gd_core_items__Gems__Skull\":[%zu,%zu]",sizeof(Gd__gd_core_items__Gems__Skull),alignof(Gd__gd_core_items__Gems__Skull));
std::printf(",\"Gd__gd_core_items__Gems__Topaz\":[%zu,%zu]",sizeof(Gd__gd_core_items__Gems__Topaz),alignof(Gd__gd_core_items__Gems__Topaz));
std::printf(",\"Gd__gd_core_items__GingerbreadMan\":[%zu,%zu]",sizeof(Gd__gd_core_items__GingerbreadMan),alignof(Gd__gd_core_items__GingerbreadMan));
std::printf(",\"Gd__gd_core_items__GlovesofHaste\":[%zu,%zu]",sizeof(Gd__gd_core_items__GlovesofHaste),alignof(Gd__gd_core_items__GlovesofHaste));
std::printf(",\"Gd__gd_core_items__Goobert\":[%zu,%zu]",sizeof(Gd__gd_core_items__Goobert),alignof(Gd__gd_core_items__Goobert));
std::printf(",\"Gd__gd_core_items__Greatsword\":[%zu,%zu]",sizeof(Gd__gd_core_items__Greatsword),alignof(Gd__gd_core_items__Greatsword));
std::printf(",\"Gd__gd_core_items__Hammer\":[%zu,%zu]",sizeof(Gd__gd_core_items__Hammer),alignof(Gd__gd_core_items__Hammer));
std::printf(",\"Gd__gd_core_items__HealingHerbs\":[%zu,%zu]",sizeof(Gd__gd_core_items__HealingHerbs),alignof(Gd__gd_core_items__HealingHerbs));
std::printf(",\"Gd__gd_core_items__HealthPotion\":[%zu,%zu]",sizeof(Gd__gd_core_items__HealthPotion),alignof(Gd__gd_core_items__HealthPotion));
std::printf(",\"Gd__gd_core_items__HeartContainer\":[%zu,%zu]",sizeof(Gd__gd_core_items__HeartContainer),alignof(Gd__gd_core_items__HeartContainer));
std::printf(",\"Gd__gd_core_items__HeartofDarkness\":[%zu,%zu]",sizeof(Gd__gd_core_items__HeartofDarkness),alignof(Gd__gd_core_items__HeartofDarkness));
std::printf(",\"Gd__gd_core_items__HeroicPotion\":[%zu,%zu]",sizeof(Gd__gd_core_items__HeroicPotion),alignof(Gd__gd_core_items__HeroicPotion));
std::printf(",\"Gd__gd_core_items__HeroLongsword\":[%zu,%zu]",sizeof(Gd__gd_core_items__HeroLongsword),alignof(Gd__gd_core_items__HeroLongsword));
std::printf(",\"Gd__gd_core_items__HeroSword\":[%zu,%zu]",sizeof(Gd__gd_core_items__HeroSword),alignof(Gd__gd_core_items__HeroSword));
std::printf(",\"Gd__gd_core_items__HoloFireLizard\":[%zu,%zu]",sizeof(Gd__gd_core_items__HoloFireLizard),alignof(Gd__gd_core_items__HoloFireLizard));
std::printf(",\"Gd__gd_core_items__HolyArmor\":[%zu,%zu]",sizeof(Gd__gd_core_items__HolyArmor),alignof(Gd__gd_core_items__HolyArmor));
std::printf(",\"Gd__gd_core_items__HolySpear\":[%zu,%zu]",sizeof(Gd__gd_core_items__HolySpear),alignof(Gd__gd_core_items__HolySpear));
std::printf(",\"Gd__gd_core_items__HungryBlade\":[%zu,%zu]",sizeof(Gd__gd_core_items__HungryBlade),alignof(Gd__gd_core_items__HungryBlade));
std::printf(",\"Gd__gd_core_items__Item\":[%zu,%zu]",sizeof(Gd__gd_core_items__Item),alignof(Gd__gd_core_items__Item));
std::printf(",\"Gd__gd_core_items__Item__INNER__SignalConnection\":[%zu,%zu]",sizeof(Gd__gd_core_items__Item__INNER__SignalConnection),alignof(Gd__gd_core_items__Item__INNER__SignalConnection));
std::printf(",\"Gd__gd_core_items__Jynxtorquilla\":[%zu,%zu]",sizeof(Gd__gd_core_items__Jynxtorquilla),alignof(Gd__gd_core_items__Jynxtorquilla));
std::printf(",\"Gd__gd_core_items__LeatherArmor\":[%zu,%zu]",sizeof(Gd__gd_core_items__LeatherArmor),alignof(Gd__gd_core_items__LeatherArmor));
std::printf(",\"Gd__gd_core_items__LeatherBoots\":[%zu,%zu]",sizeof(Gd__gd_core_items__LeatherBoots),alignof(Gd__gd_core_items__LeatherBoots));
std::printf(",\"Gd__gd_core_items__LeatherHelm\":[%zu,%zu]",sizeof(Gd__gd_core_items__LeatherHelm),alignof(Gd__gd_core_items__LeatherHelm));
std::printf(",\"Gd__gd_core_items__LightGoobert\":[%zu,%zu]",sizeof(Gd__gd_core_items__LightGoobert),alignof(Gd__gd_core_items__LightGoobert));
std::printf(",\"Gd__gd_core_items__Lightsaber\":[%zu,%zu]",sizeof(Gd__gd_core_items__Lightsaber),alignof(Gd__gd_core_items__Lightsaber));
std::printf(",\"Gd__gd_core_items__LuckyBow\":[%zu,%zu]",sizeof(Gd__gd_core_items__LuckyBow),alignof(Gd__gd_core_items__LuckyBow));
std::printf(",\"Gd__gd_core_items__LuckyClover\":[%zu,%zu]",sizeof(Gd__gd_core_items__LuckyClover),alignof(Gd__gd_core_items__LuckyClover));
std::printf(",\"Gd__gd_core_items__LuckyPiggy\":[%zu,%zu]",sizeof(Gd__gd_core_items__LuckyPiggy),alignof(Gd__gd_core_items__LuckyPiggy));
std::printf(",\"Gd__gd_core_items__MagicStaff\":[%zu,%zu]",sizeof(Gd__gd_core_items__MagicStaff),alignof(Gd__gd_core_items__MagicStaff));
std::printf(",\"Gd__gd_core_items__MagicTorch\":[%zu,%zu]",sizeof(Gd__gd_core_items__MagicTorch),alignof(Gd__gd_core_items__MagicTorch));
std::printf(",\"Gd__gd_core_items__ManaOrb\":[%zu,%zu]",sizeof(Gd__gd_core_items__ManaOrb),alignof(Gd__gd_core_items__ManaOrb));
std::printf(",\"Gd__gd_core_items__ManaPotion\":[%zu,%zu]",sizeof(Gd__gd_core_items__ManaPotion),alignof(Gd__gd_core_items__ManaPotion));
std::printf(",\"Gd__gd_core_items__Manathirst\":[%zu,%zu]",sizeof(Gd__gd_core_items__Manathirst),alignof(Gd__gd_core_items__Manathirst));
std::printf(",\"Gd__gd_core_items__MoonShield\":[%zu,%zu]",sizeof(Gd__gd_core_items__MoonShield),alignof(Gd__gd_core_items__MoonShield));
std::printf(",\"Gd__gd_core_items__MrStruggles\":[%zu,%zu]",sizeof(Gd__gd_core_items__MrStruggles),alignof(Gd__gd_core_items__MrStruggles));
std::printf(",\"Gd__gd_core_items__Pan\":[%zu,%zu]",sizeof(Gd__gd_core_items__Pan),alignof(Gd__gd_core_items__Pan));
std::printf(",\"Gd__gd_core_items__Pandamonium\":[%zu,%zu]",sizeof(Gd__gd_core_items__Pandamonium),alignof(Gd__gd_core_items__Pandamonium));
std::printf(",\"Gd__gd_core_items__PestilenceFlask\":[%zu,%zu]",sizeof(Gd__gd_core_items__PestilenceFlask),alignof(Gd__gd_core_items__PestilenceFlask));
std::printf(",\"Gd__gd_core_items__PiercingArrow\":[%zu,%zu]",sizeof(Gd__gd_core_items__PiercingArrow),alignof(Gd__gd_core_items__PiercingArrow));
std::printf(",\"Gd__gd_core_items__Piggybank\":[%zu,%zu]",sizeof(Gd__gd_core_items__Piggybank),alignof(Gd__gd_core_items__Piggybank));
std::printf(",\"Gd__gd_core_items__Pineapple\":[%zu,%zu]",sizeof(Gd__gd_core_items__Pineapple),alignof(Gd__gd_core_items__Pineapple));
std::printf(",\"Gd__gd_core_items__PlatinCustomerCard\":[%zu,%zu]",sizeof(Gd__gd_core_items__PlatinCustomerCard),alignof(Gd__gd_core_items__PlatinCustomerCard));
std::printf(",\"Gd__gd_core_items__PocketSand\":[%zu,%zu]",sizeof(Gd__gd_core_items__PocketSand),alignof(Gd__gd_core_items__PocketSand));
std::printf(",\"Gd__gd_core_items__PoisonBow\":[%zu,%zu]",sizeof(Gd__gd_core_items__PoisonBow),alignof(Gd__gd_core_items__PoisonBow));
std::printf(",\"Gd__gd_core_items__PoisonDagger\":[%zu,%zu]",sizeof(Gd__gd_core_items__PoisonDagger),alignof(Gd__gd_core_items__PoisonDagger));
std::printf(",\"Gd__gd_core_items__PoisonGoobert\":[%zu,%zu]",sizeof(Gd__gd_core_items__PoisonGoobert),alignof(Gd__gd_core_items__PoisonGoobert));
std::printf(",\"Gd__gd_core_items__PoisonIvy\":[%zu,%zu]",sizeof(Gd__gd_core_items__PoisonIvy),alignof(Gd__gd_core_items__PoisonIvy));
std::printf(",\"Gd__gd_core_items__Potion\":[%zu,%zu]",sizeof(Gd__gd_core_items__Potion),alignof(Gd__gd_core_items__Potion));
std::printf(",\"Gd__gd_core_items__PotionBelt\":[%zu,%zu]",sizeof(Gd__gd_core_items__PotionBelt),alignof(Gd__gd_core_items__PotionBelt));
std::printf(",\"Gd__gd_core_items__Present\":[%zu,%zu]",sizeof(Gd__gd_core_items__Present),alignof(Gd__gd_core_items__Present));
std::printf(",\"Gd__gd_core_items__ProtectivePurse\":[%zu,%zu]",sizeof(Gd__gd_core_items__ProtectivePurse),alignof(Gd__gd_core_items__ProtectivePurse));
std::printf(",\"Gd__gd_core_items__Pumpkin\":[%zu,%zu]",sizeof(Gd__gd_core_items__Pumpkin),alignof(Gd__gd_core_items__Pumpkin));
std::printf(",\"Gd__gd_core_items__RainbowGoobert\":[%zu,%zu]",sizeof(Gd__gd_core_items__RainbowGoobert),alignof(Gd__gd_core_items__RainbowGoobert));
std::printf(",\"Gd__gd_core_items__RainbowGoobertRanger\":[%zu,%zu]",sizeof(Gd__gd_core_items__RainbowGoobertRanger),alignof(Gd__gd_core_items__RainbowGoobertRanger));
std::printf(",\"Gd__gd_core_items__RangerBag\":[%zu,%zu]",sizeof(Gd__gd_core_items__RangerBag),alignof(Gd__gd_core_items__RangerBag));
std::printf(",\"Gd__gd_core_items__RangerCollar\":[%zu,%zu]",sizeof(Gd__gd_core_items__RangerCollar),alignof(Gd__gd_core_items__RangerCollar));
std::printf(",\"Gd__gd_core_items__RibSawBlade\":[%zu,%zu]",sizeof(Gd__gd_core_items__RibSawBlade),alignof(Gd__gd_core_items__RibSawBlade));
std::printf(",\"Gd__gd_core_items__RubyChonk\":[%zu,%zu]",sizeof(Gd__gd_core_items__RubyChonk),alignof(Gd__gd_core_items__RubyChonk));
std::printf(",\"Gd__gd_core_items__RubyEgg\":[%zu,%zu]",sizeof(Gd__gd_core_items__RubyEgg),alignof(Gd__gd_core_items__RubyEgg));
std::printf(",\"Gd__gd_core_items__RubyWhelp\":[%zu,%zu]",sizeof(Gd__gd_core_items__RubyWhelp),alignof(Gd__gd_core_items__RubyWhelp));
std::printf(",\"Gd__gd_core_items__Shield\":[%zu,%zu]",sizeof(Gd__gd_core_items__Shield),alignof(Gd__gd_core_items__Shield));
std::printf(",\"Gd__gd_core_items__ShieldofValor\":[%zu,%zu]",sizeof(Gd__gd_core_items__ShieldofValor),alignof(Gd__gd_core_items__ShieldofValor));
std::printf(",\"Gd__gd_core_items__Shovel\":[%zu,%zu]",sizeof(Gd__gd_core_items__Shovel),alignof(Gd__gd_core_items__Shovel));
std::printf(",\"Gd__gd_core_items__Spear\":[%zu,%zu]",sizeof(Gd__gd_core_items__Spear),alignof(Gd__gd_core_items__Spear));
std::printf(",\"Gd__gd_core_items__SpectralDagger\":[%zu,%zu]",sizeof(Gd__gd_core_items__SpectralDagger),alignof(Gd__gd_core_items__SpectralDagger));
std::printf(",\"Gd__gd_core_items__SpikedShield\":[%zu,%zu]",sizeof(Gd__gd_core_items__SpikedShield),alignof(Gd__gd_core_items__SpikedShield));
std::printf(",\"Gd__gd_core_items__StaffofUnhealing\":[%zu,%zu]",sizeof(Gd__gd_core_items__StaffofUnhealing),alignof(Gd__gd_core_items__StaffofUnhealing));
std::printf(",\"Gd__gd_core_items__StaminaSack\":[%zu,%zu]",sizeof(Gd__gd_core_items__StaminaSack),alignof(Gd__gd_core_items__StaminaSack));
std::printf(",\"Gd__gd_core_items__SteelGoobert\":[%zu,%zu]",sizeof(Gd__gd_core_items__SteelGoobert),alignof(Gd__gd_core_items__SteelGoobert));
std::printf(",\"Gd__gd_core_items__Stone\":[%zu,%zu]",sizeof(Gd__gd_core_items__Stone),alignof(Gd__gd_core_items__Stone));
std::printf(",\"Gd__gd_core_items__StoneHelm\":[%zu,%zu]",sizeof(Gd__gd_core_items__StoneHelm),alignof(Gd__gd_core_items__StoneHelm));
std::printf(",\"Gd__gd_core_items__StoneSkinPotion\":[%zu,%zu]",sizeof(Gd__gd_core_items__StoneSkinPotion),alignof(Gd__gd_core_items__StoneSkinPotion));
std::printf(",\"Gd__gd_core_items__StorageCoffin\":[%zu,%zu]",sizeof(Gd__gd_core_items__StorageCoffin),alignof(Gd__gd_core_items__StorageCoffin));
std::printf(",\"Gd__gd_core_items__StrongDemonicFlask\":[%zu,%zu]",sizeof(Gd__gd_core_items__StrongDemonicFlask),alignof(Gd__gd_core_items__StrongDemonicFlask));
std::printf(",\"Gd__gd_core_items__StrongHealthPotion\":[%zu,%zu]",sizeof(Gd__gd_core_items__StrongHealthPotion),alignof(Gd__gd_core_items__StrongHealthPotion));
std::printf(",\"Gd__gd_core_items__StrongPestilenceFlask\":[%zu,%zu]",sizeof(Gd__gd_core_items__StrongPestilenceFlask),alignof(Gd__gd_core_items__StrongPestilenceFlask));
std::printf(",\"Gd__gd_core_items__StrongStoneSkinPotion\":[%zu,%zu]",sizeof(Gd__gd_core_items__StrongStoneSkinPotion),alignof(Gd__gd_core_items__StrongStoneSkinPotion));
std::printf(",\"Gd__gd_core_items__TheFool\":[%zu,%zu]",sizeof(Gd__gd_core_items__TheFool),alignof(Gd__gd_core_items__TheFool));
std::printf(",\"Gd__gd_core_items__TheLovers\":[%zu,%zu]",sizeof(Gd__gd_core_items__TheLovers),alignof(Gd__gd_core_items__TheLovers));
std::printf(",\"Gd__gd_core_items__ThornBow\":[%zu,%zu]",sizeof(Gd__gd_core_items__ThornBow),alignof(Gd__gd_core_items__ThornBow));
std::printf(",\"Gd__gd_core_items__ThornWhip\":[%zu,%zu]",sizeof(Gd__gd_core_items__ThornWhip),alignof(Gd__gd_core_items__ThornWhip));
std::printf(",\"Gd__gd_core_items__Torch\":[%zu,%zu]",sizeof(Gd__gd_core_items__Torch),alignof(Gd__gd_core_items__Torch));
std::printf(",\"Gd__gd_core_items__VampiricArmor\":[%zu,%zu]",sizeof(Gd__gd_core_items__VampiricArmor),alignof(Gd__gd_core_items__VampiricArmor));
std::printf(",\"Gd__gd_core_items__VampiricGloves\":[%zu,%zu]",sizeof(Gd__gd_core_items__VampiricGloves),alignof(Gd__gd_core_items__VampiricGloves));
std::printf(",\"Gd__gd_core_items__VampiricScythe\":[%zu,%zu]",sizeof(Gd__gd_core_items__VampiricScythe),alignof(Gd__gd_core_items__VampiricScythe));
std::printf(",\"Gd__gd_core_items__VillainSword\":[%zu,%zu]",sizeof(Gd__gd_core_items__VillainSword),alignof(Gd__gd_core_items__VillainSword));
std::printf(",\"Gd__gd_core_items__WalrusTusk\":[%zu,%zu]",sizeof(Gd__gd_core_items__WalrusTusk),alignof(Gd__gd_core_items__WalrusTusk));
std::printf(",\"Gd__gd_core_items__Weapon\":[%zu,%zu]",sizeof(Gd__gd_core_items__Weapon),alignof(Gd__gd_core_items__Weapon));
std::printf(",\"Gd__gd_core_items__Whetstone\":[%zu,%zu]",sizeof(Gd__gd_core_items__Whetstone),alignof(Gd__gd_core_items__Whetstone));
std::printf(",\"Gd__gd_core_items__White_EyesBlueDragon\":[%zu,%zu]",sizeof(Gd__gd_core_items__White_EyesBlueDragon),alignof(Gd__gd_core_items__White_EyesBlueDragon));
std::printf(",\"Gd__gd_core_items__Wolpertinger\":[%zu,%zu]",sizeof(Gd__gd_core_items__Wolpertinger),alignof(Gd__gd_core_items__Wolpertinger));
std::printf(",\"Gd__gd_core_items__WoodenBuckler\":[%zu,%zu]",sizeof(Gd__gd_core_items__WoodenBuckler),alignof(Gd__gd_core_items__WoodenBuckler));
std::printf(",\"Gd__gd_core_items__WoodenSword\":[%zu,%zu]",sizeof(Gd__gd_core_items__WoodenSword),alignof(Gd__gd_core_items__WoodenSword));
std::printf(",\"Gd__gd_core_items__YggdrasilLeaf\":[%zu,%zu]",sizeof(Gd__gd_core_items__YggdrasilLeaf),alignof(Gd__gd_core_items__YggdrasilLeaf));
std::printf("},\"offsets\":{");
std::printf("\"CoreItem\":{");
std::printf("\"f_descriptor\":%zu",offsetof(Gd__gd_core__CoreItem,f_descriptor));
std::printf(",\"f_ctx\":%zu",offsetof(Gd__gd_core__CoreItem,f_ctx));
std::printf(",\"f_character_\":%zu",offsetof(Gd__gd_core__CoreItem,f_character_));
std::printf(",\"f_inventory\":%zu",offsetof(Gd__gd_core__CoreItem,f_inventory));
std::printf(",\"f_placed\":%zu",offsetof(Gd__gd_core__CoreItem,f_placed));
std::printf(",\"f_name\":%zu",offsetof(Gd__gd_core__CoreItem,f_name));
std::printf(",\"f_chargeFrame\":%zu",offsetof(Gd__gd_core__CoreItem,f_chargeFrame));
std::printf(",\"f_speedScale\":%zu",offsetof(Gd__gd_core__CoreItem,f_speedScale));
std::printf(",\"f_bonusMaxDam\":%zu",offsetof(Gd__gd_core__CoreItem,f_bonusMaxDam));
std::printf(",\"f_bonusMinDam\":%zu",offsetof(Gd__gd_core__CoreItem,f_bonusMinDam));
std::printf(",\"f_removableDam\":%zu",offsetof(Gd__gd_core__CoreItem,f_removableDam));
std::printf(",\"f_bonusDamageFactor\":%zu",offsetof(Gd__gd_core__CoreItem,f_bonusDamageFactor));
std::printf(",\"f_staminaFactor\":%zu",offsetof(Gd__gd_core__CoreItem,f_staminaFactor));
std::printf(",\"f_critChancePercent\":%zu",offsetof(Gd__gd_core__CoreItem,f_critChancePercent));
std::printf(",\"f_critTokens\":%zu",offsetof(Gd__gd_core__CoreItem,f_critTokens));
std::printf(",\"f_critSeverity\":%zu",offsetof(Gd__gd_core__CoreItem,f_critSeverity));
std::printf(",\"f_bonusChancePercent_mult\":%zu",offsetof(Gd__gd_core__CoreItem,f_bonusChancePercent_mult));
std::printf(",\"f_bonusChancePercent_additive1\":%zu",offsetof(Gd__gd_core__CoreItem,f_bonusChancePercent_additive1));
std::printf(",\"f_bonusChancePercent_additive2\":%zu",offsetof(Gd__gd_core__CoreItem,f_bonusChancePercent_additive2));
std::printf(",\"f_bonusAccuracy\":%zu",offsetof(Gd__gd_core__CoreItem,f_bonusAccuracy));
std::printf(",\"f_buffPowers\":%zu",offsetof(Gd__gd_core__CoreItem,f_buffPowers));
std::printf(",\"f_buffAmplificationChances\":%zu",offsetof(Gd__gd_core__CoreItem,f_buffAmplificationChances));
std::printf(",\"f_damageSource\":%zu",offsetof(Gd__gd_core__CoreItem,f_damageSource));
std::printf(",\"f_doubleActivationChance\":%zu",offsetof(Gd__gd_core__CoreItem,f_doubleActivationChance));
std::printf(",\"f_doubleAttackEffectChance\":%zu",offsetof(Gd__gd_core__CoreItem,f_doubleAttackEffectChance));
std::printf(",\"f_paramMult\":%zu",offsetof(Gd__gd_core__CoreItem,f_paramMult));
std::printf(",\"f_paramAdd\":%zu",offsetof(Gd__gd_core__CoreItem,f_paramAdd));
std::printf(",\"f_numCharges\":%zu",offsetof(Gd__gd_core__CoreItem,f_numCharges));
std::printf(",\"f_baseCooldownOverride\":%zu",offsetof(Gd__gd_core__CoreItem,f_baseCooldownOverride));
std::printf(",\"f_chanceRng\":%zu",offsetof(Gd__gd_core__CoreItem,f_chanceRng));
std::printf(",\"f_damageRangeRng\":%zu",offsetof(Gd__gd_core__CoreItem,f_damageRangeRng));
std::printf(",\"f_statDisplayOverrides\":%zu",offsetof(Gd__gd_core__CoreItem,f_statDisplayOverrides));
std::printf(",\"f_lastActivationTime\":%zu",offsetof(Gd__gd_core__CoreItem,f_lastActivationTime));
std::printf(",\"f_activationsThisFrame\":%zu",offsetof(Gd__gd_core__CoreItem,f_activationsThisFrame));
std::printf(",\"f_lastTriggerTime\":%zu",offsetof(Gd__gd_core__CoreItem,f_lastTriggerTime));
std::printf(",\"f_triggersThisFrame\":%zu",offsetof(Gd__gd_core__CoreItem,f_triggersThisFrame));
std::printf(",\"f_triggerTime\":%zu",offsetof(Gd__gd_core__CoreItem,f_triggerTime));
std::printf(",\"f_iterationCooldown\":%zu",offsetof(Gd__gd_core__CoreItem,f_iterationCooldown));
std::printf(",\"f_itemMetrics\":%zu",offsetof(Gd__gd_core__CoreItem,f_itemMetrics));
std::printf(",\"f__grid\":%zu",offsetof(Gd__gd_core__CoreItem,f__grid));
std::printf(",\"f__behavior\":%zu",offsetof(Gd__gd_core__CoreItem,f__behavior));
std::printf(",\"f__cooldown_changed_epoch\":%zu",offsetof(Gd__gd_core__CoreItem,f__cooldown_changed_epoch));
std::printf(",\"f__cooldown_blocked_epoch\":%zu",offsetof(Gd__gd_core__CoreItem,f__cooldown_blocked_epoch));
std::printf(",\"f_dynamicTypes\":%zu",offsetof(Gd__gd_core__CoreItem,f_dynamicTypes));
std::printf(",\"f_combatConnections\":%zu",offsetof(Gd__gd_core__CoreItem,f_combatConnections));
std::printf(",\"f_ownerType\":%zu",offsetof(Gd__gd_core__CoreItem,f_ownerType));
std::printf(",\"f_placedByPlayer\":%zu",offsetof(Gd__gd_core__CoreItem,f_placedByPlayer));
std::printf(",\"f_dragged\":%zu",offsetof(Gd__gd_core__CoreItem,f_dragged));
std::printf(",\"f_occupiedCells\":%zu",offsetof(Gd__gd_core__CoreItem,f_occupiedCells));
std::printf(",\"f_collisionCells\":%zu",offsetof(Gd__gd_core__CoreItem,f_collisionCells));
std::printf(",\"f_extensionCells\":%zu",offsetof(Gd__gd_core__CoreItem,f_extensionCells));
std::printf(",\"f_affectedExtensionCells\":%zu",offsetof(Gd__gd_core__CoreItem,f_affectedExtensionCells));
std::printf(",\"f_affectedCellsCache\":%zu",offsetof(Gd__gd_core__CoreItem,f_affectedCellsCache));
std::printf(",\"f_currentAffectedItems\":%zu",offsetof(Gd__gd_core__CoreItem,f_currentAffectedItems));
std::printf(",\"f_cachedAffectedItems\":%zu",offsetof(Gd__gd_core__CoreItem,f_cachedAffectedItems));
std::printf(",\"f_affectedTileCells\":%zu",offsetof(Gd__gd_core__CoreItem,f_affectedTileCells));
std::printf(",\"f_consumed\":%zu",offsetof(Gd__gd_core__CoreItem,f_consumed));
std::printf(",\"f_hasPreDealDamageEarlyEffect\":%zu",offsetof(Gd__gd_core__CoreItem,f_hasPreDealDamageEarlyEffect));
std::printf(",\"f_hasPreDealDamageLateEffect\":%zu",offsetof(Gd__gd_core__CoreItem,f_hasPreDealDamageLateEffect));
std::printf(",\"f_hasDealtDamageEffect\":%zu",offsetof(Gd__gd_core__CoreItem,f_hasDealtDamageEffect));
std::printf(",\"f_hasOnChargeReceivedEffect\":%zu",offsetof(Gd__gd_core__CoreItem,f_hasOnChargeReceivedEffect));
std::printf(",\"f_hasOnChargeLeftEffect\":%zu",offsetof(Gd__gd_core__CoreItem,f_hasOnChargeLeftEffect));
std::printf(",\"f_gems\":%zu",offsetof(Gd__gd_core__CoreItem,f_gems));
std::printf(",\"f__cooldown_active\":%zu",offsetof(Gd__gd_core__CoreItem,f__cooldown_active));
std::printf(",\"f_buffLabelPositionTimestamps\":%zu",offsetof(Gd__gd_core__CoreItem,f_buffLabelPositionTimestamps));
std::printf(",\"f_replacementPending\":%zu",offsetof(Gd__gd_core__CoreItem,f_replacementPending));
std::printf(",\"f_faceDirection\":%zu",offsetof(Gd__gd_core__CoreItem,f_faceDirection));
std::printf(",\"f_rotation\":%zu",offsetof(Gd__gd_core__CoreItem,f_rotation));
std::printf(",\"f_timers\":%zu",offsetof(Gd__gd_core__CoreItem,f_timers));
std::printf(",\"native_display_header_\":%zu",offsetof(Gd__gd_core__CoreItem,native_display_header_));
std::printf(",\"native_display_values_\":%zu",offsetof(Gd__gd_core__CoreItem,native_display_values_));
std::printf(",\"native_timer_header_\":%zu",offsetof(Gd__gd_core__CoreItem,native_timer_header_));
std::printf(",\"native_bridge_gems_header_\":%zu",offsetof(Gd__gd_core__CoreItem,native_bridge_gems_header_));
std::printf("}");
std::printf(",\"CoreCharacter\":{");
std::printf("\"f_ctx\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_ctx));
std::printf(",\"f_playerId\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_playerId));
std::printf(",\"f_opponent\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_opponent));
std::printf(",\"f_isDead\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_isDead));
std::printf(",\"f_buffs\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_buffs));
std::printf(",\"f_maxHealth\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_maxHealth));
std::printf(",\"f_curHealth\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_curHealth));
std::printf(",\"f_temporaryMaxHealth\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_temporaryMaxHealth));
std::printf(",\"f_temporaryMaxHealthGain\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_temporaryMaxHealthGain));
std::printf(",\"f_baseMaxStamina\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_baseMaxStamina));
std::printf(",\"f_maxStamina\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_maxStamina));
std::printf(",\"f_curStamina\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_curStamina));
std::printf(",\"f_temporaryMaxStamina\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_temporaryMaxStamina));
std::printf(",\"f_baseStaminaRegen\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_baseStaminaRegen));
std::printf(",\"f_staminaRegen\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_staminaRegen));
std::printf(",\"f_allowStaminaOverflow\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_allowStaminaOverflow));
std::printf(",\"f_staminaUpdateQueued\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_staminaUpdateQueued));
std::printf(",\"f_statsDisplay\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_statsDisplay));
std::printf(",\"f_damageResistance\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_damageResistance));
std::printf(",\"f_damageReduction\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_damageReduction));
std::printf(",\"f_invulnerable\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_invulnerable));
std::printf(",\"f_dodgeStacks\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_dodgeStacks));
std::printf(",\"f_critResistance\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_critResistance));
std::printf(",\"f_critResistStacks\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_critResistStacks));
std::printf(",\"f_critTokens\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_critTokens));
std::printf(",\"f_stunResistance\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_stunResistance));
std::printf(",\"f_unhealingAmount\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_unhealingAmount));
std::printf(",\"f_healingEfficiency\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_healingEfficiency));
std::printf(",\"f_critTokensUsed\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_critTokensUsed));
std::printf(",\"f_debuffResistStacks\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_debuffResistStacks));
std::printf(",\"f_debuffReflectStacks\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_debuffReflectStacks));
std::printf(",\"f_buffProtectStacks\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_buffProtectStacks));
std::printf(",\"f_bonusFatigueDamage\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_bonusFatigueDamage));
std::printf(",\"f_empowerDamage\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_empowerDamage));
std::printf(",\"f_blindingLightActive\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_blindingLightActive));
std::printf(",\"f_stunnedDuration\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_stunnedDuration));
std::printf(",\"f_tickCounter\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_tickCounter));
std::printf(",\"f_typedDamageFactors\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_typedDamageFactors));
std::printf(",\"f_meleeSpikesLimit\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_meleeSpikesLimit));
std::printf(",\"f_rangedSpikesLimit\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_rangedSpikesLimit));
std::printf(",\"f_effectSpikesLimit\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_effectSpikesLimit));
std::printf(",\"f_meleeVampirismLimit\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_meleeVampirismLimit));
std::printf(",\"f_rangedVampirismLimit\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_rangedVampirismLimit));
std::printf(",\"f_battleRageAura\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_battleRageAura));
std::printf(",\"f_battleRageBonusDur\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_battleRageBonusDur));
std::printf(",\"f_accuracyRng\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_accuracyRng));
std::printf(",\"f_critRng\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_critRng));
std::printf(",\"f_critResistanceRng\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_critResistanceRng));
std::printf(",\"f_stunResistanceRng\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_stunResistanceRng));
std::printf(",\"f_items\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_items));
std::printf(",\"f_inventory\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_inventory));
std::printf(",\"f_INVENTORY\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_INVENTORY));
std::printf(",\"f_character_died_handlers\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_character_died_handlers));
std::printf(",\"f_poisonDamageSource\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_poisonDamageSource));
std::printf(",\"f_spikeDamageSource\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_spikeDamageSource));
std::printf(",\"f_characterClass\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_characterClass));
std::printf(",\"f_chibi\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_chibi));
std::printf(",\"f_invulnerabilityItem\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_invulnerabilityItem));
std::printf(",\"f__invul_left\":%zu",offsetof(Gd__gd_core__CoreCharacter,f__invul_left));
std::printf(",\"f__invul_active\":%zu",offsetof(Gd__gd_core__CoreCharacter,f__invul_active));
std::printf(",\"f_autoRageItem\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_autoRageItem));
std::printf(",\"f__rage_left\":%zu",offsetof(Gd__gd_core__CoreCharacter,f__rage_left));
std::printf(",\"f__rage_active\":%zu",offsetof(Gd__gd_core__CoreCharacter,f__rage_active));
std::printf(",\"f__autoRage_left\":%zu",offsetof(Gd__gd_core__CoreCharacter,f__autoRage_left));
std::printf(",\"f__autoRage_active\":%zu",offsetof(Gd__gd_core__CoreCharacter,f__autoRage_active));
std::printf(",\"f__rage_wait\":%zu",offsetof(Gd__gd_core__CoreCharacter,f__rage_wait));
std::printf(",\"f__invul_wait\":%zu",offsetof(Gd__gd_core__CoreCharacter,f__invul_wait));
std::printf(",\"f_attack_moving_forward\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_attack_moving_forward));
std::printf(",\"f_attack_sound_ready_time\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_attack_sound_ready_time));
std::printf(",\"f__tick_timer_left\":%zu",offsetof(Gd__gd_core__CoreCharacter,f__tick_timer_left));
std::printf(",\"f__tick_timer_active\":%zu",offsetof(Gd__gd_core__CoreCharacter,f__tick_timer_active));
std::printf(",\"f_damage_anim_current\":%zu",offsetof(Gd__gd_core__CoreCharacter,f_damage_anim_current));
std::printf(",\"f__visual_x\":%zu",offsetof(Gd__gd_core__CoreCharacter,f__visual_x));
std::printf(",\"f__visual_y\":%zu",offsetof(Gd__gd_core__CoreCharacter,f__visual_y));
std::printf(",\"f__visual_from_x\":%zu",offsetof(Gd__gd_core__CoreCharacter,f__visual_from_x));
std::printf(",\"f__visual_from_y\":%zu",offsetof(Gd__gd_core__CoreCharacter,f__visual_from_y));
std::printf(",\"f__visual_to_x\":%zu",offsetof(Gd__gd_core__CoreCharacter,f__visual_to_x));
std::printf(",\"f__visual_to_y\":%zu",offsetof(Gd__gd_core__CoreCharacter,f__visual_to_y));
std::printf(",\"f__visual_forward\":%zu",offsetof(Gd__gd_core__CoreCharacter,f__visual_forward));
std::printf(",\"f__visual_back\":%zu",offsetof(Gd__gd_core__CoreCharacter,f__visual_back));
std::printf(",\"f__visual_elapsed\":%zu",offsetof(Gd__gd_core__CoreCharacter,f__visual_elapsed));
std::printf(",\"f__visual_kind\":%zu",offsetof(Gd__gd_core__CoreCharacter,f__visual_kind));
std::printf(",\"f__visual_stage\":%zu",offsetof(Gd__gd_core__CoreCharacter,f__visual_stage));
std::printf(",\"f__visual_generation\":%zu",offsetof(Gd__gd_core__CoreCharacter,f__visual_generation));
std::printf(",\"f__idle_animation_left\":%zu",offsetof(Gd__gd_core__CoreCharacter,f__idle_animation_left));
std::printf(",\"f__physics_timer_mask\":%zu",offsetof(Gd__gd_core__CoreCharacter,f__physics_timer_mask));
std::printf("}");
std::printf(",\"CoreBuff\":{");
std::printf("\"f_type\":%zu",offsetof(Gd__gd_core__CoreBuff,f_type));
std::printf(",\"f_isBuff\":%zu",offsetof(Gd__gd_core__CoreBuff,f_isBuff));
std::printf(",\"f_character\":%zu",offsetof(Gd__gd_core__CoreBuff,f_character));
std::printf(",\"f_current\":%zu",offsetof(Gd__gd_core__CoreBuff,f_current));
std::printf(",\"f_permanentStacks\":%zu",offsetof(Gd__gd_core__CoreBuff,f_permanentStacks));
std::printf(",\"f_resistChancePercent\":%zu",offsetof(Gd__gd_core__CoreBuff,f_resistChancePercent));
std::printf(",\"f_resistStacks\":%zu",offsetof(Gd__gd_core__CoreBuff,f_resistStacks));
std::printf(",\"f_reflectChancePercent\":%zu",offsetof(Gd__gd_core__CoreBuff,f_reflectChancePercent));
std::printf(",\"f_cleanseProtectionChancePercent\":%zu",offsetof(Gd__gd_core__CoreBuff,f_cleanseProtectionChancePercent));
std::printf(",\"f_signalName\":%zu",offsetof(Gd__gd_core__CoreBuff,f_signalName));
std::printf(",\"f_temporaryStacks\":%zu",offsetof(Gd__gd_core__CoreBuff,f_temporaryStacks));
std::printf(",\"f_nextTemporaryTimeout\":%zu",offsetof(Gd__gd_core__CoreBuff,f_nextTemporaryTimeout));
std::printf(",\"f_MAX_STACKS\":%zu",offsetof(Gd__gd_core__CoreBuff,f_MAX_STACKS));
std::printf(",\"f__timer_left\":%zu",offsetof(Gd__gd_core__CoreBuff,f__timer_left));
std::printf(",\"f__timer_active\":%zu",offsetof(Gd__gd_core__CoreBuff,f__timer_active));
std::printf(",\"f__timer_wait\":%zu",offsetof(Gd__gd_core__CoreBuff,f__timer_wait));
std::printf(",\"f__timer_first_pass\":%zu",offsetof(Gd__gd_core__CoreBuff,f__timer_first_pass));
std::printf(",\"f__timer_member_epoch\":%zu",offsetof(Gd__gd_core__CoreBuff,f__timer_member_epoch));
std::printf(",\"f_ctx\":%zu",offsetof(Gd__gd_core__CoreBuff,f_ctx));
std::printf("}");
std::printf(",\"CoreContext\":{");
std::printf("\"f_rng\":%zu",offsetof(Gd__gd_core__CoreContext,f_rng));
std::printf(",\"f_util\":%zu",offsetof(Gd__gd_core__CoreContext,f_util));
std::printf(",\"f_bus\":%zu",offsetof(Gd__gd_core__CoreContext,f_bus));
std::printf(",\"f_hooks\":%zu",offsetof(Gd__gd_core__CoreContext,f_hooks));
std::printf(",\"f_combat_log\":%zu",offsetof(Gd__gd_core__CoreContext,f_combat_log));
std::printf(",\"f_player\":%zu",offsetof(Gd__gd_core__CoreContext,f_player));
std::printf(",\"f_opponent\":%zu",offsetof(Gd__gd_core__CoreContext,f_opponent));
std::printf(",\"f_fight_ended\":%zu",offsetof(Gd__gd_core__CoreContext,f_fight_ended));
std::printf(",\"f_time\":%zu",offsetof(Gd__gd_core__CoreContext,f_time));
std::printf(",\"f_probe_pass\":%zu",offsetof(Gd__gd_core__CoreContext,f_probe_pass));
std::printf(",\"f_frame_counter\":%zu",offsetof(Gd__gd_core__CoreContext,f_frame_counter));
std::printf(",\"f_combat_time\":%zu",offsetof(Gd__gd_core__CoreContext,f_combat_time));
std::printf(",\"f_below_master\":%zu",offsetof(Gd__gd_core__CoreContext,f_below_master));
std::printf(",\"f_label_rng_enabled\":%zu",offsetof(Gd__gd_core__CoreContext,f_label_rng_enabled));
std::printf(",\"f_lobbies_mode\":%zu",offsetof(Gd__gd_core__CoreContext,f_lobbies_mode));
std::printf(",\"f_custom_health_multiplier\":%zu",offsetof(Gd__gd_core__CoreContext,f_custom_health_multiplier));
std::printf(",\"f__drawseq_enabled\":%zu",offsetof(Gd__gd_core__CoreContext,f__drawseq_enabled));
std::printf(",\"f_lib_fires\":%zu",offsetof(Gd__gd_core__CoreContext,f_lib_fires));
std::printf(",\"f_combat\":%zu",offsetof(Gd__gd_core__CoreContext,f_combat));
std::printf(",\"f_item_book\":%zu",offsetof(Gd__gd_core__CoreContext,f_item_book));
std::printf(",\"f_sandbag_active\":%zu",offsetof(Gd__gd_core__CoreContext,f_sandbag_active));
std::printf(",\"f_cur_mode\":%zu",offsetof(Gd__gd_core__CoreContext,f_cur_mode));
std::printf(",\"f_cur_round\":%zu",offsetof(Gd__gd_core__CoreContext,f_cur_round));
std::printf(",\"f_rope_speedups\":%zu",offsetof(Gd__gd_core__CoreContext,f_rope_speedups));
std::printf(",\"f_cube_advanced\":%zu",offsetof(Gd__gd_core__CoreContext,f_cube_advanced));
std::printf(",\"f_event_type_keys\":%zu",offsetof(Gd__gd_core__CoreContext,f_event_type_keys));
std::printf(",\"f_class_resources\":%zu",offsetof(Gd__gd_core__CoreContext,f_class_resources));
std::printf(",\"f_unhealingDamageSource\":%zu",offsetof(Gd__gd_core__CoreContext,f_unhealingDamageSource));
std::printf(",\"f_fatigueDamageSource\":%zu",offsetof(Gd__gd_core__CoreContext,f_fatigueDamageSource));
std::printf(",\"f_stealLifeDamageSource\":%zu",offsetof(Gd__gd_core__CoreContext,f_stealLifeDamageSource));
std::printf(",\"f_out_of_stamina_count\":%zu",offsetof(Gd__gd_core__CoreContext,f_out_of_stamina_count));
std::printf(",\"f_warn_unknown_api\":%zu",offsetof(Gd__gd_core__CoreContext,f_warn_unknown_api));
std::printf(",\"f_show_cooldown_progress\":%zu",offsetof(Gd__gd_core__CoreContext,f_show_cooldown_progress));
std::printf(",\"f__deferred\":%zu",offsetof(Gd__gd_core__CoreContext,f__deferred));
std::printf(",\"f__idle_frame_calls\":%zu",offsetof(Gd__gd_core__CoreContext,f__idle_frame_calls));
std::printf(",\"f__timed\":%zu",offsetof(Gd__gd_core__CoreContext,f__timed));
std::printf(",\"f_deferred_flush_enabled\":%zu",offsetof(Gd__gd_core__CoreContext,f_deferred_flush_enabled));
std::printf(",\"f_eb_relay_mirrored\":%zu",offsetof(Gd__gd_core__CoreContext,f_eb_relay_mirrored));
std::printf(",\"f_keyed_stop_clears_seen\":%zu",offsetof(Gd__gd_core__CoreContext,f_keyed_stop_clears_seen));
std::printf(",\"f_keyed_cleanse_biggest_first\":%zu",offsetof(Gd__gd_core__CoreContext,f_keyed_cleanse_biggest_first));
std::printf(",\"f__emptyGrid\":%zu",offsetof(Gd__gd_core__CoreContext,f__emptyGrid));
std::printf(",\"f_activation_rng_state\":%zu",offsetof(Gd__gd_core__CoreContext,f_activation_rng_state));
std::printf(",\"f_idle_timer_initial\":%zu",offsetof(Gd__gd_core__CoreContext,f_idle_timer_initial));
std::printf(",\"f_timer_pass_epoch\":%zu",offsetof(Gd__gd_core__CoreContext,f_timer_pass_epoch));
std::printf(",\"f_in_physics_timer_pass\":%zu",offsetof(Gd__gd_core__CoreContext,f_in_physics_timer_pass));
std::printf(",\"f_in_item_physics_pass\":%zu",offsetof(Gd__gd_core__CoreContext,f_in_item_physics_pass));
std::printf(",\"f_replay_buff_state\":%zu",offsetof(Gd__gd_core__CoreContext,f_replay_buff_state));
std::printf(",\"f_replay_engine_rng\":%zu",offsetof(Gd__gd_core__CoreContext,f_replay_engine_rng));
std::printf(",\"f_native_frame_rng\":%zu",offsetof(Gd__gd_core__CoreContext,f_native_frame_rng));
std::printf(",\"f_native_label_mode\":%zu",offsetof(Gd__gd_core__CoreContext,f_native_label_mode));
std::printf(",\"f_training_start\":%zu",offsetof(Gd__gd_core__CoreContext,f_training_start));
std::printf(",\"f_replay_native_scene_delays\":%zu",offsetof(Gd__gd_core__CoreContext,f_replay_native_scene_delays));
std::printf(",\"f__opening_delay_ready\":%zu",offsetof(Gd__gd_core__CoreContext,f__opening_delay_ready));
std::printf(",\"f_replay_util_time\":%zu",offsetof(Gd__gd_core__CoreContext,f_replay_util_time));
std::printf(",\"f__critical_shake_delta\":%zu",offsetof(Gd__gd_core__CoreContext,f__critical_shake_delta));
std::printf(",\"f__critical_shake_active\":%zu",offsetof(Gd__gd_core__CoreContext,f__critical_shake_active));
std::printf(",\"f__critical_shake_frame\":%zu",offsetof(Gd__gd_core__CoreContext,f__critical_shake_frame));
std::printf(",\"f__critical_shake_after_idle\":%zu",offsetof(Gd__gd_core__CoreContext,f__critical_shake_after_idle));
std::printf(",\"f__particle_draws\":%zu",offsetof(Gd__gd_core__CoreContext,f__particle_draws));
std::printf(",\"f_particle_draw_frame\":%zu",offsetof(Gd__gd_core__CoreContext,f_particle_draw_frame));
std::printf(",\"f__particle_pending_draws\":%zu",offsetof(Gd__gd_core__CoreContext,f__particle_pending_draws));
std::printf(",\"f__particle_before_physics\":%zu",offsetof(Gd__gd_core__CoreContext,f__particle_before_physics));
std::printf(",\"f__motion_queue\":%zu",offsetof(Gd__gd_core__CoreContext,f__motion_queue));
std::printf(",\"f_flicker_initial\":%zu",offsetof(Gd__gd_core__CoreContext,f_flicker_initial));
std::printf(",\"f__flickers\":%zu",offsetof(Gd__gd_core__CoreContext,f__flickers));
std::printf(",\"f__opponent_flickers\":%zu",offsetof(Gd__gd_core__CoreContext,f__opponent_flickers));
std::printf("}");
std::printf("}}\n");}
