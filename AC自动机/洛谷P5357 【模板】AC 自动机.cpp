#include<iostream>
#include<vector>
#include<string>
using namespace std;
const int MAXN = 200000 + 5;    // Ŀ���ַ�����������
const int MAXS = 200000 + 5;    // ����Ŀ�괮�ܳ�������
const int SIGMA = 26;           // ��ĸ����С

int n;                          // ʵ��Ŀ�괮����
int cnt = 0;                    // ��ǰ�ѷ���Ľڵ���
int edge = 0;                   // ��ͼ�߼���

// AC �Զ������ṹ
int ch[MAXS][SIGMA];            // trie ���ĺ���ָ��
int fail[MAXS];                 // fail ָ��
int end_id[MAXN];               // ��¼ÿ��ģʽ����Ӧ����ֹ�ڵ���

// ͳ��ƥ�����
long long times_cnt[MAXS];      // ÿ���ڵ�ƥ�䵽�Ĵ���

// ���� fail ָ�뷴�����õ���ʽǰ����
int head[MAXS];
int to[MAXS], nxt[MAXS];

// �����õĶ��У�ջ
int que[MAXS];
bool vis[MAXS];

// ��ģʽ������ trie
void insert_pattern(int idx, const string& s) {
    int u = 0;
    for (char c : s) {
        int d = c - 'a';
        if (!ch[u][d]) {
            ch[u][d] = ++cnt;
        }
        u = ch[u][d];
    }
    end_id[idx] = u;
}

// ���� fail ָ�루ͬʱ������ȫ���Ż����Ѳ����ڵ�ת��ָ�� fail��
void build_ac() {
    int l = 0, r = 0;
    // ���ڵ�����ֱ�Ӻ������
    for (int c = 0; c < SIGMA; c++) {
        if (ch[0][c]) {
            que[r++] = ch[0][c];
        }
    }
    // BFS ���� fail
    while (l < r) {
        int u = que[l++];
        for (int c = 0; c < SIGMA; c++) {
            int v = ch[u][c];
            if (v) {
                // ������ʵ���ӣ��� fail ָ�벢���
                fail[v] = ch[fail[u]][c];
                que[r++] = v;
            }
            else {
                // û�к��ӣ���ָ�� fail ����ͬת��
                ch[u][c] = ch[fail[u]][c];
            }
        }
    }
}

// �������мӱߣ�fail[u] -> u
void add_edge(int u, int v) {
    nxt[++edge] = head[u];
    head[u] = edge;
    to[edge] = v;
}

// �ǵݹ������� fail �����ۼ��ӽڵ�� times_cnt
void accumulate_counts(int root) {
    int top = 0;
    que[top++] = root;
    while (top) {
        int u = que[top - 1];
        if (!vis[u]) {
            vis[u] = true;
            // �Ȱ������ӽڵ�ѹջ
            for (int e = head[u]; e; e = nxt[e]) {
                que[top++] = to[e];
            }
        }
        else {
            // �ӽڵ㶼�����꣬��ջ���ۼ�
            top--;
            for (int e = head[u]; e; e = nxt[e]) {
                times_cnt[u] += times_cnt[to[e]];
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ����Ŀ�괮����
    cin >> n;
    string s;
    // ��������ģʽ��
    for (int i = 1; i <= n; i++) {
        cin >> s;
        insert_pattern(i, s);
    }
    // ���� AC �Զ���
    build_ac();

    // �����ƥ���ı�
    cin >> s;
    int u = 0;
    for (char c : s) {
        u = ch[u][c - 'a'];
        times_cnt[u]++;
    }

    // �� fail ָ��ķ�����
    for (int i = 1; i <= cnt; i++) {
        add_edge(fail[i], i);
    }
    // �Ӹ���ʼ�����ۼ�
    accumulate_counts(0);

    // ���ÿ��ģʽ����ƥ�����
    for (int i = 1; i <= n; i++) {
        cout << times_cnt[end_id[i]] << "\n";
    }
    return 0;
}
