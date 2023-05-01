#pragma once
#include <Engine/Resources/DemoFX.hpp>
#include <utilities/Timer/Timer.hpp>
#include <utilities/Engine/engineTypeAlias.hpp>

//! Clip Tuple of : Demo to play, starting point, final point
using Clip = Tuple<DemoFX&, float, float>;

//! Playing clip of : Demo playing, relativePlayingTime
using PlayingClip = Tuple<DemoFX&, float>;

/**
 * @brief Class that acts like a Track/Queue of all the DemoFX to play 
 */
class DemoTrack
{
private:
    //! Vector managing all the DemoFX to play
    Vector<Clip> demoTrack_ {};

    //! Duration of entire track in seconds
    float maxPlayTime_ { 0. };

public:

    /**
     * @brief Construct a new default Demo Track object
     */
    explicit DemoTrack() = default;

    /**
     * @brief Destroy the Demo Track object
     */
    ~DemoTrack() = default;

    /**
     * @brief Adds a new demo to the queue to be played
     * 
     * @param p_demo Reference to a demo to play
     * @param p_timeStart Start time in seconds to start playing the FX
     * @param p_duration Duration time in seconds of the FX
     */
    void
    addFXToTrack( DemoFX& p_demo, float p_timeStart, float p_duration ) noexcept;

    /**
     * @brief Get the current Playing FXs
     * 
     * @return Vector<PlayingClip> Vector with all relative data of the  playing FXs
     */
    Vector<PlayingClip>
    getPlayingFXs() noexcept;

    /**
     * @brief Get the DUration of the entire track
     * 
     * @return float Duration in seconds of entire track
     */
    inline
    float getMaxPlayTime() { return maxPlayTime_; };

};