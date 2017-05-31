#ifndef CIR_BUF__
#define CIR_BUF__

#define BUF_SIZE		(128)
#define ITEM_SIZE		(1)
#define ITEM_TYPE		char

#define ring_buf_t	void

typedef unsigned char		uint8_t;
typedef signed char			int8_t;
typedef unsigned short		uint16_t;
typedef signed short		int16_t;
typedef unsigned int		uint32_t;
typedef signed int			int32_t;

/*
 *  *Function:		get_cur_size
 *  *Description:	get the data size of the ring buffer
 *  *Parameter:		ring_buf:the ring buffer we want to get the info
 *  *Return:		the data size
 *  *Author:		geeker
 *  *Date:			20151106
 *  *modify:
 *  */
unsigned int get_cur_size(const ring_buf_t *ring_buf);

/*
 *  *Function:		get_capacity
 *  *Description:	get the capacity of the ring buffer
 *  *Parameter:		ring_buf:the ring buffer we want to get the info
 *  *Return:		the capacity of the ring buffer
 *  *Author:		geeker
 *  *Date:			20151106
 *  *modify:
 *  */
unsigned int get_capacity(const ring_buf_t *ring_buf);

/*
 *  *Function:		get_remain_size
 *  *Description:	get the remained size of the ring buffer
 *  *Parameter:		ring_buf:the ring buffer we want to get the info
 *  *Return:		the remained size of the ring buffer
 *  *Author:		geeker
 *  *Date:			20151106
 *  *modify:
 *  */
unsigned int get_remain_size(const ring_buf_t *ring_buf);

/*
 *  *Function:		get_item_size
 *  *Description:	get the item size of the ring buffer
 *  *Parameter:		ring_buf:the ring buffer we want to get the info
 *  *Return:		the item size of the ring buffer
 *  *Author:		geeker
 *  *Date:			20151106
 *  *modify:
 *  */
unsigned int get_item_size(const ring_buf_t *ring_buf);


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
ring_buf_t * create_ring_buf(unsigned int buf_size,unsigned int item_size);

/*
 *  *Function:		destroy_buf
 *  *Description:	destory the ring buffer
 *  *Parameter:		ring_buf:the buffer we want to destory
 *  *Return:		void
 *  *Author:		geeker
 *  *Date:			20151106
 *  *modify:
 *  */
void destroy_buf(ring_buf_t * ring_buf);


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
unsigned int fill_buf(ring_buf_t *ring_buf,void *start,unsigned int length);

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
unsigned int del_buf(ring_buf_t *ring_buf,unsigned int length);

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
unsigned int fetch_buf(ring_buf_t *ring_buf,void *start,unsigned int length);

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
unsigned int peek_buf(const ring_buf_t *ring_buf,void *start,unsigned int length);

#endif

