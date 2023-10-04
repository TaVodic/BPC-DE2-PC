   | **Version** | **Size [B]** |
   | :-- | :-: |
   | Ver. 1: Arduino-style | 508 |
   | Ver. 2: Registers | 182 |
   | Ver. 3: Library functions | 182 |

| **DDRB** | **PORTB** | **Direction** | **Internal pull-up resistor** | **Description** |
   | :-: | :-: | :-: | :-: | :-: |
   | 0 | 0 | input | no | Tri-state, high-impedance |
   | 0 | 1 | input | yes| Pxn will source current if ext. pulled low. |
   | 1 | 0 | output| no| driven LOW|
   | 1 | 1 | output| no| driven HIGH|