#include "../include/Filemanager.hpp"
#include "../include/Exceptions.hpp"
#include <sys/stat.h>
#include <dirent.h>
#include <QDebug>

using namespace std;

//________________________________________________________________________________________________________ LOAD FILE

//------------------------------------------------------------------------- reading game from file
void FileManager::readFile(std::string fileName, bool isChecking)
{

    // test
    qDebug() << "in readFile: " << QString::fromStdString(savedGames[2]);

    resetData();

    // test
    qDebug() << "in readFile: " << QString::fromStdString(savedGames[2]);

    // dir
    this->file_Dir = "./SavedGames/" + fileName;

    this->game_Name = fileName;
    // remove format
    for (size_t i = 0; i < 4; i++)
    {
        game_Name.pop_back();
    }

    qDebug() << "Reading file: " << QString::fromStdString(file_Dir) << endl;

    // open
    file.open(file_Dir.c_str(), ios::in);

    // if file error
    if (!file.is_open() || file.bad())
    {
        file.close();
        throw(OpenFileFailed("Can't open " + file_Dir));
    }

    // make sure is begining of file
    file.seekg(0);

    // read players name
    getline(file, p1_Name);
    getline(file, p2_Name);

    // if players names are empty
    if (!isChecking && (p1_Name.empty() || p2_Name.empty()))
    {
        file.close();
        throw LoadingFailed("Users names have not been saved well in file " + file_Dir);
    }

    // read moves in file
    string tempMove;
    while (!file.eof())
    {
        // file.ignore(1, '\"');
        getline(file, tempMove);

        if (file.eof()) // delimiter
            break;

        // ignore empty line
        if (tempMove.empty())
            continue;

        // triming
        if (tempMove[0] == '\"')
        {
            tempMove = tempMove.substr(1, (tempMove.back() - 2));
        }

        // check promotion
        bool isPrm = false;
        if (tempMove.size() == 9 || tempMove.size() == 10)
        {
            isPrm = true;
        }

        // if has unknow moves
        if (!isPrm && (tempMove.size() < 18 || tempMove.size() > 28))
        {
            resetData();
            // if is checking the file
            if (isChecking)
            {
                throw CheckingFailed("Move " + tempMove + " has invalid size in file " + file_Dir);
            }
            // if is loading the file
            else
            {
                throw LoadingFailed("Move " + tempMove + " has invalid size in file " + file_Dir);
            }
        }

        // remove Rook single move on king-rook
        if (tempMove.substr(0, 3) == "KRO")
            moves.pop_back();

        moves.push_back(tempMove);

        // color
        string moveColor = tempMove.substr((tempMove.find('%') + 2), 1);

        // score
        if (moveColor == "W")
            p1_Score += stoi(tempMove.substr(tempMove.find('$') + 1, tempMove.back()));
        else if (moveColor == "B")
            p2_Score += stoi(tempMove.substr(tempMove.find('$') + 1, tempMove.back()));
    }
    file.close();
}

//------------------------------------------------------------------------- save Manually

void FileManager::saveManually()
{
    string tempDir = "./SavedGames/" + game_Name;

    tempDir += ".txt";
    rename(file_Dir.c_str(), tempDir.c_str());
    file_Dir = tempDir;
}

//-------------------------------------------------------------------------  get loaded game data
string FileManager::get_File_Dir()
{
    return this->file_Dir;
}

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
    file.open(file_Dir.c_str(), ios::out | ios::trunc);
    file << p1_Name << '\n'
         << p2_Name << '\n';
    file.close();
}

//_________________________________________________________________________________________________ EDIT FILE

//------------------------------------------------------------------------- add move to file
void FileManager::saveMove(string move)
{
    file.open(this->file_Dir.c_str(), ios::app);
    if (!file.is_open() || file.bad())
    {
        file.close();
        throw(OpenFileFailed("FileManager::saveMove: can't open " + file_Dir));
    }

    file << '\"' << move << '\"' << '\n';
    file.close();
}

//-------------------------------------------------------------------------  remove move from file
void FileManager::delete_Last_Move()
{
    vector<string> tempMoves;
    string tempMove;
    //---------------------------------------- read
    file.open(file_Dir.c_str(), ios::in);
    if (!file.is_open() || file.bad())
    {
        file.close();
        throw(OpenFileFailed("FileManager::delete_Last_Move - read: can't open " + file_Dir));
    }
    file.seekg(0);

    getline(file, p1_Name, '\n');
    getline(file, p2_Name, '\n');

    while (!file.eof())
    {
        getline(file, tempMove);

        if (file.eof())
            break;

        tempMoves.push_back(tempMove);
    }

    file.close();

    //---------------------------------------- write
    file.open(file_Dir.c_str(), ios::trunc | ios::out);
    if (!file.is_open() || file.bad())
    {
        file.close();
        throw(OpenFileFailed("FileManager::delete_Last_Move - write: can't open " + file_Dir));
    }
    file.seekp(0);

    file << p1_Name << '\n';
    file << p2_Name << '\n';

    for (size_t i = 0; i < tempMoves.size() - 1; i++)
    {
        file << tempMoves[i] << '\n';
    }

    file.close();
}

//_________________________________________________________________________________________________ NEW FILE

//-------------------------------------------------------------------------------------------
// setting new game
void FileManager::set_newFile(std::string gameName)
{

    // if save file doesn't exist , makes one
    struct stat buff;
    if (stat("./SavedGames", &buff) != 0)
        if (mkdir("./SavedGames") != 0)
            throw OpenFileFailed("can't make save files");

    this->game_Name = gameName;
    this->file_Dir = "./SavedGames/" + game_Name + "(AutoSave)" + ".txt";

    // test file
    file.open(file_Dir.c_str(), ios::trunc | ios::out);

    if (!file.is_open() || file.bad())
    {
        file.close();
        throw(OpenFileFailed("can't open file in set game"));
    }
    file.close();
}

//-------------------------------------------------------------------------------------------

void FileManager::set_P1_Name(std::string name)
{
    file.open(file_Dir, ios::trunc | ios::out);
    this->p1_Name = name;
    file << p1_Name << '\n';
    file.close();
}

//-------------------------------------------------------------------------------------------

void FileManager::set_P2_Name(std::string name)
{
    file.open(file_Dir, ios::ate);
    this->p2_Name = name;
    file << p2_Name << '\n';
    file.close();
}

//-------------------------------------------------------------------------------------------

void FileManager::removeGameFile()
{
    remove(file_Dir.c_str());
}

//-------------------------------------------------------------------------------------------

void FileManager::loadSaveFile(unsigned index)
{
    // test
    qDebug() << "before FileManager::loadSaveFile: " << QString::fromStdString(savedGames[index]);

    readFile(savedGames[index], false);

    // add to autosave
    string tempName = "./SavedGames/" + game_Name;
    if (tempName.substr(tempName.find("(") + 1, tempName.find(")")) != "AutoSave)")
        tempName += ("(AutoSave)");
    tempName += ".txt";

    this->file_Dir = tempName;

    // test
    qDebug() << "after FileManager::loadSaveFile: " << QString::fromStdString(savedGames[index]);
}

//-------------------------------------------------------------------------------------------

void FileManager::readSaveFiles()
{
    savedGames.clear();

    struct stat buff;
    if (stat("./SavedGames", &buff) != 0)
        if (mkdir("./SavedGames") != 0)
            throw OpenFileFailed("FileManager::readSaveFiles: can't make SavedGames folder");

    // open save folder
    DIR *dir;
    struct dirent *diread;

    // if can open folder
    if ((dir = opendir("./SavedGames")) != nullptr)
    {
        // collect txt files names
        while ((diread = readdir(dir)) != nullptr)
        {
            string temp = diread->d_name;
            string suffix = temp.substr(temp.find('.'), temp.back());
            if (suffix == ".txt")
            {
                qDebug() << QString::fromStdString(temp) << " added to save games" << Qt::endl;
                savedGames.push_back(temp);
            }
        }
        closedir(dir);
        dir = nullptr;
        diread = nullptr;
    }
    else
    {
        perror("opendir");
        throw OpenFileFailed("FileManager::readSaveFiles: can't acces SaveGames folder");
    }
}

//-------------------------------------------------------------------------------------------

string FileManager::getSaveFileInfo(unsigned index)
{
    // test
    qDebug() << "before FileManager::getSaveFileInfo: " << QString::fromStdString(savedGames[index]);

    string fileName = savedGames[index];

    readFile(fileName, true);

    string score1 = '(' + to_string(p1_Score) + ')';
    string score2 = '(' + to_string(p2_Score) + ')';

    // test
    qDebug() << "after FileManager::getSaveFileInfo: " << QString::fromStdString(savedGames[index]);

    return (fileName + " :   P1:   " + p1_Name + score1 + "      P2:   " + p2_Name + score2);
}

//-------------------------------------------------------------------------------------------

vector<string> FileManager::getSaveFiles() const
{
    return savedGames;
}

//-------------------------------------------------------------------------------------------

void FileManager::removeSaveFile(unsigned index)
{
    // test
    qDebug() << "before FileManager::removeSaveFile: " << QString::fromStdString(savedGames[index]);

    remove(("./SavedGames/" + (savedGames[index])).c_str());

    // test
    qDebug() << "before FileManager::removeSaveFile: " << QString::fromStdString(savedGames[index]);
}
//-------------------------------------------------------------------------------------------
// closes file and reset class data
void FileManager::resetData()
{
    file.close();
    this->p1_Score = 0;
    this->p2_Score = 0;
    this->p1_Name.clear();
    this->p2_Name.clear();
    this->file_Dir.clear();
    this->moves.clear();
}

//-------------------------------------------------------------------------------------------

FileManager::~FileManager()
{
    resetData();
}
//-------------------------------------------------------------------------------------------
