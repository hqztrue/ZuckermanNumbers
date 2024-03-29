
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

def zeta(D, s):
    return sum(d^-s for d in D)

def zeta1(D, s):
    return -sum(log(d)*d^-s for d in D)

def Omega(b):
    O = []
    for p in prime_factors(b):
        D = []
        for d in range(1, b):
            if not p.divides(d):
                D.append(d)
        O.append(D)
    return O

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

def F(b, D, v, s):
    return log(zeta(D, s) * b^s) / (log(len(D)^v * b^s))

def G(b, D, v, s):
    return (s + v*log(len(D))/log(b))*zeta1(D, s)/zeta(D, s) - log(zeta(D, s)/len(D)^v)

def F1(b, D, v, s):
    return G(b, D, v, s) * log(b)/(log(len(D)^v * b^s))^2

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

def min_F(b, D, v):

    # Note: F(s) has derivative
    # F'(s) = G(s)*log(b)/(log(len(D)^v * b^s))^2
    # where G is monotone increasing.
    # Therefore, by the mean value theorem, we have that
    # |F(s) - F(s0)| <= |(s - s0)*G(s_max)*log(b)/(log(len(D)^v * b^s_min))^2|
    # for all s_min <= s, s0 <= s_max.

    s_min = 0
    s_max = 1
    eps = 10^-8
    
    while G(b, D, v, s_max) <= 0:
        s_max *= 2

    while True:
        s = (s_min + s_max) / 2
        
        if G(b, D, v, s) > 0:
            s_max = s
        else:
            s_min = s

        if abs((s_max - s_min) * G(b, D, v, s_max) * log(b)/(log(len(D)^v * b^s_min))^2) < eps:
            break

    return F(b, D, v, s)

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

def UpperBoundExponent(b):
    return max((log(len(D))/log(b))*min_F(b, D, 1) for D in Omega(b))

# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #

print("b \t z_b^+ \n------------------")    
for b in range(3, 20+1):
    print(b, "\t", N(UpperBoundExponent(b)))
