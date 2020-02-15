
typedef struct _DeviceVectors
{
  /* Stack pointer */
  void* pvStack;

  /* Cortex-M handlers */
  void* pfnReset_Handler;
  void* pfnNMI_Handler;
  void* pfnHardFault_Handler;
  void* pvReservedM12;
  void* pvReservedM11;
  void* pvReservedM10;
  void* pvReservedM9;
  void* pvReservedM8;
  void* pvReservedM7;
  void* pvReservedM6;
  void* pfnSVC_Handler;
  void* pvReservedM4;
  void* pvReservedM3;
  void* pfnPendSV_Handler;
  void* pfnSysTick_Handler;

  /* peripheral handlers */
  void* IRQ0_handler;
  void* IRQ1_handler;
  void* IRQ2_handler;
  void* IRQ3_handler;
  void* IRQ4_handler;
  void* IRQ5_handler;
  void* IRQ6_handler;
  void* IRQ7_handler;
  void* IRQ8_handler;
  void* IRQ9_handler;
  void* IRQ10_handler;
  void* IRQ11_handler;
  void* IRQ12_handler;
  void* IRQ13_handler;
  void* IRQ14_handler;
  void* IRQ15_handler;
  void* IRQ16_handler;
  void* IRQ17_handler;
  void* IRQ18_handler;
  void* IRQ19_handler;
  void* IRQ20_handler;
  void* IRQ21_handler;
  void* IRQ22_handler;
  void* IRQ23_handler;
  void* IRQ24_handler;
  void* IRQ25_handler;
  void* IRQ26_handler;
  void* IRQ27_handler;
  void* IRQ28_handler;
  void* IRQ29_handler;
  void* IRQ30_handler;
  void* IRQ31_handler;
} DeviceVectors;

