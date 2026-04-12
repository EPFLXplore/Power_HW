# Test Plan

Passive ranges below use the KiCad-installed passive tolerances visible in the project: resistors `+/-1%` and timing capacitors `+/-10%`. They are intended as board-level expectations before bench test. Internal IC accuracy is not added unless it is already embedded in the review math.

## TPS259830ONRGER

### Theoretical Values

`IC7`, `IC9`, `IC8`, and `IC10` implement rail e-fuse protection on `5V`, `12V`, `15V`, and `24V`.

For each rail the review math is:

- `V_UV = 1.2 * (R1 + R2 + R3) / (R2 + R3)`
- `V_OV = 1.2 * (R1 + R2 + R3) / R3`
- `I_LIMIT = 1460 / RILIM + 0.11`
- `t_ITIMER = 470 * C_ITIMER`
- `t_RETRY ~= ((C_RETRY_DLY * 1000 + 4) * 46.83) / 1000 ms`

Installed values from the KiCad project:

- `5V rail, IC7`: `R11 = 1M`, `R12 = 142k`, `R13 = 285k`, `R10 = 150`, `C15 = 22n`, `C22 = 47n`
- `12V rail, IC9`: `R21 = 1M`, `R22 = 39k`, `R23 = 97k`, `R25 = 150`, `C18 = 22n`, `C19 = 47n`
- `15V rail, IC8`: `R15 = 1M`, `R16 = 24k`, `R17 = 78k`, `R19 = 150`, `C11 = 22n`, `C31 = 47n`
- `24V rail, IC10`: `R27 = 1M`, `R28 = 9k`, `R29 = 49k`, `R31 = 150`, `C10 = 22n`, `C14 = 47n`

Calculated thresholds:

- `5V`: `V_UV = 1.2 * (1000 + 142 + 285) / (142 + 285) = 4.01V`, range `3.95V to 4.07V`; `V_OV = 1.2 * 1427 / 285 = 6.01V`, range `5.91V to 6.11V`
- `12V`: `V_UV = 1.2 * (1000 + 39 + 97) / (39 + 97) = 10.02V`, range `9.85V to 10.20V`; `V_OV = 1.2 * 1136 / 97 = 14.05V`, range `13.80V to 14.31V`
- `15V`: `V_UV = 1.2 * (1000 + 24 + 78) / (24 + 78) = 12.96V`, range `12.73V to 13.20V`; `V_OV = 1.2 * 1102 / 78 = 16.95V`, range `16.64V to 17.27V`
- `24V`: `V_UV = 1.2 * (1000 + 9 + 49) / (9 + 49) = 21.89V`, range `21.48V to 22.31V`; `V_OV = 1.2 * 1058 / 49 = 25.91V`, range `25.42V to 26.41V`
- All rails: `RILIM = 150` gives `I_LIMIT = 1460 / 150 + 0.11 = 9.84A`, range `9.75A to 9.94A`
- All rails: `ITIMER` is intentionally left open, so the overcurrent blanking interval is the minimum setting
- All rails: `CRETRY_DLY = 22nF` gives `t_RETRY ~= 1030ms`, range about `927ms to 1133ms`
- All rails: `CNRETRY = 47nF` is set for `16 retries` per the TI table used in the review flow

### Testing Plan

- Use a programmable bench supply on the rail input and an electronic load on the protected output.
- Sweep the input voltage down until the rail disconnects to measure the UV trip point.
- Sweep the input voltage up until the rail disconnects to measure the OV trip point.
- At nominal input voltage, increase load current until current limiting starts; record the steady current limit.
- Apply a hard short or low-ohm overload and use an oscilloscope on `FAULT`, `PG`, and output voltage to measure retry delay and retry count.
- Confirm no nuisance trip during normal startup at the intended load.

### Results Table

| Rail | UV theory | OV theory | OC theory | Retry delay theory | Retry count theory | Measured UV | Measured OV | Measured OC | Measured retry delay | Measured retry count | Pass/Fail | Notes |
| --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 5V | `4.01V (3.95V..4.07V)` | `6.01V (5.91V..6.11V)` | `9.84A (9.75A..9.94A)` | `1.03s (0.93s..1.13s)` | `16` |  |  |  |  |  |  |  |
| 12V | `10.02V (9.85V..10.20V)` | `14.05V (13.80V..14.31V)` | `9.84A (9.75A..9.94A)` | `1.03s (0.93s..1.13s)` | `16` |  |  |  |  |  |  |  |
| 15V | `12.96V (12.73V..13.20V)` | `16.95V (16.64V..17.27V)` | `9.84A (9.75A..9.94A)` | `1.03s (0.93s..1.13s)` | `16` |  |  |  |  |  |  |  |
| 24V | `21.89V (21.48V..22.31V)` | `25.91V (25.42V..26.41V)` | `9.84A (9.75A..9.94A)` | `1.03s (0.93s..1.13s)` | `16` |  |  |  |  |  |  |  |

## ADM1270ACPZ

### Theoretical Values

`U4` protects the battery input path against UV, OV, OC, and SOA stress through foldback.

The review math is:

- `V_ISET = 3.6 * R_BOTTOM / (R_TOP + R_BOTTOM)`
- `V_SENSE = V_ISET / 40`
- `I_LIMIT = V_SENSE / R_SHUNT`
- `V_UV = 1.0 * (R1 + R2 + R3) / (R2 + R3)`
- `V_OV = 1.0 * (R1 + R2 + R3) / R3`
- `V_OUT,FLB = V_ISET * (R_A + R_B) / R_B`

Installed values from the project and the review note:

- `R39 = 1mOhm +/-1%` shunt
- `VISET divider = 3.6k / 2.3k`
- `UV/OV divider = 1M / 15k / 37k`
- `Foldback divider = 1M / 133k`
- `C23 = 100nF` and `C32 = 100nF` for timer and retry-off timing

Calculated thresholds:

- `V_ISET = 3.6 * 2.3 / (3.6 + 2.3) = 1.403V`, range `1.386V to 1.421V`
- `V_SENSE = 1.403 / 40 = 35.08mV`, range `34.66mV to 35.51mV`
- `I_LIMIT = 35.08mV / 1mOhm = 35.08A`, range `34.31A to 35.87A`
- `V_UV = 1.0 * (1000 + 15 + 37) / (15 + 37) = 20.23V`, range `19.85V to 20.62V`
- `V_OV = 1.0 * (1000 + 15 + 37) / 37 = 28.43V`, range `27.89V to 28.99V`
- `V_OUT,FLB = 1.403 * (1000 + 133) / 133 = 11.96V`, range `11.60V to 12.32V`
- `C_TIMER = 100nF` gives nominal fault timing of about `10ms`
- `C_TIMER_OFF = 100nF` gives nominal retry-off time of about `200ms`
- With `+/-10%` timing capacitors, timing-only expectation is about `9ms to 11ms` for fault timing and `180ms to 220ms` for retry-off time

### Testing Plan

- Drive the battery input with a programmable supply and place an electronic load on `VBatt_safe`.
- Sweep the input voltage down and up slowly to measure the UV and OV trip points.
- At nominal battery voltage, increase the load current until the current limiter engages; record the limited current.
- Create a controlled overload or short so that `VOUT` is forced downward and measure the point where foldback starts reducing the current limit; target is near `12V`.
- Use an oscilloscope on output voltage, gate drive, and fault-related pins to measure fault-on time and retry-off time during a hard overload.

### Results Table

| Feature | Theory | Measured | Pass/Fail | Notes |
| --- | --- | --- | --- | --- |
| UV trip | `20.23V (19.85V..20.62V)` |  |  |  |
| OV trip | `28.43V (27.89V..28.99V)` |  |  |  |
| Current limit | `35.08A (34.31A..35.87A)` |  |  |  |
| Foldback start | `11.96V (11.60V..12.32V)` |  |  |  |
| Fault timing | `10ms nominal (9ms..11ms from C tolerance)` |  |  |  |
| Retry-off timing | `200ms nominal (180ms..220ms from C tolerance)` |  |  |  |

## LTC4372CMS8#TRPBF

### Theoretical Values

`IC701`, `IC702`, `IC4`, and `IC5` implement reverse-current protection on `5V`, `12V`, `15V`, and `24V`.

The review note for the selected MOSFET states:

- `VGS(th) = 2.33V to 3.15V`
- `RDS(on) = 1.30mOhm to 1.63mOhm`

Each protected path uses a back-to-back MOSFET pair, so:

- `R_PATH ~= 2 * RDS(on) = 2.60mOhm to 3.26mOhm`
- `V_DROP = I_TEST * R_PATH`
- At `10A`, expected forward drop is `26mV to 32.6mV`
- At `20A`, expected forward drop is `52mV to 65.2mV`
- Reverse-current expectation is functional, not adjustable: no sustained back-feed from output to input when the output is driven externally above the input or when the input source is removed
- `SHDN` is expected to open the path on command

### Testing Plan

- Power each rail from its normal input and load the protected output to a chosen current point; measure voltage drop across the protection stage.
- Turn the input supply off, then drive the output connector from a bench supply with current limit enabled; verify that the input side does not get back-powered.
- Toggle `SHDN_CTRL` and confirm that the path opens cleanly and remains reverse-blocking.
- If surge equipment is available, run a controlled non-destructive clamp test on the TVS network as a separate optional test.

### Results Table

| Rail | Forward-drop theory | Reverse-current theory | SHDN theory | Measured forward drop | Measured reverse current | Measured SHDN result | Pass/Fail | Notes |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 5V | `Vdrop = I_TEST * (2.60mOhm..3.26mOhm)` | `No sustained back-feed` | `Path opens on command` |  |  |  |  |  |
| 12V | `Vdrop = I_TEST * (2.60mOhm..3.26mOhm)` | `No sustained back-feed` | `Path opens on command` |  |  |  |  |  |
| 15V | `Vdrop = I_TEST * (2.60mOhm..3.26mOhm)` | `No sustained back-feed` | `Path opens on command` |  |  |  |  |  |
| 24V | `Vdrop = I_TEST * (2.60mOhm..3.26mOhm)` | `No sustained back-feed` | `Path opens on command` |  |  |  |  |  |
