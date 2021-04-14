#include "Settings_handler.h"

#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

map<string, int> Settings_handler::get_settings()
{
    map<string, int> tmp;

    for (pair<string, Setting> s : settings)
    {
        tmp.insert({s.first, s.second.value});
    }

    return tmp;
}

int Settings_handler::get_setting(string const& setting)
{
    if (settings.size() == 0)
    {
        load();
    }

    if (settings.find(setting) == settings.end())
    {
        cerr << "No setting with name '" << setting << "' exists! Returning -1" << endl;
        return -1;
    }

    return settings.at(setting).value;
}

void Settings_handler::inc_setting(std::string const& setting)
{
    if (settings.find(setting) == settings.end())
    {
        cerr << "No setting with name '" << setting << "' exists!" << endl;
    }
    else
    {
        Setting s = settings.at(setting);
        if (s.value + s.step <= s.max)
        {   
            settings.at(setting).value += s.step;
        }
    }
}

void Settings_handler::dec_setting(std::string const& setting)
{
    if (settings.find(setting) == settings.end())
    {
        cerr << "No setting with name '" << setting << "' exists!" << endl;
    }
    else
    {
        Setting s = settings.at(setting);
        if (s.value - s.step >= s.min)
        {   
            settings.at(setting).value -= s.step;
        }
    }
}

void Settings_handler::load_default()
{
    settings = {
        {"Window height", Setting{768, 0, 0, 9999}},
        {"Window width", Setting{1600, 0, 0, 9999}},
        {"Worm segments", Setting{25, 10, 0, 9999}},
        {"Worm width", Setting{20, 1, 0, 9999}},
        {"Worm velocity", Setting{20, 5, 0, 9999}},
        {"Ball size", Setting{45, 5, 0, 9999}},
        {"Ball velocity", Setting{15, 5, 0, 9999}},
        {"Goals to win", Setting{5, 1, 0, 9999}},
        {"Food size", Setting{35, 1, 0, 9999}},
        {"Food spawnrate", Setting{1, 1, 0, 9999}},
        {"Maximum amount of food", Setting{10, 1, 0, 9999}},
        {"Extra length per eaten food", Setting{10, 5, 0, 9999}},
        {"Segment decay time", Setting{500, 50, 0, 9999}},
        {"Powerup food boost duration", Setting{5, 1, 0, 9999}},
    };
}

void Settings_handler::write()
{
    ofstream ofs{"settings.txt", ios::out};
    for (pair<string, Setting> s : settings) 
    {
        ofs << s.first << ":" << s.second.value << endl;
    }
}

pair<string, int> Settings_handler::parse_line(string line) 
{
    string option;
    int value;

    auto it = find(line.begin(), line.end(), ':');

    if (it == line.end())
    {
        pair<string, int> setting{"INVALID LINE", -1};
        return setting;
    }

    copy(line.begin(), it, back_inserter(option));
    line.erase(line.begin(), ++it);
    value = stoi(line);

    pair<string, int> setting{option, value};
    return setting;
}

void Settings_handler::load()
{
    load_default();  
    ifstream ifs{"settings.txt", ios::in};

    if (!ifs) 
    {
        cerr << "Couldn't find 'settings.txt'. Using default settings." << endl;
    } 
    else 
    {
        string line;
        while (getline(ifs, line)) 
        {
            pair<string, int> setting = parse_line(line);

            if (setting.first == "INVALID LINE")
            {
                cerr << "found an invalid line in settings file, Using default settings." << endl;
                break;
            }
            else
            {
                settings.at(setting.first).value = setting.second;
            }
        }
    }
}