#include <bits/stdc++.h>
using namespace std;

// ====== 容量（总插入 <= 2M），略加余量 ======
static const int MAXN = 2*1024*1024 + 10;

// 隐式 Treap 数组版
int Lc[MAXN], Rc[MAXN], Sz[MAXN];
unsigned int Pri[MAXN];
char Val[MAXN];
int root = 0, tot = 0;       // 根、已用节点数
int cursor_pos = 0;          // 光标：0..Sz[root]

// 最简单的随机：xorshift32（和字符无关）
static uint32_t seed_ = 0x9e3779b9u;
inline uint32_t rnd(){ seed_ ^= seed_<<13; seed_ ^= seed_>>17; seed_ ^= seed_<<5; return seed_; }

inline int getSz(int x){ return x ? Sz[x] : 0; }
inline void pull(int x){
    if(!x) return;
    Sz[x] = getSz(Lc[x]) + getSz(Rc[x]) + 1;
}

inline int new_node(char c){
    int id = ++tot;
    Val[id] = c;
    Lc[id] = Rc[id] = 0;
    Sz[id]  = 1;
    Pri[id] = rnd();
    return id;
}

// split_k：把前 k 个字符切为 A，剩下的为 B（在第 k 个字符“后面”剪开）
void split_k(int cur, int k, int &A, int &B){
    if(!cur){ A = B = 0; return; }
    if(k <= 0){ A = 0; B = cur; return; }
    if(k >= Sz[cur]){ A = cur; B = 0; return; }

    int lsz = Sz[Lc[cur]];
    if(k <= lsz){
        // 前缀全在左边：继续去左子树切，右半与根作为 B
        split_k(Lc[cur], k, A, Lc[cur]);
        B = cur;
        pull(B);
    }else if(k == lsz + 1){
        // 正好切在根后
        A = cur;
        B = Rc[cur];
        Rc[cur] = 0;
        pull(A);
    }else{
        // 还要从右边拿 (k - lsz - 1) 个
        split_k(Rc[cur], k - lsz - 1, Rc[cur], B);
        A = cur;
        pull(A);
    }
}

// merge：把 B 接在 A 后（谁优先级小谁当根，仅影响树形，不动前后顺序）
int merge_treap(int A, int B){
    if(!A || !B) return A + B;
    if(Pri[A] < Pri[B]){
        Rc[A] = merge_treap(Rc[A], B);
        pull(A);
        return A;
    }else{
        Lc[B] = merge_treap(A, Lc[B]);
        pull(B);
        return B;
    }
}

// 把字符串 s 建成一段 treap（逐字 merge，简单直白）
int build_from_string(const string& s){
    int t = 0;
    for(char c : s){
        int id = new_node(c);
        t = merge_treap(t, id);
    }
    return t;
}

// —— 输入工具 ——
// 读下一个不含空白的单词（命令/数字）
string nextToken(){
    int c = getchar();
    while(c==' ' || c=='\n' || c=='\r' || c=='\t') c = getchar();
    string s;
    while(c!=EOF && c!=' ' && c!='\n' && c!='\r' && c!='\t'){
        s.push_back((char)c);
        c = getchar();
    }
    return s;
}
// 读一个非负整数
int nextInt(){
    int c = getchar();
    while(c<'0' || c>'9') c = getchar();
    int x = 0;
    while(c>='0' && c<='9'){ x = x*10 + (c-'0'); c = getchar(); }
    return x;
}
// 读可见字符（ASCII 32..126）共 n 个，忽略 '\n' '\r'
string readVisible(int n){
    string s; s.reserve(n);
    while((int)s.size() < n){
        int c = getchar();
        if(c=='\n' || c=='\r') continue;
        s.push_back((char)c);
    }
    return s;
}

// —— 操作 ——
// Move k：光标到第 k 个字符后（夹在 [0..len] 保险）
inline void Move(int k){
    int len = getSz(root);
    if(k < 0) k = 0;
    if(k > len) k = len;
    cursor_pos = k;
}

// Insert n s：在光标处插入 s，光标位置不变（题意）
inline void Insert(int n, const string& s){
    int A, B;
    split_k(root, cursor_pos, A, B);     // A|B
    int M = build_from_string(s);        // 要贴上的纸带
    root = merge_treap(merge_treap(A, M), B);
    // 光标“不变”指：仍在原来的“切口”位置 → 也就是新段的末尾
    cursor_pos += n;
}

// Delete n：删除光标后的 n 个
inline void DeleteN(int n){
    int A, C; split_k(root, cursor_pos, A, C);   // A|C
    int B, D; split_k(C, n, B, D);               // (要删的)B | D
    // 丢掉 B
    root = merge_treap(A, D);
    // 光标不变：仍在 A 的尾部
}

// 中序把一段打印到 out
void dump(int x, string& out){
    if(!x) return;
    dump(Lc[x], out);
    out.push_back(Val[x]);
    dump(Rc[x], out);
}

// Get n：输出光标后的 n 个字符，光标不变
inline void GetN(int n){
    int A, C; split_k(root, cursor_pos, A, C);
    int B, D; split_k(C, n, B, D);
    string out; out.reserve(n);
    dump(B, out);
    // 输出并换行
    fwrite(out.data(), 1, out.size(), stdout);
    putchar('\n');
    // 拼回原状
    root = merge_treap(merge_treap(A, B), D);
}

// Prev / Next：光标移动 1（题目保证合法）
inline void Prev(){ if(cursor_pos > 0) cursor_pos--; }
inline void Next(){ if(cursor_pos < getSz(root)) cursor_pos++; }

int main(){
    // 用 getchar 系列就不需要 ios 同步设置了
    int T = nextInt();
    while(T--){
        string op = nextToken();
        if(op[0]=='M' || op=="Move"){
            int k = nextInt();
            Move(k);
        }else if(op[0]=='I' || op=="Insert"){
            int n = nextInt();
            string s = readVisible(n);   // 跨行读 n 个可见字符
            Insert(n, s);
        }else if(op[0]=='D' || op=="Delete"){
            int n = nextInt();
            DeleteN(n);
        }else if(op[0]=='G' || op=="Get"){
            int n = nextInt();
            GetN(n);
        }else if(op[0]=='P' || op=="Prev"){
            Prev();
        }else{ // Next
            Next();
        }
    }
    return 0;
}
