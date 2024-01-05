/**
 * @file Scoreboard.h
 * @author Max Tetlow
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_SCOREBOARD_H
#define CANADIANEXPERIENCE_MACHINELIB_SCOREBOARD_H

class BasketballGoal;

/**
 * class for the scoreboard object of the goal
 */
class Scoreboard
{
private:

    ///Basketball goal the scoreboard belongs to
    BasketballGoal* mGoal = nullptr;

    ///the score on the score board
    int mScore = 0;

public:

    /// Assignment operator
    void operator=(const Scoreboard &) = delete;

    Scoreboard(int score);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    /**
     * Gets the score on the board
     * @return the score
     */
    int GetScore() {return mScore;}

    /**
     * sets the score for the board
     * @param score the score we are setting to
     */
    void SetScore(int score) {mScore = score;}

    void SetGoal(BasketballGoal* goal);

};

#endif //CANADIANEXPERIENCE_MACHINELIB_SCOREBOARD_H
