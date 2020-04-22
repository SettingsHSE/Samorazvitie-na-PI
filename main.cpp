#include <iostream>

int Wagner_Fischer(std::string& s, std::string& t, int mistakes)
{
    int s_size = s.size() + 1;
    int t_size = t.size() + 1;

    if (std::abs(s_size - t_size) > mistakes)
        return t_size - 1;

    int *lastRow = new int[t_size];
    int *curRow = new int[t_size];
    bool checkRow;

    for (int i = 0; i < t_size; i++)
    {
        lastRow[i] = i;
        curRow[i] = t_size - 1;
    }

    int result = 0;

    for (int i = 1; i < s_size; i++) {
        checkRow = false;
        curRow[0] = i;

        for (int j = std::max(1, i - mistakes); j < std::min(t_size , i + mistakes + 1); j++)
        {
            curRow[j] = std::min(std::min((lastRow[j] + 1), (curRow[j - 1] + 1)), (lastRow[j - 1] + (s[i - 1] == t[j - 1] ? 0 : 1)));
            if (curRow[j] <= mistakes)
                checkRow = true;
        }

        if (!checkRow)
        {
            result = s_size - 1;
            break;
        }

        for (int k = 0; k < t_size; k++)
        {
            std::swap(curRow[k], lastRow[k]);
            curRow[k] = t_size - 1;
        }
    }

    if (result != s_size - 1)
    {
        result = lastRow[t_size - 1];
    }

    delete[] lastRow;
    delete[] curRow;

    return result;
}

int checkCommands(std::string *commands, int mistakes, std::string curString, int commandsNumber)
{
    int result = 0;
    for (int i = 0; i < commandsNumber; i++)
    {
        if ( Wagner_Fischer(curString, commands[i], mistakes) <= mistakes)
            result++;
    }
    return result;

}

int main()
{
    int N, // number of commands
            D, // max number of mistakes
            K; // number of user's commands

    std::cin >> N;

    auto *commands = new std::string[N];
    std::string cur_string;

    for (int i = 0; i < N; i++)
    {
        std::cin >> cur_string;
        commands[i] = cur_string;
    }

    std::cin >> D;
    std::cin >> K;

    for (int i = 0; i < K; i++)
    {
        std::cin >> cur_string;
        std::cout << checkCommands(commands, D, cur_string, N) << "\n";
    }

    delete[] commands;
    return 0;
}