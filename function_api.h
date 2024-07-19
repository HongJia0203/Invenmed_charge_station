/* 
 * File:   function_api.h
 * Author: Hugo
 *
 * Created on July 16, 2024, 4:03 PM
 */

#include "stdint.h"

#ifndef FUNCTION_API_H
#define	FUNCTION_API_H

#ifdef	__cplusplus
extern "C" {
#endif

void sendStringtoPenal(const char *str);

uint16_t calculateCRC16(char *addr,uint16_t len);

#ifdef	__cplusplus
}
#endif

#endif	/* FUNCTION_API_H */

