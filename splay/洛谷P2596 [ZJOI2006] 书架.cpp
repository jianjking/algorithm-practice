#include<bits/stdc++.h>
using namespace std;

const int mx = 8*10000 + 10;

int zuo[mx], you[mx], father[mx], sz[mx], pos[mx], val[mx];
int cnt, head;

int lr(int i){ return you[father[i]] == i ? 1 : 0; }
void up(int i){ if(i) sz[i] = sz[zuo[i]] + sz[you[i]] + 1; }

void rotato(int i){
    int f = father[i];
    int g = father[f];
    if(lr(i)==0){
        zuo[f] = you[i];
        if(you[i]) father[you[i]] = f;
        you[i] = f;
    }else{
        you[f] = zuo[i];
        if(zuo[i]) father[zuo[i]] = f;
        zuo[i] = f;
    }
    father[f] = i;
    father[i] = g;
    if(g){
        if(you[g]==f) you[g]=i;
        else          zuo[g]=i;
    }else{
        head = i;
    }
    up(f);
    up(i);
}

void splay(int i,int target){
    while(father[i] != target){
        int f = father[i];
        int g = father[f];
        if(g != target){
            if(lr(i) == lr(f)) rotato(f);
            else               rotato(i);
        }
        rotato(i);
    }
    if(target==0) head = i;
}

void add(int value){
    val[++cnt] = value;
    pos[value] = cnt;
    sz[cnt] = 1;
    if(head==0){
        head = cnt;
    }else{
        you[head] = cnt;
        father[cnt] = head;
        splay(cnt, 0);
    }
}

int ranked(int cur,int k){
    while(cur){
        int ls = sz[zuo[cur]];
        if(k == ls + 1) return cur;
        if(k <= ls) cur = zuo[cur];
        else { k -= ls + 1; cur = you[cur]; }
    }
    return 0;
}

int ask(int x){
    int i = pos[x];
    splay(i, 0);
    return sz[zuo[i]] + 1;
}

void move(int a,int b){
    if(a==b) return;
    int L = ranked(head, a-1);
    int R = ranked(head, a+1);
    splay(L, 0);
    splay(R, L);
    int x = zuo[R];
    zuo[R] = 0;
    if(x) father[x] = 0;
    up(R); up(L);

    L = ranked(head, b-1);
    R = ranked(head, b);
    splay(L, 0);
    splay(R, L);
    zuo[R] = x;
    if(x) father[x] = R;
    up(R); up(L);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m; 
    cin >> n >> m;

    add(0);
    for(int i=1;i<=n;i++){
        int v; cin >> v;
        add(v);
    }
    add(n+1);
    int N = n + 2;

    for(int i=0;i<m;i++){
        string op; 
        cin >> op;
        if(op=="Top"){
            int x; cin >> x;
            int rk = ask(x);
            move(rk, 2);
        }else if(op=="Bottom"){
            int x; cin >> x;
            int rk = ask(x);
            move(rk, N-1);
        }else if(op=="Insert"){
            int x,t; cin >> x >> t;
            int rk = ask(x);
            move(rk, rk + t);
        }else if(op=="Ask"){
            int x; cin >> x;
            cout << ask(x) - 2 << '\n';
        }else{ // Query
            int k; cin >> k;
            cout << val[ ranked(head, k+1) ] << '\n';
        }
    }
    return 0;
}
