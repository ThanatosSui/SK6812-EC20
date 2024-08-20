/*

*/

#ifndef __SK6812_EC20_H__
#define __SK6812_EC20_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "rpihw.h"
#include "pwm.h"

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#define sk6812_ec20_TARGET_FREQ                            800000        // Can go as low as 400000

// 3 color R, G and B ordering                        6 words / 24 digits, front two are 00
#define SK6812_EC20_STRIP_RGB                         0x00100800    // 00010000 00001000 00000000
#define SK6812_EC20_STRIP_RBG                         0x00100008    // 00010000 00000000 00001000
#define SK6812_EC20_STRIP_GRB                         0x00081000    // 00001000 00010000 00000000
#define SK6812_EC20_STRIP_GBR                         0x00080010    // 00001000 00000000 00010000
#define SK6812_EC20_STRIP_BRG                         0x00001008    // 00000000 00010000 00001000
#define SK6812_EC20_STRIP_BGR                         0x00000810    // 00000000 00001000 00010000

// predefined fixed LED types
#define SK6812_EC20_STRIP                             SK6812_EC20_STRIP_GRB

struct sk6812_ec20_device;

typedef uint32_t sk6812_ec20_led_t;                   //< 0xWWRRGGBB
typedef struct sk6812_ec20_channel_t
{
    int gpionum;                                 //< GPIO Pin with PWM alternate function, 0 if unused
    int invert;                                  //< Invert output signal
    int count;                                   //< Number of LEDs, 0 if channel is unused
    int strip_type;                              //< Strip color layout -- one of SK6812_EC20_STRIP_xxx constants
    sk6812_ec20_led_t *leds;                     //< LED buffers, allocated by driver based on count
    uint8_t brightness;                          //< Brightness value between 0 and 255
    //uint8_t wshift;                              //< White shift value
    uint8_t rshift;                              //< Red shift value
    uint8_t gshift;                              //< Green shift value
    uint8_t bshift;                              //< Blue shift value
    uint8_t *gamma;                              //< Gamma correction table
} sk6812_ec20_channel_t;

typedef struct sk6812_ec20_t
{
    uint64_t render_wait_time;                   //< time in µs before the next render can run
    struct sk6812_ec20_device *device;           //< Private data for driver use
    const rpi_hw_t *rpi_hw;                      //< RPI Hardware Information
    uint32_t freq;                               //< Required output frequency
    int dmanum;                                  //< DMA number _not_ already in use
    sk6812_ec20_channel_t channel[RPI_PWM_CHANNELS];
} sk6812_ec20_t;

#define SK6812_EC20_RETURN_STATES(X)                                                             \
            X(0,   SK6812_EC20_SUCCESS, "Success"),                                              \
            X(-1,  SK6812_EC20_ERROR_GENERIC, "Generic failure"),                                \
            X(-2,  SK6812_EC20_ERROR_OUT_OF_MEMORY, "Out of memory"),                            \
            X(-3,  SK6812_EC20_ERROR_HW_NOT_SUPPORTED, "Hardware revision is not supported"),    \
            X(-4,  SK6812_EC20_ERROR_MEM_LOCK, "Memory lock failed"),                            \
            X(-5,  SK6812_EC20_ERROR_MMAP, "mmap() failed"),                                     \
            X(-6,  SK6812_EC20_ERROR_MAP_REGISTERS, "Unable to map registers into userspace"),   \
            X(-7,  SK6812_EC20_ERROR_GPIO_INIT, "Unable to initialize GPIO"),                    \
            X(-8,  SK6812_EC20_ERROR_PWM_SETUP, "Unable to initialize PWM"),                     \
            X(-9,  SK6812_EC20_ERROR_MAILBOX_DEVICE, "Failed to create mailbox device"),         \
            X(-10, SK6812_EC20_ERROR_DMA, "DMA error"),                                          \
            X(-11, SK6812_EC20_ERROR_ILLEGAL_GPIO, "Selected GPIO not possible"),                \
            X(-12, SK6812_EC20_ERROR_PCM_SETUP, "Unable to initialize PCM"),                     \
            X(-13, SK6812_EC20_ERROR_SPI_SETUP, "Unable to initialize SPI"),                     \
            X(-14, SK6812_EC20_ERROR_SPI_TRANSFER, "SPI transfer error")                         \

#define SK6812_EC20_RETURN_STATES_ENUM(state, name, str) name = state
#define SK6812_EC20_RETURN_STATES_STRING(state, name, str) str

typedef enum {
    SK6812_EC20_RETURN_STATES(SK6812_EC20_RETURN_STATES_ENUM),

    SK6812_EC20_RETURN_STATE_COUNT
} sk6812_ec20_return_t;

sk6812_ec20_return_t sk6812_ec20_init(sk6812_ec20_t *sk6812_ec20);                              //< Initialize buffers/hardware
void sk6812_ec20_fini(sk6812_ec20_t *sk6812_ec20);                                              //< Tear it all down
sk6812_ec20_return_t sk6812_ec20_render(sk6812_ec20_t *sk6812_ec20);                            //< Send LEDs off to hardware
sk6812_ec20_return_t sk6812_ec20_wait(sk6812_ec20_t *sk6812_ec20);                              //< Wait for DMA completion
const char * sk6812_ec20_get_return_t_str(const sk6812_ec20_return_t state);                    //< Get string representation of the given return state
void sk6812_ec20_set_custom_gamma_factor(sk6812_ec20_t *sk6812_ec20, double gamma_factor);      //< Set a custom Gamma correction array based on a gamma correction factor

#ifdef __cplusplus
}
#endif

/*class SK6812_EC20 {
public: 
	SK6812_EC20(uint16_t num_led);
	~SK6812_EC20();
	
	void set_output(uint8_t pin);
	
	RGBW get_rgb(uint16_t index);
	uint8_t set_rgb(uint16_t index, RGB px_value);

	void sync();
	
private:
	uint16_t _count_led;
	RGB *_pixels;

	const volatile uint8_t *_port;
	volatile uint8_t *_port_reg;
	uint8_t _pin_mask;

	void sendarray_mask(uint8_t *array, uint16_t length, uint8_t pinmask, uint8_t *port, uint8_t *portreg);

};
*/
#endif /* __SK6812_EC20_H__ */