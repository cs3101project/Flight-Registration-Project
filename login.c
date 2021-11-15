// PRIYANGSHU DATTA 19MS033

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
    char uname[10];
    char name[20];
    char pass[10];
}person;

typedef struct{
    char name[20];
    char p_name[20];
    char uname[10];
    int p_age;
    int ntickets;
    long int ticket_id;
    char f_id[10];
    char f_dt[20];
    char f_mt[20];
    char f_yr[20];
    char b_time[20];
}customer;

typedef struct{
    char id[10];
    int seats;
    char time[10];
    char source[20];
    char destination[20];
    char name[20];
}flight;

int menu();
void login();
// void user(person*);
void flights();
void admin();
void search();
void signup(int);
void booking(person);
long int gen_ticket();
void check();
void cancel();
// void delete();

const char* getpass(){
    char *passwrd;
    char ch;
    int i;
    for(i = 0; i < 100; i++){
        ch = getch();
        if(ch == 13)
            break;
        if (ch == 8){
            i--;
            i--;
            continue;
        }
        passwrd[i] = ch;
    }
    passwrd[i] = '\0';
    return passwrd;
}

int menu(){
    int choice;
    printf("\nChoose 1 for LOGIN/REGISTER, 2 for CHECK TICKET STATUS, 3 for FLIGHT SEARCH, 4 for exit: ");
    label:
    scanf("%d",&choice);
    switch(choice){
        case 1:
            login();
            break;
        case 2:
            check();
            break;
        case 3:
            // search();
            break;        
        case 4:
            exit(0);
            break;
        default:
            printf("Enter 1 for LOGIN, 2 for CHECK TICKET STATUS, 3 for FLIGHT SEARCH, 4 for exit: ");
            goto label;
        break;
    }
    return 0;
}

void login(){
    person temp, file;
    FILE *fp;
    int x, logged = 0;
    login:
    printf("\nEnter 1 for ADMIN, 2 for USER, 3 for main MENU: ");
    int flag;
    scanf("%d",&flag);
    switch(flag){
        case 1:
            x=1;
            break;
        case 2:
            label:
            printf("\nAre you a registered user? Enter 1 for YES, 2 for NO, 3 to go back to main MENU: ");
            int choice;
            scanf("%d",&choice);
            switch (choice){
            case 1:
            x=0;
                break;
            case 2:
                signup(0);
                break;
            case 3:
                menu();
                break;
            default:
                printf("Enter a valid option.");
                goto label;
                break;
            }
            break;
        case 3:
            menu();
            break;
        default:
            printf("Enter a valid option.");
            goto login;
            break;
    }
    flag = 1;
    new:
    if (x==1){
        printf("\nWelcome to Administrative portal.");
        fp = fopen("admin.dat","r");
    }else{
        printf("\nWelcome to User portal.");
        fp = fopen("user.dat","r");
    }
    printf("\nEnter your username: ");
    scanf("%s",temp.uname);
    pass:
    if(!flag){
        printf("Please enter your password: ");
        strcpy(temp.pass,getpass());
        goto l3;
    }
    // file = (person *) malloc(sizeof(person));
    while(fread(&file, sizeof(person), 1, fp)==1){
        if (strcmp(file.uname,temp.uname)==0){
            flag = 0;
            goto pass;
            l3:
            if(strcmp(file.pass,temp.pass)==0){
                if(x==1){
                    admin();
                    return;
                }else{
                    printf("\nEnter 1 for ticket booking, 2 for ticket cancellation: ");
                    scanf("%d",&flag);
                    if(flag == 1){
                        booking(file);
                    }else{
                        cancel();
                    }
                }
                logged = 1;
                break;
            }else{
                continue;
            }
        }
    }
    fclose(fp);
    
    if(x && logged==0){
            printf("\nYou are not a ADMIN!\n");
            menu();
    }else if(x==0 && logged==0){
        if(flag){
            printf("\nYou are not a registered user!"); 
            l1:
            printf("\nEnter 1 to register, 2 to try again, 3 to go to MAIN menu: ");
            int choice;
            scanf("%d",&choice);
            switch(choice){
                case 1:
                    signup(0);
                    break;
                case 2:
                    goto new;
                    break;
                case 3:
                    menu();
                    break;
                default:
                    printf("Enter a valid option.");
                    goto l1;
                    break;
            }
        }else{
            printf("\nIncorrect Password!"); 
            l2:
            printf("\nEnter 1 to try again, 2 for siging as a different user, 3 to go to MAIN menu: ");
            int choice;
            scanf("%d",&choice);
            switch(choice){
                case 1:
                    goto pass;
                    break;
                case 2:
                    goto new;
                    break;
                case 3:
                    menu();
                    break;
                default:
                    goto l2;
            }
        }
    }
}

void user(person user){
    w:
    printf("\nEnter 0 for booking, 1 for cancellation: ");
    int bol;
    scanf("%d",&bol);
    if (!bol){

        // booking(user);
        // return;
    }else if (bol) {
        // cancel();
        // return;
    } else{
        printf("Enter a valid option.");
        goto w;
    }
}

void signup(int x){
    person *temp= (person*) malloc(sizeof(person));
    FILE *fp;
    if (x==1){
        printf("Welcome to new admin registration portal.\n");
        fp = fopen("admin.dat", "r");
    }else{
        printf("\nWelcome to new user registration portal.\n");
        fp = fopen("user.dat", "r");
    }
    int bool=1;
    char name[20];
    while(bool){
        gets(name);
        printf("Please enter your Full Name: ");
        gets(name);
        printf("Enter 0 to proceed, 1 to change name (current: %s): ",name);
        scanf("%d",&bool);
    }
    un:
    printf("%s, please enter a username (It will be used to log you in to book flights.): ",name);
    char uname[10];
    scanf("%s",uname);
    while(fread(temp,sizeof(person),1,fp)==1){
        if (strcmp(uname,temp->uname)==0){
            printf("Username is taken, please try a different one.\n");
            goto un;
        }
    }
    fclose(fp);
    printf("Username is available. Enter 0 to create password or 1 to change the username (current: %s): ",uname);
    int choice;
    scanf("%d",&choice);
    switch(choice){
        case 1:
            goto un;
            break;
        case 0:
            break;
        default:
            break;
    }
    pass:
    printf("Enter a strong password: ");
    const char *pass = getpass();
    printf("\nEnter the password to confirm: ");
    const char *cpass = getpass();
    if (strcmp(pass,cpass)==0){
        person temp;
        strcpy(temp.uname,uname);
        strcpy(temp.name,name);
        strcpy(temp.pass,pass);
        if (x){
            fp = fopen("admin.dat", "ab");
        }else{
            fp = fopen("user.dat", "ab");
        }
        fwrite(&temp, sizeof(temp), 1, fp);
        printf("\nAccount created successfully!");
        fclose(fp);
        login();
    }else{
        printf("\nPassword does not match!\n");
        goto pass;
    }
}

long int gen_ticket(char pname[]){
    time_t sec;
    long int ticket_id;
    int num=0, i;
    for(i =0; i< strlen(pname); i++){
        num = num*10+pname[i];
        num = num/10;
    }
    time(&sec);
    ticket_id = sec+num; 
    // printf("\n%ld\n",ticket_id);
    return ticket_id;
}

void booking(person user){
    customer t;
    customer *tp;
    FILE *file;
    int newc=1;
    int ntemp; 
    const char * months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    int flag=1;
    int d,m,y;
    char dt[3], yr[6], f_id[10];
    flight fl;
    FILE *flight;
    int count=0;
    l1:
    strcpy(t.name,user.name);
    file = fopen("booking.dat","r");
    while(fread(tp,sizeof(tp),1,file)==1){
        if (strcmp(tp->uname,user.uname)==0){
            ntemp = tp->ntickets+1;
            printf("Welcome back, %s",t.name);
            newc=0;
            break;
        }
    }
    fclose(file);
    if (newc){
        t.ntickets = 1;
        ntemp = t.ntickets;
        printf("\nWelcome %s, to e-Booking portal.",t.name);
    }
    strcpy(t.uname,user.uname);
    int knw;
    printf("\nBooking ticket for self? Enter 1 for YES, 2 for NO: ");
    scanf("%d",&knw);
    if (knw == 1){
        char name[20];
        strcpy(name,t.name);
        strcpy(t.p_name,name);
    }else if(knw == 2){
        printf("Enter the name of the passenger: ");
        char pname[20];
        gets(pname);
        gets(pname);
        strcpy(t.p_name,pname);
    }else
        goto l1;
    printf("Passenger: %s.\nDo you know the flight ID you want to board? Enter 1 for YES, 2 for NO, 3 to Logout: ",t.p_name);
    scanf("%d",&knw);
    switch (knw){
    case 1:
        fid:
        printf("Enter the flight ID: ");
        scanf("%s",f_id);
        flight = fopen("flight.txt","r");
        while(fread(&fl,sizeof(fl),1,flight)==1){
            if (fl.id == f_id){
                count = 1;
                break;
            }
        }
        if (count){
            printf("Invalid flight ID.");
            goto fid;
        }
        strcpy(t.f_id,f_id);
        while (flag){
            printf("\nNow please enter date of travel.");
            printf("\nEnter date: ");
            scanf("%d", &d);
            printf("Enter month: ");
            scanf("%d", &m);
            printf("Enter year: ");
            scanf("%d", &y);
            printf("\nYour prefered choice of travel date is %d %s %d. Enter 0 to confirm, 1 to change date: ", d,months[m-1],y);
            scanf("%d",&flag);
        }
        itoa(d,dt,10);
        itoa(y,yr,10);
        strcpy(t.f_dt,dt);
        strcpy(t.f_mt,months[m-1]);
        strcpy(t.f_yr,yr);
        break;
    case 2:
        // flightInfo();
        printf("\nInformation regarding flights (search flights).");
        printf("Do you want to continue? Press enter to continue, carraige return to quit.\n");
        char ch;
        ch = getch();
        switch(ch){
            case 13:
                break;
            case 8:
                menu();
                return;
                break;
            default:
                break;
        }
        break;
    case 3:
        menu();
        return;
        break;
    default:
        printf("Enter a valid option.");
        goto l1;
        break;
    }
    int booking = 1;
    int age;
    while(booking){
        int basefare=1000;
        ag:
        printf("Age of passenger: ");
        scanf("%d",&age);
        if(age < 3){
        	basefare*1;
            c1:
            printf("The passenger is an infant. The fair is Rs. %d. Enter 1 to confirm, 2 to change age: ",basefare);
        }else if (age<=12 && age>=3){
            c2:
            printf("The passenger is an child. The fair is Rs. %d. Enter 1 to confirm, 2 to change age: ",basefare*2);
        }else if (age > 12){
            c3:
            printf("The passenger adult. The fair is Rs. %d. Enter 1 to confirm, 2 to change age: ",basefare*3);
        } else {
            printf("Enter a valid age.\n");
            goto ag;
        }
        t.p_age = age;
        FILE *fp;
        fp = fopen("booking.dat","ab");
        int d;
        scanf("%d",&knw);
        switch(knw){
            case 1:
                t.ntickets++;
                t.ticket_id;
                t.ticket_id = gen_ticket(t.p_name);
                time_t curtime;
                time(&curtime);
                strcpy(t.b_time,ctime(&curtime));
                fwrite(&t,sizeof(customer),1,fp);
                printf("Successfully booked! The ticket id is: %ld",t.ticket_id);
                booking = 0;
                fclose(fp);
                l2:
                printf("\nWant to purchase another ticket? Enter 1 for YES, 2 to go to MAIN menu: ");
                scanf("%d",&d);
                switch(d){
                    case 1:
                        goto l1;
                        break;
                    case 2:
                        menu();
                        break;
                    default:
                        printf("Enter a valid option.\n");
                        goto l2;
                        break;
                }
                break;
            case 2:
                goto ag;
                break;
            default:
                printf("Enter a valid option.\n");
                if (age < 5){
                    goto c1;
                } else if (age >=5 && age <=18){
                    goto c2;
                }else{
                    goto c3;
                }
                break;
        }
    }
}

void check(){
    printf("\nWelcome!");
    int ch;
    label:
    printf("\nTo see status of ticket enter 1, to return to user portal enter 2: ");
    scanf("%d",&ch);
    switch(ch){
        case 1:
            break;
        case 2:
            login();
            break;
        default:
            printf("Enter a valid option.\n");
            goto label;
            break;
    }
    printf("Enter the ticket id: ");
    long int ticket;
    scanf("%ld",&ticket);
    customer temp;
    FILE *fp;
    fp = fopen("booking.dat","r");
    while(fread(&temp,sizeof(customer),1,fp)==1){
        if (temp.ticket_id == ticket){
            printf("Ticket found.");
            printf("\nPassenger: %s\nFlight Date: %s %s %s\nFlight ID: %s\nAge: %d\nBooked under: %s\nDate of Booking: %s",temp.p_name,temp.f_dt,temp.f_mt,temp.f_yr,temp.f_id,temp.p_age,temp.uname,temp.b_time);
            goto label;
            return;
        }
    }
    printf("Invalid Ticket");
    goto label;
}

void admin(){
    options:
    printf("\nEnter 1 for admin creation, 2 for flight modification, 3 for user modification, 4 to return to main menu: ");
    int choice;
    scanf("%d",&choice);
    switch(choice){
        case 1:
            signup(1);
            break;
        case 2:
            flights();
            break;
        case 3:
            // user_deletion();
            break;
        case 4:
            menu();
            break;
        default:
            printf("Enter a VALID option.");
            goto options;
    }
}

void flights(){
	int choice=0;
    char id[10];
	flight fl,temp;
	while(choice==0){
    printf("Enter 1 for add flight, 2 for delete flight, 3 for modify flight: ");
    scanf("%d",&choice);
    FILE *file;
	file = fopen("flights.dat","a+"); 
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
            while(fread(&temp,sizeof(flight),1,file)==1){
                if (strcmp(fl.id,temp.id)==0){
                    printf("Error! Flight with same ID exists.");
                    goto zero;
                    break;
                }
            }
			printf("\nEnter flight time : ");
			int h,m; char th[10],tm[10];
            printf("\nEnter hours: ");
            scanf("%d", &h);
            printf("Enter minutes: ");
            scanf("%d", &m);
            itoa(h,th,10);
            itoa(m,tm,10);
            strcat(th,":"); strcat(th,tm);
        	for(i=0;i<strlen(th);i++){
        		fl.time[i]=th[i];
			}
        	//printf("%s",fl.time);
			fl.seats = 5;
            printf("\nid = %s",fl.id);
			printf("\nseats = %d",fl.seats);
			printf("\ntime = %s",fl.time);
			printf("\nsource = %s",fl.source);
			printf("\ndestination = %s",fl.destination);
			printf("\nname = %s",fl.name);
			//printf("\n%s",fl.id);
			fwrite(&fl,sizeof(flight),1,file);
			// fclose(file);
			break;
		case 2: // delete flights
			break;
		case 3: // modify flight
            scanf("%d",id);
            while(fread(&fl,sizeof(flight),1,file)==1){
                if (strcmp(fl.id,id)==0){
                    printf("Flight Details.\n");
                    printf("\nid: %s",fl.id);
                    printf("\nseats: %d",fl.seats);
                    printf("\ntime: %s",fl.time);
                    printf("\nsource: %s",fl.source);
                    printf("\ndestination: %s",fl.destination);
                    printf("\nname: %s",fl.name);
                }else{
                    printf("Error");
                }
            }
           break;
		}
        fclose(file);
	}
    

}

// void search();

void cancel(){
    // printf("\nWelcome to cancellation department!");
    // int ch;
    // label:
    // printf("\nTo cancel booked tickets enter 1, to return to user portal enter 2: ");
    // scanf("%d",&ch);
    // switch(ch){
    //     case 1:
    //         break;
    //     case 2:
    //         menu();
    //         break;
    //     default:
    //         printf("Enter a valid option.\n");
    //         goto label;
    //         break;
    // }
    // customer *temp = (customer*) malloc (sizeof(customer));
    // FILE *fp1,*fp2;
    // long int t_id;
    // printf("Enter ticket id to cancel: ");
    // scanf("%d",&t_id);
    // fp1=fopen("booking.dat","r");
    // fp2=fopen("copy.dat","ab");
    // if(fp1==NULL){
    //     fprintf(stderr,"can't open file");
    //     exit(0);
    // }
    // int c=0,t=0;
    // while(fread(temp,sizeof(temp),1,fp1)==1){   
    //     t++;
    //     printf("%ld\n",temp->ticket_id);
    //     if(temp->ticket_id==t_id){
    //     }else{
    //         c++;
    //         fwrite(&temp,sizeof(customer),1,fp2);
    //     }
    // }
    // printf("\ntotal%d\ncount%d",t,c);
    // fclose(fp1);
    // fclose(fp2);
    // if (remove("booking.dat")==0){
    //     if (rename("copy.dat","booking.dat")==0){
    //         printf("Ticket Cancelled successfully. Want to cancel another ticket?");
    //         goto label;
    //     }
    // }else{
    //     printf("Error");
    // }
    printf("\nWelcome!");
    int ch;
    label:
    printf("\nTo cancel booked tickets enter 1, to return to user portal enter 2: ");
    scanf("%d",&ch);
    switch(ch){
        case 1:
            break;
        case 2:
            login();
            break;
        default:
            printf("Enter a valid option.\n");
            goto label;
            break;
    }
    customer t;
    FILE *fp1,*fp2;
    int ticket_id,found = 0;
    fp1 = fopen("booking.dat","r");
    fp2 = fopen("temp.dat","a+");
    printf("ticket id to delete: ");
    scanf("%d",&ticket_id);
    while(fread(&t,sizeof(customer),1,fp1))
    {
    	if(t.ticket_id==ticket_id){
    		found = 1;
		}
		else
		    fwrite(&t,sizeof(flight),1,fp2);
    }
    fclose(fp1);
    fclose(fp2);
    if (found){
    	fp2 = fopen("temp.dat","r");
    	fp1= fopen("booking.dat","w");
    	while(fread(&t,sizeof(flight),1,fp2)){
    		fwrite(&t,sizeof(flight),1,fp1);
		}
		fclose(fp1);
		fclose(fp2);
        printf("Ticket cancelled successfully! Want to cancell another?")
        goto label;
	} 
    else
	    printf("Ticket ID invalid or ticket not found!");
}

int main(){
    system("cls");
    menu();
    return 0;
}
