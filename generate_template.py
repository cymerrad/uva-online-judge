#!/usr/bin/python3
import os
import sys
import requests as r
import bs4  # BeautifulSoup4
import re
from pathlib import Path
import git  # GitPython

# example input:
# https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=697

TEMPLATE = '''#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char const *argv[])
{

#ifdef DEBUG
	ifstream cin;
	try
	{
		cin.open("input.txt");
	}
	catch (const std::exception &e)
	{
		std::cerr << e.what() << std::endl;
		cin.close();
		return 1;
	}
#endif
    int numOfCases;
    cin >> numOfCases;

    // code your solution

	return 0;
}
'''

title_re = re.compile(r'(\d+)\s*-\s*((\S+ )*\S+)')


def parse_soup_for_task(soup: bs4.BeautifulSoup) -> dict:
    # for some stupid reason the only place where the number and name appear
    # is some imaginary table above the problem pdf description
    tables = soup.find_all('table')
    for tb in tables:
        found = title_re.findall(tb.text)
        if found:
            number, name, _ = found[0]
            return {
                'number': number,
                'name': name,
            }
    else:
        raise Exception("Task data not found")


allowed_chars_range = [45, 46] + \
    list(range(48, 58)) + [95] + list(range(97, 123))
allowed_chars = "".join([chr(x) for x in allowed_chars_range])


def task_name_to_filename(name: str) -> str:
    return "".join([x for x in name.lower().replace(" ", "-") if x in allowed_chars])


if __name__ == "__main__":
    addr = sys.argv[1]

    git_commit = False if "--no-git" in sys.argv[1:] else True

    # visit the page
    page = r.get(addr)
    soup = bs4.BeautifulSoup(page.content, features="lxml")

    # get the task name
    # get the task number
    task = parse_soup_for_task(soup)

    # generate directory with task number
    new_dir = Path(task['number'])
    new_dir.mkdir()

    # generate file with task name
    filename = task_name_to_filename(task['name']) + ".cpp"
    main_file = new_dir / filename
    with main_file.open("w") as fw:
        fw.write(TEMPLATE)

    # TODO: get example input from uDebug API https://www.udebug.com/API/#/
    input_file = new_dir / "input.txt"
    input_file.touch()

    output_file = new_dir / "output.txt"
    output_file.touch()

    files = [main_file, input_file, output_file]

    if git_commit:
        # git commit with task name
        root_dir = Path(".")  # TODO: be smarter about this?
        repo = git.Repo(root_dir.as_posix())
        repo.index.add(map(lambda pth: pth.as_posix(), files))
        repo.index.commit(task['name'])

        print(
            f"Added {[x.relative_to(root_dir).as_posix() for x in files]} to git.")
        print("Squash future work into this commit:")
        print("git add . ; git commit --amend --no-edit")
