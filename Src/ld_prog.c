#include "ld_prog.h"
#include "elements.h"
#include "iodef.h"

#include "os_conf.h"

unsigned short plc_cycle = 1;

short ain[AI_CNT];
short ain_raw[AI_CNT];
unsigned char ain_under[AI_CNT];
unsigned char ain_over[AI_CNT];
unsigned char ain_alarm[AI_CNT];
unsigned char din[DI_CNT];
unsigned char dinr[DI_CNT];
unsigned char dinf[DI_CNT];
unsigned char dout[DO_CNT];
unsigned char ibit[IBIT_CNT];
unsigned short tmrms[TMRMS_CNT];
unsigned short tmrs[TMRS_CNT];
short ireg[IREG_CNT];
short frsh[FRSH_CNT];
double frd[FRD_CNT];
long frl[FRL_CNT];


extern unsigned short work_time;



short p1_v1=1;
short p1_v9=0;
short p1_v17=0;
short p1_v25=0;
short p1_v33=0;
short p1_v34=0;
short p1_v35=0;
short p1_v36=0;
short p1_v37=0;

void inc_timers(){
}

void calculate_adc() {

}

void ld_process(void) {
	p1_v34=variable_short(AI1,p1_v1);
	p1_v9=relay_short(&IR1,p1_v34);
	p1_v35=variable_short(AI2,p1_v1);
	p1_v17=relay_short(&IR2,p1_v35);
	p1_v36=variable_short(AI3,p1_v1);
	p1_v25=relay_short(&IR3,p1_v36);
	p1_v37=variable_short(AI4,p1_v1);
	p1_v33=relay_short(&IR4,p1_v37);
}
