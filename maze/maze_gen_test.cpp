//reqs
//#include <bits/stdc++.h>
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <chrono>
#include <thread>
#include <cmath>
#include <complex>
#include <cstring>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <vector>
#include <climits>
#include <stack>
#include <fstream>
using namespace std;

//def
#ifndef ALY
#define ALY
//init
    #pragma GCC optimize("03")
    static int __star = []{
        ios_base::sync_with_stdio(0);
        cin.tie(NULL),cout.tie(NULL);
        return 0;
    }();
//typedef
    using ll = long long;
    using ull = unsigned long long;
    using u8 = uint8_t;
    using u16 = uint16_t;
    using u32 = uint32_t;
    using u64 = uint64_t;
    using in8 = uint8_t;
    using in16 = uint16_t;
    using in32 = uint32_t;
    using in64 = uint64_t;
    using db = long double;
    using str = string;
//pairs
    using pi = pair<int,int>;
    using pl = pair<ll,ll>;
    #define mp make_pair
    #define f first
    #define s second
//vecs
    #define vcA template<class A
    vcA> using V = vector<A>;
    vcA> using MAT = V<V<A>>;
    using vi = V<int>;
    using vb = V<bool>;
    using vl = V<ll>;
    using vd = V<db>;
    using vs = V<str>;
    using vpi = V<pi>;
    using vpl = V<pl>;
    using mat = V<vi>;
//vec ops
    #define sz(x) int((x).size())
    #define bg(x) begin(x)
    #define ed(x) end(x)
    #define all(x) begin(x),end(x)
    #define rall(x) x.rbegin(),x.rend()
    #define srt(x) sort(all(x))
    #define rsz resize
    #define ins insert
    #define pb push_back
    #define eb emplace_back
    #define em empty()
    #define ft front()
    #define bk back()
    #define ppb pop_back()
    #define ppf pop_front()
    #define pp pop()
    #define tp top()
    #define lb lower_bound
    #define ub upper_bound
    vcA> int lwb(V<A>&a,const A&b) { return int(lb(all(a),b)-bg(a)); }
    vcA> int upb(V<A>&a,const A&b) { return int(lb(all(a),b)-bg(a)); }
//loops
    #define FOR(i,a,b) for(int i=(a);i<(b);++i)
    #define F0R(i,a) FOR(i,0,a)
    #define ROF(i,a,b) for(int i=(b)-1;i>=(a);--i)
    #define R0F(i,a) ROF(i,0,a)
    #define xtime(a) F0R(_,a)
    #define each(a,x) for(auto&a:x)
//numbers
    static constexpr int MOD = 1'000'000'007;
    static constexpr int ALTMOD = 998'244'353;
    static constexpr int MX = 200'005;
    static constexpr ll LMX = 1e18;
    static constexpr int XDIR[4]{1,0,-1,0}, YDIR[4]{0,1,0,-1};
//pq
    template<class P> using pqg = priority_queue<P,vector<P>,greater<P>>; //pop lesser
    template<class P> using pql = priority_queue<P,vector<P>,less<P>>; //pop greater
//bitmax & mog
    constexpr int pct(int x) { return __builtin_popcount(x); }
    constexpr int ctz(int x) { return __builtin_ctz(x); } //count trailing zero
    constexpr int clz(int x) { return __builtin_clz(x); } //count leading zero
//math
    // a / b
    ll floored(ll a,ll b) { return a/b-((a^b)>0&&a%b); }
    ll ceiled(ll a,ll b) { return a/b+((a^b)>0&&a%b); }
//minmax
    vcA> bool fx_min(A&a,const A&b) { return b < a ? a = b, 1 : 0; }
    vcA> bool fx_max(A&a,const A&b) { return a < b ? a = b, 1 : 0; }
//prints
    vcA> void printvec(V<A>&a) { each(v,a) { cout << v << ' '; } cout << endl; }
    template<typename C>
    void meow(C num) {
        for(int bits=sizeof(num)*8;bits--;num>>=1) cout << !!(num&1);
        cout << endl;
    }
#endif

// directions for get_next and later calcs
#ifndef DIR
#define DIR
// wall key:
//   0     ^ smaller y
// 3   1   < smaller x
//   2     
const pi dir[4] = {{0,-1},{1,0},{0,1},{-1,0}};
#endif

// util for valid coordinate (within bound) for both pair<int,int> and 2xINT coords
bool valid(pi cur, const int& BX, const int& BY) {
    return !(cur.f < 0 || cur.f >= BX || cur.s < 0 || cur.s >= BY);
}

bool valid(int cx, int cy, const int& BX, const int& BY) {
    return !(cx < 0 || cx >= BX || cy < 0 || cy >= BY);
}

// get next valid random tile to move to
pi get_next(int x, int y, const int& BX, const int& BY) {
    pi cur = {-1,-1};
    while(!valid(cur,BX,BY)) {
        int d = rand() % 4,
            tx = x + dir[d].f,
            ty = y + dir[d].s;
        if(valid({tx,ty},BX,BY))
            cur = {tx,ty};
    }
    return cur;
}

// pair<int,int> equality comparison
bool pi_comp(pi& a, pi& b) {
    return a.f == b.f && a.s == b.s;
}

// sets stack to be the entire random walk
void random_walk(MAT<u8>& walls, const int& BX, const int& BY, stack<pi>& walk) {
    // 0b01000000
    //    ^ 
    //    is in current walk, for loop detection
    int cx = walk.tp.f,
        cy = walk.tp.s;
    // while last tile of walk isn't in maze
    while(!(walls[cx][cy] & 0x80)) {
        // bitmask into walk
        walls[cx][cy] |= 0x40;
        pi next = get_next(cx,cy,BX,BY);
        // current coords are from get_next
        cx = next.f,
        cy = next.s;
        // if is already in walk
        if(walls[cx][cy] & 0x40)
            while(!walk.em && !pi_comp(next,walk.tp)) {
                // reset to non-walk bitmask, including all walls
                walls[walk.tp.f][walk.tp.s] &= 0x0f;
                walk.pp;
            }
        else walk.push({cx,cy});
    }
    // last tile is in maze, no need to bitmask 0b01000000 here 
    // last tile will also be in walk
}

// cleans walls along walk
void clean_path(stack<pi>& walk, MAT<u8>& walls) {
    int px = walk.tp.f,
        py = walk.tp.s;
    walk.pp;
    // while can still backtrack
    while(!walk.em) {
        // cur x, y
        int cx = walk.tp.f,
            cy = walk.tp.s;
        // fix mask to be all 0x8x and not 0x4x
        walls[cx][cy] &= 0x0f; // retain wall state
        walls[cx][cy] ^= 0x80; // toggle maze status
        // adjust wall bitmask according to previous
        // wall key:
        //   2     
        // 3   1   < smaller x, smaller y down
        //   0     
        int key = cx-px + (2*(cy-py));
        switch(key) {
            // where current is above previous
            case(2):
                walls[cx][cy] &= 0b11111110; // ~0x1
                walls[px][py] &= 0b11111011; // ~0x4
                break;
            // where previous is to the left of current
            case(1):
                walls[cx][cy] &= 0b11110111; // ~0x8
                walls[px][py] &= 0b11111101; // ~0x2
                break;
            // where previous is to the right of current
            case(-1):
                walls[cx][cy] &= 0b11111101; // ~0x2
                walls[px][py] &= 0b11110111; // ~0x8
                break;
            // where previous is above current
            case(-2):
                walls[cx][cy] &= 0b11111011; // ~0x4
                walls[px][py] &= 0b11111110; // ~0x1
                break;
        }
        // set previous to cur
        px = cx,
        py = cy;
        walk.pp;
    }
}

// green for integrated, red for alone
void debug_map_print(MAT<u8>& walls, int x, int y) {
    F0R(i,x) {
        F0R(j,y) {
            cout << ((walls[i][j] & 0x80) ? "\x1b[32m1" : "\x1b[31m0");
        }
        cout << endl;
    }
    cout << endl;
}

void print_maze(MAT<str>& cur) {
    // color for better visualization
    cout << "\x1b[92m";
    each(l,cur)
        printvec(l);
    cout << endl;
}

MAT<str> gen_map(int x, int y) {
    int sx, sy, tile_ct;
    // creation
    MAT<u8> walls = MAT<u8>(x,V<u8>(y,0xf));
    // 0b10000000
    //   ^
    //   vis / in maze
    // random walk below:
    stack<pi> walk;
    // starting tile in maze:
    sx = rand() % x,
    sy = rand() % y,
    tile_ct = x * y - 1;
    walls[sx][sy] ^= 0x80;
    // while tiles left
    while(tile_ct) {
        int cx = sx, cy = sy;
        // find unused tile:
        while(walls[cx][cy] & 0x80)
            cx = rand() % x,
            cy = rand() % y;
        // reset walk, insert first tile
        walk = {};
        walk.push({cx,cy});
        // run random walk to generate path
        random_walk(walls,x,y,walk);
        // clean up path bitmask, change tiles needed etc.
        tile_ct -= (sz(walk)-1);
        clean_path(walk,walls);
    }
    // create and print:
    // key:
    //   0     ^ smaller y
    // 3   1   < smaller x
    //   2     
    // setting board    
    int fx_lim = 2*x+1,
        fy_lim = 2*y+1;
    MAT<str> fin = MAT<str>(fx_lim,vs(fy_lim,"0"));
    // print with walls
    F0R(i,x) {
        F0R(j,y) {
            int fx = 2*i+1,
                fy = 2*j+1;
            fin[fx][fy] = " ";
            // iter thru bitmask
            F0R(k,4)
                if(!(walls[i][j] & (1<<k))) {
                    // coordinate validity check
                    int cx = fx+dir[k].f,
                        cy = fy+dir[k].s;
                    if(valid(cx,cy,fx_lim,fy_lim))
                        fin[cx][cy] = " ";
                }
        }
    }
    return fin;
}

int bfs_validation(MAT<str>& cur) {
    queue<pi> q;
    q.push({1,1});
    int ct = 0;
    while(!q.em) {
        int x = q.ft.f,
            y = q.ft.s;
            cur[x][y] = "\x1b[91m1\x1b[92m";
            q.pp;
            ++ct;
            F0R(i,4) {
                int nx = x + dir[i].f,
                    ny = y + dir[i].s;
                if(cur[nx][ny] == " ")
                    q.push({nx,ny});
            }
        // watch bfs lmao
        /*
        print_maze(cur);
        this_thread::sleep_for(chrono::milliseconds(10));
        */
    }
    return ct;
}

int main() {
    // seeding for rand
    // srand(7);
    srand(time(0));
    for(int i = 10; i <= 50; i += 10) {
        FOR(j,0,10) {
            str file_path = "test_mazes/" + to_string(i) + "/" + to_string(j) + ".txt";
            // output to file
            // open in trunc mode to delete all previous contents
            ofstream output(file_path,ios::trunc);
            // generate map and paste each line with \n
            MAT<str> cur_maze = gen_map(i,i);
            each(l,cur_maze) {
                string cur_line = "";
                each(c,l) cur_line += c;
                output << cur_line + "\n";
            }
            output.close();
            int true_ct = 0, test_ct, time;
            each(l,cur_maze)
                each(c,l)
                    true_ct += (c == " ");
            // validation + timing:
            auto start = chrono::high_resolution_clock::now();
            test_ct = bfs_validation(cur_maze);
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double,milli> duration = end - start;
            cout << (true_ct == test_ct ? "\x1b[92m" : "\x1b[91m1") + file_path + " ----------------- " << (int)duration.count() << "ms\n";
        }
        cout << endl;
    }
    // main ret
    return 0;
}
