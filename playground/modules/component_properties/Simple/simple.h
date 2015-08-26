#ifndef SIMPLE_H
#define SIMPLE_H

#include "Simple_global.h"

#include <PlaygroundSDK/psettingtabwidget.h>

class SIMPLESHARED_EXPORT Simple : public PSettingTabWidget {
    public:
        Simple (  PActualProject *pc_project   );
        void save();
};

#endif // SIMPLE_H
