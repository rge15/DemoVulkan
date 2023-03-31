#pragma once
#include <Engine/Resources/DemoFX.hpp>
#include <utilities/Timer/Timer.hpp>

//Clip Tuple of : Demo to play, starting point, final point
using Clip = Tuple<DemoFX&, float, float>;

//Playing clip of : Demo playing, relativePlayingTime
using PlayingClip = Tuple<DemoFX&, float>;

class DemoTrack
{
private:
    Vector<Clip> demoTrack_ {};

    float maxPlayTime_ { 0. };

public:

    explicit DemoTrack() = default;

    ~DemoTrack() = default;

    void
    addFXToTrack( DemoFX& p_demo, float p_timeStart, float p_duration ) noexcept;

    Vector<PlayingClip>
    getPlayingFXs() noexcept;

    inline
    float getMaxPlayTime() { return maxPlayTime_; };

};