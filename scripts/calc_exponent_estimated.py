import math
import numpy as np
import scipy.optimize
from scipy.optimize import fsolve

idx=[1,2,3,4,6,7,8,9]
m=len(idx)

def lg(x):
    if x>0: return np.log(x)/np.log(10)
    else: return -10

def f(x):
    return np.sum([t*lg(t) for t in x])+np.sum([x[i]*lg(idx[i]) for i in range(m)])

x0=[1/m for i in range(m)]
cons=({
        'type':'eq',
        'fun': lambda x: np.sum(x)-1
     })
x=scipy.optimize.minimize(f,x0,constraints=cons)
v=-x['fun']
print(x['x'])
base=sum(1/i for i in idx)
#print([1/t/base for t in idx])
print(v)
#print(lg(base))
#print(-np.sum([t*lg(t) for t in x['x']]),np.sum([x['x'][i]*lg(idx[i]) for i in range(m)]))
