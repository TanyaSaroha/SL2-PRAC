#include<stdlib.h>
#include<stdio.h>
#include<limits.h>
void print(int *a,int n)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf(" %d ",a[(i*n)+j]);
		}
		printf("\n");
	}
}
void create(int *w,int n)
{
	int src,dest;
	char ch;
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
								
								w[(src-1)*n+dest-1]=1;
								
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

void create1(int *f,int n)
{
	int src,dest,wt,i,j;
	char ch;
	
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(i==j)
				f[i*n+j]=0;
			else
				f[i*n+j]=INT_MAX;	
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
								printf("\nenter weight of %d->%d : ",src,dest);
								scanf("%d",&wt);
								f[(src-1)*n+dest-1]=wt;
								
							}
							else
							{
								printf("\ninvalid destination\n");
							}
						}
						else
							printf("\ninvalid source");
					}
	}while(ch=='y');
	
}
void copy(int *a, int **b,int n)
{
	int i;
	for(i=0;i<n*n;i++)
	{
		*(b[0]+i)=a[i];
	}
	
}
void print1(int **a,int n)
{
	int i,j,k;
	
	for(i=0;i<=n;i++)
	{
		
		printf("\n t[ %d ] matrix \n",i);
		for(j=0;j<n;j++)
		{
			for(k=0;k<n;k++)
			{
				if(a[i][j*n+k] == INT_MAX )
					printf(" - ");
				else
					printf(" %d ",a[i][j*n+k]);
					
			}
			printf("\n");
		}
			
		
	}
}

void warshell(int **t,int n)
{
	int i,j,k;
	for(k=1;k<=n;k++)
	{
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
				if(t[k-1][i*n+j]==1 || (t[k-1][i*n+k-1]==1 && t[k-1][(k-1)*n+j]==1 ))
				{
					t[k][i*n+j]=1;
				}
			}
		}
	}
}
int min_(int i,int j)
{
	return i<j ? i:j;
}
void floyd(int **r,int n)
{
	int i,j,k;
	for(k=1;k<=n;k++)
	{
		for(i=0;i<n;i++)
		{
			for(j=0;j<n;j++)
			{
				if(r[k-1][i*n+k-1]!=INT_MAX && r[k-1][(k-1)*n+j]!=INT_MAX)
				{
				
					r[k][i*n+j]=min_(r[k-1][i*n+j] ,(r[k-1][i*n+k-1] + r[k-1][(k-1)*n+j]));
				}
				else
				{
					r[k][i*n+j]=r[k-1][i*n+j];
				}
				
			}
		}
	}
}
int main()
{
	int k,n,i;
	int *w ,**t;
	do
	{
		printf("\n1.Warshall Algorithm\n2.Floyd Algorithm\n3.Exit\n ENTER UR CHOICE : ");
		scanf("%d",&k);
		switch(k)
		{
			case 1:printf("\nENTER NO. OF VERTICES : ");
					scanf("%d",&n);
					w=(int*)calloc(n*n,sizeof(int));
					create(w,n);
					printf("\n.......MATRIX.....\n");
					print(w,n);
					t=(int**)calloc(n+1,sizeof(int*));
					for(i=0;i<=n;i++)
					{
						t[i]=(int*)calloc(n*n,sizeof(int));
						
					}
					copy(w,t,n);
					warshell(t,n);
					print1(t,n);
					free(w);
					for(i=0;i<=n;i++)
						free(t[i]);
					free(t);
					
					break;
			case 2:printf("\nENTER NO. OF VERTICES : ");
					scanf("%d",&n);
					w=(int*)calloc(n*n,sizeof(int));
					create1(w,n);
					printf("\n.......MATRIX.....\n");
					print(w,n);
					t=(int**)calloc(n+1,sizeof(int*));
					for(i=0;i<=n;i++)
					{
						t[i]=(int*)calloc(n*n,sizeof(int));
						
					}
					copy(w,t,n);
					floyd(t,n);
					print1(t,n);
					free(w);
					for(i=0;i<=n;i++)
						free(t[i]);
					free(t);
					break;
			case 3:break;
				
		}
		
		
		
	}while(k!=3);
	
	return 0;
}
