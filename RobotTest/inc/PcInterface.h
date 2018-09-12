/**
 *****************************************************************************
 * @file    PcInterface.h
 * @author  Robert Fairley
 * @brief   Defines a interface through which the PC is accessed, independent of the underlying hardware communication protocol.
 *
 * @defgroup Header
 * @ingroup  pc_interface
 * @{
 *****************************************************************************
 */

#ifndef __PC_INTERFACE_H__
#define __PC_INTERFACE_H__

#include <cstdint>

#include <UdpInterface.h>

// TODO: variable names to not use _prefix

namespace pc_interface {

// These constants should be available outside this file.
const int PC_INTERFACE_BUFFER_SIZE = 1024;
const int PC_INTERFACE_PROTOCOL_ENUM_START_MAGIC = 5656;

enum class PcProtocol {
    UDP = PC_INTERFACE_PROTOCOL_ENUM_START_MAGIC, USB_UART
};

class PcInterface {
public:
    PcInterface();
    PcInterface(PcProtocol _protocol);
    ~PcInterface();
    bool setup();
    bool receive();
    bool transmit();
    bool getRxBuffer(uint8_t *_rxArray) const;
    bool setTxBuffer(const uint8_t *_txArray);
    PcProtocol getProtocol();
    bool setUdpInterface(udp_interface::UdpInterface *_udpInterface);
    udp_interface::UdpInterface* getUdpInterface() const;

    // PcInterfaceTester implements functions that need access to private members
    // but are not to be used under normal circumstances.
    friend class PcInterfaceTester;
private:
    const PcProtocol protocol = PcProtocol::UDP; // NOTE: possibly support multiple protocols at same time? would make this array in that case. right now only designed for one protocol though.
    // TODO: consider using DMA for copies to/from rx/txBuffer, for larger PC_INTERFACE_BUFFERS, to allow other threads to run
    // TODO: may be better to have counter for space used, so not copying entire buffer length each time
    uint8_t rxBuffer[PC_INTERFACE_BUFFER_SIZE] = { }; // TODO: synchronize access to this
    uint8_t txBuffer[PC_INTERFACE_BUFFER_SIZE] = { }; // TODO: synchronize access to this
    udp_interface::UdpInterface *udpInterface = nullptr;
    // Other interfaces may be added here.
    // TODO: implement mutexes before integrating with FreeRTOS
    // rxBuffer mutex
    // txBuffer mutex
};

class PcInterfaceTester {
public:
    static bool setRxBufferDebug(
            pc_interface::PcInterface &pcInterfaceUnderTest,
            const uint8_t *_rxArray);
    static bool getTxBufferDebug(
            const pc_interface::PcInterface &pcInterfaceUnderTest,
            uint8_t *_txArray);
};

} // end namespace pc_interface

/**
 * @}
 */
/* end - Header */

#endif /* __PC_INTERFACE__ */
