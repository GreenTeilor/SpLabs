#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>

#pragma comment(lib, "..\\x64\\Debug\\Dll.lib") //For static import

void StaticImport(DWORD pid);
void DynamicImport(DWORD pid);
void Injection(DWORD pid);

const char* REPLACE_FUNC_NAME = "replaceStringInMemory";

#define TO_REPLACE "Elephant"
#define REPLACE_STR "Firewall"

struct Params {
    DWORD pid;
    char toReplace[256];
    char replaceStr[256];
};

extern "C" _declspec(dllimport) void __stdcall replaceStringInMemory(Params* params);
typedef void(__cdecl* TReplaceMemoryFunc)(Params* params); //Used as pointer on function replaceStringInMemory


int main()
{
    DWORD pid = GetCurrentProcessId();
    char data1[] = TO_REPLACE;
    std::cout << "pid: " << pid << "\n";

    std::cout << "Static Import" << "\n";
    StaticImport(pid);
    std::cout << "String to replace: " << TO_REPLACE << "; New string: " << data1 << "\n";

    return 0;
}

void StaticImport(DWORD pid)
{
    replaceStringInMemory(new Params{pid, TO_REPLACE, REPLACE_STR});
}



