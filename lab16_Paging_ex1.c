#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main()
{
	int frame[16],len=0,i,t,j;
	char data[6][2]={{'r','x'},{'y','y'},{'z','z'},{'a','b'},{'e','f'},{'c','d'}};
	char memory[16][2];
	int flag;
	srand(time(NULL));
	for(i=0;i<16;i++)
		for(j=0;j<2;j++)
			memory[i][j]=' ';
	for(i=0;i<6;i++)
	{
		do
		{
			flag=0;
			t=(rand()%16);
			//printf("t:%d\n",t);
			for(j=0;j<i;j++)
				if(t==frame[j])
				{
					flag=1;
					break;
				}
		}while(flag);
		frame[i]=t;
	}
	/*for(i=0;i<6;i++)
		printf("%d ",frame[i]);*/

	printf("process1's page_table is:\n");
	printf("page     frame\n");
	for(i=0;i<3;i++)
	{
		printf("%d        %d\n",i,frame[i]);
	}
	printf("process1's logical memory is:\n");
	printf("page     data\n");
	for(i=0;i<3;i++)
	{
		printf("%d        %c%c\n",i,data[i][0],data[i][1]);
		memory[frame[i]][0]=data[i][0];
		memory[frame[i]][1]=data[i][1];
	}
	printf("process0's page_table is:\n");
        printf("page     frame\n");
        for(i=0;i<3;i++)
        {
                printf("%d        %d\n",i,frame[i+3]);
        }
        printf("process0's logical memory is:\n");
        printf("page     data\n");
        for(i=0;i<3;i++)
        {
                printf("%d        %c%c\n",i,data[i+3][0],data[i+3][1]);
		memory[frame[i+3]][0]=data[i+3][0];
                memory[frame[i+3]][1]=data[i+3][1];
        }
	printf("physical memory is:\n");
	printf("frame   offset   data\n");
	for(i=0;i<16;i++)
	{
		printf("%d      0        %c\n",i,memory[i][0]);
		printf("%d      1        %c\n",i,memory[i][1]);
	}
	printf("free frame is:\n");
	for(i=0;i<16;i++)
	{
		flag=1;
		for(j=0;j<6;j++)
			if(i==frame[j])
			{
				flag=0;
				break;
			}
		if(flag)
			printf("%d ",i);
	}

	printf("\n");

}
