#pragma once

#include "Allocation.h"

namespace model {

class Allocations {
private:
    std::vector<std::shared_ptr<Allocation>> _allocations;
    bool _changed;

public:
    explicit Allocations() :
            _changed(false) {};

    bool hasChanged() const { return _changed; };
    void setChanged() { _changed = true; };
    void setUnchanged() { _changed = false; };
    void addAllocation(const std::shared_ptr<Allocation>& allocation_);
};

}