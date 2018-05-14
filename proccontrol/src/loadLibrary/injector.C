// A simple library injector

#include "loadLibrary/injector.h"
#include "loadLibrary/codegen.h"
#include <iostream>
#include "int_process.h"
#include "int_handler.h"
#include "Event.h"
#include <algorithm>
#include <vector>
#include "irpc.h"
//#include "pcEventMuxer.h"

using namespace Dyninst;
using namespace ProcControlAPI;
using namespace std;


#if defined(DEBUG_DISASSEMBLE)
#include "instructionAPI/h/Instruction.h"
#include "instructionAPI/h/InstructionDecoder.h"
using namespace InstructionAPI;
#endif

Injector::Injector(ProcControlAPI::Process *proc) :
   proc_(proc) {}

Injector::~Injector() {} 
bool Injector::inject(std::string libname) {
   int_process *proc = proc_->llproc();
   pthrd_printf("Injecting %s into process %d\n", libname.c_str(), proc->getPid());
   if (!checkIfExists(libname)) {
      perr_printf("Library %s doesn't exist\n", libname.c_str());
      proc->setLastError(err_nofile, "File doesn't exist\n");
      return false;
   }

   Codegen codegen(proc_, libname);
   if (!codegen.generate()) {
      perr_printf("Could not generate code\n");
      proc->setLastError(err_internal, "Error in code generation");
      return false;
   }

   int_iRPC::ptr irpc = int_iRPC::ptr(new int_iRPC(codegen.buffer().start_ptr(),
                                                   codegen.buffer().size(),
                                                   false,
                                                   true,
                                                   codegen.buffer().startAddr()));
   fprintf(stderr, "codegen buffer value in hex is %x\n", codegen.buffer());
   fprintf(stderr, "codegen startoffset value in hex is %x\n", codegen.startOffset());
   fprintf(stderr, "codegen startoffset value in hex is %x\n",codegen.buffer().startAddr());
   // Don't try to execute a library name...
   irpc->setStartOffset(codegen.startOffset());

#if defined(DEBUG_DISASSEMBLE)
   cerr << "Setting starting offset to " << hex << codegen.startOffset() << endl;
   cerr << "And starting address is " << codegen.buffer().startAddr() << dec << endl;

   unsigned char *ptr = codegen.buffer().start_ptr();
   ptr += codegen.startOffset();
   Offset size = codegen.buffer().size() - codegen.startOffset();
   InstructionDecoder d(ptr, size, proc_->getArchitecture());
   Offset off = 0;
   while (off < size) {
     Instruction::Ptr insn = d.decode();
     cerr << hex << off + codegen.startOffset() + codegen.buffer().startAddr() << " : " << insn->format() << endl;
     off += insn->size();
   }

   off = 0;
   while (off < size) {
     cerr << hex <<  off + codegen.startOffset() + codegen.buffer().startAddr() << ": " << (int) ptr[off] << dec << endl;
     off++;
   }
#endif

   //Post, but doesn't start running yet.
   bool result = rpcMgr()->postRPCToProc(proc, irpc);
   if (!result) {
      pthrd_printf("Error posting RPC to process %d\n", proc->getPid());
      return false;
   }
   //Address addr1 = codegen.buffer().startAddr();
   unsigned char *ptr = codegen.buffer().start_ptr();
   ptr += codegen.startOffset();
   Address addr1 = (Dyninst::Address)(ptr);
   Dyninst::Address addr2 = codegen.buffer().startAddr();
   ProcControlAPI::Process::mem_perm rights(true, false, true);
   ProcControlAPI::Process::mem_perm oldrights(false, false, false);
   //size_t size = codegen.buffer().size() - codegen.startOffset();
   size_t size = codegen.buffer().size();
   //- (addr % proc->getMemoryPageSize()), 
   int resultnew = proc->setMemoryAccessRights(addr2, size, rights,oldrights);

   //proc_->changeMemoryProtections(ptr, proc_->getMemoryPageSize(), rights ,false);
   //Set the internal state so that this iRPC runs.
   int_thread *thr = irpc->thread();
   thr->getInternalState().desyncState(int_thread::running);
   irpc->setRestoreInternal(true);
   bool ret = true;
   //ret &= Process::registerEventCallback(EventType(EventType::Any, EventType::SingleStep), PCEventMuxer::SingleStepCallback);
   thr->setSingleStepMode(false);

   Address addr3 = 0x00000000778E0800;
   Address addr9 = 0x00000000778E0803;
   Address addr8 = 0x00000000778E091A;
   Address addr4 =0x00000000778E155E;
   Address addr5= 0x00000000778E168C;
   Address addr6 = 0x00000000778E0B81;
   Address addr7 = 0x00000000778E0B86;
   Address addr10 = 0x0000000077030800;
   Address addr11 = 0x000000007703155;
   Address addr12 = 0x0000000077A47070; //0x0000000076E06510;
   Address addr13 = 0x0000000077A4708F; //0x0000000076E0652F;
   Address addr16 = 0x0000000077A4709F; // call to llEx

   Address addr17 = 0x000007FEFDB1BBB0; //begiining of llex
   Address addr21 = 0x000007FEFDB1BB83;
   Address addr22 = 0x000007FEFDB1BC37;

   Address addr20 = 0x000007FEFDB1BCA0; //DIDNT REACH here in llex
   
   Address addr19 = 0x000007FEFDB1BD9D; //didnt reach here
   Address addr18 = 0x000007FEFDB1BE65;   //end of llex

   Address addr14 = 0x0000000077A470A4; //0x0000000076E06544; 
   Address addr15 = 0x0000000077A470AE; //0x0000000076E0654E; //end of lla
   


    // Create the breakpoint
   ProcControlAPI::Breakpoint::ptr bp1 = Breakpoint::newBreakpoint();
   ProcControlAPI::Breakpoint::ptr bp2 = Breakpoint::newBreakpoint();
   ProcControlAPI::Breakpoint::ptr bp3 = Breakpoint::newBreakpoint();
   ProcControlAPI::Breakpoint::ptr bp4 = Breakpoint::newBreakpoint();
   ProcControlAPI::Breakpoint::ptr bp5 = Breakpoint::newBreakpoint();
   ProcControlAPI::Breakpoint::ptr bp6 = Breakpoint::newBreakpoint();
   ProcControlAPI::Breakpoint::ptr bp7 = Breakpoint::newBreakpoint();
   /* if( !proc_->addBreakpoint(addr12, bp1) ) {
        fprintf(stderr,"failed to insert a breakpoint at address entry: 0x%p\n",
                addr12);
        return false;
    }
   
   fprintf(stderr,"added trap to entry of main, address 0x%lx\n", 
            addr3);
   if( !proc_->addBreakpoint(addr13, bp2) ) {
        fprintf(stderr,"failed to insert a breakpoint at address entry: 0x%p\n",
                 addr13);
        return false;
    }
    if( !proc_->addBreakpoint(addr21, bp3) ) {
        fprintf(stderr,"failed to insert a breakpoint at address entry: 0x%p\n",
                addr14);
        return false;
    }
    
    if( !proc_->addBreakpoint(addr20, bp4) ) {
        fprintf(stderr,"failed to insert a breakpoint at address entry: 0x%p\n",
                addr20);
        return false;
    }
    
    if( !proc_->addBreakpoint(addr16, bp5) ) {
        fprintf(stderr,"failed to insert a breakpoint at address entry: 0x%p\n",
                addr5);
        return false;
    }
    if( !proc_->addBreakpoint(addr17, bp6) ) {
        fprintf(stderr,"failed to insert a breakpoint at address entry: 0x%p\n",
                addr5);
        return false;
    }
     if( !proc_->addBreakpoint(addr22, bp7) ) {
        fprintf(stderr,"failed to insert a breakpoint at address entry: 0x%p\n",
                addr5);
        return false;
    }
    if( !proc_->addBreakpoint(addr19, bp7) ) {
        fprintf(stderr,"failed to insert a breakpoint at address entry: 0x%p\n",
                addr5);
        return false;
    }*/
   //Run the IRPC and wait for completion.
   proc->throwNopEvent();
   result = int_process::waitAndHandleEvents(true);
   if (!result) {
      perr_printf("Error waiting for and handling events\n");
      return false;
   }

   //TODO: Any mechanism for error checks?
   return true;
}  

/*PCEventMuxer::cb_ret_t PCEventMuxer::SingleStepCallback(EventPtr ev) {
   INITIAL_MUXING;

   DEFAULT_RETURN;
} */                                                

bool Injector::checkIfExists(std::string name) {
   SymReader *objSymReader = proc_->llproc()->getSymReader()->openSymbolReader(name);
   return (objSymReader != NULL);
}

bool Injector::libraryLoaded(std::string name) {
   if (proc_->isTerminated()) return false;

   LibraryPool& libs = proc_->libraries();
   
   for (auto li = libs.begin(); li != libs.end(); li++) {
      if ((*li)->getName() == name) return true;
   }
   return false;
}
