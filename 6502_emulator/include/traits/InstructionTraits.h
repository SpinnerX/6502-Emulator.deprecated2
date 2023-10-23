#pragma once
#include <cstring>
#include <type_traits>
#include <cstdlib>
#include <traits/types.h>


/**
 * 
 * InstructionTraits
 * - Contain specialized templates, that are traits very dependent on the type of instructions and the opcodes with the corresponding address modes to them.
 * 
 * Base template specialization
 * - Allowing to create generalized way of retrieving data based on opcode to Address Modes
 * 
*/
template<RegisterTypes register_t, AddressModes mode, typename = void>
struct InstructionTraits{
    static constexpr opcode_t opcode = 0x00; // Default opcode
    static constexpr int bytes = 0;
    static constexpr int cycles = 0;
};



/**
 * 
 * 
 * LDA Instruction Traits Information (based on opcodes to Address Modes)
 * 
 * Basically allows us to generalize how we can retrieve information based on the Instructions
 * 
 * -- Example -- (in pseudo-code)
 * 
 * NOTE: Context is that it makes it easier to know what information we may want to retrieve
 * NOTE: So, when we go through the fetch, decode, and execute process it would be easier to extract this information (for the time being)
 * 
 * Instruction(){
 *      opcode = InstructionTraits<RegisterType, AddressMode>::opcode;
 *      bytes = InstructionTraits<RegisterType, AddressMode>::bytes;
 *      cycles = InstructionTraits<RegisterType, AddressMode>::cycles;
 * }
 * 
 * 
 * 
 * 
*/

template<>
struct InstructionTraits<RegisterTypes::LDA, AddressModes::IMMEDIATE>{
    static constexpr opcode_t opcode = 0xA9;
    static constexpr int bytes = 2;
    static constexpr int cycles = 2;
};

template<>
struct InstructionTraits<RegisterTypes::LDA, AddressModes::ZPG>{
    static constexpr opcode_t opcode = 0xA5;
    static constexpr int bytes = 2;
    static constexpr int cycles = 3;
};

template<>
struct InstructionTraits<RegisterTypes::LDA, AddressModes::ZPG_X>{
    static constexpr opcode_t opcode = 0xB5;
    static constexpr int bytes = 2;
    static constexpr int cycles = 4;
};

template<>
struct InstructionTraits<RegisterTypes::LDA, AddressModes::ABS>{
    static constexpr opcode_t opcode = 0xAD;
    static constexpr int bytes = 3;
    static constexpr int cycles = 4;
};

template<>
struct InstructionTraits<RegisterTypes::LDA, AddressModes::ABSX>{
    static constexpr opcode_t opcode = 0xBD;
    static constexpr int bytes = 3;
    static constexpr int cycles = 4;
};

template<>
struct InstructionTraits<RegisterTypes::LDA, AddressModes::ABSY>{
    static constexpr opcode_t opcode = 0xB9;
    static constexpr int bytes = 3;
    static constexpr int cycles = 4;
};

template<>
struct InstructionTraits<RegisterTypes::LDA, AddressModes::X_IND>{
    static constexpr opcode_t opcode = 0xA1;
    static constexpr int bytes = 2;
    static constexpr int cycles = 6;
};

template<>
struct InstructionTraits<RegisterTypes::LDA, AddressModes::IND_Y>{
    static constexpr opcode_t opcode = 0xB1;
    static constexpr int bytes = 2;
    static constexpr int cycles = 5;
};