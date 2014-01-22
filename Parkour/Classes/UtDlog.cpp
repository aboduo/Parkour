//
//  UtDlog.cpp
//  Parkour
//
//  Created by sanren on 14-1-12.
//
//

#include "UtDlog.h"

static bool isOpen = true;

void UtDlog::showLog(const char * pszFormat, ...)
{
    if (!isOpen)
    {
        return;
    }
    
    printf("Adam: ");
    char szBuf[kMaxLogLen+1] = {0};
    va_list ap;
    va_start(ap, pszFormat);
    vsnprintf(szBuf, kMaxLogLen, pszFormat, ap);
    va_end(ap);
    printf("%s", szBuf);
    printf("\n");
}