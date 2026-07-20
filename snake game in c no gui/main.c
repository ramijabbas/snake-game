#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 20
#define HEIGHT 15

int snakeX[100], snakeY[100];
int length = 3;

int foodX, foodY;

char direction = 'D';

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void createFood()
{
    while (1)
    {
        foodX = rand() % WIDTH;
        foodY = rand() % HEIGHT;

        int ok = 1;

        for (int i = 0; i < length; i++)
        {
            if (snakeX[i] == foodX && snakeY[i] == foodY)
            {
                ok = 0;
                break;
            }
        }

        if (ok)
            return;
    }
}

void draw()
{
    clearScreen();

    for (int y = 0; y < HEIGHT + 2; y++)
    {
        for (int x = 0; x < WIDTH + 2; x++)
        {
            if (y == 0 || y == HEIGHT + 1 || x == 0 || x == WIDTH + 1)
            {
                printf("#");
                continue;
            }

            int printed = 0;

            if (foodX == x - 1 && foodY == y - 1)
            {
                printf("*");
                printed = 1;
            }

            for (int i = 0; i < length; i++)
            {
                if (snakeX[i] == x - 1 && snakeY[i] == y - 1)
                {
                    if (i == 0)
                        printf("O");
                    else
                        printf("o");

                    printed = 1;
                    break;
                }
            }

            if (!printed)
                printf(" ");
        }

        printf("\n");
    }

    printf("\nScore : %d\n", length - 3);
    printf("Move (W A S D): ");
}

void moveSnake()
{
    for (int i = length - 1; i > 0; i--)
    {
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
    }

    if (direction == 'W')
        snakeY[0]--;

    else if (direction == 'S')
        snakeY[0]++;

    else if (direction == 'A')
        snakeX[0]--;

    else if (direction == 'D')
        snakeX[0]++;
}

int collision()
{
    if (snakeX[0] < 0 || snakeX[0] >= WIDTH)
        return 1;

    if (snakeY[0] < 0 || snakeY[0] >= HEIGHT)
        return 1;

    for (int i = 1; i < length; i++)
    {
        if (snakeX[0] == snakeX[i] &&
            snakeY[0] == snakeY[i])
            return 1;
    }

    return 0;
}

void eatFood()
{
    if (snakeX[0] == foodX &&
        snakeY[0] == foodY)
    {
        snakeX[length] = snakeX[length - 1];
        snakeY[length] = snakeY[length - 1];
        length++;

        createFood();
    }
}

int main()
{
    srand(time(NULL));

    snakeX[0] = 5;
    snakeY[0] = 5;

    snakeX[1] = 4;
    snakeY[1] = 5;

    snakeX[2] = 3;
    snakeY[2] = 5;

    createFood();

    while (1)
    {
        draw();

        scanf(" %c", &direction);

        if (direction >= 'a' && direction <= 'z')
            direction -= 32;

        moveSnake();

        if (collision())
            break;

        eatFood();
    }

    printf("\nGAME OVER!\n");
    printf("Final Score : %d\n", length - 3);

    return 0;
}