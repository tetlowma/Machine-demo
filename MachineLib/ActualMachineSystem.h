/**
 * @file ActualMachineSystem.h
 * @author Max Tetlow
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_ACTUALMACHINESYSTEM_H
#define CANADIANEXPERIENCE_MACHINELIB_ACTUALMACHINESYSTEM_H

#include "IMachineSystem.h"

class Machine;
/**
 * class that represents that actual machine system
 */
class ActualMachineSystem: public IMachineSystem
{
private:

    /// How many pixels there are for each CM
    double mPixelsPerCentimeter = 1.5;

    /// The Machine in the machine system
    std::shared_ptr<Machine> mMachine;

    /// The Location of the machine system
    wxPoint mLocation;

    ///resources directory for images in machine system
    std::wstring mResourcesDir;

    /// The current frame we are on in the machine system
    int mFrame;

    ///The frame rate
    double mFrameRate;

    /// The current time in the machine system
    double mTime;

public:

    /// Constructor
    ActualMachineSystem(std::wstring resourcesDir);

    /// Copy constructor (disabled)
    ActualMachineSystem(const ActualMachineSystem &) = delete;

    /// Assignment operator
    void operator=(const ActualMachineSystem &) = delete;

    virtual void SetLocation(wxPoint location) override;

    virtual wxPoint GetLocation() override;

    virtual void DrawMachine(std::shared_ptr<wxGraphicsContext> graphics) override;

    virtual void SetMachineFrame(int frame) override;

    virtual void SetFrameRate(double rate) override;

    void SetMachineNumber(int machine) override;

    virtual int GetMachineNumber() override;

    virtual void SetMachineTime(double time);

    virtual double GetMachineTime() override;

    virtual void SetFlag(int flag) override;

    //void SetMachine(std::shared_ptr<Machine> machine);

};

#endif //CANADIANEXPERIENCE_MACHINELIB_ACTUALMACHINESYSTEM_H
