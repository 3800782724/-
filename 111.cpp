#include <windows.h>
#include <iostream>

// 封装鼠标操作类
class MouseSimulator {
public:
    // 模拟鼠标左键按下
    static bool LeftDown() {
        INPUT input = { 0 };
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
        return SendInput(1, &input, sizeof(INPUT)) == 1;
    }

    // 模拟鼠标左键释放
    static bool LeftUp() {
        INPUT input = { 0 };
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
        return SendInput(1, &input, sizeof(INPUT)) == 1;
    }

    // 模拟鼠标左键点击（带可选延迟）
    static bool LeftClick(DWORD delayMs = 10) {
        if (!LeftDown()) return false;
        Sleep(delayMs);
        return LeftUp();
    }

    // 模拟鼠标左键长按
    static bool LeftPress(DWORD durationMs = 50) {
        if (!LeftDown()) return false;
        Sleep(durationMs);
        return LeftUp();
    }
};

// 隐藏控制台窗口
void HideConsole() {
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_HIDE);
}

// 检查是否按下热键
bool IsHotKeyPressed(int vKey) {
    return (GetAsyncKeyState(vKey) & 0x8000);
}

int main() {
    HideConsole(); // 隐藏控制台窗口

    // 主循环
    while (true) {
        // 检查启动/停止热键
        if (IsHotKeyPressed(VK_F12)) { // F12键作为启动/停止热键
            // 点击循环
            do {
                MouseSimulator::LeftPress(50); // 50毫秒的点击
                Sleep(30); // 点击间隔
            } while (IsHotKeyPressed(VK_F12)); // 按住F12持续点击，松开停止
        }

        // 检查退出热键
        if (IsHotKeyPressed(VK_ESCAPE)) {
            break; // ESC键退出程序
        }

        Sleep(10); // 降低CPU占用
    }

    return 0;
}