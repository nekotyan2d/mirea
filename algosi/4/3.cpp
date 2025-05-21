#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Проверяет, является ли prefix префиксом строки word
bool isPrefix(const string &prefix, const string &word)
{
    if (prefix.size() > word.size())
        return false;
    return word.compare(0, prefix.size(), prefix) == 0;
}

int main()
{
    vector<string> words;
    string s;

    cout << "words:" << endl;

    while (getline(cin, s) && !s.empty())
    {
        words.push_back(s);
    }

    string result;
    int maxCount = -1;

    for (const auto &word : words)
    {
        int count = 0;
        for (const auto &prefix : words)
        {
            if (isPrefix(prefix, word))
            {
                count++;
            }
        }
        if (count > maxCount)
        {
            maxCount = count;
            result = word;
        }
    }

    cout << result << " (Prefixes:";
    for (const auto &prefix : words)
    {
        if (isPrefix(prefix, result))
        {
            cout << " " << prefix;
        }
    }
    cout << ")" << endl;

    return 0;
}