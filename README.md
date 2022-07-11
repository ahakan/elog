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

[Usage](#usage) •
[Configuration](#configuration) •
[Output](#output) •
[Contribution](#contribution) 
<br>
<img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/cplusplus/cplusplus-original.svg" width="32" /> •
<img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/linux/linux-original.svg" width="32" />
</div>


## Usage
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
Copy src file with libelog.so and inc file to your project library folder and use it!


## Configuration
What to do for console output?
```
ELOG_OUTPUT(Elog::LogOutput::Console);
```

What to do to write to file?
```
ELOG_OUTPUT(Elog::LogOutput::File);
```

How to set log level?
```
ELOG_LEVEL(Elog::LogLevel::Info); => Info, Debug, Warning, Error
ELOG_LEVEL(Elog::LogLevel::Debug); => Debug, Warning, Error
ELOG_LEVEL(Elog::LogLevel::Warning); => Warning, Error
ELOG_LEVEL(Elog::LogLevel::Error); => Error
```

If you want you can change the default configurations.
```
ELOG_FILESIZE(Elog::ByteSize::MB1);
ELOG_TIDCOLSIZE(Elog::Size::Six);
ELOG_LINECOLSIZE(Elog::Size::Five);
ELOG_LEVELCOLSIZE(Elog::Size::Eight);
ELOG_FILENAMECOLSIZE(Elog::Size::Ten);
ELOG_FUNCNAMECOLSIZE(Elog::Size::Ten);
```

## Usage

```
#include "elog.h"

int main()
{
    ELOG_LEVEL(Elog::LogLevel::Info);
    ELOG_OUTPUT(Elog::LogOutput::File);
    ELOG_FILESIZE(Elog::ByteSize::MB1);

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
    <img src="https://github.com/AHakan/elog/blob/master/images/ss.png"/>
</p>

### Console
<p float="left">
    <img src="https://github.com/AHakan/elog/blob/master/images/ss-console.png"/>
</p>

## Contribution
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.


[elog]: https://github.com/ahakan/elog.git
