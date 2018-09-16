/**
 *****************************************************************************
 * @file    LwipUdpInterface.h
 * @author  Robert Fairley
 * @brief   Defines the interface through which UDP and required Lwip network stack data/functions will be accessed.
 *
 * @defgroup Header
 * @ingroup  lwip_udp_interface
 * @{
 *****************************************************************************
 */

#ifndef LWIP_UDP_INTERFACE_H
#define LWIP_UDP_INTERFACE_H

#include <cstdint>

 // TODO: make things in this class const where possible

namespace lwip_udp_interface {

// LwipUdpInterface is the real i.e. hardware-facing implementation of the
// abstract UdpInterface class. This will call out to LwIP and any
// lower-level networking functions to implement UDP functionality.
// Functions have no parameters, and instead pass the state information
// they were initialized with (members of this class). This means the PcInterface,
// UdpInterface, and mocking classes do not have to care about how the
// networking functions are implemented under the hood - only the methods
// called.
// Another approach rather than having stateful members is to pass a
// void* to every interface function, and pass data as needed into there.
class LwipUdpInterface {
public:
    LwipUdpInterface();
    // TODO: parameterized constructor.
    ~LwipUdpInterface();

    // Abstract UdpInterface class overrides.
    bool udpNew();
    bool udpBind();
    bool udpRecv();
    bool udpRemove();
    bool ethernetifInput();
    bool udpConnect();
    bool udpSend();
    bool udpDisconnect();
    bool pbufFreeRx();
    bool pbufFreeTx();
    bool waitRecv();
    bool packetToBytes(uint8_t *byteArrayOut) const;
    bool bytesToPacket(const uint8_t *byteArrayIn);

    // Helpers
    void setRecvCallbackPbuf(void* recvCallbackPbufIn);
private:
    // FIXME: These need to be of the right types for the networking stack.
    const int *pcb = nullptr;
    const int *ipaddr = nullptr;
    const int *ipaddrPc = nullptr;
    const int port = 0;
    const int portPc = 0;
    const int *netif = nullptr;
    const int *recvSemaphore = nullptr;

    // Set by recvCallback.
    void *recvCallbackPbuf = nullptr;

    int *txPbuf = nullptr;
    // TODO: synchronize access to pbufs
};

} // end namespace lwip_udp_interface

/**
 * @}
 */
/* end - Header */

#endif /* LWIP_UDP_INTERFACE_H */
