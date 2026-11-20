#include "../../native_inline_dispatch.hpp"
#include "../../native_scalar_equal.hpp"
#include "../../native_array_index.hpp"
#pragma STDC FP_CONTRACT OFF

#include "../hdrs/Gd__gd_core__Item.hpp"
#include "../hdrs/Gd__gd_core__Weapon.hpp"
#include "../hdrs/Gd__gd_core__CoreBuff__INNER__TemporaryStacks.hpp"
#include "../hdrs/Gd__gd_core__CoreBuff.hpp"
#include "../hdrs/Gd__gd_core__CoreItemBook.hpp"
#include "../hdrs/Gd__gd_core__DarkestLotus.hpp"
#include "../hdrs/Gd__gd_core__Flute.hpp"
#include "../hdrs/Gd__gd_core__HolySpear.hpp"
#include "../hdrs/Gd__gd_core__ManaPotion.hpp"
#include "../hdrs/Gd__gd_core__PoisonIvy.hpp"
#include "../hdrs/Gd__gd_core__SpikedShield.hpp"
#include "../hdrs/Gd__gd_core__StrongStoneSkinPotion.hpp"
#include "../hdrs/Gd__gd_core__YggdrasilLeaf.hpp"
#include "../hdrs/Gd__gd_core_items__BloodyDagger.hpp"
#include "../hdrs/Gd__gd_core_items__CursedDagger.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__AmuletofAgility.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__PowerPuppy.hpp"
#include "../hdrs/Gd__gd_core_items__Greatsword.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Broccoli.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__CheeseGoobert.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__ChiliGoobert.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__DarkLantern.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__DragonSet.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__EvilHat.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Toad.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__HawkRune.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__InvestmentOpportunity.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__LittleMimic.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__MechaBat.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__OnionCutter.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__PortableAltar.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__RainbowGoobertMage.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__SapphireWhelp.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__SliceofToast.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__SpellScrollLight.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__Stoned.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__TigerRune.hpp"
#include "../hdrs/Gd__gd_core_items__Exclusive__WandofDissonance.hpp"
#include "../hdrs/Gd__gd_core_items__Garlic.hpp"
#include "../hdrs/Gd__gd_core_items__HeroLongsword.hpp"
#include "../hdrs/Gd__gd_core_items__ManaPotion.hpp"
#include "../hdrs/Gd__gd_core_items__Pumpkin.hpp"
#include "../hdrs/Gd__gd_core_items__StrongHealthPotion.hpp"
#include "../hdrs/Gd__gd_core_items__YggdrasilLeaf.hpp"

namespace {
constexpr gd::GdStr battle_string_literals[] = {
    {"onPreDealDamage_early", 21u, 1141032398u},
    {"onPreDealDamage_late", 20u, 4290954099u},
    {"onDealtDamage", 13u, 1467360435u},
    {"onChargeReceived", 16u, 1513811791u},
    {"onChargeLeft", 12u, 164060557u},
    {"\n", 1u, 252472541u},
    {"", 0u, 2166136261u},
    {"itemName", 8u, 1465527077u},
    {"TOOLTIP_Requires", 16u, 3071687997u},
    {"$t", 2u, 1304173253u},
    {"\n\n", 2u, 2274317941u},
    {"$dam", 4u, 384632643u},
    {"cd", 2u, 1529452802u},
    {"chance2", 7u, 2950484105u},
    {"chance", 6u, 2459084481u},
    {"shopchance", 10u, 2610829829u},
    {"stamina", 7u, 3875003702u},
    {"p", 1u, 4111221743u},
    {"p_", 2u, 1917750800u},
    {"$block", 6u, 2348543500u},
    {"$", 1u, 554469683u},
    {"+", 1u, 772578730u},
    {"-", 1u, 671913016u},
    {"checkIfOutofStorageBounds2", 26u, 2602938099u},
    {"checkIfOutofStorageBounds3", 26u, 2586160480u},
    {"baseScale", 9u, 3579969818u},
    {"scale", 5u, 2190941297u},
    {"fuse", 4u, 4171135248u},
    {"disablePicking", 14u, 597376634u},
    {"TYPE_", 5u, 2573856662u},
    {"_DESCR", 6u, 2384941927u},
    {">100", 4u, 388149904u},
    {"<0", 2u, 2583112081u},
    {"dur", 3u, 3509645056u},
    {"boxOfRichesDescriptor", 21u, 1996212508u},
    {"Box of Riches", 13u, 862823567u},
    {"deckOfCardsDescriptor", 21u, 2722520953u},
    {"Deck of Cards", 13u, 436267722u},
    {"crossbladesDescriptor", 21u, 2033616221u},
    {"Crossblades", 11u, 3990133388u},
    {"platinCardDescriptor", 20u, 3403080056u},
    {"Platin Customer Card", 20u, 1703252961u},
    {"customerCardDescriptor", 22u, 3763003386u},
    {"Customer Card", 13u, 3033338573u},
    {"staminaSackDescriptor", 21u, 1965679473u},
    {"Stamina Sack", 12u, 3135812348u},
    {"presentDescriptor", 17u, 1858788701u},
    {"Present", 7u, 3512730252u},
    {"flameDescriptor", 15u, 3523079873u},
    {"Flame", 5u, 739594656u},
    {"forgingHammerDescriptor", 23u, 2921911980u},
    {"Forging Hammer", 14u, 2012707339u},
    {"amuletDescriptor", 16u, 1685237882u},
    {"Amulet Unidentified", 19u, 638958243u},
    {"amuletOfFeastingDescriptor", 26u, 249419962u},
    {"Amulet of Feasting", 18u, 2062239057u},
    {"starOfCourageDescriptor", 23u, 206666617u},
    {"Star of Courage", 15u, 3653331906u},
    {"toolboxDescriptor", 17u, 1367621113u},
    {"Toolbox", 7u, 597333304u},
    {"stableRecombobulatorDescriptor", 30u, 2558593979u},
    {"Stable Recombobulator", 21u, 3983563330u},
    {"unstableRecombobulatorDescriptor", 32u, 38124712u},
    {"Unstable Recombobulator", 23u, 2655714527u},
    {"extraBagsDescriptor", 19u, 2277850167u},
    {"Extra Bags", 10u, 1582034104u},
    {"rainbowBadgeDescriptor", 22u, 810458013u},
    {"Rainbow Badge", 13u, 819824714u},
    {"stoneBadgeDescriptor", 20u, 3366920828u},
    {"Stone Badge", 11u, 3715462197u},
    {"spiritBellsDescriptor", 21u, 2726125019u},
    {"Spirit Bells", 12u, 4062755974u},
    {"bagOfGivingDescriptor", 21u, 1473344899u},
    {"Bag of Giving", 13u, 4233879148u},
    {"chessboardDescriptor", 20u, 270965448u},
    {"Chess Board", 11u, 1363195651u},
    {"snowmanDescriptor", 17u, 1379168291u},
    {"Snowman", 7u, 2047827902u},
    {"uniquelyUniqueDescriptor", 24u, 1254685707u},
    {"Uniquely Unique", 15u, 1532605948u},
    {"bagtacularDescriptor", 20u, 3261577804u},
    {"Bagtacular", 10u, 2131747329u},
    {"justStatsDescriptor", 19u, 541757847u},
    {"Just Stats", 10u, 85500356u},
    {"moreStatsDescriptor", 19u, 2065898162u},
    {"More Stats", 10u, 2440539571u},
    {"unidentifiedSkillDescriptor", 27u, 469615797u},
    {"Unidentified Skill", 18u, 1611209854u},
    {"digDeeperDescriptor", 19u, 2418370651u},
    {"Dig Deeper", 10u, 1066692160u},
    {"puzzleboxDescriptor", 19u, 416930639u},
    {"Puzzlebox", 9u, 3354515146u},
    {"puzzleBadgeDescriptor", 21u, 2834935697u},
    {"Puzzle Badge", 12u, 635366294u},
    {"sewingCaseDescriptor", 20u, 4218609003u},
    {"Sewing Case", 11u, 2327584018u},
    {"twineDescriptor", 15u, 12369031u},
    {"Twine", 5u, 2118728898u},
    {"arcaneIntellectDescriptor", 25u, 1747022228u},
    {"Arcane Intellect", 16u, 561750147u},
    {"fedoraDescriptor", 16u, 3790577077u},
    {"Fedora", 6u, 1681508420u},
    {"piggyOfRichesDescriptor", 23u, 4274846161u},
    {"Piggy of Riches", 15u, 244618730u},
    {"batteryDescriptor", 17u, 4199237043u},
    {"Battery", 7u, 2215305518u},
    {"coilDescriptor", 14u, 3975905719u},
    {"Coil", 4u, 1417237842u},
    {"chargeSplitterDescriptor", 24u, 1654689239u},
    {"Charge Splitter", 15u, 3478118124u},
    {"manaCrystalDescriptor", 21u, 167005813u},
    {"Mana Crystal", 12u, 62146832u},
    {"lightningStaffDescriptor", 24u, 4188777276u},
    {"Lightning Staff", 15u, 834364379u},
    {"boxofCogsDescriptor", 19u, 2952478470u},
    {"Engineer Bag 2", 14u, 695622072u},
    {"cogDescriptor", 13u, 163099041u},
    {"Cog", 3u, 1243110080u},
    {"generatorDescriptor", 19u, 1213924711u},
    {"Generator", 9u, 2474216290u},
    {"cogBadgeDescriptor", 18u, 3174225626u},
    {"Cog Badge", 9u, 4048964603u},
    {"contraptronDescriptor", 21u, 80599494u},
    {"Con-Trap-Tron", 13u, 1378335927u},
    {"bloodAmuletDescriptor", 21u, 2844272968u},
    {"Blood Amulet", 12u, 3846820795u},
    {"magicRingDescriptor", 19u, 2626943051u},
    {"Magic Ring", 10u, 1419515934u},
    {"superiorRingDescriptor", 22u, 2733054533u},
    {"Superior Ring", 13u, 566903024u},
    {"hyperCubeDescriptor", 19u, 4054546533u},
    {"Hypercube", 9u, 3149274804u},
    {"identifier", 10u, 681945150u},
    {"name", 4u, 2369371622u},
    {"character_mana_changed", 22u, 798563205u},
    {"checkTrigger", 12u, 3751686889u},
    {"character_invulnerable_end", 26u, 3350240732u},
    {"onInvuEnded", 11u, 2135122486u},
    {"dur_invu", 8u, 277695711u},
    {"BuffTimer", 9u, 194754125u},
    {"buffEnded", 9u, 3457903416u},
    {"onManaChanged", 13u, 3105672029u},
    {"character_damaged", 17u, 745527748u},
    {"onDamaged", 9u, 2303747743u},
    {"character_spikes_changed", 24u, 3463900413u},
    {"onSpikesChanged", 15u, 3715123341u},
    {"character_poison_changed", 24u, 65736246u},
    {"onOpponentPoisonChanged", 23u, 839266911u},
    {"spikes", 6u, 439106706u},
    {"maxspikes", 9u, 2756726798u},
    {"used", 4u, 1786277552u},
    {"heal", 4u, 979982427u},
    {"onOpponentDebuffsChanged", 24u, 915890936u},
    {"onBuffChanged", 13u, 3423803215u},
    {"speed", 5u, 2072037248u},
    {"onBuffTimeout", 13u, 3028159308u},
    {"refund", 6u, 854262879u},
    {"character_empower_changed", 25u, 2356601027u},
    {"empowerChanged", 14u, 196501932u},
    {"luck", 4u, 4145017712u},
    {"luckt", 5u, 4061892428u},
    {"regen", 5u, 16724762u},
    {"reincarnated", 12u, 2408540175u},
    {"onReincarnate", 13u, 4250852970u},
    {"InvuTimer", 9u, 2229828220u},
    {"invuEnded", 9u, 1230811445u},
    {"battle_rage_started", 19u, 3997014835u},
    {"onBattleRageStarted", 19u, 3330696088u},
    {"battle_rage_ended", 17u, 4230921894u},
    {"onBattleRageEnded", 17u, 1252110145u},
    {"character_attacked", 18u, 2439462988u},
    {"onOpponentDamaged", 17u, 568571164u},
    {"lifesteal", 9u, 1515578962u},
    {"Dragonscale Armor", 17u, 1799586915u},
    {"Dragonskin Boots", 16u, 504138766u},
    {"Dragon Claws", 12u, 373507398u},
    {"Leather Armor", 13u, 3834961017u},
    {"Leather Boots", 13u, 3731890527u},
    {"Gloves of Haste", 15u, 3287234075u},
    {"heat", 4u, 577319571u},
    {"max", 3u, 3617776409u},
    {"unhealing", 9u, 1425973148u},
    {"unhealing2", 10u, 2060803818u},
    {"onDebuffsChanged", 16u, 4096794781u},
    {"onOpponentBuffsChanged", 22u, 3002324355u},
    {"buffs", 5u, 2149256365u},
    {"buffs2", 6u, 1234493005u},
    {"onBuffsChanged", 14u, 1288163266u},
    {"gained", 6u, 52449535u},
    {"mana", 4u, 3650585354u},
    {"luck2", 5u, 807137510u},
    {"mana2", 5u, 3246625064u},
    {"critchance", 10u, 985367881u},
    {"critdam", 7u, 4140065929u},
    {"maxhealth", 9u, 429334299u},
    {"vampirism", 9u, 773404377u},
    {"vampirism2", 10u, 2092004337u},
    {"dam", 3u, 4031722721u},
    {"empower", 7u, 2037162760u},
    {"staminat", 8u, 3660664550u},
    {"character_block_changed", 23u, 4278945901u},
    {"onBlockChanged", 14u, 2151465311u},
    {"attacked", 8u, 3381721668u},
    {"onStoneAttacked", 15u, 3780967220u},
    {"Stone", 5u, 1842662042u},
    {"Stone Golem", 11u, 3382673014u},
    {"Stone Armor", 11u, 1823255725u},
    {"blockfordam", 11u, 2524681669u},
    {"damreduction", 12u, 2823666870u},
    {"pre_deal_damage_late", 20u, 1012238672u},
    {"preAttack", 9u, 3919347442u},
    {"chance_vamp", 11u, 3634579442u},
    {"block", 5u, 3943480674u},
    {"healtht", 7u, 1555997217u},
    {"fatigue_start", 13u, 1129723937u},
    {"onFatigueStarted", 16u, 504449962u},
    {"dur_stun", 8u, 1388942617u},
};
}

static const gd::GdEnum::KV _ekv_Gd__gd_core__Item_Owner[] = {{"Shop", 0LL}, {"PlayerInventory", 1LL}, {"PlayerStorageBox", 2LL}, {"Opponent", 3LL}, {"Title", 4LL}, {"RecipeBook", 5LL}, {"Tooltip", 6LL}, {"Socket", 7LL}, {"ItemLibrary", 8LL}, {"InfoPanelIcon", 9LL}, {"BuildViewer", 10LL}, {"BuildViewerIcon", 11LL}, {"GridStorage", 12LL}, {"Undefined", 13LL}};
static const gd::GdEnum _enum_Gd__gd_core__Item_Owner = {"Owner", _ekv_Gd__gd_core__Item_Owner, 14u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__Item_Type[] = {{"Bag", 0LL}, {"Consumable", 1LL}, {"Food", 2LL}, {"Pet", 3LL}, {"Weapon", 4LL}, {"Shield", 5LL}, {"Armor", 6LL}, {"Gloves", 7LL}, {"Shoes", 8LL}, {"Helmet", 9LL}, {"Accessory", 10LL}, {"Potion", 11LL}, {"Card", 12LL}, {"Gem", 13LL}, {"Scroll", 14LL}, {"Book", 15LL}, {"Skill", 16LL}, {"ChessPiece", 17LL}, {"Spell", 18LL}, {"Melee", 19LL}, {"Ranged", 20LL}, {"Effect", 21LL}, {"Holy", 22LL}, {"Magic", 23LL}, {"Vampiric", 24LL}, {"Dark", 25LL}, {"Nature", 26LL}, {"Fire", 27LL}, {"Ice", 28LL}, {"Musical", 29LL}};
static const gd::GdEnum _enum_Gd__gd_core__Item_Type = {"Type", _ekv_Gd__gd_core__Item_Type, 30u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__Item_Priority[] = {{"Lowest", -10000LL}, {"Low", -1000LL}, {"Normal", 0LL}, {"High", 1000LL}, {"Highest", 10000LL}};
static const gd::GdEnum _enum_Gd__gd_core__Item_Priority = {"Priority", _ekv_Gd__gd_core__Item_Priority, 5u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__Item_CraftingPriority[] = {{"Gem", 3LL}, {"Mixed", 2LL}, {"NonGem", 1LL}};
static const gd::GdEnum _enum_Gd__gd_core__Item_CraftingPriority = {"CraftingPriority", _ekv_Gd__gd_core__Item_CraftingPriority, 3u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__Item_Tag[] = {{"None", 0LL}, {"Lifesteal", 1LL}, {"Stone", 2LL}, {"Scroll", 8LL}, {"Dragon", 16LL}, {"Staff", 32LL}, {"BattleRage", 64LL}, {"Singular", 128LL}, {"Transient", 256LL}, {"Bow", 512LL}};
static const gd::GdEnum _enum_Gd__gd_core__Item_Tag = {"Tag", _ekv_Gd__gd_core__Item_Tag, 10u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__Item_Stack[] = {{"None", 0LL}, {"Block", 1LL}, {"Lucky", 2LL}, {"Regeneration", 4LL}, {"Vampirism", 8LL}, {"Spikes", 16LL}, {"Mana", 32LL}, {"Empower", 64LL}, {"Heat", 128LL}, {"Poison", 256LL}, {"Blind", 512LL}, {"Cold", 1024LL}, {"Buff", 254LL}, {"Debuff", 1792LL}, {"BuffNoLuck", 252LL}};
static const gd::GdEnum _enum_Gd__gd_core__Item_Stack = {"Stack", _ekv_Gd__gd_core__Item_Stack, 15u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__Item_Mat[] = {{"Default", 0LL}, {"Wood", 1LL}, {"Metal", 2LL}, {"Leather", 3LL}, {"Glass", 4LL}, {"Stone", 5LL}, {"Squishy", 6LL}, {"Jewelry", 7LL}, {"Sand", 8LL}, {"Paper", 9LL}, {"Slime", 10LL}, {"Ice", 11LL}, {"Fire", 12LL}, {"Dragon", 13LL}, {"Bird", 14LL}, {"Leaf", 15LL}};
static const gd::GdEnum _enum_Gd__gd_core__Item_Mat = {"Mat", _ekv_Gd__gd_core__Item_Mat, 16u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__Item_Physics[] = {{"Default", 0LL}, {"Light", 1LL}, {"Slime", 2LL}, {"Dense", 3LL}, {"VeryDense", 4LL}, {"Floaty", 5LL}, {"Sand", 6LL}, {"Plush", 7LL}, {"BouncyDense", 8LL}, {"Ice", 9LL}, {"Ghost", 10LL}, {"BlackHole", 11LL}};
static const gd::GdEnum _enum_Gd__gd_core__Item_Physics = {"Physics", _ekv_Gd__gd_core__Item_Physics, 12u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__Item_Rarity[] = {{"Common", 0LL}, {"Rare", 1LL}, {"Epic", 2LL}, {"Legendary", 3LL}, {"Godly", 4LL}, {"Unique", 5LL}};
static const gd::GdEnum _enum_Gd__gd_core__Item_Rarity = {"Rarity", _ekv_Gd__gd_core__Item_Rarity, 6u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__Item_FaceDirection[] = {{"UP", 0LL}, {"RIGHT", 1LL}, {"DOWN", 2LL}, {"LEFT", 3LL}};
static const gd::GdEnum _enum_Gd__gd_core__Item_FaceDirection = {"FaceDirection", _ekv_Gd__gd_core__Item_FaceDirection, 4u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__Item_StatModified[] = {{"No", 0LL}, {"Positive", 1LL}, {"Negative", 2LL}};
static const gd::GdEnum _enum_Gd__gd_core__Item_StatModified = {"StatModified", _ekv_Gd__gd_core__Item_StatModified, 3u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__Item_DropResult[] = {{"AddedToInventory", 0LL}, {"Hotswap", 1LL}, {"InventoryCollision", 2LL}, {"OutsideInventory", 3LL}, {"AddedToStorageBox", 4LL}, {"Sold", 5LL}, {"Socketed", 6LL}, {"SocketHotswap", 7LL}, {"Failed", 8LL}};
static const gd::GdEnum _enum_Gd__gd_core__Item_DropResult = {"DropResult", _ekv_Gd__gd_core__Item_DropResult, 9u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__Item_PickupType[] = {{"Grabbed", 0LL}, {"Hotswap", 1LL}, {"MultiSelect", 2LL}};
static const gd::GdEnum _enum_Gd__gd_core__Item_PickupType = {"PickupType", _ekv_Gd__gd_core__Item_PickupType, 3u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__Item_Affected[] = {{"Primary", 0LL}, {"Secondary", 2LL}, {"Tertiary", 4LL}, {"Lightning", 7LL}};
static const gd::GdEnum _enum_Gd__gd_core__Item_Affected = {"Affected", _ekv_Gd__gd_core__Item_Affected, 4u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__Item_Tiles[] = {{"Extension", 2LL}, {"Collision", 3LL}, {"Affected", 4LL}, {"AffectedDynamic", 5LL}, {"AffectedSecondary", 6LL}, {"AffectedSecondaryDynamic", 7LL}, {"AffectedExtension", 8LL}, {"AffectedTertiary", 10LL}, {"AffectedLightning", 11LL}};
static const gd::GdEnum _enum_Gd__gd_core__Item_Tiles = {"Tiles", _ekv_Gd__gd_core__Item_Tiles, 9u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__Item_ActivationAni[] = {{"Scale", 0LL}, {"Jump", 1LL}, {"SquishyJump", 2LL}, {"VerySquishyJump", 3LL}, {"Slash", 4LL}, {"Stab", 5LL}, {"Bonk", 6LL}, {"ReverseBonk", 7LL}, {"Chop", 8LL}, {"Squish", 9LL}, {"Block", 10LL}, {"Wave", 11LL}, {"Potion", 12LL}, {"Sweep", 13LL}, {"Spin", 14LL}, {"Throw", 15LL}, {"Shoot", 16LL}, {"Struggle", 17LL}, {"ReverseStab", 18LL}, {"Hiss", 19LL}, {"Tackle", 20LL}, {"DoubleSlash", 21LL}, {"Flash", 22LL}};
static const gd::GdEnum _enum_Gd__gd_core__Item_ActivationAni = {"ActivationAni", _ekv_Gd__gd_core__Item_ActivationAni, 23u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__Item_Stat[] = {{"MinDamage", 0LL}, {"MaxDamage", 1LL}, {"StaminaCost", 2LL}, {"Speed", 3LL}, {"BaseCooldown", 4LL}, {"Accuracy", 5LL}, {"CritChance", 6LL}, {"Chance", 7LL}, {"Chance2", 8LL}, {"Cooldown", 9LL}};
static const gd::GdEnum _enum_Gd__gd_core__Item_Stat = {"Stat", _ekv_Gd__gd_core__Item_Stat, 10u};
static const gd::GdEnum::KV _ekv_Gd__gd_core__Item_StackChangeType[] = {{"Added_Player", 0LL}, {"Added_Opponent", 1LL}, {"Removed_Player", 2LL}, {"Removed_Opponent", 3LL}, {"Used_Player", 4LL}, {"Used_Opponent", 5LL}};
static const gd::GdEnum _enum_Gd__gd_core__Item_StackChangeType = {"StackChangeType", _ekv_Gd__gd_core__Item_StackChangeType, 6u};
void Gd__gd_core__Item::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__CoreItem::init_fields(gd_ctx);
    this->f_numStackChangeTypes = gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StackChangeType_871), gd::SYM_size, nullptr, 0);
    this->f_spriteScale = gd::GdVal::null();
    this->f_hasSquishySprite = gd::GdVal::from_bool(false);
    this->f_specificDragParticles = gd::GdVal::from_arr(gd::GdArr::create(gd_ctx.arena));
    this->f_dragParticlesEnabled = gd::GdVal::from_bool(true);
    this->f_frictionTime = gd::GdVal::from_float(15.0);
    this->f_totalWeight = gd::GdVal::from_float(0.0);
    this->f_me = gd::GdVal::from_obj(this);
    this->f_mouseIsOverItem = gd::GdVal::from_bool(false);
    this->f_hovered = gd::GdVal::from_bool(false);
    this->f_focus = gd::GdVal::from_bool(false);
    this->f_spotlight = gd::GdVal::from_bool(false);
    this->f_collisionShape = gd::GdVal::null();
    this->f_wasJustCrafted = gd::GdVal::from_bool(false);
    this->f_pickupPosition = gd::GdVal::from_vec2(0.0, 0.0);
    this->f_pickupRotation = gd::GdVal::from_float(0.0);
    this->f_pickupTopLeftCell = gd::GdVal::from_vec2(0.0, 0.0);
    this->f_pickupFaceDirection = gd::GdVal::from_int(0);
    this->f_sameOrientationAsPickup = gd::GdVal::from_bool(false);
    this->f_movebackTween = gd::GdVal::null();
    this->f_rotationTween = gd::GdVal::null();
    this->f_pickingEnabled = gd::GdVal::from_bool(true);
    this->f_tooltipEnabled = gd::GdVal::from_bool(true);
    this->f_hoverResponseEnabled = gd::GdVal::from_bool(true);
    this->f_focusEnabled = gd::GdVal::from_bool(true);
    this->f_affectedCellsActive = gd::GdVal::from_bool(true);
    this->f_affordable = gd::GdVal::from_bool(false);
    this->f_momentumStrength = gd::GdVal::from_float(0.0);
    this->f_momentum = gd::GdVal::from_vec2(0.0, 0.0);
    this->f_tooltip = gd::GdVal::null();
    this->f_tooltipMargin = gd::GdVal::from_vec2((gd::GdVal::from_int(100LL)).as_float(), (gd::GdVal::from_int(0LL)).as_float());
    this->f_tooltipUpdateQueued = gd::GdVal::from_bool(false);
    this->f_shadows = gd::GdVal::from_arr(gd::GdArr::create(gd_ctx.arena));
    this->f_spritesWithShadows = gd::GdVal::from_arr(gd::GdArr::create(gd_ctx.arena));
    this->f_shadowOffset = Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_shadowOffset_dropped_525);
    this->f_shadowTween = gd::GdVal::null();
    this->f_dropFrame = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_pickupFrame = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_mouseWheelRotationReadyTime = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_notEnoughGoldLabelReadyTime = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_averagedPosition = gd::GdVal::from_vec2(0.0, 0.0);
    this->f_impactSoundVolume = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_progressMaterial = gd::GdVal::null();
    this->f_insideRotationNode = gd::GdVal::null();
    this->f_draggedInsideItems = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_draggingParent = gd::GdVal::null();
    this->f_sold = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    this->f_lastVelocity = gd::GdVal::from_vec2(0.0, 0.0);
    this->f_lastCollisionPos = gd::GdVal::from_vec2(0.0, 0.0);
    this->f_lastCollider = gd::GdVal::null();
    this->f_impactSoundReadyTime = gd::GdVal::from_float(0.0);
    this->f_globalAffectVisuals = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_bondedBaseItem = gd::GdVal::null();
    this->f_bondedIngredients = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_locked = gd::GdVal::from_bool(false);
    this->f_bound = gd::GdVal::from_bool(false);
    this->f_curRecipe = gd::GdVal::null();
    this->f_bondVisuals = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_craftingLabel = gd::GdVal::null();
    this->f_craftingAniReadyTime = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_pooled = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    this->f_initialized = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    this->f_canAffectVisuals = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    this->f_rotationMomentum = gd::GdVal::from_int(0LL);
    this->f_bonusRotation = gd::GdVal::from_int(0LL);
    this->f_brightColor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(1.3), gd::GdVal::from_float(1.3), gd::GdVal::from_float(1.3), gd::GdVal::from_int(1LL)}; return gd::make_color_from_args(_ca, 4); })();
    this->f_defaultColor = gd::get_named_color("white");
    this->f_buildIntoRecipesTooltip = gd::GdVal::null();
    this->f_owningBuildIntoRecipesTooltip = gd::GdVal::null();
    this->f_ownerTypesWithBuildTooltip = ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 5); d->set(gd_ctx.arena, gd::GdVal::from_int(10LL), gd::GdVal::from_bool(true)); d->set(gd_ctx.arena, gd::GdVal::from_int(2LL), gd::GdVal::from_bool(true)); d->set(gd_ctx.arena, gd::GdVal::from_int(1LL), gd::GdVal::from_bool(true)); d->set(gd_ctx.arena, gd::GdVal::from_int(3LL), gd::GdVal::from_bool(true)); d->set(gd_ctx.arena, gd::GdVal::from_int(12LL), gd::GdVal::from_bool(true)); return gd::GdVal::from_dict(d); })();
    this->f_shaderTween = gd::GdVal::null();
    this->f_canCancelShaderTween = gd::GdVal::from_bool(true);
    this->f_nonRotatedProgress = gd::GdVal::from_float(0.0);
    this->f_fusing = gd::GdVal::from_bool(false);
    this->f_willBeConsumed = gd::GdVal::from_bool(false);
    this->f_fuseParticles1 = gd::GdVal::null();
    this->f_fuseParticles2 = gd::GdVal::null();
    this->f_fuseTween = gd::GdVal::null();
    this->f_fusingBonds = gd::GdVal::from_arr(gd::GdArr::create(gd_ctx.arena));
    this->f_collisionMap = gd::GdVal::null();
    this->f_animation = gd::GdVal::null();
    this->f_sprite = gd::GdVal::null();
    this->f_clickArea = gd::GdVal::null();
    this->f_dragParticles = gd::GdVal::null();
    this->f_sockets = gd::GdVal::from_arr(gd::GdArr::create(gd_ctx.arena));
    this->f_lock = gd::GdVal::null();
    this->f_lockAnimation = gd::GdVal::null();
    this->f_baseBounce = gd::GdVal::from_float(0.0);
    this->f_baseFriction = gd::GdVal::from_float(0.0);
}
const gd::GdClassMeta* Gd__gd_core__Item::meta() const { return &META_Gd__gd_core__Item; }
gd::GdVal Gd__gd_core__Item::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_Owner_854: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Owner);
        case SYM_GEN_Type_855: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Type);
        case SYM_GEN_Priority_856: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Priority);
        case SYM_GEN_CraftingPriority_857: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_CraftingPriority);
        case SYM_GEN_Tag_858: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Tag);
        case SYM_GEN_Stack_859: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Stack);
        case SYM_GEN_Mat_860: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Mat);
        case SYM_GEN_Physics_861: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Physics);
        case SYM_GEN_Rarity_862: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Rarity);
        case SYM_GEN_FaceDirection_863: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_FaceDirection);
        case SYM_GEN_StatModified_864: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_StatModified);
        case SYM_GEN_DropResult_865: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_DropResult);
        case SYM_GEN_PickupType_866: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_PickupType);
        case SYM_GEN_Affected_867: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Affected);
        case SYM_GEN_Tiles_868: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Tiles);
        case SYM_GEN_ActivationAni_869: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_ActivationAni);
        case SYM_GEN_Stat_870: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Stat);
        case SYM_GEN_StackChangeType_871: return gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_StackChangeType);
        case SYM_GEN_affectedColorToTileId_509: return ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 4); d->set(gd_ctx.arena, gd::GdVal::from_int(0LL), gd::GdVal::from_int(4LL)); d->set(gd_ctx.arena, gd::GdVal::from_int(1LL), gd::GdVal::from_int(6LL)); d->set(gd_ctx.arena, gd::GdVal::from_int(2LL), gd::GdVal::from_int(10LL)); d->set(gd_ctx.arena, gd::GdVal::from_int(3LL), gd::GdVal::from_int(11LL)); return gd::GdVal::from_dict(d); })();
        case SYM_GEN_rarityColors_511: return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.460205), gd::GdVal::from_float(0.874887), gd::GdVal::from_float(0.90625)}; return gd::make_color_from_args(_ca, 3); })(), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.0737), gd::GdVal::from_float(0.337874), gd::GdVal::from_float(0.898438)}; return gd::make_color_from_args(_ca, 3); })(), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.828125), gd::GdVal::from_int(0LL), gd::GdVal::from_int(1LL)}; return gd::make_color_from_args(_ca, 3); })(), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL), gd::GdVal::from_float(0.609375), gd::GdVal::from_int(0LL)}; return gd::make_color_from_args(_ca, 3); })(), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.980469), gd::GdVal::from_float(0.946239), gd::GdVal::from_float(0.582153)}; return gd::make_color_from_args(_ca, 3); })(), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.094223), gd::GdVal::from_float(0.964844), gd::GdVal::from_float(0.250663)}; return gd::make_color_from_args(_ca, 3); })()}));
        case SYM_GEN_offset_516: return gd::GdVal::from_int(40LL);
        case SYM_GEN_impulse_517: return gd::GdVal::from_int(50LL);
        case SYM_GEN_momentumFactor_518: return gd::GdVal::from_float(20.0);
        case SYM_GEN_affectedSoundsVolume_521: return ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 4); d->set(gd_ctx.arena, gd::GdVal::from_int(0LL), gd::gd_neg(gd::GdVal::from_int(8LL))); d->set(gd_ctx.arena, gd::GdVal::from_int(1LL), gd::gd_neg(gd::GdVal::from_int(1LL))); d->set(gd_ctx.arena, gd::GdVal::from_int(2LL), gd::gd_neg(gd::GdVal::from_int(1LL))); d->set(gd_ctx.arena, gd::GdVal::from_int(3LL), gd::gd_neg(gd::GdVal::from_int(1LL))); return gd::GdVal::from_dict(d); })();
        case SYM_GEN_cellSize_522: return gd::GdVal::from_vec2((gd::GdVal::from_int(80LL)).as_float(), (gd::GdVal::from_int(80LL)).as_float());
        case SYM_GEN_halfCellSize_523: return gd::gd_mul(gd::GdVal::from_float(0.5), Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_cellSize_522));
        case SYM_GEN_shadowOffset_shop_524: return gd::GdVal::from_vec2((gd::GdVal::from_int(5LL)).as_float(), (gd::GdVal::from_int(1LL)).as_float());
        case SYM_GEN_shadowOffset_dropped_525: return gd::GdVal::from_vec2((gd::GdVal::from_int(5LL)).as_float(), (gd::GdVal::from_int(5LL)).as_float());
        case SYM_GEN_shadowOffset_dragged_526: return gd::GdVal::from_vec2((gd::GdVal::from_int(15LL)).as_float(), (gd::GdVal::from_int(15LL)).as_float());
        case SYM_GEN_DRAG_PRIORITY_527: return gd::GdVal::from_int(2LL);
        case SYM_GEN_correction_583: return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_vec2(0.0, 0.0), gd::GdVal::from_vec2((gd::gd_neg(gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_cellSize_522), gd::SYM_x))).as_float(), (gd::GdVal::from_int(0LL)).as_float()), gd::GdVal::from_vec2((gd::gd_neg(gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_cellSize_522), gd::SYM_x))).as_float(), (gd::gd_neg(gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_cellSize_522), gd::SYM_y))).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::gd_neg(gd::get_prop(gd_ctx, Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_cellSize_522), gd::SYM_y))).as_float())}));
        case SYM_GEN_angleStep_585: return gd::GdVal::from_int(45LL);
        case SYM_GEN_moveRotationMouseFactor_588: return gd::GdVal::from_float(0.015);
        case SYM_GEN_backforce_589: return gd::GdVal::from_float(5.0);
        case SYM_GEN_fric_590: return gd::GdVal::from_float(15.0);
        case SYM_GEN_maxAngle_591: return gd::GdVal::from_int(10LL);
        case SYM_GEN_moveRotationSpeed_592: return gd::GdVal::from_float(60.0);
        case SYM_GEN_hoverableWhenMenuOpen_598: return ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 4); d->set(gd_ctx.arena, gd::GdVal::from_int(8LL), gd::GdVal::from_bool(true)); d->set(gd_ctx.arena, gd::GdVal::from_int(9LL), gd::GdVal::from_bool(true)); d->set(gd_ctx.arena, gd::GdVal::from_int(6LL), gd::GdVal::from_bool(true)); d->set(gd_ctx.arena, gd::GdVal::from_int(5LL), gd::GdVal::from_bool(true)); return gd::GdVal::from_dict(d); })();
        case SYM_GEN_MISS_OFFSET_602: return gd::GdVal::from_float(100.0);
        case SYM_GEN_PRE_FUSE_DUR_603: return gd::GdVal::from_float(1.0);
        case SYM_GEN_PRE_FUSE_DUR_COG_604: return gd::GdVal::from_float(0.2);
        case SYM_GEN_FUSE_DUR_605: return gd::GdVal::from_float(1.0);
        case SYM_GEN_TRANSFORMATION_DUR_606: return gd::GdVal::from_float(1.0);
        case SYM_GEN_labelOffsets_613: return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_vec2(0.0, 0.0), gd::GdVal::from_vec2((gd::GdVal::from_int(30LL)).as_float(), (gd::GdVal::from_int(30LL)).as_float()), gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(30LL))).as_float(), (gd::GdVal::from_int(30LL)).as_float()), gd::GdVal::from_vec2((gd::GdVal::from_int(30LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(30LL))).as_float()), gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(30LL))).as_float(), (gd::gd_neg(gd::GdVal::from_int(30LL))).as_float())}));
        case SYM_GEN_SignalConnection_877: return gd::GdVal::from_cls(&META_Gd__gd_core__Item__INNER__SignalConnection);
        default: break;
    }
    return Gd__gd_core__CoreItem::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__Item::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__Item::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_numStackChangeTypes_510: out = this->f_numStackChangeTypes; return true;
        case SYM_GEN_spriteScale_512: out = this->f_spriteScale; return true;
        case SYM_GEN_hasSquishySprite_513: out = this->f_hasSquishySprite; return true;
        case SYM_GEN_specificDragParticles_514: out = this->f_specificDragParticles; return true;
        case SYM_GEN_dragParticlesEnabled_515: out = this->f_dragParticlesEnabled; return true;
        case SYM_GEN_frictionTime_519: out = this->f_frictionTime; return true;
        case SYM_GEN_totalWeight_520: out = this->f_totalWeight; return true;
        case SYM_GEN_me_528: out = this->f_me; return true;
        case SYM_GEN_mouseIsOverItem_529: out = this->f_mouseIsOverItem; return true;
        case SYM_GEN_hovered_530: out = this->f_hovered; return true;
        case SYM_GEN_focus_531: out = this->f_focus; return true;
        case SYM_GEN_spotlight_532: out = this->f_spotlight; return true;
        case SYM_GEN_collisionShape_533: out = this->f_collisionShape; return true;
        case SYM_GEN_wasJustCrafted_534: out = this->f_wasJustCrafted; return true;
        case SYM_GEN_pickupPosition_535: out = this->f_pickupPosition; return true;
        case SYM_GEN_pickupRotation_536: out = this->f_pickupRotation; return true;
        case SYM_GEN_pickupTopLeftCell_537: out = this->f_pickupTopLeftCell; return true;
        case SYM_GEN_pickupFaceDirection_538: out = this->f_pickupFaceDirection; return true;
        case SYM_GEN_sameOrientationAsPickup_539: out = this->f_sameOrientationAsPickup; return true;
        case SYM_GEN_movebackTween_540: out = this->f_movebackTween; return true;
        case SYM_GEN_rotationTween_541: out = this->f_rotationTween; return true;
        case SYM_GEN_pickingEnabled_542: out = this->f_pickingEnabled; return true;
        case SYM_GEN_tooltipEnabled_543: out = this->f_tooltipEnabled; return true;
        case SYM_GEN_hoverResponseEnabled_544: out = this->f_hoverResponseEnabled; return true;
        case SYM_GEN_focusEnabled_545: out = this->f_focusEnabled; return true;
        case SYM_GEN_affectedCellsActive_546: out = this->f_affectedCellsActive; return true;
        case SYM_GEN_affordable_547: out = this->f_affordable; return true;
        case SYM_GEN_momentumStrength_548: out = this->f_momentumStrength; return true;
        case SYM_GEN_momentum_549: out = this->f_momentum; return true;
        case SYM_GEN_tooltip_550: out = this->f_tooltip; return true;
        case SYM_GEN_tooltipMargin_551: out = this->f_tooltipMargin; return true;
        case SYM_GEN_tooltipUpdateQueued_552: out = this->f_tooltipUpdateQueued; return true;
        case SYM_GEN_shadows_553: out = this->f_shadows; return true;
        case SYM_GEN_spritesWithShadows_554: out = this->f_spritesWithShadows; return true;
        case SYM_GEN_shadowOffset_555: out = this->f_shadowOffset; return true;
        case SYM_GEN_shadowTween_556: out = this->f_shadowTween; return true;
        case SYM_GEN_dropFrame_557: out = this->f_dropFrame; return true;
        case SYM_GEN_pickupFrame_558: out = this->f_pickupFrame; return true;
        case SYM_GEN_mouseWheelRotationReadyTime_559: out = this->f_mouseWheelRotationReadyTime; return true;
        case SYM_GEN_notEnoughGoldLabelReadyTime_560: out = this->f_notEnoughGoldLabelReadyTime; return true;
        case SYM_GEN_averagedPosition_561: out = this->f_averagedPosition; return true;
        case SYM_GEN_impactSoundVolume_562: out = this->f_impactSoundVolume; return true;
        case SYM_GEN_progressMaterial_563: out = this->f_progressMaterial; return true;
        case SYM_GEN_insideRotationNode_564: out = this->f_insideRotationNode; return true;
        case SYM_GEN_draggedInsideItems_565: out = this->f_draggedInsideItems; return true;
        case SYM_GEN_draggingParent_566: out = this->f_draggingParent; return true;
        case SYM_GEN_sold_567: out = this->f_sold; return true;
        case SYM_GEN_lastVelocity_568: out = this->f_lastVelocity; return true;
        case SYM_GEN_lastCollisionPos_569: out = this->f_lastCollisionPos; return true;
        case SYM_GEN_lastCollider_570: out = this->f_lastCollider; return true;
        case SYM_GEN_impactSoundReadyTime_571: out = this->f_impactSoundReadyTime; return true;
        case SYM_GEN_globalAffectVisuals_572: out = this->f_globalAffectVisuals; return true;
        case SYM_GEN_bondedBaseItem_573: out = this->f_bondedBaseItem; return true;
        case SYM_GEN_bondedIngredients_574: out = this->f_bondedIngredients; return true;
        case SYM_GEN_locked_575: out = this->f_locked; return true;
        case SYM_GEN_bound_576: out = this->f_bound; return true;
        case SYM_GEN_curRecipe_577: out = this->f_curRecipe; return true;
        case SYM_GEN_bondVisuals_578: out = this->f_bondVisuals; return true;
        case SYM_GEN_craftingLabel_579: out = this->f_craftingLabel; return true;
        case SYM_GEN_craftingAniReadyTime_580: out = this->f_craftingAniReadyTime; return true;
        case SYM_GEN_pooled_581: out = this->f_pooled; return true;
        case SYM_GEN_initialized_582: out = this->f_initialized; return true;
        case SYM_GEN_canAffectVisuals_584: out = this->f_canAffectVisuals; return true;
        case SYM_GEN_rotationMomentum_586: out = this->f_rotationMomentum; return true;
        case SYM_GEN_bonusRotation_587: out = this->f_bonusRotation; return true;
        case SYM_GEN_brightColor_593: out = this->f_brightColor; return true;
        case SYM_GEN_defaultColor_594: out = this->f_defaultColor; return true;
        case SYM_GEN_buildIntoRecipesTooltip_595: out = this->f_buildIntoRecipesTooltip; return true;
        case SYM_GEN_owningBuildIntoRecipesTooltip_596: out = this->f_owningBuildIntoRecipesTooltip; return true;
        case SYM_GEN_ownerTypesWithBuildTooltip_597: out = this->f_ownerTypesWithBuildTooltip; return true;
        case SYM_GEN_shaderTween_599: out = this->f_shaderTween; return true;
        case SYM_GEN_canCancelShaderTween_600: out = this->f_canCancelShaderTween; return true;
        case SYM_GEN_nonRotatedProgress_601: out = this->f_nonRotatedProgress; return true;
        case SYM_GEN_fusing_607: out = this->f_fusing; return true;
        case SYM_GEN_willBeConsumed_608: out = this->f_willBeConsumed; return true;
        case SYM_GEN_fuseParticles1_609: out = this->f_fuseParticles1; return true;
        case SYM_GEN_fuseParticles2_610: out = this->f_fuseParticles2; return true;
        case SYM_GEN_fuseTween_611: out = this->f_fuseTween; return true;
        case SYM_GEN_fusingBonds_612: out = this->f_fusingBonds; return true;
        case SYM_GEN_collisionMap_614: out = this->f_collisionMap; return true;
        case SYM_GEN_animation_615: out = this->f_animation; return true;
        case SYM_GEN_sprite_616: out = this->f_sprite; return true;
        case SYM_GEN_clickArea_617: out = this->f_clickArea; return true;
        case SYM_GEN_dragParticles_618: out = this->f_dragParticles; return true;
        case SYM_GEN_sockets_619: out = this->f_sockets; return true;
        case SYM_GEN_lock_620: out = this->f_lock; return true;
        case SYM_GEN_lockAnimation_621: out = this->f_lockAnimation; return true;
        case SYM_GEN_baseBounce_622: out = this->f_baseBounce; return true;
        case SYM_GEN_baseFriction_623: out = this->f_baseFriction; return true;
        case SYM_GEN_Owner_854: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Owner); return true;
        case SYM_GEN_Type_855: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Type); return true;
        case SYM_GEN_Priority_856: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Priority); return true;
        case SYM_GEN_CraftingPriority_857: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_CraftingPriority); return true;
        case SYM_GEN_Tag_858: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Tag); return true;
        case SYM_GEN_Stack_859: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Stack); return true;
        case SYM_GEN_Mat_860: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Mat); return true;
        case SYM_GEN_Physics_861: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Physics); return true;
        case SYM_GEN_Rarity_862: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Rarity); return true;
        case SYM_GEN_FaceDirection_863: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_FaceDirection); return true;
        case SYM_GEN_StatModified_864: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_StatModified); return true;
        case SYM_GEN_DropResult_865: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_DropResult); return true;
        case SYM_GEN_PickupType_866: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_PickupType); return true;
        case SYM_GEN_Affected_867: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Affected); return true;
        case SYM_GEN_Tiles_868: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Tiles); return true;
        case SYM_GEN_ActivationAni_869: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_ActivationAni); return true;
        case SYM_GEN_Stat_870: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_Stat); return true;
        case SYM_GEN_StackChangeType_871: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__Item_StackChangeType); return true;
        case SYM_GEN_SignalConnection_877: out = gd::GdVal::from_cls(&META_Gd__gd_core__Item__INNER__SignalConnection); return true;
        case SYM_GEN_affectedColorToTileId_509: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_rarityColors_511: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_offset_516: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_impulse_517: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_momentumFactor_518: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_affectedSoundsVolume_521: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_cellSize_522: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_halfCellSize_523: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_shadowOffset_shop_524: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_shadowOffset_dropped_525: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_shadowOffset_dragged_526: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_DRAG_PRIORITY_527: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_correction_583: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_angleStep_585: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_moveRotationMouseFactor_588: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_backforce_589: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_fric_590: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_maxAngle_591: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_moveRotationSpeed_592: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_hoverableWhenMenuOpen_598: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_MISS_OFFSET_602: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_PRE_FUSE_DUR_603: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_PRE_FUSE_DUR_COG_604: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_FUSE_DUR_605: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_TRANSFORMATION_DUR_606: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        case SYM_GEN_labelOffsets_613: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core__CoreItem::get_prop(prop, out);
}
bool Gd__gd_core__Item::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_numStackChangeTypes_510: this->f_numStackChangeTypes = val; return true;
        case SYM_GEN_spriteScale_512: this->f_spriteScale = val; return true;
        case SYM_GEN_hasSquishySprite_513: this->f_hasSquishySprite = val; return true;
        case SYM_GEN_specificDragParticles_514: this->f_specificDragParticles = val; return true;
        case SYM_GEN_dragParticlesEnabled_515: this->f_dragParticlesEnabled = val; return true;
        case SYM_GEN_frictionTime_519: this->f_frictionTime = val; return true;
        case SYM_GEN_totalWeight_520: this->f_totalWeight = gd::gd_coerce_float(val); return true;
        case SYM_GEN_me_528: this->f_me = val; return true;
        case SYM_GEN_mouseIsOverItem_529: this->f_mouseIsOverItem = val; return true;
        case SYM_GEN_hovered_530: this->f_hovered = val; return true;
        case SYM_GEN_focus_531: this->f_focus = val; return true;
        case SYM_GEN_spotlight_532: this->f_spotlight = val; return true;
        case SYM_GEN_collisionShape_533: this->f_collisionShape = val; return true;
        case SYM_GEN_wasJustCrafted_534: this->f_wasJustCrafted = val; return true;
        case SYM_GEN_pickupPosition_535: this->f_pickupPosition = val; return true;
        case SYM_GEN_pickupRotation_536: this->f_pickupRotation = gd::gd_coerce_float(val); return true;
        case SYM_GEN_pickupTopLeftCell_537: this->f_pickupTopLeftCell = val; return true;
        case SYM_GEN_pickupFaceDirection_538: this->f_pickupFaceDirection = gd::gd_coerce_int(val); return true;
        case SYM_GEN_sameOrientationAsPickup_539: this->f_sameOrientationAsPickup = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_movebackTween_540: this->f_movebackTween = val; return true;
        case SYM_GEN_rotationTween_541: this->f_rotationTween = val; return true;
        case SYM_GEN_pickingEnabled_542: this->f_pickingEnabled = val; return true;
        case SYM_GEN_tooltipEnabled_543: this->f_tooltipEnabled = val; return true;
        case SYM_GEN_hoverResponseEnabled_544: this->f_hoverResponseEnabled = val; return true;
        case SYM_GEN_focusEnabled_545: this->f_focusEnabled = val; return true;
        case SYM_GEN_affectedCellsActive_546: this->f_affectedCellsActive = val; return true;
        case SYM_GEN_affordable_547: this->f_affordable = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_momentumStrength_548: this->f_momentumStrength = gd::gd_coerce_float(val); return true;
        case SYM_GEN_momentum_549: this->f_momentum = val; return true;
        case SYM_GEN_tooltip_550: this->f_tooltip = val; return true;
        case SYM_GEN_tooltipMargin_551: this->f_tooltipMargin = val; return true;
        case SYM_GEN_tooltipUpdateQueued_552: this->f_tooltipUpdateQueued = val; return true;
        case SYM_GEN_shadows_553: this->f_shadows = val; return true;
        case SYM_GEN_spritesWithShadows_554: this->f_spritesWithShadows = val; return true;
        case SYM_GEN_shadowOffset_555: this->f_shadowOffset = val; return true;
        case SYM_GEN_shadowTween_556: this->f_shadowTween = val; return true;
        case SYM_GEN_dropFrame_557: this->f_dropFrame = gd::gd_coerce_int(val); return true;
        case SYM_GEN_pickupFrame_558: this->f_pickupFrame = gd::gd_coerce_int(val); return true;
        case SYM_GEN_mouseWheelRotationReadyTime_559: this->f_mouseWheelRotationReadyTime = gd::gd_coerce_float(val); return true;
        case SYM_GEN_notEnoughGoldLabelReadyTime_560: this->f_notEnoughGoldLabelReadyTime = gd::gd_coerce_float(val); return true;
        case SYM_GEN_averagedPosition_561: this->f_averagedPosition = val; return true;
        case SYM_GEN_impactSoundVolume_562: this->f_impactSoundVolume = gd::gd_coerce_float(val); return true;
        case SYM_GEN_progressMaterial_563: this->f_progressMaterial = val; return true;
        case SYM_GEN_insideRotationNode_564: this->f_insideRotationNode = val; return true;
        case SYM_GEN_draggedInsideItems_565: this->f_draggedInsideItems = val; return true;
        case SYM_GEN_draggingParent_566: this->f_draggingParent = val; return true;
        case SYM_GEN_sold_567: this->f_sold = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_lastVelocity_568: this->f_lastVelocity = val; return true;
        case SYM_GEN_lastCollisionPos_569: this->f_lastCollisionPos = val; return true;
        case SYM_GEN_lastCollider_570: this->f_lastCollider = val; return true;
        case SYM_GEN_impactSoundReadyTime_571: this->f_impactSoundReadyTime = val; return true;
        case SYM_GEN_globalAffectVisuals_572: this->f_globalAffectVisuals = val; return true;
        case SYM_GEN_bondedBaseItem_573: this->f_bondedBaseItem = val; return true;
        case SYM_GEN_bondedIngredients_574: this->f_bondedIngredients = val; return true;
        case SYM_GEN_locked_575: this->f_locked = val; return true;
        case SYM_GEN_bound_576: this->f_bound = val; return true;
        case SYM_GEN_curRecipe_577: this->f_curRecipe = val; return true;
        case SYM_GEN_bondVisuals_578: this->f_bondVisuals = val; return true;
        case SYM_GEN_craftingLabel_579: this->f_craftingLabel = val; return true;
        case SYM_GEN_craftingAniReadyTime_580: this->f_craftingAniReadyTime = gd::gd_coerce_float(val); return true;
        case SYM_GEN_pooled_581: this->f_pooled = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_initialized_582: this->f_initialized = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_canAffectVisuals_584: this->f_canAffectVisuals = val; return true;
        case SYM_GEN_rotationMomentum_586: this->f_rotationMomentum = val; return true;
        case SYM_GEN_bonusRotation_587: this->f_bonusRotation = val; return true;
        case SYM_GEN_brightColor_593: this->f_brightColor = val; return true;
        case SYM_GEN_defaultColor_594: this->f_defaultColor = val; return true;
        case SYM_GEN_buildIntoRecipesTooltip_595: this->f_buildIntoRecipesTooltip = val; return true;
        case SYM_GEN_owningBuildIntoRecipesTooltip_596: this->f_owningBuildIntoRecipesTooltip = val; return true;
        case SYM_GEN_ownerTypesWithBuildTooltip_597: this->f_ownerTypesWithBuildTooltip = val; return true;
        case SYM_GEN_shaderTween_599: this->f_shaderTween = val; return true;
        case SYM_GEN_canCancelShaderTween_600: this->f_canCancelShaderTween = val; return true;
        case SYM_GEN_nonRotatedProgress_601: this->f_nonRotatedProgress = val; return true;
        case SYM_GEN_fusing_607: this->f_fusing = val; return true;
        case SYM_GEN_willBeConsumed_608: this->f_willBeConsumed = val; return true;
        case SYM_GEN_fuseParticles1_609: this->f_fuseParticles1 = val; return true;
        case SYM_GEN_fuseParticles2_610: this->f_fuseParticles2 = val; return true;
        case SYM_GEN_fuseTween_611: this->f_fuseTween = val; return true;
        case SYM_GEN_fusingBonds_612: this->f_fusingBonds = val; return true;
        case SYM_GEN_collisionMap_614: this->f_collisionMap = val; return true;
        case SYM_GEN_animation_615: this->f_animation = val; return true;
        case SYM_GEN_sprite_616: this->f_sprite = val; return true;
        case SYM_GEN_clickArea_617: this->f_clickArea = val; return true;
        case SYM_GEN_dragParticles_618: this->f_dragParticles = val; return true;
        case SYM_GEN_sockets_619: this->f_sockets = val; return true;
        case SYM_GEN_lock_620: this->f_lock = val; return true;
        case SYM_GEN_lockAnimation_621: this->f_lockAnimation = val; return true;
        case SYM_GEN_baseBounce_622: this->f_baseBounce = gd::gd_coerce_float(val); return true;
        case SYM_GEN_baseFriction_623: this->f_baseFriction = gd::gd_coerce_float(val); return true;
        default: break;
    }
    return Gd__gd_core__CoreItem::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Item::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN__readyInit_140: return true;
        case SYM_GEN_preset_626: return true;
        case SYM_GEN_initPhysicsMaterial_627: return true;
        case SYM_GEN_getShadowOffset_628: return true;
        case SYM_GEN_initRecipeBook_629: return true;
        case SYM_GEN_initItemLibrary_630: return true;
        case SYM_GEN_setSpotlight_631: return true;
        case SYM_GEN_initTitle_632: return true;
        case SYM_GEN_initTooltip_633: return true;
        case SYM_GEN_initBuildViewer_634: return true;
        case SYM_GEN_initBuildViewerIcon_635: return true;
        case SYM_GEN_initInfoPanelIcon_636: return true;
        case SYM_GEN_initGridStorageIcon_637: return true;
        case SYM_GEN_getData_638: return true;
        case SYM_GEN_setData_639: return true;
        case SYM_GEN_persistDataInShop_640: return true;
        case SYM_GEN_getTranslatedName_641: return true;
        case SYM_GEN_getDescription_642: return true;
        case SYM_GEN_insertParameters_643: return true;
        case SYM_GEN_insertParameter_644: return true;
        case SYM_GEN_getModeDescription_645: return true;
        case SYM_GEN_getFlavorText_646: return true;
        case SYM_GEN_disablePicking_647: return true;
        case SYM_GEN_enablePicking_648: return true;
        case SYM_GEN_enableTooltip_649: return true;
        case SYM_GEN_disableTooltip_650: return true;
        case SYM_GEN_disableFocus_651: return true;
        case SYM_GEN_enableFocus_652: return true;
        case SYM_GEN_setEditMode_653: return true;
        case SYM_GEN_setShadowAlpha_654: return true;
        case SYM_GEN_getTopLeftGlobal_655: return true;
        case SYM_GEN_getBottomRightGlobal_656: return true;
        case SYM_GEN_getBottomCenter_657: return true;
        case SYM_GEN_getInventory_658: return true;
        case SYM_GEN_removeFromInventory_662: return true;
        case SYM_GEN_playAffectedPlacedAnimation_663: return true;
        case SYM_GEN_clearCanAffectVisuals_664: return true;
        case SYM_GEN_liesInStorage_665: return true;
        case SYM_GEN_pushToStorage_666: return true;
        case SYM_GEN_addToStorageBox_667: return true;
        case SYM_GEN_removeFromStorage_668: return true;
        case SYM_GEN_onStorageLeft_669: return true;
        case SYM_GEN_isInGridStorage_670: return true;
        case SYM_GEN_getGridStorageProxy_671: return true;
        case SYM_GEN_onAddedToGridStorage_672: return true;
        case SYM_GEN_onRemovedFromGridStorage_673: return true;
        case SYM_GEN_makeGrabbable_674: return true;
        case SYM_GEN_moveToFreeSpaceInStorage_675: return true;
        case SYM_GEN_checkIfOutofStorageBounds_676: return true;
        case SYM_GEN_checkIfOutofStorageBounds2_677: return true;
        case SYM_GEN_checkIfOutofStorageBounds3_678: return true;
        case SYM_GEN_findFreeSpace_679: return true;
        case SYM_GEN_unclip_680: return true;
        case SYM_GEN_onAddedToStorageBox_681: return true;
        case SYM_GEN__process_682: return true;
        case SYM_GEN__integrate_forces_683: return true;
        case SYM_GEN_updateShadow_684: return true;
        case SYM_GEN_lerpAngle_local_685: return true;
        case SYM_GEN_updateInsideRotationNode_686: return true;
        case SYM_GEN_spawnRotationSparks_687: return true;
        case SYM_GEN_highlight_688: return true;
        case SYM_GEN_unhighlight_689: return true;
        case SYM_GEN_setBright_690: return true;
        case SYM_GEN_resetBright_691: return true;
        case SYM_GEN_getHoverPriority_692: return true;
        case SYM_GEN_canGainFocus_693: return true;
        case SYM_GEN_gainFocus_694: return true;
        case SYM_GEN_respondToHover_695: return true;
        case SYM_GEN_canShowBuildIntoRecipesTooltip_696: return true;
        case SYM_GEN_canShowSubBuildIntoRecipesTooltip_697: return true;
        case SYM_GEN_showBuildIntoRecipesTooltip_698: return true;
        case SYM_GEN_getRelatedItemColumns_699: return true;
        case SYM_GEN_getRelatedItemHeight_700: return true;
        case SYM_GEN_getRecipeDescriptor_701: return true;
        case SYM_GEN_hideBuildIntoRecipesTooltip_702: return true;
        case SYM_GEN_loseFocus_703: return true;
        case SYM_GEN_respondToHoverEnd_704: return true;
        case SYM_GEN_activateDragParticles_705: return true;
        case SYM_GEN_deactivateDragParticles_706: return true;
        case SYM_GEN_updateTooltip_707: return true;
        case SYM_GEN_queueTooltipUpdate_708: return true;
        case SYM_GEN_clearTooltip_709: return true;
        case SYM_GEN_mouseEntered_710: return true;
        case SYM_GEN_hover_711: return true;
        case SYM_GEN_mouseExited_712: return true;
        case SYM_GEN_hoverEnd_713: return true;
        case SYM_GEN_isHovered_714: return true;
        case SYM_GEN_getScaleProp_715: return true;
        case SYM_GEN_setSpriteScale_716: return true;
        case SYM_GEN_pickup_717: return true;
        case SYM_GEN_onDraggedWithParentStart_718: return true;
        case SYM_GEN_finishMoveback_719: return true;
        case SYM_GEN_onDraggedWithParentEnd_720: return true;
        case SYM_GEN_canSnap_721: return true;
        case SYM_GEN_reactToDropResult_722: return true;
        case SYM_GEN_drop_723: return true;
        case SYM_GEN_showClickArea_724: return true;
        case SYM_GEN_cancelDrag_725: return true;
        case SYM_GEN_emptyTweenCallback_726: return true;
        case SYM_GEN_killMovebackTween_727: return true;
        case SYM_GEN_setSpriteGlobalPos_728: return true;
        case SYM_GEN_dropIntoInventory_729: return true;
        case SYM_GEN_finishInsideItemsRotation_730: return true;
        case SYM_GEN_pushDraggedItemsToStorage_731: return true;
        case SYM_GEN_reparentItemsInside_732: return true;
        case SYM_GEN_clearDraggedInsideItems_733: return true;
        case SYM_GEN_showSockets_734: return true;
        case SYM_GEN_hideSockets_735: return true;
        case SYM_GEN_playPickupSound_736: return true;
        case SYM_GEN_playDropSound_149: return true;
        case SYM_GEN_canBeSold_737: return true;
        case SYM_GEN_isPickingPossible_738: return true;
        case SYM_GEN_canBePicked_739: return true;
        case SYM_GEN_canBeDraggedWithBag_740: return true;
        case SYM_GEN_canBeDropped_741: return true;
        case SYM_GEN__input_742: return true;
        case SYM_GEN_resetSprite_743: return true;
        case SYM_GEN_combatToShop_744: return true;
        case SYM_GEN_shopEntered_745: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_startFusing_inShop_747: return true;
        case SYM_GEN_getCraftingPriority_748: return true;
        case SYM_GEN_addToCraftingQueue_749: return true;
        case SYM_GEN_combatToTitle_750: return true;
        case SYM_GEN_readyToFuse_751: return true;
        case SYM_GEN_startFusing_752: return true;
        case SYM_GEN_readyToTransform_753: return true;
        case SYM_GEN_giveGold_754: return true;
        case SYM_GEN_getTranslatedTypeName_755: return true;
        case SYM_GEN_getTypeDescription_756: return true;
        case SYM_GEN_getTranslatedRarity_757: return true;
        case SYM_GEN_logCooldown_759: return true;
        case SYM_GEN_getCombatDisplayAccuracy_760: return true;
        case SYM_GEN_getDisplayCritChance_761: return true;
        case SYM_GEN_getSalesMultiplier_762: return true;
        case SYM_GEN_prepareDiscard_763: return true;
        case SYM_GEN_discard_764: return true;
        case SYM_GEN_popIn_765: return true;
        case SYM_GEN_disappear_766: return true;
        case SYM_GEN_appearInLibrary_767: return true;
        case SYM_GEN_createParticles_768: return true;
        case SYM_GEN_deactivateParticles_769: return true;
        case SYM_GEN_makeRigidBody_770: return true;
        case SYM_GEN_dropImpulse_771: return true;
        case SYM_GEN_makeNonRigidBody_772: return true;
        case SYM_GEN_rollShopChance_773: return true;
        case SYM_GEN__physics_process_774: return true;
        case SYM_GEN_playActivationAnimation_Scale_775: return true;
        case SYM_GEN_playActivationAnimation_Jump_776: return true;
        case SYM_GEN_playActivationAnimation_JumpSquash_777: return true;
        case SYM_GEN_playActivationAnimation_778: return true;
        case SYM_GEN_playActivationSound_148: return true;
        case SYM_GEN_clearSpriteMaterial_779: return true;
        case SYM_GEN_giveProgressMaterial_780: return true;
        case SYM_GEN_getTextureSize_781: return true;
        case SYM_GEN_scaleToFit_782: return true;
        case SYM_GEN_getSpriteOffset_783: return true;
        case SYM_GEN_getGlobalCenter_784: return true;
        case SYM_GEN_getTextureSize_local_785: return true;
        case SYM_GEN_scaleToFit_local_786: return true;
        case SYM_GEN_getSpriteOffset_local_787: return true;
        case SYM_GEN_setTexture_788: return true;
        case SYM_GEN_updateShadowTexture_789: return true;
        case SYM_GEN_initSpriteMaterial_790: return true;
        case SYM_GEN_updateShaderRotation_791: return true;
        case SYM_GEN_allowCancelShaderTween_792: return true;
        case SYM_GEN_showCooldownSmooth_793: return true;
        case SYM_GEN_showCooldown_794: return true;
        case SYM_GEN_createAnimation_795: return true;
        case SYM_GEN_playAnimation_796: return true;
        case SYM_GEN_hasInventoryDuration_797: return true;
        case SYM_GEN_reveal_798: return true;
        case SYM_GEN_setRevealed_799: return true;
        case SYM_GEN_isCrafted_800: return true;
        case SYM_GEN_isMovingBack_801: return true;
        case SYM_GEN__notification_802: return true;
        case SYM_GEN_getAllInInventoryOfType_803: return true;
        case SYM_GEN_countAllInInventoryOfType_804: return true;
        case SYM_GEN_isTypeInInventory_805: return true;
        case SYM_GEN_isRecipeFinished_806: return true;
        case SYM_GEN_canStartNewRecipe_807: return true;
        case SYM_GEN_getRecipes_808: return true;
        case SYM_GEN_breakBondVisual_809: return true;
        case SYM_GEN_removeBondedBaseItem_810: return true;
        case SYM_GEN_removeBondedIngredient_811: return true;
        case SYM_GEN_removeAllIngredients_812: return true;
        case SYM_GEN_considerAsBond_813: return true;
        case SYM_GEN_addBondedIngredient_814: return true;
        case SYM_GEN_addToBaseItem_815: return true;
        case SYM_GEN_playBondAnimation_816: return true;
        case SYM_GEN_playBondFailedAnimation_817: return true;
        case SYM_GEN_isCatalystBond_818: return true;
        case SYM_GEN_isLocked_819: return true;
        case SYM_GEN_canLockBag_820: return true;
        case SYM_GEN_canBeLocked_821: return true;
        case SYM_GEN_setLocked_822: return true;
        case SYM_GEN_unlockCombining_823: return true;
        case SYM_GEN_lockCombining_824: return true;
        case SYM_GEN_showLockLabel_825: return true;
        case SYM_GEN_getLockPosition_826: return true;
        case SYM_GEN_setBoundAsIngredient_827: return true;
        case SYM_GEN_canPreviewFusions_828: return true;
        case SYM_GEN_getCraftingPreviewPosition_829: return true;
        case SYM_GEN_previewFusions_830: return true;
        case SYM_GEN_previewRecipeIngredients_831: return true;
        case SYM_GEN_previewFusionToItem_832: return true;
        case SYM_GEN_hasShopItemCraftCandidates_833: return true;
        case SYM_GEN_typeInIngredients_834: return true;
        case SYM_GEN_getTextEffect_835: return true;
        case SYM_GEN_getFusionItemName_836: return true;
        case SYM_GEN_showProgressLabel_837: return true;
        case SYM_GEN_onCraftingLabelReturned_838: return true;
        case SYM_GEN_createBondVisual_839: return true;
        case SYM_GEN_updateBondVisuals_840: return true;
        case SYM_GEN_fuse_841: return true;
        case SYM_GEN_onFusingAsIngredient_842: return true;
        case SYM_GEN_onFusingAsCatalystFinished_843: return true;
        case SYM_GEN_createCraftedShockwave_844: return true;
        case SYM_GEN_finishFusing_845: return true;
        case SYM_GEN_allowGeneratingFusionItem_846: return true;
        case SYM_GEN_catalystFusingFinished_847: return true;
        case SYM_GEN_onFusingFinished_848: return true;
        case SYM_GEN_onCraftedFrom_849: return true;
        case SYM_GEN_getCraftingOffset_850: return true;
        case SYM_GEN_playCraftedAnimation_851: return true;
        case SYM_GEN_onRestoreSnapshot_852: return true;
        case SYM_GEN_getShopPriority_853: return true;
        default: break;
    }
    return Gd__gd_core__CoreItem::has_own_method(m);
}
bool Gd__gd_core__Item::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        case SYM_GEN_getNumTooltipStats_624: out = sf_getNumTooltipStats(gd_ctx, args, argc); return true;
        case SYM_GEN_getNumStackChangeTypes_625: out = sf_getNumStackChangeTypes(gd_ctx, args, argc); return true;
        case SYM_GEN_preset_626: out = fn_preset(args, argc); return true;
        case SYM_GEN_initPhysicsMaterial_627: out = fn_initPhysicsMaterial(args, argc); return true;
        case SYM_GEN_getShadowOffset_628: out = fn_getShadowOffset(args, argc); return true;
        case SYM_GEN_initRecipeBook_629: out = fn_initRecipeBook(args, argc); return true;
        case SYM_GEN_initItemLibrary_630: out = fn_initItemLibrary(args, argc); return true;
        case SYM_GEN_setSpotlight_631: out = fn_setSpotlight(args, argc); return true;
        case SYM_GEN_initTitle_632: out = fn_initTitle(args, argc); return true;
        case SYM_GEN_initTooltip_633: out = fn_initTooltip(args, argc); return true;
        case SYM_GEN_initBuildViewer_634: out = fn_initBuildViewer(args, argc); return true;
        case SYM_GEN_initBuildViewerIcon_635: out = fn_initBuildViewerIcon(args, argc); return true;
        case SYM_GEN_initInfoPanelIcon_636: out = fn_initInfoPanelIcon(args, argc); return true;
        case SYM_GEN_initGridStorageIcon_637: out = fn_initGridStorageIcon(args, argc); return true;
        case SYM_GEN_getData_638: out = fn_getData(args, argc); return true;
        case SYM_GEN_setData_639: out = fn_setData(args, argc); return true;
        case SYM_GEN_persistDataInShop_640: out = fn_persistDataInShop(args, argc); return true;
        case SYM_GEN_getTranslatedName_641: out = fn_getTranslatedName(args, argc); return true;
        case SYM_GEN_getDescription_642: out = fn_getDescription(args, argc); return true;
        case SYM_GEN_insertParameters_643: out = fn_insertParameters(args, argc); return true;
        case SYM_GEN_insertParameter_644: out = fn_insertParameter(args, argc); return true;
        case SYM_GEN_getModeDescription_645: out = fn_getModeDescription(args, argc); return true;
        case SYM_GEN_getFlavorText_646: out = fn_getFlavorText(args, argc); return true;
        case SYM_GEN_disablePicking_647: out = fn_disablePicking(args, argc); return true;
        case SYM_GEN_enablePicking_648: out = fn_enablePicking(args, argc); return true;
        case SYM_GEN_enableTooltip_649: out = fn_enableTooltip(args, argc); return true;
        case SYM_GEN_disableTooltip_650: out = fn_disableTooltip(args, argc); return true;
        case SYM_GEN_disableFocus_651: out = fn_disableFocus(args, argc); return true;
        case SYM_GEN_enableFocus_652: out = fn_enableFocus(args, argc); return true;
        case SYM_GEN_setEditMode_653: out = fn_setEditMode(args, argc); return true;
        case SYM_GEN_setShadowAlpha_654: out = fn_setShadowAlpha(args, argc); return true;
        case SYM_GEN_getTopLeftGlobal_655: out = fn_getTopLeftGlobal(args, argc); return true;
        case SYM_GEN_getBottomRightGlobal_656: out = fn_getBottomRightGlobal(args, argc); return true;
        case SYM_GEN_getBottomCenter_657: out = fn_getBottomCenter(args, argc); return true;
        case SYM_GEN_getInventory_658: out = fn_getInventory(args, argc); return true;
        case SYM_GEN_wasAddedToInventory_659: out = sf_wasAddedToInventory(gd_ctx, args, argc); return true;
        case SYM_GEN_wasBought_660: out = sf_wasBought(gd_ctx, args, argc); return true;
        case SYM_GEN_wasHotSwap_661: out = sf_wasHotSwap(gd_ctx, args, argc); return true;
        case SYM_GEN_removeFromInventory_662: out = fn_removeFromInventory(args, argc); return true;
        case SYM_GEN_playAffectedPlacedAnimation_663: out = fn_playAffectedPlacedAnimation(args, argc); return true;
        case SYM_GEN_clearCanAffectVisuals_664: out = fn_clearCanAffectVisuals(args, argc); return true;
        case SYM_GEN_liesInStorage_665: out = fn_liesInStorage(args, argc); return true;
        case SYM_GEN_pushToStorage_666: out = fn_pushToStorage(args, argc); return true;
        case SYM_GEN_addToStorageBox_667: out = fn_addToStorageBox(args, argc); return true;
        case SYM_GEN_removeFromStorage_668: out = fn_removeFromStorage(args, argc); return true;
        case SYM_GEN_onStorageLeft_669: out = fn_onStorageLeft(args, argc); return true;
        case SYM_GEN_isInGridStorage_670: out = fn_isInGridStorage(args, argc); return true;
        case SYM_GEN_getGridStorageProxy_671: out = fn_getGridStorageProxy(args, argc); return true;
        case SYM_GEN_onAddedToGridStorage_672: out = fn_onAddedToGridStorage(args, argc); return true;
        case SYM_GEN_onRemovedFromGridStorage_673: out = fn_onRemovedFromGridStorage(args, argc); return true;
        case SYM_GEN_makeGrabbable_674: out = fn_makeGrabbable(args, argc); return true;
        case SYM_GEN_moveToFreeSpaceInStorage_675: out = fn_moveToFreeSpaceInStorage(args, argc); return true;
        case SYM_GEN_checkIfOutofStorageBounds_676: out = fn_checkIfOutofStorageBounds(args, argc); return true;
        case SYM_GEN_checkIfOutofStorageBounds2_677: out = fn_checkIfOutofStorageBounds2(args, argc); return true;
        case SYM_GEN_checkIfOutofStorageBounds3_678: out = fn_checkIfOutofStorageBounds3(args, argc); return true;
        case SYM_GEN_findFreeSpace_679: out = fn_findFreeSpace(args, argc); return true;
        case SYM_GEN_unclip_680: out = fn_unclip(args, argc); return true;
        case SYM_GEN_onAddedToStorageBox_681: out = fn_onAddedToStorageBox(args, argc); return true;
        case SYM_GEN__process_682: out = fn__process(args, argc); return true;
        case SYM_GEN__integrate_forces_683: out = fn__integrate_forces(args, argc); return true;
        case SYM_GEN_updateShadow_684: out = fn_updateShadow(args, argc); return true;
        case SYM_GEN_lerpAngle_local_685: out = fn_lerpAngle_local(args, argc); return true;
        case SYM_GEN_updateInsideRotationNode_686: out = fn_updateInsideRotationNode(args, argc); return true;
        case SYM_GEN_spawnRotationSparks_687: out = fn_spawnRotationSparks(args, argc); return true;
        case SYM_GEN_highlight_688: out = fn_highlight(args, argc); return true;
        case SYM_GEN_unhighlight_689: out = fn_unhighlight(args, argc); return true;
        case SYM_GEN_setBright_690: out = fn_setBright(args, argc); return true;
        case SYM_GEN_resetBright_691: out = fn_resetBright(args, argc); return true;
        case SYM_GEN_getHoverPriority_692: out = fn_getHoverPriority(args, argc); return true;
        case SYM_GEN_canGainFocus_693: out = fn_canGainFocus(args, argc); return true;
        case SYM_GEN_gainFocus_694: out = fn_gainFocus(args, argc); return true;
        case SYM_GEN_respondToHover_695: out = fn_respondToHover(args, argc); return true;
        case SYM_GEN_canShowBuildIntoRecipesTooltip_696: out = fn_canShowBuildIntoRecipesTooltip(args, argc); return true;
        case SYM_GEN_canShowSubBuildIntoRecipesTooltip_697: out = fn_canShowSubBuildIntoRecipesTooltip(args, argc); return true;
        case SYM_GEN_showBuildIntoRecipesTooltip_698: out = fn_showBuildIntoRecipesTooltip(args, argc); return true;
        case SYM_GEN_getRelatedItemColumns_699: out = fn_getRelatedItemColumns(args, argc); return true;
        case SYM_GEN_getRelatedItemHeight_700: out = fn_getRelatedItemHeight(args, argc); return true;
        case SYM_GEN_getRecipeDescriptor_701: out = fn_getRecipeDescriptor(args, argc); return true;
        case SYM_GEN_hideBuildIntoRecipesTooltip_702: out = fn_hideBuildIntoRecipesTooltip(args, argc); return true;
        case SYM_GEN_loseFocus_703: out = fn_loseFocus(args, argc); return true;
        case SYM_GEN_respondToHoverEnd_704: out = fn_respondToHoverEnd(args, argc); return true;
        case SYM_GEN_activateDragParticles_705: out = fn_activateDragParticles(args, argc); return true;
        case SYM_GEN_deactivateDragParticles_706: out = fn_deactivateDragParticles(args, argc); return true;
        case SYM_GEN_updateTooltip_707: out = fn_updateTooltip(args, argc); return true;
        case SYM_GEN_queueTooltipUpdate_708: out = fn_queueTooltipUpdate(args, argc); return true;
        case SYM_GEN_clearTooltip_709: out = fn_clearTooltip(args, argc); return true;
        case SYM_GEN_mouseEntered_710: out = fn_mouseEntered(args, argc); return true;
        case SYM_GEN_hover_711: out = fn_hover(args, argc); return true;
        case SYM_GEN_mouseExited_712: out = fn_mouseExited(args, argc); return true;
        case SYM_GEN_hoverEnd_713: out = fn_hoverEnd(args, argc); return true;
        case SYM_GEN_isHovered_714: out = fn_isHovered(args, argc); return true;
        case SYM_GEN_getScaleProp_715: out = fn_getScaleProp(args, argc); return true;
        case SYM_GEN_setSpriteScale_716: out = fn_setSpriteScale(args, argc); return true;
        case SYM_GEN_pickup_717: out = fn_pickup(args, argc); return true;
        case SYM_GEN_onDraggedWithParentStart_718: out = fn_onDraggedWithParentStart(args, argc); return true;
        case SYM_GEN_finishMoveback_719: out = fn_finishMoveback(args, argc); return true;
        case SYM_GEN_onDraggedWithParentEnd_720: out = fn_onDraggedWithParentEnd(args, argc); return true;
        case SYM_GEN_canSnap_721: out = fn_canSnap(args, argc); return true;
        case SYM_GEN_reactToDropResult_722: out = fn_reactToDropResult(args, argc); return true;
        case SYM_GEN_drop_723: out = fn_drop(args, argc); return true;
        case SYM_GEN_showClickArea_724: out = fn_showClickArea(args, argc); return true;
        case SYM_GEN_cancelDrag_725: out = fn_cancelDrag(args, argc); return true;
        case SYM_GEN_emptyTweenCallback_726: out = fn_emptyTweenCallback(args, argc); return true;
        case SYM_GEN_killMovebackTween_727: out = fn_killMovebackTween(args, argc); return true;
        case SYM_GEN_setSpriteGlobalPos_728: out = fn_setSpriteGlobalPos(args, argc); return true;
        case SYM_GEN_dropIntoInventory_729: out = fn_dropIntoInventory(args, argc); return true;
        case SYM_GEN_finishInsideItemsRotation_730: out = fn_finishInsideItemsRotation(args, argc); return true;
        case SYM_GEN_pushDraggedItemsToStorage_731: out = fn_pushDraggedItemsToStorage(args, argc); return true;
        case SYM_GEN_reparentItemsInside_732: out = fn_reparentItemsInside(args, argc); return true;
        case SYM_GEN_clearDraggedInsideItems_733: out = fn_clearDraggedInsideItems(args, argc); return true;
        case SYM_GEN_showSockets_734: out = fn_showSockets(args, argc); return true;
        case SYM_GEN_hideSockets_735: out = fn_hideSockets(args, argc); return true;
        case SYM_GEN_playPickupSound_736: out = fn_playPickupSound(args, argc); return true;
        case SYM_GEN_playDropSound_149: out = fn_playDropSound(args, argc); return true;
        case SYM_GEN_canBeSold_737: out = fn_canBeSold(args, argc); return true;
        case SYM_GEN_isPickingPossible_738: out = fn_isPickingPossible(args, argc); return true;
        case SYM_GEN_canBePicked_739: out = fn_canBePicked(args, argc); return true;
        case SYM_GEN_canBeDraggedWithBag_740: out = fn_canBeDraggedWithBag(args, argc); return true;
        case SYM_GEN_canBeDropped_741: out = fn_canBeDropped(args, argc); return true;
        case SYM_GEN__input_742: out = fn__input(args, argc); return true;
        case SYM_GEN_resetSprite_743: out = fn_resetSprite(args, argc); return true;
        case SYM_GEN_combatToShop_744: out = fn_combatToShop(args, argc); return true;
        case SYM_GEN_shopEntered_745: out = fn_shopEntered(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_startFusing_inShop_747: out = fn_startFusing_inShop(args, argc); return true;
        case SYM_GEN_getCraftingPriority_748: out = fn_getCraftingPriority(args, argc); return true;
        case SYM_GEN_addToCraftingQueue_749: out = fn_addToCraftingQueue(args, argc); return true;
        case SYM_GEN_combatToTitle_750: out = fn_combatToTitle(args, argc); return true;
        case SYM_GEN_readyToFuse_751: out = fn_readyToFuse(args, argc); return true;
        case SYM_GEN_startFusing_752: out = fn_startFusing(args, argc); return true;
        case SYM_GEN_readyToTransform_753: out = fn_readyToTransform(args, argc); return true;
        case SYM_GEN_giveGold_754: out = fn_giveGold(args, argc); return true;
        case SYM_GEN_getTranslatedTypeName_755: out = fn_getTranslatedTypeName(args, argc); return true;
        case SYM_GEN_getTypeDescription_756: out = fn_getTypeDescription(args, argc); return true;
        case SYM_GEN_getTranslatedRarity_757: out = fn_getTranslatedRarity(args, argc); return true;
        case SYM_GEN_getRarityName_758: out = sf_getRarityName(gd_ctx, args, argc); return true;
        case SYM_GEN_logCooldown_759: out = fn_logCooldown(args, argc); return true;
        case SYM_GEN_getCombatDisplayAccuracy_760: out = fn_getCombatDisplayAccuracy(args, argc); return true;
        case SYM_GEN_getDisplayCritChance_761: out = fn_getDisplayCritChance(args, argc); return true;
        case SYM_GEN_getSalesMultiplier_762: out = fn_getSalesMultiplier(args, argc); return true;
        case SYM_GEN_prepareDiscard_763: out = fn_prepareDiscard(args, argc); return true;
        case SYM_GEN_discard_764: out = fn_discard(args, argc); return true;
        case SYM_GEN_popIn_765: out = fn_popIn(args, argc); return true;
        case SYM_GEN_disappear_766: out = fn_disappear(args, argc); return true;
        case SYM_GEN_appearInLibrary_767: out = fn_appearInLibrary(args, argc); return true;
        case SYM_GEN_createParticles_768: out = fn_createParticles(args, argc); return true;
        case SYM_GEN_deactivateParticles_769: out = fn_deactivateParticles(args, argc); return true;
        case SYM_GEN_makeRigidBody_770: out = fn_makeRigidBody(args, argc); return true;
        case SYM_GEN_dropImpulse_771: out = fn_dropImpulse(args, argc); return true;
        case SYM_GEN_makeNonRigidBody_772: out = fn_makeNonRigidBody(args, argc); return true;
        case SYM_GEN_rollShopChance_773: out = fn_rollShopChance(args, argc); return true;
        case SYM_GEN__physics_process_774: out = fn__physics_process(args, argc); return true;
        case SYM_GEN_playActivationAnimation_Scale_775: out = fn_playActivationAnimation_Scale(args, argc); return true;
        case SYM_GEN_playActivationAnimation_Jump_776: out = fn_playActivationAnimation_Jump(args, argc); return true;
        case SYM_GEN_playActivationAnimation_JumpSquash_777: out = fn_playActivationAnimation_JumpSquash(args, argc); return true;
        case SYM_GEN_playActivationAnimation_778: out = fn_playActivationAnimation(args, argc); return true;
        case SYM_GEN_playActivationSound_148: out = fn_playActivationSound(args, argc); return true;
        case SYM_GEN_clearSpriteMaterial_779: out = fn_clearSpriteMaterial(args, argc); return true;
        case SYM_GEN_giveProgressMaterial_780: out = fn_giveProgressMaterial(args, argc); return true;
        case SYM_GEN_getTextureSize_781: out = fn_getTextureSize(args, argc); return true;
        case SYM_GEN_scaleToFit_782: out = fn_scaleToFit(args, argc); return true;
        case SYM_GEN_getSpriteOffset_783: out = fn_getSpriteOffset(args, argc); return true;
        case SYM_GEN_getGlobalCenter_784: out = fn_getGlobalCenter(args, argc); return true;
        case SYM_GEN_getTextureSize_local_785: out = fn_getTextureSize_local(args, argc); return true;
        case SYM_GEN_scaleToFit_local_786: out = fn_scaleToFit_local(args, argc); return true;
        case SYM_GEN_getSpriteOffset_local_787: out = fn_getSpriteOffset_local(args, argc); return true;
        case SYM_GEN_setTexture_788: out = fn_setTexture(args, argc); return true;
        case SYM_GEN_updateShadowTexture_789: out = fn_updateShadowTexture(args, argc); return true;
        case SYM_GEN_initSpriteMaterial_790: out = fn_initSpriteMaterial(args, argc); return true;
        case SYM_GEN_updateShaderRotation_791: out = fn_updateShaderRotation(args, argc); return true;
        case SYM_GEN_allowCancelShaderTween_792: out = fn_allowCancelShaderTween(args, argc); return true;
        case SYM_GEN_showCooldownSmooth_793: out = fn_showCooldownSmooth(args, argc); return true;
        case SYM_GEN_showCooldown_794: out = fn_showCooldown(args, argc); return true;
        case SYM_GEN_createAnimation_795: out = fn_createAnimation(args, argc); return true;
        case SYM_GEN_playAnimation_796: out = fn_playAnimation(args, argc); return true;
        case SYM_GEN_hasInventoryDuration_797: out = fn_hasInventoryDuration(args, argc); return true;
        case SYM_GEN_reveal_798: out = fn_reveal(args, argc); return true;
        case SYM_GEN_setRevealed_799: out = fn_setRevealed(args, argc); return true;
        case SYM_GEN_isCrafted_800: out = fn_isCrafted(args, argc); return true;
        case SYM_GEN_isMovingBack_801: out = fn_isMovingBack(args, argc); return true;
        case SYM_GEN__notification_802: out = fn__notification(args, argc); return true;
        case SYM_GEN_getAllInInventoryOfType_803: out = fn_getAllInInventoryOfType(args, argc); return true;
        case SYM_GEN_countAllInInventoryOfType_804: out = fn_countAllInInventoryOfType(args, argc); return true;
        case SYM_GEN_isTypeInInventory_805: out = fn_isTypeInInventory(args, argc); return true;
        case SYM_GEN_isRecipeFinished_806: out = fn_isRecipeFinished(args, argc); return true;
        case SYM_GEN_canStartNewRecipe_807: out = fn_canStartNewRecipe(args, argc); return true;
        case SYM_GEN_getRecipes_808: out = fn_getRecipes(args, argc); return true;
        case SYM_GEN_breakBondVisual_809: out = fn_breakBondVisual(args, argc); return true;
        case SYM_GEN_removeBondedBaseItem_810: out = fn_removeBondedBaseItem(args, argc); return true;
        case SYM_GEN_removeBondedIngredient_811: out = fn_removeBondedIngredient(args, argc); return true;
        case SYM_GEN_removeAllIngredients_812: out = fn_removeAllIngredients(args, argc); return true;
        case SYM_GEN_considerAsBond_813: out = fn_considerAsBond(args, argc); return true;
        case SYM_GEN_addBondedIngredient_814: out = fn_addBondedIngredient(args, argc); return true;
        case SYM_GEN_addToBaseItem_815: out = fn_addToBaseItem(args, argc); return true;
        case SYM_GEN_playBondAnimation_816: out = fn_playBondAnimation(args, argc); return true;
        case SYM_GEN_playBondFailedAnimation_817: out = fn_playBondFailedAnimation(args, argc); return true;
        case SYM_GEN_isCatalystBond_818: out = fn_isCatalystBond(args, argc); return true;
        case SYM_GEN_isLocked_819: out = fn_isLocked(args, argc); return true;
        case SYM_GEN_canLockBag_820: out = fn_canLockBag(args, argc); return true;
        case SYM_GEN_canBeLocked_821: out = fn_canBeLocked(args, argc); return true;
        case SYM_GEN_setLocked_822: out = fn_setLocked(args, argc); return true;
        case SYM_GEN_unlockCombining_823: out = fn_unlockCombining(args, argc); return true;
        case SYM_GEN_lockCombining_824: out = fn_lockCombining(args, argc); return true;
        case SYM_GEN_showLockLabel_825: out = fn_showLockLabel(args, argc); return true;
        case SYM_GEN_getLockPosition_826: out = fn_getLockPosition(args, argc); return true;
        case SYM_GEN_setBoundAsIngredient_827: out = fn_setBoundAsIngredient(args, argc); return true;
        case SYM_GEN_canPreviewFusions_828: out = fn_canPreviewFusions(args, argc); return true;
        case SYM_GEN_getCraftingPreviewPosition_829: out = fn_getCraftingPreviewPosition(args, argc); return true;
        case SYM_GEN_previewFusions_830: out = fn_previewFusions(args, argc); return true;
        case SYM_GEN_previewRecipeIngredients_831: out = fn_previewRecipeIngredients(args, argc); return true;
        case SYM_GEN_previewFusionToItem_832: out = fn_previewFusionToItem(args, argc); return true;
        case SYM_GEN_hasShopItemCraftCandidates_833: out = fn_hasShopItemCraftCandidates(args, argc); return true;
        case SYM_GEN_typeInIngredients_834: out = fn_typeInIngredients(args, argc); return true;
        case SYM_GEN_getTextEffect_835: out = fn_getTextEffect(args, argc); return true;
        case SYM_GEN_getFusionItemName_836: out = fn_getFusionItemName(args, argc); return true;
        case SYM_GEN_showProgressLabel_837: out = fn_showProgressLabel(args, argc); return true;
        case SYM_GEN_onCraftingLabelReturned_838: out = fn_onCraftingLabelReturned(args, argc); return true;
        case SYM_GEN_createBondVisual_839: out = fn_createBondVisual(args, argc); return true;
        case SYM_GEN_updateBondVisuals_840: out = fn_updateBondVisuals(args, argc); return true;
        case SYM_GEN_fuse_841: out = fn_fuse(args, argc); return true;
        case SYM_GEN_onFusingAsIngredient_842: out = fn_onFusingAsIngredient(args, argc); return true;
        case SYM_GEN_onFusingAsCatalystFinished_843: out = fn_onFusingAsCatalystFinished(args, argc); return true;
        case SYM_GEN_createCraftedShockwave_844: out = fn_createCraftedShockwave(args, argc); return true;
        case SYM_GEN_finishFusing_845: out = fn_finishFusing(args, argc); return true;
        case SYM_GEN_allowGeneratingFusionItem_846: out = fn_allowGeneratingFusionItem(args, argc); return true;
        case SYM_GEN_catalystFusingFinished_847: out = fn_catalystFusingFinished(args, argc); return true;
        case SYM_GEN_onFusingFinished_848: out = fn_onFusingFinished(args, argc); return true;
        case SYM_GEN_onCraftedFrom_849: out = fn_onCraftedFrom(args, argc); return true;
        case SYM_GEN_getCraftingOffset_850: out = fn_getCraftingOffset(args, argc); return true;
        case SYM_GEN_playCraftedAnimation_851: out = fn_playCraftedAnimation(args, argc); return true;
        case SYM_GEN_onRestoreSnapshot_852: out = fn_onRestoreSnapshot(args, argc); return true;
        case SYM_GEN_getShopPriority_853: out = fn_getShopPriority(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__CoreItem::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__Item::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_getNumTooltipStats_624: out = sf_getNumTooltipStats(gd_ctx, args, argc); return true;
        case SYM_GEN_getNumStackChangeTypes_625: out = sf_getNumStackChangeTypes(gd_ctx, args, argc); return true;
        case SYM_GEN_wasAddedToInventory_659: out = sf_wasAddedToInventory(gd_ctx, args, argc); return true;
        case SYM_GEN_wasBought_660: out = sf_wasBought(gd_ctx, args, argc); return true;
        case SYM_GEN_wasHotSwap_661: out = sf_wasHotSwap(gd_ctx, args, argc); return true;
        case SYM_GEN_getRarityName_758: out = sf_getRarityName(gd_ctx, args, argc); return true;
        default: break;
    }
    return Gd__gd_core__CoreItem::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__Item::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__CoreItem::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_hasPreDealDamageEarlyEffect = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[0])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_has_method, _ca, 1); })();
    this->f_hasPreDealDamageLateEffect = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[1])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_has_method, _ca, 1); })();
    this->f_hasDealtDamageEffect = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[2])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_has_method, _ca, 1); })();
    this->f_hasOnChargeReceivedEffect = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[3])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_has_method, _ca, 1); })();
    this->f_hasOnChargeLeftEffect = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[4])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), gd::SYM_has_method, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::sf_getNumTooltipStats(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_ItemStat_1398), gd::SYM_size, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::sf_getNumStackChangeTypes(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_StackChangeType_871), gd::SYM_size, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_preset(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_initPhysicsMaterial(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getShadowOffset(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_ownerType, gd::GdVal::from_int(0LL))))) {
        return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_shadowOffset_shop_524);
    }
    else {
        return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_shadowOffset_dropped_525);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_initRecipeBook(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_initItemLibrary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_setSpotlight(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__spotlight = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hoverEnd_713, nullptr, 0);
    if (gd::gd_truth(this->f_spotlight)) {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_respondToHover_695, nullptr, 0);
    }
    else {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_respondToHoverEnd_704, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_initTitle(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_initTooltip(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_initBuildViewer(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_initBuildViewerIcon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_initInfoPanelIcon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_initGridStorageIcon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_initBuildViewerIcon_635, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getData(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_setData(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__data = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_persistDataInShop(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getTranslatedName(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_removeLinebreaks = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(false));
    if (gd::gd_truth(lv_removeLinebreaks)) {
        return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[5]), gd::GdVal::from_str(&battle_string_literals[6])}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, this->f_descriptor, SYM_GEN_getTranslatedName_641, nullptr, 0), gd::SYM_replace, _ca, 2); })();
    }
    else {
        return gd::native_inline_call(gd_ctx, this->f_descriptor, SYM_GEN_getTranslatedName_641, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_wrapInColor = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_descr = gd::native_inline_call(gd_ctx, this->f_descriptor, SYM_GEN_getDescription_642, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_requiredItem_2714), gd::GdVal::null())))) {
        gd::GdVal lv_requiredStr = ([&]() { gd::GdVal _ca[] = {([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 1); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[7]), gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_requiredItem_2714), SYM_GEN_getTranslatedName_641, nullptr, 0)); return gd::GdVal::from_dict(d); })()}; return gd::native_inline_call(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[8])}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_tra_2715, _ca, 1); })(), SYM_GEN_format_2716, _ca, 1); })();
        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[9])}; return gd::native_inline_call(gd_ctx, lv_descr, gd::SYM_begins_with, _ca, 1); })())) {
            lv_descr = gd::gd_add(gd_ctx, lv_requiredStr, lv_descr);
        }
        else {
            lv_descr = ([&]() { gd::GdVal _ca[] = {lv_requiredStr, gd::GdVal::from_str(&battle_string_literals[10]), lv_descr}; return gd::gd_str_fn(gd_ctx.arena, _ca, 3); })();
        }
    }
    return ([&]() { gd::GdVal _ca[] = {lv_descr, lv_wrapInColor}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameters_643, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_insertParameters(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_wrapInColor = (_argc > 1) ? _args[1] : (gd::GdVal::from_bool(true));
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBaseMinDamage_152, nullptr, 0), gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(lv_wrapInColor)) : gd::GdVal::from_bool(false)))) {
        lv_descr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[11]), ([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_minDam_1675)}; return gd::gd_str_fn(gd_ctx.arena, _ca, 1); })(), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_paramColor_2717)}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_wrapInColor_fixed_2718, _ca, 2); })()}; return gd::native_inline_call(gd_ctx, lv_descr, gd::SYM_replace, _ca, 2); })();
    }
    {
        gd::GdVal _t415 = gd::gd_iter_seq(gd_ctx.arena, gd::gd_add(gd_ctx, gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_extraCds_1680), gd::SYM_size, nullptr, 0), gd::GdVal::from_int(1LL)));
        gd::GdArr* _t416 = (_t415.kind == gd::GdVal::Kind::Arr) ? _t415.arr : nullptr;
        uint32_t _len__t417 = _t416 ? _t416->len : 0u;
        for (uint32_t _t417 = 0; _t417 < _len__t417; ++_t417) {
            gd::GdVal lv_i = _t416->data[_t417];
            lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[12]), gd::gd_add(gd_ctx, lv_i, gd::GdVal::from_int(1LL))}; return gd::gd_str_fn(gd_ctx.arena, _ca, 2); })(), ([&]() { gd::GdVal _ca[] = {lv_i}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getModifiedCooldownIndex_105, _ca, 1); })(), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isCooldownModified_278, nullptr, 0), gd::GdVal::from_bool(true), lv_wrapInColor}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_644, _ca, 6); })();
        }
    }
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(&battle_string_literals[12]), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getModifiedCooldown_104, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isCooldownModified_278, nullptr, 0), gd::GdVal::from_bool(true), lv_wrapInColor}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_644, _ca, 6); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(&battle_string_literals[13]), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance2_172, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isChance2Modified_281, nullptr, 0), gd::GdVal::from_bool(true), lv_wrapInColor}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_644, _ca, 6); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(&battle_string_literals[14]), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isChance1Modified_280, nullptr, 0), gd::GdVal::from_bool(true), lv_wrapInColor}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_644, _ca, 6); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(&battle_string_literals[15]), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getShopChance_237, nullptr, 0), gd::GdVal::from_int(0LL), gd::GdVal::from_bool(true), lv_wrapInColor}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_644, _ca, 6); })();
    lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_str(&battle_string_literals[16]), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getStaminaCost_112, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isStaminaModified_113, nullptr, 0), gd::GdVal::from_bool(true), lv_wrapInColor}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_644, _ca, 6); })();
    {
        gd::GdVal _t418 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_params_1570), gd::SYM_size, nullptr, 0));
        gd::GdArr* _t419 = (_t418.kind == gd::GdVal::Kind::Arr) ? _t418.arr : nullptr;
        uint32_t _len__t420 = _t419 ? _t419->len : 0u;
        for (uint32_t _t420 = 0; _t420 < _len__t420; ++_t420) {
            gd::GdVal lv_i = _t419->data[_t420];
            lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[17]), gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::gd_add(gd_ctx, lv_i, gd::GdVal::from_int(1LL))))), ([&]() { gd::GdVal _ca[] = {lv_i}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_int(0LL), gd::GdVal::from_bool(true), lv_wrapInColor}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_644, _ca, 6); })();
        }
    }
    {
        gd::GdVal _t421 = gd::gd_iter_seq(gd_ctx.arena, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_sortedParamNames_1711));
        gd::GdArr* _t422 = (_t421.kind == gd::GdVal::Kind::Arr) ? _t421.arr : nullptr;
        uint32_t _len__t423 = _t422 ? _t422->len : 0u;
        for (uint32_t _t423 = 0; _t423 < _len__t423; ++_t423) {
            gd::GdVal lv_paramName = _t422->data[_t423];
            lv_descr = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[18]), lv_paramName), ([&]() { gd::GdVal _ca[] = {lv_paramName}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_int(0LL), gd::GdVal::from_bool(true), lv_wrapInColor}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_insertParameter_644, _ca, 6); })();
        }
    }
    if (gd::gd_truth(lv_wrapInColor)) {
        lv_descr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[19]), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_204, nullptr, 0))), gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_paramColor_2717)}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_wrapInColor_fixed_2718, _ca, 2); })()}; return gd::native_inline_call(gd_ctx, lv_descr, gd::SYM_replace, _ca, 2); })();
    }
    return lv_descr;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_insertParameter(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_paramName = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_value = (_argc > 2) ? _args[2] : gd::GdVal::null();
    gd::GdVal lv_modified = (_argc > 3) ? _args[3] : (gd::GdVal::from_int(0LL));
    gd::GdVal lv_checkZero = (_argc > 4) ? _args[4] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_wrapInColor = (_argc > 5) ? _args[5] : (gd::GdVal::from_bool(true));
    lv_value = gd::gd_stepify(lv_value, gd::GdVal::from_float(0.01));
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_value, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(lv_checkZero))))))) {
        gd::GdVal lv_replacedString = gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[20]), lv_paramName);
        gd::GdVal lv_startPos = ([&]() { gd::GdVal _ca[] = {lv_replacedString}; return gd::native_inline_call(gd_ctx, lv_descr, gd::SYM_find, _ca, 1); })();
        if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_startPos, gd::gd_neg(gd::GdVal::from_int(1LL)))))) {
            gd::GdVal lv_refEndPos = ([&]() { gd::GdVal _ca[] = {lv_descr, gd::gd_add(gd_ctx, lv_startPos, gd::GdVal::from_int(1LL))}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_findHighlightEnd_2719, _ca, 2); })();
            gd::GdVal lv_unit = ([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, lv_startPos, gd::native_inline_call(gd_ctx, lv_replacedString, gd::SYM_length, nullptr, 0)), gd::gd_sub(gd::gd_sub(lv_refEndPos, gd::gd_add(gd_ctx, lv_startPos, gd::GdVal::from_int(1LL))), gd::native_inline_call(gd_ctx, lv_paramName, gd::SYM_length, nullptr, 0))}; return gd::native_inline_call(gd_ctx, lv_descr, gd::SYM_substr, _ca, 2); })();
            gd::GdVal lv_replacement = gd::gd_add(gd_ctx, gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, lv_value)), lv_unit);
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_startPos, gd::GdVal::from_int(0LL))))) {
                if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_array_index(gd_ctx, lv_descr, gd::gd_sub(lv_startPos, gd::GdVal::from_int(1LL))), gd::GdVal::from_str(&battle_string_literals[21]))))) {
                    lv_replacedString = gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[21]), lv_replacedString);
                    lv_replacement = gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[21]), lv_replacement);
                }
                else if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_array_index(gd_ctx, lv_descr, gd::gd_sub(lv_startPos, gd::GdVal::from_int(1LL))), gd::GdVal::from_str(&battle_string_literals[22]))))) {
                    lv_replacedString = gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[22]), lv_replacedString);
                    lv_replacement = gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[22]), lv_replacement);
                }
            }
            if (gd::gd_truth(lv_wrapInColor)) {
                lv_replacement = ([&]() { gd::GdVal _ca[] = {lv_replacement, gd::native_array_index(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_statColors_2720), lv_modified)}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_wrapInColor_fixed_2718, _ca, 2); })();
            }
            lv_descr = ([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, lv_replacedString, lv_unit), lv_replacement}; return gd::native_inline_call(gd_ctx, lv_descr, gd::SYM_replace, _ca, 2); })();
        }
    }
    return lv_descr;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getModeDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_text = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_colors = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_center = (_argc > 2) ? _args[2] : (gd::GdVal::from_bool(true));
    lv_center = gd::gd_coerce_bool(lv_center);
    gd::GdVal lv_wrapInColor = (_argc > 3) ? _args[3] : (gd::GdVal::from_bool(true));
    lv_wrapInColor = gd::gd_coerce_bool(lv_wrapInColor);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getFlavorText(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::native_inline_call(gd_ctx, this->f_descriptor, SYM_GEN_getFlavorText_646, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_disablePicking(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_enablePicking(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_enableTooltip(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_disableTooltip(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_disableFocus(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(this->f_focus)) {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_loseFocus_703, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_enableFocus(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_setEditMode(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_active = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_active = gd::gd_coerce_bool(lv_active);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_setShadowAlpha(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_alpha = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_alpha = gd::gd_coerce_float(lv_alpha);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getTopLeftGlobal(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_vec2(0.0, 0.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getBottomRightGlobal(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_vec2(0.0, 0.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getBottomCenter(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_vec2(0.0, 0.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(this->f_placed)) {
        return this->f_inventory;
    }
    else {
        return gd::GdVal::null();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::sf_wasAddedToInventory(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_dropRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_dropRes, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_dropRes, gd::GdVal::from_int(1LL))))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::sf_wasBought(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_dropRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth((gd::gd_truth((gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_dropRes}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__Item::call_static_fn(gd_ctx, SYM_GEN_wasAddedToInventory_659, _ca, 1, _out); return _out; })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_dropRes, gd::GdVal::from_int(4LL))))))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_dropRes, gd::GdVal::from_int(6LL))))))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_dropRes, gd::GdVal::from_int(7LL))))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::sf_wasHotSwap(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv_dropRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_dropRes, gd::GdVal::from_int(1LL)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_dropRes, gd::GdVal::from_int(7LL))))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_removeFromInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_playAffectedPlacedAnimation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_newItemIsAffected = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_sum = gd::GdVal::from_int(0LL);
    {
        gd::GdVal _t424 = gd::gd_iter_seq(gd_ctx.arena, lv_newItemIsAffected);
        gd::GdArr* _t425 = (_t424.kind == gd::GdVal::Kind::Arr) ? _t424.arr : nullptr;
        uint32_t _len__t426 = _t425 ? _t425->len : 0u;
        for (uint32_t _t426 = 0; _t426 < _len__t426; ++_t426) {
            gd::GdVal lv_color = _t425->data[_t426];
            lv_sum = gd::gd_add(gd_ctx, lv_sum, gd::gd_coerce_int(gd::native_array_index(gd_ctx, lv_newItemIsAffected, lv_color)));
        }
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_sum, gd::GdVal::from_int(1LL))))) {
    }
    else if (gd::gd_truth(gd::native_array_index(gd_ctx, lv_newItemIsAffected, gd::GdVal::from_int(0LL)))) {
    }
    else if (gd::gd_truth(gd::native_array_index(gd_ctx, lv_newItemIsAffected, gd::GdVal::from_int(1LL)))) {
    }
    else if (gd::gd_truth(gd::native_array_index(gd_ctx, lv_newItemIsAffected, gd::GdVal::from_int(2LL)))) {
    }
    else if (gd::gd_truth(gd::native_array_index(gd_ctx, lv_newItemIsAffected, gd::GdVal::from_int(3LL)))) {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_clearCanAffectVisuals(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_liesInStorage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_ownerType, gd::GdVal::from_int(2LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_dragged)))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_pushToStorage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_targetPos = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_addToStorageBox(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_addImpulse = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_tweenBouncyness = (_argc > 1) ? _args[1] : (gd::GdVal::from_bool(true));
    lv_tweenBouncyness = gd::gd_coerce_bool(lv_tweenBouncyness);
    gd::GdVal lv_checkCollisions = (_argc > 2) ? _args[2] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_targetPos = (_argc > 3) ? _args[3] : (gd::GdVal::null());
    gd::GdVal lv_speed = (_argc > 4) ? _args[4] : (gd::GdVal::from_float(1.0));
    gd::GdVal lv_secondCheck = (_argc > 5) ? _args[5] : (gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_removeFromStorage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_killMovebackTween_727, nullptr, 0);
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStorageLeft_669, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_onStorageLeft(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_isInGridStorage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getGridStorageProxy(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_onAddedToGridStorage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_onRemovedFromGridStorage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_makeGrabbable(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_extended = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_extended = gd::gd_coerce_bool(lv_extended);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_moveToFreeSpaceInStorage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_targetPos = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    gd::GdVal lv_addImpulse = (_argc > 1) ? _args[1] : (gd::GdVal::from_bool(false));
    gd::GdVal lv_speed = (_argc > 2) ? _args[2] : (gd::GdVal::from_float(1.0));
    gd::GdVal lv_secondCheck = (_argc > 3) ? _args[3] : (gd::GdVal::from_bool(false));
    gd::GdVal lv_tweenBouncyness = (_argc > 4) ? _args[4] : (gd::GdVal::from_bool(true));
    lv_tweenBouncyness = gd::gd_coerce_bool(lv_tweenBouncyness);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_checkIfOutofStorageBounds(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[23])}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_callNextFrame_1797, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_checkIfOutofStorageBounds2(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[24])}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_callNextFrame_1797, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_checkIfOutofStorageBounds3(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_findFreeSpace(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_startPos = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_vec2(0.0, 0.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_unclip(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_onAddedToStorageBox(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn__process(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_delta = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_delta = gd::gd_coerce_float(lv_delta);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn__integrate_forces(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_state = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::native_inline_call(gd_ctx, lv_state, SYM_GEN_get_contact_count_2726, nullptr, 0), gd::GdVal::from_int(0LL))))) {
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_updateShadow(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_lerpAngle_local(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_interpolationPoint = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_from = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_to = (_argc > 2) ? _args[2] : gd::GdVal::null();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateInsideRotationNode_686, nullptr, 0);
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateShadow_684, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_updateInsideRotationNode(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(this->f_insideRotationNode, gd::GdVal::null())))) {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_spawnRotationSparks(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_rotateRight = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_highlight(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_unhighlight(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_resetSprite_743, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_setBright(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_resetBright(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getHoverPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(this->f_dragged)) {
        return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_DRAG_PRIORITY_527);
    }
    else {
        return gd::GdVal::from_int(0LL);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_canGainFocus(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_gainFocus(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canGainFocus_693, nullptr, 0))))) {
        return gd::GdVal::null();
    }
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_ownerType, gd::GdVal::from_int(1LL)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_ownerType, gd::GdVal::from_int(7LL))))))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_ownerType, gd::GdVal::from_int(3LL)))))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_highlightItem_2727, _ca, 2); })();
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_respondToHover_695, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_respondToHover(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_canShowBuildIntoRecipesTooltip(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(this->f_dragged)) {
        return gd::GdVal::from_bool(false);
    }
    gd::GdVal lv_effectiveOwner = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getEffectiveOwnerType_257, nullptr, 0);
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_ownerType, gd::GdVal::from_int(6LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(this->f_owningBuildIntoRecipesTooltip, gd::GdVal::null())))) : gd::GdVal::from_bool(false)))) {
        if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canShowSubBuildIntoRecipesTooltip_697, nullptr, 0))))) {
            return gd::GdVal::from_bool(false);
        }
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_ownerType, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_ownerType, gd::GdVal::from_int(8LL))))))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::gd_in(lv_effectiveOwner, this->f_ownerTypesWithBuildTooltip)))))))) {
        return gd::GdVal::from_bool(false);
    }
    gd::GdVal lv_descr = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getRecipeDescriptor_701, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::native_inline_call(gd_ctx, lv_descr, SYM_GEN_getNumRecipes_2728, nullptr, 0), gd::GdVal::from_int(0LL))))) {
        return gd::GdVal::from_bool(true);
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getRelatedItems_459, nullptr, 0), gd::SYM_size, nullptr, 0), gd::GdVal::from_int(0LL))))) {
        return gd::GdVal::from_bool(true);
    }
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_canShowSubBuildIntoRecipesTooltip(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_showBuildIntoRecipesTooltip(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getRelatedItemColumns(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_int(5LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getRelatedItemHeight(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_int(150LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getRecipeDescriptor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_descriptor;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_hideBuildIntoRecipesTooltip(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(this->f_buildIntoRecipesTooltip, gd::GdVal::null())))) {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_loseFocus(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(this->f_dragged)) {
        return gd::GdVal::null();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_focus)))) {
        return gd::GdVal::null();
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_respondToHoverEnd_704, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_respondToHoverEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_activateDragParticles(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t427 = gd::gd_iter_seq(gd_ctx.arena, this->f_specificDragParticles);
        gd::GdArr* _t428 = (_t427.kind == gd::GdVal::Kind::Arr) ? _t427.arr : nullptr;
        uint32_t _len__t429 = _t428 ? _t428->len : 0u;
        for (uint32_t _t429 = 0; _t429 < _len__t429; ++_t429) {
            gd::GdVal lv_specificParticles = _t428->data[_t429];
            (void)gd::native_inline_call(gd_ctx, lv_specificParticles, SYM_GEN_activate_150, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_deactivateDragParticles(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t430 = gd::gd_iter_seq(gd_ctx.arena, this->f_specificDragParticles);
        gd::GdArr* _t431 = (_t430.kind == gd::GdVal::Kind::Arr) ? _t430.arr : nullptr;
        uint32_t _len__t432 = _t431 ? _t431->len : 0u;
        for (uint32_t _t432 = 0; _t432 < _len__t432; ++_t432) {
            gd::GdVal lv_specificParticles = _t431->data[_t432];
            (void)gd::native_inline_call(gd_ctx, lv_specificParticles, SYM_GEN_deactivate_2729, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_updateTooltip(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_queueTooltipUpdate(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_clearTooltip(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hideBuildIntoRecipesTooltip_702, nullptr, 0);
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_clearCanAffectVisuals_664, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_mouseEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_hover(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_mouseExited(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_hoverEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_isHovered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(this->f_hovered) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(this->f_dragged)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getScaleProp(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(this->f_hasSquishySprite)) {
        return gd::GdVal::from_str(&battle_string_literals[25]);
    }
    else {
        return gd::GdVal::from_str(&battle_string_literals[26]);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_setSpriteScale(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_newScale = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(this->f_hasSquishySprite)) {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_pickup(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_pickupType = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_onDraggedWithParentStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_parentItem = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_finishMoveback_719, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_finishMoveback(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_onDraggedWithParentEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_canSnap(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(gd::native_inline_call(gd_ctx, this->f_draggedInsideItems, gd::SYM_empty, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_draggingParent, gd::GdVal::null())))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_reactToDropResult(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_result = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_drop(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_int(0LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_showClickArea(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_cancelDrag(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_emptyTweenCallback(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_killMovebackTween(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showClickArea_724, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_setSpriteGlobalPos(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_pos = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateShadow_684, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_dropIntoInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_hotswap = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_finishInsideItemsRotation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_pushDraggedItemsToStorage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t433 = gd::gd_iter_seq(gd_ctx.arena, this->f_draggedInsideItems);
        gd::GdArr* _t434 = (_t433.kind == gd::GdVal::Kind::Arr) ? _t433.arr : nullptr;
        uint32_t _len__t435 = _t434 ? _t434->len : 0u;
        for (uint32_t _t435 = 0; _t435 < _len__t435; ++_t435) {
            gd::GdVal lv_item = _t434->data[_t435];
            (void)gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_pushToStorage_666, nullptr, 0);
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_correctInsideItemFacedirection_479, nullptr, 0);
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_clearDraggedInsideItems_733, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_reparentItemsInside(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t436 = gd::gd_iter_seq(gd_ctx.arena, this->f_draggedInsideItems);
        gd::GdArr* _t437 = (_t436.kind == gd::GdVal::Kind::Arr) ? _t436.arr : nullptr;
        uint32_t _len__t438 = _t437 ? _t437->len : 0u;
        for (uint32_t _t438 = 0; _t438 < _len__t438; ++_t438) {
            gd::GdVal lv_item = _t437->data[_t438];
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_correctInsideItemFacedirection_479, nullptr, 0);
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_clearDraggedInsideItems_733, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_clearDraggedInsideItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t439 = gd::gd_iter_seq(gd_ctx.arena, this->f_draggedInsideItems);
        gd::GdArr* _t440 = (_t439.kind == gd::GdVal::Kind::Arr) ? _t439.arr : nullptr;
        uint32_t _len__t441 = _t440 ? _t440->len : 0u;
        for (uint32_t _t441 = 0; _t441 < _len__t441; ++_t441) {
            gd::GdVal lv_item = _t440->data[_t441];
            (void)gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_onDraggedWithParentEnd_720, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_showSockets(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_hideSockets(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_playPickupSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_playDropSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_volume = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_canBeSold(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_ownerType, gd::GdVal::from_int(1LL)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_ownerType, gd::GdVal::from_int(2LL))))))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_ownerType, gd::GdVal::from_int(7LL))))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_isPickingPossible(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_canBePicked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth((gd::gd_truth(this->f_focus) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isPickingPossible_738, nullptr, 0))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_frame_counter_1413), this->f_dropFrame)))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_canBeDraggedWithBag(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_canBeDropped(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(this->f_dragged) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_frame_counter_1413), this->f_pickupFrame)))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn__input(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_resetSprite(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_combatToShop(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isOwnedByOpponent_251, nullptr, 0))) {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_disableTooltip_650, nullptr, 0);
    }
    else {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_resetSprite_743, nullptr, 0);
        (void)gd::native_inline_call(gd_ctx, this->f_cachedAffectedItems, gd::SYM_clear, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_shopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_craft = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_craft = gd::gd_coerce_bool(lv_craft);
    this->f_baseCooldownOverride = gd::gd_coerce_float(gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_cd_1679));
    this->f_speedScale = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_bonusMinDam = gd::gd_coerce_float(gd::GdVal::from_int(0LL));
    this->f_bonusMaxDam = gd::gd_coerce_float(gd::GdVal::from_int(0LL));
    this->f_removableDam = gd::gd_coerce_float(gd::GdVal::from_int(0LL));
    this->f_bonusDamageFactor = gd::gd_coerce_float(gd::GdVal::from_float(1.0));
    this->f_staminaFactor = gd::gd_coerce_float(gd::GdVal::from_float(1.0));
    {
        gd::GdVal _t442 = gd::gd_iter_seq(gd_ctx.arena, this->f_buffPowers);
        gd::GdArr* _t443 = (_t442.kind == gd::GdVal::Kind::Arr) ? _t442.arr : nullptr;
        uint32_t _len__t444 = _t443 ? _t443->len : 0u;
        for (uint32_t _t444 = 0; _t444 < _len__t444; ++_t444) {
            gd::GdVal lv_buff = _t443->data[_t444];
            { gd::GdVal _t445 = this->f_buffPowers; gd::GdVal _t446 = lv_buff; gd::native_array_set_index(gd_ctx, _t445, _t446, gd::GdVal::from_float(1.0)); }
            { gd::GdVal _t447 = this->f_buffAmplificationChances; gd::GdVal _t448 = lv_buff; gd::native_array_set_index(gd_ctx, _t447, _t448, gd::GdVal::from_float(0.0)); }
        }
    }
    this->f_critChancePercent = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_critTokens = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_critSeverity = gd::gd_coerce_float(Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_BASE_CRIT_SEVERITY_0));
    this->f_bonusChancePercent_mult = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_bonusChancePercent_additive1 = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_bonusChancePercent_additive2 = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_bonusAccuracy = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_doubleActivationChance = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    this->f_doubleAttackEffectChance = gd::gd_coerce_float(gd::GdVal::from_float(0.0));
    (void)gd::native_inline_call(gd_ctx, this->f_paramMult, gd::SYM_clear, nullptr, 0);
    (void)gd::native_inline_call(gd_ctx, this->f_paramAdd, gd::SYM_clear, nullptr, 0);
    this->f_numCharges = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null()}; return gd::native_inline_call(gd_ctx, this->f_statDisplayOverrides, gd::SYM_fill, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, this->f_itemMetrics, gd::SYM_fill, _ca, 1); })();
    this->f_consumed = gd::GdVal::from_bool(false);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showCooldownSmooth_793, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_enablePicking_648, nullptr, 0);
    {
        gd::GdVal _t449 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemsNoNull_497, nullptr, 0));
        gd::GdArr* _t450 = (_t449.kind == gd::GdVal::Kind::Arr) ? _t449.arr : nullptr;
        uint32_t _len__t451 = _t450 ? _t450->len : 0u;
        for (uint32_t _t451 = 0; _t451 < _len__t451; ++_t451) {
            gd::GdVal lv_gem = _t450->data[_t451];
            (void)([&]() { gd::GdVal _ca[] = {lv_craft}; return gd::native_inline_call(gd_ctx, lv_gem, SYM_GEN_shopEntered_745, _ca, 1); })();
        }
    }
    if (gd::gd_truth(lv_craft)) {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addToCraftingQueue_749, nullptr, 0);
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onShopEntered_746, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_startFusing_inShop(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_PRE_FUSE_DUR_COG_604)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_startFusing_752, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getCraftingPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isGem_84, nullptr, 0))) {
        return gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_CraftingPriority_857), SYM_GEN_Gem_2731);
    }
    {
        gd::GdVal _t452 = gd::gd_iter_seq(gd_ctx.arena, this->f_bondedIngredients);
        gd::GdArr* _t453 = (_t452.kind == gd::GdVal::Kind::Arr) ? _t452.arr : nullptr;
        uint32_t _len__t454 = _t453 ? _t453->len : 0u;
        for (uint32_t _t454 = 0; _t454 < _len__t454; ++_t454) {
            gd::GdVal lv_bonded = _t453->data[_t454];
            if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_bonded, SYM_GEN_isGem_84, nullptr, 0))) {
                return gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_CraftingPriority_857), SYM_GEN_Mixed_2732);
            }
        }
    }
    return gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_CraftingPriority_857), SYM_GEN_NonGem_2733);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_addToCraftingQueue(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_combatToTitle(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isOwnedByOpponent_251, nullptr, 0))) {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_disableTooltip_650, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_readyToFuse(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(this->f_curRecipe) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(([&]() { gd::GdVal _ca[] = {this->f_bondedIngredients}; return gd::native_inline_call(gd_ctx, this->f_curRecipe, SYM_GEN_getProgress_2734, _ca, 1); })(), gd::GdVal::from_int(1LL))))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_startFusing(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_delay = (_argc > 0) ? _args[0] : (Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, SYM_GEN_PRE_FUSE_DUR_603));
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_readyToFuse_751, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_str(&battle_string_literals[27]), lv_delay}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_callDelayed_1479, _ca, 3); })();
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_disablePicking_647, nullptr, 0);
        {
            gd::GdVal _t455 = gd::gd_iter_seq(gd_ctx.arena, this->f_bondedIngredients);
            gd::GdArr* _t456 = (_t455.kind == gd::GdVal::Kind::Arr) ? _t455.arr : nullptr;
            uint32_t _len__t457 = _t456 ? _t456->len : 0u;
            for (uint32_t _t457 = 0; _t457 < _len__t457; ++_t457) {
                gd::GdVal lv_bonded = _t456->data[_t457];
                if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_curRecipe, gd::GdVal::null()))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_bonded}; return gd::native_inline_call(gd_ctx, this->f_curRecipe, SYM_GEN_isNeighborCatalyst_2735, _ca, 1); })()))))))) {
                    (void)([&]() { gd::GdVal _ca[] = {lv_bonded, gd::GdVal::from_str(&battle_string_literals[28]), gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}))}; return gd::native_inline_call(gd_ctx, this->f_ctx, SYM_GEN_defer_1482, _ca, 3); })();
                    gd::set_prop(gd_ctx, lv_bonded, SYM_GEN_willBeConsumed_608, gd::GdVal::from_bool(true));
                }
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_readyToTransform(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_giveGold(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_amount = gd::gd_coerce_int(lv_amount);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getTranslatedTypeName(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {lv_type}; return gd::native_inline_call(gd_ctx, this->f_descriptor, SYM_GEN_getTranslatedTypeName_755, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getTypeDescription(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_type = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, gd::gd_add(gd_ctx, gd::GdVal::from_str(&battle_string_literals[29]), gd::native_array_index(gd_ctx, gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_Type_855), gd::SYM_keys, nullptr, 0), lv_type)), gd::GdVal::from_str(&battle_string_literals[30]))}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_tra_2715, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getTranslatedRarity(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getRarity_236, nullptr, 0)}; gd::GdVal _out = gd::GdVal::null(); Gd__gd_core__Item::call_static_fn(gd_ctx, SYM_GEN_getRarityName_758, _ca, 1, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::sf_getRarityName(gd::BattleCtx& gd_ctx, const gd::GdVal* _args, int _argc) {
    gd::GdVal lv__rarity = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv__rarity = gd::gd_coerce_int(lv__rarity);
    return gd::GdVal::from_str(&battle_string_literals[6]);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_logCooldown(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_hasCooldown_95, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getCombatDisplayAccuracy(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_acc = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAccuracy_194, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_acc, gd::GdVal::from_int(100LL))))) {
        return gd::GdVal::from_str(&battle_string_literals[31]);
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_acc, gd::GdVal::from_int(0LL))))) {
        return gd::GdVal::from_str(&battle_string_literals[32]);
    }
    else {
        return gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, lv_acc));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getDisplayCritChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_c = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCritChancePercent_178, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_c, gd::GdVal::from_int(100LL))))) {
        return gd::GdVal::from_str(&battle_string_literals[31]);
    }
    else {
        return gd::GdVal::from_str(gd::gd_to_str(gd_ctx.arena, gd::gd_stepify(lv_c, gd::GdVal::from_float(0.1))));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getSalesMultiplier(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_float(1.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_prepareDiscard(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_discard(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_discardGems = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_popIn(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_withParticles = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    lv_withParticles = gd::gd_coerce_bool(lv_withParticles);
    gd::GdVal lv_speed = (_argc > 1) ? _args[1] : (gd::GdVal::from_float(1.0));
    gd::GdVal lv_jump = (_argc > 2) ? _args[2] : (gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_disappear(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_appearInLibrary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_createParticles(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_scene = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_baseScale = (_argc > 1) ? _args[1] : (gd::GdVal::from_vec2(1.0, 1.0));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_deactivateParticles(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_makeRigidBody(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_dropImpulse(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_direction = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    gd::GdVal lv_tweenBouncyness = (_argc > 1) ? _args[1] : (gd::GdVal::from_bool(true));
    lv_tweenBouncyness = gd::gd_coerce_bool(lv_tweenBouncyness);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_makeNonRigidBody(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_rollShopChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_shopChance = (_argc > 0) ? _args[0] : (gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_shopChance_1683));
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn__physics_process(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_delta = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_delta = gd::gd_coerce_float(lv_delta);
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_isStunned_1171, nullptr, 0))))) {
        this->f_triggerTime = gd::gd_coerce_float(gd::gd_sub(this->f_triggerTime, gd::gd_mul(lv_delta, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getSpeed_92, nullptr, 0))));
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_sub(gd::GdVal::from_float(1.0), gd::gd_div(gd_ctx, this->f_triggerTime, this->f_iterationCooldown))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showCooldown_794, _ca, 1); })();
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(this->f_triggerTime, gd::GdVal::from_int(0LL))))) {
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_trigger_143, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_playActivationAnimation_Scale(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_maxScale = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_maxScale = gd::gd_coerce_float(lv_maxScale);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_playActivationAnimation_Jump(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_height = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_maxScale = (_argc > 1) ? _args[1] : (gd::GdVal::from_float(1.0));
    lv_maxScale = gd::gd_coerce_float(lv_maxScale);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_playActivationAnimation_JumpSquash(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_height = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_intensity = (_argc > 1) ? _args[1] : (gd::GdVal::from_float(0.2));
    gd::GdVal lv_longScale = gd::gd_add(gd_ctx, gd::GdVal::from_float(1.0), lv_intensity);
    gd::GdVal lv_shortScale = gd::gd_div(gd_ctx, gd::GdVal::from_float(1.0), lv_longScale);
    gd::GdVal lv_scaling = gd::GdVal::from_vec2(0.0, 0.0);
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_faceDirection, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_UP)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_faceDirection, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_DOWN)))))))) {
        lv_scaling = gd::GdVal::from_vec2((lv_shortScale).as_float(), (lv_longScale).as_float());
    }
    else {
        lv_scaling = gd::GdVal::from_vec2((lv_longScale).as_float(), (lv_shortScale).as_float());
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_playActivationAnimation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_aniType = (_argc > 0) ? _args[0] : (gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_activationAni_1717));
    gd::GdVal lv_consume = (_argc > 1) ? _args[1] : (gd::GdVal::from_bool(false));
    lv_consume = gd::gd_coerce_bool(lv_consume);
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_resetSprite_743, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_aniType, gd::GdVal::from_int(1LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(40LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playActivationAnimation_Jump_776, _ca, 1); })();
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_aniType, gd::GdVal::from_int(2LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(40LL), gd::GdVal::from_float(0.1)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playActivationAnimation_JumpSquash_777, _ca, 2); })();
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_aniType, gd::GdVal::from_int(3LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(40LL), gd::GdVal::from_float(0.2)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playActivationAnimation_JumpSquash_777, _ca, 2); })();
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_aniType, gd::GdVal::from_int(4LL))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_aniType, gd::GdVal::from_int(5LL))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_aniType, gd::GdVal::from_int(18LL))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_aniType, gd::GdVal::from_int(6LL))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_aniType, gd::GdVal::from_int(7LL))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_aniType, gd::GdVal::from_int(13LL))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_aniType, gd::GdVal::from_int(10LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(30LL), gd::GdVal::from_float(1.3)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playActivationAnimation_Jump_776, _ca, 2); })();
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_aniType, gd::GdVal::from_int(8LL))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_aniType, gd::GdVal::from_int(11LL))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_aniType, gd::GdVal::from_int(15LL))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_aniType, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(1.5)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playActivationAnimation_Scale_775, _ca, 1); })();
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_aniType, gd::GdVal::from_int(9LL))))) {
        if (gd::gd_truth(this->f_hasSquishySprite)) {
        }
        else {
        }
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_aniType, gd::GdVal::from_int(12LL))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_aniType, gd::GdVal::from_int(19LL))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_aniType, gd::GdVal::from_int(14LL))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_aniType, gd::GdVal::from_int(20LL))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_aniType, gd::GdVal::from_int(21LL))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_aniType, gd::GdVal::from_int(17LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(30LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playActivationAnimation_Jump_776, _ca, 1); })();
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_aniType, gd::GdVal::from_int(16LL))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_aniType, gd::GdVal::from_int(22LL))))) {
    }
    if (gd::gd_truth(lv_consume)) {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_playActivationSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::GdVal::from_int(6LL))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playDropSound_149, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_clearSpriteMaterial(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_giveProgressMaterial(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getTextureSize(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_vec2(0.0, 0.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_scaleToFit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_maxSize = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_maxScale = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_maxScale = gd::gd_coerce_float(lv_maxScale);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getSpriteOffset(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_vec2(0.0, 0.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getGlobalCenter(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_vec2(0.0, 0.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getTextureSize_local(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_vec2(0.0, 0.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_scaleToFit_local(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_maxSize = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_maxScale = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_maxScale = gd::gd_coerce_float(lv_maxScale);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getSpriteOffset_local(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_vec2(0.0, 0.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_setTexture(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_newTex = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_initSpriteMaterial_790, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_updateShadowTexture(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_initSpriteMaterial(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_updateShaderRotation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_allowCancelShaderTween(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_showCooldownSmooth(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_progress = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_progress = gd::gd_coerce_float(lv_progress);
    gd::GdVal lv_fill = (_argc > 1) ? _args[1] : (gd::GdVal::from_bool(false));
    lv_fill = gd::gd_coerce_bool(lv_fill);
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_canCancelShaderTween)))) {
        return gd::GdVal::null();
    }
    if (gd::gd_truth(lv_fill)) {
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_showCooldown(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_progress = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_progress = gd::gd_coerce_float(lv_progress);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_createAnimation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_playAnimation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_hit = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    lv_hit = gd::gd_coerce_bool(lv_hit);
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_animationScene_1695))))) {
        return gd::GdVal::null();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_hasInventoryDuration(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[33])}; return gd::native_inline_call(gd_ctx, this->f_descriptor, SYM_GEN_hasParam_1578, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_reveal(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_setRevealed(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_reveal_798, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_isCrafted(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::native_inline_call(gd_ctx, this->f_descriptor, SYM_GEN_isCraftedItem_1720, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_isMovingBack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn__notification(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_what = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_what = gd::gd_coerce_int(lv_what);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getAllInInventoryOfType(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isOwnedByOpponent_251, nullptr, 0))) {
        return ([&]() { gd::GdVal _ca[] = {lv_descr}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getItemsInInventoryOfType_opponent_1667, _ca, 1); })();
    }
    else {
        return ([&]() { gd::GdVal _ca[] = {lv_descr}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getItemsInInventoryOfType_1666, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_countAllInInventoryOfType(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isOwnedByOpponent_251, nullptr, 0))) {
        return ([&]() { gd::GdVal _ca[] = {lv_descr}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_countItemsInInventoryOfType_opponent_1669, _ca, 1); })();
    }
    else {
        return ([&]() { gd::GdVal _ca[] = {lv_descr}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_countItemsInInventoryOfType_1668, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_isTypeInInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isOwnedByOpponent_251, nullptr, 0))) {
        return ([&]() { gd::GdVal _ca[] = {lv_descr}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_isItemInInventory_opponent_1672, _ca, 1); })();
    }
    else {
        return ([&]() { gd::GdVal _ca[] = {lv_descr}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_isItemInInventory_1671, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_isRecipeFinished(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(gd::native_scalar_eq(([&]() { gd::GdVal _ca[] = {this->f_bondedIngredients}; return gd::native_inline_call(gd_ctx, this->f_curRecipe, SYM_GEN_getProgress_2734, _ca, 1); })(), gd::GdVal::from_int(1LL)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_canStartNewRecipe(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isBaseItem_258, nullptr, 0)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isAvailableForCrafting_493, nullptr, 0))) : gd::GdVal::from_bool(false));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getRecipes(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_checkClassAvailability = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    gd::GdVal lv_recipes = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t458 = gd::gd_iter_seq(gd_ctx.arena, gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_recipes_2758));
        gd::GdArr* _t459 = (_t458.kind == gd::GdVal::Kind::Arr) ? _t458.arr : nullptr;
        uint32_t _len__t460 = _t459 ? _t459->len : 0u;
        for (uint32_t _t460 = 0; _t460 < _len__t460; ++_t460) {
            gd::GdVal lv_recipe = _t459->data[_t460];
            (void)([&]() { gd::GdVal _ca[] = {lv_recipe}; return gd::native_inline_call(gd_ctx, lv_recipes, gd::SYM_push_back, _ca, 1); })();
        }
    }
    return lv_recipes;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_breakBondVisual(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_toItem = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_bondIndex = ([&]() { gd::GdVal _ca[] = {lv_toItem}; return gd::native_inline_call(gd_ctx, this->f_bondedIngredients, gd::SYM_find, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_bondIndex, gd::gd_neg(gd::GdVal::from_int(1LL)))))) {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_removeBondedBaseItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setBoundAsIngredient_827, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_removeBondedIngredient(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_breakBondVisual_809, _ca, 1); })();
    if (gd::gd_truth(this->f_fusing)) {
        return gd::GdVal::null();
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showProgressLabel_837, nullptr, 0);
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, this->f_bondedIngredients, gd::SYM_empty, nullptr, 0))) {
    }
    else {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateBondVisuals_840, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_removeAllIngredients(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showProgressLabel_837, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_considerAsBond(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_neighbor = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_score = gd::GdVal::from_float(0.0);
    gd::GdVal lv_recipe = gd::GdVal::null();
    if (gd::gd_truth(this->f_curRecipe)) {
        if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isRecipeFinished_806, nullptr, 0))) {
            return gd::GdVal::null();
        }
        if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_bondedIngredients, lv_neighbor}; return gd::native_inline_call(gd_ctx, this->f_curRecipe, SYM_GEN_checkNeighbor_2759, _ca, 2); })())) {
            gd::GdVal lv_progressBefore = ([&]() { gd::GdVal _ca[] = {this->f_bondedIngredients}; return gd::native_inline_call(gd_ctx, this->f_curRecipe, SYM_GEN_getProgress_2734, _ca, 1); })();
            gd::GdVal lv_progressWithNeighbor = gd::gd_div(gd_ctx, gd::gd_add(gd_ctx, gd::native_inline_call(gd_ctx, this->f_bondedIngredients, gd::SYM_size, nullptr, 0), gd::GdVal::from_int(1LL)), gd::gd_coerce_float(gd::native_inline_call(gd_ctx, this->f_curRecipe, SYM_GEN_getNumIngredients_2760, nullptr, 0)));
            lv_score = gd::gd_add(gd_ctx, lv_progressWithNeighbor, gd::gd_mul(gd::GdVal::from_float(0.1), lv_progressBefore));
            lv_recipe = this->f_curRecipe;
        }
    }
    else {
        gd::GdVal lv_bestScore = gd::GdVal::from_float(0.0);
        {
            gd::GdVal _t461 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getRecipes_808, nullptr, 0));
            gd::GdArr* _t462 = (_t461.kind == gd::GdVal::Kind::Arr) ? _t461.arr : nullptr;
            uint32_t _len__t463 = _t462 ? _t462->len : 0u;
            for (uint32_t _t463 = 0; _t463 < _len__t463; ++_t463) {
                gd::GdVal lv_r = _t462->data[_t463];
                if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {})), lv_neighbor}; return gd::native_inline_call(gd_ctx, lv_r, SYM_GEN_checkNeighbor_2759, _ca, 2); })())) {
                    gd::GdVal lv_s = gd::gd_div(gd_ctx, gd::GdVal::from_float(1.0), gd::native_inline_call(gd_ctx, lv_r, SYM_GEN_getNumIngredients_2760, nullptr, 0));
                    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_s, lv_bestScore)))) {
                        lv_bestScore = lv_s;
                        lv_recipe = lv_r;
                    }
                }
            }
        }
        lv_score = lv_bestScore;
    }
    if (gd::gd_truth(lv_recipe)) {
        return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {lv_recipe, lv_score}));
    }
    else {
        return gd::GdVal::null();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_addBondedIngredient(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_forRecipe = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_neighbor = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(this->f_curRecipe)) {
    }
    else {
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_neighbor}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_createBondVisual_839, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateBondVisuals_840, nullptr, 0);
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playBondAnimation_816, nullptr, 0);
    if (gd::gd_truth((gd::gd_truth(gd::get_prop(gd_ctx, lv_neighbor, SYM_GEN_placedByPlayer_50)) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(this->f_placedByPlayer))))) {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showProgressLabel_837, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_addToBaseItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_baseItem = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setBoundAsIngredient_827, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_playBondAnimation_816, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_playBondAnimation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_catalyst = gd::GdVal::from_bool(false);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(this->f_bondedBaseItem, gd::GdVal::null())))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(gd::get_prop(gd_ctx, this->f_bondedBaseItem, SYM_GEN_curRecipe_577), gd::GdVal::null())))) {
            lv_catalyst = gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_bondedBaseItem, SYM_GEN_curRecipe_577), SYM_GEN_isCatalystRecipe_2761, nullptr, 0);
        }
    }
    else {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(this->f_curRecipe, gd::GdVal::null())))) {
            lv_catalyst = gd::native_inline_call(gd_ctx, this->f_curRecipe, SYM_GEN_isCatalystRecipe_2761, nullptr, 0);
        }
    }
    if (gd::gd_truth(lv_catalyst)) {
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_playBondFailedAnimation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_isCatalystBond(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_bondedItem = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_curRecipe, gd::GdVal::null())))) {
        return gd::GdVal::from_bool(false);
    }
    return ([&]() { gd::GdVal _ca[] = {lv_bondedItem}; return gd::native_inline_call(gd_ctx, this->f_curRecipe, SYM_GEN_isNeighborCatalyst_2735, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_isLocked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_locked;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_canLockBag(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_canBeLocked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_setLocked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__locked = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_showLabel = (_argc > 1) ? _args[1] : (gd::GdVal::from_bool(true));
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_locked, lv__locked)))) {
        return gd::GdVal::null();
    }
    if (gd::gd_truth(lv__locked)) {
        (void)([&]() { gd::GdVal _ca[] = {lv_showLabel}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_lockCombining_824, _ca, 1); })();
    }
    else {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_unlockCombining_823, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_unlockCombining(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_playAni = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    lv_playAni = gd::gd_coerce_bool(lv_playAni);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_lockCombining(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_showLabel = (_argc > 0) ? _args[0] : (gd::GdVal::from_bool(true));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_showLockLabel(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getLockPosition(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_vec2(0.0, 0.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_setBoundAsIngredient(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__bound = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv__bound = gd::gd_coerce_bool(lv__bound);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_canPreviewFusions(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getCraftingPreviewPosition(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_previewFusions(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_previewRecipeIngredients(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_previewFusionToItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_hoveredIngredient = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_hasShopItemCraftCandidates(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_typeInIngredients(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_candidate = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_ingredients = (_argc > 1) ? _args[1] : gd::GdVal::null();
    {
        gd::GdVal _t464 = gd::gd_iter_seq(gd_ctx.arena, lv_ingredients);
        gd::GdArr* _t465 = (_t464.kind == gd::GdVal::Kind::Arr) ? _t464.arr : nullptr;
        uint32_t _len__t466 = _t465 ? _t465->len : 0u;
        for (uint32_t _t466 = 0; _t466 < _len__t466; ++_t466) {
            gd::GdVal lv_ingredient = _t465->data[_t466];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_ingredient}; return gd::native_inline_call(gd_ctx, lv_candidate, SYM_GEN_hasType_79, _ca, 1); })())) {
                return gd::GdVal::from_bool(true);
            }
        }
    }
    return gd::GdVal::from_bool(false);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getTextEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_textEffect_2371);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getFusionItemName(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_curRecipe, SYM_GEN_fusedItem_2762), SYM_GEN_getTranslatedName_641, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_showProgressLabel(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_onCraftingLabelReturned(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_createBondVisual(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_bondNeighbor = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_updateBondVisuals(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_fuse(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_onFusingAsIngredient(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_onFusingAsCatalystFinished(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_clearSpriteMaterial_779, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setBoundAsIngredient_827, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_createCraftedShockwave(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_fusedItem = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_finishFusing(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_allowGeneratingFusionItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_catalystFusingFinished(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_onFusingFinished(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_validBonds = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_onCraftedFrom(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_baseItem = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_ingredients = (_argc > 1) ? _args[1] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getCraftingOffset(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__forDirection = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_vec2(0.0, 0.0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_playCraftedAnimation(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_originPosition = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_onRestoreSnapshot(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_finishMoveback_719, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Item::fn_getShopPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_int(0LL);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__Item(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__Item>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__Item = {CLS_Gd__gd_core__Item, "Item", "res://gd_core/Item.gd", &META_Gd__gd_core__CoreItem, false, _alloc_Gd__gd_core__Item, &Gd__gd_core__Item::get_static_prop_fn, &Gd__gd_core__Item::call_static_fn};

void Gd__gd_core__Weapon::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core__Weapon::meta() const { return &META_Gd__gd_core__Weapon; }
gd::GdVal Gd__gd_core__Weapon::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__Weapon::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__Weapon::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__Weapon::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Weapon::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_attack_941: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__Weapon::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_attack_941: out = fn_attack(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__Weapon::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__Weapon::fn_attack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    gd::GdVal lv_res = ([&]() { gd::GdVal _ca[] = {lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealDamage_220, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_res}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Weapon::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_116, nullptr, 0), gd::GdVal::from_int(0LL))))) {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_attack_941, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Weapon::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_damageSource = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), gd::SYM_new, nullptr, 0), SYM_GEN_setItem_1550, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__Weapon(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__Weapon>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__Weapon = {CLS_Gd__gd_core__Weapon, "Weapon", "res://gd_core/Weapon.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__Weapon, &Gd__gd_core__Weapon::get_static_prop_fn, &Gd__gd_core__Weapon::call_static_fn};

void Gd__gd_core__CoreBuff__INNER__TemporaryStacks::init_fields(gd::BattleCtx& gd_ctx) {
    this->f_amount = gd::GdVal::from_int(0);
    this->f_timeout = gd::GdVal::from_float(0.0);
    this->f_item = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__CoreBuff__INNER__TemporaryStacks::meta() const { return &META_Gd__gd_core__CoreBuff__INNER__TemporaryStacks; }
gd::GdVal Gd__gd_core__CoreBuff__INNER__TemporaryStacks::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return gd::GdVal::null();
}
bool Gd__gd_core__CoreBuff__INNER__TemporaryStacks::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__CoreBuff__INNER__TemporaryStacks::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_amount_1041: out = this->f_amount; return true;
        case SYM_GEN_timeout_1042: out = this->f_timeout; return true;
        case SYM_GEN_item_1043: out = this->f_item; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreBuff__INNER__TemporaryStacks::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_amount_1041: this->f_amount = gd::gd_coerce_int(val); return true;
        case SYM_GEN_timeout_1042: this->f_timeout = gd::gd_coerce_float(val); return true;
        case SYM_GEN_item_1043: this->f_item = val; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreBuff__INNER__TemporaryStacks::has_own_method(gd::SymId m) const {
    switch (m) {
        case gd::SYM__init: return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreBuff__INNER__TemporaryStacks::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case gd::SYM__init: out = fn__init(args, argc); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreBuff__INNER__TemporaryStacks::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return false;
}
gd::GdVal Gd__gd_core__CoreBuff__INNER__TemporaryStacks::fn__init(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__timeout = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv__item = (_argc > 2) ? _args[2] : (gd::GdVal::null());
    this->f_amount = gd::gd_coerce_int(lv__amount);
    this->f_timeout = gd::gd_coerce_float(lv__timeout);
    this->f_item = lv__item;
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__CoreBuff__INNER__TemporaryStacks(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__CoreBuff__INNER__TemporaryStacks>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__CoreBuff__INNER__TemporaryStacks = {CLS_Gd__gd_core__CoreBuff__INNER__TemporaryStacks, "TemporaryStacks", "", nullptr, false, _alloc_Gd__gd_core__CoreBuff__INNER__TemporaryStacks, &Gd__gd_core__CoreBuff__INNER__TemporaryStacks::get_static_prop_fn, &Gd__gd_core__CoreBuff__INNER__TemporaryStacks::call_static_fn};

void Gd__gd_core__CoreItemBook::init_fields(gd::BattleCtx& gd_ctx) {
    this->f_descriptors = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f__ctx = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__CoreItemBook::meta() const { return &META_Gd__gd_core__CoreItemBook; }
gd::GdVal Gd__gd_core__CoreItemBook::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_DESCRIPTOR_IDS_1659: return ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 49); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[34]), gd::GdVal::from_str(&battle_string_literals[35])); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[36]), gd::GdVal::from_str(&battle_string_literals[37])); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[38]), gd::GdVal::from_str(&battle_string_literals[39])); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[40]), gd::GdVal::from_str(&battle_string_literals[41])); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[42]), gd::GdVal::from_str(&battle_string_literals[43])); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[44]), gd::GdVal::from_str(&battle_string_literals[45])); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[46]), gd::GdVal::from_str(&battle_string_literals[47])); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[48]), gd::GdVal::from_str(&battle_string_literals[49])); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[50]), gd::GdVal::from_str(&battle_string_literals[51])); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[52]), gd::GdVal::from_str(&battle_string_literals[53])); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[54]), gd::GdVal::from_str(&battle_string_literals[55])); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[56]), gd::GdVal::from_str(&battle_string_literals[57])); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[58]), gd::GdVal::from_str(&battle_string_literals[59])); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[60]), gd::GdVal::from_str(&battle_string_literals[61])); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[62]), gd::GdVal::from_str(&battle_string_literals[63])); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[64]), gd::GdVal::from_str(&battle_string_literals[65])); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[66]), gd::GdVal::from_str(&battle_string_literals[67])); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[68]), gd::GdVal::from_str(&battle_string_literals[69])); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[70]), gd::GdVal::from_str(&battle_string_literals[71])); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[72]), gd::GdVal::from_str(&battle_string_literals[73])); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[74]), gd::GdVal::from_str(&battle_string_literals[75])); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[76]), gd::GdVal::from_str(&battle_string_literals[77])); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[78]), gd::GdVal::from_str(&battle_string_literals[79])); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[80]), gd::GdVal::from_str(&battle_string_literals[81])); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[82]), gd::GdVal::from_str(&battle_string_literals[83])); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[84]), gd::GdVal::from_str(&battle_string_literals[85])); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[86]), gd::GdVal::from_str(&battle_string_literals[87])); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[88]), gd::GdVal::from_str(&battle_string_literals[89])); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[90]), gd::GdVal::from_str(&battle_string_literals[91])); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[92]), gd::GdVal::from_str(&battle_string_literals[93])); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[94]), gd::GdVal::from_str(&battle_string_literals[95])); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[96]), gd::GdVal::from_str(&battle_string_literals[97])); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[98]), gd::GdVal::from_str(&battle_string_literals[99])); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[100]), gd::GdVal::from_str(&battle_string_literals[101])); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[102]), gd::GdVal::from_str(&battle_string_literals[103])); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[104]), gd::GdVal::from_str(&battle_string_literals[105])); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[106]), gd::GdVal::from_str(&battle_string_literals[107])); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[108]), gd::GdVal::from_str(&battle_string_literals[109])); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[110]), gd::GdVal::from_str(&battle_string_literals[111])); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[112]), gd::GdVal::from_str(&battle_string_literals[113])); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[114]), gd::GdVal::from_str(&battle_string_literals[115])); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[116]), gd::GdVal::from_str(&battle_string_literals[117])); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[118]), gd::GdVal::from_str(&battle_string_literals[119])); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[120]), gd::GdVal::from_str(&battle_string_literals[121])); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[122]), gd::GdVal::from_str(&battle_string_literals[123])); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[124]), gd::GdVal::from_str(&battle_string_literals[125])); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[126]), gd::GdVal::from_str(&battle_string_literals[127])); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[128]), gd::GdVal::from_str(&battle_string_literals[129])); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[130]), gd::GdVal::from_str(&battle_string_literals[131])); return gd::GdVal::from_dict(d); })();
        default: break;
    }
    return gd::GdVal::null();
}
bool Gd__gd_core__CoreItemBook::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__CoreItemBook::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_descriptors_1658: out = this->f_descriptors; return true;
        case SYM_GEN__ctx_1347: out = this->f__ctx; return true;
        case SYM_GEN_DESCRIPTOR_IDS_1659: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreItemBook::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_descriptors_1658: this->f_descriptors = val; return true;
        case SYM_GEN__ctx_1347: this->f__ctx = val; return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreItemBook::has_own_method(gd::SymId m) const {
    switch (m) {
        case gd::SYM__init: return true;
        case SYM_GEN_getDescriptor_1660: return true;
        case SYM_GEN_hasDescriptor_1661: return true;
        case SYM_GEN_register_1662: return true;
        case SYM_GEN__sideItems_1663: return true;
        case SYM_GEN__inventorySide_1664: return true;
        case SYM_GEN__filter_1665: return true;
        case SYM_GEN_getItemsInInventoryOfType_1666: return true;
        case SYM_GEN_getItemsInInventoryOfType_opponent_1667: return true;
        case SYM_GEN_countItemsInInventoryOfType_1668: return true;
        case SYM_GEN_countItemsInInventoryOfType_opponent_1669: return true;
        case SYM_GEN_countPlacedItemsInInventoryOfType_1670: return true;
        case SYM_GEN_isItemInInventory_1671: return true;
        case SYM_GEN_isItemInInventory_opponent_1672: return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreItemBook::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case gd::SYM__init: out = fn__init(args, argc); return true;
        case SYM_GEN_getDescriptor_1660: out = fn_getDescriptor(args, argc); return true;
        case SYM_GEN_hasDescriptor_1661: out = fn_hasDescriptor(args, argc); return true;
        case SYM_GEN_register_1662: out = fn_register(args, argc); return true;
        case SYM_GEN__sideItems_1663: out = fn__sideItems(args, argc); return true;
        case SYM_GEN__inventorySide_1664: out = fn__inventorySide(args, argc); return true;
        case SYM_GEN__filter_1665: out = fn__filter(args, argc); return true;
        case SYM_GEN_getItemsInInventoryOfType_1666: out = fn_getItemsInInventoryOfType(args, argc); return true;
        case SYM_GEN_getItemsInInventoryOfType_opponent_1667: out = fn_getItemsInInventoryOfType_opponent(args, argc); return true;
        case SYM_GEN_countItemsInInventoryOfType_1668: out = fn_countItemsInInventoryOfType(args, argc); return true;
        case SYM_GEN_countItemsInInventoryOfType_opponent_1669: out = fn_countItemsInInventoryOfType_opponent(args, argc); return true;
        case SYM_GEN_countPlacedItemsInInventoryOfType_1670: out = fn_countPlacedItemsInInventoryOfType(args, argc); return true;
        case SYM_GEN_isItemInInventory_1671: out = fn_isItemInInventory(args, argc); return true;
        case SYM_GEN_isItemInInventory_opponent_1672: out = fn_isItemInInventory_opponent(args, argc); return true;
        default: break;
    }
    return false;
}
bool Gd__gd_core__CoreItemBook::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return false;
}
gd::GdVal Gd__gd_core__CoreItemBook::fn__init(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemBook::fn_getDescriptor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_itemName = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_itemName}; return gd::native_inline_call(gd_ctx, this->f_descriptors, gd::SYM_has, _ca, 1); })())))) {
        { gd::GdVal _t467 = this->f_descriptors; gd::GdVal _t468 = lv_itemName; gd::native_array_set_index(gd_ctx, _t467, _t468, ([&]() { gd::GdVal _ca[] = {([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 2); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[132]), lv_itemName); d->set(gd_ctx.arena, gd::GdVal::from_str(&battle_string_literals[133]), lv_itemName); return gd::GdVal::from_dict(d); })()}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreItemData), gd::SYM_new, nullptr, 0), SYM_GEN_fromDict_1726, _ca, 1); })()); }
    }
    return gd::native_array_index(gd_ctx, this->f_descriptors, lv_itemName);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemBook::fn_hasDescriptor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_itemName = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {lv_itemName}; return gd::native_inline_call(gd_ctx, this->f_descriptors, gd::SYM_has, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemBook::fn_register(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_data = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(gd::get_prop(gd_ctx, lv_data, SYM_GEN_name_7), gd::GdVal::from_str(&battle_string_literals[6]))))) {
        { gd::GdVal _t469 = this->f_descriptors; gd::GdVal _t470 = gd::get_prop(gd_ctx, lv_data, SYM_GEN_name_7); gd::native_array_set_index(gd_ctx, _t469, _t470, lv_data); }
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(gd::get_prop(gd_ctx, lv_data, SYM_GEN_identifier_1673), gd::GdVal::from_str(&battle_string_literals[6]))))) {
        { gd::GdVal _t471 = this->f_descriptors; gd::GdVal _t472 = gd::get_prop(gd_ctx, lv_data, SYM_GEN_identifier_1673); gd::native_array_set_index(gd_ctx, _t471, _t472, lv_data); }
    }
    return lv_data;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemBook::fn__sideItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_opponentSide = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv_opponentSide = gd::gd_coerce_bool(lv_opponentSide);
    if (gd::gd_truth(lv_opponentSide)) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::get_prop(gd_ctx, this->f__ctx, SYM_GEN_opponent_75), gd::GdVal::null())))) {
            return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
        }
        return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f__ctx, SYM_GEN_opponent_75), SYM_GEN_inventory_5), SYM_GEN_getItemsAndGems_1604, nullptr, 0);
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::get_prop(gd_ctx, this->f__ctx, SYM_GEN_player_1302), gd::GdVal::null())))) {
        return gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    }
    return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, this->f__ctx, SYM_GEN_player_1302), SYM_GEN_inventory_5), SYM_GEN_getItemsAndGems_1604, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemBook::fn__inventorySide(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::get_prop(gd_ctx, lv_item, SYM_GEN_ownerType_49), gd::GdVal::from_int(1LL)))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::get_prop(gd_ctx, lv_item, SYM_GEN_ownerType_49), gd::GdVal::from_int(7LL))))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemBook::fn__filter(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_opponentSide = (_argc > 1) ? _args[1] : gd::GdVal::null();
    lv_opponentSide = gd::gd_coerce_bool(lv_opponentSide);
    gd::GdVal lv_out = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {}));
    {
        gd::GdVal _t473 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {lv_opponentSide}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__sideItems_1663, _ca, 1); })());
        gd::GdArr* _t474 = (_t473.kind == gd::GdVal::Kind::Arr) ? _t473.arr : nullptr;
        uint32_t _len__t475 = _t474 ? _t474->len : 0u;
        for (uint32_t _t475 = 0; _t475 < _len__t475; ++_t475) {
            gd::GdVal lv_item = _t474->data[_t475];
            if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_item, gd::GdVal::null()))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(gd::get_prop(gd_ctx, lv_item, SYM_GEN_descriptor_2), lv_descr))))))) {
                continue;
            }
            if (gd::gd_truth((gd::gd_truth(lv_opponentSide) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__inventorySide_1664, _ca, 1); })()))))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, lv_out, gd::SYM_push_back, _ca, 1); })();
            }
        }
    }
    return lv_out;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemBook::fn_getItemsInInventoryOfType(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__filter_1665, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemBook::fn_getItemsInInventoryOfType_opponent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__filter_1665, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemBook::fn_countItemsInInventoryOfType(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__filter_1665, _ca, 2); })(), gd::SYM_size, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemBook::fn_countItemsInInventoryOfType_opponent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__filter_1665, _ca, 2); })(), gd::SYM_size, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemBook::fn_countPlacedItemsInInventoryOfType(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_count = gd::GdVal::from_int(0LL);
    {
        gd::GdVal _t476 = gd::gd_iter_seq(gd_ctx.arena, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__sideItems_1663, _ca, 1); })());
        gd::GdArr* _t477 = (_t476.kind == gd::GdVal::Kind::Arr) ? _t476.arr : nullptr;
        uint32_t _len__t478 = _t477 ? _t477->len : 0u;
        for (uint32_t _t478 = 0; _t478 < _len__t478; ++_t478) {
            gd::GdVal lv_item = _t477->data[_t478];
            if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_item, gd::GdVal::null()))) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(gd::get_prop(gd_ctx, lv_item, SYM_GEN_descriptor_2), lv_descr))))))) {
                continue;
            }
            if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::get_prop(gd_ctx, lv_item, SYM_GEN_ownerType_49), gd::GdVal::from_int(7LL))))) {
                lv_count = gd::gd_add(gd_ctx, lv_count, gd::GdVal::from_int(1LL));
            }
            else if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::get_prop(gd_ctx, lv_item, SYM_GEN_ownerType_49), gd::GdVal::from_int(1LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::get_prop(gd_ctx, lv_item, SYM_GEN_placed_6))) : gd::GdVal::from_bool(false)))) {
                lv_count = gd::gd_add(gd_ctx, lv_count, gd::GdVal::from_int(1LL));
            }
        }
    }
    return lv_count;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemBook::fn_isItemInInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_bool(!gd::gd_truth(gd::native_inline_call(gd_ctx, ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__filter_1665, _ca, 2); })(), gd::SYM_empty, nullptr, 0)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__CoreItemBook::fn_isItemInInventory_opponent(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_bool(!gd::gd_truth(gd::native_inline_call(gd_ctx, ([&]() { gd::GdVal _ca[] = {lv_descr, gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN__filter_1665, _ca, 2); })(), gd::SYM_empty, nullptr, 0)));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__CoreItemBook(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__CoreItemBook>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__CoreItemBook = {CLS_Gd__gd_core__CoreItemBook, "CoreItemBook", "res://gd_core/CoreItemBook.gd", nullptr, false, _alloc_Gd__gd_core__CoreItemBook, &Gd__gd_core__CoreItemBook::get_static_prop_fn, &Gd__gd_core__CoreItemBook::call_static_fn};

void Gd__gd_core__DarkestLotus::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Card::init_fields(gd_ctx);
    this->f_manaParticles = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__DarkestLotus::meta() const { return &META_Gd__gd_core__DarkestLotus; }
gd::GdVal Gd__gd_core__DarkestLotus::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Card::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__DarkestLotus::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__DarkestLotus::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_manaParticles_1826: out = this->f_manaParticles; return true;
        default: break;
    }
    return Gd__gd_core__Card::get_prop(prop, out);
}
bool Gd__gd_core__DarkestLotus::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_manaParticles_1826: this->f_manaParticles = val; return true;
        default: break;
    }
    return Gd__gd_core__Card::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__DarkestLotus::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doRevealEffect_893: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Card::has_own_method(m);
}
bool Gd__gd_core__DarkestLotus::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doRevealEffect_893: out = fn_doRevealEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Card::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__DarkestLotus::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Card::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__DarkestLotus::fn_doRevealEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_mana = gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0), this->f_chainPosition);
    (void)([&]() { gd::GdVal _ca[] = {lv_mana}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_216, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0), this->f_chainPosition)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeRandomBuffs_372, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__DarkestLotus::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Card::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__DarkestLotus(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__DarkestLotus>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__DarkestLotus = {CLS_Gd__gd_core__DarkestLotus, "DarkestLotus", "res://gd_core/DarkestLotus.gd", &META_Gd__gd_core__Card, false, _alloc_Gd__gd_core__DarkestLotus, &Gd__gd_core__DarkestLotus::get_static_prop_fn, &Gd__gd_core__DarkestLotus::call_static_fn};

void Gd__gd_core__Flute::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
    this->f_options = gd::GdVal::from_arr(gd::GdArr::create(gd_ctx.arena));
}
const gd::GdClassMeta* Gd__gd_core__Flute::meta() const { return &META_Gd__gd_core__Flute; }
gd::GdVal Gd__gd_core__Flute::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__Flute::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__Flute::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_options_1876: out = this->f_options; return true;
        default: break;
    }
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__Flute::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_options_1876: this->f_options = val; return true;
        default: break;
    }
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__Flute::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__Flute::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__Flute::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__Flute::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Flute::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::gd_div(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0), gd::GdVal::from_float(100.0)), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    this->f_options = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_int(0LL), gd::GdVal::from_int(1LL), gd::GdVal::from_int(2LL)}));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Flute::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_rng = ([&]() { gd::GdVal _ca[] = {this->f_options}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_pickRandomElement_1746, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_rng, gd::GdVal::from_int(0LL))))) {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, nullptr, 0);
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_rng, gd::GdVal::from_int(1LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStamina_318, _ca, 1); })();
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_215, _ca, 1); })();
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    this->f_options = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_int(0LL), gd::GdVal::from_int(1LL), gd::GdVal::from_int(2LL)}));
    (void)([&]() { gd::GdVal _ca[] = {lv_rng}; return gd::native_inline_call(gd_ctx, this->f_options, gd::SYM_erase, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__Flute::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__Flute(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__Flute>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__Flute = {CLS_Gd__gd_core__Flute, "Flute", "res://gd_core/Flute.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__Flute, &Gd__gd_core__Flute::get_static_prop_fn, &Gd__gd_core__Flute::call_static_fn};

static const gd::GdEnum::KV _ekv_Gd__gd_core__HolySpear_SpearState[] = {{"Inactive", 0LL}, {"Active", 1LL}, {"Used", 2LL}};
static const gd::GdEnum _enum_Gd__gd_core__HolySpear_SpearState = {"SpearState", _ekv_Gd__gd_core__HolySpear_SpearState, 3u};
void Gd__gd_core__HolySpear::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Weapon::init_fields(gd_ctx);
    this->f_blockRemoval = gd::GdVal::from_int(0);
    this->f_cleanses = gd::GdVal::from_int(0);
    this->f_spearState = gd::GdVal::from_int(0);
    this->f_activationParticles = gd::GdVal::null();
    this->f_buffTimer = gd::GdVal::null();
    this->f_blockRemovalPerSlot = gd::GdVal::from_int(0);
    this->f_buffedSpeed = gd::GdVal::null();
    this->f_manaCost = gd::GdVal::from_int(0);
    this->f_light = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__HolySpear::meta() const { return &META_Gd__gd_core__HolySpear; }
gd::GdVal Gd__gd_core__HolySpear::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_SpearState_1902: return gd::GdVal::from_enum(&_enum_Gd__gd_core__HolySpear_SpearState);
        default: break;
    }
    return Gd__gd_core__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__HolySpear::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__HolySpear::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_blockRemoval_1897: out = this->f_blockRemoval; return true;
        case SYM_GEN_cleanses_1898: out = this->f_cleanses; return true;
        case SYM_GEN_spearState_1899: out = this->f_spearState; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        case SYM_GEN_buffTimer_1819: out = this->f_buffTimer; return true;
        case SYM_GEN_blockRemovalPerSlot_1900: out = this->f_blockRemovalPerSlot; return true;
        case SYM_GEN_buffedSpeed_1901: out = this->f_buffedSpeed; return true;
        case SYM_GEN_manaCost_1815: out = this->f_manaCost; return true;
        case SYM_GEN_light_949: out = this->f_light; return true;
        case SYM_GEN_SpearState_1902: out = gd::GdVal::from_enum(&_enum_Gd__gd_core__HolySpear_SpearState); return true;
        default: break;
    }
    return Gd__gd_core__Weapon::get_prop(prop, out);
}
bool Gd__gd_core__HolySpear::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_blockRemoval_1897: this->f_blockRemoval = gd::gd_coerce_int(val); return true;
        case SYM_GEN_cleanses_1898: this->f_cleanses = gd::gd_coerce_int(val); return true;
        case SYM_GEN_spearState_1899: this->f_spearState = gd::gd_coerce_int(val); return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        case SYM_GEN_buffTimer_1819: this->f_buffTimer = val; return true;
        case SYM_GEN_blockRemovalPerSlot_1900: this->f_blockRemovalPerSlot = gd::gd_coerce_int(val); return true;
        case SYM_GEN_buffedSpeed_1901: this->f_buffedSpeed = val; return true;
        case SYM_GEN_manaCost_1815: this->f_manaCost = gd::gd_coerce_int(val); return true;
        case SYM_GEN_light_949: this->f_light = val; return true;
        default: break;
    }
    return Gd__gd_core__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__HolySpear::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_affectsEmpty_255: return true;
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onPreDealDamage_late_906: return true;
        case SYM_GEN_onInvuEnded_1820: return true;
        case SYM_GEN_checkTrigger_1821: return true;
        case SYM_GEN_buffEnded_1817: return true;
        case SYM_GEN_onCombatEnd_132: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Weapon::has_own_method(m);
}
bool Gd__gd_core__HolySpear::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_affectsEmpty_255: out = fn_affectsEmpty(args, argc); return true;
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreDealDamage_late_906: out = fn_onPreDealDamage_late(args, argc); return true;
        case SYM_GEN_onInvuEnded_1820: out = fn_onInvuEnded(args, argc); return true;
        case SYM_GEN_checkTrigger_1821: out = fn_checkTrigger(args, argc); return true;
        case SYM_GEN_buffEnded_1817: out = fn_buffEnded(args, argc); return true;
        case SYM_GEN_onCombatEnd_132: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__HolySpear::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__HolySpear::fn_affectsEmpty(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_color = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HolySpear::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(22LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HolySpear::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numSlots = gd::gd_add(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumEmptyAffectedCells_426, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0));
    this->f_blockRemoval = gd::gd_coerce_int(gd::gd_mul(this->f_blockRemovalPerSlot, lv_numSlots));
    this->f_cleanses = gd::gd_coerce_int(lv_numSlots);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[134]), gd::GdVal::from_str(&battle_string_literals[135])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[136]), gd::GdVal::from_str(&battle_string_literals[137])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HolySpear::fn_onPreDealDamage_late(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_blockRemoval}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeBlock_205, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_cleanses}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseRandomDebuffs_356, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HolySpear::fn_onInvuEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_checkTrigger_1821, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HolySpear::fn_checkTrigger(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_triggerEvent = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_spearState, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_isVulnerable_1291, nullptr, 0))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_manaCost}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_checkMana_331, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL), gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 2); })();
        gd::GdVal lv_invuDur = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[138])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_invuDur, gd::GdVal::from_obj(this), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_makeInvulnerable_1211, _ca, 3); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_invuDur}; return gd::native_inline_call(gd_ctx, this->f_buffTimer, SYM_GEN_start_1779, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_manaCost, lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useMana_332, _ca, 2); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, this->f_buffedSpeed, gd::GdVal::from_float(100.0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HolySpear::fn_buffEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(2LL), gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, this->f_buffedSpeed, gd::GdVal::from_float(100.0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_reduceSpeed_274, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HolySpear::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, this->f_buffTimer, SYM_GEN_stop_1780, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HolySpear::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(0LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HolySpear::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__spearState = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv__spearState, gd::GdVal::from_int(0LL))))) {
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv__spearState, gd::GdVal::from_int(1LL))))) {
    }
    else {
    }
    this->f_spearState = gd::gd_coerce_int(lv__spearState);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HolySpear::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_add(gd_ctx, gd::GdVal::from_int(0LL), gd::GdVal::from_int(2LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__HolySpear::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_buffTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[139]), gd::GdVal::from_str(&battle_string_literals[140]), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_135, _ca, 3); })();
    this->f_blockRemovalPerSlot = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0));
    this->f_buffedSpeed = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0);
    this->f_manaCost = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__HolySpear(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__HolySpear>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__HolySpear = {CLS_Gd__gd_core__HolySpear, "HolySpear", "res://gd_core/HolySpear.gd", &META_Gd__gd_core__Weapon, false, _alloc_Gd__gd_core__HolySpear, &Gd__gd_core__HolySpear::get_static_prop_fn, &Gd__gd_core__HolySpear::call_static_fn};

void Gd__gd_core__ManaPotion::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Potion::init_fields(gd_ctx);
    this->f_healthThreshold = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__ManaPotion::meta() const { return &META_Gd__gd_core__ManaPotion; }
gd::GdVal Gd__gd_core__ManaPotion::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Potion::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__ManaPotion::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__ManaPotion::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_healthThreshold_1854: out = this->f_healthThreshold; return true;
        default: break;
    }
    return Gd__gd_core__Potion::get_prop(prop, out);
}
bool Gd__gd_core__ManaPotion::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_healthThreshold_1854: this->f_healthThreshold = val; return true;
        default: break;
    }
    return Gd__gd_core__Potion::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__ManaPotion::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onTriggerPotion_1849: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onDamaged_1855: return true;
        case SYM_GEN_onManaChanged_1929: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Potion::has_own_method(m);
}
bool Gd__gd_core__ManaPotion::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onTriggerPotion_1849: out = fn_onTriggerPotion(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onDamaged_1855: out = fn_onDamaged(args, argc); return true;
        case SYM_GEN_onManaChanged_1929: out = fn_onManaChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Potion::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__ManaPotion::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Potion::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__ManaPotion::fn_onTriggerPotion(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0), lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_216, _ca, 2); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_317, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ManaPotion::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[134]), gd::GdVal::from_str(&battle_string_literals[141])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[142]), gd::GdVal::from_str(&battle_string_literals[143])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ManaPotion::fn_onDamaged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__healthChange = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isEmpty_923, nullptr, 0))) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_relHealth = gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getRelativeHealth_302, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_relHealth, this->f_healthThreshold)))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consumePotion_1848, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ManaPotion::fn_onManaChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isEmpty_923, nullptr, 0))) {
        return gd::GdVal::null();
    }
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_amount, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_is_type(gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_getOrigin_1580, nullptr, 0), &META_Gd__gd_core_items__Item)))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_getOrigin_1580, nullptr, 0), SYM_GEN_character_74, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0))))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consumePotion_1848, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__ManaPotion::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Potion::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_healthThreshold = gd::gd_sub(gd::gd_div(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0), gd::GdVal::from_float(100.0)), gd::GdVal::from_float(0.0001));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__ManaPotion(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__ManaPotion>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__ManaPotion = {CLS_Gd__gd_core__ManaPotion, "ManaPotion", "res://gd_core/ManaPotion.gd", &META_Gd__gd_core__Potion, false, _alloc_Gd__gd_core__ManaPotion, &Gd__gd_core__ManaPotion::get_static_prop_fn, &Gd__gd_core__ManaPotion::call_static_fn};

void Gd__gd_core__PoisonIvy::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
    this->f_damageIncreaseActive = gd::GdVal::from_bool(false);
    this->f_activationParticles = gd::GdVal::null();
    this->f_poisonPerSpike = gd::GdVal::from_int(0);
}
const gd::GdClassMeta* Gd__gd_core__PoisonIvy::meta() const { return &META_Gd__gd_core__PoisonIvy; }
gd::GdVal Gd__gd_core__PoisonIvy::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__PoisonIvy::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__PoisonIvy::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_damageIncreaseActive_1963: out = this->f_damageIncreaseActive; return true;
        case SYM_GEN_activationParticles_912: out = this->f_activationParticles; return true;
        case SYM_GEN_poisonPerSpike_1964: out = this->f_poisonPerSpike; return true;
        default: break;
    }
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__PoisonIvy::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_damageIncreaseActive_1963: this->f_damageIncreaseActive = val; return true;
        case SYM_GEN_activationParticles_912: this->f_activationParticles = val; return true;
        case SYM_GEN_poisonPerSpike_1964: this->f_poisonPerSpike = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__PoisonIvy::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onSpikesChanged_944: return true;
        case SYM_GEN_onOpponentPoisonChanged_1831: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__PoisonIvy::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onSpikesChanged_944: out = fn_onSpikesChanged(args, argc); return true;
        case SYM_GEN_onOpponentPoisonChanged_1831: out = fn_onOpponentPoisonChanged(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__PoisonIvy::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__PoisonIvy::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(26LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__PoisonIvy::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[144]), gd::GdVal::from_str(&battle_string_literals[145])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[146]), gd::GdVal::from_str(&battle_string_literals[147])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0))}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeDebuffResistChances_1220, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__PoisonIvy::fn_onSpikesChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_amount, this->f_poisonPerSpike), lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictPoison_211, _ca, 2); })();
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__PoisonIvy::fn_onOpponentPoisonChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_curPoison = gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_getPoison_1229, nullptr, 0);
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_damageIncreaseActive))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv_curPoison, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0))))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0))}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_changeDamageResistance_1279, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true), gd::GdVal::from_bool(false), lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 3); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__PoisonIvy::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__PoisonIvy::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_active = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(lv_active)) {
    }
    else {
    }
    this->f_damageIncreaseActive = lv_active;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__PoisonIvy::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_poisonPerSpike = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_266, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__PoisonIvy(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__PoisonIvy>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__PoisonIvy = {CLS_Gd__gd_core__PoisonIvy, "PoisonIvy", "res://gd_core/PoisonIvy.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__PoisonIvy, &Gd__gd_core__PoisonIvy::get_static_prop_fn, &Gd__gd_core__PoisonIvy::call_static_fn};

void Gd__gd_core__SpikedShield::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Shield::init_fields(gd_ctx);
    this->f_spikesGiven = gd::GdVal::from_int(0);
    this->f_spikes = gd::GdVal::null();
    this->f_maxSpikes = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__SpikedShield::meta() const { return &META_Gd__gd_core__SpikedShield; }
gd::GdVal Gd__gd_core__SpikedShield::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Shield::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__SpikedShield::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__SpikedShield::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_spikesGiven_1982: out = this->f_spikesGiven; return true;
        case SYM_GEN_spikes_898: out = this->f_spikes; return true;
        case SYM_GEN_maxSpikes_1983: out = this->f_maxSpikes; return true;
        default: break;
    }
    return Gd__gd_core__Shield::get_prop(prop, out);
}
bool Gd__gd_core__SpikedShield::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_spikesGiven_1982: this->f_spikesGiven = gd::gd_coerce_int(val); return true;
        case SYM_GEN_spikes_898: this->f_spikes = val; return true;
        case SYM_GEN_maxSpikes_1983: this->f_maxSpikes = val; return true;
        default: break;
    }
    return Gd__gd_core__Shield::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__SpikedShield::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_beforeBlock_1941: return true;
        case SYM_GEN_afterBlock_1942: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Shield::has_own_method(m);
}
bool Gd__gd_core__SpikedShield::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_beforeBlock_1941: out = fn_beforeBlock(args, argc); return true;
        case SYM_GEN_afterBlock_1942: out = fn_afterBlock(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Shield::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__SpikedShield::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Shield::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__SpikedShield::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_spikesGiven = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__SpikedShield::fn_beforeBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Shield::call_method(gd_ctx, SYM_GEN_beforeBlock_1941, nullptr, 0, _out); return _out; })();
    gd::GdVal lv_spikesLeft = gd::gd_sub(this->f_maxSpikes, this->f_spikesGiven);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_spikesLeft, gd::GdVal::from_int(0LL))))) {
        gd::GdVal lv_spikesToGive = gd::gd_min(lv_spikesLeft, this->f_spikes);
        this->f_spikesGiven = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_spikesGiven, lv_spikesToGive));
        (void)([&]() { gd::GdVal _ca[] = {lv_spikesToGive}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveSpikes_209, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__SpikedShield::fn_afterBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0), gd::get_prop(gd_ctx, this->f_blockedDamageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_drainStamina_117, _ca, 2); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__SpikedShield::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Shield::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_spikes = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[148])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_maxSpikes = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[149])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__SpikedShield(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__SpikedShield>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__SpikedShield = {CLS_Gd__gd_core__SpikedShield, "SpikedShield", "res://gd_core/SpikedShield.gd", &META_Gd__gd_core__Shield, false, _alloc_Gd__gd_core__SpikedShield, &Gd__gd_core__SpikedShield::get_static_prop_fn, &Gd__gd_core__SpikedShield::call_static_fn};

void Gd__gd_core__StrongStoneSkinPotion::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__StoneSkinPotion::init_fields(gd_ctx);
    this->f_spikes = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__StrongStoneSkinPotion::meta() const { return &META_Gd__gd_core__StrongStoneSkinPotion; }
gd::GdVal Gd__gd_core__StrongStoneSkinPotion::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__StoneSkinPotion::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__StrongStoneSkinPotion::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__StrongStoneSkinPotion::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_spikes_898: out = this->f_spikes; return true;
        default: break;
    }
    return Gd__gd_core_items__StoneSkinPotion::get_prop(prop, out);
}
bool Gd__gd_core__StrongStoneSkinPotion::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_spikes_898: this->f_spikes = val; return true;
        default: break;
    }
    return Gd__gd_core_items__StoneSkinPotion::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__StrongStoneSkinPotion::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onTriggerPotion_1849: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__StoneSkinPotion::has_own_method(m);
}
bool Gd__gd_core__StrongStoneSkinPotion::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onTriggerPotion_1849: out = fn_onTriggerPotion(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__StoneSkinPotion::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__StrongStoneSkinPotion::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__StoneSkinPotion::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__StrongStoneSkinPotion::fn_onTriggerPotion(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {lv_triggerEvent}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__StoneSkinPotion::call_method(gd_ctx, SYM_GEN_onTriggerPotion_1849, _ca, 1, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_int(104LL), this->f_spikes, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[33])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacksTemporary_202, _ca, 5); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__StrongStoneSkinPotion::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__StoneSkinPotion::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_spikes = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[148])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__StrongStoneSkinPotion(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__StrongStoneSkinPotion>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__StrongStoneSkinPotion = {CLS_Gd__gd_core__StrongStoneSkinPotion, "StrongStoneSkinPotion", "res://gd_core/StrongStoneSkinPotion.gd", &META_Gd__gd_core_items__StoneSkinPotion, false, _alloc_Gd__gd_core__StrongStoneSkinPotion, &Gd__gd_core__StrongStoneSkinPotion::get_static_prop_fn, &Gd__gd_core__StrongStoneSkinPotion::call_static_fn};

void Gd__gd_core__YggdrasilLeaf::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core__Item::init_fields(gd_ctx);
    this->f_manaUsed = gd::GdVal::from_int(0LL);
    this->f_manaNeeded = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core__YggdrasilLeaf::meta() const { return &META_Gd__gd_core__YggdrasilLeaf; }
gd::GdVal Gd__gd_core__YggdrasilLeaf::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core__YggdrasilLeaf::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core__YggdrasilLeaf::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_manaUsed_2007: out = this->f_manaUsed; return true;
        case SYM_GEN_manaNeeded_1881: out = this->f_manaNeeded; return true;
        default: break;
    }
    return Gd__gd_core__Item::get_prop(prop, out);
}
bool Gd__gd_core__YggdrasilLeaf::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_manaUsed_2007: this->f_manaUsed = val; return true;
        case SYM_GEN_manaNeeded_1881: this->f_manaNeeded = val; return true;
        default: break;
    }
    return Gd__gd_core__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core__YggdrasilLeaf::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_onManaChanged_1929: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core__Item::has_own_method(m);
}
bool Gd__gd_core__YggdrasilLeaf::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onManaChanged_1929: out = fn_onManaChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core__YggdrasilLeaf::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core__YggdrasilLeaf::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(26LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__YggdrasilLeaf::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_manaUsed = gd::GdVal::from_int(0LL);
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[134]), gd::GdVal::from_str(&battle_string_literals[141])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__YggdrasilLeaf::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0), gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0), gd::SYM_size, nullptr, 0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_216, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0), gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0), gd::SYM_size, nullptr, 0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_214, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__YggdrasilLeaf::fn_onManaChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_amount, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[150]), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_getParam_1575, _ca, 2); })())) : gd::GdVal::from_bool(false)))) {
        this->f_manaUsed = gd::gd_add(gd_ctx, this->f_manaUsed, gd::gd_neg(lv_amount));
        gd::GdVal lv_activations = gd::gd_div(gd_ctx, this->f_manaUsed, this->f_manaNeeded);
        this->f_manaUsed = gd::gd_mod(gd_ctx, this->f_manaUsed, this->f_manaNeeded);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv_activations, gd::GdVal::from_int(1LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[151])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), lv_activations), lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP5_267, nullptr, 0), lv_activations), lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseRandomDebuffs_356, _ca, 2); })();
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core__YggdrasilLeaf::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_manaNeeded = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core__YggdrasilLeaf(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core__YggdrasilLeaf>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core__YggdrasilLeaf = {CLS_Gd__gd_core__YggdrasilLeaf, "YggdrasilLeaf", "res://gd_core/YggdrasilLeaf.gd", &META_Gd__gd_core__Item, false, _alloc_Gd__gd_core__YggdrasilLeaf, &Gd__gd_core__YggdrasilLeaf::get_static_prop_fn, &Gd__gd_core__YggdrasilLeaf::call_static_fn};

void Gd__gd_core_items__BloodyDagger::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Dagger::init_fields(gd_ctx);
    this->f_vampirismStacks = gd::GdVal::from_int(0);
}
const gd::GdClassMeta* Gd__gd_core_items__BloodyDagger::meta() const { return &META_Gd__gd_core_items__BloodyDagger; }
gd::GdVal Gd__gd_core_items__BloodyDagger::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Dagger::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__BloodyDagger::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__BloodyDagger::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_vampirismStacks_947: out = this->f_vampirismStacks; return true;
        default: break;
    }
    return Gd__gd_core_items__Dagger::get_prop(prop, out);
}
bool Gd__gd_core_items__BloodyDagger::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_vampirismStacks_947: this->f_vampirismStacks = gd::gd_coerce_int(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Dagger::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__BloodyDagger::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Dagger::has_own_method(m);
}
bool Gd__gd_core_items__BloodyDagger::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Dagger::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__BloodyDagger::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Dagger::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__BloodyDagger::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(24LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__BloodyDagger::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_vampirismStacks = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__BloodyDagger::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(this->f_vampirismStacks, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0))))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_210, _ca, 1); })();
            this->f_vampirismStacks = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_vampirismStacks, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)));
        }
        gd::GdVal lv_numAffected = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_numAffected, gd::GdVal::from_int(0LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_numAffected, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[151])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })())}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__BloodyDagger::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Dagger::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__BloodyDagger(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__BloodyDagger>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__BloodyDagger = {CLS_Gd__gd_core_items__BloodyDagger, "BloodyDagger", "res://gd_core_items/BloodyDagger.gd", &META_Gd__gd_core_items__Dagger, true, _alloc_Gd__gd_core_items__BloodyDagger, &Gd__gd_core_items__BloodyDagger::get_static_prop_fn, &Gd__gd_core_items__BloodyDagger::call_static_fn};

void Gd__gd_core_items__CursedDagger::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Dagger::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__CursedDagger::meta() const { return &META_Gd__gd_core_items__CursedDagger; }
gd::GdVal Gd__gd_core_items__CursedDagger::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Dagger::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__CursedDagger::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__CursedDagger::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Dagger::get_prop(prop, out);
}
bool Gd__gd_core_items__CursedDagger::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Dagger::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__CursedDagger::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN_onOpponentDebuffsChanged_1823: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Dagger::has_own_method(m);
}
bool Gd__gd_core_items__CursedDagger::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN_onOpponentDebuffsChanged_1823: out = fn_onOpponentDebuffsChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Dagger::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__CursedDagger::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Dagger::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__CursedDagger::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canDamage_89, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CursedDagger::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[152])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectToOpponentDebuffs_376, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CursedDagger::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictRandomDebuffs_357, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CursedDagger::fn_onOpponentDebuffsChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    gd::GdVal lv_extraCritChance = gd::gd_mul(lv_amount, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0));
    gd::GdVal lv_extraAccuracy = gd::gd_mul(lv_amount, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0));
    (void)([&]() { gd::GdVal _ca[] = {lv_extraCritChance}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addCritChancePercent_179, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {lv_extraAccuracy}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addAccuracy_177, _ca, 1); })();
    {
        gd::GdVal _t479 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t480 = (_t479.kind == gd::GdVal::Kind::Arr) ? _t479.arr : nullptr;
        uint32_t _len__t481 = _t480 ? _t480->len : 0u;
        for (uint32_t _t481 = 0; _t481 < _len__t481; ++_t481) {
            gd::GdVal lv_item = _t480->data[_t481];
            (void)([&]() { gd::GdVal _ca[] = {lv_extraCritChance}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addCritChancePercent_179, _ca, 1); })();
            if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_isWeapon_82, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_extraAccuracy}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addAccuracy_177, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__CursedDagger::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Dagger::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__CursedDagger(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__CursedDagger>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__CursedDagger = {CLS_Gd__gd_core_items__CursedDagger, "CursedDagger", "res://gd_core_items/CursedDagger.gd", &META_Gd__gd_core_items__Dagger, true, _alloc_Gd__gd_core_items__CursedDagger, &Gd__gd_core_items__CursedDagger::get_static_prop_fn, &Gd__gd_core_items__CursedDagger::call_static_fn};

void Gd__gd_core_items__Exclusive__AmuletofAgility::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_usedStacks = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_bonusSpeed = gd::GdVal::null();
    this->f_buffTimer = gd::GdVal::null();
    this->f_refund = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__AmuletofAgility::meta() const { return &META_Gd__gd_core_items__Exclusive__AmuletofAgility; }
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofAgility::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_amuletColor_2020: return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.639216), gd::GdVal::from_float(0.635294), gd::GdVal::from_float(0.215686)}; return gd::make_color_from_args(_ca, 3); })();
        default: break;
    }
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__AmuletofAgility::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__AmuletofAgility::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_usedStacks_1716: out = this->f_usedStacks; return true;
        case SYM_GEN_bonusSpeed_1882: out = this->f_bonusSpeed; return true;
        case SYM_GEN_buffTimer_1819: out = this->f_buffTimer; return true;
        case SYM_GEN_refund_2021: out = this->f_refund; return true;
        case SYM_GEN_amuletColor_2020: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__AmuletofAgility::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_usedStacks_1716: this->f_usedStacks = val; return true;
        case SYM_GEN_bonusSpeed_1882: this->f_bonusSpeed = val; return true;
        case SYM_GEN_buffTimer_1819: this->f_buffTimer = val; return true;
        case SYM_GEN_refund_2021: this->f_refund = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__AmuletofAgility::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_onBuffTimeout_2022: return true;
        case SYM_GEN_onBuffChanged_2006: return true;
        case SYM_GEN_onCombatEnd_132: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__AmuletofAgility::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onBuffTimeout_2022: out = fn_onBuffTimeout(args, argc); return true;
        case SYM_GEN_onBuffChanged_2006: out = fn_onBuffChanged(args, argc); return true;
        case SYM_GEN_onCombatEnd_132: out = fn_onCombatEnd(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__AmuletofAgility::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofAgility::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[153])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectToCharacterBuffs_374, _ca, 1); })();
    {
        gd::GdVal _t482 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1390, nullptr, 0));
        gd::GdArr* _t483 = (_t482.kind == gd::GdVal::Kind::Arr) ? _t482.arr : nullptr;
        uint32_t _len__t484 = _t483 ? _t483->len : 0u;
        for (uint32_t _t484 = 0; _t484 < _len__t484; ++_t484) {
            gd::GdVal lv_buff = _t483->data[_t484];
            { gd::GdVal _t485 = this->f_usedStacks; gd::GdVal _t486 = lv_buff; gd::native_array_set_index(gd_ctx, _t485, _t486, gd::GdVal::from_float(0.0)); }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofAgility::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasCooldown_95, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofAgility::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[33])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, this->f_buffTimer, SYM_GEN_start_1779, _ca, 1); })();
    {
        gd::GdVal _t487 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t488 = (_t487.kind == gd::GdVal::Kind::Arr) ? _t487.arr : nullptr;
        uint32_t _len__t489 = _t488 ? _t488->len : 0u;
        for (uint32_t _t489 = 0; _t489 < _len__t489; ++_t489) {
            gd::GdVal lv_item = _t488->data[_t489];
            (void)([&]() { gd::GdVal _ca[] = {this->f_bonusSpeed}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addSpeed_273, _ca, 1); })();
        }
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofAgility::fn_onBuffTimeout(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t490 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t491 = (_t490.kind == gd::GdVal::Kind::Arr) ? _t490.arr : nullptr;
        uint32_t _len__t492 = _t491 ? _t491->len : 0u;
        for (uint32_t _t492 = 0; _t492 < _len__t492; ++_t492) {
            gd::GdVal lv_item = _t491->data[_t492];
            (void)([&]() { gd::GdVal _ca[] = {this->f_bonusSpeed}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_reduceSpeed_274, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofAgility::fn_onBuffChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_amount, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[150]), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_getParam_1575, _ca, 2); })())) : gd::GdVal::from_bool(false)))) {
        gd::GdVal lv_used = gd::gd_neg(lv_amount);
        gd::GdVal lv_buffType = gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_getType_1572, nullptr, 0);
        { gd::GdVal _t493 = this->f_usedStacks; gd::GdVal _t494 = lv_buffType; gd::native_array_set_index(gd_ctx, _t493, _t494, gd::gd_add(gd_ctx, gd::native_array_index(gd_ctx, _t493, _t494), gd::gd_mul(lv_used, this->f_refund))); }
        gd::GdVal lv_toRefund = gd::gd_coerce_int(gd::gd_round(gd::native_array_index(gd_ctx, this->f_usedStacks, lv_buffType)));
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_toRefund, gd::GdVal::from_int(0LL))))) {
            { gd::GdVal _t495 = this->f_usedStacks; gd::GdVal _t496 = lv_buffType; gd::native_array_set_index(gd_ctx, _t495, _t496, gd::gd_sub(gd::native_array_index(gd_ctx, _t495, _t496), lv_toRefund)); }
            (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), lv_buffType, lv_toRefund, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_201, _ca, 4); })();
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofAgility::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, this->f_buffTimer, SYM_GEN_stop_1780, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__AmuletofAgility::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_bonusSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[154])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_buffTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[139]), gd::GdVal::from_str(&battle_string_literals[155]), gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_135, _ca, 3); })();
    this->f_refund = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[156])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__AmuletofAgility(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__AmuletofAgility>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__AmuletofAgility = {CLS_Gd__gd_core_items__Exclusive__AmuletofAgility, "AmuletofAgility", "res://gd_core_items/Exclusive/AmuletofAgility.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__AmuletofAgility, &Gd__gd_core_items__Exclusive__AmuletofAgility::get_static_prop_fn, &Gd__gd_core_items__Exclusive__AmuletofAgility::call_static_fn};

void Gd__gd_core_items__Exclusive__PowerPuppy::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_options = gd::GdVal::from_arr(gd::GdArr::create(gd_ctx.arena));
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__PowerPuppy::meta() const { return &META_Gd__gd_core_items__Exclusive__PowerPuppy; }
gd::GdVal Gd__gd_core_items__Exclusive__PowerPuppy::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__PowerPuppy::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__PowerPuppy::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_options_1876: out = this->f_options; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__PowerPuppy::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_options_1876: this->f_options = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__PowerPuppy::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_playPickupSound_736: return true;
        case SYM_GEN_playDropSound_149: return true;
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__PowerPuppy::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_playPickupSound_736: out = fn_playPickupSound(args, argc); return true;
        case SYM_GEN_playDropSound_149: out = fn_playDropSound(args, argc); return true;
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__PowerPuppy::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__PowerPuppy::fn_playPickupSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PowerPuppy::fn_playDropSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_volume = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    lv_volume = gd::gd_add(gd_ctx, lv_volume, this->f_impactSoundVolume);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PowerPuppy::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(3LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PowerPuppy::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_266, nullptr, 0)), gd::GdVal::from_float(100.0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    this->f_options = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_int(0LL), gd::GdVal::from_int(1LL), gd::GdVal::from_int(2LL)}));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PowerPuppy::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_rng = ([&]() { gd::GdVal _ca[] = {this->f_options}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_pickRandomElement_1746, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_rng, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_215, _ca, 1); })();
    }
    else if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_rng, gd::GdVal::from_int(1LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_214, _ca, 1); })();
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_217, _ca, 1); })();
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    this->f_options = gd::GdVal::from_arr(gd::GdArr::from_init(gd_ctx.arena, {gd::GdVal::from_int(0LL), gd::GdVal::from_int(1LL), gd::GdVal::from_int(2LL)}));
    (void)([&]() { gd::GdVal _ca[] = {lv_rng}; return gd::native_inline_call(gd_ctx, this->f_options, gd::SYM_erase, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PowerPuppy::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__PowerPuppy(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__PowerPuppy>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__PowerPuppy = {CLS_Gd__gd_core_items__Exclusive__PowerPuppy, "PowerPuppy", "res://gd_core_items/Exclusive/PowerPuppy.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__PowerPuppy, &Gd__gd_core_items__Exclusive__PowerPuppy::get_static_prop_fn, &Gd__gd_core_items__Exclusive__PowerPuppy::call_static_fn};

void Gd__gd_core_items__Greatsword::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_buffed = gd::GdVal::from_bool(false);
    this->f_buffParticles = gd::GdVal::null();
    this->f_empowerNeeded = gd::GdVal::null();
    this->f_buffedStamina = gd::GdVal::null();
    this->f_buffedCooldown = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Greatsword::meta() const { return &META_Gd__gd_core_items__Greatsword; }
gd::GdVal Gd__gd_core_items__Greatsword::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Greatsword::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Greatsword::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_buffed_1883: out = this->f_buffed; return true;
        case SYM_GEN_buffParticles_1884: out = this->f_buffParticles; return true;
        case SYM_GEN_empowerNeeded_1885: out = this->f_empowerNeeded; return true;
        case SYM_GEN_buffedStamina_1886: out = this->f_buffedStamina; return true;
        case SYM_GEN_buffedCooldown_1887: out = this->f_buffedCooldown; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Greatsword::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_buffed_1883: this->f_buffed = val; return true;
        case SYM_GEN_buffParticles_1884: this->f_buffParticles = val; return true;
        case SYM_GEN_empowerNeeded_1885: this->f_empowerNeeded = val; return true;
        case SYM_GEN_buffedStamina_1886: this->f_buffedStamina = val; return true;
        case SYM_GEN_buffedCooldown_1887: this->f_buffedCooldown = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Greatsword::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_isBuffed_1888: return true;
        case SYM_GEN_getStaminaCost_112: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_empowerChanged_1889: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Greatsword::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_isBuffed_1888: out = fn_isBuffed(args, argc); return true;
        case SYM_GEN_getStaminaCost_112: out = fn_getStaminaCost(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_empowerChanged_1889: out = fn_empowerChanged(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Greatsword::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Greatsword::fn_isBuffed(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_buffed;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Greatsword::fn_getStaminaCost(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_override = gd::native_array_index(gd_ctx, this->f_statDisplayOverrides, gd::GdVal::from_int(2LL));
    if (gd::gd_truth(lv_override)) {
        return lv_override;
    }
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isBuffed_1888, nullptr, 0))) {
        return gd::gd_mul(this->f_buffedStamina, this->f_staminaFactor);
    }
    else {
        return ([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN_getStaminaCost_112, nullptr, 0, _out); return _out; })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Greatsword::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[157]), gd::GdVal::from_str(&battle_string_literals[158])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Greatsword::fn_empowerChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_buffed))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getEmpower_1248, nullptr, 0), this->f_empowerNeeded)))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {this->f_buffedCooldown}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setBaseCooldown_108, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(2LL)}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 2); })();
    }
    else if (gd::gd_truth((gd::gd_truth(this->f_buffed) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getEmpower_1248, nullptr, 0), this->f_empowerNeeded)))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_resetBaseCooldown_109, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this), gd::GdVal::from_int(2LL)}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_log_1410), SYM_GEN_snapshotItemTooltipStat_1384, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Greatsword::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Greatsword::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__buffed = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_buffed = lv__buffed;
    if (gd::gd_truth(this->f_buffed)) {
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Greatsword::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_empowerNeeded = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0));
    this->f_buffedStamina = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0);
    this->f_buffedCooldown = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0);
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Greatsword(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Greatsword>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Greatsword = {CLS_Gd__gd_core_items__Greatsword, "Greatsword", "res://gd_core_items/Greatsword.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Greatsword, &Gd__gd_core_items__Greatsword::get_static_prop_fn, &Gd__gd_core_items__Greatsword::call_static_fn};

void Gd__gd_core_items__Exclusive__Broccoli::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Food::init_fields(gd_ctx);
    this->f_luck = gd::GdVal::null();
    this->f_luckNeeded = gd::GdVal::null();
    this->f_regen = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Broccoli::meta() const { return &META_Gd__gd_core_items__Exclusive__Broccoli; }
gd::GdVal Gd__gd_core_items__Exclusive__Broccoli::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Food::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Broccoli::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Broccoli::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_luck_897: out = this->f_luck; return true;
        case SYM_GEN_luckNeeded_1874: out = this->f_luckNeeded; return true;
        case SYM_GEN_regen_1999: out = this->f_regen; return true;
        default: break;
    }
    return Gd__gd_core_items__Food::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Broccoli::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_luck_897: this->f_luck = val; return true;
        case SYM_GEN_luckNeeded_1874: this->f_luckNeeded = val; return true;
        case SYM_GEN_regen_1999: this->f_regen = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Food::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Broccoli::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Food::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Broccoli::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Food::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Broccoli::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Food::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Broccoli::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getLucky_1237, nullptr, 0), this->f_luckNeeded)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_regen}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_214, _ca, 1); })();
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {this->f_luck}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_215, _ca, 1); })();
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Broccoli::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Food::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_luck = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[159])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_luckNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[160])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[161])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Broccoli(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Broccoli>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Broccoli = {CLS_Gd__gd_core_items__Exclusive__Broccoli, "Broccoli", "res://gd_core_items/Exclusive/Broccoli.gd", &META_Gd__gd_core_items__Food, true, _alloc_Gd__gd_core_items__Exclusive__Broccoli, &Gd__gd_core_items__Exclusive__Broccoli::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Broccoli::call_static_fn};

void Gd__gd_core_items__Exclusive__CheeseGoobert::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Goobert::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__CheeseGoobert::meta() const { return &META_Gd__gd_core_items__Exclusive__CheeseGoobert; }
gd::GdVal Gd__gd_core_items__Exclusive__CheeseGoobert::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Goobert::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__CheeseGoobert::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__CheeseGoobert::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Goobert::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__CheeseGoobert::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Goobert::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__CheeseGoobert::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__CheeseGoobert::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__CheeseGoobert::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Goobert::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__CheeseGoobert::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_317, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRandomBuffs_369, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__CheeseGoobert::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Goobert::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__CheeseGoobert(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__CheeseGoobert>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__CheeseGoobert = {CLS_Gd__gd_core_items__Exclusive__CheeseGoobert, "CheeseGoobert", "res://gd_core_items/Exclusive/CheeseGoobert.gd", &META_Gd__gd_core_items__Goobert, true, _alloc_Gd__gd_core_items__Exclusive__CheeseGoobert, &Gd__gd_core_items__Exclusive__CheeseGoobert::get_static_prop_fn, &Gd__gd_core_items__Exclusive__CheeseGoobert::call_static_fn};

void Gd__gd_core_items__Exclusive__ChiliGoobert::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Goobert::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__ChiliGoobert::meta() const { return &META_Gd__gd_core_items__Exclusive__ChiliGoobert; }
gd::GdVal Gd__gd_core_items__Exclusive__ChiliGoobert::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Goobert::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__ChiliGoobert::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__ChiliGoobert::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Goobert::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__ChiliGoobert::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Goobert::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__ChiliGoobert::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__ChiliGoobert::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__ChiliGoobert::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Goobert::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__ChiliGoobert::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_218, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__ChiliGoobert::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Goobert::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__ChiliGoobert(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__ChiliGoobert>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__ChiliGoobert = {CLS_Gd__gd_core_items__Exclusive__ChiliGoobert, "ChiliGoobert", "res://gd_core_items/Exclusive/ChiliGoobert.gd", &META_Gd__gd_core_items__Goobert, true, _alloc_Gd__gd_core_items__Exclusive__ChiliGoobert, &Gd__gd_core_items__Exclusive__ChiliGoobert::get_static_prop_fn, &Gd__gd_core_items__Exclusive__ChiliGoobert::call_static_fn};

void Gd__gd_core_items__Exclusive__DarkLantern::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_deathPrevented = gd::GdVal::from_bool(false);
    this->f_normalSprite = gd::GdVal::null();
    this->f_invuTimer = gd::GdVal::null();
    this->f_lanternLight = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__DarkLantern::meta() const { return &META_Gd__gd_core_items__Exclusive__DarkLantern; }
gd::GdVal Gd__gd_core_items__Exclusive__DarkLantern::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__DarkLantern::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__DarkLantern::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_deathPrevented_2191: out = this->f_deathPrevented; return true;
        case SYM_GEN_normalSprite_2192: out = this->f_normalSprite; return true;
        case SYM_GEN_invuTimer_2193: out = this->f_invuTimer; return true;
        case SYM_GEN_lanternLight_2194: out = this->f_lanternLight; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__DarkLantern::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_deathPrevented_2191: this->f_deathPrevented = val; return true;
        case SYM_GEN_normalSprite_2192: this->f_normalSprite = val; return true;
        case SYM_GEN_invuTimer_2193: this->f_invuTimer = val; return true;
        case SYM_GEN_lanternLight_2194: this->f_lanternLight = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__DarkLantern::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_canAffect_secondary_287: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onDamaged_1855: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_onReincarnate_2195: return true;
        case SYM_GEN_invuEnded_2196: return true;
        case SYM_GEN_onCombatEnd_132: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__DarkLantern::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_canAffect_secondary_287: out = fn_canAffect_secondary(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onDamaged_1855: out = fn_onDamaged(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onReincarnate_2195: out = fn_onReincarnate(args, argc); return true;
        case SYM_GEN_invuEnded_2196: out = fn_invuEnded(args, argc); return true;
        case SYM_GEN_onCombatEnd_132: out = fn_onCombatEnd(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__DarkLantern::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__DarkLantern::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(27LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DarkLantern::fn_canAffect_secondary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(25LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DarkLantern::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[142]), gd::GdVal::from_str(&battle_string_literals[143])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[162]), gd::GdVal::from_str(&battle_string_literals[163])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DarkLantern::fn_onDamaged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__damage = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(this->f_deathPrevented)) {
        return gd::GdVal::null();
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_le(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getCurrentHealth_1154, nullptr, 0), gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
        gd::GdVal lv_duration = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[138])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_duration}; return gd::native_inline_call(gd_ctx, this->f_invuTimer, SYM_GEN_start_1779, _ca, 1); })();
        (void)([&]() { gd::GdVal _ca[] = {lv_duration, gd::GdVal::from_obj(this), lv_event}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_makeInvulnerable_1211, _ca, 3); })();
        gd::GdVal lv_healAmount = gd::gd_round(gd::gd_mul(gd::gd_div(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0), gd::GdVal::from_float(100.0)), gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getMaxHealth_1160, nullptr, 0)));
        gd::GdVal lv_event2 = ([&]() { gd::GdVal _ca[] = {lv_healAmount, gd::GdVal::from_bool(false), gd::GdVal::from_obj(this), lv_event}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_reincarnate_1153, _ca, 4); })();
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DarkLantern::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::gd_div(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0), gd::GdVal::from_float(100.0)), gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getMaxHealth_1160, nullptr, 0)), gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_loseHealth_1157, _ca, 2); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DarkLantern::fn_onReincarnate(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_dam = gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMinDamage_156, nullptr, 0), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(27LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffected_type_429, _ca, 1); })());
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_dam, gd::GdVal::from_int(0LL))))) {
        gd::GdVal lv_damageRes = ([&]() { gd::GdVal _ca[] = {lv_dam, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealEffectDamage_221, _ca, 2); })();
    }
    gd::GdVal lv_numDebuffs = gd::gd_coerce_int(gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP5_267, nullptr, 0), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, _ca, 1); })()));
    (void)([&]() { gd::GdVal _ca[] = {lv_numDebuffs, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictRandomDebuffs_357, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DarkLantern::fn_invuEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DarkLantern::fn_onCombatEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, this->f_invuTimer, SYM_GEN_stop_1780, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DarkLantern::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_int(1000LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DarkLantern::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DarkLantern::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__deathPrevented = (_argc > 0) ? _args[0] : gd::GdVal::null();
    lv__deathPrevented = gd::gd_coerce_bool(lv__deathPrevented);
    this->f_deathPrevented = lv__deathPrevented;
    if (gd::gd_truth(this->f_deathPrevented)) {
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DarkLantern::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_invuTimer = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[164]), gd::GdVal::from_str(&battle_string_literals[165]), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_newItemTimer_135, _ca, 3); })();
    this->f_damageSource = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), gd::SYM_new, nullptr, 0), SYM_GEN_setItem_1550, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__DarkLantern(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__DarkLantern>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__DarkLantern = {CLS_Gd__gd_core_items__Exclusive__DarkLantern, "DarkLantern", "res://gd_core_items/Exclusive/DarkLantern.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__DarkLantern, &Gd__gd_core_items__Exclusive__DarkLantern::get_static_prop_fn, &Gd__gd_core_items__Exclusive__DarkLantern::call_static_fn};

void Gd__gd_core_items__Exclusive__DragonSet::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_dragonArmorDescr = gd::GdVal::null();
    this->f_dragonBootsDescr = gd::GdVal::null();
    this->f_dragonClawsDescr = gd::GdVal::null();
    this->f_armorDescr = gd::GdVal::null();
    this->f_bootsDescr = gd::GdVal::null();
    this->f_glovesDescr = gd::GdVal::null();
    this->f_heat = gd::GdVal::null();
    this->f_lifestealMax = gd::GdVal::null();
    this->f_activeLight1 = gd::GdVal::null();
    this->f_activeLight2 = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__DragonSet::meta() const { return &META_Gd__gd_core_items__Exclusive__DragonSet; }
gd::GdVal Gd__gd_core_items__Exclusive__DragonSet::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__DragonSet::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__DragonSet::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_dragonArmorDescr_2215: out = this->f_dragonArmorDescr; return true;
        case SYM_GEN_dragonBootsDescr_2216: out = this->f_dragonBootsDescr; return true;
        case SYM_GEN_dragonClawsDescr_2217: out = this->f_dragonClawsDescr; return true;
        case SYM_GEN_armorDescr_2218: out = this->f_armorDescr; return true;
        case SYM_GEN_bootsDescr_2219: out = this->f_bootsDescr; return true;
        case SYM_GEN_glovesDescr_2220: out = this->f_glovesDescr; return true;
        case SYM_GEN_heat_1896: out = this->f_heat; return true;
        case SYM_GEN_lifestealMax_2221: out = this->f_lifestealMax; return true;
        case SYM_GEN_activeLight1_2222: out = this->f_activeLight1; return true;
        case SYM_GEN_activeLight2_2223: out = this->f_activeLight2; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__DragonSet::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_dragonArmorDescr_2215: this->f_dragonArmorDescr = val; return true;
        case SYM_GEN_dragonBootsDescr_2216: this->f_dragonBootsDescr = val; return true;
        case SYM_GEN_dragonClawsDescr_2217: this->f_dragonClawsDescr = val; return true;
        case SYM_GEN_armorDescr_2218: this->f_armorDescr = val; return true;
        case SYM_GEN_bootsDescr_2219: this->f_bootsDescr = val; return true;
        case SYM_GEN_glovesDescr_2220: this->f_glovesDescr = val; return true;
        case SYM_GEN_heat_1896: this->f_heat = val; return true;
        case SYM_GEN_lifestealMax_2221: this->f_lifestealMax = val; return true;
        case SYM_GEN_activeLight1_2222: this->f_activeLight1 = val; return true;
        case SYM_GEN_activeLight2_2223: this->f_activeLight2 = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__DragonSet::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onItemAdded_437: return true;
        case SYM_GEN_onItemRemoved_438: return true;
        case SYM_GEN_onRemoveFromInventory_418: return true;
        case SYM_GEN_checkItems_2224: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_preCombatStart_124: return true;
        case SYM_GEN_onBattleRageStarted_2066: return true;
        case SYM_GEN_onBattleRageEnded_2067: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onOpponentDamaged_1992: return true;
        case SYM_GEN_onItemRoll_2018: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__DragonSet::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onItemAdded_437: out = fn_onItemAdded(args, argc); return true;
        case SYM_GEN_onItemRemoved_438: out = fn_onItemRemoved(args, argc); return true;
        case SYM_GEN_onRemoveFromInventory_418: out = fn_onRemoveFromInventory(args, argc); return true;
        case SYM_GEN_checkItems_2224: out = fn_checkItems(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_preCombatStart_124: out = fn_preCombatStart(args, argc); return true;
        case SYM_GEN_onBattleRageStarted_2066: out = fn_onBattleRageStarted(args, argc); return true;
        case SYM_GEN_onBattleRageEnded_2067: out = fn_onBattleRageEnded(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onOpponentDamaged_1992: out = fn_onOpponentDamaged(args, argc); return true;
        case SYM_GEN_onItemRoll_2018: out = fn_onItemRoll(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__DragonSet::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__DragonSet::fn_onItemAdded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_item}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_onItemAdded_437, _ca, 1, _out); return _out; })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_checkItems_2224, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DragonSet::fn_onItemRemoved(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_item}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_onItemRemoved_438, _ca, 1, _out); return _out; })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_checkItems_2224, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DragonSet::fn_onRemoveFromInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DragonSet::fn_checkItems(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(([&]() { gd::GdVal _ca[] = {this->f_dragonArmorDescr}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_countAllPlacedOfType_460, _ca, 1); })(), gd::GdVal::from_int(0LL))))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(([&]() { gd::GdVal _ca[] = {this->f_dragonBootsDescr}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_countAllPlacedOfType_460, _ca, 1); })(), gd::GdVal::from_int(0LL))))) {
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(([&]() { gd::GdVal _ca[] = {this->f_dragonClawsDescr}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_countAllPlacedOfType_460, _ca, 1); })(), gd::GdVal::from_int(0LL))))) {
                return gd::GdVal::null();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DragonSet::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[166]), gd::GdVal::from_str(&battle_string_literals[167])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[168]), gd::GdVal::from_str(&battle_string_literals[169])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(([&]() { gd::GdVal _ca[] = {this->f_dragonArmorDescr}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_countAllInInventoryOfType_804, _ca, 1); })(), gd::GdVal::from_int(0LL))))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(([&]() { gd::GdVal _ca[] = {this->f_dragonBootsDescr}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_countAllInInventoryOfType_804, _ca, 1); })(), gd::GdVal::from_int(0LL))))) {
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(([&]() { gd::GdVal _ca[] = {this->f_dragonClawsDescr}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_countAllInInventoryOfType_804, _ca, 1); })(), gd::GdVal::from_int(0LL))))) {
                (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[170]), gd::GdVal::from_str(&battle_string_literals[171])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DragonSet::fn_preCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN_preCombatStart_124, nullptr, 0, _out); return _out; })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_deactivateCooldown_99, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DragonSet::fn_onBattleRageStarted(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activateCooldown_98, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DragonSet::fn_onBattleRageEnded(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__event = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_deactivateCooldown_99, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DragonSet::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_heat}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_218, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DragonSet::fn_onOpponentDamaged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damageSource_24), SYM_GEN_canApplyLifesteal_1563, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        gd::GdVal lv_curLifesteal = gd::gd_min(gd::gd_mul(gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[172])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), gd::GdVal::from_float(100.0)), gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getHeat_1251, nullptr, 0)), this->f_lifestealMax);
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_ceil(gd::gd_mul(lv_curLifesteal, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518))), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DragonSet::fn_onItemRoll(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__DragonSet::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_dragonArmorDescr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[173])}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })();
    this->f_dragonBootsDescr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[174])}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })();
    this->f_dragonClawsDescr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[175])}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })();
    this->f_armorDescr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[176])}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })();
    this->f_bootsDescr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[177])}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })();
    this->f_glovesDescr = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[178])}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })();
    this->f_heat = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[179])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_lifestealMax = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[180])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__DragonSet(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__DragonSet>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__DragonSet = {CLS_Gd__gd_core_items__Exclusive__DragonSet, "DragonSet", "res://gd_core_items/Exclusive/DragonSet.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__DragonSet, &Gd__gd_core_items__Exclusive__DragonSet::get_static_prop_fn, &Gd__gd_core_items__Exclusive__DragonSet::call_static_fn};

void Gd__gd_core_items__Exclusive__EvilHat::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_selfBuffs = gd::GdVal::null();
    this->f_opponentBuffs = gd::GdVal::null();
    this->f_regen = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__EvilHat::meta() const { return &META_Gd__gd_core_items__Exclusive__EvilHat; }
gd::GdVal Gd__gd_core_items__Exclusive__EvilHat::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__EvilHat::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__EvilHat::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_selfBuffs_2251: out = this->f_selfBuffs; return true;
        case SYM_GEN_opponentBuffs_2252: out = this->f_opponentBuffs; return true;
        case SYM_GEN_regen_1999: out = this->f_regen; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__EvilHat::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_selfBuffs_2251: this->f_selfBuffs = val; return true;
        case SYM_GEN_opponentBuffs_2252: this->f_opponentBuffs = val; return true;
        case SYM_GEN_regen_1999: this->f_regen = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__EvilHat::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_canAffect_secondary_287: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onDebuffsChanged_1828: return true;
        case SYM_GEN_onOpponentBuffsChanged_2132: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_playPickupSound_736: return true;
        case SYM_GEN_playDropSound_149: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__EvilHat::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_canAffect_secondary_287: out = fn_canAffect_secondary(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onDebuffsChanged_1828: out = fn_onDebuffsChanged(args, argc); return true;
        case SYM_GEN_onOpponentBuffsChanged_2132: out = fn_onOpponentBuffsChanged(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_playPickupSound_736: out = fn_playPickupSound(args, argc); return true;
        case SYM_GEN_playDropSound_149: out = fn_playDropSound(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__EvilHat::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__EvilHat::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canDamage_89, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__EvilHat::fn_canAffect_secondary(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(25LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__EvilHat::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_unhealing = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[181])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    lv_unhealing = gd::gd_add(gd_ctx, lv_unhealing, gd::gd_div(gd_ctx, gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, _ca, 1); })(), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[182])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })()), gd::GdVal::from_float(100.0)));
    (void)([&]() { gd::GdVal _ca[] = {lv_unhealing}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_giveUnhealing_1178, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[183])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectToCharacterDebuffs_375, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[184])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectToOpponentBuffs_377, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__EvilHat::fn_onDebuffsChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_is_type(gd::get_prop(gd_ctx, lv_event, SYM_GEN_origin_1546), &META_Gd__gd_core_items__Item)))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, lv_event, SYM_GEN_origin_1546), SYM_GEN_character_74, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0))))) : gd::GdVal::from_bool(false)))) {
        gd::GdVal lv_regenToGive = gd::GdVal::from_int(0LL);
        {
            gd::GdVal _t497 = gd::gd_iter_seq(gd_ctx.arena, lv_amount);
            gd::GdArr* _t498 = (_t497.kind == gd::GdVal::Kind::Arr) ? _t497.arr : nullptr;
            uint32_t _len__t499 = _t498 ? _t498->len : 0u;
            for (uint32_t _t499 = 0; _t499 < _len__t499; ++_t499) {
                gd::GdVal lv_i = _t498->data[_t499];
                if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_173, nullptr, 0))) {
                    lv_regenToGive = gd::gd_add(gd_ctx, lv_regenToGive, this->f_regen);
                }
            }
        }
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_regenToGive, gd::GdVal::from_int(0LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {lv_regenToGive, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_214, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__EvilHat::fn_onOpponentBuffsChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_amount, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_is_type(gd::get_prop(gd_ctx, lv_event, SYM_GEN_origin_1546), &META_Gd__gd_core_items__Item)))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, lv_event, SYM_GEN_origin_1546), SYM_GEN_character_74, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0))))) : gd::GdVal::from_bool(false)))) {
        {
            gd::GdVal _t500 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
            gd::GdArr* _t501 = (_t500.kind == gd::GdVal::Kind::Arr) ? _t500.arr : nullptr;
            uint32_t _len__t502 = _t501 ? _t501->len : 0u;
            for (uint32_t _t502 = 0; _t502 < _len__t502; ++_t502) {
                gd::GdVal lv_item = _t501->data[_t502];
                (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance2_172, nullptr, 0), gd::gd_neg(lv_amount))}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addCritChancePercent_179, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__EvilHat::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_selfBuffs}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRandomBuffs_369, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_opponentBuffs, gd::GdVal::null(), gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1390, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRandomBuffs_369, _ca, 4); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__EvilHat::fn_playPickupSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__EvilHat::fn_playDropSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_volume = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    lv_volume = gd::gd_add(gd_ctx, lv_volume, this->f_impactSoundVolume);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__EvilHat::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_selfBuffs = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[185])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_opponentBuffs = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[186])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[161])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__EvilHat(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__EvilHat>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__EvilHat = {CLS_Gd__gd_core_items__Exclusive__EvilHat, "EvilHat", "res://gd_core_items/Exclusive/EvilHat.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__EvilHat, &Gd__gd_core_items__Exclusive__EvilHat::get_static_prop_fn, &Gd__gd_core_items__Exclusive__EvilHat::call_static_fn};

void Gd__gd_core_items__Exclusive__Toad::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_affectedItemsDict = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_gainedBuffs = gd::GdVal::from_int(0);
    this->f_usedBuffs = gd::GdVal::from_int(0);
    this->f_gainedThreshold = gd::GdVal::null();
    this->f_usedThreshold = gd::GdVal::null();
    this->f_luck = gd::GdVal::null();
    this->f_mana = gd::GdVal::null();
    this->f_luck2 = gd::GdVal::null();
    this->f_mana2 = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Toad::meta() const { return &META_Gd__gd_core_items__Exclusive__Toad; }
gd::GdVal Gd__gd_core_items__Exclusive__Toad::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Toad::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Toad::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_affectedItemsDict_2109: out = this->f_affectedItemsDict; return true;
        case SYM_GEN_gainedBuffs_2268: out = this->f_gainedBuffs; return true;
        case SYM_GEN_usedBuffs_2269: out = this->f_usedBuffs; return true;
        case SYM_GEN_gainedThreshold_2270: out = this->f_gainedThreshold; return true;
        case SYM_GEN_usedThreshold_2271: out = this->f_usedThreshold; return true;
        case SYM_GEN_luck_897: out = this->f_luck; return true;
        case SYM_GEN_mana_1928: out = this->f_mana; return true;
        case SYM_GEN_luck2_2272: out = this->f_luck2; return true;
        case SYM_GEN_mana2_2273: out = this->f_mana2; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Toad::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_affectedItemsDict_2109: this->f_affectedItemsDict = val; return true;
        case SYM_GEN_gainedBuffs_2268: this->f_gainedBuffs = gd::gd_coerce_int(val); return true;
        case SYM_GEN_usedBuffs_2269: this->f_usedBuffs = gd::gd_coerce_int(val); return true;
        case SYM_GEN_gainedThreshold_2270: this->f_gainedThreshold = val; return true;
        case SYM_GEN_usedThreshold_2271: this->f_usedThreshold = val; return true;
        case SYM_GEN_luck_897: this->f_luck = val; return true;
        case SYM_GEN_mana_1928: this->f_mana = val; return true;
        case SYM_GEN_luck2_2272: this->f_luck2 = val; return true;
        case SYM_GEN_mana2_2273: this->f_mana2 = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Toad::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onGainThresholdReached_2274: return true;
        case SYM_GEN_onUseThresholdReached_2275: return true;
        case SYM_GEN_onBuffsChanged_2087: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_playPickupSound_736: return true;
        case SYM_GEN_playDropSound_149: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Toad::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onGainThresholdReached_2274: out = fn_onGainThresholdReached(args, argc); return true;
        case SYM_GEN_onUseThresholdReached_2275: out = fn_onUseThresholdReached(args, argc); return true;
        case SYM_GEN_onBuffsChanged_2087: out = fn_onBuffsChanged(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_playPickupSound_736: out = fn_playPickupSound(args, argc); return true;
        case SYM_GEN_playDropSound_149: out = fn_playDropSound(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Toad::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Toad::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_gainsBuffs_296, nullptr, 0)) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_usesBuffs_297, nullptr, 0))));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Toad::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_affectedItemsDict = ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_arrayAsIndexDict_1799, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[187])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectToCharacterBuffs_374, _ca, 1); })();
    this->f_gainedBuffs = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    this->f_usedBuffs = gd::gd_coerce_int(gd::GdVal::from_int(0LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Toad::fn_onGainThresholdReached(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_ticks = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_ticks, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[151])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })()), lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, _ca, 2); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Toad::fn_onUseThresholdReached(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_ticks = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_ticks, this->f_luck), lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_215, _ca, 2); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(lv_ticks, this->f_mana), lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_216, _ca, 2); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Toad::fn_onBuffsChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::gd_in(gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_getOrigin_1580, nullptr, 0), this->f_affectedItemsDict))) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
            this->f_gainedBuffs = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_gainedBuffs, lv_amount));
            gd::GdVal lv_ticks = gd::gd_div(gd_ctx, this->f_gainedBuffs, this->f_gainedThreshold);
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_ticks, gd::GdVal::from_int(0LL))))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_ticks, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onGainThresholdReached_2274, _ca, 2); })();
                this->f_gainedBuffs = gd::gd_coerce_int(gd::gd_mod(gd_ctx, this->f_gainedBuffs, this->f_gainedThreshold));
            }
        }
        else {
            this->f_usedBuffs = gd::gd_coerce_int(gd::gd_add(gd_ctx, this->f_usedBuffs, gd::gd_coerce_int(gd::gd_abs(lv_amount))));
            gd::GdVal lv_ticks = gd::gd_div(gd_ctx, this->f_usedBuffs, this->f_usedThreshold);
            if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_ticks, gd::GdVal::from_int(0LL))))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_ticks, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onUseThresholdReached_2275, _ca, 2); })();
                this->f_usedBuffs = gd::gd_coerce_int(gd::gd_mod(gd_ctx, this->f_usedBuffs, this->f_usedThreshold));
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Toad::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_luck2}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveLucky_215, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {this->f_mana2}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_216, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Toad::fn_playPickupSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Toad::fn_playDropSound(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_volume = (_argc > 0) ? _args[0] : (gd::GdVal::from_int(0LL));
    lv_volume = gd::gd_add(gd_ctx, lv_volume, this->f_impactSoundVolume);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.9), gd::GdVal::from_float(1.1)}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_rng_1406), gd::SYM_randf_range, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Toad::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_gainedThreshold = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[188])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_usedThreshold = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[150])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_luck = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[159])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_mana = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[189])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_luck2 = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[190])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_mana2 = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[191])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Toad(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Toad>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Toad = {CLS_Gd__gd_core_items__Exclusive__Toad, "Toad", "res://gd_core_items/Exclusive/Toad.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Toad, &Gd__gd_core_items__Exclusive__Toad::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Toad::call_static_fn};

void Gd__gd_core_items__Exclusive__HawkRune::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Gems__Gem::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__HawkRune::meta() const { return &META_Gd__gd_core_items__Exclusive__HawkRune; }
gd::GdVal Gd__gd_core_items__Exclusive__HawkRune::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_gemColor_995: return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_float(0.267323), gd::GdVal::from_float(0.624508), gd::GdVal::from_float(0.970703)}; return gd::make_color_from_args(_ca, 3); })();
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__HawkRune::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__HawkRune::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_gemColor_995: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__HawkRune::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Gems__Gem::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__HawkRune::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_prepareWeapon_982: return true;
        case SYM_GEN_prepareArmor_983: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onHotSwapHoverWithGemEnd_992: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__HawkRune::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_prepareWeapon_982: out = fn_prepareWeapon(args, argc); return true;
        case SYM_GEN_prepareArmor_983: out = fn_prepareArmor(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onHotSwapHoverWithGemEnd_992: out = fn_onHotSwapHoverWithGemEnd(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__HawkRune::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Gems__Gem::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__HawkRune::fn_prepareWeapon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[192])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItem_389, nullptr, 0), SYM_GEN_addCritChancePercent_179, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[193])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0))}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItem_389, nullptr, 0), SYM_GEN_addCritSeverity_185, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HawkRune::fn_prepareArmor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(109LL), gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemPower_973, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0))}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeResistChance_1026, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HawkRune::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictBlind_213, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HawkRune::fn_onHotSwapHoverWithGemEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__HawkRune::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__HawkRune(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__HawkRune>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__HawkRune = {CLS_Gd__gd_core_items__Exclusive__HawkRune, "HawkRune", "res://gd_core_items/Exclusive/HawkRune.gd", &META_Gd__gd_core_items__Gems__Gem, true, _alloc_Gd__gd_core_items__Exclusive__HawkRune, &Gd__gd_core_items__Exclusive__HawkRune::get_static_prop_fn, &Gd__gd_core_items__Exclusive__HawkRune::call_static_fn};

void Gd__gd_core_items__Exclusive__InvestmentOpportunity::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_affectedItemsDict = gd::GdVal::from_dict(gd::GdDict::create(gd_ctx.arena));
    this->f_healthAcc = gd::GdVal::from_float(0.0);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__InvestmentOpportunity::meta() const { return &META_Gd__gd_core_items__Exclusive__InvestmentOpportunity; }
gd::GdVal Gd__gd_core_items__Exclusive__InvestmentOpportunity::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__InvestmentOpportunity::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__InvestmentOpportunity::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_affectedItemsDict_2109: out = this->f_affectedItemsDict; return true;
        case SYM_GEN_healthAcc_2324: out = this->f_healthAcc; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__InvestmentOpportunity::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_affectedItemsDict_2109: this->f_affectedItemsDict = val; return true;
        case SYM_GEN_healthAcc_2324: this->f_healthAcc = gd::gd_coerce_float(val); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__InvestmentOpportunity::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onBuffChanged_2006: return true;
        case SYM_GEN_getShopPriority_853: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__InvestmentOpportunity::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onBuffChanged_2006: out = fn_onBuffChanged(args, argc); return true;
        case SYM_GEN_getShopPriority_853: out = fn_getShopPriority(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__InvestmentOpportunity::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__InvestmentOpportunity::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveGold_754, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__InvestmentOpportunity::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_usesBuffs_297, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__InvestmentOpportunity::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_healthAcc = gd::gd_coerce_float(gd::GdVal::from_int(0LL));
    (void)gd::native_inline_call(gd_ctx, this->f_affectedItemsDict, gd::SYM_clear, nullptr, 0);
    {
        gd::GdVal _t503 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t504 = (_t503.kind == gd::GdVal::Kind::Arr) ? _t503.arr : nullptr;
        uint32_t _len__t505 = _t504 ? _t504->len : 0u;
        for (uint32_t _t505 = 0; _t505 < _len__t505; ++_t505) {
            gd::GdVal lv_item = _t504->data[_t505];
            { gd::GdVal _t506 = this->f_affectedItemsDict; gd::GdVal _t507 = lv_item; gd::native_array_set_index(gd_ctx, _t506, _t507, gd::GdVal::from_bool(true)); }
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[153])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectToCharacterBuffs_374, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__InvestmentOpportunity::fn_onBuffChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::gd_in(gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_getOrigin_1580, nullptr, 0), this->f_affectedItemsDict))) {
        if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_amount, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[150]), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_getParam_1575, _ca, 2); })())) : gd::GdVal::from_bool(false)))) {
            this->f_healthAcc = gd::gd_coerce_float(gd::gd_add(gd_ctx, this->f_healthAcc, gd::gd_mul(gd::gd_abs(lv_amount), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[194])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })())));
            gd::GdVal lv_health = gd::gd_round(this->f_healthAcc);
            this->f_healthAcc = gd::gd_coerce_float(gd::gd_sub(this->f_healthAcc, lv_health));
            (void)([&]() { gd::GdVal _ca[] = {lv_health, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_317, _ca, 2); })();
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__InvestmentOpportunity::fn_getShopPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_int(-10000LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__InvestmentOpportunity::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__InvestmentOpportunity(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__InvestmentOpportunity>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__InvestmentOpportunity = {CLS_Gd__gd_core_items__Exclusive__InvestmentOpportunity, "InvestmentOpportunity", "res://gd_core_items/Exclusive/InvestmentOpportunity.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__InvestmentOpportunity, &Gd__gd_core_items__Exclusive__InvestmentOpportunity::get_static_prop_fn, &Gd__gd_core_items__Exclusive__InvestmentOpportunity::call_static_fn};

void Gd__gd_core_items__Exclusive__LittleMimic::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_numBuffs = gd::GdVal::null();
    this->f_speedPerGold = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__LittleMimic::meta() const { return &META_Gd__gd_core_items__Exclusive__LittleMimic; }
gd::GdVal Gd__gd_core_items__Exclusive__LittleMimic::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__LittleMimic::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__LittleMimic::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_numBuffs_2005: out = this->f_numBuffs; return true;
        case SYM_GEN_speedPerGold_2350: out = this->f_speedPerGold; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__LittleMimic::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_numBuffs_2005: this->f_numBuffs = val; return true;
        case SYM_GEN_speedPerGold_2350: this->f_speedPerGold = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__LittleMimic::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_getCounterValue_2351: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onCalcTradeChance_1825: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__LittleMimic::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_getCounterValue_2351: out = fn_getCounterValue(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onCalcTradeChance_1825: out = fn_onCalcTradeChance(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__LittleMimic::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__LittleMimic::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LittleMimic::fn_getCounterValue(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_gold = gd::GdVal::from_int(0LL);
    if (gd::gd_truth(this->f_placed)) {
        {
            gd::GdVal _t508 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
            gd::GdArr* _t509 = (_t508.kind == gd::GdVal::Kind::Arr) ? _t508.arr : nullptr;
            uint32_t _len__t510 = _t509 ? _t509->len : 0u;
            for (uint32_t _t510 = 0; _t510 < _len__t510; ++_t510) {
                gd::GdVal lv_item = _t509->data[_t510];
                lv_gold = gd::gd_add(gd_ctx, lv_gold, gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_getPrice_392, nullptr, 0));
            }
        }
    }
    else {
        {
            gd::GdVal _t511 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_nocache_421, nullptr, 0));
            gd::GdArr* _t512 = (_t511.kind == gd::GdVal::Kind::Arr) ? _t511.arr : nullptr;
            uint32_t _len__t513 = _t512 ? _t512->len : 0u;
            for (uint32_t _t513 = 0; _t513 < _len__t513; ++_t513) {
                gd::GdVal lv_item = _t512->data[_t513];
                lv_gold = gd::gd_add(gd_ctx, lv_gold, gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_getPrice_392, nullptr, 0));
            }
        }
    }
    return lv_gold;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LittleMimic::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getCounterValue_2351, nullptr, 0), this->f_speedPerGold)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LittleMimic::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_numBuffs}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMostBuffs_367, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LittleMimic::fn_onCalcTradeChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__LittleMimic::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_numBuffs = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[185])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_speedPerGold = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[154])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__LittleMimic(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__LittleMimic>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__LittleMimic = {CLS_Gd__gd_core_items__Exclusive__LittleMimic, "LittleMimic", "res://gd_core_items/Exclusive/LittleMimic.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__LittleMimic, &Gd__gd_core_items__Exclusive__LittleMimic::get_static_prop_fn, &Gd__gd_core_items__Exclusive__LittleMimic::call_static_fn};

void Gd__gd_core_items__Exclusive__MechaBat::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_lifestealActive = gd::GdVal::from_bool(false);
    this->f_lifestealParticles = gd::GdVal::null();
    this->f_lifestealLight = gd::GdVal::null();
    this->f_vampirism1 = gd::GdVal::null();
    this->f_luckNeeded = gd::GdVal::null();
    this->f_luckUsed = gd::GdVal::null();
    this->f_vampirism2 = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__MechaBat::meta() const { return &META_Gd__gd_core_items__Exclusive__MechaBat; }
gd::GdVal Gd__gd_core_items__Exclusive__MechaBat::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__MechaBat::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__MechaBat::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_lifestealActive_2397: out = this->f_lifestealActive; return true;
        case SYM_GEN_lifestealParticles_2398: out = this->f_lifestealParticles; return true;
        case SYM_GEN_lifestealLight_2399: out = this->f_lifestealLight; return true;
        case SYM_GEN_vampirism1_2400: out = this->f_vampirism1; return true;
        case SYM_GEN_luckNeeded_1874: out = this->f_luckNeeded; return true;
        case SYM_GEN_luckUsed_2401: out = this->f_luckUsed; return true;
        case SYM_GEN_vampirism2_2402: out = this->f_vampirism2; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__MechaBat::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_lifestealActive_2397: this->f_lifestealActive = val; return true;
        case SYM_GEN_lifestealParticles_2398: this->f_lifestealParticles = val; return true;
        case SYM_GEN_lifestealLight_2399: this->f_lifestealLight = val; return true;
        case SYM_GEN_vampirism1_2400: this->f_vampirism1 = val; return true;
        case SYM_GEN_luckNeeded_1874: this->f_luckNeeded = val; return true;
        case SYM_GEN_luckUsed_2401: this->f_luckUsed = val; return true;
        case SYM_GEN_vampirism2_2402: this->f_vampirism2 = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__MechaBat::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onOpponentDamaged_1992: return true;
        case SYM_GEN_onChargeReceived_2129: return true;
        case SYM_GEN_onChargeLeft_2130: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_onStateChanged_383: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__MechaBat::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onOpponentDamaged_1992: out = fn_onOpponentDamaged(args, argc); return true;
        case SYM_GEN_onChargeReceived_2129: out = fn_onChargeReceived(args, argc); return true;
        case SYM_GEN_onChargeLeft_2130: out = fn_onChargeLeft(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_onStateChanged_383: out = fn_onStateChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__MechaBat::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__MechaBat::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canDamage_89, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MechaBat::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_numVamp = gd::GdVal::from_int(0LL);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getLucky_1237, nullptr, 0), this->f_luckNeeded)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_luckUsed}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useLucky_350, _ca, 1); })();
        lv_numVamp = gd::gd_add(gd_ctx, lv_numVamp, this->f_vampirism2);
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_116, nullptr, 0), gd::GdVal::from_int(0LL))))) {
        lv_numVamp = gd::gd_add(gd_ctx, lv_numVamp, this->f_vampirism1);
    }
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_numVamp, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_numVamp}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_210, _ca, 1); })();
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MechaBat::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[170]), gd::GdVal::from_str(&battle_string_literals[171])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MechaBat::fn_onOpponentDamaged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(this->f_lifestealActive)) {
        if (gd::gd_truth((gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damageSource_24), SYM_GEN_canApplyLifesteal_1563, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
            if (gd::gd_truth(gd::gd_in(gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damageSource_24), SYM_GEN_origin_1546), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0)))) {
                (void)([&]() { gd::GdVal _ca[] = {gd::gd_ceil(gd::gd_div(gd_ctx, gd::gd_mul(gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[172])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })()), gd::GdVal::from_float(100.0))), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, _ca, 2); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MechaBat::fn_onChargeReceived(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__charge = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_numCharges, gd::GdVal::from_int(1LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MechaBat::fn_onChargeLeft(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__charge = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(this->f_numCharges, gd::GdVal::from_int(0LL))))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_setState_382, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MechaBat::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_onStateChanged_383, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MechaBat::fn_onStateChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__lifestealActive = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_lifestealActive = lv__lifestealActive;
    if (gd::gd_truth(this->f_lifestealActive)) {
    }
    else {
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__MechaBat::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_vampirism1 = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[195])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_luckNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[160])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_luckUsed = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[159])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_vampirism2 = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[196])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__MechaBat(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__MechaBat>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__MechaBat = {CLS_Gd__gd_core_items__Exclusive__MechaBat, "MechaBat", "res://gd_core_items/Exclusive/MechaBat.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__MechaBat, &Gd__gd_core_items__Exclusive__MechaBat::get_static_prop_fn, &Gd__gd_core_items__Exclusive__MechaBat::call_static_fn};

void Gd__gd_core_items__Exclusive__OnionCutter::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_foodSpeed = gd::GdVal::null();
    this->f_damFactor = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__OnionCutter::meta() const { return &META_Gd__gd_core_items__Exclusive__OnionCutter; }
gd::GdVal Gd__gd_core_items__Exclusive__OnionCutter::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__OnionCutter::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__OnionCutter::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_foodSpeed_2028: out = this->f_foodSpeed; return true;
        case SYM_GEN_damFactor_1895: out = this->f_damFactor; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__OnionCutter::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_foodSpeed_2028: this->f_foodSpeed = val; return true;
        case SYM_GEN_damFactor_1895: this->f_damFactor = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__OnionCutter::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__OnionCutter::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__OnionCutter::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__OnionCutter::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(2LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__OnionCutter::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_foodSpeed, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__OnionCutter::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(this->f_damFactor)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_opponent_75, nullptr, 0), SYM_GEN_changeDamageResistance_1279, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__OnionCutter::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_foodSpeed = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[154])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_damFactor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[197])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__OnionCutter(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__OnionCutter>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__OnionCutter = {CLS_Gd__gd_core_items__Exclusive__OnionCutter, "OnionCutter", "res://gd_core_items/Exclusive/OnionCutter.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__OnionCutter, &Gd__gd_core_items__Exclusive__OnionCutter::get_static_prop_fn, &Gd__gd_core_items__Exclusive__OnionCutter::call_static_fn};

void Gd__gd_core_items__Exclusive__PortableAltar::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Bag::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__PortableAltar::meta() const { return &META_Gd__gd_core_items__Exclusive__PortableAltar; }
gd::GdVal Gd__gd_core_items__Exclusive__PortableAltar::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_valueFactor_2434: return gd::GdVal::from_float(1.0);
        default: break;
    }
    return Gd__gd_core_items__Bag::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__PortableAltar::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__PortableAltar::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_valueFactor_2434: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__PortableAltar::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Bag::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__PortableAltar::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canLockBag_820: return true;
        case SYM_GEN_showBagBorderForItem_919: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_onRecipesUpdated_2435: return true;
        case SYM_GEN_readyToFuse_751: return true;
        case SYM_GEN_onFusingFinished_848: return true;
        case SYM_GEN_getCounterValue_2351: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__PortableAltar::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canLockBag_820: out = fn_canLockBag(args, argc); return true;
        case SYM_GEN_showBagBorderForItem_919: out = fn_showBagBorderForItem(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onRecipesUpdated_2435: out = fn_onRecipesUpdated(args, argc); return true;
        case SYM_GEN_readyToFuse_751: out = fn_readyToFuse(args, argc); return true;
        case SYM_GEN_onFusingFinished_848: out = fn_onFusingFinished(args, argc); return true;
        case SYM_GEN_getCounterValue_2351: out = fn_getCounterValue(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Bag::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__PortableAltar::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Bag::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__PortableAltar::fn_canLockBag(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PortableAltar::fn_showBagBorderForItem(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::from_bool(!gd::gd_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_isBag_83, nullptr, 0)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PortableAltar::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[198])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })()}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveEmpower_217, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PortableAltar::fn_onRecipesUpdated(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(this->f_ownerType, gd::GdVal::from_int(1LL))))) {
        return gd::GdVal::null();
    }
    if (gd::gd_truth(this->f_fusing)) {
        return gd::GdVal::null();
    }
    if (gd::gd_truth((gd::gd_truth(this->f_locked) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(!gd::gd_truth(this->f_placed))))))) {
        {
            gd::GdVal _t514 = gd::gd_iter_seq(gd_ctx.arena, this->f_bondedIngredients);
            gd::GdArr* _t515 = (_t514.kind == gd::GdVal::Kind::Arr) ? _t514.arr : nullptr;
            uint32_t _len__t516 = _t515 ? _t515->len : 0u;
            for (uint32_t _t516 = 0; _t516 < _len__t516; ++_t516) {
                gd::GdVal lv_bonded = _t515->data[_t516];
                (void)gd::native_inline_call(gd_ctx, lv_bonded, SYM_GEN_removeBondedBaseItem_810, nullptr, 0);
            }
        }
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeAllIngredients_812, nullptr, 0);
        return gd::GdVal::null();
    }
    {
        gd::GdVal _t517 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getItemsInside_924, nullptr, 0));
        gd::GdArr* _t518 = (_t517.kind == gd::GdVal::Kind::Arr) ? _t517.arr : nullptr;
        uint32_t _len__t519 = _t518 ? _t518->len : 0u;
        for (uint32_t _t519 = 0; _t519 < _len__t519; ++_t519) {
            gd::GdVal lv_item = _t518->data[_t519];
            if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canStartNewRecipe_807, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_createBondVisual_839, _ca, 1); })();
                (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_updateBondVisuals_840, nullptr, 0);
                (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addToBaseItem_815, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PortableAltar::fn_readyToFuse(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(!gd::gd_truth(gd::native_inline_call(gd_ctx, this->f_bondedIngredients, gd::SYM_empty, nullptr, 0)));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PortableAltar::fn_onFusingFinished(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_validBonds = (_argc > 0) ? _args[0] : gd::GdVal::null();
    (void)([&]() { gd::GdVal _ca[] = {lv_validBonds}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Bag::call_method(gd_ctx, SYM_GEN_onFusingFinished_848, _ca, 1, _out); return _out; })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PortableAltar::fn_getCounterValue(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_gold = gd::GdVal::from_int(0LL);
    {
        gd::GdVal _t520 = gd::gd_iter_seq(gd_ctx.arena, this->f_bondedIngredients);
        gd::GdArr* _t521 = (_t520.kind == gd::GdVal::Kind::Arr) ? _t520.arr : nullptr;
        uint32_t _len__t522 = _t521 ? _t521->len : 0u;
        for (uint32_t _t522 = 0; _t522 < _len__t522; ++_t522) {
            gd::GdVal lv_item = _t521->data[_t522];
            lv_gold = gd::gd_add(gd_ctx, lv_gold, gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_getPrice_392, nullptr, 0));
        }
    }
    return lv_gold;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__PortableAltar::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Bag::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__PortableAltar(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__PortableAltar>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__PortableAltar = {CLS_Gd__gd_core_items__Exclusive__PortableAltar, "PortableAltar", "res://gd_core_items/Exclusive/PortableAltar.gd", &META_Gd__gd_core_items__Bag, true, _alloc_Gd__gd_core_items__Exclusive__PortableAltar, &Gd__gd_core_items__Exclusive__PortableAltar::get_static_prop_fn, &Gd__gd_core_items__Exclusive__PortableAltar::call_static_fn};

void Gd__gd_core_items__Exclusive__RainbowGoobertMage::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Goobert::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__RainbowGoobertMage::meta() const { return &META_Gd__gd_core_items__Exclusive__RainbowGoobertMage; }
gd::GdVal Gd__gd_core_items__Exclusive__RainbowGoobertMage::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Goobert::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__RainbowGoobertMage::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__RainbowGoobertMage::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Goobert::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__RainbowGoobertMage::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Goobert::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__RainbowGoobertMage::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__RainbowGoobertMage::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Goobert::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__RainbowGoobertMage::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Goobert::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowGoobertMage::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, nullptr, 0);
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_210, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_266, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMostBuffs_367, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP5_267, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_inflictBlind_213, _ca, 1); })();
    {
        gd::GdVal _t523 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t524 = (_t523.kind == gd::GdVal::Kind::Arr) ? _t523.arr : nullptr;
        uint32_t _len__t525 = _t524 ? _t524->len : 0u;
        for (uint32_t _t525 = 0; _t525 < _len__t525; ++_t525) {
            gd::GdVal lv_item = _t524->data[_t525];
            if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_90, nullptr, 0))) {
                (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP6_268, nullptr, 0)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addBonusDamage_161, _ca, 1); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__RainbowGoobertMage::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Goobert::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__RainbowGoobertMage(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__RainbowGoobertMage>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__RainbowGoobertMage = {CLS_Gd__gd_core_items__Exclusive__RainbowGoobertMage, "RainbowGoobertMage", "res://gd_core_items/Exclusive/RainbowGoobertMage.gd", &META_Gd__gd_core_items__Goobert, true, _alloc_Gd__gd_core_items__Exclusive__RainbowGoobertMage, &Gd__gd_core_items__Exclusive__RainbowGoobertMage::get_static_prop_fn, &Gd__gd_core_items__Exclusive__RainbowGoobertMage::call_static_fn};

void Gd__gd_core_items__Exclusive__SapphireWhelp::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
    this->f_stackTypes = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__SapphireWhelp::meta() const { return &META_Gd__gd_core_items__Exclusive__SapphireWhelp; }
gd::GdVal Gd__gd_core_items__Exclusive__SapphireWhelp::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__SapphireWhelp::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__SapphireWhelp::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_stackTypes_1926: out = this->f_stackTypes; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__SapphireWhelp::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_stackTypes_1926: this->f_stackTypes = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__SapphireWhelp::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_onPreDealDamage_early_945: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__SapphireWhelp::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onPreDealDamage_early_945: out = fn_onPreDealDamage_early(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__SapphireWhelp::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__SapphireWhelp::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_216, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SapphireWhelp::fn_onPreDealDamage_early(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_tryUseMana_333, _ca, 1); })();
        if (gd::gd_truth(lv_event)) {
            (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_204, nullptr, 0), gd::GdVal::from_bool(true), lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, _ca, 3); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL), lv_event, this->f_stackTypes}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRandomBuffs_369, _ca, 3); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SapphireWhelp::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_stackTypes = gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_getBuffs_1390, nullptr, 0);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(105LL)}; return gd::native_inline_call(gd_ctx, this->f_stackTypes, gd::SYM_erase, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__SapphireWhelp(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__SapphireWhelp>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SapphireWhelp = {CLS_Gd__gd_core_items__Exclusive__SapphireWhelp, "SapphireWhelp", "res://gd_core_items/Exclusive/SapphireWhelp.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__Exclusive__SapphireWhelp, &Gd__gd_core_items__Exclusive__SapphireWhelp::get_static_prop_fn, &Gd__gd_core_items__Exclusive__SapphireWhelp::call_static_fn};

void Gd__gd_core_items__Exclusive__SliceofToast::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Food::init_fields(gd_ctx);
    this->f_staminaThreshold = gd::GdVal::null();
    this->f_stamina = gd::GdVal::null();
    this->f_regen = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__SliceofToast::meta() const { return &META_Gd__gd_core_items__Exclusive__SliceofToast; }
gd::GdVal Gd__gd_core_items__Exclusive__SliceofToast::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Food::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__SliceofToast::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__SliceofToast::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_staminaThreshold_2075: out = this->f_staminaThreshold; return true;
        case SYM_GEN_stamina_2156: out = this->f_stamina; return true;
        case SYM_GEN_regen_1999: out = this->f_regen; return true;
        default: break;
    }
    return Gd__gd_core_items__Food::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__SliceofToast::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_staminaThreshold_2075: this->f_staminaThreshold = val; return true;
        case SYM_GEN_stamina_2156: this->f_stamina = val; return true;
        case SYM_GEN_regen_1999: this->f_regen = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Food::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__SliceofToast::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Food::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__SliceofToast::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Food::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__SliceofToast::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Food::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__SliceofToast::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getCurrentStamina_1262, nullptr, 0), this->f_staminaThreshold)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_stamina}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStamina_318, _ca, 1); })();
    }
    else {
        (void)([&]() { gd::GdVal _ca[] = {this->f_regen}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_214, _ca, 1); })();
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SliceofToast::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Food::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_staminaThreshold = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[199])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_stamina = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[16])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_regen = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[161])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__SliceofToast(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__SliceofToast>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SliceofToast = {CLS_Gd__gd_core_items__Exclusive__SliceofToast, "SliceofToast", "res://gd_core_items/Exclusive/SliceofToast.gd", &META_Gd__gd_core_items__Food, true, _alloc_Gd__gd_core_items__Exclusive__SliceofToast, &Gd__gd_core_items__Exclusive__SliceofToast::get_static_prop_fn, &Gd__gd_core_items__Exclusive__SliceofToast::call_static_fn};

void Gd__gd_core_items__Exclusive__SpellScrollLight::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_speedBonus = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__SpellScrollLight::meta() const { return &META_Gd__gd_core_items__Exclusive__SpellScrollLight; }
gd::GdVal Gd__gd_core_items__Exclusive__SpellScrollLight::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__SpellScrollLight::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__SpellScrollLight::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_speedBonus_1877: out = this->f_speedBonus; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__SpellScrollLight::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_speedBonus_1877: this->f_speedBonus = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__SpellScrollLight::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__SpellScrollLight::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__SpellScrollLight::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__SpellScrollLight::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(22LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpellScrollLight::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(this->f_speedBonus, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getNumAffectedItems_427, nullptr, 0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_addSpeed_273, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpellScrollLight::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(1LL)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseRandomDebuffs_356, _ca, 1); })();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getDebuffStacks_1216, nullptr, 0), gd::GdVal::from_int(0LL))))) {
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, nullptr, 0);
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__SpellScrollLight::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_speedBonus = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[154])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__SpellScrollLight(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__SpellScrollLight>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__SpellScrollLight = {CLS_Gd__gd_core_items__Exclusive__SpellScrollLight, "SpellScrollLight", "res://gd_core_items/Exclusive/SpellScrollLight.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__SpellScrollLight, &Gd__gd_core_items__Exclusive__SpellScrollLight::get_static_prop_fn, &Gd__gd_core_items__Exclusive__SpellScrollLight::call_static_fn};

void Gd__gd_core_items__Exclusive__Stoned::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_protectionActive = gd::GdVal::from_bool(false);
    this->f_boostedStones = gd::GdVal::from_int(0LL);
    this->f_damReductionGiven = gd::GdVal::from_float(0.0);
    this->f_stoneDescriptor = gd::GdVal::null();
    this->f_stoneGolemDescriptor = gd::GdVal::null();
    this->f_stoneArmorDescriptor = gd::GdVal::null();
    this->f_blockFactor = gd::GdVal::null();
    this->f_damReduction = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__Stoned::meta() const { return &META_Gd__gd_core_items__Exclusive__Stoned; }
gd::GdVal Gd__gd_core_items__Exclusive__Stoned::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__Stoned::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__Stoned::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_protectionActive_2552: out = this->f_protectionActive; return true;
        case SYM_GEN_boostedStones_2553: out = this->f_boostedStones; return true;
        case SYM_GEN_damReductionGiven_2554: out = this->f_damReductionGiven; return true;
        case SYM_GEN_stoneDescriptor_2555: out = this->f_stoneDescriptor; return true;
        case SYM_GEN_stoneGolemDescriptor_2556: out = this->f_stoneGolemDescriptor; return true;
        case SYM_GEN_stoneArmorDescriptor_2557: out = this->f_stoneArmorDescriptor; return true;
        case SYM_GEN_blockFactor_1977: out = this->f_blockFactor; return true;
        case SYM_GEN_damReduction_1873: out = this->f_damReduction; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__Stoned::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_protectionActive_2552: this->f_protectionActive = gd::gd_coerce_bool(val); return true;
        case SYM_GEN_boostedStones_2553: this->f_boostedStones = val; return true;
        case SYM_GEN_damReductionGiven_2554: this->f_damReductionGiven = val; return true;
        case SYM_GEN_stoneDescriptor_2555: this->f_stoneDescriptor = val; return true;
        case SYM_GEN_stoneGolemDescriptor_2556: this->f_stoneGolemDescriptor = val; return true;
        case SYM_GEN_stoneArmorDescriptor_2557: this->f_stoneArmorDescriptor = val; return true;
        case SYM_GEN_blockFactor_1977: this->f_blockFactor = val; return true;
        case SYM_GEN_damReduction_1873: this->f_damReduction = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__Stoned::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_getData_638: return true;
        case SYM_GEN_setData_639: return true;
        case SYM_GEN_onBought_455: return true;
        case SYM_GEN_canBlock_291: return true;
        case SYM_GEN_canAffect_global_2014: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onStoneAttacked_2558: return true;
        case SYM_GEN_onDamaged_1855: return true;
        case SYM_GEN_onBlockChanged_1986: return true;
        case SYM_GEN_checkBlock_2559: return true;
        case SYM_GEN_onItemRoll_2018: return true;
        case SYM_GEN_onItemRolled_2019: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__Stoned::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_getData_638: out = fn_getData(args, argc); return true;
        case SYM_GEN_setData_639: out = fn_setData(args, argc); return true;
        case SYM_GEN_onBought_455: out = fn_onBought(args, argc); return true;
        case SYM_GEN_canBlock_291: out = fn_canBlock(args, argc); return true;
        case SYM_GEN_canAffect_global_2014: out = fn_canAffect_global(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onStoneAttacked_2558: out = fn_onStoneAttacked(args, argc); return true;
        case SYM_GEN_onDamaged_1855: out = fn_onDamaged(args, argc); return true;
        case SYM_GEN_onBlockChanged_1986: out = fn_onBlockChanged(args, argc); return true;
        case SYM_GEN_checkBlock_2559: out = fn_checkBlock(args, argc); return true;
        case SYM_GEN_onItemRoll_2018: out = fn_onItemRoll(args, argc); return true;
        case SYM_GEN_onItemRolled_2019: out = fn_onItemRolled(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__Stoned::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__Stoned::fn_getData(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return this->f_boostedStones;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Stoned::fn_setData(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_data = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_ne(lv_data, gd::GdVal::null())))) {
        this->f_boostedStones = lv_data;
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Stoned::fn_onBought(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_boostedStones = gd::GdVal::from_int(4LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Stoned::fn_canBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Stoned::fn_canAffect_global(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(2LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasTag_81, _ca, 1); })()) ? gd::GdVal::from_bool(true) : gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_stoneGolemDescriptor}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_isA_245, _ca, 1); })())));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Stoned::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[200]), gd::GdVal::from_str(&battle_string_literals[201])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[142]), gd::GdVal::from_str(&battle_string_literals[143])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    this->f_protectionActive = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
    this->f_damReductionGiven = gd::GdVal::from_float(0.0);
    {
        gd::GdVal _t526 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, this->f_inventory, SYM_GEN_getItems_1603, nullptr, 0));
        gd::GdArr* _t527 = (_t526.kind == gd::GdVal::Kind::Arr) ? _t526.arr : nullptr;
        uint32_t _len__t528 = _t527 ? _t527->len : 0u;
        for (uint32_t _t528 = 0; _t528 < _len__t528; ++_t528) {
            gd::GdVal lv_item = _t527->data[_t528];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {lv_item}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_canAffect_global_2014, _ca, 1); })())) {
                (void)([&]() { gd::GdVal _ca[] = {lv_item, gd::GdVal::from_str(&battle_string_literals[202]), gd::GdVal::from_str(&battle_string_literals[203])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
            }
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Stoned::fn_onStoneAttacked(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::gd_ceil(gd::gd_mul(gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_damage_1518), this->f_blockFactor)), gd::GdVal::from_bool(true), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, _ca, 3); })();
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Stoned::fn_onDamaged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__healthChange = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_checkBlock_2559, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Stoned::fn_onBlockChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv__event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_checkBlock_2559, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Stoned::fn_checkBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(this->f_protectionActive)) {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getBlock_204, nullptr, 0), gd::GdVal::from_int(0LL))))) {
            this->f_protectionActive = gd::gd_coerce_bool(gd::GdVal::from_bool(false));
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_neg(this->f_damReduction)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeDamageResistance_1279, _ca, 1); })();
            this->f_damReductionGiven = gd::gd_sub(this->f_damReductionGiven, this->f_damReduction);
        }
    }
    else {
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getBlock_204, nullptr, 0), gd::GdVal::from_int(0LL))))) {
            this->f_protectionActive = gd::gd_coerce_bool(gd::GdVal::from_bool(true));
            (void)([&]() { gd::GdVal _ca[] = {this->f_damReduction}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeDamageResistance_1279, _ca, 1); })();
            this->f_damReductionGiven = gd::gd_add(gd_ctx, this->f_damReductionGiven, this->f_damReduction);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Stoned::fn_onItemRoll(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Stoned::fn_onItemRolled(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_descr = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(lv_descr, this->f_stoneDescriptor)))) {
        this->f_boostedStones = gd::gd_sub(this->f_boostedStones, gd::GdVal::from_int(1LL));
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__Stoned::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_stoneDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[204])}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })();
    this->f_stoneGolemDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[205])}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })();
    this->f_stoneArmorDescriptor = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[206])}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_item_book_1421), SYM_GEN_getDescriptor_1660, _ca, 1); })();
    this->f_blockFactor = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[207])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_damReduction = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[208])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__Stoned(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__Stoned>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__Stoned = {CLS_Gd__gd_core_items__Exclusive__Stoned, "Stoned", "res://gd_core_items/Exclusive/Stoned.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__Stoned, &Gd__gd_core_items__Exclusive__Stoned::get_static_prop_fn, &Gd__gd_core_items__Exclusive__Stoned::call_static_fn};

void Gd__gd_core_items__Exclusive__TigerRune::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Gems__Gem::init_fields(gd_ctx);
    this->f_buffCounter = gd::GdVal::from_int(0LL);
    this->f_vampChance = gd::GdVal::null();
    this->f_vampirism = gd::GdVal::null();
    this->f_buffsNeeded = gd::GdVal::null();
    this->f_blockForBuffs = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__TigerRune::meta() const { return &META_Gd__gd_core_items__Exclusive__TigerRune; }
gd::GdVal Gd__gd_core_items__Exclusive__TigerRune::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    switch (prop) {
        case SYM_GEN_gemColor_995: return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(3LL), gd::GdVal::from_float(2.501563), gd::GdVal::from_float(0.8)}; return gd::make_color_from_args(_ca, 3); })();
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__TigerRune::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__TigerRune::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_buffCounter_2083: out = this->f_buffCounter; return true;
        case SYM_GEN_vampChance_2591: out = this->f_vampChance; return true;
        case SYM_GEN_vampirism_940: out = this->f_vampirism; return true;
        case SYM_GEN_buffsNeeded_2085: out = this->f_buffsNeeded; return true;
        case SYM_GEN_blockForBuffs_2592: out = this->f_blockForBuffs; return true;
        case SYM_GEN_gemColor_995: out = get_static_const_or_enum(*this->rt_ctx_, prop); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__TigerRune::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_buffCounter_2083: this->f_buffCounter = val; return true;
        case SYM_GEN_vampChance_2591: this->f_vampChance = val; return true;
        case SYM_GEN_vampirism_940: this->f_vampirism = val; return true;
        case SYM_GEN_buffsNeeded_2085: this->f_buffsNeeded = val; return true;
        case SYM_GEN_blockForBuffs_2592: this->f_blockForBuffs = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__TigerRune::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canModifyChance_293: return true;
        case SYM_GEN_prepareInventory_981: return true;
        case SYM_GEN_prepareWeapon_982: return true;
        case SYM_GEN_preAttack_996: return true;
        case SYM_GEN_prepareArmor_983: return true;
        case SYM_GEN_onBuffsChanged_2087: return true;
        case SYM_GEN_onHotSwapHoverWithGemEnd_992: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__TigerRune::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canModifyChance_293: out = fn_canModifyChance(args, argc); return true;
        case SYM_GEN_prepareInventory_981: out = fn_prepareInventory(args, argc); return true;
        case SYM_GEN_prepareWeapon_982: out = fn_prepareWeapon(args, argc); return true;
        case SYM_GEN_preAttack_996: out = fn_preAttack(args, argc); return true;
        case SYM_GEN_prepareArmor_983: out = fn_prepareArmor(args, argc); return true;
        case SYM_GEN_onBuffsChanged_2087: out = fn_onBuffsChanged(args, argc); return true;
        case SYM_GEN_onHotSwapHoverWithGemEnd_992: out = fn_onHotSwapHoverWithGemEnd(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__TigerRune::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Gems__Gem::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__TigerRune::fn_canModifyChance(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::from_bool(true);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__TigerRune::fn_prepareInventory(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t529 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, this->f_inventory, SYM_GEN_getItemsAndGems_1604, nullptr, 0));
        gd::GdArr* _t530 = (_t529.kind == gd::GdVal::Kind::Arr) ? _t529.arr : nullptr;
        uint32_t _len__t531 = _t530 ? _t530->len : 0u;
        for (uint32_t _t531 = 0; _t531 < _len__t531; ++_t531) {
            gd::GdVal lv_item = _t530->data[_t531];
            (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getChance_171, nullptr, 0)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_changeAmplificiationChancePercent_allBuffs_197, _ca, 1); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__TigerRune::fn_prepareWeapon(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, this->f_socket, SYM_GEN_getItem_389, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[209]), gd::GdVal::from_str(&battle_string_literals[210])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__TigerRune::fn_preAttack(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {this->f_vampChance}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_173, _ca, 1); })())) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {this->f_vampirism}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveVampirism_210, _ca, 1); })();
        (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_miniActivate_470, nullptr, 0);
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__TigerRune::fn_prepareArmor(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_buffCounter = gd::GdVal::from_int(0LL);
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[187])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectToCharacterBuffs_374, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__TigerRune::fn_onBuffsChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_amount, gd::GdVal::from_int(0LL))))) {
        this->f_buffCounter = gd::gd_add(gd_ctx, this->f_buffCounter, lv_amount);
        gd::GdVal lv_relBuffs = gd::gd_div(gd_ctx, this->f_buffCounter, this->f_buffsNeeded);
        gd::GdVal lv_block = gd::gd_mul(lv_relBuffs, this->f_blockForBuffs);
        this->f_buffCounter = gd::gd_mod(gd_ctx, this->f_buffCounter, this->f_buffsNeeded);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(lv_block, gd::GdVal::from_int(0LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getGemPower_973, nullptr, 0), lv_block), lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {lv_relBuffs, gd::GdVal::from_bool(true)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showCooldownSmooth_793, _ca, 2); })();
        }
        else {
            (void)([&]() { gd::GdVal _ca[] = {lv_relBuffs, gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_showCooldownSmooth_793, _ca, 2); })();
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__TigerRune::fn_onHotSwapHoverWithGemEnd(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__TigerRune::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Gems__Gem::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_vampChance = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[211])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })();
    this->f_vampirism = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[195])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_buffsNeeded = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[185])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_blockForBuffs = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[212])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__TigerRune(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__TigerRune>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__TigerRune = {CLS_Gd__gd_core_items__Exclusive__TigerRune, "TigerRune", "res://gd_core_items/Exclusive/TigerRune.gd", &META_Gd__gd_core_items__Gems__Gem, true, _alloc_Gd__gd_core_items__Exclusive__TigerRune, &Gd__gd_core_items__Exclusive__TigerRune::get_static_prop_fn, &Gd__gd_core_items__Exclusive__TigerRune::call_static_fn};

void Gd__gd_core_items__Exclusive__WandofDissonance::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_healthUsed = gd::GdVal::null();
    this->f_effectDmg = gd::GdVal::null();
    this->f_availableBuffs = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Exclusive__WandofDissonance::meta() const { return &META_Gd__gd_core_items__Exclusive__WandofDissonance; }
gd::GdVal Gd__gd_core_items__Exclusive__WandofDissonance::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Exclusive__WandofDissonance::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Exclusive__WandofDissonance::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_healthUsed_2611: out = this->f_healthUsed; return true;
        case SYM_GEN_effectDmg_2585: out = this->f_effectDmg; return true;
        case SYM_GEN_availableBuffs_2612: out = this->f_availableBuffs; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__Exclusive__WandofDissonance::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_healthUsed_2611: this->f_healthUsed = val; return true;
        case SYM_GEN_effectDmg_2585: this->f_effectDmg = val; return true;
        case SYM_GEN_availableBuffs_2612: this->f_availableBuffs = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Exclusive__WandofDissonance::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__Exclusive__WandofDissonance::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Exclusive__WandofDissonance::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Exclusive__WandofDissonance::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_gt(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getCurrentHealth_1154, nullptr, 0), this->f_healthUsed)))) {
        gd::GdVal lv_event = ([&]() { gd::GdVal _ca[] = {this->f_healthUsed, gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_loseHealth_1157, _ca, 2); })();
        gd::GdVal lv_dam = gd::get_prop(gd_ctx, this->f_descriptor, SYM_GEN_minDam_1675);
        gd::GdVal lv_res = ([&]() { gd::GdVal _ca[] = {lv_dam, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealEffectDamage_221, _ca, 2); })();
        gd::GdVal lv_maxBuffs = ([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::native_inline_call(gd_ctx, this->f_availableBuffs, gd::SYM_keys, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getMostStacks_361, _ca, 2); })();
        gd::GdVal lv_buffToGive = ([&]() { gd::GdVal _ca[] = {lv_maxBuffs}; return gd::native_inline_call(gd_ctx, gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_util_1407), SYM_GEN_pickRandomElement_1746, _ca, 1); })();
        gd::GdVal lv_amount = gd::native_array_index(gd_ctx, this->f_availableBuffs, lv_buffToGive);
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), lv_buffToGive, lv_amount, lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveStacks_201, _ca, 4); })();
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WandofDissonance::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(25LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WandofDissonance::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_bonusEffectDmg = gd::GdVal::from_float(0.0);
    {
        gd::GdVal _t532 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t533 = (_t532.kind == gd::GdVal::Kind::Arr) ? _t532.arr : nullptr;
        uint32_t _len__t534 = _t533 ? _t533->len : 0u;
        for (uint32_t _t534 = 0; _t534 < _len__t534; ++_t534) {
            gd::GdVal lv_item = _t533->data[_t534];
            if (gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(18LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })())) {
                lv_bonusEffectDmg = gd::gd_add(gd_ctx, lv_bonusEffectDmg, gd::gd_mul(this->f_effectDmg, gd::GdVal::from_float(2.0)));
            }
            else {
                lv_bonusEffectDmg = gd::gd_add(gd_ctx, lv_bonusEffectDmg, this->f_effectDmg);
            }
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {lv_bonusEffectDmg}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_changeEffectDamageFactor_1281, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Exclusive__WandofDissonance::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_healthUsed = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[213])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_effectDmg = gd::gd_div(gd_ctx, ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[197])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })(), gd::GdVal::from_float(100.0));
    this->f_availableBuffs = ([&]() { auto* d = gd::GdDict::create(gd_ctx.arena, 3); d->set(gd_ctx.arena, gd::GdVal::from_int(105LL), gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[189])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })())); d->set(gd_ctx.arena, gd::GdVal::from_int(101LL), gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[159])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })())); d->set(gd_ctx.arena, gd::GdVal::from_int(102LL), gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[161])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })())); return gd::GdVal::from_dict(d); })();
    this->f_damageSource = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), gd::SYM_new, nullptr, 0), SYM_GEN_setItem_1550, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Exclusive__WandofDissonance(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Exclusive__WandofDissonance>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Exclusive__WandofDissonance = {CLS_Gd__gd_core_items__Exclusive__WandofDissonance, "WandofDissonance", "res://gd_core_items/Exclusive/WandofDissonance.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__Exclusive__WandofDissonance, &Gd__gd_core_items__Exclusive__WandofDissonance::get_static_prop_fn, &Gd__gd_core_items__Exclusive__WandofDissonance::call_static_fn};

void Gd__gd_core_items__Garlic::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Food::init_fields(gd_ctx);
    this->f_extraBlock = gd::GdVal::from_int(0LL);
}
const gd::GdClassMeta* Gd__gd_core_items__Garlic::meta() const { return &META_Gd__gd_core_items__Garlic; }
gd::GdVal Gd__gd_core_items__Garlic::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Food::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Garlic::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Garlic::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_extraBlock_1878: out = this->f_extraBlock; return true;
        default: break;
    }
    return Gd__gd_core_items__Food::get_prop(prop, out);
}
bool Gd__gd_core_items__Garlic::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_extraBlock_1878: this->f_extraBlock = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Food::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Garlic::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN_addBonusBlock_1879: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Food::has_own_method(m);
}
bool Gd__gd_core_items__Garlic::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN_addBonusBlock_1879: out = fn_addBonusBlock(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Food::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Garlic::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Food::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Garlic::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_add(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getBlock_204, nullptr, 0), this->f_extraBlock)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveBlock_203, _ca, 1); })();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_173, nullptr, 0))) {
        (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_removeVampirism_339, _ca, 1); })();
    }
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Garlic::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_extraBlock = gd::GdVal::from_int(0LL);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Garlic::fn_addBonusBlock(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__extraBlock = (_argc > 0) ? _args[0] : gd::GdVal::null();
    this->f_extraBlock = gd::gd_add(gd_ctx, this->f_extraBlock, lv__extraBlock);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Garlic::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Food::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Garlic(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Garlic>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Garlic = {CLS_Gd__gd_core_items__Garlic, "Garlic", "res://gd_core_items/Garlic.gd", &META_Gd__gd_core_items__Food, true, _alloc_Gd__gd_core_items__Garlic, &Gd__gd_core_items__Garlic::get_static_prop_fn, &Gd__gd_core_items__Garlic::call_static_fn};

void Gd__gd_core_items__HeroLongsword::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Weapon::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__HeroLongsword::meta() const { return &META_Gd__gd_core_items__HeroLongsword; }
gd::GdVal Gd__gd_core_items__HeroLongsword::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Weapon::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__HeroLongsword::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__HeroLongsword::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__Weapon::get_prop(prop, out);
}
bool Gd__gd_core_items__HeroLongsword::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__Weapon::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__HeroLongsword::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_getCraftingOffset_850: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::has_own_method(m);
}
bool Gd__gd_core_items__HeroLongsword::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_getCraftingOffset_850: out = fn_getCraftingOffset(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Weapon::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__HeroLongsword::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Weapon::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__HeroLongsword::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_canBeEmpowered_90, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HeroLongsword::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    {
        gd::GdVal _t535 = gd::gd_iter_seq(gd_ctx.arena, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0));
        gd::GdArr* _t536 = (_t535.kind == gd::GdVal::Kind::Arr) ? _t535.arr : nullptr;
        uint32_t _len__t537 = _t536 ? _t536->len : 0u;
        for (uint32_t _t537 = 0; _t537 < _len__t537; ++_t537) {
            gd::GdVal lv_item = _t536->data[_t537];
            (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_addBonusDamage_161, _ca, 1); })();
        }
    }
    (void)([&]() { gd::GdVal _ca[] = {gd::GdVal::null(), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HeroLongsword::fn_getCraftingOffset(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_forDirection = (_argc > 0) ? _args[0] : gd::GdVal::null();
    {
        gd::GdVal _t538 = lv_forDirection;
        if (gd::native_scalar_eq(_t538, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_UP))) {
            return gd::GdVal::from_vec2((gd::GdVal::from_int(0LL)).as_float(), (gd::gd_neg(gd::GdVal::from_int(1LL))).as_float());
        }
        else if (gd::native_scalar_eq(_t538, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_DOWN))) {
            return gd::GdVal::from_vec2(0.0, 0.0);
        }
        else if (gd::native_scalar_eq(_t538, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_LEFT))) {
            return gd::GdVal::from_vec2((gd::gd_neg(gd::GdVal::from_int(1LL))).as_float(), (gd::GdVal::from_int(0LL)).as_float());
        }
        else if (gd::native_scalar_eq(_t538, gd::get_prop(gd_ctx, gd::get_prop(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreConst), SYM_GEN_FaceDirection_863), gd::SYM_RIGHT))) {
            return gd::GdVal::from_vec2(0.0, 0.0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__HeroLongsword::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Weapon::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__HeroLongsword(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__HeroLongsword>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__HeroLongsword = {CLS_Gd__gd_core_items__HeroLongsword, "HeroLongsword", "res://gd_core_items/HeroLongsword.gd", &META_Gd__gd_core_items__Weapon, true, _alloc_Gd__gd_core_items__HeroLongsword, &Gd__gd_core_items__HeroLongsword::get_static_prop_fn, &Gd__gd_core_items__HeroLongsword::call_static_fn};

void Gd__gd_core_items__ManaPotion::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Potion::init_fields(gd_ctx);
    this->f_healthThreshold = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__ManaPotion::meta() const { return &META_Gd__gd_core_items__ManaPotion; }
gd::GdVal Gd__gd_core_items__ManaPotion::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Potion::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__ManaPotion::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__ManaPotion::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_healthThreshold_1854: out = this->f_healthThreshold; return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::get_prop(prop, out);
}
bool Gd__gd_core_items__ManaPotion::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_healthThreshold_1854: this->f_healthThreshold = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__ManaPotion::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onTriggerPotion_1849: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onDamaged_1855: return true;
        case SYM_GEN_onManaChanged_1929: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::has_own_method(m);
}
bool Gd__gd_core_items__ManaPotion::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onTriggerPotion_1849: out = fn_onTriggerPotion(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onDamaged_1855: out = fn_onDamaged(args, argc); return true;
        case SYM_GEN_onManaChanged_1929: out = fn_onManaChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Potion::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__ManaPotion::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Potion::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__ManaPotion::fn_onTriggerPotion(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_event = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0), lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_216, _ca, 2); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMaxHealth_317, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ManaPotion::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[134]), gd::GdVal::from_str(&battle_string_literals[141])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[142]), gd::GdVal::from_str(&battle_string_literals[143])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ManaPotion::fn_onDamaged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv__healthChange = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isEmpty_923, nullptr, 0))) {
        return gd::GdVal::null();
    }
    gd::GdVal lv_relHealth = gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), SYM_GEN_getRelativeHealth_302, nullptr, 0);
    if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_relHealth, this->f_healthThreshold)))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consumePotion_1848, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ManaPotion::fn_onManaChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_isEmpty_923, nullptr, 0))) {
        return gd::GdVal::null();
    }
    if (gd::gd_truth((gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_amount, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::gd_is_type(gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_getOrigin_1580, nullptr, 0), &META_Gd__gd_core_items__Item)))) : gd::GdVal::from_bool(false))) ? gd::GdVal::from_bool(gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_getOrigin_1580, nullptr, 0), SYM_GEN_character_74, nullptr, 0), gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0))))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_consumePotion_1848, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__ManaPotion::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Potion::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_healthThreshold = gd::gd_sub(gd::gd_div(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0), gd::GdVal::from_float(100.0)), gd::GdVal::from_float(0.0001));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__ManaPotion(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__ManaPotion>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__ManaPotion = {CLS_Gd__gd_core_items__ManaPotion, "ManaPotion", "res://gd_core_items/ManaPotion.gd", &META_Gd__gd_core_items__Potion, true, _alloc_Gd__gd_core_items__ManaPotion, &Gd__gd_core_items__ManaPotion::get_static_prop_fn, &Gd__gd_core_items__ManaPotion::call_static_fn};

void Gd__gd_core_items__Pumpkin::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Food::init_fields(gd_ctx);
    this->f_heat = gd::GdVal::null();
    this->f_normalTexture = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__Pumpkin::meta() const { return &META_Gd__gd_core_items__Pumpkin; }
gd::GdVal Gd__gd_core_items__Pumpkin::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Food::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__Pumpkin::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__Pumpkin::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_heat_1896: out = this->f_heat; return true;
        case SYM_GEN_normalTexture_1968: out = this->f_normalTexture; return true;
        default: break;
    }
    return Gd__gd_core_items__Food::get_prop(prop, out);
}
bool Gd__gd_core_items__Pumpkin::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_heat_1896: this->f_heat = val; return true;
        case SYM_GEN_normalTexture_1968: this->f_normalTexture = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Food::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__Pumpkin::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onDealtDamage_908: return true;
        case SYM_GEN_onFatigueStarted_1969: return true;
        case SYM_GEN_onShopEntered_746: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Food::has_own_method(m);
}
bool Gd__gd_core_items__Pumpkin::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_doCooldownEffect_144: out = fn_doCooldownEffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onDealtDamage_908: out = fn_onDealtDamage(args, argc); return true;
        case SYM_GEN_onFatigueStarted_1969: out = fn_onFatigueStarted(args, argc); return true;
        case SYM_GEN_onShopEntered_746: out = fn_onShopEntered(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Food::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__Pumpkin::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Food::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__Pumpkin::fn_doCooldownEffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    if (gd::gd_truth(gd::GdVal::from_bool(gd::native_scalar_eq(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_useStamina_116, nullptr, 0), gd::GdVal::from_int(0LL))))) {
        gd::GdVal lv_res = gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_dealDamage_220, nullptr, 0);
        (void)([&]() { gd::GdVal _ca[] = {lv_res}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, _ca, 1); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Pumpkin::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::set_prop(gd_ctx, this->f_descriptor, SYM_GEN_activationAni_1717, gd::get_prop(gd_ctx, Gd__gd_core_items__Pumpkin::get_static_const_or_enum(gd_ctx, SYM_GEN_ActivationAni_869), SYM_GEN_Throw_2747));
    (void)([&]() { gd::GdVal _ca[] = {gd::get_prop(gd_ctx, this->f_ctx, SYM_GEN_combat_1420), gd::GdVal::from_str(&battle_string_literals[214]), gd::GdVal::from_str(&battle_string_literals[215])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Pumpkin::fn_onDealtDamage(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_damageRes = (_argc > 0) ? _args[0] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::native_inline_call(gd_ctx, lv_damageRes, SYM_GEN_hasHit_1523, nullptr, 0)) ? gd::GdVal::from_bool(gd::gd_truth(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_rollChance_173, nullptr, 0))) : gd::GdVal::from_bool(false)))) {
        (void)([&]() { gd::GdVal _ca[] = {([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[216])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), gd::get_prop(gd_ctx, lv_damageRes, SYM_GEN_event_1517)}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_stun_330, _ca, 2); })();
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Pumpkin::fn_onFatigueStarted(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {this->f_heat}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveHeat_218, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Pumpkin::fn_onShopEntered(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__Pumpkin::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Food::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_heat = gd::gd_coerce_int(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[179])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_188, _ca, 1); })());
    this->f_damageSource = ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_obj(this)}; return gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_cls(&META_Gd__gd_core__CoreDamageSource), gd::SYM_new, nullptr, 0), SYM_GEN_setItem_1550, _ca, 1); })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__Pumpkin(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__Pumpkin>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__Pumpkin = {CLS_Gd__gd_core_items__Pumpkin, "Pumpkin", "res://gd_core_items/Pumpkin.gd", &META_Gd__gd_core_items__Food, true, _alloc_Gd__gd_core_items__Pumpkin, &Gd__gd_core_items__Pumpkin::get_static_prop_fn, &Gd__gd_core_items__Pumpkin::call_static_fn};

void Gd__gd_core_items__StrongHealthPotion::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__HealthPotion::init_fields(gd_ctx);
}
const gd::GdClassMeta* Gd__gd_core_items__StrongHealthPotion::meta() const { return &META_Gd__gd_core_items__StrongHealthPotion; }
gd::GdVal Gd__gd_core_items__StrongHealthPotion::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__HealthPotion::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__StrongHealthPotion::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__StrongHealthPotion::get_prop(gd::SymId prop, gd::GdVal& out) const {
    return Gd__gd_core_items__HealthPotion::get_prop(prop, out);
}
bool Gd__gd_core_items__StrongHealthPotion::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    return Gd__gd_core_items__HealthPotion::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__StrongHealthPotion::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_onTriggerPotion_1849: return true;
        case gd::SYM_getTriggerPriority: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__HealthPotion::has_own_method(m);
}
bool Gd__gd_core_items__StrongHealthPotion::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_onTriggerPotion_1849: out = fn_onTriggerPotion(args, argc); return true;
        case gd::SYM_getTriggerPriority: out = fn_getTriggerPriority(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__HealthPotion::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__StrongHealthPotion::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__HealthPotion::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__StrongHealthPotion::fn_onTriggerPotion(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_triggerEvent = (_argc > 0) ? _args[0] : (gd::GdVal::null());
    (void)([&]() { gd::GdVal _ca[] = {lv_triggerEvent}; gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__HealthPotion::call_method(gd_ctx, SYM_GEN_onTriggerPotion_1849, _ca, 1, _out); return _out; })();
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP4_266, nullptr, 0), lv_triggerEvent}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_214, _ca, 2); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StrongHealthPotion::fn_getTriggerPriority(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    return gd::gd_add(gd_ctx, gd::GdVal::from_int(1000LL), gd::GdVal::from_int(1LL));
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__StrongHealthPotion::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__HealthPotion::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__StrongHealthPotion(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__StrongHealthPotion>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__StrongHealthPotion = {CLS_Gd__gd_core_items__StrongHealthPotion, "StrongHealthPotion", "res://gd_core_items/StrongHealthPotion.gd", &META_Gd__gd_core_items__HealthPotion, true, _alloc_Gd__gd_core_items__StrongHealthPotion, &Gd__gd_core_items__StrongHealthPotion::get_static_prop_fn, &Gd__gd_core_items__StrongHealthPotion::call_static_fn};

void Gd__gd_core_items__YggdrasilLeaf::init_fields(gd::BattleCtx& gd_ctx) {
    Gd__gd_core_items__Item::init_fields(gd_ctx);
    this->f_manaUsed = gd::GdVal::from_int(0LL);
    this->f_manaNeeded = gd::GdVal::null();
}
const gd::GdClassMeta* Gd__gd_core_items__YggdrasilLeaf::meta() const { return &META_Gd__gd_core_items__YggdrasilLeaf; }
gd::GdVal Gd__gd_core_items__YggdrasilLeaf::get_static_const_or_enum(gd::BattleCtx& gd_ctx, gd::SymId prop) {
    return Gd__gd_core_items__Item::get_static_const_or_enum(gd_ctx, prop);
}
bool Gd__gd_core_items__YggdrasilLeaf::get_static_prop_fn(gd::SymId prop, gd::GdVal& out) {
    static thread_local gd::BattleCtx s_const_ctx(1u << 16);
    s_const_ctx.arena.reset();
    gd::GdVal r = get_static_const_or_enum(s_const_ctx, prop);
    if (r.kind == gd::GdVal::Kind::Enum || r.kind == gd::GdVal::Kind::Int || r.kind == gd::GdVal::Kind::Float || r.kind == gd::GdVal::Kind::Bool || r.kind == gd::GdVal::Kind::Vec2 || r.kind == gd::GdVal::Kind::ClassRef) { out = r; return true; }
    if (r.kind == gd::GdVal::Kind::Str && r.str) { out = gd::GdVal::from_str(gd::make_static_str(std::string_view(r.str->data, r.str->len))); return true; }
    if (r.kind == gd::GdVal::Kind::Arr && r.arr) { out = gd::GdVal::from_arr(r.arr->duplicate(gd::static_arena(), true)); return true; }
    if (r.kind == gd::GdVal::Kind::Dict && r.dict) { out = gd::GdVal::from_dict(r.dict->duplicate(gd::static_arena(), true)); return true; }
    return false;
}
bool Gd__gd_core_items__YggdrasilLeaf::get_prop(gd::SymId prop, gd::GdVal& out) const {
    switch (prop) {
        case SYM_GEN_manaUsed_2007: out = this->f_manaUsed; return true;
        case SYM_GEN_manaNeeded_1881: out = this->f_manaNeeded; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::get_prop(prop, out);
}
bool Gd__gd_core_items__YggdrasilLeaf::set_prop(gd::BattleCtx& gd_ctx, gd::SymId prop, const gd::GdVal& val) {
    switch (prop) {
        case SYM_GEN_manaUsed_2007: this->f_manaUsed = val; return true;
        case SYM_GEN_manaNeeded_1881: this->f_manaNeeded = val; return true;
        default: break;
    }
    return Gd__gd_core_items__Item::set_prop(gd_ctx, prop, val);
}
bool Gd__gd_core_items__YggdrasilLeaf::has_own_method(gd::SymId m) const {
    switch (m) {
        case SYM_GEN_canAffect_286: return true;
        case SYM_GEN_onPrepare_123: return true;
        case SYM_GEN_onCombatStart_934: return true;
        case SYM_GEN_onManaChanged_1929: return true;
        case SYM_GEN__readyInit_140: return true;
        default: break;
    }
    return Gd__gd_core_items__Item::has_own_method(m);
}
bool Gd__gd_core_items__YggdrasilLeaf::call_method(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    switch (m) {
        case SYM_GEN_canAffect_286: out = fn_canAffect(args, argc); return true;
        case SYM_GEN_onPrepare_123: out = fn_onPrepare(args, argc); return true;
        case SYM_GEN_onCombatStart_934: out = fn_onCombatStart(args, argc); return true;
        case SYM_GEN_onManaChanged_1929: out = fn_onManaChanged(args, argc); return true;
        case SYM_GEN__readyInit_140: out = fn__readyInit(args, argc); return true;
        default: break;
    }
    return Gd__gd_core_items__Item::call_method(gd_ctx, m, args, argc, out);
}
bool Gd__gd_core_items__YggdrasilLeaf::call_static_fn(gd::BattleCtx& gd_ctx, gd::SymId m, const gd::GdVal* args, int argc, gd::GdVal& out) {
    return Gd__gd_core_items__Item::call_static_fn(gd_ctx, m, args, argc, out);
}
gd::GdVal Gd__gd_core_items__YggdrasilLeaf::fn_canAffect(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_item = (_argc > 0) ? _args[0] : gd::GdVal::null();
    return ([&]() { gd::GdVal _ca[] = {gd::GdVal::from_int(26LL)}; return gd::native_inline_call(gd_ctx, lv_item, SYM_GEN_hasType_79, _ca, 1); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__YggdrasilLeaf::fn_onPrepare(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    this->f_manaUsed = gd::GdVal::from_int(0LL);
    (void)([&]() { gd::GdVal _ca[] = {gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_character_74, nullptr, 0), gd::GdVal::from_str(&battle_string_literals[134]), gd::GdVal::from_str(&battle_string_literals[141])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_connectForCombat_500, _ca, 3); })();
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__YggdrasilLeaf::fn_onCombatStart(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP1_263, nullptr, 0), gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0), gd::SYM_size, nullptr, 0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveMana_216, _ca, 1); })();
    (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP2_264, nullptr, 0), gd::native_inline_call(gd_ctx, gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getAffectedItems_420, nullptr, 0), gd::SYM_size, nullptr, 0))}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_giveRegeneration_214, _ca, 1); })();
    (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__YggdrasilLeaf::fn_onManaChanged(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    gd::GdVal lv_amount = (_argc > 0) ? _args[0] : gd::GdVal::null();
    gd::GdVal lv_event = (_argc > 1) ? _args[1] : gd::GdVal::null();
    if (gd::gd_truth((gd::gd_truth(gd::GdVal::from_bool(gd::gd_lt(lv_amount, gd::GdVal::from_int(0LL)))) ? gd::GdVal::from_bool(gd::gd_truth(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[150]), gd::GdVal::from_bool(false)}; return gd::native_inline_call(gd_ctx, lv_event, SYM_GEN_getParam_1575, _ca, 2); })())) : gd::GdVal::from_bool(false)))) {
        this->f_manaUsed = gd::gd_add(gd_ctx, this->f_manaUsed, gd::gd_coerce_int(gd::gd_neg(lv_amount)));
        gd::GdVal lv_activations = gd::gd_div(gd_ctx, this->f_manaUsed, this->f_manaNeeded);
        this->f_manaUsed = gd::gd_mod(gd_ctx, this->f_manaUsed, this->f_manaNeeded);
        if (gd::gd_truth(gd::GdVal::from_bool(gd::gd_ge(lv_activations, gd::GdVal::from_int(1LL))))) {
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(([&]() { gd::GdVal _ca[] = {gd::GdVal::from_str(&battle_string_literals[151])}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP_m_189, _ca, 1); })(), lv_activations), lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_heal_327, _ca, 2); })();
            (void)([&]() { gd::GdVal _ca[] = {gd::gd_mul(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP5_267, nullptr, 0), lv_activations), lv_event}; return gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_cleanseRandomDebuffs_356, _ca, 2); })();
            (void)gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_activate_150, nullptr, 0);
        }
    }
    return gd::GdVal::null();
}
gd::GdVal Gd__gd_core_items__YggdrasilLeaf::fn__readyInit(const gd::GdVal* _args, int _argc) {
    gd::BattleCtx& gd_ctx = *this->rt_ctx_;
    (void)([&]() {  gd::GdVal _out = gd::GdVal::null(); this->Gd__gd_core_items__Item::call_method(gd_ctx, SYM_GEN__readyInit_140, nullptr, 0, _out); return _out; })();
    this->f_manaNeeded = gd::gd_coerce_int(gd::native_inline_call(gd_ctx, gd::GdVal::from_obj(this), SYM_GEN_getP3_265, nullptr, 0));
    return gd::GdVal::null();
}
static gd::GdObj* _alloc_Gd__gd_core_items__YggdrasilLeaf(gd::BattleCtx& ctx) { return ctx.arena.make<Gd__gd_core_items__YggdrasilLeaf>(&ctx); }
const gd::GdClassMeta META_Gd__gd_core_items__YggdrasilLeaf = {CLS_Gd__gd_core_items__YggdrasilLeaf, "YggdrasilLeaf", "res://gd_core_items/YggdrasilLeaf.gd", &META_Gd__gd_core_items__Item, true, _alloc_Gd__gd_core_items__YggdrasilLeaf, &Gd__gd_core_items__YggdrasilLeaf::get_static_prop_fn, &Gd__gd_core_items__YggdrasilLeaf::call_static_fn};
