#include<stdio.h>

typedef struct flight{
	int num;
	char name[20];
	struct det{
		char sour[20];
		char dest[20];
		char time[20];
	} det;
	int seat;
	int fare;
}flight;

void newflight(){
	flight *f;
	FILE *fp;
	int n, i, j;
	printf("Enter the no. of flight to start service : ");
	scanf("%d",&n);
	
	f=(flight*)calloc(n, sizeof(flight));
	fp = fopen("allflights.txt","w");
	
	for(i=0;i<n;i++){
		f[i].seat=0;
		f[i].fare=0;
		printf("Enter Flight Number: ");
		scanf("%d",&f[i]);
		fflush(stdin);
		printf("Enter Flight Name: ");
		scanf("%[^\n]f",f[i].name);
		
		printf("Enter Source Airport :");
		scanf("%s",f[i].det.sour);
		
		printf("Enter Destination Airport :");
		scanf("%s",f[i].det.dest);
		
		printf("Enter seats : ");
		scanf("%d",&f[i].seat);
		
		printf("Enter fare : ");
		scanf("%d",&f[i].fare);
			
		fwrite(&f[i],sizeof(flight),1,fp);
	}
	fclose(fp);

}
void display(){
	flight f1;
	FILE *fp;
	fp = fopen("allflights.txt","r");
	while(fread(&f1,sizeof(flight),1,fp))
	{
		printf("\n%-5d  %-20s",f1.num,f1.name);
		printf("%-20s  %-20s",f1.det.sour,f1.det.dest);
		printf("%4d  %4d\n",f1.seat,f1.fare);
	}
	
	fclose(fp);
}
void addflight(){
	flight *f;
	FILE *fp;
	int n, i, j;
	printf("Enter the no. of flight to start service : ");
	scanf("%d",&n);
	
	f=(flight*)calloc(n, sizeof(flight));
	fp = fopen("allflights.txt","a+");
	
	for(i=0;i<n;i++){
		f[i].seat=0;
		f[i].fare=0;
		printf("Enter Flight Number: ");
		scanf("%d",&f[i]);
		fflush(stdin);
		printf("Enter Flight Name: ");
		scanf("%[^\n]f",f[i].name);
		
		printf("Enter Source Airport :");
		scanf("%s",f[i].det.sour);
		
		printf("Enter Destination Airport :");
		scanf("%s",f[i].det.dest);
		
		printf("Enter seats : ");
		scanf("%d",&f[i].seat);
		
		printf("Enter fare : ");
		scanf("%d",&f[i].fare);
			
		fwrite(&f[i],sizeof(flight),1,fp);
	}
	fclose(fp);

}

void noofflights(){
	flight f1;
	FILE *fp;
	fp = fopen("allflights.txt","r");
	fseek(fp,0,SEEK_END);
	int n=ftell(fp)/sizeof(flight);
	printf("\n\nNo of FLights = %d\n ",n);
	fclose(fp);
}

void search(){
	flight f1;
	FILE *fp;
	int num,found=0;
	char dest[20];
	fp = fopen("allflights.txt","r");
	printf("Enter Flight Number or dest to search : ");
	//scanf("%d",&num);
	scanf("%s",dest);
	while(fread(&f1,sizeof(flight),1,fp))
	{
	int flag=0,i=0;  // integer variables declaration  
    while(f1.det.dest[i]!='\0' &&dest[i]!='\0')  // while loop  
    {  
       if(f1.det.dest[i]!=dest[i])  
       {  
           flag=1;  
           break;  
       }  
       i++;  
    }    
		if(flag==0){
		found=1;
		printf("\n%-5d  %-20s",f1.num,f1.name);
		printf("%-20s  %-20s",f1.det.sour,f1.det.dest);
		printf("%4d  %4d\n",f1.seat,f1.fare);
	}
	}
	if(!found){
		printf("\nFlight NOT found\n");
	}
	fclose(fp);
	
}

int main(){
	int ch;
	do{
		printf("\n1.NEW FLIGHT");
		printf("\n2.DISPLAY");
		printf("\n3.ADD FLIGHT");
		printf("\n4.NO OF FLIGHTS");
		printf("\n5.SEARCH FLIGHTS");
		printf("\n0.EXIT");
		
		printf("\nEnter your choice : ");
		scanf("%d",&ch);
		
		switch(ch){
			case 1:
				newflight();
			break;
			case 2:
				display();
			break;
			case 3:
				addflight();
			break;
			case 4:
				noofflights();
			case 5:
				search();
			break;
		}
	}while(ch!=0);
	
	
	return 0;
}
