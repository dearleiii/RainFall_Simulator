#include <iostream>
#include <vector>
#include "updateTricle.h"

using namespace std;    

int updateTricle(int neighbors, double volumn, double** tricleMat, int r, int c) {
    // 1. Compute whether divide;
    // 2. Compute neighbor traget;
    // 3. Update tricleMat;
    int divid = neighbors / 4;
    int remain = neighbors % 4;
    switch (divid) {
        case 0: 
            if (remain == 0) {
                tricleMat[r][c] += volumn;
            } else if (remain == 2) {
                tricleMat[r-1][c] += volumn / 2;
                tricleMat[r+1][c] += volumn / 2;
            } else if (remain == 3) {
                tricleMat[r][c-1] += volumn / 2;
                tricleMat[r][c+1] += volumn / 2;
            }
            break;
        case 1: 
            switch (remain) {
                case 0: 
                    tricleMat[r-1][c] += volumn;
                    break;
                case 1: 
                    tricleMat[r][c+1] += volumn;
                    break;
                case 2: 
                    tricleMat[r+1][c] += volumn;
                    break;
                case 3: 
                    tricleMat[r][c-1] += volumn;
                    break;
                default: break;
            }
            break;
        case 2: 
            switch (remain) {
                case 0: 
                    tricleMat[r-1][c] += volumn / 2;
                    tricleMat[r][c+1] += volumn / 2;
                    break;
                case 1: 
                    tricleMat[r][c+1] += volumn / 2;
                    tricleMat[r+1][c] += volumn / 2;
                    break;
                case 2: 
                    tricleMat[r+1][c] += volumn / 2;
                    tricleMat[r][c-1] += volumn / 2;
                    break;
                case 3: 
                    tricleMat[r-1][c] += volumn / 2;
                    tricleMat[r][c-1] += volumn / 2;
                    break;
                default: break;
            }
            break;
        case 3: 
            switch (remain) {
                case 0: 
                    tricleMat[r][c+1] += volumn / 3;
                    tricleMat[r][c-1] += volumn / 3;
                    tricleMat[r+1][c] += volumn / 3;
                    break;
                case 1: 
                    tricleMat[r-1][c] += volumn / 3;
                    tricleMat[r+1][c] += volumn / 3;
                    tricleMat[r][c-1] += volumn / 3;
                    break;
                case 2: 
                    tricleMat[r][c+1] += volumn / 3;
                    tricleMat[r][c-1] += volumn / 3;
                    tricleMat[r-1][c] += volumn / 3;
                    break;
                case 3: 
                    tricleMat[r-1][c] += volumn / 3;
                    tricleMat[r+1][c] += volumn / 3;
                    tricleMat[r][c+1] += volumn / 3;
                    break;
                default: break;
            }
            break;
        case 4: 
            tricleMat[r-1][c] += volumn / 4;
            tricleMat[r+1][c] += volumn / 4;
            tricleMat[r][c+1] += volumn / 4;
            tricleMat[r][c-1] += volumn / 4;
        default: break;
    }

    return 0;
}
