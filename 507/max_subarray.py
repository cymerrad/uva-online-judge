def max_subarray(row):

    largest_ending_here = 0

    best_start = this_start = end = best_so_far = 0

    for i, x in enumerate(row):

        largest_ending_here += x

        best_so_far = max(best_so_far, largest_ending_here)

        if largest_ending_here <= 0:

            this_start = i + 1

            largest_ending_here = 0

        elif largest_ending_here == best_so_far:

            best_start = this_start

            end = i + 1  # the +1 is to have 'end' be exclusive

    return best_so_far, best_start, end


array = [4, -5, 4, -3, 4, 4, -4, 4, -5]
print(max_subarray(array))
print(max_subarray([-1, -1, -1]))
