/**
 * @file Machine.h
 * @author Max Tetlow
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_MACHINE_H
#define CANADIANEXPERIENCE_MACHINELIB_MACHINE_H

#include "b2_world.h"
#include "ContactListener.h"
#include "PhysicsPolygon.h"

class ActualMachineSystem;
class Component;

/**
 * class that represents the machine in the machine system
 */
class Machine
{
private:

    /// The box2d world
    std::shared_ptr<b2World> mWorld;

    /// The installed contact filter
    std::shared_ptr<ContactListener> mContactListener;

    /// The machine system the machine is connected to
    ActualMachineSystem* mMachineSystem = nullptr;

    ///Vector that represents the components that make up the hamster
    std::vector<std::shared_ptr<Component>> mComponents;

    ///The number of the machine
    int mMachineNumber = 1;

    //int mFlag;

public:

    Machine(int number);

    /// Assignment operator
    void operator=(const Machine &) = delete;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    void AddComponent(std::shared_ptr<Component> comp);

    void SetSystem(ActualMachineSystem* system);

    void Update(double elapsed);

    wxPoint GetLocation();

    /**
     * function that sets the machine number
     * @param number number we are setting the machine to
     */
    void SetMachineNumber(int number) {mMachineNumber = number;}

    /**
     * function that gets the machine number
     * @return the machine number
     */
    int GetNumber(){return mMachineNumber;}

    void Reset();

};

#endif //CANADIANEXPERIENCE_MACHINELIB_MACHINE_H
