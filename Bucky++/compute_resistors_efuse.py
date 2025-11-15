def compute_resistors(Vin_UV, Vin_OV, Vuv_R, Vov_R, R1=1e6):
    """
    Compute R2 and R3 given Vin_UV, Vin_OV, Vuv_R, and Vov_R.

    Parameters:
        Vin_UV : float
            Undervoltage input threshold (V)
        Vin_OV : float
            Overvoltage input threshold (V)
        Vuv_R  : float
            Reference UV voltage (V) (typically between 1 and 2)
        Vov_R  : float
            Reference OV voltage (V) (typically between 1 and 2)
        R1     : float
            Resistance R1 (Ohms), default = 1e6 (1 MΩ)

    Returns:
        (R2, R3) in Ohms
    """

    # From the two equations:
    # (1) Vin_UV = Vuv_R * (R1 + R2 + R3) / (R2 + R3)
    # (2) Vin_OV = Vov_R * (R1 + R2 + R3) / R3

    # Rearrange (2) to express (R1 + R2 + R3)# but R3 unknown yet
    # Instead, we derive directly by eliminating R2

    # Derive symbolic relationships manually:
    # From (1): (Vin_UV / Vuv_R) = (R1 + R2 + R3) / (R2 + R3)
    # From (2): (Vin_OV / Vov_R) = (R1 + R2 + R3) / R3
    # Subtract the first from the second:
    # (Vin_OV / Vov_R) - (Vin_UV / Vuv_R) = (R1 + R2 + R3)*(1/R3 - 1/(R2 + R3))
    # Simplify → we can solve symbolically, but easier numerically.

    import sympy as sp
    R2, R3 = sp.symbols('R2 R3', positive=True)

    eq1 = sp.Eq(Vin_UV, Vuv_R * (R1 + R2 + R3) / (R2 + R3))
    eq2 = sp.Eq(Vin_OV, Vov_R * (R1 + R2 + R3) / R3)

    sol = sp.solve((eq1, eq2), (R2, R3), dict=True)
    R2_val = float(sol[0][R2])
    R3_val = float(sol[0][R3])
    return R2_val, R3_val


# Example usage:
Vin_UV = 4.0  # undervoltage threshold (V)
Vin_OV = 6.0  # overvoltage threshold (V)
Vuv_R = 1.2
Vov_R = 1.2

R2, R3 = compute_resistors(Vin_UV, Vin_OV, Vuv_R, Vov_R)
print(f"R2 = {R2/1e3:.2f} kΩ")
print(f"R3 = {R3/1e3:.2f} kΩ")
