# Precharge Circuit Design
## TPS2490 + 2× SQJQ184E — 30 V / 40 A / 5000 µF

---

## 1. System Requirements

| Parameter | Value | Source |
|---|---|---|
| Bus voltage (max) | 30 V (7S LiPo fully charged: 7 × 4.2 V = 29.4 V) | Battery |
| Bus voltage (nominal) | 25.9 V (7 × 3.7 V) | Battery |
| Load capacitance | 5000 µF | 8× EPOS4 Micro 24/5 CAN (estimated) |
| Continuous operating current | 40 A | 8× motors × 5 A each |
| OCP / precharge current limit | 40 A | Design target |
| Ambient temperature (max) | 40 °C | Robot enclosure |

---

## 2. Component Selection

### 2.1 Controller: TPS2490DGSR (Texas Instruments)

Positive high-voltage, N-channel hot-swap controller with programmable power limiting and current limiting. Selected over ADM1270 because:

- Power limiting shapes V_DS × I_D = const along SOA boundary (safer for N-ch precharge than ADM1270 foldback)
- Simpler sizing: one PROG divider vs. foldback resistors
- N-channel FET drive: lower R_DS(on) for equivalent die area
- Built-in charge pump for high-side N-channel gate drive above V_IN

### 2.2 FETs: 2× SQJQ184E-T1_GE3 (Vishay, PowerPAK 8×8L)

| Parameter | Value |
|---|---|
| V_DSS | 80 V (2.67× margin over 30 V) |
| I_D | 430 A |
| R_DS(on) | 1.4 mΩ @ V_GS = 10 V |
| Q_G | 181 nC |
| Q_GD | 36 nC |
| R_thJC | 0.25 °C/W |
| R_thJA | 40 °C/W (standard PCB) |
| T_J(max) | 150 °C |
| SOA @ 30 V | ~80 A at 1 ms, ~25 A at 10 ms (per device) |

Two devices in parallel: R_DS(on) = 1.4 mΩ / 2 = **0.7 mΩ**

Gate resistors: **10 Ω per FET** — mandatory for current sharing between parallel devices and to damp gate oscillations.

---

## 3. TPS2490 Configuration

### 3.1 Current Limit — R_SNS

```
I_LIM = 50 mV / R_SNS       (V_SENSECL threshold, standalone current limiting)
R_SNS = 50 mV / 40 A = 1.25 mΩ
```

**Implementation:** 2× 2.5 mΩ resistors in parallel (e.g. Vishay WSL2512R0025FEA, 1 W rated each).

Sense voltage at I_LIM: V_SENSE = 40 A × 1.25 mΩ = **50 mV** ✓

Sense resistor power: P = V_SENSE × I_LIM = 50 mV × 40 A = **2 W total** (1 W per resistor, within rating).

### 3.2 Power Limit — PROG Divider

Power limiting protects the FET SOA during the high-V_DS portion of precharge (output near 0 V). The TPS2490 constant power engine limits V_DS × I_D = P_LIM, preventing excessive FET dissipation at full bus voltage.

**Choose P_LIM = 600 W** — sets the crossover from power limiting to current limiting at:

```
V_DS_crossover = P_LIM / I_LIM = 600 W / 40 A = 15 V
→ Power limiting active: V_OUT = 0 V to 15 V (V_DS = 30 V to 15 V)
→ Current limiting active: V_OUT = 15 V to 30 V (V_DS = 15 V to 0 V)
```

From TPS2490 Eq. 2:

```
V_PROG = P_LIM / (10 × I_LIM) = 600 W / (10 × 40 A) = 1.5 V
```

VREF = 4 V. Resistor divider from VREF to GND:

```
V_PROG = VREF × R4 / (R3 + R4)
1.5 = 4 × R4 / (R3 + R4)
→ R4 / (R3 + R4) = 0.375
```

**R3 = 17 kΩ, R4 = 10 kΩ:**

```
V_PROG = 4 × 10 / (17 + 10) = 1.481 V
P_LIM  = 1.481 × 10 × 40 = 593 W  (−1.2% from target, acceptable)
```

### 3.3 Fault Timer — C_TIMER

Timer charges at **25 µA** whenever TPS2490 is in current or power limit. Trips at **4 V** → latch off (TPS2490) or auto-retry (TPS2491).

Precharge time derivation:

**Phase 1 — Power limited (V_OUT: 0 → 15 V)**

Constant power P = 593 W into C = 5000 µF with V_IN = 30 V:

```
t1 = (C / P_LIM) × ∫₀^15 (V_IN − V) dV
   = (5000µF / 593 W) × [30×15 − 15²/2]
   = 8.434×10⁻⁶ × 337.5
   = 2.85 ms
```

Current during this phase: I = P_LIM / V_DS = 593 W / V_DS
- At V_OUT = 0 V (V_DS = 30 V): I = **19.8 A** total, **9.9 A** per FET
- At V_OUT = 15 V (V_DS = 15 V): I = **39.5 A** total, **19.8 A** per FET

**Phase 2 — Current limited (V_OUT: 15 → 30 V)**

```
t2 = C × ΔV / I_LIM = 5000µF × 15 V / 40 A = 1.875 ms
```

Current: 40 A throughout. V_DS decreasing from 15 V to 0 V.

**Total precharge time: t_precharge = 2.85 + 1.875 = 4.73 ms**

Size C_TIMER with 3.4× margin:

```
t_fault = C_TIMER × 4 V / 25 µA
C_TIMER = (3.4 × 4.73 ms × 25 µA) / 4 V = 100 nF
t_fault  = 100 nF × 4 V / 25 µA = 16 ms
```

**C_TIMER = 100 nF** → t_fault = 16 ms (3.4× margin over precharge).

---

## 4. SOA Verification

SQJQ184E SOA at 30 V per device (read from datasheet chart):
- 1 ms limit: ~80 A
- 10 ms limit: ~25 A

### Phase 1 (Power Limited, 2.85 ms)

Worst case at start of precharge: V_DS = 30 V, I = 9.9 A per FET.

Interpolating SOA on log scale between 1 ms and 10 ms at 30 V:
- At 2.85 ms: limit ≈ 45–50 A per device

**9.9 A << 45 A at 30 V, 2.85 ms → SOA: PASS ✓**

### Phase 2 (Current Limited, 1.875 ms)

V_DS drops from 15 V to 0 V. Each FET carries 20 A.
SOA at 15 V is considerably more relaxed than at 30 V.

**20 A at V_DS ≤ 15 V, 1.875 ms → SOA: PASS ✓**

---

## 5. Thermal Verification

### 5.1 Precharge Transient

Total FET energy dissipation equals energy stored in capacitor:

```
E_total = ½ × C × V² = ½ × 5000µF × 30² = 2.25 J
E_per_FET = 2.25 / 2 = 1.125 J per FET
```

Average power per FET during precharge:

```
P_avg_per_FET = E_per_FET / t_precharge = 1.125 J / 4.73 ms = 237.8 W
```

Transient thermal impedance Z_thJC at 4.73 ms for PowerPAK 8×8L:
Estimated from typical transient thermal curves: **Z_thJC ≈ 0.05 °C/W** (conservative).

```
ΔT_J = P_avg × Z_thJC = 237.8 W × 0.05 °C/W = 11.9 °C
T_J = T_ambient + ΔT = 40 + 11.9 = 51.9 °C  <<  150 °C
```

**Precharge thermal: PASS ✓ (T_J = 52 °C, margin = 98 °C)**

Repeated precharge cycles: allow ≥ 5 s between events to prevent thermal accumulation (FET package cools within 1–2 s).

### 5.2 Steady-State Conduction (40 A)

2× FETs in parallel: R_DS(on)_eff = 1.4 mΩ / 2 = 0.7 mΩ

```
P_cond_total = I² × R = 40² × 0.7 mΩ = 1.12 W
P_per_FET    = 0.56 W
ΔT_J         = 0.56 W × 40 °C/W = 22.4 °C   (using R_thJA standard PCB)
T_J          = 40 + 22.4 = 62.4 °C  <<  150 °C
```

**Steady-state thermal: PASS ✓ (T_J = 62 °C, margin = 88 °C)**

Note: With optimized PCB (4-layer, 2 oz copper, large thermal pads) R_thJA can reach 15–20 °C/W, reducing T_J further.

### 5.3 Sense Resistor Thermal

```
P_sense = I² × R_SNS = 40² × 1.25 mΩ = 2.0 W
Per resistor: 1.0 W  (WSL2512 rated 1 W each) → at rating limit
```

Use 2× WSL2512 with adequate airflow, or increase to 3× 3.75 mΩ in parallel (0.67 W each, more margin).

---

## 6. Conduction Loss Budget

| Source | Loss |
|---|---|
| 2× SQJQ184E R_DS(on) | 1.12 W |
| Sense resistors (2× 2.5 mΩ ‖) | 2.00 W |
| **Total** | **3.12 W** |

Bus efficiency at 40 A, 30 V:

```
η = (P_OUT) / (P_IN) = (30 × 40 − 3.12) / (30 × 40) = 99.74%
```

---

## 7. Gate Drive

Gate source current from TPS2490: **22 µA typ**. Total gate charge for 2× SQJQ184E: Q_G = 2 × 181 nC = 362 nC.

```
t_gate_charge = Q_G / I_GATE = 362 nC / 22 µA = 16.5 ms
```

This is the unloaded gate rise time. During precharge the TPS2490 servo-regulates V_GS in the linear region — the gate voltage is modulated, not simply charging to full. Gate resistors (10 Ω each) set individual FET di/dt and prevent gate oscillation between parallel devices.

Gate voltage clamp: 12–16 V (TPS2490 internal). SQJQ184E V_GS(max) = ±20 V → no external Zener needed.

---

## 8. OCP Behavior After Precharge

Once C_LOAD is charged and FETs are fully enhanced (V_GS ≈ 14 V, R_DS(on) = 0.7 mΩ):

| Condition | TPS2490 Action | Timer |
|---|---|---|
| I_load < 40 A | No action, FET fully on | Not charging |
| I_load = 40 A (sustained) | Gate pulled down, current clamped at 40 A | Charges at 25 µA |
| Sustained > 40 A for 16 ms | FLT asserted, GATE pulled to GND, FET off | Expires at 4 V |
| EN cycled or V_IN cycled | Reset from latch-off | — |

The 8× EPOS4 controllers each have independent 20 A overcurrent protection — they will trip before the bus TPS2490 OCP fires under normal operating conditions. The TPS2490 OCP catches hard bus-level faults (wiring shorts, catastrophic controller failure).

Peak current scenario: 8× EPOS4 at peak (15 A each) = 120 A. This exceeds I_LIM = 40 A — TPS2490 clamps at 40 A immediately, bus voltage droops, EPOS4 controllers reduce demand. If sustained 16 ms, bus trips. In practice, peak acceleration events are <10 ms — timer accumulates but may not expire.

---

## 9. Component Summary

| Reference | Component | Value / Part | Purpose |
|---|---|---|---|
| U1 | TPS2490DGSR | — | Hot-swap controller |
| Q1, Q2 | SQJQ184E-T1_GE3 | 80 V / 1.4 mΩ / PowerPAK 8×8L | Main pass FETs |
| R_SNS | 2× WSL2512R0025FEA | 2× 2.5 mΩ ‖ = 1.25 mΩ | Current sense |
| R3 | — | 17 kΩ | PROG divider (top) |
| R4 | — | 10 kΩ | PROG divider (bottom) |
| C_TIMER | — | 100 nF | Fault timer = 16 ms |
| R_G1, R_G2 | — | 10 Ω each | Gate resistors (per FET) |
| Z1 (input) | TVS diode | 33 V clamp | Input transient protection |
| C_IN | Electrolytic | ≥ 100 µF / 35 V | Input bypass |

---

## 10. Design Checklist

| Check | Result |
|---|---|
| V_DSS > 1.5× V_BUS | 80 V > 45 V ✓ |
| SOA Phase 1 (9.9 A @ 30 V, 2.85 ms) | 9.9 A << 45 A limit ✓ |
| SOA Phase 2 (20 A @ ≤15 V, 1.875 ms) | Within SOA ✓ |
| T_J precharge (Z_thJC) | 52 °C << 150 °C ✓ |
| T_J steady state (R_thJA) | 62 °C << 150 °C ✓ |
| Sense resistor power | 1 W each, at WSL2512 limit — use 3× if needed |
| C_TIMER margin | 3.4× over precharge time ✓ |
| Gate V_GS(max) | 14 V clamp << 20 V abs max ✓ |
| Efficiency at 40 A | 99.74% ✓ |

---

## 11. Reference Designs

| Design | FET | Count | R_SNS | I_LIM | Notes |
|---|---|---|---|---|---|
| power_dist r4.5b | PSMN4R8-100BSEJ | 3× | 0.5 mΩ | 100 A | 44 V, FBSOA-rated, Eagle |
| SMPS_Motherboard | SQJQ186E | 4× | 0.3 mΩ | 167 A | KiCAD retrofit, 10 Ω R_G |
| **This design** | **SQJQ184E** | **2×** | **1.25 mΩ** | **40 A** | **30 V, 5000 µF, robotics** |
