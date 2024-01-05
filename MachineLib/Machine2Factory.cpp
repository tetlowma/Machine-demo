/**
 * @file Machine2Factory.cpp
 * @author Max Tetlow
 */

#include "pch.h"
#include "Machine2Factory.h"
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
 * @param resourcesDir Directory containing the machine resources
 */
Machine2Factory::Machine2Factory(std::wstring resourcesDir):mResourcesDir(resourcesDir)
{
    mImagesDir = resourcesDir + ImagesDirectory;
}

/**
 * function to create the second machine
 * @return
 */
std::shared_ptr<Machine> Machine2Factory::Create()
{
    auto machine = std::make_shared<Machine>(2);

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
    // add the basketball goal last, so all basketballs
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
void Machine2Factory::TopBeamAndRamp(std::shared_ptr<Machine> machine)
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

    //another basketball
    auto basketball4 = std::make_shared<Body>();
    basketball4->GetPolygon()->Circle(12);
    basketball4->GetPolygon()->SetImage(mImagesDir + L"/basketball1.png");
    basketball4->GetPolygon()->SetInitialPosition(BeamX-186, 390);
    basketball4->GetPolygon()->SetDynamic();
    basketball4->GetPolygon()->SetPhysics(1, 0.5, 0.6);
    machine->AddComponent(basketball4);
}

/**
 * This is the second beam from the top and the spinning arm that hits the ball
 * @param machine Machine to add to
 */
void Machine2Factory::BeamAndSpinningArm(std::shared_ptr<Machine> machine)
{
    const double Beam2X = -25;

    // Basketball 2
    auto basketball2 = std::make_shared<Body>();
    basketball2->GetPolygon()->Circle(12);
    basketball2->GetPolygon()->SetImage(mImagesDir + L"/basketball2.png");
    basketball2->GetPolygon()->SetInitialPosition(Beam2X + 305, 240 + 12 + 20);
    basketball2->GetPolygon()->SetDynamic();
    basketball2->GetPolygon()->SetPhysics(1, 0.5, 0.75);
    machine->AddComponent(basketball2);

    //
    // The hamster motor for the second-beam
    //
    auto hamster = std::make_shared<Hamster>(mImagesDir);
    hamster->SetPosition(-50, 0 + 12 + 20);
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

    // Basketball 3
    auto basketball3 = std::make_shared<Body>();
    basketball3->GetPolygon()->Circle(12);
    basketball3->GetPolygon()->SetImage(mImagesDir + L"/basketball2.png");
    basketball3->GetPolygon()->SetInitialPosition(Beam2X, 0 + 12 + 20);
    basketball3->GetPolygon()->SetDynamic();
    basketball3->GetPolygon()->SetPhysics(1, 0.5, 0.75);
    machine->AddComponent(basketball3);
}

/**
 * Add the basketball goal to the machine
 * @param machine Machine to add to
 */
void Machine2Factory::Goal(std::shared_ptr<Machine> machine)
{
    auto goal = std::make_shared<BasketballGoal>(mImagesDir);
    goal->SetPosition(270, 0);
    machine->AddComponent(goal);
}