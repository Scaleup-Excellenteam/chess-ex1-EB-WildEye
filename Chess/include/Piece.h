#pragma once
#include <string>

class Piece {
protected:
    char symbol;
    std::string src;
    std::string dest;
    bool isAlive = true;

public:
    Piece() = default;
    Piece(char s, const std::string& source, const std::string& destination);
    virtual ~Piece() = default;

    char getSymbol() const;
    const std::string& getSrc() const;
    const std::string& getDest() const;
    bool getIsAlive() const;

    void setSymbol(char s);
    void setSrc(const std::string& source);
    void setDest(const std::string& destination);
    void setIsAlive(bool alive);

    virtual bool isValidMove(const std::string& source, const std::string& destination) const = 0;
};
