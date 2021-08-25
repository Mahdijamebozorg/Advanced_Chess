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
    std::vector<std::string> moves;

public:
    void readFile(std::string fileName);

    std::string get_Game_Name();
    std::string get_P1_Name();
    std::string get_P2_Name();
    std::vector<std::string> get_Moves();

    void reset();

    void saveMove(std::string);
    void delete_Last_Move();

    void set_Game_Name(std::string name);
    void set_P1_Name(std::string name);
    void set_P2_Name(std::string name);

};

#endif // FILEMANAGER_HPP
