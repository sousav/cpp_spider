#include "Startup.hpp"

Startup::Startup() {
}

Startup::~Startup() {
}

Startup &Startup::operator=(const Startup &obj) {
    return (*this);
}

Startup::Startup(const Startup &obj) {

}

BOOL Startup::_registerStartup(PCWSTR pszAppName, PCWSTR pathToExe, PCWSTR args)
{
    HKEY hKey = NULL;
    LONG lResult = 0;
    BOOL fSuccess = TRUE;
    DWORD dwSize;

    const size_t count = MAX_PATH*2;
    wchar_t szValue[count] = {};
    wcscpy_s(szValue, count, L"\"");
    wcscat_s(szValue, count, pathToExe);
    wcscat_s(szValue, count, L"\" ");
    if (args != NULL) {
        wcscat_s(szValue, count, args);
    }
    lResult = RegCreateKeyExW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL, 0, (KEY_WRITE | KEY_READ), NULL, &hKey, NULL);
    fSuccess = (lResult == 0);
    if (fSuccess) {
        dwSize = (wcslen(szValue)+1)*2;
        lResult = RegSetValueExW(hKey, pszAppName, 0, REG_SZ, (BYTE*)szValue, dwSize);
        fSuccess = (lResult == 0);
    }
    if (hKey != NULL) {
        RegCloseKey(hKey);
        hKey = NULL;
    }
    return fSuccess;
}

BOOL Startup::_unregisterStartup(PCWSTR pszAppName, PCWSTR pathToExe, PCWSTR args)
{
	HKEY hKey = NULL;
	LONG lResult = 0;
	BOOL fSuccess = TRUE;
	DWORD dwSize;

	const size_t count = MAX_PATH * 2;
	wchar_t szValue[count] = {};
	wcscpy_s(szValue, count, L"\"");
	wcscat_s(szValue, count, pathToExe);
	wcscat_s(szValue, count, L"\" ");
	if (args != NULL) {
		wcscat_s(szValue, count, args);
	}
	lResult = RegDeleteKeyExW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, NULL);
	fSuccess = (lResult == 0);
	if (fSuccess) {
		dwSize = (wcslen(szValue) + 1) * 2;
		lResult = RegSetValueExW(hKey, pszAppName, 0, REG_SZ, (BYTE*)szValue, dwSize);
		fSuccess = (lResult == 0);
	}
	if (hKey != NULL) {
		RegCloseKey(hKey);
		hKey = NULL;
	}
	return fSuccess;
}

void Startup::setup() {
    wchar_t szPathToExe[MAX_PATH];

    GetModuleFileNameW(NULL, szPathToExe, MAX_PATH);
    this->_registerStartup(L"Spider.exe", szPathToExe, L"");
}

void Startup::uninstall() {
	wchar_t szPathToExe[MAX_PATH];

	GetModuleFileNameW(NULL, szPathToExe, MAX_PATH);
	this->_unregisterStartup(L"Spider.exe", szPathToExe, L"");
}

void Startup::update() {

}

BOOL Startup::_checkStartup(PCWSTR pszAppName) const
{
    HKEY hKey = NULL;
    LONG lResult = 0;
    BOOL fSuccess = TRUE;
    DWORD dwRegType = REG_SZ;
    wchar_t szPathToExe[MAX_PATH]  = {};
    DWORD dwSize = sizeof(szPathToExe);

    lResult = RegOpenKeyExW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_READ, &hKey);
    fSuccess = (lResult == 0);
    if (fSuccess) {
        lResult = RegGetValueW(hKey, NULL, pszAppName, RRF_RT_REG_SZ, &dwRegType, szPathToExe, &dwSize);
        fSuccess = (lResult == 0);
    }
    if (fSuccess) {
        fSuccess = (wcslen(szPathToExe) > 0) ? TRUE : FALSE;
    }
    if (hKey != NULL) {
        RegCloseKey(hKey);
        hKey = NULL;
    }
    return fSuccess;
}

bool Startup::checkStartup() const {
    return this->_checkStartup(L"Spider.exe");
}
