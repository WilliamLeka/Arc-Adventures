#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include <time.h>

#define FILEMAX 100
#define NAMEMAX 20
#define ATTACKARRAY 5
#define XAXIS 20
#define YAXIS 40
#define PLAYERHEALTHMAX 100

char userInput();
char generateMap();
char printMap();
char printArt(char filename[]);
char moveUp();
char moveRight();
char moveDown();
char moveLeft();
int tribeEncounter(int playerDamage[],int *playerHealth,int selectedClass);
int barbarianEncounter(int playerDamage[],int *playerHealth,int selectedClass);
void healthEncounter(int *playerHealth,char filename[]);
void gateEncounter(char filename[]);


char mapArea[XAXIS][YAXIS]; // map
int px = 10, py = 20; // player location
char obstacleFound; // obstacles 

int main() 
{
    int gameEnd = 0; // gameEnd 0 = main loop keeps looping, gameEnd 1 = End main loop

    char filename[FILEMAX]; // holds ASCII ART 

    // Player Variables
    char playerName[NAMEMAX];
    int playerHealth = PLAYERHEALTHMAX;
    int selectedClass;

    char input;
    char errorCheck;
    int error;
    int i;

    // Class Damage Arrays 
    int knightDamage[ATTACKARRAY] = {20,40,50,60,70};
    int wizardDamage[ATTACKARRAY] = {20,40,50,60,70};
    

    // main loop
    while (gameEnd == 0)
    {
        // Print ASCII ART from file arcAdventures.txt
        strcpy(filename, ".\\ASCII\\arcAdventures.txt");
        printArt(filename);
        printf("Welcome to Arc-Adventures text based adventure game\n");
        
        // Start game
        while (input != 's')
        {
            printf("Please press S to start the game:\n");
            input = userInput();
        } // end while

        
        // Input character name
        do
        {
            error = 0; // used if error is found
            
            // get user input
            printf("Please enter your player's name:\n");
            fgets(playerName, NAMEMAX, stdin);
            strlwr(playerName);


            i=1;
            // Loops through playername character by character
            while (playerName[i] != '\0')
            {
                // checks if playerName character is letter, returns 0 if not letter
                if (isalpha(playerName[i-1]) == 0)
                {
                    error = 1;
                    printf("Please only use letters.\n");
                } // end if
                i++;
            } // end while 
        } while (error == 1); // end do while
        

        do
        {
            // MENU
            do
            {
                printf("Pick your Class:\n");
                printf("1: Wizard \n");
                printf("2: Knight \n");
                selectedClass = 1;
                scanf("%d", &selectedClass);
                scanf("%c", &errorCheck);

                if (selectedClass < 1 || selectedClass > 2)
                {
                    printf("Please select from the available classes\n");
                    printf("\n");
                } // end if
                
            } while (selectedClass < 1 || selectedClass > 2 ); // end do while
            
            
            
            switch (selectedClass)
            {
                case 1:
                {
                    
                    printf("You have selected The Wizard\n");
                    // print ASCII ART wizard
                    strcpy(filename, ".\\ASCII\\wizard.txt"); 
                    printArt(filename);
                    error = 0; // selected class successfully
                    break;
                } // end case 1

                case 2:
                {
                    printf("You have selected The Knight\n");
                    // print ASCII ART knight
                    strcpy(filename, ".\\ASCII\\knight.txt");
                    printArt(filename);
                    error = 0; // selected class successfully
                    break;
                } // end case 2
                
                default:
                {
                    printArt("Error");
                    error = 1;
                    break;
                } // end default

            } // end switch
            

        } while (error != 0); // end do while (class pick)
        
        generateMap(); // Function that generates map
        printMap(); // prints map

        // Main Game Loop
        while (playerHealth > 0)
        {
            input = userInput();

            switch (input)
            {
                case 'w':
                {
                    moveUp();
                    break;
                } // end case move up

                case 'd':
                {
                    moveRight();
                    break;
                } // end case move right

                case 's':
                {
                    moveDown();
                    break;
                } // end case move down

                case 'a':
                {
                    moveLeft();
                    break;
                } // end case move left
                
                default:
                {
                    printf("Error\n");
                    break;
                } // end default
                
            } // end switch

            switch (obstacleFound)
            {
                // IF tribe is encountered
                case 'T':
                {
                     // IF wizard class is chosen
                    if (selectedClass = 1)
                    {
                        gameEnd = tribeEncounter(wizardDamage, &playerHealth, selectedClass);
                    } // end if

                    // IF knight class is chosen
                    else if(selectedClass == 2)
                    {
                        gameEnd = tribeEncounter(knightDamage, &playerHealth, selectedClass);
                    } // end else if
                    break;

                } // end case 'T' tribeEncounter

                // IF barbarian is encountered
                case 'B':
                {
                    // IF wizard class is chosen
                    if (selectedClass = 1)
                    {
                        gameEnd = barbarianEncounter(wizardDamage, &playerHealth, selectedClass);
                    } // end if

                    // IF knight class is chosen
                    else if(selectedClass == 2)
                    {
                        gameEnd = barbarianEncounter(knightDamage, &playerHealth, selectedClass);
                    } // end else if
                    break;
                } // end case 'B' barbarianEncounter

                // IF health node is encountered
                case 'H':
                {
                    healthEncounter(&playerHealth,filename);
                    break;
                } // end case 'H' healthEncounter

                case '_':
                case '|':
                {
                   gateEncounter(filename);
                   break;
                } // end case '_', '|' gateEncounter
                
            
                default:
                {
                    break;
                } // end default

            } // end switch

            printMap(); // print map

        } // while game loop
    
    } // end main while
    
} // end main





// Function that generates new map when gate is encountered
void gateEncounter(char filename[]) 
{
    // print gate ASCII ART
    strcpy(filename,".\\ASCII\\gate.txt");
    printArt(filename);

    
    printf("-----------------\n");
    printf("You have discovered a new area!\n");
    printf("New map has been generated!\n");
    printf("-----------------\n");

    // IF gate is found on the x coord
    if (obstacleFound == '_')
    {
        // IF gate is found on x coord 0
        if (px == 0)
        {
            px += 19; // spawn player on opposite side of x coord in the new map
            px--;
        } // end if


        // IF gate is found on x coord 19
        else 
        {
            px -=19; // spawn player on opposite side of x coord in the new map
            px++;
        } // end else
        
    } // end if
    
    // IF gate is found on the y coord
    else 
    {
        // IF gate is found on y coord 0
        if (py == 0)
        {
            py += 39; // spawn player on opposite side of y coord in the new map
            py--;
        } // end if
        
        // IF gate is found on y coord 39
        else 
        {
            py -= 39; // spawn player on opposite side of y coord in the new map
            py++;
        } // end else

    } // end else

    generateMap(); // generate new map
    mapArea[px][py] = 'P'; // replace players current position

} // end gateEncounter Function





// Function when player moves onto a health node
void healthEncounter(int *playerHealth,char filename[]) 
{
    // Random generate health found
    srand(time(NULL));
    int health = rand() % 50 + 10;
    
    // Add randomly generated health to player health
    *playerHealth += health;

    // print health ASCII ART
    strcpy(filename, ".\\ASCII\\health.txt");
    printArt(filename);


    printf("-----------------\n");
    // IF player health goes over 100 bring health down to health max
    if (*playerHealth > PLAYERHEALTHMAX)
    {
        *playerHealth = PLAYERHEALTHMAX;
    } // end if
    
    //print Health increase by and total health after increase
    printf("Your health has increased by %d points\n", health);
    if (*playerHealth == PLAYERHEALTHMAX)
    {
        printf("Max health has been reached!\n");
    } // end if
    
    printf("Total Health: %d\n", *playerHealth);
    printf("-----------------\n");

} // end healthEncounter Function





// Function when player moves onto a barbarian node
int barbarianEncounter(int playerDamage[],int *playerHealth,int selectedClass) 
{
    char input;
    char filename[FILEMAX];
    int barbarianDamage[ATTACKARRAY] = {10,20,30,40,50};
    int barbarianHealth = 100;

    // prints barbarian ASCII ART
    strcpy(filename, ".\\ASCII\\barbarian.txt");
    printArt(filename);
    printf("You have encountered an Tribe Member!\n");

    // Fighting barbarian loop
    while (barbarianHealth > 0)
    {
        printf("-----------------\n");
        printf("Your Health: %d, barbarian Health: %d\n", *playerHealth, barbarianHealth);
        printf("-----------------\n");
        input = 0;
        while (input != 'd')
        {
            
            printf("Press D to attack\n");
            input = userInput();
        } // end while

        // Select random attack Index in playerDamage array
        srand(time(NULL));
        int attackIndex = rand() % 5;


            // Player attacks
            barbarianHealth = barbarianHealth - playerDamage[attackIndex];

            // IF barbarian health goes into minus, change into 0 so minus health is not printed
            if (barbarianHealth < 0)
            {
                barbarianHealth = 0;
            } // end if

            printf("-------------------------------------\n");
            printf("you took a strike!\n");
            printf("You did %d damage\n", playerDamage[attackIndex]);
            printf("enemy Health: %d\n", barbarianHealth);
            printf("-------------------------------------\n");
            printf("\n");


        // IF barbarian is still alive
        if (barbarianHealth > 0)
        {
            // Select random attack Index in barbarianDamage array
            srand(time(NULL));
            attackIndex = rand() % 5;

            
                    
            // barbarian attacks
            *playerHealth = *playerHealth - barbarianDamage[attackIndex];

            // IF player health goes into minus, change into 0 so minus health is not printed
            if (*playerHealth < 0)
            {
                *playerHealth = 0;
            } // end if

            printf("-------------------------------------\n");
            printf("You have been attacked!\n");
            printf("You took %d damage\n", barbarianDamage[attackIndex]);
            printf("Your Health: %d\n",*playerHealth);
            printf("-------------------------------------\n");
            printf("\n");
        } // end if
                    
                    
        // IF player dies
        if (*playerHealth <= 0)
        {
            *playerHealth = 0;
            printf("You DIED!\n");
            return 1; // return 1 to end game
        } // end if

        // ELSE IF barbarian dies
        else if (barbarianHealth <= 0)
        {
            printf("You WON!\n");
            return 0; // return 0 to continue game
        } // end if
                    
    } // end while

} // end Function barbarianEncounter





// Function when player moves onto a tribe node
int tribeEncounter(int playerDamage[],int *playerHealth,int selectedClass) 
{
    char input;
    char filename[FILEMAX];
    int tribeDamage[ATTACKARRAY] = {5,10,15,20,25};
    int tribeHealth = 75;

    // prints tribe ASCII ART
    strcpy(filename, ".\\ASCII\\tribe.txt");
    printArt(filename);
    printf("You have encountered an Tribe Member!\n");

    // Fighting Tribe loop
    while (tribeHealth > 0)
    {
        printf("-----------------\n");
        printf("Your Health: %d, tribe Health: %d\n", *playerHealth, tribeHealth);
        printf("-----------------\n");
        input = 0;
        while (input != 'd')
        {
            
            printf("Press D to attack\n");
            input = userInput();
        } // end while

        // Select random attack Index in playerDamage array
        srand(time(NULL));
        int attackIndex = rand() % 5;


            // Player attacks
            tribeHealth = tribeHealth - playerDamage[attackIndex];

            // IF tribe health goes into minus, change into 0 so minus health is not printed
            if (tribeHealth < 0)
            {
                tribeHealth = 0;
            } // end if

            printf("-------------------------------------\n");
            printf("you took a strike!\n");
            printf("You did %d damage\n", playerDamage[attackIndex]);
            printf("enemy Health: %d\n", tribeHealth);
            printf("-------------------------------------\n");
            printf("\n");


        // IF tribe is still alive
        if (tribeHealth > 0)
        {
            // Select random attack Index in tribeDamage array
            srand(time(NULL));
            attackIndex = rand() % 5;

            
                    
            // tribe attacks
            *playerHealth = *playerHealth - tribeDamage[attackIndex];

            // IF player health goes into minus, change into 0 so minus health is not printed
            if (*playerHealth < 0)
            {
                *playerHealth = 0;
            } // end if

            printf("-------------------------------------\n");
            printf("You have been attacked!\n");
            printf("You took %d damage\n", tribeDamage[attackIndex]);
            printf("Your Health: %d\n",*playerHealth);
            printf("-------------------------------------\n");
            printf("\n");
        } // end if
                    
                    
        // IF player dies
        if (*playerHealth <= 0)
        {
            *playerHealth = 0;
            printf("You DIED!\n");
            return 1; // return 1 to end game
        } // end if

        // ELSE IF tribe dies
        else if (tribeHealth <= 0)
        {
            printf("You WON!\n");
            return 0; // return 0 to continue game
        } // end if
                    
    } // end while

} // end Function tribeEncounter





// Moves player up
char moveUp() 
{
    

    // IF play tries to go outside map bounds
    if (px - 1 < 0)
    {
        mapArea[px][py] = 'P'; // replace players current position
        printf("Out of bounds\n");
    } // end if
    
    else
    {
        mapArea[px][py] = '.'; // replace players current position
        px--;// Move up
        obstacleFound = mapArea[px][py];
        mapArea[px][py] = 'P'; // place players new location
    }
} // end moveUp Function





// Moves player to the right
char moveRight() 
{
    

    // IF play tries to go outside map bounds
    if (py + 1 > 39)
    {
        mapArea[px][py] = 'P'; // replace players current position
        printf("Out of bounds\n");
    } // end if

    else 
    {
        mapArea[px][py] = '.'; // replace players current position
        py++; // Move right
        obstacleFound = mapArea[px][py];
        mapArea[px][py] = 'P'; // place players new location
    } // end else

} // end moveRight Function





// Moves player down
char moveDown() 
{
    

    // IF play tries to go outside map bounds
    if (px + 1 > 19)
    {
        mapArea[px][py] = 'P'; // replace players current position
        printf("Out of bounds\n");
    } // end if

    else
    {
        mapArea[px][py] = '.'; // replace players current position
        px++; // move Down
        obstacleFound = mapArea[px][py];
        mapArea[px][py] = 'P'; // place players new location
    } // end else

} // end moveDown Function





// Moves player to the left
char moveLeft() 
{
    
    // IF play tries to go outside map bounds
    if (py - 1 < 0)
    {
        mapArea[px][py] = 'P'; // replace players current position
        printf("Out of bounds\n");
    } // end if

    else 
    {
        mapArea[px][py] = '.'; // replace players current position
        py--; // move Left
        obstacleFound = mapArea[px][py];
        mapArea[px][py] = 'P'; // place players new location
    } // end else

} // end moveLeft Function





// GeneratesMap with nodes
char generateMap() 
{
    int x,y; // Coords for different nodes

    srand(time(NULL)); // Reset Random Number Generator
    int barbarianCount = rand() % 5 + 3; // Amount of barbarians located on a singular map

    srand(time(NULL)); // Reset Random Number Generator
    int tribeCount = rand() % 5 + 3; // Amount of tribes located on a singular map

    srand(time(NULL)); // Reset Random Number Generator
    int healthCount = rand() % 2 + 3; // Amount of health located on a singular map

    // Fill map with blank spots
    for (int i = 0; i < XAXIS; i++)
    {
        for (int j = 0; j < YAXIS; j++)
        {
            mapArea[i][j] = '.';
        } // end inner for
            
    } // end outter for
    
    
    srand(time(NULL)); // reset Random number generator for x and y variables
    //Place barbarian nodes randomly around map
    for (int i = 0; i < barbarianCount; i++)
    {
        x = rand() % 10; // first 10 rows only
        y = rand() % 40;
        mapArea[x][y] = 'B';
    } // end for



    srand(time(NULL)); // reset Random number generator for x and y variables
    //Place Tribe nodes randomly around map
    for (int i = 0; i < tribeCount; i++)
    {
        x = rand() % 10 +10; // last 10 rows only
        y = rand() % 40;
        mapArea[x][y] = 'T';
    } // end for


    srand(time(NULL)); // reset Random number generator for x and y variables
    //Place health nodes randomly around map
    for (int i = 0; i < healthCount; i++)
    {
        x = rand() % 20;
        y = rand() % 40;
        mapArea[x][y] = 'H';
    } // end for

       
   
    srand(time(NULL)); // reset Random number generator for x and y variables
    x = rand() % 20;
    y = rand() % 40;

    //Generate gate nodes

    // if x number is generated to be 0 or 19
    if (x == 0  || x == 19)
    {
        mapArea[x][y] = '_';
    } // end if

    // if y number is generated to be 0 or 30
    else 
    {
        y = rand() % 2; // rand number 0 = left wall of the map, rand number 1 = right wall of the map

        // IF y coord is 1
        if (y == 1)
        {
            y = 39; // right side of map
        } // end if

        mapArea[x][y] = '|';
            
    } // end else
    
    mapArea[px][py] = 'P'; // Place player at px and py location map (center of map)

} // end generateMap Function





// Prints map to console
char printMap() 
{
    for (int i = 0; i < XAXIS; i++)
    {
        for (int j = 0; j < YAXIS; j++)
        {
            printf("%c", mapArea[i][j]);
        } // end inner for
        printf("\n");
            
    } // end outter for
    printf("\n");
} // end printMap Function





// Gets users inputs to perform actions
char userInput() 
{
    // getche is used to get input from user without enter key having to be pressed

    char userInput = 0;

    while(userInput == 0) 
    {
        userInput = getche();
        printf("\n");
    } // end while

    userInput = userInput | 32; // Force lowercase ASCII
    return userInput;
} // end UserInput Function





// Prints ASCII Art
char printArt(char filename[]) 
{
    FILE *fptr;
    int c;

    // Open file
    fptr = fopen(filename, "r");
    if (fptr == NULL)
    {
        printf("Cannot open file \n");
        exit(0);
    } // end if
  
    // Read contents from file
    c = fgetc(fptr);
    while (c != EOF)
    {
        printf ("%c", c);
        c = fgetc(fptr);
    } // end while
    printf ("\n");

    fclose(fptr);
} // end printArt Function

