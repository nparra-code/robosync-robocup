/**
 * Basic Type Definition
 *
 * @brief   Defines the basic types and Macros of return values.
 * @version V1.1.6     - Jun 03, 2016 - Add __IO definition for QT platform.
 *          V1.1.6 (R) - Jul 27, 2016 - Release version.
 *          V1.1.7 (R) - Aug 24, 2017 - Release version.
 *
 * @attention
 *          ***** IT IS NOT RECOMMENDED TO CHANGE THIS FILE  *****
 *
 * @attention
 * <h2><center>&copy; COPYRIGHT(c) 2017 SYD Dynamics ApS</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef BASICTYPES_H
#define BASICTYPES_H

//---------------------------------------------------
// Select Platform
// #define EP_PLATFORM_QT5_
// #define EP_PLATFORM_STM32F10x_KEIL_
// #define EP_PLATFORM_STM8_IAR_
// #define SA_PLATFORM_DEFAULT_
// #define   EP_ARDUNIO_
#define EP_STC32_C251_
// Select Platform
//---------------------------------------------------

/// Basic Type Definition
#ifdef SA_PLATFORM_DEFAULT_
#include "stdint.h"
typedef uint32_t uint32;
typedef int32_t int32;
typedef uint16_t uint16;
typedef int16_t int16;
typedef uint8_t uint8;
typedef int8_t int8;
typedef float float32;
#ifndef __IO
#define __IO volatile
#endif
#endif

#ifdef EP_PLATFORM_QT5_
#include <QtGlobal>
#include <QtCore>
typedef quint64 uint64;
typedef qint64 int64;
typedef quint32 uint32;
typedef qint32 int32;
typedef quint16 uint16;
typedef qint16 int16;
typedef quint8 uint8;
typedef qint8 int8;
typedef float float32;
typedef double float64;
#ifndef __IO
#define __IO volatile
#endif
#endif

#ifdef EP_ARDUNIO_
typedef unsigned long uint32;
typedef long int32;
typedef unsigned int uint16;
typedef int int16;
typedef unsigned char uint8;
typedef char int8;
typedef float float32;
#endif

#ifdef EP_PLATFORM_STM8_IAR_
/*typedef unsigned long uint32;
typedef long          int32;
typedef unsigned int  uint16;
typedef int           int16;
typedef unsigned char uint8;
typedef char          int8;*/
#include "hal_types.h"
typedef float float32;
#ifndef __IO
#define __IO volatile
#endif
#endif

#ifdef EP_PLATFORM_STM32F10x_KEIL_
#include "stm32f1xx_hal.h"
typedef uint32_t uint32;
typedef int32_t int32;
typedef uint16_t uint16;
typedef int16_t int16;
typedef uint8_t uint8;
typedef int8_t int8;
typedef float float32;
#endif

#ifdef EP_STC32_C251_
typedef unsigned char uint8;  //  8 bits
typedef unsigned int uint16;  // 16 bits
typedef unsigned long uint32; // 32 bits

typedef signed char int8;  //  8 bits
typedef signed int int16;  // 16 bits
typedef signed long int32; // 32 bits
typedef float float32;
#endif
                              /// Return Values
#ifndef EP_FAIL_
#define EP_FAIL_ ((int16)1)
#endif
#ifndef EP_NORMAL_EXIT_
#define EP_NORMAL_EXIT_ ((int16)2)
#endif
#ifndef EP_SUCC_
#define EP_SUCC_ ((int16)4)
#endif
#ifndef EP_BUSY_
#define EP_BUSY_ ((int16)8)
#endif
#ifndef EP_TIMEOUT_
#define EP_TIMEOUT_ ((int16)16)
#endif
#ifndef EP_QUEUE_EMPTY_
#define EP_QUEUE_EMPTY_ ((int16)32)
#endif
#ifndef EP_MUTEX_LOCKED_
#define EP_MUTEX_LOCKED_ ((int16)64)
#endif

/// Checksum Options
#ifndef EP_CHECKSUM_1_BYTE_SUM_
#define EP_CHECKSUM_1_BYTE_SUM_ ((int8)1)
#endif
#ifndef EP_CHECKSUM_2_BYTES_SUM_
#define EP_CHECKSUM_2_BYTES_SUM_ ((int8)2)
#endif
#ifndef EP_CHECKSUM_2_BYTES_CRC_
#define EP_CHECKSUM_2_BYTES_CRC_ ((int8)4)
#endif

#endif // BASICTYPES_H
