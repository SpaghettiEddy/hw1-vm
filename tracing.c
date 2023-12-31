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

void print_register(int i) {
    printf("GPR[%s", regname_get(i));
    if (i == 0) printf(" ");
    printf("]: %d", regi.GPR[i]);
    print_white_space(regi.GPR[i], i);
}

// Assuming addresses should be stored as words and not bytes
// address might be wrong, other comment line might be right
void print_data_addresses() {
    int is_zero = 0;
    for (int i = 0; i < dat.data_len; i++) {
        // int offset = i / 4;
        if(is_zero == 1)
            break;
        int offset = i;
        int address = offset * 4 + dat.data_start;
        if(mem.words[offset + dat.data_start] == 0)
            is_zero = 1;
        print_spaces(address);
        //printf(" ");
        printf("%d: %u", address, mem.words[offset + dat.data_start]);
        if ((i + 1) % 6 == 0) printf("\n");
        else if (i != dat.data_len) printf("\t     ");
    }
    printf("\t...\n");
    printf("%d: %u", (((dat.data_start + dat.data_len) - 4) * 4), mem.words[dat.data_len + dat.data_start]);
    printf("\t...\n");
}

void print_spaces(int num) {
    int spaces = 4 - (num == 0);
    while (num > 0) {
        spaces--;
        num /= 10;
    }
    for (int j = 0; j < spaces; j++) printf(" ");
}

void print_white_space(int num, int i) {
    if ((i == 31) || ((i + 1) % 6 == 0)) {
        printf("\n");
        return;
    }
    print_spaces(num);
    printf("\t");
}


void print_registers() {
    // printf("GPR[%s ]: 0   	", regname_get(0)); // Change i = 1 back if needs fixing
    for (int i = 0; i < 32; i++) {
        // if(regi.GPR[i-1] > 1000 || regi.GPR[i] > 1000)
        //     printf("GPR[%s]: %u  ", regname_get(i), regi.GPR[i]);
        // else
        //     printf("GPR[%s]: %u   	", regname_get(i), regi.GPR[i]);
        // if ((i % 6 == 5) || i == 31) printf("\n");
        // print_reg(regname_get(i));
        print_register(i);
    }
}

void print_stack_address() {
    printf("==> addr:\t%u %s", regi.pc, instruction_assembly_form(mem.instrs[regi.pc / 4]));
}

void print_state() {
    print_pc();
    print_registers();
    print_data_addresses();
    print_stack_address();
}
