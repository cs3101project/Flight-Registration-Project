#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct{
    char id[10];
    int seats;
    char date[10];
    char source[20];
    char destination[20];
    char name[20];
}flight;

void flights(){
	int choice=0;
	flight fl;
	while(choice==0){
    printf("Enter 1 for add flight, 2 for delete flight, 3 for modify flight: ");
    scanf("%d",&choice);
    FILE *file;
	file = fopen("flights.txt","a"); 
	switch (choice){
		case 1: //add flights
			zero:
			printf("\nEnter the source of flight : ");
			scanf("%s",fl.source);
			printf("\nEnter the destination of flight : ");
			scanf("%s",fl.destination);
			printf("\nEnter the name of the flight : ");
			scanf("%s",fl.name);
			printf("Source : %s\nDestination:%s\nFlight name:%s\n",fl.source,fl.destination,fl.name);
			one:
			printf("\nEnter 1 to Confirm and 2 to Change: ");
			int flag=0;
			scanf("%d",&flag);
			switch(flag){
				case 1: break;
				case 2: goto zero;
				break;
				default:printf("Enter a valid option!"); goto one;
				break;	
			}
			int i=0;
			for(i=0;i<3;i++){
				fl.id[i]=fl.name[i];
			}
			char num[20];
			int ch1 = fl.source[0],ch2=fl.destination[0];
			int ch3 = ch1*100+ch2;
			itoa(ch3,num,10);
			strcat(fl.id,num);
			//printf("\n%s",fl.id);
			fwrite(&fl,sizeof(flight),1,file);
			

			
			
			break;
		case 2: // delete flights
			break;
		case 3: // modify flight
			break;
		default: choice = 0;
			break;
			printf("Invalid input!! PLease try again");
		}
	}
    

}
int main()
{
	flights();
	return 0;

}
