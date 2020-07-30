import sympy
import hashlib
#from sympy.combinatorics import Permutation
#Permutation.print_cyclic = True
import numpy as np
from sympy.combinatorics import *
from sympy.matrices import Matrix
from itertools import islice
#sympy.init_printing(pretty_print=False)



o,p,q,r,s,t,u,v,w,x,y,z = sympy.symbols('o,p,q,r,s,t,u,v,w,x,y,z')
a0,a1,a2,a3,a4,a5,a6,a7,a8,a9 = sympy.symbols('a0,a1,a2,a3,a4,a5,a6,a7,a8,a9')
z0,z1,z2,z3,z4,z5,z6,z7,z8,z9,z10 = sympy.symbols('z0,z1,z2,z3,z4,z5,z6,z7,z8,z9,z10')
RR,w0,w1,w2,w3,w4,w5,w6,w7,w8,w9,w10 = sympy.symbols('RR,w0,w1,w2,w3,w4,w5,w6,w7,w8,w9,w10')
a,b,c,d,e,f,g,h,i,j,k,l,n,m = sympy.symbols('a,b,c,d,e,f,g,h,i,j,k,l,n,m')
Y=sympy.Matrix(([0,0,0,0,0,0,1],[0,0,1,0,0,0,0],[0,0,0,0,0,1,0],[0,0,0,1,0,0,0],[0,0,0,0,1,0,0],[0,1,0,0,0,0,0],[1,0,0,0,0,0,0]))
#sympy.Matrix(([5,3],[2,4]))
print("Y**2=")
print(Y*Y)
print("Y**3=")
print(Y**3)
print("Y**4=")
print(Y**4)
print("Y**5=")
print(Y**5)
print("Y=")
print(Y)

#
#Permutation.random(4)
#
X=sympy.Matrix(([0,0,1,0,0,0,0],[0,1,0,0,0,0,0],[0,0,0,0,0,1,0],[0,0,0,0,1,0,0],[0,0,0,1,0,0,0],[0,0,0,0,0,0,1],[1,0,0,0,0,0,0]))
#sympy.Matrix(([6,7],[1,11]))
print(X)

#Permutation.random(4)
#
E=sympy.Matrix(([1,0,0,0,0,0,0],[0,1,0,0,0,0,0],[0,0,1,0,0,0,0],[0,0,0,1,0,0,0],[0,0,0,0,1,0,0],[0,0,0,0,0,1,0],[0,0,0,0,0,0,1]))
#sympy.Matrix(([1,0],[0,1]))
#
A=sympy.Matrix(([0,0],[0,0]))
#
R=sympy.Matrix(([0,0,0,0,0,0,1],[0,0,0,0,0,1,0],[0,0,0,0,1,0,0],[0,0,0,1,0,0,0],[0,0,1,0,0,0,0],[0,1,0,0,0,0,0],[1,0,0,0,0,0,0]))
#sympy.Matrix(([7,4],[1,9]))
#
K=sympy.Matrix(([0,0,1,0,0],[0,0,0,1,0],[0,1,0,0,0],[0,0,0,0,1],[0,1,0,0,0]))
#Permutation.random(4)
#
RR=sympy.Matrix(([a,b,c,d,e,w6,z6],[f,g,h,i,j,w7,z7],[k,l,n,m,o,w8,z8],[p,q,r,s,t,w9,z9],[u,v,w,x,y,w10,z10],[z0,z1,z2,z3,z4,z5,a0],[a1,a2,a3,a4,a5,a6,a7]))
#Matrix(([0,1,0],[0,0,1],[1,0,0]))

#X=Permutation.random(10)
#print(X)
#Y=Permutation.random(10)
#print(Y)
#R=Permutation.random(10)
Z=X**-1


W=X*Y*Z
print(W)
F=X*R*Z
G=W*F*W*F*W
H=Y*R*Y*R*Y
print(X**-1*G*X)
print(H)

sympy.expr0=W*RR-RR*Y
print(X)
print(sympy.solve(sympy.expr0.subs(a,1)))
print(sympy.solve(sympy.expr0.subs(b,1)))
print(sympy.solve(sympy.expr0.subs(c,1)))
print(sympy.solve(sympy.expr0.subs(d,1)))
print(sympy.solve(sympy.expr0.subs(e,1)))
print(sympy.solve(sympy.expr0.subs(w6,1)))
print(sympy.solve(sympy.expr0.subs(z6,1)))
