#include<iostream>
#include<Windows.h>
#include<tchar.h>
#define BUFSIZE 4096
void loadlibraryWrapper(char* name);
int main(){

	
	//HINSTANCE hGetProcIDDLL = LoadLibrary("C:\\Windows\\System32\\ntdll.dll");
	char *n = "C:\\Users\\mrawat\\dyninst-builds\\dyninst-release-install-64\\lib\\dyninstAPI_RT.dll";
	HINSTANCE hGetProcIDDLL = LoadLibraryA("C:\\Users\\mrawat\\test\ space\\dyninstAPI_RT.dll");
	//HINSTANCE hGetProcIDDLL = LoadLibraryA("C:\\Users\\mrawat\\dyninst-builds\\dyninst-release-install-64\\lib\\dyninstAPI_RT.dll");
	fprintf(
		stderr, "loaded"
	);

  	if (!hGetProcIDDLL) {
      		std::cout << "could not load the dynamic library" << std::endl;
          	return EXIT_FAILURE;
	    }
	loadlibraryWrapper(n);


}

void loadlibraryWrapper(char* name) {
DWORD  retval = 0;
BOOL   success;
TCHAR  buffer[BUFSIZE] = TEXT("");
TCHAR  buf[BUFSIZE] = TEXT("");
TCHAR** lppPart = { NULL };
TCHAR* path = _T("C:\\Users\\mrawat\\dyninst-builds\\dyninst-release-install-64\\lib\\dyninstAPI_RT.dll");
retval = GetFullPathName(path, BUFSIZE,
	buffer, lppPart);
if (retval == 0)
{
	// Handle an error condition.
	printf("GetFullPathName failed (%d)\n", GetLastError());
	return;
}
else
{
	_tprintf(TEXT("The full path name is:  %s\n"), buffer);
	if (lppPart != NULL && *lppPart != 0)
	{
		_tprintf(TEXT("The final component in the path name is:  %s\n"), *lppPart);
	}
}
if (retval == 0)
{
	// Handle an error condition.
	printf("GetFullPathName failed (%d)\n", GetLastError());
	return;
}
else
{
	_tprintf(TEXT("The full path name is:  %s\n"), buffer);
	if (lppPart != NULL && *lppPart != 0)
	{
		_tprintf(TEXT("The final component in the path name is:  %s\n"), *lppPart);
	}
}
	}


