# semantic_classifier_v1_2026-07-22

## 定位

这是 `beta_demo` 的纯文本、确定性 STATE/INTENT 与安全信号分类模块稳定候选快照。

它不是：

- 生产级自然语言理解系统；
- 生产级医疗或安全系统；
- 豆包 Realtime 接入版本；
- Node/C++ 通信版本。

## 核心接口

```cpp
SemanticResult classify_state_intent(
    const std::string& user_text
);
```

返回四项结果：

```text
state
intent
danger
self_harm
```

## 确定性约束

分类器：

- 只接收文本；
- 不读图片；
- 不联网；
- 不调用 VLM；
- 不调用 TTS；
- 不写日志；
- 不使用时间或随机数；
- 不含角色逻辑。

## 当前枚举

STATE：

```text
EMPTY
CONFUSED
TIRED
NORMAL
```

INTENT：

```text
NONE
ASK_HELP
EMOTION
CHAT
```

## 已知限制

当前仍为简单子字符串关键词匹配，不支持完整中文分词、复杂否定语义或上下文理解。

```text
累计
→ 因包含“累”而误判为 TIRED/EMOTION

不想活跃
→ 因包含“不想活”而误判 self_harm=true

没有胸痛
→ 因包含“胸痛”而误判 danger=true

请帮我找眼镜
→ 当前仍为 NORMAL/CHAT

我很孤单，没人陪我说话
→ 当前仍为 NORMAL/CHAT
```

## 未完成事项

```text
尚未接入豆包最终 ASR
尚未接入 Node Relay
尚未实现 Node/C++ 通信
尚未让 VLM 成功路径强制执行本地安全分类
```
