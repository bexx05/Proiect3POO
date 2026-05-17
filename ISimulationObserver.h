
#ifndef UNTITLED_ISIMULATIONOBSERVER_H
#define UNTITLED_ISIMULATIONOBSERVER_H
#pragma once

class ISimulationObserver {
public:
    virtual void onGenerationUpdate(int generation, int livingCells) = 0;
    virtual ~ISimulationObserver() = default;
};
#endif //UNTITLED_ISIMULATIONOBSERVER_H