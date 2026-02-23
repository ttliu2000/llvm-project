#include "MyRISCVAsmPrinter.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCContext.h"

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