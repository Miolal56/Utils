#include "../SegmentTree.h"

inline void fi(int &n){
    char ch;
    while(ch = getchar(), isspace(ch));
    n = ch - '0';
    while(ch = getchar(), !isspace(ch)) n *= 10, n += ch - '0';
}

inline void fi(char &ch){
    while(ch = getchar(), isspace(ch));
}

int mult(int a, int b){
    return a * b;
}

int main(){
    int n, aux, p, a, b;
    char accio;
    while(fi(n), fi(p), n || p){
        vector<int> vec;
        for(int i = 0; i < n; ++i){
            fi(aux);
            if(aux == 0) vec.push_back(0);
            else if(aux < 0) vec.push_back(-1);
            else vec.push_back(1);
        }
        SegmentTree<int> tree = SegmentTree<int>(vec, mult, 1);
        for(int i = 0; i < p; ++i){
            fi(accio), fi(a), fi(b);
            if(accio == 'C'){
                if(b == 0) tree.update(a - 1, 0);
                else if(b < 0) tree.update(a - 1, -1);
                else tree.update(a - 1, 1);
            } else {
                int tmp = tree.get(a - 1, b - 1);
                if (tmp == 0) printf("0");
                else if (tmp > 0) printf("+");
                else printf("-");
            }
        }
        printf("\n");
    }
    return 0;
}
/*
5 4
0 3 4 3 5
? 1 5
? 2 5
C 2 -3
? 2 5
6 1
-1 1 -1 1 -1 1
C 1 2
6 1
-1 1 -1 1 -1 1
? 1 6
0 0

 */