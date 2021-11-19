
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <signal.h>
/* unix */
#include <unistd.h>
#include <fcntl.h>

#include <sys/time.h>
#include <sys/types.h>
#include <sys/termios.h>
#include <sys/mman.h>

#define PC_START 0x3000
enum {
    BR,ADD,LD,ST,
    JSR,AND,LDR,STR,
    RTI,NOT,LDI,STI,
    LMP,RES,LEA,TRAP
};

enum {
    R0,R1,R2,R3,
    R4,R5,R6,R7,
    PC,CND
    RCOUNT;
};

enum {
    FL_POS=1<<0,
    FL_ZERO=1<<1,
    FL_NEG=1<<2
};

uint16_t memory[UINT16_MAX];
uint16_t regs[RCOUNT];

uint16_t sign_extend(uint16_t x,uint8_t bit_count) {
    if((x>>(bit_count-1))&1) {
        x|=0xffff<<bit_count;
    }
    return x;
}

void update_flags(uint16_t r) {
    if(regs[r]==0) {
        regs[CND]=FL_ZERO;
    } else if(regs[r]>>15) {
        regs[CND]=FL_NEG;
    } else {
        regs[CND]=FL_POS;
    }
}
int main(int argc,char* argv[]) {
    regs[PC]=PC_START;
    uint8_t running=1;
    while(running) {
        if(argc<2) {
            printf("Usage: %s [image] ...\n",argv[0]);
            exit(1);
        }
        for(int itr=1;itr<argc;itr++) {
            if(!read_image(argv[itr])) {
                printf("Error loading image file %s\n",argv[itr]);
            }
        }
        uint16_t instr=mem_read(regs[PC]++);
        uint16_t op=instr>>12;
        switch(op) {
            case ADD:
                {
                    uint16_t r0=(instr>>9)&0x7;
                    uint16_t r1=(instr>>6)&0x7;
                    uint16_t imm_flag=(instr>>5)&0x1;
                    if(imm_flag) {
                        uint16_t imm5=sign_extend(instr&0x1f,5);
                        regs[r0]=regs[r1]+imm5;
                    } else {
                        uint16_t r2=instr&0x7;
                        regs[r0]=regs[r1]+regs[r2];
                    }
                    update_flags(r0);
                }
                break;
            case AND:
                break
            case BR:
                break;
            case JMP:
                break;
            case JSR:
                break;
            case LD:
                break;
            case LDI:
                {
                    uint16_t r0=(instr>>9)&0x7;
                    uint16_t pc_offset=sign_extend(instr&0x1ff,9);
                    
                    regs[r0]=mem_read(mem_read(regs[PC]+pc_offset));
                    update_flags(r0);
                    
                }
                break;
            case LDR:
                break;
            case LEA:
                break;
            case NOT:
                break;
            case RET:
                break;
            case RTI:
                break;
            case ST:
                break;
            case STI:
                break;
            case STR:
                break;
            case TRAP:
                break;
            default:
                break;
        }
    }
}
