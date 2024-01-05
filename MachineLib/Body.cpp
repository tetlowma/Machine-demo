/**
 * @file Body.cpp
 * @author Max Tetlow
 */

#include "pch.h"
#include "Body.h"

/**
 * constructor for the body object
 */
Body::Body()
{

}

/**
 * function that draws the body object
 * @param graphics the graphics context for drawing this object
 */
void Body::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    mPolygon.Draw(graphics);
}

/**
 * function that sets the physics for this object in the physics world
 * @param listen the contact listener in the physics world
 * @param world the physics world this object is being added to
 */
void Body::SetPhysic(std::shared_ptr<ContactListener> listen, std::shared_ptr<b2World> world)
{
    mPolygon.InstallPhysics(world);
}

/**
 * function that sinks rotation with rotation source
 * @param rotation the rotation we are sinking with
 * @param speed the speed of the rotation we are sinking with
 */
void Body::Rotate(double rotation, double speed)
{
    mPolygon.SetAngularVelocity(speed);
}