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
#include <linux/sched.h>
#include <linux/wait.h>
#include "ioctl_test.h"

#define CALL_DEV_NAME  "jiffies_int"
#define CALL_DEV_MAJOR  240
#define DEBUG 0
#define IMX_GPIO_NR(bank, nr)       (((bank) - 1) * 32 + (nr))

DECLARE_WAIT_QUEUE_HEAD(WaitQueue_Read);
static int sw_irq[8] = {0};
static long sw_no = 0;

static long B_jiffies = 0;
static long N_jiffies = 0;
static long time_diff = 0;

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
//	printk("IRQ : %d, %ld\n", irq, sw_no);
	wake_up_interruptible(&WaitQueue_Read);
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
	char kbuf;
	int ret;

	if(!(filp->f_flags & O_NONBLOCK))
		if(sw_no == 0)
			interruptible_sleep_on(&WaitQueue_Read);
	kbuf = (char)sw_no;
	ret = copy_to_user(buf, &kbuf, count);

	N_jiffies = get_jiffies_64();
	time_diff = N_jiffies - B_jiffies;
	if(B_jiffies == 0)
		printk("Before : %ld, Now : %ld\n", B_jiffies, N_jiffies);
	else
		printk("Before : %ld, Now : %ld, Time : %ld\n", B_jiffies, N_jiffies, time_diff);
	B_jiffies = N_jiffies;

	sw_no = 0;
	return count;
}

static ssize_t ledkey_write(struct file*  filp, const char* buf, size_t count, loff_t* f_pos) {
	char kbuf;
	int ret;

	ret = copy_from_user(&kbuf, buf, count);
	led_write(kbuf);
	return count;
}

static long ledkey_ioctl (struct file *filp, unsigned int cmd, unsigned long arg) {
    ioctl_test_info ctrl_info = {0, 0, {0}};
    int err, size, ret;
    if( _IOC_TYPE( cmd ) != IOCTLTEST_MAGIC ) return -EINVAL;
    if( _IOC_NR( cmd ) >= IOCTLTEST_MAXNR ) return -EINVAL;

    size = _IOC_SIZE( cmd );
    if( size ) {
        err = 0;
        if( _IOC_DIR( cmd ) & _IOC_READ )
            err = access_ok( VERIFY_WRITE, (void *) arg, size );
        else if( _IOC_DIR( cmd ) & _IOC_WRITE )
            err = access_ok( VERIFY_READ , (void *) arg, size );
        if( !err ) return err;
    }
    switch( cmd ) {
        case IOCTLTEST_READ :
			ctrl_info.time = time_diff;
            ret = copy_to_user((void*)arg, (void*)&ctrl_info, sizeof(ctrl_info));
            break;
        default :
            break;
    }
    return 0;
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
	.unlocked_ioctl = ledkey_ioctl,
	.open           = ledkey_open,
	.release        = ledkey_release,
};

static int ledkey_init(void) {
	int result;
	printk("call call_init\n");
	result = register_chrdev(CALL_DEV_MAJOR, CALL_DEV_NAME, &call_fops);
	if(result < 0) return result;

	led_init();
	key_irq_init();
	return 0;
}

static void ledkey_exit(void) {
	printk("call call_exit\n");
	unregister_chrdev(CALL_DEV_MAJOR, CALL_DEV_NAME);
	led_exit();
	key_irq_exit();
}

module_init(ledkey_init);
module_exit(ledkey_exit);
MODULE_LICENSE("Dual BSD/GPL");
