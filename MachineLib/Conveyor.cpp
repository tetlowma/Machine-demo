/**
 * @file Conveyor.cpp
 * @author Max Tetlow
 */

#include "pch.h"
#include "Conveyor.h"
#include "b2_contact.h"

/// The offset from the bottom center of the conveyor
/// to the center of the drive shaft.  48
const auto ConveyorShaftOffset = wxPoint(48, 4);

/// The size of the conveyor in cm
const auto ConveyorSize = wxSize(125, 14);

/// The conveyor image to use
const std::wstring ConveyorImageName = L"/conveyor.png";

/**
 * constructor for the conveyor class
 * @param imagesDir the directory where the images for this conveyor are located
 */
Conveyor::Conveyor(std::wstring imagesDir)
{
    mConveyor.BottomCenteredRectangle(ConveyorSize);
    mConveyor.SetImage(imagesDir + ConveyorImageName);
}

/**
 * function that draws the conveyor object
 * @param graphics the graphics context for drawing
 */
void Conveyor::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    mConveyor.Draw(graphics);
}

/**
 * sets the position of the conveyor in the machine
 * @param point the position we are setting the conveyor to
 */
void Conveyor::SetPosition(wxPoint point)
{
    mLocation = point;
    mConveyor.SetInitialPosition(point.x, point.y);
}

/**
 * gets the shaft position of the conveyor where the rotation source is located
 * @return position of the shaft
 */
wxPoint Conveyor::GetShaftPosition()
{
    auto point = wxPoint(mLocation.x + ConveyorShaftOffset.x , mLocation.y + ConveyorShaftOffset.y);
    return point;
}

/**
 * sets the physics of the conveyor in the physics world
 * @param listen the contact listener for the physics world
 * @param world the physics world
 */
void Conveyor::SetPhysic(std::shared_ptr<ContactListener> listen, std::shared_ptr<b2World> world)
{
    mConveyor.InstallPhysics(world);
    listen->Add(mConveyor.GetBody(), this);
    mConveyor.InstallPhysics(world);
    mSpeed = 0;
}

/**
 * function that sets the speed of objects in contact with the conveyor
 * @param contact the contact listener in the physics world
 * @param oldManifold manifold for the contact listener
 */
void Conveyor::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
{
    contact->SetTangentSpeed(-mSpeed);
}

/**
 * function that rotates the conveyor with the rotation source
 * @param rotation the rotation in degrees for the object
 * @param speed the speed of the rotation
 */
void Conveyor::Rotate(double rotation, double speed)
{
    if (rotation != 0)
    {
        mSpeed = speed;
    }
    auto contact = mConveyor.GetBody()->GetContactList();
    while(contact != nullptr)
    {
        if(contact->contact->IsTouching())
        {
            contact->other->SetLinearVelocity(b2Vec2(-mSpeed, 0));
        }

        contact = contact->next;
    }
}