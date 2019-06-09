def show_steps(m, n):
    cur = 1
    steps_left = [x+1 for x in range(1, n)]
    steps_took = [1]
    while len(steps_left) > 1:
        m_m = (m-1) % len(steps_left)
        cur = steps_left[m_m]
        steps_took.append(cur)
        steps_left = steps_left[m_m+1:] + steps_left[:m_m]

    steps_took = steps_took + steps_left
    return steps_took


solutions = []
for i in range(2, 14):
    solutions.append(show_steps(i, 8))

print(solutions)

print('\n')
