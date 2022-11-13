/*
 * get_time.h
 *
 *  Created on: Oct 7, 2018
 *      Author: amyznikov
 */
#pragma once
#ifndef __c_get_time_h___
#define __c_get_time_h___

#include <time.h>
#include <string>


// REALTIME ms
double get_realtime_ms(void);


// current data time
struct c_datetime {
  int year;
  int month;
  int day;
  int hour;
  int min;
  int sec;
  int msec;
};

void get_current_datetime(struct c_datetime * dst);
const char * get_current_time(char buf[32]);
std::string get_current_datetime(void);
std::string get_current_datetime2(void);

#endif /* __c_get_time_h___ */
