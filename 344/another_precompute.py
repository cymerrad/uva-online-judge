from collections import Counter, OrderedDict
from functools import reduce

anums = [1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1]
rnums = "M CM D CD C XC L XL X IX V IV I".split()

def int2roman(x):
    ret = []
    for a,r in zip(anums, rnums):
        n,x = divmod(x,a)
        ret.append(r*n)
    return ''.join(ret)

zeroCount = Counter({'I': 0, 'V': 0, 'X': 0, 'L': 0, 'C': 0})
pad = len(zeroCount.keys())

romans = [int2roman(k) for k in range(1,101)]
counted = [Counter(r) for r in romans]
summed = reduce(lambda aggr, d: aggr + [aggr[-1] + d], counted, [zeroCount])
packed = [tuple(d.values()) + tuple([0] * (pad - len(d.values()))) for d in summed]

cpp_arr_template = '''
using romansCount = tuple<unsigned char,unsigned char,unsigned char,unsigned char,unsigned char>;
romansCount precomputed[] = {{
{}
}};
'''
cpp_el_template = "\t{{{}}},"


print(cpp_arr_template.format("\n".join([cpp_el_template.format(",".join(str(n) for n in tup)) for tup in packed])))
