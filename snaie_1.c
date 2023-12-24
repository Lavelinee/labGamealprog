#include <stdio.h>
#include <conio.h>
#include <string.h>

// Buat declare size map;
char map[30][30];
// Declare simbol head ama food snakenya
char player = '^', food = 'O';
// Declare tail
char tail[25] = {'*','*','*','*','*','*','*','*','*','*', '*','*','*','*','*','*','*','*','*','*'};
// Posisi spawn kepala
int y = 12; // baris
int x = 3;  // kolom
// Store posisi tail
int a[20];
int b[20];
char walk;
int score = 0;
int n = 0, p = 20, q = 20, rand, R = 1, i, j;

void generateMap(int p, int q, int R);
void outputMap(int score);
void moveUp();
void moveDown();
void moveLeft();
void moveRight();

int main() {
    int i, j, g;
    system("color d");
	char name[100];


	FILE* fp;
	fp = fopen("dataplayer.txt", "a");
	printf("Masukkan nama player: ");
	scanf("%[^\n]", &name);

    do {
        system("cls");
        generateMap(p, q, R);
        outputMap(score);
        walk = getch();
        for (i = 19; i > 0; i--) {
            a[i] = a[i-1];
            b[i] = b[i-1];
        }
        a[0] = y;
        b[0] = x;

        // Perbarui posisi kepala
        switch (walk) {
            case 'w':
            case 'W':
                moveUp();
                break;
            case 's':
            case 'S':
                moveDown();
                break;
            case 'a':
            case 'A':
                moveLeft();
                break;
            case 'd':
            case 'D':
                moveRight();
                break;
        }

        // Cek tabrakan dengan tubuh
        for (i = 1; i < R; i++) {
            if (y == a[i] && x == b[i]) {
                g = -1;
                break;
            }
        }

    } while (score < 20 && g != -1);

    // Tampilkan pesan game over atau congrats
    system("cls");
    if (g == -1) {
        printf("\t\t+===============================+\n");
        printf("\t\t|          GAME OVER!           |\n");
        printf("\t\t+===============================+\n");
        printf("Your Score : %d\n", score);
    } else {
        printf("\t\t+==============================+\n");
        printf("\t\t|      CONGRATULATION !!!      |\n");
        printf("\t\t+==============================+\n");
        printf("Your Score : %d", score);
        getch();
    }
	fprintf(fp, "%s#%d\n", name, score);
    fclose(fp);
    
    fp = fopen("dataplayer.txt", "r");
    //buat looping sort
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    struct Player {
        char name[100];
        int score;
    } players[100]; 

    int numPlayers = 0;

    while (fscanf(fp, "%[^#]#%d\n", players[numPlayers].name, &players[numPlayers].score) == 2) {
        numPlayers++;
    }

    fclose(fp);

    for (i = 0; i < numPlayers - 1; i++) {
        for (j = i + 1; j < numPlayers; j++) {
            if (players[i].score < players[j].score) {
               
                struct Player temp = players[i];
                players[i] = players[j];
                players[j] = temp;
            }
        }
    }
	
	printf("\n");
    printf("\t\t+==============================+\n");
    printf("\t\t|        LEADERBOARD           |\n");
    printf("\t\t+==============================+\n");
    for (i = 0; i < numPlayers; i++) {
        printf("%d. %s - Score: %d\n", i + 1, players[i].name, players[i].score);
    }
	fclose(fp);

    return 0;
}

void generateMap(int p, int q, int R) {
    int i, j;
    for (i = 0; i < 30; i++) {
        for (j = 0; j < 30; j++) {
            map[i][j] = ' ';
        }
    }
    map[0][0] = '+';
    map[29][0] = '+';
    map[29][29] = '+';
    map[0][29] = '+';
    for (i = 1; i < 29; i++) {
        map[i][0] = '|';
        map[i][29] = '|';
    }
    for (j = 1; j < 29; j++) {
        map[0][j] = '=';
        map[29][j] = '=';
    }
    map[y][x] = player;
    for (i = 0; i < R; i++) {
        map[a[i]][b[i]] = tail[i];
    }
    map[p][q] = food;
}

void outputMap(int score) {
    int i, j;
    for (i = 0; i < 30; i++) {
        for (j = 0; j < 30; j++) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
    printf("Score: %d", score);
}

void moveUp() {
    if (map[y - 1][x] == ' ') {
        y--;
        map[y][x] = player;
    } else if (map[y - 1][x] == food) { // spawn food
        p *= (rand + y * 3);
        q *= (rand + x * 9);
        if (p >= 29) p %= 23;
        p++;
        if (q >= 29) q %= 26;
        q++;
        score++;
        R++;
    }
    player = '^';
    for (i = 0; i < R; i++) {
        for (j = 0; j < R; j++) {
            map[a[i]][b[j]] = tail[n];
            n++;
        }
    }
}

void moveDown() {
    if (map[y + 1][x] == ' ') {
        y++;
        map[y][x] = player;
    } else if (map[y + 1][x] == food) { // spawn food
        p *= (rand + y * 6);
        q *= (rand + x * 8);
        if (p >= 29) p %= 28;
        p++;
        if (q >= 29) q %= 25;
        q++;
        score++;
        R++;
    }
    player = 'v';
    for (i = 0; i < R; i++) {
        for (j = 0; j < R; j++) {
            map[a[i]][b[j]] = tail[n];
            n++;
        }
    }
}

void moveLeft() {
    if (map[y][x - 1] == ' ') {
        x--;
        map[y][x] = player;
    } else if (map[y][x - 1] == food) { // spawn food
        p *= (rand + y * 5);
        q *= (rand + x * 7);
        if (p >= 29) p %= 28;
        p++;
        if (q >= 29) q %= 27;
        q++;
        score++;
        R++;
    }
    player = '<';
    for (i = 0; i < R; i++) {
        for (j = 0; j < R; j++) {
            map[a[i]][b[j]] = tail[n];
            n++;
        }
    }
}

void moveRight() {
    if (map[y][x + 1] == ' ') {
        x++;
        map[y][x] = player;
    } else if (map[y][x + 1] == food) {
        p *= (rand + y * 2);
        q *= (rand + x * 3);
        if (p >= 29) p %= 28;
        p++;
        if (q >= 29) q %= 28;
        q++;
        score++;
        R++;
    }
    player = '>';
    for (i = 0; i < R; i++) {
        for (j = 0; j < R; j++) {
            map[a[i]][b[j]] = tail[n];
            n++;
        }
    }
}
