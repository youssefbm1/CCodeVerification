/**
 * @file TestLightControlSpy.c
 * @brief Unit tests for the LightControlSpy module.
 *
 * This file contains unit tests for the LightControlSpy module.
 * The tests verify the behavior of the LightControlSpy module
 * by checking the last light ID and state changes recorded by the spy.
 */

#include "LightControlSpy.h" 
#include "unity.h" 

void testLightControlSpyReturnsLastStateChange(void) 
{ 
    LightControl_init(); 
    LightControl_on(42); 
    
    TEST_ASSERT_EQUAL( 42, LightControlSpy_getLastLightId() ); 
    TEST_ASSERT_EQUAL( LIGHT_ON, LightControlSpy_getLastState() ); 

    LightControl_destroy(); 
}

void testLightControlOffState(void)
{
    LightControl_init();
    LightControl_off(33);
    
    TEST_ASSERT_EQUAL_INT( 33, LightControlSpy_getLastLightId() );
    TEST_ASSERT_EQUAL_INT( LIGHT_OFF, LightControlSpy_getLastState() );

    LightControl_destroy();
}

void testStateUnknownInit(void)
{
    LightControl_init();

    TEST_ASSERT_EQUAL_INT( LIGHT_ID_UNKNOWN, LightControlSpy_getLastLightId() );
    TEST_ASSERT_EQUAL_INT( LIGHT_STATE_UNKNOWN, LightControlSpy_getLastState() );

    LightControl_destroy();
}