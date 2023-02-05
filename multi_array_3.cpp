#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/operation.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <fstream>
#include <boost/regex.hpp>



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
// Read CSV size and return column_size
int checkCsvColumnSize(string filename){
    // Use separator for this from regex command
    ifstream infile;
    string read_file_name(filename);
    infile.open(read_file_name);
    string sLine;
    int size_final=0;
    // Prints just the first line
    if (infile.good())
    {
        string sLine;
        getline(infile, sLine);
        boost::regex expr{"\\w+\\w+"};
        boost::regex_token_iterator<std::string::iterator> it{sLine.begin(), sLine.end(),expr};
        boost::regex_token_iterator<std::string::iterator> end;
        while (it != end){
            it++;
            size_final++;
        }
    }
    return size_final;
}
// Read CSV size and return row_size
int checkCsvRowSize(string filename){
    // Use separator for this from regex command
    ifstream infile;
    string read_file_name(filename);
    infile.open(read_file_name);
    string sLine;
    int size_final=0;
    while (!infile.eof())
    {
        getline(infile, sLine);
        //cout << sLine.data() << endl;
        ++size_final;
    }
    cout<<"size_final="<<size_final<<endl;
    return size_final-2;
}
// Read CSV file and file and return Filled Matrix 
void insertCsvData(matrix<int> &A,string filename,int row_size,int col_size){
    ifstream infile;
    string read_file_name(filename);
    infile.open(read_file_name);
    string sLine;
    int size_final=0;
    int tmp=0;
    std::vector <string> tokens;
    while (!infile.eof())
    {
        getline(infile, sLine);
        cout <<"size_final::="<<size_final<< endl;
        if(size_final<=row_size && size_final>0){
            // Fed sLine Data into the matrix for the specific row 
            // Matrix in index so should be no problem 
            // A(i,j)
            // Spilt the spline with Iterator
            unsigned int j=0;
            boost::regex expr{"\\w+\\w+"};
            boost::regex_token_iterator<std::string::iterator> it{sLine.begin(), sLine.end(),expr};
            boost::regex_token_iterator<std::string::iterator> end;
            //cout<<"Type of it="<<typeid(it).name()<<endl;
            
            while (it != end){
                //tmp=*it;
                //cout<<*it++<<endl;
                tokens.push_back(*it);
                string m1=tokens.back();
                int p=stoi(m1);
                A(size_final,j)=p;
                it++;
                j++;
            }
            //cout<<tokens<<endl;
        }
        ++size_final;
    }
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
    if (argc < 2) {
		filename = "NA";
	} else {
		filename = argv[1];
	}
    cout<<"FileName is "<<filename<<endl;
    cout<<"argc :"<<argc<<endl;
    int size_k=9;
    matrix<int> J(size_k,size_k);
    int size_col=checkCsvColumnSize(filename);
    int size_row=checkCsvRowSize(filename);
    cout<<"Size of CSV="<<size_col<<"::"<<size_row<<endl;
    // Now Create a Matrix of Size row*col
    matrix<int> train_data(size_row,size_col);
    insertCsvData(train_data,filename,size_row,size_col);
    return 0;
}