#ifndef BELEGREVERSILIB_GLOBAL_H
#define BELEGREVERSILIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(BELEGREVERSILIB_LIBRARY)
#  define BELEGREVERSILIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define BELEGREVERSILIBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // BELEGREVERSILIB_GLOBAL_H
