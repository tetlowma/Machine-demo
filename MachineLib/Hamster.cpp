/**
 * @file Hamster.cpp
 * @author Max Tetlow
 */

#include "pch.h"
#include "Hamster.h"
#include <cmath>


/// The center point for drawing the wheel
/// relative to the bottom center of the cage
const auto WheelCenter = wxPoint(-12, 24);

/// The size of the hamster cage in centimeters
const auto HamsterCageSize = wxSize(75, 50);

/// Size of the hamster wheel (diameter) in centimeters
const double HamsterWheelSize = 45;

/// Size of the hamster wheel (square) in centimeters
const double HamsterSize = 45;

/// How fast the hamster runs. This is now many cycles of
/// the 3 images we make per second as images 1, 2, 3, 2, ...
const double HamsterSpeed = 4.0;

/// The offset from the bottom center of the hamster cage
/// to the center of the output shaft.
const auto HamsterShaftOffset = wxPoint(25, 40);

/// The image for the hamster cage
const std::wstring HamsterCageImage = L"/hamster-cage.png";

/// The image for the hamster wheel
const std::wstring HamsterWheelImage = L"/hamster-wheel.png";

/// The hamster images. Image 0 is sleeping, 1-3 are
/// the running hamster animation images.
const std::wstring HamsterImages[4] =
    {L"/hamster-sleep.png", L"/hamster-run-1.png",
        L"/hamster-run-2.png", L"/hamster-run-3.png"};

/**
 * constructor for the hamster class
 * @param imagesDir the directory for the images used to draw the hamster
 */
Hamster::Hamster(std::wstring imagesDir) : mSource(this)
{
    mPolygon.BottomCenteredRectangle(HamsterCageSize);
    mPolygon.SetImage(imagesDir + HamsterCageImage);

    mWheel.CenteredSquare(HamsterWheelSize);
    mWheel.SetImage(imagesDir + HamsterWheelImage);

    mCage.BottomCenteredRectangle(HamsterCageSize);
    mCage.SetColor(*wxBLUE);

    mHamsters[0].CenteredSquare(HamsterSize);
    mHamsters[0].SetImage(imagesDir + HamsterImages[0]);
    mHamsters[1].CenteredSquare(HamsterSize);
    mHamsters[1].SetImage(imagesDir + HamsterImages[1]);
    mHamsters[2].CenteredSquare(HamsterSize);
    mHamsters[2].SetImage(imagesDir + HamsterImages[2]);
    mHamsters[3].CenteredSquare(HamsterSize);
    mHamsters[3].SetImage(imagesDir + HamsterImages[3]);

}

/**
 * function that draws the hamster
 * @param graphics the graphics context for drawing the hamster
 */
void Hamster::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();

    mPolygon.DrawPolygon(graphics, mLocation.x, mLocation.y, 0);
    mWheel.DrawPolygon(graphics, mLocation.x + WheelCenter.x , mLocation.y + WheelCenter.y, mRotation );

    //mCage.Draw(graphics);
    if(mSpeed < 0)
    {
        graphics->Scale(-1, 1);
        // Draw the running image
        mHamsters[hamsterIndex].DrawPolygon(graphics, -(mLocation.x + WheelCenter.x) , mLocation.y + WheelCenter.y, 0);
    }
    else
    {
        // Draw the running image
        mHamsters[hamsterIndex].DrawPolygon(graphics, mLocation.x + WheelCenter.x , mLocation.y + WheelCenter.y, 0);
    }

    graphics->PopState();
}

/**
 * function that sets the physics for the hamster
 * @param listen the contact listener for the physics world
 * @param world the physics world the hamster is in
 */
void Hamster::SetPhysic(std::shared_ptr<ContactListener> listen, std::shared_ptr<b2World> world)
{
    if(not initialRun)
    {
        isAsleep = false;
        hamsterIndex = 0;
    }

    mCage.InstallPhysics(world);
    listen->Add(mCage.GetBody(), this);
    mCage.InstallPhysics(world);
    mRotation = 0;
}

/**
 * function to set the position of the hamster
 * @param x the x coordinate of the hamsters position
 * @param y the y coordinate of the hamsters position
 */
void Hamster::SetPosition(int x, int y)
{
    mLocation = wxPoint(x, y);
    mCage.SetInitialPosition(mLocation.x, mLocation.y);
}

/**
 * returns the physics polygon that represents that hamster cage
 * @return the physics polygon for the cage
 */
cse335::PhysicsPolygon *Hamster::GetPolygon()
{
    return &mCage;
}

/**
 * Handle a contact beginning
 * @param contact Contact object
 */
void Hamster::BeginContact(b2Contact *contact)
{
    this->isAsleep = true;
}

/**
 * updates the state of the hamster
 * @param elapsed time since last frame
 */
void Hamster::Update(double elapsed)
{

    //determine weather to add or subtract from rotation to keep within 1
    if(isAsleep)
    {
        mRotation += -mSpeed * elapsed;
    }
    if(mRotation <= -1)
    {
        mRotation += 1;
    }
    else if(mRotation >= 1)
    {
        mRotation -= 1;
    }

    double degree;

    //determine how to keep degree positive based on the speed
    if(mSpeed > 0)
    {
        degree = (-mRotation * 180) / M_PI;
    }
    else
    {
        degree = (mRotation * 180) / M_PI;
    }

    mSource.SetRotation(mRotation, -mSpeed);

    //set the hamster image based on the degree of the rotation
    if(isAsleep)
    {
        if(degree >= 0 && degree < 3.75 || degree >= 15 && degree < 18.75 || degree >= 30 && degree < 33.75 || degree >= 45 && degree < 48.75 || elapsed == 0)
        {
            hamsterIndex = 1;
        }
        else if(degree >= 7.5 && degree < 11.25 || degree >= 22.5 && degree < 26.5 || degree >= 37.5 && degree < 41.25 || degree >= 52.5 && degree < 56.25)
        {
            hamsterIndex = 3;
        }
        else
        {
            hamsterIndex = 2;
        }
    }
    else
    {
        hamsterIndex = 0;
    }
}

/**
 * function that gets the position of the shaft for the hamster rotation sink
 * @return position of the shaft
 */
wxPoint Hamster::GetShaftPosition()
{
    auto point = wxPoint(mLocation.x + HamsterShaftOffset.x, mLocation.y + HamsterShaftOffset.y);
    return point;
}

/**
 * weather or not the hamster is asleep at the machine start time
 * @param sleep what we set the hamster sleep to
 */
void Hamster::SetInitiallyRunning(bool sleep)
{
    isAsleep = sleep;
    initialRun = sleep;
    if(sleep)
    {
        hamsterIndex = 1;
    }
}

