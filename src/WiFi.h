#ifndef _WiFi_h_
#define _WiFi_h_

#include "esp_wifi.h"

typedef enum {
    WL_NOT_INIT         = 0,
    WL_IDLE_STATUS      = 1,
    WL_NO_SSID_AVAIL    = 2,
    WL_SCAN_COMPLETED   = 3,
    WL_CONNECTING       = 4,
    WL_CONNECTED        = 5,
    WL_CONNECT_FAILED   = 6,
    WL_CONNECTION_LOST  = 7,
    WL_DISCONNECTED     = 8,
    WL_AP_READY         = 9,
} wl_status_t;

typedef enum {
    WL_MODE_NONE,
    WL_MODE_STA,
    WL_MODE_AP
} wl_mode_t;

class WiFiClass
{
  private:
    wl_status_t _status = WL_NOT_INIT;
    wl_mode_t _mode = WL_MODE_NONE;
    wifi_config_t _config = {};
    char _localIP[32];
    char _macAddress[32];

    bool init();
    bool deinit();

  public:
    wl_status_t status() { return _status; }
    wl_mode_t   mode() { return _mode; }
    const char* SSID() { return (char*)_config.ap.ssid; }
    const char* localIP();
    const char* macAddress();
    int8_t RSSI();

    wl_status_t begin();
    wl_status_t begin(char* ssid, char *password = nullptr, int channel = 0);
    wl_status_t stop(bool wifioff = false) { return disconnect(true); }

    wl_status_t beginAP();
    wl_status_t beginAP(char* ssid, char *password = nullptr, int channel = 0);
    wl_status_t stopAP(bool wifioff = false) { return disconnect(true); }

    wl_status_t waitForResult();
    wl_status_t reconnect();
    wl_status_t disconnect(bool wifioff = false);
};

extern WiFiClass WiFi;

#endif
