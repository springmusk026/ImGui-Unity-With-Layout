#ifndef UTILS
#define UTILS

#include <jni.h>
#include <unistd.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include <dlfcn.h>

typedef unsigned long DWORD;

static uintptr_t address;

#define sofile ("libil2cpp.so")

DWORD findLibrary(const char *library) {
    char filename[0xFF] = {0},
            buffer[1024] = {0};
    FILE *fp = NULL;
    DWORD address = 0;

    sprintf(filename, ("/proc/self/maps"));

    fp = fopen(filename, ("rt"));
    if (fp == NULL) {
        perror(("fopen"));
        goto done;
    }

    while (fgets(buffer, sizeof(buffer), fp)) {
        if (strstr(buffer, library)) {
            address = (DWORD) strtoul(buffer, NULL, 16);
            goto done;
        }
    }

    done:

    if (fp) {
        fclose(fp);
    }

    return address;
}

DWORD getAbsoluteAddress(const char *libraryName, DWORD relativeAddr) {
    address = findLibrary(libraryName);
    if (address == 0)
        return 0;
    return (reinterpret_cast<DWORD>(address + relativeAddr));
}

#endif