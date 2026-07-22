# semantic_classifier_v1_2026-07-22 测试记录

## 基本信息

- 测试日期：`2026-07-22`
- Git 分支：`main`
- Windows 工程路径：`C:\Users\xiaob\Desktop\梦\algorithm-practice\beta_demo`
- MSYS2 工程路径：`/c/Users/xiaob/Desktop/梦/algorithm-practice/beta_demo`
- Windows 快照路径：`C:\Users\xiaob\Desktop\梦\algorithm-practice\beta_demo\stable_snapshots\semantic_classifier_v1_2026-07-22`
- MSYS2 快照路径：`/c/Users/xiaob/Desktop/梦/algorithm-practice/beta_demo/stable_snapshots/semantic_classifier_v1_2026-07-22`

## 创建前 Git 状态

```text
## main...origin/main
 M beta_demo/src/beta_core.cpp
 M beta_demo/tests/protocol_test.cpp
?? beta_demo/include/semantic_classifier.h
?? beta_demo/src/semantic_classifier.cpp
?? beta_demo/tests/semantic_classifier_test.cpp
```

创建前 `git diff --check`退出码为 0。

## 工具版本

```text
g++.exe (Rev5, Built by MSYS2 project) 16.1.0
pkg-config 2.5.1
```

## 快照纯分类测试

编译命令：

```bash
SNAPSHOT=/c/Users/xiaob/Desktop/梦/algorithm-practice/beta_demo/stable_snapshots/semantic_classifier_v1_2026-07-22

g++ -std=c++17 \
"$SNAPSHOT/tests/semantic_classifier_test.cpp" \
"$SNAPSHOT/src/semantic_classifier.cpp" \
-I"$SNAPSHOT/include" \
-o /tmp/semantic_classifier_snapshot_test.exe
```

运行命令：

```bash
/tmp/semantic_classifier_snapshot_test.exe
```

结果：

```text
功能/确定性检查：24/24
已知限制复现：3/3
退出码：0
```

三项已知限制未计入语义正确的功能测试数量。

## 快照 protocol 测试

编译命令：

```bash
g++ -std=c++17 \
"$SNAPSHOT/tests/protocol_test.cpp" \
"$SNAPSHOT/src/beta_core.cpp" \
"$SNAPSHOT/src/semantic_classifier.cpp" \
"$SNAPSHOT/src/parser.cpp" \
"$SNAPSHOT/src/logger.cpp" \
"$SNAPSHOT/src/vlm_client.cpp" \
-I"$SNAPSHOT/include" \
-o /tmp/protocol_snapshot_test.exe \
`pkg-config --cflags --libs libcurl`
```

运行命令：

```bash
/tmp/protocol_snapshot_test.exe
```

结果：

```text
protocol_test：15/15
退出码：0
```

## 提交前空白清理

提交前空白检查发现 `parser.cpp` 和 `vlm_client.cpp` 共 9 个只含空格的空白行。
已在原工程与快照副本中同步删除这些空白字符。
未修改任何 C++ 业务逻辑，未转换文件行尾。
清理后重新完成快照一致性检查、编译测试和 SHA-256 校验。

## 依赖隔离与范围

- 纯分类测试只链接快照中的测试文件与 `semantic_classifier.cpp`。
- 纯分类测试不链接 OpenCV、libcurl、摄像头、VLM、音频或日志模块。
- protocol 测试只使用快照中的分类及协议集成依赖。
- 所有测试二进制均输出到 `/tmp`，没有写入快照目录。
- 主工程在创建快照前已经成功编译；本快照只保存分类及协议集成所需文件。
- 当前仍是离线分类基线，不是生产级自然语言理解、医疗或安全系统。
- 没有接入 Node、豆包最终 ASR 或小程序。
- 没有提交、推送或创建 Tag。
