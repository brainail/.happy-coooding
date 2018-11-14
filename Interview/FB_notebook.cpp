>>>>>>>
>>>>>>> If your are given an Integer Singly linked list. Print it   backwards. 
Constraints: 
1. Do not manipulate the list. (example: do not make it a doubly linked list, 
    do not add or delete elements, do not change any memory location of any element) 
2. O(n) < time < O(n^2) 3. O(1) < space < O(n) 

---
--
for index in 0..<len{
  printNode(node,at:index)
}
--

--
I divided the list in half recursively until I got a single element which i printed. 
I obviously had to return the second half of the list before the first half in recursion. 
Also, my time is O(nlogn) and space was O(logn).
--
---

>>>>>>>
>>>>>>> Given a text and a wildcard pattern, implement wildcard pattern matching algorithm that finds 
if wildcard pattern is matched with text. 
The matching should cover the entire text (not partial text).
The wildcard pattern can include the characters ‘?’ and ‘*’

---
--
bool strmatch(char str[], char pattern[], int n, int m) {
    // empty pattern can only match with
    // empty string
    if (m == 0) return (n == 0);
 
    // lookup table for storing results of
    // subproblems
    bool lookup[n + 1][m + 1];
 
    // initailze lookup table to false
    memset(lookup, false, sizeof(lookup));
 
    // empty pattern can match with empty string
    lookup[0][0] = true;
 
    // Only '*' can match with empty string
    for (int j = 1; j <= m; j++)
        if (pattern[j - 1] == '*') lookup[0][j] = lookup[0][j - 1];
 
    // fill the table in bottom-up fashion
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++)
        {
            // Two cases if we see a '*'
            // a) We ignore ‘*’ character and move
            //    to next  character in the pattern,
            //     i.e., ‘*’ indicates an empty sequence.
            // b) '*' character matches with ith
            //     character in input
            if (pattern[j - 1] == '*')
                lookup[i][j] = lookup[i][j - 1] || lookup[i - 1][j];
 
            // Current characters are considered as
            // matching in two cases
            // (a) current character of pattern is '?'
            // (b) characters actually match
            else if (pattern[j - 1] == '?' || str[i - 1] == pattern[j - 1])
                lookup[i][j] = lookup[i - 1][j - 1];
 
            // If characters don't match
            else lookup[i][j] = false;
        }
    }
 
    return lookup[n][m];
}
--
---

>>>>>>>
>>>>>>> Move all zeroes to end of array

---
--
static void pushZerosToEnd(int arr[], int n)
    {
        int count = 0;  // Count of non-zero elements
 
        // Traverse the array. If element encountered is
        // non-zero, then replace the element at index 'count'
        // with this element
        for (int i = 0; i < n; i++)
            if (arr[i] != 0) // use swap if you don't want the while loop after
                arr[count++] = arr[i]; // here count is
                                       // incremented
 
        // Now all non-zero elements have been shifted to
        // front and 'count' is set as index of first 0.
        // Make all elements 0 from count to end.
        while (count < n)
            arr[count++] = 0;
    }
--
---

>>>>>>>
>>>>>>> Divide two integers without using multiplication, division and mod operator.

---
--
int divide(int dividend, int divisor) {
    long long n = dividend, m = divisor;
    // determine sign of the quotient
    int sign = n < 0 ^ m < 0 ? -1 : 1;
 
    // remove sign of operands
    n = abs(n), m = abs(m);
 
    // q stores the quotient in computation
    long long q = 0;
 
    // test down from the highest bit
    // accumulate the tentative value for valid bits
    for (long long t = 0, i = 31; i >= 0; i--)
        if (t + (m << i) <= n)
            t += m << i, q |= 1LL << i;
 
    // assign back the sign
    if (sign < 0) q = -q;
 
    // check for overflow and return
    return q >= INT_MAX || q < INT_MIN ? INT_MAX : q;
}    
--

--
Use log_E, then pow(E, log_E(A) - log_E(B)) ...
--
---

>>>>>>>
>>>>>>> Finding three elements in an array whose sum is closest to a given number

---
--
sort() ...

for (i in 1..n-2) {
  j = i+1  // Start right after i.
  k = n    // Start at the end of the array.

  while (k > j) {
    // We got a match! All done.
    if (A[i] + A[j] + A[k] == S) return (A[i], A[j], A[k])

        // check diff

    // We didn't match. Let's try to get a little closer:
    //   If the sum was too big, decrement k.
    //   If the sum was too small, increment j.
    (A[i] + A[j] + A[k] > S) ? k-- : j++
  }
  // When the while-loop finishes, j and k have passed each other and there's
  // no more useful combinations that we can try with this i.
}
--

--
// exact
// K is the sum that we are looking for
for i 1..n
    int s1 = K - A[i]
    for j 1..i
        int s2 = s1 - A[j]
        if (set.contains(s2))
            print the numbers
    set.add(A[i])
--
---

>>>>>>>
>>>>>>> How to check if a number is a power of 2

---
--
bool IsPowerOfTwo(ulong x) {
    return (x != 0) && ((x & (x - 1)) == 0);
}
--
---

>>>>>>>
>>>>>>> You are given a set of points on x axis (consumers) 
Also you are given a set of points on a plane (producer) 
For every consumer print the nearest producer. 

---
--
def overtakes(p1, p2):
    return 0.5*float(p2[1]**2  - p1[1]**2 + p2[0]**2 - p1[0]**2)/(p2[0] - p1[0])

def getNearest(consumers, producers):
    d = deque()
    for p in producers:
        if len(d) == 0:
            d.append((p, -10**9)) # or min(consumers) - 1
            continue
        cross = overtakes(d[-1][0], p)
        while len(d) > 1 and d[-1][1] > cross:
            d.pop()
            cross = overtakes(d[-1][0], p)
        d.append((p, cross))
    res = []
    idx = 0
    for c in consumers:
        while len(d) > 1 and c >= d[1][1]:
            d.popleft()
        res.append(d[0][0])
    return res
--
---

>>>>>>
>>>>>> Given a sorted array, remove the duplicates in place such that each element appear only 
once and return the new length.

---
--
public int removeDuplicates(int[] A) {
        int j = 0;
        if(A.length == 0)
            return 0;
        for(int i = 1; i < A.length; ++i) {
            if(A[i] != A[j]) {
                j++;
                A[j] = A[i];
            }
        }
        return j + 1;
    }
--
---

>>>>>>>
>>>>>>> Given n non-negative integers representing the histogram’s bar height where the width of each bar is 1, 
find the area of largest rectangle in the histogram.

---
--
int getMaxArea(int hist[], int n)
{
    // Create an empty stack. The stack holds indexes of hist[] array
    // The bars stored in stack are always in increasing order of their
    // heights.
    stack<int> s;
 
    int max_area = 0; // Initalize max area
    int tp;  // To store top of stack
    int area_with_top; // To store area with top bar as the smallest bar
 
    // Run through all bars of given histogram
    int i = 0;
    while (i < n)
    {
        // If this bar is higher than the bar on top stack, push it to stack
        if (s.empty() || hist[s.top()] <= hist[i])
            s.push(i++);
 
        // If this bar is lower than top of stack, then calculate area of rectangle 
        // with stack top as the smallest (or minimum height) bar. 'i' is 
        // 'right index' for the top and element before top in stack is 'left index'
        else
        {
            tp = s.top();  // store the top index
            s.pop();  // pop the top
 
            // Calculate the area with hist[tp] stack as smallest bar
            area_with_top = hist[tp] * (s.empty() ? i : i - s.top() - 1);
 
            // update max area, if needed
            if (max_area < area_with_top)
                max_area = area_with_top;
        }
    }
 
    // Now pop the remaining bars from stack and calculate area with every
    // popped bar as the smallest bar
    while (s.empty() == false)
    {
        tp = s.top();
        s.pop();
        area_with_top = hist[tp] * (s.empty() ? i : i - s.top() - 1);
 
        if (max_area < area_with_top)
            max_area = area_with_top;
    }
 
    return max_area;
}
--

--
int ans = 0;
vector<int> d (m, -1), d1 (m), d2 (m);
stack<int> st;
for (int i=0; i<n; ++i) {
    for (int j=0; j<m; ++j)
        if (a[i][j] == 1)
            d[j] = i;
    while (!st.empty()) st.pop();
    for (int j=0; j<m; ++j) {
        while (!st.empty() && d[st.top()] <= d[j])  st.pop();
        d1[j] = st.empty() ? -1 : st.top();
        st.push (j);
    }
    while (!st.empty()) st.pop();
    for (int j=m-1; j>=0; --j) {
        while (!st.empty() && d[st.top()] <= d[j])  st.pop();
        d2[j] = st.empty() ? m : st.top();
        st.push (j);
    }
    for (int j=0; j<m; ++j)
        ans = max (ans, (i - d[j]) * (d2[j] - d1[j] - 1));
}
--
---

>>>>>>>
>>>>>>> The gray code is a binary numeral system where two successive values differ in only one bit. 
Given a non-negative integer n representing the total number of bits 

---
--
public ArrayList<Integer> grayCode(int n) {
        ArrayList<Integer> sol = new ArrayList<Integer>();
        if(n == 0) {
            sol.add(0);
            return sol;
        } else {
            ArrayList<Integer> previous = grayCode(n - 1);
            sol.addAll(previous);
            for(int i = previous.size() - 1; i >= 0; --i) {
                sol.add((int)Math.pow(2.0, n - 1) + previous.get(i));
            }
            return sol;
        }
    }
--

--
int g (int n) {
    return n ^ (n >> 1);
}
--
---


>>>>>>>
>>>>>>> Max palindrome

---
--
Hashing
--

--
// odd
vector<int> d1 (n);
int l=0, r=-1;
for (int i=0; i<n; ++i) {
    int k = (i>r ? 0 : min (d1[l+r-i], r-i)) + 1;
    while (i+k < n && i-k >= 0 && s[i+k] == s[i-k])  ++k;
    d1[i] = k--;
    if (i+k > r)
        l = i-k,  r = i+k;
}

// even
vector<int> d2 (n);
l=0, r=-1;
for (int i=0; i<n; ++i) {
    int k = (i>r ? 0 : min (d2[l+r-i+1], r-i+1)) + 1;
    while (i+k-1 < n && i-k >= 0 && s[i+k-1] == s[i-k])  ++k;
    d2[i] = --k;
    if (i+k-1 > r)
        l = i-k,  r = i+k-1;
}
--
---


>>>>>>
>>>>>> Given two words and a dictionary, print the path from one word to the next changing one letter at a time  

---
--
build graph + BFS
--
---

>>>>>>
>>>>>> Find longest increasing subarray in a given array  

---
--
// n^2
for (int i=0; i<n; ++i) {
    d[i] = 1;
    for (int j=0; j<i; ++j)
        if (a[j] < a[i]) d[i] = max (d[i], 1 + d[j]);
}
--

--
// nlogn
int d[MAXN];
d[0] = -INF;
for (int i=1; i<=n; ++i)
    d[i] = INF;
 
for (int i=0; i<n; i++) {
    int j = int (upper_bound (d.begin(), d.end(), a[i]) - d.begin());
    if (d[j-1] < a[i] && a[i] < d[j])
        d[j] = a[i];
}

// nlogn
// fenwick for max, squeeze numbers (if big)
/*
void init (int nn)
{
    n = nn;
    t.assign (n, INF);
}

int getmin (int r)
{
    int result = INF;
    for (; r >= 0; r = (r & (r+1)) - 1)
        result = min (result, t[r]);
    return result;
}

void update (int i, int new_val)
{
    for (; i < n; i = (i | (i+1)))
        t[i] = min (t[i], new_val);
}

void init (vector<int> a)
{
    init ((int) a.size());
    for (unsigned i = 0; i < a.size(); i++)
        update (i, a[i]);
}
*/
--
---

>>>>>>
>>>>>> Substring with Concatenation of All Words in any order

---
--
// travel all the words combinations to maintain a window
    // there are wl(word len) times travel
    // each time, n/wl words, mostly 2 times travel for each word
    // one left side of the window, the other right side of the window
    // so, time complexity O(wl * 2 * N/wl) = O(2N)
    vector<int> findSubstring(string S, vector<string> &L) {
        vector<int> ans;
        int n = S.size(), cnt = L.size();
        if (n <= 0 || cnt <= 0) return ans;
        
        // init word occurence
        unordered_map<string, int> dict;
        for (int i = 0; i < cnt; ++i) dict[L[i]]++;
        
        // travel all sub string combinations
        int wl = L[0].size();
        for (int i = 0; i < wl; ++i) {
            int left = i, count = 0;
            unordered_map<string, int> tdict;
            for (int j = i; j <= n - wl; j += wl) {
                string str = S.substr(j, wl);
                // a valid word, accumulate results
                if (dict.count(str)) {
                    tdict[str]++;
                    if (tdict[str] <= dict[str]) 
                        count++;
                    else {
                        // a more word, advance the window left side possiablly
                        while (tdict[str] > dict[str]) {
                            string str1 = S.substr(left, wl);
                            tdict[str1]--;
                            if (tdict[str1] < dict[str1]) count--;
                            left += wl;
                        }
                    }
                    // come to a result
                    if (count == cnt) {
                        ans.push_back(left);
                        // advance one word
                        tdict[S.substr(left, wl)]--;
                        count--;
                        left += wl;
                    }
                }
                // not a valid word, reset all vars
                else {
                    tdict.clear();
                    count = 0;
                    left = j + wl;
                }
            }
        }
        
        return ans;
    }
--
----

>>>>>>
>>>>>> kth largest

---
--
public static int findKthLargestUsingMedian(Integer[] array, int k) {
        // Step 1: Divide the list into n/5 lists of 5 element each.
        int noOfRequiredLists = (int) Math.ceil(array.length / 5.0);
        // Step 2: Find pivotal element aka median of medians.
        int medianOfMedian =  findMedianOfMedians(array, noOfRequiredLists);
        //Now we need two lists split using medianOfMedian as pivot. All elements in list listOne will be grater than medianOfMedian and listTwo will have elements lesser than medianOfMedian.
        List<Integer> listWithGreaterNumbers = new ArrayList<>(); // elements greater than medianOfMedian
        List<Integer> listWithSmallerNumbers = new ArrayList<>(); // elements less than medianOfMedian
        for (Integer element : array) {
            if (element < medianOfMedian) {
                listWithSmallerNumbers.add(element);
            } else if (element > medianOfMedian) {
                listWithGreaterNumbers.add(element);
            }
        }
        // Next step.
        if (k <= listWithGreaterNumbers.size()) return findKthLargestUsingMedian((Integer[]) listWithGreaterNumbers.toArray(new Integer[listWithGreaterNumbers.size()]), k);
        else if ((k - 1) == listWithGreaterNumbers.size()) return medianOfMedian;
        else if (k > (listWithGreaterNumbers.size() + 1)) return findKthLargestUsingMedian((Integer[]) listWithSmallerNumbers.toArray(new Integer[listWithSmallerNumbers.size()]), k-listWithGreaterNumbers.size()-1);
        return -1;
    }

    public static int findMedianOfMedians(Integer[] mainList, int noOfRequiredLists) {
        int[] medians = new int[noOfRequiredLists];
        for (int count = 0; count < noOfRequiredLists; count++) {
            int startOfPartialArray = 5 * count;
            int endOfPartialArray = startOfPartialArray + 5;
            Integer[] partialArray = Arrays.copyOfRange((Integer[]) mainList, startOfPartialArray, endOfPartialArray);
            // Step 2: Find median of each of these sublists.
            int medianIndex = partialArray.length/2;
            medians[count] = partialArray[medianIndex];
        }
        // Step 3: Find median of the medians.
        return medians[medians.length / 2];
    }
--
---

/*
Z-Z-Z-Z_Z
vector<int> z_function (string s) {
    int n = (int) s.length();
    vector<int> z (n);
    for (int i=1, l=0, r=0; i<n; ++i) {
        if (i <= r)
            z[i] = min (r-i+1, z[i-l]);
        while (i+z[i] < n && s[z[i]] == s[i+z[i]])
            ++z[i];
        if (i+z[i]-1 > r)
            l = i,  r = i+z[i]-1;
    }
    return z;
}
*/

/*
KMPKMPKMPKMP
vector<int> prefix_function (string s) {
    int n = (int) s.length();
    vector<int> pi (n);
    for (int i=1; i<n; ++i) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])  ++j;
        pi[i] = j;
    }
    return pi;
}
*/

/*
LONG ARITHMETICS

Сложение
Прибавляет к числу a число b и сохраняет результат в a:

int carry = 0;
for (size_t i=0; i<max(a.size(),b.size()) || carry; ++i) {
    if (i == a.size())
        a.push_back (0);
    a[i] += carry + (i < b.size() ? b[i] : 0);
    carry = a[i] >= base;
    if (carry)  a[i] -= base;
}
Вычитание
Отнимает от числа a число b (a \ge b) и сохраняет результат в a:

int carry = 0;
for (size_t i=0; i<b.size() || carry; ++i) {
    a[i] -= carry + (i < b.size() ? b[i] : 0);
    carry = a[i] < 0;
    if (carry)  a[i] += base;
}
while (a.size() > 1 && a.back() == 0)
    a.pop_back();
Здесь мы после выполнения вычитания удаляем лидирующие нули, чтобы поддерживать предикат о том, что таковые отсутствуют.

Умножение длинного на короткое
Умножает длинное a на короткое b (b < {\rm base}) и сохраняет результат в a:

int carry = 0;
for (size_t i=0; i<a.size() || carry; ++i) {
    if (i == a.size())
        a.push_back (0);
    long long cur = carry + a[i] * 1ll * b;
    a[i] = int (cur % base);
    carry = int (cur / base);
}
while (a.size() > 1 && a.back() == 0)
    a.pop_back();
Здесь мы после выполнения деления удаляем лидирующие нули, чтобы поддерживать предикат о том, что таковые отсутствуют.

(Примечание: способ дополнительной оптимизации. Если скорость работы чрезвычайно важна, то можно попробовать заменить два деления одним: посчитать только целую часть от деления (в коде это переменная carry), а затем уже посчитать по ней остаток от деления (с помощью одной операции умножения). Как правило, этот приём позволяет ускорить код, хотя и не очень значительно.)

Умножение двух длинных чисел
Умножает a на b и результат сохраняет в c:

lnum c (a.size()+b.size());
for (size_t i=0; i<a.size(); ++i)
    for (int j=0, carry=0; j<(int)b.size() || carry; ++j) {
        long long cur = c[i+j] + a[i] * 1ll * (j < (int)b.size() ? b[j] : 0) + carry;
        c[i+j] = int (cur % base);
        carry = int (cur / base);
    }
while (c.size() > 1 && c.back() == 0)
    c.pop_back();
Деление длинного на короткое
Делит длинное a на короткое b (b < {\rm base}), частное сохраняет в a, остаток в carry:

int carry = 0;
for (int i=(int)a.size()-1; i>=0; --i) {
    long long cur = a[i] + carry * 1ll * base;
    a[i] = int (cur / b);
    carry = int (cur % b);
}
while (a.size() > 1 && a.back() == 0)
    a.pop_back();
/*
