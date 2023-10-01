//https://docs.google.com/document/d/1ohnhCke5x50EayAiX12ILtaUIqgd402k976kyCdhpZw/edit


#ifndef _IMMED_H
#define _IMMED_H


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
// memory is accessed as reg.mem, i didn't know how we were accessing memory, do we have that in our struct?
// work on sb, accessing least significant beat


// do you wanna take out the gpr, hi, lo, and put it into vm straight? instead of making a struct to group them up`
extern void addi(int s, int t, immediate_type i);
extern void andi(int s, int t, immediate_type i);
extern void bori(int s, int t, immediate_type i);
extern void xori(int s, int t, immediate_type i);
extern void beq(int s, int t, immediate_type o);
extern void bne(int s, int t, immediate_type o);
extern void bgez(int s, int t, immediate_type o);
extern void bgtz(int s, int t, immediate_type o);
extern void blez(int s, int t, immediate_type o);
extern void bltz(int s, int t, immediate_type o);
extern void lbu(int b, int t  , immediate_type o);
extern void lw(int b, int t  , immediate_type o);
extern void sb(int b, int t  , immediate_type o);
extern void sw(int b, int t  , immediate_type o);


#endif



