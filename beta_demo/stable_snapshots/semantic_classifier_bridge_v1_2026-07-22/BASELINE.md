# semantic_classifier_bridge_v1_2026-07-22

快照名称：
semantic_classifier_bridge_v1_2026-07-22

快照日期：
2026-07-22

## 功能

Node 通过 `child_process.spawn()` 启动一个长期存活的 C++ 分类服务。
双方使用 stdin/stdout JSONL 通信。
C++ 服务复用 `classify_state_intent()`。
Node 使用 `request_id` 匹配响应。

## 依赖的分类器基线

```text
beta_demo/stable_snapshots/semantic_classifier_v1_2026-07-22/
```

依赖的分类器 Git 提交：

```text
e4566d29cc1618c22a1cee4ef69bfddd004d0521
```

## 协议

请求字段：

```text
request_id
user_text
```

响应字段：

```text
request_id
ok
state
intent
danger
self_harm
error
```

## 已验收

```text
合法请求 24 条
错误请求 12 条
同一 C++ 进程连续处理 36 条请求
UTF-8 中文通过
danger 通过
self_harm 通过
danger + self_harm 通过
stdout 仅 JSONL
EOF 后 C++ 退出码 0
Node 退出码 0
```

## 边界

```text
未接入豆包 Realtime
未接入 ASR
未修改 Barge-in
未修改浏览器
不是生产级进程管理系统
```

## 已知分类语义限制

```text
累计
不想活跃
没有胸痛
```
