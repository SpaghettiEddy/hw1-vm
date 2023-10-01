//https://docs.google.com/document/d/1ohnhCke5x50EayAiX12ILtaUIqgd402k976kyCdhpZw/edit

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

void jmp(address_type a) {
    regi.pc = machine_types_formAddress(regi.pc, a);
    return;
}

void jal(address_type a) {
    regi.GPR[RA] = regi.pc; 
    regi.pc = machine_types_formAddress(regi.pc, a);
    return;
}
