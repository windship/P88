#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>
#include <io.h>

#define MAX_FILES 128
#define MAX_CMDLINE 1024

char filenames[MAX_FILES][13];
int file_count = 0;

int my_stricmp(const char *s1, const char *s2) {
    int i = 0;
    while (s1[i] && s2[i]) {
        char c1 = s1[i];
        char c2 = s2[i];
        if (c1 >= 'A' && c1 <= 'Z') c1 += 'a' - 'A';
        if (c2 >= 'A' && c2 <= 'Z') c2 += 'a' - 'A';
        if (c1 != c2) return (unsigned char)c1 - (unsigned char)c2;
        i++;
    }
    return (unsigned char)s1[i] - (unsigned char)s2[i];
}

int cmp_str(const void *a, const void *b) {
    return my_stricmp((const char*)a, (const char*)b);
}

int my_isdigit(char c) {
    return (c >= '0' && c <= '9');
}

int get_priority_disk(int argc, char *argv[]) {
    int i;
    for (i = 1; i < argc; i++) {
        if (argv[i][0] == '#' && my_isdigit(argv[i][1])) {
            return atoi(&argv[i][1]) - 1;
        }
    }
    return -1;
}

int is_priority_arg(const char *arg) {
    return arg[0] == '#' && my_isdigit(arg[1]);
}

void reorder_disk(int index) {
    if (index <= 0 || index >= file_count) return;
    {
        char temp[13];
        int i;
        strcpy(temp, filenames[index]);
        for (i = index; i > 0; i--) {
            strcpy(filenames[i], filenames[i - 1]);
        }
        strcpy(filenames[0], temp);
    }
}

int main(int argc, char *argv[]) {
    char cmdline[MAX_CMDLINE] = "P88SR.EXE";
    struct find_t fcb;
    int done;
    int i;
    int prio_index;

    for (i = 1; i < argc; i++) {
        if (is_priority_arg(argv[i])) continue;
        if (strlen(cmdline) + strlen(argv[i]) + 2 >= MAX_CMDLINE) break;
        strcat(cmdline, " ");
        strcat(cmdline, argv[i]);
    }

    done = _dos_findfirst("*.D88", 0, &fcb);
    while (!done && file_count < MAX_FILES) {
        strncpy(filenames[file_count], fcb.name, 12);
        filenames[file_count][12] = '\0';
        file_count++;
        done = _dos_findnext(&fcb);
    }

    if (file_count == 0) {
        printf("D88ディスクが発見されませんでした。\n");
        return 1;
    }

    qsort(filenames, file_count, sizeof(filenames[0]), cmp_str);

    printf("P88 / P88SR 便利ランチャー v0.1                  (c) windship 2025\n");
	printf("--------------------------------------------------------------------\n");

    prio_index = get_priority_disk(argc, argv);
    if (prio_index >= file_count) {
        printf("指定された起動ディスクは存在しません。現在のディスクセットは %d枚です。\n\n", file_count - 1);
    } else if (prio_index >= 0) {
        reorder_disk(prio_index);
    }

    for (i = 0; i < file_count; i++) {
        if (strlen(cmdline) + strlen(filenames[i]) + 2 >= MAX_CMDLINE) break;
        strcat(cmdline, " ");
        strcat(cmdline, filenames[i]);
    }
	
    printf("次のディスクセットでP88SRを実行します: \n");
	printf("%s\n", cmdline);
    delay(1000); // 1? ??
    system(cmdline);

    return 0;
}
