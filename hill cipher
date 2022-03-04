// C++ program to find adjoint and inverse of a matrix
#include<bits/stdc++.h>
using namespace std;
#define N 2    
#define R1 2            
#define C1 2            
#define R2 2            
#define C2 2            
//change size here
int inv(int a){
    for(int i=1;i<26;i++){
        if((i*a)%26==1)
            return i;
    }
  return 0;
}
int in_range(int x){
    return ((x%26)+26)%26;  
}
void getCofactor(int A[N][N], int temp[N][N], int p, int q, int n)
{
	int i = 0, j = 0;
	for (int row = 0; row < n; row++)
	{
		for (int col = 0; col < n; col++)
		{
			if (row != p && col != q)
			{
				temp[i][j++] = A[row][col];
				if (j == n - 1)
				{
					j = 0;
					i++;
				}
			}
		}
	}
}
int determinant(int A[N][N], int n)
{
	int D = 0; 
	if (n == 1)
		return A[0][0];
	int temp[N][N]; // To store cofactors
	int sign = 1; // To store sign multiplier
	for (int f = 0; f < n; f++)
	{
		getCofactor(A, temp, 0, f, n);
		D += sign * A[0][f] * determinant(temp, n - 1);
		sign = -sign;
	}
	return D;
}

void adjoint(int A[N][N],int adj[N][N])
{
	if (N == 1)
	{
		adj[0][0] = 1;
		return;
	}
	int sign = 1, temp[N][N];

	for (int i=0; i<N; i++)
	{
		for (int j=0; j<N; j++)
		{
			getCofactor(A, temp, i, j, N);
			sign = ((i+j)%2==0)? 1: -1;
			adj[j][i] = (sign)*(determinant(temp, N-1));
		}
	}
}
bool inverse(int A[N][N], int inverse[N][N])
{
	int det = determinant(A, N);
	if (det == 0)
	{
		cout << "Singular matrix, can't find its inverse";
		return false;
	}
	int adj[N][N];
	adjoint(A, adj);
  if(inv(in_range(det))==0)
  {
    cout<<"det not invertible ";
    return false;
  }
	for (int i=0; i<N; i++)
		for (int j=0; j<N; j++)
			inverse[i][j] = in_range(adj[i][j]*inv(in_range(det)));

	return true;
}
template<class T>
void display(T A[N][N])
{
	for (int i=0; i<N; i++)
	{
		for (int j=0; j<N; j++)
			cout << A[i][j] << " ";
		cout << endl;
	}
}
void mulMat(int mat1[][C1], int mat2[][C2]) {
    int rslt[R1][C2];
 
    cout << "key is:\n" << endl;
 
    for (int i = 0; i < R1; i++) {
        for (int j = 0; j < C2; j++) {
            rslt[i][j] = 0;
 
            for (int k = 0; k < R2; k++) {
                rslt[i][j] += mat1[i][k] * mat2[k][j];
            }
            rslt[i][j]=in_range(rslt[i][j]);
            cout << rslt[i][j] << "\t";
        }
 
        cout << endl;
    }
}
// Driver program
int main()
{
	int A[N][N] = { {5, 6},    //message 
					{9, 5}
					// {-3, 1, 5, 0},
					// {3, -1, -9, 4}
  };
  int cipher[N][N]={{11,21},
          {8,14}
          // {9,10,11,12},
          // {1,2,3,4}
  };
	int adj[N][N]; // To store adjoint of A[][]
	int inv[N][N]; // To store inverse of A[][]
	cout << "Input matrix is :\n";
	display(A);
	cout << "\nThe Adjoint is :\n";
	adjoint(A, adj);
	display(adj);
	cout << "\nThe Inverse is :\n";
	if (inverse(A, inv)){
    display(inv);
    mulMat(inv,cipher);
  }
		

  
	return 0;
}
