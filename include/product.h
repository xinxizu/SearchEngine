#ifndef _PRODUCT_H_
#define _PRODUCT_H_

//商品id节点
typedef struct product_id
{
	char *id;
	struct product_id *next;
}product_id;

//描述商品term的节点
typedef struct term     
{
	char *term;
	product_id *id_list;
	struct term *next;
}term;




#endif
