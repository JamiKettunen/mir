/*
 * Copyright (C) 2005 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

//
// Timer functions.
//
#ifndef _LIBS_UTILS_TIMERS_H
#define _LIBS_UTILS_TIMERS_H

#include <stdint.h>
#include <sys/types.h>
#include <sys/time.h>
#include <chrono>

// ------------------------------------------------------------------
// C API

#ifdef __cplusplus
extern "C" {
#endif

typedef int64_t nsecs_t;

static inline std::chrono::nanoseconds seconds_to_nanoseconds(std::chrono::nanoseconds secs)
{
    return secs*1000000000;
}

static inline std::chrono::nanoseconds milliseconds_to_nanoseconds(std::chrono::nanoseconds secs)
{
    return secs*1000000;
}

static inline std::chrono::nanoseconds microseconds_to_nanoseconds(std::chrono::nanoseconds secs)
{
    return secs*1000;
}

static inline std::chrono::nanoseconds nanoseconds_to_seconds(std::chrono::nanoseconds secs)
{
    return secs/1000000000;
}

static inline std::chrono::nanoseconds nanoseconds_to_milliseconds(std::chrono::nanoseconds secs)
{
    return secs/1000000;
}

static inline std::chrono::nanoseconds nanoseconds_to_microseconds(std::chrono::nanoseconds secs)
{
    return secs/1000;
}

static inline std::chrono::nanoseconds s2ns(std::chrono::nanoseconds v)  {return seconds_to_nanoseconds(v);}
static inline std::chrono::nanoseconds ms2ns(std::chrono::nanoseconds v) {return milliseconds_to_nanoseconds(v);}
static inline std::chrono::nanoseconds us2ns(std::chrono::nanoseconds v) {return microseconds_to_nanoseconds(v);}
static inline std::chrono::nanoseconds ns2s(std::chrono::nanoseconds v)  {return nanoseconds_to_seconds(v);}
static inline std::chrono::nanoseconds ns2ms(std::chrono::nanoseconds v) {return nanoseconds_to_milliseconds(v);}
static inline std::chrono::nanoseconds ns2us(std::chrono::nanoseconds v) {return nanoseconds_to_microseconds(v);}

static inline std::chrono::nanoseconds seconds(std::chrono::nanoseconds v)      { return s2ns(v); }
static inline std::chrono::nanoseconds milliseconds(std::chrono::nanoseconds v) { return ms2ns(v); }
static inline std::chrono::nanoseconds microseconds(std::chrono::nanoseconds v) { return us2ns(v); }

enum {
    SYSTEM_TIME_REALTIME = 0,  // system-wide realtime clock
    SYSTEM_TIME_MONOTONIC = 1, // monotonic time since unspecified starting point
    SYSTEM_TIME_PROCESS = 2,   // high-resolution per-process clock
    SYSTEM_TIME_THREAD = 3     // high-resolution per-thread clock
};
    
// return the system-time according to the specified clock
#ifdef __cplusplus
std::chrono::nanoseconds systemTime(int clock = SYSTEM_TIME_MONOTONIC);
#else
std::chrono::nanoseconds systemTime(int clock);
#endif // def __cplusplus

/**
 * Returns the number of milliseconds to wait between the reference time and the timeout time.
 * If the timeout is in the past relative to the reference time, returns 0.
 * If the timeout is more than INT_MAX milliseconds in the future relative to the reference time,
 * such as when timeoutTime == LLONG_MAX, returns -1 to indicate an infinite timeout delay.
 * Otherwise, returns the difference between the reference time and timeout time
 * rounded up to the next millisecond.
 */
int toMillisecondTimeoutDelay(std::chrono::nanoseconds referenceTime, std::chrono::nanoseconds timeoutTime);

#ifdef __cplusplus
} // extern "C"
#endif

// ------------------------------------------------------------------
// C++ API

#ifdef __cplusplus

namespace android {
/*
 * Time the duration of something.
 *
 * Includes some timeval manipulation functions.
 */
class DurationTimer {
public:
    DurationTimer() {}
    ~DurationTimer() {}

    // Start the timer.
    void start();
    // Stop the timer.
    void stop();
    // Get the duration in microseconds.
    long long durationUsecs() const;

    // Subtract two timevals.  Returns the difference (ptv1-ptv2) in
    // microseconds.
    static long long subtractTimevals(const struct timeval* ptv1,
        const struct timeval* ptv2);

    // Add the specified amount of time to the timeval.
    static void addToTimeval(struct timeval* ptv, long usec);

private:
    struct timeval  mStartWhen;
    struct timeval  mStopWhen;
};

} // android
#endif // def __cplusplus

#endif // _LIBS_UTILS_TIMERS_H
