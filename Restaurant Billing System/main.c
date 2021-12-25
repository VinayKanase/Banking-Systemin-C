#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*----------------------------------------------------------------
    Billing System for KSJ Cafe 
----------------------------------------------------------------*/

struct FoodItem
{
    char name[100];
    int quantity;
    int pricePerItem;
};

struct Date
{
    int day;
    int month;
    int year;
};
struct Bill
{
    struct Date date;
    int billNo;
    char firstName[20];
    char lastName[20];
    int totalItems;
    struct FoodItem items[100];
};

// Global variables
double gstPercent = 2.5;
struct Bill bills[200];
struct Date today;
int totalBills = 0;

// Function Prototypes
void manager(int choice, int *exit);

// File related functions
void createNewInvoice(int index);
void addAllBills();
void readAllBills();
void deleteBillFromFiles(int index);

int main()
{
    int choice, closeSystem = 0;
    printf("Enter date in (dd mm yy) format: ");
    scanf("%d %d %d", &today.day, &today.month, &today.year);
    readAllBills();
    while (closeSystem != 1)
    {

        printf("\e[1;1H\e[2J");
        printf("\033[1;35m");
        printf("\n\t\t\t -------- KSJ CAFE -------- \n");
        printf("\033[0m");

        printf("\n\t\t\t### MENU ###\n");
        printf("\n\t\t\t 1. New bill\n\t\t\t 2. show all bills\n\t\t\t 3. Search bill\n\t\t\t 4. Delete invoice\n\t\t\t 5. Exit");
        printf("\n\n\t\tEnter choice: ");
        scanf("%d", &choice);
        manager(choice, &closeSystem);
    }
    return 0;
}

void createNewBill()
{
    printf("\e[1;1H\e[2J");
    bills[totalBills].date = today;
    printf("Enter first name: ");
    scanf("%s", bills[totalBills].firstName);
    printf("Enter last name: ");
    scanf("%s", bills[totalBills].lastName);
    char exitLoop = 0;
    int itemCount = 0;
    bills[totalBills].billNo = totalBills + 1;
    while (exitLoop != '1')
    {
        printf("Enter food item name: ");
        scanf("%s", bills[totalBills].items[itemCount].name);
        printf("Enter quantity: ");
        scanf("%d", &bills[totalBills].items[itemCount].quantity);
        printf("Enter price per item in Rs: ");
        scanf("%d", &bills[totalBills].items[itemCount].pricePerItem);
        itemCount++;
        printf("Enter 1 to complete item list: ");
        scanf(" %c", &exitLoop);
    }
    bills[totalBills].totalItems = itemCount;
    createNewInvoice(totalBills);
    totalBills++;
    addAllBills();
}

void putStringAtCenter(char string[], int totalChar)
{
    int spacesForName = totalChar - strlen(string);
    spacesForName /= 2;
    for (int j = 0; j < spacesForName; j++)
        printf(" ");
    printf("%s", string);
    for (int j = 0; j < spacesForName; j++)
        printf(" ");
    if ((totalChar - strlen(string)) % 2 != 0)
        printf(" ");
}

void displayBill(struct Bill bill)
{
    int netTotal = 0;
    float gst;
    char temp[100];

    printf("\e[1;1H\e[2J");
    printf("\033[1m");
    printf("\n\t\t\t\t\tKSJ CAFE\n");
    printf("\033[0m");

    // printf("\033[1;30m");
    printf("\033[1;37m");
    printf("\n---------------------------------------INVOICE---------------------------------------");
    printf("\033[0m");
    printf("\n\t Name:\033[1;35m %s %s\n", bill.firstName, bill.lastName);
    printf("\033[0m");
    printf("\t Date:\033[1;31m %d/%d/%d\033[0m       Bill No. \033[0;33m%d\033[0m", bill.date.day, bill.date.month, bill.date.year, bill.billNo);
    printf("\n-------------------------------------------------------------------------------------\n");
    printf("                       Item Name                     |   Qty   |   Rate   |  Amount  ");
    printf("\n\033[0;36m-------------------------------------------------------------------------------------\033[0m\n");
    for (int i = 0; i < bill.totalItems; i++)
    {
        putStringAtCenter(bill.items[i].name, 53);
        printf("|");

        sprintf(temp, "%d", bill.items[i].quantity);
        putStringAtCenter(temp, 9);
        printf("|");
        sprintf(temp, "%d", bill.items[i].pricePerItem);
        putStringAtCenter(temp, 10);
        printf("|");
        int total = bill.items[i].quantity * bill.items[i].pricePerItem;
        netTotal += total;
        sprintf(temp, "%d", total);
        putStringAtCenter(temp, 11);
        if (i != (bill.totalItems - 1))
            printf("\n\033[0;36m-------------------------------------------------------------------------------------\033[0m\n");
    }
    printf("\n-------------------------------------------------------------------------------------\n");
    printf("                                                                Net Total:   ");
    sprintf(temp, "%d", netTotal);
    putStringAtCenter(temp, 12);
    // printf("\n");

    gst = netTotal * (gstPercent / 100);
    printf("\033[0;36m                                                        -----------------------------\033[0m\n");
    printf("                                                                SGST@%.2f   ", gstPercent);
    sprintf(temp, "%.2f", gst);
    putStringAtCenter(temp, 12);
    printf("\n");
    printf("                                                                CGST@%.2f   ", gstPercent);
    putStringAtCenter(temp, 12);
    printf("\n");
    printf("\033[0;36m                                                        -----------------------------\033[0m\n");
    float grandTotal = netTotal + (gst * 2);
    printf("                                                               Grand Total: ");
    sprintf(temp, "%.2f", grandTotal);
    putStringAtCenter(temp, 10);
    printf("\n");
    printf("-------------------------------------------------------------------------------------\n");
}

void showAllBills(struct Bill bills[], int totalBills)
{
    if (totalBills == 0)
        printf("\n\t\tNO BILLS FOUND");
    for (int i = 0; i < totalBills; i++)
    {
        printf("\n\n\n");
        displayBill(bills[i]);
        printf("\n\n\n");
    }

    char wait;
    printf("\n\n\t\tEnter any character to exit ");
    scanf(" %c", &wait);
}

int searchByName(char name[])
{
    int i = 0;
    for (; i < totalBills; i++)
    {
        if (!strcmp(bills[i].firstName, name) || !strcmp(bills[i].lastName, name))
            break;
    }
    return i == totalBills ? -1 : i;
}

void searchByDate(struct Date d)
{
    for (int i = 0; i < totalBills; i++)
    {
        if (bills[i].date.day == d.day && bills[i].date.month == d.month && bills[i].date.year == d.year)
            displayBill(bills[i]);
    }
    char c;
    printf("\n\n\nEnter any char to exit: ");
    scanf(" %c", &c);
}

int searchByBillNumber(int billNum)
{
    int i = 0;
    for (; i < totalBills; i++)
    {
        if (bills[i].billNo == billNum)
            break;
    }
    return i == totalBills ? -1 : i;
}
void searchBills()
{
    int choice;
    printf("\e[1;1H\e[2J");
    printf("\033[1m");
    printf("\n\n\t\t\t\tSearch By:-\n");
    printf("\033[0m");

    printf("\n\t\t\t1. First or Last Name");
    printf("\n\t\t\t2. Date");
    printf("\n\t\t\t3. Bill Number");

    printf("\n\n\t\t\tEnter your choice: ");
    scanf("%d", &choice);
    char string[50];
    int billNum, index;
    struct Date searchDate;
    switch (choice)
    {
    case 1:
        printf("Enter first name/last name to find: ");
        scanf("%s", string);
        index = searchByName(string);
        if (index < 0)
        {
            printf("\n\t\tNo first name or last name found with %s.\n", string);
            printf("\n\n\n\t\t\t Enter any character to exit: ");
            scanf("%s", string);
            break;
        }
        displayBill(bills[index]);
        printf("\n\n\n\t\t\t Enter any character to exit: ");
        scanf("%s", string);
        break;
    case 2:
        printf("Enter date (dd mm yyyy): ");
        scanf("%d%d%d", &searchDate.day, &searchDate.month, &searchDate.year);
        searchByDate(searchDate);
        break;
    case 3:
        printf("Enter Bill Number: ");
        scanf("%d", &billNum);
        index = searchByBillNumber(billNum);
        if (index < 0)
        {
            printf("\n\t\tNo Bill number found with %d.\n", billNum);
            printf("\n\n\n\t\t\t Enter any character to exit: ");
            scanf("%s", string);
            break;
        }
        displayBill(bills[index]);
        printf("\n\n\n\t\t\t Enter any character to exit: ");
        scanf("%s", string);
        break;
    }
}

void deleteByShifting(int index)
{
    for (int i = index; i < (totalBills - 1); i++)
    {
        bills[i] = bills[i + 1];
    }
    totalBills--;
}

void deleteBill()
{
    int choice;
    printf("\e[1;1H\e[2J");
    printf("\033[1m");
    printf("\n\n\t\t\t\tDelete By:-\n");
    printf("\033[0m");

    printf("\n\t\t\t1. First or Last Name");
    printf("\n\t\t\t2. Bill Number");

    printf("\n\n\t\t\tEnter your choice: ");

    scanf("%d", &choice);

    if (choice == 1)
    {
        char string[50];
        printf("\nEnter first or last name: ");
        scanf("%s", string);
        int index = searchByName(string);
        if (index == -1)
            printf("\nNo first or last name found");
        else
        {
            displayBill(bills[index]);
            printf("\n\a\t\tEnter 0 to confirm delete: ");
            scanf("%d", &choice);
            if (choice == 0)
            {
                deleteByShifting(index);
                deleteBillFromFiles(index);
            }
        }
    }
    else if (choice == 2)
    {
        int billNum;
        printf("\nEnter Bill number: ");
        scanf("%d", &billNum);
        int index = searchByBillNumber(billNum);
        if (index == -1)
            printf("\nNo such bill number found");
        else
        {
            displayBill(bills[index]);
            printf("\n\a\t\tEnter 0 to confirm delete: ");
            scanf("%d", &choice);
            if (choice == 0)
            {
                deleteByShifting(index);
                deleteBillFromFiles(index);
            }
        }
    }
    else
    {
        printf("Invalid choice");
    }
    addAllBills();
}
void manager(int choice, int *exit)
{
    switch (choice)
    {
    case 1:
        createNewBill();
        break;
    case 2:
        showAllBills(bills, totalBills);
        break;
    case 3:
        searchBills();
        break;
    case 4:
        deleteBill();
        break;
    case 5:
        addAllBills();
        *exit = 1;
        break;
    default:
        printf("Invalid choice");
        break;
    }
}

/* FILES RELATED FUNCTIONS */
void putStringAtCenterInFile(char string[], int totalChar, FILE *file)
{
    int spacesForName = totalChar - strlen(string);
    spacesForName /= 2;
    for (int j = 0; j < spacesForName; j++)
        fprintf(file, " ");
    fprintf(file, "%s", string);
    for (int j = 0; j < spacesForName; j++)
        fprintf(file, " ");
    if ((totalChar - strlen(string)) % 2 != 0)
        fprintf(file, " ");
}

void createNewInvoice(int index)
{
    char fileName[200] = "./Bills/";
    char temp[50];
    sprintf(temp, "%d", bills[index].billNo);
    strcat(fileName, temp);
    strcat(fileName, "_");
    strcat(fileName, bills[index].firstName);
    strcat(fileName, "_");
    strcat(fileName, bills[index].lastName);
    strcat(fileName, "_");
    sprintf(temp, "%d", bills[index].date.day);
    strcat(fileName, temp);
    strcat(fileName, "_");
    sprintf(temp, "%d", bills[index].date.month);
    strcat(fileName, temp);
    strcat(fileName, "_");
    sprintf(temp, "%d", bills[index].date.year);
    strcat(fileName, temp);
    strcat(fileName, ".txt");

    FILE *file = fopen(fileName, "w");

    int netTotal = 0;
    float gst;
    fprintf(file, "\n\t\t\t\t\tKSJ CAFE\n");
    fprintf(file, "\n---------------------------------------INVOICE---------------------------------------");
    fprintf(file, "\n\t Name: %s %s\n", bills[index].firstName, bills[index].lastName);
    fprintf(file, "\t Date: %d/%d/%d       Bill No. %d", bills[index].date.day, bills[index].date.month, bills[index].date.year, bills[index].billNo);
    fprintf(file, "\n-------------------------------------------------------------------------------------\n");
    fprintf(file, "                       Item Name                     |   Qty   |   Rate   |  Amount  ");
    fprintf(file, "\n-------------------------------------------------------------------------------------\n");
    for (int i = 0; i < bills[index].totalItems; i++)
    {
        putStringAtCenterInFile(bills[index].items[i].name, 53, file);
        fprintf(file, "|");

        sprintf(temp, "%d", bills[index].items[i].quantity);
        putStringAtCenterInFile(temp, 9, file);
        fprintf(file, "|");
        sprintf(temp, "%d", bills[index].items[i].pricePerItem);
        putStringAtCenterInFile(temp, 10, file);
        fprintf(file, "|");
        int total = bills[index].items[i].quantity * bills[index].items[i].pricePerItem;
        netTotal += total;
        sprintf(temp, "%d", total);
        putStringAtCenterInFile(temp, 11, file);
        fprintf(file, "\n");
        fprintf(file, "-------------------------------------------------------------------------------------\n");
    }

    fprintf(file, "                                                                Net Total:   ");
    sprintf(temp, "%d", netTotal);
    putStringAtCenterInFile(temp, 10, file);
    fprintf(file, "\n");
    gst = netTotal * (gstPercent / 100);
    fprintf(file, "                                                        -----------------------------\n");
    fprintf(file, "                                                                SGST@%.2f   ", gstPercent);
    sprintf(temp, "%.2f", gst);
    putStringAtCenterInFile(temp, 12, file);
    fprintf(file, "\n");
    fprintf(file, "                                                                CGST@%.2f   ", gstPercent);
    putStringAtCenterInFile(temp, 12, file);
    fprintf(file, "\n");
    fprintf(file, "                                                        -----------------------------\n");
    float grandTotal = netTotal + (gst * 2);
    fprintf(file, "                                                               Grand Total: ");
    sprintf(temp, "%.2f", grandTotal);
    putStringAtCenterInFile(temp, 10, file);
    fprintf(file, "\n");
    fprintf(file, "-------------------------------------------------------------------------------------\n");

    fclose(file);
}

void addAllBills()
{
    FILE *file = fopen("data.txt", "w");
    fprintf(file, "%d\n", totalBills);

    for (int i = 0; i < totalBills; i++)
    {
        fprintf(file, "%d_%d_%d  %d", bills[i].date.day, bills[i].date.month, bills[i].date.year, bills[i].billNo);
        fprintf(file, " %s %s", bills[i].firstName, bills[i].lastName);
        fprintf(file, "  %d  ", bills[i].totalItems);
        for (int j = 0; j < bills[i].totalItems; j++)
            fprintf(file, "%s %d %d ", bills[i].items[j].name, bills[i].items[j].quantity, bills[i].items[j].pricePerItem);
        fprintf(file, "\n");
    }

    fclose(file);
}

void readAllBills()
{

    FILE *file = fopen("data.txt", "r");
    fscanf(file, "%d\n", &totalBills);
    for (int i = 0; i < totalBills; i++)
    {
        fscanf(file, "%d_%d_%d  %d", &bills[i].date.day, &bills[i].date.month, &bills[i].date.year, &bills[i].billNo);
        fscanf(file, " %s %s", bills[i].firstName, bills[i].lastName);
        fscanf(file, "  %d  ", &bills[i].totalItems);
        for (int j = 0; j < bills[i].totalItems; j++)
            fscanf(file, "%s %d %d ", bills[i].items[j].name, &bills[i].items[j].quantity, &bills[i].items[j].pricePerItem);
        fscanf(file, "\n");
    }
    fclose(file);
}

void deleteBillFromFiles(int index)
{
    char fileName[200] = "./Bills/";
    char temp[50];
    sprintf(temp, "%d", bills[index].billNo);
    strcat(fileName, temp);
    strcat(fileName, "_");
    strcat(fileName, bills[index].firstName);
    strcat(fileName, "_");
    strcat(fileName, bills[index].lastName);
    strcat(fileName, "_");
    sprintf(temp, "%d", bills[index].date.day);
    strcat(fileName, temp);
    strcat(fileName, "_");
    sprintf(temp, "%d", bills[index].date.month);
    strcat(fileName, temp);
    strcat(fileName, "_");
    sprintf(temp, "%d", bills[index].date.year);
    strcat(fileName, temp);
    strcat(fileName, ".txt");

    remove(fileName);
}