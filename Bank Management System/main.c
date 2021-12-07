#include <stdio.h>
#include <wmmintrin.h>
#include <string.h>
struct CustomerAccount
{
    int id;
    char firstName[30];
    char lastName[30];
    int accountNumber;
    double balance;
    int accCreationDate[3];
};

/* FILES RELATED FUNCTIONS */
void saveUserInfoToFile(struct CustomerAccount user);
struct CustomerAccount readCustomers(int numberOfUsers, char queryName[50], char queryValue[80]);

int printRandoms(int lower, int upper,
                 int count)
{
    int i;
    for (i = 0; i < count; i++)
    {
        int num = (rand() %
                   (upper - lower + 1)) +
                  lower;
        return num;
    }
}

void createAccount()
{
    struct CustomerAccount newCustomer;
    printf("\e[1;1H\e[2J");
    printf("Enter Your Name(FirstName LastName)\t");
    scanf("%s%s", newCustomer.firstName, newCustomer.lastName);

    printf("Enter Date (dd mm yyyy)\t");
    scanf("%d%d%d", &newCustomer.accCreationDate[0], &newCustomer.accCreationDate[1], &newCustomer.accCreationDate[2]);

    printf("Enter initial amount to store in account\t");
    scanf("%lf", &newCustomer.balance);
    newCustomer.accountNumber = printRandoms(100000, 10000000, 1);
    saveUserInfoToFile(newCustomer);
}

int main()
{
    int choice, close = 0;
    while (close != 1)
    {

        printf("\e[1;1H\e[2J");
        // system("clear");
        printf("\t\t\tXYZ BANK MANAGEMENT SYSTEM\t\t\n\n");
        printf("\t\t\t     ▓▓▓▓▓▓ MENU ▓▓▓▓▓▓\n\n");

        printf("\t1. Create a new account\n\t2. Update information of existing account\n\t3. Check details of existing account\n\t4. Delete esisting account\n\t5. View Customers List\n\t6. Transactions List\n\t7. Exit");

        printf("\n\n\tEnter Choice\t");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            createAccount();
            break;
        case 5:
            readCustomers(0, NULL, NULL);
            break;
        case 7:
            close = 1;
            break;
        default:
            break;
        }
    }

    return 0;
}

/* FILES RELATED FUNCTIONS */
int id = 0;
void saveUserInfoToFile(struct CustomerAccount user)
{
    /*
    FirstName Last Name
    Date of Account Creation
    Account Number
    Amount in Account

    */
    FILE *file = fopen("accounts.txt", "a");
    if (file == NULL)
    {
        printf("ERROR: Couldn't open accounts.txt file");
    }
    else
    {
        id++;
        fprintf(file, "\n\n%d\n%s %s\n%d %d %d\n%d\n%f", id, user.firstName, user.lastName, user.accCreationDate[0], user.accCreationDate[1], user.accCreationDate[2], user.accountNumber, user.balance);
        fclose(file);
    }
}

struct CustomerAccount readCustomers(int numberOfUsers, char queryName[50], char queryValue[80])
{
    struct CustomerAccount customerList[200];
    FILE *file = fopen("accounts.txt", "r");
    if (file == NULL)
    {
        printf("ERROR: Couldn't open accounts.txt file");
    }
    else if (numberOfUsers == 0)
    {
        char line[100];
        // Return all accounts
        while (fgets(line, 100, file) != NULL)
        {
            int len = strlen(line);
            if (len == 2)
            {
                int id = atoi(line);

                fgets(line, 100, file);
                char firstName[80];
                char lastName[80];
                int check = 0;
                int j = 0;
                for (int i = 0; i < strlen(line); i++)
                {
                    if (line[i] != ' ' && check == 0)
                        firstName[i] = line[i];
                    else if (line[i] != ' ' && check == 1)
                        lastName[j++] = line[i];
                    else if (line[i] == ' ')
                        check = 1;
                }

                fgets(line, 100, file);
                char day[2];
                day[0] = line[0];
                if (line[1] != ' ')
                    day[1] = line[1];
                char month[2];
                month[0] = line[2];
                month[1] = line[3];
                char year[4];
                year
                    // TODO:
                    int date[3];
                date[0] = atoi(day);
                date[1] = atoi(month);
                date[2] = atoi(year);

                // printf("%d %d  %d\n", date[0], date[1], date[2]);
            }
        }
    }
    else if (numberOfUsers == 1)
    {
        // One account with query
    }
    else
    {
    }
    fclose(file);
}
