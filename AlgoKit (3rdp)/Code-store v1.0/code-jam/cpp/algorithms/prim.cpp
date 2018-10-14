#include<iostream>

int map[9][9];  // 一張有權重的圖
int dist[9];    // 紀錄目前的MST到圖上各點的距離。
int parent[9];  // 紀錄各個點在MST上的父親是誰
bool visit[9];  // 紀錄各個點是不是已在MST之中

void prim()
{
    for(int i = 0; i < 9; i++) visit[i] = false;

    for(int i = 0; i < 9; i++) dist[i] = 1e9;

    dist[0] = 0;    // 可以選定任何點做為樹根，這裡以第零點做為樹根。
    parent[0] = 0;

    for(int i = 0; i < 9; i++) {
        int a = -1, b = -1, min = 1e9;

        for(int j = 0; j < 9; j++)
            if(!visit[j] && dist[j] < min) {
                a = j;  // 記錄這一條邊
                min = dist[j];
            }

        if(a == -1) break;  // 與起點相連通的MST都已找完

        visit[a] = true;

        for(b = 0; b < 9; b++)
            if(!visit[b] && map[a][b] < dist[b]) {
                dist[b] = map[a][b]; // 這一行與Dijkstra's Algorithm不同
                parent[b] = a;
            }
    }
}

int main()
{
}
