/**
 * @file RotationSource.cpp
 * @author Max Tetlow
 */

#include "pch.h"
#include "RotationSource.h"

/**
 * Constructor for the rotation source
 * @param comp the component that represents the rotation sink
 */
RotationSource::RotationSource(Component* comp)
{
    mComponent = comp;
}

/**
 * Adds a sink to the rotation source
 * @param sink the sink we are adding
 */
void RotationSource::AddSink(std::shared_ptr<RotationSink> sink)
{
    mSinks.push_back(sink);
    sink->SetSource(this);
}

/**
 * Sets the rotation for rotation sinks
 * @param r the rotation
 * @param speed the rotation speed
 */
void RotationSource::SetRotation(double r, double speed)
{
    for (auto sink : mSinks)
    {
        sink->Rotate(r, speed);
    }
}