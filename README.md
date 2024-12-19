# ticket-management-system 项目文档

该项目是一个车票管理系统，旨在为用户提供便捷的车票查询和预定服务。系统分为管理员和普通用户两种角色，具有以下功能：

## 功能概述

### 管理员功能
- 添加、修改和查看班次信息

### 普通用户功能
- 查询当前班车信息
- 预定车票
- 查询已订车票

## 文件结构

```
ticket-management-system
├── src
│   ├── main.c          // 程序入口点
│   ├── admin.c         // 管理员功能实现
│   ├── admin.h         // 管理员功能接口
│   ├── user.c          // 普通用户功能实现
│   ├── user.h          // 普通用户功能接口
│   ├── database.c      // 数据库操作实现
│   ├── database.h      // 数据库操作接口
│   └── utils
│       ├── auth.c      // 用户认证实现
│       ├── auth.h      // 用户认证接口
│       └── file_handler.h // 文件处理接口
|       └── file_handler.c // 文件处理实现
├── data
│   ├── users.txt       // 用户信息存储
│   └── schedules.txt   // 车次信息存储
│   └── bookings.txt   // 预定车次信息存储
├── include
│   └── common.h        // 公共常量和类型定义
├── Makefile            // 构建项目的规则和目标
└── README.md           // 项目文档和使用说明
```

## 使用说明

1. **编译项目**：在项目根目录下运行 mingw的make程序 例如'mingw32-make'(我是在Windows环境下的VSCode中编写并编译的)
2. **其他操作**：在make操作后接clean清理编译临时文件
3. **运行程序**：编译完成后，在make操作后解run执行程序

## 注意事项

由于编译系统在windows下，因此所有源码都使用GB2312编程。编译好后的程序生成在build目录下，如果直接运行会因为定位不到数据文件而无法正常登录，需要使用如'mingw32-make run'或是将编译好的程序和data目录放在同目录下才能正常运行