#ifndef PKG_ACTIONS_I_ACTION_H
#define PKG_ACTIONS_I_ACTION_H

#include "pkg/PackageMetadata.h"

namespace pkg::actions {
    class IAction {

    public:
        virtual ~IAction();

        virtual bool ShouldBePerformed(const Package &package) const = 0;

        virtual void Perform(const PackageMetadata &package) const = 0;
    };
}

#endif
