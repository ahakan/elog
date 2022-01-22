# eLog
<p>Easy-to-use C++  log library</p>
<p>C++11 version</p>

<p float="left">
    <img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/cplusplus/cplusplus-original.svg" width="32" />
    <img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/linux/linux-original.svg" width="32" />
</p>

## Compiling

#### Header only version
Copy the include [folder](https://github.com/AHakan/eLog/tree/master/inc) to your build tree and use a C++11 compiler.

## Usage

```
#include "eLog.h"

int main()
{
    E_LOG(INFO, "Hello, %s", "world!");
    E_LOG(DEBUG, "Hello, %s", "world!");
    E_LOG(WARNING, "Hello, %s", "world!");
    E_LOG(ERROR, "Hello, %s", "world!");
}
```

## Configuration
What to do for console output?
```
#define  LOG_CONSOLE_OR_FILE    0                               // 0=Console
```

What to do to write to file?
```
#define  LOG_CONSOLE_OR_FILE    1                               // 1=File
```

How to set log level?
```
#define  MAX_LEVEL    1                                         // 1 = Info, 
                                                                // 2 = Info, Debug, 
                                                                // 3 = Info, Debug, Warning,
                                                                // 4 = Info, Debug, Warning, Error
```

If you want you can change the default configurations.
```
#define  MAX_LEVEL              4
#define  MAX_FILE_SIZE          26214400                        // 25MB

#define  MAX_LINE_SIZE          5
#define  MAX_TID_SIZE           6
#define  MAX_LEVEL_SIZE         7
#define  MAX_FILE_NAME_SIZE     14
#define  MAX_FUNC_NAME_SIZE     12
```

## Output

### Log file
<p float="left">
    <img src="https://github.com/AHakan/eLog/blob/master/ss.png"/>
</p>

### Console
<p float="left">
    <img src="https://github.com/AHakan/eLog/blob/master/ss-console.png"/>
</p>

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.