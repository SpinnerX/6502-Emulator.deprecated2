#pragma once
#include <cstring>
#include <type_traits>
#include <cstdlib>
#include <traits/types.h>
#include <traits/CustomEnumeration.h>



/**
 * 
 * InstructionTraits
 * - Contain specialized templates, that are traits very dependent on the type of instructions and the opcodes with the corresponding address modes to them.
 * 
 * Base template specialization
 * - Allowing to create generalized way of retrieving data based on opcode to Address Modes
 * 
*/
// template<RegisterTypes type = RegisterTypes::DEFAULT, AddressModes mode = AddressModes::NOT_FOUND>
// struct InstructionTraits{
//     static constexpr opcode_t opcode = 0x00; // Default opcode
//     static constexpr int bytes = 0;
//     static constexpr int cycles = 0;
// };

struct InstructionTraits{
    AddressModes mode;
    opcode_t opcode;
    int bytes;
    int cycles;

    friend std::ostream& operator<<(std::ostream& outs, InstructionTraits& traits){
        outs << "---------[";
        if(traits.mode == AddressModes::IMMEDIATE){
            outs << "Immediate";
        }
        else if(traits.mode == AddressModes::ZPG){
            outs << "ZeroPage";
        }
        else if(traits.mode == AddressModes::ZPG_X){
            outs << "ZeroPage X";
        }
        else if(traits.mode == AddressModes::ABS){
            outs << "Absolute";
        }
        else if(traits.mode == AddressModes::ABSX) {
            outs << "Absolute X";
        }
        else if(traits.mode == AddressModes::ABSY){
            outs << "Absolute Y";
        }
        else if(traits.mode == AddressModes::X_IND){
            outs << "Indirect X";
        }
        else if(traits.mode == AddressModes::IND_Y){
            outs << "Indirect Y";
        }
        else{
            outs << "Address mode not found!";
        }
        outs << "]---------\n";
        outs << "OpCode: " << reinterpret_cast<void *>(traits.opcode) << '\n';
        outs << "Bytes: " << traits.bytes << '\n';
        outs << "Cycles: " << traits.cycles;

        return outs;
    }

};

struct InstructionStatus{
    Byte N : 1; //  Negative
    Byte Z : 1; // Overflow
    Byte C : 1; // Carry
    Byte I : 1; // Interrupt (IQR disable)
    Byte D : 1; // Decimal (use BCD for arithmetics)
    Byte V : 1; // Overflow
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

// template<RegisterTypes type = RegisterTypes::DEFAULT>
// struct InstructionTraits<type, AddressModes::IMMEDIATE>{
//     opcode_t opcode = 0xA9;
//     int bytes = 2;
//     int cycles = 2;
// };
