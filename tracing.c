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
    if(regi.pc == 0)
        printf("\t  PC: %u\n", regi.pc);
    else
        printf("\n\t  PC: %u\n", regi.pc);
}

void print_register(char * name_of_reg, int i) {
    printf("GPR: [%s", name_of_reg);
    if (i == 0) printf(" ");
    printf("]: ");
    print_white_space(regi.GPR[i], i);
}

void print_white_space(int num, int i) {
    if ((i == 31) || ((i + 1) % 6 == 0)) {
        printf("\n");
        return;
    }
    int spaces = 3;
    while (num > 0) {
        spaces--;
        num /= 10;
    }
    for (int j = 0; j < spaces; j++) printf(" ");
    printf("\t");
}

void print_registers() {
    printf("GPR[%s ]: 0   	", regname_get(0));
    for (int i = 1; i < 32; i++) {
        if(regi.GPR[i-1] > 1000 || regi.GPR[i] > 1000)
            printf("GPR[%s]: %u  ", regname_get(i), regi.GPR[i]);
        else
            printf("GPR[%s]: %u   	", regname_get(i), regi.GPR[i]);
        if ((i % 6 == 5) || i == 31) printf("\n");
        //print_reg(regname_get(i));
        // print_register(regname_get(i), i);
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
