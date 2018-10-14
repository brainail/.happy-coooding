#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct Point {
    int x, y;
    Point() {}
    Point(int px, int py) {
        x = px, y = py;
    }
};

vector<Point> P;
vector<Point> CH;


// 向量OA cross 向量OB。大於零表示從OA到OB為順時針旋轉。
double cross(const Point& o, const  Point& a, const Point& b)
{
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

// 小於。用以找出最低最左邊的點。
bool compare_position(const Point& a, const Point& b)
{
    return (a.y < b.y) || (a.y == b.y && a.x < b.x);
}

// 小於。以P[0]當中心點做角度排序，以逆時針方向排序。
// 若角度一樣，則順序隨便。
bool compare_angle(const Point& a, const Point& b)
{
    return cross(P[0], a, b) > 0;
}

void findConvexHull()
{
    /* 用最低最左邊的點當作是起點。起點必須是凸包的端點。 */
    // 將端點換到第一點。O(N)
    swap(P[0], *min_element(P.begin(), P.end(), compare_position));
    // 其餘各點照角度排序，並以第一點當中心點。O(NlogN)
    sort(P.begin(), P.end(), compare_angle);
    /* 包，逆時針方向。O(N) */
    P.push_back(P[0]);
    CH.push_back(P[0]);
    CH.push_back(P[1]);

    for(int i = 2; i < P.size(); ++i) {
        while(CH.size() >= 2 && cross(CH[ CH.size() - 2 ], CH[ CH.size() - 1 ] , P[i]) < 0) CH.pop_back();

        CH.push_back(P[i]);
    }
}

int main()
{
    P.push_back(Point(100, 0));
    P.push_back(Point(0, 0));
    P.push_back(Point(0, 100));
    P.push_back(Point(100, 100));
    P.push_back(Point(50, 50));
    P.push_back(Point(30, 40));
    findConvexHull();
    vector<Point>::iterator it;

    for(it = CH.begin(); it != CH.end(); ++it)
        printf("%d %d\n", it->x, it->y);

    return 0;
}
