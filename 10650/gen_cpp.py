import json

unordered_map_template = '''unordered_map<int, vector<int>> len{chain_len}Chains = {{
{tuples}
}};
{map_keys}
'''
int_arr_template = '{{{key}, {{{comma_sep_els}}}}}'
int_arr_keys = 'vector<int> len{chain_len}Keys = {{{els}}};'

with open("chains_compacted.json", "r") as fr:
    chains = json.load(fr)

with open("gen.cpp", "w") as fw:
    per_gap = [unordered_map_template.format(
        chain_len=chain_len,
        map_keys=int_arr_keys.format(
            chain_len=chain_len,
            els=", ".join(x for x in d_chains.keys())
        ),
        tuples=",\n".join(
            int_arr_template.format(
                key=gap_size,
                comma_sep_els=", ".join(str(x) for x in chain_starts)
            ) for gap_size, chain_starts in d_chains.items()
        )
    ) for chain_len, d_chains in chains.items()]
    fw.writelines(per_gap)
