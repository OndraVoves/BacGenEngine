#ifndef PMESHRENDERERPROPERTIES_GLOBAL_H
#define PMESHRENDERERPROPERTIES_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PMESHRENDERERPROPERTIES_LIBRARY)
#  define PMESHRENDERERPROPERTIESSHARED_EXPORT Q_DECL_EXPORT
#else
#  define PMESHRENDERERPROPERTIESSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // PMESHRENDERERPROPERTIES_GLOBAL_H
