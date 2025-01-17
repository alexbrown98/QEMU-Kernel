/* Copyright (C) 2017 Daniel Page <csdsp@bristol.ac.uk>
 *
 * Use of this source code is restricted per the CC BY-NC-ND license, a copy of 
 * which can be found via http://creativecommons.org (and should be included as 
 * LICENSE.txt within the associated archive or repository).
 */

#ifndef __HILEVEL_H
#define __HILEVEL_H

// Include functionality relating to newlib (the standard C library).

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>


// Include functionality relating to the platform
#include "GIC.h"
#include "PL011.h"
#include "PL050.h"
#include "PL111.h"
#include   "SYS.h"
#include "libc.h"

// Include functionality relating to the   kernel.

#include "lolevel.h"
#include "/home/alex/Desktop/SCP/COMS20001-CW2/Stage 2a/device/disk.h"
#include     "int.h"

typedef int pid_t;

typedef enum {
  STATUS_CREATED,
  STATUS_READY,
  STATUS_INVALID,
  STATUS_EXECUTING,
  STATUS_WAITING,
  STATUS_TERMINATED,
  STATUS_EXIT
} status_t;

typedef struct {
  uint32_t cpsr, pc, gpr[ 13 ], sp, lr;
} ctx_t;

typedef struct {
     pid_t    pid;
  status_t status;
     ctx_t    ctx;
     uint32_t tos;
     int precedence;
     int age;
} pcb_t;

typedef struct {
  int data;
  bool available;
  bool written;
} pipe_t;

#define MAX_PROCS 20
#define STACK_SIZE 0x00001000

#endif
