#include <boost/interprocess/sync/interprocess_semaphore.hpp>


using namespace boost::interprocess;

struct shared_memory_buffer {
//writer initialized with one to start
//reader have to wait
shared_memory_buffer(): writer(1), reader(0), value(0){}

interprocess_semaphore writer, reader;

float value;
};
