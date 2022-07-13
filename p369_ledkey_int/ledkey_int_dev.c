#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <asm/uaccess.h>

#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/fcntl.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/irq.h>

#define CALL_DEV_NAME  "ledkey_int"
#define CALL_DEV_MAJOR  240
#define DEBUG 0
#define IMX_GPIO_NR(bank, nr)       (((bank) - 1) * 32 + (nr))

static int sw_irq[8] = {0};
static long sw_no = 0;

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

irqreturn_t sw_isr(int irq, void* unuse) {
	int i;
	for(i = 0; i < ARRAY_SIZE(key); i++) {
		if(irq == sw_irq[i]) {
			sw_no = i + 1;
			break;
		}
	}
	printk("IRQ : %d, %ld\n", irq, sw_no);
	return IRQ_HANDLED;
}

static int led_init(void) {
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

#if 0
static int key_init(void) {
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
#endif

static int key_irq_init(void) {
	int ret = 0;
	int i;
	char* irq_name[8] = {"irq sw1", "irq sw2", "irq sw3", "irq sw4", "irq sw5", "irq sw6", "irq sw7", "irq sw8"};
	for(i = 0; i < ARRAY_SIZE(key); i++) {
		sw_irq[i] = gpio_to_irq(key[i]); //GPIO번호를 irq번호로 변환
	}
	for(i = 0; i < ARRAY_SIZE(key); i++) {
		ret = request_irq(sw_irq[i], sw_isr, IRQF_TRIGGER_RISING, irq_name[i], NULL);
		if(ret) {
			printk("### FAILED Request irq %d, error : %d", sw_irq[i], ret);
		}
	}
	return ret;
}

static void led_exit(void) {
    int i;
    for(i = 0; i < ARRAY_SIZE(led); i++) {
        gpio_free(led[i]);
    }
}

#if 0
static void key_exit(void) {
	int i;
	for(i = 0; i < ARRAY_SIZE(key); i++) {
		gpio_free(key[i]);
	}
}
#endif

static void key_irq_exit(void) {
	int i;
	for(i = 0; i < ARRAY_SIZE(key); i++)
		free_irq(sw_irq[i], NULL);
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

#if 0
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
#endif

static int ledkey_open(struct inode* inode, struct file* filp) {
	int num0 = MINOR(inode -> i_rdev);
	int num1 = MAJOR(inode -> i_rdev);
	printk("call open -> minor : %d\n", num0);
	printk("call open -> major : %d\n", num1);
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
//	key_read(&kbuf); //먼저 읽어오고 사용자 공간에 담음
//	put_user(kbuf, buf); //변수(kernel 버퍼), 포인터(사용자 버퍼)
	kbuf = (char)sw_no;
	ret = copy_to_user(buf, &kbuf, count);
	sw_no = 0;
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

//	get_user(kbuf, buf); //먼저 사용자 공간 주소의 데이터를 담아옴
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

	led_init();
//	key_init();
	key_irq_init();
	return 0;
}

static void ledkey_exit(void) {
	printk("call call_exit\n");
	unregister_chrdev(CALL_DEV_MAJOR, CALL_DEV_NAME);
	led_exit();
//	key_exit();
	key_irq_exit();
}

module_init(ledkey_init);
module_exit(ledkey_exit);
MODULE_LICENSE("Dual BSD/GPL");
