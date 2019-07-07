/*
    This redefines cin as a stream reading from input.txt file.
    Why? because you can't define in VSCode a debugging task
    with file being fed on stdin.
*/
#ifdef DEBUG
std::ifstream cin;
try
{
    cin.open("input.txt");
}
catch (const std::exception &e)
{
    std::cerr << e.what() << '\n';
    cin.close();
    return 1;
}
#endif