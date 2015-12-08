#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
#include"product.h"
#include"merge.h"
#include"hashTable.h"

//交换函数
void swap(product_id *data1 , product_id *data2)  
{
    product_id *temp;

	temp=data1;
	data1=data2;
	data2=temp;
} 


//向堆里面添加元素，并调整为新堆(小顶堆)
//升序为小顶堆，降序为大顶堆
void push_heap(product_id *a[],int index)  
{
	if (index<=0 || a==NULL)
	{
		return;
	}

	int parent=(index-1)/2;

	while(parent>=0 && index!=0)
	{
		if(strcmp(a[parent]->id,a[index]->id)<0)
		{
			return;
		}

		product_id *temp;
        	temp=a[parent];
      	        a[parent]=a[index];
                a[index]=temp;

		index=parent;
		parent=(index-1)/2;
	}

}

//生成堆（大顶堆）
void make_heap(product_id * a[],int length)  
{
	if (a==NULL)
	{
		return;
	}
        
	int i;

	for( i=0;i<length;i++)
	{
		push_heap(a,i);
	}
}


//替换堆顶元素之后调整为新堆
void pop_heap(product_id *  a[],int n)  
{
	if (a==NULL || n==0)
	{
		return;
	}

	int i=0;
	int leftChild=i*2+1;
	while(leftChild<n)
	{
		int child=leftChild;
		if(leftChild+1<n )
		{
			child= strcmp(a[leftChild]->id,a[leftChild+1]->id)>0 ? leftChild :leftChild+1;
		}
		
		if(strcmp(a[i]->id,a[child]->id)>=0)
		{
			return;
		}

		//swap(a[i],a[child]);
	        product_id *temp;
        	temp=a[i];
      	        a[i]=a[child];
        	a[child]=temp;

		i=child;
	    	leftChild=i*2+1;
	}
}

//判断有没有链表指向了空指针
int isNULL(product_id *product_id_array[], size_t  count)     
{
	int i;
        if (count<=0 || product_id_array==NULL)
	{
		return 0;
	}

	for(i=0;i<count;i++)
	{
		if(NULL==product_id_array[i])
		{
			return 1;
			break;
		}
	}

	return 0;
}

//判断堆中的元素是否都相同
int  isEqual(product_id *product_id_array[], size_t  count)    
{
	char* temp=product_id_array[0]->id;
	int i;

	for(i=1;i<count;i++)
	{
		if(strcmp(product_id_array[i]->id,temp))
		{
			return 0;
		}
	}

	return 1;
}



//归并返回指向所有相同商品的链表head(取交集)
product_id  * merge(size_t  count, product_id *product_id_array[])  
{
        int i;
        product_id *head=NULL;
	
	if(count<=0)
	{
		return head;
	}
        //判断商品数组中有没有空指针，如果没有就构造堆
	if(isNULL(product_id_array,count))
	{
		return head;
	}
	else
	{			
        	make_heap(product_id_array,count);
	}
    
	//逐个查找相似的商品
        while(!isNULL(product_id_array,count))
	{
		if(isEqual(product_id_array,count))
		{
			 product_id *temp=(product_id*)malloc(sizeof(product_id));
			 check_malloc(temp);
			 temp->id=(char*)malloc(sizeof(product_id_array[0]->id));
			 check_malloc(temp->id);
		         strcpy(temp->id,product_id_array[0]->id);

			 temp->next=head;
			 head=temp;
                       
                         for(i=0;i<count;i++)
			 {
				product_id_array[i]=product_id_array[i]->next;
			 }

	    	        if(isNULL(product_id_array,count))
		   	{
				return head;
			}
			else
			{
				make_heap(product_id_array,count);
			}
		 }

		else
		{
			product_id_array[0]=product_id_array[0]->next;

	    	        if(product_id_array[0]==NULL)
			{
				return head;
			}
			else
			{
				pop_heap(product_id_array,count);
			}
		}
	}

	return head;
}   

//打印输出搜索结果
void print_result(product_id * head)   
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

/*
//返回相似商品的id列表
char *search_merge(char *args,product *hashTable)
{

	char *res;
	res=(char*)malloc(sizeof(char)*10000);
	res[0]='\0';

       	if (args==NULL || hashTable==NULL)
	{
		strcat(res,"No same ID!");
                return res;
	}

	product_id *head=unionSet(args, hashTable);
	head=insert_sort(head);
        //printSameID(head);

	if (head==NULL)
	{
		strcat(res,"No same ID!");
        }
	else
        {
		 strcat(res,"Same ID:");
	}

	product_id *p=head;

	 while(p)
	 {
		strcat(res,p->id);
		strcat(res,",");
		p=p->next;
	 }

	 destroy_head(head);
	 return res;
}
*/

