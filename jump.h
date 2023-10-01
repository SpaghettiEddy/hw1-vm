#ifndef _JUMP_H
#define _JUMP_H

#include <stdio.h>
#include "vm.h"
#include "machine_types.h"
#include "bof.h"
#include "instruction.h"
#include "regname.h"
#include "utilities.h"
#include "file_location.h"
#include "reg.h"
#include "immed.h"
#include "sys.h"
#include "scanbof.h"

//stuff goes here
extern void jmp(address_type a);
extern void jal(address_type a);

#endif