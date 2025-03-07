/*
===========================================================================
Copyright (C) 1999-2005 Id Software, Inc.

This file is part of Quake III Arena source code.

Quake III Arena source code is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the License,
or (at your option) any later version.

Quake III Arena source code is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Quake III Arena source code; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
===========================================================================
*/
//
// q_ac.c -- Unix and Windows compatible AC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#ifdef _WIN32
#include <windows.h>
#include <tlhelp32.h>
#endif

#define MAX_LINE 512

#ifdef __linux__
const char *allowed_libs_lin[] = {
    "/lib/x86_64-linux-gnu/libc.so.6", // Adjust for your system
    "/lib64/ld-linux-x86-64.so.2",      // Adjust for your system
    "engine_vulkan_x86_64.so",
    "engine_opengl_x86_64.so",
    NULL // End marker
};
#endif

#ifdef _WIN32
const char *allowed_libs_win[] = {
    "C:\\Windows\\System32\\kernel32.dll",  // Full path for Windows system DLLs
    "C:\\Windows\\System32\\ntdll.dll",    // Full path for Windows system DLLs
    "engine_vulkan_x86_64.dll",
    "engine_opengl_x86_64.dll",
    NULL // End marker
};
#endif

// Function to check if a given library is allowed
bool is_allowed_lib(const char *lib) {
#ifdef __linux__
    for (int i = 0; allowed_libs_lin[i] != NULL; i++) {
        if (strstr(lib, allowed_libs_lin[i])) {
            return true;
        }
    }
#endif
#ifdef _WIN32
    for (int i = 0; allowed_libs_win[i] != NULL; i++) {
        if (strstr(lib, allowed_libs_win[i])) {
            return true;
        }
    }
#endif
    return false;
}

#ifdef __linux__
// Function to detect injected shared objects (Linux)
void detect_injected_so() {
    FILE *maps = fopen("/proc/self/maps", "r"); // Injections are usually mapped in /proc/self/maps
    if (!maps) {
        perror("Failed to open /proc/self/maps");
        return;
    }
    
    char line[MAX_LINE];
    while (fgets(line, sizeof(line), maps)) {
        if (strstr(line, ".so") && !is_allowed_lib(line)) {
            printf("[!Qytrine AntiCheat!] Detected suspicious shared object: %s", line);
        }
    }
    fclose(maps);
}

// Function to scan memory for suspicious RWX pages (Linux)
void detect_suspicious_memory() {
    FILE *maps = fopen("/proc/self/maps", "r");
    if (!maps) {
        perror("Failed to open /proc/self/maps");
        return;
    }
    
    char line[MAX_LINE];
    while (fgets(line, sizeof(line), maps)) {
        if (strstr(line, "rwx")) {
            printf("[!Qytrine AntiCheat!] Detected RWX memory region: %s", line);
        }
    }
    fclose(maps);
}
#endif

#ifdef _WIN32
// Function to detect injected DLLs (Windows)
void detect_injected_dlls() {
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetCurrentProcessId());
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        printf("[!Qytrine AntiCheat!] Failed to create snapshot.\n");
        return;
    }
    
    MODULEENTRY32 me;
    me.dwSize = sizeof(MODULEENTRY32);
    if (Module32First(hSnapshot, &me)) {
        do {
            if (!is_allowed_lib(me.szExePath)) {
                printf("[!Qytrine AntiCheat!] Detected suspicious DLL: %s\n", me.szExePath);
            }
        } while (Module32Next(hSnapshot, &me));
    }
    CloseHandle(hSnapshot);
}
#endif

// Main function to run the anti-cheat checks
void run_anticheat() {
    printf("[!Qytrine AntiCheat!] Running security checks...\n");
#ifdef __linux__
    detect_injected_so();
    detect_suspicious_memory();
#endif
#ifdef _WIN32
    detect_injected_dlls();
#endif
    printf("[ANTICHEAT LOG] Scan complete.\n");
}

// Example integration into a main function
int main() {
    run_anticheat();
    
}
