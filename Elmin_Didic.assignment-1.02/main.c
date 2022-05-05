// @Author ●  ̿' ̿'\̵͇̿̿\з=(◕_◕)=ε/̵͇̿̿/'̿'̿ ̿ ● Elmin Didic


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

//Board Size
#define width 80
#define height 21

/* List of Symbols and their meaning
 * ♨ Tall Grass
 * ↑ Tree
 * 184 © Pokemon Center
 * 169 ℗ Poke Mart
 * 219 █ Rock
 * 176 ░ Floor
 * 177 ▒ Un-Used
 * 178 ▓ Water
 * 200 ╚ DownRight Road
 * 188 ╝ DownLeft Road
 * 201 ╔ UpRight Road
 * 187 ╗ UpLeft Road
 * 202 ╩ DownLeftRight Road
 * 203 ╦ UpLeftRight Road
 * 204 ╠ UpRightDown Road
 * 185 ╣ UpLeftDown Road
 * 205 ═ LeftRight Road
 * 206 ╬ AllWays Road
 * 186 ║ UpDown Road
 */

typedef struct {

    char board[height][width];
    int North,East,South,West;

} map;

map *wrld[399][399];




//List of All Colors
#define BLK "\e[1;90m"
#define BHBLK "\e[1;90m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define GGRN "\e[1;92m"
#define UGRN "\e[4;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"





void gen_world(map *world[399][399],int x, int y, int preX, int preY)
{



    if(world[y][x] == NULL) {
        wrld[y][x] = malloc(sizeof *wrld[y][x]);
        int i, j, tileRand;

        /*
         * World Generation
         * % Rock
         * . Normal Clearing Grass
         * , Tall Grass
         * " Tree
         */
        for (i = 0; i < height; ++i) {
            for (j = 0; j < width; ++j) {
                if (i == 0 || i == 20 || j == 0 || j == 79) {
                    world[y][x]->board[i][j] = '%';
                } else {
                    tileRand = rand() % 40 + 1;
                    if (tileRand == 32) {
                        world[y][x]->board[i][j] = ',';

                    } else if (tileRand == 37) {
                        world[y][x]->board[i][j] = '"';
                    } else {
                        world[y][x]->board[i][j] = '.';
                    }


                }
            }


        }

        //Another Border Generator Too make sure nothing goes out of line
        for (i = 0; i < height; ++i) {
            for (j = 0; j < width; ++j) {
                if (i == 0 || i == 20 || j == 0 || j == 79) {


                    world[y][x]->board[i][j] = '%';

                }
            }
        }

        //road placer
        int North;
        int South;
        int East;
        int West;

        if(y-1 < 0)
        {
            North = rand() % 74 + 3;
        }
        else
        {
            if (world[y - 1][x] != NULL) {

                North = world[y - 1][x]->South;
            } else {
                North = rand() % 74 + 3;
            }
        }

        if(y + 1 > 398)
        {
            South = rand() % 74 + 3;
        }
        else
        {
            if (world[y + 1][x] != NULL) {
                South = world[y + 1][x]->North;
            } else {
                South = rand() % 74 + 3;
            }
        }


        if(x + 1 > 398)
        {
            East = rand() % 15 + 3;
        }
        else
        {
            if (world[y][x + 1] != NULL) {
                East = world[y][x + 1]->West;
            } else {
                East = rand() % 15 + 3;
            }
        }


    if(x - 1 < 0 )
    {
        West = rand() % 15 + 3;
    }
    else
    {
        if (world[y][x - 1] != NULL) {
            West = world[y][x - 1]->East;
        } else {
            West = rand() % 15 + 3;
        }
    }





        world[y][x]->North = North;
        world[y][x]->South = South;
        world[y][x]->East = East;
        world[y][x]->West = West;




        int DownRand = rand() % 10 + 5;


        //Adding Roads
        for (i = 0; i < DownRand; i++) {
            world[y][x]->board[i][North] = '#';
        }
        for (i = 20; i > DownRand; i--) {
            world[y][x]->board[i][South] = '#';
        }


        if (North > South) {
            for (i = South; i <= North; i++) {
                world[y][x]->board[DownRand][i] = '#';
            }

        } else {
            for (i = North; i <= South; i++) {
                world[y][x]->board[DownRand][i] = '#';
            }

        }

        int SideRand = rand() % 40 + 25;

        for (i = 0; i < SideRand; i++) {
            world[y][x]->board[West][i] = '#';
        }
        for (i = 79; i > SideRand; i--) {
            world[y][x]->board[East][i] = '#';
        }


        if (West > East) {
            for (i = East; i <= West; i++) {
                world[y][x]->board[i][SideRand] = '#';
            }

        } else {
            for (i = West; i <= East; i++) {
                world[y][x]->board[i][SideRand] = '#';
            }


        }

        if(x == 0)
        {
            world[y][x]->board[West][0] = '%';
        }
        if(x == 398)
        {

            world[y][x]->board[East][79] = '%';
        }
        if(y == 0)
        {
            world[y][x]->board[0][North] = '%';
        }
        if(y == 398)
        {
            world[y][x]->board[20][South] = '%';
        }

        double manDist, chance;

        manDist = abs(preX - x)+ abs(preY- y);
        if(manDist >= 200)
        {
            chance = 5;
        }
        else
        {
            chance = ((-45.0 * manDist)/ 200.0) + 50;
        }

        if(x == 199 && y == 199)
        {
            world[y][x]->board[2][North + 1] = 'M';
            world[y][x]->board[West + 1][4] = 'C';
        }
        else
        {
            if (rand() % 101 < chance) {
                //Adding PokeMart and PokeCenter
                world[y][x]->board[2][North + 1] = 'M';

            }

            if (rand() % 101 < chance) {
                //Adding PokeMart and PokeCenter
                world[y][x]->board[West + 1][4] = 'C';

            }
        }






        for (i = 0; i < height; ++i) {
            for (j = 0; j < width; ++j) {

                if (world[y][x]->board[i][j] == '%') {
                    printf(BHBLK "█");
                } else if (world[y][x]->board[i][j] == '.') {
                    printf(GRN ".");
                } else if (world[y][x]->board[i][j] == 'N' || world[y][x]->board[i][j] == 'E' ||
                           world[y][x]->board[i][j] == 'S' || world[y][x]->board[i][j] == 'W') {
                    printf(RED "%c", world[y][x]->board[i][j]);
                } else if (world[y][x]->board[i][j] == '#') {
                    if (world[y][x]->board[i - 1][j] == '#' && world[y][x]->board[i][j - 1] != '#' &&
                        world[y][x]->board[i][j + 1] != '#') {
                        printf(WHT "║");
                    } else if (world[y][x]->board[i - 1][j] == '#' && world[y][x]->board[i][j - 1] == '#' &&
                               world[y][x]->board[i + 1][j] == '#' && world[y][x]->board[i][j + 1] == '#') {
                        printf(WHT "╬");
                    } else if (world[y][x]->board[i - 1][j] != '#' && world[y][x]->board[i + 1][j] != '#' &&
                               world[y][x]->board[i][j - 1] == '#' && world[y][x]->board[i][j + 1] == '#') {
                        printf(WHT "═");
                    } else if (world[y][x]->board[i + 1][j] != '#' && world[y][x]->board[i][j + 1] == '#' &&
                               world[y][x]->board[i][j - 1] != '#' && world[y][x]->board[i - 1][j] == '#') {
                        printf(WHT "╚");
                    } else if (world[y][x]->board[i + 1][j] != '#' && world[y][x]->board[i][j + 1] != '#' &&
                               world[y][x]->board[i][j - 1] == '#' && world[y][x]->board[i - 1][j] == '#') {
                        printf(WHT "╝");

                    } else if (world[y][x]->board[i + 1][j] == '#' && world[y][x]->board[i][j + 1] == '#' &&
                               world[y][x]->board[i][j - 1] != '#' && world[y][x]->board[i - 1][j] != '#') {
                        printf(WHT "╔");


                    } else if (world[y][x]->board[i + 1][j] == '#' && world[y][x]->board[i][j + 1] != '#' &&
                               world[y][x]->board[i][j - 1] == '#' && world[y][x]->board[i - 1][j] != '#') {
                        printf(WHT "╗");


                    } else if (world[y][x]->board[i + 1][j] != '#' && world[y][x]->board[i][j + 1] == '#' &&
                               world[y][x]->board[i][j - 1] == '#' && world[y][x]->board[i - 1][j] == '#') {
                        printf(WHT "╩");


                    } else if (world[y][x]->board[i + 1][j] == '#' && world[y][x]->board[i][j + 1] == '#' &&
                               world[y][x]->board[i][j - 1] == '#' && world[y][x]->board[i - 1][j] != '#') {
                        printf(WHT "╦");


                    } else if (world[y][x]->board[i + 1][j] == '#' && world[y][x]->board[i][j + 1] == '#' &&
                               world[y][x]->board[i][j - 1] != '#' && world[y][x]->board[i - 1][j] == '#') {
                        printf(WHT "╠");


                    } else if (world[y][x]->board[i + 1][j] == '#' && world[y][x]->board[i][j + 1] != '#' &&
                               world[y][x]->board[i][j - 1] == '#' && world[y][x]->board[i - 1][j] == '#') {
                        printf(WHT "╣");


                    } else if (world[y][x]->board[i - 1][j] == '%' && world[y][x]->board[i + 1][j] == '%') {
                        printf(WHT "═");
                    } else if (world[y][x]->board[i][j - 1] == '%' && world[y][x]->board[i][j + 1] == '%') {
                        printf(WHT "║");
                    } else {
                        printf(WHT "#");
                    }


                } else if (world[y][x]->board[i][j] == '"') {
                    printf(UGRN "↑");
                } else if (world[y][x]->board[i][j] == ',') {
                    printf(GGRN "♨");
                } else if (world[y][x]->board[i][j] == 'M') {
                    printf(RED "℗");
                } else if (world[y][x]->board[i][j] == 'C') {
                    printf(YEL "©");
                }


            }
            printf("\n");

        }
    }
    else
    {
        int i,j;

        for (i = 0; i < height; ++i) {
            for (j = 0; j < width; ++j) {

                if (world[y][x]->board[i][j] == '%') {
                    printf(BHBLK "█");
                } else if (world[y][x]->board[i][j] == '.') {
                    printf(GRN ".");
                } else if (world[y][x]->board[i][j] == 'N' || world[y][x]->board[i][j] == 'E' ||
                           world[y][x]->board[i][j] == 'S' || world[y][x]->board[i][j] == 'W') {
                    printf(RED "%c", world[y][x]->board[i][j]);
                } else if (world[y][x]->board[i][j] == '#') {
                    if (world[y][x]->board[i - 1][j] == '#' && world[y][x]->board[i][j - 1] != '#' &&
                        world[y][x]->board[i][j + 1] != '#') {
                        printf(WHT "║");
                    } else if (world[y][x]->board[i - 1][j] == '#' && world[y][x]->board[i][j - 1] == '#' &&
                               world[y][x]->board[i + 1][j] == '#' && world[y][x]->board[i][j + 1] == '#') {
                        printf(WHT "╬");
                    } else if (world[y][x]->board[i - 1][j] != '#' && world[y][x]->board[i + 1][j] != '#' &&
                               world[y][x]->board[i][j - 1] == '#' && world[y][x]->board[i][j + 1] == '#') {
                        printf(WHT "═");
                    } else if (world[y][x]->board[i + 1][j] != '#' && world[y][x]->board[i][j + 1] == '#' &&
                               world[y][x]->board[i][j - 1] != '#' && world[y][x]->board[i - 1][j] == '#') {
                        printf(WHT "╚");
                    } else if (world[y][x]->board[i + 1][j] != '#' && world[y][x]->board[i][j + 1] != '#' &&
                               world[y][x]->board[i][j - 1] == '#' && world[y][x]->board[i - 1][j] == '#') {
                        printf(WHT "╝");

                    } else if (world[y][x]->board[i + 1][j] == '#' && world[y][x]->board[i][j + 1] == '#' &&
                               world[y][x]->board[i][j - 1] != '#' && world[y][x]->board[i - 1][j] != '#') {
                        printf(WHT "╔");


                    } else if (world[y][x]->board[i + 1][j] == '#' && world[y][x]->board[i][j + 1] != '#' &&
                               world[y][x]->board[i][j - 1] == '#' && world[y][x]->board[i - 1][j] != '#') {
                        printf(WHT "╗");


                    } else if (world[y][x]->board[i + 1][j] != '#' && world[y][x]->board[i][j + 1] == '#' &&
                               world[y][x]->board[i][j - 1] == '#' && world[y][x]->board[i - 1][j] == '#') {
                        printf(WHT "╩");


                    } else if (world[y][x]->board[i + 1][j] == '#' && world[y][x]->board[i][j + 1] == '#' &&
                               world[y][x]->board[i][j - 1] == '#' && world[y][x]->board[i - 1][j] != '#') {
                        printf(WHT "╦");


                    } else if (world[y][x]->board[i + 1][j] == '#' && world[y][x]->board[i][j + 1] == '#' &&
                               world[y][x]->board[i][j - 1] != '#' && world[y][x]->board[i - 1][j] == '#') {
                        printf(WHT "╠");


                    } else if (world[y][x]->board[i + 1][j] == '#' && world[y][x]->board[i][j + 1] != '#' &&
                               world[y][x]->board[i][j - 1] == '#' && world[y][x]->board[i - 1][j] == '#') {
                        printf(WHT "╣");


                    } else if (world[y][x]->board[i - 1][j] == '%' && world[y][x]->board[i + 1][j] == '%') {
                        printf(WHT "═");
                    } else if (world[y][x]->board[i][j - 1] == '%' && world[y][x]->board[i][j + 1] == '%') {
                        printf(WHT "║");
                    } else {
                        printf(WHT "#");
                    }


                } else if (world[y][x]->board[i][j] == '"') {
                    printf(UGRN "↑");
                } else if (world[y][x]->board[i][j] == ',') {
                    printf(GGRN "♨");
                } else if (world[y][x]->board[i][j] == 'M') {
                    printf(RED "℗");
                } else if (world[y][x]->board[i][j] == 'C') {
                    printf(YEL "©");
                }


            }
            printf("\n");

        }
    }

}



int main(int argc, char *argv[])
{



    srand(time(NULL));
    int curX, curY, preX, preY;
    char userInput;
    curX = 199;
    curY = 199;
    preX = curX;
    preY = curY;



    /*
     * • n: Display the map immediately north of the current map.
    • s: Display the map immediately south of the current map.
    • e: Display the map immediately east of the current map.
    • w: Display the map immediately west of the current map.
    • f x y: x and y are integers; Fly1
        to map (x, y).
    • q: Quit the game.
     */
    gen_world(wrld, curX,curY, preX, preY);

    while(1)
    {
        printf("Enter: \n");
        scanf("%c", &userInput);
        userInput = tolower(userInput);

        if(userInput == 'n')
        {
            preY = curY;
            preX = curX;
            curY--;
            if(curY < 0 || curY > 398)
            {
                curY = preY;
            }
            gen_world(wrld, curX,curY, preX, preY);

        }
        else if(userInput == 'e')
        {
            preY = curY;
            preX = curX;
            curX++;
            if(curX < 0 || curX > 398)
            {
                curX = preX;
            }
            gen_world(wrld, curX,curY, preX, preY);
        }
        else if(userInput == 's')
        {
            preY = curY;
            preX = curX;
            curY++;
            if(curY < 0 || curY > 398)
            {
                curY = preY;
            }
            gen_world(wrld, curX,curY, preX, preY);
        }
        else if(userInput == 'w')
        {

            preY = curY;
            preX = curX;
            curX--;
            if(curX < 0 || curX > 398)
            {
                curX = preX;
            }
            gen_world(wrld, curX,curY, preX, preY);
        }
        else if(userInput == 'f')
        {
            preY = curY;
            preX = curX;
            printf("Enter X and Y: \n");
            scanf("%d %d", &curX, &curY);
            if(curX < 0 || curX > 398)
            {
                curX = preX;
            }
            if(curY < 0 || curY > 398)
            {
                curY = preY;
            }
            gen_world(wrld, curX,curY, preX, preY);

        }
        else if(userInput == 'q')
        {
            break;
        }
        else
        {
            printf("Invalid option \n");
        }

        while(getchar() != '\n');


    }

    for(int i = 0; i < 399; i++)
    {
        for(int j = 0; j < 399; j++)
        {
            free(wrld[i][j]);
        }
    }


    return 0;
}
