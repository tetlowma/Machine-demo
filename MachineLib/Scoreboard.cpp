/**
 * @file Scoreboard.cpp
 * @author Max Tetlow
 */

#include "pch.h"
#include "Scoreboard.h"
#include "BasketballGoal.h"

#include <iostream>
#include <iomanip>
#include <sstream>

/// The color of the scoreboard background
const auto ScoreboardBackgroundColor = wxColor(24, 69, 59);

/// Width of the black line around the scoreboard
const int ScoreboarderLineWidth = 3;

/// Scoreboard font size (height) in cm
/// The font color is white
const int ScoreboardFontSize = 20;

/// Rectangle that represents the location relative to the
/// goal position for the scoreboard and its size.
const auto ScoreboardRectangle = wxRect(5, 280, 30, 20);

/// Location of the scoreboard text relative to the
/// scoreboard location in cm.
const auto ScoreboardTextLocation = wxPoint(9, 299);

/**
 * constructor for the scoreboard
 * @param score the score for the board
 */
Scoreboard::Scoreboard(int score)
{
    mScore = score;
}

/**
 * function that draws the scoreboard
 * @param graphics the graphics context for drawing
 */
void Scoreboard::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();

    auto point = mGoal->GetPosition();
    auto dp = point + wxPoint(ScoreboardRectangle.x , ScoreboardRectangle.y);
    // Set the background color
    graphics->SetBrush(wxBrush(ScoreboardBackgroundColor));
    graphics->DrawRectangle(dp.x , dp.y, ScoreboardRectangle.width, ScoreboardRectangle.height);

    // Draw the black border around the scoreboard
    graphics->SetPen(wxPen(wxColour(0, 0, 0), ScoreboarderLineWidth));
    graphics->DrawRectangle(dp.x, dp.y, ScoreboardRectangle.width, ScoreboardRectangle.height);

    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << mScore;
    std::string scoreString = oss.str();

    // Set the font for the scoreboard text
    wxFont font(ScoreboardFontSize, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    graphics->SetFont(font, wxColour(255, 255, 255));


    graphics->Translate( ScoreboardTextLocation.x/2 +dp.x , ScoreboardTextLocation.y);
    graphics->Scale(1, -1);
    // Draw the scoreboard text
    graphics->DrawText(scoreString,0,0);

    graphics->PopState();
}

/**
 * function that sets the goal the scoreboard belongs to
 * @param goal the goal the bord belongs to
 */
void Scoreboard::SetGoal(BasketballGoal *goal)
{
    mGoal = goal;
}