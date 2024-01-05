/**
 * @file Pulley.cpp
 * @author Max Tetlow
 */

#include "pch.h"
#include "Pulley.h"

/**
 * constructor for the pulley object
 * @param radius the radius of the pulley
 */
Pulley::Pulley(double radius) : mSource(this)
{

    mRadius = radius;
    mPolygon.CenteredSquare(mRadius * 2);

}

/**
 * function that draws the pulley system
 * @param graphics the graphics context for drawing
 */
void Pulley::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if(mPulley != nullptr)
    {
        auto point = mPulley->GetPosition();
        double y2 = point.y ;
        double x2 = point.x ;
        double y1 = mLocation.y;
        double x1 = mLocation.x;
        double xDiffSquared = (x2 - x1) * (x2 - x1);
        double yDiffSquared = (y2 - y1) * (y2 - y1);
        // Calculate the sum of squared differences
        double sumSquaredDiffs = xDiffSquared + yDiffSquared;
        // Calculate the square root of the sum
        double distance = sqrt(sumSquaredDiffs);
        //calculate alpha
        double alphax = mRadius/1.1*((point.x - mLocation.x) / distance);
        double alphay = mRadius/1.1*((point.y - mLocation.y) / distance);

        graphics->SetPen(wxPen(wxColour(0, 0, 0), 2));
        graphics->StrokeLine(x2 + alphay , y2 - alphax , x1 + alphay  ,y1 - alphax);
        graphics->StrokeLine(x2 - alphay , y2 + alphax , x1 - alphay  ,y1 + alphax);

    }

    mPolygon.DrawPolygon(graphics, mLocation.x, mLocation.y, mRotation);
}

/**
 * Sets the position of the pulley
 * @param point the point we are setting the position to
 */
void Pulley::SetPosition(wxPoint point)
{
    mLocation = point;
}

/**
 * function that rotates the pulley with the rotation source
 * @param rotation the rotation we are setting pulley to in radians
 * @param speed the speed of the rotation
 */
void Pulley::Rotate(double rotation, double speed)
{
    mSource.SetRotation(rotation, speed);
    mRotation = rotation;
    if(mPulley != nullptr)
    {
        mPulley->GetSource()->SetRotation(rotation, speed);
        mPulley->Rotate(rotation, speed);
    }
}

/**
 * function that links 2 pulleys together in the pulleys system
 * @param pulley the pulley that is being linked to this pulley
 */
void Pulley::Drive(std::shared_ptr<Pulley> pulley)
{
    mPulley = pulley;
}