/**
 * @file HamsterAndConveyorFactory.h
 * @author Max Tetlow
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_HAMSTERANDCONVEYORFACTORY_H
#define CANADIANEXPERIENCE_MACHINELIB_HAMSTERANDCONVEYORFACTORY_H

class Machine;
class Hamster;
class Conveyor;
class Body;

/**
 * Factory that creates a Hamster to drive and a
 * conveyor belt connected by two pulleys.
 *
 * Since the example machine has three of these combinations we
 * use this factory that creates a hamster, conveyor, and the
 * pulley combinations to drive the conveyor.
 *
 */
class HamsterAndConveyorFactory
{
private:
    /// The machine we are adding these components to
    std::shared_ptr<Machine> mMachine;

    /// The directory for the images
    std::wstring mImagesDir;

    /// The hamster wheel
    std::shared_ptr<Hamster> mHamster;

    /// The conveyor
    std::shared_ptr<Conveyor> mConveyor;

public:
    /**
     * Constructor
     * @param machine The Machine to add the components to
     * @param imagesDir Directory containing the images
     */
    HamsterAndConveyorFactory(std::shared_ptr<Machine> machine, std::wstring imagesDir) :
        mMachine(machine), mImagesDir(imagesDir) {}

    /// Default constructor (disabled)
    HamsterAndConveyorFactory() = delete;

    /// Copy constructor (disabled)
    HamsterAndConveyorFactory(const HamsterAndConveyorFactory &) = delete;

    /// Assignment operator
    void operator=(const HamsterAndConveyorFactory &) = delete;

    void Create(wxPoint hamsterPosition, wxPoint conveyorPosition);

    std::shared_ptr<Body> AddBall(double placement);

    /**
     * Get the constructed Hamster object
     * @return Hamster object
     */
    std::shared_ptr<Hamster> GetHamster() {return mHamster;}

    /**
     * Get the constructed Conveyor object
     * @return Conveyor object
     */
    std::shared_ptr<Conveyor> GetConveyor() {return mConveyor;}
};

#endif //CANADIANEXPERIENCE_MACHINELIB_HAMSTERANDCONVEYORFACTORY_H
