#include "number.h"
#include<iostream>
#include<bits/stdc++.h>

#define N 2022

using namespace std;

uint2022_t from_uint(uint32_t i) {
    bitset<M> i_bit(i);
    return uint2022_t(i_bit);
}

uint2022_t from_string(const char* buff) {
    bitset<M> tmp = str_to_bit(buff);
    return uint2022_t(tmp);
}

uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs) {
    bitset<M> tmp = lhs.value + rhs.value;
    return uint2022_t(tmp);
}

uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs) {
    bitset<M> tmp = lhs.value - rhs.value;
    return uint2022_t(tmp);
}

uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs) {
    bitset<M> tmp = lhs.value * rhs.value;
    return uint2022_t(tmp);
}

uint2022_t operator/(const uint2022_t& lhs, const uint2022_t& rhs) {
    bitset<M> tmp = lhs.value / rhs.value;
    return uint2022_t(tmp);
}

bool operator==(const uint2022_t& lhs, const uint2022_t& rhs) {
    bitset<M> l = lhs.value;
    bitset<M> r = rhs.value;

    if (l == r) {
        return true;
    } else {
        return false;
    }
}

bool operator!=(const uint2022_t& lhs, const uint2022_t& rhs) {
    return !(lhs == rhs);
}

std::ostream& operator<<(std::ostream& stream, const uint2022_t& value) {
    stream << bit_to_str(value.value);

    return stream;
}

//////////////////

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

    if (b == ans) {
        cerr << "zero division error" << endl;
    }

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

    if (ans.size() == 0) {
        ans.push_back('0');
    }

    string ans_str = "";

    for (int i = 0; i < ans.size(); i++) {
        ans_str.push_back(ans[(ans.size() - 1) - i]);
    }

    return ans_str;
}

int main(int argc, char* argv[]) {          //MAIN
    //bitset<M> a(3000000000);
    //bitset<M> b(3000000000);
    //bitset<M> c = a * b * b * b;
    //string s = "1000000000";
    const char* buff = "1469832487054184013178321496623041557517329857560238757278117847507488415462666081345922349701550571520";
    uint2022_t a(3000000000);
    uint2022_t b(3000000000);
    uint2022_t d = from_string(buff);
    uint2022_t c = a * b * b * b;

    cout << d << endl;

    return 0;
}
