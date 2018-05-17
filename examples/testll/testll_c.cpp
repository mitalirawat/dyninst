#define DLL_EXPORT

#include <iostream>
#include<windows.h>
#include<tchar.h>
#include "tesll_h.h"
#include <fstream>


#define BUFSIZE 4096

extern "C"
{
	DECLDIR void call_to_dll(int a) {
		fprintf(stderr
			, "yay m called");
		return;
	}
	DECLDIR int functtl()
	{
		HINSTANCE hGetProcIDDLL = LoadLibraryA("C:\\Users\\mrawat\\dyninst-builds\\dyninst-release-install-64\\lib\\dyninstAPI_RT.dll");
		fprintf(
			stderr, "loaded"
		);

		if (!hGetProcIDDLL) {
			std::cout << "could not load the dynamic library" << std::endl;
			return EXIT_FAILURE;
		}
		return 0;
	}


	DECLDIR void loadlibraryWrapper(wchar_t* name) {
		std::ofstream myfile;
		myfile.open (".\\printingfromdll.txt");
		myfile << "Writing this to a file.\n";
		myfile << name;
		myfile.close();
		printf("Path (%s)\n", name);
		DWORD  retval = 0;
		BOOL   success;
		TCHAR  buffer[BUFSIZE] = TEXT("");
		TCHAR  buf[BUFSIZE] = TEXT("");
		TCHAR** lppPart = { NULL };
		TCHAR* path = _T(".\\..\\dyninst-builds\\dyninst-release-install-64\\lib\\dyninstAPI_RT.dll");
		TCHAR* str1 = _T("C:\\Users\\Windows Admin\\Documents\\dyninst-builds\\dyninst-release-install-64\\lib\\dyninstAPI_RT.dll");
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
		fprintf(
			stderr, "new again"
		);
		TCHAR* pathll = _T("E:\\documents\\dyninst-builds\\dyninst-release-install-64\\lib\\dyninstAPI_RT.dll");
		const wchar_t* pathn = L"E:\\documents\\dyninst-builds\\dyninst-release-install-64\\lib\\dyninstAPI_RT.dll";
		//HINSTANCE hGetProcIDDLL = LoadLibraryW(pathn);
		//HINSTANCE hGetProcIDDLL = LoadLibrary(_T("E:\\documents\\dyninst-builds\\new-release-install-build-64\\lib\\dyninstAPI_RT.dll"));
		HINSTANCE hGetProcIDDLL = LoadLibrary(name);
		printf("out of LL");
		fprintf(
			stderr, "loaded"
		);

		if (!hGetProcIDDLL) {
			std::cout << "could not load the dynamic library" << std::endl;
			return ; 
		}
		fprintf(
			stderr, "loaded msg after error check- dyninstapirt.dll- using path"
		);

	}
}
