#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define HEIGHT 250 + 2
#define WIDE 50 + 2
#define CNT_OF_CELL 1000

char cell = '*';
char death = ' ';

void print_screen(char dp[WIDE][HEIGHT]){
    clear_screen();
    //draw our array(screen)
    for (int i = 0; i < WIDE; i++)
    {
        for (int j = 0; j < HEIGHT; j++)
        {
            printf("%c", dp[i][j]);
        }
        printf("\n");
    }
    sleep(1);
    
}

void clear_screen() 
{ 
    printf("\033[2J"); /* Clear the entire screen. */ 
    printf("\033[0;0f"); /* Move cursor to the top left hand corner */ 
}

void create_map(char dp[WIDE][HEIGHT], int spawn_needed)
{
    if (spawn_needed == 1)
    {
        //spawn our cell on the map
        for (int i = 0; i < CNT_OF_CELL; i++ ){
            dp[rand()%WIDE][rand()%HEIGHT] = cell;
        }
    }
    for (int i = 0; i < WIDE; i++)
    {
       
        for (int j = 0; j < HEIGHT; j++)
        {   if (dp[i][j] != cell)
                dp[i][j] = death;

            if ((i == 0) || (i == (WIDE-1))){
                dp[i][j] = '-';
            }
            if ((j==0) || (j == (HEIGHT-1))){
                dp[i][j] = '|';
            }
        }
        
    }
    //make corners look like +
    dp[0][0] = '+';
    dp[0][HEIGHT-1] = '+';
    dp[WIDE-1][0] = '+';
    dp[WIDE-1][HEIGHT-1] = '+'; 
}

void copy(char mas[WIDE][HEIGHT], char dp[WIDE][HEIGHT])
{
    for(int i = 0; i < WIDE; i++){
        for (int j = 0; j < HEIGHT; j++){
            mas[i][j] = dp[i][j];
        }
    }
}

int neighbours(char dp[WIDE][HEIGHT], int wide, int height){ //returns count of neighbours
    int i, j;
    int cnt = 0;
    int step = 1;//how big will be our radius of looking around for neighbours
    for(i = (wide - step); i <= (wide + step); i++){
        for(j = (height - step); j <= (height + step); j++){
            if (dp[i][j] == cell)
                cnt++;
        }
    }
    //if place, which neighbours we a checking, is a cell
    //we shouldnt count it
    return cnt - (dp[wide][height] == cell);
}

int if_end(char mas[WIDE][HEIGHT], char dp[WIDE][HEIGHT]){
    //checks if game is over
    for(int i = 0; i < WIDE; i++){
        for (int j = 0; j < HEIGHT; j++){
            if (mas[i][j] != dp[i][j])
                return 0; //if arrays arent the same
        }
    }
    return 1;//if arrays are the same
}



int main(){
    char mas[WIDE][HEIGHT]; //our map
    char prev_mas[WIDE][HEIGHT];
    
    srand(time(NULL));//initialisation for rand. called once.
    create_map(mas, 1); 
    create_map(prev_mas, 0);

    for (;;){
        //draw our map
        print_screen(mas);
        for (int i = 1; i < WIDE -1; i++)
        {  
            for (int j = 1; j < HEIGHT -1; j++)
            {
                int neib = 0;
                neib = neighbours(mas, i, j);
                //if cell has 2or3 neighbours it will live, overwise it'll die
                if (mas[i][j] == cell){
                    if ((2 <= neib) && (neib <= 3))
                        prev_mas[i][j] = cell;
                    else
                        prev_mas[i][j] = death;
                }
                if (mas[i][j] == death){
                    if (neib == 3)
                        prev_mas[i][j] = cell;
                    else
                        prev_mas[i][j] = death;
                }    
            }
        }
        if (if_end(mas, prev_mas) == 1){
            clear_screen();
            printf("Game Over");
            break;
        }
        copy(mas, prev_mas);
    }
    return 0;
}