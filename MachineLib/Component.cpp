/**
 * @file Component.cpp
 * @author Max Tetlow
 */

#include "pch.h"
#include "Component.h"
#include "Machine.h"

/**
 * constructor for the component class
 */
Component::Component()
{

}

/**
 * function to draw component, only used in override
 * @param graphics the graphics context for drawing
 */
void Component::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{

}

/**
 * update component
 * @param elapsed the amount of time that has increased from last update
 */
void Component::Update(double elapsed)
{

}

/**
 * used to set the machine this component belongs to
 * @param machine
 */
void Component::SetMachine(Machine* machine)
{
    mMachine = machine;
}

/**
 * function that gets the position of the machine
 * @return the position of the machine
 */
wxPoint Component::GetPosition()
{
    return mMachine->GetLocation();
}