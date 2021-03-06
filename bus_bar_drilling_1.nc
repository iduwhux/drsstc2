%
(1001)
(T1  D=6.35 CR=0. TAPER=118deg - ZMIN=-1. - center drill)
(T2  D=2.54 CR=0. TAPER=118deg - ZMIN=-8.073 - drill)
(T3  D=4.039 CR=0. TAPER=118deg - ZMIN=-8.523 - drill)
G90 G54 G64 G50 G17 G40 G80 G94 G91.1 G49
G21 (Metric)
G30

N10(Center Drill)
T1 G43 H1 M6
S3820 M3 M8
G54
G0 X63. Y15.
G0 Z10.
G0 Z5.
G98 G81 X63. Y15. Z-1. R5. F254.
X68. Y22.
X73. Y15.
Y5.
X63.
Y-5.
X73.
Y-15.
X68. Y-22.
X63. Y-15.
X35.
X40. Y-22.
X45. Y-15.
Y-5.
X35.
Y5.
X45.
Y15.
X40. Y22.
X35. Y15.
X17.
X12. Y22.
X7. Y15.
Y5.
X17.
Y-5.
X7.
Y-15.
X12. Y-22.
X17. Y-15.
G80
G0 Z10.
M5 M9
G30

N20(Small Drill)
M1
T2 G43 H2 M6
S5000 M3 M8
G0 X63. Y-15.
G0 Z10.
G0 Z5.
G98 G83 X63. Y-15. Z-8.073 R5. Q2. F508.
X73.
Y-5.
X63.
Y5.
X73.
Y15.
X63.
X45.
X35.
Y5.
X45.
Y-5.
X35.
Y-15.
X45.
X17.
X7.
Y-5.
X17.
Y5.
X7.
Y15.
X17.
G80
G0 Z10.
M5 M9
G30

N30(Large Drill)
M1
T3 G43 H3 M6
S5000 M3 M8
G0 X63. Y-15.
G0 Z10.
G0 Z5.
G0 Z2.
G1 Z-3. F508.
G0 Z-2.
G1 Z-6. F508.
G0 Z-5.
G1 Z-8.523 F508.
G4 P0.1
G0 Z5.
G0 X73.
G0 Z2.
G1 Z-3. F508.
G0 Z-2.
G1 Z-6. F508.
G0 Z-5.
G1 Z-8.523 F508.
G4 P0.1
G0 Z5.
G0 Y-5.
G0 Z2.
G1 Z-3. F508.
G0 Z-2.
G1 Z-6. F508.
G0 Z-5.
G1 Z-8.523 F508.
G4 P0.1
G0 Z5.
G0 X63.
G0 Z2.
G1 Z-3. F508.
G0 Z-2.
G1 Z-6. F508.
G0 Z-5.
G1 Z-8.523 F508.
G4 P0.1
G0 Z5.
G0 Y5.
G0 Z2.
G1 Z-3. F508.
G0 Z-2.
G1 Z-6. F508.
G0 Z-5.
G1 Z-8.523 F508.
G4 P0.1
G0 Z5.
G0 X73.
G0 Z2.
G1 Z-3. F508.
G0 Z-2.
G1 Z-6. F508.
G0 Z-5.
G1 Z-8.523 F508.
G4 P0.1
G0 Z5.
G0 Y15.
G0 Z2.
G1 Z-3. F508.
G0 Z-2.
G1 Z-6. F508.
G0 Z-5.
G1 Z-8.523 F508.
G4 P0.1
G0 Z5.
G0 X63.
G0 Z2.
G1 Z-3. F508.
G0 Z-2.
G1 Z-6. F508.
G0 Z-5.
G1 Z-8.523 F508.
G4 P0.1
G0 Z5.
G0 X45.
G0 Z2.
G1 Z-3. F508.
G0 Z-2.
G1 Z-6. F508.
G0 Z-5.
G1 Z-8.523 F508.
G4 P0.1
G0 Z5.
G0 X35.
G0 Z2.
G1 Z-3. F508.
G0 Z-2.
G1 Z-6. F508.
G0 Z-5.
G1 Z-8.523 F508.
G4 P0.1
G0 Z5.
G0 Y5.
G0 Z2.
G1 Z-3. F508.
G0 Z-2.
G1 Z-6. F508.
G0 Z-5.
G1 Z-8.523 F508.
G4 P0.1
G0 Z5.
G0 X45.
G0 Z2.
G1 Z-3. F508.
G0 Z-2.
G1 Z-6. F508.
G0 Z-5.
G1 Z-8.523 F508.
G4 P0.1
G0 Z5.
G0 Y-5.
G0 Z2.
G1 Z-3. F508.
G0 Z-2.
G1 Z-6. F508.
G0 Z-5.
G1 Z-8.523 F508.
G4 P0.1
G0 Z5.
G0 X35.
G0 Z2.
G1 Z-3. F508.
G0 Z-2.
G1 Z-6. F508.
G0 Z-5.
G1 Z-8.523 F508.
G4 P0.1
G0 Z5.
G0 Y-15.
G0 Z2.
G1 Z-3. F508.
G0 Z-2.
G1 Z-6. F508.
G0 Z-5.
G1 Z-8.523 F508.
G4 P0.1
G0 Z5.
G0 X45.
G0 Z2.
G1 Z-3. F508.
G0 Z-2.
G1 Z-6. F508.
G0 Z-5.
G1 Z-8.523 F508.
G4 P0.1
G0 Z5.
G0 X17.
G0 Z2.
G1 Z-3. F508.
G0 Z-2.
G1 Z-6. F508.
G0 Z-5.
G1 Z-8.523 F508.
G4 P0.1
G0 Z5.
G0 X7.
G0 Z2.
G1 Z-3. F508.
G0 Z-2.
G1 Z-6. F508.
G0 Z-5.
G1 Z-8.523 F508.
G4 P0.1
G0 Z5.
G0 Y-5.
G0 Z2.
G1 Z-3. F508.
G0 Z-2.
G1 Z-6. F508.
G0 Z-5.
G1 Z-8.523 F508.
G4 P0.1
G0 Z5.
G0 X17.
G0 Z2.
G1 Z-3. F508.
G0 Z-2.
G1 Z-6. F508.
G0 Z-5.
G1 Z-8.523 F508.
G4 P0.1
G0 Z5.
G0 Y5.
G0 Z2.
G1 Z-3. F508.
G0 Z-2.
G1 Z-6. F508.
G0 Z-5.
G1 Z-8.523 F508.
G4 P0.1
G0 Z5.
G0 X7.
G0 Z2.
G1 Z-3. F508.
G0 Z-2.
G1 Z-6. F508.
G0 Z-5.
G1 Z-8.523 F508.
G4 P0.1
G0 Z5.
G0 Y15.
G0 Z2.
G1 Z-3. F508.
G0 Z-2.
G1 Z-6. F508.
G0 Z-5.
G1 Z-8.523 F508.
G4 P0.1
G0 Z5.
G0 X17.
G0 Z2.
G1 Z-3. F508.
G0 Z-2.
G1 Z-6. F508.
G0 Z-5.
G1 Z-8.523 F508.
G4 P0.1
G0 Z5.
G0 Z10.
M5 M9

G30
M30
%
