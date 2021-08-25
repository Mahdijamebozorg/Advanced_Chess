#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>
#include <iostream>

class EmptySquare : public std::logic_error
{
public:
    EmptySquare(std::string msg = "EmptySquare"): logic_error(msg)
    {}
};

class AccessDenied : public std::logic_error
{
public:
    AccessDenied(std::string msg = "AccessDenied"):logic_error(msg)
    {}
};
class FinalCellForPawn : public std::logic_error
{
public:
  FinalCellForPawn(std::string msg = "FinalCellForPawn"):logic_error(msg)
  {}
};

class EmptyMoveMents : public std::logic_error
{
public:
  EmptyMoveMents(std::string msg = "FinalCellForPawn"):logic_error(msg)
  {}
};

class ImpossibleHitKing : public std::logic_error
{
public:
  ImpossibleHitKing(std::string msg = "ImpossibleHitKing"):logic_error(msg)
  {}
};

class KingIsChecked : public std::logic_error
{
public:
    KingIsChecked(std::string msg = "ImpossibleHitKing")
        : logic_error(msg)
    {}
};

class Checkmate : public std::logic_error
{
public:
    Checkmate(std::string msg = "ImpossibleHitKing")
        : logic_error(msg)
    {}
};

#endif // EXCEPTIONS_HPP
