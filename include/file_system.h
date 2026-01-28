#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H
#define FS_READ   0x1
#define FS_WRITE  0x2

int fs_createFile(const char *name, int permissions); 
int fs_readFile(const char *name); // Read file 
int fs_writeFile(const char *name, const char *data); // Write data 
int fs_deleteFile(const char *name); // Delete file 
void fs_listFiles(void); // show all files
void fs_cleanup(void);   // cleanup


#endif
