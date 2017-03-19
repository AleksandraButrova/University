import numpy
from scipy import integrate
from scipy.special import jacobi
from tabulate import tabulate
 
a = -1.0
b = 1.0
 
Q1 = numpy.poly1d([1])
Q2 = numpy.poly1d([1, 0])
 
 
def f(x):
    return 1 + x / 2
 
def w(n):
    if n == 1:
        return [Q1]
    elif n == 2:
        return [Q1, Q2]
    else:
        jacobi_tail = [numpy.poly1d([1, 0, -2, 0, 1]) *
                       jacobi(i - 3, 2, 2) for i in range(3, n + 1)]
        return [Q1, Q2] + jacobi_tail
 
 
def L_diff(w, x):
    w_2 = numpy.polyder(w, 2)
    w_1 = numpy.polyder(w, 1)
    ans = -2 / (2 + x) * w_2(x) + ( (1+x) / 2 + 2 / ((2 + x)**2) )* w_1(x) + numpy.cos(x / 2) * w(x)
    return ans
 
def FindC(l, n):
    L, g = l(n)
    return numpy.linalg.solve(L, g)
 

def L_Gal(n):
    L = numpy.zeros((n, n))
    g = numpy.zeros(n)
    W = w(n)
 
    for j in range(0, n):
        for i in range(0, n):
            L[j, i] = integrate.quad(lambda x: W[j](x) * L_diff(W[i], x), a, b)[0]
        g[j] = integrate.quad(lambda x: W[j](x) * f(x), a, b)[0]


    
    return L, g

def colloc_points(n):
    return [numpy.cos(((2 * i - 1) * numpy.pi) / (2 * n)) for i in range(1, n + 1)]
 
def L_Collocation(n):
    L = numpy.zeros((n, n))
    g = numpy.zeros(n)
    W = w(n)
    X = colloc_points(n)
 
    for i in range(0, n):
        for j in range(0, n):
            L[i, j] = L_diff(W[j], X[i])
        g[i] = f(X[i])
    return L, g
 

def Calculate(W, C, n):
    return lambda x: numpy.dot(numpy.array([W[i](x) for i in range(0, n)]), C)
 
def printExMatrix(L, g, n):
    print('\nExtended Matrix:\n')
    for i in range(n):
        for j in range(n):
            print ('%-10f' % L[i][j], end = '\t')
        print('%-10f' % g[i], end = '\n')
    print ()
    return
 
def print_table(n, a, b, l):
    L, g = l(n)
    printExMatrix(L, g, n)

    
    table = []
    for i in range(3, n + 1):
        W = w(i)
        C = FindC(l, i)
        sol = Calculate(W, C, i)
        table.append([i, sol(a), sol((a + b) / 2), sol(b)])
    print ('\nCoefficients:\n')
    for i in range (n):
        print ('%-10f' % C[i])
    
    print('\n\nSolution:\n')
    print('  '+ 'n'+(' '*2)+ (' ' * 14) + 'y_n(x)' + (' ' * 16))
    head = ['x = {0}'.format(a), 'x = {0}'.format((a + b) / 2), 'x = {0}'.format(b)]
    print(tabulate(table, headers=[' '] + head * 2, tablefmt="plain", floatfmt="f"))



#Start work---------------------------------------------------------------------------
num = 7
print('\n\n' + '_'*38 + '\n' +'_'*38)
print('Task 6.\nVar 4.\n')

print('-'*38)
print ('Galerkin method\n')
print_table(num, a, b, L_Gal)

print('\n\n'+ '-'*38)
print('Collocation method\n')
print_table(num, a, b, L_Collocation)
print('\n\n'+ '-'*38 + '\n\n')

