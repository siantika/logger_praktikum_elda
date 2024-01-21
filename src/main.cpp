/*
 * main.cpp or driver code.
 * Created by: I Putu Pawesi Siantika, S.T.
 * This file is intended for specifying the behaviour of
 * bussines logic of device.
 *
 * It logs the voltages and currents (DC and AC) reading to
 * sd card.
 *
 * NOTE: Implements in Kerja Praktik Junantara
 *       in Teknik Elektro Udayana

*/

#include "header.h"
#include "ACS712.h"

// Current
ACS712 input_current_sensor(PIN_INPUT_CURRENT_SENSOR, 5.0, 1023, 185);

float get_current()
{
  float average = 0;
  //  uint32_t start = millis();
  for (int i = 0; i < 100; i++)
  {
    //  select sppropriate function
    //  average += ACS.mA_AC_sampling();
    average += input_current_sensor.mA_AC();
  }
  return average / 100000.0 - CALIBRATED_CONST;
}

void setup()
{
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  // Serial.begin(115200);
  // For debug mode
  pinMode(PIN_DEBUG, INPUT_PULLUP);
  disp1.init();
  disp2.init();
  // Make init message visible in display hardwares
  delay(2000);

  // Debug mode trigger
  // due to pullup, logic LOW means debug mode is active.
  debug_mode_state = digitalRead(PIN_DEBUG);
  if (!debug_mode_state)
  {
    disp1.disp_custom(F("DEBUG MODE:"), F("ACTIVATED"));
    delay(2000);
  }
  else
  {
    disp1.disp_custom(F("DEBUG MODE:"), F("DEACTIVATED"));
    delay(2000);
  }
  // SD Card handling. The problems occurs in hardware frequently
  // (wires are not installed properly, insufficient power supply to SD card )
  bool status_sd_card = logger.init(PIN_CS_DATA_LOGGER);
  if (status_sd_card == 1)
    no_sd_card_handle(disp1, disp2);

  // Alocate objects dynamically
  VoltageSensorAc *input_voltage_sensor = new VoltageSensorAc(PIN_INPUT_VOLTAGE_SENSOR);
  VoltageSensorDc *output_voltage_sensor = new VoltageSensorDc(PIN_OUTPUT_VOLTAGE_SENSOR);

  // Show the first messages on display hardwares
  disp1.first_message();
  disp2.first_message();

  // Wait users to finish the circuit and push the push button
  while (button_state != 0)
  {
    button_state = read_button_state();
  }

  // Calibrate the current-sensors
  // ( for increasing the precission of current values)
  // input_current_sensor->calibrate();
  // output_current_sensor->calibrate();

  // Tell users that the device is ready by sending message
  // on dislpay hardwares
  disp1.second_message();
  disp2.second_message();

  // Make those displays visible
  delay(500);

  // Waiting users to push the button for capture-data confirmation.
  button_state = 1;
  while (button_state != 0)
  {
    button_state = read_button_state();
  }

  disp1.disp_custom(F("** INFORMASI **"), F("Collecting ..."));
  disp2.disp_custom(F("** INFORMASI **"), F("Collecting ..."));

  // Capture data from sensors
  data_input.current = get_current();
  data_output.current = get_current();
  // delay(1000);
  data_input.volt = input_voltage_sensor->calculate();
  data_output.volt = output_voltage_sensor->calculate();

  // Debug mode
  if (!debug_mode_state)
  {
    for (;;)
    {
      // Capture data from sensors
      data_input.current = get_current();
      data_output.current = get_current();
      data_input.volt = input_voltage_sensor->calculate();
      data_output.volt = output_voltage_sensor->calculate();

      // Display to LCDs periodically
      disp1.disp_measurements(data_input.volt, data_input.current, 0, true);
      disp2.disp_measurements(data_output.volt, data_output.current, 1, true);

      delay(500);
    }
  }
  // Dealocate memory used by objetcs
  // delete input_voltage_sensor;
  // delete output_voltage_sensor;
  delay(50);
  // Display captured data on LCDs
  disp1.disp_measurements(data_input.volt, data_input.current, 0);
  disp2.disp_measurements(data_output.volt, data_output.current, 1);

  // Log captured data once to SD card.
  bool status_log = logger.log(data_input.volt, data_input.current, data_output.volt,
                               data_output.current, "sensor.txt");
  // Error handling for logger process
  if (status_log == 1)
    log_failed_handle(disp1, disp2);

  // stuck here
}

void loop()
{
  // pass
}

/* Functions implementations
   The implementations of functions declared in 'header.h'

*/

bool read_button_state(void)
{
  return digitalRead(PIN_BUTTON);
}

void no_sd_card_handle(Display &disp1, Display &disp2)
{
  disp1.disp_custom(F("**   ERROR   **"), F("  NO SD CARD !"));
  disp2.disp_custom(F("**   ERROR   **"), F("  NO SD CARD !"));
  for (;;)
    ; // stuck forever
}

void log_failed_handle(Display &disp1, Display &disp2)
{
  disp1.disp_custom(F("**   ERROR   **"), F("  SD CARD FAIL !"));
  disp2.disp_custom(F("**   ERROR   **"), F("  SD CARD FAIL !"));
  for (;;)
    ; // stuck forever
}

/* EOF */