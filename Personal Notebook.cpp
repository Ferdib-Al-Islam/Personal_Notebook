#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<time.h>

int password();
void addrecord();
void viewrecord();
void editrecord();
void editpassword();
void deleterecord();
int time();

struct record
{
    char time[6];
    char name[30];
    char details[1000000];
    char place[250];
    char duration[10];
};

int main()
{
    system("color 1e");

    int ch;

    printf("\t         Welcome to your own's world\n");

    time();

    while(1)
    {
        printf("\n\n\t\tUser Menu");
        printf("\n\n\tAdd Record\t[1]");
        printf("\n\tView Record\t[2]");
        printf("\n\tEdit Record\t[3]");
        printf("\n\tDelete Record\t[4]");
        printf("\n\tEdit password\t[5]");
        printf("\n\tExit\t\t[6]");
        printf("\n\n\t*******************");
        printf("\n\t*******************\n");

        printf("\n\tEnter Key : ");
        scanf("%d",&ch);

        switch(ch)
        {
        case 1:
            addrecord();
            break;
        case 2:
            viewrecord();
            break;
        case 3:
            editrecord();
            break;
        case 4:
            deleterecord();
            break;
        case 5:
            editpassword();
            break;
        case 6:
            printf("\n\n\t\tThank you for using my software : \n\n\t Ferdib-Al-Islam \n\n\t ID: 20121201036 \n\n\t Mobile: 01759296808 \n\n\t Address: Dept. of CSE, BSMRSTU ...");
            getch();

            exit(0);
        default:
            printf("\nYou Entered Wrong Key...");
            printf("\nPress Any Key To Try Again...");
            getch();
            break;
        }
        system("cls");
    }
    return 0;
}

int time()
{
	time_t t;
    time(&t);

    printf("\n\n\tDate and Time : %s", ctime(&t));
}

void addrecord()
{
    system("cls");
    system("color 5f");
    time();
    FILE *fp ;
    char another = 'Y' ,time[10];
    struct record e ;
    char filename[15];
    int k;

    printf("\n\n\t\t***************************\n");
    printf("\t\t*\t Add Menu \t*");
    printf("\n\t\t***************************\n\n");
    printf("\n\n\tEnter Record's Details : [yyyy-mm-dd] : ");

    fflush(stdin);
    gets(filename);

    fp = fopen(filename, "ab+") ;
    if( fp == NULL )
    {
        fp=fopen(filename,"wb+");
        if(fp==NULL)
        {
            printf("\nError...");
            printf("\nPress Any Key To Exit...");
            getch();
            return ;
        }
    }
    while(another == 'Y'|| another=='y')
    {
        k=0;
        fflush(stdin);
        printf("\n\tEnter Time : [hh:mm] : ");

        scanf("%s",time);
        rewind(fp);
        while(fread(&e,sizeof(e),1,fp)==1)
        {
            if(strcmp(e.time,time)==0)
            {
                printf("\n\tAlready Exists...\n");
                k=1;
            }
        }
        if(k==0)
        {
            strcpy(e.time,time);
            printf("\n\tEnter Name : ");

            fflush(stdin);
            gets(e.name);
            fflush(stdin);

            printf("\n\tEnter Place : ");
            gets(e.place);
            fflush(stdin);

            printf("\n\tEnter Duration : ");
            gets(e.duration);
            fflush(stdin);

            printf("\n\tDetails : ");
            gets(e.details);

            fwrite( &e, sizeof ( e ), 1, fp);
            printf("\nAddition Completed...\n");
        }

        printf( "\n\tAnother...???\n\tPress Y/N " ) ;
        fflush(stdin);
        another = getchar( ) ;
    }
    fclose ( fp ) ;
    printf("\n\n\tPress Any Key To Exit...");
    getch();
}

void viewrecord()
{
    FILE *fpte ;
    system("cls");
    time();

    struct record customer ;
    char time[6],k,filename[14];
    int ch;

    printf("\n\n\t\t*******************************\n");
    printf("\t\t*\t Collection \t*");
    printf("\n\t\t*******************************\n\n");

    k=password();

    if(k!=0)
    {
        return ;
    }
    do
    {
        printf("\n\tEnter Details :[yyyy-mm-dd]: ");
        fflush(stdin);
        gets(filename);

        fpte = fopen( filename, "rb" ) ;
        if ( fpte == NULL )
        {
            puts ( "\nNot Exists...\n" ) ;
            printf("Press Any Key To Exit...");
            getch();
            return ;
        }
        system("cls");
        printf("\n\tPlease, Select : \n");
        printf("\n\t1.View all.");
        printf("\n\t2.Exact time.");
        printf("\n\t\tEnter Key: ");
        scanf("%d",&ch);
        switch(ch)
        {
        case 1:
            printf("\nAll Record of %s are: ",filename);
            while ( fread ( &customer, sizeof ( customer ), 1, fpte ) == 1 )
            {
                printf("\n");
                printf("\nTime: %s",customer.time);
                printf("\nMeeting With: %s",customer.name);
                printf("\nMeeting With at: %s",customer.place);
                printf("\nDuration: %s",customer.duration);
                printf("\nDetails: %s",customer.details);
                printf("\n");
            }
            break;

        case 2:
            fflush(stdin);
            printf("\nEnter Time:[hh:mm]: ");
            gets(time);
            while ( fread ( &customer, sizeof ( customer ), 1, fpte ) == 1 )
            {
                if(strcmp(customer.time,time)==0)
                {
                    printf("\nRecord: ");
                    printf("\nTime: %s",customer.time);
                    printf("\nMeeting With : %s",customer.name);
                    printf("\nMeeting Place: %s",customer.place);
                    printf("\nDuration: %s",customer.duration);
                    printf("\nDetails: %s",customer.details);
                }
            }
            break;

        default:
            printf("\nWrong Key Pressed...\n");
            break;
        }

        printf("\n\nWant to continue...? (Y/N):");

        fflush(stdin);
        scanf("%c",&k);
    }
    while(k=='Y'||k=='y');

    fclose ( fpte ) ;
    return ;
}
void editrecord()
{
    system("cls");
    system("color 5f");
    FILE *fpte ;

    struct record customer ;
    char time[6],k,filename[14];

    int num,count=0;

    printf("\n\n\t\t*******************************\n");

    printf("\t\t* Edit Menu *");

    printf("\n\t\t*******************************\n\n");
    k=password();

    if(k!=0)
    {
        return ;
    }

    do
    {
        printf("\n\tEnter Details: [yyyy-mm-dd] : ");
        fflush(stdin);
        gets(filename);

        printf("\n\tenter time: [hh:mm]: ");

        gets(time);

        fpte = fopen ( filename, "rb+" ) ;
        if ( fpte == NULL )
        {
            printf( "\nNot Exists...." ) ;
            printf("\nPress Any Key To Go Back...");
            getch();

            return;
        }
        while ( fread ( &customer, sizeof ( customer ), 1, fpte ) == 1 )
        {
            if(strcmp(customer.time,time)==0)
            {
                printf("\nyour Old Record Was As: ");
                printf("\nTime: %s",customer.time);
                printf("\nMeeting With: %s",customer.name);
                printf("\nMeeting Place: %s",customer.place);
                printf("\nDuration: %s",customer.duration);
                printf("\nDetails: %s",customer.details);
                printf("\n\n\t\tWhat Would You Like To Edit...???");
                printf("\n1.Time.");
                printf("\n2.Meeting With Person.");
                printf("\n3.Meeting Place.");
                printf("\n4.Duration.");
                printf("\n5.Details.");
                printf("\n6.WHOLE RECORD.");
                printf("\n7.Go To Main Menu.");
                do
                {
                    printf("\n\tEnter Key: ");
                    fflush(stdin);
                    scanf("%d",&num);
                    fflush(stdin);

                    switch(num)
                    {
                    case 1:
                        printf("\nEnter New Data: ");
                        printf("\nNew Time: [hh:mm]: ");
                        gets(customer.time);
                        break;

                    case 2:
                        printf("\nEnter New Data: ");
                        printf("\nNew Meeting Person: ");
                        gets(customer.name);
                        break;

                    case 3:
                        printf("\nEnter New Data: ");
                        printf("\nNew Meeting Place: ");
                        gets(customer.place);
                        break;

                    case 4:
                        printf("\nEnter New Data: ");
                        printf("\nDuration: ");
                        gets(customer.duration);
                        break;

                    case 5:
                        printf("Enter New Data: ");
                        printf("\nDetails: ");
                        gets(customer.details);
                        break;

                    case 6:
                        printf("\nEnter New Data: ");
                        printf("\nNew Time: [hh:mm]: ");
                        gets(customer.time);
                        printf("\nNew Meeting Person: ");
                        gets(customer.name);
                        printf("\nNew Meeting Place: ");
                        gets(customer.place);
                        printf("\nDuration: ");
                        gets(customer.duration);
                        printf("\nDetails: ");
                        gets(customer.details);
                        break;

                    case 7:
                        printf("\nPress Any Key To Go Back...\n");
                        getch();
                        return ;
                        break;

                    default:
                        printf("\nYou Pressed Something Else...Try Again\n");
                        break;
                    }
                }
                while(num<1 || num>8);
                fseek(fpte,-sizeof(customer),SEEK_CUR);
                fwrite(&customer,sizeof(customer),1,fpte);
                fseek(fpte,-sizeof(customer),SEEK_CUR);
                fread(&customer,sizeof(customer),1,fpte);
                k=5;
                break;
            }
        }
        if(k==5)
        {
            system("cls");
            printf("\n\t\tEditing Complete...\n");
            printf("--------------------\n");
            printf("the New Record Is: \n");
            printf("--------------------\n");
            printf("\nTime: %s",customer.time);
            printf("\nMeeting With: %s",customer.name);
            printf("\nMeeting With At: %s",customer.place);
            printf("\nDuration: %s",customer.duration);
            printf("\nDetails: %s",customer.details);
            fclose(fpte);
            printf("\n\n\tWould You Like To Edit Another...??? (Y/N)");

            scanf("%c",&k);
            count++;
        }
        else
        {
            printf("\nRecord Not Exists.\n");
            printf("\nWanna Try Again...??? (Y/N)");
            scanf("%c",&k);
        }
    }
    while(k=='Y' || k=='y');
    fclose ( fpte ) ;
    if(count==1)
        printf("\n%d File Is Edited...\n",count);
    else if(count>1)
        printf("\n%d Files Are Edited...\n",count);
    else
        printf("\nNo Files Are Edited...\n");
    printf("\tPress Enter To Exit Editing...");
    getch();
}


int password()
{
    system("color 60");
    time();

    char pass[15]= {0},check[15]= {0},ch;
    FILE *fpp;
    int i=0,j;

    printf("\tSecurity Check -> ");
    printf("You will get atmost 3 Trials...");

    for(j=0; j<3; j++)
    {
        i=0;
        printf("\n\n\tEnter Password: ");
        pass[0]=getch();
        while(pass[i]!='\r')
        {
            if(pass[i]=='\b')
            {
                i--;
                printf("\b");
                printf(" ");
                printf("\b");
                pass[i]=getch();
            }
            else
            {
                printf("*");
                i++;
                pass[i]=getch();
            }
        }
        pass[i]='\0';
        fpp=fopen("password","r");
        if (fpp==NULL)
        {
            printf("\nError -> -> -> File Missing\n");
            getch();
            return 1;
        }
        else
            i=0;

        while(1)
        {
            ch=fgetc(fpp);
            if(ch==EOF)
            {
                check[i]='\0';
                break;
            }
            check[i]=ch-5;
            i++;
        }
        if(strcmp(pass,check)==0)
        {
            printf("\n\n\tAccess Granted...\n");
            return 0;
        }
        else
        {
            printf("\n\n\tWrong Password..\n\n\n");
        }
    }
    printf("\n\n\tNo More Trial Exists.\n\n\tPress Any Key To Go Back...");
    getch();

    return 1;
}

void editpassword()
{
    system("cls");
    printf("\n");
    time();

    char pass[15]= {0},confirm[15]= {0},ch;
    int k,i,check;

    FILE *fp;
    fp=fopen("password","rb");

    if(fp==NULL)
    {
        fp=fopen("password","wb");

        if(fp==NULL)
        {
            printf("Error...");
            getch();
            return ;
        }
        fclose(fp);
        printf("\nSystem Restored...\nYour Password Is 'enter'\n Press Enter To Change Password\n\n");

        getch();
    }
    fclose(fp);
    check=password();

    if(check==1)
    {
        return ;
    }
    do
    {
        if(check==0)
        {
            i=0;
            k=0;
            printf("\n\n\tEnter The New Password: ");

            fflush(stdin);
            pass[0]=getch();

            while(pass[i]!='\r')
            {
                if(pass[i]=='\b')
                {
                    i--;
                    printf("\b");
                    printf(" ");
                    printf("\b");
                    pass[i]=getch();
                }
                else
                {
                    printf("*");
                    i++;
                    pass[i]=getch();
                }
            }
            pass[i]='\0';

            i=0;

            printf("\n\tConfirm Password: ");
            confirm[0]=getch();

            while(confirm[i]!='\r')
            {
                if(confirm[i]=='\b')
                {
                    i--;
                    printf("\b");
                    printf(" ");
                    printf("\b");
                    confirm[i]=getch();
                }
                else
                {
                    printf("*");
                    i++;
                    confirm[i]=getch();
                }
            }
            confirm[i]='\0';
            if(strcmp(pass,confirm)==0)
            {
                fp=fopen("password","wb");
                if(fp==NULL)
                {
                    printf("\n\t\tError");
                    getch();
                    return ;
                }
                i=0;
                while(pass[i]!='\0')
                {
                    ch=pass[i];
                    putc(ch+5,fp);
                    i++;
                }
                putc(EOF,fp);
                fclose(fp);
            }
            else
            {
                printf("\n\tThe New Password Does Not Match...");
                k=1;
            }
        }
    }
    while(k==1);
    printf("\n\n\tPassword Changed...\n\n\tPress Any Key To Go Back...");
    getch();
}

void deleterecord()
{
    system("cls");
    system("color 42");
    time();
    FILE *fp,*fptr ;

    struct record file ;
    char filename[15],another = 'Y' ,time[10];;
    int k,check;

    printf("\n\n\t\t*************************\n");
    printf("\t\t*Delete Menu*");
    printf("\n\t\t*************************\n\n");

    check = password();

    if(check==1)
    {
        return ;
    }
    while ( another == 'Y')
    {
        printf("\n\n\tPlease, Select...");
        printf("\n\n\t#Delete All\t\t\t[1]");
        printf("\n\t#Delete Time-wise\t[2]");
        do
        {
            printf("\n\t\tEnter Key: ");
            scanf("%d",&k);
            switch(k)
            {
            case 1:
                printf("\n\tEnter The Record's Details :[yyyy-mm-dd] : ");
                fflush(stdin);
                gets(filename);
                fp = fopen (filename, "wb" ) ;
                if ( fp == NULL )
                {
                    printf("\nFile Not Exists...");
                    printf("\nPress Any Key To Return...");
                    getch();
                    return ;
                }
                fclose(fp);
                remove(filename);
                printf("\nDelete Completed...");
                break;

            case 2:
                printf("\n\tEnter Date :[yyyy-mm-dd]: ");
                fflush(stdin);
                gets(filename);
                fp = fopen (filename, "rb" ) ;
                if(fp==NULL)


                {
                    printf("\nFile Not Exists...");
                    printf("\nPress Any Key To Return...");
                    getch();
                    return ;
                }
                fptr=fopen("temp","wb");
                if(fptr==NULL)
                {
                    printf("\nError...!!!");
                    printf("\nPress Any Key To Return...");
                    getch();
                    return ;
                }
                printf("\n\tEnter The Record's Time: [hh:mm]: ");
                fflush(stdin);
                gets(time);

                while(fread(&file,sizeof(file),1,fp)==1)
                {
                    if(strcmp(file.time,time)!=0)
                        fwrite(&file,sizeof(file),1,fptr);
                }
                fclose(fp);
                fclose(fptr);
                remove(filename);
                rename("temp",filename);
                printf("\nDelete Completed...");
                break;

            default:
                printf("\n\tYou Entered Wrong Key...");
                break;
            }
        }
        while(k<1||k>2);
        printf("\n\tWanna Delete Another Record...??? (Y/N)");
        fflush(stdin);
        scanf("%c",&another);
    }
    printf("\n\n\tPress Any Key To Exit......");
    getchar();
}


