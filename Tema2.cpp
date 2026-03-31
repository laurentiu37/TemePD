#include <windows.h>
#include <setupapi.h>
#include <iostream>

#pragma comment(lib, "setupapi.lib")

void AfiseazaInfoDevice(HDEVINFO lista, SP_DEVINFO_DATA& devData)
{
    BYTE buffer[512];
    DWORD dim = 0, tip;

    // Descriere
    if (SetupDiGetDeviceRegistryPropertyW(lista, &devData, SPDRP_DEVICEDESC, &tip, buffer, sizeof(buffer), &dim))
        std::wcout << L"Descriere: " << (wchar_t*)buffer << std::endl;

    // Nume uzual
    if (SetupDiGetDeviceRegistryPropertyW(lista, &devData, SPDRP_FRIENDLYNAME, &tip, buffer, sizeof(buffer), &dim))
        std::wcout << L"Nume: " << (wchar_t*)buffer << std::endl;

    // Producator
    if (SetupDiGetDeviceRegistryPropertyW(lista, &devData, SPDRP_MFG, &tip, buffer, sizeof(buffer), &dim))
        std::wcout << L"Producator: " << (wchar_t*)buffer << std::endl;

    // Hardware ID
    if (SetupDiGetDeviceRegistryPropertyW(lista, &devData, SPDRP_HARDWAREID, &tip, buffer, sizeof(buffer), &dim))
        std::wcout << L"Hardware ID: " << (wchar_t*)buffer << std::endl;
}

int main()
{
    std::wcout << L"Lista dispozitivelor conectate:\n\n";

    // obtinem toate dispozitivele prezente
    HDEVINFO listaDispozitive = SetupDiGetClassDevsW(
        NULL,
        NULL,
        NULL,
        DIGCF_PRESENT | DIGCF_ALLCLASSES
    );

    if (listaDispozitive == INVALID_HANDLE_VALUE)
    {
        std::wcout << L"Eroare la obtinerea listei.\n";
        return 1;
    }

    SP_DEVINFO_DATA devData;
    devData.cbSize = sizeof(SP_DEVINFO_DATA);

    DWORD i = 0;

    // parcurgere dispozitive
    while (SetupDiEnumDeviceInfo(listaDispozitive, i, &devData))
    {
        std::wcout << L"\n=== Device " << i + 1 << L" ===\n";

        AfiseazaInfoDevice(listaDispozitive, devData);

        i++;
    }

    SetupDiDestroyDeviceInfoList(listaDispozitive);

    std::wcout << L"\nTotal dispozitive: " << i << std::endl;

    return 0;
}
