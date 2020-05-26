#ifdef _WIN32
#include "boardLibrary.c"
#include "computerLogic.c"
#include "coordinatesFunctions.c"
#include "shipsFunctions.c"
#include "stack.c"
#endif

#include "battleship.h"

#define PORT 7777
#define MAX_NUM_CLIENTS 1

int main() {

#ifdef _WIN32
    window size = {5 + 4 * COLS + 1, 1 + 3 + 2 * ROWS + 1 + 4};
    setWindowSize(size.x, size.y);

    WSADATA wsa;
	SOCKET mainSocket, acceptSocket;
#else
    int mainSocket, acceptSocket;
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

    int shot_checker, number_of_tested_shots = -1; // number_of_tested_shots is for co-op, testing is every field around hit tested

    int game_mode  = -1, // Stores mode of the game (0 or 1)
        com_mode   = -1,
        numHits[2] = {0},
        player     = rand() % 2,
        temp,           // Stores temporary values
        i, j;           // Counters

    char temp_ch[3],
         ip[14];

    stackElement *stack = NULL;

    initializeBoard(boardOne);
    initializeBoard(boardTwo);

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

    if(game_mode == PLAYER_V_PLAYER) {
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

        struct sockaddr_in sock_addr;
        int sockAddrInLength = sizeof(struct sockaddr_in);

#ifdef _WIN32
        if (WSAStartup(MAKEWORD(2,2), &wsa)) {
            printf("Failed. Error Code : %d\n",WSAGetLastError());
            return 1;
        }
#endif

        if((mainSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
            printf("Could not create socket.\n");
            return 1;
        }

        sock_addr.sin_family = AF_INET;
        sock_addr.sin_port = htons(PORT);

        if(com_mode) {
            system(CLEAR);
            printf("Paste the ip address here: ");
            scanf("%s", ip);
            sock_addr.sin_addr.s_addr = inet_addr(ip);
            if(connect(mainSocket, (struct sockaddr*) &sock_addr, sizeof sock_addr) < 0) {
                printf("Connection failed.\n");
                return 1;
            }
            RECEIVE(mainSocket, temp_ch, 1 PARAMETER);
            player = temp_ch[0] - '0';
        } else {
            system(CLEAR);
            printf("> Send this ip address to a client\n> ");
#ifdef _WIN32
            system("@echo off & for /f \"tokens=2 delims=:\" %a in ('ipconfig ^| findstr IPv4') do echo %a");
#else
            system("ip -4 addr show wlp2s0 | grep -oP '(?<=inet\\s)\\d+(\\.\\d+){3}'");
#endif
            sock_addr.sin_addr.s_addr = INADDR_ANY;
            if(bind(mainSocket, (struct sockaddr*)&sock_addr, sizeof(sock_addr)) == -1) {
                printf("Binding socket on port %d failed.\n", PORT);
                return 1;
            }

            listen(mainSocket, MAX_NUM_CLIENTS);

            acceptSocket = accept(mainSocket, (struct sockaddr*)&sock_addr, &sockAddrInLength);
            if(acceptSocket == -1) {
                printf("Accept failed.\n");
                return 1;
            }

            temp_ch[0] = !player + '0';
            temp_ch[1] = '\0';
            SEND(acceptSocket, temp_ch, 1 PARAMETER);
        }
    }

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

    while(true) {
        if(game_mode == PLAYER_VS_COOP) {
            if(player == 0) {
                do {
                    system(CLEAR);
                    printf("Your turn:\n");
                    printBoard(boardTwo, false);
                    target = inputCoordinate();
                    shot_checker = checkShot(boardTwo, target);
                } while(shot_checker == -1);
                updateCell(boardTwo, target);
            } else if(player == 1) {
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
                if (isShipSunken(target,ships_details,player)){
                    printf("> Sank the ");
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
                    //if ship is sunken and if game is vs co-op remove field from the stack
                    stack = Pop(stack);
                }
            }
            else{
                printf("> %c%c is a miss!\n", target.x + 'A', target.y + '0');
                player = !player;
            }

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
                while(player == 1) {
                    system(CLEAR);
                    printf("Enemy playing...\n");
                    printBoard(boardOne, true);
                    RECEIVE((com_mode) ? mainSocket : acceptSocket, temp_ch, 2 PARAMETER);
                    target.x = temp_ch[0] - 'A';
                    target.y = temp_ch[1] - '0';
                    shot_checker = checkShot(boardOne, target);
                    if(shot_checker == 0) printf("He missed! :)\n");
                    else printf("We got hit...\n");
                    temp_ch[0] = shot_checker + '0';
                    temp_ch[1] = '\0';
                    SEND((com_mode) ? mainSocket : acceptSocket, temp_ch, 1 PARAMETER);
                    RECEIVE((com_mode) ? mainSocket : acceptSocket, temp_ch, 1 PARAMETER);
                    player = temp_ch[0] - '0';
                    updateCell(boardOne, target);
                }
            } else if(player == 0) {
                system(CLEAR);
                printf("It's your move!\n");
                printBoard(boardTwo, false);
                target = inputCoordinate();
                temp_ch[0] = target.x + 'A';
                temp_ch[1] = target.y + '0';
                temp_ch[2] = '\0';
                SEND((com_mode) ? mainSocket : acceptSocket, temp_ch, 2 PARAMETER);
                RECEIVE((com_mode) ? mainSocket : acceptSocket, temp_ch, 1 PARAMETER);
                if(temp_ch[0] - '0' == 0) {
                    boardTwo[target.x][target.y].symbol = MISS;
                    player = !player;
                } else if(temp_ch[0] - '0' > 0 && temp_ch[0] - '0' < 5) {
                    numHits[0]++;
                    boardTwo[target.x][target.y].symbol = HIT;
                }
                if(numHits[0] == 20) {
                    temp_ch[0] = '2';
                    temp_ch[1] = '\0';
                    player = 3;
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

        else{

        }


    }

    #ifdef _WIN32
        CLOSE_SOCKET;
    #endif

    return 0;
}
