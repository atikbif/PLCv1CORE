/*
 * elements.c
 *
 *  Created on: 18 окт. 2018 г.
 *      Author: Roman
 */

#include "elements.h"
#include <math.h>

unsigned char open_contact(unsigned char contact, unsigned char inpState){if(contact) return inpState;else return 0;}
unsigned char clos_contact(unsigned char contact, unsigned char inpState){if(contact==0) return inpState;else return 0;}

unsigned char plus_bool(unsigned char a, unsigned char b){return a+b;}
short plus_short(short a, short b){return a+b;}
long plus_long(long a, long b){return a+b;}
double plus_double(double a, double b){return a+b;}

unsigned char minus_bool(unsigned char a, unsigned char b){if(a<b) return 0;return a-b;}
short minus_short(short a, short b){return a-b;}
long minus_long(long a, long b){return a-b;}
double minus_double(double a, double b){return a-b;}

unsigned char relay_bool(unsigned char *v, unsigned char inpState){*v=inpState; return inpState;}
short relay_short(short *v,short inpState){*v=inpState; return inpState;}
long relay_long(long *v, long inpState){*v=inpState; return inpState;}
double relay_double(double *v, double inpState){*v=inpState; return inpState;}

unsigned char relay_enabled_bool(unsigned char *v, unsigned char inpState, short en) {if(en) *v=inpState; return *v;}
short relay_enabled_short(short *v,short inpState, short en) {if(en) *v=inpState; return *v;}
long relay_enabled_long(long *v, long inpState, short en) {if(en) *v=inpState; return *v;}
double relay_enabled_double(double *v, double inpState, short en) {if(en) *v=inpState; return *v;}

unsigned char const_bool(unsigned char value, short inpState){if(inpState) return value;else return 0;}
short const_short(short value, short inpState){if(inpState) return value;else return 0;}
long const_long(long value, short inpState){if(inpState) return value;else return 0;}
double const_double(double value, short inpState){if(inpState) return value;else return 0;}

unsigned char variable_bool(unsigned char v, short inpState){if(inpState) return v; else return 0;}
short variable_short(short v, short inpState){if(inpState) return v; else return 0;}
long variable_long(long v, short inpState){if(inpState) return v; else return 0;}
double variable_double(double v, short inpState){if(inpState) return v; else return 0;}

short sr_trig(short prev_value,short a, short b){
	if(a==0 && b==0) return prev_value;
	if(a==0 && b!=0) return 0;
	return 1;
}
short rs_trig(short prev_value,short a, short b){
	if(a==0 && b==0) return prev_value;
	if(a==0 && b!=0) return 1;
	return 0;
}

short delay_on(short *ms_tmr, short *filter_on, short a, short b){
	if(a==0) {*ms_tmr=0;*filter_on=1;return 0;}
	else
	{
		if(*filter_on) {
			if(*ms_tmr>=b) {*filter_on=0;return 1;}
			else return 0;
		}else return 1;
	}
}
short delay_off(short *ms_tmr, short *filter_on, short a, short b){
	if(a) {*ms_tmr=0;*filter_on=1;return 1;}
	else
	{
		if(*filter_on) {
			if(*ms_tmr>=b) {*filter_on=0;return 0;}
			else return 1;
		}else return 0;
	}
}

short empty(short v){return 0;}

unsigned char greater_bool(unsigned char a, unsigned char b){return a>b;}
unsigned char greater_short(short a,short b){return a>b;}
unsigned char greater_long(long a, long b){return a>b;}
unsigned char greater_double(double a, double b){return a>b;}

unsigned char greater_or_equal_bool(unsigned char a, unsigned char b){return a>=b;}
unsigned char greater_or_equal_short(short a,short b){return a>=b;}
unsigned char greater_or_equal_long(long a, long b){return a>=b;}
unsigned char greater_or_equal_double(double a, double b){return a>=b;}

unsigned char less_bool(unsigned char a, unsigned char b){return a<b;}
unsigned char less_short(short a, short b){return a<b;}
unsigned char less_long(long a, long b){return a<b;}
unsigned char less_double(double a, double b){return a<b;}

unsigned char less_or_equal_bool(unsigned char a, unsigned char b){return a<=b;}
unsigned char less_or_equal_short(short a, short b){return a<=b;}
unsigned char less_or_equal_long(long a, long b){return a<=b;}
unsigned char less_or_equal_double(double a, double b){return a<=b;}

unsigned char multiple_bool(unsigned char a, unsigned char b){return a*b;}
short multiple_short(short a,short b){return a*b;}
long multiple_long(long a, long b){return a*b;}
double multiple_double(double a, double b){return a*b;}

unsigned char divide_bool(unsigned char a, unsigned char b){if(b!=0) return a/b;else return 0;}
short divide_short(short a, short b){if(b!=0) return a/b;else return 0;}
long divide_long(long a, long b){if(b!=0) return a/b;else return 0;}
double divide_double(double a, double b){if(b!=0) return a/b;else return 0;}

unsigned char equal_bool(unsigned char a, unsigned char b){return a==b;}
short equal_short(short a,short b){return a==b;}
long equal_long(long a, long b){return a==b;}
unsigned char equal_double(double a, double b){return fabs(a-b)<=1e-5;}

unsigned char not_equal_bool(unsigned char a, unsigned char b){return a!=b;}
short not_equal_short(short a,short b){return a!=b;}
long not_equal_long(long a, long b){return a!=b;}
unsigned char not_equal_double(double a, double b){return fabs(a-b)>1e-5;}

unsigned char not_operation_bool(unsigned char a) {if(a) return 0;return 1;}
unsigned char not_operation_short(short a) {if(a) return 0;return 1;}
unsigned char not_operation_long(long a) {if(a) return 0;return 1;}
unsigned char not_operation_double(double a) {if(a>1e-5) return 0;return 1;}
