#include <random.h>
#include <cstdint>

int32_t CRandom::getInt() {

    return (int32_t)getUint();

}

float CRandom::getFloat() {

    uint32_t u = getUint();

    float f = (float)((double)u / ((double)0xFFFFFFFFU));

    return math::Clamp<float>(f, 0.0F, 1.0F);

}

float CRandom::getAngle() {

    return (getFloat() * math::TWOPI<float>);

}

bool CRandom::getBool() {

    return !!(getUint() & 0x1);

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

    uint32_t e = (mState[0] - math::RotateBits(mState[1], 27));

    mState[0] = (mState[1] ^ math::RotateBits(mState[2], 17));

    mState[1] = (mState[2] + mState[3]);

    mState[2] = (mState[3] + e);

    mState[3] = (e + mState[0]);

    return mState[3];

}
