# STM32-HAL-CMake简单示例(集成FreeRTOS)

> 本工程基于CLion

## 在已生成并编辑的工程中添加外设教程:
- 在CubeMX中新生成一个工程,添加对应的外设
- 将新工程的`Src`和`Inc`目录下的对应外设文件(例: `adc.c` `adc.h` )拷贝到现有工程的 `Core/Src` 和 `Core/Inc` 中
- 在 `cmake/stm32cubemx/CMakeLists.txt` 中添加对应外设的源文件:
    ```cmake
    set(MX_Application_Src  # 对应Core/Src目录中的源文件
        ...
        ${CMAKE_CURRENT_SOURCE_DIR}/../Core/Src/adc.c
        ...
    )
    ```
- 在 `Core/Inc/stm32f4xx_hal_conf.h` 中取消预编译选项注释,声明对应外设
    ```c
    ...
    #define HAL_ADC_MODULE_ENABLED  // 取消注释以在编译时启用ADC
    ...
    ```
- 在 `Core/Inc/main.h` 中包含对应外设的头文件
    ```c
    #include "adc.h"  // 包含ADC头文件
    ```
- 在 `Core/Src/main.c` 中添加对应外设的初始化函数
    ```c
    int main(void)
    {
        ...
        MX_ADC_Init();  // 调用ADC初始化函数
        ...
    }
    ```

## 添加用户文件教程:
- 头文件加入到 `Core/Inc` 目录下即可自动被编译
- 源文件需要在 `CmakeLists.txt` 中添加:
    ```cmake
    set(MY_SOURCE  # 对应Core/Src目录中的源文件
        ...
        "Core/Src/app_main.c"
        ...
    )
  
    target_sources(${CMAKE_PROJECT_NAME} PRIVATE
        ${MY_SOURCE}
    ) # 添加用户源文件
    ```

## 注意事项:
- 如果要删除文件,务必在CmakeLists中删除对应的文件路径,否则会编译报错
- 更多基础教程参考 [B站视频](https://www.bilibili.com/video/BV1ren2zMEaS/)