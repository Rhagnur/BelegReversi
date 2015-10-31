#ifndef MYDICT_H
#define MYDICT_H

#include <QString>
#include <map>
#include <array>

//! Dictonary class
/*!
    A class which provides the different dictonaries for the GUI and texts
    In the Moment only available in german and english
 * \author Baran
*/
class MyDict
{
public:
    //! Constructor
    MyDict();

    /*!
     * \brief Gets the choosen dict
     * \param sprache
     * defines the needed language
     * \return dict
     * returns the choosen dict as stringarray
     */
    QString* getDict(QString sprache);

private:

    std::map<QString, QString*> dict;
    QString deutsch[31], english[31];
};

#endif // MYDICT_H
