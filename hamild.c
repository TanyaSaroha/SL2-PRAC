
#include<stdio.h>
#include<stdlib.h>

void create(int *h, int n, int m)
{
	int src,dest,i;
		for(i=1;i<=m;i++)
		{
			printf("Enter Source of edge %d:-  ",i);
			scanf("%d",&src);
			if(src>0 || src<=n)
			{
				printf("Enter destination of edge %d:-  ",i);
				scanf("%d",&dest);
				if(dest >0 && dest <=n)
				{
					
					if(h[(src-1)*n+(dest-1)]==1)
					{
						printf("edge already exists");
						i--;
					}
					else
						h[(src-1)*n+(dest-1)]=1;
				}
				else
					{
						printf("INVALID");
						i--;
					}
			}
			else
			{
				printf("INVALID");
				i--;
			}
		}
}
void display(int *h, int n)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%d ",h[i*n+j]);
		}printf("\n");
	}
}

void nextval(int k, int n, int *x, int *adj)
{
	printf("THIS IS ONE");
	int i;
	while(1)
	{
		if(x[k]==n)
			x[k]=-1;
		x[k]=x[k]+1;
		if(x[k]==n)
			return;
		if(adj[x[k-1]*n+x[k]]==1)
		{
			for(i=0;i<k;i++)
			{
				if(x[i]==x[k])
					break;
			}
			if(i==k)
			{
				if(k<n-1||(k=n-1) && (adj[x[k]*n+0]==1))
				return;
			}
		
		}
	
	}
}
int rec(int k, int n, int flag, int *x, int *adj, int *count)
{
	printf("THIS IS rec");
	int i;
	while(1)
	{
		if(flag==-1)
			return flag;
		nextval(k,n,x,adj);
		if(x[k]==n)
			return flag;
		if(k==n-1)
		{
			*count=*count+1;
			printf("\n%d solution is:-\n",*count);
			for(i=0;i<n;i++)
			{
				printf("%d->", x[i]+1);
			}
			printf("%d",1);
			printf("\n");
			if(flag==0)
				return -1;
		}
		else
		{
			flag=rec(k+1,n,flag,x,adj,count);
		}
	}
	return flag;
}

int ite(int n, int flag, int *x, int *adj)
{
	printf("THIS IS ite");
	int i,count=0,k;
	k=1;
	while(k>0 && k<n)
	{
		nextval(k,n,x,adj);
		if(x[k]==n)
		{
			x[k]=-1;
			k--;
		}
		else
		{
			if(k==n-1)
			{
				count++;
				printf("%d solution is:- ",count);
				for(i=0;i<n;i++)
				{
					printf("%d->", x[i]+1);
				}
				printf("%d",1);
				printf("\n");
				if(flag==0)
					return -1;
			}
			else
				k++;
		}
	}
	return count;
}

int main()
{
	int n,m,*adj=NULL,ch,*x;
		int ch1;
	int count=0,i,a;
	do
	{
		printf("\n*HAMILTONIAN CYCLE*\n\n Choosw what you want to do \n press 1 for entering the graph\n press 2 for finding hamiltonian path using recursive backtracking\n press 3 to find hamitonian path using iterative backtracking\n press 4 to exit\n");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1: if(adj!=NULL)
						free(adj);
					printf("\tEnter the number of vertices in your graph\t");	
					scanf("%d",&n);
					printf("Enter the number of edges in your graph\t");
					scanf("%d",&m);
					adj=(int *)calloc(n*n,sizeof(int));
					create(adj,n,m);	
					printf("\nTHE ADJACENCY MATRIX YOU ENTERED IS\n");
					display(adj,n);
					break;
			case 2:
					do
					{
						printf("\nTHIS IS RECURSIVE BACKTRAKING\npress 1 for all solutions\npress 2 for one solution\npress 3 to exit");
						scanf("%d",&ch1);
						x=(int *)malloc(n*sizeof(int));
						x[0]=0;
						for(i=1;i<n;i++)
							x[i]=-1;
						switch(ch1)
						{
							case 1: //all solutions
									count=0;
									rec(1,n,1,x,adj,&count);
									break;
							case 2: //one solution
									count=0;
									rec(1,n,0,x,adj,&count);
									break;
							case 3: break;
						}
						//free(x);
					}while((ch1)!=3);
					break;
					
			case 3:	do
					{
					printf("\nTHIS IS ITERATIVE BACKTRAKING\npress 1 for all solutions\npress 2 for one solution\npress 3 to exit");
					scanf("%d",&ch1);
					x=(int *)malloc(n*sizeof(int));
					x[0]=0;
					for(i=1;i<n;i++)
						x[i]=-1;
					switch(ch1)
					{
						case 1: //all solutions
								a=ite(n,1,x,adj);
								printf("OTTAL soln are %d",a);
								break;
						case 2: //one solution
								ite(n,0,x,adj);
								break;
						case 3: break;
					}
					//free(x);
	
					}while(ch1!=3);
					
					break;
			case 4: printf("\nGOOD BYE!\n");
					break;
			default: exit(0);
		}
		//free(adj);
	}while(ch!=4);
return 0;
}
