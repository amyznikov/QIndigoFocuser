/*
 * get_time.cc
 *
 *  Created on: Oct 7, 2018
 *      Author: amyznikov
 */

#include "get_time.h"
#include <sys/time.h>
#include <string.h>

// REALTIME ms
double get_realtime_ms(void)
{
  struct timespec t;
  clock_gettime(CLOCK_REALTIME, &t);
  return (double) (t.tv_sec * 1000 + t.tv_nsec / 1e6);
}



void get_current_datetime(struct c_datetime * ct)
{
  struct timespec t;
  struct tm * tm;

  clock_gettime(CLOCK_REALTIME, &t);
  tm = gmtime(&t.tv_sec);

  ct->year = tm->tm_year + 1900;
  ct->month = tm->tm_mon + 1;
  ct->day = tm->tm_mday;
  ct->hour = tm->tm_hour;
  ct->min = tm->tm_min;
  ct->sec = tm->tm_sec;
  ct->msec = t.tv_nsec / 1000000;
}

const char * get_current_datetime(char buf[32])
{
  struct c_datetime ct;
  get_current_datetime(&ct);
  snprintf(buf, 31, "%.4d-%.2d-%.2d-%.2d:%.2d:%.2d.%.3d",
      ct.year, ct.month, ct.day, ct.hour, ct.min, ct.sec, ct.msec);
  return buf;
}

std::string get_current_datetime(void)
{
  struct c_datetime ct;
  char buf[32] = "";
  get_current_datetime(&ct);
  snprintf(buf, 31, "%.4d-%.2d-%.2d-%.2d:%.2d:%.2d.%.3d",
      ct.year, ct.month, ct.day, ct.hour, ct.min, ct.sec, ct.msec);
  return buf;
}

std::string get_current_datetime2(void)
{
  struct c_datetime ct;
  char buf[32] = "";
  get_current_datetime(&ct);
  snprintf(buf, 31, "%.4d-%.2d-%.2d-%.2d-%.2d-%.2d-%.3d",
      ct.year, ct.month, ct.day, ct.hour, ct.min, ct.sec, ct.msec);
  return buf;
}
