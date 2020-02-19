#include "ld_prog.h"
#include "elements.h"
#include "iodef.h"

#include "os_conf.h"

unsigned short plc_cycle = 1;

unsigned short ain[AI_CNT];
unsigned short ain_raw[AI_CNT];
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
unsigned short ireg[IREG_CNT];
unsigned short frsh[FRSH_CNT];
double frd[FRD_CNT];
unsigned long frl[FRL_CNT];


extern unsigned short work_time;



unsigned short p1_v1=1;
unsigned short p1_v9=0;
unsigned short p1_v17=0;
unsigned short p1_v25=0;
unsigned short p1_v33=0;
unsigned short p1_v34=0;
unsigned short p1_v35=0;
unsigned short p1_v36=0;
unsigned short p1_v37=0;

void inc_timers(){
}

void calculate_adc() {

}

void ld_process(void) {
	p1_v34=variable_unsigned_short(AI1,p1_v1);
	p1_v9=relay_unsigned_short(&IR1,p1_v34);
	p1_v35=variable_unsigned_short(AI2,p1_v1);
	p1_v17=relay_unsigned_short(&IR2,p1_v35);
	p1_v36=variable_unsigned_short(AI3,p1_v1);
	p1_v25=relay_unsigned_short(&IR3,p1_v36);
	p1_v37=variable_unsigned_short(AI4,p1_v1);
	p1_v33=relay_unsigned_short(&IR4,p1_v37);
}
