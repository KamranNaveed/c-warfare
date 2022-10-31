#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <windows.h>

#define sizey 26 // BEST from tial and error
#define sizex 23 // BEST form trial and error
static HANDLE hOut;
char Map;

void gotoxy(int x, int y);            // Function to move position of cursor.
void setCursorPosition(int x, int y); // Function used in reduction of flickering when updating console

int GameLoop(char left, char right, char fire, char pause, char difficulty, char Map); // Actual Game, returns victory integer
char DisplayMap(void);                                                                 // Displays Map selection screen and returns the option entered by user

void DisplayWorld(char a[][sizex], int score);                          // Prints game world or map
void DisplayMainMenu(void);                                             // Prints Main Menu
void printControls(char up, char down, char fire);                      // Prints 'Controls' screen
void DisplaySettingsScreen(void);                                       // Prints 'Settings' screen
void DisplayInstructionScreen(void);                                    // Prints 'Instructions' screen
void DisplayEndScreen(int victory, int totalEnemies, int i, int score); // Displays screens seen when the game ends
void UpdateMessage(void);                                               // Blinks an update message on the console
void DisplayMovingTitleScreen(void);                                    // Initial screen where title moves upward to reveal Main Menu
void DisplayWelcomeMessages(void);                                      // Displays welcome messages when user starts the  game
void PrintTitle(void);                                                  // Prints title of game
void PrintTitleWithoutDelay(void);                                      // Prints title of game without delays

int main()
{
    /*This code enables Full Screen Mode*/
    COORD Coord;
    SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, &Coord);

    /*Messages for the player*/
    Sleep(2000); // This function causes delays in output. Useful for printing messages and creating animation effects
    printf("\n\n\n\n\n\t\tPlease maximise screen completely for the best experience.");
    Sleep(4000);

    system("cls");
    Sleep(1500);
    gotoxy(75, 10);
    printf("WELCOME!");
    Sleep(2500);
    gotoxy(50, 21);
    printf("YOU ARE ABOUT TO PLAY C WARFARE, A SPACE INVADERS CLONE GAME.");
    Sleep(2500);
    gotoxy(10, 30);
    printf("\n\n\n\t\tMADE BY:\n\n\n\t\tKamran Naveed Syed\n\n\n");
    Sleep(3000);
    system("cls");
    gotoxy(79, 25);
    Sleep(5000);
    gotoxy(65, 20);
    printf("YOUR SOFTWARE HAS BEEN RIDDLED WITH BUGS.");
    gotoxy(64, 28);
    Sleep(2500);
    printf("FIGHT THEM, AND SAVE YOUR OS FROM CRASHING.");
    Sleep(2500);
    system("cls");
    Sleep(3000);

    /*Initialise variables*/

    char difficulty = '1'; // difficulty of game
    int previous = 1;
    int again;
    char try_again;

    /*Default Movement keys*/
    char left = 'a';  // Left Key
    char right = 'd'; // Right Key
    char fire = 'w';  // Fire Key
    char pause = 'p'; // Pause key

    /*Creates welcome screen*/
    DisplayMovingTitleScreen();

    /*Select option from menu*/
    fflush(stdin);                // Clears input buffer
    char SelectOption = _getch(); // Input the selection from main menu entered by user

    /*Take action according to input*/
    while (SelectOption != '0') // As long as user does not press 0 to exit game, sentinel controlled loop for selection from main menu
    {
        switch (SelectOption) // Decides what action is to be taken according to user selection
        {

        case '1': // START GAME
        {
            system("cls"); // Clears system
            /*Start Game*/
            Sleep(500);
            Map = DisplayMap(); // User asked for Map selection
            while (Map != '0')
            {
                if (Map == '1' || Map == '2' || Map == '3' || Map == '4')
                {
                    system("cls");
                    DisplayWelcomeMessages();                                    // Displays welcome messages at start of the game
                    again = GameLoop(left, right, fire, pause, difficulty, Map); // Game loop returns status of victory
                    while (again == 0)                                           // As long as user loses, sentinel loop for playing again
                    {
                        /*Print 'Try Again' message*/
                        system("cls");
                        gotoxy(78, 20);
                        printf(" TRY AGAIN?");
                        gotoxy(74, 29);
                        printf("1.  YES\t 2.  NO");
                        try_again = _getch();                  // User selection, if they want to play again
                        while (try_again == '1' && again == 0) // yes
                        {
                            system("cls");
                            again = GameLoop(left, right, fire, pause, difficulty, Map);
                            system("cls");
                            if (again == 1)
                            {
                                break;
                            } // game starts again
                            if (again == 0)
                            {

                                gotoxy(78, 20);
                                printf(" TRY AGAIN?");
                                gotoxy(74, 29);
                                printf("1.  YES\t 2.  NO");
                                try_again = _getch();
                            }
                        }

                        system("cls");
                        Map = DisplayMap();
                        if (try_again == '2')
                            break; // return to Map selection
                    }

                    while (again == 1) // As long as user wins
                    {
                        system("cls");
                        Map = DisplayMap(); // Jump straight back to Map selection screen
                        if (Map == '0')     // Exit to main menu if user presses 0
                            goto loop1;
                        else if (Map != '1' && Map != '2' && Map != '3' && Map != '4' && Map != '5')
                        {
                            break; // Get Map again if user enters invalid input
                        }
                        /*Starts game again if user wants to play and selects another or same Map*/
                        system("cls");
                        DisplayWelcomeMessages();
                        again = GameLoop(left, right, fire, pause, difficulty, Map);
                    }
                }

                if (Map != '1' || Map != '2' || Map != '3' || Map != '4')
                {
                    system("cls");
                    Map = DisplayMap();
                }
            }

            break; // Enables printing of main menu when user returns from a selection screen
        }

        case '2': // CONTROLS
        {
            system("cls");
            Sleep(900);
            printControls(left, right, fire); // Prints current controls
            char leave = _getch();            // Get user input for what key they want to change
            while (leave != '0')              // As long as user does not press 0, sentinel loop for exiting
            {
                /*Print message according to their selection*/
                if (leave == '1')
                {
                    printf("\n\n\n\n\n\t\t\t\t\t\t\t\t\t Select key for LEFT\t");
                    left = _getch();
                    /*update screen when user selects desired key*/
                    UpdateMessage();
                    printControls(left, right, fire);
                }

                else if (leave == '2')
                {
                    /*Print message according to their selection*/

                    printf("\n\n\n\n\n\t\t\t\t\t\t\t\t\t Select key for RIGHT\t");
                    right = _getch();
                    /*update screen when user selects desired key*/

                    UpdateMessage();
                    printControls(left, right, fire);
                }
                else if (leave == '3')
                {
                    /*Print message according to their selection*/

                    printf("\n\n\n\n\n\t\t\t\t\t\t\t\t\t Select key for FIRE\t");
                    fire = _getch();
                    /*update screen when user selects desired key*/

                    UpdateMessage();
                    printControls(left, right, fire);
                }

                else
                {
                    system("cls");
                    printControls(left, right, fire); // If user presses wrong key, Print the screen again instantaneously, gives the effect that nothing has happened
                }
                fflush(stdin);    // Clear input buffer
                leave = _getch(); // Next input
            }

            break;
        }
        case '3': // SETTINGS
        {
            system("cls");
            Sleep(900);
            DisplaySettingsScreen(); // Displays setting screen
            if (previous == 1)
            {
                printf("\n\n\n\t\t\t\t\t\t\t\t     Current Difficulty Mode: EASY\n\n");
            }

            else if (previous == 2)
            {
                printf("\n\n\t\t\t\t\t\t\t\t   Current Difficulty Mode: MEDIUM\n\n");
            }
            else if (previous == 3)
            {
                printf("\n\n\t\t\t\t\t\t\t\t      Current Difficulty Mode: HARD\n\n");
            }

            fflush(stdin);
            difficulty = _getch(); // Get users input, what do they want to select?

            while (difficulty != '0') // as long as user does not press zero, sentinel loop for exiting
            {

                /*Take action according to users input*/

                if (difficulty == '1')
                {
                    UpdateMessage();
                    DisplaySettingsScreen();

                    printf("\n\n\n\t\t\t\t\t\t\t\t     Current Difficulty Mode: EASY\n\n");
                    previous = 1;
                }

                else if (difficulty == '2')
                {
                    UpdateMessage();
                    DisplaySettingsScreen();

                    printf("\n\n\t\t\t\t\t\t\t\t      Current Difficulty Mode: MEDIUM\n\n");

                    previous = 2;
                }
                else if (difficulty == '3')
                {
                    UpdateMessage();
                    DisplaySettingsScreen();

                    printf("\n\n\t\t\t\t\t\t\t\t      Current Difficulty Mode: HARD\n\n");
                    previous = 3;
                }

                difficulty = _getch();
            }

            break;
        }
        case '4': // INSTRUCTIONS
        {
            system("cls");
            DisplayInstructionScreen(); // Pprints Instructions screen
            printf("\n\n\n\t\tPress any key to exit to main menu.");
            _getch();
            break;
        }

        default:
            break;
        }
    loop1:
    resume:
        system("cls");
        DisplayMainMenu();       // Everytime a user presses 0 on a selection screen, he returns to main menu
        SelectOption = _getch(); // Asks user his next choice
    }
    system("cls");
    Sleep(1000);
    gotoxy(72, 25);
    printf("You chose to exit the game!"); // Exit the game when user presses 0 while on main menu
    Sleep(2500);
}

void DisplayWorld(char a[][sizex], int score) // Function prints game world
{
    printf("\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t       SCORE:    %d", score);

    printf("\n\n\n\n\n\n\n\t\t\t\t\t");
    for (int y = 0; y < sizey; y++)
    {
        printf("\t\t\t\t|");
        for (int x = 0; x < sizex; x++)
        {
            printf("%c", a[y][x]);
        }
        printf("|");
        printf("\n\t\t\t\t\t");
    }
    return;
}
void DisplayMovingTitleScreen(void) // Function displays moving title at the start
{
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"); // print lines
    PrintTitle();                                     // print title
    Sleep(3000);
    system("cls");

    /*Moves the title upwards by printing one less line each time*/

    for (int i = 18; i >= 2; i--)
    {
        for (int j = i; j >= 0; j--)
        {
            printf("\n");
        }
        PrintTitleWithoutDelay();
        Sleep(40);
        system("cls");
        setCursorPosition(0, 0);
    }
    setCursorPosition(0, 0); // Function helps to avoid flicker by reprinting over existing screen with all changes
    printf("\n\n\n");
    PrintTitleWithoutDelay();

    /*Displays main menu  title reaches top */

    Sleep(1800);
    gotoxy(60, 21);
    printf("To select an option, press the number besides it.\n\n\n\n\n");
    gotoxy(70, 27);
    printf("\t1.\tSTART GAME");
    Sleep(80);
    gotoxy(70, 32);
    printf("\t2.\tCONTROLS");
    Sleep(80);
    gotoxy(70, 37);
    printf("\t3.\tSETTINGS");
    Sleep(80);
    gotoxy(70, 42);
    ;
    printf("\t4.\tINSTRUCTIONS");
    Sleep(80);
    gotoxy(73, 51);
    Sleep(2000);
    printf("  Press 0 to leave.\n\n");
    return;
}
void DisplayMainMenu(void) // Functin displays main menu
{
    printf("\n\n\n");
    PrintTitleWithoutDelay();
    gotoxy(60, 21);
    printf("To select an option, press the number besides it.\n\n\n\n\n");
    gotoxy(70, 27);
    printf("\t1.\tSTART GAME");
    gotoxy(70, 32);
    printf("\t2.\tCONTROLS");
    gotoxy(70, 37);
    printf("\t3.\tSETTINGS");
    gotoxy(70, 42);
    ;
    printf("\t4.\tINSTRUCTIONS");
    gotoxy(73, 51);
    printf("  Press 0 to leave.\n\n");

    return;
}

void DisplayEndScreen(int victory, int totalEnemies, int i, int score) // Displays screen when a game finishes
{
    if (victory == 1) // when user wins
    {
        system("cls");
        gotoxy(77, 15);
        printf("CONGRATULATIONS!");
        Sleep(1000);
        gotoxy(78, 20);
        printf(" SCORE: %d", score);
        Sleep(1500);
        int bonus = i / 7;
        gotoxy(80, 25);
        printf("Bonus: %d", bonus);
        Sleep(1500);
        gotoxy(77, 30);
        printf("TOTAL SCORE: %d", score + bonus);
        gotoxy(77, 35);
        printf("Well done");
        Sleep(1500);
        printf(", Hero.");
        Sleep(2000);
        gotoxy(68, 42);
        printf("Press any key to exit to Map selection.");
        _getch();
    }
    else if (victory == 0) // when user loses
    {
        gotoxy(80, 15);
        printf("YOU HAVE FAILED.");
        Sleep(1500);
        gotoxy(79, 20);
        printf("WINDOWS IS DOOMED!");
        Sleep(1500);
        gotoxy(80, 29);
        printf("FINAL SCORE: %d", score);
        Sleep(3500);
    }
    system("cls");
    return;
}

int GameLoop(char left, char right, char fire, char pause, char difficulty, char Map)
{

    /*Initialising all variables to be included*/
    int x, y, yi;
    char world[sizey][sizex]; // the world map

    /*Characters of the game*/
    char player = 'A';
    char playerLaser = '^';
    char enemy = 'M';
    char enemyShielded = 'O';
    char enemyLaser = 'U';
    char explosion = 'x';
    int score = 0;
    int victory = 1;
    int count_pause = 0;

    /*Variables to determine if enemy is ready to fire, i.e there is no other enemy infront of it*/
    int laserReady = 1, enemyReady = 0;

    /*initialise world*/
    int totalEnemies = 0;
    for (x = 0; x < sizex; x++)
    {
        for (y = 0; y < sizey; y++)
        {
            /*Change look of game world according to Map selected by user*/

            if (Map == '1') // MAP 1
            {
                // Prints a row of regular and a row of shielded enemies

                if ((y + 1) % 2 == 0 && y == 5 && x > 4 && x < sizex - 5 && x % 2 == 0)
                {
                    world[y][x] = enemy;
                    totalEnemies++;
                }
                else if ((y + 1) % 2 == 0 && ((y >= 7 && y < 9) || (y >= 5 && y < 6)) && x > 4 && x < sizex - 5 && x % 2 == 0)
                {
                    world[y][x] = enemyShielded;
                    totalEnemies = totalEnemies + 2;
                }
                else
                {
                    world[y][x] = ' ';
                }
            }

            if (Map == '2') // MAP 2
            {
                // prints two rows of Map 1

                if ((y + 1) % 2 == 0 && (y == 3 || y == 7) && x > 4 && x < sizex - 5 && x % 2 == 0)
                {
                    world[y][x] = enemy;
                    totalEnemies++;
                }
                else if ((y + 1) % 2 == 0 && ((y >= 7 && y < 11) || (y >= 1 && y <= 3)) && x > 4 && x < sizex - 5 && x % 2 == 0)
                {
                    world[y][x] = enemyShielded;
                    totalEnemies = totalEnemies + 2;
                }
                else
                {
                    world[y][x] = ' ';
                }
            }

            if (Map == '3') // MAP 3
            {
                // Prints first row shielded enemies, and regular enemies at the back
                if ((y + 1) % 2 == 0 && y < 7 && x > 4 && x < sizex - 5 && x % 2 == 0)
                {
                    world[y][x] = enemy;
                    totalEnemies++;
                }
                else if ((y + 1) % 2 == 0 && y >= 7 && y < 9 && x > 4 // for printing shielded enemies on the front line
                         && x < sizex - 5 && x % 2 == 0)
                {
                    world[y][x] = enemyShielded;
                    totalEnemies = totalEnemies + 2;
                }
                else
                {
                    world[y][x] = ' ';
                }
            }
            if (Map == '4') // MAP 4
                            // prints alternating rows of regular and shielded enemies
            {

                if ((y + 1) % 2 == 0 && (y == 3 || y == 7) && x > 4 && x < sizex - 5 && x % 2 == 0)
                {
                    world[y][x] = enemy;
                    totalEnemies++;
                }
                else if ((y + 1) % 2 == 0 && ((y >= 7 && y < 11) || (y >= 1 && y <= 5)) && x > 4 && x < sizex - 5 && x % 2 == 0)
                {
                    world[y][x] = enemyShielded;
                    totalEnemies = totalEnemies + 2;
                }
                else
                {
                    world[y][x] = ' ';
                }
            }
        }
    }
    world[sizey - 1][sizex / 2] = player; // Places player at bottom middle of world
    int i = 1;
    char direction = 'l'; // Default direction, move to left
    char keyPress;        // Gets key press
    int currentEnemies = totalEnemies;

    srand(time(NULL));

    system("cls");
    int enemySpeed;

    while (currentEnemies > 0 && victory) // While there are still any enemies left or if the player has won, sentinel loop for running game till it finishes
    {
        int drop = 0; // Are enemies ready to drop down?

        // Control enemy speed
        enemySpeed = 4 + 4 * currentEnemies / totalEnemies;

        laserReady++;

        /*display world*/
        setCursorPosition(0, 0); // Helps avoid flicker by reprinting updated world over existing world
        DisplayWorld(world, score);
        printf("\n\n\n\n\n\n\t\t\t\t\t\t\t\t\tPress 'p' to pause game.");

        /*laser time*/
        for (x = 0; x < sizex; x++)
        {
            for (y = sizey - 1; y >= 0; y--)
            {
                if ((i % 2 == 0) && world[y][x] == enemyLaser && (world[y + 1][x] != enemy || world[y + 1][x] != enemyShielded)) // If there is no enemy in front of an enemy laser, move it one space down
                {
                    world[y][x] = ' ';
                    world[y + 1][x] = enemyLaser;
                }
                else if ((i % 2 == 0) && world[y][x] == enemyLaser && (world[y + 1][x] == enemy || world[y + 1][x] == enemyShielded)) // If there is an enemy infront of an enemy laser, delete it
                {
                    world[y][x] = ' ';
                }
            }
        }

        for (x = 0; x < sizex; x++)
        {
            for (y = 0; y < sizey; y++)
            {
                if ((i % 5 == 0) && (world[y][x] == enemyShielded || world[y][x] == enemy) && (rand() % 15 > 13) && world[y + 1][x] != playerLaser) // Enemies shoot randomly (If generated number is greater than set number)
                {
                    for (yi = y + 1; yi < sizey; yi++) // loop runs from an enemy to the end of the map
                    {
                        if (world[yi][x] == enemy || world[yi][x] == enemyShielded) // if there is another enemy below an enemy in the column, then enemy not ready to shoot
                        {
                            enemyReady = 0;
                            break;
                        }
                        enemyReady = 1; // Otherwise enemy ready to shoot
                    }
                    if (enemyReady) // if enemy is ready, fire laser
                    {
                        world[y + 1][x] = enemyLaser;
                    }
                }
                if (world[y][x] == playerLaser && world[y - 1][x] == enemy) // If there is a player laser below an enemy, delete the enemy and print an explosion
                {
                    world[y][x] = ' ';
                    world[y - 1][x] = explosion;
                    currentEnemies--;
                    score += 50;
                }
                else if (world[y][x] == playerLaser && world[y - 1][x] == enemyShielded) // If there is a player laser below a shielded enemy, delete the shielded enemy and print a regular enemy
                {
                    world[y][x] = ' ';
                    world[y - 1][x] = enemy;
                    currentEnemies--;
                    score += 50;
                }
                else if (world[y][x] == playerLaser && world[y - 1][x] == enemyLaser) // Delete player laser and enemy laser if they collide (if enemy laser is one or two spaces above player laser)
                {
                    if (difficulty == '3') // For hard mode, never delete  enemy lasers
                    {
                        world[y][x] = ' ';
                    }
                    else if (difficulty == '1' || difficulty == '1') // otherwise do
                    {
                        world[y][x] = ' ';
                        world[y - 1][x] = ' ';
                    }
                }
                else if (world[y][x] == explosion) // delete an explosion
                {
                    world[y][x] = ' ';
                }
                else if ((i + 1) % 2 == 0 && world[y][x] == enemyLaser && world[y + 1][x] == player) // If there is an enemy laser above the player, the player dies
                {
                    world[y + 1][x] = explosion;
                    world[y][x] = ' ';
                    victory = 0;
                    break;
                }
                else if (world[y][x] == playerLaser && world[y - 1][x] != enemyLaser) // if there is not an enemy laser above player laser, player laser continues to move upward
                {
                    world[y][x] = ' ';
                    world[y - 1][x] = playerLaser;
                }
            }
        }

        /*update enemy direction*/
        for (y = 0; y < sizey; y++)
        {
            if (world[y][0] == enemy || world[y][0] == enemyShielded)
            {
                direction = 'r';
                drop = 1;
                break;
            }
            if (world[y][sizex - 1] == enemy || world[y][sizex - 1] == enemyShielded)
            {
                direction = 'l';
                drop = 1;
                break;
            }
        }

        /*update board*/
        if (i % enemySpeed == 0)
        {
            if (direction == 'l')
            {
                for (x = 0; x < sizex - 1; x++)
                {
                    for (y = 0; y < sizey; y++)
                    {
                        if (drop && (world[y - 1][x + 1] == enemy || world[y - 1][x + 1] == enemyShielded))
                        {
                            world[y][x] = world[y - 1][x + 1];
                            world[y - 1][x + 1] = ' ';
                        }
                        else if (!drop && (world[y][x + 1] == enemy || world[y][x + 1] == enemyShielded))
                        {
                            world[y][x] = world[y][x + 1];
                            world[y][x + 1] = ' ';
                        }
                    }
                }
            }
            else
            {
                for (x = sizex; x > 0; x--)
                {
                    for (y = 0; y < sizey; y++)
                    {
                        if (drop && (world[y - 1][x - 1] == enemy || world[y - 1][x - 1] == enemyShielded))
                        {
                            world[y][x] = world[y - 1][x - 1];
                            world[y - 1][x - 1] = ' ';
                        }
                        else if (!drop && (world[y][x - 1] == enemy || world[y][x - 1] == enemyShielded))
                        {
                            world[y][x] = world[y][x - 1];
                            world[y][x - 1] = ' ';
                        }
                    }
                }
            }
            for (x = 0; x < sizex; x++)
            {
                if (world[sizey - 1][x] == enemy || world[sizey - 1][x] == enemyShielded)
                {
                    victory = 0;
                    break;
                }
            }
        }

        /*control player*/

        if (_kbhit())
        {
            keyPress = _getch();
        }
        else
        {
            keyPress = ' ';
        }

        /*Move player according to key selection by user*/

        if (keyPress == left)
        {
            for (x = 0; x < sizex; x = x + 1)
            {
                if (world[sizey - 1][x + 1] == player)
                {
                    world[sizey - 1][x] = player;
                    world[sizey - 1][x + 1] = ' ';
                }
            }
        }

        if (keyPress == right)
        { /* Capital letters are added to cater for the situation when user
          accidentally presses capslock while playing with WAD keys*/
            for (x = sizex - 1; x > 0; x = x - 1)
            {
                if (world[sizey - 1][x - 1] == player)
                {
                    world[sizey - 1][x] = player;
                    world[sizey - 1][x - 1] = ' ';
                }
            }
        }
        if (keyPress == fire)
        {
            if (laserReady > 2)
            {
                for (x = 0; x < sizex; x = x + 1)
                {
                    if (world[sizey - 1][x] == player)
                    {
                        world[sizey - 2][x] = playerLaser;
                        laserReady = 0;
                    }
                }
            }
        }

        if (keyPress == pause) // Pause game

        {
            count_pause++;
        }

        while (count_pause % 2 != 0)
        {
            setCursorPosition(0, 0);
            DisplayWorld(world, score);
            printf("\n\n\n\n\n\n\t\t\t\t\t\t\tPress 'p' to resume game or press 0 to return to map selection");

            if (_getch() == 'p' || _getch() == 'P')
            {
                system("cls");
                count_pause++;
                setCursorPosition(0, 0);
                DisplayWorld(world, score);
                printf("\n\n\n\n\n\n\t\t\t\t\t\t\t\t\tPress 'p' to pause game.");
            }

            else if (_getch() == '0')
            {
                victory = 1;
                goto loop2;
            }
        }

        i++;
        Sleep(50); // For next iteration
    }
    setCursorPosition(0, 0);
    DisplayWorld(world, score);
    printf("\n\n\n\n\n\n\t\t\t\t\t\t\t\t\tPress 'p' to pause game.");
    Sleep(1000);
    system("cls");
    Sleep(2200);
    DisplayEndScreen(victory, totalEnemies, i, score); // Displays end game messages
loop2:
    return victory;
}

void DisplayInstructionScreen(void) // Displays the instructions
{
    Sleep(900);
    printf("\n\n\t\t\t\t\t\t\t\t___     ______     _______ _      __");
    printf("\n\t\t\t\t\t\t\t\t | |\\ |(_  ||_)| |/  |  | / \\|\\ |(_ ");
    printf("\n\t\t\t\t\t\t\t\t_|_| \\|__) || \\|_|\\_ | _|_\\_/| \\|__)");

    printf("\n\n\n\n\n\n\t\t1- The game begins with bugs lined up at the top.\n\n\n");

    printf("\n\n\t\t2- You must carefully dodge their bullets by moving left and right using keys 'a' (default) and 'd' (default).\n\n\n");

    printf("\n\n\t\t3- Fire at the bugs using 'w' (default). \n\n\n");

    printf("\n\n\t\t4- All the bugs must be eliminated to achieve victory. \n\n\n");

    printf("\n\n\t\t5- If you get hit by a bullet or the enemies reach the bottom, you lose. \n\n\n");

    printf("\n\n\t\t6- In HARD mode, bug bullets are indestructible. \n\n\n");

    printf("\n\n\t\t7- Sheilded bugs - 'O' - require two bullets to kill.   \n\n\n");

    printf("\n\n\n\t\t\t\t\t\t\t\t You get one shot, make it count! \n\n\n");

    return;
}

void printControls(char left, char right, char fire) // Prints the control screen
{

    printf("\n\n\t\t\t\t\t\t\t\t\t _ _    ____  _    __");
    printf("\n\t\t\t\t\t\t\t\t\t/ / \\|\\ |||_)/ \\| (_ ");
    printf("\n\t\t\t\t\t\t\t\t\t\\_\\_/| \\||| \\\\_/|___)\n\n\n\n");

    printf("\n\n\n\n\t\t\t\t\t\t\t     The controls for the game are as follows:\n\n\n\n");
    printf("\n\n\n\n\t\t\t\t\t\t\t\t1. LEFT:\t\t\t%c     \n\n\n", left);
    printf("\n\n\n\n\t\t\t\t\t\t\t\t2. RIGHT:\t\t\t%c     \n\n\n", right);
    printf("\n\n\n\n\t\t\t\t\t\t\t\t3. FIRE:\t\t\t%c \n\n\n", fire);
    printf("\n\n\n\n\t\t\t\t\t  To change a control, press the number besides it, or press 0 to exit to main menu.     \n\n\n");
    return;
}

void DisplaySettingsScreen(void) // prints settings screen
{

    printf("\n\n\n\t\t\t\t\t\t\t\t\t __ __________     __ __");
    printf("\n\t\t\t\t\t\t\t\t\t(_ |_ |  |  | |\\ |/__(_ ");
    printf("\n\t\t\t\t\t\t\t\t\t__)|_ |  | _|_| \\|\\_|__)\n\n");

    printf("\n\n\n\n\n\n\t\t\t\t\t\t\t\t\tSELECT DIFFICULTY MAP");
    printf("\n\n\n\n\n\n\t\t\t\t\tPress the corresponding number to select difficulty or press 0 to exit to main menu.");
    printf("\n\n\n\n\n\t\t\t\t\t\t\t\t\t     1.\tEASY");
    printf("\n\n\n\n\n\t\t\t\t\t\t\t\t\t     2.\tMEDIUM");
    printf("\n\n\n\n\n\t\t\t\t\t\t\t\t\t     3.\tHARD");
    printf("\n\n\n\n");
}

void UpdateMessage(void) // Update message when user changes a control or difficulty
{

    Sleep(1000);
    system("cls");
    gotoxy(73, 25);
    printf("SUCCESSFULLY UPDATED!");
    Sleep(2000);
    system("cls");
    return;
}

void gotoxy(int x, int y) // cursor goes to a specific location on console
{
    COORD c = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void setCursorPosition(int x, int y)
{
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    fflush(stdout);
    COORD coord = {(SHORT)x, (SHORT)y};
    SetConsoleCursorPosition(hOut, coord);
}

void PrintTitle(void) // Print animated game title
{
    printf("\t\t\t\t\t\t        _____  __          __     _____  ______      _____  ______ ");
    Sleep(120);
    printf("\n\t\t\t\t\t\t       / ____| \\ \\        / /\\   |  __ \\|  ____/\\   |  __ \\|  ____|");
    Sleep(120);
    printf("\n\t\t\t\t\t\t      | |       \\ \\  /\\  / /  \\  | |__) | |__ /  \\  | |__) | |__   ");
    Sleep(120);
    printf("\n\t\t\t\t\t\t      | |        \\ \\/  \\/ / /\\ \\ |  _  /|  __/ /\\ \\ |  _  /|  __|  ");
    Sleep(120);
    printf("\n\t\t\t\t\t\t      | |____     \\  /\\  / ____ \\| | \\ \\| | / ____ \\| | \\ \\| |____ ");
    Sleep(120);
    printf("\n\t\t\t\t\t\t       \\_____|     \\/  \\/_/    \\_\\_|  \\_\\_|/_/    \\_\\_|  \\_\\______|");
    Sleep(3000);
    printf("\n\n\n\n\t\t\t\t\t\t\t\t\tDO YOU HAVE WHAT IT TAKES?");
    return;
}
void PrintTitleWithoutDelay(void) // Print game title without delays
{
    printf("\t\t\t\t\t\t        _____  __          __     _____  ______      _____  ______ ");
    printf("\n\t\t\t\t\t\t       / ____| \\ \\        / /\\   |  __ \\|  ____/\\   |  __ \\|  ____|");
    printf("\n\t\t\t\t\t\t      | |       \\ \\  /\\  / /  \\  | |__) | |__ /  \\  | |__) | |__   ");
    printf("\n\t\t\t\t\t\t      | |        \\ \\/  \\/ / /\\ \\ |  _  /|  __/ /\\ \\ |  _  /|  __|  ");
    printf("\n\t\t\t\t\t\t      | |____     \\  /\\  / ____ \\| | \\ \\| | / ____ \\| | \\ \\| |____ ");
    printf("\n\t\t\t\t\t\t       \\_____|     \\/  \\/_/    \\_\\_|  \\_\\_|/_/    \\_\\_|  \\_\\______|");
    printf("\n\n\n\n\t\t\t\t\t\t\t\t\tDO YOU HAVE WHAT IT TAKES?");

    return;
}

char DisplayMap(void) // displays Map selection screen and returns user's selection
{
    printf("\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\tSELECT GAME MAP");

    printf("\n\n\n\n\n\n\n\t\t\t\t\t\tPress the corresponding number to select a map or press 0 to return to main menu.");

    printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t    MAP 1");
    printf("\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t    MAP 2");
    printf("\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t    MAP 3");
    printf("\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t    MAP 4");

    printf("\n\n\n\n");
    char y = _getch();

    return y;
}
void DisplayWelcomeMessages(void) // Displays welcome messages at the start of the game
{
    /*welcome screen*/
    gotoxy(74, 13);
    Sleep(1500);
    printf("WELCOME PROGRAMMER!");
    Sleep(1500);
    gotoxy(67, 21);
    printf("DEFEAT ALL THE BUGS IN THE CODE.");
    Sleep(1500);
    gotoxy(65, 29);
    printf("YOUR OPERATING SYSTEM DEPENDS ON YOU.");
    Sleep(1500);
    gotoxy(78, 37);
    printf(" GOOD LUCK.");
    gotoxy(72, 45);

    Sleep(1500);
    printf("Press any key to start.");
    _getch();
    return;
}
