#include <windows.h>
#include <fstream>

#define NUME_SERVICIU "MyHelloService"

SERVICE_STATUS statusServiciu;
SERVICE_STATUS_HANDLE handleStatus;

void ScrieMesaj(const char* text)
{
    std::ofstream f("C:\\Temp\\service_log.txt", std::ios::app);
    if (f)
    {
        f << text << std::endl;
    }
}

void WINAPI HandlerControl(DWORD cod)
{
    if (cod == SERVICE_CONTROL_STOP)
    {
        statusServiciu.dwCurrentState = SERVICE_STOPPED;
        SetServiceStatus(handleStatus, &statusServiciu);

        ScrieMesaj("Serviciu oprit");
    }
}

void WINAPI PornireServiciu(DWORD argc, LPTSTR* argv)
{
    handleStatus = RegisterServiceCtrlHandlerA(NUME_SERVICIU, HandlerControl);

    if (!handleStatus)
        return;

    statusServiciu.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    statusServiciu.dwCurrentState = SERVICE_RUNNING;
    statusServiciu.dwControlsAccepted = SERVICE_ACCEPT_STOP;

    SetServiceStatus(handleStatus, &statusServiciu);

    ScrieMesaj("Hello World!");

    while (statusServiciu.dwCurrentState == SERVICE_RUNNING)
    {
        Sleep(2000);
    }
}

int main()
{
    SERVICE_TABLE_ENTRYA tabel[] =
    {
        {(LPSTR)NUME_SERVICIU, (LPSERVICE_MAIN_FUNCTIONA)PornireServiciu},
        {NULL, NULL}
    };

    StartServiceCtrlDispatcherA(tabel);

    return 0;
}
