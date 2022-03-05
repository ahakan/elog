<!-- markdownlint-configure-file {
  "MD013": {
    "code_blocks": false,
    "tables": false
  },
  "MD033": false,
  "MD041": false
} -->

<div align="center">

# elog

Easy-to-use C++ log library

[Installation](#installation) •
[Configuration](#configuration) •
[Output](#output) •
[Contributing](#contributing) 
<br>
<img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/cplusplus/cplusplus-original.svg" width="32" /> •
<img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/linux/linux-original.svg" width="32" />
</div>


## Installation
### *Step 1: Clone elog*

Clone [elog][elog].

```sh
git clone https://github.com/ahakan/elog.git  
```

### *Step 2: Build elog*
```sh
cd elog
mkdir build && cd build
cmake ..
make  
```
### *Step 3: Copy library file*
Copy src file with libelog.a and inc file to your project library folder and use it!


## Configuration
What to do for console output?
```
#define  LOG_CONSOLE_OR_FILE    0                   // 0=Console
```

What to do to write to file?
```
#define  LOG_CONSOLE_OR_FILE    1                   // 1=File
```

How to set log level?
```
#define  MAX_LEVEL              4                   // 1 = Error, 
                                                    // 2 = Error, Warning, 
                                                    // 3 = Error, Warning, Debug, 
                                                    // 4 = Error, Warning, Debug, Info
```

If you want you can change the default configurations.
```
#define  LOG_CONSOLE_OR_FILE    1                   // 1=File
#define  MAX_LEVEL              4                   // 1 = Error, 
                                                    // 2 = Error, Warning, 
                                                    // 3 = Error, Warning, Debug, 
                                                    // 4 = Error, Warning, Debug, Info
#define  MAX_FILE_SIZE          26214400            // 25MB

#define  MAX_LINE_SIZE          5
#define  MAX_TID_SIZE           6
#define  MAX_LEVEL_SIZE         7
#define  MAX_FILE_NAME_SIZE     14
#define  MAX_FUNC_NAME_SIZE     12
#define  MAX_MESSAGE_LENGTH     2048  
```

## Usage

```
#include "elog.h"

int main()
{
    int i = 0; 
    std::string world = "world!";

    ELOG(INFO, "Hello, %s", world.c_str());
    ELOG(DEBUG, "Hello, %d", i);
    ELOG(WARNING, "Hello, %s", "world!");
    ELOG(ERROR, "Hello, %s", "world!");
}
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


[elog]: https://github.com/ahakan/elog.git
