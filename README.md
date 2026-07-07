# pi-zero-baremetal
I will document my bare metal journey using the Raspberry Pi Zero 2 W.

## Progress
* Working on Understanding Interrupts and enabling them (Using the Cortex-a53 documentation also learning how to navigate it)

### Finished

* Implemented the Mini UART transmitter in polling mode (no interrupts).
* Transmitted data using only the UART data register (using a single FIFO entry rather than the full FIFO).
* Implemeted FIFO for Receiver and Transmitter
* Function to send 1 char throught the transmitter
* Function to send a string through the transmitter

