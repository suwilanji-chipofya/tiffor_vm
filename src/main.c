#include <stdio.h>

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE (UINT16_MAX*2)
enum Registers {
    R_R0,
    R_R1,
    R_R2,
    R_R3,
    R_R4,
    R_R5,
    R_R6,
    R_R7,
    R_COND,
    R_PC,
    R_SP,
    R_COUNT
};

enum Instructions {
    HALT,
    STR,
    LD,
    MOV,
    ADD,
    SUB,
    MUL,
    DIV,
    AND,
    OR,
    RET,
    RETS,
    LOOP,
    BREAK
};

static uint16_t opCode,reg_1,reg_2,reg_3,imm;
static uint16_t memory[UINT16_MAX]={0x3000,0x3319,0xC004,0xD000,0xB000,0x0000};
static uint16_t stack[STACK_SIZE]={0};
static uint16_t regs[R_COUNT]={0};
uint16_t fetch() {
    return memory[regs[R_PC]++];
}
void decode(uint16_t instr) {
    opCode=(instr&0xf000)>>12;
    reg_1=(instr&0xf00)>>8;
    reg_2=(instr&0xf0)>>4;
    reg_3=(instr&0xf);
    imm=(instr&0xff);
}

void execute(instr) {
        decode(instr);
        switch(opCode) {
            case 0x0:
                exit(EXIT_SUCCESS);
                break;
            case 0x1:
                regs[R_SP]++;
                if(reg_1==0) {
                    //store register
                    stack[regs[R_SP]]=regs[reg_2];
                } else {
                    stack[regs[R_SP]]=imm;
                }
                break;
            case 0x2:
                //load value from stack and store in reg_1
                regs[reg_1]=stack[reg_2];
                printf("%c ",regs[reg_1]);
                break;
            case 0x3:
                printf("%d\n",imm);
                regs[reg_1]=imm;
                break;
            case 0x4:
                regs[reg_1]=regs[reg_2]+regs[reg_3];
                break;
            case 0x5:
                regs[reg_1]=regs[reg_2]-regs[reg_3];
                break;
            case 0x6:
                regs[reg_1]=regs[reg_2]*regs[reg_3];
                break;
            case 0x7:
                regs[reg_1]=regs[reg_2]/regs[reg_3];
                break;
            case 0x8:
                regs[R_R0]=regs[reg_1]&regs[reg_2];
                break;
            case 0x9:
                regs[R_R0]=regs[reg_1]|regs[reg_2];
                break;
            case 0xA:
                printf("%d",regs[reg_1]);
                break;
            case 0xB:
                
                for(int i=0;i<=regs[R_R3];i++) {
                    printf("%c",stack[regs[R_R0]]);
                    regs[R_R0]++;
                }
                break;
            case 0xC:
                while(1) {
                    regs[R_PC]=imm;
                    execute(memory[regs[R_PC]]);
                }
                break;
            case 0xD:
                break;
            case 0xE:
                break;
            case 0xF:
                break;
                
            default:
                break;
        }
}
int run() {
    bool running=true;
    while(running) {
        uint16_t instr=fetch();
        execute(instr);
    }
    return 0;
}
int main() {
    for(int i=0;i<=25;++i) {
        stack[i]=65+i;
    }
    run();
    printf("\n");
    return 0;
}
