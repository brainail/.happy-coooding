/** @ http://stackoverflow.com/questions/244452/what-is-an-efficient-algorithm-to-find-area-of-overlapping-rectangles

An efficient way of computing this area is to use a sweep algorithm. Let us assume that we sweep a vertical line L(x) through the union of rectangles U:

- first of all, you need to build an event queue Q, which is, in this case, the ordered list of all x-coordinates (left and right) of the rectangles.
- during the sweep, you should maintain a 1D datastructure, which should give you the total length of the intersection of L(x) and U. The important thing is that this length is constant between two consecutive events q and q' of Q. So, if l(q) denotes the total length of L(q+) (i.e. L just on the rightside of q) intersected with U, the area swept by L between events q and q' is exactly l(q)*(q' - q).
- you just have to sum up all these swept areas to get the total one.

We still have to solve the 1D problem. You want a 1D structure, which computes dynamically a union of (vertical) segments. By dynamically, I mean that you sometimes add a new segment, and sometimes remove one.

I already detailed in my answer to this collapsing ranges question how to do it in a static way (which is in fact a 1D sweep). So if you want something simple, you can directly apply that (by recomputing the union for each event). If you want something more efficient, you just need to adapt it a bit:

- assuming that you know the union of segments S1...Sn consists of disjoints segments D1...Dk. Adding Sn+1 is very easy, you just have to locate both ends of Sn+1 amongs the ends of D1...Dk.
- assuming that you know the union of segments S1...Sn consists of disjoints segments D1...Dk, removing segment Si (assuming that Si was included in Dj) means recomputing the union of segments that Dj consisted of, except Si (using the static algorithm).

This is your dynamic algorithm. Assuming that you will use sorted sets with log-time location queries to represent D1...Dk, this is probably the most efficient non-specialized method you can get.
*/
#include <iostream>
#include <vector>
using namespace std;
struct Rectangle
{
    int x[2], y[2];
    Rectangle(int x1, int y1, int x2, int y2) {
        x[0] = x1;
        y[0] = y1;
        x[1] = x2;
        y[1] = y2;
    };
    void print(void) {
        cout << "Rect: " << x[0] << " " << y[0] << " " << x[1] << " " << y[1] << " " << endl;
    };
};
// return the iterator of rec in list
vector<Rectangle *>::iterator bin_search(vector<Rectangle *> &list, int begin, int end, Rectangle *rec)
{
    int mid = (begin + end) / 2;
    if(list[mid]->y[0] == rec->y[0]) {
        if(list[mid]->y[1] == rec->y[1])
            return list.begin() + mid;
        else if(list[mid]->y[1] < rec->y[1]) {
            if(mid == end)
                return list.begin() + mid + 1;
            return bin_search(list, mid + 1, mid, rec);
        } else {
            if(mid == begin)
                return list.begin() + mid;
            return bin_search(list, begin, mid - 1, rec);
        }
    } else if(list[mid]->y[0] < rec->y[0]) {
        if(mid == end) {
            return list.begin() + mid + 1;
        }
        return bin_search(list, mid + 1, end, rec);
    } else {
        if(mid == begin) {
            return list.begin() + mid;
        }
        return bin_search(list, begin, mid - 1, rec);
    }
}
// add rect to rects
void add_rec(Rectangle *rect, vector<Rectangle *> &rects)
{
    if(rects.size() == 0) {
        rects.push_back(rect);
    } else {
        vector<Rectangle *>::iterator it = bin_search(rects, 0, rects.size() - 1, rect);
        rects.insert(it, rect);
    }
}
// remove rec from rets
void remove_rec(Rectangle *rect, vector<Rectangle *> &rects)
{
    vector<Rectangle *>::iterator it = bin_search(rects, 0, rects.size() - 1, rect);
    rects.erase(it);
}
// calculate the total vertical length covered by rectangles in the active set
int vert_dist(vector<Rectangle *> as)
{
    int n = as.size();
    int totallength = 0;
    int start, end;
    int i = 0;
    while(i < n) {
        start = as[i]->y[0];
        end = as[i]->y[1];
        while(i < n && as[i]->y[0] <= end) {
            if(as[i]->y[1] > end) {
                end = as[i]->y[1];
            }
            i++;
        }
        totallength += end - start;
    }
    return totallength;
}
bool mycomp1(Rectangle* a, Rectangle* b)
{
    return (a->x[0] < b->x[0]);
}
bool mycomp2(Rectangle* a, Rectangle* b)
{
    return (a->x[1] < b->x[1]);
}
double findarea(vector<Rectangle *> rects)
{
    vector<Rectangle *> start = rects;
    vector<Rectangle *> end = rects;
    sort(start.begin(), start.end(), mycomp1);
    sort(end.begin(), end.end(), mycomp2);
    // active set
    vector<Rectangle *> as;
    int n = rects.size();
    double totalarea = 0.0f;
    int current = start[0]->x[0];
    int next = 0;
    int i = 0, j = 0;
    // big loop
    while(j < n) {
        // add all recs that start at current
        while(i < n && start[i]->x[0] == current) {
            // add start[i] to AS
            add_rec(start[i], as);
            i++;
        }
        // remove all recs that end at current
        while(j < n && end[j]->x[1] == current) {
            // remove end[j] from AS
            remove_rec(end[j], as);
            j++;
        }
        // find next event x
        if(i < n && j < n) {
            if(start[i]->x[0] <= end[j]->x[1]) {
                next = start[i]->x[0];
            } else {
                next = end[j]->x[1];
            }
        } else if(j < n) {
            next = end[j]->x[1];
        }
        // distance to next event
        int horiz = next - current;
        // figure out vertical dist
        int vert = vert_dist(as);
        totalarea += vert * horiz;
        current = next;
    }
    return totalarea;
}
int main()
{
    vector<Rectangle *> rects;
    rects.push_back(new Rectangle(1,1,7,7));
    rects.push_back(new Rectangle(2,3,8,9));
    rects.push_back(new Rectangle(4.5,3.5,5.5,5.5));
	printf("%.2f\n", findarea(rects));;
}
