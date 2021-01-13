#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE *fp;

int print_result()
{
	fp=fopen("/dev/alu","r");

	if(fp==NULL)
	{
		printf("Greska pri otvaranju");
		return -1;
	
	}
	int rezultat=0,carry=0;
	fscanf(fp,"%d , %d",&rezultat,&carry);
	fclose(fp);
	printf("Rezultat je %d,carry je %d\n",rezultat,carry);
	return 0;

}

int operacija(char regx,char regy,char op)
{
	char buff[30];
	fp=fopen("/dev/alu","w");
	sprintf(buff,"reg%c %c reg%c",regx,op,regy);
	fputs(buff,fp);
	fclose(fp);


}

int main()
{
	char buff[30];

	while(1)
	{
		printf("Unesite matematicku operaciju: ");
		scanf("%s",buff);
		if(!strcmp(buff,"exit"))
			return 0;
		int val[4];
		char op[3];

		int i;
		for(i=0;i<4;i++)
			val[i]=0;
		for(i=0;i<3;i++)
			op[i]=0;

		sscanf(buff,"%d%c%d%c%d%c%d",&val[0],&op[0],&val[1],&op[1],&val[2],&op[2],&val[3]);
		for(i=0;i<4;i++)
			printf("%d\n",val[i]);
		for(i=0;i<3;i++)
			printf("%c\n",op[i]);
		for(i=0;i<4;i++)
		{
			fp=fopen("/dev/alu","w");
			sprintf(buff,"reg%c=%x",'A'+i,val[i]);
			fputs(buff,fp);
			fclose(fp);
		
		}
		int op_count;
		if(op[0]!=0) op_count=1;
		if(op[1]!=0) op_count=2;
		if(op[2]!=0) op_count=3;

		if(op_count==1)
			operacija('A','B',op[0]);
		else 
			printf("vise od 1");
		print_result();
	
	
	}



}
