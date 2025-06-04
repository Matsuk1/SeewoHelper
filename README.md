# 希沃白板黑屏弹窗问题解决方案
针对希沃白板黑屏屏保问题而设计的C++脚本。
#### 利用WindowsAPI中的数据类型及函数：
- struct SYSTEMTIME 用于存储时间信息
- WINBASEAPI VOID WINAPI GetLocalTime (LPSYSTEMTIME lpSystemTime) 用于获取系统时间
- WINUSERAPI WINBOOL WINAPI GetCursorPos(LPPOINT lpPoint) 用于获取鼠标坐标
- WINUSERAPI WINBOOL WINAPI SetCursorPos(int X,int Y) 用于设置鼠标坐标
- WINUSERAPI VOID WINAPI mouse_event(DWORD dwFlags,DWORD dx,DWORD dy,DWORD dwData,ULONG_PTR dwExtraInfo) 用于模拟鼠标事件
- WINBASEAPI VOID WINAPI Sleep (DWORD dwMilliseconds) 用于处理轮询时间间隔
- WINUSERAPI HDC WINAPI GetDC(HWND hWnd) 用于获取屏幕分辨率
#### 利用_mingw.h库中的数据类型及函数：
- std::time_t 用于储存时间戳
- std::time() 用于获取当前时间戳

------------
### 作者链接：  
[matsuki](http://www.matsuki.work)  
[GitHub](https://github.com/matsuk1)  

感谢支持。
