/**
 * @file RotationSink.h
 * @author Max Tetlow
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_ROTATIONSINK_H
#define CANADIANEXPERIENCE_MACHINELIB_ROTATIONSINK_H

class Component;
class RotationSource;

/**
 * Interface for setting sinks to the same rotation as there source
 */
class RotationSink
{
private:

public:

    /// Copy constructor (disabled)
    RotationSink(const RotationSink &) = delete;

    /// Assignment operator (disabled)
    void operator=(const RotationSink &) = delete;

    ///enable default constructor in order to prevent errors
    RotationSink() = default;

    /**
     * pure virtual function for rotating source with sink
     * @param rotation the rotation in radians
     * @param speed the speed of the rotation
     */
    virtual void Rotate(double rotation, double speed) = 0;
    /**
     * set the source for the rotation sink
     * @param source the source for the rotation sink
     */
    virtual void SetSource(RotationSource* source) = 0;

};

#endif //CANADIANEXPERIENCE_MACHINELIB_ROTATIONSINK_H
