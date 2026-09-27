# 背包乱斗 AI — 项目记忆

## 一句话
《Backpack Battles》外置 AI：进程内存读取 + pyautogui 操作，不改游戏文件。核心资产 = Python 战斗模拟器 + 逆向产出的 `gd_core` 无头内核（当前主线）。

## 运行环境（每次会话必用）
- PATH 前缀：`export PATH="/c/Users/Windows/.workbuddy/binaries/PortableGit/versions/1.2.0/usr/bin:/c/Windows/System32:$PATH"`
- Python：`C:/Users/Windows/.workbuddy/binaries/python/versions/3.13.12/python.exe`；**含 pycryptodome** 的：`.../python/envs/default/Scripts/python.exe`
- Godot 3.6 宿主：`output/godot36/Godot_v3.6-stable_win64.exe`
- 长命令一律 `timeout N`；★ heredoc 会吞反斜杠（`\w`→`w`）→ 正则/脚本写成文件再跑
- ★ 并行 Edit 同一文件**会丢改动**（必须串行）；`rm -rf <dir>` 触发 SIGTERM（逐个 `rm -f`）

## 逆向资产
- GDEC 密钥 `8671424952511006d39f4c9e918f821391e2b06a80d946d693fb8757154ce849`（`tools/script_key.txt`）；物品 CSV 另有 `tools/csv_key.txt`
- 容器 `[4 "GDEC"][4 ver][16 MD5(明文)][8 LE 长度][AES-256-ECB]`（无 IV）
- `decompiled_full/` = 820 个 .gd 全量反编译（**权威源码**）；`extracted/` = 原始 .gde/.tscn
- ★ 原版 tscn / CSV 加密，utf-8 直读会**静默出乱码** → 一律走 `tools/item_sheet.py`

## gd_core 无头内核（当前主线）
- 目标：战斗逻辑移植成不依赖场景树的纯逻辑内核，**逻辑 1:1 不变**且更快
- 形态：`gd_core/` 18 脚本 9067 行，全 `extends Reference`；单例→`ctx` 注入；表现→`CoreHooks` 51 个空实现（**全在函数尾部，不参与判定**——保真论证前提）
- ★★ **直挂方案**：`gd_core_items/`（503 份自动生成）= `Item.gd` 适配层 + 502 件物品脚本，**逐字不改**直挂 CoreItem；转译只做「视觉剥离 + 符号映射」
- ★★ `_behavior` **两级派发**：注入优先 → 回落 `callv` 打物品自身，回落**仅限 `SELF_BEHAVIOR_METHODS` 白名单**（只含基类未定义的回调名），否则自我递归。早先只做注入 → 98 件 `onCombatStart` 等回调全静默不执行且零报错
- 验收：`python tools/run_gd_core.py [--bench]` = **十道闸门**，须 `EXIT=0`；闸门 9 = 517 件逐一上场（≈22s）；闸门 10 = 宝石 Socket 门面
- 覆盖度 **709/998 = 71.0%**（CoreItem 422/628）；**判定路径缺口 0 项**（2026-09-27 归零）
- ★ **Socket = 折叠，不是缺类**：插座身份折叠为宿主物品本身（`setGem` 把 self 当 socket、`getItem()` 恒返回 self）。定裁判据 = **访问面枚举**（`socket.` 共 15 处，战斗路径只有 `socket.getItem()`）。`setGemData`（存档序列化）/`initSockets`（后置条件恒真）本就不参与战斗。★ 若将来有行为脚本用 `socket.getGem()`，折叠即漏 → 需按 socketId 建门面。`lineup_gem_test` 已解锁（原 SKIP 理由陈旧）
- ★ **「零报错 ≠ 生效」**：宝石折叠没接上会安静跑完整场却毫无效果、一行错都不报。故宝石独有两道取证：闸门 8 的 A/B（去宝石侧 `gem_heals` 必须 0）+ 闸门 10 公式级（100→+7、57→+4 验 ceil；Armor 分支反向卡门「不得订阅 attacked」；Inventory 模式推帧让自身冷却自行触发）
- ★ 尚**不得宣称 gd_core 等价原版**：静态覆盖已核，但未做 `verify_cooldowns` 等价校验与双引擎逐事件对照，当前只是「无已知偏差」
- 取证文档 `docs/gd_core_truth.md`（§5 五条剥离陷阱；§6 19 条已知偏差/张力；§7 闸门表）
- ★ **生成物里不许写死核算结论**：数字必须生成那刻现算，需另一工具才知道的结论只能**指向**它（反例留痕：写死的「判定路径缺口为 0」曾是假断言，09-27 才偶然变成真）
- ★ 原版死代码照搬，但**不给死代码立契约**（`Gem.isInInventory()` 覆写了一个 Item 上不存在的方法、无调用点 → 刻意不写断言）
- ★ 压缩已到地板（`tools/measure_dead_weight.py`，只报告不删除）：死残留 `gd_core` 0.3%（26/9067）/ `gd_core_items` 1.5%（304/20244）。328 个空桩函数看似垃圾，实为原版 `has_method()` 派发落点，删了会让回调静默失效

## GDScript 3.x 坑位（改 gd_core 必看）
- `log`/`seed` 是内置函数，不能作成员名/形参；`class_name` 互相引用含自引用报 cyclic dependency
- `round()`/`ceil()` 返 float，不能直接 return 给 `-> int`
- 无头跑须 `--script` + `extends SceneTree` + `_init`；Godot 每脚本**只报首个** parse error（逐文件 `load` 批量暴露）
- ★ **报错行号取自「函数真正定义的脚本」**（`PoisonIvy.gd:1441` 实为 `CoreItem.gd` 的行号）→ 按「函数名 + 行号」回内核找
- Godot 遇 `Nonexistent function` 只打 `SCRIPT ERROR` 后**继续执行，退出码仍 0** → 流水线必须扫 stdout
- 控制台中文按 CP936 输出
- **冷却语义三方分歧（勿混用）**：`engine/` 与 `gd_core/` 照搬原版 `cd×randf_range(0.95,1.05)`；`simulator/` 返回固定 `cd`

## Python 侧模块
- `simulator/` = 主模拟器（tkinter GUI + 打包 exe），数据源 `assets/battle_items.json`（**多段流水线产物**，整文件重生成会抹掉后续字段 → 定点重写）
- `engine/` = 早期引擎；`core/` + `gui/` = 外挂 AI 本体；`tools/` = 逆向与生成工具
- ★ 构建产物直接留 `dist/`，不要单独 present exe 让用户另存；打包 `PyInstaller --windowed --onefile`，覆盖前先 `Stop-Process` 杀进程

## Godot 内存布局（2026-07-26 活体标定，本机构建有效）
```
OS::singleton RVA=0x1eba290 → +0x1d0 main_loop(SceneTree) → +0x148 root Viewport（★+0x230 是 current_scene）
Node: parent=+0xf0, children=CowData@+0x108, name(+0x130→_Data→String@+0x10), script_instance=+0x58
GDScriptInstance: script=+0x10, members Vector<Variant>=+0x20；CowData 元素数在 _ptr-4；Variant=24B
Game = root.children[8]；成员下标 gold=72, hp=68, round=65；Node2D 局部pos=+0x270, 全局origin=+0x260；背包格 80px
物品树 Main/Player/<物品>=摆盘、Main/Shop/Storagebox=储物箱、Main/Shop/Items=商店
格坐标 = floor((物品pos − Player/Inventory pos(50,60)) / 80)；排除 SocketsNode/BagBorder/Tiles/Animations
```

## GitHub Release
- `gh` 不在 PATH：`python -c "import zipfile;zipfile.ZipFile('gh.zip').extractall('gh_tmp')"` → 用 `gh_tmp/bin/gh.exe`；凭据在 keyring（cttt-des，`repo`），**无需 PAT**
- `github.com` 主站常不可达，但 `api.github.com`/`uploads.github.com` 稳定；GitHub MCP 对 Release **只读**
- ★ 稳妥流程：`gh release create <tag> --draft` → `gh release upload <tag> --clobber <files>` → `edit --draft=false`
- 已发标签：v0.0.1 / v0.1.0 / v0.1.1 / v0.1.2

## 用户偏好（工程）
- 「**如没有则先不实现**」（底层数据未就位就不提前开发）、「**宁可少删**」（清理/重构保守）
- 要求与原版逐项对齐，做不到或不确定**宁可暂缓也不臆测**；权威源 = backpackbattles.wiki.gg + iyingdi.com + 逆向代码三方交叉
- 输出偏好：结构化表格、分步骤状态、根因分析；常一次性抛多个编号问题，期待按序逐条处理
