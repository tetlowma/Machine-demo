/**
 * @file Pulley.h
 * @author Max Tetlow
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_PULLEY_H
#define CANADIANEXPERIENCE_MACHINELIB_PULLEY_H

#include "Component.h"
#include "RotationSink.h"
#include "RotationSource.h"

class RotationSource;

/**
 * class that represents a pulley component in the machine
 */
class Pulley : public Component, public RotationSink
{
private:

    ///Rotation source we sink this object with
    RotationSource* mSink = nullptr;

    /// Rotation source for this component
    RotationSource mSource;

    ///The other pulley this pulley is connected to
    std::shared_ptr<Pulley> mPulley = nullptr;

    ///Weather or not this pulley is rotating
    bool isRotating = false;

    /// Polygon that represents the pulley object
    cse335::Polygon mPolygon;

    ///the radius of the pulley
    double mRadius = 1;

    ///The rotation of the pulley
    double mRotation = 0;

    ///the location of the pulley
    wxPoint mLocation;

public:

    Pulley(double radius);

    void SetPosition(wxPoint point);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
     * getter for the polygon that represent the pulley
     * @return the polygon that represents the pulley
     */
    cse335::Polygon* GetPolygon() override {return &mPolygon;}

    void Rotate(double rotation, double speed) override;

    /**
     * sets the physics for the pulley, just sets rotation to zero
     * @param listen the contact listener for the physics world
     * @param world the physics world
     */
    void SetPhysic(std::shared_ptr<ContactListener> listen, std::shared_ptr<b2World> world) override{mRotation = 0;};

    void Drive(std::shared_ptr<Pulley> pulley);

    /**
     * Get the position of the polley
     * @return the position of the pulley
     */
    wxPoint GetPosition() override {return mLocation;}

    /**
    * Get a pointer to the source object
    * @return Pointer to RotationSource object
    */
    RotationSource *GetSource() { return &mSource; }

    /**
     * sets the rotation source this pulley sinks with
     * @param source the rotation source the pulley sinks with =
     */
    void SetSource(RotationSource* source) override {mSink = source;}

};

#endif //CANADIANEXPERIENCE_MACHINELIB_PULLEY_H
