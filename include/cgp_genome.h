//
// Created by hungr on 2020/08/13.
//

#ifndef CGP_CGP_GENOME_H
#define CGP_CGP_GENOME_H

#include <cstdint>
#include <vector>
#include "cgp_feedforward.h"

struct cgp_genome {
    using expression_t = cgp_feedforward;
    std::uint32_t input;
    std::pair<std::uint32_t, std::uint32_t> network_size;
    std::vector<std::uint32_t> node;
    std::vector<std::uint32_t> conn;
    std::vector<std::uint32_t> output;
    static cgp_genome crossover(const cgp_genome& d1, const cgp_genome& d2);
};

#endif //CGP_CGP_GENOME_H
