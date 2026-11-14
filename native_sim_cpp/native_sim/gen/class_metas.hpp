#pragma once
#include "../gd_rt.hpp"

enum GenClsId : gd::ClsId {
    CLS_GEN_START = 1,
    CLS_Gd__gd_core__CoreItem,
    CLS_Gd__gd_core__Item,
    CLS_Gd__gd_core__Card,
    CLS_Gd__gd_core__AceofSpades,
    CLS_Gd__gd_core__RangerCollar,
    CLS_Gd__gd_core__AcornCollar,
    CLS_Gd__gd_core_items__Item,
    CLS_Gd__gd_core_items__Stone,
    CLS_Gd__gd_core__ArtifactStoneCold,
    CLS_Gd__gd_core__ArtifactStoneHeat,
    CLS_Gd__gd_core__Bag,
    CLS_Gd__gd_core__BagofStones,
    CLS_Gd__gd_core__Food,
    CLS_Gd__gd_core__Banana,
    CLS_Gd__gd_core__BloodAmulet,
    CLS_Gd__gd_core__Goobert,
    CLS_Gd__gd_core__BloodGoobert,
    CLS_Gd__gd_core__Weapon,
    CLS_Gd__gd_core__Bloodthorne,
    CLS_Gd__gd_core__Dagger,
    CLS_Gd__gd_core__BloodyDagger,
    CLS_Gd__gd_core__Blueberries,
    CLS_Gd__gd_core__Bow,
    CLS_Gd__gd_core__BowandArrow,
    CLS_Gd__gd_core__BoxofRiches,
    CLS_Gd__gd_core__Broom,
    CLS_Gd__gd_core_items__Gems__Gem,
    CLS_Gd__gd_core__BurningCoal,
    CLS_Gd__gd_core__BurningTorch,
    CLS_Gd__gd_core__Carrot,
    CLS_Gd__gd_core__CarrotGoobert,
    CLS_Gd__gd_core__ClawsofAttack,
    CLS_Gd__gd_core__CoreBuff,
    CLS_Gd__gd_core__CoreBuff__INNER__TemporaryStacks,
    CLS_Gd__gd_core__CoreCharacter,
    CLS_Gd__gd_core__CoreCombat,
    CLS_Gd__gd_core__CoreCombat__INNER__CoreItemSort,
    CLS_Gd__gd_core__CoreCombatLog,
    CLS_Gd__gd_core__CoreConst,
    CLS_Gd__gd_core__CoreContext,
    CLS_Gd__gd_core__CoreDamageResult,
    CLS_Gd__gd_core__CoreDamageSource,
    CLS_Gd__gd_core__CoreEvent,
    CLS_Gd__gd_core__CoreEventBus,
    CLS_Gd__gd_core__CoreGrid,
    CLS_Gd__gd_core__CoreHooks,
    CLS_Gd__gd_core__CoreItem__INNER__CoreElectricalCharge,
    CLS_Gd__gd_core__CoreItem__INNER__CoreSignalConnection,
    CLS_Gd__gd_core__CoreItemBook,
    CLS_Gd__gd_core__CoreItemData,
    CLS_Gd__gd_core__CoreRng,
    CLS_Gd__gd_core__CoreRng__INNER__BalancedRng,
    CLS_Gd__gd_core__CoreRng__INNER__BalancedRange,
    CLS_Gd__gd_core__CoreTimer,
    CLS_Gd__gd_core__CoreUtil,
    CLS_Gd__gd_core__CoreUtil__INNER__DictSorter,
    CLS_Gd__gd_core__CorruptedArmor,
    CLS_Gd__gd_core__CritwoodStaff,
    CLS_Gd__gd_core__Crossblades,
    CLS_Gd__gd_core__Crown,
    CLS_Gd__gd_core__CursedDagger,
    CLS_Gd__gd_core__CursedHairComb,
    CLS_Gd__gd_core__CustomerCard,
    CLS_Gd__gd_core__DancingDragon,
    CLS_Gd__gd_core__DarkestLotus,
    CLS_Gd__gd_core__Darksaber,
    CLS_Gd__gd_core__DeathScythe,
    CLS_Gd__gd_core__DeckofCards,
    CLS_Gd__gd_core__Potion,
    CLS_Gd__gd_core__DemonicFlask,
    CLS_Gd__gd_core__DjinnLamp,
    CLS_Gd__gd_core__DragonEgg,
    CLS_Gd__gd_core_items__Weapon,
    CLS_Gd__gd_core_items__Pan,
    CLS_Gd__gd_core__Eggscalibur,
    CLS_Gd__gd_core__EvilCap,
    CLS_Gd__gd_core__FalconBlade,
    CLS_Gd__gd_core__FancyFencingRapier,
    CLS_Gd__gd_core__Fanfare,
    CLS_Gd__gd_core__FannyPack,
    CLS_Gd__gd_core__Flute,
    CLS_Gd__gd_core__FlyAgaric,
    CLS_Gd__gd_core__Garlic,
    CLS_Gd__gd_core__GingerbreadMan,
    CLS_Gd__gd_core__GlovesofHaste,
    CLS_Gd__gd_core__Greatsword,
    CLS_Gd__gd_core__Hammer,
    CLS_Gd__gd_core__HealingHerbs,
    CLS_Gd__gd_core__HealthPotion,
    CLS_Gd__gd_core__HeartContainer,
    CLS_Gd__gd_core__HeartofDarkness,
    CLS_Gd__gd_core__HeroLongsword,
    CLS_Gd__gd_core__HeroSword,
    CLS_Gd__gd_core__HeroicPotion,
    CLS_Gd__gd_core__HoloFireLizard,
    CLS_Gd__gd_core__HolyArmor,
    CLS_Gd__gd_core__HolySpear,
    CLS_Gd__gd_core__HungryBlade,
    CLS_Gd__gd_core__Item__INNER__SignalConnection,
    CLS_Gd__gd_core__Jynxtorquilla,
    CLS_Gd__gd_core__LeatherArmor,
    CLS_Gd__gd_core__LeatherBoots,
    CLS_Gd__gd_core__LeatherHelm,
    CLS_Gd__gd_core__LightGoobert,
    CLS_Gd__gd_core__Lightsaber,
    CLS_Gd__gd_core__LuckyBow,
    CLS_Gd__gd_core__LuckyClover,
    CLS_Gd__gd_core_items__Piggybank,
    CLS_Gd__gd_core__LuckyPiggy,
    CLS_Gd__gd_core__MagicStaff,
    CLS_Gd__gd_core__MagicTorch,
    CLS_Gd__gd_core__ManaOrb,
    CLS_Gd__gd_core__ManaPotion,
    CLS_Gd__gd_core__Manathirst,
    CLS_Gd__gd_core__Shield,
    CLS_Gd__gd_core__MoonShield,
    CLS_Gd__gd_core__MrStruggles,
    CLS_Gd__gd_core__Pan,
    CLS_Gd__gd_core__Pandamonium,
    CLS_Gd__gd_core__PestilenceFlask,
    CLS_Gd__gd_core__PiercingArrow,
    CLS_Gd__gd_core__Piggybank,
    CLS_Gd__gd_core__Pineapple,
    CLS_Gd__gd_core__PlatinCustomerCard,
    CLS_Gd__gd_core__PocketSand,
    CLS_Gd__gd_core__PoisonBow,
    CLS_Gd__gd_core__PoisonDagger,
    CLS_Gd__gd_core__PoisonGoobert,
    CLS_Gd__gd_core__PoisonIvy,
    CLS_Gd__gd_core__PotionBelt,
    CLS_Gd__gd_core__Present,
    CLS_Gd__gd_core__ProtectivePurse,
    CLS_Gd__gd_core__Pumpkin,
    CLS_Gd__gd_core__RainbowGoobert,
    CLS_Gd__gd_core__RainbowGoobertRanger,
    CLS_Gd__gd_core__RangerBag,
    CLS_Gd__gd_core__RibSawBlade,
    CLS_Gd__gd_core__RubyChonk,
    CLS_Gd__gd_core__RubyEgg,
    CLS_Gd__gd_core__RubyWhelp,
    CLS_Gd__gd_core__ShieldofValor,
    CLS_Gd__gd_core__Shovel,
    CLS_Gd__gd_core__Spear,
    CLS_Gd__gd_core__SpectralDagger,
    CLS_Gd__gd_core__SpikedShield,
    CLS_Gd__gd_core__StaffofUnhealing,
    CLS_Gd__gd_core__StaminaSack,
    CLS_Gd__gd_core__SteelGoobert,
    CLS_Gd__gd_core__Stone,
    CLS_Gd__gd_core_items__LeatherHelm,
    CLS_Gd__gd_core__StoneHelm,
    CLS_Gd__gd_core__StoneSkinPotion,
    CLS_Gd__gd_core__StorageCoffin,
    CLS_Gd__gd_core__StrongDemonicFlask,
    CLS_Gd__gd_core_items__Potion,
    CLS_Gd__gd_core_items__HealthPotion,
    CLS_Gd__gd_core__StrongHealthPotion,
    CLS_Gd__gd_core_items__PestilenceFlask,
    CLS_Gd__gd_core__StrongPestilenceFlask,
    CLS_Gd__gd_core_items__StoneSkinPotion,
    CLS_Gd__gd_core__StrongStoneSkinPotion,
    CLS_Gd__gd_core__TheFool,
    CLS_Gd__gd_core__TheLovers,
    CLS_Gd__gd_core__ThornBow,
    CLS_Gd__gd_core__ThornWhip,
    CLS_Gd__gd_core__Torch,
    CLS_Gd__gd_core__VampiricArmor,
    CLS_Gd__gd_core__VampiricGloves,
    CLS_Gd__gd_core__VampiricScythe,
    CLS_Gd__gd_core__VillainSword,
    CLS_Gd__gd_core__WalrusTusk,
    CLS_Gd__gd_core__Whetstone,
    CLS_Gd__gd_core__White_EyesBlueDragon,
    CLS_Gd__gd_core__Wolpertinger,
    CLS_Gd__gd_core__WoodenBuckler,
    CLS_Gd__gd_core__WoodenSword,
    CLS_Gd__gd_core__YggdrasilLeaf,
    CLS_Gd__gd_core_items__Card,
    CLS_Gd__gd_core_items__AceofSpades,
    CLS_Gd__gd_core_items__RangerCollar,
    CLS_Gd__gd_core_items__AcornCollar,
    CLS_Gd__gd_core_items__ArtifactStoneCold,
    CLS_Gd__gd_core_items__ArtifactStoneHeat,
    CLS_Gd__gd_core_items__Bag,
    CLS_Gd__gd_core_items__BagofStones,
    CLS_Gd__gd_core_items__Food,
    CLS_Gd__gd_core_items__Banana,
    CLS_Gd__gd_core_items__BloodAmulet,
    CLS_Gd__gd_core_items__Goobert,
    CLS_Gd__gd_core_items__BloodGoobert,
    CLS_Gd__gd_core_items__Bloodthorne,
    CLS_Gd__gd_core_items__Dagger,
    CLS_Gd__gd_core_items__BloodyDagger,
    CLS_Gd__gd_core_items__Blueberries,
    CLS_Gd__gd_core_items__Bow,
    CLS_Gd__gd_core_items__BowandArrow,
    CLS_Gd__gd_core_items__BoxofRiches,
    CLS_Gd__gd_core_items__Broom,
    CLS_Gd__gd_core_items__BurningCoal,
    CLS_Gd__gd_core_items__BurningTorch,
    CLS_Gd__gd_core_items__Carrot,
    CLS_Gd__gd_core_items__CarrotGoobert,
    CLS_Gd__gd_core_items__ClawsofAttack,
    CLS_Gd__gd_core_items__Coins,
    CLS_Gd__gd_core_items__CorruptedArmor,
    CLS_Gd__gd_core_items__CritwoodStaff,
    CLS_Gd__gd_core_items__Crossblades,
    CLS_Gd__gd_core_items__Crown,
    CLS_Gd__gd_core_items__CursedDagger,
    CLS_Gd__gd_core_items__CursedHairComb,
    CLS_Gd__gd_core_items__CustomerCard,
    CLS_Gd__gd_core_items__DancingDragon,
    CLS_Gd__gd_core_items__DarkestLotus,
    CLS_Gd__gd_core_items__Darksaber,
    CLS_Gd__gd_core_items__DeathScythe,
    CLS_Gd__gd_core_items__DeckofCards,
    CLS_Gd__gd_core_items__DemonicFlask,
    CLS_Gd__gd_core_items__DjinnLamp,
    CLS_Gd__gd_core_items__DragonEgg,
    CLS_Gd__gd_core_items__Eggscalibur,
    CLS_Gd__gd_core_items__EvilCap,
    CLS_Gd__gd_core_items__Exclusive__AcornAce,
    CLS_Gd__gd_core_items__Exclusive__AmethystEgg,
    CLS_Gd__gd_core_items__Exclusive__AmethystWhelp,
    CLS_Gd__gd_core_items__Exclusive__AmuletUnidentified,
    CLS_Gd__gd_core_items__Exclusive__AmuletofAgility,
    CLS_Gd__gd_core_items__Exclusive__AmuletofAlchemy,
    CLS_Gd__gd_core_items__Exclusive__AmuletofDarkness,
    CLS_Gd__gd_core_items__Exclusive__AmuletofFeasting,
    CLS_Gd__gd_core_items__Exclusive__AmuletofFortune,
    CLS_Gd__gd_core_items__Exclusive__AmuletofLife,
    CLS_Gd__gd_core_items__Exclusive__AmuletofLight,
    CLS_Gd__gd_core_items__Exclusive__AmuletofSteel,
    CLS_Gd__gd_core_items__Exclusive__AmuletoftheWild,
    CLS_Gd__gd_core_items__Exclusive__AngelCrystal,
    CLS_Gd__gd_core_items__Exclusive__Anvil,
    CLS_Gd__gd_core_items__Exclusive__ArcaneBoots,
    CLS_Gd__gd_core_items__Exclusive__ArcaneIntellect,
    CLS_Gd__gd_core_items__Exclusive__CouragePuppy,
    CLS_Gd__gd_core_items__Exclusive__ArmoredCouragePuppy,
    CLS_Gd__gd_core_items__Exclusive__PowerPuppy,
    CLS_Gd__gd_core_items__Exclusive__ArmoredPowerPuppy,
    CLS_Gd__gd_core_items__Exclusive__WisdomPuppy,
    CLS_Gd__gd_core_items__Exclusive__ArmoredWisdomPuppy,
    CLS_Gd__gd_core_items__Exclusive__ArtifactStoneDeath,
    CLS_Gd__gd_core_items__Exclusive__Automanaton,
    CLS_Gd__gd_core_items__Exclusive__Axe,
    CLS_Gd__gd_core_items__Exclusive__BadgerRune,
    CLS_Gd__gd_core_items__Exclusive__SpiritCompanion,
    CLS_Gd__gd_core_items__Exclusive__BadgerSpirit,
    CLS_Gd__gd_core_items__Exclusive__BagofGiving,
    CLS_Gd__gd_core_items__Exclusive__Bagtacular,
    CLS_Gd__gd_core_items__Exclusive__Battery,
    CLS_Gd__gd_core_items__Exclusive__Bazooka,
    CLS_Gd__gd_core_items__Exclusive__BerserkerBag,
    CLS_Gd__gd_core_items__Exclusive__Bewitchment,
    CLS_Gd__gd_core_items__Greatsword,
    CLS_Gd__gd_core_items__Exclusive__BigBloodthorne,
    CLS_Gd__gd_core_items__Exclusive__BionicArmor,
    CLS_Gd__gd_core_items__Exclusive__Cube,
    CLS_Gd__gd_core_items__Exclusive__BismuthCube,
    CLS_Gd__gd_core_items__Exclusive__BloodManipulation,
    CLS_Gd__gd_core_items__Exclusive__Bomb,
    CLS_Gd__gd_core_items__Exclusive__BookofBasics,
    CLS_Gd__gd_core_items__Exclusive__BookofDarkness,
    CLS_Gd__gd_core_items__Exclusive__BookofIce,
    CLS_Gd__gd_core_items__Exclusive__BookofLight,
    CLS_Gd__gd_core_items__Exclusive__BookofNature,
    CLS_Gd__gd_core_items__Exclusive__Boomerang,
    CLS_Gd__gd_core_items__Exclusive__BowlofTreats,
    CLS_Gd__gd_core_items__Exclusive__BoxofProsperity,
    CLS_Gd__gd_core_items__Exclusive__BrassKnuckles,
    CLS_Gd__gd_core_items__Exclusive__Broccoli,
    CLS_Gd__gd_core_items__Exclusive__BroccoliGoobert,
    CLS_Gd__gd_core_items__Exclusive__Broccotree,
    CLS_Gd__gd_core_items__Exclusive__BurningBanner,
    CLS_Gd__gd_core_items__Exclusive__BurningSword,
    CLS_Gd__gd_core_items__Exclusive__BurningBlade,
    CLS_Gd__gd_core_items__Exclusive__BurningSpikes,
    CLS_Gd__gd_core_items__Exclusive__BustedBlade,
    CLS_Gd__gd_core_items__Exclusive__BuytheHolyLight,
    CLS_Gd__gd_core_items__Exclusive__CapofBrilliance,
    CLS_Gd__gd_core_items__Exclusive__CatSpirit,
    CLS_Gd__gd_core_items__Exclusive__Cauldron,
    CLS_Gd__gd_core_items__Exclusive__ChainWhip,
    CLS_Gd__gd_core_items__Exclusive__Chainsaw,
    CLS_Gd__gd_core_items__Exclusive__ChargeSplitter,
    CLS_Gd__gd_core_items__Exclusive__Cheese,
    CLS_Gd__gd_core_items__Exclusive__CheeseGoobert,
    CLS_Gd__gd_core_items__Exclusive__Chess__ChessPiece,
    CLS_Gd__gd_core_items__Exclusive__Chess__BlackBishop,
    CLS_Gd__gd_core_items__Exclusive__Chess__BlackKing,
    CLS_Gd__gd_core_items__Exclusive__Chess__BlackKnight,
    CLS_Gd__gd_core_items__Exclusive__Chess__BlackPawn,
    CLS_Gd__gd_core_items__Exclusive__Chess__BlackQueen,
    CLS_Gd__gd_core_items__Exclusive__Chess__BlackRook,
    CLS_Gd__gd_core_items__Exclusive__Chess__WhiteBishop,
    CLS_Gd__gd_core_items__Exclusive__Chess__WhiteKing,
    CLS_Gd__gd_core_items__Exclusive__Chess__WhiteKnight,
    CLS_Gd__gd_core_items__Exclusive__Chess__WhitePawn,
    CLS_Gd__gd_core_items__Exclusive__Chess__WhiteQueen,
    CLS_Gd__gd_core_items__Exclusive__Chess__WhiteRook,
    CLS_Gd__gd_core_items__Exclusive__ChessBoard,
    CLS_Gd__gd_core_items__Exclusive__ChessMaster,
    CLS_Gd__gd_core_items__Exclusive__ChiliGoobert,
    CLS_Gd__gd_core_items__Exclusive__ChiliPepper,
    CLS_Gd__gd_core_items__Exclusive__ChromeCube,
    CLS_Gd__gd_core_items__Exclusive__Cog,
    CLS_Gd__gd_core_items__Exclusive__CogBadge,
    CLS_Gd__gd_core_items__Exclusive__Coil,
    CLS_Gd__gd_core_items__Exclusive__ConTrapTron,
    CLS_Gd__gd_core_items__Exclusive__CriticalPoison,
    CLS_Gd__gd_core_items__Exclusive__Crow,
    CLS_Gd__gd_core_items__Exclusive__Cthulhu,
    CLS_Gd__gd_core_items__Exclusive__Cubert,
    CLS_Gd__gd_core_items__Exclusive__Cupcake,
    CLS_Gd__gd_core_items__Exclusive__CupcakeDragon,
    CLS_Gd__gd_core_items__Exclusive__CupcakeGoobert,
    CLS_Gd__gd_core_items__Exclusive__CupcakeStaff,
    CLS_Gd__gd_core_items__Exclusive__Daggerang,
    CLS_Gd__gd_core_items__Exclusive__DarkLantern,
    CLS_Gd__gd_core_items__Exclusive__DarkRitual,
    CLS_Gd__gd_core_items__Exclusive__DeathLotus,
    CLS_Gd__gd_core_items__Exclusive__DeerTotem,
    CLS_Gd__gd_core_items__Exclusive__DevouringSphere,
    CLS_Gd__gd_core_items__Exclusive__DigDeeper,
    CLS_Gd__gd_core_items__Exclusive__DivinePotion,
    CLS_Gd__gd_core_items__Exclusive__DoomCap,
    CLS_Gd__gd_core_items__Exclusive__DoubleAxe,
    CLS_Gd__gd_core_items__Exclusive__DoubleRainbow,
    CLS_Gd__gd_core_items__Exclusive__DraconicOrb,
    CLS_Gd__gd_core_items__Exclusive__DragonClaws,
    CLS_Gd__gd_core_items__RubyWhelp,
    CLS_Gd__gd_core_items__Exclusive__DragonKnight,
    CLS_Gd__gd_core_items__Exclusive__DragonNest,
    CLS_Gd__gd_core_items__Exclusive__DragonSet,
    CLS_Gd__gd_core_items__Exclusive__DragonscaleArmor,
    CLS_Gd__gd_core_items__Exclusive__DragonskinBoots,
    CLS_Gd__gd_core_items__Exclusive__DualWielding,
    CLS_Gd__gd_core_items__Exclusive__Eat_o_matic,
    CLS_Gd__gd_core_items__Exclusive__EchoingBattlecry,
    CLS_Gd__gd_core_items__Exclusive__ElectricTorch,
    CLS_Gd__gd_core_items__Exclusive__ElephantRune,
    CLS_Gd__gd_core_items__Exclusive__EmeraldEgg,
    CLS_Gd__gd_core_items__Exclusive__EmeraldWhelp,
    CLS_Gd__gd_core_items__LeatherArmor,
    CLS_Gd__gd_core_items__Exclusive__EmployeeUniform,
    CLS_Gd__gd_core_items__Exclusive__EnchantedWeapons,
    CLS_Gd__gd_core_items__Exclusive__EnergyConversion,
    CLS_Gd__gd_core_items__Exclusive__EngineerBag2,
    CLS_Gd__gd_core_items__Exclusive__EngineerBox,
    CLS_Gd__gd_core_items__Exclusive__Everburning,
    CLS_Gd__gd_core_items__Exclusive__EvilHat,
    CLS_Gd__gd_core_items__Exclusive__ExtraAngy,
    CLS_Gd__gd_core_items__Exclusive__ExtraBags,
    CLS_Gd__gd_core_items__Exclusive__FalseLife,
    CLS_Gd__gd_core_items__Exclusive__Fedora,
    CLS_Gd__gd_core_items__Exclusive__FirePit,
    CLS_Gd__gd_core_items__Exclusive__Shelly,
    CLS_Gd__gd_core_items__Exclusive__FireShelly,
    CLS_Gd__gd_core_items__Exclusive__Flame,
    CLS_Gd__gd_core_items__Exclusive__FlameBadge,
    CLS_Gd__gd_core_items__Exclusive__FlameWhip,
    CLS_Gd__gd_core_items__Exclusive__ForestDragon,
    CLS_Gd__gd_core_items__Exclusive__ForestFriend,
    CLS_Gd__gd_core_items__Exclusive__ForgingHammer,
    CLS_Gd__gd_core_items__Exclusive__FortunasKiss,
    CLS_Gd__gd_core_items__Exclusive__FriendlyFire,
    CLS_Gd__gd_core_items__Exclusive__Toad,
    CLS_Gd__gd_core_items__Exclusive__FrogPrince,
    CLS_Gd__gd_core_items__Exclusive__Frostbite,
    CLS_Gd__gd_core_items__Shield,
    CLS_Gd__gd_core_items__Exclusive__FrozenBuckler,
    CLS_Gd__gd_core_items__Exclusive__FrozenFlame,
    CLS_Gd__gd_core_items__Exclusive__FullBodyProtection,
    CLS_Gd__gd_core_items__Exclusive__FurciferPrime,
    CLS_Gd__gd_core_items__Exclusive__Generator,
    CLS_Gd__gd_core_items__Exclusive__Ghost,
    CLS_Gd__gd_core_items__Exclusive__Gigawatz,
    CLS_Gd__gd_core_items__Exclusive__GirlPower,
    CLS_Gd__gd_core_items__Exclusive__GoldArmor,
    CLS_Gd__gd_core_items__Exclusive__GoldCube,
    CLS_Gd__gd_core_items__Exclusive__Halberd,
    CLS_Gd__gd_core_items__Exclusive__Hardwood,
    CLS_Gd__gd_core_items__Exclusive__HawkRune,
    CLS_Gd__gd_core_items__Exclusive__HeartShield,
    CLS_Gd__gd_core_items__Exclusive__HeartoftheCards,
    CLS_Gd__gd_core_items__Exclusive__HeavyDrinking,
    CLS_Gd__gd_core_items__Exclusive__Hedgehog,
    CLS_Gd__gd_core_items__WoodenBuckler,
    CLS_Gd__gd_core_items__Exclusive__HeroShield,
    CLS_Gd__gd_core_items__Exclusive__HogusBogus,
    CLS_Gd__gd_core_items__Exclusive__Holdall,
    CLS_Gd__gd_core_items__Exclusive__HolyCollar,
    CLS_Gd__gd_core_items__Exclusive__HyperHedgehog,
    CLS_Gd__gd_core_items__Exclusive__Hypercube,
    CLS_Gd__gd_core_items__Exclusive__IceArmor,
    CLS_Gd__gd_core_items__Exclusive__IceDragon,
    CLS_Gd__gd_core_items__Exclusive__IceFlower,
    CLS_Gd__gd_core_items__Exclusive__InnerPower,
    CLS_Gd__gd_core_items__Exclusive__InvestmentOpportunity,
    CLS_Gd__gd_core_items__Exclusive__Joker,
    CLS_Gd__gd_core_items__Exclusive__JustStats,
    CLS_Gd__gd_core_items__Exclusive__JynxStaff,
    CLS_Gd__gd_core_items__RibSawBlade,
    CLS_Gd__gd_core_items__Exclusive__Katana,
    CLS_Gd__gd_core_items__Exclusive__KingCrown,
    CLS_Gd__gd_core_items__Exclusive__KingGoobert,
    CLS_Gd__gd_core_items__Exclusive__KingoftheBling,
    CLS_Gd__gd_core_items__Exclusive__KnifetoMeetYou,
    CLS_Gd__gd_core_items__Exclusive__Laboratory,
    CLS_Gd__gd_core_items__Exclusive__LeafBadge,
    CLS_Gd__gd_core_items__Exclusive__LevelUp,
    CLS_Gd__gd_core_items__Exclusive__LightFlower,
    CLS_Gd__gd_core_items__Exclusive__LightningPotion,
    CLS_Gd__gd_core_items__Exclusive__LightningStaff,
    CLS_Gd__gd_core_items__Exclusive__LittleMimic,
    CLS_Gd__gd_core_items__Exclusive__LongSpear,
    CLS_Gd__gd_core_items__Exclusive__Lootbox,
    CLS_Gd__gd_core_items__Exclusive__LuckyCat,
    CLS_Gd__gd_core_items__Exclusive__LuckyShortbow,
    CLS_Gd__gd_core_items__Exclusive__MageHat,
    CLS_Gd__gd_core_items__Exclusive__MagicBadge,
    CLS_Gd__gd_core_items__Exclusive__MagicCollar,
    CLS_Gd__gd_core_items__Exclusive__MagicMirror,
    CLS_Gd__gd_core_items__Exclusive__MagicRing,
    CLS_Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect,
    CLS_Gd__gd_core_items__Exclusive__MagiteccArmor,
    CLS_Gd__gd_core_items__Exclusive__ManaCrystal,
    CLS_Gd__gd_core_items__Exclusive__ManaMastery,
    CLS_Gd__gd_core_items__Exclusive__Mananana,
    CLS_Gd__gd_core_items__Exclusive__Markswoman,
    CLS_Gd__gd_core_items__Exclusive__MechaBat,
    CLS_Gd__gd_core_items__Exclusive__MegaClover,
    CLS_Gd__gd_core_items__Exclusive__MercuryElemental,
    CLS_Gd__gd_core_items__Exclusive__MissFortune,
    CLS_Gd__gd_core_items__Exclusive__MoltenDagger,
    CLS_Gd__gd_core_items__Exclusive__MoltenGreatsword,
    CLS_Gd__gd_core_items__Exclusive__MoltenSpear,
    CLS_Gd__gd_core_items__Exclusive__MoltenSpear2,
    CLS_Gd__gd_core_items__Exclusive__MoonArmor,
    CLS_Gd__gd_core_items__Exclusive__MoreStats,
    CLS_Gd__gd_core_items__Exclusive__MrsStruggles,
    CLS_Gd__gd_core_items__Exclusive__MushroomFarm,
    CLS_Gd__gd_core_items__Exclusive__NoRushPlease,
    CLS_Gd__gd_core_items__Exclusive__NullBlade,
    CLS_Gd__gd_core_items__Exclusive__ObsidianDragon,
    CLS_Gd__gd_core_items__Exclusive__OilLamp,
    CLS_Gd__gd_core_items__Exclusive__OnionCutter,
    CLS_Gd__gd_core_items__Exclusive__OwlSpirit,
    CLS_Gd__gd_core_items__Exclusive__ParadiseBirb,
    CLS_Gd__gd_core_items__Exclusive__PerpetuumMobile,
    CLS_Gd__gd_core_items__Exclusive__Phoenix,
    CLS_Gd__gd_core_items__Exclusive__Phoenix2,
    CLS_Gd__gd_core_items__Exclusive__PiggyPinata,
    CLS_Gd__gd_core_items__Exclusive__PiggyofRiches,
    CLS_Gd__gd_core_items__SpikedShield,
    CLS_Gd__gd_core_items__Exclusive__PineProtector,
    CLS_Gd__gd_core_items__Exclusive__PlasticCube,
    CLS_Gd__gd_core_items__Exclusive__PoisonFrog,
    CLS_Gd__gd_core_items__Exclusive__PoisonGrenade,
    CLS_Gd__gd_core_items__Exclusive__PoisonShortbow,
    CLS_Gd__gd_core_items__Exclusive__PoisonSpear,
    CLS_Gd__gd_core_items__Exclusive__Pop,
    CLS_Gd__gd_core_items__Exclusive__PortableAltar,
    CLS_Gd__gd_core_items__Exclusive__Pot,
    CLS_Gd__gd_core_items__Exclusive__PoweroftheMoon,
    CLS_Gd__gd_core_items__Exclusive__PrismaticSword,
    CLS_Gd__gd_core_items__Exclusive__PrismaticWand,
    CLS_Gd__gd_core_items__Exclusive__PuzzleBadge,
    CLS_Gd__gd_core_items__Exclusive__PuzzlebagJ,
    CLS_Gd__gd_core_items__Exclusive__PuzzlebagL,
    CLS_Gd__gd_core_items__Exclusive__PuzzlebagS,
    CLS_Gd__gd_core_items__Exclusive__PuzzlebagT,
    CLS_Gd__gd_core_items__Exclusive__PuzzlebagZ,
    CLS_Gd__gd_core_items__Exclusive__Puzzlebox,
    CLS_Gd__gd_core_items__Exclusive__RainbowBadge,
    CLS_Gd__gd_core_items__Exclusive__RainbowGoobertAdventurer,
    CLS_Gd__gd_core_items__Exclusive__RainbowGoobertBerserker,
    CLS_Gd__gd_core_items__Exclusive__RainbowGoobertEngineer,
    CLS_Gd__gd_core_items__Exclusive__RainbowGoobertMage,
    CLS_Gd__gd_core_items__Exclusive__RainbowGoobertPyromancer,
    CLS_Gd__gd_core_items__Exclusive__RainbowOrb,
    CLS_Gd__gd_core_items__Exclusive__RainbowPotion,
    CLS_Gd__gd_core_items__Exclusive__RandomLoadoutBag,
    CLS_Gd__gd_core_items__Exclusive__Rat,
    CLS_Gd__gd_core_items__Exclusive__RatChef,
    CLS_Gd__gd_core_items__Exclusive__Recombobulator,
    CLS_Gd__gd_core_items__Exclusive__RelicCase,
    CLS_Gd__gd_core_items__Exclusive__Repeater,
    CLS_Gd__gd_core_items__Exclusive__Resistor,
    CLS_Gd__gd_core_items__Exclusive__Reverse,
    CLS_Gd__gd_core_items__Exclusive__Robodog,
    CLS_Gd__gd_core_items__Exclusive__Rope,
    CLS_Gd__gd_core_items__Exclusive__Sandbag,
    CLS_Gd__gd_core_items__Exclusive__SapphireEgg,
    CLS_Gd__gd_core_items__Exclusive__SapphireWhelp,
    CLS_Gd__gd_core_items__Exclusive__Scale,
    CLS_Gd__gd_core_items__Exclusive__ScholarBag,
    CLS_Gd__gd_core_items__Lightsaber,
    CLS_Gd__gd_core_items__Exclusive__Scissorswords,
    CLS_Gd__gd_core_items__Exclusive__SealtheDeal,
    CLS_Gd__gd_core_items__Exclusive__SerpentStaff,
    CLS_Gd__gd_core_items__Exclusive__SewingCase,
    CLS_Gd__gd_core_items__Exclusive__ShamanMask,
    CLS_Gd__gd_core_items__Exclusive__ShellTotem,
    CLS_Gd__gd_core_items__Exclusive__ShepherdsCrook,
    CLS_Gd__gd_core_items__Exclusive__Shielded,
    CLS_Gd__gd_core_items__Exclusive__ShinyMantle,
    CLS_Gd__gd_core_items__Exclusive__ShinyShell,
    CLS_Gd__gd_core_items__Exclusive__SkullBadge,
    CLS_Gd__gd_core_items__Exclusive__SliceofBread,
    CLS_Gd__gd_core_items__Exclusive__SliceofToast,
    CLS_Gd__gd_core_items__Exclusive__SlimeTime,
    CLS_Gd__gd_core_items__Exclusive__Sloth,
    CLS_Gd__gd_core_items__Exclusive__SmellyBarrier,
    CLS_Gd__gd_core_items__Exclusive__SmithingForDummies,
    CLS_Gd__gd_core_items__Exclusive__Snake,
    CLS_Gd__gd_core_items__Exclusive__SnowStick,
    CLS_Gd__gd_core_items__Exclusive__Snowball,
    CLS_Gd__gd_core_items__Exclusive__Snowcake,
    CLS_Gd__gd_core_items__Exclusive__Snowman,
    CLS_Gd__gd_core_items__Exclusive__Snowmaster,
    CLS_Gd__gd_core_items__Exclusive__Solaris,
    CLS_Gd__gd_core_items__Exclusive__SpeakwithAnimals,
    CLS_Gd__gd_core_items__Exclusive__SpellScrollDark,
    CLS_Gd__gd_core_items__Exclusive__SpellScrollFrostbolt,
    CLS_Gd__gd_core_items__Exclusive__SpellScrollIce,
    CLS_Gd__gd_core_items__Exclusive__SpellScrollLight,
    CLS_Gd__gd_core_items__Exclusive__SpellScrollNature,
    CLS_Gd__gd_core_items__Exclusive__SpicyBanana,
    CLS_Gd__gd_core_items__Exclusive__SpikedCollar,
    CLS_Gd__gd_core_items__Exclusive__SpikedStaff,
    CLS_Gd__gd_core_items__Exclusive__SpikedWall,
    CLS_Gd__gd_core_items__Exclusive__SpintoWin,
    CLS_Gd__gd_core_items__Exclusive__SpiritBells,
    CLS_Gd__gd_core_items__Exclusive__SpringLoader,
    CLS_Gd__gd_core_items__Exclusive__Squirrel,
    CLS_Gd__gd_core_items__Exclusive__SquirrelArcher,
    CLS_Gd__gd_core_items__Exclusive__StaffofFire,
    CLS_Gd__gd_core_items__Exclusive__StarofCourage,
    CLS_Gd__gd_core_items__Exclusive__SteelDragon,
    CLS_Gd__gd_core_items__Exclusive__StoneArmor,
    CLS_Gd__gd_core_items__Exclusive__StoneBadge,
    CLS_Gd__gd_core_items__Exclusive__StoneGloves,
    CLS_Gd__gd_core_items__Exclusive__StoneGolem,
    CLS_Gd__gd_core_items__Exclusive__StoneShoes,
    CLS_Gd__gd_core_items__Exclusive__Stoned,
    CLS_Gd__gd_core_items__Exclusive__StrongDivinePotion,
    CLS_Gd__gd_core_items__Exclusive__VampiricPotion,
    CLS_Gd__gd_core_items__Exclusive__StrongVampiricPotion,
    CLS_Gd__gd_core_items__Exclusive__SunArmor,
    CLS_Gd__gd_core_items__Exclusive__SunShield,
    CLS_Gd__gd_core_items__Exclusive__TeslaCoil,
    CLS_Gd__gd_core_items__Exclusive__ThornElemental,
    CLS_Gd__gd_core_items__Exclusive__ThornShortbow,
    CLS_Gd__gd_core_items__Exclusive__Thornbloom,
    CLS_Gd__gd_core_items__Exclusive__Thornburst,
    CLS_Gd__gd_core_items__Exclusive__ThorsHammer,
    CLS_Gd__gd_core_items__Exclusive__ThunderDrake,
    CLS_Gd__gd_core_items__Exclusive__TigerRune,
    CLS_Gd__gd_core_items__Exclusive__TimeDilator,
    CLS_Gd__gd_core_items__Exclusive__TimeMelting,
    CLS_Gd__gd_core_items__Exclusive__TimePendant,
    CLS_Gd__gd_core_items__Exclusive__ToastGoobert,
    CLS_Gd__gd_core_items__Exclusive__Toolbox,
    CLS_Gd__gd_core_items__Exclusive__Turtle,
    CLS_Gd__gd_core_items__Exclusive__Twine,
    CLS_Gd__gd_core_items__Exclusive__TwineBadge,
    CLS_Gd__gd_core_items__Exclusive__Ukulele,
    CLS_Gd__gd_core_items__Exclusive__Ultima,
    CLS_Gd__gd_core_items__Exclusive__UnidentifiedSkill,
    CLS_Gd__gd_core_items__Exclusive__UniquelyUnique,
    CLS_Gd__gd_core_items__Exclusive__VampiricCollar,
    CLS_Gd__gd_core_items__Exclusive__VineweaveBasket,
    CLS_Gd__gd_core_items__Exclusive__Wand,
    CLS_Gd__gd_core_items__Exclusive__WandofDissonance,
    CLS_Gd__gd_core_items__Exclusive__WarScythe,
    CLS_Gd__gd_core_items__Exclusive__WaterElemental,
    CLS_Gd__gd_core_items__Whetstone,
    CLS_Gd__gd_core_items__Exclusive__Whetstone3,
    CLS_Gd__gd_core_items__Exclusive__WingedBoots,
    CLS_Gd__gd_core_items__Exclusive__Wisp,
    CLS_Gd__gd_core_items__Exclusive__WolfBadge,
    CLS_Gd__gd_core_items__Exclusive__WolfEmblem,
    CLS_Gd__gd_core_items__Exclusive__Wrench,
    CLS_Gd__gd_core_items__FalconBlade,
    CLS_Gd__gd_core_items__FancyFencingRapier,
    CLS_Gd__gd_core_items__Fanfare,
    CLS_Gd__gd_core_items__FannyPack,
    CLS_Gd__gd_core_items__Flute,
    CLS_Gd__gd_core_items__FlyAgaric,
    CLS_Gd__gd_core_items__Garlic,
    CLS_Gd__gd_core_items__Gems__Amethyst,
    CLS_Gd__gd_core_items__Gems__CorruptedCrystal,
    CLS_Gd__gd_core_items__Gems__Emerald,
    CLS_Gd__gd_core_items__Gems__LumpofCoal,
    CLS_Gd__gd_core_items__Gems__Ruby,
    CLS_Gd__gd_core_items__Gems__Sapphire,
    CLS_Gd__gd_core_items__Gems__Skull,
    CLS_Gd__gd_core_items__Gems__Topaz,
    CLS_Gd__gd_core_items__GingerbreadMan,
    CLS_Gd__gd_core_items__GlovesofHaste,
    CLS_Gd__gd_core_items__Hammer,
    CLS_Gd__gd_core_items__HealingHerbs,
    CLS_Gd__gd_core_items__HeartContainer,
    CLS_Gd__gd_core_items__HeartofDarkness,
    CLS_Gd__gd_core_items__HeroLongsword,
    CLS_Gd__gd_core_items__HeroSword,
    CLS_Gd__gd_core_items__HeroicPotion,
    CLS_Gd__gd_core_items__HoloFireLizard,
    CLS_Gd__gd_core_items__HolyArmor,
    CLS_Gd__gd_core_items__HolySpear,
    CLS_Gd__gd_core_items__HungryBlade,
    CLS_Gd__gd_core_items__Item__INNER__SignalConnection,
    CLS_Gd__gd_core_items__Jynxtorquilla,
    CLS_Gd__gd_core_items__LeatherBoots,
    CLS_Gd__gd_core_items__LightGoobert,
    CLS_Gd__gd_core_items__LuckyBow,
    CLS_Gd__gd_core_items__LuckyClover,
    CLS_Gd__gd_core_items__LuckyPiggy,
    CLS_Gd__gd_core_items__MagicStaff,
    CLS_Gd__gd_core_items__MagicTorch,
    CLS_Gd__gd_core_items__ManaOrb,
    CLS_Gd__gd_core_items__ManaPotion,
    CLS_Gd__gd_core_items__Manathirst,
    CLS_Gd__gd_core_items__MoonShield,
    CLS_Gd__gd_core_items__MrStruggles,
    CLS_Gd__gd_core_items__Pandamonium,
    CLS_Gd__gd_core_items__PiercingArrow,
    CLS_Gd__gd_core_items__Pineapple,
    CLS_Gd__gd_core_items__PlatinCustomerCard,
    CLS_Gd__gd_core_items__PocketSand,
    CLS_Gd__gd_core_items__PoisonBow,
    CLS_Gd__gd_core_items__PoisonDagger,
    CLS_Gd__gd_core_items__PoisonGoobert,
    CLS_Gd__gd_core_items__PoisonIvy,
    CLS_Gd__gd_core_items__PotionBelt,
    CLS_Gd__gd_core_items__Present,
    CLS_Gd__gd_core_items__ProtectivePurse,
    CLS_Gd__gd_core_items__Pumpkin,
    CLS_Gd__gd_core_items__RainbowGoobert,
    CLS_Gd__gd_core_items__RainbowGoobertRanger,
    CLS_Gd__gd_core_items__RangerBag,
    CLS_Gd__gd_core_items__RubyChonk,
    CLS_Gd__gd_core_items__RubyEgg,
    CLS_Gd__gd_core_items__ShieldofValor,
    CLS_Gd__gd_core_items__Shovel,
    CLS_Gd__gd_core_items__Spear,
    CLS_Gd__gd_core_items__SpectralDagger,
    CLS_Gd__gd_core_items__StaffofUnhealing,
    CLS_Gd__gd_core_items__StaminaSack,
    CLS_Gd__gd_core_items__SteelGoobert,
    CLS_Gd__gd_core_items__StoneHelm,
    CLS_Gd__gd_core_items__StorageCoffin,
    CLS_Gd__gd_core_items__StrongDemonicFlask,
    CLS_Gd__gd_core_items__StrongHealthPotion,
    CLS_Gd__gd_core_items__StrongPestilenceFlask,
    CLS_Gd__gd_core_items__StrongStoneSkinPotion,
    CLS_Gd__gd_core_items__TheFool,
    CLS_Gd__gd_core_items__TheLovers,
    CLS_Gd__gd_core_items__ThornBow,
    CLS_Gd__gd_core_items__ThornWhip,
    CLS_Gd__gd_core_items__Torch,
    CLS_Gd__gd_core_items__VampiricArmor,
    CLS_Gd__gd_core_items__VampiricGloves,
    CLS_Gd__gd_core_items__VampiricScythe,
    CLS_Gd__gd_core_items__VillainSword,
    CLS_Gd__gd_core_items__WalrusTusk,
    CLS_Gd__gd_core_items__White_EyesBlueDragon,
    CLS_Gd__gd_core_items__Wolpertinger,
    CLS_Gd__gd_core_items__WoodenSword,
    CLS_Gd__gd_core_items__YggdrasilLeaf,
};
extern const gd::GdClassMeta META_Gd__gd_core__CoreItem;
extern const gd::GdClassMeta META_Gd__gd_core__Item;
extern const gd::GdClassMeta META_Gd__gd_core__Card;
extern const gd::GdClassMeta META_Gd__gd_core__AceofSpades;
extern const gd::GdClassMeta META_Gd__gd_core__RangerCollar;
extern const gd::GdClassMeta META_Gd__gd_core__AcornCollar;
extern const gd::GdClassMeta META_Gd__gd_core_items__Item;
extern const gd::GdClassMeta META_Gd__gd_core_items__Stone;
extern const gd::GdClassMeta META_Gd__gd_core__ArtifactStoneCold;
extern const gd::GdClassMeta META_Gd__gd_core__ArtifactStoneHeat;
extern const gd::GdClassMeta META_Gd__gd_core__Bag;
extern const gd::GdClassMeta META_Gd__gd_core__BagofStones;
extern const gd::GdClassMeta META_Gd__gd_core__Food;
extern const gd::GdClassMeta META_Gd__gd_core__Banana;
extern const gd::GdClassMeta META_Gd__gd_core__BloodAmulet;
extern const gd::GdClassMeta META_Gd__gd_core__Goobert;
extern const gd::GdClassMeta META_Gd__gd_core__BloodGoobert;
extern const gd::GdClassMeta META_Gd__gd_core__Weapon;
extern const gd::GdClassMeta META_Gd__gd_core__Bloodthorne;
extern const gd::GdClassMeta META_Gd__gd_core__Dagger;
extern const gd::GdClassMeta META_Gd__gd_core__BloodyDagger;
extern const gd::GdClassMeta META_Gd__gd_core__Blueberries;
extern const gd::GdClassMeta META_Gd__gd_core__Bow;
extern const gd::GdClassMeta META_Gd__gd_core__BowandArrow;
extern const gd::GdClassMeta META_Gd__gd_core__BoxofRiches;
extern const gd::GdClassMeta META_Gd__gd_core__Broom;
extern const gd::GdClassMeta META_Gd__gd_core_items__Gems__Gem;
extern const gd::GdClassMeta META_Gd__gd_core__BurningCoal;
extern const gd::GdClassMeta META_Gd__gd_core__BurningTorch;
extern const gd::GdClassMeta META_Gd__gd_core__Carrot;
extern const gd::GdClassMeta META_Gd__gd_core__CarrotGoobert;
extern const gd::GdClassMeta META_Gd__gd_core__ClawsofAttack;
extern const gd::GdClassMeta META_Gd__gd_core__CoreBuff;
extern const gd::GdClassMeta META_Gd__gd_core__CoreBuff__INNER__TemporaryStacks;
extern const gd::GdClassMeta META_Gd__gd_core__CoreCharacter;
extern const gd::GdClassMeta META_Gd__gd_core__CoreCombat;
extern const gd::GdClassMeta META_Gd__gd_core__CoreCombat__INNER__CoreItemSort;
extern const gd::GdClassMeta META_Gd__gd_core__CoreCombatLog;
extern const gd::GdClassMeta META_Gd__gd_core__CoreConst;
extern const gd::GdClassMeta META_Gd__gd_core__CoreContext;
extern const gd::GdClassMeta META_Gd__gd_core__CoreDamageResult;
extern const gd::GdClassMeta META_Gd__gd_core__CoreDamageSource;
extern const gd::GdClassMeta META_Gd__gd_core__CoreEvent;
extern const gd::GdClassMeta META_Gd__gd_core__CoreEventBus;
extern const gd::GdClassMeta META_Gd__gd_core__CoreGrid;
extern const gd::GdClassMeta META_Gd__gd_core__CoreHooks;
extern const gd::GdClassMeta META_Gd__gd_core__CoreItem__INNER__CoreElectricalCharge;
extern const gd::GdClassMeta META_Gd__gd_core__CoreItem__INNER__CoreSignalConnection;
extern const gd::GdClassMeta META_Gd__gd_core__CoreItemBook;
extern const gd::GdClassMeta META_Gd__gd_core__CoreItemData;
extern const gd::GdClassMeta META_Gd__gd_core__CoreRng;
extern const gd::GdClassMeta META_Gd__gd_core__CoreRng__INNER__BalancedRng;
extern const gd::GdClassMeta META_Gd__gd_core__CoreRng__INNER__BalancedRange;
extern const gd::GdClassMeta META_Gd__gd_core__CoreTimer;
extern const gd::GdClassMeta META_Gd__gd_core__CoreUtil;
extern const gd::GdClassMeta META_Gd__gd_core__CoreUtil__INNER__DictSorter;
extern const gd::GdClassMeta META_Gd__gd_core__CorruptedArmor;
extern const gd::GdClassMeta META_Gd__gd_core__CritwoodStaff;
extern const gd::GdClassMeta META_Gd__gd_core__Crossblades;
extern const gd::GdClassMeta META_Gd__gd_core__Crown;
extern const gd::GdClassMeta META_Gd__gd_core__CursedDagger;
extern const gd::GdClassMeta META_Gd__gd_core__CursedHairComb;
extern const gd::GdClassMeta META_Gd__gd_core__CustomerCard;
extern const gd::GdClassMeta META_Gd__gd_core__DancingDragon;
extern const gd::GdClassMeta META_Gd__gd_core__DarkestLotus;
extern const gd::GdClassMeta META_Gd__gd_core__Darksaber;
extern const gd::GdClassMeta META_Gd__gd_core__DeathScythe;
extern const gd::GdClassMeta META_Gd__gd_core__DeckofCards;
extern const gd::GdClassMeta META_Gd__gd_core__Potion;
extern const gd::GdClassMeta META_Gd__gd_core__DemonicFlask;
extern const gd::GdClassMeta META_Gd__gd_core__DjinnLamp;
extern const gd::GdClassMeta META_Gd__gd_core__DragonEgg;
extern const gd::GdClassMeta META_Gd__gd_core_items__Weapon;
extern const gd::GdClassMeta META_Gd__gd_core_items__Pan;
extern const gd::GdClassMeta META_Gd__gd_core__Eggscalibur;
extern const gd::GdClassMeta META_Gd__gd_core__EvilCap;
extern const gd::GdClassMeta META_Gd__gd_core__FalconBlade;
extern const gd::GdClassMeta META_Gd__gd_core__FancyFencingRapier;
extern const gd::GdClassMeta META_Gd__gd_core__Fanfare;
extern const gd::GdClassMeta META_Gd__gd_core__FannyPack;
extern const gd::GdClassMeta META_Gd__gd_core__Flute;
extern const gd::GdClassMeta META_Gd__gd_core__FlyAgaric;
extern const gd::GdClassMeta META_Gd__gd_core__Garlic;
extern const gd::GdClassMeta META_Gd__gd_core__GingerbreadMan;
extern const gd::GdClassMeta META_Gd__gd_core__GlovesofHaste;
extern const gd::GdClassMeta META_Gd__gd_core__Greatsword;
extern const gd::GdClassMeta META_Gd__gd_core__Hammer;
extern const gd::GdClassMeta META_Gd__gd_core__HealingHerbs;
extern const gd::GdClassMeta META_Gd__gd_core__HealthPotion;
extern const gd::GdClassMeta META_Gd__gd_core__HeartContainer;
extern const gd::GdClassMeta META_Gd__gd_core__HeartofDarkness;
extern const gd::GdClassMeta META_Gd__gd_core__HeroLongsword;
extern const gd::GdClassMeta META_Gd__gd_core__HeroSword;
extern const gd::GdClassMeta META_Gd__gd_core__HeroicPotion;
extern const gd::GdClassMeta META_Gd__gd_core__HoloFireLizard;
extern const gd::GdClassMeta META_Gd__gd_core__HolyArmor;
extern const gd::GdClassMeta META_Gd__gd_core__HolySpear;
extern const gd::GdClassMeta META_Gd__gd_core__HungryBlade;
extern const gd::GdClassMeta META_Gd__gd_core__Item__INNER__SignalConnection;
extern const gd::GdClassMeta META_Gd__gd_core__Jynxtorquilla;
extern const gd::GdClassMeta META_Gd__gd_core__LeatherArmor;
extern const gd::GdClassMeta META_Gd__gd_core__LeatherBoots;
extern const gd::GdClassMeta META_Gd__gd_core__LeatherHelm;
extern const gd::GdClassMeta META_Gd__gd_core__LightGoobert;
extern const gd::GdClassMeta META_Gd__gd_core__Lightsaber;
extern const gd::GdClassMeta META_Gd__gd_core__LuckyBow;
extern const gd::GdClassMeta META_Gd__gd_core__LuckyClover;
extern const gd::GdClassMeta META_Gd__gd_core_items__Piggybank;
extern const gd::GdClassMeta META_Gd__gd_core__LuckyPiggy;
extern const gd::GdClassMeta META_Gd__gd_core__MagicStaff;
extern const gd::GdClassMeta META_Gd__gd_core__MagicTorch;
extern const gd::GdClassMeta META_Gd__gd_core__ManaOrb;
extern const gd::GdClassMeta META_Gd__gd_core__ManaPotion;
extern const gd::GdClassMeta META_Gd__gd_core__Manathirst;
extern const gd::GdClassMeta META_Gd__gd_core__Shield;
extern const gd::GdClassMeta META_Gd__gd_core__MoonShield;
extern const gd::GdClassMeta META_Gd__gd_core__MrStruggles;
extern const gd::GdClassMeta META_Gd__gd_core__Pan;
extern const gd::GdClassMeta META_Gd__gd_core__Pandamonium;
extern const gd::GdClassMeta META_Gd__gd_core__PestilenceFlask;
extern const gd::GdClassMeta META_Gd__gd_core__PiercingArrow;
extern const gd::GdClassMeta META_Gd__gd_core__Piggybank;
extern const gd::GdClassMeta META_Gd__gd_core__Pineapple;
extern const gd::GdClassMeta META_Gd__gd_core__PlatinCustomerCard;
extern const gd::GdClassMeta META_Gd__gd_core__PocketSand;
extern const gd::GdClassMeta META_Gd__gd_core__PoisonBow;
extern const gd::GdClassMeta META_Gd__gd_core__PoisonDagger;
extern const gd::GdClassMeta META_Gd__gd_core__PoisonGoobert;
extern const gd::GdClassMeta META_Gd__gd_core__PoisonIvy;
extern const gd::GdClassMeta META_Gd__gd_core__PotionBelt;
extern const gd::GdClassMeta META_Gd__gd_core__Present;
extern const gd::GdClassMeta META_Gd__gd_core__ProtectivePurse;
extern const gd::GdClassMeta META_Gd__gd_core__Pumpkin;
extern const gd::GdClassMeta META_Gd__gd_core__RainbowGoobert;
extern const gd::GdClassMeta META_Gd__gd_core__RainbowGoobertRanger;
extern const gd::GdClassMeta META_Gd__gd_core__RangerBag;
extern const gd::GdClassMeta META_Gd__gd_core__RibSawBlade;
extern const gd::GdClassMeta META_Gd__gd_core__RubyChonk;
extern const gd::GdClassMeta META_Gd__gd_core__RubyEgg;
extern const gd::GdClassMeta META_Gd__gd_core__RubyWhelp;
extern const gd::GdClassMeta META_Gd__gd_core__ShieldofValor;
extern const gd::GdClassMeta META_Gd__gd_core__Shovel;
extern const gd::GdClassMeta META_Gd__gd_core__Spear;
extern const gd::GdClassMeta META_Gd__gd_core__SpectralDagger;
extern const gd::GdClassMeta META_Gd__gd_core__SpikedShield;
extern const gd::GdClassMeta META_Gd__gd_core__StaffofUnhealing;
extern const gd::GdClassMeta META_Gd__gd_core__StaminaSack;
extern const gd::GdClassMeta META_Gd__gd_core__SteelGoobert;
extern const gd::GdClassMeta META_Gd__gd_core__Stone;
extern const gd::GdClassMeta META_Gd__gd_core_items__LeatherHelm;
extern const gd::GdClassMeta META_Gd__gd_core__StoneHelm;
extern const gd::GdClassMeta META_Gd__gd_core__StoneSkinPotion;
extern const gd::GdClassMeta META_Gd__gd_core__StorageCoffin;
extern const gd::GdClassMeta META_Gd__gd_core__StrongDemonicFlask;
extern const gd::GdClassMeta META_Gd__gd_core_items__Potion;
extern const gd::GdClassMeta META_Gd__gd_core_items__HealthPotion;
extern const gd::GdClassMeta META_Gd__gd_core__StrongHealthPotion;
extern const gd::GdClassMeta META_Gd__gd_core_items__PestilenceFlask;
extern const gd::GdClassMeta META_Gd__gd_core__StrongPestilenceFlask;
extern const gd::GdClassMeta META_Gd__gd_core_items__StoneSkinPotion;
extern const gd::GdClassMeta META_Gd__gd_core__StrongStoneSkinPotion;
extern const gd::GdClassMeta META_Gd__gd_core__TheFool;
extern const gd::GdClassMeta META_Gd__gd_core__TheLovers;
extern const gd::GdClassMeta META_Gd__gd_core__ThornBow;
extern const gd::GdClassMeta META_Gd__gd_core__ThornWhip;
extern const gd::GdClassMeta META_Gd__gd_core__Torch;
extern const gd::GdClassMeta META_Gd__gd_core__VampiricArmor;
extern const gd::GdClassMeta META_Gd__gd_core__VampiricGloves;
extern const gd::GdClassMeta META_Gd__gd_core__VampiricScythe;
extern const gd::GdClassMeta META_Gd__gd_core__VillainSword;
extern const gd::GdClassMeta META_Gd__gd_core__WalrusTusk;
extern const gd::GdClassMeta META_Gd__gd_core__Whetstone;
extern const gd::GdClassMeta META_Gd__gd_core__White_EyesBlueDragon;
extern const gd::GdClassMeta META_Gd__gd_core__Wolpertinger;
extern const gd::GdClassMeta META_Gd__gd_core__WoodenBuckler;
extern const gd::GdClassMeta META_Gd__gd_core__WoodenSword;
extern const gd::GdClassMeta META_Gd__gd_core__YggdrasilLeaf;
extern const gd::GdClassMeta META_Gd__gd_core_items__Card;
extern const gd::GdClassMeta META_Gd__gd_core_items__AceofSpades;
extern const gd::GdClassMeta META_Gd__gd_core_items__RangerCollar;
extern const gd::GdClassMeta META_Gd__gd_core_items__AcornCollar;
extern const gd::GdClassMeta META_Gd__gd_core_items__ArtifactStoneCold;
extern const gd::GdClassMeta META_Gd__gd_core_items__ArtifactStoneHeat;
extern const gd::GdClassMeta META_Gd__gd_core_items__Bag;
extern const gd::GdClassMeta META_Gd__gd_core_items__BagofStones;
extern const gd::GdClassMeta META_Gd__gd_core_items__Food;
extern const gd::GdClassMeta META_Gd__gd_core_items__Banana;
extern const gd::GdClassMeta META_Gd__gd_core_items__BloodAmulet;
extern const gd::GdClassMeta META_Gd__gd_core_items__Goobert;
extern const gd::GdClassMeta META_Gd__gd_core_items__BloodGoobert;
extern const gd::GdClassMeta META_Gd__gd_core_items__Bloodthorne;
extern const gd::GdClassMeta META_Gd__gd_core_items__Dagger;
extern const gd::GdClassMeta META_Gd__gd_core_items__BloodyDagger;
extern const gd::GdClassMeta META_Gd__gd_core_items__Blueberries;
extern const gd::GdClassMeta META_Gd__gd_core_items__Bow;
extern const gd::GdClassMeta META_Gd__gd_core_items__BowandArrow;
extern const gd::GdClassMeta META_Gd__gd_core_items__BoxofRiches;
extern const gd::GdClassMeta META_Gd__gd_core_items__Broom;
extern const gd::GdClassMeta META_Gd__gd_core_items__BurningCoal;
extern const gd::GdClassMeta META_Gd__gd_core_items__BurningTorch;
extern const gd::GdClassMeta META_Gd__gd_core_items__Carrot;
extern const gd::GdClassMeta META_Gd__gd_core_items__CarrotGoobert;
extern const gd::GdClassMeta META_Gd__gd_core_items__ClawsofAttack;
extern const gd::GdClassMeta META_Gd__gd_core_items__Coins;
extern const gd::GdClassMeta META_Gd__gd_core_items__CorruptedArmor;
extern const gd::GdClassMeta META_Gd__gd_core_items__CritwoodStaff;
extern const gd::GdClassMeta META_Gd__gd_core_items__Crossblades;
extern const gd::GdClassMeta META_Gd__gd_core_items__Crown;
extern const gd::GdClassMeta META_Gd__gd_core_items__CursedDagger;
extern const gd::GdClassMeta META_Gd__gd_core_items__CursedHairComb;
extern const gd::GdClassMeta META_Gd__gd_core_items__CustomerCard;
extern const gd::GdClassMeta META_Gd__gd_core_items__DancingDragon;
extern const gd::GdClassMeta META_Gd__gd_core_items__DarkestLotus;
extern const gd::GdClassMeta META_Gd__gd_core_items__Darksaber;
extern const gd::GdClassMeta META_Gd__gd_core_items__DeathScythe;
extern const gd::GdClassMeta META_Gd__gd_core_items__DeckofCards;
extern const gd::GdClassMeta META_Gd__gd_core_items__DemonicFlask;
extern const gd::GdClassMeta META_Gd__gd_core_items__DjinnLamp;
extern const gd::GdClassMeta META_Gd__gd_core_items__DragonEgg;
extern const gd::GdClassMeta META_Gd__gd_core_items__Eggscalibur;
extern const gd::GdClassMeta META_Gd__gd_core_items__EvilCap;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__AcornAce;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__AmethystEgg;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__AmethystWhelp;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__AmuletUnidentified;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__AmuletofAgility;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__AmuletofAlchemy;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__AmuletofDarkness;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__AmuletofFeasting;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__AmuletofFortune;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__AmuletofLife;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__AmuletofLight;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__AmuletofSteel;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__AmuletoftheWild;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__AngelCrystal;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Anvil;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ArcaneBoots;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ArcaneIntellect;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__CouragePuppy;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ArmoredCouragePuppy;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__PowerPuppy;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ArmoredPowerPuppy;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__WisdomPuppy;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ArmoredWisdomPuppy;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ArtifactStoneDeath;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Automanaton;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Axe;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__BadgerRune;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SpiritCompanion;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__BadgerSpirit;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__BagofGiving;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Bagtacular;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Battery;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Bazooka;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__BerserkerBag;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Bewitchment;
extern const gd::GdClassMeta META_Gd__gd_core_items__Greatsword;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__BigBloodthorne;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__BionicArmor;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Cube;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__BismuthCube;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__BloodManipulation;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Bomb;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__BookofBasics;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__BookofDarkness;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__BookofIce;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__BookofLight;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__BookofNature;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Boomerang;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__BowlofTreats;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__BoxofProsperity;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__BrassKnuckles;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Broccoli;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__BroccoliGoobert;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Broccotree;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__BurningBanner;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__BurningSword;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__BurningBlade;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__BurningSpikes;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__BustedBlade;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__BuytheHolyLight;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__CapofBrilliance;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__CatSpirit;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Cauldron;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ChainWhip;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Chainsaw;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ChargeSplitter;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Cheese;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__CheeseGoobert;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Chess__ChessPiece;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Chess__BlackBishop;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Chess__BlackKing;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Chess__BlackKnight;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Chess__BlackPawn;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Chess__BlackQueen;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Chess__BlackRook;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Chess__WhiteBishop;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Chess__WhiteKing;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Chess__WhiteKnight;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Chess__WhitePawn;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Chess__WhiteQueen;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Chess__WhiteRook;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ChessBoard;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ChessMaster;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ChiliGoobert;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ChiliPepper;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ChromeCube;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Cog;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__CogBadge;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Coil;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ConTrapTron;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__CriticalPoison;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Crow;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Cthulhu;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Cubert;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Cupcake;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__CupcakeDragon;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__CupcakeGoobert;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__CupcakeStaff;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Daggerang;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__DarkLantern;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__DarkRitual;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__DeathLotus;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__DeerTotem;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__DevouringSphere;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__DigDeeper;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__DivinePotion;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__DoomCap;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__DoubleAxe;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__DoubleRainbow;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__DraconicOrb;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__DragonClaws;
extern const gd::GdClassMeta META_Gd__gd_core_items__RubyWhelp;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__DragonKnight;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__DragonNest;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__DragonSet;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__DragonscaleArmor;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__DragonskinBoots;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__DualWielding;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Eat_o_matic;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__EchoingBattlecry;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ElectricTorch;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ElephantRune;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__EmeraldEgg;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__EmeraldWhelp;
extern const gd::GdClassMeta META_Gd__gd_core_items__LeatherArmor;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__EmployeeUniform;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__EnchantedWeapons;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__EnergyConversion;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__EngineerBag2;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__EngineerBox;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Everburning;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__EvilHat;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ExtraAngy;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ExtraBags;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__FalseLife;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Fedora;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__FirePit;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Shelly;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__FireShelly;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Flame;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__FlameBadge;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__FlameWhip;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ForestDragon;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ForestFriend;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ForgingHammer;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__FortunasKiss;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__FriendlyFire;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Toad;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__FrogPrince;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Frostbite;
extern const gd::GdClassMeta META_Gd__gd_core_items__Shield;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__FrozenBuckler;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__FrozenFlame;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__FullBodyProtection;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__FurciferPrime;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Generator;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Ghost;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Gigawatz;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__GirlPower;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__GoldArmor;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__GoldCube;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Halberd;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Hardwood;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__HawkRune;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__HeartShield;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__HeartoftheCards;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__HeavyDrinking;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Hedgehog;
extern const gd::GdClassMeta META_Gd__gd_core_items__WoodenBuckler;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__HeroShield;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__HogusBogus;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Holdall;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__HolyCollar;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__HyperHedgehog;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Hypercube;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__IceArmor;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__IceDragon;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__IceFlower;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__InnerPower;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__InvestmentOpportunity;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Joker;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__JustStats;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__JynxStaff;
extern const gd::GdClassMeta META_Gd__gd_core_items__RibSawBlade;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Katana;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__KingCrown;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__KingGoobert;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__KingoftheBling;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__KnifetoMeetYou;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Laboratory;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__LeafBadge;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__LevelUp;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__LightFlower;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__LightningPotion;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__LightningStaff;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__LittleMimic;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__LongSpear;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Lootbox;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__LuckyCat;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__LuckyShortbow;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__MageHat;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__MagicBadge;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__MagicCollar;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__MagicMirror;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__MagicRing;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__MagicRing__INNER__RingEffect;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__MagiteccArmor;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ManaCrystal;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ManaMastery;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Mananana;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Markswoman;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__MechaBat;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__MegaClover;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__MercuryElemental;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__MissFortune;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__MoltenDagger;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__MoltenGreatsword;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__MoltenSpear;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__MoltenSpear2;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__MoonArmor;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__MoreStats;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__MrsStruggles;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__MushroomFarm;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__NoRushPlease;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__NullBlade;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ObsidianDragon;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__OilLamp;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__OnionCutter;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__OwlSpirit;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ParadiseBirb;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__PerpetuumMobile;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Phoenix;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Phoenix2;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__PiggyPinata;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__PiggyofRiches;
extern const gd::GdClassMeta META_Gd__gd_core_items__SpikedShield;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__PineProtector;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__PlasticCube;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__PoisonFrog;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__PoisonGrenade;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__PoisonShortbow;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__PoisonSpear;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Pop;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__PortableAltar;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Pot;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__PoweroftheMoon;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__PrismaticSword;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__PrismaticWand;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__PuzzleBadge;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__PuzzlebagJ;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__PuzzlebagL;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__PuzzlebagS;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__PuzzlebagT;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__PuzzlebagZ;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Puzzlebox;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__RainbowBadge;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__RainbowGoobertAdventurer;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__RainbowGoobertBerserker;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__RainbowGoobertEngineer;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__RainbowGoobertMage;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__RainbowGoobertPyromancer;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__RainbowOrb;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__RainbowPotion;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__RandomLoadoutBag;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Rat;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__RatChef;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Recombobulator;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__RelicCase;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Repeater;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Resistor;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Reverse;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Robodog;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Rope;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Sandbag;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SapphireEgg;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SapphireWhelp;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Scale;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ScholarBag;
extern const gd::GdClassMeta META_Gd__gd_core_items__Lightsaber;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Scissorswords;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SealtheDeal;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SerpentStaff;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SewingCase;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ShamanMask;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ShellTotem;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ShepherdsCrook;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Shielded;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ShinyMantle;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ShinyShell;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SkullBadge;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SliceofBread;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SliceofToast;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SlimeTime;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Sloth;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SmellyBarrier;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SmithingForDummies;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Snake;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SnowStick;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Snowball;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Snowcake;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Snowman;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Snowmaster;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Solaris;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SpeakwithAnimals;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SpellScrollDark;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SpellScrollFrostbolt;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SpellScrollIce;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SpellScrollLight;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SpellScrollNature;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SpicyBanana;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SpikedCollar;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SpikedStaff;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SpikedWall;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SpintoWin;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SpiritBells;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SpringLoader;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Squirrel;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SquirrelArcher;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__StaffofFire;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__StarofCourage;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SteelDragon;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__StoneArmor;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__StoneBadge;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__StoneGloves;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__StoneGolem;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__StoneShoes;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Stoned;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__StrongDivinePotion;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__VampiricPotion;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__StrongVampiricPotion;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SunArmor;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SunShield;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__TeslaCoil;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ThornElemental;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ThornShortbow;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Thornbloom;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Thornburst;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ThorsHammer;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ThunderDrake;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__TigerRune;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__TimeDilator;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__TimeMelting;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__TimePendant;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ToastGoobert;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Toolbox;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Turtle;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Twine;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__TwineBadge;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Ukulele;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Ultima;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__UnidentifiedSkill;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__UniquelyUnique;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__VampiricCollar;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__VineweaveBasket;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Wand;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__WandofDissonance;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__WarScythe;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__WaterElemental;
extern const gd::GdClassMeta META_Gd__gd_core_items__Whetstone;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Whetstone3;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__WingedBoots;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Wisp;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__WolfBadge;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__WolfEmblem;
extern const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Wrench;
extern const gd::GdClassMeta META_Gd__gd_core_items__FalconBlade;
extern const gd::GdClassMeta META_Gd__gd_core_items__FancyFencingRapier;
extern const gd::GdClassMeta META_Gd__gd_core_items__Fanfare;
extern const gd::GdClassMeta META_Gd__gd_core_items__FannyPack;
extern const gd::GdClassMeta META_Gd__gd_core_items__Flute;
extern const gd::GdClassMeta META_Gd__gd_core_items__FlyAgaric;
extern const gd::GdClassMeta META_Gd__gd_core_items__Garlic;
extern const gd::GdClassMeta META_Gd__gd_core_items__Gems__Amethyst;
extern const gd::GdClassMeta META_Gd__gd_core_items__Gems__CorruptedCrystal;
extern const gd::GdClassMeta META_Gd__gd_core_items__Gems__Emerald;
extern const gd::GdClassMeta META_Gd__gd_core_items__Gems__LumpofCoal;
extern const gd::GdClassMeta META_Gd__gd_core_items__Gems__Ruby;
extern const gd::GdClassMeta META_Gd__gd_core_items__Gems__Sapphire;
extern const gd::GdClassMeta META_Gd__gd_core_items__Gems__Skull;
extern const gd::GdClassMeta META_Gd__gd_core_items__Gems__Topaz;
extern const gd::GdClassMeta META_Gd__gd_core_items__GingerbreadMan;
extern const gd::GdClassMeta META_Gd__gd_core_items__GlovesofHaste;
extern const gd::GdClassMeta META_Gd__gd_core_items__Hammer;
extern const gd::GdClassMeta META_Gd__gd_core_items__HealingHerbs;
extern const gd::GdClassMeta META_Gd__gd_core_items__HeartContainer;
extern const gd::GdClassMeta META_Gd__gd_core_items__HeartofDarkness;
extern const gd::GdClassMeta META_Gd__gd_core_items__HeroLongsword;
extern const gd::GdClassMeta META_Gd__gd_core_items__HeroSword;
extern const gd::GdClassMeta META_Gd__gd_core_items__HeroicPotion;
extern const gd::GdClassMeta META_Gd__gd_core_items__HoloFireLizard;
extern const gd::GdClassMeta META_Gd__gd_core_items__HolyArmor;
extern const gd::GdClassMeta META_Gd__gd_core_items__HolySpear;
extern const gd::GdClassMeta META_Gd__gd_core_items__HungryBlade;
extern const gd::GdClassMeta META_Gd__gd_core_items__Item__INNER__SignalConnection;
extern const gd::GdClassMeta META_Gd__gd_core_items__Jynxtorquilla;
extern const gd::GdClassMeta META_Gd__gd_core_items__LeatherBoots;
extern const gd::GdClassMeta META_Gd__gd_core_items__LightGoobert;
extern const gd::GdClassMeta META_Gd__gd_core_items__LuckyBow;
extern const gd::GdClassMeta META_Gd__gd_core_items__LuckyClover;
extern const gd::GdClassMeta META_Gd__gd_core_items__LuckyPiggy;
extern const gd::GdClassMeta META_Gd__gd_core_items__MagicStaff;
extern const gd::GdClassMeta META_Gd__gd_core_items__MagicTorch;
extern const gd::GdClassMeta META_Gd__gd_core_items__ManaOrb;
extern const gd::GdClassMeta META_Gd__gd_core_items__ManaPotion;
extern const gd::GdClassMeta META_Gd__gd_core_items__Manathirst;
extern const gd::GdClassMeta META_Gd__gd_core_items__MoonShield;
extern const gd::GdClassMeta META_Gd__gd_core_items__MrStruggles;
extern const gd::GdClassMeta META_Gd__gd_core_items__Pandamonium;
extern const gd::GdClassMeta META_Gd__gd_core_items__PiercingArrow;
extern const gd::GdClassMeta META_Gd__gd_core_items__Pineapple;
extern const gd::GdClassMeta META_Gd__gd_core_items__PlatinCustomerCard;
extern const gd::GdClassMeta META_Gd__gd_core_items__PocketSand;
extern const gd::GdClassMeta META_Gd__gd_core_items__PoisonBow;
extern const gd::GdClassMeta META_Gd__gd_core_items__PoisonDagger;
extern const gd::GdClassMeta META_Gd__gd_core_items__PoisonGoobert;
extern const gd::GdClassMeta META_Gd__gd_core_items__PoisonIvy;
extern const gd::GdClassMeta META_Gd__gd_core_items__PotionBelt;
extern const gd::GdClassMeta META_Gd__gd_core_items__Present;
extern const gd::GdClassMeta META_Gd__gd_core_items__ProtectivePurse;
extern const gd::GdClassMeta META_Gd__gd_core_items__Pumpkin;
extern const gd::GdClassMeta META_Gd__gd_core_items__RainbowGoobert;
extern const gd::GdClassMeta META_Gd__gd_core_items__RainbowGoobertRanger;
extern const gd::GdClassMeta META_Gd__gd_core_items__RangerBag;
extern const gd::GdClassMeta META_Gd__gd_core_items__RubyChonk;
extern const gd::GdClassMeta META_Gd__gd_core_items__RubyEgg;
extern const gd::GdClassMeta META_Gd__gd_core_items__ShieldofValor;
extern const gd::GdClassMeta META_Gd__gd_core_items__Shovel;
extern const gd::GdClassMeta META_Gd__gd_core_items__Spear;
extern const gd::GdClassMeta META_Gd__gd_core_items__SpectralDagger;
extern const gd::GdClassMeta META_Gd__gd_core_items__StaffofUnhealing;
extern const gd::GdClassMeta META_Gd__gd_core_items__StaminaSack;
extern const gd::GdClassMeta META_Gd__gd_core_items__SteelGoobert;
extern const gd::GdClassMeta META_Gd__gd_core_items__StoneHelm;
extern const gd::GdClassMeta META_Gd__gd_core_items__StorageCoffin;
extern const gd::GdClassMeta META_Gd__gd_core_items__StrongDemonicFlask;
extern const gd::GdClassMeta META_Gd__gd_core_items__StrongHealthPotion;
extern const gd::GdClassMeta META_Gd__gd_core_items__StrongPestilenceFlask;
extern const gd::GdClassMeta META_Gd__gd_core_items__StrongStoneSkinPotion;
extern const gd::GdClassMeta META_Gd__gd_core_items__TheFool;
extern const gd::GdClassMeta META_Gd__gd_core_items__TheLovers;
extern const gd::GdClassMeta META_Gd__gd_core_items__ThornBow;
extern const gd::GdClassMeta META_Gd__gd_core_items__ThornWhip;
extern const gd::GdClassMeta META_Gd__gd_core_items__Torch;
extern const gd::GdClassMeta META_Gd__gd_core_items__VampiricArmor;
extern const gd::GdClassMeta META_Gd__gd_core_items__VampiricGloves;
extern const gd::GdClassMeta META_Gd__gd_core_items__VampiricScythe;
extern const gd::GdClassMeta META_Gd__gd_core_items__VillainSword;
extern const gd::GdClassMeta META_Gd__gd_core_items__WalrusTusk;
extern const gd::GdClassMeta META_Gd__gd_core_items__White_EyesBlueDragon;
extern const gd::GdClassMeta META_Gd__gd_core_items__Wolpertinger;
extern const gd::GdClassMeta META_Gd__gd_core_items__WoodenSword;
extern const gd::GdClassMeta META_Gd__gd_core_items__YggdrasilLeaf;
