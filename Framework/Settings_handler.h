/**
 * \class Settings_handler
 * \brief Handles input and output to the external settings file.
 *
 * This class handles input and output to the external settings
 * file and parses the file's content into workable data.
 */

#pragma once

#include <map>

class Settings_handler
{
    public:
    /** \brief Gets a map containing all game settings.
      * \return Map of <string, int> pairs.
      * 
      * Gets and returns the entire settings map.
      **/
    static std::map<std::string, int> get_settings();

    /** \brief Gets the value of the setting with name 'setting'.
      * \param Name of setting as a string.
      * \return Integer value of setting.
      * 
      * Gets the value of inputed setting. If the setting does
      * not exist return -1. If the internal settings are empty
      * they first get loaded from settings.txt.
      **/
    static int get_setting(std::string const& setting);

    /** \brief Sets the internal value of the setting with name 'setting' to 
      * the value 'value'.
      * \param Name of setting to change as a string and new value as int.
      * 
      * Sets the value of inputed setting to the inputed value. If the setting 
      * does not exist no changes are made to the internal settings. If the 
      * internal settings are empty they first get loaded from settings.txt
      **/
    //static void set_setting(std::string const& setting, int value);

    /** \brief Increments the value of the setting 'setting'.
      * \param Name of a setting as a string.
      * 
      * Increments the value of the setting with the provided name with
      * an internal number.
      **/
    static void inc_setting(std::string const& setting);

    /** \brief Decrements the value of the setting 'setting'.
      * \param Name of a setting as a string.
      * 
      * Decrements the value of the setting with the provided name with
      * an internal number.
      **/
    static void dec_setting(std::string const& setting);

    /** \brief Loads the default settings map.
      * 
      * Loads the default hardcoded settings map to the Scope handler's
      * internal settings map.
      **/
    static void load_default();

    /** \brief Writes to 'settings.txt'.
      * 
      * Opens 'settings.txt' and overwrites all stored settings 
      * with Scope_handler's internally stored settings.
      **/
    static void write();

    private:
    ///Struct containing all data associated with a specific setting. Used in the settings map.
    struct Setting
    {
      int value;
      int step;
      int min;
      int max;
    };    

    ///Settings parsed from the settings file
    inline static std::map<std::string, Setting> settings{};

    /** \brief Parses an inputed string for a setting and value pair.
      * \param A string to parse.
      * \return Returns a std::pair<std::string, int> containing the 
      * parsed setting and its value.
      * 
      * Finds a setting and value pair by splitting the inputed string
      * on the first found ':'.
      **/
    static std::pair<std::string, int> parse_line(std::string line);

    /** \brief Load settings from 'settings.txt'.
      * 
      * Loads 'settings.txt' and parses it's content.
      * If 'settings.txt' is not found the function creates a
      * new settings file and loads the default hardcoded settings
      * into it.
      **/
    static void load();
};