# Daemonizer

A small tool written to daemonize a process (linux based).

## How to use it

* It can be used in the init scripts of a program to daemonize itself
* It can be used as a tool for quick daemonization without modifying any codes (just a wrapper shell script)

## How to compile it

* First, you have to get [libsysapi](https://github.com/devnaga/libsysapi) project.
* Second, you have to compile the library with the following command

  ```cd libsysapi/ ; ./build.py```

* As the compilation proceeds, it also installs the library into the standard path (which is ```/usr/lib/```), and
it may ask you for root password. Go ahead and give the root password for it to install it in the standard path.

* Download this project [daemonize](https://github.com/devnaga/daemonize).

* Compile the project with the command

  ```make INCLUDES=/path/to/libsysapi/core/```

  usually in most cases the directory structure can be that both projects will be under same parent directory. In such
  cases you can just use the command as ```make INCLUDES=../libsysapi/core```

* You are all set now to execute the binary

## How to run

* see the help message of the binary by running ```./deamonize```

* Basically it asks you to give ```directory```, ```lockfile``` and ```processname``` with full path along with any of its
extra command line arguments. (There is no limit to the number of command line arguments your process can give to the ```deamonizer```)

* For ex: ```daemonizer / lockfile.lock /home/stuff/daemonizer/testdaemon```

  will daemonize the process (check to see if its running via ```ps -e | grep testdaemon```)


