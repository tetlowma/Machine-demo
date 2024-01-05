/**
 * @file Machine2Factory.h
 * @author Max Tetlow
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_MACHINE2FACTORY_H
#define CANADIANEXPERIENCE_MACHINELIB_MACHINE2FACTORY_H

#include "Machine.h"

/**
 * factory class for building the second machine
 */
class Machine2Factory
{
private:

    /// Path to the resources directory
    std::wstring mImagesDir;

    /// Path to the images directory
    std::wstring mResourcesDir;

    void TopBeamAndRamp(std::shared_ptr<Machine> machine);
    void BeamAndSpinningArm(std::shared_ptr<Machine> machine);
    void Goal(std::shared_ptr<Machine> machine);

public:

    Machine2Factory(std::wstring resourcesDir);

    std::shared_ptr<Machine> Create();

};

#endif //CANADIANEXPERIENCE_MACHINELIB_MACHINE2FACTORY_H
