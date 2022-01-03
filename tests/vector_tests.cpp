#include <assert.h> 
#include <vector.hpp>
#include <iostream>


void testDefaultConstructor() {
    SL::vector<int> v;
    assert(v.size() == 0);
    assert(v.capacity() == 0);
}

int main() {
    testDefaultConstructor();
    return 0;
}

// all tests should run fully -> and report error?


