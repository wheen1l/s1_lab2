#include<iostream>
#include<vector>
#include<bits/stdc++.h>

using namespace std;

#define M 8

bitset<M> operator+(bitset<M> a, bitset<M> b);

int main() {
    bitset<M> a(1);
    bitset<M> b(8);
    a[1] = 1;
    bitset<M> c = a + b;
    cout << c << endl;
    cout << a[1] + a[0] << endl;
    //cout << b << endl;
    return 0;
}

bitset<M> operator+(bitset<M> a, bitset<M> b) {
    bitset<M> c;
    int overflow = 0;
    for(int i = 0; i < M; i++) {
        if(overflow > 0) {
            c[i] = 1;
            overflow = 0;

        }
        if(a[i] + b[i] + c[i] > 1) {
            overflow = 1;
        }
        c[i] = (a[i] + b[i] + c[i]) % 2;
    }

    return c;
}
