//
//  main.cpp
//  HidatoPuzzle
//
//  Created by Jayyoung Yang on 17/11/2018.
//  Copyright © 2018 Jayyoung Yang. All rights reserved.
//

#include "bits/stdc++.h"

using namespace std;

int vx[] = {1,1,0,-1,-1,-1,0,1};
int vy[] = {0,-1,-1,-1,0,1,1,1};
int board[101][101] = {0};

int dfs(int X[][101],int x, int y, int n, int width, int height, int maxNum) {
    if(n == maxNum) return 1;
    
    board[y][x] = n;
    
    for(int i = 0; i < 8; i++) {
        int nextX = x + vx[i], nextY = y + vy[i];
        
        if(0 <= nextX && nextX < width
           && 0 <= nextY && nextY < height
           && board[nextY][nextX] == 0
           && (((1 <= X[nextY][nextX] && X[nextY][nextX] <= maxNum) && X[nextY][nextX] == board[y][x] + 1)
               || X[nextY][nextX] == -1)) {
               board[nextY][nextX] = board[y][x] + 1;
               if (dfs(X, nextX, nextY, n + 1, width, height, maxNum))
                   return 1;
               board[nextY][nextX] = 0;
           }
    }
    
    
    return 0;
}

int main() {
    int height, width;
    scanf("%d %d", &height, &width);
    
    int hidato[101][101];
    int startX, startY;
    int zeroCount = 0;
    
    for(int i = 0; i <height; i++)
        for(int j = 0; j < width; j++) {
            scanf("%d", &hidato[i][j]);
            if(hidato[i][j] == 1) {
                startX = j, startY = i;
            }
            if(hidato[i][j] == 0) zeroCount++;
        }
    int maxNum = height * width - zeroCount;
    
    board[startY][startX] = 1;
    
    dfs(hidato, startX, startY, 1, width, height, maxNum);
    
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++)
            printf("%2d ", board[i][j]);
        putchar('\n');
    }
    
    return 0;
}
