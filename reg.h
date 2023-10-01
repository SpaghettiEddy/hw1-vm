#ifndef _REG_H
#define _REG_H

#include <stdio.h>
#include "vm.h"
#include "machine_types.h"
#include "bof.h"
#include "instruction.h"
#include "regname.h"
#include "utilities.h"
#include "file_location.h"
#include "reg.h"



extern void add(int s, int t, int d);

extern void sub(int s, int t, int d);

extern void mult(int s, int t);

extern void divi(int s, int t);

extern void mfhi(int d);

extern void mflo(int d);

extern void and (int s, int t, int d);

extern void bor(int s, int t, int d);

extern void nor(int s, int t, int d);

extern void xor (int s, int t, int d);

extern void sll(int t, int d, int h);

extern void srl(int t, int d, int h);

extern void jr(int s);

#endif
