#include "..\include\random.h"
#include <cstdint>


int32_t CRandom::getInt() {

    return (int32_t)getUint();

}

float CRandom::getFloat() {

    uint32_t u = getUint();

    float f = (float)((double)u / ((double)0xFFFFFFFFU));

	return 0;

}

float CRandom::getAngle() {

    return (getFloat() * M_TWOPI);

}

bool CRandom::getBool() {

    return !!(getUint() & 0x1);

}

vec2f CRandom::getVector() {

	return vec2f(getFloat(), getFloat());

}

int32_t CRandom::getColor() {

	return getUint() | 0xFF;

}

// ------------------------------------------------------------------------- //

CFastRandom::CFastRandom() {

    mState[0] = 0;

    mState[1] = 0;

    mState[2] = 0;

    mState[3] = 0;

}

CFastRandom::CFastRandom(uint32_t seed) {

    CFastRandom::seed(seed);

}

void CFastRandom::seed(uint32_t seed) {

    mState[0] = seed;

    mState[1] = 0;

    mState[2] = 0;

    mState[3] = 0;

    // initialize values 1-3 by advancing a few times

    for (size_t i = 0; i < 20; ++i) {

        CFastRandom::getUint();

    }

}

uint32_t CFastRandom::getUint() {

    uint32_t e = (mState[0] - (mState[1] << 27));

    mState[0] = (mState[1] ^ (mState[2] << 17));

    mState[1] = (mState[2] + mState[3]);

    mState[2] = (mState[3] + e);

    mState[3] = (e + mState[0]);

    return mState[3];

}
