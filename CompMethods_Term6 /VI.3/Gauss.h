#define N 3
#define eps	0

void  BackSubstitution(double **A, double *x);

//2. Метод Гаусса с выбором главного элемента по столбцу
void SwapLine(double **A, int i, int minInd);
void ChooseColumn(double **A, int i);
void ForwardEliminationColumn(double **A);
void GaussColumn(double **A, double *x);

void printMatrix(double **Matrix, int n, int m);
void error(double **A, double *x);

//4. Нахождение обратной матрицы методом Гаусса с выбором
void MtoA_withI(double **M, double **A, int I);
double ** InverseA(double **A);