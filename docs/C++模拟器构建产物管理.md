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
