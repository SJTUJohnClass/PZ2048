> Author: StarryPurple

`src/server.cpp`为Gemini模型帮助下编写，涉及一些网络通信逻辑；具体使用方法在主`README.md`中已经有所介绍。

`src/user_logic_test_concurrency.cpp`为Deepseek模型帮助下编写，涉及C语言进程相关概念。

因为它的IO通讯逻辑与`src/user_logic_test.cpp`有所不同，你会发现它即使在单进程下运行速度也比后者快，这是正常现象。

但是鉴于ACM OJ对并发支持有限，你最好还是以单进程版本为运行时间参考。

进程数由 $num\_processes$ 变量控制，你可以修改其值以探究对于你的设备与逻辑最高效的配置。

当然，这些文件并不会被提交到OJ或助教的本地机上，所以你可以自由修改它们
（比如给server加上自动执行本地user logic的功能，比如让progress bar在所有游戏执行前也显示一个默认值等）。