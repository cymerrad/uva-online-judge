#!/usr/bin/python
import sys

LINE_LIMIT = 80
SOFTENING = 10
SOFT_LINE_LIMIT = LINE_LIMIT - SOFTENING


def fix_line(line):
    fixed_lines = []
    end_of_prev_line = 0
    last_comma = 0

    # this is not guaranteed to work
    # for example the line might be very long and without any commas,
    # where we could break the line
    for ind, char in enumerate(line):
        if char == ',':
            if (ind - end_of_prev_line) > SOFT_LINE_LIMIT:
                fixed_lines.append(line[end_of_prev_line:last_comma] + "\\\n")
                end_of_prev_line = last_comma

            last_comma = ind + 1  # include the comma

    fixed_lines.append(line[end_of_prev_line:])
    return fixed_lines


if __name__ == "__main__":
    filename = sys.argv[1]
    with open(filename, "r") as fr:
        with open(filename + ".fixed", "w") as fw:
            for line in fr:
                if len(line) > LINE_LIMIT:
                    for fixed_line in fix_line(line):
                        fw.write(fixed_line)
                else:
                    fw.write(line)
