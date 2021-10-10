# eLog
<p float="left">
    <p>Easy-to-use C++  log library</p>
    <img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/cplusplus/cplusplus-original.svg" width="32" />
</p>

## Platforms
<p float="left">
    <img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/linux/linux-original.svg" width="32" />
</p>

## Usage

```
#include "eLog.h"

int main()
{
    E_LOG(INFO, "Hello, %s\n", "world!");
    E_LOG(DEBUG, "Hello, %s\n", "world!");
    E_LOG(WARNING, "Hello, %s\n", "world!");
    E_LOG(ERROR, "Hello, %s\n", "world!");
}
```

## Output
```
[2021.10.10-13:22:44.464][        main.cpp][12972][       foo][   14][   INFO]: Hello, world!
[2021.10.10-13:22:44.464][        main.cpp][12972][       foo][   15][  DEBUG]: Hello, world!
[2021.10.10-13:22:44.464][        main.cpp][12972][       foo][   16][WARNING]: Hello, world!
[2021.10.10-13:22:44.464][        main.cpp][12972][       foo][   17][  ERROR]: Hello, world!
```

## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.