/*
 *  Problem:  POJ 1204
 *  Source:   Southwestern Europe 2002
 *  Description:
 *    Given a 2D char table containing only upper letters.
 *    And also give you some query strings. You're required to find
 *    the position of query strings in the table.
 *  Algorithm:
 *    Trie tree search(A simplified trie graph which save a lot of
 *    memory space).
 *  Reference: Trie Graph paper -> wc2006, maigo.
 * */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXSIZE = 1000;
const int MAXALPHA = 26;
const int MAXDIR = 8;
const int dx[] = {-1, -1,  0, +1, +1, +1,  0, -1};
const int dy[] = { 0, +1, +1, +1,  0, -1, -1, -1};

struct TrieNode {
  int end, danger;
  TrieNode *child[MAXALPHA], *prefix;
  TrieNode() {
    end = -1;
    danger = 0;
    prefix = NULL;
    memset(child, 0, sizeof(child));
  }
};

int row, col, words, ans[MAXSIZE][3];
char puzzle[MAXSIZE+5][MAXSIZE+5];
char buf[MAXSIZE];
TrieNode root, *que[MAXSIZE * MAXSIZE];

inline int getChar(const char ch) {
  return ch - 'A';
}

inline bool inside(const int x, const int y) {
  if (x >= 0 && x < row && y >= 0 && y < col)
    return true;
  else
    return false;
}

void addWord(char *pattern, int wordID) {
  TrieNode *p = &root;
  for (char *cp = pattern; *cp; cp++) {
    if (p->child[getChar(*cp)] == NULL)
      p->child[getChar(*cp)] = new TrieNode();
    p = p->child[getChar(*cp)];
  }
  p->end = wordID;
  p->danger = 1;
}

void clear(TrieNode *p) {
  for (int i = 0; i < MAXALPHA; i++)
    if (p->child[i]) clear(p->child[i]);
  delete p;
}

// the main procedure of building a trie tree.
void build_trie_tree() {
  TrieNode *p, *q;
  int i, front, rear;
  front = rear = 0;

  root.prefix = &root;
  for (i = 0; i < MAXALPHA; i++) if (p = root.child[i]) {
    p->prefix = &root;
    que[rear++] = p;
  }

  while (front < rear) {
    TrieNode *node = que[front++];
    for (i = 0; i < MAXALPHA; i++) if (p = node->child[i]) {
      q = node->prefix;
      while (q != &root && q->child[i] == NULL) q = q->prefix;
      if (q->child[i] == NULL) p->prefix = &root;
      else p->prefix = q->child[i];

      //p->danger = p->danger || p->prefix->danger;
      if (!p->danger && p->prefix->danger) {
        p->danger = p->prefix->danger;
        p->end = p->prefix->end;
      }
      que[rear++] = p;
    }
  }
}

void input() {
  int i;
  scanf("%d%d%d", &row, &col, &words);
  for (i = 0; i < row; i++)
    scanf("%s", puzzle[i]);
  for (i = 0; i < words; i++) {
    scanf("%s", buf);
    int len = strlen(buf);
    reverse(buf, buf + len);
    addWord(buf, i);
  }
}

void search(int x, int y, int d) {
  TrieNode *p = &root;
  while (inside(x, y)) {
    int ch = puzzle[x][y]-'A';
    while (p != &root && p->child[ch] == NULL)
      p = p->prefix;
    if (p->child[ch]) p = p->child[ch];
    if (p->danger) {
      // go back to find all the occurance of query strings.
      for (TrieNode *q = p; q != &root; q=q->prefix) {
        ans[q->end][0] = x;
        ans[q->end][1] = y;
        ans[q->end][2] = d;
      }
    }
    x = x - dx[d];
    y = y - dy[d];
  }
}

void solve() {
  int i, j;
  for (j = 0; j < col; j++) search(0, j, 0); // A
  for (j = 0; j < col; j++) search(0, j, 1); // B
  for (i = 0; i < row; i++) search(i, col-1, 1); // B
  for (i = 0; i < row; i++) search(i, col-1, 2); // C
  for (i = 0; i < row; i++) search(i, col-1, 3); // D
  for (j = 0; j < col; j++) search(row-1, j, 3); // D
  for (j = 0; j < col; j++) search(row-1, j, 4); // E
  for (j = 0; j < col; j++) search(row-1, j, 5); // F
  for (i = 0; i < row; i++) search(i, 0, 5); // F
  for (i = 0; i < row; i++) search(i, 0, 6); // G
  for (i = 0; i < row; i++) search(i, 0, 7); // H
  for (j = 0; j < col; j++) search(0, j, 7); // H

  for (i = 0; i < words; i++)
    printf("%d %d %c\n", ans[i][0], ans[i][1], ans[i][2] + 'A');
}

int main() {
  input();
  build_trie_tree();
  solve();
  clear(&root);
return 0;
}

