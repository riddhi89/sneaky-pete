#include "pch.hpp"
#include "nova/guest/backup/BackupMessageHandler.h"
#include "nova/guest/GuestException.h"
#include <boost/foreach.hpp>
#include "nova/Log.h"
#include <sstream>
#include <string>

using nova::backup::BackupCreationArgs;
using nova::backup::BackupManagerPtr;
using nova::JsonData;
using nova::JsonDataPtr;
using nova::Log;
using nova::guest::GuestException;
using boost::optional;
using std::string;
using namespace boost;

namespace nova { namespace guest { namespace backup {

BackupCreationArgs from_input(const GuestInput & input) {
    if (!input.tenant) {
        NOVA_LOG_ERROR("Tenant was not specified by this RPC call! "
                       "Aborting...");
        throw GuestException(GuestException::MALFORMED_INPUT);
    }
    if (!input.token) {
        NOVA_LOG_ERROR("Token was not specified by this RPC call! "
                       "Aborting...");
        throw GuestException(GuestException::MALFORMED_INPUT);
    }
    BackupCreationArgs args = {
        input.tenant.get(),
        input.token.get(),
        input.args->get_object("backup_info")->get_string("id"),
        input.args->get_object("backup_info")->get_string("location")
    };
    return args;
}

BackupMessageHandler::BackupMessageHandler(BackupManagerPtr backup_manager)
: backup_manager(backup_manager) {
}


JsonDataPtr BackupMessageHandler::handle_message(const GuestInput & input) {
    NOVA_LOG_DEBUG("entering the handle_message method now ");
    if (input.method_name == "create_backup") {
        NOVA_LOG_DEBUG("handling the create_backup method");
        BackupCreationArgs args = from_input(input);
        backup_manager->run_backup(args);
        return JsonData::from_null();
    } else {
        return JsonDataPtr();
    }
}



} } } // end namespace nova::guest::backup
