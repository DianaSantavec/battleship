#include "boardLibrary.c"
#include "computerLogic.c"
#include "coordinatesFunctions.c"
#include "shipsFunctions.c"

#include "battleship.h"

#define IP "192.168.0.18"
#define PORT 7777
#define MAX_NUM_CLIENTS 1
#define MAX_LEN 1000

int main() {

#ifdef _WIN32
    window size = {5 + 4 * COLS + 1, 1 + 2 * (3 + 2 * ROWS + 1) + 3};
    setWindowSize(size.x, size.y);

    WSADATA wsa;
	SOCKET mainSocket, acceptSocket;
    char ips[100];
    /*strcpy(ips, );
    ips[100] = '\0';*/
    sprintf(ips, "%s\n", stdout);
    system("@echo off & for /f \"usebackq tokens=2 delims=:\" %a in (`ipconfig ^| findstr \"IPv4\"`) do echo %a");
    getchar();
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

    int game_mode = -1, // Stores mode of the game (0 or 1)
        com_mode = -1,
        temp,           // Stores temporary values
        i, j;           // Counters

    char temp_ch[2];

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
    char message[MAX_LEN];
    int messageLength;

    if (WSAStartup(MAKEWORD(2,2), &wsa)) {
        printf("Failed. Error Code : %d\n",WSAGetLastError());
        return 1;
    }

    if((mainSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
        printf("Could not create socket : %d" , WSAGetLastError());
        return 1;
    }

    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(PORT);

    if(com_mode) {
        sock_addr.sin_addr.s_addr = inet_addr(IP);
        if(connect(mainSocket, (struct sockaddr*) &sock_addr, sizeof sock_addr) < 0) {
            printf("Connection failed. error: %s\n",WSAGetLastError());
            return 1;
        }
    } else {
        sock_addr.sin_addr.s_addr = INADDR_ANY;
        if(bind(mainSocket, (struct sockaddr*)&sock_addr, sizeof(sock_addr)) == SOCKET_ERROR) {
            printf("Binding socket on port %d failed.\n", PORT);
            return 1;
        }

        listen(mainSocket, MAX_NUM_CLIENTS);

        acceptSocket = accept(mainSocket, (struct sockaddr*)&sock_addr, &sockAddrInLength);
        if(acceptSocket == INVALID_SOCKET) {
            printf("Accept failed.\n");
            return 1;
        }
    }

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

    if(game_mode == PLAYER_VS_COOP) {
        randomShips(boardTwo, ship, &ships_details[0]);
    } else {
        system(CLEAR);
        printf("> Place ships:\n");
        printf("> [1] Manually\n");
        printf("> [2] Randomly\n");
        do {
            printf("> ");
            scanf("%d", &temp);
            if(temp == 1) manualShips(boardOne, ship, &ships_details[1]);
            else if(temp == 2) randomShips(boardOne, ship, &ships_details[1]);
        } while(temp != 1 && temp != 2);
    }

    while(true) {
        if(game_mode == PLAYER_VS_COOP) {

        } else if(game_mode == PLAYER_V_PLAYER) {

        }
    }

    closesocket(mainSocket);
    closesocket(acceptSocket);
    WSACleanup();
    return 0;
}
