#include <bits/stdc++.h>
using namespace std;

// IP, Inverse IP, E table, P, PC1, PC2
const int Permu_in[7] =  {64, 64, 32, 32, 64, 56};
const int Permu_out[7] = {64, 64, 48, 32, 56, 48};

const int Permu[7][64] = {
   // IP 
    {57, 49, 41, 33, 25, 17,  9, 1,
     59, 51, 43, 35, 27, 19, 11, 3,
     61, 53, 45, 37, 29, 21, 13, 5,
     63, 55, 47, 39, 31, 23, 15, 7,
     56, 48, 40, 32, 24, 16,  8, 0,
     58, 50, 42, 34, 26, 18, 10, 2,
     60, 52, 44, 36, 28, 20, 12, 4,
     62, 54, 46, 38, 30, 22, 14, 6},
   // Inverse IP
    {39, 7, 47, 15, 55, 23, 63, 31,
     38, 6, 46, 14, 54, 22, 62, 30,
     37, 5, 45, 13, 53, 21, 61, 29,
     36, 4, 44, 12, 52, 20, 60, 28,
     35, 3, 43, 11, 51, 19, 59, 27,
     34, 2, 42, 10, 50, 18, 58, 26,
     33, 1, 41,  9, 49, 17, 57, 25,
     32, 0, 40,  8, 48, 16, 56, 24},
    // E table
    {31,  0,  1,  2,  3,  4,
      3,  4,  5,  6,  7,  8,
      7,  8,  9, 10, 11, 12,
     11, 12, 13, 14, 15, 16,
     15, 16, 17, 18, 19, 20,
     19, 20, 21, 22, 23, 24,
     23, 24, 25, 26, 27, 28,
     27, 28, 29, 30, 31,  0},
    // P
    {15,  6, 19, 20, 28, 11, 27, 16,
      0, 14, 22, 25,  4, 17, 30,  9,
      1,  7, 23, 13, 31, 26,  2,  8,
     18, 12, 29,  5, 21, 10,  3, 24},
    // PC1
     {56, 48, 40, 32, 24, 16,  8,
       0, 57, 49, 41, 33, 25, 17,
       9,  1, 58, 50, 42, 34, 26,
      18, 10,  2, 59, 51, 43, 35,
      62, 54, 46, 38, 30, 22, 14,
       6, 61, 53, 45, 37, 29, 21,
      13,  5, 60, 52, 44, 36, 28,
      20, 12,  4, 27, 19, 11,  3},
    // PC2
     {13, 16, 10, 23,  0,  4,  2, 27,
      14,  5, 20,  9, 22, 18, 11,  3,
      25,  7, 15,  6, 26, 19, 12,  1,
      40, 51, 30, 36, 46, 54, 29, 39,
      50, 44, 32, 47, 43, 48, 38, 55,
      33, 52, 45, 41, 49, 35, 28, 31}
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

const int key_rotate[20] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

void Print48(unsigned long long text) {
    cout << bitset<48>(text) << '\n';
}

unsigned long long Permutation(unsigned long long text, int table, unsigned long long target = 0) {
    int idx1, idx2;
    for (int i = 0; i < Permu_out[table]; i ++) {
        idx1 = Permu_out[table] - i - 1;
        idx2 = Permu_in[table] - Permu[table][i] - 1;
        if (text & (1ULL << idx2))
            target |= (1ULL << idx1);
    }
    return target;
}

unsigned long long E(unsigned long long text) {
    // E table
    unsigned long long target = Permutation(text, 2);
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
    }
    unsigned long long ret = 0;
    for (int i = 0; i < 8; i ++) {
        ret = ret << 4;
        ret |= target[i];
    }
    return ret;
}

unsigned long long P(unsigned long long text) {
    return Permutation(text, 3);
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
    key = Permutation(key, 5);
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

unsigned long long Swap(unsigned long long text) {
    // 32-bit Swap
    unsigned long long L = (text & ((1ULL << 32) - 1) << 32) >> 32;
    unsigned long long R = text & ((1ULL << 32) - 1);
    text = (R << 32) | L;
    return text;
}

unsigned long long DES(unsigned long long text, unsigned long long key, bool state) {

    // IP
    text = Permutation(text, 0);
    
    // PC1
    key = Permutation(key, 4);
    
    // 16 Rounds and Key scheduling
    if (!state)
        key = Key_scheduling(key, 0, state);
    for (int round = 0; round < 16; round ++) {
        int r = round + 1;
        if (state) r = 16 - round - 1;
        text = Round(text, key);
        key = Key_scheduling(key, r, state);
    }

    // 32-bit Swap
    text = Swap(text);
    
    // Inverse IP
    text = Permutation(text, 1);

    return text;
}

int main() {
    
    clock_t start, end;
    double cpu_time_used;
    start = clock();

    bool state = false; // 0: enc, 1: dec
    unsigned long long key  =   0x5B5A57676A56676E;
    unsigned long long text =   0x675A69675E5A6B5A;
    unsigned long long cipher = 0x974AFFBF86022D1F;
    int ignore;

    int T = 10;
    while (T --) {
        scanf("%llx %llx", &key, &text);
        printf("%llX\n", DES(text, key, state));
    }

    T = 10; state = true;
    while (T --) {
        scanf("%llx %llx", &key, &text);
        printf("%llX\n", DES(text, key, state));
    }

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    cout << "Running time: " << cpu_time_used << '\n';
}
