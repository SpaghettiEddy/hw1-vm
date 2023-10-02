#ifndef _VM_H
#define _VM_H

#include <stdio.h>
#include <stdlib.h>
#include "machine_types.h"
#include "instruction.h"
#include "bof.h"
#include "regname.h"
#include "scanbof.h"
#include "sys.h"
#include "reg.h"
#include "jump.h"
#include "immed.h"
#include "utilities.h"
#include "file_location.h"
#include "disasm.h"
#include "tracing.h"


#define V0 2
#define A0 4

// a size for the memory (2^16 bytes = 64k)
#define MEMORY_SIZE_IN_BYTES (65536 - BYTES_PER_WORD)
#define MEMORY_SIZE_IN_WORDS (MEMORY_SIZE_IN_BYTES / BYTES_PER_WORD)

#define MAX_STACK_HEIGHT 4096 //subject to change, might be wrong

typedef union mem_u
{
    byte_type bytes[MEMORY_SIZE_IN_BYTES];
    word_type words[MEMORY_SIZE_IN_WORDS];
    bin_instr_t instrs[MEMORY_SIZE_IN_WORDS];
} memory;

typedef struct
{
    address_type GPR[32];
    address_type hi;
    address_type lo;
    address_type pc;
    int is_tracing;
} registers;

typedef struct
{
    address_type data_start;
    word_type data_len;
} data_t;

memory mem;
registers regi;
data_t dat;

extern void initialize_registers(BOFHeader bfHeader);
extern int execute_instr(bin_instr_t instr, BOFFILE bf);






#endif