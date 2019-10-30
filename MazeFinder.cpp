//
// Created by 汪晓成 on 2019/10/27.
//

#include "MazeFinder.h"

void MazeFinder::MazeShow() {
    {
        for (int i=0;i<rnum;i++)
        {
            for (int j=0;j<lnum;j++)
            {
                if (maze[i][j] == 1)
                {
                    cout << "#" ;
                }
                else if (maze[i][j]==2)
                {
                    cout << "*";
                }
                else if (maze[i][j]==3)
                {
                    cout << "+";
                }
                else cout << " ";
            }
            cout << endl;
        }
    }
}

bool MazeFinder::isEnd() {
    return 1;
}

bool MazeFinder::isFork() {
    int i = 0;
    if(CanGo(x+1,y))
        i++;
    if(CanGo(x-1,y))
        i++;
    if(CanGo(x,y+1))
        i++;
    if(CanGo(x,y-1))
        i++;
    return i>1;
}

bool MazeFinder::isWall(int x, int y) {
    return maze[x][y]==1;
}

bool MazeFinder::isDone(int x, int y) {
    return maze[x][y]==2;
}

int MazeFinder::Go() {
    int result = 1;
    if(isFork()){//遇到分叉，记录分叉口位置
        forkps.push(point(x,y));
        //cout<<x<<','<<y<<endl;
        result = 3;
    }
    if(CanGo(x+1,y)){
        maze[x][y] = 2;
        x++;
    }
    else if(CanGo(x-1,y)){
        maze[x][y] = 2;
        x--;
    }
    else if(CanGo(x,y+1)){
        maze[x][y] = 2;
        y++;
    }
    else if(CanGo(x,y-1)){
        maze[x][y] = 2;
        y--;
    }
    else if(forkps.size()==0){
        maze[x][y] = 2;
        result = 0;
        cout<<"无解"<<endl;
    } else{//没地方走了，但是可以退回分叉口位置
        maze[x][y] = 2;
        x = forkps.top().x;
        y = forkps.top().y;
        forkps.pop();
        maze[x][y] = 3;
        result = 2;
    }
    maze[x][y] = 3;
    return result;
}

void MazeFinder::Find() {
    current = new stack<point>;
    current->push(point(x,y));
    while (1){
        int flag = Go();
        if(isSuccess()) {
            current->push(point(x,y));
            cout<<"ok"<<endl;
            break;
        }
        if(flag == 0)//无解
            break;
        if(flag == 1)//单纯前进一步
            current->push(point(x,y));
        else if(flag == 3){//遇到分叉路口
            //cout<<current->size()<<endl;
            map.push(*current);
            current = new stack<point>;
            current->push(point(x,y));
        } else if (flag == 2){//跳回记录位置
            current = new stack<point>;
            *current = map.top();
            map.pop();
            //cout<<"map pop"<<endl;
        }
    }
    map.push(*current);
    //cout<<x<<' '<<y<<endl;
}

bool MazeFinder::CanGo(int x, int y) {
    return !isWall(x,y)&&!isDone(x,y);
}

void MazeFinder::ShowMap() {
    while (!map.empty()){
        map.top();
        while (!map.top().empty()){
            maze[map.top().top().x][map.top().top().y] = 9;
            cout<<map.top().top().x<<","<<map.top().top().y<<endl;
            map.top().pop();
        }
        map.pop();
    }
    for (int i=0;i<rnum;i++){
        for (int j=0;j<lnum;j++){
            if (maze[i][j] == 1){
                cout << "#" ;
            }
            else if(maze[i][j]==9){
                cout<<"*";
            }
            else cout << " ";
        }
        cout << endl;
    }
}

bool MazeFinder::isSuccess() {
    return x==endx&&y==endy;
}
