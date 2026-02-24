#include "MyRISCVAsmPrinter.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/IR/GlobalVariable.h"
#include "llvm/CodeGen/MachineInstr.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"
#include "llvm/CodeGen/TargetInstrInfo.h"
#include <string>

using namespace llvm;

MyRISCVAsmPrinter::MyRISCVAsmPrinter(TargetMachine &TM,
                   std::unique_ptr<MCStreamer> Streamer)
  : RISCVAsmPrinter(TM, std::move(Streamer)) {}

void MyRISCVAsmPrinter::emitStartOfAsmFile(Module &M) {

  // Emit custom label before first .text
  MCSymbol *TextLabel =
      OutContext.getOrCreateSymbol("__before_text");
  OutStreamer->emitLabel(TextLabel);

  RISCVAsmPrinter::emitStartOfAsmFile(M);
}

void MyRISCVAsmPrinter::emitEndOfAsmFile(Module &M) {

  MCSymbol *DataLabel =
      OutContext.getOrCreateSymbol("__before_data");
  OutStreamer->emitLabel(DataLabel);

  RISCVAsmPrinter::emitEndOfAsmFile(M);
}

void MyRISCVAsmPrinter::emitFunctionBodyStart() {
  // Emit custom label at the start of each function body
  MCSymbol *FuncLabel =
      OutContext.getOrCreateSymbol("__start_of_function_" + CurrentFnSym->getName());
  OutStreamer->emitLabel(FuncLabel);

  RISCVAsmPrinter::emitFunctionBodyStart();
}

void MyRISCVAsmPrinter::emitFunctionBodyEnd() {
  // Emit custom label at the end of each function body
  MCSymbol *FuncEndLabel =
      OutContext.getOrCreateSymbol("__end_of_function_" + CurrentFnSym->getName());
  OutStreamer->emitLabel(FuncEndLabel);

  RISCVAsmPrinter::emitFunctionBodyEnd();
}

void MyRISCVAsmPrinter::emitGlobalVariable(const GlobalVariable *GV) {
  // Emit custom label for each global variable
  MCSymbol *GlobalLabel =
      OutContext.getOrCreateSymbol("__global_variable_" + GV->getName());
  OutStreamer->emitLabel(GlobalLabel);

  RISCVAsmPrinter::emitGlobalVariable(GV);
}

void MyRISCVAsmPrinter::emitInstruction(const MachineInstr *MI) {
  // Emit custom comment before each instruction by get mi's opcode name

  std::string Text = "    # Emitting instruction: ";
  const auto *InstrInfo = MI->getMF()->getSubtarget().getInstrInfo();
  Text += InstrInfo->getName(MI->getOpcode());
  OutStreamer->emitRawText(Text);

  RISCVAsmPrinter::emitInstruction(MI);
}