/* 全局头文件 */
#include "msg.h"
#include "log.h"
#include "common.h"

int main(int argc, char *argv[])
{
        int ret;

        /* 初始化ｌｏｇ日志管理 */
        log_init();
#if 0     
        /* 创建线程*/
        INFO("Create Thread.");
        ret = create_thread();
        if (ret != 0) {
                ERROR("create thread error\n");
                return -1;
        } 
        
        /*初始化设备*/
        INFO("Device Initialization.");
        ret = init_device();
        if (ret != 0) {
                ERROR("init device error\n");
                return -1;
        } 
#endif   
        /* 创建socket */
        INFO("Create Socket.");
        ret = create_socket();
        if (ret != 0) {
            ERROR("create socket error\n");
            return -1;
        }
        
        return 0;
}
