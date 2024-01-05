/**
 * @file Machine1Factory.cpp
 * @author Charles Owen
 */

#include "pch.h"
#include "Machine1Factory.h"
#include "Machine.h"
#include "Body.h"
#include "BasketballGoal.h"
#include "Hamster.h"
#include "Conveyor.h"
#include "HamsterAndConveyorFactory.h"

/// The images directory in resources
const std::wstring ImagesDirectory = L"/images";


/**
 * Constructor
 * @param resourcesDir Path to the resources directory
 */
Machine1Factory::Machine1Factory(std::wstring resourcesDir) :
    mResourcesDir(resourcesDir)
{
    mImagesDir = mResourcesDir + ImagesDirectory;
}



/**
 * Factory method to create machine #1
 * @return
 */
std::shared_ptr<Machine> Machine1Factory::Create()
{
    // The machine itself
    // In this solution the machine number is passed
    // to the working machine constructor, so it knows
    // its number.
    auto machine = std::make_shared<Machine>(1);

    // Notice: All dimensions are in centimeters and assumes
    // the Y axis is positive in the up direction.

    const double FloorWidth = 600;
    const double FloorHeight = 15;

    //
    // The floor
    //
    // The values are chosen so the top of the floor
    // is at Y=0
    //
    auto floor = std::make_shared<Body>();
    floor->GetPolygon()->Rectangle(-FloorWidth/2, -FloorHeight, FloorWidth, FloorHeight);
    floor->GetPolygon()->SetImage(mImagesDir + L"/floor.png");
    machine->AddComponent(floor);

    //
    // Create the top beam and the basketball
    // that rolls off of it
    //
    TopBeamAndRamp(machine);

    //
    // Create the beam with the hamster driving a
    // spinning arm that hits the ball to make it roll
    //
    BeamAndSpinningArm(machine);

    //
    // Create a stack of dominos
    //
    const auto DominoStack1Position = wxPoint2DDouble(-230, 0);

    DominoStack(machine, DominoStack1Position);

    //
    // Create another stack of dominos
    //
    const auto DominoStack2Position = wxPoint2DDouble(115, 0);

    DominoStack(machine, DominoStack2Position);

    //
    // Create a factory that will manufacture hamster, pulley,
    // pulley, and conveyor assemblies
    //
    HamsterAndConveyorFactory hamsterAndConveyorFactory(machine, mImagesDir);

    //
    // First conveyor with a ball sitting on it
    //
    hamsterAndConveyorFactory.Create(wxPoint(240, 0), wxPoint(100, 90));
    hamsterAndConveyorFactory.AddBall(40);
    auto hamster1 = hamsterAndConveyorFactory.GetHamster();
    auto conveyor1 = hamsterAndConveyorFactory.GetConveyor();
    hamster1->SetSpeed(-1);

    //
    // Second conveyor with a ball on it
    //
    wxPoint conveyor2position(-230, 130);

    // Dominos on a beam that the conveyor ball will knock down.
    // Add this first, so it is behind the second conveyor pulleys
    DominoesOnBeam(machine, conveyor2position + wxPoint(140, 0));

    hamsterAndConveyorFactory.Create(conveyor1->GetPosition() + wxPoint(-105, -40), conveyor2position);
    hamsterAndConveyorFactory.AddBall(-40);
    auto hamster2 = hamsterAndConveyorFactory.GetHamster();
    auto conveyor2 = hamsterAndConveyorFactory.GetConveyor();

    //
    // Third hamster/conveyor assembly.
    //
    wxPoint conveyor3position(150, 200);

    hamsterAndConveyorFactory.Create(conveyor2position + wxPoint(260, 20), conveyor3position);
    hamsterAndConveyorFactory.AddBall(-40);
    auto hamster3 = hamsterAndConveyorFactory.GetHamster();
    hamster3->SetSpeed(1.5);
    auto conveyor3 = hamsterAndConveyorFactory.GetConveyor();

    //
    // We add the basketball goal last, so all basketballs
    // will draw behind it.
    //
    Goal(machine);

    return machine;
}



/**
 * Generate the top beam and its basketball
 *
 * The top beam and ramp and basketball that
 * rolls right and goes through the hoop.
 * @param machine Beam to generate
 */
void Machine1Factory::TopBeamAndRamp(std::shared_ptr<Machine> machine)
{
    const double BeamX = -25;
    auto beam1 = std::make_shared<Body>();
    beam1->GetPolygon()->BottomCenteredRectangle(400, 20);
    beam1->GetPolygon()->SetImage(mImagesDir + L"/beam.png");
    beam1->GetPolygon()->SetInitialPosition(BeamX, 300);
    machine->AddComponent(beam1);

    auto wedge1 = std::make_shared<Body>();
    wedge1->GetPolygon()->AddPoint(-25, 0);
    wedge1->GetPolygon()->AddPoint(25, 0);
    wedge1->GetPolygon()->AddPoint(25, 4.5);
    wedge1->GetPolygon()->AddPoint(-25, 25);
    wedge1->GetPolygon()->SetImage(mImagesDir + L"/wedge.png");
    wedge1->GetPolygon()->SetInitialPosition(BeamX-175, 320);
    machine->AddComponent(wedge1);

    // Basketball 1
    auto basketball1 = std::make_shared<Body>();
    basketball1->GetPolygon()->Circle(12);
    basketball1->GetPolygon()->SetImage(mImagesDir + L"/basketball1.png");
    basketball1->GetPolygon()->SetInitialPosition(BeamX-186, 353);
    basketball1->GetPolygon()->SetDynamic();
    basketball1->GetPolygon()->SetPhysics(1, 0.5, 0.6);
    machine->AddComponent(basketball1);
}

/**
 * Create a stack of 9 dominos.
 * @param machine Machine to add to
 * @param position The position to draw the domino stack at
 */
void Machine1Factory::DominoStack(std::shared_ptr<Machine> machine, wxPoint2DDouble position)
{
    Domino(machine, position + wxPoint2DDouble(30, DominoHeight/2), 0, DominoColor::Red);
    Domino(machine, position + wxPoint2DDouble(10, DominoHeight/2), 0, DominoColor::Blue);
    Domino(machine, position + wxPoint2DDouble(20, DominoHeight + DominoWidth/2), 0.25, DominoColor::Green);

    Domino(machine, position + wxPoint2DDouble(-10, DominoHeight/2), 0, DominoColor::Red);
    Domino(machine, position + wxPoint2DDouble(-30, DominoHeight/2), 0, DominoColor::Green);
    Domino(machine, position + wxPoint2DDouble(-20, DominoHeight + DominoWidth/2), 0.25, DominoColor::Black);

    const int DominoLevel2 = DominoHeight + DominoWidth;

    Domino(machine, position + wxPoint2DDouble(10, DominoLevel2 + DominoHeight/2), 0, DominoColor::Red);
    Domino(machine, position + wxPoint2DDouble(-10, DominoLevel2 + DominoHeight/2), 0, DominoColor::Green);
    Domino(machine, position + wxPoint2DDouble(0, DominoLevel2 + DominoHeight + DominoWidth/2), 0.25, DominoColor::Black);
}

/**
 * This is the second beam from the top and the spinning arm that hits the ball
 * @param machine Machine to add to
 */
void Machine1Factory::BeamAndSpinningArm(std::shared_ptr<Machine> machine)
{
    const double Beam2X = -25;
    auto beam2 = std::make_shared<Body>();
    beam2->GetPolygon()->BottomCenteredRectangle(400, 20);
    beam2->GetPolygon()->SetImage(mImagesDir + L"/beam.png");
    beam2->GetPolygon()->SetInitialPosition(Beam2X, 240);
    machine->AddComponent(beam2);

    // Basketball 2
    auto basketball2 = std::make_shared<Body>();
    basketball2->GetPolygon()->Circle(12);
    basketball2->GetPolygon()->SetImage(mImagesDir + L"/basketball2.png");
    basketball2->GetPolygon()->SetInitialPosition(Beam2X - 170, 240 + 12 + 20);
    basketball2->GetPolygon()->SetDynamic();
    basketball2->GetPolygon()->SetPhysics(1, 0.5, 0.75);
    machine->AddComponent(basketball2);

    //
    // The hamster motor for the second-beam
    //
    auto hamster = std::make_shared<Hamster>(mImagesDir);
    hamster->SetPosition(-220, 185);
    hamster->SetInitiallyRunning(true);      // Initially running
    hamster->SetSpeed(0.60);
    machine->AddComponent(hamster);
    auto hamster1shaft = hamster->GetShaftPosition();

    auto arm = std::make_shared<Body>();
    arm->GetPolygon()->SetInitialPosition(hamster1shaft.x, hamster1shaft.y);
    arm->GetPolygon()->AddPoint(-7, 10);
    arm->GetPolygon()->AddPoint(7, 10);
    arm->GetPolygon()->AddPoint(7, -60);
    arm->GetPolygon()->AddPoint(-7, -60);
    arm->GetPolygon()->SetImage(mImagesDir + L"/arm.png");
    arm->GetPolygon()->SetKinematic();
    machine->AddComponent(arm);

    hamster->GetSource()->AddSink(arm);
}

/**
 * Add the basketball goal to the machine
 * @param machine Machine to add to
 */
void Machine1Factory::Goal(std::shared_ptr<Machine> machine)
{
    auto goal = std::make_shared<BasketballGoal>(mImagesDir);
    goal->SetPosition(270, 0);
    machine->AddComponent(goal);
}

/**
 * Create the beam that has 10 dominoes on it.
 * @param machine Machine to add bem to
 * @param position Location to place the beam.
 */
void Machine1Factory::DominoesOnBeam(std::shared_ptr<Machine> machine, wxPoint position)
{
    // The beam the dominoes sit on
    auto beam = std::make_shared<Body>();
    beam->GetPolygon()->BottomCenteredRectangle(150, 15);
    beam->GetPolygon()->SetImage(mImagesDir + L"/beam.png");
    beam->GetPolygon()->SetInitialPosition(position.x, position.y);
    machine->AddComponent(beam);

    for(int d=0; d<10; d++)
    {
        // Where to put this domino
        auto dominos = position + wxPoint2DDouble(-70 + d * 15, 27);

        Domino(machine, dominos, 0, DominoColor::Green);
    }
}


/**
 * Create a Domino and add it to the machine.
 *
 * This has been created to make it easier to create
 * a lot of dominos
 *
 * @param machine Machine to add the domino to
 * @param position Position to place the center of the domino
 * @param rotation Rotation in turns
 * @param color Color code
 * @return Returns the created domino body
 */
std::shared_ptr<Body>  Machine1Factory::Domino(std::shared_ptr<Machine> machine, wxPoint2DDouble position, double rotation, DominoColor color)
{
    auto x = position.m_x;
    auto y = position.m_y;

    auto domino = std::make_shared<Body>();
    domino->GetPolygon()->Rectangle(-DominoWidth/2, -DominoHeight/2, DominoWidth, DominoHeight);
    switch(color)
    {
        case DominoColor::Black:
            domino->GetPolygon()->SetImage(mImagesDir + L"/domino-black.png");
            break;

        case DominoColor::Red:
            domino->GetPolygon()->SetImage(mImagesDir + L"/domino-red.png");
            break;

        case DominoColor::Green:
            domino->GetPolygon()->SetImage(mImagesDir + L"/domino-green.png");
            break;

        case DominoColor::Blue:
            domino->GetPolygon()->SetImage(mImagesDir + L"/domino-blue.png");
            break;
    }

    domino->GetPolygon()->SetInitialPosition(x, y);
    domino->GetPolygon()->SetInitialRotation(rotation);
    domino->GetPolygon()->SetDynamic();
    machine->AddComponent(domino);

    return domino;
}

