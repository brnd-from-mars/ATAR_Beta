#include <avr/interrupt.h>
#include <util/delay.h>

#include "mcu/io/DigitalInputPin.hpp"

#include "mcu/io/AnalogInputController.hpp"
#include "mcu/io/AnalogInputPin.hpp"

#include "mcu/usart/UARTConnection.hpp"

#include "periph/LightEmittingDiode.hpp"
#include "periph/Acceleromter.hpp"


int main ()
{
    // TODO: interrupt handler
    UARTConnection uartCentral(0, 38400);

    SingleColorLED ledHeartbeat;
    ledHeartbeat.RegisterPin(&PORTB, PB5);

    SingleColorLED ledVictimLeft;
    ledVictimLeft.RegisterPin(&PORTC, PC0);

    SingleColorLED ledVictimRight;
    ledVictimRight.RegisterPin(&PORTB, PB4);

    TriColorLED ledState;
    ledState.RegisterPin(&PORTD, PD6);
    ledState.RegisterPin(&PORTB, PB0);
    ledState.RegisterPin(&PORTD, PD7);

    // outsource
    DigitalInputPin switch1(&PINB, PB1);
    DigitalInputPin switch2(&PINB, PB2);
    DigitalInputPin switch3(&PINB, PB3);

    AnalogInputController analogInputController;

    // TODO: outsource
    AnalogInputPin sharpFR(0x02, 4);
    analogInputController.RegisterAnalogPin(&sharpFR);
    AnalogInputPin sharpFC(0x04, 4);
    analogInputController.RegisterAnalogPin(&sharpFC);
    AnalogInputPin sharpFL(0x03, 4);
    analogInputController.RegisterAnalogPin(&sharpFL);
    AnalogInputPin sharpBR(0x01, 4);
    analogInputController.RegisterAnalogPin(&sharpBR);
    AnalogInputPin sharpBL(0x05, 4);
    analogInputController.RegisterAnalogPin(&sharpBL);

    Acceleromter acceleromter(0x04, 0xff, 0x05, analogInputController);

    analogInputController.Enable();

    sei();


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
    while (true)
    { }
#pragma clang diagnostic pop


#pragma ide diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"
    return 0;
#pragma ide diagnostic pop

}
