/*
logging.h - Include file for logging via Serial.
Copyright (C) 2019  by Stefan Andres

Works for ESP only
Include this file in *.cpp file
comment/uncomment #define _LOGGING_OFF for global remove logging 
#define _LOGGING_OFF in cpp for not Logging in this file

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#include <Arduino.h>

#ifndef _LOGGING_H_
#define _LOGGING_H_

// #define _LOGGING_OFF  // global logging off

void __log_time();

#ifdef _LOGGING_OFF
#define _log(__log_x)
#define _logf(__log_x, ...)
#define _logs(__log_x, ...)
#define _log_begin(__log_x)
#else
#define _log(__log_x) __log_time();Serial.println(__log_x)
#define _logf(__log_x, ...) __log_time();Serial.printf(__log_x,##__VA_ARGS__)
#define _logs(__log_x, ...) Serial.printf(__log_x,##__VA_ARGS__)
#define _log_begin(__log_x) Serial.begin(__log_x); Serial.printf("\n\nLogging Start (%d)\n",__log_x)
#endif

#endif /* _LOGGING_H_ */
