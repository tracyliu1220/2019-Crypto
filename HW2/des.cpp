#include <bits/stdc++.h>
using namespace std;

// IP, Inverse IP, E table 1, E table 2, P, PC1, PC2
const int Permu_actual[7] = {64, 64, 32, 32, 32, 64, 56};
const int Permu_total[7] = {64, 64, 48, 48, 32, 56, 48};

const int Permu[7][64] = {
   // IP 
    {39, 7, 47, 15, 55, 23, 63, 31,
     38, 6, 46, 14, 54, 22, 62, 30,
     37, 5, 45, 13, 53, 21, 61, 29,
     36, 4, 44, 12, 52, 20, 60, 28,
     35, 3, 43, 11, 51, 19, 59, 27,
     34, 2, 42, 10, 50, 18, 58, 26,
     33, 1, 41,  9, 49, 17, 57, 25,
     32, 0, 40,  8, 48, 16, 56, 24},
   // Inverse IP
    {57, 49, 41, 33, 25, 17,  9, 1,
     59, 51, 43, 35, 27, 19, 11, 3,
     61, 53, 45, 37, 29, 21, 13, 5,
     63, 55, 47, 39, 31, 23, 15, 7,
     56, 48, 40, 32, 24, 16,  8, 0,
     58, 50, 42, 34, 26, 18, 10, 2,
     60, 52, 44, 36, 28, 20, 12, 4,
     62, 54, 46, 38, 30, 22, 14, 6},
    // E table 1
    { 1,  2,  3,  4,
      7,  8,  9, 10,
     13, 14, 15, 16,
     19, 20, 21, 22,
     25, 26, 27, 28,
     31, 32, 33, 34,
     37, 38, 39, 40,
     43, 44, 45, 46},
    // E table 2
    {47, -1, -1,  6,
      5, -1, -1, 12,
     11, -1, -1, 18,
     17, -1, -1, 24,
     23, -1, -1, 30,
     29, -1, -1, 36,
     35, -1, -1, 42,
     41, -1, -1,  0},
    // P
    { 8, 16, 22, 30, 12, 27,  1, 17,
     23, 15, 29,  5, 25, 19,  9,  0,
      7, 13, 24,  2,  3, 28, 10, 18,
     31, 11, 21,  6,  4, 26, 14, 20},
    // PC1
    { 7, 15, 23, 55, 51, 43, 35, -1, 
      6, 14, 22, 54, 50, 42, 34, -1, 
      5, 13, 21, 53, 49, 41, 33, -1, 
      4, 12, 20, 52, 48, 40, 32, -1, 
      3, 11, 19, 27, 47, 39, 31, -1, 
      2, 10, 18, 26, 46, 38, 30, -1, 
      1,  9, 17, 25, 45, 37, 29, -1, 
      0,  8, 16, 24, 44, 36, 28, -1},
    // PC2
     { 4, 23,  6, 15,  5,  9, 19, 17, 
      -1, 11,  2, 14, 22,  0,  8, 18, 
       1, -1, 13, 21, 10, -1, 12,  3, 
      -1, 16, 20,  7, 46, 30, 26, 47, 
      34, 40, -1, 45, 27, -1, 38, 31, 
      24, 43, -1, 36, 33, 42, 28, 35, 
      37, 44, 32, 25, 41, -1, 29, 39}
    };

const int Box[8][4][16] = {
// S1
{
{14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7},
{ 0, 15,  7,  3, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8},
{ 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7, 13, 10,  5,  0},
{15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13}
},

// S2
{
{15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10},
{ 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5},
{ 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15},
{13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9}
},

// S3
{
{10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8},
{13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1},
{13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7},
{ 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12}
},

// S4
{
{ 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15},
{13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9},
{10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4},
{ 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14}
},

// S5
{
{ 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9},
{14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6},
{ 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14},
{11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3}
},

// S6
{
{12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11},
{10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8},
{ 9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6},
{ 4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13}
},

// S7
{
{ 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1},
{13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6},
{ 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2},
{ 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12}
},

// S8
{
{13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7},
{ 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2},
{ 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8},
{ 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11}
} };

const unsigned long long Box_block[8] = {277076930199552, 
    4329327034368, 
    67645734912, 
    1056964608, 
    16515072, 
    258048, 
    4032, 
    63};

const int key_rotate[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

void Print64(unsigned long long text) {
    cout << bitset<64>(text) << '\n';
}

void Print56(unsigned long long text) {
    cout << bitset<56>(text) << '\n';
}

void Print48(unsigned long long text) {
    cout << bitset<48>(text) << '\n';
}

void Print32(unsigned long long text) {
    cout << bitset<32>(text) << '\n';
}

void Print28(unsigned long long text) {
    cout << bitset<28>(text) << '\n';
}

unsigned long long Permutation(unsigned long long text, int table, unsigned long long target = 0) {
    int idx;
    for (int i = 0; i < Permu_actual[table]; i ++) {
        idx = Permu_actual[table] - i - 1;
        if (Permu[table][idx] == -1) continue;
        // if (text & (1ULL << idx)) cout << idx << ' ' << Permu[table][idx] << '\n';
        if (text & (1ULL << idx))
            target |= (1ULL << (Permu_total[table] - Permu[table][idx] - 1));
            // target |= (1ULL << Permu[table][idx]);
    }
    return target;
}

unsigned long long E(unsigned long long text) {
    // E table
    unsigned long long target = Permutation(text, 2);
    target = Permutation(text, 3, target);
    return target;
}

unsigned long long S_box(unsigned long long text) {
    unsigned long long target[8] = {0};
    for (int i = 0; i < 8; i ++) {
        target[i] = (text & Box_block[i]) >> (6 * (8 - i - 1));
        int a = 0, b = 0;
        a |= (target[i] & (1 << 5)) >> 4;
        a |= target[i] & 1;
        b = (target[i] >> 1) & 15;
        target[i] = Box[i][a][b];
        // cout << a << ' ' << b << ' ' << target[i] << '\n';
    }
    unsigned long long ret = 0;
    for (int i = 0; i < 8; i ++) {
        ret = ret << 4;
        ret |= target[i];
    }
    return ret;
}

unsigned long long P(unsigned long long text) {
    return Permutation(text, 4);
}

unsigned long long Key_shift(unsigned long long text, int s, bool state) { // s = shift time
    if (state) { // dec: right
        int tmp = (text & ((1 << s) - 1)) << (28 - s);
        text = (text >> s) | tmp;
    } else { // enc: left
        int tmp = (text & ((1 << s) - 1) << (28 - s)) >> (28 - s);
        text = ((text & ((1 << (28 - s)) - 1)) << s) | tmp;
    }
    return text;
}

unsigned long long Key_scheduling(unsigned long long text, int r, bool state) { // r = round
    unsigned long long L = (text & ((1ULL << 28) - 1) << 28) >> 28;
    unsigned long long R = text & ((1ULL << 28) - 1);
    L = Key_shift(L, key_rotate[r], state);
    R = Key_shift(R, key_rotate[r], state);
    return (L << 28) | R;
}

unsigned long long Round(unsigned long long text, unsigned long long key) {
    // break into L and R
    unsigned long long L = (text & ((1ULL << 32) - 1) << 32) >> 32;
    unsigned long long R = text & ((1ULL << 32) - 1);
    unsigned long long nextL = R;

    /* F function */ 
    // E table
    R = E(R);
    
    // R XOR with PC2 Key
    key = Permutation(key, 6);
    /*
    unsigned long long K = 0;
    for (int i = 0; i < 8; i ++) {
        unsigned long long tmp = (key & Box_block[i]) >> 6 * (8 - i - 1);
        K |= tmp;
        if (i != 7) K = (K << 8);
    }
    cout << "Key: " << hex << K;
    cout << ' ';
    */
    R ^= key;
    
    // S-box
    R = S_box(R);
    
    // P
    R = P(R);
    
    // L XOR
    R ^= L;
    
    // stick L and R together
    return (nextL << 32) | R;
}

unsigned long long DES(unsigned long long text, unsigned long long key, bool state) {
    // IP
    text = Permutation(text, 0);
    // cout << "IP: " << hex << text << '\n';
    
    // PC1
    key = Permutation(key, 5);
    Print56(key);
    
    // 16 Rounds and Key scheduling
    for (int round = 0; round < 16; round ++) {
        key = Key_scheduling(key, round, state);
        Print56(key);
        text = Round(text, key);
        // cout << hex << text;
        // cout << '\n';
    }

    // 32-bit Swap
    unsigned long long L = (text & ((1ULL << 32) - 1) << 32) >> 32;
    unsigned long long R = text & ((1ULL << 32) - 1);
    text = (R << 32) | L;
    
    // Inverse IP
    text = Permutation(text, 1);

    return text;
}

int main() {

    bool state = false; // 0: enc, 1: dec
    // 0x5B5A57676A56676E 0x675A69675E5A6B5A
    // unsigned long long key  = 0x0f1571c947d9e859;
    // unsigned long long text = 0x02468aceeca86420;
    
    unsigned long long key  = 0x5B5A57676A56676E;
    unsigned long long text = 0x675A69675E5A6B5A;

    cout << hex << DES(text, key, state) << '\n';
}
