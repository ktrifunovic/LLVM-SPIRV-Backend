//===--- SPIRVCallLowering.h - Call lowering --------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file describes how to lower LLVM calls to machine code calls.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_SPIRV_SPIRVCALLLOWERING_H
#define LLVM_LIB_TARGET_SPIRV_SPIRVCALLLOWERING_H

#include "llvm/CodeGen/GlobalISel/CallLowering.h"

namespace llvm {

class SPIRVTypeRegistry;
class SPIRVTargetLowering;

class SPIRVCallLowering : public CallLowering {
private:
  // Used to create and assign function, argument, and return type information
  SPIRVTypeRegistry *TR;

public:
  SPIRVCallLowering(const SPIRVTargetLowering &TLI, SPIRVTypeRegistry *TR);

  // Built OpReturn or OpReturnValue
  bool lowerReturn(MachineIRBuilder &MIRBuiler, const Value *Val,
                   ArrayRef<Register> VReg) const override;

  // Build OpFunction, OpFunctionParameter, and any EntryPoint or Linkage data
  bool lowerFormalArguments(MachineIRBuilder &MIRBuilder, const Function &F,
                            ArrayRef<ArrayRef<Register>> VRegs) const override;

  // Build OpCall, or replace with a builtin function
  bool lowerCall(MachineIRBuilder &MIRBuilder, CallingConv::ID CallConv,
                 const MachineOperand &Callee, const ArgInfo &OrigRet,
                 ArrayRef<ArgInfo> OrigArgs,
                 const MDNode *KnownCallees = nullptr) const override;
};
} // end namespace llvm

#endif // LLVM_LIB_TARGET_SPIRV_SPIRVCALLLOWERING_H
