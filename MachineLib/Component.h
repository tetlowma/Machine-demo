/**
 * @file Component.h
 * @author Max Tetlow
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_COMPONENT_H
#define CANADIANEXPERIENCE_MACHINELIB_COMPONENT_H

#include "PhysicsPolygon.h"
#include "ContactListener.h"

class Machine;

/**
 * base class for all the components that make up the machine
 */
class Component
{
private:

    ///the machine this component belongs to
    Machine* mMachine = nullptr;

public:

    Component();
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics);
    void SetMachine(Machine* machine);
    virtual void Update(double elapsed);
    virtual wxPoint GetPosition();

    /**
     * virtual function to get polygon only used in override
     * @return nullptr
     */
    virtual cse335::Polygon* GetPolygon() {return nullptr;}

    /**
     * virtual function to set physics, only used in override
     * @param listen contact listener in physics world
     * @param world physics world
     */
    virtual void SetPhysic(std::shared_ptr<ContactListener> listen, std::shared_ptr<b2World> world){};

    /**
     * virtual function for setting rotation, only used in override
     * @param r the rotation we are setting to
     */
    virtual void SetRotation(double r){}

};

#endif //CANADIANEXPERIENCE_MACHINELIB_COMPONENT_H
