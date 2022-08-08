#include <vector>
#include <iostream>
using namespace std;

#ifndef MATRIX_H
#define MATRIX_H

template <typename Obj>
class matrix
{
private:
    /* data */
    vector<vector< Obj> > array;
    int shape[2];
public:
    matrix(int rows, int cols) : array(rows)
    {
        for(int i=0; i<rows; i++)
            array[i].resize(cols);
        shape[0]=rows;
        shape[1]=cols;
    }
    const vector<Obj> &operator[] (int row) const 
    {return array[row];}
    vector<Obj> & operator[] (int row)
    {return array[row];}
    
    void printM()
    {
        for(int i=0; i<shape[0]; i++){
            for(int j=0; j<shape[1]; j++)
                cout<<array[i][j]<<", ";
            cout<<endl;
        }
    }

    int numrow()
    {return shape[0];}
    int numcol()
    {return shape[1];}

};


#endif
int main(int argc, char const *argv[])
{
    /* code */
    matrix<int> M(5, 6);
    M[1][2]=5;
    M[2][3]=M[1][2];
    M.printM();
    cout<<M[1][2]<<endl;

    return 0;
}
