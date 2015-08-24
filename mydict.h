#ifndef MYDICT_H
#define MYDICT_H

#include <iostream>
#include <map>
#include <array>

//! Dictonary class
/*!
    A class which provides the different dictonaries for the GUI and texts
    In the Moment only available in german and english
*/
class MyDict
{
public:
    //! Constructor
    MyDict();

    //! Get method
    /*!
     * \brief Gets the choosen dict
     * \param sprache
     * defines the needed language
     * \return dict
     * returns the choosen dict as stringarray
     */
    std::string* getDict(std::string sprache);

private:

    std::map<std::string, std::string*> dict;
    std::string deutsch[28], english[28];
};

#endif // MYDICT_H
