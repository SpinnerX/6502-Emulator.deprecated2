#pragma once
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <traits/types.h>
#include <array>
#include <ctime>
#include <stdio.h>
#include <unistd.h>
#include <map>
#include <set>
#include <unordered_map>
#include <Registers/RegisterExperiemental.h>
#include <Configurations/Memory.h>

/**
 * 
 * CPU Information
 * PC - program counter (8 bits, 1 byte): Holds the memory address of the next instruction going to be fetched, decoded, and executed.
 * SP - stack pointer (16 bits, 2 bytes): Used to keep track of the current position on the stack
 * A - accumulator (8 bits, 1 byte): main register used for arithmetic and logical operations
 * X - index register (8 bits, 1 byte): primarily used for indexing memory locations or as a counter.
 * Y - index register (8 bits, 1 byte): used for indexing memory or as a counter
 * Reset Vector - (16 bits, 2 bytes): stores memory addresses where CPU starts execution after reset signal received.
 * 
*/

class CPU{
    CPU() = default;

    // This is how the CPU configures the instructions, during the boot up phase
    void memoryConfigurations(){}

    opcode_t fetch(){
        PC++;
        std::cout << "Program Counter: " << PC << '\n';
        return memory[PC];
    }

    void decode(opcode_t opcode){}

    // Application user only should execute this function without creating an instance of an object directly from main.
    friend void execute(bool isCpuRunning);

    /*
        resetVector = 0xFFFFC;
        PC = 0x0000; // 0x0000 to 0xFFFF
        SP = 0xFF; // 0x0100
        AC = 0;
        X = 0;
        Y = 0;
    */
    Bytes2 PC = 0x0000; // Program Counter
    Byte SP=0xFF; // Stack Ptr
    Byte A = 0; // accumulator
    Byte X = 0; // index-reg
    Byte Y = 0; // index-reg
    std::array<u8, 65536> memory; // Ram Memory
    int resetVector = 0xFFFFC;
};

void execute(bool isCpuRunning){
    CPU cpu = CPU();
    Instruction<RegisterTypes::LDA> lda{};
    std::array<u8, 65536> ramMemory;
    ramMemory[0xFFFC] = 12;
    uint16_t reset_vector_address = 0xFFFC;

    std::cout << reinterpret_cast<void *>(ramMemory[reset_vector_address+1]) << '\n';
    std::cout << reinterpret_cast<void *>( ramMemory[reset_vector_address+2]) << '\n';
    std::cout << reinterpret_cast<void *>( ramMemory[reset_vector_address+3]) << '\n';

    uint16_t resetVector = (ramMemory[reset_vector_address] << 8) | ramMemory[0xFFFC];
    // std::cout << reinterpret_cast<void *>(resetVector) << '\n';
    uint16_t PC = resetVector; // This is how we start executing the first instructions.
    std::cout << "Value: " << reinterpret_cast<void *>( ramMemory[0xFFFC]) << '\n';

    
    /*
    while(isCpuRunning){
        // opcode_t opcode = cpu.fetch();
        opcode_t opcode = ramMemory[cpu.PC++];
        InstructionTraits* t = lda.decode(opcode);
        std::cout << "Current Iterating Opcode: " << reinterpret_cast<void *>(opcode) << '\n';
        if(t != nullptr){
            std::cout << t << '\n';
        }
        // cpu.PC++;
        sleep(1);
    }
    */
}