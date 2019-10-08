import sys
from queue import Queue
from collections import defaultdict


class LowerBoundedList(list):
    def __getitem__(self, index):
        if index < 0:
            # with  or index >= self.__len__() it would be fully bounded
            raise IndexError("list index out of range")
        return super(LowerBoundedList, self).__getitem__(index)


MAX_SIZE = 25
ACCEPTED = "good\n"
REJECTED = "wrong\n"

grid = LowerBoundedList([LowerBoundedList([0]*MAX_SIZE)
                         for x in range(MAX_SIZE)])


def paired(iterable):
    return zip(*[iter(iterable)]*2)


def zeroGrid(size):
    for i in range(size):
        for j in range(size):
            grid[i][j] = [size, False, (i, j)]


def get_neighbors(x, y, size):
    neighs = []
    for x_, y_ in [(x-1, y), (x+1, y), (x, y-1), (x, y+1)]:
        if x_ == size or y_ == size:
            continue
        try:
            neighs.append(grid[x_][y_])
        except IndexError:
            continue

    return neighs


def find_example_of_last(size):
    for i in range(size):
        for j in range(size):
            if grid[i][j][0] == size:
                return grid[i][j]


def is_equi(size, examples):
    "analyzing filled out grid and knowing the instance size"
    color_queues = defaultdict(Queue)

    for ex in examples.values():
        found = 0
        cur = ex
        cur_color = cur[0]
        color_queues[cur_color].put(cur)

        while not color_queues[cur_color].empty():
            cur = color_queues[cur_color].get()
            found += 1
            neighs = get_neighbors(*cur[2], size)
            cur[1] = True  # visited
            for n in neighs:
                if n[0] is cur_color:
                    if n[1] is False:
                        # same color and unvisited
                        color_queues[cur_color].put(n)

        if found != size:
            return False

    return True


if __name__ == "__main__":
    n = int(sys.stdin.readline())

    while n > 0:
        good = True

        zeroGrid(n)

        examples = {}

        for col in range(1, n):  # n-1 rows in input
            line = sys.stdin.readline().strip().split(' ')
            if not good:
                # read but ignore
                continue

            grouped = set([(int(x) - 1, int(y) - 1) for x, y in paired(line)])
            if len(grouped) != n:
                good = False
                continue

            for x, y in grouped:
                grid[x][y] = [col, False, (x, y)]  # cur_color / visited / xy

            ex = grouped.pop()
            examples[col] = grid[ex[0]][ex[1]]

        if not good:
            sys.stdout.write(REJECTED)
        else:
            ex = find_example_of_last(n)
            examples[n] = ex

            is_it = is_equi(n, examples)
            if is_it:
                sys.stdout.write(ACCEPTED)
            else:
                sys.stdout.write(REJECTED)

        n = int(sys.stdin.readline())

    exit(0)
