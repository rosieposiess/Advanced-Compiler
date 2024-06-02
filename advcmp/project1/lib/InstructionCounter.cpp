#include "InstructionCounter.h"
#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/InstIterator.h"

using namespace llvm;


PreservedAnalyses InstructionCounter::run(Function &F,
                                          FunctionAnalysisManager &FAM) {
  //******************************** TODO 1 ********************************

  for(auto &BB:F){ //Fuction 클래스 안에 이렇게 Basic Block들이 이중연결 리스트로 연결되어있음
		for(auto &I:BB){  //Basic Block도 동일하게~
      const char* opcode_name=I.getOpcodeName();
      //printf("%s %d\n",opcode_name,I.getOpcode());
      InstructionCounter[I.getOpcodeName()]++;
    } 
 	}

  // F is a pointer to a Function instance
  /*
  for (inst_iterator I = inst_begin(F), E = inst_end(F); I != E; ++I)
    errs() << *I << "\n"; //테스트
  */
  //****************************** TODO 1 END ******************************

  errs() << "Instruction hit counts\n";
  errs() << "-----------------------------\n";

  
  for (auto &InstructionCount : InstructionCounter) { //InstructionCounter 맵에 있는 모든 요소들을 InstructionCount가 참조해서 가져오는듯
    errs() << InstructionCount.getKey() << " : " << InstructionCount.getValue()
           << "\n"; //key에는 instruction 이름이, value에는 나온 횟수가 들어갈 거라는 것을 추측할 수 있음
  }
  errs() << "-----------------------------\n";

  return PreservedAnalyses::all(); //모든 분석 결과 보존!
}

/*******************************************************************************
 *                        Pass Plugin Registration
 ******************************************************************************/

// Hiding callback functions for registration steps inside anonymous namespace.
namespace {
/**
 * Register pass to the pipeline.
 *
 * Registered pass can be called from `opt` by its name.
 */
bool regInstructionCounterToPipeline(StringRef Name, FunctionPassManager &FPM,
                                     ArrayRef<PassBuilder::PipelineElement>) {
  if (Name != "instruction-counter")
    return false;
  FPM.addPass(InstructionCounter());
  return true;
}

void PBHook(PassBuilder &PB) {
  PB.registerPipelineParsingCallback(regInstructionCounterToPipeline);
}

PassPluginLibraryInfo getInstructionCounterPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "Advanced Compilers - Instruction Counter",
          LLVM_VERSION_STRING, PBHook};
}
} // namespace

// Pass registeration.
extern "C" ::llvm::PassPluginLibraryInfo LLVM_ATTRIBUTE_WEAK
llvmGetPassPluginInfo() {
  return getInstructionCounterPluginInfo();
}