#include "freertos/FreeRTOS.h"
#include "lwip/ip_addr.h"
#include "esp_system.h"
#include "esp_event_loop.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "string.h"
#include "WiFi.h"

static esp_err_t eventHandler(void *ctx, system_event_t *event)
{
    wl_status_t *_status = (wl_status_t*)ctx;
    switch (event->event_id) {
        case SYSTEM_EVENT_STA_GOT_IP:
            //strcpy(_localIP, ip4addr_ntoa(&event->event_info.got_ip.ip_info.ip));
            *_status = WL_CONNECTED;
            break;
        case SYSTEM_EVENT_STA_CONNECTED:
            //*_status = WL_CONNECTED;
            break;
        case SYSTEM_EVENT_STA_DISCONNECTED:
            *_status = WL_CONNECTION_LOST;
            break;
        default:
            break;
    }
    return ESP_OK;
}

bool WiFiClass::init()
{
    if (_status == WL_NOT_INIT) {
        wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
        esp_log_level_set("wifi", ESP_LOG_WARN);
        tcpip_adapter_init();
        ESP_ERROR_CHECK(esp_wifi_init(&cfg));
        ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
        esp_event_loop_init(&eventHandler, &_status);
        _status = WL_IDLE_STATUS;
    }
    return true;
}

bool WiFiClass::deinit()
{
    if (_status != WL_NOT_INIT) {
        esp_wifi_stop();
        esp_wifi_deinit();
        _status = WL_NOT_INIT;
    }
    return true;
}

wl_status_t WiFiClass::begin()
{
    if (init() && (_status != WL_CONNECTED || _mode != WL_MODE_STA)) {
        ESP_ERROR_CHECK_WITHOUT_ABORT(esp_wifi_set_mode(WIFI_MODE_STA));
        ESP_ERROR_CHECK_WITHOUT_ABORT(esp_wifi_set_config(ESP_IF_WIFI_STA, &_config));
        ESP_ERROR_CHECK_WITHOUT_ABORT(esp_wifi_start());
        if (esp_wifi_connect() == ESP_OK) {
            _status = WL_CONNECTING;
            _mode = WL_MODE_STA;
        } else {
            _status = WL_CONNECT_FAILED;
            _mode = WL_MODE_STA;
        }
    }
    return _status;
}

wl_status_t WiFiClass::begin(char* ssid, char *password, int channel)
{
    disconnect(false);

    memset(&_config, 0, sizeof(_config));
    strncpy((char*)_config.sta.ssid, ssid, 32);
    strncpy((char*)_config.sta.password, password ?: "", 64);
    _config.sta.channel = channel;

    return begin();
}

wl_status_t WiFiClass::beginAP(char* ssid, char *password, int channel)
{
    disconnect(false);

    memset(&_config, 0, sizeof(_config));
    strncpy((char*)_config.ap.ssid, ssid, 32);
    strncpy((char*)_config.ap.password, password ?: "", 64);
    _config.ap.authmode = _config.ap.password[0] ? WIFI_AUTH_WPA_PSK : WIFI_AUTH_OPEN;
    _config.ap.max_connection = 4;
    _config.ap.channel = channel;

    return beginAP();
}

wl_status_t WiFiClass::beginAP()
{
    if (init() && (_status != WL_CONNECTED || _mode != WL_MODE_AP)) {
        ESP_ERROR_CHECK_WITHOUT_ABORT(esp_wifi_set_mode(WIFI_MODE_AP));
        ESP_ERROR_CHECK_WITHOUT_ABORT(esp_wifi_set_config(ESP_IF_WIFI_AP, &_config));
        _mode = WL_MODE_AP;
        _status = WL_CONNECTED;
    }
    return _status;
}

wl_status_t WiFiClass::waitForResult()
{
    while (_status == WL_CONNECTING) {
        vPortYield();
    }
    return _status;
}

wl_status_t WiFiClass::reconnect()
{
    disconnect();
    return begin();
}

wl_status_t WiFiClass::disconnect(bool wifioff)
{
    if (_status == WL_CONNECTED) {
        esp_wifi_disconnect();
        _status = WL_DISCONNECTED;
    }
    if (wifioff) {
        deinit();
    }
    return _status;
}

const char* WiFiClass::localIP()
{
    tcpip_adapter_ip_info_t net;
    tcpip_adapter_get_ip_info((_mode == WL_MODE_STA) ? TCPIP_ADAPTER_IF_STA : TCPIP_ADAPTER_IF_AP, &net);
    return strcpy(_localIP, ip4addr_ntoa(&net.ip));
}

const char* WiFiClass::macAddress()
{
    esp_read_mac((uint8_t*)_macAddress, (_mode == WL_MODE_STA) ? ESP_MAC_WIFI_STA : ESP_MAC_WIFI_SOFTAP);
    return _macAddress;
}

int8_t WiFiClass::RSSI()
{
    wifi_ap_record_t wifidata;
    if (esp_wifi_sta_get_ap_info(&wifidata) == ESP_OK) {
        return wifidata.rssi;
    }
    return 0;
}

WiFiClass WiFi;
