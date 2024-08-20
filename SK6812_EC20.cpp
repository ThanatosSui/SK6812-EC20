



// F_CPU is defined to SystemCoreClock (not constant number)
#if SYSCLK_FREQ_144MHz_HSE == 144000000 || SYSCLK_FREQ_HSE == 144000000 || \
  SYSCLK_FREQ_144MHz_HSI == 144000000 || SYSCLK_FREQ_HSI == 144000000
#define CH32_F_CPU 144000000

#elif SYSCLK_FREQ_120MHz_HSE == 120000000 || SYSCLK_FREQ_HSE == 120000000 || \
  SYSCLK_FREQ_120MHz_HSI == 120000000 || SYSCLK_FREQ_HSI == 120000000
#define CH32_F_CPU 120000000

#elif SYSCLK_FREQ_96MHz_HSE == 96000000 || SYSCLK_FREQ_HSE == 96000000 || \
  SYSCLK_FREQ_96MHz_HSI == 96000000 || SYSCLK_FREQ_HSI == 96000000
#define CH32_F_CPU 96000000

#elif SYSCLK_FREQ_72MHz_HSE == 72000000 || SYSCLK_FREQ_HSE == 72000000 || \
  SYSCLK_FREQ_72MHz_HSI == 72000000 || SYSCLK_FREQ_HSI == 72000000
#define CH32_F_CPU 72000000

#elif SYSCLK_FREQ_56MHz_HSE == 56000000 || SYSCLK_FREQ_HSE == 56000000 || \
  SYSCLK_FREQ_56MHz_HSI == 56000000 || SYSCLK_FREQ_HSI == 56000000
#define CH32_F_CPU 56000000

#elif SYSCLK_FREQ_48MHz_HSE == 48000000 || SYSCLK_FREQ_HSE == 48000000 || \
  SYSCLK_FREQ_48MHz_HSI == 48000000 || SYSCLK_FREQ_HSI == 48000000
#define CH32_F_CPU 48000000

#endif