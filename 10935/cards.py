import io
import math

cards = list(range(1, 20))


def throw(cards, buff):
    n = len(cards)
    if n == 1:
        print(cards[0], file=buff)
        return buff
    deck = []
    for i, c in enumerate(cards):
        if i % 2 == 0:
            print(c, end=" ", file=buff)
        else:
            deck.append(c)

    if n % 2 == 1:
        deck = deck[1:] + [deck[0]]
    print("", file=buff)

    return throw(deck, buff)


def shift(k, by, mod):
    if 1 <= k + by <= mod:
        return k + by
    else:
        return (k + by) % mod + 1


def generateThrows(n: int, stringBuilder: io.StringIO):

    # failed attempt
    def _print(*values, **kwargs):
        print(*values, file=stringBuilder, **kwargs)

    shift_by = 0
    for scale in range(1, 1 + math.floor(math.log2(n))):
        for i in range(n):
            c = i + 1  # PLUS SOME FUCKING MAGIC
            if i % 2 == 0:
                _print(c, end=" ")

        if n % 2 == 1:
            shift_by += 1
            pass

        n = n//2
        _print("")


with (io.StringIO()) as stringBuilder:
    throw(cards, stringBuilder)
    stringBuilder.seek(0)
    result = stringBuilder.read()

with io.StringIO() as stringBuilder:
    generateThrows(len(cards), stringBuilder)
    stringBuilder.seek(0)
    result2 = stringBuilder.read()


# assert result == result2
print(result2)
