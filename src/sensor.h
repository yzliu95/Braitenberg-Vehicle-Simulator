/**
 * @file sensor.h
 *
 * @copyright Yuanzhe Liu, All rights reserved.
 */
#ifndef SRC_SENSOR_H_
#define SRC_SENSOR_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/common.h"
#include "src/params.h"
#include "src/entity_type.h"
#include "src/sensor_type.h"
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
 * @brief Class representing a sensor
 * general class for any sensor that sense entities and return a scaled value
 */
class Sensor {
 public:
    Sensor() : type_(kSensor), heading_(LEFT_SENSOR), reading_(0.0),
    sensitivity_(1200) {}
    virtual ~Sensor() = default;
    /**
     * @brief reset reading to zero
     */
    void Reset() {reading_ = 0;}
    /**
     * @brief setter for sensor type
     */
    void set_type(SensorType type) {type_ = type;}
    /**
     * @brief Gette for sensor type
     */
    SensorType get_type() {return type_;}

    /**
     * @brief Setter for sensor position (left/right)
     */
    void set_sensorheading(int h) {heading_ = h;}
    /**
     * @brief Getter for sensor position (left/right)
     */
    int get_sensorheading() {return heading_;}
    /**
     * @brief Setter for reading
     */
    void set_reading(double reading) {reading_ = reading;}
    /**
     * @brief getter for reading
     */
    double get_reading() {return reading_;}

    /**
    * @brief set the sensitivity (constant for calculate sensor reading)
    */
    void set_sensitivity(int s) {sensitivity_ = s;}

 private:
    // store the sensor type
    SensorType type_;
    // indicate left/right sensor
    int heading_;
    // reading of this sensor
    double reading_;

 protected:
    int sensitivity_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_SENSOR_H_
