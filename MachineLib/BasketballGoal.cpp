/**
 * @file BasketballGoal.cpp
 * @author Max Tetlow
 */

#include "pch.h"
#include "BasketballGoal.h"
#include "b2_contact.h"
#include "Scoreboard.h"

/// Image to draw for the goal
const std::wstring GoalImage = L"/goal.png";

/// Size to draw the entire goal post image
/// This does not go into the physics system at all
const auto GoalSize = wxSize(65, 247);

/// Size to create a rectangle in the physics system only
/// (does not draw) to reflect off of the backboard and post
const auto PostSize = wxSize(10, 250);

/// Size of a target object inside the goal net that
/// we'll consider a score when touched by a ball
const auto TargetSize = wxSize(20, 5);

/// Position of the goalpost polygon relative to the entire goal
/// This plus the location set by SetPosition is where to draw
/// the goalpost PhysicsPolygon object.
const wxPoint PostPosition = wxPoint(22, 0);

/// Position of the basket goal polygon relative to the entire goal
/// This plus the location set by SetPosition is where to draw
/// the goalpost PhysicsPolygon object.
const wxPoint GoalPosition = wxPoint(-12, 165);

/**
 * constructor for the basketball goal object
 * @param imagesDir the location of the images for this object
 */
BasketballGoal::BasketballGoal(std::wstring imagesDir)
{

    mPolygon.BottomCenteredRectangle(GoalSize);
    mPolygon.SetImage(imagesDir + GoalImage);

    mPost.BottomCenteredRectangle(PostSize);
    mPost.SetColor(*wxBLUE);

    mGoal.BottomCenteredRectangle(TargetSize);
    mGoal.SetColor(*wxBLUE);

    StartScoreboard();
}

/**
 * function that sets the position of the basketball goal
 * @param x the x coordinate of the location
 * @param y the y coordinate if the location
 */
void BasketballGoal::SetPosition(int x, int y)
{
    mLocation = wxPoint(x, y);
    auto pPosition = mLocation + PostPosition;
    auto gPosition = mLocation + GoalPosition;
    mPost.SetInitialPosition(pPosition.x , pPosition.y);
    mGoal.SetInitialPosition( gPosition.x, gPosition.y);
}

/**
 * function that draws the basketball goal
 * @param graphics the graphics context for drawing
 */
void BasketballGoal::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{

    mPolygon.DrawPolygon(graphics, mLocation.x, mLocation.y, 0);
    //mPost.Draw(graphics);
    //mGoal.Draw(graphics);
    mScoreboard.Draw(graphics);
}

/**
 * Handle a contact beginning
 * @param contact Contact object
 */
void BasketballGoal::BeginContact(b2Contact *contact)
{
    //increase the score on the board by 2
    auto score = mScoreboard.GetScore();
    score += 2;
    mScoreboard.SetScore(score);
}

/**
 * Handle before the solution of a contact with the
 * scoreboard target object. We take this time to
 * turn off the contact, so the ball will pass through.
 * @param contact Contqct object
 * @param oldManifold Manifold object
 */
void BasketballGoal::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
{
    contact->SetEnabled(false);
}

/**
 * sets the physics in the physics
 * @param listen the contact listener in the physics world
 * @param world the physics world we are adding this object to
 */
void BasketballGoal::SetPhysic( std::shared_ptr<ContactListener> listen, std::shared_ptr<b2World> world)
{
    mGoal.InstallPhysics(world);
    listen->Add(mGoal.GetBody(), this);
    mPost.InstallPhysics(world);
    StartScoreboard();
}

/**
 * Getter for the polygon in this function
 * @return nothing
 */
cse335::PhysicsPolygon* BasketballGoal::GetPolygon()
{
    return nullptr;
}

/**
 * function that starts and links that scoreboard to this goal
 */
void BasketballGoal::StartScoreboard()
{
    mScoreboard.SetScore(0);
    mScoreboard.SetGoal(this);
}
