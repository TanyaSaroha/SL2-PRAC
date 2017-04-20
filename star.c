#include<stdio.h>
#include<stdlib.h>

int check(int n)
{
	int num=1;
	while(num<n)
	{
		num=num*2;
	}
	return num;
}

void enter(int *a, int n, int n1)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			scanf("%d",&a[(i*n1)+j]);
		}
	}
}

void sum(int *a, int *b, int *c, int n)
{
	int i,j;
	//printf("\nHI in sum \n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			c[(i*n)+j]=a[(i*n)+j]+b[(i*n)+j];
		}
	}
}

void minus(int *a, int *b, int *c, int n)
{
	int i,j;
	//printf("\nHI in minus\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			c[(i*n)+j]=a[(i*n)+j]-b[(i*n)+j];
		}
	}
}
/*
void print1(int *a, int n1)
{
	int i,j;
	//printf("\nHI display1\n");
	for(i=0;i<n1;i++)
	{
		for(j=0;j<n1;j++)
		{
			printf("%d\t",a[(i*n1)+j]);
		}
	}printf("\n");
}*/

void copy1(int *c,int *c1,int *c2,int *c3,int *c4,int n)
{
	int i,j;
	//printf("\nconquer\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			c[i*2*n+j]         = c1[i*n+j];
			c[i*2*n +j+n]      = c2[i*n+j];
			c[(i+n)*(2*n)+j]   = c3[i*n+j];
			c[(i+n)*(2*n)+j+n] = c4[i*n+j];
	
		}
	}
}

void copy(int *a,int*b,int *a1,int *a2,int *a3,int *a4,int *b1,int *b2,int *b3,int *b4,int n)
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			a1[i*n +j]=a[i*2*n+j];
			b1[i*n +j]=b[i*2*n+j];
			a2[i*n +j]=a[i*2*n +j+n];
			b2[i*n +j]=b[i*2*n +j+n];
			a3[i*n +j]=a[(i+n)*(2*n)+j];
			b3[i*n +j]=b[(i+n)*(2*n)+j];
			a4[i*n +j]=a[(i+n)*(2*n)+j+n];
			b4[i*n +j]=b[(i+n)*(2*n)+j+n];
		}
	}
}
void strassen(int *a, int *b, int *c, int n1)
{
	int *a1,*a2,*a3,*a4,*b1,*b2,*b3,*b4,*c1,*c2,*c3,*c4,*t1,*t2,*p1,*p2,*p3,*p4,*p5,*p6,*p7;
	//printf("\nHI in strassens\n");
	a1=(int *)calloc((n1/2)*(n1/2),sizeof(int));
	a2=(int *)calloc((n1/2)*(n1/2),sizeof(int));
	a3=(int *)calloc((n1/2)*(n1/2),sizeof(int));
	a4=(int *)calloc((n1/2)*(n1/2),sizeof(int));
	b1=(int *)calloc((n1/2)*(n1/2),sizeof(int));
	b2=(int *)calloc((n1/2)*(n1/2),sizeof(int));
	b3=(int *)calloc((n1/2)*(n1/2),sizeof(int));
	b4=(int *)calloc((n1/2)*(n1/2),sizeof(int));
	p1=(int *)calloc((n1/2)*(n1/2),sizeof(int));
	p2=(int *)calloc((n1/2)*(n1/2),sizeof(int));
	p3=(int *)calloc((n1/2)*(n1/2),sizeof(int));
	p4=(int *)calloc((n1/2)*(n1/2),sizeof(int));
	p5=(int *)calloc((n1/2)*(n1/2),sizeof(int));
	p6=(int *)calloc((n1/2)*(n1/2),sizeof(int));
	p7=(int *)calloc((n1/2)*(n1/2),sizeof(int));
	t1=(int *)calloc((n1/2)*(n1/2),sizeof(int));
	t2=(int *)calloc((n1/2)*(n1/2),sizeof(int));
	c1=(int *)calloc((n1/2)*(n1/2),sizeof(int));
	c2=(int *)calloc((n1/2)*(n1/2),sizeof(int));
	c3=(int *)calloc((n1/2)*(n1/2),sizeof(int));
	c4=(int *)calloc((n1/2)*(n1/2),sizeof(int));
	
	if(n1==1)
		c[0]=a[0]*b[0];
	else
	{
			
		copy(a,b,a1,a2,a3,a4,b1,b2,b3,b4,n1/2);
		minus(b2,b4,t1,n1/2);
		//print1(t1,n1/2);
		strassen(t1,a1,p1,n1/2);
		//print1(p1,n1/2);
		sum(a1,a2,t1,n1/2);
		//print1(t1,n1/2);
		strassen(t1,b4,p2,n1/2);
		//print1(p2,n1/2);
		sum(a3,a4,t1,n1/2);
		//print1(t1,n1/2);
		strassen(t1,b1,p3,n1/2);
		//print1(p3,n1/2);
		minus(b3,b1,t1,n1/2);
		strassen(t1,a4,p4,n1/2);
		//print1(p4,n1/2);
		sum(a1,a4,t1,n1/2);
		sum(b1,b4,t2,n1/2);
		strassen(t1,t2,p5,n1/2);
		//print1(p5,n1/2);
		minus(a2,a4,t1,n1/2);
		sum(b3,b4,t2,n1/2);
		strassen(t1,t2,p6,n1/2);
		//print1(p6,n1/2);
		minus(a1,a3,t1,n1/2);
		sum(b1,b2,t2,n1/2);
		strassen(t1,t2,p7,n1/2);
		//print1(p7,n1/2);
		
		sum(p6,p5,t1,n1/2);
		minus(p4,p2,t2,n1/2);
		sum(t1,t2,c1,n1/2);
		sum(p1,p2,c2,n1/2);
		sum(p3,p4,c3,n1/2);
		sum(p1,p5,t1,n1/2);
		minus(p3,p7,t2,n1/2);
		minus(t1,t2,c4,n1/2);
		//print1(c1,n1/2);
		//print1(c2,n1/2);
		//print1(c3,n1/2);
		//print1(c4,n1/2);
		
		copy1(c,c1,c2,c3,c4,n1/2);		
	}	
}
void print(int *a, int n, int n1)
{
	int i,j;
	//printf("\nHI display\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			printf("%d\t",a[i*n1+j]);
		}printf("\n");
	}

}
int main()
{
	int n,n1,*a,*b,*c;
	printf("\nEnter the size of your matrix\n");
	scanf("%d",&n);
	n1=check(n);
	a=(int *)calloc(n1*n1,sizeof(int));
	b=(int *)calloc(n1*n1,sizeof(int));
	printf("\nEnter the elements of matrix 1: \n");
	enter(a,n,n1);
	printf("\nEnter the elements of matrix 2: \n");
	enter(b,n,n1);
	printf("\n The First matrix you entered is \n");
	print(a,n,n1);
	printf("\n The Second matrix you entered is \n");
	print(b,n,n1);
	
	c=(int *)calloc(n1*n1,sizeof(int));
	strassen(a,b,c,n1);
	printf("strassens matrix multiplication\n");
	print(c,n,n1);
	
return 0;
	
}
