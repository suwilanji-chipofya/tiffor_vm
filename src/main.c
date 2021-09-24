#include <stdio.h>
#include <stdint.h>

enum {
R_R0,
R_R1,
R_R2,
R_R3,
R_R4,
R_R5,
R_R6,
R_R7,
R_R8,
R_R9,
R_RA
,R_RB,
R_RC,
R_RD,
R_RE,
R_RF,
R_PC,
R_COUNT};
uint16_t memory[UINT16_MAX];
uint16_t regs[R_COUNT];
int main(int argc,char* argv[]) {
    printf("Hello, World\n");
    return 0;
}
