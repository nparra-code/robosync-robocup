#include "vl6180x_lib.h"

#define I2C_SCL 15
#define I2C_SDA 16

#define N_MEASURE_AVG   10

int Sample_InitForOffsetCalib(VL6180xDev_t myDev){
    int status = 1, init_status = 1;
    init_status = VL6180x_InitData(myDev);
    vTaskDelay(1/portTICK_PERIOD_MS); // your code sleep at least 1 msec
    ESP_LOGI("VL6180x", "init_status %d", init_status);
    if(init_status == 0 || init_status == CALIBRATION_WARNING ){
        status = VL6180x_Prepare(myDev);
        ESP_LOGI("VL6180x", "Prepare status %d", status);
        if( !status )
            status=init_status; // if prepare is successfull return potential init warning
    }
    return status; 
}

int Sample_OffsetRunCalibration(VL6180xDev_t myDev)
{
    VL6180x_RangeData_t Range[N_MEASURE_AVG];
    int32_t   RangeSum;
    int status = 1;
    int i;
    int offset;
    int RealTargetDistance;
    /* Real target distance is 50 mm in proximity ranging configuration (scaling x1) or 100 mm in extended-range configuration */
    RealTargetDistance = (VL6180x_UpscaleGetScaling(myDev)==1) ? 50 : 100;
    
    /* Turn off wrap-around filter (to avoid first invalid distances and decrease number of I2C accesses at maximum) */
    VL6180x_FilterSetState(myDev, 0);
    /* Clear all interrupts */
    status = VL6180x_ClearAllInterrupt(myDev);
    if( status ){
        ESP_LOGE("VL6180x", "VL6180x_ClearAllInterrupt  fail");
    }
    /* Ask user to place a white target at know RealTargetDistance */
    ESP_LOGI("VL6180x", "Calibrating : place white target at %dmm", RealTargetDistance);
    
    /* Program a null offset */
    VL6180x_SetOffsetCalibrationData(myDev, 0);
    
    /* Perform several ranging measurement */
    for( i=0; i<N_MEASURE_AVG; i++){
        status = VL6180x_RangePollMeasurement(myDev, &Range[i]);
        ESP_LOGI("VL6180x", "Doing VL6180x_RangePollMeasurement");
        if( status ){
            ESP_LOGE("VL6180x", "VL6180x_RangePollMeasurement  fail");
            i--;
        }
        if( Range[i].errorStatus != 0 ){
            ESP_LOGE("VL6180x", "No target detect. ");
            i--;
        }
        vTaskDelay(1000/portTICK_PERIOD_MS); // your code sleep at least 1 msec
    }
    
    /* Calculate ranging average (sum) */
    RangeSum=0;
    for( i=0; i<N_MEASURE_AVG; i++){
        RangeSum+= Range[i].range_mm;
    }
    
    /* Calculate part-to-part offset */
    offset = RealTargetDistance - (RangeSum/N_MEASURE_AVG);
    ESP_LOGI("VL6180x", "offset: %d", offset);
    return offset;
}

uint8_t Sample_OffsetCalibrate(VL6180xDev_t myDev) {
    VL6180x_RangeData_t Range;
    int offset;
    int status;
    /* init device */
    status = Sample_InitForOffsetCalib(myDev);
    if( status < 0 ){
        ESP_LOGE("VL6180x", "Sample_InitForOffsetCalib  fail");
        return 0;
    } else {
        ESP_LOGI("VL6180x", "Sample_InitForOffsetCalib  success");
    }
    /* run calibration */
    offset = Sample_OffsetRunCalibration(myDev);
    ESP_LOGI("VL6180x", "offset adjusted: %d", offset);
    /* when possible reset re-init device otherwise set back required filter */
    VL6180x_FilterSetState(myDev, 1);  // turn on wrap around filter again
    
    // /* program offset */
    VL6180x_SetOffsetCalibrationData(myDev, offset);
    
    /* Perform ranging measurement to check */
    do {
        VL6180x_RangePollMeasurement(myDev, &Range);
        if (Range.errorStatus == 0 )
            // MyDev_ShowRange(myDev, Range.range_mm,0); // your code display range in mm
            ESP_LOGI("VL6180x", "Range %ld", Range.range_mm);
        else
            // MyDev_ShowErr(myDev, Range.errorStatus); // your code display error code
            ESP_LOGE("VL6180x", "Error %lu", Range.errorStatus);
        vTaskDelay(500/portTICK_PERIOD_MS);
    } while (true); // your code to stop looping

    return offset;
}

void app_main(void)
{
    // Initialize the VL6180x sensor
    VL6180x_t vl6180x_dev;
    vl6180x_dev.addr = VL6180X_I2C_ADDR; // Default I2C address
    vl6180x_dev.irq = 0; // No IRQ pin used

    // Initialize the I2C driver
    VL6180x_Init(&vl6180x_dev, I2C_NUM_1, I2C_SCL, I2C_SDA);
    
    Sample_OffsetCalibrate(vl6180x_dev.i2c_handle);
}