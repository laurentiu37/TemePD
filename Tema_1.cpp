#include <windows.h>
#include <stdio.h>

#define MAX_NAME 128
#define MAX_DATA 256

void AfisareValoriRegistry(const wchar_t* caleCheie)
{
    HKEY hKey;

    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, caleCheie, 0, KEY_READ, &hKey) != ERROR_SUCCESS)
    {
        wprintf(L"Eroare la deschiderea cheii.\n");
        return;
    }

    DWORD nrValori;

    if (RegQueryInfoKeyW(hKey, NULL, NULL, NULL, NULL, NULL, NULL, &nrValori, NULL, NULL, NULL, NULL) != ERROR_SUCCESS)
    {
        wprintf(L"Eroare la citirea informatiilor despre cheie.\n");
        RegCloseKey(hKey);
        return;
    }

    wprintf(L"Numar valori in cheie: %lu\n", nrValori);

    for (DWORD i = 0; i < nrValori; i++)
    {
        wchar_t numeValoare[MAX_NAME];
        BYTE date[MAX_DATA];

        DWORD dimNume = MAX_NAME;
        DWORD dimDate = MAX_DATA;
        DWORD tip;

        if (RegEnumValueW(hKey, i, numeValoare, &dimNume, NULL, &tip, date, &dimDate) == ERROR_SUCCESS)
        {
            wprintf(L"\nValoarea %lu:\n", i + 1);

            if (dimNume == 0)
                wprintf(L"Nume: (Default)\n");
            else
                wprintf(L"Nume: %s\n", numeValoare);

            if (tip == REG_SZ)
            {
                wprintf(L"Tip: REG_SZ\n");
                wprintf(L"Data: %s\n", (wchar_t*)date);
            }
            else if (tip == REG_DWORD)
            {
                wprintf(L"Tip: REG_DWORD\n");
                wprintf(L"Data: %lu\n", *(DWORD*)date);
            }
            else
            {
                wprintf(L"Alt tip de date\n");
            }
        }
    }

    RegCloseKey(hKey);
}

int main()
{
    const wchar_t* subcheie =
        L"SYSTEM\\CurrentControlSet\\Control\\Session Manager";

    AfisareValoriRegistry(subcheie);

    return 0;
}
