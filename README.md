# ns
ns stands for nimble status. It is written for dwm, and supports using X root window name (think of `xsetroot -name`) and `stdout` using the `-s` command line argument. 
Supports showing `cmus` info (will not show if nothing is playing), uptime, load average, ram usage, how long the last status took to generate, and the date. Can be configured using config.h.

Compile using `make`, install using `sudo make install`, and remove using `sudo make clean`. By default will install to `/usr/local/bin/`.

Sample output:

`04:36 / 06:09 SongName.mp3 | up 1 day, 18:31 | 2.25 | 5723MiB | 0.000326s | Saturday July 17 05:21:19 PM`

To edit which elements show up in the status, edit `status_components` in `config.h`. Each component will appear in the order specified.
You can also customize the separator (by default is ` | `)

The time is formatted using `strftime`. You can specify a custom format in `config.h`.
