#include <iostream>
#include <iomanip>
#include "2048.h"
using namespace std;

void display(const Grid &grid)
{
    const string line = "+------+------+------+------+";

    cout << line << "\n";
    for (int i = 0; i < N; i++)
    {
        cout << "|";
        for (int j = 0; j < N; j++)
        {
            if (grid[i][j] == 0)
            {
                cout << "      |";
            }
            else
            {
                cout << setw(5) << grid[i][j] << " |";
            }
        }
        cout << "\n"
             << line << "\n";
    }
}

int moveRight(Grid &g, bool &moved)
{
    int score = 0;
    moved = false;
    for (int r = 0; r < N; r++)
    {
        int tmp[4] = {0, 0, 0, 0};
        int n = 0;
        for (int c = 3; c >= 0; --c)
        {
            if (g[r][c] != 0)
                tmp[n++] = g[r][c];
        }

        int out[4] = {0, 0, 0, 0};
        int k = 0;
        for (int i = 0; i < n;)
        {
            if (i +1 < n && tmp[i] == tmp[i + 1])
            {
                out[k++] = 2 * tmp[i];
                score += 2 * tmp[i];
                i += 2;
            }
            else
            {
                out[k++] = tmp[i++];
            }
        }

        for (int c = 3, i = 0; c >= 0; --c, ++i)
        {
            if (g[r][c] != out[i])
                moved = true;
            g[r][c] = out[i];
        }
    }
    return score;
}

int moveLeft(Grid &g, bool &moved){
    int score = 0;
    moved = false;

    for(int r = 0 ; r < N ; r ++){
        int tmp[4] = {0,0,0,0};
        int n = 0;
        for(int c = 0; c < N ;  c++){
            if(g[r][c] != 0) tmp[n++] = g[r][c];
        }

        int out[4] = {0,0,0,0};
        int k = 0;
        for(int i = 0 ;  i < n ;){
            if(i + 1 < n && tmp[i] == tmp[i+1]){
                out[k++] = 2*tmp[i];
                score += 2* tmp[i];
                i += 2;
            }else{
                out[k++] = tmp[i++];
            }

        }

        for (int c = 0 ; c < N ; c++){
            if(g[r][c] != out[c]) moved = true;
            g[r][c] = out[c] ;

        }
    }
    return score;
}

int moveUp(Grid &g , bool &moved){
    int score = 0;
    moved = false;

    for (int c = 0 ; c < N; c++){

        int tmp[4] = {0,0,0,0};
        int n = 0;
        for(int r = 0 ;  r < N  ; r++){
            if (g[r][c] != 0) tmp[n++] = g[r][c];
        }

        int out[4] = {0,0,0,0};
        int k = 0;
        for(int i = 0 ; i < n;){
            if(i + 1 < n && tmp[i] == tmp[i+1]){
                out[k++] = 2*tmp[i];
                score += 2*tmp[i];
                i += 2;
            }
            else{
                out[k++] = tmp[i++];
            }

        }

        for(int r = 0 ; r < N; r++)
        {
            if(g[r][c] != out[r]) moved = true;

            g[r][c] = out[r];
        }
    }

    return score;
}

int moveDown(Grid &g , bool &moved){
    int score = 0;
    moved = false;

    for (int c = 0 ; c < N; c++){

        int tmp[4] = {0,0,0,0};
        int n = 0;
        for(int r = 3 ;  r >= 0  ; r--){
            if (g[r][c] != 0) tmp[n++] = g[r][c];
        }

        int out[4] = {0,0,0,0};
        int k = 0;
        for(int i = 0 ; i < n;){
            if(i + 1 < n && tmp[i] == tmp[i+1]){
                out[k++] = 2*tmp[i];
                score += 2*tmp[i];
                i += 2;
            }
            else{
                out[k++] = tmp[i++];
            }

        }

        for (int r = 3, i = 0; r >= 0; --r, ++i)
        {

            if(g[r][c] != out[r]) moved = true;

            g[r][c] = out[i];
        }
    }

    return score;
}
int main()
{
    Grid g{};
    g[0][0] = 2;
    g[1][0] = 2;
    bool moved = false;
    display(g);
    moveDown(g, moved);
    display(g);

    return 1;
}
