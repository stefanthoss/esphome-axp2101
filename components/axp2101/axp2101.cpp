#include "axp2101.h"
#include "esphome/core/log.h"
#include "esp_sleep.h"
#include <Esp.h>

namespace esphome {
namespace axp2101 {

static const char *TAG = "axp2101.sensor";
void AXP2101Component::setup()
{
    Serial.printf("getID:0x%x\n", PMU.getChipID());

    // Set the minimum common working voltage of the PMU VBUS input,
    // below this value will turn off the PMU
    PMU.setVbusVoltageLimit(XPOWERS_AXP2101_VBUS_VOL_LIM_4V36);

    // Set the maximum current of the PMU VBUS input,
    // higher than this value will turn off the PMU
    PMU.setVbusCurrentLimit(XPOWERS_AXP2101_VBUS_CUR_LIM_1500MA);


    // Get the VSYS shutdown voltage
    uint16_t vol = PMU.getSysPowerDownVoltage();
    Serial.printf("->  getSysPowerDownVoltage:%u\n", vol);

    // Set VSY off voltage as 2600mV , Adjustment range 2600mV ~ 3300mV
    PMU.setSysPowerDownVoltage(2600);

    vol = PMU.getSysPowerDownVoltage();
    Serial.printf("->  getSysPowerDownVoltage:%u\n", vol);


    // DC1 IMAX=2A
    // 1500~3400mV,100mV/step,20steps
    PMU.setDC1Voltage(3300);
    Serial.printf("DC1  : %s   Voltage:%u mV \n",  PMU.isEnableDC1()  ? "+" : "-", PMU.getDC1Voltage());

    // DC2 IMAX=2A
    // 500~1200mV  10mV/step,71steps
    // 1220~1540mV 20mV/step,17steps
    PMU.setDC2Voltage(1000);
    Serial.printf("DC2  : %s   Voltage:%u mV \n",  PMU.isEnableDC2()  ? "+" : "-", PMU.getDC2Voltage());

    // DC3 IMAX = 2A
    // 500~1200mV,10mV/step,71steps
    // 1220~1540mV,20mV/step,17steps
    // 1600~3400mV,100mV/step,19steps
    PMU.setDC3Voltage(3300);
    Serial.printf("DC3  : %s   Voltage:%u mV \n",  PMU.isEnableDC3()  ? "+" : "-", PMU.getDC3Voltage());

    // DCDC4 IMAX=1.5A
    // 500~1200mV,10mV/step,71steps
    // 1220~1840mV,20mV/step,32steps
    PMU.setDC4Voltage(1000);
    Serial.printf("DC4  : %s   Voltage:%u mV \n",  PMU.isEnableDC4()  ? "+" : "-", PMU.getDC4Voltage());

    // DC5 IMAX=2A
    // 1200mV
    // 1400~3700mV,100mV/step,24steps
    PMU.setDC5Voltage(3300);
    Serial.printf("DC5  : %s   Voltage:%u mV \n",  PMU.isEnableDC5()  ? "+" : "-", PMU.getDC5Voltage());

    //ALDO1 IMAX=300mA
    //500~3500mV, 100mV/step,31steps
    PMU.setALDO1Voltage(3300);

    //ALDO2 IMAX=300mA
    //500~3500mV, 100mV/step,31steps
    PMU.setALDO2Voltage(3300);

    //ALDO3 IMAX=300mA
    //500~3500mV, 100mV/step,31steps
    PMU.setALDO3Voltage(3300);

    //ALDO4 IMAX=300mA
    //500~3500mV, 100mV/step,31steps
    PMU.setALDO4Voltage(3300);

    //BLDO1 IMAX=300mA
    //500~3500mV, 100mV/step,31steps
    PMU.setBLDO1Voltage(3300);

    //BLDO2 IMAX=300mA
    //500~3500mV, 100mV/step,31steps
    PMU.setBLDO2Voltage(3300);

    //CPUSLDO IMAX=30mA
    //500~1400mV,50mV/step,19steps
    PMU.setCPUSLDOVoltage(1000);

    //DLDO1 IMAX=300mA
    //500~3400mV, 100mV/step,29steps
    PMU.setDLDO1Voltage(3300);

    //DLDO2 IMAX=300mA
    //500~1400mV, 50mV/step,2steps
    PMU.setDLDO2Voltage(3300);


    // PMU.enableDC1();
    PMU.enableDC2();
    PMU.enableDC3();
    PMU.enableDC4();
    PMU.enableDC5();
    PMU.enableALDO1();
    PMU.enableALDO2();
    PMU.enableALDO3();
    PMU.enableALDO4();
    PMU.enableBLDO1();
    PMU.enableBLDO2();
    PMU.enableCPUSLDO();
    PMU.enableDLDO1();
    PMU.enableDLDO2();


    Serial.println("DCDC=======================================================================");
    Serial.printf("DC1  : %s   Voltage:%u mV \n",  PMU.isEnableDC1()  ? "+" : "-", PMU.getDC1Voltage());
    Serial.printf("DC2  : %s   Voltage:%u mV \n",  PMU.isEnableDC2()  ? "+" : "-", PMU.getDC2Voltage());
    Serial.printf("DC3  : %s   Voltage:%u mV \n",  PMU.isEnableDC3()  ? "+" : "-", PMU.getDC3Voltage());
    Serial.printf("DC4  : %s   Voltage:%u mV \n",  PMU.isEnableDC4()  ? "+" : "-", PMU.getDC4Voltage());
    Serial.printf("DC5  : %s   Voltage:%u mV \n",  PMU.isEnableDC5()  ? "+" : "-", PMU.getDC5Voltage());
    Serial.println("ALDO=======================================================================");
    Serial.printf("ALDO1: %s   Voltage:%u mV\n",  PMU.isEnableALDO1()  ? "+" : "-", PMU.getALDO1Voltage());
    Serial.printf("ALDO2: %s   Voltage:%u mV\n",  PMU.isEnableALDO2()  ? "+" : "-", PMU.getALDO2Voltage());
    Serial.printf("ALDO3: %s   Voltage:%u mV\n",  PMU.isEnableALDO3()  ? "+" : "-", PMU.getALDO3Voltage());
    Serial.printf("ALDO4: %s   Voltage:%u mV\n",  PMU.isEnableALDO4()  ? "+" : "-", PMU.getALDO4Voltage());
    Serial.println("BLDO=======================================================================");
    Serial.printf("BLDO1: %s   Voltage:%u mV\n",  PMU.isEnableBLDO1()  ? "+" : "-", PMU.getBLDO1Voltage());
    Serial.printf("BLDO2: %s   Voltage:%u mV\n",  PMU.isEnableBLDO2()  ? "+" : "-", PMU.getBLDO2Voltage());
    Serial.println("CPUSLDO====================================================================");
    Serial.printf("CPUSLDO: %s Voltage:%u mV\n",  PMU.isEnableCPUSLDO() ? "+" : "-", PMU.getCPUSLDOVoltage());
    Serial.println("DLDO=======================================================================");
    Serial.printf("DLDO1: %s   Voltage:%u mV\n",  PMU.isEnableDLDO1()  ? "+" : "-", PMU.getDLDO1Voltage());
    Serial.printf("DLDO2: %s   Voltage:%u mV\n",  PMU.isEnableDLDO2()  ? "+" : "-", PMU.getDLDO2Voltage());
    Serial.println("===========================================================================");

    // Set the time of pressing the button to turn off
    PMU.setPowerKeyPressOffTime(XPOWERS_POWEROFF_4S);
    uint8_t opt = PMU.getPowerKeyPressOffTime();
    Serial.print("PowerKeyPressOffTime:");
    switch (opt) {
    case XPOWERS_POWEROFF_4S: Serial.println("4 Second");
        break;
    case XPOWERS_POWEROFF_6S: Serial.println("6 Second");
        break;
    case XPOWERS_POWEROFF_8S: Serial.println("8 Second");
        break;
    case XPOWERS_POWEROFF_10S: Serial.println("10 Second");
        break;
    default:
        break;
    }
    // Set the button power-on press time
    PMU.setPowerKeyPressOnTime(XPOWERS_POWERON_128MS);
    opt = PMU.getPowerKeyPressOnTime();
    Serial.print("PowerKeyPressOnTime:");
    switch (opt) {
    case XPOWERS_POWERON_128MS: Serial.println("128 Ms");
        break;
    case XPOWERS_POWERON_512MS: Serial.println("512 Ms");
        break;
    case XPOWERS_POWERON_1S: Serial.println("1 Second");
        break;
    case XPOWERS_POWERON_2S: Serial.println("2 Second");
        break;
    default:
        break;
    }

    Serial.println("===========================================================================");

    bool en;

    // DCDC 120%(130%) high voltage turn off PMIC function
    en = PMU.getDCHighVoltagePowerDowmEn();
    Serial.print("getDCHighVoltagePowerDowmEn:");
    Serial.println(en ? "ENABLE" : "DISABLE");
    // DCDC1 85% low voltage turn off PMIC function
    en = PMU.getDC1LowVoltagePowerDowmEn();
    Serial.print("getDC1LowVoltagePowerDowmEn:");
    Serial.println(en ? "ENABLE" : "DISABLE");
    // DCDC2 85% low voltage turn off PMIC function
    en = PMU.getDC2LowVoltagePowerDowmEn();
    Serial.print("getDC2LowVoltagePowerDowmEn:");
    Serial.println(en ? "ENABLE" : "DISABLE");
    // DCDC3 85% low voltage turn off PMIC function
    en = PMU.getDC3LowVoltagePowerDowmEn();
    Serial.print("getDC3LowVoltagePowerDowmEn:");
    Serial.println(en ? "ENABLE" : "DISABLE");
    // DCDC4 85% low voltage turn off PMIC function
    en = PMU.getDC4LowVoltagePowerDowmEn();
    Serial.print("getDC4LowVoltagePowerDowmEn:");
    Serial.println(en ? "ENABLE" : "DISABLE");
    // DCDC5 85% low voltage turn off PMIC function
    en = PMU.getDC5LowVoltagePowerDowmEn();
    Serial.print("getDC5LowVoltagePowerDowmEn:");
    Serial.println(en ? "ENABLE" : "DISABLE");

    // PMU.setDCHighVoltagePowerDowm(true);
    // PMU.setDC1LowVoltagePowerDowm(true);
    // PMU.setDC2LowVoltagePowerDowm(true);
    // PMU.setDC3LowVoltagePowerDowm(true);
    // PMU.setDC4LowVoltagePowerDowm(true);
    // PMU.setDC5LowVoltagePowerDowm(true);

    // It is necessary to disable the detection function of the TS pin on the board
    // without the battery temperature detection function, otherwise it will cause abnormal charging
    PMU.disableTSPinMeasure();

    // PMU.enableTemperatureMeasure();

    // Enable internal ADC detection
    PMU.enableBattDetection();
    PMU.enableVbusVoltageMeasure();
    PMU.enableBattVoltageMeasure();
    PMU.enableSystemVoltageMeasure();


    /*
      The default setting is CHGLED is automatically controlled by the PMU.
    - XPOWERS_CHG_LED_OFF,
    - XPOWERS_CHG_LED_BLINK_1HZ,
    - XPOWERS_CHG_LED_BLINK_4HZ,
    - XPOWERS_CHG_LED_ON,
    - XPOWERS_CHG_LED_CTRL_CHG,
    * */
    PMU.setChargingLedMode(XPOWERS_CHG_LED_OFF);


    // Force add pull-up
    pinMode(pmu_irq_pin, INPUT_PULLUP);
    attachInterrupt(pmu_irq_pin, setFlag, FALLING);


    // Disable all interrupts
    PMU.disableIRQ(XPOWERS_AXP2101_ALL_IRQ);
    // Clear all interrupt flags
    PMU.clearIrqStatus();
    // Enable the required interrupt function
    PMU.enableIRQ(
        XPOWERS_AXP2101_BAT_INSERT_IRQ    | XPOWERS_AXP2101_BAT_REMOVE_IRQ      |   //BATTERY
        XPOWERS_AXP2101_VBUS_INSERT_IRQ   | XPOWERS_AXP2101_VBUS_REMOVE_IRQ     |   //VBUS
        XPOWERS_AXP2101_PKEY_SHORT_IRQ    | XPOWERS_AXP2101_PKEY_LONG_IRQ       |   //POWER KEY
        XPOWERS_AXP2101_BAT_CHG_DONE_IRQ  | XPOWERS_AXP2101_BAT_CHG_START_IRQ       //CHARGE
        // XPOWERS_AXP2101_PKEY_NEGATIVE_IRQ | XPOWERS_AXP2101_PKEY_POSITIVE_IRQ   |   //POWER KEY
    );

    // Set the precharge charging current
    PMU.setPrechargeCurr(XPOWERS_AXP2101_PRECHARGE_50MA);
    // Set constant current charge current limit
    PMU.setChargerConstantCurr(XPOWERS_AXP2101_CHG_CUR_200MA);
    // Set stop charging termination current
    PMU.setChargerTerminationCurr(XPOWERS_AXP2101_CHG_ITERM_25MA);

    // Set charge cut-off voltage
    PMU.setChargeTargetVoltage(XPOWERS_AXP2101_CHG_VOL_4V1);

    // Set the watchdog trigger event type
    PMU.setWatchdogConfig(XPOWERS_AXP2101_WDT_IRQ_TO_PIN);
    // Set watchdog timeout
    PMU.setWatchdogTimeout(XPOWERS_AXP2101_WDT_TIMEOUT_4S);
    // Enable watchdog to trigger interrupt event
    PMU.enableWatchdog();

    // PMU.disableWatchdog();

    // Enable Button Battery charge
    PMU.enableButtonBatteryCharge();

    // Set Button Battery charge voltage
    PMU.setButtonBatteryChargeVoltage(3300);
}

void AXP2101Component::dump_config() {
  ESP_LOGCONFIG(TAG, "AXP2101:");
  LOG_I2C_DEVICE(this);
  LOG_SENSOR("  ", "Battery Level", this->batterylevel_sensor_);
}

float AXP2101Component::get_setup_priority() const { return setup_priority::DATA; }

void AXP2101Component::update() {

    if (this->batterylevel_sensor_ != nullptr) {
      float vbat = PMU.getBattVoltage();

      // The battery percentage may be inaccurate at first use, the PMU will automatically
      // learn the battery curve and will automatically calibrate the battery percentage
      // after a charge and discharge cycle
      float batterylevel;
      if (PMU.isBatteryConnect()) {
        batterylevel = PMU.getBatteryPercent();
      } else {
        batterylevel = 100.0 * ((vbat - 3.0) / (4.1 - 3.0));
      }

      ESP_LOGD(TAG, "Got Battery Level=%f (%f)", batterylevel, vbat);
      if (batterylevel > 100.) {
        batterylevel = 100;
      }
      this->batterylevel_sensor_->publish_state(batterylevel);
    }

    UpdateBrightness();
}

void AXP2101Component::Write1Byte( uint8_t Addr ,  uint8_t Data )
{
    this->write_byte(Addr, Data);
}

uint8_t AXP2101Component::Read8bit( uint8_t Addr )
{
    uint8_t data;
    this->read_byte(Addr, &data);
    return data;
}

uint16_t AXP2101Component::Read12Bit( uint8_t Addr)
{
    uint16_t Data = 0;
    uint8_t buf[2];
    ReadBuff(Addr,2,buf);
    Data = ((buf[0] << 4) + buf[1]); //
    return Data;
}

uint16_t AXP2101Component::Read13Bit( uint8_t Addr)
{
    uint16_t Data = 0;
    uint8_t buf[2];
    ReadBuff(Addr,2,buf);
    Data = ((buf[0] << 5) + buf[1]); //
    return Data;
}

uint16_t AXP2101Component::Read16bit( uint8_t Addr )
{
    uint32_t ReData = 0;
    uint8_t Buff[2];
    this->read_bytes(Addr, Buff, sizeof(Buff));
    for( int i = 0 ; i < sizeof(Buff) ; i++ )
    {
        ReData <<= 8;
        ReData |= Buff[i];
    }
    return ReData;
}

uint32_t AXP2101Component::Read24bit( uint8_t Addr )
{
    uint32_t ReData = 0;
    uint8_t Buff[3];
    this->read_bytes(Addr, Buff, sizeof(Buff));
    for( int i = 0 ; i < sizeof(Buff) ; i++ )
    {
        ReData <<= 8;
        ReData |= Buff[i];
    }
    return ReData;
}

uint32_t AXP2101Component::Read32bit( uint8_t Addr )
{
    uint32_t ReData = 0;
    uint8_t Buff[4];
    this->read_bytes(Addr, Buff, sizeof(Buff));
    for( int i = 0 ; i < sizeof(Buff) ; i++ )
    {
        ReData <<= 8;
        ReData |= Buff[i];
    }
    return ReData;
}

void AXP2101Component::ReadBuff( uint8_t Addr , uint8_t Size , uint8_t *Buff )
{
    this->read_bytes(Addr, Buff, Size);
}

void AXP2101Component::UpdateBrightness()
{
    if (brightness_ == curr_brightness_)
    {
        return;
    }

    ESP_LOGD(TAG, "Brightness=%f (Curr: %f)", brightness_, curr_brightness_);
    curr_brightness_ = brightness_;

    const uint8_t c_min = 7;
    const uint8_t c_max = 12;
    auto ubri = c_min + static_cast<uint8_t>(brightness_ * (c_max - c_min));

    if (ubri > c_max)
    {
        ubri = c_max;
    }
    switch (this->model_) {
      case AXP2101_M5STICKC:
      {
        uint8_t buf = Read8bit( 0x28 );
        Write1Byte( 0x28 , ((buf & 0x0f) | (ubri << 4)) );
        break;
      }
      case AXP2101_M5CORE2:
      {
        uint8_t buf = Read8bit( 0x27 );
        Write1Byte( 0x27 , ((buf & 0x80) | (ubri << 3)) );
        break;
      }
      case AXP2101_M5TOUGH:
      {
        uint8_t buf = Read8bit( 0x27 );
        Write1Byte( 0x27 , ((buf & 0x80) | (ubri << 3)) );
        break;
      }
    }
}

bool AXP2101Component::GetBatState()
{
    if( Read8bit(0x01) | 0x20 )
        return true;
    else
        return false;
}

uint8_t AXP2101Component::GetBatData()
{
    return Read8bit(0x75);
}
//---------coulombcounter_from_here---------
//enable: void EnableCoulombcounter(void);
//disable: void DisableCOulombcounter(void);
//stop: void StopCoulombcounter(void);
//clear: void ClearCoulombcounter(void);
//get charge data: uint32_t GetCoulombchargeData(void);
//get discharge data: uint32_t GetCoulombdischargeData(void);
//get coulomb val affter calculation: float GetCoulombData(void);
//------------------------------------------
void  AXP2101Component::EnableCoulombcounter(void)
{
    Write1Byte( 0xB8 , 0x80 );
}

void  AXP2101Component::DisableCoulombcounter(void)
{
    Write1Byte( 0xB8 , 0x00 );
}

void  AXP2101Component::StopCoulombcounter(void)
{
    Write1Byte( 0xB8 , 0xC0 );
}

void  AXP2101Component::ClearCoulombcounter(void)
{
    Write1Byte( 0xB8 , 0xA0 );
}

uint32_t AXP2101Component::GetCoulombchargeData(void)
{
    return Read32bit(0xB0);
}

uint32_t AXP2101Component::GetCoulombdischargeData(void)
{
    return Read32bit(0xB4);
}

float AXP2101Component::GetCoulombData(void)
{

  uint32_t coin = 0;
  uint32_t coout = 0;

  coin = GetCoulombchargeData();
  coout = GetCoulombdischargeData();

  //c = 65536 * current_LSB * (coin - coout) / 3600 / ADC rate
  //Adc rate can be read from 84H ,change this variable if you change the ADC reate
  float ccc = 65536 * 0.5 * (coin - coout) / 3600.0 / 25.0;
  return ccc;

}
//----------coulomb_end_at_here----------

uint16_t AXP2101Component::GetVbatData(void){

    uint16_t vbat = 0;
    uint8_t buf[2];
    ReadBuff(0x78,2,buf);
    vbat = ((buf[0] << 4) + buf[1]); // V
    return vbat;
}

uint16_t AXP2101Component::GetVinData(void)
{
    uint16_t vin = 0;
    uint8_t buf[2];
    ReadBuff(0x56,2,buf);
    vin = ((buf[0] << 4) + buf[1]); // V
    return vin;
}

uint16_t AXP2101Component::GetIinData(void)
{
    uint16_t iin = 0;
    uint8_t buf[2];
    ReadBuff(0x58,2,buf);
    iin = ((buf[0] << 4) + buf[1]);
    return iin;
}

uint16_t AXP2101Component::GetVusbinData(void)
{
    uint16_t vin = 0;
    uint8_t buf[2];
    ReadBuff(0x5a,2,buf);
    vin = ((buf[0] << 4) + buf[1]); // V
    return vin;
}

uint16_t AXP2101Component::GetIusbinData(void)
{
    uint16_t iin = 0;
    uint8_t buf[2];
    ReadBuff(0x5C,2,buf);
    iin = ((buf[0] << 4) + buf[1]);
    return iin;
}

uint16_t AXP2101Component::GetIchargeData(void)
{
    uint16_t icharge = 0;
    uint8_t buf[2];
    ReadBuff(0x7A,2,buf);
    icharge = ( buf[0] << 5 ) + buf[1] ;
    return icharge;
}

uint16_t AXP2101Component::GetIdischargeData(void)
{
    uint16_t idischarge = 0;
    uint8_t buf[2];
    ReadBuff(0x7C,2,buf);
    idischarge = ( buf[0] << 5 ) + buf[1] ;
    return idischarge;
}

uint16_t AXP2101Component::GetTempData(void)
{
    uint16_t temp = 0;
    uint8_t buf[2];
    ReadBuff(0x5e,2,buf);
    temp = ((buf[0] << 4) + buf[1]);
    return temp;
}

uint32_t AXP2101Component::GetPowerbatData(void)
{
    uint32_t power = 0;
    uint8_t buf[3];
    ReadBuff(0x70,2,buf);
    power = (buf[0] << 16) + (buf[1] << 8) + buf[2];
    return power;
}

uint16_t AXP2101Component::GetVapsData(void)
{
    uint16_t vaps = 0;
    uint8_t buf[2];
    ReadBuff(0x7e,2,buf);
    vaps = ((buf[0] << 4) + buf[1]);
    return vaps;
}

void AXP2101Component::SetSleep(void)
{
    Write1Byte(0x31 , Read8bit(0x31) | ( 1 << 3)); // Power off voltag 3.0v
    Write1Byte(0x90 , Read8bit(0x90) | 0x07); // GPIO1 floating
    Write1Byte(0x82, 0x00); // Disable ADCs
    Write1Byte(0x12, Read8bit(0x12) & 0xA1); // Disable all outputs but DCDC1
}

// -- sleep
void AXP2101Component::DeepSleep(uint64_t time_in_us)
{
    SetSleep();
    esp_sleep_enable_ext0_wakeup((gpio_num_t)37, 0 /* LOW */);
    if (time_in_us > 0)
    {
        esp_sleep_enable_timer_wakeup(time_in_us);
    }
    else
    {
        esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_TIMER);
    }
    (time_in_us == 0) ? esp_deep_sleep_start() : esp_deep_sleep(time_in_us);
}

void AXP2101Component::LightSleep(uint64_t time_in_us)
{
    if (time_in_us > 0)
    {
        esp_sleep_enable_timer_wakeup(time_in_us);
    }
    else
    {
        esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_TIMER);
    }
    esp_light_sleep_start();
}

// 0 not press, 0x01 long press, 0x02 press
uint8_t AXP2101Component::GetBtnPress()
{
    uint8_t state = Read8bit(0x46);
    if(state)
    {
        Write1Byte( 0x46 , 0x03 );
    }
    return state;
}

uint8_t AXP2101Component::GetWarningLevel(void)
{
    return Read8bit(0x47) & 0x01;
}

float AXP2101Component::GetBatCurrent()
{
    float ADCLSB = 0.5;
    uint16_t CurrentIn = Read13Bit( 0x7A );
    uint16_t CurrentOut = Read13Bit( 0x7C );
    return ( CurrentIn - CurrentOut ) * ADCLSB;
}

float AXP2101Component::GetVinVoltage()
{
    float ADCLSB = 1.7 / 1000.0;
    uint16_t ReData = Read12Bit( 0x56 );
    return ReData * ADCLSB;
}

float AXP2101Component::GetVinCurrent()
{
    float ADCLSB = 0.625;
    uint16_t ReData = Read12Bit( 0x58 );
    return ReData * ADCLSB;
}

float AXP2101Component::GetVBusVoltage()
{
    float ADCLSB = 1.7 / 1000.0;
    uint16_t ReData = Read12Bit( 0x5A );
    return ReData * ADCLSB;
}

float AXP2101Component::GetVBusCurrent()
{
    float ADCLSB = 0.375;
    uint16_t ReData = Read12Bit( 0x5C );
    return ReData * ADCLSB;
}

float AXP2101Component::GetTempInAXP2101()
{
    float ADCLSB = 0.1;
    const float OFFSET_DEG_C = -144.7;
    uint16_t ReData = Read12Bit( 0x5E );
    return OFFSET_DEG_C + ReData * ADCLSB;
}

float AXP2101Component::GetBatPower()
{
    float VoltageLSB = 1.1;
    float CurrentLCS = 0.5;
    uint32_t ReData = Read24bit( 0x70 );
    return  VoltageLSB * CurrentLCS * ReData/ 1000.0;
}

float AXP2101Component::GetBatChargeCurrent()
{
    float ADCLSB = 0.5;
    uint16_t ReData = Read13Bit( 0x7A );
    return ReData * ADCLSB;
}

float AXP2101Component::GetAPSVoltage()
{
    float ADCLSB = 1.4  / 1000.0;
    uint16_t ReData = Read12Bit( 0x7E );
    return ReData * ADCLSB;
}

float AXP2101Component::GetBatCoulombInput()
{
    uint32_t ReData = Read32bit( 0xB0 );
    return ReData * 65536 * 0.5 / 3600 /25.0;
}

float AXP2101Component::GetBatCoulombOut()
{
    uint32_t ReData = Read32bit( 0xB4 );
    return ReData * 65536 * 0.5 / 3600 /25.0;
}

void AXP2101Component::SetCoulombClear()
{
    Write1Byte(0xB8,0x20);
}

void AXP2101Component::SetLDO2( bool State )
{
    uint8_t buf = Read8bit(0x12);
    if( State == true )
    {
        buf = (1<<2) | buf;
    }
    else
    {
        buf = ~(1<<2) & buf;
    }
    Write1Byte( 0x12 , buf );
}

void AXP2101Component::SetLDO3(bool State)
{
    uint8_t buf = Read8bit(0x12);
    if( State == true )
    {
        buf = (1<<3) | buf;
    }
    else
    {
        buf = ~(1<<3) & buf;
    }
    Write1Byte( 0x12 , buf );
}

void AXP2101Component::SetChargeCurrent(uint8_t current)
{
    uint8_t buf = Read8bit(0x33);
    buf = (buf & 0xf0) | (current & 0x07);
    Write1Byte(0x33, buf);
}

void AXP2101Component::PowerOff()
{
    Write1Byte(0x32, Read8bit(0x32) | 0x80);
}

void AXP2101Component::SetAdcState(bool state)
{
    Write1Byte(0x82, state ? 0xff : 0x00);
}

std::string AXP2101Component::GetStartupReason() {
  esp_reset_reason_t reset_reason = ::esp_reset_reason();
  if (reset_reason == ESP_RST_DEEPSLEEP) {
    esp_sleep_source_t wake_reason = esp_sleep_get_wakeup_cause();
    if (wake_reason == ESP_SLEEP_WAKEUP_EXT0)
      return "ESP_SLEEP_WAKEUP_EXT0";
    if (wake_reason == ESP_SLEEP_WAKEUP_EXT0)
      return "ESP_SLEEP_WAKEUP_EXT0";
    if (wake_reason == ESP_SLEEP_WAKEUP_EXT1)
      return "ESP_SLEEP_WAKEUP_EXT1";
    if (wake_reason == ESP_SLEEP_WAKEUP_TIMER)
      return "ESP_SLEEP_WAKEUP_TIMER";
    if (wake_reason == ESP_SLEEP_WAKEUP_TOUCHPAD)
      return "ESP_SLEEP_WAKEUP_TOUCHPAD";
    if (wake_reason == ESP_SLEEP_WAKEUP_ULP)
      return "ESP_SLEEP_WAKEUP_ULP";
    if (wake_reason == ESP_SLEEP_WAKEUP_GPIO)
      return "ESP_SLEEP_WAKEUP_GPIO";
    if (wake_reason == ESP_SLEEP_WAKEUP_UART)
      return "ESP_SLEEP_WAKEUP_UART";
    return std::string{"WAKEUP_UNKNOWN_REASON"};
  }

  if (reset_reason == ESP_RST_UNKNOWN)
    return "ESP_RST_UNKNOWN";
  if (reset_reason == ESP_RST_POWERON)
    return "ESP_RST_POWERON";
  if (reset_reason == ESP_RST_SW)
    return "ESP_RST_SW";
  if (reset_reason == ESP_RST_PANIC)
    return "ESP_RST_PANIC";
  if (reset_reason == ESP_RST_INT_WDT)
    return "ESP_RST_INT_WDT";
  if (reset_reason == ESP_RST_TASK_WDT)
    return "ESP_RST_TASK_WDT";
  if (reset_reason == ESP_RST_WDT)
    return "ESP_RST_WDT";
  if (reset_reason == ESP_RST_BROWNOUT)
    return "ESP_RST_BROWNOUT";
  if (reset_reason == ESP_RST_SDIO)
    return "ESP_RST_SDIO";
  return std::string{"RESET_UNKNOWN_REASON"};
}

}
}
