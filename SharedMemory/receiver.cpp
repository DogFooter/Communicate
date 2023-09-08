#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/sync/named_condition.hpp>
#include "ICommData.h"

int main() {
    using namespace boost::interprocess;

    shared_memory_object shdmem{ open_only, "MySharedMemory", read_write };

    named_mutex nmutex{ open_only, "mtx" };
    named_condition ncond{ open_only, "cond" };

    mapped_region region{ shdmem, read_write };

    {
        scoped_lock<named_mutex> lock(nmutex);
        while (region.get_size() != sizeof(InitialData))
            cond.wait(lock);

        InitialData* pData = static_cast<InitialData*>(region.get_address());
        pData->print();

        ProgressData* progress = new (region.get_address()) Progressdata;

        for (int i = 0; i < 10; ++i) {
            progress->progress1 = i;
            progress->progress2 = i * 2;
            progress->progress3 = i * 3;

            // Notify A that the progress data is ready
            ncond.notify_one();
        }
    }

    {
        scoped_lock<named_mutex> lock(nmutex);
        while (region.get_size() != sizeof(ResultData))
            cond.wait(lock);

        ResultData* result = static_cast<ResultData*>(region.get_address());
        result->print();
    }

    // Remove shared memory on destruction
    shared_memory_object::remove("MySharedMemory");

    return 0;
}
