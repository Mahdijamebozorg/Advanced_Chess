#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include <fstream>
#include <iostream>
#include <vector>

class FileManager
{
private:
    std::fstream file;
    std::string game_Name = "";
    std::string p1_Name = "";
    std::string p2_Name = "";
    unsigned p1_Score = 0;
    unsigned p2_Score = 0;
    std::vector<std::string> moves;
    std::vector<std::string> savedGames;

public:
    // reads file and fills class data
    void readFile(std::string fileName, bool temp = true);

    // add (AutoSave) to current game file name
    void add_to_autoSave();

    // removes (AutoSave) from current game file name
    void saveManually();

    //--------------------------------------------------------------
    void set_newFile(std::string name);
    void set_P1_Name(std::string name);
    void set_P2_Name(std::string name);

    std::string get_File_Name();
    std::string get_P1_Name();
    std::string get_P2_Name();
    unsigned get_P1_Score();
    unsigned get_P2_Score();
    std::vector<std::string> get_Moves();
    std::vector<std::string> getSaveFiles() const;

    //--------------------------------------------------------------

    void saveMove(std::string);
    void delete_Last_Move();

    //--------------------------------------------------------------

    // load selected game
    void loadSaveFile(unsigned index);

    // read name of all save file in folder
    void readSaveFiles();

    // read and return selected save file
    std::string getSaveFileInfo(unsigned index);

    // remove selected save file
    void removeSaveFile(unsigned index);

    // remove current game save file
    void removeGameFile();

    // reset current game save file
    void resetFile();

    // reset class data
    void resetData();

    ~FileManager();
};

#endif // FILEMANAGER_HPP
