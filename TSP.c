#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
typedef struct node
{
	int lower,*rcm,vertex_no,level; 
	struct node *parent;
}node;
typedef struct list
{
	node* addr;
	struct list* next;
}list;
void insert(list **head,node *n)
{
	list *l,*p,*q;
	l=(list*)calloc(1,sizeof(list));
	l->addr=n;
	l->next=NULL;
	if((*head)==NULL)
	{
		(*head)=l;
		return;
	}
	else
	{
		p=*head;
		q=p;
		while(p!=NULL && p->addr->lower<=n->lower)
		{
			q=p;
			p=p->next;
		}
		if(p==*head)
		{
			l->next = *head;
			*head = l;
		}else{
			l->next=p;
			q->next= l;
		}
		
	}
	
}
void dead_insert(list **head,node *n)
{
	list *l,*p,*q;
	l=(list*)calloc(1,sizeof(list));
	l->addr=n;
	l->next=NULL;
	if((*head)==NULL)
	{
		(*head)=l;
		return;
	}
	else
	{
		l->next=*head;
		*head=l;
		
	}
}
	
int isempty(list *head)
{
	return (head==NULL)?1:0;
}

node* deletee(list **head)
{
	node* n;
	list* temp;
	temp=*head;
	n=temp->addr;
	*head=(*head)->next;
	free(temp);
	return n;

}

void printlist(list* head)
{
	list* p;
	p=head;
	printf("\n\nLIST OF LIVE NODE\n");
	while(p->next!=NULL)
	{
		printf("%d->",p->addr->lower);
		p=p->next;
	}
	if(p!=NULL)
	{
		printf("%d",p->addr->lower);
	}
	printf("\n\n");
}
void create(int *w,int n)
{
	int src,dest,wt,i,j;
	char ch;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			w[(i*n)+j]=INT_MAX;
				
			
		}
		
	}
	do
	{
	
		printf("\nIS THEIR ANY EDGE PRESS Y IF YES ELSE N : ");
				scanf(" %c",&ch);
					if(ch=='y')
						{
						printf("\n ENTER SOURCE VERTEX : ");
						scanf("%d",&src);
						if(src<=n && src>0)
						{
							printf("\n ENTER DESTINATION VERTEX : ");
							scanf("%d",&dest);
							if(dest<=n && dest>0)
							{
								
								printf("ENTER WEIGHT OF %d->%d \n",src,dest);
								scanf("%d",&wt);
								w[(src-1)*n+dest-1]=wt;
								
								
							}
							else
							{
								printf("\ninvalid destination\n");
							}
						}
						else
							printf("\ninvalid source\n");
					}
	}while(ch=='y');
	
}
void print(int *a,int n)
{
	int i,j;
	
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(a[(i*n)+j]!=INT_MAX)
				printf(" %d ",a[(i*n)+j]);
			else
				printf("  ~");
		}
		printf("\n");
	}
}
int rcm(int* g,int n)
{
	int i,j,k,min,c=0;
	
	for(i=0;i<n;i++)
	{
		min=INT_MAX;
		for(j=0;j<n;j++)
		{
			if(g[i*n+j]<min)
			{
				min=g[i*n+j];
			}
		}
		if(min!=INT_MAX && min!=0)
		{
			c=c+min;
			for(j=0;j<n;j++)
			{
				if(g[i*n+j]!=INT_MAX)
					g[i*n+j]=g[i*n+j]-min;
			}
		}
	}

	for(i=0;i<n;i++)
	{
		min=INT_MAX;
		for(j=0;j<n;j++)
		{
			if(g[j*n+i]<min)
			{
				min=g[j*n+i];
			
			}
		}
		if(min!=INT_MAX && min!=0)
		{
			c+=min;
			for(j=0;j<n;j++)
			{
				if(g[j*n+i]!=INT_MAX)
					g[j*n+i]-=min;
			}
		}
	}

	return c;
}
void copy(int *o,int *n,int m)
{
	int i,j;
	for(i=0;i<m;i++)
	{
		for(j=0;j<m;j++)
		{
			n[i*m+j]=o[i*m+j];
		}
	}
	
}
void print_node(node* n,int m,int cost)
{
	printf("\nVERTEX : %d\n",n->vertex_no+1);
	printf("LEVEL : %d\n",n->level+1);
	printf("c^(c) = c^(p)+ rcm[p][p,c] + rcm[c]\n     = %d + %d + %d\n     = %d \n",n->parent->lower,n->parent->rcm[(n->parent->vertex_no)*m+n->vertex_no],cost,n->lower);
	if(n->parent!=NULL)
			printf("\nPARENT : %d\n",(n->parent->vertex_no)+1);
	else
			printf("NO PARENT EXIST\n");
		
	printf("RCM\n");
	print(n->rcm,m);
	printf("\n");
	
}
void print_root(node* n,int m,int cost)
{
	printf("\nVERTEX : %d\n",n->vertex_no+1);
	printf("LEVEL : %d\n",n->level+1);
	printf("c^(c) = c^(p)+ rcm[p][p,c] + rcm[c]\n     = %d + %d + %d\n     = %d \n",0,0,cost,n->lower);
	if(n->parent!=NULL)
			printf("\nPARENT : %d\n",(n->parent->vertex_no)+1);
	else
			printf("\nNO PARENT EXIST\n");
		
	printf("RCM\n");
	print(n->rcm,m);
	printf("\n");
	
}
void path(node *n,int m)
{
	int *x,i;
	x=(int*)calloc(1,m*sizeof(int));
	for(i=m-1;i>=0;i--)
	{
		x[i]=(n->vertex_no)+1;
		
		n=n->parent;
	}
	for(i=0;i<m;i++)
	{
		printf("%d -> ",x[i]);
	}
	printf("%d",x[0]);
	free(x);
}
void tsp(int *g,int m)
{
	list *live=NULL,*dead=NULL;
	node *n,*enode;
	node *ansnode=NULL;
	int *r;
	int i,j,c,upper=INT_MAX;
	r=(int*)calloc(m*m,sizeof(int));
	copy(g,r,m);
	c=rcm(r,m);
	n=(node*)calloc(1,sizeof(node));
	//ansnode=(node*)calloc(1,sizeof(node));
	n->level=0;
	n->vertex_no=0;
	n->lower=c;
	n->rcm=r;
	n->parent=NULL;	
	printf("x%d = %d\n",n->level+1,1);
	print_root(n,m,c);
	insert(&live,n);
	while(! isempty(live))
	{
		printlist(live);
		enode=deletee(&live);
		
		if(enode->lower<=upper)
		{
			
			for(i=0;i<m;i++)
			{
				if(enode->rcm[(enode->vertex_no )*m+i]!=INT_MAX )
				{
					
					r=(int*)calloc(m*m,sizeof(int));
					n=(node*)calloc(1,sizeof(node));
					copy(enode->rcm,r,m);
					for(j=0;j<m;j++)
					{
						r[(enode->vertex_no )*m+j]=INT_MAX;
						r[j*m+i]=INT_MAX;
					}
					r[i*m+0]=INT_MAX;
					c=rcm(r,m);
					
					n->level=(enode->level)+1;
					n->vertex_no=i;
					n->lower= enode->lower + enode->rcm[(enode->vertex_no)*m+i]+c;
					n->rcm=r;
					n->parent=enode;
					printf("x%d = %d\n",n->level+1,i+1);
					print_node(n,m,c);
					if(n->level==m-1)
					{
						
						if(n->lower<upper && g[(n->vertex_no)*m]!=INT_MAX)
						{
							
							if(ansnode!=NULL)
							{
								free(ansnode->rcm);								
								free(ansnode);
							}
							printf("\nUPPER CHANGE FROM %d TO %d ",upper ,n->lower);							
							upper=n->lower;
							ansnode=n;		
						}
						else
						{
							free(n->rcm);
							free(n);
						}
					}
					else
					{
						insert(&live,n);
					}
				}
			}
			dead_insert(&dead,enode);
		}
		else
		{
			printf("\nx%d = %d IS KILLED\n  c^(.)  Upper\n   %d  >  %d",enode->level+1,enode->level+1,enode->lower,upper );
			free(enode->rcm);
			free(enode);
		}
		
	}
	
	
	if(ansnode!=NULL)	
	{
		printf("\nPATH :");
		path(ansnode,m);
		free(ansnode->rcm);		
		free(ansnode);
	}
	else
	{
		printf("\nNO SOLUTION EXIST\n");
	}
	printf("\n\n");
	while(!isempty(dead))
	{
		n=deletee(&dead);
		printf("%d IS KILLED\n",n->lower);
		free(n->rcm);
		free(n);
	}
}

int main()
{
	
	//int g[25]={INT_MAX,10,15,20,10,INT_MAX,35,25,15,35,INT_MAX,30,20,25,30,INT_MAX};
	int *g1=NULL;
	int *g;
	int n;
	//int n=4;
	int i,k,j;
		do
	{
		printf("\n1.Input(Directed Graph) \n2.Solution by LC Branch and Bound\n3.Exit\n ENTER UR CHOICE : ");
		scanf("%d",&k);
		switch(k)
		{
			case 1:printf("\n.......MATRIX.....\n");
					printf("ENter no of vertices \t");
					scanf("%d",&n);
					g=(int*)calloc(n*n,sizeof(int));
					create(g,n);
					print(g,n);
					break;
			case 2:		tsp(g,n);
					break;	
			case 3:	break;
		}
	}while(k!=3);	
	return 0;
}
