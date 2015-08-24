#ifndef MYDICT_H
#define MYDICT_H

#include <iostream>
#include <map>
#include <array>

class MyDict
{
public:
    MyDict();
    std::string* getDict(std::string sprache);
private:
    std::map<std::string, std::string*> dict;
    std::string deutsch[28];
    std::string english[28];
};

#endif // MYDICT_H
