# 基于传统文化 IP 的老龄化多模态陪伴系统 C++ Demo

## 1. 项目简介

本项目是王子豪老师暑期项目 Beta 方向的 C++ 工程实践，当前方向为“基于传统文化 IP 的老龄化多模态陪伴系统”。

项目没有推翻原有“VLM 实时网课陪伴助手”的代码，而是在原有 C++ 最小闭环基础上进行场景迁移。系统继续保留文本预处理、摄像头图像采集、VLM 调用、协议解析、失败降级和日志记录等模块，将原来的学生学习陪伴语义迁移为面向老年用户的情绪识别、陪伴需求判断和陪伴回复。

当前系统主流程为：

```text
老年用户文本输入
→ 摄像头采集并保存图像帧
→ 文本输入预处理
→ C++ 调用 VLM 接口
→ VLM 失败时自动使用本地 mock 降级
→ 解析情绪状态与陪伴需求
→ 输出陪伴回复
→ 保存完整运行日志
```

当前版本已经能够完成文字输入、摄像头图像保存、VLM HTTP 客户端封装、结构化输出协议校验、mock 降级、结果解析和日志记录。即使 VLM 配置缺失或调用失败，系统也不会直接崩溃，而是返回可解释的老年陪伴回复，保证最小业务链路继续运行。

传统文化 IP 目前主要体现在 VLM 提示词与项目场景定位中。具体角色设定、角色知识库、语音音色和前端虚拟形象仍属于后续扩展内容。

---

## 2. 当前实现功能

当前 Demo 已实现以下功能：

1. 接收老年用户的中文文本输入，并支持输入 `exit` 正常退出程序；
2. 对用户输入进行基础预处理，去除首尾多余空白字符；
3. 使用 C++ 和 OpenCV 从摄像头捕获图像帧；
4. 将图像依次保存到 `frames/frame_001.jpg`、`frames/frame_002.jpg` 等路径；
5. 将用户文本和摄像头图像路径组织为多模态输入；
6. 使用 `vlm_client` 模块封装基于 libcurl 的 VLM HTTP 调用；
7. 读取图像二进制数据并进行 Base64 编码；
8. 使用 JSON 构造多模态请求体并解析模型响应；
9. 将 VLM 提示词迁移为传统文化 IP 老年多模态陪伴场景；
10. 对 VLM 返回的 `STATE`、`INTENT` 和 `ADVICE` 字段进行格式校验和规范化；
11. 当图片不可用、VLM 配置缺失、网络失败、HTTP 异常或响应格式错误时自动进入 mock 降级；
12. 根据用户输入判断 `EMPTY`、`CONFUSED`、`TIRED`、`NORMAL` 等情绪状态；
13. 根据用户输入判断 `NONE`、`ASK_HELP`、`EMOTION`、`CHAT` 等陪伴需求；
14. 解析并显示视觉输入、回复来源、情绪状态、陪伴需求、陪伴回复和降级原因；
15. 将原始输入、视频帧状态、图片路径、核心模块结果和最终回复追加到日志文件；
16. 日志文件打开失败时输出警告并返回，不导致主程序崩溃；
17. 在 Windows 环境下设置 UTF-8 控制台编码，减少中文输入输出乱码；
18. 已完成 VLM 协议测试，结果为 `15 / 15` 全部通过；
19. 已完成 logger 独立测试，结果为 `11 / 11` 全部通过；
20. 已完成完整主程序回归测试，摄像头、降级回复、解析输出和日志记录均正常工作。

---

## 3. 开发环境与技术栈

### 3.1 开发环境

```text
操作系统：Windows
终端环境：MSYS2 UCRT64
项目目录：/c/Users/xiaob/Desktop/梦/algorithm-practice/beta_demo
语言标准：C++17
```

### 3.2 主要技术

| 技术 | 用途 |
|---|---|
| C++17 | 系统主控、模块组织和业务流程实现 |
| OpenCV 4 | 摄像头打开、图像帧捕获和图片保存 |
| libcurl | 发送 VLM HTTP 请求并接收响应 |
| nlohmann/json | 构造请求 JSON 和解析响应 JSON |
| Base64 | 将本地 JPEG 图片编码为多模态接口可接收的数据 |
| MSYS2 UCRT64 | Windows 下的编译和运行环境 |
| 文件日志 | 保存每次输入、图像状态、核心结果和最终输出 |

C++ 负责系统骨架和流程控制，VLM 只是由 C++ 调用的外部能力。即使后续更换模型或服务地址，外层主流程仍可保持不变。

---

## 4. 工程目录结构

当前项目的核心目录结构如下：

```text
beta_demo/
├── include/
│   ├── preprocess.h
│   ├── beta_core.h
│   ├── parser.h
│   ├── logger.h
│   ├── camera_capture.h
│   └── vlm_client.h
├── src/
│   ├── preprocess.cpp
│   ├── beta_core.cpp
│   ├── parser.cpp
│   ├── logger.cpp
│   ├── camera_capture.cpp
│   └── vlm_client.cpp
├── tests/
│   ├── protocol_test.cpp
│   └── logger_test.cpp
├── frames/
│   ├── frame_001.jpg
│   ├── frame_002.jpg
│   ├── frame_003.jpg
│   ├── frame_module_test.jpg
│   └── latest_frame.jpg
├── logs/
│   └── beta_log.txt
├── competition_demo/
├── elder_companion_demo/
├── main.cpp
└── README.md
```

各核心模块作用如下：

| 文件或目录 | 作用 |
|---|---|
| `main.cpp` | 程序入口，负责接收输入并串联摄像头、预处理、核心调用、解析、输出和日志模块 |
| `include/preprocess.h` | 声明文本预处理模块对外提供的函数 |
| `src/preprocess.cpp` | 实现用户输入的基础清理和预处理 |
| `include/camera_capture.h` | 声明摄像头图像捕获接口 |
| `src/camera_capture.cpp` | 使用 OpenCV 打开摄像头、捕获图像帧并保存图片 |
| `include/vlm_client.h` | 声明 VLM 客户端和 VLM 调用结果结构 |
| `src/vlm_client.cpp` | 读取图片、执行 Base64 编码、构造 JSON、发送 HTTP 请求并解析响应 |
| `include/beta_core.h` | 声明系统核心处理函数和 VLM 输出规范化函数 |
| `src/beta_core.cpp` | 组织 VLM 调用、校验模型输出，并在失败时执行本地 mock 降级逻辑 |
| `include/parser.h` | 声明核心结果解析接口 |
| `src/parser.cpp` | 解析视觉状态、回复来源、情绪状态、陪伴需求、陪伴回复和降级原因 |
| `include/logger.h` | 声明日志保存和控制台编码初始化函数 |
| `src/logger.cpp` | 将输入、图片状态、核心结果和最终回复追加写入日志文件 |
| `tests/protocol_test.cpp` | 独立验证 VLM 输出规范化、非法协议拒绝和 parser 输出 |
| `tests/logger_test.cpp` | 独立验证日志标题、字段记录和文件打开失败处理 |
| `frames/` | 保存摄像头捕获或测试生成的图像帧 |
| `logs/beta_log.txt` | 保存主程序每次运行的完整日志 |
| `competition_demo/` | 保存比赛或提交相关辅助材料 |
| `elder_companion_demo/` | 保存老年多模态陪伴系统的展示或提交材料 |

项目根目录中的 `.exe` 和 `.o` 文件属于编译产物，不是手工维护的源代码，可以通过重新编译生成。

---

## 5. 核心流程说明

程序启动后，首先设置控制台编码并初始化 VLM 客户端，然后进入循环，持续接收用户输入。

```text
init_console_encoding()
→ 读取 VLM_BASE_URL 和 VLM_API_KEY
→ 创建 VlmClient 对象
→ getline(cin, user_input)
→ 判断是否输入 exit
→ 生成本次图像保存路径
→ capture_frame(frame_path)
→ preprocess(user_input)
→ call_beta_core(processed_input, image_path, vlm_client)
→ parse_result(core_result)
→ 控制台输出 final_response
→ save_log(...)
→ 等待下一次用户输入
```

### 5.1 控制台编码初始化

```cpp
init_console_encoding();
```

该函数在 Windows 环境下将控制台输入和输出代码页设置为 UTF-8，用于减少中文提示、中文输入和中文回复出现乱码的情况。

### 5.2 VLM 配置读取

程序通过 `getenv()` 读取以下环境变量：

```text
VLM_BASE_URL
VLM_API_KEY
```

实际密钥不会写入源代码、README 或日志。

如果 VLM 地址或密钥缺失，程序不会退出。真实 VLM 调用失败后，核心模块会自动进入本地 mock 降级流程。

### 5.3 用户输入与退出判断

程序使用：

```cpp
getline(cin, user_input);
```

读取用户输入的完整一行文本。

当用户输入：

```text
exit
```

程序会结束循环并正常退出，不再捕获图片或调用核心模块。

### 5.4 图像路径生成

每次收到新的用户输入时，程序生成新的图片路径，例如：

```text
frames/frame_001.jpg
frames/frame_002.jpg
frames/frame_003.jpg
```

图片编号使用三位数字，不足三位时在前面补 `0`，避免后一次捕获覆盖前一次图片。

### 5.5 摄像头图像捕获

程序调用：

```cpp
bool frame_success = capture_frame(frame_path);
```

返回结果含义：

- `true`：摄像头图像捕获并保存成功；
- `false`：摄像头打开、图像读取或图片保存失败。

图像捕获失败时，系统仍会继续处理文字输入，不会直接退出。

### 5.6 文本输入预处理

程序调用：

```cpp
string processed_input = preprocess(user_input);
```

该步骤对原始文本进行基础清理，为核心模块提供更稳定的输入。

### 5.7 核心模块调用

程序调用：

```cpp
string core_result = call_beta_core(
    processed_input,
    image_path,
    vlm_client
);
```

三个参数分别为：

1. `processed_input`：预处理后的用户文本；
2. `image_path`：本次图片路径，图像不可用时为空字符串；
3. `vlm_client`：负责执行 VLM HTTP 请求的客户端对象。

核心模块优先尝试真实 VLM。调用失败或输出不符合协议时，自动生成 mock 结果，并记录具体降级原因。

### 5.8 结果解析与控制台输出

程序调用：

```cpp
string final_response = parse_result(core_result);
```

解析后的控制台结果包括：

```text
视觉输入
回复来源
情绪状态
陪伴需求
陪伴回复
降级原因
```

`降级原因` 主要在回复来源为 `MOCK` 时显示。

### 5.9 日志记录

程序调用：

```cpp
save_log(
    user_input,
    processed_input,
    core_result,
    final_response,
    frame_path,
    frame_success
);
```

该函数将本次运行过程追加写入：

```text
logs/beta_log.txt
```

日志打开失败时，系统通过 `cerr` 输出：

```text
警告：日志文件打开失败
```

随后结束本次 `save_log()` 调用，不会退出整个主程序。

---

## 6. VLM 输入输出协议

为了让 VLM 输出能够被 C++ 稳定解析，核心模块要求模型只返回一行结构化文本：

```text
STATE:<情绪状态>; INTENT:<陪伴需求>; ADVICE:<陪伴回复>
```

允许的 `STATE` 值为：

```text
EMPTY
CONFUSED
TIRED
NORMAL
```

允许的 `INTENT` 值为：

```text
NONE
ASK_HELP
EMOTION
CHAT
```

示例：

```text
STATE:TIRED; INTENT:EMOTION; ADVICE:您今天可能有些疲惫，可以先坐稳休息一会儿，再告诉我现在的感受。
```

系统会对 VLM 原始输出执行规范化和校验，包括：

1. 去除字段首尾空白；
2. 清理 `ADVICE` 前多余的英文冒号或中文冒号；
3. 将建议内部的英文分号替换为逗号，防止破坏字段边界；
4. 将换行符转换为空格；
5. 拒绝未知的 `STATE`；
6. 拒绝未知的 `INTENT`；
7. 拒绝空的 `ADVICE`；
8. 输出格式不合法时进入 mock 降级。

核心模块最终返回给 parser 的完整格式为：

### VLM 成功

```text
VISION:UNDERSTOOD; SOURCE:VLM; STATE:...; INTENT:...; ADVICE:...
```

### mock 降级

```text
VISION:FAILED; SOURCE:MOCK; FALLBACK_REASON:...; STATE:...; INTENT:...; ADVICE:...
```

当摄像头没有提供可用图片时，视觉状态可以为：

```text
VISION:MISSING
```

---

## 7. 降级策略

系统采用“真实 VLM 优先，本地 mock 保底”的策略。

以下情况会触发降级：

1. 摄像头没有提供可用图片；
2. `VLM_BASE_URL` 为空；
3. `VLM_API_KEY` 为空；
4. 模型名称为空；
5. 用户问题为空；
6. 图片路径为空；
7. 图片文件无法打开；
8. 图片读取失败；
9. Base64 编码结果为空；
10. JSON 请求构造失败；
11. libcurl 初始化失败；
12. HTTP 请求失败或超时；
13. HTTP 状态码不是 2xx；
14. 响应 JSON 缺少 `choices`、`message` 或 `content`；
15. 模型返回空内容；
16. 模型输出不符合规定协议。

降级结果仍会包含：

```text
VISION
SOURCE
FALLBACK_REASON
STATE
INTENT
ADVICE
```

这样做的目的不是掩盖错误，而是让系统在外部服务不可用时仍能提供基本陪伴回复，同时保留清晰的失败原因，便于调试和复现。

---

## 8. 编译与运行

### 8.1 编译完整主程序

在项目根目录执行：

```bash
g++ main.cpp src/preprocess.cpp src/beta_core.cpp src/parser.cpp src/logger.cpp src/camera_capture.cpp src/vlm_client.cpp -Iinclude -o beta_app `pkg-config --cflags --libs opencv4 libcurl`
```

### 8.2 运行完整主程序

```bash
./beta_app
```

程序会提示输入当前想说的话。输入：

```text
exit
```

即可正常退出。

### 8.3 VLM 配置说明

真实 VLM 调用依赖本机环境变量：

```text
VLM_BASE_URL
VLM_API_KEY
```

README、源代码、日志和测试截图中均不应保存或展示实际 API Key。

没有配置 VLM 时仍可以运行完整程序，系统会自动使用 mock 降级逻辑。

---

## 9. 独立测试

### 9.1 VLM 协议测试

编译：

```bash
g++ -std=c++17 tests/protocol_test.cpp src/beta_core.cpp src/parser.cpp src/logger.cpp src/vlm_client.cpp -Iinclude -o protocol_test `pkg-config --cflags --libs libcurl`
```

运行：

```bash
./protocol_test
```

当前验证结果：

```text
Passed: 15 / 15
All protocol tests passed.
```

协议测试主要覆盖：

- 正常协议输出；
- 多余英文冒号；
- 多余中文冒号；
- 字段前导空格；
- 非法情绪状态；
- 非法陪伴需求；
- 空陪伴回复；
- 只有冒号的陪伴回复；
- VLM 成功结果解析；
- mock 降级结果解析；
- 其他协议边界和异常情况。

### 9.2 logger 独立测试

编译：

```bash
g++ -std=c++17 tests/logger_test.cpp src/logger.cpp -Iinclude -o logger_test
```

运行：

```bash
./logger_test
```

当前验证结果：

```text
Passed: 11 / 11
All logger tests passed.
```

logger 测试主要覆盖：

- 日志文件创建；
- 新日志标题；
- 成功场景的原始输入；
- 成功场景的视频帧状态；
- 成功场景的视频帧路径；
- 失败场景的原始输入；
- 失败场景的视频帧状态；
- 失败场景的视频帧路径；
- 核心模块结果记录；
- 最终回复记录；
- 日志文件打开失败警告。

---

## 10. 日志说明

日志文件路径：

```text
logs/beta_log.txt
```

日志使用追加模式写入，不会在每次运行时覆盖旧记录。

当前日志标题为：

```text
========== 老年多模态陪伴系统日志 ==========
```

每次记录包括：

```text
时间
原始输入
视频帧状态
视频帧路径
预处理后
核心模块返回
最终输出
```

示例：

```text
========== 老年多模态陪伴系统日志 ==========
时间：2026-07-16 23:28:33
原始输入：我今天有点累
视频帧状态：成功
视频帧路径：frames/frame_001.jpg
预处理后：我今天有点累
核心模块返回：VISION:FAILED; SOURCE:MOCK; FALLBACK_REASON:VLM base URL is empty.; STATE:TIRED; INTENT:EMOTION; ADVICE:您今天可能有些疲惫，可以先坐稳休息一会儿，再告诉我现在的感受。
最终输出：
视觉输入：FAILED
回复来源：MOCK
情绪状态：TIRED
陪伴需求：EMOTION
陪伴回复：您今天可能有些疲惫，可以先坐稳休息一会儿，再告诉我现在的感受。
降级原因：VLM base URL is empty.
```

日志用于调试、测试验证、问题复现和最终报告撰写。

---

## 11. 当前运行示例

输入：

```text
我今天有点累
```

当摄像头成功保存图像，但 VLM 地址没有配置时，程序输出：

```text
视觉输入：FAILED
回复来源：MOCK
情绪状态：TIRED
陪伴需求：EMOTION
陪伴回复：您今天可能有些疲惫，可以先坐稳休息一会儿，再告诉我现在的感受。
降级原因：VLM base URL is empty.
```

同时摄像头成功保存：

```text
frames/frame_001.jpg
```

这里的两个状态并不矛盾：

```text
视频帧捕获成功
```

表示 OpenCV 已经从摄像头读取图像并保存到本地；

```text
视觉输入：FAILED
```

表示该图像没有被真实 VLM 成功分析。当前失败原因是 VLM 地址为空，因此系统改用 mock 回复。

---

## 12. 当前版本边界

当前版本已经完成可运行的最小多模态工程闭环，但仍存在以下边界：

1. 当前输入方式仍以键盘文本为主，尚未接入 ASR 语音识别；
2. 摄像头当前只负责捕获单帧图片，没有持续视频理解；
3. 当前情绪状态和陪伴需求仍使用有限枚举；
4. mock 降级主要依赖关键词规则，不等同于完整语义理解；
5. 传统文化 IP 目前主要位于提示词和场景定位层，尚未形成完整角色知识库；
6. 尚未接入 RAG，没有加载传统文化角色故事、人物关系和对话资料；
7. 尚未接入 TTS 或 V2V，当前只输出控制台文字；
8. 尚未实现适老化前端界面、大字体交互和一键语音通话；
9. 尚未实现多轮会话记忆；
10. 尚未实现隐私脱敏、权限控制和日志轮转；
11. 当前主要完成本机 Demo 验证，尚未进行真实老人用户测试；
12. 外部 VLM 的可用性仍受服务地址、网络和接口兼容性影响。

这些限制不会影响当前版本作为工程最小闭环 Demo 的展示价值，但在真实部署前必须逐步解决。

---

## 13. 后续计划

后续仍然在现有 C++ 架构上逐步扩展，不推翻重写。

1. 完善传统文化 IP 的角色设定、语言风格和陪伴边界；
2. 引入 RAG，为模型提供角色故事、传统文化知识和固定人物设定；
3. 扩展情绪状态和陪伴需求枚举；
4. 增加多轮对话上下文管理；
5. 接入 ASR，将老年用户语音转换为文本；
6. 接入 TTS 或 V2V，将陪伴回复转换为语音；
7. 设计大字体、少按钮的一键式适老化交互界面；
8. 增加摄像头权限提示、图像保存策略和隐私处理；
9. 增加网络异常、图片损坏和日志异常的更多自动测试；
10. 整理运行截图、测试截图和日志证据；
11. 完成最终 README；
12. 完成 1—2 页项目架构与实现总结 PDF。

---

## 14. 阶段总结

当前项目已经从最初的 C++ 命令行 mock Demo，逐步扩展为包含文本输入、摄像头图像采集、图片 Base64 编码、libcurl HTTP 请求、JSON 处理、VLM 协议校验、失败降级、结果解析、日志记录和独立测试的多模块工程。

在场景迁移过程中，项目保留了原有模块边界和主流程，只修改陪伴语义、提示词、展示字段、日志标题和 mock 回复，实现了从“VLM 实时网课陪伴助手”到“基于传统文化 IP 的老龄化多模态陪伴系统”的最小迁移。

当前已经验证：

```text
摄像头图像保存成功
VLM 配置缺失时自动降级成功
老年陪伴语义输出成功
protocol_test：15 / 15
logger_test：11 / 11
完整主程序回归测试成功
```

该版本已经具备“能编译、能运行、能展示、能解释、能测试、能记录”的最小工程闭环，为后续接入 ASR、RAG、TTS、传统文化 IP 角色资产和适老化界面提供了稳定的 C++ 系统骨架。