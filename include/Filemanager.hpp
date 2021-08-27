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

public:
    void readFile(std::string fileName, bool temp = true);

    std::string get_Game_Name();
    std::string get_P1_Name();
    std::string get_P2_Name();
    unsigned get_P1_Score();
    unsigned get_P2_Score();
    std::vector<std::string> get_Moves();

    void resetFile();

    void saveMove(std::string);
    void delete_Last_Move();

    void set_Game_Name(std::string name);
    void set_P1_Name(std::string name);
    void set_P2_Name(std::string name);

    void resetData();

    ~FileManager();
};

#endif // FILEMANAGER_HPP
