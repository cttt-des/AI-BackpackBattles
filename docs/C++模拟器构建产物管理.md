# C++模拟器构建产物管理

2026-11-27，按用户要求将构建中间目录统一放到 `D:\CodexNativeBuilds\work`，构建结束后清理。优化 goal 仍保持暂停，存储维护不等于恢复测速或部署。

## 复用与清理边界

正式发布采用每轮完整20单元插桩、当轮采样及18热点重新PGO，上一轮的LTO分片、汇编和测试程序不参与下一轮。原先部分普通原型会复用旧对象文件以节省编译时间；现在普通原型也完整重编，避免缓存长期累积。

同一次PGO构建内，需要保留对象文件和采样数据直到第二阶段链接及编译选项提取结束。随后立即清理对象、分片、汇编、预处理文件和临时可执行文件。最终DLL、源码、日志、哈希、编译选项和必要的冻结PGO证据保存在D盘项目的实验bundle中。

基线选项校验读取`compiled_options/*.txt`，并核对原`compiled_option_receipt.json`、对象SHA及选项文件SHA；不再要求旧对象文件仍然存在。C盘历史缓存清理不改写历史收据中的路径，它们作为当时构建记录保留；清理目录另有清单说明。

## 执行入口

```powershell
python output/_v1110/run_native_managed.py output/_v1110/structure_round.py build
```

管理入口仅修改被启动进程及子进程的TEMP/TMP/TMPDIR、构建对象目录和Python启动钩子，不修改Windows全局环境变量。旧脚本显式指定的`%LOCALAPPDATA%\CodexNativeBuilds`临时目录也会重定向到当前D盘工作区。

LTO子单元在每次链接成功后清理；完整构建作用域退出时清理剩余对象和临时DLL。子进程失败会先保留源码／数据／日志证据，再清理工作区。强制终止无法执行finally时，下次管理入口会按PID及进程创建时间识别并处理孤立工作区，不触碰仍在运行的任务。

源码、数据和日志的辅助归档在`output/_v1110/build_storage/archive`。旧C盘缓存中有独立历史版本的DLL，因此按SHA去重保存到`D:\CodexNativeBuilds\retained-legacy`后，再删除可重建中间文件；迁移清单与实测空间变化见`output/_v1110/build_storage/c_drive_retirement_20261127/receipt.json`。

已用5单元真实MinGW LTO构建验证D盘路径、链接后分片清理、构建结束清理、子进程重定向及失败路径清理；另验证18份基线选项无需旧对象仍可校验，损坏的选项记录会被拒绝。测试记录在`build_storage/storage_tests/receipt.json`。

实际子进程以17退出时仍清理工作区且保留错误日志；也验证了强制终止遗留目录的回收，见`storage_tests/lifecycle_tests.json`。另从保存的验证目录收据中确认并清理了5个C盘临时测试目录，记录在`build_storage/c_temp_retirement_20261127`。

## 2026-11-28：独立控制编译与 LTO 并行度

按用户要求提高后续构建效率，同时为日常使用电脑预留余量。`native_build_schedule.py` 自动上限为物理核心数减一、逻辑线程数减二中的较小值；本机为4核8线程，因此最多3个计算任务，保持 BelowNormal 优先级。再按启动时可用内存预留2 GiB，普通编译按每任务1 GiB、LTO按每任务0.5 GiB估算，内存不足时进一步降到2或1路。这些是调度预算，不是操作系统硬隔离或内存占用上限。

`build_native_hot_lto.py` 源码编译和 LTO 链接分别选并行数，`--jobs 0 --lto-jobs 0` 为自动；显式请求也受上述余量上限限制。对象编译选项继续为 `-flto=2`，只在最终链接命令中使用 `-flto=N`；`-O3`、浮点选项、balanced分片、PGO及验证标准不变。GCC明确支持通过链接时 `-flto=N` 控制并行任务，见[官方说明](https://gcc.gnu.org/onlinedocs/gcc-16.1.0/gcc/Optimize-Options.html)。没有引入跨轮对象或增量LTO缓存，D盘清理规则不变。

每次构建额外保存 `*.build_schedule.json`，记录硬件、内存预算、实际make命令、观察到的并行进程数和链接耗时。历史构建脚本及源码快照保持原样；当前架构构建包装器只在未来调用时适配调度。正在执行的2路构建继续完成，避免重启损失。

真实MinGW测试使用同一组5份LTO对象分别以2路、3路链接，确认make接收到对应的并行数、对象文件未变、最终`.text`字节一致、导出函数结果一致，以及D盘中间产物清理完成。低内存回退、显式请求仍保留CPU余量也已验证。证据：`output/_v1110/build_storage/parallel_headroom_tests_20261128/receipt.json`。测试与正式构建并发，因此不将两次小链接的耗时差作为提速比例。

首次辅助检查在objcopy读取中文路径时失败，已保留首轮链接收据；修正为先复制到D盘ASCII临时目录后通过。该问题不涉及正式DLL或模拟器语义。

实际验证中遇到一次测试通过后清理`check.exe`的Windows访问拒绝。现对已校验的托管目录增加最多10秒的访问失败重试；超过时限仍明确报错，并保留所有者标记以供后续回收。模拟短暂锁定后的重试、证据保留和最终清理已通过，见同目录`cleanup_retry_test.json`。另外，扩展药水检查改为建立独立临时目录，不再依赖前一个检查已清理的工作目录；测试用例和原版预期不变。


备份证据时使用独立GIT_INDEX_FILE，不移动本地分支或用户暂存区。2026-11-28，14,209个明确路径的git add出现长时间路径处理；保留首轮日志后，改用native_backup_index.py批量hash-object（禁用内容过滤）和update-index写入字面路径，保留原文件模式，并通过cat-file逐块比较全部提交内容，避免把整个备份一次读入内存。中文、空格、方括号、CRLF、二进制和可执行位的真实Git对照树完全一致，错误内容也会被拒绝；证据为本轮bundle的backup_batch_index_test.json。Git打包限2线程，备份进程BelowNormal；历史脚本不改写。[Git对象写入说明](https://git-scm.com/docs/git-hash-object)、[索引格式说明](https://git-scm.com/docs/git-update-index)。

诊断采样若加载临时DLL，须让采样子进程退出后再清理。Windows不会因Python函数返回就解除模块文件锁；本轮已保留首轮清理错误并回收目录，后续包装器改为子进程，实际子进程加载／调用／退出后清理检查通过，未重跑候选A/B或重复采样。
