#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <thread>
using namespace std;

// Function for initializing the values in single Matrix
void initMatrix(vector<vector<int>> &Matrix, int rows, int cols)
{
    Matrix.resize(rows, vector<int>(cols));

    /* iterate through the matrix and assign random values in left to right,top to down manner,all columns for row 0
       all columns for row 1 and so on */
    for (int i = 0; i < Matrix.size(); i++)
    {
        for (int j = 0; j < Matrix[0].size(); j++)
        {
            Matrix[i][j] = rand();
        }
    }
}

// function for initializing values in both Matrices
void initMatrices(vector<vector<int>> &matrixA, vector<vector<int>> &matrixB, char *argv[])
{
    // calculate the row and column by converting the string argument into integers using stoi
    int M1rowCount = stoi(argv[1]);
    int M2colCount = stoi(argv[2]);

    int M1colCount = 1000;
    int M2rowCount = 1000;

    // assign the seed for matrix A and init matrix A
    srand(0x1234);
    initMatrix(matrixA, M1rowCount, M1colCount);

    // assign the seed for matrix B and init matrix B
    srand(0x3535);
    initMatrix(matrixB, M2rowCount, M2colCount);
}

// function for multiplying a single row of matrix A and single column of matrix B
int multRowCol(vector<vector<int>> &matrixA, vector<vector<int>> &matrixB, vector<vector<long>> &result, int rowNum, int colNum)
{
    int sum = 0;

    /* iterate though the entire row of matrix A
    columns of A = rows of B */

    for (int i = 0; i < matrixA[rowNum].size(); i++)
    {
        sum += matrixA[rowNum][i] * matrixB[i][colNum];         // multiply column value of matrix A with row value of matrix B
    }

    result[rowNum][colNum] = sum;                               // write the sum in result matrix
    return sum;
}

// function for multiplying matrices with K rows and K columns given starting and ending indexes
vector<vector<long>> multKRowCol(vector<vector<int>> &matrixA, vector<vector<int>> &matrixB, vector<vector<long>> &result, int row_si, int col_si, int row_ei, int col_ei)
{
    vector<vector<long>> sums(row_ei, vector<long>(col_ei));

    // iterate through the starting and ending row and col ranges
    for (int i = row_si; i < row_ei; i++)
    {
        for (int j = col_si; j < col_ei; j++)
        {
            /*
            call multRowCol for each row and column
            store the resultant value in sums array
            */
            sums[i][j] = multRowCol(matrixA, matrixB, result, i, j);
        }
    }

    return sums;
}

// function for multiplying matrices using less threads
vector<vector<long>> multMatrixCase2(vector<vector<int>> &matrixA, vector<vector<int>> &matrixB)
{

    // assign the value of division of threads
    int k = 10;

    /*  calculate the the number of threads require for row and columns, if 50 rows of matrix A and 50 cols of matrix B
        5 threads each containing K (10) rows of matrixA and
        5 threads each containing K (10) columns of matrixB     */
    int rowDim = matrixA.size() / k;
    int colDim = matrixB[0].size() / k;

    /*  calculate the reminder rows and columns
        if 52 rows of matrix A and 52 cols of matrix B and k=10
        remaining  rows and cols =2     */
    int remRows = matrixA.size() % k;
    int remCols = matrixB[0].size() % k;

    // init the indexes and count require for number of threads
    int tCount = rowDim * colDim;
    int tIndex = 0;

    // init resultant matrix and threads
    vector<vector<long>> result(matrixA.size(), vector<long>(matrixB[0].size()));
    thread *threads = new thread[tCount];

    int row_si, row_ei;
    int col_si, col_ei;

    /*  if 50 rows of matrix A and 50 cols of matrix B
        0-10 rows are multiplied with 0-10 cols, then 10-20 cols till 40-50 cols etc */
    for (int i = 0; i < rowDim; i++)
    {

        /*  calculate the starting row index
            if k=10 and i=0 then rsi=0 and rei = 0+10=10    */
        row_si = i * k;

        // if it is the last range, add the remainder rows left by division
        if (i == rowDim - 1)
            row_ei = row_si + k + remRows;
        else
            row_ei = row_si + k;

        for (int j = 0; j < colDim; j++)
        {
            // calculate the starting column index
            col_si = j * k;

            /* if it is the last column range, add the remainder columns in the last thread left by division
             create a new thread calculating a matrix with K rows and K columns */
            if (j == colDim - 1)
            {
                col_ei = col_si + k + remCols;
                threads[tIndex++] = thread(multKRowCol, ref(matrixA), ref(matrixB), ref(result), row_si, col_si, row_ei, col_ei);
            }
            else
            {
                col_ei = col_si + k;
                threads[tIndex++] = thread(multKRowCol, ref(matrixA), ref(matrixB), ref(result), row_si, col_si, row_ei, col_ei);
            }
        }
    }

    // join all the created threads
    for (int i = 0; i < tCount; i++)
    {
        threads[i].join();
    }

    cout << "Number of threads: " << tCount << endl;
    return result;
}

// function for multiplying matrices
vector<vector<long>> multMatrixCase1(vector<vector<int>> &matrixA, vector<vector<int>> &matrixB)
{

    vector<vector<long>> result(matrixA.size(), vector<long>(matrixB[0].size()));

    // init index of thread array and total number of threads
    int tCount = matrixA.size() * matrixB[0].size();
    int tIndex = 0;
    thread *threads = new thread[tCount];

    // loop for total number of rows in matrix A
    for (int i = 0; i < matrixA.size(); i++)
    {
        // loop for total number of columns in matrix B
        for (int j = 0; j < matrixB[0].size(); j++)
        {
            // create threads for each row and col and make changes in resultant array
            threads[tIndex++] = thread(multRowCol, ref(matrixA), ref(matrixB), ref(result), i, j);
        }
    }

    // join all the created threads
    for (int i = 0; i < tCount; i++)
    {
        threads[i].join();
    }

    cout << "Number of threads: " << tCount << endl;
    return result;
}

// function for checking command line arguments
bool isRetConditions(int argc, char *argv[])
{
    // arguments must be 3
    if (argc < 3 || argc > 3)
        return true;

    // convert string to int
    int M1rowCount = stoi(argv[1]);
    int M2colCount = stoi(argv[2]);

    // check arguments count
    if (M1rowCount < 50 || M1rowCount > 75 || M2colCount < 50 || M2colCount > 75)
        return true;

    return false;
}

int main(int argc, char *argv[])
{

    // check conditions for arguments
    if (isRetConditions(argc, argv))
        return -1;

    // delcare two vectors for matrix multiplication
    vector<vector<int>> matrixA, matrixB;
    vector<vector<long>> result;

    // initialize the matrices
    initMatrices(matrixA, matrixB, argv);

    // calculate time of case 1
    auto begin = std::chrono::high_resolution_clock::now();
    result = multMatrixCase1(matrixA, matrixB);
    auto end = std::chrono::high_resolution_clock::now();
    cout << "Execution time of Case 1 in ms: " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << endl;

    // calculate time of case 2
    begin = std::chrono::high_resolution_clock::now();
    result = multMatrixCase2(matrixA, matrixB);
    end = std::chrono::high_resolution_clock::now();
    cout << "Execution time of Case 2 in ms: " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << endl;
}

