#include "include/utils.h"

#include <random>
#include <chrono>

namespace PZ2048 {

static std::mt19937_64 gen;
static uint gen_seed;

// pass in seed = 0 for random seed
void srand(uint seed) {
    gen_seed = seed;
    gen.seed(seed);
}

void tsrand() {
    srand(static_cast<uint>(std::chrono::system_clock::now().time_since_epoch().count()));
}

uint rand() {
    return gen();
}

uint get_seed() {
    return gen_seed;
}

}