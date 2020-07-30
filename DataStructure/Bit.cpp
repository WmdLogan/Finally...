//
// Created by logan on 2020/7/30.
//
// 461. Hamming Distance (Easy)

#include <iostream>
using namespace std;

class Solution {
public:
// 461. Hamming Distance (Easy)
    int hammingDistance(int x, int y) {
    /*    int x_y = x ^ y;
        int distance = 0;
        while (x_y != 0) {
            if (x_y % 2 == 1)
                distance += 1;
            x_y = x_y >> 1;
        }
        return distance;*/
        int x_y = x ^ y;
        int distance = 0;
        while (x_y != 0) {
            distance += 1;
            // remove the rightmost bit of '1'
            x_y = x_y & (x_y - 1);
        }
        return distance;

    }
};