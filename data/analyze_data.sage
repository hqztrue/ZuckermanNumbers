
import os

def TheoreticalExponent(b):
    p = max(prime_factors(b))
    s = 0
    for d in range(1, b):
        if not p.divides(d):
            s += 1/d
    return log(s) / log(b)

# Return x in the format '0.xxx' (if x < 1) or 'x.xx \cdot 10^-e'
# (if x < 0.1)
def truncate(x):
    e = 0
    while 10^(e+1)*x < 1:
        e += 1
    if e == 0:
        return str(N(x, digits=20))[:5] + "\dots"
    return str(N(x * 10^(e+1), digits=20))[:5] + r"\ldots \mbox{\tiny$\times$} 10^{%d}" % -(e+1)

Z = dict()
for b in range(3,12+1):
    file_name = "Zuckerman%d.output" % b
    if os.path.isfile(file_name):
        file_input = open(file_name, "r")
        Z[b] = []
        for l in file_input.readlines():
            if l.startswith("Loading") or l.startswith(" "):
                continue
            Z[b].append(int(l.split()[1]))

print("**************************************************************")
print("Print data as Python arrays")
print("**************************************************************\n")
for b in Z:
    print("base =", b)
    print(Z[b])
    print("\n")

print("**************************************************************")
print("Test heuristic")
print("**************************************************************\n")

for b in Z:
    print("base =", b)
    print("n \t Z \t error")
    print("--------------------------------------------------------------")
    for n, z in enumerate(Z[b],start=1):
        theo_exp = TheoreticalExponent(b)
        error = N(abs(log(z) / (n*log(b)) - theo_exp) / theo_exp)
        print(n, "\t", z, "\t", error)
    print("--------------------------------------------------------------\n")

print("**************************************************************")
print("LaTeX Table of Errors")
print("**************************************************************\n")

print(r"""\begin{table}[h!]
    \centering
    \begin{tabular}{rrrrrr}
    \toprule
    $b$ & $n$ & $Z_{b,n}$ & $\widetilde{z}_{b,n}$ & $z_b$ & error \\
    \midrule""")

for b in Z:
    n = len(Z[b])
    Zbn = Z[b][n-1]
    zbn = log(Zbn) / (n*log(b))
    zb = TheoreticalExponent(b)
    error = abs(zbn - zb) / zb
    print(r"    $%d$ & $%d$ & $%d$ & $%s$ & $%s$ & $%s$ \\" % (b, n, Zbn, truncate(zbn), truncate(zb), truncate(error)))
    
print(r"""\bottomrule
\end{tabular}
\caption{Here $\widetilde{z}_{b,n} := \log(z_{b,n}) / \log(b^n)$ and error is equal to $|\widetilde{z}_{b,n} - z_b| / z_b$.}
\label{tab:errors}
\end{table}""")
