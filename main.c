#ifdef __WIN32
#include "boardLibrary.c"
#include "computerLogic.c"
#include "coordinatesFunctions.c"
#include "shipsFunctions.c"
#include "stack.c"
#endif

//#endif

#include "battleship.h"

#define PORT 7777           // Port number
#define MAX_NUM_CLIENTS 1   // Number of connections to listen to

int main() {

#ifdef _WIN32
    // Set command prompt size on Windows OS
    window size = {5 + 4 * COLS + 1, 1 + 3 + 2 * ROWS + 1 + 4};
    setWindowSize(size.x, size.y);
    // Inicialise Windows libraries for sockets
    WSADATA wsa;
	SOCKET mainSocket, acceptSocket; // Store sockets on Windows OS
#else
    int mainSocket, acceptSocket;    // Store sockets on Linux OS
#endif

    srand(time(NULL));

    shipDetails ships_details[2][NUMBER_OF_SHIPS_IN_TOTAL]; //2 as in two players

    ShipType ship[NUM_OF_SHIPS] = {
        {NOSAC_AVIONA, 4, 1},
        {KRSTARICA, 3, 2},
        {RAZARAC, 2, 3},
        {PODMORNICA, 1, 4},
    };

    cell boardOne[ROWS][COLS],  // Stores player 1 board
         boardTwo[ROWS][COLS];  // Stores player 2 board

    coordinates target, last_target = {-1,-1}; // Last_target is for co-op

    int shot_checker;

    int game_mode  = -1, // Stores mode of the game (0 or 1)
        com_mode   = -1, // Communication mode (1 - client, 0 - server)
        numHits[2] = {0}, // Number of hits
        player = rand() % 2,         // Current player
        temp,           // Stores temporary values
        i, j;           // Counters

    char temp_ch[3],    // Used for sending 1 or 2 byte data between computers
         ip[14];        // Stores ip address

    stackElement *stack = NULL, *element; //pointer to top of a stack for co-op

    // Set both boards to WATER

    initializeBoard(boardOne);
    initializeBoard(boardTwo);

    // First, player picks a game mode
    do {
        system(CLEAR);
        printf("> [1] Player vs CO-OP\n");
        printf("> [2] Player vs Player\n");
        printf("> ");
        fflush(stdin);
        scanf("%1[^\n]s", temp_ch);
        if(temp_ch[0] == '1' || temp_ch[0] == '2') {
            game_mode = temp_ch[0] - '1';
        }
    } while(game_mode == -1);

    /*
     * If the game mode is player vs player, we have to establish
     * connection between two players
     *
     * ************************Important!************************
     * Server has to be started first!
     * Client starts after and has to have the address of
     * server's computer which will be displayed on the screen!
     */
    if(game_mode == PLAYER_V_PLAYER) {
        // Pick the side of the communication
        do {
            system(CLEAR);
            printf("> [1] Server\n");
            printf("> [2] Client\n");
            printf("> ");
            fflush(stdin);
            scanf("%1[^\n]s", temp_ch);
            if(temp_ch[0] == '1' || temp_ch[0] == '2') {
                com_mode = temp_ch[0] - '1';
            }
        } while(com_mode == -1);

        struct sockaddr_in sock_addr; // Structure for saving addresses
        int sockAddrInLength = sizeof(struct sockaddr_in);

#ifdef _WIN32
        // Initiates use of the Winsock DLL by a process.
        if (WSAStartup(MAKEWORD(2,2), &wsa)) {
            printf("Failed. Error Code : %d\n",WSAGetLastError());
            return 1;
        }
#endif
        // The socket function creates a socket that is bound to a specific transport service provider.
        if((mainSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
            printf("Could not create socket.\n");
            return 1;
        }

        sock_addr.sin_family = AF_INET;     // Address family for IPv4 addresses
        sock_addr.sin_port = htons(PORT);   // The htons function converts a u_short from host to TCP/IP network byte order (which is big-endian).

        // If on client side
        if(com_mode) {
            // Wait for IP address from server
            system(CLEAR);
            printf("Paste the ip address here: ");
            scanf("%s", ip);
            // inet_addr() function converts given string in a proper IP address
            sock_addr.sin_addr.s_addr = inet_addr(ip);
            // Establishe a connection to a specified socket.
            if(connect(mainSocket, (struct sockaddr*) &sock_addr, sizeof sock_addr) < 0) {
                printf("Connection failed.\n");
                return 1;
            }
            // Receive which player plays first
            RECEIVE(mainSocket, temp_ch, 1 PARAMETER);
            player = temp_ch[0] - '0';
        } else { // Else if on server side
            // Print IPv4 address of computer on which the server is running
            // Node: Give this number to a client!
            system(CLEAR);
            printf("> Send this ip address to a client\n> ");
#ifdef _WIN32
            system("@echo off & for /f \"tokens=2 delims=:\" %a in ('ipconfig ^| findstr IPv4') do echo %a");
#else
            system("ip -4 addr show wlp2s0 | grep -oP '(?<=inet\\s)\\d+(\\.\\d+){3}'");
#endif
            sock_addr.sin_addr.s_addr = INADDR_ANY;
            // Associate a local address with a socket.
            if(bind(mainSocket, (struct sockaddr*)&sock_addr, sizeof(sock_addr)) == -1) {
                printf("Binding socket on port %d failed.\n", PORT);
                return 1;
            }

            // Listen for a connection
            listen(mainSocket, MAX_NUM_CLIENTS);
            // When a request for connecting comes, accept it
            acceptSocket = accept(mainSocket, (struct sockaddr*)&sock_addr, &sockAddrInLength);
            if(acceptSocket == -1) {
                printf("Accept failed.\n");
                return 1;
            }
            // Send which player is playing to client
            temp_ch[0] = !player + '0';
            temp_ch[1] = '\0';
            SEND(acceptSocket, temp_ch, 1 PARAMETER);
        }
    }

    // Set ships and prepare for game
    if(game_mode == PLAYER_VS_COOP) {
        randomShips(boardTwo, ship, &ships_details[0]);
    }
    do {
        system(CLEAR);
        printf("> [1] Place ships manually\n");
        printf("> [2] Place ships randomly\n");
        printf("> ");
        fflush(stdin);
        scanf("%1[^\n]s", temp_ch);
        if(temp_ch[0] == '1') manualShips(boardOne, ship, &ships_details[1]);
        else if(temp_ch[0] == '2') randomShips(boardOne, ship, &ships_details[1]);
    } while(temp_ch[0] != '1' && temp_ch[0] != '2');
    // Game start
    while(true) {
        if(game_mode == PLAYER_VS_COOP) {
            if(player == PLAYER1) {
                // Player 1 (YOU) inputs coordinates and updates player 2 board
                do {
                    system(CLEAR);
                    printf("Your turn:\n");
                    printBoard(boardTwo, false);
                    target = inputCoordinate();
                    shot_checker = checkShot(boardTwo, target);
                } while(shot_checker == -1);
                updateCell(boardTwo, target);
            } else if(player == PLAYER2) {
                system(CLEAR);
                printf("Computers turn:\n");
                if (stack == NULL){ //if last shot was a miss due a random shot do random shot again
                    do {
                		target.x = rand() % 10;
                		target.y = rand() % 10;
                		shot_checker = checkShot(boardOne, target);
                	} while(shot_checker == -1);

                    if (shot_checker != -1 && shot_checker != 0) { // if a ship is hit
                        stack = Push(stack,target,-1);     //remember coordinates on stack, -1 because no more fields are tested around hit
                    }
                    updateCell(boardOne, target);
                }

                else {
                        target = tryEveryDirection(boardOne, &stack);
                        shot_checker = checkShot(boardOne,target);
                        updateCell(boardOne, target);
                }
                printBoard(boardOne, true);
            }
        if(shot_checker != -1 && shot_checker != 0) {
            numHits[player]++;
            printf("> %c%c is a hit!\n", target.x + 'A', target.y + '0');
            //checks every coordinate that contains a ship and decreases number of fields that ship contains
            for (i=0;i<NUMBER_OF_SHIPS_IN_TOTAL;i++){
                for (j=0;j<LONGEST_SHIP;j++){  //actually, it could go to lengt of hitted ship, but tbh, this is easier for implementation and execution time is not so much longer
                    if (ships_details[player][i].all_coordinates[j].x == target.x && ships_details[player][i].all_coordinates[j].y == target.y){
                        ships_details[player][i].number_of_remaining_fields -=1;
                        if (ships_details[player][i].number_of_remaining_fields <= 0){
                            printf("> you sank the ");
                            switch (shot_checker){
                                case 1:
                                    printf("nosac aviona");  //I don't know translations
                                    break;
                                case 2:
                                    printf ("krstarica");
                                    break;
                                case 3:
                                    printf("razarac");
                                    break;
                                case 4:
                                    printf("submarine");
                                    break;
                            }
                            printf("!\n");
                            if (game_mode == PLAYER_VS_COOP && player == PLAYER2){  //if ship is sunken and if game is vs co-op remove field from the stack
                                stack = Pop(stack);
                            }
                        }
                    }
                }
            }
        }
            else{
                // If missed, reverse players
                printf("> %c%c is a miss!\n", target.x + 'A', target.y + '0');
                player = !player;
            }

            // Check if the game ended
            if(numHits[PLAYER1] == 20) {
                system(CLEAR);
                printf("You won!\n");
                break;
            } else if(numHits[PLAYER2] == 20) {
                system(CLEAR);
                printf("You lost!\n");
                break;
            }
            getchar();
            getchar();
        }
        else if(game_mode == PLAYER_V_PLAYER) {
            if(player == 1) {
                // While you aren't playing
                system(CLEAR);
                printf("Enemy playing...\n");
                // Display your board
                printBoard(boardOne, true);
                // Receive new target and check for hits
                RECEIVE((com_mode) ? mainSocket : acceptSocket, temp_ch, 2 PARAMETER);
                target.x = temp_ch[0] - 'A';
                target.y = temp_ch[1] - '0';
                shot_checker = checkShot(boardOne, target);
                // Send whether you're hit or not
                temp_ch[0] = shot_checker + '0';
                temp_ch[1] = '\0';
                SEND((com_mode) ? mainSocket : acceptSocket, temp_ch, 1 PARAMETER);
                // Receive who's playing next
                RECEIVE((com_mode) ? mainSocket : acceptSocket, temp_ch, 1 PARAMETER);
                player = temp_ch[0] - '0';
                updateCell(boardOne, target);
            } else if(player == 0) {
                // If you are playing
                system(CLEAR);
                printf("It's your move!\n");
                // Print enemy board
                printBoard(boardTwo, false);
                // Input new target
                target = inputCoordinate();
                // Send new target to the enemy computer
                temp_ch[0] = target.x + 'A';
                temp_ch[1] = target.y + '0';
                temp_ch[2] = '\0';
                SEND((com_mode) ? mainSocket : acceptSocket, temp_ch, 2 PARAMETER);
                // Receive whether it's a hit or not and do the required checks
                RECEIVE((com_mode) ? mainSocket : acceptSocket, temp_ch, 1 PARAMETER);
                if(temp_ch[0] - '0' == 0) {
                    boardTwo[target.x][target.y].symbol = MISS;
                    player = !player;
                } else if(temp_ch[0] - '0' > 0 && temp_ch[0] - '0' < 5) {
                    numHits[0]++;
                    boardTwo[target.x][target.y].symbol = HIT;
                }
                // Check if the game is over
                if(numHits[0] == 20) {
                    temp_ch[0] = '2'; // Player = 2 used to tell the other computer that he lost
                    temp_ch[1] = '\0';
                    player = 3; // Player = 3 used to tell this computer that he won
                } else {
                    temp_ch[0] = !player + '0';
                    temp_ch[1] = '\0';
                }
                SEND((com_mode) ? mainSocket : acceptSocket, temp_ch, 1 PARAMETER);
                updateCell(boardTwo, target);
            } else if(player == 2) {
                system(CLEAR);
                printf("You lost! >:(\n");
                break;
            } else {
                system(CLEAR);
                printf("YOU WON!\n");
                break;
            }
        }
    }

    if(game_mode == PLAYER_V_PLAYER) {
        CLOSE_SOCKET(mainSocket);
        CLOSE_SOCKET(acceptSocket);
#ifdef _WIN32
        WSACleanup();
#endif
    } else Free(stack);
    return 0;
}
