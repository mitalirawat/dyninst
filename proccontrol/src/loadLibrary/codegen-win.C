#include "loadLibrary/codegen.h"

using namespace Dyninst;
using namespace ProcControlAPI;
using namespace std;

bool Codegen::generateInt() {
   // Windows is utterly unlike Linux. 

   // Well, mostly. 
   
   //Address loadLibraryB = findinhinttable();
   //Address loadLibraryA = findSymbolAddr("__imp_LoadLibraryA");
   //Address loadLibraryB = findSymbolAddr("RtlGetFullPathName_UstrEx");
   Address loadLibraryB = findSymbolAddr("loadlibraryWrapper");
   Address loadLibraryA = findSymbolAddr("_LoadLibraryA@4");
   if (!loadLibraryA) {
      loadLibraryA = findSymbolAddr("_LoadLibraryA");
   }
   if (!loadLibraryA) {
      loadLibraryA = findSymbolAddr("LoadLibraryA");
   }
   if (!loadLibraryA) return false;

   std::vector<Address> arguments;
   Address libbase = copyString(libname_);
   fprintf(stderr, "buffer value is %s and libbase is %p\n",buffer_.start_ptr(), libbase);
   
   arguments.push_back(libbase);

   // No noops needed on a real OS
   codeStart_ = buffer_.curAddr();
   generatePreamble();
   if (!generateCall(loadLibraryB, arguments)) return false;
   
   return true;
}
