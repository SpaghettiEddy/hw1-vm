#include <stdio.h>
#include "sys.h"
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

void ext(BOFFILE bf)
{
    bof_close(bf);
}

void pstr()
{
    regi.GPR[V0] = printf("%s", (char *)&mem.words[regi.GPR[A0]]);
}

void pch()
{
    regi.GPR[V0] = fputc(regi.GPR[A0], stdout);
}

void rch()
{
    regi.GPR[V0] = getc(stdin);
}

void stra()
{
    is_tracing = 1;
}

void notr()
{
    is_tracing = 0;
}
