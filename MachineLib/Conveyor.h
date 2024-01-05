/**
 * @file Conveyor.h
 * @author Max Tetlow
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_CONVEYOR_H
#define CANADIANEXPERIENCE_MACHINELIB_CONVEYOR_H

#include "Component.h"
#include "RotationSink.h"

class RotationSource;

/**
 * class the represents a conveyor object in the machine
 */
class Conveyor : public Component , public RotationSink , public b2ContactListener
{
private:

    /// The rotation source for this object
    RotationSource* mSink = nullptr;

    ///the polygon that represents this object
    cse335::PhysicsPolygon mConveyor;

    ///The location of the conveyor
    wxPoint mLocation;

    ///The speed that the conveyor is moving
    double mSpeed = 0;

public:

    Conveyor(std::wstring imagesDir);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void Rotate(double rotation, double speed) override;
    void SetPhysic(std::shared_ptr<ContactListener> listen, std::shared_ptr<b2World> world) override;
    void PreSolve(b2Contact *contact, const b2Manifold *oldManifold) override;

    /**
     * getter for the polygon that represents the conveyor
     * @return the polygon that represents this conveyor
     */
    cse335::PhysicsPolygon* GetPolygon() override {return &mConveyor;}

    void SetPosition(wxPoint point);

    /**
     * returns the location of the conveyor
     * @return the location of the conveyor
     */
    wxPoint GetPosition() override {return mLocation;}
    wxPoint GetShaftPosition();

    /**
     * sets the rotation source we are sinking this object with
     * @param source the source we are sinking with
     */
    void SetSource(RotationSource* source) override {mSink = source;}

};

#endif //CANADIANEXPERIENCE_MACHINELIB_CONVEYOR_H
