#ifndef MEMORY_INTERFACE_H
#define MEMORY_INTERFACE_H
#include <sstream>
#include <iostream>
#include "sqlite3.h"
#include <vector>
namespace MemoryInterface{

bool write_data(std::vector<double> data, const std::string& filename); // save data directly into a file with csv format
int read_data();

template < typename T>
bool Insert_DataBase(const T& obj, std::vector<double> data){   // write data into DataBase
    std::ostringstream ss;
    std::string sql_string;
    char *errMsg = 0;
    const char * sql;
    sqlite3* db ;

    if (sqlite3_open(obj->get_DataBase_name().c_str(),&db)){
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;

        return false ;
    }
    ss.str(""); // Clear the string stream

    ss << "CREATE TABLE IF NOT EXISTS " << obj->name <<" ("
       << "Sensor_Name TEXT, "
       << "Sensor_ID INT, "
       << "Sensor_data REAL, "
       << "Log_Time TEXT, "
       << "Log_Date TEXT);";


    sql_string= ss.str();
    sql = sql_string.c_str();
 //   std::cout << sql <<std::endl;

    if(sqlite3_exec(db,sql,0,0,&errMsg)){

        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_close(db);

        return false;
    }
    ss.str(""); // Clear the string stream
    //ss.clear();
    for (auto temp_data: data ){
        ss << "INSERT INTO "<< obj->name << "(Sensor_Name, Sensor_ID, Sensor_data, Log_Time, Log_Date) "
           << "VALUES ('"<<obj->name<<"', 1, " << temp_data << ", '20:20:20', '2024-08-15');";
    }

    sql_string= ss.str();
    sql = sql_string.c_str();

    if(sqlite3_exec(db,sql,0,0,&errMsg)){
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_close(db);

        return false;
    }


    // Clean up
    sqlite3_close(db);

    return true;
}


template <typename T>
std::vector<double> Select_database( const T& obj, int number_of_selected_data=1 ) // Read data from Data Base
{

    std::ostringstream ss;
    std::string sql_string;
    char *errMsg = 0;
    const char * sql;
    sqlite3* db ;
    std::vector<double> selected_data;


    if (sqlite3_open(obj->get_DataBase_name().c_str(),&db)){
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;

        return selected_data ;
    }
    ss.str(""); // Clear the string stream

    ss << "CREATE TABLE IF NOT EXISTS " << obj->name <<" ("
       << "Sensor_Name TEXT, "
       << "Sensor_ID INT, "
       << "Sensor_data REAL, "
       << "Log_Time TEXT, "
       << "Log_Date TEXT);";

    sql_string= ss.str();
    sql = sql_string.c_str();

    if(sqlite3_exec(db,sql,0,0,&errMsg)){

        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_close(db);

        return selected_data;
    }
    ss.str(""); // Clear the string stream

    ss << "SELECT * FROM "<< obj->name <<" ORDER BY ROWID DESC LIMIT "<< number_of_selected_data <<";";

    sql_string= ss.str();
    sql = sql_string.c_str();

    sqlite3_stmt *stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0)) {
        std::cerr << "Failed to execute query: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return selected_data;
    } else {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            const unsigned char *sensor_name = sqlite3_column_text(stmt, 0);
            int Sensor_ID = sqlite3_column_int(stmt, 1);
            double saved_data = sqlite3_column_double(stmt, 2);
            selected_data.push_back(saved_data);

            const unsigned char *time = sqlite3_column_text(stmt, 3);
            const unsigned char *date = sqlite3_column_text(stmt, 4);

            // std::cout << "Sensor Type: " << sensor_name
            //           << ", Sensor ID: " << Sensor_ID
            //           << ", Data: " << saved_data
            //           << ", Time: " << time
            //           << ", Date: " << date << std::endl;
        }
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return selected_data;

} // End of Select data template

}  // End of namespace MemoryInterface


#endif  //MEMORY_INTERFACE_H
