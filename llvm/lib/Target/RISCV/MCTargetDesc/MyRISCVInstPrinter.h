#ifndef LLVM_LIB_TARGET_RISCV_MCTARGETDESC_MYRISCVINSTPRINTER_H
#define LLVM_LIB_TARGET_RISCV_MCTARGETDESC_MYRISCVINSTPRINTER_H

#include "RISCVInstPrinter.h"      // for llvm::RISCVInstPrinter
#include "llvm/MC/MCInst.h"        // for llvm::MCInst
#include "llvm/MC/MCSubtargetInfo.h" // for llvm::MCSubtargetInfo
#include "llvm/Support/raw_ostream.h" // for llvm::raw_ostream
#include "llvm/ADT/StringRef.h"    // for llvm::StringRef

namespace llvm {
  class MyRISCVInstPrinter : public RISCVInstPrinter {
  public:
    using RISCVInstPrinter::RISCVInstPrinter;

    void printInst(const MCInst *MI, uint64_t Address, StringRef Annot,
                   const MCSubtargetInfo &STI, raw_ostream &O) override;
  };
} // namespace llvm

#endif // LLVM_LIB_TARGET_RISCV_MCTARGETDESC_MYRISCVINSTPRINTER_H