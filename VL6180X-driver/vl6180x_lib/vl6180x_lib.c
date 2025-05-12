#include "vl6180x_lib.h"

void VL6180x_Init(VL6180x_t *vl6180x_i2c, i2c_port_t port, uint8_t scl, uint8_t sda){

    if(!i2c_init(&vl6180x_i2c->i2c_handle, port, scl, sda, I2C_FREQUENCY, vl6180x_i2c->addr)){
        ESP_LOGE("VL6180x", "I2C init failed");
        return;
    }

    VL6180xDev_t myDev = vl6180x_i2c->i2c_handle;

    vTaskDelay(10/portTICK_PERIOD_MS);

    int status = 1, init_status = VL6180x_InitData(myDev);
    ESP_LOGI("VL6180x", "init_status %d", init_status);
    if(init_status == 0 || init_status == CALIBRATION_WARNING ){
        status = VL6180x_Prepare(myDev);
        ESP_LOGI("VL6180x", "Prepare status %d", status);
        if( !status )
            status=init_status; // if prepare is successfull return potential init warning
    }
}

void VL6180x_Deinit(VL6180x_t *vl6180x_i2c)
{
    i2c_deinit(&vl6180x_i2c->i2c_handle);
    gpio_deinit(&vl6180x_i2c->gpio_handle);
}

int32_t VL6180x_GetRange(VL6180x_t *vl6180x_i2c){

    VL6180xDev_t myDev = vl6180x_i2c->i2c_handle;
    VL6180x_RangeData_t Range;

    VL6180x_RangePollMeasurement(myDev, &Range);
        if (Range.errorStatus == 0 )
            //ESP_LOGI("VL6180x", "Range %ld mm", Range.range_mm); // your code display range in mm
            ESP_LOGI("VL6180x", "Range obtained.");
        else
            ESP_LOGE("VL6180x", "Range error %lu", Range.errorStatus);

        vTaskDelay(1000/portTICK_PERIOD_MS); // your code sleep at least 1 msec
        return Range.range_mm;
}