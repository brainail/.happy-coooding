#include<iostream>
#include<queue>
using namespace std;

bool map[100][100]; // 一張圖，資料結構為adjacency matrix。
bool visit[100];    // 紀錄圖上的點是否遍歷過，有遍歷過為true。

void DFS(int s)
{
    visit[s] = true;    // 標記為已檢查

    for(int t = 0; t < 100; t++)
        if(map[s][t] && !visit[t])
            DFS(t);
}

void BFS(int s)
{
    queue<int> q;
    q.push(s);
    visit[s] = true;

    while(!q.empty()) {
        int cur = q.front();
        q.pop();
        visit[cur] = true;

        for(int t = 0; t < 100; t++)
            if(map[s][t] && !visit[t])
                q.push(s);
    }
}

int main()
{
    DFS(5); //從5號node開始DFS
    BFS(5); //從5號node開始BFS
}
