//
// Created by hungr on 2020/08/12.
//

#ifndef CGP_CGP_H
#define CGP_CGP_H

#include <cstdint>
#include <functional>
#include <vector>
#include "genetic.h"
#include "cgp_genome.h"

struct cgp_config {
    std::uint32_t input_num;
    std::uint32_t output_num;
    std::uint32_t node_input_num;
    std::pair<std::uint32_t, std::uint32_t> network_size;
    std::vector<std::function<float(float)>> f;
};

template <std::size_t I, class... TArgs>
void configure_cgp(const cgp_config& config, genetic::ga_config<TArgs...>& gconfig) {
    static_assert(I < std::tuple_size_v<std::tuple<TArgs...>>, "index out of range of parameter pack `TArgs...`");
    static_assert(std::is_same_v<std::tuple_element_t<I, std::tuple<TArgs...>>, cgp_genome>,
                  "selected type should be cgp_genome");

}

#endif //CGP_CGP_H
