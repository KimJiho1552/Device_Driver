#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <asm/uaccess.h>

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

void led_write(char data) {
    int i;
    for(i = 0; i < ARRAY_SIZE(led); i++){
        gpio_direction_output(led[i], (data >> i) & 0x01);
    }
#if DEBUG
    printk("#### %s, data = %d\n", __FUNCTION__, data);
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

static int ledkey_open(struct inode* inode, struct file* filp) {
	int num0 = MINOR(inode -> i_rdev);
	int num1 = MAJOR(inode -> i_rdev);
	printk("call open -> minor : %d\n", num0);
	printk("call open -> major : %d\n", num1);
	init_led();
	init_key();
	return 0;
}

static loff_t ledkey_llseek(struct file* filp, loff_t off, int whence) {
	printk("call llseek -> off : %08X, whence : %08X\n", (unsigned int)off, whence);
	return 0x23;
}

static ssize_t ledkey_read(struct file* filp, char* buf, size_t count, loff_t* f_pos) {
//	printk("call read -> buf : %08X, count : %08X\n", (unsigned int)buf, count);
	char kbuf;
	int ret;
	
//	key_read(buf);
	key_read(&kbuf); //?????? ???????????? ????????? ????????? ??????
//	put_user(kbuf, buf); //??????(kernel ??????), ?????????(????????? ??????)
	ret = copy_to_user(buf, &kbuf, count);
/*
   char kbuf[10] = {0}; //Not 1byte
   for(int i = 0; i < count; i++)
	   put_user(kbuf[i], buf++);
*/
	return count;
}

static ssize_t ledkey_write(struct file*  filp, const char* buf, size_t count, loff_t* f_pos) {
//	printk("call write -> buf : %08X, count : %08X\n", (unsigned int)buf, count);
	char kbuf;
	int ret;

//	get_user(kbuf, buf); //?????? ????????? ?????? ????????? ???????????? ?????????
	ret = copy_from_user(&kbuf, buf, count);
//	led_write(buf);
	led_write(kbuf);
	return count;
}

static long ledkey_inctl(struct file* filp, unsigned int cmd, unsigned long arg) {
	printk("call ioctl -> cmd : %08X, arg : %08X\n", cmd, (unsigned int)arg);
	return 0x53;
}

static int ledkey_release(struct inode* inode, struct file* filp) {
	printk("call release\n");
	exit_led();
	exit_key();
	return 0;
}

struct file_operations call_fops =
{
	.owner          = THIS_MODULE,
	.llseek         = ledkey_llseek,
	.read           = ledkey_read,
	.write          = ledkey_write,
	.unlocked_ioctl = ledkey_inctl,
	.open           = ledkey_open,
	.release        = ledkey_release,
};

static int ledkey_init(void) {
	int result;
	printk("call call_init\n");
	result = register_chrdev(CALL_DEV_MAJOR, CALL_DEV_NAME, &call_fops);
	if(result < 0) return result;
	return 0;
}

static void ledkey_exit(void) {
	printk("call call_exit\n");
	unregister_chrdev(CALL_DEV_MAJOR, CALL_DEV_NAME);
}

module_init(ledkey_init);
module_exit(ledkey_exit);
MODULE_LICENSE("Dual BSD/GPL");
