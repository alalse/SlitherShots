/**
 * \class Settings_handler
 * \brief Handles input and output to external settings file.
 *
 * This class handles input and output to the external settings
 * file and parses the file's content into workable data.
 */

#pragma once

#include <map>

class Settings_handler
{
    public:
    ///Create a Settings_handler class
    Settings_handler(std::string file = "settings.txt");

    /** \brief Load settings from assigned file.
      * \return Map containing parsed data from assigned file.
      * 
      * Loads assigned file and parses it's content.
      * If file is not found the function creates a
      * new settings file and loads the default settings
      * from template_settings.txt into it.
      * */
    std::map<std::string, int> load();

    /** \brief Writes to assigned file
     * \param Map parsed from assigned file
      * 
      * Opens assigned file and writes content
      * of map parameter to it.
      * */
    void write(std::map<std::string, int> settings);

    private:
    ///Assigned file
    std::string file;

    /** \brief Parses a string from assigned file.
     * \param A line to parse
     * \return Returns a parsed line as std::pair<std::string, int>.
     * 
     * Loads assigned file and parses it's content.
     * If file is not found the function creates a
     * new settings file and loads the default settings
     * from template_settings.txt into it.
     * */
    std::pair<std::string, int> parse_line(std::string line);
};