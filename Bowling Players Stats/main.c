/*

 Name: Vinay Sitaram Kanse
 Batch: F2
 Date: 7 Dec 2021
 */
/* QUESTION:
Program to declare an array of structure `players` having data members (name, total
matches played, best bowling figure). Program should do the following operations
using functions.
a. Insert Minimum 5 player data in array of structure
b. Sort and display this data in descending order of their best bowling figure (if
wickets are same then consider less run conceded as priority) and in proper
tabular form
c. Delete the data for any one player.
d. Search for a particular player using its name.
*/
#include <stdio.h>
#include <string.h>
// #include <wmmintrin.h>
// Player Struct
struct Player
{
    char name[20];
    int totalMatches;
    int wickets;
    int runs;
};

// Global Variables
struct Player players[200];
int totalPlayersAdded = 0;

// Function Prototypes
void insertPlayers();
void displayPlayers();
int searchPlayerIndex(char name[]);
void deletePlayer();
void searchPlayer();

int main()
{
    int choice;
    int closeProgram = 0;
    while (closeProgram != 1)
    {
        printf("\e[1;1H\e[2J");
        // system("clear");
        printf("\n\t\t\t------BOWLING PLAYERS STATS------\n\n\n");
        printf("\t\t\t\t### MENU ###");
        printf("\n\n\t\t\t\t1. Insert\n\t\t\t\t2. Display\n\t\t\t\t3. Delete\n\t\t\t\t4. Search\n\t\t\t\t5. Exit");
        printf("\n\n\tEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            insertPlayers();
            break;
        case 2:
            displayPlayers(players, totalPlayersAdded);
            break;
        case 3:
            deletePlayer();
            break;
        case 4:
            searchPlayer();
            break;
        case 5:
            closeProgram = 1;
            break;
        default:
            printf("\nEnter valid choice");
            break;
        }
    }

    return 0;
}

void insertPlayers()
{
    printf("\e[1;1H\e[2J");
    int noOfPlayers;
    printf("\nEnter Number of players to be added: ");
    scanf("%d", &noOfPlayers);
    for (int i = 0; i < noOfPlayers; i++)
    {
        printf("Enter name of Player %d: ", i + 1);
        scanf("%s", players[i].name);
        printf("Enter Total Matches played by Player %d: ", i + 1);
        scanf("%d", &players[i].totalMatches);
        printf("Enter Wickets taken by Player %d: ", i + 1);
        scanf("%d", &players[i].wickets);
        printf("Enter Runs Given by Player %d: ", i + 1);
        scanf("%d", &players[i].runs);
        totalPlayersAdded++;
    }
}

void displayPlayers(struct Player players[], int playerLength)
{
    char quit[5];
    printf("\e[1;1H\e[2J");
    printf("|         NAME        |Total Matches Played|   Wickets Taken    |     Runs Given     |\n");
    printf("---------------------------------------------------------------------------------------\n");

    for (int i = 0; i < playerLength; i++)
    {
        printf("   ");
        char list[4][20];
        sprintf(list[0], "%s", players[i].name);
        sprintf(list[1], "%d", players[i].totalMatches);
        sprintf(list[2], "%d", players[i].wickets);
        sprintf(list[3], "%d", players[i].runs);
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 20; k++)
            {
                if (k <= strlen(list[j]))
                    printf("%c", list[j][k]);
                else if (k > strlen(list[j]))
                    printf(" ");
            }
            printf("|");
        }
        printf("\n");
    }
    printf("\n\t\tTo Go back to menu type any character and enter: ");
    scanf("%s", quit);
}

int searchPlayerIndex(char name[])
{
    int i = 0;
    for (; i < totalPlayersAdded; i++)
    {
        if (!strcmp(name, players[i].name))
            return i;
    }
    return -1;
}

void deletePlayer()
{
    printf("\e[1;1H\e[2J");
    while (1)
    {
        char name[20];

        printf("\n\t\tEnter name of player to delete his data from list \n\t\t\tEnter 0 to quit and return to Menu: ");
        scanf("%s", name);
        if (name[0] == '0')
            break;
        int deleteIndex = searchPlayerIndex(name);
        if (deleteIndex < 0)
            printf("No player with %s  name found.", name);
        else
        {
            for (int i = deleteIndex; i < totalPlayersAdded - 1; i++)
            {
                players[i] = players[i + 1];
            }
            totalPlayersAdded--;
        }
    }
}

void searchPlayer()
{
    printf("\e[1;1H\e[2J");
    char playerName[20];
    while (1)
    {
        printf("\nEnter player name to search\nTo quit enter 0: ");
        scanf("%s", playerName);
        if (playerName[0] == '0')
            break;
        int index = searchPlayerIndex(playerName);
        if (index < 0)
            printf("\nNo player with %s name found.", playerName);
        else
        {
            struct Player _players[1] = {players[index]};
            displayPlayers(_players, 1);
        }
    }
}