#include <stdio.h>

int main() {
    // Windows 检测
    #ifdef _WIN32
        printf("Windows 32-bit or 64-bit\n");
    #endif
    
    #ifdef _WIN64
        printf("Windows 64-bit\n");
    #endif
    
    // Linux/Unix 检测
    #ifdef __linux__
        printf("Linux\n");
    #endif
    
    #ifdef __unix__
        printf("Unix\n");
    #endif
    
    #ifdef __APPLE__
        #ifdef __MACH__
            printf("macOS\n");
        #endif
    #endif
    
    // ARM 架构检测
    #ifdef __arm__
        printf("ARM architecture\n");
    #endif
    
    #ifdef __aarch64__
        printf("ARM64 (AArch64) architecture\n");
    #endif
    
    // x86/x64 检测
    #ifdef __i386__
        printf("x86 (32-bit) architecture\n");
    #endif
    
    #ifdef __x86_64__
        printf("x64 (64-bit) architecture\n");
    #endif
    
    return 0;
}
