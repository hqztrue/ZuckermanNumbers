
from sage.graphs.graph_coloring import all_graph_colorings


def zeta(D, s):
    return sum(d^-s for d in D)

def zeta1(D, s):
    return -sum(log(d)*d^-s for d in D)
    
def F(b, D, s):
    return log(zeta(D,s)*b^s) / log(len(D)*b^s)

def G(b, D, s):
    return log(zeta(D,s)/len(D)) - (log(len(D))/log(b) + s) * zeta1(D,s)/zeta(D,s)

def minimize_F(b, D):
    eps = 10^-4
    min_s = 0
    max_s = 10
    while G(b, D, max_s) > 0:
        max_s *= 2
    for i in range(0, 100):
        s = (min_s + max_s) / 2
        if G(b, D, s) > eps:
            min_s, s = s, (s + max_s) / 2
        elif G(b, D, s) < -eps:
            max_s, s = s, (min_s + s) / 2
        else:
            break
    return s, F(b, D, s)


def check_subset(b, D):
    for d1 in D:
        for d2 in D:
            if d1 != d2 and (d1*d2) % b == 0:
                return False
    return True
                        
def Omega(b):
    L = []
    for D in Subsets(range(1, b)):
        if check_subset(b,D):
            L.append(D)
    O = []
    for l1 in L:
        f = True
        for l2 in L:
            if l1 != l2 and l1.issubset(l2):
                f = False
                break
        if f:
            O.append(l1)
    return O


print("b \t eta_b \n------------------")    
for b in range(3, 20+1):
    eta_b = 0
    for D in Omega(b):
        s, min_F = minimize_F(b, D)
        eta_b = max(eta_b, N((log(len(D))/log(b))*min_F))
    print(b, "\t", eta_b)
