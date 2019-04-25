#include <iostream>
#include <fstream>

using namespace std;

/******************************************************
	matrixPrint()
	N - one side pMatrix size
	pMatrix - pointer to N*N array(pMatrix)
******************************************************/
void matrixPrint(size_t N, const uint32_t* pMatrix);


enum class Direction {
	RIGHT,
	LEFT
};
/*******************************************************
	matrixRotate()
	N - one side pMatrix size
	pMatrix - pointer to N*N array(pMatrix)
********************************************************/
uint8_t matrixRotate(size_t N, uint32_t* pMatrix, Direction dir);

/****************************************************************
	getSqrMatrix() - create two-dimensional array(square matrix)
	from one-dimensonal without copy 
	N - one side pMatrix size
	pMatrix - pointer to N*N array(pMatrix)
	return - pointer to two-dimensional array (square matrix)
****************************************************************/
uint32_t** getSqrMatrix(size_t N, uint32_t* pMatrix);

/****************************************************************
	sqrMatrixRotateLeft() - rotate square matrix to the left
	by 90deg.
	N - side size
	pSqrMatrix -  pointer to two-dimensional array
****************************************************************/
void sqrMatrixRotateLeft(size_t N, uint32_t** pSqrMatrix);

/****************************************************************
	sqrMatrixRotateRight() - rotate square matrix to the right
	by 90deg.
	N - side size
	pSqrMatrix -  pointer to two-dimensional array
****************************************************************/
void sqrMatrixRotateRight(size_t N, uint32_t** pQuadMatrix);

/****************************************************************
	sqrMatrixPrint() - print square matrix
	N - side size
	pSqrMatrix -  pointer to two-dimensional array
****************************************************************/
void sqrMatrixPrint(size_t N, uint32_t** pSqrMatrix);

int main()
{
	ifstream inputFile;
	inputFile.open("input.txt");
	if (!inputFile.is_open()) {
		cout << "File isn't open!\n";
		return 0;
	}
	size_t N = 0;
	inputFile >> N;
	if (N == 0) {
		cout << "Err! N = 0 \n";
		return 0;
	}
	uint32_t* pMatrix = new uint32_t[N * N];
	if (pMatrix) {
		for (size_t i = 0; !inputFile.eof() && (i < N * N); ++i) {
			inputFile >> pMatrix[i];
		}
		inputFile.close();

		cout << "input matrix:\n";
		matrixPrint(N, pMatrix);
		cout << endl;

		cout << "rotate to the right:\n";
		matrixRotate(N, pMatrix, Direction::RIGHT);
		matrixPrint(N, pMatrix);
		cout << endl;


		cout << "rotate twice to the left:\n";
		matrixRotate(N, pMatrix, Direction::LEFT);
		matrixPrint(N, pMatrix);
		cout << endl;
		matrixRotate(N, pMatrix, Direction::LEFT);
		matrixPrint(N, pMatrix);
		cout << endl;

	}


	return 0;
}


uint8_t matrixRotate(size_t N, uint32_t* matrix, Direction dir) {
	uint32_t** pSqrMatrix = getSqrMatrix(N, matrix);
	if (!pSqrMatrix) {
		return -1;
	}

	switch (dir) {
	case Direction::LEFT:
		sqrMatrixRotateLeft(N, pSqrMatrix);
		break;
	case Direction::RIGHT:
		sqrMatrixRotateRight(N, pSqrMatrix);
		break;
	}

	delete[] pSqrMatrix;
	return 0;
}



void matrixPrint(size_t N, const uint32_t* pMatrix) {
	for (size_t i = 0; i < N; ++i) {
		for (size_t j = 0; j < N; ++j) {
			printf("%4u", pMatrix[i * N + j]);
		}
		cout << endl;
	}
}


uint32_t** getSqrMatrix(size_t N, uint32_t * pMatrix) {
	uint32_t** pSqrMatrix = new uint32_t * [N];
	if (pSqrMatrix) {
		for (size_t i = 0; i < N; ++i) {
			pSqrMatrix[i] = pMatrix + i * N;
		}
	}
	return pSqrMatrix;
}

void sqrMatrixPrint(size_t N, uint32_t * * pSqrMatrix) {
	for (size_t i = 0; i < N; ++i) {
		for (size_t j = 0; j < N; ++j) {
			printf("%4u", pSqrMatrix[i][j]);
		}
		cout << endl;
	}
}

void sqrMatrixRotateLeft(size_t N, uint32_t * * pSqrMatrix) {
	for (size_t i = 0; i < N / 2; ++i) {
		for (size_t j = i; j < N - i - 1; ++j) {
			uint32_t tmp = pSqrMatrix[i][j];
			pSqrMatrix[i][j] = pSqrMatrix[j][N - 1 - i];
			pSqrMatrix[j][N - 1 - i] = pSqrMatrix[N - 1 - i][N - 1 - j];
			pSqrMatrix[N - 1 - i][N - 1 - j] = pSqrMatrix[N - 1 - j][i];
			pSqrMatrix[N - 1 - j][i] = tmp;

#ifdef DEBUG
			cout << '(' << i << ", " << j << ')' << endl;
			quadMatrixPrint(N, pSqrMatrix);
			cout << endl;
#endif
		}
	}
}

void sqrMatrixRotateRight(size_t N, uint32_t * *pQuadMatrix) {
	for (size_t i = 0; i < N / 2; ++i) {
		for (size_t j = i; j < N - i - 1; ++j){
			uint32_t tmp = pQuadMatrix[i][j];
			pQuadMatrix[i][j] = pQuadMatrix[N - j - 1][i];
			pQuadMatrix[N - j - 1][i] = pQuadMatrix[N - i - 1][N - j - 1];
			pQuadMatrix[N - i - 1][N - j - 1] = pQuadMatrix[j][N - i - 1];
			pQuadMatrix[j][N - i - 1] = tmp;
#ifdef DEBUG
			cout << '(' << i << ", " << j << ')' << endl;
			quadMatrixPrint(N, pQuadMatrix);
			cout << endl;
#endif
		}
	}
}

