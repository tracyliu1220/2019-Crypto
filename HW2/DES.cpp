#include <bits/stdc++.h>
using namespace std;

// IP, Inverse IP, E table 1, E table 2
int Permu_cnt[2] = {64, 64, 32, 32};

const int Permu[4][64] = {
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
     41, -1, -1,  0} };

const int Box[8][4][16] = {
// S1
{
{14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7},
{ 0, 15,  7,  3, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8},
{ 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7, 13, 10,  5,  0},
{15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13},
},

// S2
{
{15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10},
{ 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5},
{ 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15},
{13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9},
},

// S3
{
{10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8},
{13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1},
{13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7},
{ 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12},
},

// S4
{
{ 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15},
{13,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9},
{10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4},
{ 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14},
}

}



void Print(unsigned long long text) {
    cout << bitset<64>(text) << '\n';
}

unsigned long long Permutation(unsigned long long text, int table, unsigned long long target = 0) {
    int idx;
    for (int i = 0; i < Permu_cnt[table]; i ++) {
        idx = Permu_cnt[table] - i - 1;
        if (Permu[table][idx] == -1) continue;
        // if (text & (1ULL << idx)) cout << idx << ' ' << Permu[table][idx] << '\n';
        if (text & (1ULL << idx))
            target |= (1ULL << (Permu_cnt[table] - Permu[table][idx] - 1));
    }
    return target;
}

unsigned long long E(unsigned long long text) {
    // E table
    unsigned long long target = Permutation(text, 2);
    target = Permutation(text, 3, target);
    return target;
}
/*
unsigned long long S_box() {

}

unsigned long long P() {

}

unsigned long long Key() {

}

unsigned long long Round() {
    // break into L and R

    // F function 
    // E table
    
    // Key scheduling
    
    // R XOR with Key
    
    // S-box
    
    // P
    
    // L XOR
    
    // stick L and R together
}


unsigned long long DES(unsigned long long text, unsigned long long key, bool state) {
    // IP
    
    
    // Key PC1
    
    // 16 Rounds

    // 32-bit Swap
    
    // Inverse IP

    return target;
}
*/


int main() {

    bool state = 0; // 0: enc, 1: dec
    unsigned long long test = 1023;
    unsigned long long target = Permutation(test, 1);
    Print(test);
    Print(target);    

}
