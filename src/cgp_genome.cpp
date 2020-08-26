//
// Created by hungr on 2020/08/13.
//
#include "cgp_genome.h"

cgp_genome cgp_genome::crossover(const cgp_genome &d1, const cgp_genome &d2) {
    cgp_genome d;
    d.input = d1.input;
    d.network_size = d1.network_size;
    d.node.reserve(d1.node.size());
    d.conn.reserve(d1.conn.size());
    d.output.reserve(d1.output.size());
    for(auto i = 0; i < d1.node.size(); i++) {
        d.node.push_back(i < d1.node.size() / 2 ? d1.node[i] : d2.node[i]);
    }
    for(auto i = 0; i < d1.conn.size(); i++) {
        d.conn.push_back(i < d1.conn.size() / 2 ? d1.conn[i] : d2.conn[i]);
    }
    for(auto i = 0; i < d1.output.size(); i++) {
        d.output.push_back(i < d1.output.size() / 2 ? d1.output[i] : d2.output[i]);
    }
    return d1;
}
