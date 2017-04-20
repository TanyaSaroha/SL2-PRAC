#include<string.h>
#include<stdio.h>
#include<stdlib.h>
typedef struct info
{
	char c;
	int freq;
}info;

typedef struct huff
{
	info data;
	struct huff *lc,*rc;
		
}huff;

typedef struct list 
{
	int flag;
	union u
	{
		info data;
		huff* addr;
	}u;
	struct list * next;
}list;

typedef struct hashmap
{
	char * code;
}hashmap;

sort( info *arr, int n)
{
	int i,j;
	info temp;
	for(i = 0; i < n;i++)
		for(j = 0 ;j < n-i-1 ;j++)
		{
			if(arr[j].freq > arr[j+1].freq)
			{
				temp = arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=temp;
			}
		}			 		
}

print(info* arr , int n)
{
	int i ;
	for( i = 0; i < n ; i++)
		printf("%c-%d\t",arr[i].c,arr[i].freq);
	
}

list* create_list(info* arr,int n)
{
	int i;	
	list *head=NULL,*ptr=NULL;
	for(i = 0 ;i < n ;i++)
	{	
		list* node = (list*) malloc(sizeof(list));
		node->flag=0;
		node->u.data.c=arr[i].c;
		node->u.data.freq=arr[i].freq;
		node->next=NULL;
		if(head==NULL)
			head=ptr=node;
		else
		{
			ptr->next=node;
			ptr=ptr->next;
		}
	}
	return head;
}	

huff*create_tree(list *head)
{
	list*ptr=head,*temp;
	huff * node,*left,*right;
	if(ptr->next!=NULL)
	{
		while(ptr!=NULL && ptr->next!=NULL)
		{
			if(ptr->flag==0)
			{
				node=(huff*)malloc(sizeof(huff));
				node->data.c = ptr->u.data.c;
				node->data.freq = ptr->u.data.freq;
				node->lc=NULL;
				node->rc=NULL;
			}
			else
			{
				node=ptr->u.addr;
			}
			left=node;
			temp=ptr;
			ptr=ptr->next;
			free(temp);
			
			if(ptr->flag==0)
			{
				node=(huff*)malloc(sizeof(huff));
				node->data.c = ptr->u.data.c;
				node->data.freq = ptr->u.data.freq;
				node->lc=NULL;
				node->rc=NULL;
			}
			else
			{
				node=ptr->u.addr;
			}
			right=node;
			node=(huff*)malloc(sizeof(huff));	//parent node
			node->data.freq = left->data.freq + right->data.freq;
			node->data.c ='-';
			node->lc=left;
			node->rc=right;
			ptr->flag=1;
			ptr->u.addr=node;
			int pat=node->data.freq;
			temp=ptr;
			
			while(temp->next!=NULL && ((temp->next->flag==0 && pat > temp->next->u.data.freq)||(temp->next->flag==1 && pat > temp->next->u.addr->data.freq)))
				temp=temp->next;
				
			if(temp!=ptr)
			{	
				head = ptr->next;
				ptr->next =temp->next;
				temp->next =ptr;
				ptr=head;
			}
			else
				head=ptr;
		}
	}
	else
	{
		node=(huff*)malloc(sizeof(huff));
		node->data.c = head->u.data.c;
		node->data.freq = head->u.data.freq;
		node->lc=NULL;
		node->rc=NULL;
		head->u.addr=node;
		head->flag=1;
	}	
	node=head->u.addr;
	free(head);
	return node;	
}
traversal(huff*tree,int index,char ch[],hashmap map[])
{
	if(tree!=NULL)
	{
		if(tree->lc==NULL)
		{
			map[tree->data.c-'a'].code =(char*) malloc(index*sizeof(char)); 
			ch[index]='\0';
			strcpy(map[tree->data.c-'a'].code,ch);
		}
		ch[index]='0';
		traversal(tree->lc,index+1,ch,map);
		printf("%c=%d ",tree->data.c,tree->data.freq);
		ch[index]='1';
		traversal(tree->rc,index+1,ch,map);
	}
}

int main()
{
	info*arr;
	int n,i,check[26]={},freq;
	hashmap str[26];
	char ch[26],c;
	printf("\n enter no. the elements");
	scanf("%d",&n);
	while(n<=0)
	{
		printf("enter valid integer");
		scanf("%d",&n);
	}
	arr=(info*) malloc(n*sizeof(info));
	for(i = 0; i<n ; i++)
	{
		getchar();
		printf("\nenter character :");
		scanf("%c",&c);
		printf("\nenter frequency :");
		scanf("%d",&freq);
		if(check[c-'a']==0)
		{
			arr[i].c=c;
			arr[i].freq=freq;		
			check[arr[i].c-'a']++;
		}
		else
		{	
			printf("\ndata already exists\n");
			i--;
		} 
	}
	print(arr,n);
	sort(arr,n);
	printf("\nafter sorting\n");
	print(arr,n);
	list * head=create_list(arr,n);
	list * ptr=head;
	printf("\nlist created\n");
	while(ptr!=NULL)
	{
		printf(" %c %d ",ptr->u.data.c,ptr->u.data.freq);
		ptr=ptr->next;
	} 
	huff* tree=create_tree(head);
	printf("root is %d\n",tree->data.freq);
	traversal(tree,0,ch,str);
	//encoding
	printf("\n enter string to encode \n");
	scanf("%s",ch);
	printf("%s",ch);
	for(i=0;i<strlen(ch);i++)
	   	 if(!check[ch[i]-'a'])
			break;
	if(i==strlen(ch))
	{
		for(i=0;i<strlen(ch) ;i++)
		{
			printf("%s",str[ch[i]-'a'].code);
		}
	}
	else
	printf("\ninvalid string!\n");	
	//decoding 
	printf("\n enter string to decode \n");
	scanf("%s",ch);
	i=0;
	huff*temp=tree;
	while(ch[i]!='\0')
	{
		if(ch[i]!='0'&& ch[i]!='1')
		{
			printf("invalid string ");
			break;
		}
		if(temp->lc==NULL)
		{
			printf("%c",temp->data.c);
			temp=tree;
			
		}
		if(ch[i]=='0')
		{
			temp=temp->lc;
			i++;
		}
		if(ch[i]=='1')
		{
			temp=temp->rc;
			i++;
		}
	}
		if(temp->lc==NULL)
		{
			printf("%c",temp->data.c);
		}
		else
		printf("\ninvalid");
	
}
