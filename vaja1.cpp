#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

bool readNumbers(vector<int> &vec, const char s[]) {
    ifstream input(s);
    int num;

    if (!input.is_open()) {
        return false;
    }

    while (!input.eof()) {
        input >> num;
        vec.push_back(num);
        while (isspace(input.peek())) input.get();
    }
    input.close();
    return true;
}

void outputNumbers(int* field, unsigned int vec_size) {
    ofstream output("out.txt");

    for (int i = 0; i < vec_size; i++) {
        output << field[i] << ' ';
    }
}

int main(int argc, const char* argv[]) {
    vector<int> A;
    vector<int> B;
    vector<int> C;
    int i, toFill = 0;

    if (argc < 3) return 0;
    if (!readNumbers(A, argv[2])) return 0;

    int mini = *min_element(A.begin(), A.end());
    for (i = 0; i < A.size(); i++) {
        A[i] = A[i] - (mini);
    }

    int maxi = *max_element(A.begin(), A.end());
    for (i = 0; i < (maxi + 1); i++) {
        C.push_back(toFill);
    }

    for (i = 0; i < A.size(); i++) {
        C[A[i]] = C[A[i]] + 1;
    }

    if (argv[1][0] == '0') {
        //counting sort
        for (i = 1; i < C.size(); i++) {
            C[i] = C[i] + C[i-1];
        }

        for (i = 0; i < A.size(); i++) {
            B.push_back(toFill);
        }

        for (i = (A.size() - 1); i >= 0; i--) {
            B[C[A[i]]-1] = A[i];
            C[A[i]] = C[A[i]] - 1;
        }
    }
    else {
        //Roman sort
        for (i = 0; i < C.size(); i++) {
            for (int j = 0; j < C[i]; j++) {
                B.push_back(i);
            }
        }
    }
    for (i = 0; i < B.size(); i++) {
        B[i] = B[i] + (mini);
    }
    outputNumbers(&B[0],B.size());

    return 0;
}
