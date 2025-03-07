#include <windows.h>
#include <winevt.h>
#include <stdio.h>

LPCWSTR ConvertToLPCWSTR(const char* str) {
    int size_needed = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
    wchar_t* wstr = (wchar_t*)malloc(size_needed * sizeof(wchar_t));
    MultiByteToWideChar(CP_UTF8, 0, str, -1, wstr, size_needed);
    return wstr;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <remote_server> <log_name>\n", argv[0]);
        return 1;
    }

    LPCWSTR remoteServer = ConvertToLPCWSTR(argv[1]);
    LPCWSTR logName = ConvertToLPCWSTR(argv[2]);

    EVT_RPC_LOGIN rpcLogin = {0};
    rpcLogin.Server = (LPWSTR)remoteServer;
    rpcLogin.Flags = EvtRpcLoginAuthDefault;

    printf("[+] Opening session to: %S\n", remoteServer);
    EVT_HANDLE hSession = EvtOpenSession(EvtRpcLogin, &rpcLogin, 0, 0);
    if (hSession == NULL) {
        printf("Failed to open session, error %d", GetLastError());
        free((void*)remoteServer);
        free((void*)logName);
        return 1;
    }

    printf("[+] Clearing event log\n");
    if (!EvtClearLog(hSession, logName, NULL, 0)) {
        printf("Failed to clear event log, error %d", GetLastError());
        EvtClose(hEventLog);
        EvtClose(hSession);
        free((void*)remoteServer);
        free((void*)logName);
        return 1;
    }

    printf("[+] Event log cleared successfully.\n");
    EvtClose(hEventLog);
    EvtClose(hSession);
    free((void*)remoteServer);
    free((void*)logName);
    return 0;
}
