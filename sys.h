#ifndef _SYS_H
#define _SYS_H
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
#include "scanbof.h"

extern void ext(BOFFILE bf);
extern void pstr();
extern void pch();
extern void rch();
extern void stra();
extern void notr();

#endif
