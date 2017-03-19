/* Roomba / Scooba (iRobot) control
 * 
 * Author(s): Vladimir Navrat
 * License: LGPL-2.1
 * 
 * Roomba uses 8bit length command. MSB is transmitted first. Every
 * bit is 4ms long and different ratio is used for diferent values. 
 * 0 is 1ms mark and 3ms space, 1 is 3ms mark and 1ms space. 
 */
 
#include "IRremote.h"
#include "IRremoteInt.h"

//==============================================================================
//             RRRR   OOO   OOO  M   M BBBB   AA  
//             R   R O   O O   O MM MM B   B A  A 
//             RRRR  O   O O   O M M M BBBB  AAAA 
//             R R   O   O O   O M   M B   B A  A 
//             R  RR  OOO   OOO  M   M BBBB  A  A 
//==============================================================================

#define BITS           8  // The number of bits in the command

#define ONE_MARK    3000  // The length of a Bit:Mark for 1's
#define ONE_SPACE   1000  // The length of a Bit:Space for 1's
#define ZERO_MARK   1000  // The length of a Bit:Mark for 0's
#define ZERO_SPACE  3000  // The length of a Bit:Space for 0's

//+=============================================================================
//
#if SEND_ROOMBA
void  IRsend::sendRoomba (unsigned long data,  int nbits)
{
	// Set IR carrier frequency
	enableIROut(38);

	// Data
	for (unsigned long  mask = 1UL << (nbits - 1);  mask;  mask >>= 1) {
		if (data & mask) {
			mark (ONE_MARK);
			space(ONE_SPACE);
		} else {
			mark (ZERO_MARK);
			space(ZERO_SPACE);
		}
	}

    space(0);  // Always end with the LED off
}
#endif

//+=============================================================================
//
#if DECODE_ROOMBA
bool  IRrecv::decodeRoomba (decode_results *results)
{
    return false;
}
#endif
