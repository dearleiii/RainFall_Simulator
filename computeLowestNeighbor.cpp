#include <iostream>
#include <vector>
#include "computeLowestNeighbor.h"

using namespace std;

int hashMinNeighbors(vector<int> &resList) {
    int hashing;
    if (resList.size() == 1) {
        if (resList[0] == 0) hashing = 0;
        else if (resList[0] == 1) hashing = 4;
        else if (resList[0] == 2) hashing = 5;
        else if (resList[0] == 3) hashing = 6;
        else if (resList[0] == 4) hashing = 7;
    } else if (resList.size() == 2) {
        if (resList[0] == 1 && resList[1] == 2) hashing = 8;
        else if (resList[0] == 2 && resList[1] == 3) hashing = 9;
        else if (resList[0] == 3 && resList[1] == 4) hashing = 10;
        else if (resList[0] == 1 && resList[1] == 4) hashing = 11;
        else if (resList[0] == 1 && resList[1] == 3) hashing = 2;
        else if (resList[0] == 2 && resList[1] == 4) hashing = 3;
    } else if (resList.size() == 3) {
        if (resList[0] == 2 && resList[1] == 3 && resList[2] == 4) hashing = 12;
        else if (resList[0] == 1 && resList[1] == 3 && resList[2] == 4) hashing = 13;
        else if (resList[0] == 1 && resList[1] == 2 && resList[2] == 4) hashing = 14;
        else if (resList[0] == 1 && resList[1] == 2 && resList[2] == 3) hashing = 15;
    } else if (resList.size() == 4) {
        hashing = 16;
    }
    return hashing;
}

void computeMinNeighbors(int **eleMat, int r, int c, vector<int> &neighbors, vector<int> &minNeighbors) {
    int min = eleMat[r][c]; // Initialize the min elevation at center point 
    int center = eleMat[r][c];
    int tie = 1;
    int i = 0;
    int item;

    for (vector<int>::iterator it = neighbors.begin() ; it != neighbors.end(); ++it) {
        switch (*it) {
            case 1: // compare with upper pixel, compare(min, center, cntTie, eleMat[r-1][c]);
                if (min > eleMat[r-1][c]) {
                    min = eleMat[r-1][c];
                    tie = 1;
                    minNeighbors.clear();
                    minNeighbors.push_back(1);
                } else if (min == eleMat[r-1][c] && min != center) { 
                    // TIE: If min == center, no need to change, no tricle
                    tie++;
                    minNeighbors.push_back (1);
                } 
                break;
            case 2: // compare with right, compare(min, center, tie, eleMat[r][c+1]);
                if (min > eleMat[r][c+1]) {
                    min = eleMat[r][c+1];
                    tie = 1;
                    minNeighbors.clear();
                    minNeighbors.push_back(2);
                } else if (min == eleMat[r][c+1] && min != center) { 
                    tie++;
                    minNeighbors.push_back(2);
                } 
                break;
            case 3: // compare with lower, compare(min, center, tie, eleMat[r+1][c]);
                if (min > eleMat[r+1][c]) {
                    min = eleMat[r+1][c];
                    tie = 1;
                    minNeighbors.clear();
                    minNeighbors.push_back(3);
                } else if (min == eleMat[r+1][c] && min != center) {
                    tie++;
                    minNeighbors.push_back(3);
                } 
                break;
            case 4: // compare with left, compare(min, center, tie, eleMat[r][c-1]);
                if (min > eleMat[r][c-1]) {
                    min = eleMat[r][c-1];
                    tie = 1;
                    minNeighbors.clear();
                    minNeighbors.push_back(4);
                } else if (min == eleMat[r][c-1] && min != center) { 
                    tie++;
                    minNeighbors.push_back(4);
                } 
                break;
            default: break;
        }                
    }        

    // check minneighbors
    if (minNeighbors.size() == 0) {
        minNeighbors.push_back(0);
    }
    return; 
}

void computeNeighbors(int r, int c, int N, vector<int> &neighbors) {
    if (r == 0 && c == 0) {
        neighbors.push_back(2);
        neighbors.push_back(3);
    } else if (r == 0 && c == N-1) {
        neighbors.push_back(3);
        neighbors.push_back(4);
    } else if (r == N-1 && c == 0) {
        neighbors.push_back(1);
        neighbors.push_back(2);
    } else if (r == N-1 && c== N-1) {
        neighbors.push_back(1);
        neighbors.push_back(4);
    } else if (r == 0) {
        neighbors.push_back(2);
        neighbors.push_back(3);
        neighbors.push_back(4);
    } else if (r == N-1) {
        neighbors.push_back(1);
        neighbors.push_back(2);
        neighbors.push_back(4);
    } else if (c == 0) {
        neighbors.push_back(1);
        neighbors.push_back(2);
        neighbors.push_back(3);
    } else if (c == N-1) { 
        neighbors.push_back(1);
        neighbors.push_back(3);
        neighbors.push_back(4);
    } else {
        neighbors.push_back(1);
        neighbors.push_back(2);
        neighbors.push_back(3);
        neighbors.push_back(4);
    }
    // cout vector neighbors
    return;
}

void computeLowestNeighbor(int **eleMat, int **lowestMat, int N) {
    // int** lowestMat pass in success!
    int hashingValue = 0;
    vector<int> neighbors;
    vector<int> minNeighbors;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            computeNeighbors(i, j, N, neighbors);
            computeMinNeighbors(eleMat, i, j, neighbors, minNeighbors);
            hashingValue = hashMinNeighbors(minNeighbors);
            lowestMat[i][j] = hashingValue;

            /* cout << "check computeNeighbors results at " << i << ", " << j << ": " << endl;
            for (vector<int>::iterator it = neighbors.begin() ; it != neighbors.end(); ++it) {
                cout << *it << " ";
            }
            cout << "\n" << "check computeMinNeighbors results: " << endl;
            for (vector<int>::iterator it = minNeighbors.begin() ; it != minNeighbors.end(); ++it) {
                cout << *it << " ";
            }
            cout << "\n" << "hashing value: " << hashingValue << endl; */

            neighbors.clear();
            minNeighbors.clear();
        }
    }
    return;
}
