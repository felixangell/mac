#ifndef __INSTRUCTIONS_H
#define __INSTRUCTIONS_H

/**
    Threw this into a header so it can be used with
    the assembler
*/

/** Instructions */
typedef enum {
    HLT, // 0  -- hlt              :: halts program
    PSH, // 1  -- psh val          :: pushes <val> to stack
    POP, // 2  -- pop              :: pops value from stack
    ADD, // 3  -- add              :: adds top two vals on stack
    MUL, // 4  -- mul              :: multiplies top two vals on stack
    DIV, // 5  -- div              :: divides top two vals on stack
    SUB, // 6  -- sub              :: subtracts top two vals on stack
    SLT, // 7  -- slt reg_a, reg_b :: pushes (reg_a < reg_b) to stack
    MOV, // 8  -- mov reg_a, reg_b :: movs the value in reg_a to reg_b
    SET, // 9  -- set reg, val     :: sets the reg to value
    LOG, // 10 -- log a            :: prints out a
    IF,  // 11 -- if reg val ip    :: if the register == val branch to the ip
    IFN, // 12 -- ifn reg val ip   :: if the register != val branch to the ip
    GLD, // 13 -- gld reg          :: loads a register to the stack
    GPT, // 14 -- gpt reg          :: pushes top of stack to the given register
    NOP  // 15 -- nop              :: nothing
} Instructions;

#endif __INSTRUCTIONS_H