#include <iostream>
#include <map>
using namespace std;

//dynamic solution to the classic narrow art gallery problem 
map <string, int> memo;


int optimize(int gallery[][2], int r, int door, int k, int size){

    if( r == size + 1){
        return 0;
    }

    if(k == size - r + 1) {
        if (door == 0) {
            string key = to_string(r+1) + to_string(0) + to_string(k-1);
            if (memo.count(key)){
                return gallery[r][0] + (memo[key]);
            }else{
                int t = optimize(gallery, r+1, 0, k-1, size);
                memo[key] = t;
                return gallery[r][0] + t;
            }
        } else if (door == 1) {
            string key = to_string(r+1) + to_string(1) + to_string(k-1);
            if(memo.count(key)){
                return gallery[r][1] + memo[key];
            }else{
                int t = optimize(gallery, r+1, 1, k-1, size);
                memo[key] = t;
                return gallery[r][1] + t;
            }

        } else if (door == -1) {
            string key = to_string(r+1) + to_string(0) + to_string(k-1);
            string key2 = to_string(r+1) + to_string(1) + to_string(k-1);
            if(memo.count(key) && memo.count(key2)){ //THIS could be more optimized
                int z = gallery[r][0] + memo[key];
                int o = gallery[r][1] + memo[key2];
                return max(z, o);
            }else{
                int zt = optimize(gallery, r+1, 0, k-1, size);
                int zero = gallery[r][0] + zt;
                memo[key] = zt;
                int ot = optimize(gallery, r+1, 1, k-1, size);
                int one = gallery[r][1] + ot;
                memo[key2] = ot;
                return max(zero, one);
            }
        }
    }
    if( door == 0){
//        int initialzero = gallery[r][0] + optimize(gallery, r+1, 0, k-1, size);
//        int nextcombo = gallery[r][0] + gallery[r][1] + optimize(gallery, r+1, -1, k, size);
//        int final = max(initialzero, nextcombo);
//        return final;
        string key = to_string(r+1) + to_string(0) + to_string(k-1);
        string key2 = to_string(r+1) + to_string(-1) + to_string(k);

        if(memo.count(key) && memo.count(key2)){
            int z = gallery[r][0] + memo[key];
            int n = gallery[r][0] + gallery[r][1] +memo[key2];
            return max(z,n);
        }else{
            int iz = optimize(gallery, r+1, 0, k-1, size);
            int initialzero = gallery[r][0] + iz;

            int nc = optimize(gallery, r+1, -1, k, size);
            int nextcombo = gallery[r][0] + gallery[r][1] + nc;
            memo[key] = iz;
            memo[key2] = nc;
            int final = max(initialzero, nextcombo);
            return final;
        }

    }else if(door == 1){
//        int initialone = gallery[r][1] + optimize(gallery, r+1, 1, k-1, size);
//        int nextcombo = gallery[r][1] + gallery[r][0] + optimize(gallery, r+1, -1, k, size);
//        int final = max(initialone, nextcombo);
//        return final;
        string key = to_string(r+1) + to_string(1) + to_string(k-1);
        string key2 = to_string(r+1) + to_string(-1) + to_string(k);

        if(memo.count(key) && memo.count(key2)){
            int o = gallery[r][1] + memo[key];
            int nc = gallery[r][1] + gallery[r][0] + memo[key2];
            return max(o, nc);
        }else{
            int io = optimize(gallery, r+1, 1, k-1, size);
            int initialone = gallery[r][1] + io;
            int nc = optimize(gallery, r+1, -1, k, size);
            int nextcombo = gallery[r][1] + gallery[r][0] + nc;

            memo[key] = io;
            memo[key2] = nc;
            int final = max(initialone, nextcombo);
            return final;
        }

    }else if(door == -1) {
//        int initialzero = gallery[r][0] + optimize(gallery, r+1, 0, k-1, size);
//        int initialone = gallery[r][1] + optimize(gallery, r+1, 1, k-1, size);
//        int compareto = gallery[r][1] + gallery[r][0] + optimize(gallery, r+1, -1, k, size);
//        int temp = max(initialzero, initialone);
//        int final = max(temp, compareto);
//        return final;
        string key = to_string(r + 1) + to_string(0) + to_string(k - 1);
        string key2 = to_string(r + 1) + to_string(1) + to_string(k - 1);
        string key3 = to_string(r + 1) + to_string(-1) + to_string(k);

        if (memo.count(key) && memo.count(key2) && memo.count(key3)) {
            int iz = gallery[r][0] + memo[key];
            int io = gallery[r][1] + memo[key2];
            int ct = gallery[r][1] + gallery[r][0] + memo[key3];
            int temp = max(iz, io);
            int fin = max(temp, ct);
            return fin;
        } else {
            int iz = optimize(gallery, r + 1, 0, k - 1, size);
            int initialzero = gallery[r][0] + iz;

            int io = optimize(gallery, r + 1, 1, k - 1, size);
            int initialone = gallery[r][1] + io;

            int ct = optimize(gallery, r + 1, -1, k, size);
            int compareto = gallery[r][1] + gallery[r][0] + ct;

            memo[key] = iz;
            memo[key2] = io;
            memo[key3] = ct;
            int temp = max(initialzero, initialone);
            int final = max(temp, compareto);
            return final;
        }

    }
    return 0;
}

void driver(int gallery[][2], int n, int k, int size){
    int startthedrive = optimize(gallery, 0, -1, k, size);
    cout << startthedrive << endl;

}

void foo(int _n, int _k){
    int i = 0, n, k;
    n = _n;
    k = _k;
    int size = 0;

    int gallery[n][2];

    int zeroth = 0, first = 0;
    for(; i < n; i++){
        scanf("%d%d", &zeroth, &first);
        gallery[i][0] = zeroth;
        gallery[i][1] = first;
        size = i;
    }

    driver(gallery, n, k, size);
}

int main() {
    int i=0, n, k;
    while(true){
        scanf("%d%d", &n, &k);
        if(n == 0 && k == 0){
            return 0;
        }


        foo(n, k);
        memo.clear();
        //at the 0 0
    }

    return 0;
}
