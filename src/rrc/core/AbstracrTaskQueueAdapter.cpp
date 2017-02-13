/**
 *  @autor arssivka
 *  @date 7/20/16
 */

#include <rrc/core/AbstracrTaskQueueAdapter.h>


bool rrc::AbstracrTaskQueueAdapter::execOnce() {
    Task task;
    if (this->tryDequeue(task)) {
        task();
        return true;
    }
    return false;
}


void rrc::AbstracrTaskQueueAdapter::execAll() {
    Task task;
    while (this->tryDequeue(task)) {
        task();
    }
}