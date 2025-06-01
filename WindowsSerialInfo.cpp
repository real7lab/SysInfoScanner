// !_!

#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <shlobj.h> 
#include <Lmcons.h> 
#include <winreg.h>

std::string GetHWID() {
    HKEY hKey;
    const char* regPath = "SOFTWARE\\Microsoft\\Cryptography";
    const char* valueName = "MachineGuid";
    char value[256];
    DWORD value_length = sizeof(value);

    if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, regPath, 0, KEY_READ | KEY_WOW64_64KEY, &hKey) == ERROR_SUCCESS) {
        if (RegQueryValueExA(hKey, valueName, nullptr, nullptr, (LPBYTE)value, &value_length) == ERROR_SUCCESS) {
            RegCloseKey(hKey);
            return std::string(value);
        }
        RegCloseKey(hKey);
    }
    return "Unknown";
}

void GetDriveInfo() {
    DWORD driveMask = GetLogicalDrives();
    for (char letter = 'A'; letter <= 'Z'; ++letter) {
        if (driveMask & (1 << (letter - 'A'))) {
            std::string root = std::string(1, letter) + ":\\";
            UINT type = GetDriveTypeA(root.c_str());

            if (type == DRIVE_FIXED || type == DRIVE_REMOVABLE) {
                ULARGE_INTEGER freeBytesAvailable, totalBytes, totalFreeBytes;
                if (GetDiskFreeSpaceExA(root.c_str(), &freeBytesAvailable, &totalBytes, &totalFreeBytes)) {
                    char fsName[MAX_PATH] = { 0 };
                    GetVolumeInformationA(root.c_str(), nullptr, 0, nullptr, nullptr, nullptr, fsName, sizeof(fsName));
                    std::cout << "Drive " << root << "\n";
                    std::cout << "  Filesystem: " << fsName << "\n";
                    std::cout << "  Total Space: " << totalBytes.QuadPart / (1024 * 1024 * 1024) << " GB\n";
                    std::cout << "  Free Space: " << totalFreeBytes.QuadPart / (1024 * 1024 * 1024) << " GB\n\n";
                }
            }
        }
    }
}

std::string GetCPUName() {
    char cpuBrand[0x40] = { 0 };
    int cpuInfo[4] = { -1 };

    __cpuid(cpuInfo, 0x80000000);
    unsigned int nExIds = cpuInfo[0];

    if (nExIds >= 0x80000004) {
        __cpuid((int*)cpuInfo, 0x80000002);
        memcpy(cpuBrand, cpuInfo, sizeof(cpuInfo));
        __cpuid((int*)cpuInfo, 0x80000003);
        memcpy(cpuBrand + 16, cpuInfo, sizeof(cpuInfo));
        __cpuid((int*)cpuInfo, 0x80000004);
        memcpy(cpuBrand + 32, cpuInfo, sizeof(cpuInfo));
    }
    return std::string(cpuBrand);
}

void GetRAMInfo() {
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);
    GlobalMemoryStatusEx(&statex);
    std::cout << "Total RAM: " << statex.ullTotalPhys / (1024 * 1024) << " MB\n";
    std::cout << "Available RAM: " << statex.ullAvailPhys / (1024 * 1024) << " MB\n";
}

void GetUserAndComputerName() {
    char username[UNLEN + 1];
    DWORD username_len = UNLEN + 1;
    GetUserNameA(username, &username_len);

    char computerName[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD comp_len = MAX_COMPUTERNAME_LENGTH + 1;
    GetComputerNameA(computerName, &comp_len);

    std::cout << "Username: " << username << "\n";
    std::cout << "Computer Name: " << computerName << "\n";
}

int main() {
std::cout << "=== SYSTEM INFO ===\n\n";

std::cout << "[~] HWID: " << GetHWID() << "\n\n";
std::cout << "[~] User and Computer Info:\n";
GetUserAndComputerName();
std::cout << "\n[~] CPU: " << GetCPUName() << "\n\n";
std::cout << "[~] RAM Info:\n";
GetRAMInfo();
std::cout << "\n[~] Drive Info:\n";
GetDriveInfo();
Sleep(50000);
    return 0;
}
