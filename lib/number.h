#pragma once
#include <cinttypes>
#include <iostream>
#include <bits/stdc++.h>
#define N 2022

using namespace std;

const int M = N + 1;

struct uint2022_t {
    bitset<M> value;
    uint2022_t(bitset<M> value) {
        this->value = value;
    }
};

static_assert(sizeof(uint2022_t) <= 300, "Size of uint2022_t must be no higher than 300 bytes");

uint2022_t from_uint(uint32_t i);

uint2022_t from_string(const char* buff);

uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs);

uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs);

uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs);

uint2022_t operator/(const uint2022_t& lhs, const uint2022_t& rhs);

bool operator==(const uint2022_t& lhs, const uint2022_t& rhs);

bool operator!=(const uint2022_t& lhs, const uint2022_t& rhs);

std::ostream& operator<<(std::ostream& stream, const uint2022_t& value);

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
