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

extern void print_pc();
extern void print_register(int i);
extern void print_data_addresses();
extern void print_spaces(int num);
extern void print_white_space(int num, int i);
extern void print_white_space(int num, int i);
extern void print_registers();
extern void print_stack_address();
extern void print_state();
extern void print_white_space(int num, int i);