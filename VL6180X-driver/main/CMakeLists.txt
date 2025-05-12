set(srcs "i2c_vl6180x_calibration.c" "../platform/platform_esp32s3.c"
           "../vl6180x_api/vl6180x_i2c.c" "../vl6180x_api/vl6180x_api.c"
           "../vl6180x_lib/vl6180x_lib.c")

idf_component_register(SRCS ${srcs}
                    INCLUDE_DIRS "." "../vl6180x_lib/include" "../vl6180x_api/include" "../platform/include")
