#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/gpio.h>
#define DEBUG 1
#define IMX_GPIO_NR(bank, nr)       (((bank) - 1) * 32 + (nr))

int led[] = {
    IMX_GPIO_NR(1, 16),   //16
    IMX_GPIO_NR(1, 17),   //17
    IMX_GPIO_NR(1, 18),   //18
    IMX_GPIO_NR(1, 19),   //19
};

static int init_led(void) {
    int ret = 0;
    int i;

    for (i = 0; i < ARRAY_SIZE(led); i++) {
        ret = gpio_request(led[i], "gpio led");
        if(ret < 0){
            printk("#### FAILED Request gpio %d. error : %d \n", led[i], ret);
        }
        gpio_direction_output(led[i], 0);
    }
    return ret;
}

static void exit_led(void) {
    int i;
    for (i = 0; i < ARRAY_SIZE(led); i++){
        gpio_free(led[i]);
    }
}

void led_write(unsigned long data) {
    int i;
    for(i = 0; i < ARRAY_SIZE(led); i++){
        gpio_set_value(led[i], (data >> i) & 0x01);
    }
#if DEBUG
    printk("#### %s, data = %ld\n", __FUNCTION__, data);
#endif
}

/*
void led_read(unsigned long * led_data) {
    int i;
    unsigned long data=0;
    unsigned long temp;
    for(i = 0 ;i < 4; i++) {
        gpio_direction_input(led[i]); //error led all turn off
        temp = gpio_get_value(led[i]) << i;
        data |= temp;
    }
#if DEBUG
    printk("#### %s, data = %ld\n", __FUNCTION__, data);
#endif
    *led_data = data;
    return;
}
*/

static int LED_init(void) {
    printk("LED ON\n");
    init_led();
    led_write(15);
//    led_read(&led_data);
    return 0;
}

static void LED_exit(void) {
	printk("LED OFF\n");
    led_write(0);
    exit_led();
}

module_init(LED_init);
module_exit(LED_exit);

MODULE_AUTHOR("kcci");
MODULE_DESCRIPTION("test module");
MODULE_LICENSE("Dual BSD/GPL");
