//
//  HidatoGenerator.cpp
//  HidatoPuzzle
//
//  Created by Jayyoung Yang on 13/12/2018.
//  Copyright © 2018 Jayyoung Yang. All rights reserved.
//

#include "bits/stdc++.h"

using namespace std;

int vx[] = {1, 1, 0, -1, -1, -1, 0, 1};
int vy[] = {0, -1, -1, -1, 0, 1, 1, 1};
int board[101][101] = {0};

int dfs(int X[][101], int x, int y, int n, int width, int height, int maxNum)
{
    if (n == maxNum)
        return 1;
    
    board[y][x] = n;
    
    for (int i = 0; i < 8; i++)
    {
        int nextX = x + vx[i], nextY = y + vy[i];
        
        if (0 <= nextX && nextX < width &&
            0 <= nextY && nextY < height &&
            board[nextY][nextX] == 0 &&
            (((1 <= X[nextY][nextX] && X[nextY][nextX] <= maxNum) && X[nextY][nextX] == board[y][x] + 1) ||
             X[nextY][nextX] == -1))
        {
            board[nextY][nextX] = board[y][x] + 1;
            if (dfs(X, nextX, nextY, n + 1, width, height, maxNum))
                return 1;
            board[nextY][nextX] = 0;
        }
    }
    return 0;
}

void randomStart(int X[][101], int height, int width, int start[2]) {
    srand((unsigned)time(NULL));
    int x = rand() % width;
    int y = rand() % height;
    while(1) {
        if(X[y][x] == -1) {
            start[0] = x;
            start[1] = y;
            
            return;
        } else {
            x = rand() % width;
            y = rand() % height;
        }
    }
}

void makeHidatoPuzzle(int board[][101], int height, int width, int maxNum) {
    vector<int> randomNums;
    int randomStart = 1;
    randomNums.push_back(randomStart);
    while(1) {
        randomStart += rand() % 13 + 1;
        if(randomStart >= maxNum) break;
        else randomNums.push_back(randomStart);
    }
    randomNums.push_back(maxNum);
    
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            if(board[i][j] == 0) continue;
            int flag = 0;
            for(int k = 0; k < randomNums.size(); k++) {
                if(board[i][j] == randomNums[k]) {
                    flag = 1;
                    break;
                }
            }
            if(flag == 1) continue;
            else board[i][j] = -1;
        }
    }
    
}

void printBoard(int board[][101], int height, int width) {
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
            printf("%2d ", board[i][j]);
        putchar('\n');
    }
}

void makeTxtFile(int board[][101], int height, int width) {
    ofstream out;
    out.open("SoInput.txt");
    
    out << height << " " << width << '\n';
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            out << board[i][j] << " ";
        }
        out << '\n';
    }
    
    out.close();
}

int main()
{
    ifstream in;
    int height, width;
    in.open("GeInput.txt");
    in >> height >> width;
    
    int hidato[101][101];
    int zeroCount = 0;
    
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
        {
            in >> hidato[i][j];
            if (hidato[i][j] == 0)
                zeroCount++;
        }
    int maxNum = height * width - zeroCount;
    
    for(int i = 0; i < height; i++)
        for(int j = 0; j < width; j++)
            if(hidato[i][j] == 1) hidato[i][j] = -1;
    
    int start[2];
    int finish[2];
    randomStart(hidato, height, width, start);
    hidato[start[1]][start[0]] = 1;
    randomStart(hidato, height, width, finish);
    hidato[finish[1]][finish[0]] = maxNum;
    
    board[start[1]][start[0]] = 1;
    
    while(dfs(hidato, start[0], start[1], 1, width, height, maxNum) != 1) {
        hidato[start[1]][start[0]] = -1;
        hidato[finish[1]][finish[0]] = -1;
        board[start[1]][start[0]] = 0;
        randomStart(hidato, height, width, start);
        hidato[start[1]][start[0]] = 1;
        randomStart(hidato, height, width, finish);
        hidato[finish[1]][finish[0]] = maxNum;
        board[start[1]][start[0]] = 1;
    }
    
    makeHidatoPuzzle(board, height, width, maxNum);
    printBoard(board, height, width);
    makeTxtFile(board, height, width);
    
    return 0;
}
