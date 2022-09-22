# hostupd
A small daemon that periodically pings a lists of hosts and stores the results in an SQLite database.

## Requirements:
- `ping` package provided by iputils or some other implementation with an equivalent syntax and stdout.
- SQLite3 library. By default the CMake file expects to find it on `lib/sqlite3`.
- Does not require root access to run.
- CMake

## Build instructions:
1. Download the SQLite C source code from sqlite.org and uncompress it to the `lib/sqlite3` directory.
2. build with `cmake . && make`

## Usage instructions:
Once built the binary expects a configuration file called `hostupd.conf` in the same path where the binary is. See `hostupd.conf.example`. The database file is located in the same directory and stored as `hostupd.db`, it will be automatically created at startup with the required tables for newly added hosts.

## Database format:
Each host has it's own table with the following columns:
```	
  "min"	NUMERIC,          //minimum response time in ms
  "avg"	NUMERIC,            //average response time in ms
  "max"	NUMERIC,            //maximum response time in ms
  "packet_loss"	NUMERIC,    //packet loss %
  "time"	INTEGER,          //total time elapsed by the ping command
  "date"	INTEGER,          //epoch time when the measurment was made
  ```
