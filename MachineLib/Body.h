/**
 * @file Body.h
 * @author Max Tetlow
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_BODY_H
#define CANADIANEXPERIENCE_MACHINELIB_BODY_H

#include "Component.h"
#include "PhysicsPolygon.h"
#include "RotationSink.h"

class RotationSource;

/**
 * class that represents non specified objects in the machine
 */
class Body : public Component, public RotationSink
{
private:

    /// Rotation source this object sinks to
    RotationSource* mSink = nullptr;

    /// The physics polygon object for the body
    cse335::PhysicsPolygon mPolygon;

public:

    Body();

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void SetPhysic(std::shared_ptr<ContactListener> listen, std::shared_ptr<b2World> world) override;
    void Rotate(double rotation, double speed) override;



    /**
    * Get a pointer to the polygon this body uses
    * @return Pointer to the polygon object
    */
    cse335::PhysicsPolygon* GetPolygon() override {return &mPolygon;}

    /**
     * sets the rotation source we are sinking with this object
     * @param source
     */
    void SetSource(RotationSource* source) override {mSink = source;};

};

#endif //CANADIANEXPERIENCE_MACHINELIB_BODY_H
