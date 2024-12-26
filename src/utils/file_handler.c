#include "file_handler.h"
#include <stdlib.h>
#include <string.h>

// 将数据写入文件
void write_to_file(const char *filename, const char *data) {
    FILE *file = fopen(filename, "a");  // 以追加模式打开文件
    if (file == NULL) {
        return;
    }
    fprintf(file, "%s\n", data); // 将数据写入文件
    fclose(file);
}

// 从文件中读取数据
char* read_from_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return NULL;
    }
    
    fseek(file, 0, SEEK_END); // 定位到文件末尾
    long size = ftell(file); // 获取文件大小
    fseek(file, 0, SEEK_SET); // 定位到文件开头
    
    char *content = (char*)malloc(size + 1); // 为文件内容分配内存
    if (content == NULL) {
        fclose(file);
        return NULL;
    }
    
    fread(content, 1, size, file); // 读取文件内容
    content[size] = '\0'; // 添加字符串结束符
    
    fclose(file);
    return content;
}