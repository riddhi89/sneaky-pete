#include "pch.hpp"
#include "nova/backup/BackupException.h"

namespace nova { namespace backup {

/**---------------------------------------------------------------------------
 *- BackupException
 *---------------------------------------------------------------------------*/

BackupException::BackupException(Code code) throw()
: code(code) {
}

BackupException::~BackupException() throw() {
}

const char * BackupException::what() const throw() {
    switch(code) {
        case INVALID_STATE:
            return "State was invalid.";
        default:
            return "An error occurred.";
    }
}

} }  // end namespace nova::guest::backup

