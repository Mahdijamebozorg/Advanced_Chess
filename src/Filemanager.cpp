#include "../include/Filemanager.hpp"
#include <QDebug>

using namespace std;

//________________________________________________________________________________________________________ LOAD FILE

//------------------------------------------------------------------------- reading game from file
void FileManager::readFile(std::string fileName, bool temp)
{
    resetData();

    this->game_Name = "./SavedGames/" + fileName;

    qDebug() << game_Name.c_str();

    file.open(game_Name.c_str(), ios::in);
    if (!file.is_open())
        throw(runtime_error("can't open file"));

    file.seekg(0); //to be sure

    string tempMove;

    getline(file, p1_Name);
    getline(file, p2_Name);

    while (!file.eof()) {
        file.ignore(1, '\"');
        getline(file, tempMove, '\"');

        if (file.eof() || tempMove.empty()) //delimiter
            break;

        moves.push_back(tempMove);

        string moveColor = tempMove.substr((tempMove.find('%') + 2), 1);
        if (moveColor == "W")
            p1_Score += stoi(tempMove.substr(tempMove.find('$') + 1, tempMove.back()));
        else if (moveColor == "B")
            p2_Score += stoi(tempMove.substr(tempMove.find('$') + 1, tempMove.back()));
    }
    file.close();

    if (!temp)
        this->resetFile();
}

//-------------------------------------------------------------------------  get loaded game data
string FileManager::get_Game_Name()
{
    return this->game_Name;
}
string FileManager::get_P1_Name()
{
    return this->p1_Name;
}
string FileManager::get_P2_Name()
{
    return this->p2_Name;
}

unsigned FileManager::get_P1_Score()
{
    return this->p1_Score;
}

unsigned FileManager::get_P2_Score()
{
    return this->p2_Score;
}
vector<string> FileManager::get_Moves()
{
    return this->moves;
}

//-------------------------------------------------------------------------  discard data

void FileManager::resetFile()
{
    file.open(game_Name.c_str(), ios::out | ios::trunc);
    file << p1_Name << '\n' << p2_Name << '\n';
    file.close();
}

//________________________________________________________________________________________________________ EDIT FILE

//------------------------------------------------------------------------- add move to file
void FileManager::saveMove(string move)
{
    file.open(this->game_Name.c_str(), ios::app);
    if (!file.is_open())
        throw(runtime_error("can't open file"));

    file << '\"' << move << '\"' << '\n';
    file.close();
}

//-------------------------------------------------------------------------  remove move from file
void FileManager::delete_Last_Move()
{
    vector<string> tempMoves;
    string tempMove;
    //---------------------------------------- read
    file.open(game_Name.c_str(), ios::in);
    if (!file)
        throw(runtime_error("can't open file"));
    file.seekg(0);

    getline(file, p1_Name, '\n');
    getline(file, p2_Name, '\n');

    while (!file.eof()) {
        file.ignore(1, '\"');
        getline(file, tempMove, '\"');

        if (file.eof())
            break;

        tempMoves.push_back(tempMove);
    }

    file.close();

    //---------------------------------------- write
    file.open(game_Name.c_str(), ios::trunc | ios::out);
    if (!file.is_open())
        throw(runtime_error("can't open file"));
    file.seekp(0);

    file << p1_Name << '\n';
    file << p2_Name << '\n';

    for (size_t i = 0; i < tempMoves.size() - 1; i++) {
        file << '\"' << tempMoves[i] << '\"' << '\n';
    }

    file.close();
}

//________________________________________________________________________________________________________ NEW FILE

//------------------------------------------------------------------------- setting new game
void FileManager::set_Game_Name(std::string name)
{
    this->game_Name = "./SavedGames/" + name + ".txt";
    file.open(game_Name.c_str(), ios::out);
    if (!file)
        throw(runtime_error("can't open file in set game"));
}
void FileManager::set_P1_Name(std::string name)
{
    this->p1_Name = name;
    file << p1_Name << '\n';
}
void FileManager::set_P2_Name(std::string name)
{
    this->p2_Name = name;
    file << p2_Name << '\n';
    file.close();
}

//-------------------------------------------------------------------------------------------

void FileManager::resetData()
{
    file.close();
    this->p1_Score = 0;
    this->p2_Score = 0;
    this->p1_Name = "";
    this->p2_Name = "";
    this->game_Name = "";
    this->moves.clear();
}

//-------------------------------------------------------------------------------------------

FileManager::~FileManager()
{
    resetData();
}
//-------------------------------------------------------------------------------------------
