#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

// Central event handler, to respond to rx events, tell equipment what to do, exchange data with system components, and transmit to tx.
//
// Typical use cycle looks like
// 1. receive bytes from pc interface
// 2. parse the command from char array into a data structure
// 3. pass the command to equipment handler
// 4. read sensor data cache (or block on sensor data update signal)
// 5. serialize the read sensor data
// 6. transmit the sensor data to the pc


// TODO: use proper types not void*
// TODO: rethink parameters and returns for all these functions
class EventHandler {
public:
    void receive(char *dataFromPc);                     // Makes a call to pcInterface, to receive data into dataFromPc
    void parseCommand(char *rawData);                   // Converts a command from raw bytes into a command data structure.
    void dispatch();                                    // Does action; dispatches command to event handler, requests update from sensordata cache, ...
    void serializeSensorData(void * commandStruct);     // Converts a command from a command data structure to raw bytes.
    void transmit(char *dataToPc);                      // Makes a call to pcInterface, to transmit data in dataToPc
private:
    void setMotorPositions();           // Tells the equipmentHandler to set the motor positions, passing in required data
    void waitSensorDataRefresh();       // Blocks until sensorDataCache sends a signal saying all data has been updated since when this function was called
                                        //      - probably the signal would be the releasing of some synchronization primitive contained by the sensordatacache, which cacheWriter thread should set
    void getSensorData();               // Accesses the sensorDataCache and returns struct containing the data currently in it
    void getSystemStatus();             // Gets a "system status" by querying necessary equipment (implementation to be decided on)

    void equipmentHandler;          // equipmentHandler class - the lifetime of this matches the EventHandler so it is contained inside (not as a reference)
    void *pcInterface;              // pcInterface - set to a global instance of pcInterface when this class is constructed
    void *sensorDataCache;          // sensorDataCache - set to a global instance of sensorDataCache when this class is constructed
};

#endif
