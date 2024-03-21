import math,random
import numpy as np
import scipy.optimize
from scipy.optimize import fsolve

eps=1e-10
idx=[1,2,3,4,6,7,8,9]
m=len(idx)

def lg(x):
    if x<eps: x=eps
    return np.log(x)/np.log(10)

def h(t):
    return (1-t)*lg(8)

def f(x):
    r=np.sum(x)
    return 0.5*r*np.sum([x[i]/r*lg(x[i]/r) for i in range(m)])

opt=0.37937096
opt_thres=opt/lg(8)/(1/lg(2)-1)

#x0=[1./8,1./8,1./8,1./8,1./8,1./8,1./8,1./8]
x0=[random.random()/8 for i in range(m)]
x0[-1]=1-sum(x0[:-1])

def F(T,flag=False):
    t=T[0]
    def pow2_eq(x):
        r=np.minimum((x[1]+2*x[3]+x[4]+3*x[6])*lg(2),opt_thres)
        s=1-sum(x)
        return s-r
    
    cons=(
        {
            'type':'ineq',
            'fun': lambda x: 1-np.sum(x)
        },
        {
            'type':'ineq',
            'fun': lambda x: t-np.sum([x[i]*lg(idx[i]) for i in range(m)])
        },
        {
            'type':'eq',
            'fun': pow2_eq
        }
    )

    bnds=[(0,1) for i in range(m)]
    res=scipy.optimize.minimize(f,x0,constraints=cons,bounds=bnds)
    x=res['x']
    v=-f(x) #v=-res['fun']
    if flag:
        print(x)
        print('v=',v,'h=',h(t))
        print('M=',np.sum([x[i]*lg(idx[i]) for i in range(m)]))
        r=(x[1]+2*x[3]+x[4]+3*x[6])*lg(2)
        print('r=',r,'s=',1-sum(x))
    return h(t)-v

t0=[0.5]
while True:
    t=fsolve(F,t0)[0]
    if F([t])<1e-8: break
print('t=%.8f exponent=%.8f'%(t,h(t)))
F([t],flag=True)
