#ifndef _FILETABLE_H_
#define _FILETABLE_H_

#define TABLE_SIZE 1024

#include "tree.hh"

struct FILE_ITEM
{
    char *path;
    unsigned int nPathLen;
    unsigned char *handle;
    bool bCached;
};

struct FILE_TABLE
{
	tree_node_<FILE_ITEM>* pItems[TABLE_SIZE];
    FILE_TABLE *pNext;
};

struct CACHE_LIST
{
    FILE_ITEM *pItem;
    CACHE_LIST *pNext;
};
class CFileTree;
class CFileTable
{
public :

    static CFileTable g_FileTable;
    static CFileTree g_FileTree;
public:
    static bool FileExists(const char* path);
    static unsigned long GetFileID(const char* path);
    static unsigned char* GetFileHandle(const char* path);
    static bool GetFilePath(unsigned char* handle, std::string& filePath);
    static int SRenameFile(const char* pathFrom, const char* pathTo);
    static int RenameDirectory(const char* pathFrom, const char* pathTo);
    static int RemoveFolder(const char* path);
    static bool RemoveFile(const char* path);
    static void RemovePathFromFileTable(char* path);
public:
    CFileTable();
    ~CFileTable();
    unsigned long GetIDByPath(const char *path);
    unsigned char *GetHandleByPath(const char *path);
    bool GetPathByHandle(unsigned char *handle, std::string &path);
	tree_node_<FILE_ITEM>* FindItemByPath(const char *path);
    bool RemoveItem(const char *path);
	void RenameFile(const char *pathFrom, const char *pathTo);

    protected:
		tree_node_<FILE_ITEM>* AddItem(const char *path);

    private:
    FILE_TABLE *m_pFirstTable, *m_pLastTable;
    unsigned int m_nTableSize;
    CACHE_LIST *m_pCacheList;

	tree_node_<FILE_ITEM>* GetItemByID(unsigned int nID);
    void PutItemInCache(FILE_ITEM *pItem);


};

#endif
