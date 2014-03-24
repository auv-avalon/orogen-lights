/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "Lights.hpp"
#include <fcntl.h>
#include <unistd.h>

using namespace lights;

Lights::Lights(std::string const& name)
    : LightsBase(name)
{
}

Lights::Lights(std::string const& name, RTT::ExecutionEngine* engine)
    : LightsBase(name, engine)
{
}

Lights::~Lights()
{
}



/// The following lines are template definitions for the various state machine
// hooks defined by Orocos::RTT. See Lights.hpp for more detailed
// documentation about them.

bool Lights::configureHook()
{
    if (! LightsBase::configureHook())
        return false;
    return true;
}
bool Lights::startHook()
{
    if (! LightsBase::startHook())
        return false;

    fd = open("/dev/ttyACM0",O_WRONLY);
    if(fd<0){
        std::cerr << "error to open fd" << std::endl;
        return false;

    }
    return true;
}
void Lights::updateHook()
{
    LightsBase::updateHook();
    canbus::Message msg;
    while (_can_in.read(msg) == RTT::NewData){
        uint8_t light_value1 = (uint8_t)msg.data[0];
        uint8_t light_value2 = (uint8_t)msg.data[1];
        uint16_t value = light_value1; 
        value = value << 8 | value2;
        _light_value.write(value);
        char a = '@';
        write(fd,&a,1);
        write(fd,&light_value2,1);
        write(fd,&light_value1,1);
        write(fd,&a,1);
        write(fd,&light_value2,1);
        write(fd,&light_value1,1);
    }
}
void Lights::errorHook()
{
    LightsBase::errorHook();
}
void Lights::stopHook()
{
    LightsBase::stopHook();
}
void Lights::cleanupHook()
{
    LightsBase::cleanupHook();
}
