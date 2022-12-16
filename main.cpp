#include <iostream>
#include <string>
#include <windows.h>

void DiskList();

void DiskInfo();

void DiskChange();

void FileCreate();

void FileCopy();

void FileAtribute();

void SetAtr(LPCSTR file_name);

void Task2();

int completions = 0;

VOID CALLBACK Completion(DWORD dwErrorCode, DWORD dwNumberOfBytesTransfered, LPOVERLAPPED lpOverlapped) { completions++; }

using namespace std;

int main() {
    string tmp;
    setlocale(LC_ALL, "RU");
    int answer;
    do {
        system("cls");
        cout << "������� 1 ��� ������ ������ ������\n";
        cout << "������� 2 ��� ������ ���������� � ��������� �����\n";
        cout << "������� 3 ��� �������� � �������� �������� ���������\n";
        cout << "������� 4 ��� �������� ������ � ����� ���������\n";
        cout << "������� 5 ��� ����������� � ����������� ������ ����� ����������\n";
        cout << "������� 6 ��� ������� � ��������� ��������� ������\n";
        cout << "������� 7 ��� ����������� ����� � ������� �������� ���������������� �����-������\n";
        cout << "������� 0 ��� ������\n";
        cin >> tmp;
        answer = stoi(tmp);
        switch (answer) {
            case 1:
                DiskList();
                break;
            case 2:
                DiskInfo();
                break;
            case 3:
                DiskChange();
                break;
            case 4:
                FileCreate();
                break;
            case 5:
                FileCopy();
                break;
            case 6:
                FileAtribute();
                break;
            case 7:
                Task2();
                break;
            default:
                break;
        }
    } while (answer != 0);
    return 0;
}

void DiskList() {
    string tmp;
    setlocale(LC_ALL, "RU");
    int answer, n, dsk;
    cout << "������� 1 ��� ������ ������ ������ � ���� ������������������ ���\n";
    cout << "������� 2 ��� ������ ������ ������ � ���� ������������������ ��������\n";
    cin >> tmp;
    answer = stoi(tmp);
    char buf[255];
    switch (answer) {
        case 1:
            dsk = GetLogicalDrives();
            for (int i = 0; i < 26; i++) {
                n = ((dsk >> i) & 1);
                if (n) {
                    cout << "������ ������: " << char(65 + i) << ":\\" << endl;
                }
            }
            system("pause");
            break;
        case 2:
            dsk = GetLogicalDriveStrings(255, (LPSTR) buf);
            cout << "������ ������: ";
            for (int i = 0; i < dsk; ++i) {
                cout << buf[i] << " ";
            }
            system("pause");
            break;
        default:
            break;
    }
}

void DiskInfo() {
    string disk_name;

    LPCSTR name;
    UINT x;

    LPCSTR lpVolumeNameBuffer[MAX_PATH + 1];
    DWORD lpVolumeSerialNumber = 0;
    DWORD lpMaximumComponentLength = 0;
    DWORD lpFileSystemFlags = 0;
    LPCSTR lpFileSystemNameBuffer[MAX_PATH + 1];

    DWORD sectorsPerCluster;
    DWORD bytesPerSector;
    DWORD numberOfFreeClusters;
    DWORD totalNumberOfClusters;


    cout << "������� �������� ����� (������: c:\\): ";
    cin >> disk_name;

    name = disk_name.c_str();
    x = GetDriveType(name);

    if (x == DRIVE_UNKNOWN) cout << "UNKNOWN (����������� ���)" << endl;
    if (x == DRIVE_NO_ROOT_DIR) cout << "DRIVE NO ROOT DIR (������������ ����)" << endl;
    if (x == DRIVE_REMOVABLE) cout << "REMOVABLE (������� ����)" << endl;
    if (x == DRIVE_FIXED) cout << "FIXED (������������� ����)" << endl;
    if (x == DRIVE_REMOTE) cout << "REMOTE (�������� ����)" << endl;
    if (x == DRIVE_CDROM) cout << "CDROM (CD-ROM ����)" << endl;
    if (x == DRIVE_RAMDISK) cout << "RAMDISK (RAM ����)" << endl;

    //GetVolumeInfomation
    if (!GetVolumeInformation(name, (LPSTR) (lpVolumeNameBuffer), sizeof(lpVolumeNameBuffer), &lpVolumeSerialNumber,
                              &lpMaximumComponentLength, &lpFileSystemFlags,
                              (LPSTR) (lpFileSystemNameBuffer), sizeof(lpFileSystemNameBuffer))) {
        cout << "������. �� ������� ���������� ������" << endl;
    } else {
        cout << "�������� ���������� �����: " << (char *) lpVolumeNameBuffer << endl;
        cout << "C������� ����� �����: " << (unsigned long) lpVolumeSerialNumber << endl;
        cout << "������������ ����� �����: " << dec << lpMaximumComponentLength << endl;
        cout << "����� �������� �������: " << endl;

        //����������� lpFileSystemFlags

        if (lpFileSystemFlags & FILE_CASE_PRESERVED_NAMES)
            cout << " - ��������� ��� ������������ ����������� ������� ���� ������, ����� �� �������� ��� �� ����."
                 << endl;
        if (lpFileSystemFlags & FILE_CASE_SENSITIVE_SEARCH)
            cout << " - ��������� ��� ������������ ����� ������ � ������ ��������." << endl;
        if (lpFileSystemFlags & FILE_DAX_VOLUME)
            cout << " - ��������� ��� �������� ����� ������� ������� (DAX)." << endl;
        if (lpFileSystemFlags & FILE_FILE_COMPRESSION)
            cout << " - ��������� ��� ������������ ������ ������." << endl;
        if (lpFileSystemFlags & FILE_NAMED_STREAMS)
            cout << " - ��������� ��� ������������ ����������� ������." << endl;
        if (lpFileSystemFlags & FILE_PERSISTENT_ACLS)
            cout << " - ��������� ��� ��������� � ��������� ������ ���������� �������� (ACL)." << endl;
        if (lpFileSystemFlags & FILE_READ_ONLY_VOLUME)
            cout << " - ��������� ��� �������� ������ ��� ������." << endl;
        if (lpFileSystemFlags & FILE_SEQUENTIAL_WRITE_ONCE)
            cout << " - ��������� ��� ������������ ���� ���������������� ������." << endl;
        if (lpFileSystemFlags & FILE_SUPPORTS_ENCRYPTION)
            cout << " - ��������� ��� ������������ ������������� �������� ������� (EFS)." << endl;
        if (lpFileSystemFlags & FILE_SUPPORTS_EXTENDED_ATTRIBUTES)
            cout << " - ��������� ��� ������������ ����������� ��������." << endl;
        if (lpFileSystemFlags & FILE_SUPPORTS_HARD_LINKS)
            cout << " - ��������� ��� ������������ ������� ������." << endl;
        if (lpFileSystemFlags & FILE_SUPPORTS_OBJECT_IDS)
            cout << " - ��������� ��� ������������ �������������� ��������." << endl;
        if (lpFileSystemFlags & FILE_SUPPORTS_OPEN_BY_FILE_ID)
            cout << " - �������� ������� ������������ �������� �� FileID." << endl;
        if (lpFileSystemFlags & FILE_SUPPORTS_REPARSE_POINTS)
            cout << " - ��������� ��� ������������ ����� ���������� �������." << endl;
        if (lpFileSystemFlags & FILE_SUPPORTS_SPARSE_FILES)
            cout << " - ��������� ��� ������������ ����������� �����." << endl;
        if (lpFileSystemFlags & FILE_SUPPORTS_TRANSACTIONS)
            cout << " - ��������� ��� ������������ ����������." << endl;
        if (lpFileSystemFlags & FILE_SUPPORTS_USN_JOURNAL)
            cout << " - ��������� ��� ������������ ������� ���������� ���������� ������� (USN)." << endl;
        if (lpFileSystemFlags & FILE_UNICODE_ON_DISK)
            cout << " - ��������� ��� ������������ Unicode � ������ ������ �� ���� �� ��������� �� �����." << endl;
        if (lpFileSystemFlags & FILE_VOLUME_IS_COMPRESSED)
            cout << " - ��������� ��� �������� ������ �����." << endl;
        if (lpFileSystemFlags & FILE_VOLUME_QUOTAS)
            cout << " - ��������� ��� ������������ �������� �����." << endl;
        if (lpFileSystemFlags & FILE_SUPPORTS_BLOCK_REFCOUNTING)
            cout
                    << " - ��������� ��� ������������ ���������� ������������� ���������� ��������� ����� ������� �� ����� ����."
                    << endl;

        //����� ����������� lpFileSystemFlags

        cout << "��� �������� �������: " << (char *) lpFileSystemNameBuffer << endl;
    }

    //GetFreeDiskSpace

    if (GetDiskFreeSpace(name, &sectorsPerCluster, &bytesPerSector,
                         &numberOfFreeClusters, &totalNumberOfClusters)) {
        cout << endl << "����� �������� � ��������: " << sectorsPerCluster << endl;
        cout << "����� ���� � �������: " << bytesPerSector << endl;
        cout << "����� ��������� ���������: " << numberOfFreeClusters << endl;
        cout << "����� ����� ���������: " << totalNumberOfClusters << endl;
    }
    system("pause");
}

void DiskChange() {
    string disk_name;

    LPCSTR direct_name;

    string tmp;
    int answer;
    cout << "������� 1 ��� �������� ��������\n";
    cout << "������� 2 ��� �������� ��������\n";
    cin >> tmp;
    answer = stoi(tmp);
    cout << "������� ��� �������� (������: c:\\folder): ";
    cin >> disk_name;
    direct_name = disk_name.c_str();
    switch (answer) {
        case 1:
            //CreateDirectory
            if (!CreateDirectory(direct_name, nullptr)) {
                cout << "������� �� ������� �������! ������." << endl;
            } else {
                cout << "������� ������." << endl;
            }
            system("pause");
            break;
        case 2:
            //RemoveDirectory
            if (!RemoveDirectory(direct_name)) {
                cout << "������� �� ������� �������! ������." << endl;
            } else {
                cout << "������� ������." << endl;
            }
            system("pause");
            break;
        default:
            break;
    }
}

void FileCreate() {
    LPCSTR file_name;
    string disk_name;

    cout << "������� ��� ����� (������: c:\\folder\\example.txt): ";
    cin >> disk_name;

    //CreateFile
    file_name = disk_name.c_str();
    if (CreateFile(file_name, GENERIC_WRITE | GENERIC_READ,
                   FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                   nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr) == INVALID_HANDLE_VALUE) {
        cout << "���� �� ������� �������. ��� ������: " << GetLastError();
    } else {
        cout << "���� ������� ������." << endl;
    }

    system("pause");
}

void FileCopy() {
    LPCSTR firstFile;
    LPCSTR secondFile;
    string disk_name;
    string disk_name2;

    int moveFileEx_temp;
    string tmp;
    int answer;
    cout << "������� 1 ��� ����������� �����\n";
    cout << "������� 2 ��� ����������� �����\n";
    cout << "������� 3 ��� ����������� ����� � ��������� �� ����������\n";
    cin >> tmp;
    answer = stoi(tmp);
    cout << "������� ��� �����-��������� (������: c:\\folder\\example.txt): ";
    cin >> disk_name;
    cout << "������� ����� ���������� (������: c:\\folder\\example.txt): ";
    cin >> disk_name2;

    firstFile = disk_name.c_str();
    secondFile = disk_name2.c_str();
    switch (answer) {
        case 1:
            //CopyFile
            if (CopyFile(firstFile, secondFile, false)) {
                cout << "���� ������� ����������." << endl;
            } else {
                cout << "������! �� ������� ����������� ����. ��� ������: " << GetLastError() << endl;
            }
            system("pause");
            break;

        case 2:
            //MoveFile
            if (MoveFile(firstFile, secondFile)) {
                cout << "���� ������� ���������." << endl;
            } else {
                cout << "������! �� ������� ����������� ����. ��� ������: " << GetLastError() << endl;
            }
            system("pause");
            break;
        case 3:
            //MoveFileEx
            moveFileEx_temp = 0;
            if (MoveFileEx(firstFile, secondFile, NULL)) {
                cout << "���� ��� ������� ������� ���������!" << endl;
            } else if (GetLastError() == 183) {
                cout << "��� ���������� ����� ���� � ������ ��������. �������� ���?" << endl;
                cout << "1 - ��" << endl;
                cout << "0 - ���" << endl;
                cin >> moveFileEx_temp;
                if (moveFileEx_temp) {
                    if (MoveFileEx(firstFile, secondFile, MOVEFILE_REPLACE_EXISTING)) {
                        cout << "���� ��� ������� ������� ���������!" << endl;
                    } else {
                        cout << "������! �� ������� ����������� ����. ��� ������: " << GetLastError() << endl;
                    }
                }
            } else {
                cout << "������! �� ������� ����������� ����. ��� ������: " << GetLastError() << endl;
            }
            system("pause");
            break;
        default:
            break;
    }

}

void FileAtribute() {
    string disk_name;
    string disk_name2;
    LPCSTR file_name;
    string tmp;
    int answer;
    DWORD attribute;

    LPCSTR fileLPC;

    HANDLE fileT;

    FILETIME timeCreate, timeLastAccess, timeLastWrite;
    FILETIME fileTime;

    SYSTEMTIME time;
    SYSTEMTIME systemTime;
    cout << "������� 1 ��� ������ ��������� �����\n";
    cout << "������� 2 ��� ��������� ��������� �����\n";
    cout << "������� 3 ��� ��������� ���������� � ����� �� �����������\n";
    cout << "������� 4 ��� ��������� ���������� � ������� �����\n";
    cout << "������� 5 ��� ��������� ������� �����\n";
    cout << "������� 0 ��� ������\n";
    cin >> tmp;
    answer = stoi(tmp);
    cout << "������� ��� ����� (������: c:\\folder\\example.txt): ";
    cin >> disk_name;
    file_name = disk_name.c_str();
    switch (answer) {
        case 1:
            attribute = GetFileAttributes(file_name);
            if (attribute == 0) {
                cout << "������! �� ������� �������� �������� �����." << endl;
            } else if (attribute == -1) {
                cout << "������! ���� �� ������." << endl;
            } else {
                cout << "�������� ����� (" << attribute << "):" << endl;
                if (FILE_ATTRIBUTE_ARCHIVE & attribute) cout << "- �������� ����" << endl;
                if (FILE_ATTRIBUTE_COMPRESSED & attribute) cout << "- ������ ����" << endl;
                if (FILE_ATTRIBUTE_DIRECTORY & attribute) cout << "- �������" << endl;
                if (FILE_ATTRIBUTE_HIDDEN & attribute) cout << "- ������� ���� ��� �������" << endl;
                if (FILE_ATTRIBUTE_NORMAL & attribute) cout << "- ���� �� ����� ���������" << endl;
                if (FILE_ATTRIBUTE_READONLY & attribute) cout << "- ���� ������ ��� ������" << endl;
            }
            system("pause");
            break;
        case 2:
            SetAtr(file_name);
            system("pause");
            break;
        case 3:
            long handleInfo, FileAttributes;
            BY_HANDLE_FILE_INFORMATION infoFile;
            HANDLE handleFile;

            handleFile = CreateFileA((LPCSTR) disk_name.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0,
                                     nullptr);
            handleInfo = GetFileInformationByHandle(handleFile, &infoFile);
            if (!handleInfo)
                cout << " ��������� ������. ��� ������: " << GetLastError() << endl;
            else {
                FileAttributes = infoFile.dwFileAttributes;
                if (FileAttributes == -1)
                    cout << " ���� " << disk_name << " �� ������." << endl;
                else {

                    cout << "���������� � ����� �� �����������:" << endl;

                    if (FileAttributes & FILE_ATTRIBUTE_ARCHIVE)
                        cout << " ���� " << disk_name << " - ��������." << endl;
                    if (FileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                        cout << " ���� " << disk_name << " - ����������." << endl;
                    if (FileAttributes & FILE_ATTRIBUTE_READONLY)
                        cout << " ���� " << disk_name << " - ������ ��� ������." << endl;
                    if (FileAttributes & FILE_ATTRIBUTE_SYSTEM)
                        cout << " ���� " << disk_name << " - ���������." << endl;
                    if (FileAttributes & FILE_ATTRIBUTE_COMPRESSED)
                        cout << " ���� " << disk_name << " - ������." << endl;
                    if (FileAttributes & FILE_ATTRIBUTE_HIDDEN)
                        cout << " ���� " << disk_name << " - �������." << endl;
                    if (FileAttributes & FILE_ATTRIBUTE_NORMAL)
                        cout << " ����� ��������� ���� " << disk_name << " �� �����.";
                    if (FileAttributes == 0)
                        cout << " ��������� ������. ��� ������: " << GetLastError() << endl;
                }

                cout << " ������� ����� ����������� �������������� ����� � ������: " << infoFile.nFileIndexHigh << endl;
                cout << " ���������� ����� ����, ������� �������� ����: " << infoFile.dwVolumeSerialNumber << endl;
                cout << " ������� ����� ������� �����: " << infoFile.nFileSizeHigh << endl;
                cout << " ������� ����� ������� �����: " << infoFile.nFileSizeLow << endl;
                cout << " ����� ������ � ���� ������: " << infoFile.nNumberOfLinks << endl;
                cout << " ������� ����� ����������� �������������� ����� � ������: " << infoFile.nFileIndexLow << endl;
            }
            CloseHandle(handleFile);
            cout << endl;

            system("pause");
            break;
        case 4:
            //GetFileTime
            fileLPC = disk_name.c_str();
            fileT = CreateFileA(fileLPC, GENERIC_READ,
                                FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr,
                                OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
            if (GetFileTime(fileT, &timeCreate, &timeLastAccess, &timeLastWrite)) {
                FileTimeToSystemTime(&timeCreate, &time);
                cout << "���� � ����� �������� �����: " <<
                     time.wYear << "/" << time.wMonth << "/" << time.wDay << "   " << time.wHour << ":" <<
                     time.wMinute << ":" << time.wSecond << endl;
                FileTimeToSystemTime(&timeLastAccess, &time);
                cout << "���� � ����� ���������� ��������� � �����: " <<
                     time.wYear << "/" << time.wMonth << "/" << time.wDay << "   " << time.wHour << ":" <<
                     time.wMinute << ":" << time.wSecond << endl;
                FileTimeToSystemTime(&timeLastWrite, &time);
                cout << "���� � ����� ��������� ����������� �����: " <<
                     time.wYear << "/" << time.wMonth << "/" << time.wDay << "   " << time.wHour << ":" <<
                     time.wMinute << ":" << time.wSecond << endl;
            } else {
                cout << "������! �� ������� �������� ���������� � �����. ��� ������: " << GetLastError() << endl;
            }
            system("pause");
            break;
        case 5:
            //SetFileTime
            fileLPC = disk_name.c_str();
            fileT = CreateFileA(fileLPC, GENERIC_READ | GENERIC_WRITE,
                                FILE_SHARE_DELETE | FILE_SHARE_READ | FILE_SHARE_WRITE,
                                nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
            GetSystemTime(&systemTime);
            SystemTimeToFileTime(&systemTime, &fileTime);
            if (SetFileTime(fileT, &fileTime, &fileTime, &fileTime)) {
                cout << "�������� ������� �������� �������!" << endl;
            } else {
                cout << "������! ��� ������: " << GetLastError() << endl;
            }
            system("pause");
            break;
        default:
            break;
    }
}

void SetAtr(LPCSTR file_name) {
    string tmp;
    int answer;
    cout << "������� 1 ��� ��������� �������� ����� �� �������� ����\n";
    cout << "������� 2 ��� ��������� �������� ����� �� ������� ����\n";
    cout << "������� 3 ��� ��������� �������� ����� �� ���� ��� ���������\n";
    cout << "������� 4 ��� ��������� �������� ����� �� ���� ������ ������\n";
    cout << "������� 5 ��� ��������� �������� ����� �� ��������� ����\n";
    cout << "������� 0 ��� ������\n";
    cin >> tmp;
    answer = stoi(tmp);
    switch (answer) {
        case 1:
            if (SetFileAttributes(file_name,
                                  FILE_ATTRIBUTE_ARCHIVE)) {
                cout << "������� ����� ������� �������!" << endl;
            } else {
                cout << "������! �� ������� �������� ������� �����. ��� ������: " << GetLastError() << endl;
            }
            break;
        case 2:
            if (SetFileAttributes(file_name,
                                  FILE_ATTRIBUTE_HIDDEN)) {
                cout << "������� ����� ������� �������!" << endl;
            } else {
                cout << "������! �� ������� �������� ������� �����. ��� ������: " << GetLastError() << endl;
            }
            break;
        case 3:
            if (SetFileAttributes(file_name,
                                  FILE_ATTRIBUTE_NORMAL)) {
                cout << "������� ����� ������� �������!" << endl;
            } else {
                cout << "������! �� ������� �������� ������� �����. ��� ������: " << GetLastError() << endl;
            }
            break;
        case 4:
            if (SetFileAttributes(file_name,
                                  FILE_ATTRIBUTE_READONLY)) {
                cout << "������� ����� ������� �������!" << endl;
            } else {
                cout << "������! �� ������� �������� ������� �����. ��� ������: " << GetLastError() << endl;
            }
            break;
        case 5:
            if (SetFileAttributes(file_name,
                                  FILE_ATTRIBUTE_SYSTEM)) {
                cout << "������� ����� ������� �������!" << endl;
            } else {
                cout << "������! �� ������� �������� ������� �����. ��� ������: " << GetLastError() << endl;
            }
            break;
        default:
            break;
    }
}

void Task2() {
    int blockSize, operations, totalBlockSize, iter;
    long fileSize, finalFileSize;
    char *buf1, *buf2, *pToBuf;
    bool firstRead = false, firstWrite = false;
    string tmp1, tmp2;
    LPCSTR p1, p2;
    HANDLE h1, h2;
    DWORD timeStart, timeEnd;
    OVERLAPPED *over1, *over2;
    printf("������� ������ �����: 4096 * ");
    cin >> blockSize;
    printf("������� ����� ��������: ");
    cin >> operations;
    printf("������� ������ ���� ������� ����� (c:\\folder\\example.txt): ");
    cin >> tmp1;
    p1 = tmp1.c_str();
    printf("������� ������ ���� ������� ����� (c:\\folder\\example.txt): ");
    cin >> tmp2;
    p2 = tmp2.c_str();
    timeStart = GetTickCount();
    totalBlockSize = 4096 * blockSize;
    h1 = CreateFile(p1, GENERIC_READ, NULL, nullptr, OPEN_EXISTING, FILE_FLAG_NO_BUFFERING | FILE_FLAG_OVERLAPPED,
                    nullptr);
    h2 = CreateFile(p2, GENERIC_READ | GENERIC_WRITE, NULL, nullptr, CREATE_ALWAYS,
                    FILE_FLAG_NO_BUFFERING | FILE_FLAG_OVERLAPPED, nullptr);
    fileSize = GetFileSize(h1, nullptr);
    finalFileSize = fileSize;
    pToBuf = new char[totalBlockSize * operations];
    over1 = new OVERLAPPED[operations];
    over2 = new OVERLAPPED[operations];
    for (int i = 0; i < operations; i++) {
        over1[i].Offset = 0;
        over1[i].OffsetHigh = 0;
        over1[i].hEvent = nullptr;
        over2[i].Offset = 0;
        over2[i].OffsetHigh = 0;
        over2[i].hEvent = nullptr;
    }

    do {
        completions = 0;
        iter = 0;
        buf1 = pToBuf;
        buf2 = pToBuf;
        for (int i = 0; i < operations; i++) {
            if (fileSize > 0) {
                iter++;
                if (firstRead) {
                    for (int j = 0; j < operations; j++) {
                        over1[j].Offset += totalBlockSize;
                    }
                }
                if (i) buf1 += totalBlockSize;
                firstRead = true;
                ReadFileEx(h1, buf1, totalBlockSize, &over1[i], Completion);
                fileSize -= totalBlockSize;
            }
        }
        while (completions < iter)
            SleepEx(-1, true);
        completions = 0;


        for (int i = 0; i < operations; i++) {
            if (firstWrite) {
                for (int j = 0; j < operations; j++) {
                    over2[j].Offset += totalBlockSize;
                }
            }
            if (i) buf2 += totalBlockSize;
            firstWrite = true;
            WriteFileEx(h2, buf2, totalBlockSize, &over2[i], Completion);
        }

        while (completions < iter)
            SleepEx(-1, true);

    } while (fileSize > 0);

    SetFilePointer(h2, finalFileSize, nullptr, FILE_BEGIN);
    SetEndOfFile(h2);
    timeEnd = GetTickCount();
    if (GetLastError() == ERROR_SUCCESS ||
        GetLastError() == ERROR_ALREADY_EXISTS)
        printf("���� ������� ����������\n");
    else
        printf("����������� ����� ����������� � �������: %lu\n", GetLastError());

    printf("��������� �������: %.3f\n", ((float) (timeEnd - timeStart) / 1000));
    CloseHandle(h1);
    CloseHandle(h2);
    system("pause");
}