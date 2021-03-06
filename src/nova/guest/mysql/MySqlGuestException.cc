#include "pch.hpp"
#include "nova/guest/guest.h"
#include "nova/guest/mysql/MySqlGuestException.h"
#include <uuid/uuid.h>


using boost::optional;
using namespace std;


namespace nova { namespace guest { namespace mysql {

/**---------------------------------------------------------------------------
 *- MySqlGuestException
 *---------------------------------------------------------------------------*/

MySqlGuestException::MySqlGuestException(MySqlGuestException::Code code) throw()
: code(code) {
}

MySqlGuestException::~MySqlGuestException() throw() {
}

const char *  MySqlGuestException::code_to_string(Code code) {
    switch(code) {
        case CANT_CONNECT_WITH_MYCNF:
            return "Can't connect using my.cnf file settings.";
        case CANT_READ_ORIGINAL_MYCNF:
            return "Can't read from original my.cnf file.";
        case CANT_WRITE_TMP_MYCNF:
            return "Couldn't write temp my.cnf file.";
        case COULD_NOT_START_MYSQL:
            return "Could not start MySQL!";
        case COULD_NOT_STOP_MYSQL:
            return "Could not stop MySQL!";
        case DEBIAN_SYS_MAINT_USER_NOT_FOUND:
            return "Could not locate 'debian-sys-maint' user!";
        case GUEST_INSTANCE_ID_NOT_FOUND:
            return "Guest instance ID not found.";
        case INVALID_ZERO_LIMIT:
            return "Limit parameter must be positive and non-zero.";
        case MYSQL_NOT_STOPPED:
            return "MySQL was not stopped.";
        case NO_PASSWORD_FOR_CREATE_USER:
            return "Can't create user because no password was specified.";
        case USER_NOT_FOUND:
            return "User not found.";
        case CANT_WRITE_TMP_FILE:
            return "Can't write temporary file.";
        default:
            return "MySqlGuest failure.";
    }
}

const char * MySqlGuestException::what() const throw() {
    return code_to_string(code);
}


} } } // end namespace
