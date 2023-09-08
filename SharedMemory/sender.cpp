#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/sync/named_condition.hpp>
#include "ICommData.h"

int main() {
    using namespace boost::interprocess;

    shared_memory_object shdmem{ create_only, "MySharedMemory", read_write };
    shdmem.truncate(sizeof(ICommData));

    named_mutex nmutex{ create_only, "mtx" };
    named_condition ncond{ create_only, "cond" };

    {
        scoped_lock<named_mutex> lock(nmutex);

        mapped_region region{ shdmem, read_write };

        InitialData* data = new (region.get_address()) InitialData;
        data->arg1 = 10;
        data->arg2 = 20;
        data->arg3 = 30;
        data->arg4 = "Hello from Program A!";

        // Notify B that the initial data is ready
        ncond.notify_one();
    }

    for (int i = 0; i < 10; ++i) {
        scoped_lock<named_mutex> lock(nmutex);
        ncond.wait(lock);

        ICommData* pData = static_cast<ICommData*>(region.get_address());
        pData->print();

        if (i == 9) { // last progress update
            ResultData* result = new (region.get_address()) ResultData;
            result->resultStr = "Final Result";
            result->resultCode = 100;

            // Notify B that the final result is ready
            ncond.notify_one();
        }
    }

    return 0;
}
