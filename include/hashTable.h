#ifndef _HASHTABLE_H_
#define _HASHTABLE_H_

#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
#include"product.h" 
#include"hashTable.h"

#define HASHTABLE_SIZE 1001
//哈希函数
unsigned int SDBMHash(char *str);

//初始化哈希表
void  init_hashtable(term *hashTable);

//校验malloc是否正常获取内存
void check_malloc(void *str);

//链表拷贝
product_id *copy_list(product_id * src_list);

//创建哈希表
term *create_hashtable(char *filename);

//在哈希表里查找指定元素，并返回指向链表的头指针
product_id *search_hashtable(term *hashTable , char *product_term);

////打印输出结果
void print_list(product_id * head);

//释放哈希表里的内存
void destroy(term *hashTable);

//释放链表的内存
void free_list(product_id *src_list);
#endif
