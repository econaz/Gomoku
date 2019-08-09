#ifndef GAME_H
#define GAME_H

#include <vector>
using namespace std;


extern int const chess_size;
class Game
{
public:
    Game();
    ~Game();
    vector<vector<int>> map;
    bool flag;
    bool isWins;
    void start();
    bool isWin(int x,int y);
    bool isDraw();
};

#endif // GAME_H
