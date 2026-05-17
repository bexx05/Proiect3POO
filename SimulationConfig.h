
#ifndef UNTITLED_SIMULATIONCONFIG_H
#define UNTITLED_SIMULATIONCONFIG_H
#pragma once

class SimulationConfig {
    int rows_, cols_, cellType_;
    float probability_;

    SimulationConfig() = default;
public:
    SimulationConfig(const SimulationConfig&) = delete;
    SimulationConfig& operator=(const SimulationConfig&) = delete;

    static SimulationConfig& instance() {
        static SimulationConfig cfg;
        return cfg;
    }

    void set(int r, int c, int type, float prob) {
        rows_=r; cols_=c; cellType_=type; probability_=prob;
    }
    int rows()        const { return rows_; }
    int cols()        const { return cols_; }
    int cellType()    const { return cellType_; }
    float probability() const { return probability_; }
};
#endif //UNTITLED_SIMULATIONCONFIG_H