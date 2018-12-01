#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>
#include <stdio.h>
#include "computeLowestNeighbor.h"
#include "updateTricle.h"

using namespace std;

int main(int argc, char** argv) 
{
    int parallelThreads, timeSteps, N; 
    float absorbRate;
    string elevationFile;

    // read the command arguments 
    if (argc != 6) {
        cout << "Enter arguments format: ";
        cout << "./rainfall <P> <M> <A> <N> <elevation_file> ";
        exit(1);
    }

    istringstream ss1(argv[1]);
    if (!(ss1 >> parallelThreads)) {
        cerr << "Invalid number for parallel threads number: " << argv[1] << "\n";
    } 
    istringstream ss2(argv[2]);
    if (!(ss2 >> timeSteps)) {
        cerr << "Invalid number for time steps: " << argv[2] << "\n";
    } // cout << "read timesteps: " << timeSteps << endl;
    istringstream ss3(argv[3]);
    if (!(ss3 >> absorbRate)) {
        cerr << "Invalid number for absorbtion rate: " << argv[3] << "\n";
    } // cout << "read absorbtion rate: " << absorbRate << endl;
    istringstream ss4(argv[4]);
    if (!(ss4 >> N)) {
        cerr << "Invalid number for dimension: " << argv[4] << "\n";
    } // cout << "read dimension: " << N << endl;
    istringstream ss5(argv[5]);
    if (!(ss5 >> elevationFile)) {
        cerr << "Invalid number for input file name: " << argv[5] << "\n";
    } 

    // store input file ro elevation matrix 
    ifstream inFile;
    inFile.open(elevationFile + ".txt");
    if (!inFile) {
        cout << "Unable to open in file\n";
        exit(1);
    } 

    int **eleMatPtr = new int *[N];
    for (int i = 0 ; i <N; i++) {
        eleMatPtr[i] = new int[N];
        for (int j = 0; j < N; j++) {
            inFile >> eleMatPtr[i][j];
        }
    }
    inFile.close();

    /* cout << "Check eleMat: " << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << eleMatPtr[i][j] << " ";
        }
        cout << endl;
    } */
    // int **lowsestNeighbor = computeLowestNeighbor(eleMatPtr, N);
    int **lowsestNeighbor = new int*[N];
    for (int i = 0; i < N; i++) {
        lowsestNeighbor[i] = new int[N];
    }
    // init sucess!
    // cout << "start compute lowestMat:  " << endl;
    computeLowestNeighbor(eleMatPtr, lowsestNeighbor, N);

    /* cout << "Check lowsestNeighbor: " << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << lowsestNeighbor[i][j] << " ";
        }
        cout << endl;
    } */

    for (int i = 0; i < N; i++) {
        delete[] eleMatPtr[i];
    }
    delete[] eleMatPtr;

    // Algorithm for time = timeSteps, During rainfall phase
    int i,j;
    bool unfinish = true;
    double maxVol = 0;
    int cntIter = 0;

    double **stepVol = new double *[N];
    double **tricleMat = new double *[N];
    double **absorbed = new double *[N];

    for (int i = 0; i < N; i++) {
        stepVol[i] = new double[N];
        tricleMat[i] = new double[N];
        absorbed[i] = new double[N];
    }

    // for (int t = 0; t < timeSteps; t++) {
        // First traversal: 
        // 1. receive a new raindrop for each point 
        // 2. if there are raindrops on a point, absorb water into the point
    const clock_t begin = clock();

    while (unfinish) { 
        cntIter++;
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                if (cntIter <= timeSteps) { // When still raining 
                    absorbed[i][j] += absorbRate * 1;
                    tricleMat[i][j] += (1 - absorbRate) * 1;
                } else { // Only Absorb without rain
                    if (tricleMat[i][j] <= absorbRate * 1) {
                        absorbed[i][j] += tricleMat[i][j];
                        tricleMat[i][j] = 0;
                    } else { // tricleMat[i][j] > absorbRate volumn
                        absorbed[i][j] += absorbRate * 1;
                        tricleMat[i][j] -= absorbRate * 1;
                    }
                }    
                // 3a. calcualte the number of raindrops that will next tricle to the lowest neighbors 
                if (tricleMat[i][j] > 1) {
                    stepVol[i][j] = 1;
                    tricleMat[i][j] -= 1;
                } else {
                    stepVol[i][j] = tricleMat[i][j];
                    tricleMat[i][j] = 0;
                } 
            }
        }

        // Second traversal: 
        // 3b. for each point, use the calculation in 3a
            // update the number of raindrops at each lowest neighbor 
        /*
        cout << "checking stepVol mat at " << cntIter << ": " << endl;
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                cout << stepVol[i][j] << " ";
            }
            cout << endl; 
        }
        */
        
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                updateTricle(lowsestNeighbor[i][j], stepVol[i][j], tricleMat, i, j);
            }
        }   
        if (cntIter > timeSteps) {
            maxVol = 0;
            for (i = 0;  i < N; i++) {
                for (j = 0; j < N; j++) {
                    maxVol = max(maxVol, tricleMat[i][j]);
                    if (maxVol > 0) break;
                }
                if (maxVol > 0) break;
            }
            if (maxVol == 0) unfinish = false;   
        }
        
        /*
        cout << "Check tricleMat at time " << cntIter << endl;
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                cout << tricleMat[i][j] << " ";
            }
            cout << endl;
        }
        std::cout << "Check absorbedMat at time " << cntIter << endl;
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                cout << absorbed[i][j] << " ";
            }
            cout << endl;
        }
        */
    }
    
    // output
    ofstream myfile;
    string out_name = to_string(N) + 'x' + "_myout.txt";
    myfile.open (out_name);
    clock_t end_clock = clock();

    cout << "Rainfall simulation took " << cntIter << " time steps to complete." << endl;
    cout << "Runtime = " << double(end_clock - begin) / CLOCKS_PER_SEC << " ms"<< endl;
    myfile << "Rainfall simulation took " << cntIter << " time steps to complete." << endl;
    myfile << "Runtime = " << double(end_clock - begin) / CLOCKS_PER_SEC << " ms"<< endl;

    cout << "\n" << "The following grid shows the number of raindrops absorbed at each point: " << endl;
    myfile << "\n" << "The following grid shows the number of raindrops absorbed at each point: " << endl;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            cout << absorbed[i][j] << " ";
            myfile << absorbed[i][j] << " ";
        }
        cout << endl; 
        myfile << endl;
    }
    myfile.close();

    // Free memory
    for (int i = 0; i < N; i++) {
        delete[] absorbed[i];
        delete[] stepVol[i];
        delete[] tricleMat[i];
        // delete[] eleMatPtr[i];
        delete[] lowsestNeighbor[i];
    }
    delete[] absorbed;
    delete[] stepVol;
    delete[] tricleMat;
    // delete[] eleMatPtr;
    delete[] lowsestNeighbor;

    return 0;
}
