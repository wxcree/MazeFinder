//
// Created by 汪晓成 on 2019/10/27.
//

#ifndef MAZE_MAZEFINDER_H
#define MAZE_MAZEFINDER_H

#include <iostream>
#include <stack>
class point{
public:
    int x;
    int y;
    point();
    point(int a,int b):x(a),y(b){};
};
using namespace std;
class MazeFinder {
private:
    int x;
    int y;
    int endx;
    int endy;
    stack<point> forkps;
    stack<stack<point>>map;
    stack<point> * current;
    int rnum = 10;
    int lnum =10;
    int maze[10][10]
            {
                    {1,1,1,1,1,1,1,1,1,1},
                    {1,0,0,1,0,0,1,1,0,1},
                    {1,0,0,1,0,0,0,1,0,1},
                    {1,0,0,0,0,1,1,0,0,1},
                    {1,0,1,1,1,0,0,0,0,1},
                    {1,0,0,0,1,0,0,0,0,1},
                    {1,0,1,0,0,0,1,0,0,1},
                    {1,0,1,1,1,0,1,1,0,1},
                    {1,1,0,0,0,0,0,0,0,1},
                    {1,1,1,1,1,1,1,1,1,1}
            };
    bool isFork();
    bool isEnd();
    bool isWall(int x,int y);
    bool isDone(int x,int y);
    bool CanGo(int x,int y);
    int Go();
    bool isSuccess();
public:
    MazeFinder():x(1),y(2),endx(8),endy(8){};
    void Find();
    void MazeShow();
    void ShowMap();
};


#endif //MAZE_MAZEFINDER_H
