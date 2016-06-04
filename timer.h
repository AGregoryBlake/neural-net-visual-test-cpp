//
//  Timer.h
//  Tools/Core
//

#ifndef Tools_Core_Timer_h
#define Tools_Core_Timer_h


// ================================================================================ Standard Includes
// Standard Includes
// --------------------------------------------------------------------------------
#include <chrono>


namespace Core
{
    // ============================================================================ SmartWrapper
    // Timer
    //
    // A basic timer utility
    // ----------------------------------------------------------------------------
    class Timer
    {
    public:
        // -------------------------------------------------------------------- Types
        using Clock_t     = std::chrono::high_resolution_clock;
        using Timepoint_t = std::chrono::time_point< Clock_t >;
        using Duration_t  = std::chrono::duration< double >;

    private:
        // -------------------------------------------------------------------- State
        Timepoint_t _start;


    public:
        // ==================================================================== Construct
        // Construct
        // -------------------------------------------------------------------- Construct ( default )
        Timer() : _start( Clock_t::now() ) {}


    public:
        // ==================================================================== Public API
        // Public API
        // -------------------------------------------------------------------- Restart()
        void Restart()
        {
            _start = Clock_t::now();
        }

        // -------------------------------------------------------------------- Elapsed()
        double Elapsed_Seconds()
        {
            Timepoint_t end      = Clock_t::now();
            Duration_t  duration = end - _start;

            return duration.count();
        }
    };
}

#endif