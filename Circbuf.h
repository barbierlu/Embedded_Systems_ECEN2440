/*
 * buffer.h
 *
 *  Created on: Oct 11, 2016
 *      Author: Luke Barbier
 */

#ifndef BUFFER_H_
#define BUFFER_H_

typedef enum CB_Err_t{
	// Circular Buffer error (general)
	CB_NO_ERROR = 0,
	CB_INIT_ERROR = 1,
}CB_Err;

typedef enum BF_Err_t{
	// Buffer full error
	BF_NO_ERROR = 0,
	BF_INIT_ERROR = 1,
}BF_Err;

typedef enum BE_Err_t{
	// Buffer empty error
	BE_NO_ERROR = 0,
	BE_INIT_ERROR = 1,
}BE_Err;

typedef struct CircBuf_t{
	   uint8_t * buffer; //beginning of actual buffer in memorary
	   uint8_t * head; //points to oldest data (will be pulled off first)
	   uint8_t * tail; //points to newest data (just added)
	   uint8_t size; //size of buffer
	   uint32_t num_items; //number of items currently in buffer
}CircBuf;

CB_Err InitializeBuffer(CircBuf *buf, uint32_t length);
void add_item_buffer(CircBuf * buf, uint8_t data);
uint8_t get_item_buffer(CircBuf * buf);
BF_Err buffer_full(CircBuf * buf);
void buffer_overwrite(CircBuf * buf);
void clear_buffer(CircBuf * buf);

#endif /* BUFFER_H_ */ 
