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
        cout << "Введите 1 для вывода списка дисков\n";
        cout << "Введите 2 для вывода информации о выбранном диске\n";
        cout << "Введите 3 для создания и удаления заданных каталогов\n";
        cout << "Введите 4 для создания файлов в новых каталогах\n";
        cout << "Введите 5 для копирования и перемещения файлов между каталогами\n";
        cout << "Введите 6 для анализа и изменения атрибутов файлов\n";
        cout << "Введите 7 для копирования файла с помощью операций перекрывающегося ввода-вывода\n";
        cout << "Введите 0 для выхода\n";
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
    cout << "Введите 1 для вывода списка дисков в виде последовательности бит\n";
    cout << "Введите 2 для вывода списка дисков в виде последовательности символов\n";
    cin >> tmp;
    answer = stoi(tmp);
    char buf[255];
    switch (answer) {
        case 1:
            dsk = GetLogicalDrives();
            for (int i = 0; i < 26; i++) {
                n = ((dsk >> i) & 1);
                if (n) {
                    cout << "Список дисков: " << char(65 + i) << ":\\" << endl;
                }
            }
            system("pause");
            break;
        case 2:
            dsk = GetLogicalDriveStrings(255, (LPSTR) buf);
            cout << "Список дисков: ";
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


    cout << "Введите название диска (пример: c:\\): ";
    cin >> disk_name;

    name = disk_name.c_str();
    x = GetDriveType(name);

    if (x == DRIVE_UNKNOWN) cout << "UNKNOWN (Неизвестный тип)" << endl;
    if (x == DRIVE_NO_ROOT_DIR) cout << "DRIVE NO ROOT DIR (Неправильный путь)" << endl;
    if (x == DRIVE_REMOVABLE) cout << "REMOVABLE (Съёмный диск)" << endl;
    if (x == DRIVE_FIXED) cout << "FIXED (Фиксированный диск)" << endl;
    if (x == DRIVE_REMOTE) cout << "REMOTE (Удалённый диск)" << endl;
    if (x == DRIVE_CDROM) cout << "CDROM (CD-ROM диск)" << endl;
    if (x == DRIVE_RAMDISK) cout << "RAMDISK (RAM диск)" << endl;

    //GetVolumeInfomation
    if (!GetVolumeInformation(name, (LPSTR) (lpVolumeNameBuffer), sizeof(lpVolumeNameBuffer), &lpVolumeSerialNumber,
                              &lpMaximumComponentLength, &lpFileSystemFlags,
                              (LPSTR) (lpFileSystemNameBuffer), sizeof(lpFileSystemNameBuffer))) {
        cout << "Ошибка. Не удалось обработать запрос" << endl;
    } else {
        cout << "Название указанного диска: " << (char *) lpVolumeNameBuffer << endl;
        cout << "Cерийный номер диска: " << (unsigned long) lpVolumeSerialNumber << endl;
        cout << "Максимальная длина файла: " << dec << lpMaximumComponentLength << endl;
        cout << "Опции файловой системы: " << endl;

        //Расшифровка lpFileSystemFlags

        if (lpFileSystemFlags & FILE_CASE_PRESERVED_NAMES)
            cout << " - Указанный том поддерживает сохраненный регистр имен файлов, когда он помещает имя на диск."
                 << endl;
        if (lpFileSystemFlags & FILE_CASE_SENSITIVE_SEARCH)
            cout << " - Указанный том поддерживает имена файлов с учетом регистра." << endl;
        if (lpFileSystemFlags & FILE_DAX_VOLUME)
            cout << " - Указанный том является томом прямого доступа (DAX)." << endl;
        if (lpFileSystemFlags & FILE_FILE_COMPRESSION)
            cout << " - Указанный том поддерживает сжатие файлов." << endl;
        if (lpFileSystemFlags & FILE_NAMED_STREAMS)
            cout << " - Указанный том поддерживает именованные потоки." << endl;
        if (lpFileSystemFlags & FILE_PERSISTENT_ACLS)
            cout << " - Указанный том сохраняет и применяет списки управления доступом (ACL)." << endl;
        if (lpFileSystemFlags & FILE_READ_ONLY_VOLUME)
            cout << " - Указанный том доступен только для чтения." << endl;
        if (lpFileSystemFlags & FILE_SEQUENTIAL_WRITE_ONCE)
            cout << " - Указанный том поддерживает одну последовательную запись." << endl;
        if (lpFileSystemFlags & FILE_SUPPORTS_ENCRYPTION)
            cout << " - Указанный том поддерживает зашифрованную файловую систему (EFS)." << endl;
        if (lpFileSystemFlags & FILE_SUPPORTS_EXTENDED_ATTRIBUTES)
            cout << " - Указанный том поддерживает расширенные атрибуты." << endl;
        if (lpFileSystemFlags & FILE_SUPPORTS_HARD_LINKS)
            cout << " - Указанный том поддерживает жесткие ссылки." << endl;
        if (lpFileSystemFlags & FILE_SUPPORTS_OBJECT_IDS)
            cout << " - Указанный том поддерживает идентификаторы объектов." << endl;
        if (lpFileSystemFlags & FILE_SUPPORTS_OPEN_BY_FILE_ID)
            cout << " - Файловая система поддерживает открытие по FileID." << endl;
        if (lpFileSystemFlags & FILE_SUPPORTS_REPARSE_POINTS)
            cout << " - Указанный том поддерживает точки повторного разбора." << endl;
        if (lpFileSystemFlags & FILE_SUPPORTS_SPARSE_FILES)
            cout << " - Указанный том поддерживает разреженные файлы." << endl;
        if (lpFileSystemFlags & FILE_SUPPORTS_TRANSACTIONS)
            cout << " - Указанный том поддерживает транзакции." << endl;
        if (lpFileSystemFlags & FILE_SUPPORTS_USN_JOURNAL)
            cout << " - Указанный том поддерживает журналы обновления порядковых номеров (USN)." << endl;
        if (lpFileSystemFlags & FILE_UNICODE_ON_DISK)
            cout << " - Указанный том поддерживает Unicode в именах файлов по мере их появления на диске." << endl;
        if (lpFileSystemFlags & FILE_VOLUME_IS_COMPRESSED)
            cout << " - Указанный том является сжатым томом." << endl;
        if (lpFileSystemFlags & FILE_VOLUME_QUOTAS)
            cout << " - Указанный том поддерживает дисковые квоты." << endl;
        if (lpFileSystemFlags & FILE_SUPPORTS_BLOCK_REFCOUNTING)
            cout
                    << " - Указанный том поддерживает совместное использование логических кластеров между файлами на одном томе."
                    << endl;

        //Конец расшифровка lpFileSystemFlags

        cout << "Имя файловой системы: " << (char *) lpFileSystemNameBuffer << endl;
    }

    //GetFreeDiskSpace

    if (GetDiskFreeSpace(name, &sectorsPerCluster, &bytesPerSector,
                         &numberOfFreeClusters, &totalNumberOfClusters)) {
        cout << endl << "Число секторов в кластере: " << sectorsPerCluster << endl;
        cout << "Число байт в секторе: " << bytesPerSector << endl;
        cout << "Число свободных кластеров: " << numberOfFreeClusters << endl;
        cout << "Общее число кластеров: " << totalNumberOfClusters << endl;
    }
    system("pause");
}

void DiskChange() {
    string disk_name;

    LPCSTR direct_name;

    string tmp;
    int answer;
    cout << "Введите 1 для создания каталога\n";
    cout << "Введите 2 для удаления каталога\n";
    cin >> tmp;
    answer = stoi(tmp);
    cout << "Введите имя каталога (пример: c:\\folder): ";
    cin >> disk_name;
    direct_name = disk_name.c_str();
    switch (answer) {
        case 1:
            //CreateDirectory
            if (!CreateDirectory(direct_name, nullptr)) {
                cout << "Каталог не удалось создать! Ошибка." << endl;
            } else {
                cout << "Каталог создан." << endl;
            }
            system("pause");
            break;
        case 2:
            //RemoveDirectory
            if (!RemoveDirectory(direct_name)) {
                cout << "Каталог не удалось удалить! Ошибка." << endl;
            } else {
                cout << "Каталог удален." << endl;
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

    cout << "Введите имя файла (пример: c:\\folder\\example.txt): ";
    cin >> disk_name;

    //CreateFile
    file_name = disk_name.c_str();
    if (CreateFile(file_name, GENERIC_WRITE | GENERIC_READ,
                   FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                   nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr) == INVALID_HANDLE_VALUE) {
        cout << "Файл не удалось создать. Код ошибки: " << GetLastError();
    } else {
        cout << "Файл успешно создан." << endl;
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
    cout << "Введите 1 для копирования файла\n";
    cout << "Введите 2 для перемещения файла\n";
    cout << "Введите 3 для перемещения файла с проверкой на повторения\n";
    cin >> tmp;
    answer = stoi(tmp);
    cout << "Введите имя файла-источника (пример: c:\\folder\\example.txt): ";
    cin >> disk_name;
    cout << "Введите адрес назначения (пример: c:\\folder\\example.txt): ";
    cin >> disk_name2;

    firstFile = disk_name.c_str();
    secondFile = disk_name2.c_str();
    switch (answer) {
        case 1:
            //CopyFile
            if (CopyFile(firstFile, secondFile, false)) {
                cout << "Файл успешно скопирован." << endl;
            } else {
                cout << "Ошибка! Не удалось скопировать файл. Код ошибки: " << GetLastError() << endl;
            }
            system("pause");
            break;

        case 2:
            //MoveFile
            if (MoveFile(firstFile, secondFile)) {
                cout << "Файл успешно перемещен." << endl;
            } else {
                cout << "Ошибка! Не удалось переместить файл. Код ошибки: " << GetLastError() << endl;
            }
            system("pause");
            break;
        case 3:
            //MoveFileEx
            moveFileEx_temp = 0;
            if (MoveFileEx(firstFile, secondFile, NULL)) {
                cout << "Файл или каталог успешно перемещен!" << endl;
            } else if (GetLastError() == 183) {
                cout << "Уже существует такой файл в данном каталоге. Заменить его?" << endl;
                cout << "1 - Да" << endl;
                cout << "0 - Нет" << endl;
                cin >> moveFileEx_temp;
                if (moveFileEx_temp) {
                    if (MoveFileEx(firstFile, secondFile, MOVEFILE_REPLACE_EXISTING)) {
                        cout << "Файл или каталог успешно перемещен!" << endl;
                    } else {
                        cout << "Ошибка! Не удалось переместить файл. Код ошибки: " << GetLastError() << endl;
                    }
                }
            } else {
                cout << "Ошибка! Не удалось переместить файл. Код ошибки: " << GetLastError() << endl;
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
    cout << "Введите 1 для вывода атрибутов файла\n";
    cout << "Введите 2 для установки атрибутов файла\n";
    cout << "Введите 3 для получения информации о файле по дескриптору\n";
    cout << "Введите 4 для получения информации о времени файла\n";
    cout << "Введите 5 для установки времени файла\n";
    cout << "Введите 0 для выхода\n";
    cin >> tmp;
    answer = stoi(tmp);
    cout << "Введите имя файла (пример: c:\\folder\\example.txt): ";
    cin >> disk_name;
    file_name = disk_name.c_str();
    switch (answer) {
        case 1:
            attribute = GetFileAttributes(file_name);
            if (attribute == 0) {
                cout << "Ошибка! Не удалось получить атрибуты файла." << endl;
            } else if (attribute == -1) {
                cout << "Ошибка! Файл не найден." << endl;
            } else {
                cout << "Атрибуты файла (" << attribute << "):" << endl;
                if (FILE_ATTRIBUTE_ARCHIVE & attribute) cout << "- Архивный файл" << endl;
                if (FILE_ATTRIBUTE_COMPRESSED & attribute) cout << "- Сжатый файл" << endl;
                if (FILE_ATTRIBUTE_DIRECTORY & attribute) cout << "- Каталог" << endl;
                if (FILE_ATTRIBUTE_HIDDEN & attribute) cout << "- Скрытый файл или каталог" << endl;
                if (FILE_ATTRIBUTE_NORMAL & attribute) cout << "- Файл не имеет атрибутов" << endl;
                if (FILE_ATTRIBUTE_READONLY & attribute) cout << "- Файл только для чтения" << endl;
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
                cout << " Произошла ошибка. Код ошибки: " << GetLastError() << endl;
            else {
                FileAttributes = infoFile.dwFileAttributes;
                if (FileAttributes == -1)
                    cout << " Файл " << disk_name << " не найден." << endl;
                else {

                    cout << "Информация о файле по дескриптору:" << endl;

                    if (FileAttributes & FILE_ATTRIBUTE_ARCHIVE)
                        cout << " Файл " << disk_name << " - архивный." << endl;
                    if (FileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                        cout << " Файл " << disk_name << " - директория." << endl;
                    if (FileAttributes & FILE_ATTRIBUTE_READONLY)
                        cout << " Файл " << disk_name << " - только для чтения." << endl;
                    if (FileAttributes & FILE_ATTRIBUTE_SYSTEM)
                        cout << " Файл " << disk_name << " - системный." << endl;
                    if (FileAttributes & FILE_ATTRIBUTE_COMPRESSED)
                        cout << " Файл " << disk_name << " - сжатый." << endl;
                    if (FileAttributes & FILE_ATTRIBUTE_HIDDEN)
                        cout << " Файл " << disk_name << " - скрытый." << endl;
                    if (FileAttributes & FILE_ATTRIBUTE_NORMAL)
                        cout << " Таких атрибутов файл " << disk_name << " не имеет.";
                    if (FileAttributes == 0)
                        cout << " Произошла ошибка. Код ошибки: " << GetLastError() << endl;
                }

                cout << " Старшая часть уникального идентификатора связи с файлом: " << infoFile.nFileIndexHigh << endl;
                cout << " Порядковый номер тома, который содержит файл: " << infoFile.dwVolumeSerialNumber << endl;
                cout << " Старшая часть размера файла: " << infoFile.nFileSizeHigh << endl;
                cout << " Младшая часть размера файла: " << infoFile.nFileSizeLow << endl;
                cout << " Число связей с этим файлом: " << infoFile.nNumberOfLinks << endl;
                cout << " Младшая часть уникального идентификатора связи с файлом: " << infoFile.nFileIndexLow << endl;
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
                cout << "Дата и время создания файла: " <<
                     time.wYear << "/" << time.wMonth << "/" << time.wDay << "   " << time.wHour << ":" <<
                     time.wMinute << ":" << time.wSecond << endl;
                FileTimeToSystemTime(&timeLastAccess, &time);
                cout << "Дата и время последнего обращения к файлу: " <<
                     time.wYear << "/" << time.wMonth << "/" << time.wDay << "   " << time.wHour << ":" <<
                     time.wMinute << ":" << time.wSecond << endl;
                FileTimeToSystemTime(&timeLastWrite, &time);
                cout << "Дата и время последней модификации файла: " <<
                     time.wYear << "/" << time.wMonth << "/" << time.wDay << "   " << time.wHour << ":" <<
                     time.wMinute << ":" << time.wSecond << endl;
            } else {
                cout << "Ошибка! Не удалось получить информацию о файле. Код ошибки: " << GetLastError() << endl;
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
                cout << "Атрибуты времени заменены успешно!" << endl;
            } else {
                cout << "Ошибка! Код ошибки: " << GetLastError() << endl;
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
    cout << "Введите 1 для изменения атрибута файла на архивный файл\n";
    cout << "Введите 2 для изменения атрибута файла на скрытый файл\n";
    cout << "Введите 3 для изменения атрибута файла на файл без атрибутов\n";
    cout << "Введите 4 для изменения атрибута файла на файл только чтения\n";
    cout << "Введите 5 для изменения атрибута файла на системный файл\n";
    cout << "Введите 0 для выхода\n";
    cin >> tmp;
    answer = stoi(tmp);
    switch (answer) {
        case 1:
            if (SetFileAttributes(file_name,
                                  FILE_ATTRIBUTE_ARCHIVE)) {
                cout << "Атрибут файла успешно изменен!" << endl;
            } else {
                cout << "Ошибка! Не удалось изменить атрибут файла. Код ошибки: " << GetLastError() << endl;
            }
            break;
        case 2:
            if (SetFileAttributes(file_name,
                                  FILE_ATTRIBUTE_HIDDEN)) {
                cout << "Атрибут файла успешно изменен!" << endl;
            } else {
                cout << "Ошибка! Не удалось изменить атрибут файла. Код ошибки: " << GetLastError() << endl;
            }
            break;
        case 3:
            if (SetFileAttributes(file_name,
                                  FILE_ATTRIBUTE_NORMAL)) {
                cout << "Атрибут файла успешно изменен!" << endl;
            } else {
                cout << "Ошибка! Не удалось изменить атрибут файла. Код ошибки: " << GetLastError() << endl;
            }
            break;
        case 4:
            if (SetFileAttributes(file_name,
                                  FILE_ATTRIBUTE_READONLY)) {
                cout << "Атрибут файла успешно изменен!" << endl;
            } else {
                cout << "Ошибка! Не удалось изменить атрибут файла. Код ошибки: " << GetLastError() << endl;
            }
            break;
        case 5:
            if (SetFileAttributes(file_name,
                                  FILE_ATTRIBUTE_SYSTEM)) {
                cout << "Атрибут файла успешно изменен!" << endl;
            } else {
                cout << "Ошибка! Не удалось изменить атрибут файла. Код ошибки: " << GetLastError() << endl;
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
    printf("Введите размер блока: 4096 * ");
    cin >> blockSize;
    printf("Введите число операций: ");
    cin >> operations;
    printf("Введите полный путь первого файла (c:\\folder\\example.txt): ");
    cin >> tmp1;
    p1 = tmp1.c_str();
    printf("Введите полный путь второго файла (c:\\folder\\example.txt): ");
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
        printf("Файл успешно скопирован\n");
    else
        printf("Копирование файла завершилось с ошибкой: %lu\n", GetLastError());

    printf("Затрачено времени: %.3f\n", ((float) (timeEnd - timeStart) / 1000));
    CloseHandle(h1);
    CloseHandle(h2);
    system("pause");
}