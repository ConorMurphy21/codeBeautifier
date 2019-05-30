
int main() {
    FILE *pFile;
    char buffer[100];

    pFile = fopen( "" , "" );
    if (pFile == NULL) perror( "" );
    else {
        while (!feof(pFile)) {
            if (fgets(buffer, 100, pFile) == NULL) break;
            fputs(buffer, stdout);
        }
        fclose(pFile);
    }
    return 0;
}
