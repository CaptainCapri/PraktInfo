#include <boost/interprocess/shared_memory_object.hpp>

#include <boost/interprocess/mapped_region.hpp>

#include <iostream>

#include <boost/interprocess/sync/interprocess_semaphore.hpp>

#include <math.h>

#include "semaphore_shared_data.hpp"


using namespace boost::interprocess;

int main (){
//create a shared memory object.
shared_memory_object shm(open_only, "shared_memory",read_write);

//Map the whole shared memory in this process
mapped_region region(shm,read_write);

//get the region address
void * addr = region.get_address();

//Obtain the shared structure
shared_memory_buffer * data = static_cast<shared_memory_buffer*>(addr);

while(true){
//wait until a number gets available
data->reader.wait();

//print the original value
std::cout << "Original Value: " << data->value << "\n";

//create the sqrt of the original value
data->value = sqrt(data->value);

//writer can print sqrt
data->writer.post();
}
return 0;
}
