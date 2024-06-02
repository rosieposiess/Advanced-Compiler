// Advanced Compilers
// VMO Lab.
#ifndef INSTRUCTIONCOUNTER_H
#define INSTRUCTIONCOUNTER_H

#include "llvm/ADT/StringMap.h"
#include "llvm/IR/PassManager.h"

class InstructionCounter : public llvm::AnalysisInfoMixin<InstructionCounter> {
//InstructionCounter가 public llvm::AnalysisInfoMixin<InstructionCounter>를 상속받음
public:
  llvm::PreservedAnalyses run(llvm::Function &F,
                              llvm::FunctionAnalysisManager &FAM);
  /*
  반환값이 llvm::PreservedAnalyses라는 뜻
  PreservedAnalyses는 pass가 실행된 후에 어떤 결과를 보존할 건지 나타냄
  (왜냐하면 pass가 실행되면, 다른 pass가 이미 실행한 분석 결과를 무효활 할 수 있기 떄문ㅇㅇ)
  */            
 /*
 llvm::PreservedAnalyses의 주요 메서드
llvm::PreservedAnalyses::none(): 어떤 분석 결과도 보존x
llvm::PreservedAnalyses::all(): 모든 분석 결과가 보존됨
llvm::PreservedAnalyses::preserve<Pass>(): 특정 패스의 결과를 보존
 */                
  static bool isRequired() { return false; }

private:
  static llvm::AnalysisKey Key;
  llvm::StringMap<int> InstructionCounter;
  //llvm:StringMap<int>는 InstructionCounter["add"] = 5; 이런식으로 값 저장
};

#endif // INSTRUCTIONCOUNTER_H