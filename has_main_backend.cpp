#include "has_main_backend.h"
#include <QThread>
#include <QDebug>

#include <chrono>
#include <ctime>
#include <QString>
#include <iomanip>
#include <sstream>
#include <QThread>
#include <QFuture>

#include "sensor.h"
#include "temp_sensor.h"
#include "actuator.h"
#include "heater_controller.h"
#include "camera.h"

HAS_Main_Backend::HAS_Main_Backend(QWidget *parent)
    : QWidget{parent}
{
    qDebug() << "Defulat Constructor of central manager is called! " ;

}

HAS_Main_Backend::HAS_Main_Backend(std::string_view username, std::string_view password, int user_ID_number)
{
    // Call the initialization function and check its return value
    if (!initial_analysis()) {
        // Throw an exception if the initialization failed
        throw std::runtime_error("Initialization failed in CentralManager");
    }

    qDebug() << "CentralManager successfully initialized." ;

}


void HAS_Main_Backend::start_point()
{

    qDebug() << " Program started ..." ;

    // create and start Object of Temp sensor -> Temp sensor data reading start  (Polymorphysm)
    Sensor* sensor   = new Temp_Sensor("Temperature", 1 , 10, true, 3);
    qDebug() << "Sensor Name from main first: " << sensor;

    Sensor* sensor2 = new Sensor("Hosbital",10,2,false,9);
    // call actuator adjuster  (Polymorphysm)
    Actuator* actuator = new Heater_Controller("Heater", 2, 100, true, 2, sensor2);


}

bool HAS_Main_Backend::initial_analysis()
{
    //Analysis like check and set all input and also primary adjustment
    qDebug() << "Primary analysis and settlment Done!";
    return true;
}

std::string HAS_Main_Backend::getCurrentTime()
{
    return "";
}

std::string HAS_Main_Backend::getCurrentDate()
{
    return "";

}



HAS_Main_Backend::~HAS_Main_Backend()
{

}


