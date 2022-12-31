#pragma once
#include <stdio.h>
#include <string.h>
#include "definitions.h"
/**
 * Opens the dictionary file.
 *
 * @returns -1 if fails to open file, 0 if succesful.
 */
int openFile()
{
    char fName[20] = "dict.txt";
    // gcc
    if ((fp = fopen(fName, "r")) == NULL)
    {
        return (-1);
    }

    // Visual Studio users
    // if ((fopen_s(&fp, fName, "r")) != NULL)
    // {
    //     return (-1);
    // }
    if (fp == NULL)
    {
        perror("Error opening file");
        return (-1);
    }
    return 0;
}

/**
 * Closes the file if it is open.
 *
 * @returns None
 */
void closeFile()
{
    if (fp)
    {
        fclose(fp);
    }
}
