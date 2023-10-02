#include <stdio.h>
#include "vm.h"
#include "machine_types.h"
#include "bof.h"
#include "instruction.h"
#include "regname.h"
#include "utilities.h"
#include "file_location.h"
#include "reg.h"
#include "jump.h"
#include "immed.h"
#include "sys.h"
#include "scanbof.h"

void print_pc() {
    printf("\t  PC: %u\n", regi.pc);
}
void print_registers() {
    for (int i = 0; i < 32; i++) {
        char * new_line = {((i % 6 == 5) || (i == 31)) * '\n'};
        printf("GPR[%s]: %u\t%s", regname_get(i), regi.GPR[i], new_line);
    }
}
void print_pointers() {
    printf("...pointers...\n");
}

void print_stack_address() {
    printf("==> addr:\t%u %s", regi.pc, instruction_assembly_form(mem.instrs[regi.pc / 4]));
}

void print_state() {
    print_pc();
    print_registers();
    print_pointers();
    print_stack_address();
}
