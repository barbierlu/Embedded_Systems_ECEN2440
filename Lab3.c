///*****************************************************************************
//
// MSP432 Lab4.c main
// Author: Samantha Williams, Luke Barbier, Alec Fremier
//
// TI MSP432 Clock and timer configuration, Serial UART communication
//
//****************************************************************************

#include "msp.h"
#include <stdio.h>
#include <stdint.h>
#include "Lab3.h"
#include <stdlib.h>			// string functions
#include "buffer.h"

//#define PROBLEM_2
//#define PROBLEM_3_4
#define PROBLEM_5
//s#define PROBLEM_6
//#define PROBLEM_6_G

#define BUFF_SIZE (256)

CircBuf buf;

#ifdef PROBLEM_6_G
void port1_handler();
#endif

void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;           // Stop watchdog timer
    configure_clocks();
    configure_serial_port();
#ifdef PROBLEM_6_G
    configure_buttons();
#endif

#ifdef PROBLEM_2 //Calling for 0xAA to transmit
    while(1){
		uart_putchar(0xAA);
    }
#endif

#ifdef PROBLEM_3_4 //Prints a string
    	char str[] ="Why not Zoidberg?";
    	uint32_t len = strlen(str);
    	uart_putchar_n(str, len);
#endif

#ifdef PROBLEM_5  //Takes in input from Realterm, places it in RX and sends it back out TX
    	InitializeBuffer(&buf, BUFF_SIZE);
    	while (1){;}
#endif

#ifdef PROBLEM_6
    	InitializeBuffer(&buf, BUFF_SIZE);
    	while (1){;}
#endif

}

void configure_clocks(void){
   CS->KEY = 0x695A;         //Unlcok CS module for register access
   CS->CTL0 = 0;              //Reset tuning parameters
   CS->CTL0 |= CS_CTL0_DCORSEL_1; //Sets DCO clock
   CS->CTL1 = CS_CTL1_SELA_2 | CS_CTL1_SELS_3 | CS_CTL1_SELM_3; //Some preset bullshit we gotta do
   CS->KEY = 0; //Locks CS
}

void configure_serial_port(){

	UCA0CTLW0 |= UCSWRST;         // Put eUSCI in reset // set to UART
	P1SEL0 |= BIT2 | BIT3;       //Configures UART mode
	P1SEL1 &= ~BIT2 & ~BIT3;
    UCA0CTLW0 = UCSSEL1;     //Sets SMCLK source
    UCA0BR0 = 26;              //Sets the BAUD rate
    UCA0BR1 = 0x00;
    UCA0CTLW0 &= ~UCSWRST;
    UCA0IE |= UCRXIE;
    NVIC->ISER[0] = 1 << ((EUSCIA0_IRQn) & 31);

}

#ifdef PROBLEM_6_G
void configure_buttons()
{
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
}
#endif

void uart_putchar(uint8_t tx_data){ //send single byte function
   while((UCA0IFG & UCTXIFG)){
   	   UCA0TXBUF = tx_data; // Load data onto buffer
   }
}

void uart_putchar_n(uint8_t * data, uint32_t num_items){
	volatile int i = 0;
	while ((data[i] != '\0')){
		if(UCA0IFG & UCTXIFG)
			UCA0TXBUF = data[i++];
	}
}

void dump_buffer(uint8_t data)
{
	if ((data == 13) || (buffer_full(&buf))){
				char a[] = "Num_items: ";
				uint32_t alen = strlen(a);  		//Length of string above
				uart_putchar_n(&a, alen);

				char number_items[3];
				sprintf((char *)number_items, "%d", buf.num_items);
				uint8_t kule = strlen((char *)number_items);
				uart_putchar_n(number_items,kule);


				int i;
				for(i = 0; i < 100; i++);
				uart_putchar(13);
				uint8_t alpha = 0;
				uint8_t punc = 0;
				uint8_t number = 0;
				uint8_t space = 0;
				uint8_t boop = 0;
				while(buf.tail != buf.head){
					if(UCA0IFG & UCTXIFG){		// Ready to send{
						buf.tail++;

						if (((*buf.tail >= 65) && (*buf.tail <= 90)) || ((*buf.tail >= 97) && (*buf.tail <= 122))) alpha++;
						if (((*buf.tail >= 33) && (*buf.tail <= 47)) || ((*buf.tail >= 58) && (*buf.tail <= 64)) || ((*buf.tail >= 91) && (*buf.tail <= 96)) || (*buf.tail >= 123)) punc++;
						if ((*buf.tail >= 48) && (*buf.tail <= 57)) number++;
						if ((*buf.tail == 32) || (*buf.tail == 9))  space++;
						if ((*buf.tail < 32) && (*buf.tail != 9)) boop++;

						UCA0TXBUF = *buf.tail;
					}
				}
				//LETTERS
				for(i = 0; i < 100; i++);
				uart_putchar(13);
				char alph[] = "# of letters: ";
				uint32_t blen = strlen(alph);  		//Length of string above
				uart_putchar_n(&alph, blen);

				char number_items_a[3];
				sprintf((char *)number_items_a, "%d", alpha);
				uint8_t kule_a = strlen((char *)number_items_a);
				uart_putchar_n(number_items_a,kule_a);

				//PUNCTUATION
				for(i = 0; i < 100; i++);
				uart_putchar(13);
				char pun[] = "# of punctions: ";
				uint32_t plen = strlen(pun);  		//Length of string above
				uart_putchar_n(&pun, plen);

				char number_items_p[3];
				sprintf((char *)number_items_p, "%d", punc);
				uint8_t kule_p = strlen((char *)number_items_p);
				uart_putchar_n(number_items_p,kule_p);

				//NUMBERS
				for(i = 0; i < 100; i++);
				uart_putchar(13);
				char num[] = "# of numbers: ";
				uint32_t nlen = strlen(num);  		//Length of string above
				uart_putchar_n(&num, nlen);

				char number_items_n[3];
				sprintf((char *)number_items_n, "%d", number);
				uint8_t kule_n = strlen((char *)number_items_n);
				uart_putchar_n(number_items_n,kule_n);

				//WHITESPACE
				for(i = 0; i < 100; i++);
				uart_putchar(13);
				char white[] = "# of whitespace: ";
				uint32_t wlen = strlen(white);  		//Length of string above
				uart_putchar_n(&white, wlen);

				char number_items_s[3];
				sprintf((char *)number_items_s, "%d", space);
				uint8_t kule_s = strlen((char *)number_items_s);
				uart_putchar_n(number_items_s,kule_s);

				//NON-PRINTABLES
				for(i = 0; i < 100; i++);
				uart_putchar(13);
				char boo[] = "# of non-printables: ";
				uint32_t nplen = strlen(boo);  		//Length of string above
				uart_putchar_n(&boo, nplen);

				char number_items_b[3];
				sprintf((char *)number_items_b, "%d", boop);
				uint8_t kule_b = strlen((char *)number_items_b);
				uart_putchar_n(number_items_b,kule_b);

				buf.num_items = 0; //Reset num_items
			}
			else if(!(buffer_full(&buf))){
				add_item_buffer(&buf,data);
			}
}

#ifdef PROBLEM_6_G
void PORT1_IRQHandler()
{
	if(P1IFG & BIT4) //dump data
	{
		dump_buffer(13);
		P1IFG &= ~BIT4;
	}
	else		// clear buffer
	{
		clear_buffer(&buf);
		P1IFG &= ~BIT1;
	}
}
#endif

void EUSCIA0_IRQHandler(void){
	uint8_t data;
	if (UCA0IFG & UCRXIFG){ 		 //If UART receiver buffer full
		data = UCA0RXBUF;
#ifdef PROBLEM_5  					//Adds items to the buffer
		add_item_buffer(&buf, data);
		if (UCA0IFG & UCTXIFG){	//Sends received data back to terminal
			uart_putchar(get_item_buffer(&buf));
		}
#endif
#ifdef PROBLEM_6
		dump_buffer(data);
#endif
}
}
