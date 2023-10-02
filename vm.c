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
            printf("%4d", regi.pc);
            printf(" %s\n", instruction_assembly_form(mem.instrs[regi.pc / 4]));
            regi.pc += 4;
        }

        return 0;
    }
    
    BOFFILE bf = bof_read_open(argv[1]);
    BOFHeader bfHeader = bof_read_header(bf);

    initialize_registers(bfHeader);

    scan_instructions(bfHeader, bf);
    scan_words(bfHeader, bf);

    // for (int i = 0; i < bfHeader.text_length / 4; i++)
    // {
    //     printf("%d\n", i);
    //     print_instr(mem.instrs[i], bf);
    //     regi.pc += 4;
    // }

    int test = 1;
    regi.is_tracing = 1;
    printf("is_tracing is: %d\n", regi.is_tracing);
    while (test != 0)
    {   
        if(regi.pc >= MEMORY_SIZE_IN_BYTES)
            return 0;
        if(regi.is_tracing)
            print_state();
        test = execute_instr(mem.instrs[regi.pc / 4], bf);
        regi.pc += 4;
    }

    return 0;
}