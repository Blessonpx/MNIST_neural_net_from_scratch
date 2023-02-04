#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/operation.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/io.hpp>

using namespace std;
using namespace boost::numeric::ublas;
void printMatrix(matrix<int> matrix){
    for(unsigned int i=0;i<matrix.size1();i++){
        for(unsigned int j=0;j<matrix.size2();j++){
            cout<<matrix(i,j);
            if(j+1!=matrix.size2()){
                cout << "\t";
            }
        }
        cout<<endl;
    }
}
// Matrix Modify Column
void rowProxyModify(matrix<int> &A){
    for (unsigned int i=0;i<A.size1();i++){
        matrix_row<matrix<int>> mr (A,i);
        for (unsigned j = 0; j < mr.size (); ++ j)
            mr (j) = 3 * i + j;
    }
}
// Matrix Modify Row
void columnProxyModify(matrix<int> &A){
    for (unsigned int i=0;i<A.size2();i++){
        matrix_column<matrix<int>> mc (A,i);
        for (unsigned j = 0; j < mc.size (); ++ j)
            mc(j) = 3 * i + j;
    }
}
// Read CSV and return matrix Function
void readDataCsv(matrix<int> &A,string filename){
    // Use separator for this from regex command
}

int main(int argc, char* argv[]){
    cout<<"Inside code"<<endl;
    // Declare matrix of size n
    int n=4;
    matrix<int> A(n,n);
    int a=1;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            A(i,j) = a;
			a++;
        }
    }
    printMatrix(A);
    // Change a segment of matrix with help of proxies if possible
    rowProxyModify(A);
    cout<<"After Row Proxy Modifications"<<endl;
    printMatrix(A);
    columnProxyModify(A);
    cout<<"After Column Proxy Modifications"<<endl;
    printMatrix(A);
    // Operations with Matrix Range and Matrix Projections  and Matrix Expressions
    // Vector RANGE
    matrix_vector_range<matrix<int>> mvr (A, range (1, 3), range (1, 3));
    cout << mvr <<endl;
    matrix_vector_range<matrix<int>> mvr2 (A, range (0, 3), range (0, 3));
    cout << mvr2 <<endl;
    // Vector SLICE
    matrix_vector_slice<matrix<int> > mvs (A, slice (0, 1, 4), slice (0, 1, 4));
    std::cout << mvs << std::endl;
    // Now Read CSV Files
    string filename;
    //filename = argv[1];
    if (argc < 2) {
		filename = "NA";
	} else {
		filename = argv[1];
	}
    cout<<"FileName is "<<filename<<endl;
    cout<<"argc :"<<argc<<endl;
    int size_k=9;
    matrix<int> J(size_k,size_k);
    readDataCsv(J,filename);
    return 0;
}