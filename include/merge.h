#ifndef _MERGE_H_
#define _MERGE_H_
#include"product.h"

//交换函数
void swap(product_id *data1 , product_id *data2);

//向堆里面添加元素，并调整为新堆(大顶堆)
void push_heap(product_id *a[],int index);

//生成堆（大顶堆）
void make_heap(product_id * a[],int length);

//替换堆顶元素之后调整为新堆
void pop_heap(product_id *  a[],int n);

//判断有没有链表指向了空指针
int isNULL(product_id *product_id_array[],size_t count);

//判断堆中的元素是否都相同
int  isEqual(product_id *product_id_array[],size_t count);

//归并返回指向所有相同商品的链表head
product_id  * merge(size_t count, product_id *product_id_array[]);

//打印输出搜索结果
void print_result(product_id * head);



#endif 
