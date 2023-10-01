#include <stdio.h>
#include "machine_types.h"
#include "bof.h"
#include "instruction.h"
#include "regname.h"
#include "utilities.h"
#include "file_location.h"
#include "vm.h"
#include "scanbof.h"


extern void scan_instructions(BOFHeader bfHeader, BOFFILE bf) {
    int numOfInstructs = bfHeader.text_length / 4;
    for (int i = 0; i < numOfInstructs; i++)
    {
        mem.instrs[bfHeader.text_start_address + i] = instruction_read(bf);
    }
    return;
}


extern void scan_words(BOFHeader bfHeader, BOFFILE bf) {
    int numOfWords = bfHeader.data_length / 4;
    for(int i = 0; i < numOfWords; i++)
    {
        mem.words[bfHeader.data_start_address + i] = bof_read_word(bf);
    }
    return;
}