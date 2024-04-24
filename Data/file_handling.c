#include "../Include/file_handling.h"

int count_files()
{
    DIR *dir;
    struct dirent *entry;
    int count = 0;
    char current_dir[1024];

    // Get the current working directory
    if (getcwd(current_dir, sizeof(current_dir)) == NULL) {
        perror("getcwd");
        return 1;
    }

    printf("Current working directory: %s\n", current_dir);

    // Construct the path to the 'files' subdirectory
    char files_dir[1024];
    snprintf(files_dir, sizeof(files_dir), "%s/%s", current_dir, "player_saves");

    printf("Attempting to open directory: %s\n", files_dir);

    // Open the directory
    dir = opendir(files_dir);
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    // Loop through each entry in the directory
    while ((entry = readdir(dir)) != NULL) {
        // Ignore "." and ".." entries
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            count++;
        }
    }

    // Close the directory
    closedir(dir);

    printf("Total files in 'files' subdirectory: %d\n", count);

    return 0;

}

int save_game()
{
    count_files();
    printf("Save game\n");
    return 1;
}

void load_game()
{
    count_files();
    printf("Load game\n");
}

void check_saves()
{
    printf("Check saves\n");
}
