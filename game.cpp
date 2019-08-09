#include "game.h"
#include <cmath>

Game::Game()
{
}

void Game::start()
{
    map.clear();
    for (int i = 0;i< chess_size;i++) {
        vector<int> line;
        for (int j=0;j< chess_size;j++) {
           line.push_back(0);
        }
        map.push_back(line);
    }
    flag = true;
    isWins = false;
}

bool Game::isWin(int x,int y)
{
    //对角线检查
    int size = 0;
    int startLengthX = x - 0;
    int startLengthY = y - 0;
    int startDistence = min(startLengthX,startLengthY);
    if(startDistence > 4){
        startDistence = 4;
    }
    int startX = x - startDistence;
    int startY = y - startDistence;

    int endLengthX = chess_size -1 - x;
    int endLengthY = chess_size -1 - y;
    int endDistance = min(endLengthX,endLengthY);
    if (endDistance > 4){
        endDistance = 4;
    }
    int endX = x + endDistance;
    int endY = y + endDistance;



    vector<unsigned long>::size_type useEndX = static_cast<unsigned long>(endX);

    while(true){
        vector<unsigned long>::size_type useStartX = static_cast<unsigned long>(startX);
        vector<unsigned long>::size_type useStartY = static_cast<unsigned long>(startY);
        if(useStartX == useEndX){
            break;
        }
        if(map[useStartX][useStartY] == map[useStartX+1][useStartY+1]){
            size++;
        }else {
            size = 0;
        }
        if(size == 4){
            return true;
        }
        startX += 1;
        startY += 1;
    }

    //斜对角线
    size = 0;
    startLengthX = x - 0;
    startLengthY = chess_size -1 - y;
    startDistence = min(startLengthX,startLengthY);
    if (startDistence > 4){
        startDistence = 4;
    }
    startX = x - startDistence;
    startY = y + startDistence;

    endLengthX = chess_size -1 - x;
    endLengthY = y - 0;
    endDistance = min(endLengthX,endLengthY);
    if(endDistance > 4){
        endDistance = 4;
    }
    endX = x + endDistance;
    endY = y - endDistance;

    useEndX = static_cast<unsigned long>(endX);

    while(true){
        vector<unsigned long>::size_type useStartX = static_cast<unsigned long>(startX);
        vector<unsigned long>::size_type useStartY = static_cast<unsigned long>(startY);
        if(useStartX == useEndX){
            break;
        }
        if(map[useStartX][useStartY] == map[useStartX+1][useStartY-1]){
            size++;
        }else {
            size = 0;
        }
        if(size == 4) return true;
        startX += 1;
        startY -= 1;
    }

    //列检查
    size = 0;
    startY = y - 4 >=0 ? y-4 : 0;
    endY = y + 4 < chess_size ? y+4 : chess_size -1;
     for (;startY < endY;startY++) {
         vector<unsigned long>::size_type useStartY = static_cast<unsigned long>(startY);
          vector<unsigned long>::size_type useStartX = static_cast<unsigned long>(x);
          if(map[useStartX][useStartY] == map[useStartX][useStartY+1]){
              size++;
          }
          else{
              size = 0;
          }
          if(size == 4) return true;
     }

   //行检查e
   size = 0;
   startX = x - 4 >=0 ? x - 4: 0;
   endX = x + 4 < chess_size ? x + 4 : chess_size -1;
    for (;startX < endX;startX++) {
        vector<unsigned long>::size_type useStartX = static_cast<unsigned long>(startX);
         vector<unsigned long>::size_type useStartY = static_cast<unsigned long>(y);
         if(map[useStartX][useStartY] == map[useStartX+1][useStartY]){
             size++;
         }
         else{
             size = 0;
         }
         if(size == 4) return true;
    }
    return false;
}

bool Game::isDraw()
{

    for (int i = 0;i<chess_size;i++) {
        for (int j = 0;j<chess_size;j++) {
            if(map[i][j] == 0){
                return false;
            }
        }
    }
    return true;
}
