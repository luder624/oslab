#include<stdio.h>

void mySort()
{
	int arr[5]={15, 22, 41, 8, 35};
	int len=5;
	int i,j,min,temp;
	for(i=0;i<len-1;i++)
	{
		min=i;
		for(j=i+1;j<len;j++)
		{
			if(arr[j]<arr[min])
				min=j;
		}
		if(i!=min)
		{
			temp=arr[i];
			arr[i]=arr[min];
			arr[min]=temp;
		}
	}
	for(i=0;i<5;i++)
		printf("%d ",arr[i]);
	printf("\n");
}
