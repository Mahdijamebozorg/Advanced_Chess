#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>
#include <iostream>

class EmptySquare : public std::logic_error
{
public:
    EmptySquare(std::string msg = "EmptySquare") : logic_error(msg)
    {
    }
};

class AccessDenied : public std::logic_error
{
public:
    AccessDenied(std::string msg = "AccessDenied") : logic_error(msg)
    {
    }
};
class FinalCellForPawn : public std::logic_error
{
public:
    FinalCellForPawn(std::string msg = "FinalCellForPawn") : logic_error(msg)
    {
    }
};

class EmptyMovements : public std::logic_error
{
public:
    EmptyMovements(std::string msg = "EmptyMovement") : logic_error(msg)
    {
    }
};

class ImpossibleHitKing : public std::logic_error
{
public:
    ImpossibleHitKing(std::string msg = "Impossible Hit King") : logic_error(msg)
    {
    }
};

class KingIsChecked : public std::logic_error
{
public:
    KingIsChecked(std::string msg = "KingIs Checked")
        : logic_error(msg)
    {
    }
};

class Checkmate : public std::logic_error
{
public:
    Checkmate(std::string msg = "Checkmate")
        : logic_error(msg)
    {
    }
};

class OpenFileFailed : public std::logic_error
{
public:
    OpenFileFailed(std::string msg = "Open File Failed")
        : logic_error(msg)
    {
    }
};

class CheckingFailed : public std::logic_error
{
public:
    CheckingFailed(std::string msg = "Loading Failed")
        : logic_error(msg)
    {
    }
};

class LoadingFailed : public std::logic_error
{
public:
    LoadingFailed(std::string msg = "Loading Failed")
        : logic_error(msg)
    {
    }
};

#endif // EXCEPTIONS_HPP
