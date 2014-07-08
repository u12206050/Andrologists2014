#include "DatabasePersistRequest.h"

 DatabasePersistRequest:: DatabasePersistRequest(string filename, QDateTime timestamp)
 {
      originalImageFilename = filename;
      timeStamp = timestamp;
 }
