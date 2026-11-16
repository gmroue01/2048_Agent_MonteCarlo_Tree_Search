#include <iostream>
#include <iomanip>
#include "2048.h"
using namespace std;

void display(const Grid& grid){
    const string line = "+------+------+------+------+";

    cout << line << "\n";
    for (int i = 0; i < N; i++){
        cout << "|" ; 
        for (int j = 0 ; j < N ; j++){
            if(grid[i][j] == 0){
                cout << "      |";
            }
            else{
                cout << setw(5) << grid[i][j] << " |";
            }
        }
        cout << "\n" << line << "\n";
    }
}



int main(){
    Grid g{};

    display(g);


    return 1;
}



