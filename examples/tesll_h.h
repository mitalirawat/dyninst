#pragma once
#ifndef _DLL_TESTLL_H_
#define _DLL_TESTLL_H_
#include <iostream>

#if defined DLL_EXPORT
#define DECLDIR __declspec(dllexport)
#else
#define DECLDIR __declspec(dllimport)
#endif

extern "C"
{
	DECLDIR int functtl();
	DECLDIR void loadlibraryWrapper(char *);
	DECLDIR void call_to_dll(int);
	
}

#endif
