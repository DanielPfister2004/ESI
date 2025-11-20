#include <hal_general.h>
#include <dl_General.h>
#include "hal_usciB1.h"

#include <stdint.h>  // for uint32_t or other variables

#define BYTE1 'AA'
#define BYTE2 'CC'

extern USCIB1_SPICom LCD;
extern int one_hz_cnt;

// '0' ... motor init off
// '1' ... motor init on
int activate_motor = 0;

void main(void)
{
    LCD.Status.TxSuc = 1;
    hal_init();
    dl_Init();

    dl_LCDWriteText("A", 1, 1, 0);
    dl_LCDWriteText("B", 1, 1, 20);
    dl_LCDWriteText("Ich halt es nicht", 17, 3, 0);
    dl_LCDWriteText("mehr aus", 8, 4, 0);
    dl_LCDWriteText("67", 2, 6, 9);

    while (1)
    {
        //test_movements();

    }
}

