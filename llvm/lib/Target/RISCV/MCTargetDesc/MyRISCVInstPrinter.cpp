#include "MyRISCVInstPrinter.h"

namespace llvm {

    void MyRISCVInstPrinter::printInst(
        const MCInst *MI,
        uint64_t Address,
        StringRef Annot,
        const MCSubtargetInfo &STI,
        raw_ostream &OS) {

        OS << "TALIU: ";
        RISCVInstPrinter::printInst(MI, Address, Annot, STI, OS);
    }

}