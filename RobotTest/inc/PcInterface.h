/**
 *****************************************************************************
 * @file    PcInterface.h
 * @author  Robert Fairley
 * @brief   Defines and implements a interface through which the PC is accessed, independent of the underlying hardware communication protocol.
 *
 * @defgroup Header
 * @ingroup  pc_interface
 * @{
 *****************************************************************************
 */

#ifndef PC_INTERFACE_H
#define PC_INTERFACE_H

#include <cstdint>

// TODO: doxygen documentation for functions once complete

namespace pc_interface {

// These constants should be available outside this file.
constexpr int PC_INTERFACE_BUFFER_SIZE = 1024;
constexpr int PC_INTERFACE_PROTOCOL_ENUM_START_MAGIC = 5656;

enum class PcProtocol {
    UDP = PC_INTERFACE_PROTOCOL_ENUM_START_MAGIC, USB_UART
};

template<class UdpInterface>
class PcInterface {
public:
    PcInterface();
    PcInterface(PcProtocol protocolIn);
    ~PcInterface();
    bool setup();
    bool receive();
    bool transmit();
    bool getRxBuffer(uint8_t *rxArrayOut) const;
    bool setTxBuffer(const uint8_t *txArrayIn);
    PcProtocol getProtocol();
    bool setUdpInterface(UdpInterface *udpInterfaceIn);
    UdpInterface* getUdpInterface() const;

    // PcInterfaceTester implements functions that need access to private members
    // but are not to be used under normal circumstances.
    friend class PcInterfaceTester;
private:
    const PcProtocol protocol = PcProtocol::UDP; // NOTE: possibly support multiple protocols at same time? would make this array in that case. right now only designed for one protocol though.
    // TODO: consider using DMA for copies to/from rx/txBuffer, for larger PC_INTERFACE_BUFFERS, to allow other threads to run
    // TODO: may be better to have counter for space used, so not copying entire buffer length each time
    uint8_t rxBuffer[PC_INTERFACE_BUFFER_SIZE] = { }; // TODO: synchronize access to this
    uint8_t txBuffer[PC_INTERFACE_BUFFER_SIZE] = { }; // TODO: synchronize access to this
    UdpInterface *udpInterface = nullptr;
    // Other interfaces may be added here.
    // TODO: implement mutexes before integrating with FreeRTOS
    // rxBuffer mutex
    // txBuffer mutex
};

class PcInterfaceTester {
public:
    template<class UdpInterface>
    static bool setRxBufferDebug(
            pc_interface::PcInterface<UdpInterface> &pcInterfaceUnderTest,
            const uint8_t *rxArrayIn);
    template<class UdpInterface>
    static bool getTxBufferDebug(
            const pc_interface::PcInterface<UdpInterface> &pcInterfaceUnderTest,
            uint8_t *txArrayOut);
};

template<class UdpInterface> PcInterface<UdpInterface>::PcInterface() {
    // No need to initialize any members here; this is done in PcInterface.h
}

template<class UdpInterface> PcInterface<UdpInterface>::PcInterface(PcProtocol protocolIn) :
        protocol(protocolIn) {
    // No need to initialize any members here; this is done in PcInterface.h
}

template<class UdpInterface> PcInterface<UdpInterface>::~PcInterface() {

}

// NOTE: this is a good place where err_t (which is set to integer values
// for each error) might be handy, to tell what kind of error happened.
template<class UdpInterface> bool PcInterface<UdpInterface>::setup() {
    bool success = false;
    switch (protocol) {
    case PcProtocol::UDP:
        if (!getUdpInterface()) {
            return false;
        }
        success = udpInterface->udpNew();
        if (success) {
            success = udpInterface->udpBind();
            if (success) {
                udpInterface->udpRecv();
            } else {
                udpInterface->udpRemove();
            }
        }
        break;
    default:
        break;
    }
    return success;
}

// NOTE: Consider an input() function that calls only ethernetifInput, which runs
// in its own thread.

// Purpose: to make the HW calls and convert packets into array of bytes.
template<class UdpInterface> bool PcInterface<UdpInterface>::receive() {
    switch (protocol) {
    case PcProtocol::UDP:
        if (!getUdpInterface()) {
            return false;
        }
        udpInterface->ethernetifInput(); // Extract packets from network interface
        udpInterface->waitRecv(); // Wait for callback to write data members (including packets) to UdpInterface
        udpInterface->packetToBytes(rxBuffer); // Copy contents of the packets into rxBuffer
        udpInterface->pbufFreeRx();
        return true;
    default:
        return false;
    }
}

// Purpose: to covert array of bytes into packets and make the HW calls.
template<class UdpInterface> bool PcInterface<UdpInterface>::transmit() {
    switch (protocol) {
    case PcProtocol::UDP:
        if (!getUdpInterface()) {
            return false;
        }
        udpInterface->bytesToPacket(txBuffer);
        udpInterface->udpConnect();
        udpInterface->udpSend();
        udpInterface->udpDisconnect();
        udpInterface->pbufFreeTx();
        return true;
    default:
        return false;
    }
}

// NOTE: Consider using <array> to allow arrays of variable length < PC_INTERFACE_BUFFER_SIZE to be input. Also thinking about just
// adding another parameter for array size for these functions to avoid including another dependency.
// TODO: should detect if input array is too small for what the buffer has to give, and pass the error up (return false)

// getRxBuffer deep copies all elements, out of rxBuffer to _rxArray.
// _rxArray must have length == PC_INTERFACE_BUFFER_SIZE.
template<class UdpInterface> bool PcInterface<UdpInterface>::getRxBuffer(uint8_t *rxArrayOut) const {
    for (int iRxBuffer = 0; iRxBuffer < PC_INTERFACE_BUFFER_SIZE; iRxBuffer++) {
        rxArrayOut[iRxBuffer] = rxBuffer[iRxBuffer];
    }
    return true;
}

// setTxBuffer deep copies all elements, into txBuffer from _txArray.
// _txArray must have length == PC_INTERFACE_BUFFER_SIZE.
template<class UdpInterface> bool PcInterface<UdpInterface>::setTxBuffer(const uint8_t *txArrayIn) {
    for (int iTxArray = 0; iTxArray < PC_INTERFACE_BUFFER_SIZE; iTxArray++) {
        txBuffer[iTxArray] = txArrayIn[iTxArray];
    }
    return true;
}

template<class UdpInterface> PcProtocol PcInterface<UdpInterface>::getProtocol() {
    return protocol;
}

template<class UdpInterface> bool PcInterface<UdpInterface>::setUdpInterface(UdpInterface *udpInterfaceIn) {
    if (getProtocol() != PcProtocol::UDP) {
        return false;
    }
    if (!udpInterfaceIn) {
        return false;
    }
    udpInterface = udpInterfaceIn;
    return true;
}

template<class UdpInterface> UdpInterface* PcInterface<UdpInterface>::getUdpInterface() const {
    return udpInterface;
}

// TODO: should detect if input array is too small for what the buffer has to give, and pass the error up (return false)
template<class UdpInterface> bool PcInterfaceTester::setRxBufferDebug(
        pc_interface::PcInterface<UdpInterface> &pcInterfaceUnderTest,
        const uint8_t *rxArrayIn) {
    for (int iRxArray = 0; iRxArray < pc_interface::PC_INTERFACE_BUFFER_SIZE;
            iRxArray++) {
        pcInterfaceUnderTest.rxBuffer[iRxArray] = rxArrayIn[iRxArray];
    }
    return true;
}

template<class UdpInterface> bool PcInterfaceTester::getTxBufferDebug(
        const pc_interface::PcInterface<UdpInterface> &pcInterfaceUnderTest,
        uint8_t *txArrayOut) {
    for (int iTxBuffer = 0; iTxBuffer < pc_interface::PC_INTERFACE_BUFFER_SIZE;
            iTxBuffer++) {
        txArrayOut[iTxBuffer] = pcInterfaceUnderTest.txBuffer[iTxBuffer];
    }
    return true;
}

} // end namespace pc_interface

/**
 * @}
 */
/* end - Header */

#endif /* PC_INTERFACE */
