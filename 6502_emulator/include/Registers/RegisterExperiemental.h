#pragma once
#include <type_traits>
#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <traits/types.h>
#include <traits/InstructionTraitsExperiemental.h>


/**
 * 
 * Partial sub template specialization
 * - Reason for this is because we want to use registers corresponding with different address modes
 * - Instruction will be partial specialized templates, to allow for us to basically call a generalized opcodes, and address modes.
 * - std::enable_if<T, T> is to in compile-time to check if the type is the type we want this to be.
 *
 * Changed to just using a generic template of type RegisterType and AddressMode to be generic, just so
 * we can use the decoding process to allow us to note, when we shhould use specific address modes, corresponding to those opcodes/registers
 * 
*/

template<RegisterTypes type>
struct Instruction{};

template<>
struct Instruction<RegisterTypes::LDA>{
    Instruction<RegisterTypes::LDA>(){
        addressModes.insert({0xA9, InstructionTraits{AddressModes::IMMEDIATE, 0xA9, 2, 2}});
        addressModes.insert({0xA5, InstructionTraits{AddressModes::ZPG, 0xA5, 2, 3}});
        addressModes.insert({0xB5, InstructionTraits{AddressModes::ZPG_X, 0xB5, 2, 4}});
        addressModes.insert({0xAD, InstructionTraits{AddressModes::ABS, 0xAD, 3, 4}});
        addressModes.insert({0xBD, InstructionTraits{AddressModes::ABSX, 0xBD, 3, 4}});
        addressModes.insert({0xB9, InstructionTraits{AddressModes::ABSY, 0xB9, 3, 4}});
        addressModes.insert({0xA1, InstructionTraits{AddressModes::X_IND, 0xA1, 2, 6}});
        addressModes.insert({0xB1, InstructionTraits{AddressModes::IND_Y, 0xB1, 2, 5}});
    }

    // We want to check for nullptr so we know when we can validate instructions.
    InstructionTraits* decode(opcode_t opcode){
        if(!addressModes.contains(opcode)){
            return nullptr;
        }

        information = &addressModes[opcode];
        return &addressModes[opcode];
    }

    InstructionTraits& data() const { return *information; }

    friend std::ostream& operator<<(std::ostream& outs, Instruction<RegisterTypes::LDA> ins){
        return outs;
    }

    std::map<opcode_t, InstructionTraits> addressModes; // contains opcodes as the key, and traits are information about address modes, opcodes, etc as the value.
    InstructionTraits* information; // contains the following information: opcodes, bytes, cycles
    InstructionStatus status;
};
