#include<bits/stdc++.h>
#define N 8
using namespace std;
void ShowBoard(int board[N][N])         //A function used to print the solution
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
        {
            cout<<" "<<board[i][j];
        }
		cout<<endl;
	}
}

bool CheckSafety(int row, int col, int diag1[N][N],int diag2[N][N], bool row_check[],bool diag1_check[], bool diag2_check[] )      //Function to check safety of queen
{
	if (diag1_check[diag1[row][col]] || diag2_check[diag2[row][col]] || row_check[row])
        return false;
    return true;
}

bool main_solve(int board[N][N], int col,
	int diag1[N][N], int diag2[N][N], bool row_check[N],
	bool diag1_check[], bool diag2_check[] )
{
	if (col >= N)
		return true;
	for (int i = 0; i < N; i++)
	{
		if ( CheckSafety(i, col, diag1, diag2, row_check,
					diag1_check, diag2_check) )
		{
			board[i][col] = 1;
			row_check[i] = true;
			diag1_check[diag1[i][col]] = true;
			diag2_check[diag2[i][col]] = true;

			if ( main_solve(board, col + 1, diag1, diag2,
					row_check, diag1_check, diag2_check) )
				return true;

			board[i][col] = 0;
			row_check[i] = false;
			diag1_check[diag1[i][col]] = false;
			diag2_check[diag2[i][col]] = false;
		}
	}
	return false;
}

bool initiator_function()
{
	int board[N][N];
	memset(board, 0, sizeof board);

	int diag1[N][N];
	int diag2[N][N];

	bool row_check[N] = {false};

	bool diag1_check[2*N - 1] = {false};
	bool diag2_check[2*N - 1] = {false};

	for (int r = 0; r < N; r++)
		for (int c = 0; c < N; c++)
			diag1[r][c] = r + c,
			diag2[r][c] = r - c + 7;

	if (main_solve(board, 0, diag1, diag2,
	row_check, diag1_check, diag2_check) == false )
	{
		cout<<"No Solution\n";
		return false;
	}

	ShowBoard(board);
	return true;
}

int main()
{
	initiator_function();       //No input needed as problem has fixed size of N=8
    return 0;
}

