#include<iostream>
#include<bits/stdc++.h>
//#include<gmp.h>

using namespace std;

#define N 8

const int M = N + 1;

bool comparation_cratch(bitset<M> a, bitset<M> b);
bitset<M> inc(bitset<M> arg);
bool operator==(bitset<M> a, bitset<M> b);
bool operator!=(bitset<M> a, bitset<M> b);
bitset<M> operator+(bitset<M> a, bitset<M> b);
bitset<M> service_addition_function(bitset<M> a, bitset<M> b);
bitset<M> operator-(bitset<M> a, bitset<M> b);
bitset<M> operator*(bitset<M> a, bitset<M> b);
bitset<M> operator/(bitset<M> a, bitset<M> b);

int main(int argc, char* argv[]) {
    bitset<M> a(6);
    bitset<M> b(5);

    bitset<M> c = a / b;
    cout << c << endl;

    cout << c.to_string() << endl;

    //mpz_t z;
    //mpz_init_set_str(z, c.to_string().c_str(), 2);
    //std::cout << z << std::endl;
    //gmpz_clear(z);
    return 0;
}

bool comparation_cratch(bitset<M> a, bitset<M> b) {
    bitset<M> complement(1);
    b = ~b;
    b = service_addition_function(b, complement);

    bitset<M> c = service_addition_function(a, b);

    if (c[M - 1] == 0)
        return true;
    else
        return false;
}

bitset<M> inc(bitset<M> arg) {
    bitset<M> one(1);
    bitset<M> ans = arg + one;
    return ans;
}

bool operator==(bitset<M> a, bitset<M> b) {
    bool ans = true;        //в битсете вроде из коробки операторы сравнения итак перегружены, но пусть будет
    for (int i = 0; i < M; i++) {
        if (a[i] != b[i]) {
            ans = false;
            break;
        }
    }
    return ans;
}

bool operator!=(bitset<M> a, bitset<M> b) {
    bool ans = !(a == b);
    return ans;
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
    if (c[M - 1] == 1)
        cerr << "overflow error" << endl;
    return c;
}

bitset<M> service_addition_function(bitset<M> a, bitset<M> b) {
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
    //if (c[M - 1] == 1)
        //cerr << "overflow error" << endl;
    return c;
}

bitset<M> operator-(bitset<M> a, bitset<M> b) {
    bitset<M> complement(1);
    b = ~b;
    b = service_addition_function(b, complement);
    bitset<M> c = a + b;
    if (c[M - 1] == 1)
        cerr << "overflow error" << endl;

    return c;
}

bitset<M> operator*(bitset<M> a, bitset<M> b) {
    bitset<M> c(0);
    for (bitset<M> iter(0); iter != b; iter = inc(iter)) {
        c = c + a;
    }
    return c;
}

bitset<M> operator/(bitset<M> a, bitset<M> b) {
    bitset<M> counter(0);
    bitset<M> c = a;
    for (bitset<M> iter(0); comparation_cratch(c, b); iter = inc(iter)) {
        counter = inc(counter);
        c = c - b;
    }
    return counter;
}
