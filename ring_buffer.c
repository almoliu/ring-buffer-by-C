/****************(C)COPYRIGHE 2015 Geeker*****************
 *file name:		ring_buf.c
 *description:		about the ring buffer
 *author:			geeker.g
 *date:				20151106
 *version:			v0.1
 * ******************************************************************/
#include "ring_buffer.h"
#include <stdlib.h>
#include <string.h>

typedef struct{
	void *raw_head;
	uint32_t head;
	uint32_t tail;
	uint32_t item_size;
	uint32_t cur_size;
	uint32_t size;
}cir_buf_t;

/*
 *  *Function:		get_cur_size
 *  *Description:	get the data size of the ring buffer
 *  *Parameter:		ring_buf:the ring buffer we want to get the info
 *  *Return:		the data size
 *  *Author:		geeker
 *  *Date:			20151106
 *  *modify:
 *  */
uint32_t get_cur_size(const ring_buf_t *ring_buf)
{
	return ((cir_buf_t *)ring_buf)->cur_size;
}

/*
 *  *Function:		get_capacity
 *  *Description:	get the capacity of the ring buffer
 *  *Parameter:		ring_buf:the ring buffer we want to get the info
 *  *Return:		the capacity of the ring buffer
 *  *Author:		geeker
 *  *Date:			20151106
 *  *modify:
 *  */
uint32_t get_capacity(const ring_buf_t *ring_buf)
{
	return ((cir_buf_t *)ring_buf)->size;
}

/*
 *  *Function:		get_remain_size
 *  *Description:	get the remained size of the ring buffer
 *  *Parameter:		ring_buf:the ring buffer we want to get the info
 *  *Return:		the remained size of the ring buffer
 *  *Author:		geeker
 *  *Date:			20151106
 *  *modify:
 *  */
uint32_t get_remain_size(const ring_buf_t *ring_buf)
{
	return ((cir_buf_t *)ring_buf)->size - ((cir_buf_t *)ring_buf)->cur_size;
}

/*
 *  *Function:		get_item_size
 *  *Description:	get the item size of the ring buffer
 *  *Parameter:		ring_buf:the ring buffer we want to get the info
 *  *Return:		the item size of the ring buffer
 *  *Author:		geeker
 *  *Date:			20151106
 *  *modify:
 *  */
uint32_t get_item_size(const ring_buf_t *ring_buf)
{
	return ((cir_buf_t *)ring_buf)->item_size;
}

/*
 *  *Function:		find_prv_pos
 *  *Description:	find the previous position in the ring buffer	
 *  *Parameter:		ring_buf:the ring buffer we want to find
 *					pos:current position
 *  *Return:		the position we want to find
 *  *Author:		geeker
 *  *Date:			20151106
 *  *modify:
 *  */
static uint32_t find_prv_pos(const ring_buf_t * ring_buf,uint32_t pos)
{
	if(0 == pos)
		return ((cir_buf_t *)ring_buf)->size - 1;
	else
		return pos - 1;
}

/*
 *  *Function:		find_next_pos
 *  *Description:	find the next position in the ring buffer
 *  *Parameter:		ring_buf:the ring buffer we want to find
 *					pos:current position
 *  *Return:		the position we want to find
 *  *Author:		geeker
 *  *Date:			20151106
 *  *modify:
 *  */
static uint32_t find_next_pos(const ring_buf_t * ring_buf,uint32_t pos)
{
	if((((cir_buf_t *)ring_buf)->size - 1) == pos)
		return 0;
	else 
		return pos + 1;
}

/*
 *  *Function:		create_ring_buf
 *  *Description:	create a ring buffer
 *  *Parameter:		buf_size:how many item we want to save
 *					item_size:the size of the item(byte)
 *  *Return:		NULL if failed,otherwise a pointer
 *  *Author:		geeker
 *  *Date:			20151106
 *  *modify:
 *  */
ring_buf_t * create_ring_buf(uint32_t buf_size,uint32_t item_size)
{
	cir_buf_t *cir_buf = malloc(sizeof(cir_buf_t));
	if(NULL == cir_buf)
		return NULL;

	cir_buf->raw_head = malloc(buf_size * item_size);
	if(NULL == cir_buf->raw_head){
		free(cir_buf);
		return NULL;
	}

	cir_buf->head = 0;
	cir_buf->tail = 0;
	cir_buf->item_size = item_size;
	cir_buf->cur_size = 0;
	cir_buf->size = buf_size;
	return cir_buf;
}

/*
 *  *Function:		destroy_buf
 *  *Description:	destory the ring buffer
 *  *Parameter:		ring_buf:the buffer we want to destory
 *  *Return:		void
 *  *Author:		geeker
 *  *Date:			20151106
 *  *modify:
 *  */
void destroy_buf(ring_buf_t * ring_buf)
{
	free(((cir_buf_t *)ring_buf)->raw_head);
	free(ring_buf);
}

/*
 *  *Function:		fill_buf_unit__
 *  *Description:	fill an item in the ring buffer
 *  *Parameter:		ring_buf:the buffer we want to fill
 *					item:the item we want to fill in the ring buffer
 *  *Return:		-1 if sth error,else 0
 *  *Author:		geeker
 *  *Date:			20151106
 *  *modify:
 *  */
static int8_t fill_buf_unit__(ring_buf_t *ring_buf,void *item)
{
	cir_buf_t *cir_buf = ring_buf;
	
	if(cir_buf->cur_size >= cir_buf->size)
		return -1;
	
	memcpy((char *)(cir_buf->raw_head) + (cir_buf->tail * cir_buf->item_size),item,cir_buf->item_size);
	cir_buf->tail = find_next_pos(cir_buf,cir_buf->tail);
	++cir_buf->cur_size;
	
	return 0;
}

/*
 *  *Function:		fetch_buf_unit__
 *  *Description:	fetch an item in the ring buffer,the fetch data will delete in the buffer
 *  *Parameter:		ring_buf:the buffer we want to fetch from
 *					item:the data which we fetched saved in
 *  *Return:		-1 if sth error,else 0
 *  *Author:		geeker
 *  *Date:			20151106
 *  *modify:
 *  */
static int8_t fetch_buf_unit__(ring_buf_t *ring_buf,void *item)
{
	cir_buf_t *cir_buf = ring_buf;
	
	if(0 == cir_buf->cur_size)
		return -1;
	
	memcpy(item,(char *)(cir_buf->raw_head) + (cir_buf->head * cir_buf->item_size),cir_buf->item_size);
	cir_buf->head = find_next_pos(cir_buf,cir_buf->head);
	--cir_buf->cur_size;
	
	return 0;
}

/*
 *  *Function:		peek_buf_unit__
 *  *Description:	peek an item in the ring buffer,the peek data will stay in the buffer
 *  *Parameter:		ring_buf:the buffer we want to fetch from
 *					item:the data which we fetched saved in
 *					used_for_multi_peek:if we need read more than one item,we should used this
 *					parameter,every read cycle,this parameter should add 1.if we only peek one
 *					item,this parameter should be 0.
 *  *Return:		-1 if sth error,else 0
 *  *Author:		geeker
 *  *Date:			20151106
 *  *modify:
 *  */
static int8_t peek_buf_unit__(const ring_buf_t *ring_buf,void *item,uint32_t used_for_multi_peek)
{
	uint32_t i;
	const cir_buf_t *cir_buf = ring_buf;
	uint32_t cal_pos = cir_buf->head;
	
	if( cir_buf->cur_size - used_for_multi_peek <= 0)
		return -1;
	
	for(i = 0;i < used_for_multi_peek;i++){
		cal_pos = find_next_pos(ring_buf,cal_pos);
	}
	memcpy(item,(char *)(cir_buf->raw_head) + (cal_pos) * cir_buf->item_size,cir_buf->item_size);
	
	return 0;
}

/*
 *  *Function:		fill_buf
 *  *Description:	fill the ring buffer with the data
 *  *Parameter:		ring_buf:the buffer we want to fill
 *					start:the start address of the data we want to fill in the buffer
 *					length:the length of the data we want to fill
 *  *Return:		the length of the data filled in the ring buffer
 *  *Author:		geeker
 *  *Date:			20151106
 *  *modify:
 *  */
uint32_t fill_buf(ring_buf_t *ring_buf,void *start,uint32_t length)
{
	uint32_t i;
	cir_buf_t *cir_buf = ring_buf;
	
	for(i = 0;i < length;i++){
		if(fill_buf_unit__(cir_buf,(char *)start + i * cir_buf->item_size) < 0)
			break;
	}
	
	return i;
}

/*
 *  *Function:		del_buf
 *  *Description:	delete data from the ring buffer 
 *  *Parameter:		ring_buf:the buffer we want to delete from
 *					length:the length we want to delete
 *  *Return:		the length we delete
 *  *Author:		geeker
 *  *Date:			20151106
 *  *modify:
 *  */
uint32_t del_buf(ring_buf_t *ring_buf,uint32_t length)
{
	uint32_t i,true_len;
	cir_buf_t *cir_buf = ring_buf;
	
	true_len = (length > cir_buf->cur_size)?cir_buf->cur_size:length;

	for(i = 0;i < true_len;i++)
		cir_buf->head  = find_next_pos(cir_buf,cir_buf->head);
	
	cir_buf->cur_size -= true_len;
	return i;
}

/*
 *  *Function:		fetch_buf
 *  *Description:	fill the ring buffer to the assigned address,and the data we fetched will delete
 *  from the ring buffer
 *  *Parameter:		ring_buf:the buffer we want to fetch
 *					start:the address which the fetched data move to
 *					length:the length we want to fetch
 *  *Return:		the length we fetched
 *  *Author:		geeker
 *  *Date:			20151106
 *  *modify:
 *  */
uint32_t fetch_buf(ring_buf_t *ring_buf,void *start,uint32_t length)
{
	uint32_t i;
	cir_buf_t *cir_buf = ring_buf;
	
	for(i = 0;i < length;i++){
		if(fetch_buf_unit__(cir_buf,(char *)start + i * cir_buf->item_size) < 0)
			break;
	}
	
	return i;
}

/*
 *  *Function:		peek_buf
 *  *Description:	fill the ring buffer to the assigned address,and the data we peeked will stay in
 *  the ring buffer
 *  *Parameter:		ring_buf:the buffer we want to peek
 *					start:the address which the peek data fill in
 *					length:the length we want to peek
 *  *Return:		the length we peeked
 *  *Author:		geeker
 *  *Date:			20151106
 *  *modify:
 *  */
uint32_t peek_buf(const ring_buf_t *ring_buf,void *start,uint32_t length)
{
	uint32_t i;
	const cir_buf_t *cir_buf = ring_buf;
	
	for(i = 0;i < length;i++){
		if(peek_buf_unit__(cir_buf,(char *)start + i * cir_buf->item_size,i) < 0)
			break;
	}

	return i;
}


