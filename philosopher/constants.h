#pragma once

// Use explicit assignment here and in GLSL
// so we can easily ensure / verify alignment.
enum ItemState {
    PHILOSOPHER_THINKING = 0
,   PHILOSOPHER_WAITING  = 1
,   PHILOSOPHER_EATING   = 2
,   CHOPSTICK_FREE       = 4
,   CHOPSTICK_LEFT       = 5
,   CHOPSTICK_RIGHT      = 6
};
