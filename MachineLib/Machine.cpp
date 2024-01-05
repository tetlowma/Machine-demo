/**
 * @file Machine.cpp
 * @author Max Tetlow
 */

#include "pch.h"
#include "Machine.h"
#include "ActualMachineSystem.h"
#include "Component.h"
#include "BasketballGoal.h"

#include <vector>

/// Gravity in meters per second per second
const float Gravity = -9.8f;

/// Number of velocity update iterations per step
const int VelocityIterations = 6;

/// Number of position update iterations per step
const int PositionIterations = 2;

/**
 * constructor
 * @param number the number that the machine is
 */
Machine::Machine(int number)
{
    mWorld = std::make_shared<b2World>(b2Vec2(0.0f, Gravity));
}

/**
 * Draw the machine
 * @param graphics Graphics device to render onto
 */
void Machine::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{

    for (auto component : mComponents)
    {
        component->Draw(graphics);
    }
}

/**
 * function that adds a component to the machine
 * @param comp the component we are adding to the machine
 */
void Machine::AddComponent(std::shared_ptr<Component> comp)
{
    mComponents.push_back(comp);
    comp->SetMachine(this);
}

/**
 * sets the machine system the machine belongs to
 * @param system the machine system the machine belongs to
 */
void Machine::SetSystem(ActualMachineSystem *system)
{
    mMachineSystem = system;
}

/**
 * gets the location of the machine
 * @return the location of the machine
 */
wxPoint Machine::GetLocation()
{
    return mMachineSystem->GetLocation();
}

/**
 * updates the machine
 * @param elapsed time since the last Update
 */
void Machine::Update(double elapsed)
{
    // Call Update on all of our components so they can advance in time
    for (auto component : mComponents)
    {
        component->Update(elapsed);
    }
    // Advance the physics system one frame in time
    mWorld->Step(elapsed, VelocityIterations, PositionIterations);
}

/**
 * resets the machine, restores everything to value at time zero
 */
void Machine::Reset()
{
    mWorld = std::make_shared<b2World>(b2Vec2(0.0f, Gravity));

    // Create and install the contact filter
    mContactListener = std::make_shared<ContactListener>();
    mWorld->SetContactListener(mContactListener.get());

    //install each component to the physics system
    for (auto component : mComponents)
    {
        component->SetPhysic(mContactListener, mWorld);

    }

}