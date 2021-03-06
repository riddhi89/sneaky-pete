#include <stdio.h>
#include <iostream>
#include "nova/Log.h"
#include "nova/VolumeManager.h"
#include <boost/algorithm/string.hpp>

using namespace std;
using nova::Log;
using nova::LogApiScope;
using nova::LogOptions;
using nova::VolumeManager;
using nova::VolumeDevice;


int main(int argc, char **argv)
{
    LogApiScope log(LogOptions::simple());

    if (argc < 4) {
        cerr << "Usage: " << (argc > 0 ? argv[0] : "mount_file")
        << " device_path mount_point write_to_fstab" << endl;
        return 1;
    }

    const string device_path = argv[1];
    const string mount_point = argv[2];
    string write_to_fstab = argv[3];

    bool write_to_fstab_bool = false;
    boost::algorithm::to_lower(write_to_fstab);
    if (write_to_fstab == "true") {
        write_to_fstab_bool = true;
    }

    const unsigned int num_tries_device_exists = 3;
    const string volume_fstype = "ext3";
    const string format_options = "-m 5";
    const unsigned int volume_format_timeout = 120;
    const string mount_options = "defaults,noatime";

    /* Create Volume Manager. */
    VolumeManager volumeManager(
        num_tries_device_exists,
        volume_fstype,
        format_options,
        volume_format_timeout,
        "/mount_point",
        mount_options
    );

    NOVA_LOG_INFO("Creating volume device with device_path: %s", device_path.c_str());
    VolumeDevice vol_device = volumeManager.create_volume_device(device_path);

    NOVA_LOG_INFO("Mounting volume device to: %s", mount_point.c_str());
    vol_device.mount(mount_point, write_to_fstab_bool);

    NOVA_LOG_INFO("Mounted the volume.");

    return 0;
}
