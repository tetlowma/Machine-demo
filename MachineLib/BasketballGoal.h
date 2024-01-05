/**
 * @file BasketballGoal.h
 * @author Max Tetlow
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_BASKETBALLGOAL_H
#define CANADIANEXPERIENCE_MACHINELIB_BASKETBALLGOAL_H

#include "Component.h"
#include "PhysicsPolygon.h"
#include "Polygon.h"
#include "b2_world_callbacks.h"
#include "ContactListener.h"
#include "Scoreboard.h"

/**
 * the class the represent the basketball goal
 */
class BasketballGoal :  public Component, public b2ContactListener
{
private:

    /// the scoreboard
    Scoreboard mScoreboard = Scoreboard(0);

    /// The polygon that draws the goal
    cse335::Polygon mPolygon;

    /// The physics polygon that represents the goal post
    cse335::PhysicsPolygon mPost ;

    /// the physics polygon for detecting when the boal goes through the goal
    cse335::PhysicsPolygon mGoal;

    ///the location of the goal
    wxPoint mLocation;

public:

    ///constuctor
    BasketballGoal(std::wstring imagesDir);

    void SetPosition(int x, int y);

    /**
     * Get the position of the basketball goal
     * @return the point that represents the location of the basketball goal
     */
    wxPoint GetPosition() override {return mLocation;}

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void BeginContact(b2Contact *contact) override;
    void PreSolve(b2Contact *contact, const b2Manifold *oldManifold) override;
    void SetPhysic(std::shared_ptr<ContactListener> listen, std::shared_ptr<b2World> world) override;
    void StartScoreboard();
    cse335::PhysicsPolygon * GetPolygon() override;

};

#endif //CANADIANEXPERIENCE_MACHINELIB_BASKETBALLGOAL_H
