#ifndef _SCANBOF_H
#define _SCANBOF_H

#include <stdio.h>
#include "machine_types.h"
#include "bof.h"
#include "instruction.h"
#include "regname.h"
#include "utilities.h"
#include "file_location.h"
#include "vm.h"


extern void scan_instructions(BOFHeader bfHeader, BOFFILE bf);
 
extern void scan_words(BOFHeader bfHeader, BOFFILE bf);


#endif