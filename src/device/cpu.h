#ifndef _HAL_CPU_H
#define _HAL_CPU_H

#include <stdint.h>

#define  CPU_SR_ALLOC()           uint8_t  cpu_sr = (uint8_t)0

#define  ENTER_CRITICAL()         do { cpu_sr = get_ipl(); \
                                       set_ipl(12);        } while (0)
#define  EXIT_CRITICAL()          do { set_ipl(cpu_sr);    } while (0)     /* Restore CPU status word. */

extern void set_ipl(uint8_t ipl);
extern uint8_t get_ipl(void);

#endif
