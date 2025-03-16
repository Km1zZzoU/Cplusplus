#include <random>

// Note: This namespace works like 'static' modifier in C
namespace {

    // this is slow generator, that uses your OS entropy to generate pure random number
    std::random_device random_device;

    std::mt19937 gen(random_device()); // we use this slow generator to generate random seed
                                       // for our nice and fast random generator

    /** This class cares about converting
      * result of your generator to 
      * uniformly distributed values from
      * given type diapasion
      */
    std::uniform_int_distribution<int> dist; 
                                            

    int generatePriority() {
        return(dist(gen));
    }
}


