#include "string.h"
#include "unistd.h"
#include "sys/stat.h"
#include "esp_vfs_fat.h"
#include "driver/sdmmc_host.h"
#include "driver/sdspi_host.h"

#include "SD.h"

bool SDClass::begin(int miso, int mosi, int sck, int cs)
{
    sdmmc_host_t host = SDSPI_HOST_DEFAULT();
    sdspi_slot_config_t slot_config = SDSPI_SLOT_CONFIG_DEFAULT();
    slot_config.gpio_miso = (gpio_num_t)miso;
    slot_config.gpio_mosi = (gpio_num_t)mosi;
    slot_config.gpio_sck  = (gpio_num_t)sck;
    slot_config.gpio_cs   = (gpio_num_t)cs;
    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
        .format_if_mount_failed = false,
        .max_files = 8
    };
    return esp_vfs_fat_sdmmc_mount(mountPoint, &host, &slot_config, &mount_config, NULL) == ESP_OK;
}

bool SDClass::end()
{
    return esp_vfs_fat_sdmmc_unmount() == ESP_OK;
}

bool SDClass::exists(char *path)
{
    return ::access(realpath(path), F_OK) != -1;
}

bool SDClass::mkdir(char *path)
{
    return ::mkdir(realpath(path), 0777);
}

FILE *SDClass::open(char *path, char *mode)
{
    return ::fopen(realpath(path), mode);
}

bool SDClass::remove(char *path)
{
    return ::unlink(realpath(path));
}

bool SDClass::rename(char *path, char *newPath)
{
    return ::rename(realpath(path), realpath(newPath));
}

bool SDClass::rmdir(char *path)
{
    return ::rmdir(realpath(path));
}

char *SDClass::realpath(char *path)
{
    char buffer[256];
    sprintf(buffer, "%s/%s", mountPoint, path);
    return path;
}

SDClass SD;
