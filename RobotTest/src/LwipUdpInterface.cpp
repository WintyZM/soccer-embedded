/**
  *****************************************************************************
  * @file    LwipUdpInterface.cpp
  * @author  Robert Fairley
  * @brief   Implements Lwip/UDP interface-facing functions, and means to access network stack data.
  *
  * @defgroup lwip_udp_interface
  * @brief    The lwip_udp_interface module provides an abstraction layer to the LwIP network stack, so that network parameters and actions are hidden from other components, and means to access only necessary data is provided.
  * @{
  *****************************************************************************
  */


#include <LwipUdpInterface.h>

// TODO: implement these functions.
// Most will simply be a 1-line call out to lwIP library,
// passing in data members defined in the LwipUdpInterface class
// as parameters.

// TODO: doxygen documentation for functions once complete

namespace lwip_udp_interface {

// FIXME: use correct networking stack types in callback function.
void recvCallback(void *arg, void *pcb, void *p,
		const void *addr, int port);

LwipUdpInterface::LwipUdpInterface() {

}

LwipUdpInterface::~LwipUdpInterface() {

}

bool LwipUdpInterface::udpNew() {
	return true;
}

bool LwipUdpInterface::udpBind() {
	return true;
}

bool LwipUdpInterface::udpRecv() {
	return true;
}

bool LwipUdpInterface::udpRemove() {
	return true;
}

bool LwipUdpInterface::ethernetifInput() {
	return true;
}

bool LwipUdpInterface::udpConnect() {
	return true;
}

bool LwipUdpInterface::udpSend() {
	return true;
}

bool LwipUdpInterface::udpDisconnect() {
	return true;
}

bool LwipUdpInterface::pbufFreeRx() {
	return true;
}

bool LwipUdpInterface::pbufFreeTx() {
	return true;
}

bool LwipUdpInterface::waitRecv() {
	return true;
}

bool LwipUdpInterface::packetToBytes(uint8_t *_byteArray) {
	return true;
}

bool LwipUdpInterface::bytesToPacket(const uint8_t *_byteArray) {
	return true;
}

void LwipUdpInterface::setRecvCallbackPbuf(void* _recvCallbackPbuf) {
	recvCallbackPbuf = _recvCallbackPbuf;
}

void recvCallback(void *arg, void *pcb, void *p,
		const void *addr, int port) {
	// TODO: synchronize access to these members (stop them getting clobbered before read by PcInterface)
	lwip_udp_interface::LwipUdpInterface *lwipUdpInterfaceCaller = (lwip_udp_interface::LwipUdpInterface*)arg;
	lwipUdpInterfaceCaller->setRecvCallbackPbuf(p);
	// TODO: release recvSemaphore
}

} // end namespace lwip_udp_interface

/**
 * @}
 */
/* end - lwip_udp_interface */
