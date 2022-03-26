/*
*   Function declarations for RC servo decoding
*/
#ifndef IOPROC_H
#define IOPROC_H

// Processing Servo Inputs to switched- and servo-outputs

#ifdef IBUS
extern void Process_RX_CH3();
#endif
extern void Process_RX_CH5();
extern void Process_RX_CH6();

#endif //IOPROC_H