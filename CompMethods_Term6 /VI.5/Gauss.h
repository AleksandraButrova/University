#define eps	1e-10

void  BackSubstitution(double **A, double *x, int N);

//2. Метод Гаусса с выбором главного элемента по столбцу
void SwapLine(double **A, int i, int minInd, int N);
void ChooseColumn(double **A, int i, int N);
void ForwardEliminationColumn(double **A, int N);
void GaussColumn(double **A, double *x, int N);

void printMatrix(double **Matrix, int n, int m);
void error(double **A, double *x, int N);

//4. Нахождение обратной матрицы методом Гаусса с выбором
void MtoA_withI(double **M, double **A, int I, int N);
double ** InverseA(double **A, int N);


void SwapRaws(double **matrix, int first, int second, int n);
double* GaussRow(double** matrix, int n);
