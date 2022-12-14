#ifndef ST7789JOB_HPP
#define ST7789JOB_HPP

// standard includes
#include <cstdint>

// esp32 includes

// project includes
#include "St7789Types.hpp"

static const char *TAG_ST7789_JOB = "St7789Job";

/**
 * @brief Essentially a collection of pointers that will have to be freed later.
 *
 * @tparam SpiTransaction the native type of transaction
 */
template <typename SpiTransaction> class St7789Job {
    private:
    St7789Command *command;
    SpiTransaction *transactionOfCommand;
    SpiTransaction *transactionOfData;

    public:
    St7789Job(St7789Command *cmd, SpiTransaction *tcmd, SpiTransaction *tdat)
        : command(cmd), transactionOfCommand(tcmd), transactionOfData(tdat) {}

    virtual ~St7789Job() {
        if (command) {
            if (MUST_USE_EXTERNAL_BUFFER(command->dataLength) && !(command->keepExternalBufferOnDelete)) {
                delete command->externalBuffer;
            }
            delete command;
        }
        if (transactionOfCommand) {
            delete transactionOfCommand;
        }
        if (transactionOfData) {
            delete transactionOfData;
        }
    }

    SpiTransaction *getTransactionOfCommand() { return transactionOfCommand; }
    SpiTransaction *getTransactionOfData() { return transactionOfData; }
};

#endif