#include "MyRISCVAsmPrinter.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCSymbol.h"

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