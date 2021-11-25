// PRIYANGSHU DATTA 19MS033

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
    char uname[10];
    char name[20];
    char pass[10];
} person;

typedef struct
{
    char name[20];
    char p_name[20];
    char uname[10];
    int p_age;
    int ntickets;
    char fare[5];
    long int ticket_id;
    char f_id[10];
    char f_dt[20];
    char f_mt[20];
    char f_yr[20];
    char b_time[20];
} customer;

typedef struct
{
    char id[10];
    int seats;
    char time[10];
    char source[20];
    char destination[20];
    char name[20];
    int fare;
} flight;

void menu();
void login();
void flights();
void admin();
void search();
void signup(int);
void booking(person);
long int gen_ticket();
void check();
void cancel(person);
// 033
const char *getpass()
{
    char *passwrd = (char *)malloc(sizeof(char) * 20);
    char ch;
    int i;
    for (i = 0; i < 100; i++)
    {
        ch = getch();
        if (ch == 13)
            break;
        if (ch == 8)
        {
            i--;
            i--;
            continue;
        }
        passwrd[i] = ch;
    }
    passwrd[i] = '\0';
    return passwrd;
}

void menu()
{
    int choice;
    printf("\nChoose 1 for LOGIN/REGISTER, 2 for CHECK TICKET STATUS, 3 for FLIGHT SEARCH, 4 for exit: ");
label:
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        login();
        return;
        break;
    case 2:
        check();
        return;
        break;
    case 3:
        search();
        menu();
        return;
        break;
    case 4:
        exit(0);
        break;
    default:
        printf("Enter 1 for LOGIN, 2 for CHECK TICKET STATUS, 3 for FLIGHT SEARCH, 4 for exit: ");
        goto label;
        break;
    }
    return;
}
// 033
void login()
{
    person temp, file;
    FILE *fp;
    int x, logged = 0;
login:
    printf("\nEnter 1 for ADMIN, 2 for USER, 3 for main MENU: ");
    int flag;
    scanf("%d", &flag);
    switch (flag)
    {
    case 1:
        x = 1;
        break;
    case 2:
    label:
        printf("\nAre you a registered user? Enter 1 for YES, 2 for NO, 3 to go back to main MENU: ");
        int choice;
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            x = 0;
            break;
        case 2:
            signup(0);
            return;
            break;
        case 3:
            menu();
            return;
            break;
        default:
            printf("Enter a valid option.");
            goto label;
            break;
        }
        break;
    case 3:
        menu();
        return;
        break;
    default:
        printf("Enter a valid option.");
        goto login;
        break;
    }
    flag = 1;
    new : if (x == 1)
    {
        printf("\nWelcome to Administrative portal.");
        fp = fopen("admin.dat", "r");
    }
    else
    {
        printf("\nWelcome to User portal.");
        fp = fopen("user.dat", "r");
    }
    printf("\nEnter your username: ");
    scanf("%s", temp.uname);
pass:
    if (!flag)
    {
        printf("Please enter your password: ");
        strcpy(temp.pass, getpass());
        goto l3;
    }
    // file = (person *) malloc(sizeof(person));
    while (fread(&file, sizeof(person), 1, fp) == 1)
    {
        if (strcmp(file.uname, temp.uname) == 0)
        {
            flag = 0;
            goto pass;
        l3:
            if (strcmp(file.pass, temp.pass) == 0)
            {
                if (x == 1)
                {
                    admin();
                    return;
                }
                else
                {
                    printf("\nEnter 1 for ticket booking, 2 for ticket cancellation: ");
                    scanf("%d", &flag);
                    if (flag == 1)
                    {
                        booking(file);
                        return;
                    }
                    else
                    {
                        cancel(file);
                        return;
                    }
                }
                logged = 1;
                break;
            }
            else
            {
                continue;
            }
        }
    }
    fclose(fp);

    if (x && logged == 0)
    {
        printf("\nYou are not a ADMIN!\n");
        menu();
        return;
    }
    else if (x == 0 && logged == 0)
    {
        if (flag)
        {
            printf("\nYou are not a registered user!");
        l1:
            printf("\nEnter 1 to register, 2 to try again, 3 to go to MAIN menu: ");
            int choice;
            scanf("%d", &choice);
            switch (choice)
            {
            case 1:
                signup(0);
                return;
                break;
            case 2:
                goto new;
                break;
            case 3:
                menu();
                return;
                break;
            default:
                printf("Enter a Valid option.");
                goto l1;
                break;
            }
        }
        else
        {
            printf("\nIncorrect Password!");
        l2:
            printf("\nEnter 1 to try again, 2 for siging as a different user, 3 to go to MAIN menu: ");
            int choice;
            scanf("%d", &choice);
            switch (choice)
            {
            case 1:
                goto pass;
                break;
            case 2:
                goto new;
                break;
            case 3:
                menu();
                return;
                break;
            default:
                goto l2;
            }
        }
    }
}
// 156
void signup(int x)
{
    person *temp = (person *)malloc(sizeof(person));
    FILE *fp;
    if (x == 1)
    {
        printf("Welcome to new admin registration portal.\n");
        fp = fopen("admin.dat", "r");
    }
    else
    {
        printf("\nWelcome to new user registration portal.\n");
        fp = fopen("user.dat", "r");
    }
    int bool = 1;
    char name[20];
    while (bool)
    {
        gets(name);
        printf("Please enter your Full Name: ");
        gets(name);
        printf("Enter 0 to proceed, 1 to change name (current: %s): ", name);
        scanf("%d", &bool);
    }
un:
    printf("%s, please enter a username (It will be used to log you in to book flights.): ", name);
    char uname[10];
    scanf("%s", uname);
    while (fread(temp, sizeof(person), 1, fp) == 1)
    {
        if (strcmp(uname, temp->uname) == 0)
        {
            printf("Username is taken, please try a different one.\n");
            goto un;
        }
    }
    fclose(fp);
    printf("Username is available. Enter 0 to create password or 1 to change the username (current: %s): ", uname);
    int choice;
    scanf("%d", &choice);
    switch (choice)
    {
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
    if (strcmp(pass, cpass) == 0)
    {
        person temp;
        strcpy(temp.uname, uname);
        strcpy(temp.name, name);
        strcpy(temp.pass, pass);
        if (x)
        {
            fp = fopen("admin.dat", "ab");
        }
        else
        {
            fp = fopen("user.dat", "ab");
        }
        fwrite(&temp, sizeof(temp), 1, fp);
        printf("\nAccount created successfully!");
        fclose(fp);
        login();
    }
    else
    {
        printf("\nPassword does not match!\n");
        goto pass;
    }
}
// 033
long int gen_ticket(char pname[])
{
    time_t sec;
    long int ticket_id;
    int num = 0, i;
    for (i = 0; i < strlen(pname); i++)
    {
        num = num * 10 + pname[i];
        num = num / 10;
    }
    time(&sec);
    ticket_id = sec + num;
    // printf("\n%ld\n",ticket_id);
    return ticket_id;
}
// 033
void booking(person user)
{
    customer t;
    customer *tp;
    FILE *file;
    int newc = 1;
    int ntemp;
    const char *months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    int flag = 1;
    int d, m, y;
    char dt[3], yr[6], f_id[10];
    flight fl, tempo;
    FILE *flight;
    int count = 1;
l1:
    strcpy(t.name, user.name);
    file = fopen("booking.dat", "rb");
    while (fread(tp, sizeof(tp), 1, file) == 1)
    {
        if (strcmp(tp->uname, user.uname) == 0)
        {
            ntemp = tp->ntickets + 1;
            printf("Welcome back, %s", t.name);
            newc = 0;
            break;
        }
    }
    fclose(file);
    if (newc)
    {
        t.ntickets = 1;
        ntemp = t.ntickets;
        printf("\nWelcome %s, to e-Booking portal.", t.name);
    }
    strcpy(t.uname, user.uname);
    int knw;
    printf("\nBooking ticket for self? Enter 1 for YES, 2 for NO: ");
    scanf("%d", &knw);
    if (knw == 1)
    {
        char name[20];
        strcpy(name, t.name);
        strcpy(t.p_name, name);
    }
    else if (knw == 2)
    {
        printf("Enter the name of the passenger: ");
        char pname[20];
        gets(pname);
        gets(pname);
        strcpy(t.p_name, pname);
    }
    else
        goto l1;
fid:
    printf("Passenger: %s.\nDo you know the flight ID you want to board? Enter 1 for YES, 2 for NO, 3 to Logout: ", t.p_name);
    scanf("%d", &knw);
    switch (knw)
    {
    case 1:
        printf("Enter the flight ID: ");
        scanf("%s", f_id);
        flight = fopen("flights.dat", "rb");
        while (fread(&fl, sizeof(fl), 1, flight) == 1)
        {
            if ((strcmp(fl.id, f_id) == 0) && (fl.seats > 0))
            {
                count = 0;
                break;
            }
        }
        if (count)
        {
            printf("Invalid flight ID or No seats available.\n");
            goto fid;
        }
        strcpy(t.f_id, f_id);
        while (flag)
        {
            printf("\nNow please enter date of travel.");
            printf("\nEnter date: ");
            scanf("%d", &d);
            printf("Enter month: ");
            scanf("%d", &m);
            printf("Enter year: ");
            scanf("%d", &y);
            printf("\nYour prefered choice of travel date is %d %s %d. Enter 0 to confirm, 1 to change date: ", d, months[m - 1], y);
            scanf("%d", &flag);
        }
        itoa(d, dt, 10);
        itoa(y, yr, 10);
        strcpy(t.f_dt, dt);
        strcpy(t.f_mt, months[m - 1]);
        strcpy(t.f_yr, yr);
        break;
    case 2:
        search();
        // printf("\nInformation regarding flights (search flights).");
        printf("Do you want to continue? Press enter to continue, carraige return to quit.\n");
        char ch;
        ch = getch();
        switch (ch)
        {
        case 13:
            goto fid;
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
    int age, ch1;
    while (booking)
    {
        int basefare = fl.fare;
    ag:
        printf("Age of passenger: ");
        scanf("%d", &age);
        if (age < 3)
        {
        c1:
            sprintf(t.fare, "%d", basefare);
            // t.fare = basefare;
            printf("The passenger is an infant. The fair is Rs. %s. Enter 1 to confirm, 2 to change age: ", t.fare);
        }
        else if (age <= 12 && age >= 3)
        {
        c2:
            sprintf(t.fare, "%d", basefare * 2);
            // t.fare = basefare*2;
            printf("The passenger is an child. The fair is Rs. %s. Enter 1 to confirm, 2 to change age: ", t.fare);
        }
        else if (age > 12)
        {
        c3:
            sprintf(t.fare, "%d", basefare * 3);
            // t.fare = basefare*3;
            printf("The passenger adult. The fair is Rs. %s. Enter 1 to confirm, 2 to change age: ", t.fare);
        }
        else
        {
            printf("Enter a valid age.\n");
            goto ag;
        }
        t.p_age = age;
        FILE *fp;
        fp = fopen("booking.dat", "ab");
        int d;
        scanf("%d", &knw);
        switch (knw)
        {
        case 1:
            t.ntickets++;
            t.ticket_id;
            t.ticket_id = gen_ticket(t.p_name);
            time_t curtime;
            time(&curtime);
            // printf("%d",t.fare);
            fl.seats--;
            FILE *fli;
            fli = fopen("temp.dat", "wb");
            fclose(flight);
            flight = fopen("flights.dat", "r");
            while (fread(&tempo, sizeof(tempo), 1, flight) == 1)
            {
                if (strcmp(tempo.id, fl.id) == 0)
                {
                    tempo.seats = tempo.seats - 1;
                }
                fwrite(&tempo, sizeof(tempo), 1, fli);
            }
            fclose(flight);
            fclose(fli);
            remove("flights.dat");
            rename("temp.dat", "flights.dat");
            strcpy(t.b_time, ctime(&curtime));
            fwrite(&t, sizeof(customer), 1, fp);
            printf("Successfully booked! The ticket id is: %ld", t.ticket_id);
            booking = 0;
            fclose(fp);
        l2:
            printf("\nWant to purchase another ticket? Enter 1 for YES, 2 to go to MAIN menu: ");
            scanf("%d", &d);
            switch (d)
            {
            case 1:
                goto l1;
                break;
            case 2:
                menu();
                // return;
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
            if (age < 5)
            {
                goto c1;
            }
            else if (age >= 5 && age <= 18)
            {
                goto c2;
            }
            else
            {
                goto c3;
            }
            break;
        }
    }
}
// 156
void check()
{
    printf("\nWelcome to Ticket status portal!");
    int ch;
label:
    printf("\nTo see status of ticket enter 1, to return to LOGIN portal enter 2: ");
    scanf("%d", &ch);
    switch (ch)
    {
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
    scanf("%ld", &ticket);
    customer temp;
    FILE *fp;
    fp = fopen("booking.dat", "r");
    while (fread(&temp, sizeof(customer), 1, fp) == 1)
    {
        if (temp.ticket_id == ticket)
        {
            printf("Ticket found.");
            printf("\nPassenger: %s\nFlight Date: %s %s %s\nFlight ID: %s\nAge: %d\nBooked under: %s\nFare: %s\nDate of Booking: %s", temp.p_name, temp.f_dt, temp.f_mt, temp.f_yr, temp.f_id, temp.p_age, temp.uname, temp.fare, temp.b_time);
            goto label;
            return;
        }
    }
    printf("Invalid Ticket or Ticket not Found!");
    goto label;
}
// 159
void admin()
{
options:
    printf("\nEnter 1 for admin creation, 2 for flight modification, 3 to return to main menu: ");
    int choice;
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
        signup(1);
        break;
    case 2:
        flights();
        break;
    case 3:
        menu();
        break;
    default:
        printf("Enter a VALID option.");
        goto options;
    }
}
// 159
void flights()
{
    int choice = 0;
    char id[10], mod[10], num[20];
    int p[7];
    int flag, ch, ch1, ch2, ch3, h, m, i, j;
    char th[10], tm[10];
    FILE *file, *t;
    flight fl, temp, modif;
    int count = 0, total = 0;
    while (choice == 0)
    {
    menu:
        printf("Enter 0 for viewing flights, 1 for add flight, 2 for delete flight, 3 for modify flight, 4 for login menu: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 0:
            file = fopen("flights.dat", "rb");
            while (fread(&modif, sizeof(modif), 1, file) == 1)
            {
                printf("%-5s  %-20s", modif.id, modif.name);
                printf("%-20s  %-20s", modif.source, modif.destination);
                printf("%4d  %4d\n", modif.seats, modif.fare);
                ++count;
            }
            if (!count)
            {
                printf("\nNo flights are added!\n");
            }
            count = 0;
            fclose(file);
            break;
        case 1: //add flights
        zero:
            getchar();
            printf("Enter the source of flight : ");
            scanf("%s", fl.source);
            printf("Enter the destination of flight : ");
            scanf("%s", fl.destination);
            printf("Enter the name of the flight : ");
            fflush(stdin);
            scanf("%[^\n]f", fl.name);
            printf("Source : %s\nDestination:%s\nFlight name:%s\n", fl.source, fl.destination, fl.name);
        one:
            printf("Enter 1 to Confirm and 2 to Change: ");
            flag = 0;
            scanf("%d", &flag);
            switch (flag)
            {
            case 1:
                break;
            case 2:
                goto zero;
                break;
            default:
                printf("Enter a valid option!");
                goto one;
                break;
            }
            for (i = 0; i < 3; i++)
            {
                fl.id[i] = fl.name[i];
            }
            fl.id[3] = '\0';
            ch1 = fl.source[0], ch2 = fl.destination[0];
            ch3 = ch1 * 100 + ch2;
            sprintf(num, "%d", ch3);
            file = fopen("flights.dat", "a+b");
            strcat(fl.id, num);
            while (fread(&temp, sizeof(flight), 1, file) == 1)
            {
                if (strcmp(fl.id, temp.id) == 0)
                {
                    printf("Error! Flight with same ID exists.\n");
                    goto zero;
                    break;
                }
            }
            printf("\nEnter flight time.");
            printf("\nEnter hours: ");
            scanf("%d", &h);
            printf("Enter minutes: ");
            scanf("%d", &m);
            itoa(h, th, 10);
            itoa(m, tm, 10);
            strcat(th, ":");
            strcat(th, tm);
            for (i = 0; i < strlen(th); i++)
            {
                fl.time[i] = th[i];
            }
            printf("Enter maximum number of seats: ");
            scanf("%d", &fl.seats);
            printf("Enter fare for the flight: ");
            scanf("%d", &fl.fare);
            fwrite(&fl, sizeof(flight), 1, file);
            printf("Flight with ID: %s, is added.", fl.id);
            fclose(file);
            break;
        case 2: // delete flights
        label:
            file = fopen("flights.dat", "rb");
            while (fread(&modif, sizeof(modif), 1, file) == 1)
            {
                printf("%-5s  %-20s", modif.id, modif.name);
                printf("%-20s  %-20s", modif.source, modif.destination);
                printf("%4d  %4d", modif.seats, modif.fare);
                ++count;
            }
            fclose(file);
            if (!count)
            {
                printf("\nNo flights are available to remove!\n");
                menu();
            }
            count = 0;
            printf("\nTo remove flights enter 1, to return in main menu enter 2: ");
            scanf("%d", &ch);
            switch (ch)
            {
            case 1:
                break;
            case 2:
                menu();
                return;
                break;
            default:
                printf("Enter a valid option.\n");
                goto label;
                break;
            }
            FILE *fp1, *fp2;
            int found = 0;
            char f_id[10];
            fp1 = fopen("flights.dat", "rb");
            fp2 = fopen("temp.dat", "ab");
            printf("Enter flight id to remove: ");
            scanf("%s", f_id);
            while (fread(&modif, sizeof(modif), 1, fp1))
            {
                if (strcmp(modif.id, f_id) == 0)
                    found = 1;
                else
                    fwrite(&modif, sizeof(modif), 1, fp2);
            }
            fclose(fp1);
            fclose(fp2);
            if (found)
            {
                fp2 = fopen("temp.dat", "r");
                fp1 = fopen("flights.dat", "wb");
                while (fread(&modif, sizeof(modif), 1, fp2))
                {
                    fwrite(&modif, sizeof(modif), 1, fp1);
                }
                fclose(fp1);
                fclose(fp2);
                remove("temp.dat");
                printf("Flight removed successfully!");
            }
            else
            {
                remove("temp.dat");
                printf("No flight found with ID: %s!", f_id);
            }
            break;
        case 3: // modify flight
        modify:
            file = fopen("flights.dat", "rb");
            while (fread(&modif, sizeof(modif), 1, file) == 1)
            {
                printf("%-5s  %-20s", modif.id, modif.name);
                printf("%-20s  %-20s", modif.source, modif.destination);
                printf("%4d  %4d\n", modif.seats, modif.fare);
                ++count;
            }
            if (!count)
            {
                printf("\nNo flights are available to modify!\n");
                menu();
            }
            fclose(file);
            printf("\nEnter Flight ID to modify: ");
            scanf("%s", id);
            t = fopen("temp.dat", "wb");
            flag = 1;
            count = 0;
            file = fopen("flights.dat", "rb");
            while (fread(&fl, sizeof(flight), 1, file) == 1)
            {
                ++total;
                if (strcmp(fl.id, id) == 0)
                {
                    printf("Flight Details.\n");
                    printf("Current ID: %s", fl.id);
                    strcpy(temp.id, fl.id);
                    printf("\n1. seats: %d", fl.seats);
                    temp.seats = fl.seats;
                    printf("\n2. time: %s", fl.time);
                    strcpy(temp.time, fl.time);
                    printf("\n3. source: %s", fl.source);
                    strcpy(temp.source, fl.source);
                    printf("\n4. destination: %s", fl.destination);
                    strcpy(temp.destination, fl.destination);
                    printf("\n5. name: %s", fl.name);
                    strcpy(temp.name, fl.name);
                    printf("\n6. fare: Rs. %d\n", fl.fare);
                    temp.fare = fl.fare;
                    flag = 0;
                // modification starts
                chan:
                    printf("Enter the serial number of the property you want to modify for the flight %s: ", fl.name);
                    getchar();
                    fgets(mod, 14, stdin);
                    int res = sscanf(mod, "%d %d %d %d %d %d %d", &p[0], &p[1], &p[2], &p[3], &p[4], &p[5], &p[6]);
                    // printf("%d\n",res);
                    int check[8] = {0, 0, 0, 0, 0, 0, 0, 0};
                    for (i = 0; i < res; i++)
                    {
                        switch (p[i])
                        {
                        case 1:
                        seats:
                            printf("Enter the modified number of seats. (current number of seats: %d): ", fl.seats);
                            scanf("%d", &temp.seats);
                        s1:
                            printf("Enter 1 to confirm, 2 to change new number of seats (current: %d; modified: %d)\nEnter 3 to exit modification menu: ", fl.seats, temp.seats);
                            scanf("%d", &choice);
                            if (choice == 1)
                            {
                            }
                            else if (choice == 2)
                            {
                                goto seats;
                            }
                            else if (choice == 3)
                            {
                                goto menu;
                            }
                            else
                            {
                                printf("Enter a valid option.");
                                goto s1;
                            }
                            check[0] = 1;
                            break;
                        case 2:
                        t:
                            printf("Enter the modified flight timing. (current time of flight: %s)", fl.time);
                            printf("\nEnter hours: ");
                            scanf("%d", &h);
                            printf("Enter minutes: ");
                            scanf("%d", &m);
                            itoa(h, th, 10);
                            itoa(m, tm, 10);
                            strcat(th, ":");
                            strcat(th, tm);
                            for (j = 0; j < strlen(th); j++)
                            {
                                temp.time[j] = th[j];
                            }
                        t1:
                            printf("Enter 1 to confirm, 2 to change new timing of flight (current: %s; modified: %s)\nEnter 3 to exit modification menu: ", fl.time, temp.time);
                            scanf("%d", &choice);
                            if (choice == 1)
                            {
                            }
                            else if (choice == 2)
                            {
                                goto t;
                            }
                            else if (choice == 3)
                            {
                                goto menu;
                            }
                            else
                            {
                                printf("Enter a valid option.");
                                goto t1;
                            }
                            check[1] = 2;
                            break;
                        case 3:
                        source:
                            printf("Enter new departure of the flight (current: %s): ", fl.source);
                            scanf("%s", temp.source);
                        so1:
                            printf("Enter 1 to confirm, 2 to change new departure of flight (current: %s; modified: %s)\nEnter 3 to exit modification menu: ", fl.source, temp.source);
                            scanf("%d", &choice);
                            if (choice == 1)
                            {
                            }
                            else if (choice == 2)
                            {
                                goto source;
                            }
                            else if (choice == 3)
                            {
                                goto menu;
                            }
                            else
                            {
                                printf("Enter a valid option.");
                                goto so1;
                            }
                            check[2] = 3;
                            break;
                        case 4:
                        des:
                            printf("Enter new destination of the flight (current: %s): ", fl.destination);
                            scanf("%s", temp.destination);
                        // fgets(temp.destination,20,stdin);
                        de1:
                            printf("Enter 1 to confirm, 2 to change new departure of flight (current: %s; modified: %s)\nEnter 3 to exit modification menu: ", fl.source, temp.source);
                            scanf("%d", &choice);
                            if (choice == 1)
                            {
                            }
                            else if (choice == 2)
                            {
                                goto des;
                            }
                            else if (choice == 3)
                            {
                                goto menu;
                            }
                            else
                            {
                                printf("Enter a valid option.");
                                goto de1;
                            }
                            check[3] = 4;
                            break;
                        case 5:
                        na:
                            printf("Enter new name of flight. (current: %s): ", fl.name);
                            fflush(stdin);
                            scanf("%[^\n]ff", temp.name);
                        // fgets(temp.name,20,stdin);
                        na1:
                            printf("Enter 1 to confirm, 2 to change new departure of flight (current: %s; modified: %s)\nEnter 3 to exit modification menu: ", fl.name, temp.name);
                            scanf("%d", &choice);
                            if (choice == 1)
                            {
                            }
                            else if (choice == 2)
                            {
                                goto na;
                            }
                            else if (choice == 3)
                            {
                                goto menu;
                            }
                            else
                            {
                                printf("Enter a valid option.");
                                goto na1;
                            }
                            check[4] = 5;
                            break;
                        case 6:
                        fare:
                            printf("Enter new fare (current: %d): ", fl.fare);
                            scanf("%d", &temp.fare);
                            printf("Enter 1 to confirm, 2 to change new fare for flight (current: %d; modified: %d)\nEnter 3 to exit modification menu: ", fl.fare, temp.fare);
                            scanf("%d", &choice);
                            if (choice == 1)
                            {
                            }
                            else if (choice == 2)
                            {
                                goto na;
                            }
                            else if (choice == 3)
                            {
                                goto menu;
                            }
                            else
                            {
                                printf("Enter a valid option.");
                                goto na1;
                            }
                            check[5] = 6;
                            break;
                        default:
                        er:
                            printf("Properties serial number out of range or invalid. Enter 1 to go to Login menu, 2 to try agin: ");
                            scanf("%d", &choice);
                            if (choice == 1)
                            {
                                login();
                                return;
                            }
                            else if (choice == 2)
                            {
                                goto chan;
                            }
                            else
                            {
                                printf("Enter a valid option.\n");
                                goto er;
                            }
                            break;
                        }
                    }

                    if ((check[2] == 3) || (check[3] == 4) || (check[4] == 5))
                    {
                        char n_id[10];
                        for (i = 0; i < 3; i++)
                        {
                            n_id[i] = temp.name[i];
                        }
                        n_id[3] = '\0';
                        ch1 = temp.source[0];
                        ch2 = temp.destination[0];
                        ch3 = ch1 * 100 + ch2;
                        sprintf(num, "%d", ch3);
                        strcat(n_id, num);
                        strcpy(temp.id, n_id);
                        while (fread(&modif, sizeof(flight), 1, file) == 1)
                        {
                            if (strcmp(temp.id, modif.id) == 0)
                            {
                                printf("Error! Flight with same ID exists. Program will exit now.");
                                exit(0);
                                break;
                            }
                        }
                    }
                    else
                    {
                        strcpy(temp.id, fl.id);
                    }

                    fwrite(&temp, sizeof(temp), 1, t);
                    ++count;
                }
                else
                {
                    fwrite(&fl, sizeof(fl), 1, t);
                    ++count;
                }
            }
            fclose(t);
            fclose(file);
            t = fopen("temp.dat", "rb");
            printf("Modified FLight ID: %s", temp.id);
            fclose(t);
            if (count == total)
            {
                remove("flights.dat");
                rename("temp.dat", "flights.dat");
                printf("\nModification successful.");
            }
            else
            {
                printf("Some error occured");
                exit(0);
            }
            getchar();
            if (flag)
            {
            opt:
                printf("INVALID FLIGHT ID. Enter 1 to try again, 2 to return to LOGIN menu, 3 to choose other option: ");
                fclose(t);
                remove("temp.dat");
                scanf("%d", &flag);
                switch (flag)
                {
                case 1:
                    goto modify;
                    break;
                case 2:
                    login();
                    break;
                case 3:
                    choice = 0;
                    break;
                default:
                    printf("Enter a valid option.");
                    goto opt;
                    break;
                }
            }
            break;
        case 4:
            login();
            break;
        default:
            printf("Enter a valid option.");
            choice = 0;
            // goto menu;
            break;
        }
    }
    login(); // after every successfull action admin is logged out.
    return;
}
// 157; 159
void search()
{
    flight f1;
    FILE *fp;
    int found = 0;
    char text[20];
    fp = fopen("flights.dat", "rb");
    printf("Enter free text to search : ");
    scanf("%s", text);
    while (fread(&f1, sizeof(flight), 1, fp))
    {
        int flag1 = 0, flag2 = 0, flag3 = 0, flag4 = 0, i = 0; // integer variables declaration
                                                               //USING DESTINATION
        while (f1.destination[i] != '\0' && text[i] != '\0')
        {
            if (f1.destination[i] != text[i])
            {
                flag1 = 1;
                break;
            }
            i++;
        }
        //USING SOURCE
        while (f1.source[i] != '\0' && text[i] != '\0')
        {
            if (f1.source[i] != text[i])
            {
                flag2 = 1;
                break;
            }
            i++;
        }
        //USING FLIGHT NAME
        while (f1.name[i] != '\0' && text[i] != '\0')
        {
            if (f1.name[i] != text[i])
            {
                flag3 = 1;
                break;
            }
            i++;
        }
        //USING FLIGHT ID
        while (f1.id[i] != '\0' && text[i] != '\0')
        {
            if (f1.id[i] != text[i])
            {
                flag4 = 1;
                break;
            }
            i++;
        }
        if (flag1 == 0 || flag2 == 0 || flag3 == 0 || flag4 == 0)
        {
            found = 1;
            printf("\n%-5s  %-20s", f1.id, f1.name);
            printf("%-20s  %-20s", f1.source, f1.destination);
            printf("%4d  %4d\n", f1.seats, f1.fare);
        }
    }
    if (!found)
    {
        printf("\nFlight NOT found\n");
    }
    fclose(fp);
    return;
}
// 157
void cancel(person user)
{
    printf("\nWelcome to cancellation department!");
    int ch;
label:
    printf("\nTo cancel booked tickets enter 1, to return to login menu enter 2: ");
    scanf("%d", &ch);
    switch (ch)
    {
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
    FILE *fp1, *fp2;
    int ticket_id, found = 0;
    fp1 = fopen("booking.dat", "r");
    fp2 = fopen("temp.dat", "ab");
    printf("ticket id to delete: ");
    scanf("%d", &ticket_id);
    while (fread(&t, sizeof(t), 1, fp1))
    {
        if ((t.ticket_id == ticket_id) && (strcmp(t.uname, user.uname) == 0))
        {
            found = 1;
        }
        else
            fwrite(&t, sizeof(t), 1, fp2);
    }
    fclose(fp1);
    fclose(fp2);
    if (found)
    {
        fp2 = fopen("temp.dat", "r");
        fp1 = fopen("booking.dat", "wb");
        while (fread(&t, sizeof(t), 1, fp2))
        {
            fwrite(&t, sizeof(t), 1, fp1);
        }
        fclose(fp1);
        fclose(fp2);
        remove("temp.dat");
        flight tempo;
        FILE *flight;
        FILE *fli;
        fli = fopen("temp.dat", "wb");
        flight = fopen("flights.dat", "r");
        while (fread(&tempo, sizeof(tempo), 1, flight) == 1)
        {
            if (strcmp(tempo.id, t.f_id) == 0)
            {
                tempo.seats = tempo.seats + 1;
            }
            fwrite(&tempo, sizeof(tempo), 1, fli);
        }
        remove("flights.dat");
        rename("temp.dat", "flights.dat");
        printf("Ticket cancelled successfully! Want to cancel another?");
        goto label;
    }
    else
    {
        remove("temp.dat");
        printf("Ticket ID invalid or ticket not found booked under %s!", user.name);
        // cancel();
    }
}

int main()
{
    system("cls");
    printf("\nWELCOME TO IISER KOLKATA FLIGHT BOOKING SYSTEM\n");
    menu();
    return 0;
}
