#include "DemoTrack.hpp"

void
DemoTrack::addFXToTrack( DemoFX& p_demo, float p_timeStart, float p_duration ) noexcept
{
    float endClipTime { p_timeStart + p_duration };

    Clip clip = Clip( p_demo, p_timeStart, endClipTime);

    if( maxPlayTime_ < endClipTime )
        maxPlayTime_ = endClipTime;

    demoTrack_.push_back(clip);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

Vector<PlayingClip>
DemoTrack::getPlayingFXs() noexcept
{
    double ellapsedTime = Timer::getInstance().ellapsedSeconds();
    Vector<PlayingClip> clips {};

    for( auto& clip : demoTrack_ )
    {
        float timeStartPoint    = std::get<1>(clip);
        float timeEndPoint      = std::get<2>(clip);
        
        if(timeStartPoint < ellapsedTime && ellapsedTime < timeEndPoint)
        {
            float   relativeTime = ellapsedTime - timeStartPoint;
            DemoFX& demoFX = std::get<0>(clip);

            PlayingClip playingClip = PlayingClip( demoFX, relativeTime );
            clips.push_back(playingClip );
        }
    }

    return clips;
}
