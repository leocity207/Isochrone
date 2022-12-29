#ifndef NETWORK_OPTIMIZER_H
#define NETWORK_OPTIMIZER_H

#include "includes/network_optimizer/network.h"
#include "algorithm_station.h"

class Network_Optimizer
{
private:
    
public:
    Network_Optimizer() = delete;
    Network_Optimizer(const Network&);

    std::vector<Algorithm_Station> Optimize();
    

    const Network& m_network;
};




#endif