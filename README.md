# keybmap-broforce

键盘映射，允许您在 broforce 游戏中同时控制四个角色。
我使用 <Windows.h> 中的 GetAsyncKeyState() 和 keybd_event() 来检测按键状态和合成击键，并用宏函数对其做了简单封装。

keymap, allows you to control four characters at the same time in broforce game
Mainly use GetAsyncKeyState() and keybd_event() in <Windows.h> to get key states and synthesize keystrokes
I used some macro functions to simply encapsulate them
