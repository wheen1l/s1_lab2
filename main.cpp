#include<iostream>
#include<bits/stdc++.h>

using namespace std;

#define N 32

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
bitset<M> operator%(bitset<M> a, bitset<M> b);
bitset<M> str_to_bit(string s);
string bit_to_str(bitset<M> b);

int main(int argc, char* argv[]) {
    //bitset<M> a("123");
    //bitset<M> b(1);
    //string s = "1027000000000000";
    bitset<M> c(123987612);
    string ans = bit_to_str(c);
    //c = a / b;

    cout << ans << endl;
    //cout << c << endl;
    //cout << c.to_ullong() << endl;

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
    bitset<M> tmp(0);
    bool overflow = false;

    for (int i = 0; i < M; i++) {
        if (b[i] == 1) {
            if (a[i] == 1 and i * 2 >= M) {
                overflow = true;
            }
            tmp = a << i;
            c = c + tmp;
        }
    }

    if (overflow)
        cerr << "overflow error" << endl;

    return c;
}

bitset<M> operator/(bitset<M> a, bitset<M> b) {
    int counter = 0;
    bitset<M> c = a;
    bitset<M> ans(0);

    while(comparation_cratch(c, (b << counter + 1)))
        counter++;

    while(counter >= 0) {
        if (comparation_cratch(c, b << counter)) {
            ans[counter] = 1;
            c = c - (b << counter);
        }
        counter--;
    }

    return ans;
}

bitset<M> operator%(bitset<M> a, bitset<M> b) {
    return a - ((a / b) * b);       //да жирно. но пусть пока так. лень переписывать деление
}

int char_to_int(char c) {
    if (!(c >= '0' and c <= '9')) {
        cerr << "char_to_bin converting error" << endl;
    }
    return (int) (c - '0');
}


bitset<M> str_to_bit(string s) {
    bitset<M> ans(0);
    bitset<M> dec_digits[10];
    bitset<M> const dec(10);
    bitset<M> dec_power(1);

    for (int i = 0; i < 10; i++) {
        bitset<M> tmp(i);
        dec_digits[i] = tmp;
    }

    for(int i = 0; i < s.size(); i++) {
        char c = s[(s.size() - 1) - i];
        bitset<M> digit_tmp(char_to_int(c));
        ans = ans + (dec_power * digit_tmp);
        dec_power = dec_power * dec;
    }

    return ans;
}

string bit_to_str(bitset<M> b) {
    bitset<M> const null(0);
    bitset<M> const dec(10);
    bitset<M> dec_digits[10];
    for (int i = 0; i < 10; i++) {
        bitset<M> tmp(i);
        dec_digits[i] = tmp;
    }
    vector<char> ans;
    while (b != null) {
        char c;
        bitset<M> tmp_digit = b % dec;
        int tmp_digit_int = tmp_digit[0] * 1 + tmp_digit[1] * 2 + tmp_digit[2] * 4 + tmp_digit[3] * 8;
        c = '0' + tmp_digit_int;
        ans.push_back(c);
        b = b / dec;
    }

    string ans_str = "";

    for (int i = 0; i < ans.size(); i++) {
        ans_str.push_back(ans[(ans.size() - 1) - i]);
    }

    return ans_str;
}


