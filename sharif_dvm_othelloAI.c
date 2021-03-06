#include <stdio.h>

void createmap(char const *pargv[], int MapArray[][8]);
void printmap(int pMapArray[][8]);
void checkvalidcell(int MapArray[][8], int validcell[][60], int bead);
void checkdown(int MapArray[][8], int validcell[][60], int bead, int x, int y);
void checkdownright(int MapArray[][8], int validcell[][60], int bead, int x, int y);
void checkdownleft(int MapArray[][8], int validcell[][60], int bead, int x, int y);
void checkup(int MapArray[][8], int validcell[][60], int bead, int x, int y);
void checkupleft(int MapArray[][8], int validcell[][60], int bead, int x, int y);
void checkright(int MapArray[][8], int validcell[][60], int bead, int x, int y);
void checkupright(int MapArray[][8], int validcell[][60], int bead, int x, int y);
void checkleft(int MapArray[][8], int validcell[][60], int bead, int x, int y);
void removeDangerZone(int validcell[][60]);
int getMaxIndex(int validcell[][60]);
int main(int argc, char const *argv[])
{
    int i;
    int bead;
    int MapArray[8][8];   // our game map 2d-array
    int validcell[3][60]; //shows valid cell
    bead = *argv[9] - 48;                      //bead var shows our bead color
    for (i = 0; i < 60; i++)
    {
        validcell[0][i] = -1;
        validcell[1][i] = -1;
        validcell[2][i] = -1;
    }
    createmap(argv, MapArray);                 // puts argvs in 2d-array
    checkvalidcell(MapArray, validcell, bead); //finds validcells and puts them + score in 60*3 array
    //printmap(MapArray);  //checking game map (commented during final release)
    removeDangerZone(validcell);
    int maxIndex = getMaxIndex(validcell); // function finds cell giving best score and returns its index
    printf("%d %d", validcell[1][maxIndex], validcell[0][maxIndex]);
    return 0;
}
void createmap(char const *pargv[], int MapArray[][8])
{
    int i, j;
    // nested for to convert chars to ints and put in array
    for (i = 1; i <= 8; ++i)
    {
        for (j = 0; pargv[i][j] != '\0'; j++)
        {
            MapArray[i - 1][j] = pargv[i][j] - 48;
        }
    }
}
void printmap(int MapArray[][8])
{
    int i, j;
    // nested for to print the array
    for (j = 0; j < 8; j++)
    {
        for (i = 0; i < 8; i++)
        {
            printf("%d ", MapArray[j][i]);
        }
        printf("\n");
    }
}
//remove danger cell
void removeDangerZone(int validcell[][60])
{
    int i, j;
    for (j = 0; j < 3; j++)
    {
        for (i = 0; i < 60; i++)
        {
            if (validcell[j][i] != -1)
            {
                if (j == 2 &&
                 ((validcell[0][i] == 1 && validcell[1][i] == 1)||
                  (validcell[0][i] == 6 && validcell[1][i] == 1) || 
                  (validcell[0][i] == 1 && validcell[1][i] == 6) || 
                  (validcell[0][i] == 6 && validcell[1][i] == 6)||
                  (validcell[0][i] == 0 && validcell[1][i] == 1)||
                  (validcell[0][i] == 1 && validcell[1][i] == 0)||
                  (validcell[0][i] == 6 && validcell[1][i] == 7)||
                  (validcell[0][i] == 7 && validcell[1][i] == 6)||
                  (validcell[0][i] == 0 && validcell[1][i] == 6)||
                  (validcell[0][i] == 1 && validcell[1][i] == 7)||
                  (validcell[0][i] == 6 && validcell[1][i] == 0)||
                  (validcell[0][i] == 7 && validcell[1][i] == 1))
                  )
                {
                    validcell[j][i] = 0;
                }
            }
        }
    }
}
int getMaxIndex(int validcell[][60])
{
    int i, j, maxIndex = 0, maxIndexDanger = 0, counter = 0;
    for (j = 0; j < 3; j++)
    {
        for (i = 0; i < 60; i++)
        {
            if (validcell[j][i] != -1)
            {
                //printf("%d ", validcell[j][i]);
                if (j == 2 && validcell[j][i] > validcell[j][maxIndex])
                {
                    maxIndex = i;
                }
            }
        }
        //printf("\n");
    }
    return maxIndex;
}
void checkvalidcell(int MapArray[][8], int validcell[][60], int bead)
{
    int i, j;
    for (i = 0; i < 8; i++)
    {
        for (j = 0; j < 8; j++)
        {
            if (MapArray[i][j] == 0)
            {
                if ((i + 1) < 8 && MapArray[i + 1][j] != bead && MapArray[i + 1][j] != 0)
                    checkdown(MapArray, validcell, bead, i, j);
                if ((i - 1) >= 0 && MapArray[i - 1][j] != bead && MapArray[i - 1][j] != 0)
                    checkup(MapArray, validcell, bead, i, j);
                if ((j + 1) < 8 && MapArray[i][j + 1] != bead && MapArray[i][j + 1] != 0)
                    checkright(MapArray, validcell, bead, i, j);
                if ((j - 1) >= 0 && MapArray[i][j - 1] != bead && MapArray[i][j - 1] != 0)
                    checkleft(MapArray, validcell, bead, i, j);
                if ((j + 1) < 8 && (i - 1) >= 0 && MapArray[i - 1][j + 1] != bead && MapArray[i - 1][j + 1] != 0)
                    checkupright(MapArray, validcell, bead, i, j);
                if ((j + 1) < 8 && (i + 1) < 8 && MapArray[i + 1][j + 1] != bead && MapArray[i + 1][j + 1] != 0)
                    checkdownright(MapArray, validcell, bead, i, j);
                if ((j - 1) >= 0 && (i - 1) >= 0 && MapArray[i - 1][j - 1] != bead && MapArray[i - 1][j - 1] != 0)
                    checkupleft(MapArray, validcell, bead, i, j);
                if ((j - 1) >= 0 && (i + 1) < 8 && MapArray[i + 1][j - 1] != bead && MapArray[i + 1][j - 1] != 0)
                    checkdownleft(MapArray, validcell, bead, i, j);
            }
        }
    }
}
void checkdown(int MapArray[][8], int validcell[][60], int bead, int x, int y)
{
    int i, j;
    for (i = 1; x + i < 8; i++)
    {
        if (MapArray[x + i][y] == bead)
        {
            for (j = 0; validcell[0][j] != -1; j++)
                ;
            validcell[0][j] = x;
            validcell[1][j] = y;
            validcell[2][j] = i - 1;
            break;
        }
        if (MapArray[x + i][y] == 0)
            break;
    }
}
void checkup(int MapArray[][8], int validcell[][60], int bead, int x, int y)
{
    int i, j;
    for (i = 1; x - i >= 0; i++)
    {
        if (MapArray[x-i][y] == bead)
        {
            for (j = 0; validcell[0][j] != -1; j++);
            validcell[0][j] = x;
            validcell[1][j] = y;
            validcell[2][j] = i - 1;
            break;
        }
        if (MapArray[x - i][y] == 0)
            break;
    }
}
void checkleft(int MapArray[][8], int validcell[][60], int bead, int x, int y)
{
    int i, j;
    for (i = 1; y - i >= 0; i++)
    {
        if (MapArray[x][y - i] == bead)
        {
            for (j = 0; validcell[0][j] != -1; j++)
                ;
            validcell[0][j] = x;
            validcell[1][j] = y;
            validcell[2][j] = i - 1;
            break;
        }
        if (MapArray[x][y - i] == 0)
            break;
    }
}
void checkright(int MapArray[][8], int validcell[][60], int bead, int x, int y)
{
    int i, j;
    for (i = 1; y + i < 8; i++)
    {
        if (MapArray[x][y + i] == bead)
        {
            for (j = 0; validcell[0][j] != -1; j++)
                ;
            validcell[0][j] = x;
            validcell[1][j] = y;
            validcell[2][j] = i - 1;
            break;
        }
        if (MapArray[x][y + i] == 0)
            break;
    }
}
void checkdownright(int MapArray[][8], int validcell[][60], int bead, int x, int y)
{
    int i, j;
    for (i = 1; y + i < 8 && x + i < 8; i++)
    {
        if (MapArray[x + i][y + i] == bead)
        {
            for (j = 0; validcell[0][j] != -1; j++)
                ;
            validcell[0][j] = x;
            validcell[1][j] = y;
            validcell[2][j] = i - 1;
            break;
        }
        if (MapArray[x + i][y + i] == 0)
            break;
    }
}
void checkupright(int MapArray[][8], int validcell[][60], int bead, int x, int y)
{
    int i, j;
    for (i = 1; y + i < 8 && x - i >= 0; i++)
    {
        if (MapArray[x - i][y + i] == bead)
        {
            for (j = 0; validcell[0][j] != -1; j++)
                ;
            validcell[0][j] = x;
            validcell[1][j] = y;
            validcell[2][j] = i - 1;
            break;
        }
        if (MapArray[x - i][y + i] == 0)
            break;
    }
}
void checkupleft(int MapArray[][8], int validcell[][60], int bead, int x, int y)
{
    int i, j;
    for (i = 1; y - i >= 0 && x - i >= 0; i++)
    {
        if (MapArray[x - i][y - i] == bead)
        {
            for (j = 0; validcell[0][j] != -1; j++)
                ;
            validcell[0][j] = x;
            validcell[1][j] = y;
            validcell[2][j] = i - 1;
            break;
        }
        if (MapArray[x - i][y - i] == 0)
            break;
    }
}
void checkdownleft(int MapArray[][8], int validcell[][60], int bead, int x, int y)
{
    int i, j;
    for (i = 1; y - i >= 0 && x + i < 8; i++)
    {
        if (MapArray[x + i][y - i] == bead)
        {
            for (j = 0; validcell[0][j] != -1; j++)
                ;
            validcell[0][j] = x;
            validcell[1][j] = y;
            validcell[2][j] = i - 1;
            break;
        }
        if (MapArray[x + i][y - i] == 0)
            break;
    }
}
