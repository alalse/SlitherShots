#include "Settings_handler.h"

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

Settings_handler::Settings_handler(string file)
: file{file} {}

pair<string, int> Settings_handler::parse_line(string line)
{
    string option;
    int value;

    auto it = find(line.begin(), line.end(), ':');
    copy(line.begin(), it, back_inserter(option));
    line.erase(line.begin(), ++it);
    value = stoi(line);

    pair<string, int> setting{option, value};
    return setting;
}

map<string, int> Settings_handler::load()
{
    map<string, int> settings;
    ifstream ifs{file, ios::in};

    if (!ifs)
    {
        std::cerr << "Couldn't find 'settings.txt'. Reading default template." << std::endl;
        Settings_handler sh{"template_settings.txt"};
        settings = sh.load();
    }
    else
    {
        string line;
        while (getline(ifs, line))
        {
            settings.insert(parse_line(line)); 
        }
    }

    return settings;
}

void Settings_handler::write(map<string, int> settings)
{
    ofstream ofs{file, ios::out};
    
    for (pair<string, int> s : settings)
    {
        ofs << s.first << ":" << s.second << endl;
    }
}