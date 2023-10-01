//https://docs.google.com/document/d/1ohnhCke5x50EayAiX12ILtaUIqgd402k976kyCdhpZw/edit?usp=sharing

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
// memory is accessed as regi.mem
// work on sb, accessing least significant beat


void addi(int s, int t, immediate_type i) {
    regi.GPR[t] = regi.GPR[s] + i;
    return;
}

void andi(int s, int t, immediate_type i) {
    regi.GPR[t] = regi.GPR[s] & machine_types_zeroExt(i);
    return;
}

void bori(int s, int t, immediate_type i) {
    regi.GPR[t] = regi.GPR[s] | machine_types_zeroExt(i);
    return;
}

void xori(int s, int t, immediate_type i) {
    regi.GPR[t] = regi.GPR[s] ^ machine_types_zeroExt(i);
    return;
}

void beq(int s, int t, immediate_type o) {
    if (regi.GPR[t] == regi.GPR[s]) regi.pc += machine_types_formOffset(o);
    return;
}

void bne(int s, int t, immediate_type o) {
    if (regi.GPR[t] != regi.GPR[s]) regi.pc += machine_types_formOffset(o);
    return;
}

void bgez(int s, int t, immediate_type o) {
    if (regi.GPR[s] >= 0) regi.pc += machine_types_formOffset(o);
    return;
}

void bgtz(int s, int t, immediate_type o) {
    if (regi.GPR[s] > 0)  regi.pc += machine_types_formOffset(o);
    return;
}

void blez(int s, int t, immediate_type o) {
    if (regi.GPR[s] <= 0) regi.pc += machine_types_formOffset(o);
    return;
}

void bltz(int s, int t, immediate_type o) {
    if (regi.GPR[s] < 0)  regi.pc += machine_types_formOffset(o);
    return;
}

void lbu(int b, int t, immediate_type o) {
    regi.GPR[t] = machine_types_zeroExt(mem.bytes[regi.GPR[b] + machine_types_formOffset(o)]); //accessing bytes
    return;
}

void lw(int b, int t, immediate_type o) {
    regi.GPR[t] = mem.words[regi.GPR[b] + machine_types_formOffset(o)]; //accessing words
    return;
}

void sb(int b, int t  , immediate_type o) { // least significant bit
    mem.bytes[regi.GPR[b] + machine_types_formOffset(o)] = regi.GPR[t]; //accessing bytes
    return;
}

void sw(int b, int t, immediate_type o) {
    mem.words[regi.GPR[b] + machine_types_formOffset(o)] = regi.GPR[t]; //accessing words
    return;
}




