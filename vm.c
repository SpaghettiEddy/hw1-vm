#include "vm.h"
#include "string.h"


void initialize_registers(BOFHeader bfHeader)
{
    regi.hi = 0;
    regi.lo = 0;
    regi.pc = bfHeader.text_start_address;

    for (int i = 0; i < 32; i++)
    {
        regi.GPR[i] = 0;
    }

    regi.GPR[GP] = bfHeader.data_start_address;
    regi.GPR[SP] = bfHeader.stack_bottom_addr;
    regi.GPR[FP] = bfHeader.stack_bottom_addr;
    return;
}

int execute_instr(bin_instr_t instr, BOFFILE bf)
{
    instr_type it = instruction_type(instr);

    switch (it)
    {
    case syscall_instr_type:
        switch (instr.syscall.code)
        {
        case exit_sc:
            ext(bf);
            return 0;
            break;
        case print_str_sc:
            pstr();
            break;
        case print_char_sc:
            pch();
            break;
        case read_char_sc:
            rch();
            break;
        case start_tracing_sc:
            stra();
            break;
        case stop_tracing_sc:
            notr();
            break;
        }
        break;

    case reg_instr_type:
        switch (instr.reg.func)
        {
        case ADD_F:
            add(instr.reg.rs, instr.reg.rt, instr.reg.rd);
            break;
        case SUB_F:
            sub(instr.reg.rs, instr.reg.rt, instr.reg.rd);
            break;
        case MUL_F:
            mult(instr.reg.rs, instr.reg.rt);
            break;
        case DIV_F:
            divi(instr.reg.rs, instr.reg.rt);
            break;
        case MFHI_F:
            mfhi(instr.reg.rd);
            break;
        case MFLO_F:
            mflo(instr.reg.rd);
            break;
        case AND_F:
            and(instr.reg.rs, instr.reg.rt, instr.reg.rd);
            break;
        case BOR_F:
            bor(instr.reg.rs, instr.reg.rt, instr.reg.rd);
            break;
        case NOR_F:
            nor(instr.reg.rs, instr.reg.rt, instr.reg.rd);
            break;
        case XOR_F:
            xor(instr.reg.rs, instr.reg.rt, instr.reg.rd);
            break;
        case SLL_F:
            sll(instr.reg.rt, instr.reg.rd, instr.reg.shift);
            break;
        case SRL_F:
            srl(instr.reg.rt, instr.reg.rd, instr.reg.shift);
            break;
        case JR_F:
            jr(instr.reg.rs);
            break;
        case SYSCALL_F:
            // should never reach here because it will check syscall before reg
            break;
        default:
            break;
        }
        break;

    case immed_instr_type:
        switch (instr.immed.op)
        {
        case ADDI_O:
            addi(instr.immed.rs, instr.immed.rt, instr.immed.immed);
            break;
        case ANDI_O:
            andi(instr.immed.rs, instr.immed.rt, instr.immed.immed);
            break;
        case BORI_O:
            bori(instr.immed.rs, instr.immed.rt, instr.immed.immed);
            break;
        case XORI_O:
            xori(instr.immed.rs, instr.immed.rt, instr.immed.immed);
            break;
        case BEQ_O:
            beq(instr.immed.rs, instr.immed.rt, instr.immed.immed);
            break;
        case BNE_O:
            bne(instr.immed.rs, instr.immed.rt, instr.immed.immed);
            break;
        case BGEZ_O:
            bgez(instr.immed.rs, instr.immed.rt, instr.immed.immed);
            break;
        case BGTZ_O:
            bgtz(instr.immed.rs, instr.immed.rt, instr.immed.immed);
            break;
        case BLEZ_O:
            blez(instr.immed.rs, instr.immed.rt, instr.immed.immed);
            break;
        case BLTZ_O:
            bltz(instr.immed.rs, instr.immed.rt, instr.immed.immed);
            break;
        case LBU_O:
            lbu(instr.immed.rs, instr.immed.rt, instr.immed.immed);
            break;
        case LW_O:
            lw(instr.immed.rs, instr.immed.rt, instr.immed.immed);
            break;
        case SB_O:
            sb(instr.immed.rs, instr.immed.rt, instr.immed.immed);
            break;
        case SW_O:
            sw(instr.immed.rs, instr.immed.rt, instr.immed.immed);
            break;
        default:
            break;
        }
        break;

    case jump_instr_type:
        switch (instr.jump.op)
        {
        case JMP_O:
            jmp(instr.jump.addr);
            break;
        case JAL_O:
            jal(instr.jump.addr);
            break;
        }
        break;

    default: // should never reach
        break;
    }
    return 1;
}


int print_instr(bin_instr_t instr, BOFFILE bf)
{
    instr_type it = instruction_type(instr);

    switch (it)
    {
    case syscall_instr_type:
        switch (instr.syscall.code)
        {
        case exit_sc:
            printf(" EXIT\n");
            return 1;
            break;
        case print_str_sc:
            printf(" PSTR\n");  // REMEMBER TO CHANGE THIS (MAYBE)
            break;
        case print_char_sc:
            printf(" PCH\n");
            break;
        case read_char_sc:
            printf(" RCH\n");
            break;
        case start_tracing_sc:
            printf(" STRA\n");
            break;
        case stop_tracing_sc:
            printf(" NOTR\n");
            break;
        }
        break;

    case reg_instr_type:
        switch (instr.reg.func)
        {
        case ADD_F:
            //add(instr.reg.rs, instr.reg.rt, instr.reg.rd);
            printf(" ADD %s, %s, %s\n", regname_get(instr.reg.rs), regname_get(instr.reg.rt), regname_get(instr.reg.rd));
            break;
        case SUB_F:
            printf(" SUB %s, %s, %s\n", regname_get(instr.reg.rs), regname_get(instr.reg.rt), regname_get(instr.reg.rd));
            break;
        case MUL_F:
            printf(" MUL %s, %s\n", regname_get(instr.reg.rs), regname_get(instr.reg.rt));
            break;
        case DIV_F:
            printf(" DIV %s, %s\n", regname_get(instr.reg.rs), regname_get(instr.reg.rt));
            break;
        case MFHI_F:
            printf(" MFHI %s\n", regname_get(instr.reg.rd));
            break;
        case MFLO_F:
            printf(" MFLO %s\n", regname_get(instr.reg.rd));
            break;
        case AND_F:
            printf(" AND %s, %s, %s\n", regname_get(instr.reg.rs), regname_get(instr.reg.rt), regname_get(instr.reg.rd));
            break;
        case BOR_F:
            printf(" BOR %s, %s, %s\n", regname_get(instr.reg.rs), regname_get(instr.reg.rt), regname_get(instr.reg.rd));
            break;
        case NOR_F:
            printf(" NOR %s, %s, %s\n", regname_get(instr.reg.rs), regname_get(instr.reg.rt), regname_get(instr.reg.rd));
            break;
        case XOR_F:
            printf(" XOR %s, %s, %s\n", regname_get(instr.reg.rs), regname_get(instr.reg.rt), regname_get(instr.reg.rd));
            break;
        case SLL_F:
            printf(" SLL %s, %s, %s\n", regname_get(instr.reg.rt), regname_get(instr.reg.rd), regname_get(instr.reg.shift));
            break;
        case SRL_F:
            printf(" SRL %s, %s, %s\n", regname_get(instr.reg.rt), regname_get(instr.reg.rd), regname_get(instr.reg.shift));
            break;
        case JR_F:
            printf(" JR %s\n", regname_get(instr.reg.rs));
            break;
        case SYSCALL_F:
            // should never reach here because it will check syscall before reg
            break;
        default:
            break;
        }
        break;

    case immed_instr_type:
        switch (instr.immed.op)
        {
        case ADDI_O:
            printf(" ADDI %s, %s, %hu\n", regname_get(instr.immed.rs), regname_get(instr.immed.rt), instr.immed.immed);
            break;
        case ANDI_O:
            printf(" ANDI %s, %s, %hu\n", regname_get(instr.immed.rs), regname_get(instr.immed.rt), instr.immed.immed);
            break;
        case BORI_O:
            printf(" BORI %s, %s, %hu\n", regname_get(instr.immed.rs), regname_get(instr.immed.rt), instr.immed.immed);
            break;
        case XORI_O:
            printf(" XORI %s, %s, %hu\n", regname_get(instr.immed.rs), regname_get(instr.immed.rt), instr.immed.immed);
            break;
        case BEQ_O:
            printf(" BEQ %s, %hu\n", regname_get(instr.immed.rs), instr.immed.immed);  //ADD OFFSET
            break;
        case BNE_O:
            printf(" BNE %s, %hu\n", regname_get(instr.immed.rs), instr.immed.immed);  //ADD OFFSET
            break;
        case BGEZ_O:
            printf(" BGEZ %s, %hu\n", regname_get(instr.immed.rs), instr.immed.immed);  //ADD OFFSET
            break;
        case BGTZ_O:
            printf(" BGTZ %s, %hu\n", regname_get(instr.immed.rs), instr.immed.immed);  //ADD OFFSET
            break;
        case BLEZ_O:
            printf(" BLEZ %s, %hu\n", regname_get(instr.immed.rs), instr.immed.immed);  //ADD OFFSET
            break;
        case BLTZ_O:
            printf(" BLTZ %s, %hu\n", regname_get(instr.immed.rs), instr.immed.immed);  //ADD OFFSET
            break;
        case LBU_O:   //ADD OFFSET
            printf(" LBU %s, %s, %hu\n", regname_get(instr.immed.rs), regname_get(instr.immed.rt), instr.immed.immed);
            break;
        case LW_O:  //ADD OFFSET
            printf(" LW %s, %s, %hu\n", regname_get(instr.immed.rs), regname_get(instr.immed.rt), instr.immed.immed);
            break;
        case SB_O:  //ADD OFFSET
            printf(" SB %s, %s, %hu\n", regname_get(instr.immed.rs), regname_get(instr.immed.rt), instr.immed.immed);
            break;
        case SW_O:  //ADD OFFSET
            printf(" SW %s, %s, %hu\n", regname_get(instr.immed.rs), regname_get(instr.immed.rt), instr.immed.immed);
            break;
        default:
            break;
        }
        break;

    case jump_instr_type:
        switch (instr.jump.op)
        {
        case JMP_O:
            printf(" JMP %hu\n", instr.jump.addr);
            break;
        case JAL_O:
            printf(" JAL %hu\n", instr.jump.addr);
            break;
        }
        break;

    default: // should never reach
        break;
    }
    return 0;
}

int main(int argc, char *argv[])
{

    if (strcmp(argv[1], "-p") == 0)
    {
        BOFFILE bf = bof_read_open(argv[2]);
        BOFHeader bfHeader = bof_read_header(bf);

        initialize_registers(bfHeader);

        
        scan_instructions(bfHeader, bf);
        scan_words(bfHeader, bf);

        printf("Addr Instruction\n");

        int numInstructs = bfHeader.text_length / 4;
    
        for (int i = 0; i < numInstructs; i++) {
            printf("   %d", regi.pc);
            print_instr(mem.instrs[i], bf);
            regi.pc += 4;
        }

        return 0;
    }
    
    BOFFILE bf = bof_read_open(argv[1]);
    BOFHeader bfHeader = bof_read_header(bf);

    initialize_registers(bfHeader);

    // printf("\n%d\n", bfHeader.data_start_address);

    scan_instructions(bfHeader, bf);
    scan_words(bfHeader, bf);

    int test = 1;
    while (test)
    {   
        if(regi.pc >= MEMORY_SIZE_IN_BYTES)
            return 0;
        print_state();
        test = execute_instr(mem.instrs[regi.pc], bf);
        regi.pc += 4;
    }

    return 0;
}