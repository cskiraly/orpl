/*
 * Copyright (c) 2013, Swedish Institute of Computer Science.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
  *
 */
/**
 * \file
 *         Header file for orpl-log.c, and a set of macros for ORPL logging
 *
 * \author Simon Duquennoy <simonduq@sics.se>
 */

#ifndef ORPL_LOG_H
#define ORPL_LOG_H

#include <stdio.h>

/* Data strcutrues copied at the end of all data packets, making it possible
 * to trace packets at every hop, from every layer. */
struct app_data {
  uint32_t seqno;
  uint16_t src;
  uint16_t dest;
  uint8_t hop;
  uint8_t ping;
  uint8_t fpcount;
};

/* Copy an appdata to another with no assumption that the addresses are aligned */
void appdata_copy(struct app_data *dst, struct app_data *src);
/* Get dataptr from the packet currently in uIP buffer */
struct app_data *appdataptr_from_uip();
/* Get dataptr from the current packetbuf */
struct app_data *appdataptr_from_packetbuf();
/* Log information about a data packet along with ORPL routing information */
void log_appdataptr(struct app_data *dataptr);

#define ORPL_LOG(...) printf(__VA_ARGS__)
#define ORPL_LOG_FROM_APPDATAPTR(appdataptr, ...) { printf(__VA_ARGS__); log_appdataptr(appdataptr); }
#define ORPL_LOG_NULL(...) ORPL_LOG_FROM_APPDATAPTR(NULL, __VA_ARGS__)
#define ORPL_LOG_FROM_UIP(...) ORPL_LOG_FROM_APPDATAPTR(appdataptr_from_uip(), __VA_ARGS__)
#define ORPL_LOG_FROM_PACKETBUF(...) ORPL_LOG_FROM_APPDATAPTR(appdataptr_from_packetbuf(), __VA_ARGS__)

#endif /* ORPL_LOG */