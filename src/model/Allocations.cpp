#include "Allocations.h"

void model::Allocations::addAllocation(const std::shared_ptr<Allocation>& allocation_)
{
    _allocations.emplace_back(allocation_);
    _changed = true;
}