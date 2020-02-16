#ifndef IGFXDEVICEDELEGATE_H
#define IGFXDEVICEDELEGATE_H


class IGfxDeviceDelegate
{
public:
    virtual ~IGfxDeviceDelegate();

    virtual void* getImageData() = 0;
};

#endif // IGFXDEVICEDELEGATE_H
