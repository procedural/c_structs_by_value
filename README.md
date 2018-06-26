Passing structs by value
------------------------

Tested on Ubuntu 18.04, Clang 6.0.

`#define BY_VAL 1`, -O0

<img width="1000px" src="https://i.imgur.com/zhd7l4F.png" />

`#define BY_VAL 0`, -O0

<img width="1000px" src="https://i.imgur.com/YJkB9ce.png" />

`#define BY_VAL 1`, -O1

<img width="1000px" src="https://i.imgur.com/Y8XIV1H.png" />

`#define BY_VAL 0`, -O1

<img width="1000px" src="https://i.imgur.com/17aAaQI.png" />

`#define BY_VAL 1`, -O2

<img width="1000px" src="https://i.imgur.com/4rK03FL.png" />

`#define BY_VAL 0`, -O2

<img width="1000px" src="https://i.imgur.com/kQs3YBw.png" />