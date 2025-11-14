
1. Соответствие сигналов и контактов HDMI

HDMI_TX0-       IO_B35_LN8      M18
HDMI_TX0+       IO_B35_LP8      M17

HDMI_TX1-       IO_B35_LN24     J16
HDMI_TX1+       IO_B35_LP24     K16

HDMI_TX2-       IO_B35_LN9      L20
HDMI_TX2+       IO_B35_LP9      L19

HDMI_TXC-       IO_B35_LN11     L17
HDMI_TXC+       IO_B35_LP11     L16

HDMI_I2C_SCL    IO_B35_LP23     M14
HDMI_I2C_SDA    IO_B35_LN23     M15

HDMI_CEC        IO_B35_LP21     N15
HDMI_HPD        IO_B35_LN21     N16

HDMI_OUT_EN     IO_B35_LP7      M19
HDMI_DET_IO     IO_B35_LN7      M20

Проверить уровни HDMI сигналов.

появляется 4 новых сигнала: HDMI_I2C_SCL, HDMI_I2C_SDA, HDMI_CEC и HDMI_HPD.

HDMI_I2C_SCL и HDMI_I2C_SDA сигналы I2C от zynq через м/х SN74LVC2G07 (преобразование уровня?).
можно сделать программно от процессора.   Уровни 3.3В.
Считать не может, только записать.


сигнал HDMI_CEC -- Consumer Electronics Control (CEC)
двунаправленная последовательная шина, использующая протокол промышленного стандарта AV.Link (англ.) для удалённого управления электронными устройствами.
попробовать найти простой вариант на github. опять программно от процессора.
может опустить пока.

сигнал HDMI_HPD (Hot Plug Detect) распадается на 3 сигнала: HDMI_HPD похоже входной,
HDMI_DET_IO и HDMI_OUT_EN возможно разрешение выходного сигнала и сам выходной сигнал.
через м/х NL17SZ126DFT2G. все 3.3в. 
одновременно HDMI_DET_IO вход через м/х SN74LVC1G07DCKR. Уровень 3.3В.  

Какие уровни сигналов(последних 6) 1.8 или 3.3В.

Настроить UART, настроить DDR memory.
ROM memory настроить.   QUAD SPI FLASH.

Debug UART:     UART1_TX  --  B12   --  MIO 48
                UART1_RX  --  C12   --  MIO 49
                
Настройка DDR:
                Memory Type                 DDR3
                Memory Part                 MT41K128M16 HA-15E
                Effective DRAM Bus Width    32 Bit
                ECC                         Disabled
                burst Length                8
                DDR                         533.33333
                Interval Vref               0
                Junion Temperature (C)      <Select>
                Bank Address Count (Bits)   3
                Row Address Count (Bits)    14
                Col Address Count (Bits)    10
                CAS Latency (cycles)        7
                CAS Write Latency (cycles)  6
                RAS to CAS Delay (cycles)   7
                Precharge Time (cycles)     7
                tRC(ns)                     49.5
                tRASmin (ns)                36.0
                tFAW (ns)                   45.0
                
                DQS to Clock Delay (ns)
                    DQS0                    0.220
                    DQS1                    0.245
                    DQS2                    0.126
                    DQS3                    0.152
                    
                Board Delay (ns)
                    DQ[7:0]                 0.270
                    DQ[15:8]                0.256
                    DQ[23:16]               0.227
                    DQ[31:24]               0.215
                    
                Enable HPR
                HPR/LPR Queue Partioning            HPR(0)/LPR(32)
                LPR to Critical Priority Level      2
                HPR to Critical Priority Level      15
                Write to Critical Priority Level    2
                
