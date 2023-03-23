

# This file was *autogenerated* from the file mat.sage
from sage.all_cmdline import *   # import sage library

_sage_const_16 = Integer(16); _sage_const_10 = Integer(10); _sage_const_0 = Integer(0); _sage_const_1 = Integer(1); _sage_const_2 = Integer(2); _sage_const_3 = Integer(3); _sage_const_4 = Integer(4); _sage_const_5 = Integer(5); _sage_const_6 = Integer(6); _sage_const_7 = Integer(7); _sage_const_8 = Integer(8); _sage_const_9 = Integer(9)
M=MatrixSpace(GF(_sage_const_16 ,'a'),_sage_const_10 ,_sage_const_10 )
A=M([['a^10',_sage_const_0 ,'a','a^8',_sage_const_1 ,_sage_const_0 ,'a^9','a^2',_sage_const_1 ,'a^4'],
[_sage_const_0 ,'a^8',_sage_const_1 ,'a^9','a^2',_sage_const_1 ,'a','a^14','a^9','a^4'],
['a',_sage_const_1 ,_sage_const_0 ,'a^2',_sage_const_1 ,'a^4','a^14','a^9','a^4','a^12'],
['a^8','a^9','a^2','a','a^14','a^9','a^10','a^14','a^8','a'],
[_sage_const_1 ,'a^2',_sage_const_1 ,'a^14','a^9','a^4','a^14','a^8','a','a^5'],
[_sage_const_0 ,_sage_const_1 ,'a^4','a^9','a^4','a^12','a^8','a','a^5',_sage_const_0 ],
['a^9','a','a^14','a^10','a^14','a^8','a^2','a^3','a^2','a^14'],
['a^2','a^14','a^9','a^14','a^8','a','a^3','a^2','a^14','a^7'],
[_sage_const_1 ,'a^9','a^4','a^8','a','a^5','a^2','a^14','a^7','a^2'],
['a^4','a^4','a^12','a','a^5',_sage_const_0 ,'a^14','a^7','a^2','a^9']])
print("det(A)=",det(A))
print("rank=",rank(A))

#z=var('z0,z1,z2,z3,z4,z5,z6,z7,z8,z9')
X = PolynomialRing(GF(_sage_const_16 ,'a'),_sage_const_10 ,"z")
z=X.gens()
G=GF(_sage_const_16 ,'a')
zz=vector([z[_sage_const_0 ],z[_sage_const_1 ],z[_sage_const_2 ],z[_sage_const_3 ],z[_sage_const_4 ],z[_sage_const_5 ],z[_sage_const_6 ],z[_sage_const_7 ],z[_sage_const_8 ],z[_sage_const_9 ]])
f=A*zz
print(f)

#z0,z1,z2,z3,z4,z5,z6,z7,z8,z9=var('z0,z1,z2,z3,z4,z5,z6,z7,z8,z9')

#ff=[f[0]==G('a'),f[1]==G('a^2'),f[2]==G('a^3'),f[3]==G('a^5'),f[4]==G('a^7'),f[5]==0,f[6]==1,f[7]==0,f[8]==G('a^8'),f[9]==0]
ff=[f[_sage_const_0 ]==_sage_const_0 ,f[_sage_const_1 ]==_sage_const_0 ,f[_sage_const_2 ]==_sage_const_0 ,f[_sage_const_3 ]==_sage_const_0 ,f[_sage_const_4 ]==_sage_const_0 ,f[_sage_const_5 ]==_sage_const_0 ,f[_sage_const_6 ]==_sage_const_0 ,f[_sage_const_7 ]==_sage_const_0 ,f[_sage_const_8 ]==_sage_const_0 ,f[_sage_const_9 ]==_sage_const_0 ]
print(solve(ff==_sage_const_0 ,zz))
#z[0],z[1],z[2],z[3],z[4],z[5],z[6],z[7],z[8],z[9]))



