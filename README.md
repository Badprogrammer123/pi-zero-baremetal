# pi-zero-baremetal
I will document my bare metal journey using the Raspberry Pi Zero 2 W.

## Progress
* UART ECHO back data in receiver function
* Add parity check

### Finished

* Implemented the UART transmitter in polling mode (no interrupts).
* Transmitted data using only the UART data register (using a single FIFO entry rather than the full FIFO).
* Implemeted FIFO for Receiver and Transmitter

