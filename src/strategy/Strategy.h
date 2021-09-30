//
// Created by Vinay Manektalla on 30/9/21.
//

#pragma once
#include "../Utils.h"

template <typename TOrdApi>
class Strategy {
    void evaluate();
    bool shouldEvalute();
    void createAllocation();
};

template<typename TOrdApi>
void Strategy<TOrdApi>::evaluate() {

}

template<typename TOrdApi>
bool Strategy<TOrdApi>::shouldEvalute() {
    return true;
}

template<typename TOrdApi>
void Strategy<TOrdApi>::createAllocation() {

}
