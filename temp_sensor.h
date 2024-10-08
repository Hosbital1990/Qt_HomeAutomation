#ifndef TEMP_SENSOR_H
#define TEMP_SENSOR_H

#include <iostream>
#include <string>
#include <mutex>
#include<vector>
#include<any>
#include <thread>
#include <condition_variable>

#include "sensor.h"
#include  <QObject>
class Temp_Sensor : public Sensor {

public:
    Temp_Sensor();
    Temp_Sensor(std::string_view name, int order_number, int priority, bool power_state, short int operation_state);
    virtual ~Temp_Sensor();


    virtual std::vector<double> providing_data() override;

    std::string get_DataBase_name();


    std::string_view name;


    private slots:

    virtual void start_data_reading() override;

private:
 //   virtual void start_data_reading() override;

    std::mutex temp_mtx;
    std::vector<double> raw_temp_data ;

    //std::string_view name;
    int order_number;
    int priority;
    bool power_state;
    short int operation_state;

    std::jthread temp_data_reading_thread ;
    bool data_is_ready=false ;
    std::condition_variable cv;
    const std::string_view file_save_location = "~/Project/comeback/temp_storage" ;
    const std::string DataBase_name = "temp_DataBase.db";
    short int db_bunch_size{10} ;
    QThread* qtemp_data_reading_thread ;

};

#endif // TEMP_SENSOR_H
