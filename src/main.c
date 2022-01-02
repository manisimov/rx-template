#include "iodefine.h"
#include "interrupt_handlers.h"
#include "cpu.h"


#define LED1	PORTD.DR.BIT.B0
#define LED2	PORTD.DR.BIT.B1
#define LED3	PORTD.DR.BIT.B2
#define LED4	PORTD.DR.BIT.B3
#define LED5	PORTD.DR.BIT.B4
#define LED6	PORTD.DR.BIT.B5
#define LED7	PORTD.DR.BIT.B6
#define LED8	PORTD.DR.BIT.B7
#define LED9	PORTE.DR.BIT.B0
#define LED10	PORTE.DR.BIT.B1
#define LED11	PORTE.DR.BIT.B2
#define LED12	PORTE.DR.BIT.B3

#define LED1_DDR	PORTD.DDR.BIT.B0
#define LED2_DDR	PORTD.DDR.BIT.B1
#define LED3_DDR	PORTD.DDR.BIT.B2
#define LED4_DDR	PORTD.DDR.BIT.B3
#define LED5_DDR	PORTD.DDR.BIT.B4
#define LED6_DDR	PORTD.DDR.BIT.B5
#define LED7_DDR	PORTD.DDR.BIT.B6
#define LED8_DDR	PORTD.DDR.BIT.B7
#define LED9_DDR	PORTE.DDR.BIT.B0
#define LED10_DDR	PORTE.DDR.BIT.B1
#define LED11_DDR	PORTE.DDR.BIT.B2
#define LED12_DDR	PORTE.DDR.BIT.B3

volatile uint32_t test_u32;

void uc_init(void)
{
    /* Set ICLK clock selector */
    SYSTEM.SCKCR.BIT.ICK = 0;   // 0 - 96 MHz
    SYSTEM.SCKCR.BIT.PCK = 1;   // 1 - 48 MHz
    for(int i = 0; i < 10; i++)
    {
        test_u32++;
    }
    SYSTEM.SCKCR.BIT.BCK = 1;   // 1 - 48 MHz
    /* Test pin as output */
    PORTE.DDR.BIT.B6 = 1;
    /* MTU0 timer settings */
    /* For 10ms:
     * PCLK = 48 * 10^6,
     * Time between two PCLK ticks. tpclk = 1/(48*10^6) = 2.0833333333333335e-08
     * Number of ticks in 10ms. n = 480000.
     * Prescaler is 64, so timer value is 480000/64 = 7500 = 0x1d4c
     */
    SYSTEM.MSTPCRA.BIT.MSTPA9 = 0;  // Enable clocks
    MTU0.TCR.BIT.TPSC = 3;          // PCLK prescaler /64
    MTU0.TGRA = 0x1d4c;             // Max value of counter.
    MTU0.TCR.BIT.CCLR = 1;          // Clear source is TGRA.
    MTU0.TIER.BIT.TGIEA = 1;        // Enable TGRA interrupt.
    IPR(MTU0, TGIA0) = 1;
    IEN(MTU0, TGIA0) = 1;
    MTUA.TSTR.BIT.CST0 = 1;         // Start the timer.
}

void set_test_pin(void)
{
    PORTE.DR.BIT.B6 = 1;
}

void clear_test_pin(void)
{
    PORTE.DR.BIT.B6 = 0;
}

void toogle_test_pin(void)
{
    int value;

    value = PORTE.DR.BIT.B6;
    if(value == 0)
    {
        PORTE.DR.BIT.B6 = 1;
    }
    else
    {
        PORTE.DR.BIT.B6 = 0;
    }
}

void toogle_led_pin(void)
{
    int value;

    value = PORTE.DR.BIT.B3;
    if(value == 0)
    {
        PORTE.DR.BIT.B3 = 1;
    }
    else
    {
        PORTE.DR.BIT.B3 = 0;
    }
}

void  INT_Excep_MTU0_TGIA0(void)
{
    static int i = 0;

    toogle_test_pin();
    if(i % 100 == 0)
    {
        toogle_led_pin();
        i = 0;
    }
    i++;
}

const int DELAY = 500000;

void main(void)
{
    uint8_t a;

    LED12_DDR = 1;
    LED11_DDR = 1;
    LED9_DDR = 1;
    LED12 = 1;
    LED11 = 0;
    uc_init();

    while(1)
    {
        LED11 = 0;

        for(int i = 0; i < DELAY; i++)
        {
            test_u32++;
        }

        LED11 = 1;

        for(int i = 0; i < DELAY; i++)
        {
            test_u32++;
        }
    }
}
