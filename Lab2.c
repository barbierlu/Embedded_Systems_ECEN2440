//*****************************************************************************
//
// MSP432 main.c template - Empty main
// Samantha Williams, Luke Barbier, Alec Fremier
//
// TI MSP432 Interrupt configuration and LED usage
//
//****************************************************************************
#include <stdio.h>
#include <stdint.h>
#include "msp.h"
#include "main.h"

//#define PROBLEM_1			// Press button 1.1 and measure p2.6 with oscilloscope for button debounce
//#define PROBLEM_2			// Button press causes ISR to flip p1.0 LED on/off
//#define PROBLEM_3			// Manually trigger interrupt to find latency
#define PROBLEM_4			// Move through 8 LED states, one button plus, minus
//#define PROBLEM_5			// flip LED in Timer A ISR with different values
// PROBLEM_6 uses values from PROBLEM_5
//#define PROBLEM_7			// Analyze Prescalar values
//#define PROBLEM_9
//#define PROBLEM_10
//#define PROBLEM_11
//#define PROBLEM_12

uint32_t count;

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;           // Stop watchdog timer
	configure_pins();					// always called
#ifdef PROBLEM_5
	configure_timer_interrupts();
#endif
#ifdef PROBLEM_7
	configure_timer_interrupts();
#endif
	/*
	 * PROBLEM_8: Use problem 7 for determining the formula
	 */
#ifdef PROBLEM_9
	configure_timer_interrupts();
#endif

	__enable_interrupt();

	while(1){

#ifdef PROBLEM_3
		P2OUT ^= BIT6; // flip p2.6
		P1IFG |= BIT0; // manually trigger button interrupt
#endif
	}
}

void configure_pins()
{
#ifdef PROBLEM_1
	/*
	 * Configure button p1.1 and output pin 2.6
	 */
		P1DIR &= ~BIT1; 			// p1.4 as input (STEP 1)
		P1REN |= BIT1;				// p1.4 register enabled pull-up / pull-down (STEP 2)
		P1OUT |= BIT1;				// p1.4 output register pull-up resistor enabled  (STEP 3)
		P1IFG &= ~BIT1; 			// clear flag P1.4 Interrupt (STEP 4)
		P1IES |= BIT1;				//High-to-low transition of p1.4 (STEP 5)
		P1IE |= BIT1; 			    // p1.4 interrupt enabler (STEP 6)
		NVIC_EnableIRQ(PORT1_IRQn); //Enable p1.4 interrupt with NVIC (STEP 7)
									//ISR (Interrupt Service Routine) function (STEP 8)
		P2DIR |= BIT6; // measure PIN2.6
		P2OUT &= ~BIT6;
#endif
#ifdef PROBLEM_2

		/*
		 * Configure buttons p1.1 and p1.4 and LED p1.0
		 */
			P1DIR &= ~BIT4; 			// p1.4 as input (STEP 1)
			P1REN |= BIT4;				// p1.4 register enabled pull-up / pull-down (STEP 2)
			P1OUT |= BIT4;				// p1.4 output register pull-up resistor enabled  (STEP 3)
			P1IFG &= ~BIT4; 			// clear flag P1.4 Interrupt (STEP 4)
			P1IES |= BIT4;				//High-to-low transition of p1.4 (STEP 5)
			P1IE |= BIT4; 			    // p1.4 interrupt enabler (STEP 6)
			NVIC_EnableIRQ(PORT1_IRQn); //Enable p1.4 interrupt with NVIC (STEP 7)
										//ISR (Interrupt Service Routine) function (STEP 8)

			P1DIR &= ~BIT1; 			// p1.1 as input (STEP 1)
			P1REN |= BIT1;				// p1.1 register enabled pull-up / pull-down (STEP 2)
			P1OUT |= BIT1;				// p1.1 output register pull-up resistor enabled  (STEP 3)
			P1IFG &= ~BIT1; 			// clear flag P1.1 Interrupt (STEP 4)
			P1IES |= BIT1;				//High-to-low transition of p1.1 (STEP 5)
			P1IE |= BIT1; 			    // p1.1 interrupt enabler (STEP 6)
											//STEP 7 and STEP 8 are the same for Port 1
			P1DIR |= BIT0;
			P1OUT &= ~BIT0; 			// LED starts off
#endif

#ifdef PROBLEM_3
	P2DIR |= BIT6;		// p2.6 output
	P2OUT &= ~BIT6; // clear p2.6
#endif

#ifdef PROBLEM_4
	P1DIR &= ~BIT4; 			// p1.4 as input (STEP 1)
	P1REN |= BIT4;				// p1.4 register enabled pull-up / pull-down (STEP 2)
	P1OUT |= BIT4;				// p1.4 output register pull-up resistor enabled  (STEP 3)
	P1IFG &= ~BIT4; 			// clear flag P1.4 Interrupt (STEP 4)
	P1IES |= BIT4;				//High-to-low transition of p1.4 (STEP 5)
	P1IE |= BIT4; 			    // p1.4 interrupt enabler (STEP 6)
	NVIC_EnableIRQ(PORT1_IRQn); //Enable p1.4 interrupt with NVIC (STEP 7)
								//ISR (Interrupt Service Routine) function (STEP 8)

	P1DIR &= ~BIT1; 			// p1.1 as input (STEP 1)
	P1REN |= BIT1;				// p1.1 register enabled pull-up / pull-down (STEP 2)
	P1OUT |= BIT1;				// p1.1 output register pull-up resistor enabled  (STEP 3)
	P1IFG &= ~BIT1; 			// clear flag P1.1 Interrupt (STEP 4)
	P1IES |= BIT1;				//High-to-low transition of p1.1 (STEP 5)
	P1IE |= BIT1; 			    // p1.1 interrupt enabler (STEP 6)
									//STEP 7 and STEP 8 are the same for Port 1
	P2DIR |= BIT0;
	P2DIR |= BIT1;
	P2DIR |= BIT2; 				// LED's configured as outputs

	P2OUT &= ~BIT0;
	P2OUT &= ~BIT1;
	P2OUT &= ~BIT2;				// clear LED values
#endif
#ifdef PROBLEM_5
	// configure p1.0 LED and pin 2.6 as output
	P1DIR |= BIT0;				// LED output
	P1OUT &= ~BIT0; 			// LED starts off

	P2DIR |= BIT6;				// p2.6 configured as output

#endif
#ifdef PROBLEM_7
	P1DIR |= BIT0;				// LED output
	P1OUT &= ~BIT0; 			// LED starts off

	P2DIR |= BIT6;				// p2.6 configured as output

#endif
#ifdef PROBLEM_9
	P1DIR |= BIT0;
	P1OUT &= ~BIT0;				// LED starts off

	P2DIR |= BIT6;				// p2.6 configured as output for measurement with o-scope
#endif
#ifdef PROBLEM_10
	P1DIR &= ~BIT4; 			// p1.4 as input (STEP 1)
	P1REN |= BIT4;				// p1.4 register enabled pull-up / pull-down (STEP 2)
	P1OUT |= BIT4;				// p1.4 output register pull-up resistor enabled  (STEP 3)
	P1IFG &= ~BIT4; 			// clear flag P1.4 Interrupt (STEP 4)
	P1IES |= BIT4;				//High-to-low transition of p1.4 (STEP 5)
	P1IE |= BIT4; 			    // p1.4 interrupt enabler (STEP 6)
	NVIC_EnableIRQ(PORT1_IRQn); //Enable p1.4 interrupt with NVIC (STEP 7)
									//ISR (Interrupt Service Routine) function (STEP 8)

	P1DIR &= ~BIT1; 			// p1.1 as input (STEP 1)
	P1REN |= BIT1;				// p1.1 register enabled pull-up / pull-down (STEP 2)
	P1OUT |= BIT1;				// p1.1 output register pull-up resistor enabled  (STEP 3)
	P1IFG &= ~BIT1; 			// clear flag P1.1 Interrupt (STEP 4)
	P1IES |= BIT1;				//High-to-low transition of p1.1 (STEP 5)
	P1IE |= BIT1; 			    // p1.1 interrupt enabler (STEP 6)
										//STEP 7 and STEP 8 are the same for Port 1
	P2DIR |= BIT6;				//measure p2.6 to get 500msces
	P2DIR |= BIT0;
	P2DIR |= BIT1;
	P2DIR |= BIT2;				// LED's p2.0 - p2.2 set as outputs

	P2OUT &= ~BIT0;
	P2OUT &= ~BIT1;
	P2OUT &= ~BIT2;				// clear LED registers
#endif

#ifdef PROBLEM_11
	P4DIR &= ~BIT1; // input causes an interrupt
	P4REN |= BIT1;
	P4OUT |= BIT1;
	P4IFG &= ~BIT1;
	P4IES |= BIT1;
	P4IE |= BIT1;
	NVIC_EnableIRQ(PORT4_IRQn);

	count = 0;
#endif

#ifdef PROBLEM_12
	P4DIR &= ~BIT1; // input casues an interrupt
	P4REN |= BIT1;
	P4OUT |= BIT1;
	P4IFG &= ~BIT1;
	P4IES |= BIT1;
	P4IE |= BIT1;
	NVIC_EnableIRQ(PORT4_IRQn);

	P1DIR |= BIT0;
	P1OUT &= ~BIT0;

	count = 0;
#endif
}

void Port1_Handler()
{
#ifdef PROBLEM_1
	/*
	 * Send output debounce of button and delay to bypass the debounce
	 */
	P1IFG &= ~BIT1; 	 	// clear flag
	P2OUT ^= BIT6;			// toggle pin 2.6

	P1IE &= ~BIT1; 			// disable interrupts
	unsigned int i;
	// for(i = 0; i < 10000; i++) P1IFG &= ~BIT1; // DELAY_COUNT = 1000 AND clear flag
	P1IE |= BIT1; 			// enable interrupts
	P1IFG &= ~BIT1; 		// clear the flag again

#endif
#ifdef PROBLEM_2
		P1IFG &= ~BIT1;
		P1IFG &= ~BIT4;
		P1IE &= ~BIT1;
		P1IE &= ~BIT4; 			// disable interrupts
		P1OUT ^= BIT0;			// toggle LED

		/*
		 * BYPASS DEBOUNCE
		 */

		uint16_t i;
		 for(i = 0; i < 10000; i++)
		 {
			 P1IFG &= ~BIT1;
			 P1IFG &= ~BIT4; // DELAY_COUNT = 1000
		 }
		P1IE |= BIT1;
		P1IE |= BIT4; 			// enable interrupts
		P1IFG &= ~BIT1;
		P1IFG &= ~BIT4;
#endif

#ifdef PROBLEM_3
			P2OUT ^= BIT6; // toggle p2.6
#endif

#ifdef PROBLEM_4
	if(P1IFG & BIT1) // up mode
	{
		P2OUT = (P2OUT + 1) % 8;
	}
	else if(P1IFG & BIT4) // down mode
	{
		P2OUT = (P2OUT - 1) % 8;
	}

	/*
	 *  BYPASS DEBOUNCE:
	 */

	P1IE &= ~BIT1; // disable interrupts
	P1IE &= ~BIT4;
	unsigned int i;
	for(i = 0; i < 10000; i++)
	{
		P1IFG &= ~BIT1;
		P1IFG &= ~BIT4;
	}
	P1IE |= BIT1;
	P1IE |= BIT4;
	P1IFG &= ~BIT1;
	P1IFG &= ~BIT4; // clear flags

#endif
#ifdef PROBLEM_10
	P1OUT ^= BIT0; // toggle LED
	TA0CCTL0 &= ~CCIFG; // clear capture compare flag
	TA0CCR0 = 16000; // Count on ACLK with prescaled 1/8
	TA0CTL = TIMER_A_CTL_SSEL__ACLK | TIMER_A_CTL_MC__UP; //BIT4 sets up Mode
	TA0R = 0; // value of timer
	TA0CCTL0 = TIMER_A_CCTLN_CCIE; // Enabler
	NVIC_EnableIRQ(TA0_0_IRQn);

	P1IE &= ~BIT1;
	P1IE &= ~BIT4; // disable button interrupts

#endif
}
void Port4_Handler()
{
	count++; // breakpoint here in PROBLEM_12
	P1OUT |= BIT0;
	P4IE &= ~BIT1;
	unsigned int i;
		for(i = 0; i < 10000; i++)
		{
			P4IFG &= ~BIT1;
		}
	P4IE |= BIT1;
	P4IFG &= ~BIT1;
}

void configure_timer_interrupts()
{
#ifdef PROBLEM_5
	TA0CCTL0 &= ~CCIFG; // clear capture compare flag
	TA0CCR0 = 65000; //Counts to this value, with clock pre-scaled by 1/8
	TA0CTL = TIMER_A_CTL_SSEL__SMCLK | TIMER_A_CTL_MC__UP; //BIT4 sets up Mode
	TA0R = 0; //Initial of timer
	TA0CCTL0 = TIMER_A_CCTLN_CCIE; // Enabler
	NVIC_EnableIRQ(TA0_0_IRQn);
#endif
#ifdef PROBLEM_7
	TA0CCTL0 &= ~CCIFG; // clear capture compare flag
	TA0CCR0 = 50000; //Counts to this value, with clock pre-scaled by 1/8
	TA0CTL = TIMER_A_CTL_SSEL__SMCLK | TIMER_A_CTL_MC__UP | TIMER_A_CTL_ID__8; //BIT4 sets up Mode
	TA0R = 0; //Initial of timer
	TA0CCTL0 = TIMER_A_CCTLN_CCIE; // Enabler
	NVIC_EnableIRQ(TA0_0_IRQn);
#endif

#ifdef PROBLEM_9 // PROBLEM_9 and other problems
	TA0CCTL0 &= ~CCIFG; // clear capture compare flag
	TA0CCR0 = 37500; //Counts to this value, with clock pre-scaled by 1/8
	TA0CTL = TIMER_A_CTL_SSEL__SMCLK | TIMER_A_CTL_MC__UP | TIMER_A_CTL_ID__8; //BIT4 sets up Mode
	TA0R = 0; //Initial of timer
	TA0CCTL0 = TIMER_A_CCTLN_CCIE; // Enabler
	NVIC_EnableIRQ(TA0_0_IRQn);
#endif
}

void TimerA0_Handler(void)
{
	TA0CCTL0 &= ~CCIFG; // clear flag
	TA0R = 0;
#ifdef PROBLEM_5
	P1OUT ^= BIT0;
	P2OUT ^= BIT6; 		// toggle p2.6 and LED p1.0
#endif
#ifdef PROBLEM_7
	P1OUT ^= BIT0;
	P2OUT ^= BIT6;
#endif
#ifdef PROBLEM_9
	P1OUT ^= BIT0; 		// toggle LED
	P2OUT ^= BIT6;
#endif
#ifdef PROBLEM_10
	if (P2OUT != 7){
		P2OUT = (P2OUT + 1);
		P1IFG &= ~BIT1;
		P1IFG &= ~BIT4; // clear any pending flags
	}
	else
	{
		TA0CTL = TIMER_A_CTL_MC__STOP;
		P2OUT -= 7;
		P1IE |= BIT1;
		P1IE |= BIT4; // enable button interrupts
	}
#endif
}

