#include "LightControlSpy.h"
#include <stdlib.h>

typedef struct LightControlSpy
{
   int id;
   int state;
}LightControlSpy;

LightControlSpy lastLight;

/**
 * @brief Initializes the Light Control module.
 * 
 * This function sets the initial values for the lastLight structure.
 * It sets the id to LIGHT_ID_UNKNOWN and the state to LIGHT_STATE_UNKNOWN.
 */
void LightControl_init(void) {
    lastLight.id = LIGHT_ID_UNKNOWN;
    lastLight.state = LIGHT_STATE_UNKNOWN;
    return;
}

/**
 * @brief Destroys the Light Control module.
 * 
 * This function does not perform any specific action.
 * It is provided for completeness and can be used for cleanup if needed.
 */
void LightControl_destroy(void) {
    // No specific action required for destruction
}

/**
 * @brief Turns on the specified light.
 * 
 * This function updates the lastLight structure with the provided id and sets the state to LIGHT_ON.
 * 
 * @param id The id of the light to turn on.
 */
void LightControl_on(int id) {
    lastLight.id = id;
    lastLight.state = LIGHT_ON;
    return;
}

/**
 * @brief Turns off the specified light.
 * 
 * This function updates the lastLight structure with the provided id and sets the state to LIGHT_OFF.
 * 
 * @param id The id of the light to turn off.
 */
void LightControl_off(int id) {
    lastLight.id = id;
    lastLight.state = LIGHT_OFF;
    return;
}

/**
 * @brief Gets the id of the last light that was controlled.
 * 
 * This function returns the id of the last light that was turned on or off using the LightControl module.
 * 
 * @return The id of the last light.
 */
int LightControlSpy_getLastLightId(void) {
    return lastLight.id;
}

/**
 * @brief Gets the state of the last light that was controlled.
 * 
 * This function returns the state of the last light that was turned on or off using the LightControl module.
 * 
 * @return The state of the last light (LIGHT_ON or LIGHT_OFF).
 */
int LightControlSpy_getLastState(void) {
    return lastLight.state;
}