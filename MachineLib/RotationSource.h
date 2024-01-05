/**
 * @file RotationSource.h
 * @author Max Tetlow
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_ROTATIONSOURCE_H
#define CANADIANEXPERIENCE_MACHINELIB_ROTATIONSOURCE_H

#include "Component.h"
#include "RotationSink.h"

/**
 * class that represents a rotation source
 */
class RotationSource
{
private:

    /// Component that is the rotation source
    Component* mComponent = nullptr;

    ///Vector of the rotation sinks
    std::vector<std::shared_ptr<RotationSink>> mSinks;

public:

    /// Copy constructor (disabled)
    RotationSource(const RotationSource &) = delete;

    /// Assignment operator (disabled)
    void operator=(const RotationSource &) = delete;

    RotationSource(Component* comp);

    void AddSink(std::shared_ptr<RotationSink> sink);

    void SetRotation(double r, double speed);

};

#endif //CANADIANEXPERIENCE_MACHINELIB_ROTATIONSOURCE_H
