#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include <linux/gpio.h>
#define DEBUG 1
#define IMX_GPIO_NR(bank, nr)       (((bank) - 1) * 32 + (nr))
#define CALL_DEV_NAME  "ledkey"
#define CALL_DEV_MAJOR  240

static int led[] = {
    IMX_GPIO_NR(1, 16),   //16
    IMX_GPIO_NR(1, 17),   //17
    IMX_GPIO_NR(1, 18),   //18
    IMX_GPIO_NR(1, 19),   //19
};

static int key[] = {
	IMX_GPIO_NR(1, 20), //SW1
	IMX_GPIO_NR(1, 21), //SW2
	IMX_GPIO_NR(4, 8),  //SW3
	IMX_GPIO_NR(4, 9),  //SW4
  	IMX_GPIO_NR(4, 5),
  	IMX_GPIO_NR(7, 13),
  	IMX_GPIO_NR(1, 7),
 	IMX_GPIO_NR(1, 8),
};

static int init_led(void) {
    int ret = 0;
    int i;

    for(i = 0; i < ARRAY_SIZE(led); i++) {
		ret = gpio_request(led[i], "gpio led");
        if(ret < 0) {
            printk("#### FAILED Request gpio %d. error : %d \n", led[i], ret);
        }
    }
    return ret;
}

static int init_key(void) {
	int ret = 0;
	int i;

	for(i = 0; i < ARRAY_SIZE(key); i++) {
		ret = gpio_request(key[i], "gpio key");
		if(ret < 0) {
			printk("#### FAILED Request gpio %d. error : %d \n", key[i], ret);
		}
	}
	return ret;
}

static void exit_led(void) {
    int i;
    for(i = 0; i < ARRAY_SIZE(led); i++) {
        gpio_free(led[i]);
    }
}

static void exit_key(void) {
	int i;
	for(i = 0; i < ARRAY_SIZE(key); i++) {
		gpio_free(key[i]);
	}
}

void led_write(unsigned long data) {
    int i;
    for(i = 0; i < ARRAY_SIZE(led); i++){
        gpio_direction_output(led[i], (data >> i) & 0x01);
    }
#if DEBUG
    printk("#### %s, data = %ld\n", __FUNCTION__, data);
#endif
}

//void led_read(char* led_data) {
void key_read(char* led_data) {
    int i;
	int j;
    unsigned long data = 0;
    unsigned long temp;
	unsigned long val = 0;
    for(i = 0 ; i < 8; i++) {
        gpio_direction_input(key[i]); //error led all turn off
        temp = gpio_get_value(key[i]) << i;
        data |= temp;
    }
	for(j = 0; j <= 8; j++) {
		if(val == data) {
			*led_data = (char)j;
			break;
		}
		else
			val = 0x01 << j;
	}
    return;
}

static int call_open(struct inode* inode, struct file* filp) {
	int num0 = MINOR(inode -> i_rdev);
	int num1 = MAJOR(inode -> i_rdev);
	printk("call open -> minor : %d\n", num0);
	printk("call open -> major : %d\n", num1);
	init_led();
	init_key();
	return 0;
}

static loff_t call_llseek(struct file* filp, loff_t off, int whence) {
	printk("call llseek -> off : %08X, whence : %08X\n", (unsigned int)off, whence);
	return 0x23;
}

static ssize_t call_read(struct file* filp, char* buf, size_t count, loff_t* f_pos) {
	printk("call read -> buf : %08X, count : %08X\n", (unsigned int)buf, count);
	key_read(buf);
	return count;
}

static ssize_t call_write(struct file*  filp, const char* buf, size_t count, loff_t* f_pos) {
	printk("call write -> buf : %08X, count : %08X\n", (unsigned int)buf, count);
	led_write(*buf);
	return count;
}

static long call_inctl(struct file* filp, unsigned int cmd, unsigned long arg) {
	printk("call ioctl -> cmd : %08X, arg : %08X\n", cmd, (unsigned int)arg);
	return 0x53;
}

static int call_release(struct inode* inode, struct file* filp) {
	printk("call release\n");
	exit_led();
	exit_key();
	return 0;
}

struct file_operations call_fops =
{
	.owner = THIS_MODULE,
	.llseek = call_llseek,
	.read = call_read,
	.write = call_write,
	.unlocked_ioctl = call_inctl,
	.open = call_open,
	.release = call_release,
};

static int call_init(void) {
	int result;
	printk("call call_init\n");
	result = register_chrdev(CALL_DEV_MAJOR, CALL_DEV_NAME, &call_fops);
	if(result < 0) return result;
	return 0;
}

static void call_exit(void) {
	printk("call call_exit\n");
	unregister_chrdev(CALL_DEV_MAJOR, CALL_DEV_NAME);
}

module_init(call_init);
module_exit(call_exit);
MODULE_LICENSE("Dual BSD/GPL");
