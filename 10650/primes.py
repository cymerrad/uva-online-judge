import math
import numpy as np
import json

primes = np.empty(3433, dtype=int)
primes[0] = 2
cur_ind = 1
last_cut_prime = 2
last_cut_ind = 0

for n in range(3, 32000, 2):
    top = math.floor(math.sqrt(n))
    if top > last_cut_prime:
        for q in primes[last_cut_ind+1:]:
            last_cut_ind += 1
            if q >= top:
                last_cut_prime = q
                break
        else:
            raise Exception("We should never run out of primes")

    for p in primes[1:last_cut_ind+1]:
        if n % p == 0:
            break
    else:
        primes[cur_ind] = n
        cur_ind += 1

primes = primes[1:cur_ind]  # exclude 2 and the tail


last_checked_val = math.inf
last_checked_ind = math.inf
last_checked_res = False


def reset_cache():
    global last_checked_val
    global last_checked_ind
    global last_checked_res
    last_checked_val = math.inf
    last_checked_ind = math.inf
    last_checked_res = False


def is_in(arr_sorted, el) -> bool:
    global last_checked_val
    global last_checked_ind
    global last_checked_res

    if el > last_checked_val:
        # cache can help with this
        last_checked_ind, last_checked_res = find_in(
            arr_sorted, el, left=last_checked_ind)
    else:
        last_checked_ind, last_checked_res = find_in(arr_sorted, el)

        last_checked_val = el

    return last_checked_res


def find_in(arr_sorted, el, left=0, right=None) -> (int, bool):
    length = len(arr_sorted)
    l = left
    r = length - 1 if right is None else right
    pivot = (r+l)//2
    while l < pivot < r:
        if el < arr_sorted[pivot]:
            r = pivot
        elif el > arr_sorted[pivot]:
            l = pivot
        else:
            break
        pivot = (r+l)//2

    if arr_sorted[pivot] == el:
        return (pivot, True)
    if arr_sorted[l] == el:
        return (l, True)
    if arr_sorted[r] == el:
        return (r, True)

    return (left, False)


arr = np.array([2,  3,  5,  7, 11, 13, 17, 19])
for i, el in enumerate(arr):
    assert is_in(arr, el), f"{i}, {el}"

highest_p = primes[-1]
highest_gap = (primes[-1] - primes[0])//2
gap = highest_gap
milestone = (highest_gap//2)
milestone = milestone if milestone % 2 == 0 else milestone - 1
pairs_of_gap = dict()
while gap:
    # break # UNDO
    temp = dict()
    for p in primes:
        nxt = p + gap
        if nxt > highest_p:
            break
        if is_in(primes, nxt):
            temp[p] = nxt
    if len(temp):
        pairs_of_gap[gap] = temp

    gap -= 2
    reset_cache()
    if gap == milestone:
        print(f"Gap size: {gap} ...")
        milestone = (milestone//2)
        milestone = milestone if milestone % 2 == 0 else milestone - 1


chains = dict()
for gap in pairs_of_gap.keys():
    t_chains = []
    pairs = pairs_of_gap[gap].items()

    t_chain = [0, 0]
    for pair in pairs:
        if t_chain[-1] == pair[0]:
            t_chain.append(pair[1])
        else:
            if len(t_chain) > 2:
                t_chains.append(t_chain)
            t_chain = list(pair)

    if len(t_chains) > 0:
        chains[gap] = t_chains

with open("chains.json", "w") as fw:
    def convert(o):
        if isinstance(o, np.int64):
            return int(o)
        raise TypeError

    chainz = dict((str(k), v) for k, v in chains.items())
    json.dump(chainz, fw, default=convert)

longest = 0
for chz in chains.values():
    longest = max(longest, max(len(ch) for ch in chz))
print(f"Longest chains has {longest} elements.")
# for known input it's 5

chains_by_len = {
    3: dict(),
    4: dict(),
    5: dict(),
}

for gap, chz in chains.items():
    for ch in chz:
        try:
            chains_by_len[len(ch)][gap].append(ch[0])
        except KeyError:
            chains_by_len[len(ch)][gap] = []
            chains_by_len[len(ch)][gap].append(ch[0])

with open("chains_compacted.json", "w") as fw:
    chainzzzwtf = dict((str(k), dict((str(kk), vv) for kk,vv in v.items())) for k, v in chains_by_len.items())
    json.dump(chainzzzwtf, fw, default=convert)

print("{}\n{}\n{}\n".format(*[list(chains_by_len[k].keys()) for k in [3,4,5]]))