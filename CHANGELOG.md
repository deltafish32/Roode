# Changelog

## 1.6.0

- Vendor the VL53L1X_ULD library (BSD 3-Clause, by rneurink) into the `vl53l1x` component and route its I2C traffic through the ESPHome I2C bus instead of Arduino `Wire`; the external `rneurink/VL53L1X_ULD` and `Wire` library dependencies are removed
- Add `Shortest` ranging mode to automatic ranging mode selection for idle distances up to 1000 mm
- Add sensor shutdown control (`set_xshut()`) on both `Roode` and `VL53L1X` to power the sensor down and back up at runtime
- Add automatic sensor recovery: timeout while waiting for measurement data prevents a hung sensor from blocking the loop, and when a distance read fails the VL53L1X is power-cycled via `xshut_pin` (if configured), re-initialized and restored to the last used ranging mode
- Record sensor read errors (count plus the last 10 entries with timestamps and status codes) and show them in `dump_config()`

## 1.5.4

- Fix ESPHome 2026.2+ compatibility by migrating ESP8266 configurations to new platform format
- Update CI configurations and example files to use separate `esp8266:` block instead of deprecated `platform:` key
- Fix Wire library dependency for VL53L1X_ULD to resolve build errors on ESP32
- Fix release workflow to skip creating releases that already exist

## 1.5.0

- Manual ROI configuration fixed
- Sensor initialization fixed
- Fix setup priorities to ensure proper boot up
- Code formatting
- Cleanup

## 1.4.1

- Timing budget test by @Lyr3x in #60
- Restructure configuration by @Lyr3x in #61
- v1.4.0 by @Lyr3x in #55
- Improve roi calibration by @Lyr3x in #64
- Fix presence sensor and wdt crashes by @Lyr3x in #67
- Improve sensor creation, initialization and measurement reads by @Lyr3x in #68
- Use sampling always by @Lyr3x in #71
- Improve error log and fix manual mode by @Lyr3x in #73
- Configure IDE intellisense by @CarsonF in #74
- Fix error handling by @Lyr3x in #75
- Fix manual roi setting by @Lyr3x in #78
