/**
 * @file ActualMachineSystem.cpp
 * @author Max Tetlow
 */

#include "pch.h"
#include "ActualMachineSystem.h"
#include "Machine.h"
#include "Machine1Factory.h"
#include "Machine2Factory.h"

/**
 * constructor for the machine system
 * @param resourcesDir directory where the images for the machine are located
 */
ActualMachineSystem::ActualMachineSystem(std::wstring resourcesDir):mResourcesDir(resourcesDir)
{
    SetMachineNumber(1);
}

/**
* Set the position for the root of the machine
* @param location The x,y location to place the machine
*/
void ActualMachineSystem::SetLocation(wxPoint location)
{
    mLocation = location;
}

/**
 * Get the location of the machine
 * @return Location x,y in pixels as a point
 */
wxPoint ActualMachineSystem::GetLocation()
{
    return mLocation;
}

/**
* Draw the machine at the currently specified location
* @param graphics Graphics object to render to
*/
void ActualMachineSystem::DrawMachine(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();
    graphics->Translate(mLocation.x, mLocation.y);
    graphics->Scale(mPixelsPerCentimeter, -mPixelsPerCentimeter);
    mMachine->Draw(graphics);
    graphics->PopState();
}

/**
* Set the current machine animation frame
* @param frame Frame number
*/
void ActualMachineSystem::SetMachineFrame(int frame)
{
    if(frame < mFrame)
    {
        mFrame = 0;
        mMachine->Reset();
    }

    for( ; mFrame < frame;  mFrame++)
    {

        mMachine->Update(1.0 / mFrameRate);
    }
    SetMachineTime(mFrame/mFrameRate);
}

/**
 * Set the expected frame rate in frames per second
 * @param rate Frame rate in frames per second
 */
void ActualMachineSystem::SetFrameRate(double rate)
{
    mFrameRate = rate;
}

/**
* Set the machine number
* @param machine An integer number. Each number makes a different machine
*/
void ActualMachineSystem::SetMachineNumber(int machine)
{
    if(machine == 1)
    {
        Machine1Factory machine1Factory(mResourcesDir);
        mMachine = machine1Factory.Create();
        mMachine->SetMachineNumber(1);
        mMachine->SetSystem(this);
        mMachine->Reset();
    }
    else
    {
        Machine2Factory machine2Factory(mResourcesDir);
        mMachine = machine2Factory.Create();
        mMachine->SetMachineNumber(2);
        mMachine->SetSystem(this);
        mMachine->Reset();
    }
}

/**
 * Get the current machine number
 * @return Machine number integer
 */
int ActualMachineSystem::GetMachineNumber()
{
    return mMachine->GetNumber();
}

/**
 * function for setting the time
 * @param time the time we are setting to
 */
void ActualMachineSystem::SetMachineTime(double time)
{
    mTime = time;
}

/**
 * Get the current machine time.
 * @return Machine time in seconds
 */
double ActualMachineSystem::GetMachineTime()
{
    return mTime;
}

/**
 * function for setting flags in the machine system
 * @param flag
 */
void ActualMachineSystem::SetFlag(int flag)
{

}

