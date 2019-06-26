#include <linux/module.h> 
#include <linux/printk.h> 
#include <linux/kobject.h> 
#include <linux/sysfs.h> 
#include <linux/init.h> 
#include <linux/fs.h> 
#include <linux/string.h> 

#define MAX_POLICY 2
#define MIN_POLICY 0

static struct kobject *lb_policy;
static int policy;

/**extern int load_balance_set_action(int new_action);**/

static ssize_t policy_show(struct kobject *kobj, struct kobj_attribute *attr,
                      char *buf)
{
        return sprintf(buf, "%d\n", policy);
}

static ssize_t policy_store(struct kobject *kobj, struct kobj_attribute *attr,
                      const char *buf, size_t count)
{
        int ret = sscanf(buf, "%du", &policy);
        if (ret != 1)
                return -EINVAL;
	
	if (!(policy >= MIN_ACTION && policy <= MAX_ACTION)) {
		pr_debug("policy %d is not allowed!\n", policy);
		return -EPERM;
	}

        /***TO DO: RL update****/

        pr_debug("new action is %d\n", policy);

        return count;
}


static struct kobj_attribute policy_attribute =__ATTR(policy, 0644, policy_show, policy_store);

static int __init rlmodule_init (void)
{
        int error = 0;

        pr_debug("Module initialized successfully \n");

        lb_policy = kobject_create_and_add("lb_policy",
                                                 kernel_kobj);
        if(!lb_policy)
                return -ENOMEM;

        error = sysfs_create_file(lb_policy, &policy_attribute.attr);
        if (error) {
                pr_debug("failed to create the action file in /sys/kernel/lb_action \n");
        }

        return error;
}

static void __exit rlmodule_exit (void)
{
        pr_debug ("Module un initialized successfully \n");
        kobject_put(lb_policy);
	sysfs_remove_file(kernel_kobj, &policy_attribute.attr);
}

module_init(rlmodule_init); 
module_exit(rlmodule_exit); 
MODULE_LICENSE("GPL"); 
MODULE_AUTHOR("Unknown");

