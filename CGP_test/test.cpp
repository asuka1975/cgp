//
// Created by hungr on 2020/08/12.
//
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "cgp.h"

namespace {
    float add(const std::vector<float>& v) { return std::accumulate(v.begin(), v.end(), 0.0f); }
    float mul(const std::vector<float>& v) { return std::accumulate(v.begin(), v.end(), 1.0f, [](float a, float b) { return a * b; }); }
    auto sini(std::size_t i) { return [i](const std::vector<float>& v) { return std::sin(v[i]); }; }
    auto cosi(std::size_t i) { return [i](const std::vector<float>& v) { return std::cos(v[i]); }; }
    float sigmoid(float v) { return 1.0f / (1.0f + std::exp(-v)); }

    TEST(CLASS_TEST, CGP) {
        cgp_config config;
        config.input_num = 2;
        config.output_num = 1;
        config.node_input_num = 2;
        config.network_size = std::make_pair(2u, 1u);
        config.conn_mutate_prob = 0.05f;
        config.func_mutate_prob = 0.05f;
        config.f = std::vector<std::function<float(const std::vector<float>&)>> {
            add, mul, sini(0), sini(1), cosi(0), cosi(1)
        };
        genetic::ga_config<cgp_genome> gconfig;
        configure_cgp<0, cgp_genome>(config, gconfig);
        gconfig.population = 20;
        gconfig.epoch = 100;
        gconfig.fitness_max = 4;
        gconfig.fitness_min = 0;
        gconfig.select = genetic::elite<cgp_genome> { 1 };
        gconfig.scale = [](float x) { return x * x; };
        gconfig.step = [](const std::vector<genetic::ga_config<cgp_genome>::expression_t>& d) {
            std::vector<float> f(d.size());
            std::transform(d.begin(), d.end(), f.begin(), [](genetic::ga_config<cgp_genome>::expression_t e) {
                float f = 0;
                cgp_feedforward& n = std::get<0>(e);
                n.input(std::vector<float> { 0.0f, 0.0f });
                f += 1 - sigmoid(n.get_outputs()[0]);
                n.input(std::vector<float>{0.0f, 1.0f});
                f += sigmoid(n.get_outputs()[0]);
                n.input(std::vector<float> { 1.0f, 0.0f });
                f += sigmoid(n.get_outputs()[0]);
                n.input(std::vector<float> { 1.0f, 1.0f });
                f += 1 - sigmoid(n.get_outputs()[0]);
                return f;
            });
            return f;
        };
        gconfig.callback = [](const std::vector<genetic::ga_config<cgp_genome>::expression_t>& e, const std::vector<float>& f) {
            float average = std::accumulate(f.begin(), f.end(), 0.0f) / f.size();
            float max = *std::max_element(f.begin(), f.end());
            float min = *std::min_element(f.begin(), f.end());
            std::cout << average << " " << max << " " << min << std::endl;
        };
        genetic::ga<cgp_genome> ga(gconfig);
        ga.run();
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

