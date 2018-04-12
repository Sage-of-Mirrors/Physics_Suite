#pragma once
#include "vec2.h"
#include <cstdint>

class CRandom {

    public:

    CRandom() = default;

    virtual ~CRandom() = default;

    virtual void seed(uint32_t seed) = 0;

    virtual uint32_t getUint() = 0;

    virtual int32_t getInt();

    virtual float getFloat();

    virtual float getAngle();

    virtual bool getBool();

	virtual vec2f getVector();

	virtual int32_t getColor();

};

// ------------------------------------------------------------------------- //

class CFastRandom : public CRandom {

    public:

    CFastRandom();

    CFastRandom(uint32_t seed);

    void seed(uint32_t seed) override;

    uint32_t getUint() override;

    protected:

    uint32_t mState[4];

};