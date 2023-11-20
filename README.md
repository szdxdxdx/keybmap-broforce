# keybmap-broforce

keymap, allows you to control four characters at the same time in broforce game

键盘映射，允许您在 broforce 游戏中同时控制四个角色

Mainly use GetAsyncKeyState() and keybd_event() in <Windows.h> to get key states and synthesize keystrokes

使用 <Windows.h> 了中的 GetAsyncKeyState() 和 keybd_event()，来检测按键状态和合成击键

I used some macro functions to simply encapsulate them

我用宏函数对其做了简单封装
