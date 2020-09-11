//
// Created by hungr on 2020/08/12.
//

#ifndef CGP_CGP_H
#define CGP_CGP_H

#include <cstdint>
#include <functional>
#include <random>
#include <vector>
#include "genetic.h"
#include "cgp_genome.h"

struct cgp_config {
    std::uint32_t input_num;
    std::uint32_t output_num;
    std::uint32_t node_input_num;
    std::pair<std::uint32_t, std::uint32_t> network_size;
    std::vector<std::function<float(const std::vector<float>&)>> f;
    float func_mutate_prob;
    float conn_mutate_prob;
};

template <std::size_t I, class... TArgs>
void configure_cgp(const cgp_config& config, genetic::ga_config<TArgs...>& gconfig) {
    static_assert(I < std::tuple_size_v<std::tuple<TArgs...>>, "index out of range of parameter pack `TArgs...`");
    static_assert(std::is_same_v<std::tuple_element_t<I, std::tuple<TArgs...>>, cgp_genome>,
                  "selected type should be cgp_genome");
    using individual_t = typename genetic::ga_config<TArgs...>::individual_t;
    std::get<I>(gconfig.express) = [f = config.f](const cgp_genome& g) {
        cgp_feedforward_config config;
        config.input_num = g.input;
        config.output_num = g.output.size();
        config.network_size = g.network_size;
        config.output = g.output;
        config.conn = g.conn;
        config.node = g.node;
        config.f = f;
        return cgp_feedforward(config);
    };
    std::get<I>(gconfig.initializer) = [&config] () {
        cgp_genome g;
        g.network_size = config.network_size;
        g.input = config.input_num;
        g.conn.resize(g.network_size.first * g.network_size.second * config.node_input_num);
        g.node.resize(g.network_size.first * g.network_size.second);
        g.output.resize(config.output_num);
        for(auto& n : g.node) n = random_generator::random<std::uint32_t>() % config.f.size();
        for(auto i = 0; i < g.network_size.second; i++) {
            for(auto j = 0; j < g.network_size.first; j++) {
                for(auto k = 0; k < config.node_input_num; k++) {
                    auto idx = k + (j + i * g.network_size.first) * config.node_input_num;
                    g.conn[idx] = random_generator::random<std::uint32_t>() % (g.input + g.network_size.first * i);
                }
            }
        }
        for(auto& o : g.output) o = random_generator::random<std::uint32_t>() % (g.input + g.node.size());
        return g;
    };
    gconfig.node_mutates.emplace_back(config.func_mutate_prob, [&config](float p, individual_t& d) {
        cgp_genome& g = std::get<I>(d);
        for(auto& n : g.node) {
            if(p < random_generator::random<float>()) {
                n = random_generator::random<std::uint32_t>() % config.f.size();
            }
        }

    });
    gconfig.node_mutates.emplace_back(config.conn_mutate_prob, [&config](float p, individual_t& d) {
        cgp_genome& g = std::get<I>(d);
        for(auto i = 0; i < g.network_size.second; i++) {
            for(auto j = 0; j < g.network_size.first; j++) {
                for(auto k = 0; k < config.node_input_num; k++) {
                    if(p < random_generator::random<float>()) {
                        auto idx = k + (j + i * g.network_size.first) * config.node_input_num;
                        g.conn[idx] = random_generator::random<std::uint32_t>() % (g.input + g.network_size.first * i);
                    }
                }
            }
        }
    });
}

#endif //CGP_CGP_H
