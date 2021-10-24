# eLog
<p float="left">
    <p>Easy-to-use C++  log library</p>
    <img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/cplusplus/cplusplus-original.svg" width="32" />
</p>

## Platforms
<p float="left">
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
    E_LOG(INFO, "Hello, %s\n", "world!");
    E_LOG(DEBUG, "Hello, %s\n", "world!");
    E_LOG(WARNING, "Hello, %s\n", "world!");
    E_LOG(ERROR, "Hello, %s\n", "world!");
}
```

## Output

<p float="left">
    <img src="https://github.com/AHakan/eLog/blob/master/ss.png"/>
</p>


## Contributing
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

Please make sure to update tests as appropriate.