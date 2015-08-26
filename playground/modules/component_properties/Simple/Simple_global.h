#ifndef SIMPLE_GLOBAL_H
#define SIMPLE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SIMPLE_LIBRARY)
#  define SIMPLESHARED_EXPORT Q_DECL_EXPORT
#else
#  define SIMPLESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SIMPLE_GLOBAL_H
