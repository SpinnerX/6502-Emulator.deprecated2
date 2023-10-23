#pragma once
#include <type_traits>
#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <traits/types.h>
#include <traits/InstructionTraits.h>
#include <traits/InstructionTraits.h>


/**
 * 
 * Partial sub template specialization
 * - Reason for this is because we want to use registers corresponding with different address modes
 * - Instruction will be partial specialized templates, to allow for us to basically call a generalized opcodes, and address modes.
 * - std::enable_if<T, T> is to in compile-time to check if the type is the type we want this to be.
 * 
 * 
*/
template<RegisterTypes regType, AddressModes mode, typename = void>
struct Instruction{};

template<RegisterTypes type, AddressModes mode>
struct Instruction<type, mode, std::enable_if<type == RegisterTypes::LDA>>{
    // Instruction<type, mode>(){
    //     opcode = InstructionTraits<type, mode>::opcode;
    //     bytes = Instruction<type, mode>::bytes;
    //     cycles = Instruction<type, mode>::cycles;
    // }

    // // friend std::ostream& operator<<(std::ostream& outs, Instruction<type, mode> ins){
    // //     outs << "OpCode: " << reinterpret_cast<void *>(ins.opcode) << '\n';
    // //     outs << "Bytes: " << ins.bytes << '\n';
    // //     outs << "Cycles: " << ins.cycles;
    // // }

    // opcode_t opcode;
    // int bytes;
    // int cycles;
};


template<>
struct Instruction<RegisterTypes::LDA, AddressModes::IMMEDIATE>{
    Instruction<RegisterTypes::LDA, AddressModes::IMMEDIATE>(){
        opcode = InstructionTraits<RegisterTypes::LDA, AddressModes::IMMEDIATE>::opcode;
        bytes = InstructionTraits<RegisterTypes::LDA, AddressModes::IMMEDIATE>::bytes;
        cycles = InstructionTraits<RegisterTypes::LDA, AddressModes::IMMEDIATE>::cycles;
    }

    friend std::ostream& operator<<(std::ostream& outs, Instruction<RegisterTypes::LDA, AddressModes::IMMEDIATE> ins){
        outs << "OpCode: " << reinterpret_cast<void *>(ins.opcode) << '\n';
        outs << "Bytes: " << ins.bytes << '\n';
        outs << "Cycles: " << ins.cycles;
        return outs;
    }

    opcode_t opcode;
    int bytes=0;
    int cycles=0;
};

