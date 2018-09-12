/**
  *****************************************************************************
  * @file    PcInterface.cpp
  * @author  Robert Fairley
  * @brief   Implements an interface to access the PC, through choice of hardware communication protocol.
  *
  * @defgroup pc_interface
  * @brief    The pc_interface module provides an abstract layer to communicate with the PC, and handles all communication-related data and actions appropriate for the selected interface.
  * @{
  *****************************************************************************
  */

#include <PcInterface.h>

// TODO: doxygen documentation for functions once complete

namespace pc_interface {

PcInterface::PcInterface() {
	// No need to initialize any members here; this is done in PcInterface.h
}

PcInterface::PcInterface(PcProtocol _protocol) : protocol(_protocol) {
	// No need to initialize any members here; this is done in PcInterface.h
}

PcInterface::~PcInterface() {

}

// NOTE: this is a good place where err_t (which is set to integer values
// for each error) might be handy, to tell what kind of error happened.
bool PcInterface::setup() {
	bool success = false;
	switch(protocol) {
	case PcProtocol::UDP:
		if (!getUdpInterface()) {
			return false;
		}
		success = udpInterface->udpNew();
		if (success) {
			success = udpInterface->udpBind();
			if (success) {
				udpInterface->udpRecv();
			}
			else {
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
bool PcInterface::receive() {
	switch(protocol) {
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
bool PcInterface::transmit() {
	switch(protocol) {
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

// NOTE: Consider using <array> to allow arrays of variable length < PC_INTERFACE_BUFFER_SIZE to be input.
// TODO: should detect if input array is too small for what the buffer has to give, and pass the error up (return false)

// getRxBuffer deep copies all elements, out of rxBuffer to _rxArray.
// _rxArray must have length == PC_INTERFACE_BUFFER_SIZE.
bool PcInterface::getRxBuffer(uint8_t *_rxArray) const {
	for (int iRxBuffer = 0; iRxBuffer < PC_INTERFACE_BUFFER_SIZE; iRxBuffer++) {
		_rxArray[iRxBuffer] = rxBuffer[iRxBuffer];
	}
	return true;
}

// setTxBuffer deep copies all elements, into txBuffer from _txArray.
// _txArray must have length == PC_INTERFACE_BUFFER_SIZE.
bool PcInterface::setTxBuffer(const uint8_t *_txArray) {
	for (int iTxArray = 0; iTxArray < PC_INTERFACE_BUFFER_SIZE; iTxArray++) {
		txBuffer[iTxArray] = _txArray[iTxArray];
	}
	return true;
}

PcProtocol pc_interface::PcInterface::getProtocol() {
	return protocol;
}

bool PcInterface::setUdpInterface(udp_interface::UdpInterface *_udpInterface) {
	if (getProtocol() != PcProtocol::UDP) {
		return false;
	}
	if (!_udpInterface) {
		return false;
	}
	udpInterface = _udpInterface;
	return true;
}

udp_interface::UdpInterface* PcInterface::getUdpInterface() const {
	return udpInterface;
}

// TODO: should detect if input array is too small for what the buffer has to give, and pass the error up (return false)
bool PcInterfaceTester::setRxBufferDebug(pc_interface::PcInterface &pcInterfaceUnderTest, const uint8_t *_rxArray) {
	for (int iRxArray = 0; iRxArray < pc_interface::PC_INTERFACE_BUFFER_SIZE; iRxArray++) {
		pcInterfaceUnderTest.rxBuffer[iRxArray] = _rxArray[iRxArray];
	}
	return true;
}

bool PcInterfaceTester::getTxBufferDebug(const pc_interface::PcInterface &pcInterfaceUnderTest, uint8_t *_txArray) {
	for (int iTxBuffer = 0; iTxBuffer < pc_interface::PC_INTERFACE_BUFFER_SIZE; iTxBuffer++) {
		_txArray[iTxBuffer] = pcInterfaceUnderTest.txBuffer[iTxBuffer];
	}
	return true;
}

} // end namespace pc_interface

/**
 * @}
 */
/* end - pc_interface */
