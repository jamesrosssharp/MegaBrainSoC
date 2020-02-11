#ifndef SPIDEVICE_H
#define SPIDEVICE_H

#include <stdint.h>

class SPIDevice {

public:

    virtual ~SPIDevice();

    virtual void assertChipSelect(bool assert) = 0;
    virtual void transceive(uint8_t send, uint8_t* receive) = 0;


};

#endif // SPIDEVICE_H

