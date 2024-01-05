/**
 * @file Hamster.h
 * @author Max Tetlow
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_HAMSTER_H
#define CANADIANEXPERIENCE_MACHINELIB_HAMSTER_H

#include "Component.h"
#include "PhysicsPolygon.h"
#include "Polygon.h"
#include "RotationSource.h"

/**
 * function that represents a hamster in the machine
 */
class Hamster : public Component, public b2ContactListener
{
private:

    /// Rotation source for this component
    RotationSource mSource;

    /// value that keeps track of rotation
    double mRotation = 0;

    /// the speed of the rotation
    double mSpeed = 1;

    ///the index for the hamster image we are using
    int hamsterIndex = 0;

    ///weather or not the hamster was running initially
    bool initialRun = false;

    ///weather or not the hamster is running
    bool isAsleep = false;

    ///variable for hamster images
    cse335::Polygon mHamsters[4];

    ///variable for cage drawing
    cse335::Polygon mPolygon;

    ///variable for the cage physics
    cse335::PhysicsPolygon mCage;

    ///variable for wheel
    cse335::Polygon mWheel;

    ///location of the cage
    wxPoint mLocation;

public:
    Hamster(std::wstring imagesDir);

    void SetPosition(int x, int y);

    wxPoint GetShaftPosition();

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void SetPhysic(std::shared_ptr<ContactListener> listen, std::shared_ptr<b2World> world) override;
    cse335::PhysicsPolygon * GetPolygon() override;
    void BeginContact(b2Contact *contact) override;
    void Update(double elapsed) override;


    /**
    * Get a pointer to the source object
    * @return Pointer to RotationSource object
    */
    RotationSource *GetSource() { return &mSource; }

    void SetInitiallyRunning(bool sleep);

    /**
     * sets the speed the hamster will run at
     * @param speed the speed we are setting for the hamster
     */
    void SetSpeed(double speed) {mSpeed = speed;}

};

#endif //CANADIANEXPERIENCE_MACHINELIB_HAMSTER_H
