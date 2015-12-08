#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
#include"product.h" 
#include"hashTable.h"
#include"merge.h"

//哈希函数
unsigned int SDBMHash(char *str)
{
	unsigned int hash=0;
	while(*str)
	{
		hash=(*str++)+(hash<<6)+(hash<<16)-hash;
	}

	return (hash & 0x7FFFFFFF);
}

//初始化哈希表
void  init_hashtable(term *hashTable)
{
	unsigned int i;

        for(i=0;i<HASHTABLE_SIZE;i++)
	{
		hashTable[i].term=NULL;
		hashTable[i].id_list=NULL;
		hashTable[i].next=NULL;
	}
}

//校验malloc是否正常获取内存
void check_malloc(void *str)
{
    if (str==NULL)
    {
	    printf("无法申请内存！");
	    exit(0);
    }
}

//链表拷贝
product_id *copy_list(product_id * src_list)
{
	if(src_list==NULL)
	{
		return NULL;
	}
	
	product_id *head=NULL;
	while(src_list)
	{
		product_id * copy_id=(product_id*)malloc(sizeof(product_id));
		size_t	length_id=strlen(src_list->id);
		copy_id->id=(char*)malloc(length_id+1);
		strcpy(copy_id->id,src_list->id);
		copy_id->id[length_id]='\0';

		copy_id->next=head;
		head=copy_id;
		src_list=src_list->next;
	}
	return head;
}

//创建哈希表
term *create_hashtable(char *filename)
{

    term *hashTable=(term*)malloc(sizeof(term)*HASHTABLE_SIZE);	
    check_malloc(hashTable);
    //初始化哈希表
    init_hashtable(hashTable);

    FILE *fp=fopen(filename,"r");
    if(fp==NULL)
    {
	
	    printf("Can't open the file %s!", filename);
	    exit(0);
    }

    char line_string[10000];
    char *id;
    char *query; 

    //int len_line=sizeof(line_string);
    while(fgets(line_string,10000,fp)!=NULL)
    {

	//去掉每一行的换行符
	int length=strlen(line_string)-1;
	if(line_string[length]=='\n')
	{
		line_string[length]='\0';
	}

	//获取商品信息
        id=strtok(line_string," ");
        int length_id=strlen(id);
	while((query=strtok(NULL," "))!=NULL)
	{

		//查询query在哈希表中的位置
		size_t  hashkey=SDBMHash(query)%HASHTABLE_SIZE; 		
		term * term_pos=hashTable[hashkey].next;
		while( term_pos!=NULL && strcmp(term_pos->term,query))
		{
			term_pos=term_pos->next;
		}
	

		//构造id链表
		product_id * id_temp=(product_id*)malloc(sizeof(product_id));
		check_malloc(id_temp);
		id_temp->id=(char*)malloc(length_id+1);
		strcpy(id_temp->id,id);
	        id_temp->id[length_id]='\0';
		//printf("%s->%s\n",query,id_temp->id);
		//把id插入哈希表中
		if(term_pos==NULL)
		{
			length=strlen(query);
			term * temp=(term*)malloc(sizeof(term));
			check_malloc(temp);
			temp->term=(char*)malloc(length+1); 
			strcpy(temp->term,query);
	       		temp->term[length]='\0';
			temp->id_list=NULL;
			id_temp->next=temp->id_list;
			temp->id_list=id_temp;
			temp->next=hashTable[hashkey].next; 
			hashTable[hashkey].next=temp; 
		}
		else
		{
                      id_temp->next=term_pos->id_list;
		      term_pos->id_list=id_temp;
		}
		//
                //print_list(temp->id_list);
	}
    }

    fclose(fp);
    return hashTable;
}

//在哈希表里查找指定元素，并返回指向链表的头指针
product_id *search_hashtable(term *hashTable , char *product_term)
{
	if(hashTable==NULL || product_term==NULL)
	{
		return NULL;
	}

	unsigned int hashKey=SDBMHash(product_term)%HASHTABLE_SIZE;
	term *temp=hashTable[hashKey].next;
	product_id *head=NULL;

	while( temp!=NULL && strcmp(product_term,temp->term) )
	{
		temp=temp->next;
	}

	if(temp!=NULL)
	{
		product_id *id_temp=temp->id_list;
		head=copy_list(id_temp);
	}
	
	return head;
}

//打印输出结果
void print_list(product_id * head)   
{
	product_id *p=head;

	if(NULL==p)
	{
		printf("No Result !");
	}
	else
	{
		printf("Item List : ");
	}

	while(p!=NULL)
	{
		printf("-> %s",p->id);
		p=p->next;
	}

	printf("\n");
}

//释放哈希表里的内存
void destroy(term *hashTable)
{
	if(NULL==hashTable)
	{
		return ;
	}

	int i=0;

	for(i=0;i<HASHTABLE_SIZE;i++)
	{   
		term *temp=hashTable[i].next;
		while(temp!=NULL)
		{
			term *next_term=temp->next;
			while(temp->id_list!=NULL)
			{
				product_id *next_id=temp->id_list->next;
				free(temp->id_list->id);
				free(temp->id_list);
				temp->id_list=next_id;
			}
			free(temp->term);
			free(temp);
			temp=next_term;
		}
	}

	free(hashTable);
}

//释放链表的内存
void free_list(product_id *src_list)
{
	if (src_list==NULL)
	{
		return ;
	}
	
	while(src_list)
	{
		product_id *next_list=src_list->next;
		free(src_list->id);
		free(src_list);
		src_list=next_list;
	}
	return ;
}
//------------------test--------------------
/*
int main(int argc, char *argv[])
{
        //void print_result(product_id * head);
	term *hash_table=create_hashtable("../data/data1");
	char *product_term="包邮";
	product_id *head=search_hashtable(hash_table,product_term);
	//print_result(head);
	free_list(head);
	destroy(hash_table);
	return 0;
}
*/

