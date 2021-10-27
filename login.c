// PRIYANGSHU DATTA 19MS033

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#ifdef _WIN32
    #include <conio.h>
#elif linux
    #include <unistd.h>
    #include <termio.h>
#endif

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
}customer;


int menu();
void login(int);
void user();
void userSignup();
void booking();
long int gen_ticket();
void check();

const char* getpasswd(){
    char *passwrd;
    char ch;
    #ifdef _WIN32
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
    #elif linux
        struct termios oldattr, newattr;
        tcgetattr( STDIN_FILENO, &oldattr );
        newattr = oldattr;
        newattr.c_lflag &= ~( ICANON | ECHO );
        tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
        gets(passwrd);
        tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
        return passwrd;
    #endif
}

int menu(){
    int choice;
    printf("\nChoose 1 for ADMIN, 2 for USER, 3 for exit: ");
    label:
    scanf("%d",&choice);
    switch(choice){
        case 1:
            login(1);
            break;
        case 2:
            user();
            break;
        case 3:
            exit(0);
            break;
        default:
            printf("Enter 1 for Administrative purposes, 2 for Booking or 3 for exit: ");
            goto label;
        break;
    }
    return 0;
}

void login(int x){
    person temp, *file;
    FILE *fp;
    int flag = 1;
    new:
    if (x){
        printf("\nWelcome to Administrative portal.");
        fp = fopen("admin.dat","r");
    }else{
        printf("\nWelcome to User portal. Enter 1 to book a flight, 2 for checking status of ticket: ");
        int f;
        scanf("%d",&f);
        switch(f){
            case 1:
                break;
            case 2:
                check();
                return;
                break;
            default:
                printf("Enter a valid option.\n");
                goto new;
                break;
        }
        fp = fopen("user.dat","r");
    }
    printf("\nEnter your username: ");
    scanf("%s",temp.uname);
    pass:
    if(!flag){
        printf("Please enter your password: ");
        strcpy(temp.pass,getpasswd());
        goto l3;
    }
    int logged = 1;
    file = (person *) malloc(sizeof(person));
    while(fread(file, sizeof(person), 1, fp)==1){
        if (strcmp(file->uname,temp.uname)==0){
            flag = 0;
            goto pass;
            l3:
            if(strcmp(file->pass,temp.pass)==0){
                if(x==1)
                    printf("\nAdmin");
                else
                    booking(file);
                logged = 0;
                break;
            }else{
                continue;
            }
        }
    }
    fclose(fp);
    if(x && logged){
            printf("\nYou are not a ADMIN!\n");
            menu();
    }else if(x==0 && logged){
        if(flag){
            printf("\nYou are not a registered user!"); 
            l1:
            printf("\nEnter 1 to register, 2 to try again, 3 to go to MAIN menu: ");
            int choice;
            scanf("%d",&choice);
            switch(choice){
                case 1:
                    userSignup();
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
            printf("\nTry again? Enter 1 to try again, 2 for siging as a different user, 3 to go to MAIN menu: ");
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

void user(){
    label:
    printf("\nAre you a registered user? Enter 1 for YES, 2 for NO, 3 to go back to main MENU: ");
    int choice;
    scanf("%d",&choice);
    switch (choice)
    {
    case 1:
        login(0);
        break;
    case 2:
        userSignup();
        break;
    case 3:
        menu();
        break;
    default:
        printf("Enter a valid option.");
        goto label;
        break;
    }
}

void userSignup(){
    person *temp= (person*) malloc(sizeof(person));
    printf("\nWelcome to registration portal.\n");
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
    FILE *fp;
    fp = fopen("user.dat", "r");
    while(fread(temp,sizeof(person),1,fp)==1){
        if (strcmp(uname,temp->uname)==0){
            printf("Username is taken, please try a different one.\n");
            goto un;
        }
    }
    fclose(fp);
    printf("Username is available. Enter 0 to create password or 1 to change the username: ");
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
    const char *pass = getpasswd();
    printf("\nEnter the password to confirm: ");
    const char *cpass = getpasswd();
    if (strcmp(pass,cpass)==0){
        person temp;
        strcpy(temp.uname,uname);
        strcpy(temp.name,name);
        strcpy(temp.pass,pass);
        fp = fopen("user.dat", "ab");
        fwrite(&temp, sizeof(temp), 1, fp);
        printf("\nAccount created successfully!");
        fclose(fp);
        user();
    }else{
        printf("\nPassword does not match!\n");
        goto pass;
    }
}

long int gen_ticket(char pname[]){
    time_t sec;
    long int ticket_id;
    int num=0;
    for(int i =0; i< strlen(pname); i++){
        num = num*10+pname[i];
        num = num/10;
    }
    // printf("%ld",num);
    time(&sec);
    ticket_id = sec+num; 
    printf("\n%ld\n",ticket_id);
    return ticket_id;
}

void booking(person *user){
    customer t;
    customer *tp;
    FILE *file;
    int newc=1;
    int ntemp; 
    l1:
    strcpy(t.name,user->name);
    file = fopen("booking.dat","r");
    while(fread(tp,sizeof(tp),1,file)==1){
        if (strcmp(tp->uname,user->uname)==0){
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
    strcpy(t.uname,user->uname);
    if (t.ntickets > 5){
        printf("\nCancel a ticket to book another!");
        return;
    }else{
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
            break;
        case 2:
            // flightInfo();
            printf("\nInformation regarding flights (search flights).");
            printf("Do you want to continue? Press enter to continue, carraige return to quit.\n");
            char ch;
            ch = getchar();
            switch(ch){
                case 13:
                    break;
                case 8:
                    menu();
                    break;
                default:
                    break;
            }
            break;
        case 3:
            menu();
            break;
        default:
            printf("Enter a valid option.");
            goto l1;
            break;
        }
        int booking = 1;
        int age;
        while(booking){
            ag:
            printf("Age of passenger: ");
            scanf("%d",&age);
            if(age < 3){
                c1:
                printf("The passenger is an infant. The fair is Rs. ______. Enter 1 to confirm, 2 to change age: ");
            }else if (age<=12 && age>=3){
                c2:
                printf("The passenger is an child. The fair is Rs. ______. Enter 1 to confirm, 2 to change age: ");
            }else if (age > 12){
                c3:
                printf("The passenger adult. The fair is Rs. ______. Enter 1 to confirm, 2 to change age: ");
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
}

void check(){
    label:
    printf("\nWelcome! \nTo see status of ticket enter 1, to return to user portal enter 2: ");
    int ch;
    scanf("%d",&ch);
    switch(ch){
        case 1:
            break;
        case 2:
            user();
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
            printf("\nPassenger: %s\nAge: %d\nBooked under: %s",temp.p_name,temp.p_age,temp.uname);
            goto label;
            return;
        }
    }
    printf("Invalid Ticket");
    goto label;
}

int main(){
    system("cls");
    menu();
    return 0;
}
