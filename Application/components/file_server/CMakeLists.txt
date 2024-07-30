idf_component_register(SRCS "file_server_main.c" "file_server.c" "mount.c"
                    INCLUDE_DIRS "."
                    PRIV_REQUIRES esp_http_server spiffs nvs_flash esp_event vfs esp_netif app_update esp_psram
                    EMBED_FILES "favicon.ico" "upload_script.html")
