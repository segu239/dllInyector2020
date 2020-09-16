#include "mainwindow.h"
#include "ui_mainwindow.h"


using namespace std;

//-----------------------------------------------------------
// Inject DLL to target process
//-----------------------------------------------------------
bool MainWindow::InjectDLL(const int &pid, const string &DLL_Path)
{
    long dll_size = DLL_Path.length() + 1;

    HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

    if (hProc == NULL)
    {
        MessageBox(0, L"No fu posible abrir el proceso seleccionado", L"ERROR",MB_ICONEXCLAMATION | MB_SYSTEMMODAL);
        //cerr << "[!]Fail to open target process!" << endl;
        return false;
    }
    //cout << "[+]Opening Target Process..." << endl;

    LPVOID MyAlloc = VirtualAllocEx(hProc, NULL, dll_size, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    if (MyAlloc == NULL)
    {
        MessageBox(0, L"No fu posible VitualAlloc", L"ERROR",MB_ICONEXCLAMATION | MB_SYSTEMMODAL);
        //cerr << "[!]Fail to allocate memory in Target Process." << endl;
        return false;
    }

    //cout << "[+]Allocating memory in Targer Process." << endl;
    int IsWriteOK = WriteProcessMemory(hProc , MyAlloc, DLL_Path.c_str() , dll_size, 0);

    if (IsWriteOK == 0)
    {
        MessageBox(0, L"No fu posible Writeprocess", L"ERROR",MB_ICONEXCLAMATION | MB_SYSTEMMODAL);
        return false;
    }
    //cout << "[+]Creating Remote Thread in Target Process" << endl;

    DWORD dWord;
    LPTHREAD_START_ROUTINE addrLoadLibrary = (LPTHREAD_START_ROUTINE)GetProcAddress(LoadLibraryA("kernel32"), "LoadLibraryA");
    HANDLE ThreadReturn = CreateRemoteThread(hProc, NULL, 0, addrLoadLibrary, MyAlloc, 0, &dWord);
    if (ThreadReturn == NULL)
    {
        MessageBox(0, L"No fu posible Createremote", L"ERROR",MB_ICONEXCLAMATION | MB_SYSTEMMODAL);
        return false;
    }

    if ((hProc != NULL) && (MyAlloc != NULL) && (IsWriteOK != ERROR_INVALID_HANDLE) && (ThreadReturn != NULL))
    {
        MessageBox(0, L"Injection :)", L"GENIAL",MB_ICONEXCLAMATION | MB_SYSTEMMODAL);
        return true;
    }

    return false;
}
