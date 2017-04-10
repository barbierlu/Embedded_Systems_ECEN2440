#include "msp.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "buffer.h"

/* Circular buffer for the TI MSP432 */

CB_Err InitializeBuffer(CircBuf *buf, uint32_t length)
{
	buf->buffer = (uint8_t *)malloc(length);

	if(!buf->buffer)		// buf->buffer is zero -> return an error
	{
		return CB_INIT_ERROR;
	}

	buf->head = buf->buffer;
	buf->tail = buf->buffer;
	buf->size = length;
	buf->num_items = 0;
	return CB_NO_ERROR;
}

void add_item_buffer(CircBuf * buf, uint8_t data){
	if (buf->size == buf->num_items)
		buffer_overwrite(&buf);

	if (buf->head == (buf->head + buf->size))
		buf->head = buf->buffer;

	else
		buf->head++;
	*buf->head = data;
	buf->num_items++;
}

void buffer_overwrite(CircBuf * buf){
	if (buf->tail == (buf->buffer + buf->size))		// if it's on the end
		buf->tail = buf->buffer;
	else
		*buf->tail++;
}

uint8_t get_item_buffer(CircBuf * buf){ 			//Get and remove value at tail
	if (buf->tail == (buf->buffer + buf->size))		// if it's on the end
		buf->tail = buf->buffer;
	else if (buffer_empty(&buf))
		return 1;		// how proper error
	else
	{
		buf->tail++;
	}

	buf->num_items--;
	return *buf->tail;
}

/* Checks if the circular buffer is empty*/
BE_Err buffer_empty(CircBuf * buf){
	if((buf->head == buf->tail) && (buf->num_items == 0))
		return BE_INIT_ERROR;
	return BE_NO_ERROR;
}

/* Checks for a full circular buffer*/
BF_Err buffer_full(CircBuf * buf){
	if(buf->num_items == buf->size)
		return BF_INIT_ERROR;

	return BF_NO_ERROR;
}

void clear_buffer(CircBuf * buf)
{
	buf->head = buf->buffer;
	buf->tail = buf->buffer;		// reset head and tail
	buf->num_items = 0;
}
