import sympy
import hashlib
#from sympy.combinatorics import Permutation
#Permutation.print_cyclic = True
import numpy as np
from sympy.combinatorics import *
from sympy.matrices import Matrix
from itertools import islice
#sympy.init_printing(pretty_print=False)



def main():
    A = np.array([[1,0],[0,2]])

    la, v = np.linalg.eig(A)  
    print("koyuuti", la)
    print("koyuu_vector", v)

if __name__ == '__main__':
    main()
P=0xFFFFFFFFFFFFFFFFC90FDAA22168C234C4C6628B80DC1CD129024E088A67CC74020BBEA63B139B22514A08798E3404DDEF9519B3CD3A431B302B0A6DF25F14374FE1356D6D51C245E485B576625E7EC6F44C42E9A637ED6B0BFF5CB6F406B7EDEE386BFB5A899FA5AE9F24117C4B1FE649286651ECE45B3DC2007CB8A163BF0598DA48361C55D39A69163FA8FD24CF5F83655D23DCA3AD961C62F356208552BB9ED529077096966D670C354E4ABC9804F1746C08CA18217C32905E462E36CE3BE39E772C180E86039B2783A2EC07A28FB5C55DF06F4C52C9DE2BCBF6955817183995497CEA956AE515D2261898FA051015728E5A8AACAA68FFFFFFFFFFFFFFFF
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
X=Permutation.random(6)

print(X)
Y=Permutation.random(6)
print(Y)
R=Permutation.random(6)
Z=X**-1


W=X*Y*Z
print(W)
F=X*R*Z
G=W*F*W*F*W
H=Y*R*Y*R*Y
print(X*H*X**-1)
print(G)
exit()


sympy.expr0=W*RR-RR*Y
print(X)
print(sympy.solve(sympy.expr0.subs(a,1)))
print(sympy.solve(sympy.expr0.subs(b,1)))
print(sympy.solve(sympy.expr0.subs(c,1)))
print(sympy.solve(sympy.expr0.subs(d,1)))
print(sympy.solve(sympy.expr0.subs(e,1)))
print(sympy.solve(sympy.expr0.subs(w6,1)))

R1=R
W1=X**2*Y*Z**2
B=Permutation.random(10)
print(B)
#
W2=sympy.Matrix(([w0,w1,w2],[w3,w4,w5],[w6,w7,w8]))
print(hashlib.sha256(str(R1)).hexdigest())
print(R1)
#print(W.inv()**3*W1**3)

WW=W**8*W1**8
print(WW)


#sympy.Matrix(([a,b],[c,d]))
C=X.inv()*WW*X**2
sympy.expr1=RR*C-X*RR
#sympy.expr1=(RR*(r*W1*W1+s*W1+t*E)-WW*RR)
print(Y**8)
T=sympy.solve(sympy.expr1)
print(sympy.solve(sympy.expr0.subs(a,1)))
print(sympy.solve(sympy.expr0.subs(b,1)))
print(sympy.solve(sympy.expr0.subs(c,1)))
print(sympy.solve(sympy.expr0.subs(d,1)))
print(sympy.solve(sympy.expr0.subs(e,1)))
print(sympy.solve(sympy.expr0.subs(w6,1)))
print(sympy.solve(sympy.expr0.subs(z6,1)))
print(T)
#exit()

#sympy.expr2=(a*Y**7+b*Y**6+c*Y**5+d*Y**4+e*Y**3+f*Y**2+g*Y+h*E)*X.inv()*WW*X**2-X*(a*Y**7+b*Y**6+c*Y**5+d*Y**4+e*Y**3+f*Y**2+g*Y+h*E)
#print(sympy.expr2)
sympy.expr3=(Y**7-(a*Y**6+b*Y**5+c*Y**4+d*Y**3+e*Y**2+f*Y+g*E))
R2=sympy.solve(sympy.expr3)
print(R2)
print(Y**7)
exit()

R2=sympy.solve(sympy.expr3.subs(w1,1))
print(R2)
R2=sympy.solve(sympy.expr3.subs(w2,1))
print(R2)
R2=sympy.solve(sympy.expr3.subs(w3,1))
print(R2)
R2=sympy.solve(sympy.expr3.subs(w4,1))
print(R2)
R2=sympy.solve(sympy.expr3.subs(w5,1))
print(R2)

#
print(Y**8)
exit()

E=sympy.solve(sympy.expr2.subs(w0,1))
print(E)
print(sympy.solve(sympy.expr1,sympy.expr2))
B=sympy.Matrix(([1,2],[4,5]))
C=sympy.Matrix(([3,1],[1,4]))
D=sympy.Matrix(([a,b],[c,d]))
sympy.expr5=D*B-C*D
print(sympy.solve(sympy.expr5))
exit()

A[0]=R2[a]
A[1]=R2[b]
A[2]=R2[c]
A[3]=R2[d]
A[4]=R2[e]
A[5]=R2[f]
A[6]=R2[g]
A[7]=R2[h]
A[8]=R2[i]
A[9]=R2[j]
A[10]=R2[k]
A[11]=R2[l]
A[12]=R2[n]
A[13]=R2[m]
A[14]=R2[o]
A[15]=R2[p]

print(hashlib.sha256(str(A)).hexdigest())
