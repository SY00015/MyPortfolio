#include "Header.h"

int main() {
	vector <int> A = { 2, 3, 3, 4};
	vector <int> B = { 1, 4, 5, 5 };
	vector <int> C = { 5, 2, 5, 2 };
	vector <int> D = { 1,5,5  };
	DoubleHanoi(A, 3, 1); //return 3
	cout << endl;
	DoubleHanoi(B, 6, 4); // return 4
	cout<< endl;
	DoubleHanoi(C, 8, 1); //return 4 
	cout << endl;
	DoubleHanoi(D, 4, 2); //return 2

}


int DoubleHanoi(vector<int>& A, int L, int R) {
	/*
	given an array A of integers representing the sizes of the N disks and two integers L and R representing 
	the size of the initial disks on the left and right rods respectively, 
	returns the maximum number of disks from A that can be placed on the rods while satisfying the rules presented above.

	E.g. Given A = [1, 4, 5, 5], L = 6 and R = 4, your function should return 4.
	*/
	
	// store each placed disk  
	int counter = 0;
	// sort array order 
	std::sort(A.begin(), A.end());

	for (int i = 0; i < A.size(); i++) {
		// small-> large
		if (R < A[i]) {
			R = A[i];
			A.erase(A.begin()+i);
			counter += 1;
			i = -1; 
			
		}
	}
	std::reverse(A.begin(), A.end());

	for (int i = 0; i < A.size(); i++) {
		//large-> small
		if (L > A[i]) {
			L = A[i];
			counter += 1;
		}

	}

	cout << counter;
	return 1;
}
