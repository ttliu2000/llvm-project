#pragma once

#include "RISCVAsmPrinter.h"

#include <memory>

namespace llvm {

class MyRISCVAsmPrinter : public RISCVAsmPrinter {
public:
    MyRISCVAsmPrinter(TargetMachine &TM, std::unique_ptr<MCStreamer> Streamer);

    void emitStartOfAsmFile(Module &M) override;
    void emitEndOfAsmFile(Module &M) override;
};

}