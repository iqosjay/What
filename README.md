# 魔兽争霸III 冰封王座 字体重叠解决方案

# 工具下载
[Windows32 位](https://github.com/iqosjay/What/blob/main/Builds/What32.exe)
[Windows64 位](https://github.com/iqosjay/What/blob/main/Builds/What64.exe)

# 使用方法
## 1、打开此工具
打开了就不要关，因为我需要监听快捷键，你要是关了我就监听不到

## 2、以窗口模式运行 Warcraft III（必须）
在命令提示符中启动并追加 **-window** 参数即可以窗口模式启动

如果不以窗口模式启动，我暂时不知道怎么获取全屏游戏的窗口句柄

如果哪天我知道了这个方法，再来更新吧~~~

## 3、使用快捷键
**CTRL + SHIFT + F** 会将 War3 全屏

**CTRL + SHIFT + O** 会去除 War3 的窗体边框

**CTRL + O** 则会恢复 War3 的窗体边框

**CTRL + SHIFT + L** 会启用窗口模式锁定鼠标

**CTRL + L** 会解除窗口模式鼠标锁定

**CTRL + SHIFT + Z** 会强制刷新 War3 的窗口从而解决字体重叠问题

也就是说，游戏过程中只要出现了字体重叠你就 **CTRL + SHIFT + Z** 就行

**CTRL + SHIFT + Z** 的三个键都在键盘左下角，只要左手就可以轻松完成

# 注意事项

1、**调整了窗口大小或者是切换过程序，都需要按一次 **CTRL + SHIFT + L** 重新窗口锁鼠**

2、**调整了窗口大小或者是切换过程序，都需要按一次 **CTRL + SHIFT + L** 重新窗口锁鼠**

3、**调整了窗口大小或者是切换过程序，都需要按一次 **CTRL + SHIFT + L** 重新窗口锁鼠**

# 原理
War3 太古老了，支持不好了现今非常牛逼的高清屏幕

如：你使用 4k 显示器玩 RPG ，可能 10 分钟不到就出现字体重叠了

只要你重新调整一下窗口大小就以让 War3 重新绘制，字体就会正确

但是游戏中过程去调整窗口很影响体验，所以使用快捷键调整

当你按下 **CTRL + SHIFT + Z** 时，War3 的窗口宽高会减少 2 像素再立刻加上 2 像素

然后 Windows 就会对 War3 重新绘制

# Bug 反馈
使用过程发现有Bug发送邮件到: iqosjay@gmail.com 
当然了~我不一定有时间修复~~~~~
