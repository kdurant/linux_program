#include <pwd.h>
#include <grp.h>
#include <ctype.h>
#include <stddef.h> // NULL
#include <stdlib.h> // strtol
#include "ugid_functions.h"

char* userNameFromId(uid_t uid) {
    struct passwd* pwd = getpwuid(uid);
    return pwd == NULL ? NULL : pwd->pw_name;
}

uid_t userIdFromName(const char* name) {
    if (name == NULL || *name == '\0') {
        return -1;
    }

    // 如果 name 直接是全数字的字符串，则直接返回这个数字
    char* endptr;
    uid_t uid = strtol(name, &endptr, 10);
    if (*endptr == '\0') {
        return uid;
    }

    struct passwd* pwd;
    pwd = getpwnam(name);
    if (pwd == NULL) {
        return -1;
    }
    return pwd->pw_uid;
}

char* groupNameFromId(gid_t gid) {
    struct group *grp = getgrgid(gid);
    return grp == NULL ? NULL : grp->gr_name;
}

gid_t groupIdFromName(const char* name) {
    if (name == NULL || *name == '\0') {
        return -1;
    }

    // 如果 name 直接是全数字的字符串，则直接返回这个数字
    char* endptr;
    gid_t gid = strtol(name, &endptr, 10);
    if (*endptr == '\0') {
        return gid;
    }

    struct group* grp = getgrnam(name);
    if (grp == NULL) {
        return -1;
    }
    return grp->gr_gid;
}