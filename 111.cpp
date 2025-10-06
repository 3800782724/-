#include <windows.h>
#include <iostream>

// ��װ��������
class MouseSimulator {
public:
    // ģ������������
    static bool LeftDown() {
        INPUT input = { 0 };
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
        return SendInput(1, &input, sizeof(INPUT)) == 1;
    }

    // ģ���������ͷ�
    static bool LeftUp() {
        INPUT input = { 0 };
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
        return SendInput(1, &input, sizeof(INPUT)) == 1;
    }

    // ģ�����������������ѡ�ӳ٣�
    static bool LeftClick(DWORD delayMs = 10) {
        if (!LeftDown()) return false;
        Sleep(delayMs);
        return LeftUp();
    }

    // ģ������������
    static bool LeftPress(DWORD durationMs = 50) {
        if (!LeftDown()) return false;
        Sleep(durationMs);
        return LeftUp();
    }
};

// ���ؿ���̨����
void HideConsole() {
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_HIDE);
}

// ����Ƿ����ȼ�
bool IsHotKeyPressed(int vKey) {
    return (GetAsyncKeyState(vKey) & 0x8000);
}

int main() {
    HideConsole(); // ���ؿ���̨����

    // ��ѭ��
    while (true) {
        // �������/ֹͣ�ȼ�
        if (IsHotKeyPressed(VK_F12)) { // F12����Ϊ����/ֹͣ�ȼ�
            // ���ѭ��
            do {
                MouseSimulator::LeftPress(50); // 50����ĵ��
                Sleep(30); // ������
            } while (IsHotKeyPressed(VK_F12)); // ��סF12����������ɿ�ֹͣ
        }

        // ����˳��ȼ�
        if (IsHotKeyPressed(VK_ESCAPE)) {
            break; // ESC���˳�����
        }

        Sleep(10); // ����CPUռ��
    }

    return 0;
}