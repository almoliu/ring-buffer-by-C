#include <stdio.h>
#include "ring_buffer.h"


int main()
{
	int i,j;
	int a[20];
	int b[20];
	ring_buf_t *ring_buf = create_ring_buf(20,sizeof(int));
	
	for(i = 0;i < 15;i++){
		fill_buf(ring_buf,&i,1);
	}

	i = del_buf(ring_buf,10);
	printf("del_buf return is %d,current_size = %d,capacity = %d,remain_size = %d,item_size = %d \n",i,get_cur_size(ring_buf),get_capacity(ring_buf),get_remain_size(ring_buf),get_item_size(ring_buf));
#if 0
	for(i = 0;i < 15;i++)
		printf("a[%d] = %d		",i,a[i]);

	i = fetch_buf(ring_buf,b,15);
	printf("fetch_buf return is %d,current_size = %d,capacity = %d,remain_size = %d,item_size = %d \n",i,get_cur_size(ring_buf),get_capacity(ring_buf),get_remain_size(ring_buf),get_item_size(ring_buf));

	for(i = 0;i < 15;i++)
		printf("b[%d] = %d		",i,b[i]);
//---------------------------------------------------------------------------------------
	for(i = 0;i < 10;i++){
		j = 10 - i;
		fill_buf(ring_buf,&j,1);
	}

	i = peek_buf(ring_buf,a,10);
	printf("peek_buf return is %d,current_size = %d,capacity = %d,remain_size = %d,item_size = %d \n",i,get_cur_size(ring_buf),get_capacity(ring_buf),get_remain_size(ring_buf),get_item_size(ring_buf));
	for(i = 0;i < 10;i++)
		printf("a[%d] = %d		",i,a[i]);

	i = fetch_buf(ring_buf,b,15);
	printf("fetch_buf return is %d,current_size = %d,capacity = %d,remain_size = %d,item_size = %d \n",i,get_cur_size(ring_buf),get_capacity(ring_buf),get_remain_size(ring_buf),get_item_size(ring_buf));
	for(i = 0;i < 10;i++)
		printf("b[%d] = %d		",i,b[i]);
#endif
	destroy_buf(ring_buf);
	
	return 0;
}








