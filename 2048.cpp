#include <iostream>
#include <iomanip>
#include <conio.h>
#include <random>
#include <vector>
#include <cstdio>
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

enum Action { Up,Down,Left,Right,Quit,None};

Action read_action(){
    int ch = _getch();

    if (ch == 0 || ch == 224){
        switch (_getch())
        {
        case 72: return Up;
        case 80: return Down;
        case 75: return Left;
        case 77:return Right;
        default: return None;
        }
    }
    switch (ch) {                          // touches normales
    case 'z': case 'Z': return Up;
    case 's': case 'S': return Down;
    case 'q': case 'Q': return Left;
    case 'd': case 'D': return Right;
    case 27:  case 'x': return Quit;       // Échap ou x
    default:            return None;       // toute autre touche
    }
}

int playmove(Grid &g, Action a, bool &moved){
    switch(a){
        case Up : return moveUp(g,moved);
        case Down: return moveDown(g,moved);
        case Left : return moveLeft(g,moved);
        case Right : return moveRight(g,moved);
        default : moved = false; return 0;
    }
}

void spawn_tile(Grid &g, std::mt19937 rng){
 vector<pair<int,int>> empties;
 for(int r = 0 ; r < N; r++){
    for(int c = 0 ;  c < N; c++){
        if(g[r][c] == 0) empties.push_back({r,c});

    }
 };
 if(empties.empty()) return;


 uniform_int_distribution<int> pick(0, int(empties.size() - 1));
 auto [r,c] = empties[pick(rng)];

 bernoulli_distribution is_two(0.9);
 g[r][c] = is_two(rng) ? 2 : 4;

}



int main()
{
    Grid g{};
    std::mt19937 rng(std::random_device{}());
    
    spawn_tile(g, rng);
    spawn_tile(g, rng);
    
    int score = 0;
    while (true){
        
        display(g);
        printf("Score : %d\n",score);
        Action a = read_action();
        if(a == Quit) break;
        if (a == None) continue;

        bool moved = false;
        score += playmove(g,a,moved);

        if (!moved) continue;
        spawn_tile(g,rng);

    }



    return 1;
}
