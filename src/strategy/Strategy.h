//
// Created by Vinay Manektalla on 30/9/21.
//

#pragma once
#include "../Utils.h"

template <typename TOrdApi>
class Strategy {
    Strategy();
    void evaluate();
    bool shouldEvaluate();
    void createAllocation();
};


template<typename TOrdApi>
Strategy<TOrdApi>::Strategy() {

}

template<typename TOrdApi>
void Strategy<TOrdApi>::evaluate() {

}

template<typename TOrdApi>
bool Strategy<TOrdApi>::shouldEvaluate() {
    return true;
}

template<typename TOrdApi>
void Strategy<TOrdApi>::createAllocation() {

}
