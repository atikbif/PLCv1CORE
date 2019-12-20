/*
 * elements.h
 *
 *  Created on: 18 окт. 2018 г.
 *      Author: Roman
 */

#ifndef ELEMENTS_H_
#define ELEMENTS_H_

unsigned char open_contact(unsigned char contact, unsigned char inpState);
unsigned char clos_contact(unsigned char contact, unsigned char inpState);

unsigned char plus_bool(unsigned char a, unsigned char b);
short plus_short(short a, short b);
long plus_long(long a, long b);
double plus_double(double a, double b);

unsigned char minus_bool(unsigned char a, unsigned char b);
short minus_short(short a, short b);
long minus_long(long a, long b);
double minus_double(double a, double b);

unsigned char relay_bool(unsigned char *v, unsigned char inpState);
short relay_short(short *v,short inpState);
long relay_long(long *v, long inpState);
double relay_double(double *v, double inpState);

unsigned char relay_enabled_bool(unsigned char *v, unsigned char inpState, short en);
short relay_enabled_short(short *v,short inpState, short en);
long relay_enabled_long(long *v, long inpState, short en);
double relay_enabled_double(double *v, double inpState, short en);

unsigned char const_bool(unsigned char value, short inpState);
short const_short(short value, short inpState);
long const_long(long value, short inpState);
double const_double(double value, short inpState);

unsigned char variable_bool(unsigned char v, short inpState);
short variable_short(short v, short inpState);
long variable_long(long v, short inpState);
double variable_double(double v, short inpState);

short sr_trig(short prev_value,short a, short b);
short rs_trig(short prev_value,short a, short b);

short delay_on(short *ms_tmr, short *prev_ip, short a, short b);
short delay_off(short *ms_tmr, short *prev_ip, short a, short b);

short empty(short v);

unsigned char greater_bool(unsigned char a, unsigned char b);
unsigned char greater_short(short a,short b);
unsigned char greater_long(long a, long b);
unsigned char greater_double(double a, double b);

unsigned char greater_or_equal_bool(unsigned char a, unsigned char b);
unsigned char greater_or_equal_short(short a,short b);
unsigned char greater_or_equal_long(long a, long b);
unsigned char greater_or_equal_double(double a, double b);

unsigned char less_bool(unsigned char a, unsigned char b);
unsigned char less_short(short a, short b);
unsigned char less_long(long a, long b);
unsigned char less_double(double a, double b);

unsigned char less_or_equal_bool(unsigned char a, unsigned char b);
unsigned char less_or_equal_short(short a, short b);
unsigned char less_or_equal_long(long a, long b);
unsigned char less_or_equal_double(double a, double b);

unsigned char multiple_bool(unsigned char a, unsigned char b);
short multiple_short(short a,short b);
long multiple_long(long a, long b);
double multiple_double(double a, double b);

unsigned char divide_bool(unsigned char a, unsigned char b);
short divide_short(short a, short b);
long divide_long(long a, long b);
double divide_double(double a, double b);

unsigned char equal_bool(unsigned char a, unsigned char b);
short equal_short(short a,short b);
long equal_long(long a, long b);
unsigned char equal_double(double a, double b);

unsigned char not_equal_bool(unsigned char a, unsigned char b);
short not_equal_short(short a,short b);
long not_equal_long(long a, long b);
unsigned char not_equal_double(double a, double b);

unsigned char not_operation_bool(unsigned char a);
unsigned char not_operation_short(short a);
unsigned char not_operation_long(long a);
unsigned char not_operation_double(double a);


#endif /* ELEMENTS_H_ */
