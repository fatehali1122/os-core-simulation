#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_system.h"


/* =====================================
   FILE METADATA STRUCTURE
   ===================================== */



typedef struct FileNode {
    char name[32];           
    int permissions;         // READ/WRITE
    char *content;           // dynamically allocated data
    size_t size;             
    struct FileNode *next;   // linked list
} FileNode;

static FileNode *fs_head = NULL;
static int file_count = 0;

static FileNode* findFile(const char *name)
{
    FileNode *curr = fs_head;
    while (curr) {
        if (strcmp(curr->name, name) == 0)
            return curr;
        curr = curr->next;
    }
    return NULL;
}

int fs_createFile(const char *name, int permissions) 
{
    if (findFile(name)) //  checks duplicate file
    {
        printf("File '%s' already exists\n", name);
        return -1;
    }

    FileNode *file = (FileNode*)calloc(1, sizeof(FileNode));
    if (!file)
    {
        printf("File allocation failed\n");
        return -1;
    }

    strncpy(file->name, name, sizeof(file->name) - 1);
    file->permissions = permissions;
    file->content = NULL;
    file->size = 0;

    file->next = fs_head;
    fs_head = file;

	file_count++;
    printf("File '%s' created\n", name);
    return 0;
}

int fs_readFile(const char *name)
{
    FileNode *file = findFile(name);
    if (!file) {
        printf("File '%s' not found\n", name);
        return -1;
    }

    if (!(file->permissions & FS_READ)) {
        printf("Read permission denied for '%s'\n", name);
        return -1;
    }

    printf("---- %s (%zu bytes) ----\n",
           file->name, file->size);

    if (file->content)
        printf("%s\n", file->content);
    else
        printf("(empty)\n");

    return 0;
}

int fs_writeFile(const char *name, const char *data)
{
    FileNode *file = findFile(name);
    if (!file) {
        printf("File '%s' not found\n", name);
        return -1;
    }

    if (!(file->permissions & FS_WRITE)) {
        printf("Write permission denied for '%s'\n", name);
        return -1;
    }

    // Freeing old content  
    free(file->content);

    file->size = strlen(data);
    file->content = (char*)malloc(file->size + 1);

    if (!file->content) {
        printf("Memory allocation failed\n");
        return -1;
    }

    strcpy(file->content, data);
    printf("Written %zu bytes to '%s'\n",
           file->size, file->name);

    return 0;
}

int fs_deleteFile(const char *name)
{
    FileNode *curr = fs_head;
    FileNode *prev = NULL;

    while (curr) {
        if (strcmp(curr->name, name) == 0) {

            if (prev)
                prev->next = curr->next;
            else
                fs_head = curr->next;
			file_count--;
            free(curr->content);
            free(curr);

            printf("File '%s' deleted\n", name);
            return 0;
        }
        prev = curr;
        curr = curr->next;
    }

    printf("File '%s' not found\n", name);
    return -1;
}

void fs_listFiles(void)
{
    FileNode *curr = fs_head;

    printf("\nFILE NAME        SIZE    PERM\n");
    printf("--------------------------------\n");

    while (curr)
     {
        printf("%-15s %-7zu %c%c\n",
               curr->name,
               curr->size,
               (curr->permissions & FS_READ) ? 'R' : '-',
               (curr->permissions & FS_WRITE) ? 'W' : '-');
        curr = curr->next;
    }
}

void fs_cleanup(void)
{
    FileNode *curr = fs_head;
    while (curr) {
        FileNode *tmp = curr;
        curr = curr->next;
        free(tmp->content);
        free(tmp);
    }
    fs_head = NULL;
}

void fs_init(void)
{
	if(fs_head != NULL) {
		
		fs_cleanup();
		
	}
    fs_head = NULL;
    file_count = 0;
	printf("File System Initialized.\n");
}

int getFileCount(void) {
	
	return file_count;
	
}