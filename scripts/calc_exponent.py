import math
import numpy as np
import scipy.optimize
from scipy.optimize import fsolve

def F(T):
    t=T[0]
    def lg(x):
        return np.log(x)/np.log(10)

    def f(x):
        return [-lg(x[1])-1+x[5]+x[0]*lg(1),
                -lg(x[2])-1+x[5]+x[0]*lg(2),
                -lg(x[3])-1+x[5]+x[0]*lg(3),
                -lg(x[4])-1+x[5]+x[0]*lg(4),
                -lg(x[6])-1+x[5]+x[0]*lg(6),
                -lg(x[7])-1+x[5]+x[0]*lg(7),
                -lg(x[8])-1+x[5]+x[0]*lg(8),
                -lg(x[9])-1+x[5]+x[0]*lg(9),
                x[1]+x[2]+x[3]+x[4]+x[6]+x[7]+x[8]+x[9]-1,
                x[1]*lg(1)+x[2]*lg(2)+x[3]*lg(3)+x[4]*lg(4)+x[6]*lg(6)+x[7]*lg(7)+x[8]*lg(8)+x[9]*lg(9)-t]

    def g(x):
        return -0.5*(x[1]*lg(x[1])+x[2]*lg(x[2])+x[3]*lg(x[3])+x[4]*lg(x[4])+x[6]*lg(x[6])+x[7]*lg(x[7])+x[8]*lg(x[8])+x[9]*lg(x[9]))

    def h(x):
        return (1-t)*lg(8)

    x0=[1,1./8,1./8,1./8,1./8,1,1./8,1./8,1./8,1./8]
    #print('f=',f(x0))
    x=fsolve(f,x0)
    #print('x=',x)
    #print(f(x))
    #print('t=',t,'v=',h(t),'g=',g(x))
    #np.isclose(f(x),[0]*10)
    return h(t)-g(x)

t1=0.608
#t1=0.51094641
#F([t1]); exit(0)

t0=[0.5]
t=fsolve(F,t0)[0]
print('t=',t,(1-t)*np.log(8)/np.log(10))
