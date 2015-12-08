#include"hashTable.h"
#include"merge.h"
#include<time.h>

int main(int argc, char *argv[])
{
	//建立倒排表
	clock_t start,end; 
	start=clock();
	term *hash_table=create_hashtable("../data/small_data");
	end=clock();
	double duration=(double)(end-start)/CLOCKS_PER_SEC;
	printf("Bulid inverted table cost : %lf seconds\n",duration);

	//输入要查询的term
	char * product_term=(char*)malloc(20);
 	size_t  array_count=0;
	product_id *id_array[10]={NULL};
	
	printf("please input the term : ");
	scanf("%s",product_term);

	while(strcmp(product_term,"over"))
	{
		id_array[array_count++]=search_hashtable(hash_table,product_term);
		//print_result(search_hashtable(hash_table,product_term));
		printf("please input the term : ");
		scanf("%s",product_term);
	}

	//归并链表
	product_id *id_result=merge(array_count,id_array);
	print_result(id_result);
	
	//释放内存
	destroy(hash_table);
	size_t i;
	for(i=0;i<array_count;i++)
	{
		free_list(id_array[i]);
	}
	free(product_term);
	free_list(id_result);
	
	return 0;

}
