//
// Created by 袁浩东 on 16/6/10.
//

#ifndef WNSLOGHELPER_FILEUTILS_HPP
#define WNSLOGHELPER_FILEUTILS_HPP

#include <dirent.h>
#include <sys/stat.h>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

bool isLogFile(char *filename) {
    return filename[0] != '.';
}

void splitFilename(const string& str, string &folder, string &filename){
	size_t found;
	found = str.find_last_of("/\\");
	folder = str.substr(0, found);
	filename = str.substr(found + 1);
}

bool isFile(const char *path) {
    struct stat s;
    if (stat(path, &s) == 0) {
        if (s.st_mode & S_IFREG) {
            return true;
        }
    }
    return false;
}

int listFiles(const char *dirname, vector<string> &out) {
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(dirname)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (!isLogFile(ent->d_name)) {
                continue;
            }
            string s(dirname);
            s = s + "/" + ent->d_name;

            if (!isFile(s.c_str())) {
                continue;
            }

            out.push_back(s);
        }
        closedir(dir);
    } else {
        perror("Failed to visit directory!");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

#endif