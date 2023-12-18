#include "Header.h"


int main() {

	//BinaryGap();
	//RotateTable();
	//vector <int> A = {1};
	//vector <int> B = { 2 };
	//Dinner (A,B);
	//OddOccurrencesInArray(A)
	//FrogJump(13,90,10);
	vector<int> C = {3, 1, 2, 4, 3};
	TapeEquilibrium(C);
	//return 0; 
}


void BinaryGap() {
	int number;
	string output;
	/*A binary gap within a positive integer N is any maximal sequence of consecutive zeros that is surrounded by ones at both ends in the binary representation of N.
	For example, number 9 has binary representation 1001 and contains a binary gap of length 2.
	The number 529 has binary representation 1000010001 and contains two binary gaps: one of length 4 and one of length 3.
	The number 20 has binary representation 10100 and contains one binary gap of length 1.
	The number 15 has binary representation 1111 and has no binary gaps. The number 32 has binary representation 100000 and has no binary gaps.*/

	cout << " Input you number to check binary gap: ";
	cin >> number;
	// find out the binary number for the input 
	vector <bool> binary;
	int maxNum = 0; // holders for the max count of 0s
	int counts = 0; // holders for 0s 
	bool isClosed = true; //checker for 0 between 1

	while (number != 0) {
		binary.push_back(number % 2 != 0);
		number /= 2;
	}

	// print binary 
	cout << " The binary for your number is: ";
	std::reverse(binary.begin(), binary.end());
	for (int i = 0; i < binary.size(); i++) {
		cout << binary[i];
	}

	//check 0 between 1

	for (int i = 0; i < binary.size(); i++) {
		//reset count if meet 1
		if (binary[i] == 1) {
			// update the max count 
			if (maxNum < counts) {
				maxNum = counts;
			}
			counts = 0;
			isClosed = true; //The gap is closed
		}

		if (isClosed) {
			if (binary[i] == 0) {
				//check the current 0 is not the binginning or the last number, else it is not a closed gap
				if (i != 0 && i != -1) {
					counts += 1;
				}
				else {
					isClosed = false; //do not count the 0 untile find the next 0 after number 1
					counts = 0; //reset the count 
				}
			}

		}
	}
	cout << endl;
	cout << " The gaps are: ";
	cout << maxNum;
}

void RotateTable() {

	/* compare 2 arrays A, B
	returns the minimum number of table rotations required so A[K] != B[K] 
	
	return -1 if can never have different number in same place
	
	return 0 if no need to turn */

	//int solution(vector<int> &A, vector<int> &B

	vector <int> A = { 1,2,3,4 }; // eg: { 1, 1, 1, 1 }, { 1,2,3,4}
	vector <int> B = { 0,3,1,4 }; // eg: { 1, 2, 3, 4 }, { 0,3,1,4 }
	int rotation = 0; //count rotation needed
	// loop when it is not a full rotation yet

	if (A.size() == 1) {
		if (A[0] == B[0]) {
			rotation = -1; 
		}

		else { rotation = 0; }
	}
	else {
	for (int k = 0; k < B.size(); k++) {
		// compare the number in the arrays
		for (int i = 0; i < B.size(); i++) {
			// if both arrays have the same number at the same place, do a rotation and update the number of rotation count
			if (A[i] == B[i] && rotation < B.size()) {
				std::rotate(B.begin(), B.begin() + B.size() - 1 , B.end());
				rotation += 1;
				//jump out of the loop redo the number check
				i = B.size();
				
			}
			// if we already did a full rotation and still have the same number in same place, return the rotation number to be -1
			else if (rotation == B.size() && A[i]==B[i]) {
				rotation = -1;
				break;
			}
		}
	}
	
	if (rotation > B.size() - 1) {
		rotation = -1;
	}
	cout << "Number of rotation needed: ";
	cout << rotation;	
	}


}

int Dinner(vector<int>& A, vector<int>& B) {
	unsigned int r = 0; //unsigned count rotation 
	int rotation = 0; //return this 

	// if only 1 number in array, check if they are the same 
	if (A.size() == 1) {
		if (A[0] == B[0]) {
			return -1;
		}

		else { return 0; }
	}

	else {
		// loop when it is not a full rotation yet 
		for (unsigned int k = 0; k < B.size(); k++) {
			// compare the number in the arrays
			for (unsigned int i = 0; i < B.size(); i++) {
				// if both arrays have the same number at the same place, do a rotation and update the number of rotation count 
				if (A[i] == B[i] && r < B.size()) {
					std::rotate(B.begin(), B.begin() + B.size() - 1, B.end());
					r += 1;
					rotation += 1;
					//jump out of the loop redo the number check 
					i = B.size();
				}
				// if we already did a full rotation and still have the same number in same place, return the rotation number to be -1
				else if (r == B.size() && A[i] == B[i]) {
					rotation = -1;
					break;
				}
			}
		}

		if (rotation > B.size() - 1) {

			rotation = -1;
		}
		return rotation;

	}

}

int OddOccurrencesInArray(vector<int>& A) {
	if (A.size() == 1) {
		return A[0];
	}

	std::sort(A.begin(), A.end());

	for (int i = 0; i < A.size(); i += 2) {
		if (A[i] != A[i + 1]) {
			return A[i];
		}
	}

}


int FrogJump(int X, int Y, int D) {
	/*A small frog wants to get to the other side of the road. 
	The frog is currently located at position X and wants to get to a position greater than or equal to Y. 
	The small frog always jumps a fixed distance, D.
	Count the minimal number of jumps that the small frog must perform to reach its target.*/
\
	//check if the end point is valid 
	if (Y > X) {
		// if the distance can not fully devided by D after taking the first move 
		// the divided remains +1
		if (((Y - X) % D) != 0) {
			cout << (((Y - X) / D) + 1);
			return  (((Y - X) / D) + 1);
		}
		// no remains 
		cout << ((Y - X) / D) ;
		return  ((Y - X) / D) ;
	}	
	
	// return 0 as the end point is not valid 
	cout << 0;
	return 0;
}

void MissingElem(vector<int>& A)
{
		/*Given an array A, returns the value of the missing element.*/
		cout<< (((A.size()+1)*(A.size()+2)/2) - (accumulate(A.begin(),A.end(),0)));
}

void TapeEquilibrium(vector<int>& A)
{	/*
	eg: {3,1,2,4,3}

	P = 1, difference = |3 − 10| = 7
	P = 2, difference = |4 − 9| = 5
	P = 3, difference = |6 − 7| = 1
	P = 4, difference = |10 − 3| = 7
	 returns the minimal difference that can be achieved.
	*/

	long diff = 0; //long has 64 bit storage 
	int sumLeft = A[0]; //left side of teh tape
	int sumRight = accumulate(A.begin() + 1, A.end(), 0); //right side of the tape, start with all the sum 
	long tape = abs(sumLeft - sumRight); 

	for (unsigned int i = 1; i < A.size() - 1; i++)
	{
		sumLeft += A[i];
		sumRight -= A[i];
		diff = abs(sumLeft - sumRight);
		if (diff <= tape)
		{
			tape = diff;
		}
	}
	
	cout<< tape;
}
