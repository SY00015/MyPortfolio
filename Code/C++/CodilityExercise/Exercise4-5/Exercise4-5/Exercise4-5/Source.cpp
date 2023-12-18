#include "Header.h"

int main() {
    //vector <int> A = { 1, 3, 1, 4, 2, 3, 5, 4 };
    //frogRiverOne(5, A);
    
    vector <int> A = { 3, 4, 4, 6, 1, 4, 4 };
    MaxCounters(5, A);

}

int frogRiverOne(int X, vector<int>& A) {
    /*
    A small frog wants to get to the other side of a river. 
    The frog is initially located on one bank of the river (position 0) and wants to get to the opposite bank (position X+1). 
    Leaves fall from a tree onto the surface of the river.
    You are given an array A consisting of N integers representing the falling leaves. 
    A[K] represents the position where one leaf falls at time K, measured in seconds.

    The goal is to find the earliest time when the frog can jump to the other side of the river. 
    The frog can cross only when leaves appear at every position across the river from 1 to X 
    (that is, we want to find the earliest moment when all the positions from 1 to X are covered by leaves). 
    You may assume that the speed of the current in the river is negligibly small, 
    i.e. the leaves do not change their positions once they fall in the river.*/


    // Size of B = X, fill the space with -1 
        vector <int> B(X, -1);
        for (unsigned int i = 0; i < A.size(); i++) {
            if (A[i] <= X) {
                // if first time having leaf fall on the position, 
                if (B[A[i] - 1] == -1) {
                    // make the element in B[i] the second the leaf fall (the index in A = second)
                    B[A[i] - 1] = i;
                }
            }
        }
        int max = 0;
        for (int i = 0; i < B.size(); i++) {
            //if element in B array is -1, means that space never had leaf fall on it 
            if (B[i] == -1) { cout << "-1 "; return -1; }
            if (max < B[i]) { max = B[i]; }
        }
        cout << max;
        return max;
    }



vector <int> MaxCounters(int X, vector<int>& A) {
    vector <int> B(X, 0);
    /*performance 40%
    int max = 0;
    for (unsigned int i = 0; i < A.size(); i++) {
        if (A[i] > X) {
            //find max number in B 
            for (int j = 0; j < B.size(); j++) {
                B[j] = max;
              
               }                
        }

        else {
            cout << " B + = 1 " << endl;
            B[A[i] - 1] += 1;
            if (B[A[i] - 1] > max) {
                max = B[A[i] - 1];
                
            }


        }
    }


    for (int i = 0; i < B.size(); i++) {
        cout << B[i];
    }

    return B;  */


    int m = 0;
    int b = 0; 
    for (int i = 0; i < A.size(); i++) {
        if (A[i] <= X) {
            B[A[i] - 1] = max(b, B[A[i] - 1]) + 1;
            if (m < B[A[i] - 1]) {
                m = B[A[i] - 1];
            }
        }
        else { b = m; }
    }
}